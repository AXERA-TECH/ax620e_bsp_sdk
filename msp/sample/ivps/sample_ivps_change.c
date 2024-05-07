/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_ivps_main.h"

SAMPLE_IVPS_CHANGE_T gSampleChange[] = {
    {
        .nRepeatNum = -1,
        .nFilterIdx = 0x10,
        .tMaxValue = {
            .nDstPicStride = 3840,
            .nDstPicWidth = 2160,
            .nDstPicHeight = 3840,
        },
        .tMinValue = {
            .nDstPicStride = 704,
            .nDstPicWidth = 704,
            .nDstPicHeight = 576,
        },
        .nWidthStep = 8,
        .nHeightStep = 8,
        .nCropX0Step = 0,
        .nCropY0Step = 0,
        .nCropWStep = 0,
        .nCropHStep = 0,
    },
    {
        .nRepeatNum = -1,
        .nFilterIdx = 0x10,
        .tMaxValue = {
            .nDstPicStride = 3840,
            .nDstPicWidth = 2160,
            .nDstPicHeight = 3840,
        },
        .tMinValue = {
            .nDstPicStride = 708,
            .nDstPicWidth = 708,
            .nDstPicHeight = 580,
        },
        .nWidthStep = 8,
        .nHeightStep = 8,
        .nCropX0Step = 0,
        .nCropY0Step = 0,
        .nCropWStep = 0,
        .nCropHStep = 0,
    }};

static AX_S32 IVPS_FilterAttrParaUpdate(int pipe_idx, int filter_idx, SAMPLE_IVPS_GRP_T *pGrp, SAMPLE_IVPS_CHANGE_T *pChange)
{
    pGrp->tPipelineAttr.tFilter[pipe_idx][filter_idx].nDstPicStride = pChange->tCurValue.nDstPicStride;
    pGrp->tPipelineAttr.tFilter[pipe_idx][filter_idx].nDstPicWidth = pChange->tCurValue.nDstPicWidth;
    pGrp->tPipelineAttr.tFilter[pipe_idx][filter_idx].nDstPicHeight = pChange->tCurValue.nDstPicHeight;
    printf("GRP[%d]PIPE[%d]FILTER[%d] Stride:%d W:%d H:%d\n", pGrp->nIvpsGrp, pipe_idx, filter_idx,
           pGrp->tPipelineAttr.tFilter[pipe_idx][filter_idx].nDstPicStride,
           pGrp->tPipelineAttr.tFilter[pipe_idx][filter_idx].nDstPicWidth,
           pGrp->tPipelineAttr.tFilter[pipe_idx][filter_idx].nDstPicHeight);

    AX_IVPS_SetPipelineAttr(pGrp->nIvpsGrp, &pGrp->tPipelineAttr);

    pChange->tCurValue.nDstPicWidth = pChange->tCurValue.nDstPicWidth + pChange->nWidthStep;
    pChange->tCurValue.nDstPicHeight = pChange->tCurValue.nDstPicHeight + pChange->nHeightStep;
    if (pChange->tCurValue.nDstPicWidth > pChange->tMaxValue.nDstPicWidth)
        pChange->tCurValue.nDstPicWidth = pChange->tMinValue.nDstPicWidth;
    if (pChange->tCurValue.nDstPicHeight > pChange->tMaxValue.nDstPicHeight)
        pChange->tCurValue.nDstPicHeight = pChange->tMinValue.nDstPicHeight;

    pChange->tCurValue.nDstPicStride = ALIGN_UP(pChange->tCurValue.nDstPicWidth, 16);

    return IVPS_SUCC;
}

static AX_S32 IVPS_FilterAttrChange(int pipe_idx, int filter_idx, SAMPLE_IVPS_GRP_T *pGrp, SAMPLE_IVPS_CHANGE_T *pChange)
{
    int ret;

    IVPS_FilterAttrParaUpdate(pipe_idx, filter_idx, pGrp, pChange);

    pGrp->bChnDisabled = AX_TRUE;
    usleep(1000); /* 1ms */
    ALOGI("GRP[%d]CHN[%d] disable\n", pGrp->nIvpsGrp, pipe_idx - 1);
    ret = AX_IVPS_DisableChn(pGrp->nIvpsGrp, pipe_idx - 1);
    if (IVPS_SUCC != ret)
    {
        ALOGE("GRP[%d]CHN[%d] disable failed, ret=0x%x.", pGrp->nIvpsGrp, pipe_idx - 1, ret);
        return ret;
    }
    ALOGI("GRP[%d]CHN[%d] enable\n", pGrp->nIvpsGrp, pipe_idx - 1);
    ret = AX_IVPS_EnableChn(pGrp->nIvpsGrp, pipe_idx - 1);
    if (IVPS_SUCC != ret)
    {
        ALOGE("GRP[%d]CHN[%d] enable failed, ret=0x%x.", pGrp->nIvpsGrp, pipe_idx - 1, ret);
        return ret;
    }
    pGrp->bChnDisabled = AX_FALSE;
    sleep(1);
    return IVPS_SUCC;
}

/*
 * IVPS_FilterAttrChangeThread()
 * Dynamic switch channel test.
 */
static AX_VOID *IVPS_FilterAttrChangeThread(AX_VOID *pArg)
{
    SAMPLE_IVPS_GRP_T *pGrp = (SAMPLE_IVPS_GRP_T *)pArg;

    int pipe_idx = (gSampleChange[pGrp->nChangeIdx].nFilterIdx & 0xf0) >> 4;
    int filter_idx = (gSampleChange[pGrp->nChangeIdx].nFilterIdx & 0xf);

    gSampleChange[pGrp->nChangeIdx].tCurValue.nDstPicWidth = gSampleChange[pGrp->nChangeIdx].tMinValue.nDstPicWidth;
    gSampleChange[pGrp->nChangeIdx].tCurValue.nDstPicHeight = gSampleChange[pGrp->nChangeIdx].tMinValue.nDstPicHeight;
    gSampleChange[pGrp->nChangeIdx].tCurValue.nDstPicStride = ALIGN_UP(gSampleChange[pGrp->nChangeIdx].tCurValue.nDstPicWidth, 16);

    while (!ThreadLoopStateGet() && gSampleIvpsMain.nIvpsRepeatNum)
    {
        IVPS_FilterAttrChange(pipe_idx, filter_idx, pGrp, &gSampleChange[pGrp->nChangeIdx]);
    }

    return (AX_VOID *)0;
}

/*
 * IVPS_FilterAttrThreadStart()
 * This function will start a thread and change the IVPS channel attributes frequently.
 */
AX_S32 IVPS_AttrChangeThreadStart(const IVPS_ARG_T *ptArg, SAMPLE_IVPS_GRP_T *pGrp, AX_S32 nChangeIdx)
{
    pGrp->nChangeIdx = nChangeIdx;
    if (pGrp->nChangeIdx >= sizeof(gSampleChange) / sizeof(gSampleChange[0]))
    {
        ALOGE("GRP[%d] nChangeIdxp[%d] is illegal!", pGrp->nIvpsGrp, pGrp->nChangeIdx);
        return -1;
    }

    if (ptArg->pChangeIni)
        IVPS_ChangeIniParser(ptArg->pChangeIni, &gSampleChange[pGrp->nChangeIdx]);

    if (0 != pthread_create(&gSampleIvpsMain.change_tid, NULL, IVPS_FilterAttrChangeThread, (AX_VOID *)pGrp))
    {
        return -1;
    }
    return 0;
}

AX_S32 IVPS_AttrChangeThreadStop(AX_VOID)
{
    pthread_join(gSampleIvpsMain.change_tid, NULL);
    return 0;
}