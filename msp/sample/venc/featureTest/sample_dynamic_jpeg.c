/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_dynamic_jpeg.h"

#include "sample_case.h"
#include "sample_roicfg.h"

static AX_BOOL gLoopExit = AX_FALSE;
static SAMPLE_VENC_SENDFRAME_PARA_T gstFrmParam[AX_MAX_VENC_CHN_NUM];
static SAMPLE_VENC_GETSTREAM_PARA_T gstStrmParam[AX_MAX_VENC_CHN_NUM];

static void SigHandler(AX_S32 signo)
{
    SAMPLE_LOG("catch signal(%d).\n", signo);
    gLoopExit = AX_TRUE;
}

AX_S32 UTestDynamicJpeg(SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret;
    AX_U32 chnNum;
    AX_S32 chnIdx;
    chnNum = (pCml->defaultUt == VENC_TEST_ALL_CASE) ? 1 : pCml->chnNum;
    AX_PAYLOAD_TYPE_E enType;
    SAMPLE_VENC_RC_E enRcMode = pCml->rcMode;
    AX_U64 gVencCaseLoopExit = 0;

    signal(SIGINT, SigHandler);

    for (chnIdx = 0; chnIdx < chnNum; chnIdx++) {
        memset(&gstFrmParam[chnIdx], 0, sizeof(SAMPLE_VENC_SENDFRAME_PARA_T));
        memset(&gstStrmParam[chnIdx], 0, sizeof(SAMPLE_VENC_GETSTREAM_PARA_T));

        enType = PT_JPEG;

        if (PT_BUTT == enType) {
            SAMPLE_LOG_ERR("chn-%d: Invalid codec type!\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        s32Ret = COMMON_VENC_Start(chnIdx, enType, enRcMode, pCml);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_Start failed.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        SampleSendFrameInit(chnIdx, enType, &gstFrmParam[chnIdx], pCml);

        s32Ret = SAMPLE_VENC_StartSendFrame(&gstFrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_StartSendFrame err.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        sleep(1);

        SampleGetStreamInit(chnIdx, enType, &gstStrmParam[chnIdx], pCml);

        s32Ret = SAMPLE_VENC_StartGetStream(&gstStrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_StartGetStream err.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        COMMON_VENC_AdjustLoopExit(&gVencCaseLoopExit, chnIdx);
        sleep(1);
    }

    while ((!gLoopExit) && (gVencCaseLoopExit != pCml->vencLoopExit))
        sleep(1);

FREE:

    for (chnIdx = 0; chnIdx < chnNum; chnIdx++) {
        SAMPLE_VENC_StopSendFrame(&gstFrmParam[chnIdx]);
        SAMPLE_VENC_StopGetStream(&gstStrmParam[chnIdx]);
        COMMON_VENC_Stop(chnIdx);
    }

    pCml->vencLoopExit = 0;

    return s32Ret;
}

static void SampleJpegRoiInit(SAMPLE_ROI_CFG_T *pstArg, SAMPLE_VENC_SENDFRAME_PARA_T *pCml)
{
    pstArg->qFactor = pCml->qFactor;
    pstArg->roiEnable = pCml->roiEnable;
    pstArg->roimapFile = pCml->jencRoiMap;
    pstArg->qRoiFactor = pCml->qRoiFactor;
}

static void SampleJpegParamDebug(AX_S32 VencChn, AX_VENC_JPEG_PARAM_T *pStJpegParam)
{
    if (NULL == pStJpegParam) {
        SAMPLE_LOG_ERR("NULL pointer\n");
        return;
    }

    SAMPLE_LOG_DEBUG("VencChn %d u32Qfactor %d\n", VencChn, pStJpegParam->u32Qfactor);
    SAMPLE_LOG_DEBUG("VencChn %d bEnableRoi %d bSaveNonRoiQt %d u32RoiQfactor %d\n", VencChn, pStJpegParam->bEnableRoi,
                     pStJpegParam->bSaveNonRoiQt, pStJpegParam->u32RoiQfactor);

    return;
}

AX_S32 SampleJpegParam(AX_S32 VencChn, AX_VOID *handle)
{
    AX_S32 s32Ret = AX_SUCCESS;
    AX_VENC_JPEG_PARAM_T stJpegParam;
    SAMPLE_ROI_CFG_T roiCfg;
    SAMPLE_VENC_SENDFRAME_PARA_T *pCml = (SAMPLE_VENC_SENDFRAME_PARA_T *)handle;

    memset(&stJpegParam, 0, sizeof(stJpegParam));
    if (pCml->enType == PT_H264 || pCml->enType == PT_H265)
        return AX_SUCCESS;

    s32Ret = AX_VENC_GetJpegParam(VencChn, &stJpegParam);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("AX_VENC_GetJpegParam:%d failed!\n", VencChn);
        return -1;
    }

    SampleJpegParamDebug(VencChn, &stJpegParam);

    stJpegParam.u32Qfactor = pCml->qFactor;

    memcpy(stJpegParam.u8YQt, QTableLuminance, sizeof(QTableLuminance));
    memcpy(stJpegParam.u8CbCrQt, QTableChrominance, sizeof(QTableChrominance));

    if (pCml->roiEnable) {
        memset(&roiCfg, 0x0, sizeof(SAMPLE_ROI_CFG_T));
        SampleJpegRoiInit(&roiCfg, pCml);
        s32Ret = SampleJpegRoiCfg(&roiCfg, &stJpegParam);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("SampleJpegRoiCfg err.\n");
            return -1;
        }
    }

    s32Ret = AX_VENC_SetJpegParam(VencChn, &stJpegParam);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("AX_VENC_SetJpegParam:%d failed!\n", VencChn);
        return -1;
    }

    SampleJpegParamDebug(VencChn, &stJpegParam);

    return AX_SUCCESS;
}

AX_S32 SampleJpegDynResolution(AX_S32 VencChn, AX_VOID *handle)
{

    AX_POOL_CONFIG_T stPoolConfig;
    SAMPLE_VENC_SENDFRAME_PARA_T *pstArg = NULL;

    pstArg = (SAMPLE_VENC_SENDFRAME_PARA_T *)handle;
    VENC_CHN VeChn = pstArg->VeChn;

    if (!pstArg->bDynRes) {
        SAMPLE_LOG_ERR("chn-%d: Disable dynamic resolution!\n", VeChn);
        return -1;
    }

    if (pstArg->fileInput) {
        fclose(pstArg->fFileIn);
        pstArg->fFileIn = NULL;

        pstArg->fFileIn = fopen(pstArg->newInput, "rb");
        if (NULL == pstArg->fFileIn) {
            SAMPLE_LOG_ERR("chn-%d: Open input file(%s) error!\n", VeChn, pstArg->newInput);
            return -1;
        }
    }

    /* update new resolution params */
    pstArg->frameSize = pstArg->blkSize = pstArg->newPicW * pstArg->newPicH * 2;
    switch (pstArg->eFmt) {
    case AX_FORMAT_YUV420_PLANAR:
        pstArg->strideY = pstArg->newPicW;
        pstArg->strideU = pstArg->strideV = pstArg->newPicW / 2;
        break;
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
        pstArg->strideY = pstArg->newPicW;
        pstArg->strideU = pstArg->newPicW;
        break;
    case AX_FORMAT_YUV422_INTERLEAVED_YUYV:
    case AX_FORMAT_YUV422_INTERLEAVED_UYVY:
        pstArg->strideY = 2 * pstArg->newPicW;
        break;
    default:
        SAMPLE_LOG_ERR("chn-%d: image format(%d) unsupport change stride dynamically!\n", VeChn, pstArg->eFmt);
        return -1;
    }

    pstArg->width = pstArg->newPicW;
    pstArg->height = pstArg->newPicH;

    /* use user pool */
    memset(&stPoolConfig, 0, sizeof(AX_POOL_CONFIG_T));
    stPoolConfig.MetaSize = 8192;
    stPoolConfig.BlkCnt = 2;
    stPoolConfig.BlkSize = pstArg->blkSize;
    stPoolConfig.CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    memset(stPoolConfig.PartitionName, 0, sizeof(stPoolConfig.PartitionName));
    strcpy((AX_CHAR *)stPoolConfig.PartitionName, "anonymous");

    pstArg->poolId = AX_POOL_CreatePool(&stPoolConfig);
    if (AX_INVALID_POOLID == pstArg->poolId) {
        SAMPLE_LOG_ERR("Create pool err.\n");
        goto CLOSE_FD;
    }

    SAMPLE_LOG_DEBUG("chn-%d: new resolution: %u*%u.\n", VencChn, pstArg->newPicW, pstArg->newPicH);

    return 0;

CLOSE_FD:
    if (pstArg->fileInput) {
        fclose(pstArg->fFileIn);
        pstArg->fFileIn = NULL;
    }

    return -1;

    return AX_SUCCESS;
}