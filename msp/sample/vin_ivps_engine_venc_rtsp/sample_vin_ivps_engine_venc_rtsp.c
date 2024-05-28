/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_vin_ivps_engine_venc_rtsp.h"
#include "sample_ivps_hal.h"
#include "sample_engine.h"


/* comm pool */
COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_16BPP, 10},      /* vin raw16 use */
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 10},    /* vin nv21/nv21 use */
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 3, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 3, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 4},    /* vin nv21/nv21 use */
    {1920, 1080, 1920, AX_FORMAT_YUV420_SEMIPLANAR, 3},    /* vin nv21/nv21 use */
    {720, 576, 720, AX_FORMAT_YUV420_SEMIPLANAR, 3},    /* vin nv21/nv21 use */
};

/* private pool */
COMMON_SYS_POOL_CFG_T gtPrivatePoolSingleDummySdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_16BPP, 10},
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolSingleOs04a10Sdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 12, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw16 use */
};

// SC450AI
COMMON_SYS_POOL_CFG_T gtSysCommPoolSingleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 3, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 4},    /* vin nv21/nv21 use */
    {1920, 1080, 1920, AX_FORMAT_YUV420_SEMIPLANAR, 3},    /* vin nv21/nv21 use */
    {720, 576, 720, AX_FORMAT_YUV420_SEMIPLANAR, 3},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolSingleSc450aiSdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 8, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

static AX_CAMERA_T gCams[MAX_CAMERAS] = {0};
static SAMPLE_RTSP_PARAM_T gRtspParam;
static SAMPLE_CHN_ATTR_T gOutChnAttr[] = {
    {
        .nStride = 2688,
        .nWidth =  2688,
        .nHeight = 1520,
        .eFbcMode = AX_COMPRESS_MODE_NONE,
    },
    {
        .nStride = 1920,
        .nWidth =  1920,
        .nHeight = 1080,
        .eFbcMode = AX_COMPRESS_MODE_NONE,
    },
    {
        .nStride = 640,
        .nWidth = 640,
        .nHeight = 360,
        .eFbcMode = AX_COMPRESS_MODE_NONE,
    }
};

static AX_ISP_IQ_LDC_PARAM_T ldc_param = {
    /* nLdcEnable */
    1,
    /* nType */
    0,
    /* tLdcV1Param */
    {
        /* bAspect */
        0,
        /* nXRatio */
        0,
        /* nYRatio */
        0,
        /* nXYRatio */
        0,
        /* nCenterXOffset */
        0,
        /* nCenterYOffset */
        0,
        /* nDistortionRatio */
        1234,
        /* nSpreadCoef */
        0,
    },
    /* tLdcV2Param */
    {
        /* nMatrix[3][3] */
        {
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 1, /*0 - 2*/},
        },
        /* nDistortionCoeff[8] */
        {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
    },
};


SAMPLE_VIN_PARAM_T gtVinParam = {
    SAMPLE_VIN_SINGLE_OS04A10,
    COMMON_VIN_SENSOR,
    AX_SNS_LINEAR_MODE,
    LOAD_RAW_NONE,
    0,
    .statDeltaPtsFrmNum = 0,
};

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
    pCam->tPipeAttr[pCam->nPipeId].eSnsMode = eHdrMode;
    pCam->tPipeAttr[pCam->nPipeId].bAiIspEnable = bAiispEnable;
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
        pCam->nPipeId = 0;
        COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);

        pCam->nDevId = 0;
        pCam->nRxDev = 0;
        pCam->tSnsClkAttr.nSnsClkIdx = 0;
        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
        pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(eSnsType);
        pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
        pCam->eLoadRawNode = eLoadRawNode;
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
#if 0
static AX_U32 __sample_case_single_os08a20(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    AX_S32 j = 0;
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
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        if (pCam->tPipeInfo[j].bAiispEnable) {
            if (eHdrMode <= AX_SNS_LINEAR_MODE) {
                strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/os08a20_sdr_dual3dnr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
            } else {
                strncpy(pCam->tPipeInfo[j].szBinPath, "/opt/etc/os08a20_hdr_2x_ainr.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
            }
        } else {
            strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
        }
    }
    return 0;
}
#endif
static AX_U32 __sample_case_single_os04a10(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;
    AX_S32 j = 0;
    pCommonArgs->nCamCnt = 1;
    pCam = &pCamList[0];
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->nPipeId = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], eHdrMode);
    __set_vin_attr(pCam, eSnsType, eHdrMode, eSysMode, pVinParam->bAiispEnable);
    for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        strncpy(pCam->tPipeInfo[j].szBinPath, "null.bin", sizeof(pCam->tPipeInfo[j].szBinPath));
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
    pCam->nPipeId = 0;
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                                &pCam->tSnsClkAttr, &pCam->tDevAttr,
                                &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->eLoadRawNode = eLoadRawNode;
    pCam->tDevBindPipe.nPipeId[0] = pCam->nPipeId;
    pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(eSnsType);
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

static AX_U32 __sample_case_config(SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs,
                                   COMMON_SYS_ARGS_T *pPrivArgs)
{
    AX_CAMERA_T         *pCamList = &gCams[0];
    SAMPLE_SNS_TYPE_E   eSnsType = OMNIVISION_OS04A10;

    ALOGI2("eSysCase %d, eSysMode %d, eLoadRawNode %d, eHdrMode %d, bAiispEnable %d", pVinParam->eSysCase,
                 pVinParam->eSysMode,
                 pVinParam->eLoadRawNode, pVinParam->eHdrMode, pVinParam->bAiispEnable);

    switch (pVinParam->eSysCase) {
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
    case SAMPLE_VIN_SINGLE_SC450AI:
        eSnsType = SMARTSENS_SC450AI;
        /* comm pool config */
        __cal_dump_pool(gtSysCommPoolSingleSc450aiSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolSingleSc450aiSdr) / sizeof(gtSysCommPoolSingleSc450aiSdr[0]);
        pCommonArgs->pPoolCfg = gtSysCommPoolSingleSc450aiSdr;

        /* private pool config */
        __cal_dump_pool(gtPrivatePoolSingleSc450aiSdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolSingleSc450aiSdr) / sizeof(gtPrivatePoolSingleSc450aiSdr[0]);
        pPrivArgs->pPoolCfg = gtPrivatePoolSingleSc450aiSdr;

        /* cams config */
        __sample_case_single_sc450ai(pCamList, eSnsType, pVinParam, pCommonArgs);
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

static VENC_GETSTREAM_PARAM_T gGetStreamPara[SAMPLE_VENC_CHN_NUM_MAX];
static pthread_t gGetStreamPid[SAMPLE_VENC_CHN_NUM_MAX];
typedef struct
{
    AX_U64 totalGetStrmNum;
    AX_U64 maxDeltaPts;
    AX_U64 minDeltaPts;
    AX_U64 totalDeltaPts;
} SAMPLE_DELTA_PTS_INFO_T;
#define SAMPLE_MIN_DELTAPTS_NUM (30)

SAMPLE_DELTA_PTS_INFO_T gSampleDeltaPts[64];
static AX_VOID SAMPLE_DeltaPtsStatistic(AX_S32 Chn, AX_VENC_STREAM_T *pstStream)
{
    if (gtVinParam.statDeltaPtsFrmNum < SAMPLE_MIN_DELTAPTS_NUM)
        return;

    static bool bPrint = AX_TRUE;

    SAMPLE_DELTA_PTS_INFO_T *pstDeltaPts = &gSampleDeltaPts[Chn];
    AX_U64 currPts = 0, inPts = 0, deltaPts = 0, seqNum = 0, avgDeltaPts = 0;
    AX_SYS_GetCurPTS(&currPts);

    inPts = pstStream->stPack.u64PTS;
    seqNum = pstStream->stPack.u64SeqNum;
    deltaPts = currPts - inPts;
    if (pstDeltaPts->totalGetStrmNum >= gtVinParam.statDeltaPtsFrmNum) {
        if (!bPrint)
            return;

        avgDeltaPts = pstDeltaPts->totalDeltaPts - pstDeltaPts->maxDeltaPts -
                      pstDeltaPts->minDeltaPts;
        ALOGI2("chn-%d: totalNum=%llu, minDeltaPts=%llu, maxDeltaPts=%llu, avgDeltaPts=%llu(us).\n", Chn,
              pstDeltaPts->totalGetStrmNum, pstDeltaPts->minDeltaPts,
              pstDeltaPts->maxDeltaPts,
              avgDeltaPts/(pstDeltaPts->totalGetStrmNum-2)); /* not include min,max delta pts */

        bPrint = AX_FALSE;

        return;
    }

    if (inPts > 0 && deltaPts > 0) {
        if (deltaPts > pstDeltaPts->maxDeltaPts)
            pstDeltaPts->maxDeltaPts = deltaPts;

        if (0 == pstDeltaPts->totalGetStrmNum)
            pstDeltaPts->minDeltaPts = deltaPts;

        if (deltaPts < pstDeltaPts->minDeltaPts)
            pstDeltaPts->minDeltaPts = deltaPts;

        pstDeltaPts->totalDeltaPts += deltaPts;
        pstDeltaPts->totalGetStrmNum++;

    } else {
        ALOGE("chn-%d: invalid inPts=%llu, seqNum=%llu, currPts=%llu.\n", Chn, inPts, seqNum, currPts);
        return;
    }

    return;
}

/* venc get stream task */
static void *VencGetStreamProc(void *arg)
{
    AX_S32 s32Ret = -1;
    AX_VENC_RECV_PIC_PARAM_T stRecvParam;
    VENC_GETSTREAM_PARAM_T *pstPara;
    pstPara = (VENC_GETSTREAM_PARAM_T *)arg;
    AX_VENC_STREAM_T stStream = {0};
    AX_S16 syncType = -1;
    FILE *pStrm = NULL;
    AX_S8 esName[150];
    AX_U32 totalGetStream = 0;

    s32Ret = AX_VENC_StartRecvFrame(pstPara->VeChn, &stRecvParam);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_VENC_StartRecvFrame failed, s32Ret:0x%x", s32Ret);
        return NULL;
    }

    memset(esName, 0, 150);

    if (pstPara->ePayloadType == PT_H265)
        sprintf((char*)esName, "enc_%d.265", pstPara->VeChn);
    else if (pstPara->ePayloadType == PT_H264)
        sprintf((char*)esName, "enc_%d.264", pstPara->VeChn);

    pStrm = fopen((char*)esName, "wb");

    if (pStrm == NULL) {
        ALOGE("Open output file error!");
    }

    while (AX_TRUE == pstPara->bThreadStart && !ThreadLoopStateGet()) {
        s32Ret = AX_VENC_GetStream(pstPara->VeChn, &stStream, syncType);

        if (AX_SUCCESS == s32Ret) {
            totalGetStream++;
            SAMPLE_DeltaPtsStatistic(pstPara->VeChn, &stStream);            /* save 30 frames default */
            /* save 30 frames default */
            if (pStrm && totalGetStream <= 30){
                fwrite(stStream.stPack.pu8Addr, 1, stStream.stPack.u32Len, pStrm);
                fflush(pStrm);
            }

            /* Send to RTSP */
            if (gRtspParam.pRtspHandle) {
                AX_BOOL bIFrame = (AX_VENC_INTRA_FRAME == stStream.stPack.enCodingType) ? AX_TRUE : AX_FALSE;
                AX_Rtsp_SendNalu(gRtspParam.pRtspHandle, pstPara->VeChn, stStream.stPack.pu8Addr, stStream.stPack.u32Len,
                                     stStream.stPack.u64PTS, bIFrame);
                 ALOGI("VencChn %d: u64PTS:%lld pu8Addr:%p u32Len:%d enCodingType:%d", pstPara->VeChn,
                       stStream.stPack.u64PTS, stStream.stPack.pu8Addr, stStream.stPack.u32Len, stStream.stPack.enCodingType);
            }

            s32Ret = AX_VENC_ReleaseStream(pstPara->VeChn, &stStream);
            if (AX_SUCCESS != s32Ret) {
                ALOGE("VencChn %d: AX_VENC_ReleaseStream failed!s32Ret:0x%x", pstPara->VeChn, s32Ret);
                goto EXIT;
            }
        } else if (AX_ERR_VENC_FLOW_END == s32Ret) {
            ALOGI2("VencChn %d: AX_VENC_GetStream end flow,exit!", pstPara->VeChn);
            goto EXIT;
        }
    }

EXIT:

    if (pStrm != NULL) {
        fclose(pStrm);
        pStrm = NULL;
    }

    ALOGI2("VencChn %d: Total get %u encoded frames. getStream Exit!", pstPara->VeChn, totalGetStream);
    return NULL;
}

static AX_S32 SAMPLE_VENC_Init(AX_S32 nChnNum, AX_IVPS_ROTATION_E eRotAngle)
{
    AX_VENC_CHN_ATTR_T stVencChnAttr;
    VIDEO_CONFIG_T config = { 0 };
    AX_S32 VencChn = 0,s32Ret = 0;
    AX_VENC_MOD_ATTR_T stModAttr = {
        .enVencType = AX_VENC_MULTI_ENCODER,
        .stModThdAttr.u32TotalThreadNum = 1,
        .stModThdAttr.bExplicitSched = AX_FALSE,
    };

    s32Ret = AX_VENC_Init(&stModAttr);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_VENC_Init failed, s32Ret:0x%x", s32Ret);
        return s32Ret;
    }

    config.stRCInfo.eRCType = SAMPLE_RC_CBR;
    config.nGOP = 120;
    config.stRCInfo.nMinQp = 10;
    config.stRCInfo.nMaxQp = 51;
    config.stRCInfo.nMinIQp = 10;
    config.stRCInfo.nMaxIQp = 51;
    config.stRCInfo.nIntraQpDelta = -2;

    for (VencChn = 0; VencChn < nChnNum; VencChn++) {
        switch (VencChn) {
        case 0:
            config.ePayloadType = PT_H264;
            config.nSrcFrameRate = 30;
            config.nDstFrameRate = 30;
            config.nBitrate = 4096;
            break;
        case 1:
            config.ePayloadType = PT_H264;
            config.nSrcFrameRate = 30;
            config.nDstFrameRate = 30;
            config.nBitrate = 2048;
            break;
        case 2:
            config.ePayloadType = PT_H264;
            config.nSrcFrameRate = 30;
            config.nDstFrameRate = 30;
            config.nBitrate = 1024;
            break;
        }

        if (eRotAngle == AX_IVPS_ROTATION_90 || eRotAngle == AX_IVPS_ROTATION_270) {
            config.nInWidth = gOutChnAttr[VencChn].nHeight;
            config.nInHeight = gOutChnAttr[VencChn].nWidth;
        } else {
            config.nInWidth = gOutChnAttr[VencChn].nWidth;
            config.nInHeight = gOutChnAttr[VencChn].nHeight;
        }
        if (gOutChnAttr[VencChn].eFbcMode)
            config.nStride = ALIGN_UP(gOutChnAttr[VencChn].nWidth, 128);
        else
            config.nStride = ALIGN_UP(gOutChnAttr[VencChn].nWidth, 16);

        memset(&stVencChnAttr, 0, sizeof(AX_VENC_CHN_ATTR_T));

        stVencChnAttr.stVencAttr.u32MaxPicWidth = config.nInWidth;
        stVencChnAttr.stVencAttr.u32MaxPicHeight = config.nInHeight;
        stVencChnAttr.stVencAttr.u8InFifoDepth = 4;
        stVencChnAttr.stVencAttr.u8OutFifoDepth = 4;
        stVencChnAttr.stVencAttr.u32PicWidthSrc = config.nInWidth;
        stVencChnAttr.stVencAttr.u32PicHeightSrc = config.nInHeight;
        stVencChnAttr.stRcAttr.stFrameRate.fSrcFrameRate  = 30;
        stVencChnAttr.stRcAttr.stFrameRate.fDstFrameRate = 30;

        ALOGI2("VencChn %d:w:%d, h:%d, s:%d, rcType:%d, payload:%d", VencChn,
               stVencChnAttr.stVencAttr.u32PicWidthSrc,
               stVencChnAttr.stVencAttr.u32PicHeightSrc,
               config.nStride,
               config.stRCInfo.eRCType,
               config.ePayloadType);

        stVencChnAttr.stVencAttr.u32BufSize = config.nStride * config.nInHeight * 3 / 2;
        stVencChnAttr.stVencAttr.enLinkMode = AX_LINK_MODE;

        /* GOP Setting */
        stVencChnAttr.stGopAttr.enGopMode = AX_VENC_GOPMODE_NORMALP;

        stVencChnAttr.stVencAttr.enType = config.ePayloadType;
        switch (stVencChnAttr.stVencAttr.enType) {
            case PT_H265: {
                stVencChnAttr.stVencAttr.enProfile = AX_VENC_HEVC_MAIN_PROFILE;
                stVencChnAttr.stVencAttr.enLevel = AX_VENC_HEVC_LEVEL_5_1;
                stVencChnAttr.stVencAttr.enTier = AX_VENC_HEVC_MAIN_TIER;

                if (config.stRCInfo.eRCType == SAMPLE_RC_CBR) {
                    AX_VENC_H265_CBR_T stH265Cbr;
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265CBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH265Cbr.u32Gop = config.nGOP;
                    stH265Cbr.u32BitRate = config.nBitrate;
                    stH265Cbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH265Cbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH265Cbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH265Cbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH265Cbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    stH265Cbr.u32MinIprop = 30;
                    stH265Cbr.u32MaxIprop = 40;
                    memcpy(&stVencChnAttr.stRcAttr.stH265Cbr, &stH265Cbr, sizeof(AX_VENC_H265_CBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_VBR) {
                    AX_VENC_H265_VBR_T stH265Vbr;
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265VBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH265Vbr.u32Gop = config.nGOP;
                    stH265Vbr.u32MaxBitRate = config.nBitrate;
                    stH265Vbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH265Vbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH265Vbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH265Vbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH265Vbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    memcpy(&stVencChnAttr.stRcAttr.stH265Vbr, &stH265Vbr, sizeof(AX_VENC_H265_VBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_FIXQP) {
                    AX_VENC_H265_FIXQP_T stH265FixQp;
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265FIXQP;
                    stH265FixQp.u32Gop = config.nGOP;
                    stH265FixQp.u32IQp = 25;
                    stH265FixQp.u32PQp = 30;
                    stH265FixQp.u32BQp = 32;
                    memcpy(&stVencChnAttr.stRcAttr.stH265FixQp, &stH265FixQp, sizeof(AX_VENC_H265_FIXQP_T));
                }
                break;
            }
            case PT_H264: {
                stVencChnAttr.stVencAttr.enProfile = AX_VENC_H264_MAIN_PROFILE;
                stVencChnAttr.stVencAttr.enLevel = AX_VENC_H264_LEVEL_5_2;

                if (config.stRCInfo.eRCType == SAMPLE_RC_CBR) {
                    AX_VENC_H264_CBR_T stH264Cbr;
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264CBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH264Cbr.u32Gop = config.nGOP;
                    stH264Cbr.u32BitRate = config.nBitrate;
                    stH264Cbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH264Cbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH264Cbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH264Cbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH264Cbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    stH264Cbr.u32MinIprop = 10;
                    stH264Cbr.u32MaxIprop = 40;
                    memcpy(&stVencChnAttr.stRcAttr.stH264Cbr, &stH264Cbr, sizeof(AX_VENC_H264_CBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_VBR) {
                    AX_VENC_H264_VBR_T stH264Vbr;
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264VBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH264Vbr.u32Gop = config.nGOP;
                    stH264Vbr.u32MaxBitRate = config.nBitrate;
                    stH264Vbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH264Vbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH264Vbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH264Vbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH264Vbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    memcpy(&stVencChnAttr.stRcAttr.stH264Vbr, &stH264Vbr, sizeof(AX_VENC_H264_VBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_FIXQP) {
                    AX_VENC_H264_FIXQP_T stH264FixQp;
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264FIXQP;
                    stH264FixQp.u32Gop = config.nGOP;
                    stH264FixQp.u32IQp = 25;
                    stH264FixQp.u32PQp = 30;
                    stH264FixQp.u32BQp = 32;
                    memcpy(&stVencChnAttr.stRcAttr.stH264FixQp, &stH264FixQp, sizeof(AX_VENC_H264_FIXQP_T));
                }
                break;
            }
            default:
                ALOGE("VencChn %d:Payload type unrecognized.",VencChn);
                return -1;
        }

        AX_S32 ret = AX_VENC_CreateChn(VencChn, &stVencChnAttr);
        if (AX_SUCCESS != ret) {
            ALOGE("VencChn %d: AX_VENC_CreateChn failed, s32Ret:0x%x", VencChn, ret);
            return -1;
        }

        /* create get output stream thread */
        gGetStreamPara[VencChn].VeChn = VencChn;
        gGetStreamPara[VencChn].bThreadStart = AX_TRUE;
        gGetStreamPara[VencChn].ePayloadType = config.ePayloadType;
        pthread_create(&gGetStreamPid[VencChn], NULL, VencGetStreamProc, (void *)&gGetStreamPara[VencChn]);
    }

    return 0;
}

static AX_S32 SampleVencDeInit(AX_S32 nChnNum)
{
    AX_S32 VencChn = 0, s32Ret = 0, s32Retry = 5;

    for (VencChn = 0; VencChn < nChnNum; VencChn++) {

        s32Ret = AX_VENC_StopRecvFrame(VencChn);
        if (0 != s32Ret) {
            ALOGE("VencChn %d:AX_VENC_StopRecvFrame failed,s32Ret:0x%x", VencChn, s32Ret);
            return s32Ret;
        }

        s32Retry = 5;
        do {
            s32Ret = AX_VENC_DestroyChn(VencChn);
            if (AX_ERR_VENC_BUSY == s32Ret) {
                ALOGE("VencChn %d:AX_VENC_DestroyChn return AX_ERR_VENC_BUSY,retry...", VencChn);
                --s32Retry;
                usleep(100 * 1000);
            } else {
                break;
            }
        } while (s32Retry >= 0);

        if (s32Retry == -1 || AX_SUCCESS != s32Ret) {
            ALOGE("VencChn %d: AX_VENC_DestroyChn failed, s32Retry=%d, s32Ret=0x%x\n", VencChn, s32Retry, s32Ret);
        }

        if (AX_TRUE == gGetStreamPara[VencChn].bThreadStart) {
            gGetStreamPara[VencChn].bThreadStart = AX_FALSE;
            pthread_join(gGetStreamPid[VencChn], NULL);
        }
    }
    s32Ret = AX_VENC_Deinit();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_VENC_Deinit failed, s32Ret=0x%x", s32Ret);
        return s32Ret;
    }

    return 0;
}

static int SAMPLE_IVPS_Init(AX_S32 nGrpId, AX_S32 nChnNum, AX_IVPS_ROTATION_E eRotAngle)
{
    AX_S32 s32Ret = 0, nChn;
    AX_IVPS_GRP_ATTR_T stGrpAttr = { 0 };
    AX_IVPS_PIPELINE_ATTR_T stPipelineAttr = { 0 };

    s32Ret = AX_IVPS_Init();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_Init failed,s32Ret:0x%x", s32Ret);
        return s32Ret;
    }

    stGrpAttr.nInFifoDepth = 2;
    stGrpAttr.ePipeline = AX_IVPS_PIPELINE_DEFAULT;
    s32Ret = AX_IVPS_CreateGrp(nGrpId, &stGrpAttr);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_CreateGrp failed,nGrp %d,s32Ret:0x%x", nGrpId, s32Ret);
        return s32Ret;
    }

    stPipelineAttr.nOutChnNum = nChnNum + 1;
    stPipelineAttr.tFilter[0][0].bEngage = AX_TRUE;
    if (eRotAngle == AX_IVPS_ROTATION_90 || eRotAngle == AX_IVPS_ROTATION_270) {
        stPipelineAttr.tFilter[0][0].nDstPicWidth = gOutChnAttr[0].nHeight;
        stPipelineAttr.tFilter[0][0].nDstPicHeight = gOutChnAttr[0].nWidth;
    } else {
        stPipelineAttr.tFilter[0][0].nDstPicWidth = gOutChnAttr[0].nWidth;
        stPipelineAttr.tFilter[0][0].nDstPicHeight = gOutChnAttr[0].nHeight;
    }
    stPipelineAttr.tFilter[0][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[0][0].nDstPicWidth, 128);
    stPipelineAttr.tFilter[0][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
    stPipelineAttr.tFilter[0][0].eEngine = AX_IVPS_ENGINE_VPP;

    for (nChn = 0; nChn < nChnNum; nChn++) {
        stPipelineAttr.tFilter[nChn + 1][0].bEngage = AX_TRUE;
        if (eRotAngle == AX_IVPS_ROTATION_90 || eRotAngle == AX_IVPS_ROTATION_270) {
            stPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth = gOutChnAttr[nChn].nHeight;
            stPipelineAttr.tFilter[nChn + 1][0].nDstPicHeight = gOutChnAttr[nChn].nWidth;
        } else {
            stPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth = gOutChnAttr[nChn].nWidth;
            stPipelineAttr.tFilter[nChn + 1][0].nDstPicHeight = gOutChnAttr[nChn].nHeight;
        }
        stPipelineAttr.tFilter[nChn + 1][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth, 128);
        stPipelineAttr.tFilter[nChn + 1][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        stPipelineAttr.tFilter[nChn + 1][0].eEngine = AX_IVPS_ENGINE_VPP;

        stPipelineAttr.tFilter[nChn + 1][1].bEngage = AX_TRUE;
        stPipelineAttr.tFilter[nChn + 1][1].nDstPicWidth = gOutChnAttr[nChn].nWidth;
        stPipelineAttr.tFilter[nChn + 1][1].nDstPicHeight = gOutChnAttr[nChn].nHeight;
        stPipelineAttr.tFilter[nChn + 1][1].nDstPicStride = ALIGN_UP_128(stPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth);
        stPipelineAttr.tFilter[nChn + 1][1].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        stPipelineAttr.tFilter[nChn + 1][1].eEngine = AX_IVPS_ENGINE_TDP;
        stPipelineAttr.tFilter[nChn + 1][1].bInplace = AX_TRUE;

        // stPipelineAttr.nOutFifoDepth[nChn] = 1;
    }

    stPipelineAttr.tFilter[ALGO_CHN + 1][0].bEngage = AX_TRUE;
    if (eRotAngle == AX_IVPS_ROTATION_90 || eRotAngle == AX_IVPS_ROTATION_270) {
        stPipelineAttr.tFilter[ALGO_CHN + 1][0].nDstPicWidth = INFER_HEIGHT;
        stPipelineAttr.tFilter[ALGO_CHN + 1][0].nDstPicHeight = INFER_WIDTH;
    } else {
        stPipelineAttr.tFilter[ALGO_CHN + 1][0].nDstPicWidth = INFER_WIDTH;
        stPipelineAttr.tFilter[ALGO_CHN + 1][0].nDstPicHeight = INFER_HEIGHT;
    }
    stPipelineAttr.tFilter[ALGO_CHN + 1][0].nDstPicStride = ALIGN_UP(INFER_WIDTH, 128);
    stPipelineAttr.tFilter[ALGO_CHN + 1][0].eDstPicFormat = INFER_FORMAT;
    stPipelineAttr.tFilter[ALGO_CHN + 1][0].eEngine = AX_IVPS_ENGINE_TDP;
    stPipelineAttr.tFilter[ALGO_CHN + 1][0].tTdpCfg.eRotation = AX_IVPS_ROTATION_0;
    stPipelineAttr.tFilter[ALGO_CHN + 1][0].tAspectRatio.eMode = AX_IVPS_ASPECT_RATIO_AUTO;
    stPipelineAttr.tFilter[ALGO_CHN + 1][0].tAspectRatio.eAligns[0] = AX_IVPS_ASPECT_RATIO_HORIZONTAL_CENTER;
    stPipelineAttr.tFilter[ALGO_CHN + 1][0].tAspectRatio.eAligns[1] = AX_IVPS_ASPECT_RATIO_VERTICAL_CENTER;

    stPipelineAttr.nOutFifoDepth[ALGO_CHN] = 1;


    s32Ret = AX_IVPS_SetPipelineAttr(nGrpId, &stPipelineAttr);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_SetPipelineAttr failed,nGrp %d,s32Ret:0x%x", nGrpId, s32Ret);
        return s32Ret;
    }
    for (nChn = 0; nChn < stPipelineAttr.nOutChnNum + 1; nChn++) {
        s32Ret = AX_IVPS_EnableChn(nGrpId, nChn);
        if (AX_SUCCESS != s32Ret) {
            ALOGE("AX_IVPS_EnableChn failed,nGrp %d,nChn %d,s32Ret:0x%x", nGrpId, nChn, s32Ret);
            return s32Ret;
        }
    }
    s32Ret = AX_IVPS_StartGrp(nGrpId);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_StartGrp failed,nGrp %d,s32Ret:0x%x", nGrpId, s32Ret);
        return s32Ret;
    }

    return 0;
}

static AX_S32 SampleIvpsDeInit(AX_S32 nGrpId, AX_S32 nChnNum)
{
    AX_S32 s32Ret = 0, nChn = 0;

    s32Ret = AX_IVPS_StopGrp(nGrpId);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_StopGrp failed,nGrp %d,s32Ret:0x%x", nGrpId, s32Ret);
        return s32Ret;
    }

    for (nChn = 0; nChn < nChnNum + 1; nChn++) {
        s32Ret = AX_IVPS_DisableChn(nGrpId, nChn);
        if (AX_SUCCESS != s32Ret) {
            ALOGE("AX_IVPS_DisableChn failed,nGrp %d,nChn %d,s32Ret:0x%x", nGrpId, nChn, s32Ret);
            return s32Ret;
        }
    }

    s32Ret = AX_IVPS_DestoryGrp(nGrpId);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_DestoryGrp failed,nGrp %d,s32Ret:0x%x", nGrpId, s32Ret);
        return s32Ret;
    }

    s32Ret = AX_IVPS_Deinit();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_Deinit failed,s32Ret:0x%x", s32Ret);
        return s32Ret;
    }

    return 0;
}

static AX_S32 SAMPLE_SYS_LinkInit(AX_S32 nGrpId, AX_U8 nChnNum)
{
    AX_S32 i = 0;

    /*
    VIN --> IVPS --> VENC
    (ModId   GrpId   ChnId) | (ModId   GrpId   ChnId)
    --------------------------------------------------
    (VIN        0       0) -> (IVPS     0       0)
    (IVPS       0       0) -> (VENC     0       0)
    (IVPS       0       1) -> (VENC     0       1)
    (IVPS       0       2) -> (VENC     0       2)
    */

    AX_MOD_INFO_T srcMod, dstMod;
    srcMod.enModId = AX_ID_VIN;
    srcMod.s32GrpId = 0;
    srcMod.s32ChnId = 0;

    dstMod.enModId = AX_ID_IVPS;
    dstMod.s32GrpId = nGrpId;
    dstMod.s32ChnId = 0;
    AX_SYS_Link(&srcMod, &dstMod);

    for (i = 0; i < 3; i++) {
        srcMod.enModId = AX_ID_IVPS;
        srcMod.s32GrpId = nGrpId;
        srcMod.s32ChnId = i;

        dstMod.enModId = AX_ID_VENC;
        dstMod.s32GrpId = 0;
        dstMod.s32ChnId = i;
        AX_SYS_Link(&srcMod, &dstMod);
    }

    return 0;
}

static AX_S32 SampleLinkDeInit(AX_S32 nGrpId, AX_U8 nChnNum)
{
    AX_S32 i = 0;

    AX_MOD_INFO_T srcMod, dstMod;
    srcMod.enModId = AX_ID_VIN;
    srcMod.s32GrpId = 0;
    srcMod.s32ChnId = 0;
    dstMod.enModId = AX_ID_IVPS;
    dstMod.s32GrpId = nGrpId;
    dstMod.s32ChnId = 0;
    AX_SYS_UnLink(&srcMod, &dstMod);

    for (i = 0; i < 3; i++) {
        srcMod.enModId = AX_ID_IVPS;
        srcMod.s32GrpId = nGrpId;
        srcMod.s32ChnId = i;

        dstMod.enModId = AX_ID_VENC;
        dstMod.s32GrpId = 0;
        dstMod.s32ChnId = i;
        AX_SYS_UnLink(&srcMod, &dstMod);
    }

    return 0;
}

static AX_S32 SampleRtspInit(AX_S32 nChnNum)
{
    if (gRtspParam.bEnable) {
        AX_S32 VencChn = 0;
        AX_RTSP_ATTR_T stAttr[MAX_RTSP_MAX_CHANNEL_NUM];

        memset(&stAttr[0], 0x00, sizeof(stAttr));

        for (VencChn = 0; VencChn < nChnNum; VencChn++) {
            switch (VencChn)
            {
            case 0:
                stAttr[0].nChannel = VencChn;
                stAttr[0].stVideoAttr.bEnable = AX_TRUE;
                stAttr[0].stVideoAttr.ePt = PT_H264;
                break;
            case 1:
                stAttr[1].nChannel = VencChn;
                stAttr[1].stVideoAttr.bEnable = AX_TRUE;
                stAttr[1].stVideoAttr.ePt = PT_H264;
                break;
            case 2:
                stAttr[2].nChannel = VencChn;
                stAttr[2].stVideoAttr.bEnable = AX_TRUE;
                stAttr[2].stVideoAttr.ePt = PT_H264;
                break;
            default:
                break;
            }
        }

        AX_Rtsp_Init(&gRtspParam.pRtspHandle, &stAttr[0], nChnNum, 0);
        AX_Rtsp_Start(gRtspParam.pRtspHandle);
        ALOGI2("RTSP pRtspHandle:%p nChnNum:%d", gRtspParam.pRtspHandle, nChnNum);
    }

    return 0;
}

static AX_S32 SampleRtspDeInit(AX_VOID)
{
    if (gRtspParam.pRtspHandle) {
        AX_Rtsp_Stop(gRtspParam.pRtspHandle);
        AX_Rtsp_Deinit(gRtspParam.pRtspHandle);
        gRtspParam.pRtspHandle = NULL;
    }

    return 0;
}

/*
 *                  |--> VENC0 --> RTSP0 (2688x1520)
 *                  |
 *   VIN --> IVPS --|--> VENC1 --> RTSP1 (1920x1080)
 *                  |
 *                  |--> VENC2 --> RTSP2 (720x576)
 */
static AX_S32 SAMPLE_VIN_IVPS_ENGINE_VENC_RTSP(SAMPLE_VIN_PARAM_T *pVinParam)
{
    AX_S32 s32Ret = 0, i = 0, j = 0;
    COMMON_SYS_ARGS_T tCommonArgs = {0};
    COMMON_SYS_ARGS_T tPrivArgs = {0};

    /* Step1: cam config & pool Config */
    __sample_case_config(pVinParam, &tCommonArgs, &tPrivArgs);

    /* Step2: SYS Init */
    s32Ret = COMMON_SYS_Init(&tCommonArgs);
    if (s32Ret) {
        ALOGE("COMMON_SYS_Init fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL;
    }

    s32Ret = AX_SYS_SetVINIVPSMode(0, pVinParam->nGrpId, pVinParam->eMode);
    if (s32Ret) {
        ALOGE("AX_SYS_SetVINIVPSMode failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL1;
    }

    /* Step3: link init */
    s32Ret = SAMPLE_SYS_LinkInit(pVinParam->nGrpId, pVinParam->nOutChnNum);
    if (s32Ret) {
        ALOGE("SAMPLE_SYS_LinkInit failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL1;
    }

    /* Step4: NPU Init */
    s32Ret = COMMON_NPU_Init();
    if (s32Ret) {
        ALOGE("COMMON_NPU_Init fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL2;
    }

    /* Step5: IVPS init */
    s32Ret = SAMPLE_IVPS_Init(pVinParam->nGrpId, pVinParam->nOutChnNum, pVinParam->eRotAngle);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("SAMPLE_IVPS_Init failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL4;
    }

    /* Step6: VENC init */
    s32Ret = SAMPLE_VENC_Init(pVinParam->nOutChnNum, pVinParam->eRotAngle);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("SAMPLE_VENC_Init failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL5;
    }

    /* Step7: Cam Init */
    s32Ret = COMMON_CAM_Init();
    if (s32Ret) {
        ALOGE("COMMON_CAM_Init fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL2;
    }

    s32Ret = COMMON_CAM_PrivPoolInit(&tPrivArgs);
    if (s32Ret) {
        ALOGE("COMMON_CAM_PrivPoolInit fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL3;
    }

    /* Step8: Cam Open */
    s32Ret = COMMON_CAM_Open(&gCams[0], tCommonArgs.nCamCnt);
    if (s32Ret) {
        ALOGE("COMMON_CAM_Open fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL3;
    }

    if(pVinParam->eMode == AX_GDC_ONLINE_VPP){
        s32Ret = AX_ISP_IQ_SetLdcParam(0, &ldc_param);
        if (s32Ret) {
            ALOGE("AX_ISP_IQ_SetLdcParam fail, ret:0x%x", s32Ret);
            goto EXIT_FAIL3;
        }
        s32Ret = AX_VIN_SetChnRotation(0, 0, pVinParam->eRotAngle);
        if (s32Ret) {
            ALOGE("AX_VIN_SetChnRotation fail, ret:0x%x", s32Ret);
            goto EXIT_FAIL3;
        }
    }

    /*
    * Step9. NT Init (tuning socket server. optional)
    * Stream default port 6000, Ctrl default port 8082
    */
    s32Ret = COMMON_NT_Init(6000, 8082);
    if (s32Ret) {
        ALOGE("COMMON_NT_Init fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL6;
    }

    /* update pipe attribute */
    for (i = 0; i < tCommonArgs.nCamCnt; i++) {
        for (j = 0; j < gCams[i].tDevBindPipe.nNum; j++) {
            COMMON_NT_UpdateSource(gCams[i].tDevBindPipe.nPipeId[j]);
        }
    }

    /* step 10. RTSP init and start */
    s32Ret = SampleRtspInit(pVinParam->nOutChnNum);
    if (s32Ret) {
        ALOGE("SampleRtspInit fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL7;
    }

    /* Step7: ENGINE Init & Load */
    s32Ret = SAMPLE_ENGINE_Load(SAMPLE_ENGINE_MODEL_FILE);
    if (s32Ret != 0)
    {
        printf("SAMPLE_ENGINE_Load failed! ret=0x%x\n", s32Ret);
        goto EXIT_FAIL7;
    }

    /* step 11. region start */
    // SAMPLE_IVPS_RegionStart(pVinParam->nGrpId, pVinParam->nOutChnNum);
    // SAMPLE_IVPS_RegionUpdateStart(pVinParam->nOutChnNum);

    if (pVinParam->pFrameInfo) {
        /* Step11: Send a specified image into IVPS */
        SAMPLE_IVPS_SendFrame(pVinParam->nGrpId, pVinParam->pFrameInfo);
    }

    /* Step13: Get frame and inference */
    s32Ret = SAMPLE_IVPS_GetFrame_and_Inference(pVinParam->nGrpId);
    if (s32Ret)
    {
        ALOGE("SAMPLE_IVPS_GetFrame_and_Inference fail, ret:0x%x", s32Ret);
        goto EXIT_FAIL7;
    }
    printf("Inference thread start\n");

    while (!ThreadLoopStateGet()) {
        sleep(1);
    }

    // SAMPLE_IVPS_RegionUpdateStop();
    // SAMPLE_IVPS_RegionStop();
    SampleRtspDeInit();

EXIT_FAIL7:
    COMMON_NT_DeInit();
EXIT_FAIL6:
    SampleVencDeInit(pVinParam->nOutChnNum);
EXIT_FAIL5:
    SampleIvpsDeInit(pVinParam->nGrpId, pVinParam->nOutChnNum);
    SAMPLE_ENGINE_Release();
EXIT_FAIL4:
    COMMON_CAM_Close(&gCams[0], tCommonArgs.nCamCnt);
EXIT_FAIL3:
    COMMON_CAM_Deinit();
EXIT_FAIL2:
    SampleLinkDeInit(pVinParam->nGrpId, pVinParam->nOutChnNum);
EXIT_FAIL1:
    COMMON_SYS_DeInit();
EXIT_FAIL:
    return s32Ret;
}

AX_VOID PrintHelp()
{
    printf("CMD:\n");
    printf("\t-n: frames to calc delta pts.\n");
    printf("\t-c: VIN Sensor Type\n");
    printf("\t\t0: Single DummySensor\n");
    printf("\t\t1: Single OS04A10\n");
    printf("\t\t2: Single SC450AI\n");

    printf("\n\t-m(optional): Work Mode\n");
    printf("\t\t0: LoadRaw Mode\n");
    printf("\t\t1: Sensor Mode\n");
    printf("\t\t2: TPG Mode\n");

    printf("\n\t-e(optional): SDR/HDR Mode\n");
    printf("\t\t1: SDR\n");
    printf("\t\t2: HDR 2DOL\n");

    printf("\n\t-a(optional): Enable AIISP\n");
    printf("\t\t0: Disable(default)\n");
    printf("\t\t1: Enable\n");

    printf("\n\t-d(optional): Continue Frame Dump\n");
    printf("\t\tn: N Frame Blk\n");

    printf("\n\t-r(optional): Enable RTSP\n");
    printf("\t\t0: Disable(default)\n");
    printf("\t\t1: Enable\n");

    printf("\n\t-z(optional): VIN->IVPS link Mode\n");
    printf("\t\t0: VPP offline\n");
    printf("\t\t1: GDC->VPP online\n");
    printf("\t\t2: ITP->VPP online\n");

    printf("\n\t-t(optional): rotation angle\n");
    printf("\t\t0: 0 degree\n");
    printf("\t\t1: 90 degree\n");
    printf("\t\t2: 180 degree\n");
    printf("\t\t3: 270 degree\n");

    printf("\nOS04A10:\n");
    printf("\nExample:\n\tsample_vin_ivps_engine_ venc_rtsp -c 1 -m 1 -e 1 -r 1\n");

    printf("\nSC450AI:\n");
    printf("\nExample:\n\tsample_vin_ivps_engine_ venc_rtsp -c 2 -m 1 -e 1 -r 1\n");
}

static AX_VOID SigInt(AX_S32 signo)
{
    ALOGI2("SigInt Catch signal %d", signo);
    ThreadLoopStateSet(AX_TRUE);
}

static AX_VOID SigStop(AX_S32 signo)
{
    ALOGI2("SigStop Catch signal %d", signo);
    ThreadLoopStateSet(AX_TRUE);
}

int main(int argc, char *argv[])
{
    ALOGI2("VIN Sample. Build at %s %s", __DATE__, __TIME__);

    int c;
    int isExit = 0;

    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, SigInt);
    signal(SIGTSTP, SigStop);

    if (argc < 3) {
        PrintHelp();
        exit(0);
    }

    while ((c = getopt(argc, argv, "c:m:e:l:d:a:r:h:v:z:t:n:")) != -1) {
        isExit = 0;
        switch (c) {
        case 'c':
            gtVinParam.eSysCase = (SAMPLE_VIN_CASE_E)atoi(optarg);
            break;
        case 'm':
            gtVinParam.eSysMode = (COMMON_VIN_MODE_E)atoi(optarg);
            break;
        case 'e':
            gtVinParam.eHdrMode = (AX_SNS_HDR_MODE_E)atoi(optarg);
            break;
        case 'd':
            gtVinParam.nDumpFrameNum = (AX_S32)atoi(optarg);
            break;
        case 'a':
            gtVinParam.bAiispEnable = (AX_BOOL)atoi(optarg);
            break;
        case 'r':
            gRtspParam.bEnable = (AX_BOOL)atoi(optarg);
            break;
        case 'v':
            gtVinParam.pFrameInfo = optarg;
            break;
        case 'z':
            gtVinParam.eMode = (AX_S32)atoi(optarg);
            break;
        case 't':
            gtVinParam.eRotAngle = (AX_S32)atoi(optarg);
            break;
        case 'h':
            isExit = 1;
            break;
        case 'n':
            gtVinParam.statDeltaPtsFrmNum = atoi(optarg);
            if (gtVinParam.statDeltaPtsFrmNum < SAMPLE_MIN_DELTAPTS_NUM) {
                ALOGE("-n not less than %d!\n", SAMPLE_MIN_DELTAPTS_NUM);
                isExit = AX_TRUE;
            }
            break;
        default:
            isExit = 1;
            break;
        }
    }
    gtVinParam.nOutChnNum = 3;
    gtVinParam.nGrpId = 1;

    if (isExit) {
        PrintHelp();
        exit(0);
    }

    if (gtVinParam.eSysCase >= SAMPLE_VIN_BUTT || gtVinParam.eSysCase <= SAMPLE_VIN_NONE) {
        ALOGE("error sys case : %d", gtVinParam.eSysCase);
        exit(0);
    }

    if (gtVinParam.eSysMode >= COMMON_VIN_BUTT || gtVinParam.eSysMode <= COMMON_VIN_NONE) {
        ALOGE("error sys mode : %d", gtVinParam.eSysMode);
        exit(0);
    }

    SAMPLE_VIN_IVPS_ENGINE_VENC_RTSP(&gtVinParam);

    ALOGI2("Sample Completed");

    exit(0);
}
