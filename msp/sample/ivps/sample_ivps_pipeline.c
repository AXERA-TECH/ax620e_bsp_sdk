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

#define DEFAULT_DELIM "@"
#define EPOLL_MAXUSERS 128

AX_IVPS_TDP_CFG_T gSampleTdpCfg = {
    .bMirror = AX_FALSE,
    .bFlip = AX_FALSE,
    .eRotation = AX_IVPS_ROTATION_0,
    .bRotationOnly = AX_FALSE,
};

AX_IVPS_GDC_CFG_T gSampleGdcCfg = {
    .eRotation = AX_IVPS_ROTATION_0,
    .eDewarpType = AX_IVPS_DEWARP_LDC,
    .tLdcAttr = {
        .nDistortionRatio = 10000,
        .nXRatio = 0,
        .nYRatio = 0,
    }};

SAMPLE_IVPS_GRP_T gSampleIvpsGrp = {
    .eGrpIdx = IVPS_GRP_IDX_0,
    .nIvpsGrp = 1,

    .tGrpAttr = {
        .ePipeline = AX_IVPS_PIPELINE_DEFAULT,
    },
    .tPipelineAttr = {

        .nOutChnNum = 1,
        .nOutFifoDepth = {2, 2, 2, 2, 2},
        .tFilter = {
            {
                /* group filter0 */
                {
                    .bEngage = AX_FALSE,
                    .eEngine = AX_IVPS_ENGINE_TDP,
                    .bCrop = AX_FALSE,
                    .tCropRect = {
                        .nX = 0,
                        .nY = 0,
                        .nW = 0,
                        .nH = 0,
                    },
                    .nDstPicWidth = 3840,
                    .nDstPicHeight = 2160,
                    .nDstPicStride = 3840,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },

            {
                /* channel 0 filter0 */
                {
                    .bEngage = AX_TRUE,
                    .eEngine = AX_IVPS_ENGINE_TDP,
                    .bCrop = AX_FALSE,
                    .tCompressInfo = {
                        .enCompressMode = AX_COMPRESS_MODE_NONE,
                        .u32CompressLevel = 4,
                    },
                    .tCropRect = {
                        .nX = 0,
                        .nY = 0,
                        .nW = 0,
                        .nH = 0,
                    },
                    .nDstPicWidth = 1920,
                    .nDstPicHeight = 1080,
                    .nDstPicStride = 1920,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                    /*.tAspectRatio = {.eMode = IVPS_ASPECT_RATIO_MANUAL, .tRect = {64, 20, 500, 500}},*/
                    .tAspectRatio = {.eMode = AX_IVPS_ASPECT_RATIO_STRETCH, .eAligns = {AX_IVPS_ASPECT_RATIO_HORIZONTAL_RIGHT, AX_IVPS_ASPECT_RATIO_VERTICAL_TOP}},
                },
                /* channel 0 filter1 */
                {
                    .bEngage = AX_FALSE,
                    .eEngine = AX_IVPS_ENGINE_VO,
                    .nDstPicWidth = 1920,
                    .nDstPicHeight = 1080,
                    .nDstPicStride = 1920,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },
            {
                /* channel 1 filter0 */
                {
                    .bEngage = AX_TRUE,
                    .eEngine = AX_IVPS_ENGINE_TDP,
                    .bCrop = AX_FALSE,
                    .tCropRect = {
                        .nX = 0,
                        .nY = 0,
                        .nW = 0,
                        .nH = 0,
                    },
                    .nDstPicWidth = 2688,
                    .nDstPicHeight = 1520,
                    .nDstPicStride = 2688,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },
            {
                /* channel 2 filter0 */
                {
                    .bEngage = AX_TRUE,
                    .eEngine = AX_IVPS_ENGINE_TDP,
                    .bCrop = AX_FALSE,
                    .tCropRect = {
                        .nX = 0,
                        .nY = 0,
                        .nW = 0,
                        .nH = 0,
                    },
                    .nDstPicWidth = 1280,
                    .nDstPicHeight = 768,
                    .nDstPicStride = 1280,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },
            {
                /* channel 3 filter0 */
                {
                    .bEngage = AX_TRUE,
                    .eEngine = 0,
                    .bCrop = AX_FALSE,
                    .tCropRect = {
                        .nX = 0,
                        .nY = 0,
                        .nW = 0,
                        .nH = 0,
                    },
                    .nDstPicWidth = 256,
                    .nDstPicHeight = 256,
                    .nDstPicStride = 256,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },

            {
                /* channel 4 filter0 */
                {
                    .bEngage = AX_TRUE,
                    .eEngine = 0,
                    .bCrop = AX_FALSE,
                    .tCropRect = {
                        .nX = 0,
                        .nY = 0,
                        .nW = 0,
                        .nH = 0,
                    },
                    .nDstPicWidth = 1024,
                    .nDstPicHeight = 1024,
                    .nDstPicStride = 1024,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },
        },
    },
};

SAMPLE_IVPS_GRP_T gSampleIvpsGrpExt = {
    .eGrpIdx = IVPS_GRP_IDX_1,
    .nIvpsGrp = 0,

    .tGrpAttr = {
        .ePipeline = AX_IVPS_PIPELINE_DEFAULT,
    },
    .tPipelineAttr = {
        .nOutChnNum = 1,
        .nOutFifoDepth = {2, 2, 2},
        .tFilter = {
            {
                /* group filter0 */
                {
                    .bEngage = AX_FALSE,
                    .eEngine = AX_IVPS_ENGINE_TDP,
                    .nDstPicWidth = 1024,
                    .nDstPicHeight = 1024,
                    .nDstPicStride = 1024,
                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },
            {
                /* channel 0 filter0 */
                {
                    .bEngage = AX_TRUE,
                    .eEngine = AX_IVPS_ENGINE_TDP,
                    .nDstPicWidth = 1024,
                    .nDstPicHeight = 1024,
                    .nDstPicStride = 1024,

                    .eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR,
                },
            },
        },
    },
};

static SAMPLE_IVPS_USERMAP_CFG_T gSampleUserMapCfg = {
    .pMeshFile = "/opt/data/ivps/mesh_8M_LDC.hex",
    .nMeshNumH = 33,
    .nMeshNumV = 33,
    .nMeshWidth = 128,
    .nMeshHeight = 128,
};

static AX_VOID IVPS_UserMapAttrCfg(AX_IVPS_DEWARP_TYPE_E eDewarpType, AX_IVPS_MAP_USER_ATTR_T *pAttr)
{
    if (eDewarpType != AX_IVPS_DEWARP_MAP_USER)
        return;

    int size = ALIGN_UP(gSampleUserMapCfg.nMeshNumH, 4) * gSampleUserMapCfg.nMeshNumV * 8;
    LoadMeshHex(gSampleUserMapCfg.pMeshFile, size, (AX_U64 *)&gSampleUserMapCfg.nMeshPhyAddr, &gSampleUserMapCfg.pMeshVirAddr);
    pAttr->nMeshStartX = 0;
    pAttr->nMeshStartY = 0;
    pAttr->nMeshWidth = gSampleUserMapCfg.nMeshWidth;
    pAttr->nMeshHeight = gSampleUserMapCfg.nMeshHeight;
    pAttr->nMeshNumH = gSampleUserMapCfg.nMeshNumH;
    pAttr->nMeshNumV = gSampleUserMapCfg.nMeshNumV;
    pAttr->pUserMap = NULL;
    pAttr->nMeshTablePhyAddr = gSampleUserMapCfg.nMeshPhyAddr;
    printf("nMeshTablePhyAddr:%llx\n", pAttr->nMeshTablePhyAddr);
}

static AX_VOID IVPS_EngineAttrCfg(SAMPLE_IVPS_GRP_T *p)
{
    for (int chn = 0; chn < p->tPipelineAttr.nOutChnNum + 1; chn++) {
        switch (p->tPipelineAttr.tFilter[chn][0].eEngine)
        {
        case AX_IVPS_ENGINE_TDP:
            memcpy(&p->tPipelineAttr.tFilter[chn][0].tTdpCfg, &gSampleTdpCfg, sizeof(AX_IVPS_TDP_CFG_T));
            break;
        case AX_IVPS_ENGINE_GDC:
            memcpy(&p->tPipelineAttr.tFilter[chn][0].tGdcCfg, &gSampleGdcCfg, sizeof(AX_IVPS_GDC_CFG_T));
            IVPS_UserMapAttrCfg(p->tPipelineAttr.tFilter[chn][0].tGdcCfg.eDewarpType,
                                &p->tPipelineAttr.tFilter[chn][0].tGdcCfg.tMapUserAttr);
            break;
        default:
            break;
        }
    }

    switch (p->tPipelineAttr.tFilter[0][1].eEngine)
    {
    case AX_IVPS_ENGINE_TDP:
        memcpy(&p->tPipelineAttr.tFilter[0][1].tTdpCfg, &gSampleTdpCfg, sizeof(AX_IVPS_TDP_CFG_T));
        break;
    case AX_IVPS_ENGINE_GDC:
        memcpy(&p->tPipelineAttr.tFilter[0][1].tGdcCfg, &gSampleGdcCfg, sizeof(AX_IVPS_GDC_CFG_T));
        IVPS_UserMapAttrCfg(p->tPipelineAttr.tFilter[0][1].tGdcCfg.eDewarpType,
                            &p->tPipelineAttr.tFilter[0][1].tGdcCfg.tMapUserAttr);
        break;
    default:
        break;
    }
}

static AX_VOID *IVPS_GetFrameThread(AX_VOID *pArg)
{

    AX_S32 i, ret = 0;
    SAMPLE_IVPS_GRP_T *pThis = (SAMPLE_IVPS_GRP_T *)pArg;

    ALOGI("--- IVPS Grp: %d, Chn num: %d", pThis->nIvpsGrp, pThis->tPipelineAttr.nOutChnNum);

    for (i = 0; i < pThis->tPipelineAttr.nOutChnNum; i++)
    {
        pThis->arrOutChns[i].bEmpty = AX_TRUE;
    }

    AX_VIDEO_FRAME_T tDstFrame[pThis->tPipelineAttr.nOutChnNum];
    while (!ThreadLoopStateGet())
    {
        for (i = 0; i < pThis->tPipelineAttr.nOutChnNum; i++)
        {
            if (!pThis->arrOutChns[i].bEmpty)
            {
                break;
            }
        }
        if (i == pThis->tPipelineAttr.nOutChnNum)
        {
            ALOGI("Enter DevPolWait");
            DevPolWait(pThis->nEfd, pThis->tPipelineAttr.nOutChnNum, -1);

            for (i = 0; i < pThis->tPipelineAttr.nOutChnNum; i++)
            {
                pThis->arrOutChns[i].bEmpty = AX_FALSE;
            }
        }

        for (i = 0; i < pThis->tPipelineAttr.nOutChnNum; i++)
        {
            if (!pThis->arrOutChns[i].bEmpty)
            {
                ret = AX_IVPS_GetChnFrame(pThis->nIvpsGrp, i, &tDstFrame[i], 0);

                if (ret)
                {
                    /* reach EOF */
                    ALOGW("warning! CHN[%d] is empty ret:%x", i, ret);
                    pThis->arrOutChns[i].bEmpty = AX_TRUE;
                    continue;
                }

                printf("AX_IVPS_GetChnFrame(%lld): Chn:%d, (%d x %d) Stride:%d, Phy:%llx, UserData:%llx, PTS:%llx, BlockId:%x\n",
                       tDstFrame[i].u64SeqNum, i, tDstFrame[i].u32Width, tDstFrame[i].u32Height, tDstFrame[i].u32PicStride[0],
                       tDstFrame[i].u64PhyAddr[0], tDstFrame[i].u64UserData, tDstFrame[i].u64PTS, tDstFrame[i].u32BlkId[0]);

                SaveFileExt(&tDstFrame[i], pThis->nIvpsGrp, i, pThis->pFilePath, "PPL",
                            pThis->tFrameInput.s16CropWidth, pThis->tFrameInput.s16CropHeight);

                gSampleIvpsMain.nIvpsGetNum--;
                printf("pThis->nIvpsGetNum:%d\n", gSampleIvpsMain.nIvpsGetNum);

                ret = AX_IVPS_ReleaseChnFrame(pThis->nIvpsGrp, i, &tDstFrame[i]);
                if (ret)
                {
                    ALOGE("AX_IVPS_ReleaseFrame fail, ret=0x%x", ret);
                    return (AX_VOID *)-1;
                }
            }
        }
        ALOGI("AX_IVPS_GetFrame");
    }

    ALOGI("IVPS END");
    return (AX_VOID *)0;
}

static AX_VOID *IVPS_SendFrameThread(AX_VOID *pArg)
{
    AX_S32 ret = 0;
    SAMPLE_IVPS_GRP_T *pThis = (SAMPLE_IVPS_GRP_T *)pArg;

    ALOGI("+++ IVPS Grp: %d", pThis->nIvpsGrp);

    gSampleIvpsMain.nIvpsGetNum = gSampleIvpsMain.nIvpsRepeatNum * pThis->tPipelineAttr.nOutChnNum;
    while (!ThreadLoopStateGet() && (gSampleIvpsMain.nIvpsRepeatNum))
    {
        if (pThis->bChnDisabled)
        {
            usleep(20000);
            continue;
        }

        ALOGI("nRepeatNum:%d", gSampleIvpsMain.nIvpsRepeatNum);
        if (gSampleIvpsMain.nIvpsRepeatNum > 0)
            gSampleIvpsMain.nIvpsRepeatNum--;

        pThis->tFrameInput.u64SeqNum++;
        pThis->tFrameInput.u64PTS = GetTickCount();
        ALOGI("AX_IVPS_SendFrame(nChnNum: %d) seq num:%lld PTS:%lld userdata: %llx +++",
              pThis->tPipelineAttr.nOutChnNum, pThis->tFrameInput.u64SeqNum,
              pThis->tFrameInput.u64PTS, pThis->tFrameInput.u64UserData);

        ret = AX_IVPS_SendFrame(pThis->nIvpsGrp, &pThis->tFrameInput, 0);
        usleep(20000);
        ALOGI("AX_IVPS_SendFrame(Grp:%d) ---, ret: 0x%x",pThis->nIvpsGrp, ret);
        if (IVPS_SUCC != ret)
        {
            ALOGE("AX_IVPS_SendFrame(Grp:%d) failed, ret=0x%x", pThis->nIvpsGrp, ret);
            continue;
        }
    }

    ALOGI("IVPS Grp: %d ---", pThis->nIvpsGrp);
    return (AX_VOID *)0;
}

AX_S32 IVPS_StartGrp(const IVPS_ARG_T *ptArg, SAMPLE_IVPS_GRP_T *pGrp)
{
    int ret = 0, nFd;
    AX_IVPS_POOL_ATTR_T PoolAttr = {0};

    IVPS_ChnInfoParser(ptArg, &pGrp->tPipelineAttr);
    IVPS_EngineAttrCfg(pGrp);

    /* IVPS pipeline attr config */
    switch (pGrp->eGrpIdx) {
    case IVPS_GRP_IDX_0:
        if (ptArg->pPipelineIni)
            IVPS_GrpIniParser(ptArg->pPipelineIni, pGrp);
    break;
    case IVPS_GRP_IDX_1:
        if (ptArg->pPipelineExtIni)
            IVPS_GrpIniParser(ptArg->pPipelineExtIni, pGrp);
    break;
    default:
    break;
    }

    pGrp->nEfd = DevEfdCreate(EPOLL_MAXUSERS);

    ret = AX_IVPS_CreateGrp(pGrp->nIvpsGrp, &pGrp->tGrpAttr);
    if (IVPS_SUCC != ret)
    {
        ALOGE("AX_IVPS_CreateGrp(Grp: %d) failed, ret=0x%x.", pGrp->nIvpsGrp, ret);
        return -1;
    }
    ret = AX_IVPS_SetPipelineAttr(pGrp->nIvpsGrp, &pGrp->tPipelineAttr);
    if (IVPS_SUCC != ret)
    {
        ALOGE("AX_IVPS_SetPipelineAttr(Grp: %d) failed, ret=0x%x.", pGrp->nIvpsGrp, ret);
        return -1;
    }

    /* set pool type */
    if (AX_POOL_SOURCE_PRIVATE == pGrp->ePoolSrc) {
        PoolAttr.ePoolSrc = AX_POOL_SOURCE_PRIVATE;
        PoolAttr.nFrmBufNum = 10;
    } else if (AX_POOL_SOURCE_USER == pGrp->ePoolSrc) {
        PoolAttr.ePoolSrc = AX_POOL_SOURCE_USER;
        PoolAttr.PoolId = pGrp->user_pool_id;
    } else {
        PoolAttr.ePoolSrc = AX_POOL_SOURCE_COMMON;
    }
    printf("PoolAttr.ePoolSrc :%d\n", PoolAttr.ePoolSrc);
    ret = AX_IVPS_SetGrpPoolAttr(pGrp->nIvpsGrp, &PoolAttr);
    if (IVPS_SUCC != ret)
    {
        ALOGE("AX_IVPS_SetGrpPoolAttr(Grp: %d) failed, ret=0x%x.", pGrp->nIvpsGrp, ret);
        return -1;
    }
    for (IVPS_CHN chn = 0; chn < pGrp->tPipelineAttr.nOutChnNum; chn++)
    {
        ret = AX_IVPS_SetChnPoolAttr(pGrp->nIvpsGrp, chn, &PoolAttr);
        if (IVPS_SUCC != ret)
        {
            ALOGE("AX_IVPS_SetChnPoolAttr(Grp: %d) failed, ret=0x%x.", pGrp->nIvpsGrp, ret);
            return -1;
        }
    }

    printf("nOutChnNum :%d\n", pGrp->tPipelineAttr.nOutChnNum);
    for (IVPS_CHN chn = 0; chn < pGrp->tPipelineAttr.nOutChnNum; chn++)
    {
        printf("chn id :%d", chn);

        ret = AX_IVPS_EnableChn(pGrp->nIvpsGrp, chn);
        if (IVPS_SUCC != ret)
        {
            ALOGE("AX_IVPS_EnableChn(Chn: %d) failed, ret=0x%x.", chn, ret);
            return -1;
        }

        nFd = AX_IVPS_GetChnFd(pGrp->nIvpsGrp, chn);
        pGrp->arrOutChns[chn].nFd = nFd;
        DevFdListen(pGrp->nEfd, nFd);
    }

    ret = AX_IVPS_StartGrp(pGrp->nIvpsGrp);
    if (IVPS_SUCC != ret)
    {
        ALOGE("AX_IVPS_StartGrp(Grp: %d) failed, ret=0x%x.", pGrp->nIvpsGrp, ret);
        return -1;
    }

    return 0;
}

AX_S32 IVPS_StopGrp(const SAMPLE_IVPS_GRP_T *pGrp)
{
    AX_S32 ret = IVPS_SUCC;

    ret = AX_IVPS_StopGrp(pGrp->nIvpsGrp);
    if (IVPS_SUCC != ret)
    {
        ALOGE("AX_IVPS_StopGrp(Grp: %d) failed(this grp is not started) ret=0x%x.", pGrp->nIvpsGrp, ret);
        return -1;
    }

    for (IVPS_CHN chn = 0; chn < pGrp->tPipelineAttr.nOutChnNum; ++chn)
    {
        ret = AX_IVPS_DisableChn(pGrp->nIvpsGrp, chn);
        if (IVPS_SUCC != ret)
        {
            ALOGE("AX_IVPS_DestoryChn(Chn: %d) failed, ret=0x%x.", chn, ret);
            return -1;
        }
    }

    ret = AX_IVPS_DestoryGrp(pGrp->nIvpsGrp);
    if (IVPS_SUCC != ret)
    {
        ALOGE("AX_IVPS_DestoryGrp(Grp: %d) failed, ret=0x%x.", pGrp->nIvpsGrp, ret);
        return -1;
    }

    /* AX_IVPS_CloseAllFd(); */
    DevEfdRelease(pGrp->nEfd);
    return 0;
}

/*
 * IVPS_GrpThreadStart()
 * IVPS frame send and get can be done separately in different threads.
 */
AX_S32 IVPS_GrpThreadStart(AX_VOID *src, AX_VOID *dst)
{
    if (dst)
    {
        if (0 != pthread_create(&gSampleIvpsMain.get_frame_tid, NULL, IVPS_GetFrameThread, dst))
        {
            gSampleIvpsMain.get_frame_tid = 0;
            return -1;
        }
        pthread_detach(gSampleIvpsMain.get_frame_tid);
    }

    if (src)
    {
        if (0 != pthread_create(&gSampleIvpsMain.send_frame_tid, NULL, IVPS_SendFrameThread, src))
        {
            gSampleIvpsMain.send_frame_tid = 0;
            return -1;
        }
    }
    return 0;
}

AX_S32 IVPS_GrpThreadStop(AX_VOID)
{
    if (gSampleIvpsMain.send_frame_tid)
    {
        pthread_join(gSampleIvpsMain.send_frame_tid, NULL);
        gSampleIvpsMain.send_frame_tid = 0;
    }
    return 0;
}