/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include "ax_global_type.h"
#include "ax_isp_api.h"
#include "sample_vin.h"
#include "common_sys.h"
#include "common_cam.h"
#include "common_isp.h"
//#include "ax_vin_error_code.h"
#include "common_nt.h"
#include "sample_case_dcg_vs.h"

/* comm pool */
COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_16BPP, 6},      /*vin raw16 use */
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR,4,  AX_COMPRESS_MODE_LOSSY, 4},    /*vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleDVPSdr[] = {
    {320, 240, 320, AX_FORMAT_YUV420_SEMIPLANAR, 10},          /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleBTSdr[] = {
    {720, 480, 720, AX_FORMAT_YUV422_INTERLEAVED_UYVY, 25 * 2}, /*vin yuv422 uyvy use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleLVDSSdr[] = {
    {1600, 1200, 1600, AX_FORMAT_YUV420_SEMIPLANAR, 10},      /* vin nv21/nv21 use */
};

/* private pool */
COMMON_SYS_POOL_CFG_T gtPrivatePoolSingleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_16BPP, 10, AX_COMPRESS_MODE_LOSSY, 4},
};

COMMON_SYS_POOL_CFG_T gtSysPrivatePoolSingleDVPSdr[] = {
    {320, 240, 320, AX_FORMAT_BAYER_RAW_10BPP, 25 * 2},         /*vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysPrivatePoolSingleBTSdr[] = {
    {720, 480, 720, AX_FORMAT_YUV422_INTERLEAVED_UYVY, 25 * 2}, /*vin yuv422 uyvy use */
};

COMMON_SYS_POOL_CFG_T gtSysPrivatePoolSingleLVDSSdr[] = {
    {1600, 1200, 1600, AX_FORMAT_BAYER_RAW_10BPP, 25 * 2},      /*vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 3, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolSingleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 8, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolDoubleOs04a10Bt656Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 7, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
    {720, 480, 720, AX_FORMAT_YUV422_SEMIPLANAR, 6, AX_COMPRESS_MODE_NONE, 0},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolDoubleOs04a10Bt656Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
    {720, 480, 720, AX_FORMAT_YUV422_SEMIPLANAR, 5, AX_COMPRESS_MODE_NONE, 0},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolDoubleOs04a10Bt656Hdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 7, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
    {720, 480, 720, AX_FORMAT_YUV422_SEMIPLANAR, 7, AX_COMPRESS_MODE_NONE, 0},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolDoubleOs04a10Bt656Hdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 13, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
    {720, 480, 720, AX_FORMAT_YUV422_SEMIPLANAR, 5, AX_COMPRESS_MODE_NONE, 0},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolDoubleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 6, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolDoubleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolDoubleOs04a10Hdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 6, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolDoubleOs04a10Hdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_NONE, 0},      /* vin raw10 use */
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleOs450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 3, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolSingleOs450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 8, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolDoubleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 6, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolDoubleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolDoubleSc450aiHdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 6, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolDoubleSc450aiHdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_NONE, 0},      /* vin raw10 use */
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolSingles5kjn1sq03Sdr[] = {
    {1920, 1080, 1920, AX_FORMAT_YUV420_SEMIPLANAR, 3, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolSingles5kjn1sq03Sdr[] = {
    {1920, 1080, 1920, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 8, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static AX_CAMERA_T gCams[MAX_CAMERAS] = {0};
static volatile AX_S32 gLoopExit = 0;
extern AX_CHIP_TYPE_E AX_SYS_GetChipType(AX_VOID);

static AX_VOID __sigint(int iSigNo)
{
    COMM_ISP_PRT("Catch signal %d\n", iSigNo);
    gLoopExit = 1;

    return ;
}

static AX_VOID __cal_dump_pool(COMMON_SYS_POOL_CFG_T pool[], AX_SNS_HDR_MODE_E eHdrMode, AX_S32 nFrameNum)
{
    if (NULL == pool) {
        return;
    }
    if (nFrameNum > 0) {
        switch (eHdrMode) {
        case AX_SNS_LINEAR_MODE:
            pool[0].nBlkCnt += nFrameNum;
            break;

        case AX_SNS_HDR_2X_MODE:
            pool[0].nBlkCnt += nFrameNum * 2;
            break;

        case AX_SNS_HDR_3X_MODE:
            pool[0].nBlkCnt += nFrameNum * 3;
            break;

        case AX_SNS_HDR_4X_MODE:
            pool[0].nBlkCnt += nFrameNum * 4;
            break;

        default:
            pool[0].nBlkCnt += nFrameNum;
            break;
        }
    }
}

static AX_VOID __set_pipe_hdr_mode(AX_U32 *pHdrSel, AX_SNS_HDR_MODE_E eHdrMode)
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

static AX_VOID __set_vin_attr(AX_CAMERA_T *pCam, SAMPLE_SNS_TYPE_E eSnsType, AX_SNS_HDR_MODE_E eHdrMode,
                              COMMON_VIN_MODE_E eSysMode, AX_BOOL bAiispEnable)
{
    pCam->eSnsType = eSnsType;
    pCam->tSnsAttr.eSnsMode = eHdrMode;
    pCam->tDevAttr.eSnsMode = eHdrMode;
    pCam->eHdrMode = eHdrMode;
    pCam->eSysMode = eSysMode;
    pCam->tPipeAttr.eSnsMode = eHdrMode;
    pCam->tPipeAttr.bAiIspEnable = bAiispEnable;

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
    pCam->bChnEn[0] = AX_TRUE;
    pCam->bRegisterSns = AX_TRUE;

    return;
}

static AX_U32 __sample_case_single_dummy(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_S32 i = 0;
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    SAMPLE_LOAD_RAW_NODE_E eLoadRawNode = pVinParam->eLoadRawNode;
    pCam = &pCamList[0];
    pCommonArgs->nCamCnt = 1;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        pCam = &pCamList[i];
        COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr, pCam->tChnAttr);


        pCam->nDevId = 0;
        pCam->nRxDev = 0;
        pCam->nPipeId = 0;
        pCam->tSnsClkAttr.nSnsClkIdx = 0;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
        pCam->eLoadRawNode = eLoadRawNode;
        pCam->eInputMode = AX_INPUT_MODE_MIPI;
        __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
        __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
        for (AX_S32 j = 0; j < AX_VIN_MAX_PIPE_NUM; j++) {
            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
            strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
        }
    }

    return 0;
}

static AX_U32 __sample_case_single_dvp(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    pCommonArgs->nCamCnt = 1;
    pCam = &pCamList[0];
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr, pCam->tChnAttr);
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->nPipeId = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    pCam->eInputMode = AX_INPUT_MODE_DVP;
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    for (AX_S32 j = 0; j < AX_VIN_MAX_PIPE_NUM; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
    }

    return 0;
}

static AX_U32 __sample_case_single_bt(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    pCommonArgs->nCamCnt = 1;
    pCam = &pCamList[0];
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr, pCam->tChnAttr);
    pCam->nDevId = 2;
    pCam->nRxDev = 2;
    pCam->nPipeId = 2;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    pCam->eInputMode = AX_INPUT_MODE_BT656;
    pCam->tDevAttr.nConvYuv422To420En = 1;
    pCam->tDevAttr.nConvFactor = 2;
    pCam->tPipeAttr.ePipeWorkMode = AX_VIN_PIPE_ISP_BYPASS_MODE;
    pCam->tPipeAttr.ePixelFmt = AX_FORMAT_YUV420_SEMIPLANAR;
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    pCam->bRegisterSns = AX_FALSE;
    for (AX_S32 j = 0; j < AX_VIN_MAX_PIPE_NUM; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
    }

    return 0;
}

static AX_U32 __sample_case_single_lvds(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    pCommonArgs->nCamCnt = 1;
    pCam = &pCamList[0];
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr, pCam->tChnAttr);
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->nPipeId = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    pCam->eInputMode = AX_INPUT_MODE_LVDS;
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    for (AX_S32 j = 0; j < AX_VIN_MAX_PIPE_NUM; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
    }

    return 0;
}

static AX_U32 __sample_case_single_os04a10(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    AX_S32 j = 0;
    SAMPLE_LOAD_RAW_NODE_E eLoadRawNode = pVinParam->eLoadRawNode;
    pCommonArgs->nCamCnt = 1;
    pCam = &pCamList[0];
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr, pCam->tChnAttr);
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->nPipeId = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->eLoadRawNode = eLoadRawNode;
    pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    pCam->eInputMode = AX_INPUT_MODE_MIPI;
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
    }
    return 0;
}

static AX_U32 __sample_case_double_os04a10(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    AX_S32 j = 0, i = 0;
    pCommonArgs->nCamCnt = 2;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        pCam = &pCamList[i];
        pCam->nNumber = i;
        COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr, pCam->tChnAttr);

        pCam->nDevId = i;
        if (i == 0) {
            pCam->nRxDev = 0;
            pCam->nI2cAddr = 0x36;
        } else {
            pCam->nRxDev = 1;
            if (AX_SYS_GetChipType() == AX620Q_CHIP)
                pCam->nI2cAddr = 0x10;
            else
                pCam->nI2cAddr = 0x36;
        }
        pCam->nPipeId = i;
        pCam->tSnsClkAttr.nSnsClkIdx = 0;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
        if (eHdrMode == AX_SNS_LINEAR_MODE)
            pCam->tSnsAttr.nSettingIndex = 33;
        else
            pCam->tSnsAttr.nSettingIndex = 34;
        pCam->tMipiAttr.eLaneNum = AX_MIPI_DATA_LANE_2;
        pCam->eInputMode = AX_INPUT_MODE_MIPI;
        __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
        __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
        if (pCam->nPipeId != 0 && eHdrMode == AX_SNS_HDR_2X_MODE) {
            pCam->tPipeAttr.tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
        }
        for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
            strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
        }
    }
    return 0;
}

static AX_U32 __sample_case_single_sc450ai(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    AX_S32 j = 0;
    SAMPLE_LOAD_RAW_NODE_E eLoadRawNode = pVinParam->eLoadRawNode;
    pCommonArgs->nCamCnt = 1;

    pCam = &pCamList[0];
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr, pCam->tChnAttr);
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->nPipeId = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->eLoadRawNode = eLoadRawNode;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    pCam->eInputMode = AX_INPUT_MODE_MIPI;
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        if (pCam->tPipeInfo[j].bAiispEnable) {
            if (eHdrMode <= AX_SNS_LINEAR_MODE) {
                strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/sc450ai_sdr_dual3dnr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
            } else {
                strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/sc450ai_hdr_2x_ainr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
            }
        } else {
            strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
        }
    }
    return 0;
}

static AX_U32 __sample_case_double_sc450ai(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    AX_S32 j = 0, i = 0;
    pCommonArgs->nCamCnt = 2;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        pCam = &pCamList[i];
        pCam->nNumber = i;
        COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr, pCam->tChnAttr);

        pCam->nDevId = i;
        if (i == 0) {
            pCam->nRxDev = 0;
            pCam->nI2cAddr = 0x30;
        } else {
            pCam->nRxDev = 1;
            if (AX_SYS_GetChipType() == AX620Q_CHIP)
                pCam->nI2cAddr = 0x31;
            else
                pCam->nI2cAddr = 0x30;
        }
        pCam->nPipeId = i;
        pCam->tSnsClkAttr.nSnsClkIdx = 0;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
        if (eHdrMode == AX_SNS_LINEAR_MODE)
            pCam->tSnsAttr.nSettingIndex = 33;
        else
            pCam->tSnsAttr.nSettingIndex = 35;
        pCam->tMipiAttr.eLaneNum = AX_MIPI_DATA_LANE_2;
        pCam->eInputMode = AX_INPUT_MODE_MIPI;
        __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
        __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
        if (pCam->nPipeId != 0 && eHdrMode == AX_SNS_HDR_2X_MODE) {
            pCam->tPipeAttr.tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
        }
        for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
            if (pCam->tPipeInfo[j].bAiispEnable) {
                if (eHdrMode <= AX_SNS_LINEAR_MODE) {
                    strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/sc450ai_sdr_dual3dnr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
                } else {
                    strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/sc450ai_hdr_2x_ainr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
                }
            } else {
                strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
            }
        }
    }
    return 0;
}

static AX_U32 __sample_case_double_os04a10_and_bt656(AX_CAMERA_T *pCamList,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    SAMPLE_SNS_TYPE_E eSnsType;
    AX_S32 j = 0, i = 0;
    pCommonArgs->nCamCnt = 3;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        if (i < 2)
            eSnsType = OMNIVISION_OS04A10;
        else {
            eSnsType = SAMPLE_SNS_BT656;
            eHdrMode = AX_SNS_LINEAR_MODE;
        }
        pCam = &pCamList[i];
        pCam->nNumber = i;
        COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr, pCam->tChnAttr);

        pCam->nDevId = i;
        pCam->nRxDev = i;
        if (i == 0) {
            pCam->nI2cAddr = 0x36;
        } else if (i == 1) {
            if (AX_SYS_GetChipType() == AX620Q_CHIP)
                pCam->nI2cAddr = 0x10;
            else
                pCam->nI2cAddr = 0x36;
        }
        pCam->nPipeId = i;
        pCam->tSnsClkAttr.nSnsClkIdx = 0;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
        if (eHdrMode == AX_SNS_LINEAR_MODE)
            pCam->tSnsAttr.nSettingIndex = 33;
        else
            pCam->tSnsAttr.nSettingIndex = 34;
        pCam->tMipiAttr.eLaneNum = AX_MIPI_DATA_LANE_2;
        pCam->eInputMode = AX_INPUT_MODE_MIPI;
        if (i == 2) {
            pCam->eInputMode = AX_INPUT_MODE_BT656;
            pCam->bRegisterSns = AX_FALSE;
        }
        __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
        __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
        for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
            if (pCam->tPipeInfo[j].bAiispEnable && i < 2) {
                if (eHdrMode <= AX_SNS_LINEAR_MODE) {
                    strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/os04a10_sdr_dual3dnr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
                } else {
                    strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/os04a10_hdr_2x_ainr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
                }
            } else {
                strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
            }
        }
    }
    return 0;
}

static AX_U32 __sample_case_single_s5kjn1sq03(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    AX_S32 j = 0;
    SAMPLE_LOAD_RAW_NODE_E eLoadRawNode = pVinParam->eLoadRawNode;
    pCommonArgs->nCamCnt = 1;
    pCam = &pCamList[0];
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr, pCam->tChnAttr);
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->nPipeId = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->eLoadRawNode = eLoadRawNode;
    pCam->ptSnsHdl = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    pCam->eInputMode = AX_INPUT_MODE_MIPI;
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
    }
    return 0;
}

static AX_U32 __sample_case_config(SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs,
                                   COMMON_SYS_ARGS_T *pPrivArgs)
{
    AX_CAMERA_T         *pCamList = &gCams[0];
    SAMPLE_SNS_TYPE_E   eSnsType = OMNIVISION_OS04A10;

    COMM_ISP_PRT("eSysCase %d, eSysMode %d, eHdrMode %d, bAiispEnable %d\n", pVinParam->eSysCase,
                 pVinParam->eSysMode, pVinParam->eHdrMode, pVinParam->bAiispEnable);

    switch (pVinParam->eSysCase) {
    case SYS_CASE_SINGLE_DVP:
        eSnsType = SAMPLE_SNS_DVP;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleDVPSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleDVPSdr) / sizeof(gtSysCommPoolSingleDVPSdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleDVPSdr;

        /* private pool config */
        __cal_dump_pool(gtSysPrivatePoolSingleDVPSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtSysPrivatePoolSingleDVPSdr) / sizeof(gtSysPrivatePoolSingleDVPSdr[0]);
        pPrivArgs->pPoolCfg = gtSysPrivatePoolSingleDVPSdr;

        /* cams config */
        __sample_case_single_dvp(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SYS_CASE_SINGLE_BT601:
        eSnsType = SAMPLE_SNS_BT601;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleBTSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleBTSdr) / sizeof(gtSysCommPoolSingleBTSdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleBTSdr;

        /* private pool config */
        __cal_dump_pool(gtSysPrivatePoolSingleBTSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtSysPrivatePoolSingleBTSdr) / sizeof(gtSysPrivatePoolSingleBTSdr[0]);
        pPrivArgs->pPoolCfg = gtSysPrivatePoolSingleBTSdr;

        /* cams config */
        __sample_case_single_bt(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SYS_CASE_SINGLE_BT656:
        eSnsType = SAMPLE_SNS_BT656;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleBTSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleBTSdr) / sizeof(gtSysCommPoolSingleBTSdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleBTSdr;

        /* private pool config */
        __cal_dump_pool(gtSysPrivatePoolSingleBTSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtSysPrivatePoolSingleBTSdr) / sizeof(gtSysPrivatePoolSingleBTSdr[0]);
        pPrivArgs->pPoolCfg = gtSysPrivatePoolSingleBTSdr;

        /* cams config */
        __sample_case_single_bt(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SYS_CASE_SINGLE_BT1120:
        eSnsType = SAMPLE_SNS_BT1120;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleBTSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleBTSdr) / sizeof(gtSysCommPoolSingleBTSdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleBTSdr;

        /* private pool config */
        __cal_dump_pool(gtSysPrivatePoolSingleBTSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtSysPrivatePoolSingleBTSdr) / sizeof(gtSysPrivatePoolSingleBTSdr[0]);
        pPrivArgs->pPoolCfg = gtSysPrivatePoolSingleBTSdr;

        /* cams config */
        __sample_case_single_bt(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SYS_CASE_SINGLE_LVDS:
        eSnsType = SAMPLE_SNS_LVDS;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleLVDSSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleLVDSSdr) / sizeof(gtSysCommPoolSingleLVDSSdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleLVDSSdr;

        /* private pool config */
        __cal_dump_pool(gtSysPrivatePoolSingleLVDSSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtSysPrivatePoolSingleLVDSSdr) / sizeof(gtSysPrivatePoolSingleLVDSSdr[0]);
        pPrivArgs->pPoolCfg = gtSysPrivatePoolSingleLVDSSdr;

        /* cams config */
        __sample_case_single_lvds(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_SINGLE_OS04A10:
        eSnsType = OMNIVISION_OS04A10;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleOs04a10Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleOs04a10Sdr) / sizeof(gtSysCommPoolSingleOs04a10Sdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleOs04a10Sdr;

        /* private pool config */
        __cal_dump_pool(gtPrivatePoolSingleOs04a10Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolSingleOs04a10Sdr) / sizeof(gtPrivatePoolSingleOs04a10Sdr[0]);
        pPrivArgs->pPoolCfg = gtPrivatePoolSingleOs04a10Sdr;

        /* cams config */
        __sample_case_single_os04a10(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_DOUBLE_OS04A10:
        eSnsType = OMNIVISION_OS04A10;
        /* comm pool config */
        if (AX_SNS_LINEAR_MODE == pVinParam->eHdrMode) {
            __cal_dump_pool(gtSysCommPoolDoubleOs04a10Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolDoubleOs04a10Sdr) / sizeof(gtSysCommPoolDoubleOs04a10Sdr[0]);
            pCommonArgs->pPoolCfg  = gtSysCommPoolDoubleOs04a10Sdr;
        } else {
            __cal_dump_pool(gtSysCommPoolDoubleOs04a10Hdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolDoubleOs04a10Hdr) / sizeof(gtSysCommPoolDoubleOs04a10Hdr[0]);
            pCommonArgs->pPoolCfg  = gtSysCommPoolDoubleOs04a10Hdr;
        }

        /* private pool config */
        if (AX_SNS_LINEAR_MODE == pVinParam->eHdrMode) {
            __cal_dump_pool(gtPrivatePoolDoubleOs04a10Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolDoubleOs04a10Sdr) / sizeof(gtPrivatePoolDoubleOs04a10Sdr[0]);
            pPrivArgs->pPoolCfg  = gtPrivatePoolDoubleOs04a10Sdr;
        } else {
            __cal_dump_pool(gtPrivatePoolDoubleOs04a10Hdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolDoubleOs04a10Hdr) / sizeof(gtPrivatePoolDoubleOs04a10Hdr[0]);
            pPrivArgs->pPoolCfg  = gtPrivatePoolDoubleOs04a10Hdr;
        }

        /* cams config */
        __sample_case_double_os04a10(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_DOUBLE_SC450AI:
        eSnsType = SMARTSENS_SC450AI;
        /* comm pool config */
        if (AX_SNS_LINEAR_MODE == pVinParam->eHdrMode) {
            __cal_dump_pool(gtSysCommPoolDoubleSc450aiSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolDoubleSc450aiSdr) / sizeof(gtSysCommPoolDoubleSc450aiSdr[0]);
            pCommonArgs->pPoolCfg  = gtSysCommPoolDoubleSc450aiSdr;
        } else {
            __cal_dump_pool(gtSysCommPoolDoubleSc450aiHdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolDoubleSc450aiHdr) / sizeof(gtSysCommPoolDoubleSc450aiHdr[0]);
            pCommonArgs->pPoolCfg  = gtSysCommPoolDoubleSc450aiHdr;
        }

        /* private pool config */
        if (AX_SNS_LINEAR_MODE == pVinParam->eHdrMode) {
            __cal_dump_pool(gtPrivatePoolDoubleSc450aiSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolDoubleSc450aiSdr) / sizeof(gtPrivatePoolDoubleSc450aiSdr[0]);
            pPrivArgs->pPoolCfg  = gtPrivatePoolDoubleSc450aiSdr;
        } else {
            __cal_dump_pool(gtPrivatePoolDoubleSc450aiHdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolDoubleSc450aiHdr) / sizeof(gtPrivatePoolDoubleSc450aiHdr[0]);
            pPrivArgs->pPoolCfg  = gtPrivatePoolDoubleSc450aiHdr;
        }

        /* cams config */
        __sample_case_double_sc450ai(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_SINGLE_SC450AI:
        eSnsType = SMARTSENS_SC450AI;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleOs450aiSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleOs450aiSdr) / sizeof(gtSysCommPoolSingleOs450aiSdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleOs450aiSdr;

        /* private pool config */
        __cal_dump_pool(gtPrivatePoolSingleOs450aiSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolSingleOs450aiSdr) / sizeof(gtPrivatePoolSingleOs450aiSdr[0]);
        pPrivArgs->pPoolCfg = gtPrivatePoolSingleOs450aiSdr;

        /* cams config */
        __sample_case_single_sc450ai(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_DOUBLE_OS04A10_AND_BT656:
        /* comm pool config */
        if (AX_SNS_LINEAR_MODE == pVinParam->eHdrMode) {
            __cal_dump_pool(gtSysCommPoolDoubleOs04a10Bt656Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolDoubleOs04a10Bt656Sdr) / sizeof(gtSysCommPoolDoubleOs04a10Bt656Sdr[0]);
            pCommonArgs->pPoolCfg  = gtSysCommPoolDoubleOs04a10Bt656Sdr;
        } else {
            __cal_dump_pool(gtSysCommPoolDoubleOs04a10Bt656Hdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolDoubleOs04a10Bt656Hdr) / sizeof(gtSysCommPoolDoubleOs04a10Bt656Hdr[0]);
            pCommonArgs->pPoolCfg  = gtSysCommPoolDoubleOs04a10Bt656Hdr;
        }

        /* private pool config */
        if (AX_SNS_LINEAR_MODE == pVinParam->eHdrMode) {
            __cal_dump_pool(gtPrivatePoolDoubleOs04a10Bt656Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolDoubleOs04a10Bt656Sdr) / sizeof(gtPrivatePoolDoubleOs04a10Bt656Sdr[0]);
            pPrivArgs->pPoolCfg  = gtPrivatePoolDoubleOs04a10Bt656Sdr;
        } else {
            __cal_dump_pool(gtPrivatePoolDoubleOs04a10Bt656Hdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
            pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolDoubleOs04a10Bt656Hdr) / sizeof(gtPrivatePoolDoubleOs04a10Bt656Hdr[0]);
            pPrivArgs->pPoolCfg  = gtPrivatePoolDoubleOs04a10Bt656Hdr;
        }

        /* cams config */
        __sample_case_double_os04a10_and_bt656(pCamList, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_SINGLE_S5KJN1SQ03:
        eSnsType = SAMSUNG_S5KJN1SQ03;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingles5kjn1sq03Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingles5kjn1sq03Sdr) / sizeof(gtSysCommPoolSingles5kjn1sq03Sdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingles5kjn1sq03Sdr;

        /* private pool config */
        __cal_dump_pool(gtPrivatePoolSingles5kjn1sq03Sdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolSingles5kjn1sq03Sdr) / sizeof(gtPrivatePoolSingles5kjn1sq03Sdr[0]);
        pPrivArgs->pPoolCfg = gtPrivatePoolSingles5kjn1sq03Sdr;

        /* cams config */
        __sample_case_single_s5kjn1sq03(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_SINGLE_DUMMY:
    default:
        eSnsType = SAMPLE_SNS_DUMMY;
        /* pool config */
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleDummySdr) / sizeof(gtSysCommPoolSingleDummySdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleDummySdr;

        /* private pool config */
        pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolSingleDummySdr) / sizeof(gtPrivatePoolSingleDummySdr[0]);
        pPrivArgs->pPoolCfg = gtPrivatePoolSingleDummySdr;

        /* cams config */
        __sample_case_single_dummy(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    }

    return 0;
}

AX_S32 SAMPLE_CASE_VIN(SAMPLE_VIN_PARAM_T *pVinParam)
{
    AX_S32 axRet = 0;
    AX_S32 i = 0, j = 0;
    COMMON_SYS_ARGS_T tCommonArgs = {0};
    COMMON_SYS_ARGS_T tPrivArgs = {0};

    /* Step1: cam config & pool Config */
    __sample_case_config(pVinParam, &tCommonArgs, &tPrivArgs);

    /* Step2: SYS Init */
    axRet = COMMON_SYS_Init(&tCommonArgs);
    if (axRet) {
        COMM_ISP_PRT("COMMON_SYS_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL;
    }
    /* Step3: NPU Init */
    axRet = COMMON_NPU_Init();
    if (axRet) {
        COMM_ISP_PRT("COMMON_NPU_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL1;
    }
    /* Step4: Cam Init */
    axRet = COMMON_CAM_Init();
    if (axRet) {
        COMM_ISP_PRT("COMMON_CAM_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL1;
    }

    axRet = COMMON_CAM_PrivPoolInit(&tPrivArgs);
    if (axRet) {
        COMM_ISP_PRT("COMMON_CAM_PrivPoolInit fail, ret:0x%x", axRet);
        goto EXIT_FAIL1;
    }
    /* Step5: Cam Open */
    axRet = COMMON_CAM_Open(&gCams[0], tCommonArgs.nCamCnt);
    if (axRet) {
        COMM_ISP_PRT("COMMON_CAM_Open fail, ret:0x%x", axRet);
        goto EXIT_FAIL2;
    }
    /* Step6. NT Init (tuning socket server. optional)
    Stream default port 6000, Ctrl default port 8082 */
    axRet = COMMON_NT_Init(6000, 8082);
    if (axRet) {
        COMM_ISP_PRT("COMMON_NT_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL3;
    }
    /* update pipe attribute */
    for (i = 0; i < tCommonArgs.nCamCnt; i++) {
        for (j = 0; j < gCams[i].tDevBindPipe.nNum; j++) {
            COMMON_NT_UpdateSource(gCams[i].tDevBindPipe.nPipeId[j]);
        }
    }

    while (!gLoopExit) {
        sleep(1);
    }

    COMMON_NT_DeInit();
EXIT_FAIL3:
    COMMON_CAM_Close(&gCams[0], tCommonArgs.nCamCnt);
EXIT_FAIL2:
    COMMON_CAM_Deinit();
EXIT_FAIL1:
    COMMON_SYS_DeInit();
EXIT_FAIL:
    return axRet;
}

AX_VOID PrintHelp()
{
    COMM_ISP_PRT("command:\n");
    COMM_ISP_PRT("\t-c: VIN Sample Case:\n");
    COMM_ISP_PRT("\t\t0: Single DummySensor\n");
    COMM_ISP_PRT("\t\t1: Single OS04A10\n");
    COMM_ISP_PRT("\t\t2: Double OS04A10\n");
    COMM_ISP_PRT("\t\t3: Single SC450AI\n");
    COMM_ISP_PRT("\t\t4: Double SC450AI\n");
    COMM_ISP_PRT("\t\t5: Double OS04A10 + BT656\n");
    COMM_ISP_PRT("\t\t6: Single S5KJN1SQ03\n");
    COMM_ISP_PRT("\t\t7: Single OS04A10 DCG HDR\n");
    COMM_ISP_PRT("\t\t8: Single OS04A10 DCG VS HDR\n");

    COMM_ISP_PRT("\t\t20: Single DVP\n");
    COMM_ISP_PRT("\t\t21: Single BT.601\n");
    COMM_ISP_PRT("\t\t22: Single BT.656\n");
    COMM_ISP_PRT("\t\t23: Single BT.1120\n");
    COMM_ISP_PRT("\t\t24: Single LVDS\n");

    COMM_ISP_PRT("\t-m: Work Mode:\n");
    COMM_ISP_PRT("\t\t0: LoadRaw Mode\n");
    COMM_ISP_PRT("\t\t1: Sensor Mode\n");
    COMM_ISP_PRT("\t\t2: TPG Mode\n");

    COMM_ISP_PRT("\t-e: SDR/HDR Mode:\n");
    COMM_ISP_PRT("\t\t1: SDR\n");
    COMM_ISP_PRT("\t\t2: HDR 2DOL\n");

    COMM_ISP_PRT("\t-a: Enable AIISP:\n");
    COMM_ISP_PRT("\t\t0: Disable(default)\n");
    COMM_ISP_PRT("\t\t1: Enable\n");

    COMM_ISP_PRT("\t-d: Continue Frame Dump:\n");
    COMM_ISP_PRT("\t\tn: N Frame Blk\n");
}

int main(int argc, char *argv[])
{
    COMM_ISP_PRT("VIN Sample. Build at %s %s\n", __DATE__, __TIME__);

    int c;
    int isExit = 0;
    SAMPLE_VIN_PARAM_T tVinParam = {
        SAMPLE_VIN_SINGLE_OS04A10,
        COMMON_VIN_SENSOR,
        AX_SNS_LINEAR_MODE,
        LOAD_RAW_NONE,
        0,
    };
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, __sigint);

    if (argc < 3) {
        PrintHelp();
        exit(0);
    }

    while ((c = getopt(argc, argv, "c:m:e:l:d:a:h")) != -1) {
        isExit = 0;
        switch (c) {
        case 'c':
            tVinParam.eSysCase = (SAMPLE_VIN_CASE_E)atoi(optarg);
            break;
        case 'm':
            tVinParam.eSysMode = (COMMON_VIN_MODE_E)atoi(optarg);
            break;
        case 'e':
            tVinParam.eHdrMode = (AX_SNS_HDR_MODE_E)atoi(optarg);
            break;
        case 'd':
            tVinParam.nDumpFrameNum = (AX_S32)atoi(optarg);
            break;
        case 'a':
            tVinParam.bAiispEnable = (AX_BOOL)atoi(optarg);
            break;
        case 'h':
            isExit = 1;
            break;
        default:
            isExit = 1;
            break;
        }
    }

    if (isExit) {
        PrintHelp();
        exit(0);
    }

    if (tVinParam.eSysCase >= SAMPLE_VIN_BUTT || tVinParam.eSysCase <= SAMPLE_VIN_NONE) {
        COMM_ISP_PRT("error sys case : %d\n", tVinParam.eSysCase);
        exit(0);
    }

    if (tVinParam.eSysMode >= COMMON_VIN_BUTT || tVinParam.eSysMode <= COMMON_VIN_NONE) {
        COMM_ISP_PRT("error sys mode : %d\n", tVinParam.eSysMode);
        exit(0);
    }

    if (tVinParam.eLoadRawNode >= LOAD_RAW_BUTT || tVinParam.eLoadRawNode < LOAD_RAW_NONE) {
        COMM_ISP_PRT("error load raw mode : %d\n", tVinParam.eLoadRawNode);
        exit(0);
    }

    if (tVinParam.eSysCase == SAMPLE_VIN_SINGLE_OS04A10_DCG_HDR ||
        tVinParam.eSysCase == SAMPLE_VIN_SINGLE_OS04A10_DCG_VS_HDR) {
        SAMPLE_CASE_VIN_DCG_VS(&tVinParam);
    } else {
        SAMPLE_CASE_VIN(&tVinParam);
    }

    COMM_ISP_PRT("Sample Completed\n");

    exit(0);
}
