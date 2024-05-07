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

SAMPLE_IVPS_MAIN_T gSampleIvpsMain;

AX_S32 main(AX_S32 argc, char *argv[])
{
    AX_S32 ret = IVPS_SUCC;
    IVPS_ARG_T *pIvpsArg = &gSampleIvpsMain.tIvpsArg;
    SAMPLE_IVPS_GRP_T *pGrp = &gSampleIvpsGrp;
    SAMPLE_IVPS_GRP_T *pGrpExt = &gSampleIvpsGrpExt;
    IVPS_BLK_T arrBlkInfo[16];
    char *pFrameFile;
    AX_U32 BlkSize;

    printf("IVPS Sample. Build at %s %s\n", __DATE__, __TIME__);

    /* Parse the input parameter */
    IVPS_ArgsParser(argc, argv, pIvpsArg);

    /* SYS global init */
    CHECK_RESULT(AX_SYS_Init());

    /* Create common pool */
    if (pIvpsArg->bFewPool) {
        arrBlkInfo[0].nSize = CalcImgSize(3840, 3840, 2160, AX_FORMAT_RGBA8888, 16);
        arrBlkInfo[0].nCnt = 5;
        ret = IVPS_CommonPoolCreate(&arrBlkInfo[0], 1);
        if (ret)
        {
            ALOGE("AX_IVPS_Init failed, ret=0x%x.", ret);
            goto error0;
        }
    } else {
        arrBlkInfo[0].nSize = CalcImgSize(1920, 1920, 1080, AX_FORMAT_RGBA8888, 16);
        arrBlkInfo[0].nCnt = 6;
        arrBlkInfo[1].nSize = CalcImgSize(3840, 3840, 2160, AX_FORMAT_RGBA8888, 16);
        arrBlkInfo[1].nCnt = 2;
        ret = IVPS_CommonPoolCreate(&arrBlkInfo[0], 2);
        if (ret)
        {
            ALOGE("AX_IVPS_Init failed, ret=0x%x.", ret);
            goto error0;
        }
    }

    printf("pIvpsArg->ePoolSrc:%d", pIvpsArg->ePoolSrc);
    pGrp->ePoolSrc = pIvpsArg->ePoolSrc;
    if (AX_POOL_SOURCE_USER == pIvpsArg->ePoolSrc) {
        /* Create user pool, get pool id */
        BlkSize = CalcImgSize(1920, 1920, 1080, AX_FORMAT_YUV420_SEMIPLANAR, 16);
        pGrp->user_pool_id = IVPS_UserPoolCreate(BlkSize, 10);
    }

    /* IVPS initialization */
    ret = AX_IVPS_Init();
    if (ret)
    {
        ALOGE("AX_IVPS_Init failed, ret=0x%x.", ret);
        goto error1;
    }

    /* Source image buffer and info get */
    pFrameFile = FrameInfoGet(pIvpsArg->pFrameInfo, &pGrp->tFrameInput);
    if (access(pFrameFile, 0))
    {
        ALOGW("FILE:%s not accessed, autogen test pattern!", pFrameFile);
        ret = PatternAutoGen(-1, pGrp->tFrameInput.enImgFormat, pGrp->tFrameInput.u32PicStride[0],
                             pGrp->tFrameInput.s16CropWidth - pGrp->tFrameInput.s16CropX,
                             pGrp->tFrameInput.s16CropHeight - pGrp->tFrameInput.s16CropY,
                             &pGrp->tFrameInput.u32BlkId[0], &pGrp->tFrameInput.u64PhyAddr[0],
                             (AX_VOID **)&pGrp->tFrameInput.u64VirAddr[0]);
        if (0 != ret) {
            ALOGE("TestPatternAutoGen fail, ret=0x%x", ret);
            return ret;
        }
    } else {
        FrameBufGet(0, &pGrp->tFrameInput, pFrameFile);
    }

    printf("INPUT nW:%d nH:%d File:%s\n", pGrp->tFrameInput.u32Width, pGrp->tFrameInput.u32Height, pFrameFile);

    pGrp->pFileName = pFrameFile;
    gSampleIvpsMain.nIvpsStreamNum = pIvpsArg->nStreamNum;
    gSampleIvpsMain.nIvpsRepeatNum = pIvpsArg->nRepeatCount;
    pGrpExt->tFrameInput = pGrp->tFrameInput;

    /* save path of output frame */
    if (pIvpsArg->pSavePath)
        pGrp->pFilePath = pIvpsArg->pSavePath;
    else
        pGrp->pFilePath = NULL;

    pGrpExt->pFilePath = pGrp->pFilePath;

    ALOGI("nRepeatCount:%d nRegionNum:%d", pIvpsArg->nRepeatCount, pIvpsArg->nRegionNum);

    /* IVPS sync api */
    SAMPLE_IVPS_SyncApi(pIvpsArg, pGrp, &gSampleIvpsSyncApi);

    /* IVPS dewarp api */
    SAMPLE_IVPS_Dewarp(pIvpsArg, pGrp);

    /* IVPS pipeline start */
    ret = IVPS_StartGrp(pIvpsArg, pGrp);
    if (ret)
    {
        ALOGE("IVPS_StartGrp failed, ret=0x%x.", ret);
        goto error2;
    }

    /* IVPS region start */
    if (pIvpsArg->nRegionNum > 0)
    {
        /* Start region with parameter */
        if (0 != IVPS_StartRegion(pIvpsArg->nRegionNum))
        {
            ThreadLoopStateSet(AX_TRUE);
            ALOGE("IVPS_StartRegion failed");
            goto error3;
        }
        IVPS_RegionUpdateThreadStart(pIvpsArg->nRegionNum, pGrp, pIvpsArg->bRegionStop);
    }

    printf("bCropInfo:%d nIvpsGrp:%d\n", pIvpsArg->bCropInfo, pGrp->nIvpsGrp);
    /* IVPS crop function */
    if (pIvpsArg->bCropInfo)
    {
        AX_IVPS_CROP_INFO_T tCropInfo;
        AX_IVPS_SetGrpCrop(pGrp->nIvpsGrp, &pIvpsArg->tCropInfo);
        AX_IVPS_GetGrpCrop(pGrp->nIvpsGrp, &tCropInfo);
        printf("Get Crop nX:%d nY:%d nW:%d nH:%d", tCropInfo.tCropRect.nX, tCropInfo.tCropRect.nY, tCropInfo.tCropRect.nW, tCropInfo.tCropRect.nH);
    }

    switch (pIvpsArg->nLinkMode)
    {
    case IVPS_LINK_IVPS:
        SAMPLE_IVPS_LinkIvps(pIvpsArg, pGrp->nIvpsGrp, 0, pGrpExt);
        IVPS_GrpThreadStart(pGrp, pGrpExt);
        /* Dynamic change channel attributes */
        if (pIvpsArg->pChangeIni)
        {
            IVPS_AttrChangeThreadStart(pIvpsArg, pGrp, 0);
            IVPS_AttrChangeThreadStart(pIvpsArg, pGrpExt, 1);
        }
        break;
    default:
        IVPS_GrpThreadStart(pGrp, pGrp);
        /* Dynamic change channel attributes */
        if (pIvpsArg->pChangeIni)
        {
            IVPS_AttrChangeThreadStart(pIvpsArg, pGrp, 0);
        }
        break;
    }

    if (pIvpsArg->nRegionNum > 0 && pIvpsArg->bRegionStop)
    {
        IVPS_StopRegionById(0);
    }

    while (!ThreadLoopStateGet() && (gSampleIvpsMain.nIvpsRepeatNum || pIvpsArg->nStreamNum))
    {
        sleep(1);
    }
    IVPS_GrpThreadStop();

    /* Stop IVPS region */
    if (pIvpsArg->nRegionNum > 0)
    {
        IVPS_RegionUpdateThreadStop(pIvpsArg->bRegionStop);
        IVPS_StopRegion();
    }

    if (pIvpsArg->pChangeIni)
    {
        IVPS_AttrChangeThreadStop();
    }

    /* Stop IVPS group-ext */
    switch (pIvpsArg->nLinkMode)
    {
    case IVPS_LINK_IVPS:
        IVPS_StopGrp(pGrpExt);
        break;
    default:
        break;
    }

error3:
    /* Stop IVPS group */
    IVPS_StopGrp(pGrp);

    /* Release all block IDs */
    if (pGrp->tFrameInput.u32BlkId[0])
    {
        AX_POOL_ReleaseBlock(pGrp->tFrameInput.u32BlkId[0]);
        pGrp->tFrameInput.u32BlkId[0] = 0;
    }
    if (gSampleIvpsSyncApi.nOsdBlkId)
    {
        AX_POOL_ReleaseBlock(gSampleIvpsSyncApi.nOsdBlkId);
        gSampleIvpsSyncApi.nOsdBlkId = 0;
    }
error2:
    /* IVPS release */
    AX_IVPS_Deinit();

error1:
    /* POOL release */
    if (AX_POOL_SOURCE_USER == pIvpsArg->ePoolSrc) {
        AX_POOL_DestroyPool(pGrp->user_pool_id);
    }
    AX_POOL_Exit();

error0:
    /* SYS release */
    AX_SYS_Deinit();

    printf("\nsample test run success\n");
    return 0;
}
