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

#include "ax_sensor_struct.h"
#include "ax_base_type.h"
#include "ax_isp_common.h"
#include "isp_sensor_internal.h"
#include "isp_sensor_types.h"
#include "isp_sensor_internal.h"

#include "sc200ai.h"
#include "sc200ai_settings.h"
#include "sc200ai_reg.h"
#include "sc200ai_ae_ctrl.h"

/* default param */
#include "sc200ai_sdr.h"
#include "sc200ai_sdr_qs.h"
#include "sc200ai_hdr_2x.h"
/****************************************************************************
 * golbal variables  and macro definition
 ****************************************************************************/

/****************************************************************************
 * Internal function definition
 ****************************************************************************/
static AX_S32 sensor_ctx_init(ISP_PIPE_ID nPipeId)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_S32 ret = 0;

    SNS_DBG("sc200ai sensor_ctx_init. ret = %d\n", ret);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    if (AX_NULL == sns_obj) {
        sns_obj = (SNS_STATE_OBJ *)calloc(1, sizeof(SNS_STATE_OBJ));
        if (AX_NULL == sns_obj) {
            SNS_ERR("malloc g_szsc200aiCtx failed\r\n");
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

#if 0
/****************************************************************************
 * sensor control function
 ****************************************************************************/
static AX_S32 sc200ai_get_version(ISP_PIPE_ID nPipeId, AX_CHAR * ptSnsVerInfo)
{
    SNS_CHECK_PTR_VALID(ptSnsVerInfo);

    memcpy(ptSnsVerInfo, axera_module_version, sizeof(axera_module_version));

    return AX_SNS_SUCCESS;
}
#endif

static void sc200ai_init(ISP_PIPE_ID nPipeId)
{
    AX_S32 nRet = 0;
    AX_S32 nImagemode = 0;
    AX_S32 nSnsId = 0;
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

    /* 2. i2c init */
    sc200ai_i2c_init(nPipeId);
#if 0
    nRet = sc200ai_get_chipid(nPipeId, &nSnsId);
    if (nRet != AX_SNS_SUCCESS) {
        SNS_ERR("can't find sc200ai sensor id.\r\n");
    } else {
        SNS_DBG("sc200ai check chip id success.\r\n");
    }

    /* 3. config settings  */
    nImagemode = sns_obj->eImgMode;
    sc200ai_write_settings(nPipeId, nImagemode);
#endif
    /* 4. refresh ae param */
    sc200ai_cfg_aec_param(nPipeId);

    /* 5. refresh ae regs table */
    sc200ai_refresh_all_regs_from_tbl(nPipeId);

    sns_obj->bSyncInit = AX_FALSE;

    return;
}

static void sc200ai_exit(ISP_PIPE_ID nPipeId)
{
    if (nPipeId < 0 || (nPipeId >= AX_VIN_MAX_PIPE_NUM)) {
        return;
    }

    sc200ai_i2c_exit(nPipeId);
    sensor_ctx_exit(nPipeId);

    return;
}

static AX_S32 sc200ai_set_mode(ISP_PIPE_ID nPipeId, AX_SNS_ATTR_T *sns_mode)
{
    AX_S32 nRet = 0;
    AX_S32 setting_index = 0;
    AX_F32 setting_fps = 30.0;
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

    if (sns_mode->nWidth == 1920            &&
        sns_mode->nHeight == 1080           &&
        sns_mode->eRawType == AX_RT_RAW10   &&
        sns_mode->eSnsMode == AX_SNS_LINEAR_MODE)
    {
        setting_index = e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_SDR_60FPS;
        setting_fps = 60.0;
    }

    if(setting_index == 0) {
        SNS_ERR("it's not supported. pipe=%u, mode=%u_%u_%u_%u_%.2f\n", nPipeId,
                sns_mode->eSnsMode, sns_mode->nWidth, sns_mode->nHeight, sns_mode->eRawType, setting_fps);
        return AX_SNS_ERR_NOT_SUPPORT;
    }

    if (sns_mode->nSettingIndex > 0) {
        setting_index = sns_mode->nSettingIndex;
    }

    SNS_INFO("pipe=%u, setting_index:%d, mode=%u_%u_%u_%u_%.2f\n",
            nPipeId, setting_index, sns_mode->eSnsMode, sns_mode->nWidth,
            sns_mode->nHeight, sns_mode->eRawType, setting_fps);

    sns_obj->eImgMode = setting_index;
    sns_obj->sns_mode_obj.eHDRMode = sns_mode->eSnsMode;
    sns_obj->sns_mode_obj.nWidth = sns_mode->nWidth;
    sns_obj->sns_mode_obj.nHeight = sns_mode->nHeight;
    sns_obj->sns_mode_obj.fFrameRate = setting_fps;
    memcpy(&sns_obj->sns_attr_param, sns_mode, sizeof(AX_SNS_ATTR_T));

    return AX_SNS_SUCCESS;
}

static AX_S32 sc200ai_testpattern_ctrl(ISP_PIPE_ID nPipeId, AX_U32 on)
{
    return AX_SNS_SUCCESS;
}

/****************************************************************************
 * get module default parameters function
 ****************************************************************************/
static AX_S32 sc200ai_get_isp_default_params(ISP_PIPE_ID nPipeId, AX_SENSOR_DEFAULT_PARAM_T *ptDftParam)
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
    case AX_SNS_LINEAR_MODE:
        /* TODO: Users configure their own default parameters */
        AX_SENSOR_SET_DEFAULT_SPECIAL_PARAM(sdr_qs);
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
    default:
        SNS_ERR(" hdr mode %d error\n", nHdrmode);
        break;
    }

    return AX_SNS_SUCCESS;
}

AX_SYS_API_PUBLIC AX_SENSOR_REGISTER_FUNC_T gSnssc200aiObjQs = {

    /* sensor ctrl */
    .pfn_sensor_chipid                      = sc200ai_get_chipid,
    .pfn_sensor_init                        = sc200ai_init,
    .pfn_sensor_exit                        = sc200ai_exit,
    .pfn_sensor_reset                       = AX_NULL,
    .pfn_sensor_streaming_ctrl              = sc200ai_streaming_ctrl,
    .pfn_sensor_sleep_wakeup                = sc200ai_sleep_wakeup,
    .pfn_sensor_testpattern                 = sc200ai_testpattern_ctrl,

    .pfn_sensor_set_mode                    = sc200ai_set_mode,
    .pfn_sensor_get_mode                    = sc200ai_get_mode,
    .pfn_sensor_set_fps                     = sc200ai_set_fps,
    .pfn_sensor_get_fps                     = sc200ai_get_fps,
    .pfn_sensor_set_slaveaddr               = sc200ai_set_slaveaddr,

    /* communication : register read/write */
    .pfn_sensor_set_bus_info                = sc200ai_set_bus_info,
    .pfn_sensor_write_register              = sc200ai_write_register,
    .pfn_sensor_read_register               = sc200ai_read_register,

    /* default param */
    .pfn_sensor_get_default_params          = sc200ai_get_isp_default_params,
    .pfn_sensor_get_black_level             = sc200ai_get_black_level,

    /* ae ctrl */
    .pfn_sensor_get_hw_exposure_params      = sc200ai_get_hw_exposure_params,
    .pfn_sensor_get_gain_table              = sc200ai_get_gain_table,
    .pfn_sensor_set_again                   = sc200ai_set_again,
    .pfn_sensor_set_dgain                   = sc200ai_set_dgain,
    .pfn_sensor_hcglcg_ctrl                 = AX_NULL,

    .pfn_sensor_set_integration_time        = sc200ai_set_integration_time,
    .pfn_sensor_get_integration_time_range  = sc200ai_get_integration_time_range,
    .pfn_sensor_set_slow_fps                = sc200ai_set_fps,
    .pfn_sensor_get_slow_shutter_param      = sc200ai_get_slow_shutter_param,
    .pfn_sensor_get_sns_reg_info            = sc200ai_ae_get_sensor_reg_info,
};
