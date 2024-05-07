/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "i2c.h"
#include "ax_sensor_struct.h"
#include "ax_base_type.h"
#include "dummysensor_settings.h"
#include "ax_isp_common.h"
#include "isp_sensor_internal.h"
#include "isp_sensor_types.h"

/* default param */
#include "dummysensor_sdr.h"
#include "dummysensor_hdr_2x.h"

#include "ax_module_version.h"

/* Control print level */
static AX_F32 nAgainTable[SENSOR_MAX_GAIN_STEP];
static AX_F32 nDgainTable[SENSOR_MAX_GAIN_STEP];

/****************************************************************************
 * golbal variables  and macro definition                                                         *
 ****************************************************************************/

#ifndef EPS
    #define EPS         (1E-06)
#endif
#define SNS_1_SECOND_UNIT_US            (1000000)

static AX_SNS_COMMBUS_T gDummyBusInfo[AX_VIN_MAX_PIPE_NUM] = {0};
SNS_STATE_OBJ *sns_ctx[AX_VIN_MAX_PIPE_NUM] = {AX_NULL};

#define SENSOR_GET_CTX(dev, pstCtx) (pstCtx = sns_ctx[dev])
#define SENSOR_SET_CTX(dev, pstCtx) (sns_ctx[dev] = pstCtx)
#define SENSOR_RESET_CTX(dev) (sns_ctx[dev] = AX_NULL)

const char axera_sns_dummysensor_version[] = AXERA_MODULE_VERSION;

AX_S32 dummysensor_set_aecparam(ISP_PIPE_ID nPipeId);

/****************************************************************************
 * Internal function definition
 ****************************************************************************/
static AX_S32 sensor_ctx_init(ISP_PIPE_ID nPipeId)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_S32 ret = 0;

    SNS_DBG("dummysensor sensor_ctx_init. ret = %d\n", ret);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);

    if (AX_NULL == sns_obj) {
        sns_obj = (SNS_STATE_OBJ *)calloc(1, sizeof(SNS_STATE_OBJ));
        if (AX_NULL == sns_obj) {
            SNS_ERR("malloc sns_ctx failed\r\n");
            return AX_SNS_ERR_NOMEM;
        }
    }

    memset(sns_obj, 0, sizeof(SNS_STATE_OBJ));

    SENSOR_SET_CTX(nPipeId, sns_obj);

    return AX_SNS_SUCCESS;
}

static AX_VOID sensor_ctx_exit(ISP_PIPE_ID nPipeId)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SENSOR_GET_CTX(nPipeId, sns_obj);
    free(sns_obj);
    SENSOR_RESET_CTX(nPipeId);
}

/****************************************************************************
 * sensor control function
 ****************************************************************************/
static void dummysensor_init(ISP_PIPE_ID nPipeId)
{
    AX_S32 nImagemode = 0;
    AX_S32 nRet = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    if (nPipeId < 0 || (nPipeId >= AX_VIN_MAX_PIPE_NUM)) {
        return;
    }

    /* 1. contex init */
    SENSOR_GET_CTX(nPipeId, sns_obj);
    if (AX_NULL == sns_obj) {
        /* contex init */
        nRet = sensor_ctx_init(nPipeId);
        if (0 != nRet) {
            SNS_ERR("sensor_ctx_init failed!\n");
            return;
        } else {
            SENSOR_GET_CTX(nPipeId, sns_obj);
        }
    }

    /* 2. refresh ae param */
    dummysensor_set_aecparam(nPipeId);

    return;
}

static void dummysensor_exit(ISP_PIPE_ID nPipeId)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    if (nPipeId < 0 || (nPipeId >= AX_VIN_MAX_PIPE_NUM)) {
        return;
    }

    SENSOR_GET_CTX(nPipeId, sns_obj);
    if (AX_NULL == sns_obj) {
        SNS_ERR("dummysensor_exit sns_obj null\n");
        return;
    }

    sensor_ctx_exit(nPipeId);
    return;
}

static AX_S32 dummy_set_bus_info(ISP_PIPE_ID nPipeId, AX_SNS_COMMBUS_T tSnsBusInfo)
{
    gDummyBusInfo[nPipeId].I2cDev = tSnsBusInfo.I2cDev;

    return AX_SNS_SUCCESS;
}

static AX_S32 dummysensor_streaming_ctrl(ISP_PIPE_ID nPipeId, AX_U32 on)
{
    AX_S32 result = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    if (1 == on) {
    } else {
    }
    if (0 != result) {
        return AX_SNS_ERR_UNKNOWN;
    }
    usleep(300 * 1000);

    return AX_SNS_SUCCESS;
}

static AX_S32 dummysensor_sensor_set_mode(ISP_PIPE_ID nPipeId, AX_SNS_ATTR_T *sns_mode)
{
    AX_S32 width;
    AX_S32 height;
    AX_S32 hdrmode;
    AX_S32 framerate = 25; // init value to 30fps, void null fps gives.
    AX_S32 nRet = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(sns_mode);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    if (AX_NULL == sns_obj) {
        /* contex init */
        nRet = sensor_ctx_init(nPipeId);
        if (0 != nRet) {
            SNS_ERR("sensor_ctx_init failed!\n");
            return AX_SNS_ERR_NOT_INIT;
        } else {
            SENSOR_GET_CTX(nPipeId, sns_obj);
        }
    }

    width = sns_mode->nWidth;
    height = sns_mode->nHeight;
    framerate = sns_mode->fFrameRate;
    if ((1 != sns_mode->eSnsMode) &&
        (2 != sns_mode->eSnsMode) &&
        (3 != sns_mode->eSnsMode)) {
        hdrmode = 1;
    } else {
        hdrmode = sns_mode->eSnsMode;
    }

    sns_obj->sns_mode_obj.eHDRMode = hdrmode;
    sns_obj->sns_mode_obj.nWidth = width;
    sns_obj->sns_mode_obj.nHeight = height;
    sns_obj->sns_mode_obj.fFrameRate = framerate;
    memcpy(&sns_obj->sns_attr_param, sns_mode, sizeof(AX_SNS_ATTR_T));

    return AX_SNS_SUCCESS;
}

static AX_S32 dummysensor_sensor_get_mode(ISP_PIPE_ID nPipeId, AX_SNS_ATTR_T *pSnsMode)
{
    AX_S32 nRet = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(pSnsMode);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    if (AX_NULL == sns_obj) {
        /* contex init */
        nRet = sensor_ctx_init(nPipeId);
        if (0 != nRet) {
            SNS_ERR("sensor_ctx_init failed!\n");
            return AX_SNS_ERR_NOT_INIT;
        } else {
            SENSOR_GET_CTX(nPipeId, sns_obj);
        }
    }

    memcpy(pSnsMode, &sns_obj->sns_attr_param, sizeof(AX_SNS_ATTR_T));

    return AX_SNS_SUCCESS;
}


static AX_S32 dummysensor_testpattern_ctrl(ISP_PIPE_ID nPipeId, AX_U32 on)
{
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SNS_DBG("test pattern enable: %d\n", on);
    if (1 == on) {
    } else {
    }

    return AX_SNS_SUCCESS;
}

/****************************************************************************
 * get module default parameters function
 ****************************************************************************/
static AX_S32 dummy_get_isp_default_params(ISP_PIPE_ID nPipeId, AX_SENSOR_DEFAULT_PARAM_T *ptDftParam)
{
    AX_S32 nRet = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_SNS_HDR_MODE_E nHdrmode;

    SNS_CHECK_PTR_VALID(ptDftParam);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);


    SENSOR_GET_CTX(nPipeId, sns_obj);
    if (AX_NULL == sns_obj) {
        /* contex init */
        nRet = sensor_ctx_init(nPipeId);
        if (0 != nRet) {
            SNS_ERR("sensor_ctx_init failed!\n");
            return AX_SNS_ERR_NOT_INIT;
        } else {
            SENSOR_GET_CTX(nPipeId, sns_obj);
        }
    }

    memset(ptDftParam, 0, sizeof(AX_SENSOR_DEFAULT_PARAM_T));

    nHdrmode = sns_obj->sns_mode_obj.eHDRMode;

    SNS_DBG(" current hdr mode %d \n", nHdrmode);

    switch (nHdrmode) {
    default:
    case AX_SNS_LINEAR_MODE:
        /* TODO: Users configure their own default parameters */
        AX_SENSOR_SET_DEFAULT_LINEAR_PARAM();
        break;

    case AX_SNS_HDR_2X_MODE:
        /* TODO: Users configure their own default parameters */
        AX_SENSOR_SET_DEFAULT_HDR_2X_PARAM();
        break;

    case AX_SNS_HDR_3X_MODE:
        /* TODO: Users configure their own default parameters */
        break;

    case AX_SNS_HDR_4X_MODE:
        /* TODO: Users configure their own default parameters */
        break;
    }

    return AX_SNS_SUCCESS;
}

/* dummy sensor black level will overwrite by AX_ISP_SetPubAttr() */
static AX_S32 dummy_get_black_level(ISP_PIPE_ID nPipeId, AX_SNS_BLACK_LEVEL_T *ptBlackLevel)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(ptBlackLevel);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    /* black level of linear mode */
    if (AX_SNS_LINEAR_MODE == sns_obj->sns_mode_obj.eHDRMode) {
        ptBlackLevel->nBlackLevel[0] = 1024;  /* linear mode 10bit sensor default blc 64(U10.0) --> 1024(U8.6) */
        ptBlackLevel->nBlackLevel[1] = 1024;
        ptBlackLevel->nBlackLevel[2] = 1024;
        ptBlackLevel->nBlackLevel[3] = 1024;
    } else {
        ptBlackLevel->nBlackLevel[0] = 1024;
        ptBlackLevel->nBlackLevel[1] = 1024;
        ptBlackLevel->nBlackLevel[2] = 1024;
        ptBlackLevel->nBlackLevel[3] = 1024;
    }

    return AX_SNS_SUCCESS;
}
#if 0
static AX_S32 dummysensor_get_sensor_caps(ISP_PIPE_ID nPipeId, AX_SNS_CAP_T *params)
{
    SNS_CHECK_PTR_VALID(params);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);


    params->nSnsMode_caps = AX_SNS_LINEAR_MODE | AX_SNS_HDR_2X_MODE | AX_SNS_HDR_3X_MODE;
    params->nSnsRawType_caps = AX_SNS_RAWTYPE_12BIT;
    params->nSnsFps_caps = AX_SNS_25FPS;
    params->nSnsResolution_caps = AX_SNS_RES_2688_1520;
    return AX_SNS_SUCCESS;
}
#endif
/****************************************************************************
 * exposure control function
 ****************************************************************************/
AX_S32 dummysensor_set_aecparam(ISP_PIPE_ID nPipeId)
{
    AX_F32 vs_line_period = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    sns_obj->ae_ctrl_param.fSnsHcgLcgRatio = 4.05f;
    sns_obj->ae_ctrl_param.sns_ae_param.fCurFps = sns_obj->sns_mode_obj.fFrameRate;
    sns_obj->ae_ctrl_param.fTimePerLine = 10;

    /* sensor again  limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_LONG_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_LONG_FRAME_IDX] = 15.5;
    sns_obj->ae_ctrl_param.sns_ae_param.fAGainIncrement[HDR_LONG_FRAME_IDX] = (AX_F32)1 / 16;

    /* sensor dgain  limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_LONG_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_LONG_FRAME_IDX] = 15.99;
    sns_obj->ae_ctrl_param.sns_ae_param.fDGainIncrement[HDR_LONG_FRAME_IDX] = (AX_F32)1 / 1024;

    /* sensor medium again limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_MEDIUM_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_MEDIUM_FRAME_IDX] = 15.5;
    sns_obj->ae_ctrl_param.sns_ae_param.fAGainIncrement[HDR_MEDIUM_FRAME_IDX] = (AX_F32)1 / 16;

    /* sensor medium dgain limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_MEDIUM_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_MEDIUM_FRAME_IDX] = 15.99;
    sns_obj->ae_ctrl_param.sns_ae_param.fDGainIncrement[HDR_MEDIUM_FRAME_IDX] = (AX_F32)1 / 1024;

    sns_obj->ae_ctrl_param.sns_ae_limit.fMinRatio = 1.0;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxRatio = 16.0;

    if (IS_LINEAR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX] = 1;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] =
            1000000 / sns_obj->ae_ctrl_param.sns_ae_param.fCurFps / sns_obj->ae_ctrl_param.fTimePerLine;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_LONG_FRAME_IDX] = 1;
    } else if (IS_2DOL_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX] = 1;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] =
            1000000 / sns_obj->ae_ctrl_param.sns_ae_param.fCurFps / sns_obj->ae_ctrl_param.fTimePerLine;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_LONG_FRAME_IDX] = 1;

        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX] = 1;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX] =
            1000000 / sns_obj->ae_ctrl_param.sns_ae_param.fCurFps / sns_obj->ae_ctrl_param.fTimePerLine;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_MEDIUM_FRAME_IDX] = 1;
    } else {
        // wrong hdr mode
    }

    // sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_LONG_FRAME_IDX] = 2.0f;
    // sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_LONG_FRAME_IDX] = 1.0f;
    // sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX] = 8;
    // sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX] = 8;

    SNS_DBG("inttime min = %f, max = %f\n",
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX]);

    return AX_SNS_SUCCESS;
}

static AX_S32 dummysensor_set_again(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptAGain)
{
    AX_U8 Gain_in;
    AX_U8 Gain_de;
    AX_S32 result = 0;
    AX_F32 gain_value = 0;
    AX_F32 nGainFromUser = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptAGain);

    if (ptAGain->fGain[HDR_LONG_FRAME_IDX]) {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_LONG_FRAME_IDX] = ptAGain->fGain[HDR_LONG_FRAME_IDX];
    }

    if (ptAGain->fGain[HDR_MEDIUM_FRAME_IDX]) {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_MEDIUM_FRAME_IDX] = ptAGain->fGain[HDR_MEDIUM_FRAME_IDX];
    }

    if (ptAGain->fGain[HDR_SHORT_FRAME_IDX]) {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_SHORT_FRAME_IDX] = ptAGain->fGain[HDR_SHORT_FRAME_IDX];
    }

    return AX_SNS_SUCCESS;
}

static AX_S32 dummysensor_set_dgain(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptDGain)
{
    AX_U8 Gain_in;
    AX_U8 Gain_de;
    AX_U8 Gain_de2;
    AX_S32 result = 0;
    AX_F32 gain_value = 0;
    AX_F32 nGainFromUser = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptDGain);

    if (ptDGain->fGain[HDR_LONG_FRAME_IDX]) {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_LONG_FRAME_IDX] = ptDGain->fGain[HDR_LONG_FRAME_IDX];
    }

    if (ptDGain->fGain[HDR_MEDIUM_FRAME_IDX]) {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_MEDIUM_FRAME_IDX] = ptDGain->fGain[HDR_MEDIUM_FRAME_IDX];
    }

    if (ptDGain->fGain[HDR_SHORT_FRAME_IDX]) {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_SHORT_FRAME_IDX] = ptDGain->fGain[HDR_SHORT_FRAME_IDX];
    }

    return AX_SNS_SUCCESS;
}


/* Calculate the max int time according to the exposure ratio */
AX_S32 dummysensor_get_integration_time_range(ISP_PIPE_ID nPipeId, AX_F32 fHdrRatio,
        AX_SNS_AE_INT_TIME_RANGE_T *ptIntTimeRange)
{
    AX_F32 ratio = 0.0f;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptIntTimeRange);

    if (fabs(fHdrRatio) < EPS) {
        SNS_ERR("hdr ratio is error \n");
        return AX_SNS_ERR_ILLEGAL_PARAM;
    }

    if (AX_SNS_HDR_2X_MODE == sns_obj->sns_mode_obj.eHDRMode) {

        ratio = fHdrRatio;
        ratio = AXSNS_CLIP3(ratio, sns_obj->ae_ctrl_param.sns_ae_limit.fMinRatio, sns_obj->ae_ctrl_param.sns_ae_limit.fMaxRatio);
        if (fabs(ratio) <= EPS) {
            SNS_ERR("hdr ratio is error \n");
        }

        ptIntTimeRange->fMaxIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX];
        ptIntTimeRange->fMinIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX];
        ptIntTimeRange->fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX];
        ptIntTimeRange->fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX];

    } else if (AX_SNS_LINEAR_MODE == sns_obj->sns_mode_obj.eHDRMode) {

        ptIntTimeRange->fMaxIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX];
        ptIntTimeRange->fMinIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX];

    } else {
        // do nothing
    }

    return AX_SNS_SUCCESS;
}

AX_S32 dummysensor_set_integration_time(ISP_PIPE_ID nPipeId, AX_SNS_AE_SHUTTER_CFG_T *ptIntTime)
{
    AX_F32 fExpLineFromUser = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptIntTime);

    SNS_DBG("Exptime:%.2f-%.2f-%.2f-%.2f, Hdrratio:%.2f-%.2f-%.2f-%.2f\n",
            ptIntTime->fIntTime[0], ptIntTime->fIntTime[1], ptIntTime->fIntTime[2], ptIntTime->fIntTime[3],
            ptIntTime->fHdrRatio[0], ptIntTime->fHdrRatio[1], ptIntTime->fHdrRatio[2], ptIntTime->fHdrRatio[3]);

    fExpLineFromUser = ptIntTime->fIntTime[HDR_LONG_FRAME_IDX];

    fExpLineFromUser = AXSNS_CLIP3(fExpLineFromUser,
                                    sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX],
                                    sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX]);

    sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX] = fExpLineFromUser;

    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        fExpLineFromUser = ptIntTime->fIntTime[HDR_MEDIUM_FRAME_IDX];

        fExpLineFromUser = AXSNS_CLIP3(fExpLineFromUser,
                                        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX],
                                        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX]);

        sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX] = fExpLineFromUser;
    }

    sns_obj->sztRegsInfo[0].tSnsExpInfo.szExpTime[HDR_LONG_FRAME_IDX] =
        sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX];

    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        sns_obj->sztRegsInfo[0].tSnsExpInfo.szExpTime[HDR_MEDIUM_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX];
    }

    SNS_DBG("Exp line: long frame %d, short frame %d\n",
            sns_obj->sztRegsInfo[0].tSnsExpInfo.szExpTime[HDR_LONG_FRAME_IDX],
            sns_obj->sztRegsInfo[0].tSnsExpInfo.szExpTime[HDR_MEDIUM_FRAME_IDX]);

    return AX_SNS_SUCCESS;
}

AX_S32 dummysensor_hcglcg_ctrl(ISP_PIPE_ID nPipeId, AX_U32 nSnsHcgLcg)
{
    AX_U8 Gain_in = 0;
    AX_U8 hcglcg_value = 0;
    AX_U8 Gain_de = 0;
    AX_U32 result;
    AX_F32 gain_value = 0;
    float gain = 0.0f;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if (nSnsHcgLcg == AX_LCG_MODE) {
        SNS_DBG("%s: switch to LCG mode \n", __func__);
        sns_obj->ae_ctrl_param.eSnsHcgLcgMode = AX_LCG_MODE;
    } else if (nSnsHcgLcg == AX_HCG_MODE) {
        SNS_DBG("%s: switch to HCG mode \n", __func__);
        sns_obj->ae_ctrl_param.eSnsHcgLcgMode = AX_HCG_MODE;
    } else if (nSnsHcgLcg == AX_LCG_NOTSUPPORT_MODE) {
        SNS_DBG("%s: switch to LCG_NOTSUPPORT_MODE mode \n", __func__);
        sns_obj->ae_ctrl_param.eSnsHcgLcgMode = AX_LCG_NOTSUPPORT_MODE;
    }

    return AX_SNS_SUCCESS;
}


AX_S32 dummysensor_get_hw_exposure_params(ISP_PIPE_ID nPipeId, AX_SNS_EXP_CTRL_PARAM_T *ptAeCtrlParam)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(ptAeCtrlParam);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    memcpy(ptAeCtrlParam, &sns_obj->ae_ctrl_param, sizeof(AX_SNS_EXP_CTRL_PARAM_T));
    memcpy(&ptAeCtrlParam->sns_dev_attr, &sns_obj->sns_attr_param, sizeof(AX_SNS_ATTR_T));

    return AX_SNS_SUCCESS;
}

static AX_S32 dummysensor_get_gain_table(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_TABLE_T *params)
{
    AX_U32 i;
    AX_S32 d_max = 0;
    AX_S32 d_min = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    if (!params)
        return AX_SNS_ERR_NULL_PTR;

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    d_max = log10(sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_LONG_FRAME_IDX]) * (float)200 / 3;
    d_min = log10(sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_LONG_FRAME_IDX]) * (float)200 / 3;

    params->nAgainTableSize = d_max - d_min + 1;
    for (int i = d_min; i < (d_max + 1); i++) {
        nAgainTable[i] = pow(10, i * (float)3 / 200);
        params->pAgainTable = nAgainTable;
    }

    params->nDgainTableSize = d_max - d_min + 1;
    for (int i = d_min; i < (d_max + 1); i++) {
        nDgainTable[i] = pow(10, i * (float)3 / 200);
        params->pDgainTable = nDgainTable;
    }

    return AX_SNS_SUCCESS;
}
#if 0
static AX_S32 dummysensor_get_sensor_gain_table(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_TABLE_T *params)
{
    AX_S32 result = 0;
    SNS_CHECK_PTR_VALID(params);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    result = dummysensor_get_gain_table(nPipeId, params);

    return result;
}
#endif

AX_S32 dummysensor_reset(ISP_PIPE_ID nPipeId, AX_U32 nResetGpio)
{
    return AX_SNS_SUCCESS;
}

AX_SYS_API_PUBLIC AX_SENSOR_REGISTER_FUNC_T gSnsdummyObj = {

    /* sensor ctrl */
    .pfn_sensor_reset                       = dummysensor_reset,
    .pfn_sensor_chipid                      = AX_NULL,
    .pfn_sensor_init                        = dummysensor_init,
    .pfn_sensor_exit                        = dummysensor_exit,
    .pfn_sensor_streaming_ctrl              = dummysensor_streaming_ctrl,
    .pfn_sensor_testpattern                 = dummysensor_testpattern_ctrl,

    .pfn_sensor_set_mode                    = dummysensor_sensor_set_mode,
    .pfn_sensor_get_mode                    = dummysensor_sensor_get_mode,

    /* communication : register read/write */
    .pfn_sensor_set_bus_info                = dummy_set_bus_info,

    /* default param */
    .pfn_sensor_get_default_params          = dummy_get_isp_default_params,
    .pfn_sensor_get_black_level             = dummy_get_black_level,

    /* ae ctrl */
    .pfn_sensor_get_hw_exposure_params      = dummysensor_get_hw_exposure_params,
    .pfn_sensor_get_gain_table              = dummysensor_get_gain_table,
    .pfn_sensor_set_again                   = dummysensor_set_again,
    .pfn_sensor_set_dgain                   = dummysensor_set_dgain,
    .pfn_sensor_hcglcg_ctrl                 = dummysensor_hcglcg_ctrl,

    .pfn_sensor_set_integration_time        = dummysensor_set_integration_time,
    .pfn_sensor_get_integration_time_range  = dummysensor_get_integration_time_range,
    .pfn_sensor_set_fps                     = AX_NULL,
    .pfn_sensor_get_slow_shutter_param      = AX_NULL,
    .pfn_sensor_get_sns_reg_info            = AX_NULL,

};

