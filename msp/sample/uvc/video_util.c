/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <sys/prctl.h>
#include "video_util.h"

/* isp tuning */
#include "ax_vin_error_code.h"
#include "common_nt.h"
#include "ax_ivps_api.h"
#include "ax_buffer_tool.h"
#include "common_sys.h"
#include "common_isp.h"
#include "ax_isp_iq_api.h"

#define COLOR_COUNT 6

static AX_CAMERA_T gUVCCams[MAX_UVC_CAMERAS];

static SAMPLE_JPEGENC_RCMODE enRcMode = JPEGENC_CBR;

extern volatile AX_S32 uvc_exit;
pthread_t gDispatchFramePid[MAX_UVC_CAMERAS];

static YUV_T gArrYUVColor[COLOR_COUNT] = {
    {255, 128, 128},    //white
    {0, 128, 128},      //black
    {76, 85, 255},      //red
    {75, 85, 74},       //green
    {29, 255, 107},     //blue
    {52, 170, 181},     //purple
};

/* comm pool */
static COMMON_SYS_POOL_CFG_T stSysCommPoolSingleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 6, AX_COMPRESS_MODE_NONE, 0},     /* vin yuv use */
};

static COMMON_SYS_POOL_CFG_T stSysCommPoolDoubleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 12, AX_COMPRESS_MODE_NONE, 0},     /* vin yuv use */
};

static COMMON_SYS_POOL_CFG_T stSysCommPoolSingleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 4, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
    {1920, 1080, 1920, AX_FORMAT_YUV420_SEMIPLANAR, 4, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
};

static COMMON_SYS_POOL_CFG_T stSysCommPoolDoubleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 8, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
    {1920, 1080, 1920, AX_FORMAT_YUV420_SEMIPLANAR, 8, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
};

static COMMON_SYS_POOL_CFG_T stSysCommPoolSingleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 4, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
    {1920, 1080, 1920, AX_FORMAT_YUV420_SEMIPLANAR, 4, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
};

static COMMON_SYS_POOL_CFG_T stSysCommPoolDoubleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 8, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
    {1920, 1080, 1920, AX_FORMAT_YUV420_SEMIPLANAR, 8, AX_COMPRESS_MODE_NONE, 0}, /* vin yuv use */
};

/* private pool */
static COMMON_SYS_POOL_CFG_T stPrivPoolSingleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static COMMON_SYS_POOL_CFG_T stPrivPoolDoubleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP, 14, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static COMMON_SYS_POOL_CFG_T stPrivPoolSingleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static COMMON_SYS_POOL_CFG_T stPrivPoolDoubleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP, 14, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static COMMON_SYS_POOL_CFG_T stPrivPoolSingleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static COMMON_SYS_POOL_CFG_T stPrivPoolDoubleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP, 14, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static AX_VOID uvc_set_pipe_hdr_mode(AX_U32 *pHdrSel, AX_SNS_HDR_MODE_E eHdrMode)
{
    if (NULL == pHdrSel) {
        return;
    }

    switch (eHdrMode) {
    case AX_SNS_LINEAR_MODE:
        *pHdrSel = 0x1;
        break;

    case AX_SNS_HDR_2X_MODE:
        *pHdrSel = 0x1 | 0x2;
        break;

    case AX_SNS_HDR_3X_MODE:
        *pHdrSel = 0x1 | 0x2 | 0x4;
        break;

    case AX_SNS_HDR_4X_MODE:
        *pHdrSel = 0x1 | 0x2 | 0x4 | 0x8;
        break;

    default:
        *pHdrSel = 0x1;
        break;
    }
}
#if 0
static AX_S32 nv12_to_yuv422(AX_U32 width, AX_U32 height, AX_U8 *src_img, AX_U8 *dst_img)
{
    if (NULL == src_img || NULL == dst_img) {
        printf("invalid image pointer!\n");
        return -1;
    }

    AX_S32 y_src_index = 0;
    AX_S32 uv_src_index = 0;
    AX_S32 dst_index = 0;

    AX_U8 *src_uv = src_img + width * height;

    for (AX_S32 i = 0; i < height / 2; i++) {
        AX_S32 uv_width = width;
        for (AX_S32 j = 0; j < uv_width / 2; j++) {
            //Y
            dst_img[dst_index] = src_img[y_src_index];
            dst_img[dst_index + uv_width * 2] = src_img[y_src_index + uv_width];
            dst_index++;
            y_src_index++;

            //U
            dst_img[dst_index] = src_uv[uv_src_index];
            dst_img[dst_index + uv_width * 2] = src_uv[uv_src_index];
            dst_index++;

            //Y
            dst_img[dst_index] = src_img[y_src_index];
            dst_img[dst_index + uv_width * 2] = src_img[y_src_index + uv_width];
            dst_index++;
            y_src_index++;

            //V
            dst_img[dst_index] = src_uv[uv_src_index + 1];
            dst_img[dst_index + uv_width * 2] = src_uv[uv_src_index + 1];
            dst_index++;

            uv_src_index += 2;
        }
        dst_index += uv_width * 2;
        y_src_index += uv_width;
    }
    return AX_SUCCESS;
}
#endif

static AX_VOID uvc_set_vin_attr(AX_CAMERA_T *pCam, SAMPLE_SNS_TYPE_E eSnsType, AX_SNS_HDR_MODE_E eHdrMode, COMMON_VIN_MODE_E eSysMode, AX_S32 nAiispMode)
{
    pCam->eSnsType = eSnsType;
    pCam->tSnsAttr.eSnsMode = eHdrMode;
    pCam->tDevAttr.eSnsMode = eHdrMode;
    pCam->eHdrMode = eHdrMode;
    pCam->eSysMode = eSysMode;
    pCam->tPipeAttr[pCam->nPipeId].eSnsMode = eHdrMode;
    pCam->tPipeAttr[pCam->nPipeId].bAiIspEnable = nAiispMode == 0 ? AX_FALSE : AX_TRUE;
    if (eHdrMode > AX_SNS_LINEAR_MODE) {
        pCam->tDevAttr.eSnsOutputMode = AX_SNS_DOL_HDR;
    }

    if (COMMON_VIN_TPG == eSysMode) {
        pCam->tDevAttr.eSnsIntfType = AX_SNS_INTF_TYPE_TPG;
    }

    if (COMMON_VIN_LOADRAW == eSysMode) {
        pCam->bEnableDev = AX_FALSE;
    } else {
        pCam->bEnableDev = AX_TRUE;
    }

    pCam->bRegisterSns = AX_TRUE;

    return;
}

static AX_U32 uvc_init_dummy(AX_CAMERA_T *pCamList, UVC_VIN_PARAM_T *pParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_S32 i = 0;
    AX_CAMERA_T *pCam = NULL;
    pCam = &pCamList[0];
    pCommonArgs->nCamCnt = 2;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        pCam = &pCamList[i];
        pCam->nPipeId = i;
        COMMON_VIN_GetSnsConfig(pParam->eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);

        pCam->nDevId = i;
        if (i == 0) {
            pCam->nRxDev = 0;
        } else {
            pCam->nRxDev = 1;
        }
        pCam->tSnsClkAttr.nSnsClkIdx = i;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(pParam->eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(pParam->eSnsType);
        pCam->eLoadRawNode = pParam->eLoadRawNode;
        if (pParam->nCamCount == 2) {
            if (pParam->eHdrMode == AX_SNS_LINEAR_MODE) {
                pCam->tSnsAttr.nSettingIndex = 4;
            } else {
                pCam->tSnsAttr.nSettingIndex = 5;
            }
            pCam->tMipiAttr.eLaneNum = AX_MIPI_DATA_LANE_2;
        }

        uvc_set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], pParam->eHdrMode);
        uvc_set_vin_attr(pCam, pParam->eSnsType, pParam->eHdrMode, pParam->eSysMode, pParam->nAiispMode);
        for (AX_S32 j = 0; j < AX_VIN_MAX_PIPE_NUM; j++) {
            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pParam->nAiispMode == 0 ? AX_FALSE : AX_TRUE;;
            strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
        }
    }

    return AX_SUCCESS;
}

static AX_U32 uvc_init_os04a10(AX_CAMERA_T *pCamList, UVC_VIN_PARAM_T *pParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    AX_S32 j = 0, i = 0;
    pCommonArgs->nCamCnt = pParam->nCamCount;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        pCam = &pCamList[i];
        pCam->nPipeId = i;
        COMMON_VIN_GetSnsConfig(pParam->eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);

        pCam->nDevId = i;
        if (i == 0) {
            pCam->nRxDev = 0;
        } else {
            pCam->nRxDev = 1;
        }
        pCam->tSnsClkAttr.nSnsClkIdx = 0;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(pParam->eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(pParam->eSnsType);
        pCam->eLoadRawNode = pParam->eLoadRawNode;
        if (pParam->nCamCount == 2) {
            if (i == 0) {
                pCam->nI2cAddr = 0x36;
            } else {
                if (AX_SYS_GetChipType() == AX620Q_CHIP)
                    pCam->nI2cAddr = 0x10;
                else
                    pCam->nI2cAddr = 0x36;
            }

            if (pParam->eHdrMode == AX_SNS_LINEAR_MODE) {
                pCam->tSnsAttr.nSettingIndex = 4;
            } else {
                pCam->tSnsAttr.nSettingIndex = 5;
            }
            pCam->tMipiAttr.eLaneNum = AX_MIPI_DATA_LANE_2;
        }

        uvc_set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], pParam->eHdrMode);
        uvc_set_vin_attr(pCam, pParam->eSnsType, pParam->eHdrMode, pParam->eSysMode, pParam->nAiispMode);
        for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pParam->nAiispMode == 0 ? AX_FALSE : AX_TRUE;
            strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
        }
    }
    return 0;
}

static AX_U32 uvc_init_sc450ai(AX_CAMERA_T *pCamList, UVC_VIN_PARAM_T *pParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    AX_S32 j = 0, i = 0;
    pCommonArgs->nCamCnt = pParam->nCamCount;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        pCam = &pCamList[i];
        pCam->nPipeId = i;
        COMMON_VIN_GetSnsConfig(pParam->eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);

        pCam->nDevId = i;
        if (i == 0) {
            pCam->nRxDev = 0;
        } else {
            pCam->nRxDev = 1;
        }
        pCam->tSnsClkAttr.nSnsClkIdx = 0;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(pParam->eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(pParam->eSnsType);
        pCam->eLoadRawNode = pParam->eLoadRawNode;
        if (pParam->nCamCount == 2) {
            if (i == 0) {
                pCam->nI2cAddr = 0x30;
            } else {
                if (AX_SYS_GetChipType() == AX620Q_CHIP)
                    pCam->nI2cAddr = 0x31;
                else
                    pCam->nI2cAddr = 0x30;
            }

            if (pParam->eHdrMode == AX_SNS_LINEAR_MODE) {
                pCam->tSnsAttr.nSettingIndex = 6;
            } else {
                pCam->tSnsAttr.nSettingIndex = 7;
            }
            pCam->tMipiAttr.eLaneNum = AX_MIPI_DATA_LANE_2;
        }

        uvc_set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], pParam->eHdrMode);
        uvc_set_vin_attr(pCam, pParam->eSnsType, pParam->eHdrMode, pParam->eSysMode, pParam->nAiispMode);
        for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pParam->nAiispMode == 0 ? AX_FALSE : AX_TRUE;;
            /*
            if (pCam->tPipeInfo[j].bAiispEnable) {
                if (pParam->eHdrMode <= AX_SNS_LINEAR_MODE) {
                    strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/sc450ai_sdr_dual3dnr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
                } else {
                    strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/sc450ai_hdr_2x_ainr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
                }
            } else*/ {
                strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
            }
        }
    }
    return 0;
}

static AX_S32 init_sys_config(UVC_VIN_PARAM_T *pParam, COMMON_SYS_ARGS_T *pSysArg, COMMON_SYS_ARGS_T *pPrvPoolArg)
{
    printf("%s +++\n", __func__);

    if (NULL == pSysArg || NULL == pPrvPoolArg) {
        printf("sys_arg is NULL\n");
        return -1;
    }

	AX_CAMERA_T *pCamList = &gUVCCams[0];

    printf("sys_case %d, vin_mode %d, hdr_mode %d, sns_type %d, aiisp_mode %d\n",
            pParam->eSysCase, pParam->eSysMode, pParam->eHdrMode, pParam->eSnsType, pParam->nAiispMode);

	if (UVC_SYS_CASE_SINGLE_OS04A10 == pParam->eSysCase) {
		pSysArg->nPoolCfgCnt = sizeof(stSysCommPoolSingleOs04a10Sdr) / sizeof(stSysCommPoolSingleOs04a10Sdr[0]);
		pSysArg->pPoolCfg = stSysCommPoolSingleOs04a10Sdr;
		pPrvPoolArg->nPoolCfgCnt = sizeof(stPrivPoolSingleOs04a10Sdr) / sizeof(stPrivPoolSingleOs04a10Sdr[0]);
		pPrvPoolArg->pPoolCfg = stPrivPoolSingleOs04a10Sdr;
		uvc_init_os04a10(pCamList, pParam, pSysArg);
    } else if (UVC_SYS_CASE_DUAL_OS04A10 == pParam->eSysCase) {
		pSysArg->nPoolCfgCnt = sizeof(stSysCommPoolDoubleOs04a10Sdr) / sizeof(stSysCommPoolDoubleOs04a10Sdr[0]);
		pSysArg->pPoolCfg = stSysCommPoolDoubleOs04a10Sdr;
		pPrvPoolArg->nPoolCfgCnt = sizeof(stPrivPoolDoubleOs04a10Sdr) / sizeof(stPrivPoolDoubleOs04a10Sdr[0]);
		pPrvPoolArg->pPoolCfg = stPrivPoolDoubleOs04a10Sdr;
		uvc_init_os04a10(pCamList, pParam, pSysArg);
    } else if (UVC_SYS_CASE_SINGLE_DUMMY == pParam->eSysCase) {
		pSysArg->nPoolCfgCnt = sizeof(stSysCommPoolSingleDummySdr) / sizeof(stSysCommPoolSingleDummySdr[0]);
		pSysArg->pPoolCfg = stSysCommPoolSingleDummySdr;
		pPrvPoolArg->nPoolCfgCnt = sizeof(stPrivPoolSingleDummySdr) / sizeof(stPrivPoolSingleDummySdr[0]);
		pPrvPoolArg->pPoolCfg = stPrivPoolSingleDummySdr;
		uvc_init_dummy(pCamList, pParam, pSysArg);
    } else if (UVC_SYS_CASE_DUAL_DUMMY == pParam->eSysCase) {
		pSysArg->nPoolCfgCnt = sizeof(stSysCommPoolDoubleDummySdr) / sizeof(stSysCommPoolDoubleDummySdr[0]);
		pSysArg->pPoolCfg = stSysCommPoolDoubleDummySdr;
		pPrvPoolArg->nPoolCfgCnt = sizeof(stPrivPoolDoubleDummySdr) / sizeof(stPrivPoolDoubleDummySdr[0]);
		pPrvPoolArg->pPoolCfg = stPrivPoolDoubleDummySdr;
		uvc_init_dummy(pCamList, pParam, pSysArg);
    } else if (UVC_SYS_CASE_SINGLE_SC450AI == pParam->eSysCase) {
		pSysArg->nPoolCfgCnt = sizeof(stSysCommPoolSingleSc450aiSdr) / sizeof(stSysCommPoolSingleSc450aiSdr[0]);
		pSysArg->pPoolCfg = stSysCommPoolSingleSc450aiSdr;
		pPrvPoolArg->nPoolCfgCnt = sizeof(stPrivPoolSingleSc450aiSdr) / sizeof(stPrivPoolSingleSc450aiSdr[0]);
		pPrvPoolArg->pPoolCfg = stPrivPoolSingleSc450aiSdr;
		uvc_init_sc450ai(pCamList, pParam, pSysArg);
    } else if (UVC_SYS_CASE_DUAL_SC450AI == pParam->eSysCase) {
		pSysArg->nPoolCfgCnt = sizeof(stSysCommPoolDoubleSc450aiSdr) / sizeof(stSysCommPoolDoubleSc450aiSdr[0]);
		pSysArg->pPoolCfg = stSysCommPoolDoubleSc450aiSdr;
		pPrvPoolArg->nPoolCfgCnt = sizeof(stPrivPoolDoubleSc450aiSdr) / sizeof(stPrivPoolDoubleSc450aiSdr[0]);
		pPrvPoolArg->pPoolCfg = stPrivPoolDoubleSc450aiSdr;
		uvc_init_sc450ai(pCamList, pParam, pSysArg);
    } else {
		printf("uvc sys case is not supported!\n");
		return -1;
    }

    printf("%s ---\n", __func__);
    return AX_SUCCESS;
}

#ifdef TEST_LATENCY
    AX_U64 g_u64GetVencLatency = 0;
    AX_U64 g_u64GetVencCount = 0;
    AX_U64 g_u64GetVinLatency = 0;
    AX_U64 g_u64GetVinCount = 0;
#endif

AX_VOID *venc_get_stream(AX_VOID *arg)
{
    printf("%s +++\n", __func__);

    prctl(PR_SET_NAME, "venc_get_stream");

    AX_S32 s32Ret = -1;
    AX_S32 timeOutMs = 200;
    UVC_DEVICE_T *dev;
    dev = (UVC_DEVICE_T *)arg;

    AX_VIDEO_FRAME_INFO_T stFrame;
    AX_VENC_STREAM_T stStream;
    memset(&stFrame, 0, sizeof(AX_VIDEO_FRAME_INFO_T));
    memset(&stStream, 0, sizeof(AX_VENC_STREAM_T));

    if (PT_H264 == dev->venc_param.enPayloadType || PT_H265 == dev->venc_param.enPayloadType) {
        printf("AX_VENC_RequestIDR ...\n");
        AX_VENC_RequestIDR(dev->venc_param.s32VencChn, AX_TRUE);
    }

#ifdef TEST_LATENCY
    g_u64GetVencLatency = 0;
    g_u64GetVencCount = 0;
    g_u64GetVinLatency = 0;
    g_u64GetVinCount = 0;
#endif
    while (!uvc_exit && (AX_TRUE == dev->venc_param.bThreadStart)) {
        if (!dev->is_link) {
            s32Ret = AX_IVPS_GetChnFrame(dev->dev_id, dev->ivps_chn, &stFrame.stVFrame, timeOutMs);
            if (0 != s32Ret) {
                printf("AX_IVPS_GetChnFrame fail, grp:%d, chn:%d, nRet:0x%x\n", dev->dev_id, dev->ivps_chn, s32Ret);
                continue;
            }
#ifdef TEST_LATENCY
            AX_U64 u64CurPtsVin = 0;
            AX_SYS_GetCurPTS(&u64CurPtsVin);
            if (g_u64GetVinCount < 1000) {
                g_u64GetVinLatency += u64CurPtsVin - stFrame.stVFrame.u64PTS;
                g_u64GetVinCount++;
                if (g_u64GetVinCount == 1000) {
                    printf("===============get vin frame: avg latency: %llu\n", g_u64GetVinLatency / 1000);
                    g_u64GetVinLatency = 0;
                    g_u64GetVinCount = 0;
                }
            }
#endif
            s32Ret = AX_VENC_SendFrame(dev->venc_param.vencMod.s32ChnId, &stFrame, 0);
            if (0 != s32Ret) {
                printf("AX_VENC_SendFrame failed, s32ret = 0x%x\n", s32Ret);
                s32Ret = AX_IVPS_ReleaseChnFrame(dev->dev_id, dev->ivps_chn, &stFrame.stVFrame);
                if (AX_SUCCESS  != s32Ret) {
                    printf("AX_VIN_ReleaseYuvFrame failed, s32Ret=0x%x\n", s32Ret);
                }
                continue;
            }
        }

        s32Ret = AX_VENC_GetStream(dev->venc_param.s32VencChn, &stStream, gTimeout);
        switch (s32Ret) {
        case AX_SUCCESS: {
#ifdef TEST_LATENCY
                AX_U64 u64CurPts = 0;
                AX_SYS_GetCurPTS(&u64CurPts);
                if (g_u64GetVencCount < 1000) {
                    g_u64GetVencLatency += u64CurPts - stStream.stPack.u64PTS;
                    g_u64GetVencCount++;
                    if (g_u64GetVencCount == 1000) {
                        printf("===============get venc stream: avg latency: %llu\n", g_u64GetVencLatency / 1000);
                        g_u64GetVencLatency = 0;
                        g_u64GetVencCount = 0;
                    }
                }
#endif
                if (stStream.stPack.pu8Addr != NULL && stStream.stPack.u32Len != 0) {
                    pthread_mutex_lock(&dev->img_mutex);
                    uvc_img_cache_put(dev, stStream.stPack.pu8Addr, stStream.stPack.u32Len,
                                    stStream.stPack.u64SeqNum, stStream.stPack.u64PTS,
                                    (AX_VENC_INTRA_FRAME == stStream.stPack.enCodingType) ? AX_TRUE : AX_FALSE);
                    pthread_mutex_unlock(&dev->img_mutex);
                } else {
                    printf("VENC[%d]: AX_VENC_GetStream frame size is 0\n", dev->venc_param.s32VencChn);
                }

                s32Ret = AX_VENC_ReleaseStream(dev->venc_param.s32VencChn, &stStream);
                if (AX_SUCCESS != s32Ret) {
                    printf("VENC[%d]: AX_VENC_ReleaseStream failed, error type 0x%x!\n", dev->venc_param.s32VencChn, s32Ret);
                }
            }
            break;

        case AX_ERR_VENC_FLOW_END:
            printf("venc flow end!\n");
            dev->venc_param.bThreadStart = AX_FALSE;
            break;

        case AX_ERR_VENC_BUF_EMPTY:
            printf("venc buf empty!\n");
            break;

        default:
            printf("VENC[%d]: error type 0x%x\n", dev->venc_param.s32VencChn, s32Ret);
        }
    }

    printf("%s ---\n", __func__);

    return (void *)(intptr_t)s32Ret;
}

AX_S32 jenc_chn_init(UVC_DEVICE_T *dev, AX_S32 width, AX_S32 height, AX_U32 bitrate)
{
    printf("%s +++\n", __func__);
    if (NULL == dev) {
        printf("jenc_chn_init failed, dev is NULL!\n");
        return -1;
    }

    AX_VENC_CHN_ATTR_T stJencChnAttr;
    AX_VENC_MJPEG_CBR_T stMjpegCbrAttr;
    AX_VENC_MJPEG_VBR_T stMjpegVbrAttr;
    AX_VENC_MJPEG_FIXQP_T stMjpegFixQpAttr;
    AX_VENC_JPEG_PARAM_T stJpegParam;
    AX_VENC_RECV_PIC_PARAM_T stRecvParam = {0};

    dev->venc_param.bThreadStart = AX_FALSE;
    dev->venc_param.bChnCreated = AX_FALSE;

    AX_S32 s32Ret = -1;

    AX_S32 s32InputWidth = width;
    AX_S32 s32InputHeight = height;

    if (0 == s32InputWidth) {
        s32InputWidth = gUVCCams[dev->dev_id].tChnAttr[0].nWidth;
    }

    if (0 == s32InputHeight) {
        s32InputHeight = gUVCCams[dev->dev_id].tChnAttr[0].nHeight;
    }

    memset(&stJencChnAttr, 0, sizeof(stJencChnAttr));
    memset(&stMjpegCbrAttr, 0, sizeof(stMjpegCbrAttr));
    memset(&stMjpegVbrAttr, 0, sizeof(stMjpegVbrAttr));
    memset(&stMjpegFixQpAttr, 0, sizeof(stMjpegFixQpAttr));
    memset(&stJpegParam, 0, sizeof(stJpegParam));

    stJencChnAttr.stVencAttr.u32MaxPicWidth = ALIGN_UP(s32InputWidth, UVC_ENCODER_FBC_WIDTH_ALIGN_VAL);
    stJencChnAttr.stVencAttr.u32MaxPicHeight = ALIGN_UP(s32InputHeight, UVC_ENCODER_FBC_WIDTH_ALIGN_VAL);

    stJencChnAttr.stVencAttr.enMemSource = AX_MEMORY_SOURCE_CMM;
    stJencChnAttr.stVencAttr.u32PicWidthSrc = s32InputWidth;
    stJencChnAttr.stVencAttr.u32PicHeightSrc = s32InputHeight;
    stJencChnAttr.stVencAttr.u32BufSize = s32InputWidth * s32InputHeight * 3 / 4;

    stJencChnAttr.stVencAttr.u32PicWidthSrc = s32InputWidth;
    stJencChnAttr.stVencAttr.u32PicHeightSrc = s32InputHeight;

    stJencChnAttr.stVencAttr.u8InFifoDepth = 1;
    stJencChnAttr.stVencAttr.u8OutFifoDepth = 1;
    if (dev->is_link) {
        stJencChnAttr.stVencAttr.enLinkMode = AX_LINK_MODE;
    } else {
        stJencChnAttr.stVencAttr.enLinkMode = AX_UNLINK_MODE;
    }

    stJencChnAttr.stVencAttr.enType = PT_MJPEG;
    stJencChnAttr.stRcAttr.stFrameRate.fSrcFrameRate = f32SrcVideoFrameRate;
    stJencChnAttr.stRcAttr.stFrameRate.fDstFrameRate = f32DstVideoFrameRate;

    switch (stJencChnAttr.stVencAttr.enType) {
    case PT_MJPEG: {
        if (JPEGENC_CBR  == enRcMode) {
            stJencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_MJPEGCBR;
            stMjpegCbrAttr.u32StatTime = 1;
            stMjpegCbrAttr.u32BitRate = bitrate;
            stMjpegCbrAttr.u32MinQp = gU32QPMin;
            stMjpegCbrAttr.u32MaxQp = gU32QPMax;
            memcpy(&stJencChnAttr.stRcAttr.stMjpegCbr, &stMjpegCbrAttr, sizeof(AX_VENC_MJPEG_CBR_T));
        } else if (JPEGENC_VBR == enRcMode) {
            stJencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_MJPEGVBR;
            stMjpegVbrAttr.u32StatTime = 1;
            stMjpegVbrAttr.u32MaxBitRate = bitrate;
            stMjpegVbrAttr.u32MinQp = gU32QPMin;
            stMjpegVbrAttr.u32MaxQp = gU32QPMax;
            memcpy(&stJencChnAttr.stRcAttr.stMjpegVbr, &stMjpegVbrAttr, sizeof(AX_VENC_MJPEG_VBR_T));
        } else if (JPEGENC_FIXQP == enRcMode) {
            stJencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_MJPEGFIXQP;
            stMjpegFixQpAttr.s32FixedQp = gU32FixedQP;
            memcpy(&stJencChnAttr.stRcAttr.stMjpegFixQp, &stMjpegFixQpAttr, sizeof(AX_VENC_MJPEG_FIXQP_T));
        }
    }
    break;
    default:
        printf("invalid codec type, 0x%x!\n", stJencChnAttr.stVencAttr.enType);
        return s32Ret;
    }

    s32Ret = AX_VENC_CreateChn(dev->venc_param.s32VencChn, &stJencChnAttr);
    if (AX_SUCCESS != s32Ret) {
        printf("AX_VENC_CreateChn %d   failed! error type = 0x%x\n", dev->venc_param.s32VencChn, s32Ret);
        return s32Ret;
    }

    dev->venc_param.bChnCreated = AX_TRUE;
    printf("venc[%d] channel created\n", dev->venc_param.s32VencChn);

    stRecvParam.s32RecvPicNum = -1;
    s32Ret = AX_VENC_StartRecvFrame(dev->venc_param.s32VencChn, &stRecvParam);
    if (AX_SUCCESS != s32Ret) {
        printf("start recv frame failed, error type = 0x%x!\n", s32Ret);
        return s32Ret;
    }

    dev->venc_param.bThreadStart = AX_TRUE;

    pthread_create(&dev->get_stream_pid, NULL, venc_get_stream, (void *)dev);
    printf("%s ---\n", __func__);
    return AX_SUCCESS;
}


static AX_S32 link_init(UVC_VIN_PARAM_T *pParam) {
    AX_S32 s32Ret = 0;

    for (AX_S32 i = 0; i < pParam->nCamCount; i++) {
        s32Ret = AX_SYS_SetVINIVPSMode(i, i, pParam->eMode);
        if (s32Ret) {
            printf("AX_SYS_SetVINIVPSMode failed, ret:0x%x\n", s32Ret);
            break;
        }

        /*
        VIN --> IVPS
        (ModId   GrpId   ChnId) | (ModId   GrpId   ChnId)
        --------------------------------------------------
        (VIN        0       0) -> (IVPS     0       0)
        (VIN        1       0) -> (IVPS     1       0)
        */

        AX_MOD_INFO_T srcMod, dstMod;
        srcMod.enModId = AX_ID_VIN;
        srcMod.s32GrpId = i;
        srcMod.s32ChnId = 0;

        dstMod.enModId = AX_ID_IVPS;
        dstMod.s32GrpId = i;
        dstMod.s32ChnId = 0;
        s32Ret = AX_SYS_Link(&srcMod, &dstMod);
        if (s32Ret) {
            printf("AX_SYS_Link failed, ret:0x%x\n", s32Ret);
            break;
        }
    }

    return s32Ret;
}


static AX_S32 link_deinit(UVC_VIN_PARAM_T *pParam) {
    AX_S32 s32Ret = 0;

    for (AX_S32 i = 0; i < pParam->nCamCount; i++) {
        /*
        VIN --> IVPS
        (ModId   GrpId   ChnId) | (ModId   GrpId   ChnId)
        --------------------------------------------------
        (VIN        0       0) -> (IVPS     0       0)
        (VIN        1       0) -> (IVPS     1       0)
        */

        AX_MOD_INFO_T srcMod, dstMod;
        srcMod.enModId = AX_ID_VIN;
        srcMod.s32GrpId = i;
        srcMod.s32ChnId = 0;

        dstMod.enModId = AX_ID_IVPS;
        dstMod.s32GrpId = i;
        dstMod.s32ChnId = 0;
        s32Ret = AX_SYS_UnLink(&srcMod, &dstMod);
        if (s32Ret) {
            printf("AX_SYS_Link failed, ret:0x%x\n", s32Ret);
            break;
        }
    }

    return s32Ret;
}

AX_S32 video_init(UVC_DEVICE_T **dev, UVC_VIN_PARAM_T *pParam)
{
    printf("%s +++\n", __func__);
    if (NULL == dev) {
        printf("video_init failed, dev is NULL\n");
        return -1;
    }

    COMMON_SYS_ARGS_T stSysArg = {0};
    COMMON_SYS_ARGS_T stPrivPoolArg = {0};

    AX_S32 s32Ret = 0;

    if (UVC_SYS_CASE_BUTT <= pParam->eSysCase ||  UVC_SYS_CASE_NONE >= pParam->eSysCase) {
        printf("error , no such sys case type!\n");
        return s32Ret;
    }

    if (COMMON_VIN_BUTT <= pParam->eSysMode ||  COMMON_VIN_NONE >= pParam->eSysMode) {
        printf("error , no such sys mode type!\n");
        return s32Ret;
    }

    s32Ret = init_sys_config(pParam, &stSysArg, &stPrivPoolArg);
    if (0 != s32Ret) {
        printf("init_sys_config failed , error type = 0x%x\n", s32Ret);
        return s32Ret;
    }

    printf("nCamCnt=%d, nPoolCfgCnt=%d, nBlkCnt=%d, nFmt=%d, nHeight=%d, nWidth=%d, nWidthStride=%d\n",
           stSysArg.nCamCnt, stSysArg.nPoolCfgCnt, stSysArg.pPoolCfg->nBlkCnt,
           stSysArg.pPoolCfg->nFmt, stSysArg.pPoolCfg->nHeight, stSysArg.pPoolCfg->nWidth, stSysArg.pPoolCfg->nWidthStride);


    do
    {
        s32Ret = COMMON_SYS_Init(&stSysArg);
        if (AX_SUCCESS != s32Ret) {
            printf("COMMON_SYS_Init failed, ret:0x%x\n", s32Ret);
            break;
        }

        s32Ret = link_init(pParam);
        if (AX_SUCCESS != s32Ret) {
            printf("link_init failed, ret:0x%x\n", s32Ret);
            break;
        }

        s32Ret = COMMON_NPU_Init();
        if (s32Ret) {
            printf("COMMON_NPU_Init fail, ret:0x%x\n", s32Ret);
            break;
        }
        s32Ret = COMMON_CAM_Init();
        if (AX_SUCCESS != s32Ret) {
            printf("COMMON_CAM_Init failed, ret:0x%x\n", s32Ret);
            break;
        }
        s32Ret = COMMON_CAM_PrivPoolInit(&stPrivPoolArg);
        if (s32Ret) {
            printf("UVC_COMMON_CAM_PrivPoolInit failed, ret:0x%x\n", s32Ret);
            break;
        }
        s32Ret = COMMON_CAM_Open(&gUVCCams[0], stSysArg.nCamCnt);
        if (s32Ret) {
            printf("COMMON_CAM_Open failed, ret:0x%x\n", s32Ret);
            break;
        }

        for (AX_S32 i = 0; i < stSysArg.nCamCnt; i++) {
            dev[i]->pipe = gUVCCams[i].nPipeId;
        }

        if (pParam->bTuningEnable) {
            s32Ret = COMMON_NT_Init(6000, 8082);
            if (s32Ret) {
                printf("COMMON_NT_Init failed, ret:0x%x\n", s32Ret);
                break;
            }
            /* update pipe attribute */
            for (AX_S32 i = 0; i < stSysArg.nCamCnt; i++) {
                for (AX_S32 j = 0; j < gUVCCams[i].tDevBindPipe.nNum; j++) {
                    COMMON_NT_UpdateSource(gUVCCams[i].tDevBindPipe.nPipeId[j]);
                }
            }
        }

        for (AX_S32 i = 0; i < stSysArg.nCamCnt; i++) {
            for (AX_S32 j = 0; j < gUVCCams[i].tDevBindPipe.nNum; j++) {

                if (pParam->nAiispMode <= E_VIN_AIISP_DEFAULT_SCENE_MODE_E) {
                    continue;
                }

                AX_ISP_IQ_SCENE_PARAM_T tIspSceneParam;
                memset(&tIspSceneParam, 0x0, sizeof(tIspSceneParam));
                s32Ret = AX_ISP_IQ_GetSceneParam(gUVCCams[i].tDevBindPipe.nPipeId[j], &tIspSceneParam);
                if (s32Ret) {
                    printf("AX_ISP_IQ_GetSceneParam failed, ret:0x%x\n", s32Ret);
                    continue;
                }

                switch (pParam->nAiispMode) {
                case E_VIN_AIISP_MANUAL_SCENE_AIISP_MODE_E:
                    // manual mode
                    tIspSceneParam.nAutoMode = 0;
                    tIspSceneParam.tManualParam.nAiWorkMode = AX_AI_ENABLE;
                    break;
                case E_VIN_AIISP_MANUAL_SCENE_TISP_MODE_E:
                    // manual mode
                    tIspSceneParam.nAutoMode = 0;
                    tIspSceneParam.tManualParam.nAiWorkMode = AX_AI_DISABLE;
                    break;
                case E_VIN_AIISP_AUTO_SCENE_MODE_E:
                    // auto mode
                    tIspSceneParam.nAutoMode = 1;
                    // AX620E TODO for auto mode param settings
                    break;
                default:
                    break;
                }
                s32Ret = AX_ISP_IQ_SetSceneParam(gUVCCams[i].tDevBindPipe.nPipeId[j], &tIspSceneParam);
                if (s32Ret) {
                    printf("AX_ISP_IQ_SetSceneParam failed, ret:0x%x\n", s32Ret);
                    continue;
                }
            }
        }

        s32Ret = ivps_init(stSysArg.nCamCnt);
        if (s32Ret) {
            printf("ivps_init failed, ret:0x%x\n", s32Ret);
            break;
        }

        printf("%s ---\n", __func__);
        return AX_SUCCESS;
    } while (0);

    video_deinit(pParam);
    printf("%s ---\n", __func__);
    return s32Ret;
}

AX_S32 video_deinit(UVC_VIN_PARAM_T *pParam)
{
    printf("%s +++\n", __func__);

    link_deinit(pParam);

    COMMON_CAM_Close(&gUVCCams[0], MAX_UVC_CAMERAS);

    if (pParam->bTuningEnable) {
        COMMON_NT_DeInit();
    }

    COMMON_CAM_Deinit();

    ivps_deinit(pParam->nCamCount);

    COMMON_SYS_DeInit();

    printf("%s ---\n", __func__);
    return AX_SUCCESS;
}


AX_S32 venc_init()
{
    printf("%s +++\n", __func__);

    AX_S32 s32Ret = -1;
    AX_VENC_MOD_ATTR_T stVencModAttr = {0};
    stVencModAttr.enVencType = AX_VENC_MULTI_ENCODER;
    stVencModAttr.stModThdAttr.u32TotalThreadNum = 2;
    stVencModAttr.stModThdAttr.bExplicitSched = AX_FALSE;

    s32Ret = AX_VENC_Init(&stVencModAttr);
    if (AX_SUCCESS != s32Ret) {
        printf("AX_VENC_Init failed, ret:0x%x\n", s32Ret);
        return s32Ret;
    }

    printf("%s ---\n", __func__);
    return AX_SUCCESS;
}

AX_S32 venc_deinit(AX_VOID)
{
    printf("%s +++\n", __func__);

    AX_S32 s32Ret = -1;
    s32Ret = AX_VENC_Deinit();
    if (AX_SUCCESS != s32Ret) {
        printf("AX_VENC_Deinit failed, ret:0x%x\n", s32Ret);
    }

    printf("%s ---\n", __func__);
    return s32Ret;
}

AX_S32 venc_chn_init(UVC_DEVICE_T *dev, AX_S32 width, AX_S32 height, AX_U32 bitrate, AX_PAYLOAD_TYPE_E payload_type)
{
    printf("%s +++\n", __func__);

    if (NULL == dev) {
        printf("venc_chn_init failed, dev is NULL\n");
        return -1;
    }

    AX_S32 s32Ret = -1;
    AX_VENC_CHN_ATTR_T stVencChnAttr = {0};
    VIDEO_CONFIG_T stVencCfg = {0};
    AX_VENC_RECV_PIC_PARAM_T stRecvParam = {0};

    dev->venc_param.bThreadStart = AX_FALSE;
    dev->venc_param.bChnCreated = AX_FALSE;

    stVencCfg.stRCInfo.eRCType = VENC_RC_CBR;
    stVencCfg.nGOP = 30;
    stVencCfg.nBitrate = bitrate;
    stVencCfg.stRCInfo.nMinQp = 10;
    stVencCfg.stRCInfo.nMaxQp = 51;
    stVencCfg.stRCInfo.nMinIQp = 10;
    stVencCfg.stRCInfo.nMaxIQp = 51;
    stVencCfg.stRCInfo.nMinIProp = 10;
    stVencCfg.stRCInfo.nMaxIProp = 40;
    stVencCfg.stRCInfo.nIntraQpDelta = -2;

    if (0 >= width  || width > gUVCCams[dev->dev_id].tChnAttr[0].nWidth) {
        stVencCfg.nWidth = gUVCCams[dev->dev_id].tChnAttr[0].nWidth;
    } else {
        stVencCfg.nWidth = width;
    }

    if (0 >= height || height > gUVCCams[dev->dev_id].tChnAttr[0].nHeight) {
        stVencCfg.nHeight = gUVCCams[dev->dev_id].tChnAttr[0].nHeight;
    } else {
        stVencCfg.nHeight = height;
    }

    stVencCfg.nStride = stVencCfg.nWidth;
    stVencCfg.ePayloadType = payload_type;
    stVencCfg.nSrcFrameRate = f32SrcVideoFrameRate;
    stVencCfg.nDstFrameRate = f32DstVideoFrameRate;

    memset(&stVencChnAttr, 0, sizeof(AX_VENC_CHN_ATTR_T));

    stVencChnAttr.stVencAttr.u32MaxPicWidth = ALIGN_UP(width, UVC_ENCODER_FBC_WIDTH_ALIGN_VAL);
    stVencChnAttr.stVencAttr.u32MaxPicHeight = ALIGN_UP(height, UVC_ENCODER_FBC_WIDTH_ALIGN_VAL);

    stVencChnAttr.stVencAttr.u32PicWidthSrc = stVencCfg.nWidth;
    stVencChnAttr.stVencAttr.u32PicHeightSrc = stVencCfg.nHeight;


    stVencChnAttr.stVencAttr.enMemSource = AX_MEMORY_SOURCE_CMM;

    /*stream buffer size*/
    stVencChnAttr.stVencAttr.u32BufSize = stVencCfg.nStride * stVencCfg.nHeight * 3 / 4;

    //stVencChnAttr.stVencAttr.u32MbLinesPerSlice = 0;
    stVencChnAttr.stVencAttr.u8InFifoDepth = 1;
    stVencChnAttr.stVencAttr.u8OutFifoDepth = 1;

    /*link mode*/
    if (dev->is_link) {
        stVencChnAttr.stVencAttr.enLinkMode = AX_LINK_MODE;
    } else {
        stVencChnAttr.stVencAttr.enLinkMode = AX_UNLINK_MODE;
    }

    //stVencChnAttr.stVencAttr.u32GdrDuration = 0;
    stVencChnAttr.stVencAttr.enType = stVencCfg.ePayloadType;

    /*GOP Setting*/
    stVencChnAttr.stGopAttr.enGopMode = AX_VENC_GOPMODE_NORMALP;

    stVencChnAttr.stRcAttr.stFrameRate.fSrcFrameRate = stVencCfg.nSrcFrameRate;
    stVencChnAttr.stRcAttr.stFrameRate.fDstFrameRate = stVencCfg.nDstFrameRate;

    switch (stVencChnAttr.stVencAttr.enType) {
    case PT_H265: {
        stVencChnAttr.stVencAttr.enProfile = AX_VENC_HEVC_MAIN_PROFILE;
        stVencChnAttr.stVencAttr.enLevel = AX_VENC_HEVC_LEVEL_5_1;
        stVencChnAttr.stVencAttr.enTier = AX_VENC_HEVC_MAIN_TIER;

        if (VENC_RC_CBR == stVencCfg.stRCInfo.eRCType) {
            AX_VENC_H265_CBR_T stH265Cbr = {0};

            stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265CBR;
            stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
            stH265Cbr.u32Gop = stVencCfg.nGOP;

            stH265Cbr.u32BitRate  = stVencCfg.nBitrate;

            stH265Cbr.u32MinQp = stVencCfg.stRCInfo.nMinQp;
            stH265Cbr.u32MaxQp = stVencCfg.stRCInfo.nMaxQp;
            stH265Cbr.u32MinIQp = stVencCfg.stRCInfo.nMinIQp;
            stH265Cbr.u32MaxIQp = stVencCfg.stRCInfo.nMaxIQp;
            stH265Cbr.u32MinIprop = stVencCfg.stRCInfo.nMinIProp;
            stH265Cbr.u32MaxIprop = stVencCfg.stRCInfo.nMaxIProp;

            stH265Cbr.s32IntraQpDelta = stVencCfg.stRCInfo.nIntraQpDelta;

            memcpy(&stVencChnAttr.stRcAttr.stH265Cbr, &stH265Cbr, sizeof(AX_VENC_H265_CBR_T));
        } else if (VENC_RC_VBR ==  stVencCfg.stRCInfo.eRCType) {
            AX_VENC_H265_VBR_T stH265Vbr = {0};

            stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265VBR;
            stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
            stH265Vbr.u32Gop = stVencCfg.nGOP;

            stH265Vbr.u32MaxBitRate = stVencCfg.nBitrate;

            stH265Vbr.u32MinQp = stVencCfg.stRCInfo.nMinQp;
            stH265Vbr.u32MaxQp = stVencCfg.stRCInfo.nMaxQp;
            stH265Vbr.u32MinIQp = stVencCfg.stRCInfo.nMinIQp;
            stH265Vbr.u32MaxIQp = stVencCfg.stRCInfo.nMaxIQp;
            stH265Vbr.u32MinIQp = stVencCfg.stRCInfo.nMinIProp;
            stH265Vbr.u32MaxIQp = stVencCfg.stRCInfo.nMaxIProp;

            stH265Vbr.s32IntraQpDelta = stVencCfg.stRCInfo.nIntraQpDelta;

            memcpy(&stVencChnAttr.stRcAttr.stH265Vbr, &stH265Vbr, sizeof(AX_VENC_H265_VBR_T));
        } else if (VENC_RC_FIXQP == stVencCfg.stRCInfo.eRCType) {
            AX_VENC_H265_FIXQP_T stH265FixQp = {0};

            stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265FIXQP;

            stH265FixQp.u32Gop = stVencCfg.nGOP;

            stH265FixQp.u32IQp = 25;
            stH265FixQp.u32PQp = 30;
            stH265FixQp.u32BQp = 32;

            memcpy(&stVencChnAttr.stRcAttr.stH265FixQp, &stH265FixQp, sizeof(AX_VENC_H265_FIXQP_T));
        } else {
            printf("eRCtype is not supported!\n");
            return s32Ret;
        }
        break;
    }
    case PT_H264: {
        stVencChnAttr.stVencAttr.enProfile = AX_VENC_H264_MAIN_PROFILE;
        stVencChnAttr.stVencAttr.enLevel = AX_VENC_H264_LEVEL_5_2;
        if (VENC_RC_CBR == stVencCfg.stRCInfo.eRCType) {
            AX_VENC_H264_CBR_T stH264Cbr = {0};
            stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264CBR;
            stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
            stH264Cbr.u32Gop = stVencCfg.nGOP;

            stH264Cbr.u32BitRate = stVencCfg.nBitrate;

            stH264Cbr.u32MinQp = stVencCfg.stRCInfo.nMinQp;
            stH264Cbr.u32MaxQp = stVencCfg.stRCInfo.nMaxQp;
            stH264Cbr.u32MinIQp = stVencCfg.stRCInfo.nMinIQp;
            stH264Cbr.u32MaxIQp = stVencCfg.stRCInfo.nMaxIQp;
            stH264Cbr.u32MinIprop = stVencCfg.stRCInfo.nMinIProp;
            stH264Cbr.u32MaxIprop = stVencCfg.stRCInfo.nMaxIProp;

            stH264Cbr.s32IntraQpDelta = stVencCfg.stRCInfo.nIntraQpDelta;

            memcpy(&stVencChnAttr.stRcAttr.stH264Cbr, &stH264Cbr, sizeof(AX_VENC_H264_CBR_T));
        } else if (VENC_RC_VBR == stVencCfg.stRCInfo.eRCType) {
            AX_VENC_H264_VBR_T stH264Vbr = {0};

            stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264VBR;
            stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
            stH264Vbr.u32Gop = stVencCfg.nGOP;

            stH264Vbr.u32MaxBitRate = stVencCfg.nBitrate;

            stH264Vbr.u32MinQp = stVencCfg.stRCInfo.nMinQp;
            stH264Vbr.u32MaxQp = stVencCfg.stRCInfo.nMaxQp;
            stH264Vbr.u32MinIQp = stVencCfg.stRCInfo.nMinIQp;
            stH264Vbr.u32MaxIQp = stVencCfg.stRCInfo.nMaxIQp;

            stH264Vbr.s32IntraQpDelta = stVencCfg.stRCInfo.nIntraQpDelta;

            memcpy(&stVencChnAttr.stRcAttr.stH264Vbr, &stH264Vbr, sizeof(AX_VENC_H264_VBR_T));
        } else if (VENC_RC_FIXQP == stVencCfg.stRCInfo.eRCType) {
            AX_VENC_H264_FIXQP_T  stH264FixQp = {0};

            stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264FIXQP;

            stH264FixQp.u32Gop = stVencCfg.nGOP;

            stH264FixQp.u32IQp = 25;
            stH264FixQp.u32PQp = 30;
            stH264FixQp.u32BQp = 32;

            memcpy(&stVencChnAttr.stRcAttr.stH264FixQp, &stH264FixQp, sizeof(AX_VENC_H264_FIXQP_T));
        } else {
            printf("eRCtype is not supported!\n");
            return s32Ret;
        }
        break;
    }
    default:
        printf("payload type is not supported!\n");
        return s32Ret;
    }

    s32Ret = AX_VENC_CreateChn(dev->venc_param.s32VencChn, &stVencChnAttr);
    if (AX_SUCCESS != s32Ret) {
        printf("VencChn %d AX_VENC_CreateChn failed, s32Ret=0x%x\n", dev->venc_param.s32VencChn, s32Ret);
        return s32Ret;
    }
    dev->venc_param.bChnCreated = AX_TRUE;
    printf("venc[%d] channel created\n", dev->venc_param.s32VencChn);

    stRecvParam.s32RecvPicNum = -1;
    s32Ret = AX_VENC_StartRecvFrame(dev->venc_param.s32VencChn, &stRecvParam);
    if (AX_SUCCESS != s32Ret) {
        printf("start recv frame failed, error type = 0x%x!\n", s32Ret);
        return s32Ret;
    }

    dev->venc_param.bThreadStart = AX_TRUE;

    pthread_create(&dev->get_stream_pid, NULL, venc_get_stream, (void *)dev);

    printf("%s ---\n", __func__);
    return s32Ret;
}

AX_S32 venc_chn_deinit(UVC_DEVICE_T *dev, AX_S32 enc_format)
{
    printf("%s +++\n", __func__);

    if (NULL == dev) {
        printf("venc_chn_deinit failed, dev is NULL!\n");
        return -1;
    }

    AX_S32 s32Ret = -1, s32Retry = 5;

    if ((V4L2_PIX_FMT_H264 == enc_format) || (V4L2_PIX_FMT_MJPEG == enc_format) || (V4L2_PIX_FMT_H265 == enc_format)) {
        dev->venc_param.bThreadStart = AX_FALSE;
    } else {
        printf("enc_format is not supported!\n");
        return -1;
    }

    if (!dev->venc_param.bChnCreated) {
        printf("%s ---\n", __func__);
        return s32Ret;
    }

    s32Ret = AX_VENC_StopRecvFrame(dev->venc_param.s32VencChn);
    if (s32Ret < 0) {
        printf("AX_VENC_StopRecvFrame failed, error type = 0x%x!\n", s32Ret);
    }

    usleep(50 * 1000);

    do {
        s32Ret = AX_VENC_DestroyChn(dev->venc_param.s32VencChn);
        if (AX_ERR_VENC_BUSY == s32Ret) {
            printf("venc[%d] AX_VENC_DestroyChn return AX_ERR_VENC_BUSY,retry...", dev->venc_param.s32VencChn);
            usleep(100 * 1000);
            --s32Retry;
        } else {
            break;
        }
    } while (s32Retry >= 0);

    if (s32Retry == -1 || AX_SUCCESS != s32Ret) {
        printf("venc[%d] AX_VENC_DestroyChn failed, s32Retry=%d, s32Ret=0x%x\n", dev->venc_param.s32VencChn, s32Retry, s32Ret);
    }

    dev->venc_param.bChnCreated = AX_FALSE;
    printf("venc[%d] channel destroyed\n", dev->venc_param.s32VencChn);
    printf("%s ---\n", __func__);
    return s32Ret;
}


AX_S32 link_to_venc(UVC_DEVICE_T* dev, AX_BOOL bLink)
{
    printf("%s +++, (bLink=%d)\n", __func__,  bLink);
    if (NULL == dev) {
        printf("link_to_venc (bLink=%d) failed, dev is NULL\n", bLink);
        return -1;
    }

    AX_S32 s32Ret = 0;
    if (bLink) {
        s32Ret = AX_SYS_Link(&(dev->venc_param.ivpsMod), &(dev->venc_param.vencMod));
        if (AX_SUCCESS != s32Ret) {
            printf("AX_SYS_Link failed! error type 0x%x\n", s32Ret);
            return s32Ret;
        }
    } else {
        s32Ret = AX_SYS_UnLink(&(dev->venc_param.ivpsMod), &(dev->venc_param.vencMod));
        if (AX_SUCCESS != s32Ret && !uvc_exit) {
            printf("AX_SYS_Unlink failed! error type 0x%x\n", s32Ret);
            return s32Ret;
        }
    }
    printf("%s ---, (bLink=%d)\n", __func__,  bLink);
    return s32Ret;
}

#ifdef TEST_LATENCY
    AX_U64 g_u64GetYuvLatency = 0;
    AX_U64 g_u64GetYuvCount = 0;
    AX_U64 g_u64GetYuvCscLatency = 0;
    AX_U64 g_u64GetYuvCscCount = 0;
#endif

static AX_VOID *get_yuv2_stream(AX_VOID *arg)
{
    printf("%s +++\n", __func__);

    prctl(PR_SET_NAME, "get_yuv2_stream");
    AX_S32 s32Ret = 0;
    AX_S32 timeOutMs = 2000;
    AX_VIDEO_FRAME_T stFrame = {0};

    UVC_DEVICE_T *dev = (UVC_DEVICE_T *)arg;

    AX_U64 dst_phy = 0;
    AX_U8* dst_img = NULL;
    AX_VIDEO_FRAME_T stFrameDst = {0};
    s32Ret = AX_SYS_MemAllocCached(&dst_phy, (AX_VOID **)&dst_img, dev->stYUV2Cfg.u32Width * dev->stYUV2Cfg.u32Height * 2, 0x1000, (AX_S8 *)"uvc_yuv2");
    if (s32Ret != 0) {
        printf("AX_SYS_MemAllocCached failed\n");
        return NULL;
    }
    stFrameDst.enImgFormat = AX_FORMAT_YUV422_INTERLEAVED_YUYV;
    stFrameDst.u32Width = dev->stYUV2Cfg.u32Width;
    stFrameDst.u32Height = dev->stYUV2Cfg.u32Height;
    stFrameDst.u32PicStride[0] = dev->stYUV2Cfg.u32Width;
    stFrameDst.u64PhyAddr[0] = dst_phy;
    stFrameDst.u64VirAddr[0] = (AX_U64)(uintptr_t)dst_img;

    while (!uvc_exit && !dev->stYUV2Cfg.bExit) {
        s32Ret = AX_IVPS_GetChnFrame(dev->dev_id, dev->ivps_chn, &stFrame, timeOutMs);
        if (AX_SUCCESS != s32Ret) {
            printf("AX_IVPS_GetChnFrame fail, grp:%d, chn:%d, nRet:0x%x\n", dev->dev_id, dev->ivps_chn, s32Ret);
            continue;
        }

        do {
            if ((dev->stYUV2Cfg.u32Width != stFrame.u32Width) || (dev->stYUV2Cfg.u32Height != stFrame.u32Height)) {
                break;
            }

#ifdef TEST_LATENCY
            AX_U64 u64CurPts = 0;
            AX_SYS_GetCurPTS(&u64CurPts);
            if (g_u64GetYuvCount < 1000) {
                g_u64GetYuvLatency += u64CurPts - stFrame.u64PTS;
                g_u64GetYuvCount++;
                if (g_u64GetYuvCount == 1000) {
                    printf("===============get yuv stream: avg latency: %llu\n", g_u64GetYuvLatency / 1000);
                    g_u64GetYuvLatency = 0;
                    g_u64GetYuvCount = 0;
                }
            }
            AX_SYS_GetCurPTS(&u64CurPts);
#endif

            // s32Ret = nv12_to_yuv422_cpu(stFrame.u32Width, stFrame.u32Height, (AX_U8 *)AX_POOL_GetBlockVirAddr(stFrame.u32BlkId[0]), dst_img);
            s32Ret = AX_IVPS_CscTdp(&stFrame, &stFrameDst);
            if (AX_SUCCESS != s32Ret) {
                printf("nv12_to_yuv422 failed, s32Ret=0x%x\n", s32Ret);
                break;
            }

#ifdef TEST_LATENCY
            AX_U64 u64CurPts2 = 0;
            AX_SYS_GetCurPTS(&u64CurPts2);
            if (g_u64GetYuvCscCount < 1000) {
                g_u64GetYuvCscLatency += u64CurPts2 - u64CurPts;
                g_u64GetYuvCscCount++;
                if (g_u64GetYuvCscCount == 1000) {
                    printf("===============csc cost: avg latency: %llu\n", g_u64GetYuvCscLatency / 1000);
                    g_u64GetYuvCscLatency = 0;
                    g_u64GetYuvCscCount = 0;
                }
            }
#endif

            pthread_mutex_lock(&dev->img_mutex);
            uvc_img_cache_put(dev, dst_img, dev->stYUV2Cfg.u32Width * dev->stYUV2Cfg.u32Height * 2, stFrame.u64SeqNum, stFrame.u64PTS, AX_TRUE);
            pthread_mutex_unlock(&dev->img_mutex);

        } while (0);

        s32Ret = AX_IVPS_ReleaseChnFrame(dev->dev_id, dev->ivps_chn, &stFrame);
        if (AX_SUCCESS  != s32Ret) {
            printf("AX_IVPS_ReleaseChnFrame failed, s32Ret=0x%x\n", s32Ret);
            dev->stYUV2Cfg.bExit = AX_TRUE;
            uvc_exit = 1;
        }
    }

    s32Ret = AX_SYS_MemFree(dst_phy, (AX_VOID *)dst_img);
	if (s32Ret != 0) {
        printf("AX_SYS_MemFree failed\n");
    }

    printf("%s ---\n", __func__);
    return (void *)(intptr_t)s32Ret;
}


AX_S32 yuv2_chn_init(UVC_DEVICE_T *dev, AX_S32 width, AX_S32 height)
{
    printf("%s +++\n", __func__);

    if (NULL == dev) {
        printf("yuv2_chn_init failed, dev is NULL\n");
        return -1;
    }

    dev->stYUV2Cfg.u32Width = width;
    dev->stYUV2Cfg.u32Height = height;
    dev->stYUV2Cfg.bExit = AX_FALSE;

    pthread_create(&dev->get_stream_pid, NULL, get_yuv2_stream, (void *)dev);

    printf("%s ---\n", __func__);

    return AX_SUCCESS;
}

AX_S32 yuv2_chn_deinit(UVC_DEVICE_T *dev)
{
    printf("%s +++\n", __func__);
    if (NULL == dev) {
        printf("yuv2_chn_deinit failed, dev is NULL!\n");
        return 1;
    }
    dev->stYUV2Cfg.bExit = AX_TRUE;
    printf("%s ---n", __func__);
    return AX_SUCCESS;
}

AX_S32 uvc_draw_yuv422_color_stripe(AX_S32 width, AX_S32 height, AX_U8 *img)
{
    if (NULL == img) {
        printf("invalid image pointer!\n");
        return -1;
    }

    AX_S32 dst_index = 0;
    AX_S32 color_index = 0;
    YUV_T color = gArrYUVColor[color_index];

    for (AX_S32 i = 0; i < height / 2; i++) {
        AX_S32 uv_width = width;
        for (AX_S32 j = 0; j < uv_width / 2; j++) {
            //Y
            img[dst_index] = color.y;
            img[dst_index + uv_width * 2] = color.y;
            dst_index++;

            //U
            img[dst_index] = color.u;
            img[dst_index + uv_width * 2] = color.u;
            dst_index++;

            //Y
            img[dst_index] = color.y;
            img[dst_index + uv_width * 2] = color.y;
            dst_index++;

            //V
            img[dst_index] = color.v;
            img[dst_index + uv_width * 2] = color.v;
            dst_index++;
        }
        dst_index += uv_width * 2;

        if (0 == (i + 1) % (height / 2 / COLOR_COUNT)) {
            color_index++;
            color = gArrYUVColor[color_index];
        }
    }
    return AX_SUCCESS;
}


AX_S32 ivps_init(AX_S32 nSnsCount)
{
    printf("%s +++\n", __func__);
    AX_S32 s32Ret = 0;
    AX_IVPS_GRP_ATTR_T stGrpAttr = { 0 };
    AX_IVPS_PIPELINE_ATTR_T stPipelineAttr = { 0 };

    s32Ret = AX_IVPS_Init();
    if (AX_SUCCESS != s32Ret) {
        printf("AX_IVPS_Init failed, s32Ret:0x%x\n", s32Ret);
        return s32Ret;
    }

    for (AX_S32 i = 0; i < nSnsCount; i++) {
        stGrpAttr.nInFifoDepth = 2;
        stGrpAttr.ePipeline = AX_IVPS_PIPELINE_DEFAULT;
        s32Ret = AX_IVPS_CreateGrp(i, &stGrpAttr);
        if (AX_SUCCESS != s32Ret) {
            printf("AX_IVPS_CreateGrp failed, nGrp %d, s32Ret:0x%x\n", i, s32Ret);
            return s32Ret;
        }

        stPipelineAttr.nOutChnNum = 2; // MJPEG/H264/H265 use chn0， YUV2 uses chn1
        stPipelineAttr.tFilter[0][0].bEngage = AX_TRUE;
        stPipelineAttr.tFilter[0][0].nDstPicWidth = gUVCCams[i].tChnAttr[0].nWidth;
        stPipelineAttr.tFilter[0][0].nDstPicHeight = gUVCCams[i].tChnAttr[0].nHeight;
        stPipelineAttr.tFilter[0][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[0][0].nDstPicWidth, 16);
        stPipelineAttr.tFilter[0][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        stPipelineAttr.tFilter[0][0].eEngine = AX_IVPS_ENGINE_VPP;
        stPipelineAttr.tFilter[0][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
        stPipelineAttr.tFilter[0][0].tCompressInfo.u32CompressLevel = 0;


        stPipelineAttr.tFilter[1][0].bEngage = AX_TRUE;
        stPipelineAttr.tFilter[1][0].nDstPicWidth = gUVCCams[i].tChnAttr[0].nWidth;
        stPipelineAttr.tFilter[1][0].nDstPicHeight = gUVCCams[i].tChnAttr[0].nHeight;
        stPipelineAttr.tFilter[1][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[1][0].nDstPicWidth, 128);
        stPipelineAttr.tFilter[1][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        stPipelineAttr.tFilter[1][0].eEngine = AX_IVPS_ENGINE_SCL;
        stPipelineAttr.tFilter[1][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
        stPipelineAttr.tFilter[1][0].tCompressInfo.u32CompressLevel = 0;
        stPipelineAttr.tFilter[1][0].tFRC.fSrcFrameRate = 30.0f;
        stPipelineAttr.tFilter[1][0].tFRC.fDstFrameRate = 30.0f;
        stPipelineAttr.nOutFifoDepth[0] = 0;


        stPipelineAttr.tFilter[2][0].bEngage = AX_TRUE;
        stPipelineAttr.tFilter[2][0].nDstPicWidth = 1920;
        stPipelineAttr.tFilter[2][0].nDstPicHeight = 1080;
        stPipelineAttr.tFilter[2][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[2][0].nDstPicWidth, 16);
        stPipelineAttr.tFilter[2][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        stPipelineAttr.tFilter[2][0].eEngine = AX_IVPS_ENGINE_SCL;
        stPipelineAttr.tFilter[2][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
        stPipelineAttr.tFilter[2][0].tCompressInfo.u32CompressLevel = 0;
        stPipelineAttr.tFilter[2][0].tFRC.fSrcFrameRate = 30.0f;
        stPipelineAttr.tFilter[2][0].tFRC.fDstFrameRate = 20.0f;
        stPipelineAttr.nOutFifoDepth[1] = 2;


        s32Ret = AX_IVPS_SetPipelineAttr(i, &stPipelineAttr);
        if (AX_SUCCESS != s32Ret) {
            printf("AX_IVPS_SetPipelineAttr failed, nGrp %d, s32Ret:0x%x\n", i, s32Ret);
            return s32Ret;
        }

        for (AX_S32 nChn = 0; nChn < stPipelineAttr.nOutChnNum; nChn++) {
            s32Ret = AX_IVPS_EnableChn(i, nChn);
            if (AX_SUCCESS != s32Ret) {
                printf("AX_IVPS_EnableChn failed, nGrp %d, nChn %d, s32Ret:0x%x\n", i, nChn, s32Ret);
                return s32Ret;
            }
        }

        s32Ret = AX_IVPS_StartGrp(i);
        if (AX_SUCCESS != s32Ret) {
            printf("AX_IVPS_StartGrp failed, nGrp %d, s32Ret:0x%x\n", i, s32Ret);
            return s32Ret;
        }
    }

    printf("%s ---\n", __func__);
    return AX_SUCCESS;
}

AX_S32 ivps_deinit(AX_S32 nSnsCount)
{
    printf("%s +++\n", __func__);
    AX_S32 s32Ret = 0;
    AX_S32 nChnNum = 2;
    for(AX_S32 i = 0; i < nSnsCount; i++) {
        s32Ret = AX_IVPS_StopGrp(i);
        if (AX_SUCCESS != s32Ret) {
            printf("AX_IVPS_StopGrp failed, nGrp %d, s32Ret:0x%x\n", i, s32Ret);
            return s32Ret;
        }

        for (AX_S32 nChn = 0; nChn < nChnNum; nChn++) {
            s32Ret = AX_IVPS_DisableChn(i, nChn);
            if (AX_SUCCESS != s32Ret) {
                printf("AX_IVPS_DisableChn failed, nGrp %d, nChn %d, s32Ret:0x%x\n", i, nChn, s32Ret);
                return s32Ret;
            }
        }

        s32Ret = AX_IVPS_DestoryGrp(i);
        if (AX_SUCCESS != s32Ret) {
            printf("AX_IVPS_DestoryGrp failed, nGrp %d, s32Ret:0x%x\n", i, s32Ret);
            return s32Ret;
        }

        s32Ret = AX_IVPS_Deinit();
        if (AX_SUCCESS != s32Ret) {
            printf("AX_IVPS_Deinit failed, s32Ret:0x%x\n", s32Ret);
            return s32Ret;
        }
    }
    printf("%s ---\n", __func__);
    return AX_SUCCESS;
}

AX_S32 ivps_update_resolution(AX_U8 nGrp, AX_U8 nChn, AX_S32 nWidth, AX_S32 nHeight, AX_S32 nFps)
{
    printf("%s +++\n", __func__);
    AX_S32 s32Ret = 0;
    AX_IVPS_PIPELINE_ATTR_T stPipelineAttr = { 0 };

    s32Ret = AX_IVPS_GetPipelineAttr(nGrp, &stPipelineAttr);
    if (AX_SUCCESS != s32Ret) {
        printf("AX_IVPS_GetPipelineAttr failed,nGrp %d,s32Ret:0x%x\n", nGrp, s32Ret);
        return s32Ret;
    }

    stPipelineAttr.tFilter[nChn+1][0].nDstPicWidth = nWidth;
    stPipelineAttr.tFilter[nChn+1][0].nDstPicHeight = nHeight;
    if (nChn == 0) {
        stPipelineAttr.tFilter[nChn+1][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[nChn+1][0].nDstPicWidth, UVC_ENCODER_FBC_WIDTH_ALIGN_VAL);
        // if ((nWidth == 1920 && nHeight == 1080) || (nWidth == 2688 && nHeight == 1520) ) {
        //     stPipelineAttr.tFilter[1][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_LOSSY;
        //     stPipelineAttr.tFilter[1][0].tCompressInfo.u32CompressLevel = 0;
        // } else {
        //     stPipelineAttr.tFilter[1][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
        //     stPipelineAttr.tFilter[1][0].tCompressInfo.u32CompressLevel = 0;
        // }

    } else {
        stPipelineAttr.tFilter[nChn+1][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[nChn+1][0].nDstPicWidth, 16);
    }
    stPipelineAttr.tFilter[nChn+1][0].tFRC.fDstFrameRate = nFps;


    s32Ret = AX_IVPS_DisableChn(nGrp, nChn);
    if (AX_SUCCESS != s32Ret) {
        printf("AX_IVPS_DisableChn failed,nGrp %d,s32Ret:0x%x\n", nGrp, s32Ret);
        return s32Ret;
    }

    s32Ret = AX_IVPS_SetPipelineAttr(nGrp, &stPipelineAttr);
    if (AX_SUCCESS != s32Ret) {
        printf("AX_IVPS_SetPipelineAttr failed,nGrp %d,s32Ret:0x%x\n", nGrp, s32Ret);
        return s32Ret;
    }

    s32Ret = AX_IVPS_EnableChn(nGrp, nChn);
    if (AX_SUCCESS != s32Ret) {
        printf("AX_IVPS_EnableChn failed,nGrp %d,s32Ret:0x%x\n", nGrp, s32Ret);
        return s32Ret;
    }
    printf("%s ---\n", __func__);
    return AX_SUCCESS;
}
