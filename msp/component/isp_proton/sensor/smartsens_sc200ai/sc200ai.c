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
#include "sc200ai_hdr_2x.h"

#include "ax_module_version.h"
/****************************************************************************
 * golbal variables  and macro definition
 ****************************************************************************/

SNS_STATE_OBJ *g_szsc200aiCtx[AX_VIN_MAX_PIPE_NUM] = {NULL};

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

AX_S32 sc200ai_get_chipid(ISP_PIPE_ID nPipeId, AX_S32 *pSnsId)
{
    AX_U32 sensor_id = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    sensor_id |= sc200ai_reg_read(nPipeId, 0x3107) << 8;
    sensor_id |= sc200ai_reg_read(nPipeId, 0x3108);

    SNS_DBG("sc200ai sensor_id: 0x%x\n", sensor_id);

    if (sensor_id != SC200AI_SENSOR_CHIP_ID) {
        SNS_ERR("Failed to read sc200ai sensor_id: 0x%x\n", sensor_id);
        return AX_SNS_ERR_UNKNOWN;
    }

    *pSnsId = sensor_id;

    return AX_SNS_SUCCESS;
}

static void sc200ai_init(ISP_PIPE_ID nPipeId)
{
    AX_S32 nRet = 0;
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

    sc200ai_get_chipid(nPipeId, &nSnsId);

    /* 3. config settings  */
    sc200ai_write_settings(nPipeId);

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

AX_S32 sc200ai_streaming_ctrl(ISP_PIPE_ID nPipeId, AX_U32 on)
{
    AX_S32 result = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    if (1 == on) {
        result = sc200ai_write_register(nPipeId, 0x0100, 0x01); // stream on
        SNS_DBG("sensor stream on!\n");
    } else {
        result = sc200ai_write_register(nPipeId, 0x0100, 0x00); // stream off
        usleep(50 * 1000);
        SNS_DBG("sensor stream off!\n");
    }
    if (result) {
        return result;
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_sleep_wakeup(ISP_PIPE_ID nPipeId, AX_SNS_SLEEP_WAKEUP_E eSleepWakeup)
{
    AX_S32 result = 0;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    if (AX_SNS_EVENT_WAKE_UP == eSleepWakeup) {
        result = sc200ai_write_register(nPipeId, 0x0100, 0x01); // wakeup
        SNS_DBG("sensor wakeup !\n");
    } else if (AX_SNS_EVENT_SLEEP == eSleepWakeup) {
        result = sc200ai_write_register(nPipeId, 0x0100, 0x00); // sleep
        SNS_DBG("sensor sleep !\n");
    }

    if (result) {
        return result;
    }

    return AX_SNS_SUCCESS;
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

    if (AX_SNS_SYNC_MASTER == sns_mode->eMasterSlaveSel) {
        if (sns_mode->nWidth == 1920            &&
            sns_mode->nHeight == 1080           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_LINEAR_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_MASTER;

        } else if (sns_mode->nWidth == 1920     &&
            sns_mode->nHeight == 1080           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_HDR_2X_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_MASTER;
        }
    } else if (AX_SNS_SYNC_SLAVE == sns_mode->eMasterSlaveSel) {
        if (sns_mode->nWidth == 1920            &&
            sns_mode->nHeight == 1080           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_LINEAR_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_SLAVE;

        } else if (sns_mode->nWidth == 1920     &&
            sns_mode->nHeight == 1080           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_HDR_2X_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_SLAVE;
        }
    } else {
        if (sns_mode->nWidth == 1920            &&
            sns_mode->nHeight == 1080           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_LINEAR_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS;

        } else if (sns_mode->nWidth == 1920     &&
            sns_mode->nHeight == 1080           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_HDR_2X_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS;

        /* 1920*1088 sdr */
        } else if (sns_mode->nWidth == 1920     &&
            sns_mode->nHeight == 1088           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_LINEAR_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1088_10BIT_SDR_30FPS;

        /* 1920*1088 hdr */
        } else if (sns_mode->nWidth == 1920     &&
            sns_mode->nHeight == 1088           &&
            sns_mode->eRawType == AX_RT_RAW10   &&
            sns_mode->eSnsMode == AX_SNS_HDR_2X_MODE)
        {
            setting_index = e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1088_10BIT_HDR_30FPS;
        }
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

AX_S32 sc200ai_get_mode(ISP_PIPE_ID nPipeId, AX_SNS_ATTR_T *pSnsMode)
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

static AX_S32 sc200ai_testpattern_ctrl(ISP_PIPE_ID nPipeId, AX_U32 on)
{
    AX_S32 value = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SNS_DBG("test pattern enable: %d\n", on);

    value = sc200ai_reg_read(nPipeId, 0x4501);

    value &= 0xF7;

    if (1 == on) {
        sc200ai_write_register(nPipeId, 0x4501, 0x08 | value); //bit3=1
    } else {
        sc200ai_write_register(nPipeId, 0x4501, 0x00 | value);
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_mirror_flip(ISP_PIPE_ID nPipeId, AX_SNS_MIRRORFLIP_TYPE_E eSnsMirrorFlip)
{
    AX_S32 ret = 0;
    AX_U32 value = 0;

    ret = sc200ai_read_register(nPipeId, 0x3221, &value);
    if(ret) {
        return ret;
    }

    value &= 0x99;

    switch (eSnsMirrorFlip) {
        default:
        case AX_SNS_MF_NORMAL:
            value |= 0x00;
            break;

        case AX_SNS_MF_MIRROR:
            value |= 0x06;      //bit[2:1]
            break;

        case AX_SNS_MF_FLIP:
            value |= 0x60;      //bit[6:5]
            break;

        case AX_SNS_MF_MIRROR_FLIP:
            value |= 0x66;
            break;
    }

    sc200ai_write_register(nPipeId, 0x3221, value);

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
        ptDftParam->ptDpc           = (typeof(ptDftParam->ptDpc))&dpc_param_sdr;
        ptDftParam->ptBlc           = (typeof(ptDftParam->ptBlc))&blc_param_sdr;
        ptDftParam->ptCsc           = (typeof(ptDftParam->ptCsc))&csc_param_sdr;
        ptDftParam->ptCa            = (typeof(ptDftParam->ptCa))&ca_param_sdr;
        ptDftParam->ptDemosaic      = (typeof(ptDftParam->ptDemosaic))&demosaic_param_sdr;
        ptDftParam->ptGic           = (typeof(ptDftParam->ptGic))&gic_param_sdr;
        ptDftParam->ptFcc           = (typeof(ptDftParam->ptFcc))&fcc_param_sdr;
        ptDftParam->ptGamma         = (typeof(ptDftParam->ptGamma))&gamma_param_sdr;
        ptDftParam->ptCc            = (typeof(ptDftParam->ptCc))&cc_param_sdr;
        ptDftParam->ptRltm          = (typeof(ptDftParam->ptRltm))&rltm_param_sdr;
        ptDftParam->ptRaw2dnr       = (typeof(ptDftParam->ptRaw2dnr))&raw2dnr_param_sdr;
        ptDftParam->ptDehaze        = (typeof(ptDftParam->ptDehaze))&dehaze_param_sdr;
        ptDftParam->ptDepurple      = (typeof(ptDftParam->ptDepurple))&depurple_param_sdr;
        ptDftParam->ptLsc           = (typeof(ptDftParam->ptLsc))&lsc_param_sdr;
        ptDftParam->ptSharpen       = (typeof(ptDftParam->ptSharpen))&sharpen_param_sdr;
        ptDftParam->ptScm           = (typeof(ptDftParam->ptScm))&scm_param_sdr;
        ptDftParam->ptYnr           = (typeof(ptDftParam->ptYnr))&ynr_param_sdr;
        ptDftParam->ptCnr           = (typeof(ptDftParam->ptCnr))&cnr_param_sdr;
        ptDftParam->ptCcmp          = (typeof(ptDftParam->ptCcmp))&ccmp_param_sdr;
        ptDftParam->ptYcproc        = (typeof(ptDftParam->ptYcproc))&ycproc_param_sdr;
        ptDftParam->ptHs2dlut       = (typeof(ptDftParam->ptHs2dlut))&hs2dlut_param_sdr;
        ptDftParam->ptYcrt          = (typeof(ptDftParam->ptYcrt))&ycrt_param_sdr;
        ptDftParam->ptAinr          = (typeof(ptDftParam->ptAinr))&ainr_param_sdr;
        ptDftParam->ptYuv3dnr       = (typeof(ptDftParam->ptYuv3dnr))&yuv3dnr_param_sdr;
        ptDftParam->ptAwbDftParam   = (typeof(ptDftParam->ptAwbDftParam))&awb_param_sdr;
        ptDftParam->ptAeDftParam    = (typeof(ptDftParam->ptAeDftParam))&ae_param_sdr;
        ptDftParam->ptLdc           = (typeof(ptDftParam->ptLdc))&ldc_param_sdr;
        ptDftParam->ptClp           = (typeof(ptDftParam->ptClp))&clp_param_sdr;
        ptDftParam->ptDis           = (typeof(ptDftParam->ptDis))&dis_param_sdr;
        ptDftParam->pIspMeParam     = (typeof(ptDftParam->pIspMeParam))&me_param_sdr;
        ptDftParam->ptNuc           = (typeof(ptDftParam->ptNuc))&nuc_param_sdr;
        ptDftParam->ptScene         = (typeof(ptDftParam->ptScene))&scene_param_sdr;
        break;

    case AX_SNS_HDR_2X_MODE:
        /* TODO: Users configure their own default parameters */
        ptDftParam->ptDpc           = (typeof(ptDftParam->ptDpc))&dpc_param_hdr_2x;
        ptDftParam->ptBlc           = (typeof(ptDftParam->ptBlc))&blc_param_hdr_2x;
        ptDftParam->ptCsc           = (typeof(ptDftParam->ptCsc))&csc_param_hdr_2x;
        ptDftParam->ptCa            = (typeof(ptDftParam->ptCa))&ca_param_hdr_2x;
        ptDftParam->ptDemosaic      = (typeof(ptDftParam->ptDemosaic))&demosaic_param_hdr_2x;
        ptDftParam->ptGic           = (typeof(ptDftParam->ptGic))&gic_param_hdr_2x;
        ptDftParam->ptFcc           = (typeof(ptDftParam->ptFcc))&fcc_param_hdr_2x;
        ptDftParam->ptDepurple      = (typeof(ptDftParam->ptDepurple))&depurple_param_hdr_2x;
        ptDftParam->ptHdr           = (typeof(ptDftParam->ptHdr))&hdr_param_hdr_2x;
        ptDftParam->ptGamma         = (typeof(ptDftParam->ptGamma))&gamma_param_hdr_2x;
        ptDftParam->ptCc            = (typeof(ptDftParam->ptCc))&cc_param_hdr_2x;
        ptDftParam->ptRltm          = (typeof(ptDftParam->ptRltm))&rltm_param_hdr_2x;
        ptDftParam->ptRaw2dnr       = (typeof(ptDftParam->ptRaw2dnr))&raw2dnr_param_hdr_2x;
        ptDftParam->ptDehaze        = (typeof(ptDftParam->ptDehaze))&dehaze_param_hdr_2x;
        ptDftParam->ptLsc           = (typeof(ptDftParam->ptLsc))&lsc_param_hdr_2x;
        ptDftParam->ptSharpen       = (typeof(ptDftParam->ptSharpen))&sharpen_param_hdr_2x;
        ptDftParam->ptScm           = (typeof(ptDftParam->ptScm))&scm_param_hdr_2x;
        ptDftParam->ptYnr           = (typeof(ptDftParam->ptYnr))&ynr_param_hdr_2x;
        ptDftParam->ptCnr           = (typeof(ptDftParam->ptCnr))&cnr_param_hdr_2x;
        ptDftParam->ptCcmp          = (typeof(ptDftParam->ptCcmp))&ccmp_param_hdr_2x;
        ptDftParam->ptYcproc        = (typeof(ptDftParam->ptYcproc))&ycproc_param_hdr_2x;
        ptDftParam->ptHs2dlut       = (typeof(ptDftParam->ptHs2dlut))&hs2dlut_param_hdr_2x;
        ptDftParam->ptYcrt          = (typeof(ptDftParam->ptYcrt))&ycrt_param_hdr_2x;
        ptDftParam->ptAinr          = (typeof(ptDftParam->ptAinr))&ainr_param_hdr_2x;
        ptDftParam->ptYuv3dnr       = (typeof(ptDftParam->ptYuv3dnr))&yuv3dnr_param_hdr_2x;
        ptDftParam->ptAwbDftParam   = (typeof(ptDftParam->ptAwbDftParam))&awb_param_hdr_2x;
        ptDftParam->ptAeDftParam    = (typeof(ptDftParam->ptAeDftParam))&ae_param_hdr_2x;
        ptDftParam->ptLdc           = (typeof(ptDftParam->ptLdc))&ldc_param_hdr_2x;
        ptDftParam->ptClp           = (typeof(ptDftParam->ptClp))&clp_param_hdr_2x;
        ptDftParam->ptDis           = (typeof(ptDftParam->ptDis))&dis_param_hdr_2x;
        ptDftParam->pIspMeParam     = (typeof(ptDftParam->pIspMeParam))&me_param_hdr_2x;
        ptDftParam->ptNuc           = (typeof(ptDftParam->ptNuc))&nuc_param_hdr_2x;
        ptDftParam->ptScene         = (typeof(ptDftParam->ptScene))&scene_param_hdr_2x;
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

AX_S32 sc200ai_get_black_level(ISP_PIPE_ID nPipeId, AX_SNS_BLACK_LEVEL_T *ptBlackLevel)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(ptBlackLevel);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    /* black level of linear mode */
    if (AX_SNS_LINEAR_MODE == sns_obj->sns_mode_obj.eHDRMode) {
        ptBlackLevel->nBlackLevel[0] = 1040;   /* linear mode 10bit sensor default blc 64(U10.0) --> 1024(U8.6) */
        ptBlackLevel->nBlackLevel[1] = 1040;
        ptBlackLevel->nBlackLevel[2] = 1040;
        ptBlackLevel->nBlackLevel[3] = 1040;
    } else {
        ptBlackLevel->nBlackLevel[0] = 1040;
        ptBlackLevel->nBlackLevel[1] = 1040;
        ptBlackLevel->nBlackLevel[2] = 1040;
        ptBlackLevel->nBlackLevel[3] = 1040;
    }

    return AX_SNS_SUCCESS;
}


AX_SYS_API_PUBLIC AX_SENSOR_REGISTER_FUNC_T gSnssc200aiObj = {

    /* sensor ctrl */
    .pfn_sensor_chipid                      = sc200ai_get_chipid,
    .pfn_sensor_init                        = sc200ai_init,
    .pfn_sensor_exit                        = sc200ai_exit,
    .pfn_sensor_reset                       = sc200ai_reset,
    .pfn_sensor_streaming_ctrl              = sc200ai_streaming_ctrl,
    .pfn_sensor_sleep_wakeup                = sc200ai_sleep_wakeup,
    .pfn_sensor_testpattern                 = sc200ai_testpattern_ctrl,
    .pfn_sensor_mirror_flip                 = sc200ai_mirror_flip,

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
