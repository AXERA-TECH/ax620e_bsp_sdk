/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_ivps_hal.h"
#include "ax_venc_api.h"
#include "sample_engine.h"

/***********************************************************************************/
/*                                  UTILS                                          */
/***********************************************************************************/
static AX_S32 BufPoolBlockAddrGet(AX_POOL PoolId, AX_U32 BlkSize, AX_U64 *nPhyAddr, AX_VOID **pVirAddr, AX_BLK *BlkId)
{

    *BlkId = AX_POOL_GetBlock(PoolId, BlkSize, NULL);
    *nPhyAddr = AX_POOL_Handle2PhysAddr(*BlkId);
    if (!(*nPhyAddr))
    {
        ALOGE("fail!");
        return -1;
    }

    ALOGI("success (Blockid:0x%X --> PhyAddr=0x%llx)", *BlkId, *nPhyAddr);
    *pVirAddr = AX_POOL_GetBlockVirAddr(*BlkId);

    if (!(*pVirAddr))
    {
        ALOGE("fail!");
        return -2;
    }

    ALOGI("success blockVirAddr=0x%p", *pVirAddr);
    return 0;
}

static AX_BOOL Split(char *pSrc, const char *pDelim, char **ppDst, AX_S32 nDstCnt, AX_S32 *pNum)
{

    if (!pSrc || 0 == strlen(pSrc) || 0 == nDstCnt || !pDelim || 0 == strlen(pDelim))
    {
        ALOGE("Invalid para");
        return AX_FALSE;
    }

    AX_S32 nCount = 0;
    char *pToken = strtok(pSrc, pDelim);
    while (NULL != pToken)
    {
        if (++nCount > nDstCnt)
        {
            ALOGE("nCount overflow");
            return AX_FALSE;
        }

        *ppDst++ = pToken;
        pToken = strtok(NULL, pDelim);
    }
    if (pNum)
    {
        *pNum = nCount;
    }

    return AX_TRUE;
}

static AX_U32 CalcImgSize(AX_U32 nStride, AX_U32 nW, AX_U32 nH, AX_IMG_FORMAT_E eType, AX_U32 nAlign)
{
    AX_U32 nBpp = 0;
    if (nW == 0 || nH == 0)
    {
        ALOGE("Invalid width %d or height %d!", nW, nH);
        return 0;
    }
    if (0 == nStride)
    {
        nStride = (0 == nAlign) ? nW : ALIGN_UP(nW, nAlign);
    }
    else
    {
        if (nAlign > 0)
        {
            if (nStride % nAlign)
            {
                ALOGE("stride: %u not %u aligned.!", nStride, nAlign);
                return 0;
            }
        }
    }
    switch (eType)
    {
    case AX_FORMAT_YUV400:
        nBpp = 8;
        break;
    case AX_FORMAT_YUV420_PLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
        nBpp = 12;
        break;
    case AX_FORMAT_YUV422_INTERLEAVED_YUYV:
    case AX_FORMAT_YUV422_INTERLEAVED_UYVY:
    case AX_FORMAT_RGB565:
    case AX_FORMAT_BGR565:
        nBpp = 16;
        break;
    case AX_FORMAT_YUV444_PACKED:
    case AX_FORMAT_RGB888:
    case AX_FORMAT_BGR888:
        nBpp = 24;
        break;
    case AX_FORMAT_RGBA8888:
    case AX_FORMAT_ARGB8888:
        nBpp = 32;
        break;
    default:
        nBpp = 0;
        break;
    }
    return nStride * nH * nBpp / 8;
}

static AX_BOOL LoadImageExt(AX_POOL PoolId, const char *pszImge, AX_U32 nOffset, AX_S32 nImgSize,
                            AX_BLK *BlkId, AX_BOOL isYUVSplit, AX_U64 *nPhyAddr, AX_VOID **pVirAddr)
{
    AX_S32 ret;
    AX_BLK *BlkIdTmp;
    FILE *fp = fopen(pszImge, "rb");
    if (!fp)
    {
        ALOGE("fopen %s fail, %s", pszImge, strerror(errno));
        return AX_FALSE;
    }
    if (nImgSize <= 0)
    {
        fseek(fp, 0, SEEK_END);
        nImgSize = ftell(fp);
        if (nImgSize <= 0)
        {
            ALOGE("file size not right, %d", nImgSize);
            fclose(fp);
            return AX_FALSE;
        }
    }
    fseek(fp, nOffset, SEEK_SET);

    if (isYUVSplit)
    {
        nImgSize = nImgSize / 3;
        ret = BufPoolBlockAddrGet(PoolId, nImgSize * 2, nPhyAddr, pVirAddr, BlkId);
        if (0 != ret)
        {
            ALOGE("BufPoolBlockAddrGet fail, ret=0x%x", ret);
            fclose(fp);
            return AX_FALSE;
        }
        if (fread(*pVirAddr, nImgSize, 2, fp) != 2)
        {
            ALOGE("fread fail, %s", strerror(errno));
            ret = AX_POOL_ReleaseBlock(*BlkId);
            if (ret)
            {
                ALOGE("IVPS Release BlkId fail, ret=0x%x", ret);
            }
            fclose(fp);
            return AX_FALSE;
        }

        fseek(fp, nImgSize * 2, SEEK_SET);
        nPhyAddr++;
        pVirAddr += sizeof(pVirAddr) / 2;
        BlkIdTmp = BlkId;
        BlkId++;
        ret = BufPoolBlockAddrGet(PoolId, nImgSize, nPhyAddr, pVirAddr, BlkId);
        if (0 != ret)
        {
            ALOGE("BufPoolBlockAddrGet fail, ret=0x%x", ret);
            ret = AX_POOL_ReleaseBlock(*BlkIdTmp);
            if (ret)
            {
                ALOGE("IVPS Release BlkId fail, ret=0x%x", ret);
            }
            fclose(fp);
            return AX_FALSE;
        }
        if (fread(*pVirAddr, nImgSize, 1, fp) != 1)
        {
            ALOGE("fread fail, %s", strerror(errno));
            ret = AX_POOL_ReleaseBlock(*BlkIdTmp);
            if (ret)
            {
                ALOGE("IVPS Release BlkId fail, ret=0x%x", ret);
            }
            ret = AX_POOL_ReleaseBlock(*BlkId);
            if (ret)
            {
                ALOGE("IVPS Release BlkId fail, ret=0x%x", ret);
            }
            fclose(fp);
            return AX_FALSE;
        }
        fclose(fp);
        return AX_TRUE;
    }

    ret = BufPoolBlockAddrGet(PoolId, nImgSize, nPhyAddr, pVirAddr, BlkId);
    if (0 != ret)
    {
        ALOGE("BufPoolBlockAddrGet UV fail, ret=0x%x", ret);
        fclose(fp);
        return AX_FALSE;
    }
    if (fread(*pVirAddr, nImgSize, 1, fp) != 1)
    {
        ALOGE("fread fail, %s", strerror(errno));
        ret = AX_POOL_ReleaseBlock(*BlkId);
        if (ret)
        {
            ALOGE("IVPS Release BlkId fail, ret=0x%x", ret);
        }
        fclose(fp);
        return AX_FALSE;
    }
    fclose(fp);

    return AX_TRUE;
}

static int ImgInfoParse(SAMPLE_IMAGE_INFO_T *tImage, char *pArg)
{
    char *end, *p = NULL;

    if (pArg && strlen(pArg) > 0)
    {
        char *ppToken[4] = {NULL};
        AX_S32 nNum = 0;
        if (!Split(pArg, "@", ppToken, 4, &nNum))
        {
            ALOGE("error! para is not right!");
            return -1;
        }
        else
        {
            if (nNum == 1)
            {
                p = ppToken[0];
            }
            else if (nNum == 4)
            {
                tImage->pImgFile = ppToken[0];
                // tImage->tImage.eFormat = (AX_IMG_FORMAT_E)(int)(ppToken[1]);
                p = ppToken[2];

                tImage->tImage.nStride = strtoul(p, &end, 10);
                if (*end != 'x')
                    return -1;
                p = end + 1;
                tImage->tImage.nH = strtoul(p, &end, 10);
                p = ppToken[3];
            }
        }
    }
    tImage->tRect.nW = strtoul(p, &end, 10);
    if (*end != 'x')
        return -1;
    p = end + 1;
    tImage->tRect.nH = strtoul(p, &end, 10);

    if (*end == '+' || *end == '-')
    {
        p = end + 1;
        tImage->tRect.nX = strtol(p, &end, 10);
        if (*end != '+' && *end != '-')
            return -1;
        p = end + 1;
        tImage->tRect.nY = strtol(p, &end, 10);
    }
    else
    {
        tImage->tRect.nX = 0;
        tImage->tRect.nY = 0;
    }
    if (*end == '*')
    {
        p = end + 1;
        tImage->nAlpha = strtoul(p, &end, 10);
    }
    else
    {
        tImage->nAlpha = 255;
    }

    if (*end == '%')
    {
        p = end + 1;
        tImage->eBlkSize = (AX_IVPS_MOSAIC_BLK_SIZE_E)strtoul(p, &end, 10);
    }
    else
    {
        tImage->eBlkSize = (AX_IVPS_MOSAIC_BLK_SIZE_E)1;
    }

    if (*end == ':')
    {
        p = end + 1;
        tImage->nColor = strtoul(p, &end, 16);
    }
    else
    {
        tImage->nColor = 0x808080;
    }

    if (*end == '-')
    {
        p = end + 1;
        tImage->nLineW = strtoul(p, &end, 10);
    }
    else
    {
        tImage->nLineW = 1;
    }
    if (*end == '#')
    {
        p = end + 1;
        tImage->nChn = strtoul(p, &end, 10);
    }
    else
    {
        tImage->nChn = 0;
    }

    ALOGI("path:%s,format:%d, stride:%d (w:%d, h:%d, x:%d, y:%d) alpha:%d\n",
          tImage->pImgFile, tImage->tImage.eFormat, tImage->tImage.nStride,
          tImage->tRect.nW, tImage->tRect.nH, tImage->tRect.nX,
          tImage->tRect.nY, tImage->nAlpha);
    ALOGI("blksize:%d, color:%x, line:%d, chn:%d",
          tImage->eBlkSize, tImage->nColor, tImage->nLineW, tImage->nChn);
    ALOGI("image parse end nPhyAddr:%x", tImage->tImage.nPhyAddr);
    return 0;
}

static char *FrameInfoGet(char *optArg, AX_VIDEO_FRAME_T *ptFrame)
{
    SAMPLE_IMAGE_INFO_T tImage = {0};

    ImgInfoParse(&tImage, optArg);

    ptFrame->s16CropX = tImage.tRect.nX;
    ptFrame->s16CropY = tImage.tRect.nY;
    ptFrame->s16CropWidth = tImage.tRect.nW;
    ptFrame->s16CropHeight = tImage.tRect.nH;
    ptFrame->enImgFormat = tImage.tImage.eFormat;
    ptFrame->u32PicStride[0] = tImage.tImage.nStride;
    ptFrame->u32Width = tImage.tImage.nStride;
    ptFrame->u32Height = tImage.tImage.nH;

    ptFrame->u32FrameSize = CalcImgSize(ptFrame->u32PicStride[0], ptFrame->u32Width,
                                        ptFrame->u32Height, ptFrame->enImgFormat, 0);

    ALOGI2("ptFrame Width:%d Height:%d", ptFrame->u32Width, ptFrame->u32Height);
    ALOGI("CROP: X0:%d Y0:%d W:%d H:%d", ptFrame->s16CropX, ptFrame->s16CropY,
          ptFrame->s16CropWidth, ptFrame->s16CropHeight);

    ptFrame->u64PTS = 0x2020;
    ptFrame->u64SeqNum = 0;

    return tImage.pImgFile;
}

static AX_S32 FrameBufGet(AX_S32 nFrameIdx, AX_VIDEO_FRAME_T *ptImage, char *pImgFile)
{
    if (!pImgFile)
    {
        ALOGE("pImgFile is NULL!");
        return -1;
    }
    if (!LoadImageExt(-1, pImgFile, nFrameIdx * ptImage->u32FrameSize, ptImage->u32FrameSize, &ptImage->u32BlkId[0],
                      AX_FALSE, &ptImage->u64PhyAddr[0], (AX_VOID **)&ptImage->u64VirAddr[0]))
    {
        ALOGE("LoadImageExt error!");
        return -2;
    }
    ALOGI("VirAddr:0x%x VirAddr_UV:0x%x", (AX_U32)ptImage->u64VirAddr[0], (AX_U32)ptImage->u64VirAddr[1]);

    return 0;
}

static AX_U64 GetTickCount(AX_VOID)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
}

/***********************************************************************************/
/*                                  HAL                                            */
/***********************************************************************************/
static volatile AX_BOOL bThreadLoopExit;
static SAMPLE_IVPS_GRP_T gSampleIvpsGrp;

AX_VOID ThreadLoopStateSet(AX_BOOL bValue)
{
    bThreadLoopExit = bValue;
}

AX_BOOL ThreadLoopStateGet(AX_VOID)
{
    return bThreadLoopExit;
}

static AX_VOID *IVPS_SendFrameThread(AX_VOID *pArg)
{
    AX_S32 ret = 0;
    SAMPLE_IVPS_GRP_T *pThis = (SAMPLE_IVPS_GRP_T *)pArg;

    printf("+++IVPS Grp: %d", pThis->nIvpsGrp);

    while (!ThreadLoopStateGet())
    {
        pThis->tFrameInput.u64SeqNum++;
        pThis->tFrameInput.u64PTS = GetTickCount();
        printf("AX_IVPS_SendFrame seq num:%lld PTS:%lld userdata: %llx +++\n", pThis->tFrameInput.u64SeqNum,
               pThis->tFrameInput.u64PTS, pThis->tFrameInput.u64UserData);

        ret = AX_IVPS_SendFrame(pThis->nIvpsGrp, &pThis->tFrameInput, -1);

        usleep(40000);
        ALOGI("AX_IVPS_SendFrame(Grp:%d) ---, ret: 0x%x", pThis->nIvpsGrp, ret);
        if (IVPS_SUCC != ret)
        {
            ALOGE("AX_IVPS_SendFrame(Grp:%d) failed, ret=0x%x.", pThis->nIvpsGrp, ret);
            continue;
        }
    }
    return (AX_VOID *)0;
}

void visualize_infer_result(IVPS_RGN_HANDLE handle, SAMPLE_ENGINE_Results *objects, float aspect_w, float aspect_h)
{
    int obj_num = objects->obj_count;

    // if (obj_num == 0)
    //     return;

    AX_IVPS_RGN_DISP_GROUP_T *rgn_grp = (AX_IVPS_RGN_DISP_GROUP_T *)malloc(sizeof(AX_IVPS_RGN_DISP_GROUP_T));
    memset(rgn_grp, 0, sizeof(AX_IVPS_RGN_DISP_GROUP_T));

    rgn_grp->nNum = obj_num;
    rgn_grp->tChnAttr.nZindex = 0;
    rgn_grp->tChnAttr.bSingleCanvas = AX_TRUE;
    rgn_grp->tChnAttr.nAlpha = 255;
    rgn_grp->tChnAttr.eFormat = AX_FORMAT_RGBA8888;
    AX_IVPS_RGN_DISP_T *disp = rgn_grp->arrDisp;

    for (int i = 0; i < (obj_num < AX_IVPS_REGION_MAX_DISP_NUM ? obj_num : AX_IVPS_REGION_MAX_DISP_NUM); i++)
    {
        disp[i].bShow = AX_TRUE;
        disp[i].eType = AX_IVPS_RGN_TYPE_RECT;
        disp[i].uDisp.tPolygon.tRect.nX = (int)(objects->objs[i].x * aspect_w);
        disp[i].uDisp.tPolygon.tRect.nY = (int)(objects->objs[i].y * aspect_h);
        disp[i].uDisp.tPolygon.tRect.nW = (int)(objects->objs[i].width * aspect_w);
        disp[i].uDisp.tPolygon.tRect.nH = (int)(objects->objs[i].height * aspect_h);
        if (disp[i].uDisp.tPolygon.tRect.nW == 0 || disp[i].uDisp.tPolygon.tRect.nH == 0)
        {
            disp[i].bShow = AX_FALSE;
        }
        // printf("x y w h: %d %d %d %d\n", disp[i].uDisp.tPolygon.tRect.nX, disp[i].uDisp.tPolygon.tRect.nY, disp[i].uDisp.tPolygon.tRect.nW, disp[i].uDisp.tPolygon.tRect.nH);
        disp[i].uDisp.tPolygon.nLineWidth = 3;
        disp[i].uDisp.tPolygon.bSolid = AX_FALSE;
        disp[i].uDisp.tPolygon.tCornerRect.bEnable = AX_FALSE;
        disp[i].uDisp.tPolygon.tCornerRect.nHorLength = 20;
        disp[i].uDisp.tPolygon.tCornerRect.nVerLength = 10;
        disp[i].uDisp.tPolygon.nAlpha = 255;
        disp[i].uDisp.tPolygon.nColor = objects->objs[i].color;
    }

    int ret = AX_IVPS_RGN_Update(handle, rgn_grp);
    if (ret != 0)
    {
        printf("AX_IVPS_RGN_Update failed. ret=0x%x\n", ret);
    }

    free(rgn_grp);
}

static AX_VOID *IVPS_GetFrameThread(AX_VOID *pArg)
{
    AX_S32 ret = 0;
    SAMPLE_IVPS_GRP_T *pThis = (SAMPLE_IVPS_GRP_T *)pArg;
    AX_VIDEO_FRAME_T engine_input_frame;
    IVPS_GRP nGrp = pThis->nIvpsGrp;
    AX_IVPS_PIPELINE_ATTR_T stPipelineAttr;
    ret = AX_IVPS_GetPipelineAttr(nGrp, &stPipelineAttr);
    if (ret != 0)
    {
        printf("AX_IVPS_GetPipelineAttr failed. ret=0x%x\n", ret);
        return (AX_VOID *)0;
    }

    int chn_num = stPipelineAttr.nOutChnNum - 1;
    const int infer_chn = ALGO_CHN;

    IVPS_RGN_HANDLE *rgn_handles = (IVPS_RGN_HANDLE *)malloc(sizeof(IVPS_RGN_HANDLE) * chn_num);
    float *aspect_w = (float *)malloc(sizeof(float) * chn_num);
    float *aspect_h = (float *)malloc(sizeof(float) * chn_num);
    for (int i = 0; i < chn_num; i++)
    {
        rgn_handles[i] = AX_IVPS_RGN_Create();
        ret = AX_IVPS_RGN_AttachToFilter(rgn_handles[i], nGrp, 16 * (i + 1));
        if (ret != 0)
        {
            printf("AX_IVPS_RGN_AttachToFilter filter=%d failed. ret=%d\n", i + 1, ret);
            AX_IVPS_RGN_Destroy(rgn_handles[i]);
            free(rgn_handles);
            free(aspect_w);
            free(aspect_h);
            return (AX_VOID *)0;
        }

        aspect_w[i] = stPipelineAttr.tFilter[i + 1][0].nDstPicWidth * 1.0f / 1920;
        aspect_h[i] = stPipelineAttr.tFilter[i + 1][0].nDstPicHeight * 1.0f / 1080;

        // printf("aspect ratio[%d]: %f %f\n", i, aspect_w[i], aspect_h[i]);
    }

    while (!ThreadLoopStateGet())
    {
        // Get infer_chn frame
        memset(&engine_input_frame, 0, sizeof(AX_VIDEO_FRAME_T));
        ret = AX_IVPS_GetChnFrame(nGrp, infer_chn, &engine_input_frame, -1);
        if (ret != 0)
        {
            printf("AX_IVPS_GetChnFrame(Grp:%d Chn:%d) failed, ret=0x%x.\n", nGrp, infer_chn, ret);
            continue;
        }

        // inference
        engine_input_frame.u64VirAddr[0] = (AX_U64)AX_POOL_GetBlockVirAddr(engine_input_frame.u32BlkId[0]);
        engine_input_frame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(engine_input_frame.u32BlkId[0]);

        SAMPLE_ENGINE_Results stResults;
        stResults.obj_count = 0;
        ret = SAMPLE_ENGINE_Inference(&engine_input_frame, &stResults);
        if (ret != 0)
        {
            printf("inference failed, ret=%d.\n", ret);
        }
        if (stResults.obj_count > 0)
            printf("Detected %d object(s)\n", stResults.obj_count);

        // draw frame
        for (int i = 0; i < chn_num; i++)
            visualize_infer_result(rgn_handles[i], &stResults, aspect_w[i], aspect_h[i]);

        ret = AX_IVPS_ReleaseChnFrame(nGrp, infer_chn, &engine_input_frame);
        if (ret != 0)
        {
            printf("AX_IVPS_ReleaseChnFrame(Grp:%d Chn:%d) failed, ret=0x%x.\n", nGrp, infer_chn, ret);
        }
    }

    for (int i = 0; i < chn_num; i++)
    {
        ret = AX_IVPS_RGN_DetachFromFilter(rgn_handles[i], nGrp, 16 * (i + 1));
        if (ret != 0)
        {
            printf("AX_IVPS_RGN_DetachFromFilter failed, ret=0x%x.\n", ret);
        }

        ret = AX_IVPS_RGN_Destroy(rgn_handles[i]);
        if (ret != 0)
        {
            printf("AX_IVPS_RGN_Destroy chn:%d failed, ret=0x%x.\n", i, ret);
        }
    }

    free(rgn_handles);
    free(aspect_w);
    free(aspect_h);

    return (AX_VOID *)0;
}

/* IVPS frame send and get can be done separately in different threads */
static AX_S32 SAMPLE_IVPS_SendThreadStart(AX_VOID *src)
{
    pthread_t tid = 0;
    if (src)
    {
        if (0 != pthread_create(&tid, NULL, IVPS_SendFrameThread, src))
        {
            return -1;
        }
        pthread_detach(tid);
    }
    return 0;
}

static AX_S32 SAMPLE_IVPS_GetThreadStart(AX_VOID *src)
{
    pthread_t tid = 0;
    if (src)
    {
        if (0 != pthread_create(&tid, NULL, IVPS_GetFrameThread, src))
        {
            return -1;
        }
        pthread_detach(tid);
    }
    return 0;
}

/* Send frame without VIN */
AX_S32 SAMPLE_IVPS_SendFrame(AX_S32 nIvpsGrp, char *pFrameInfo)
{
    int nRet;

    if (!pFrameInfo)
    {
        ALOGE("pFrameInfo is NULL!");
        return -1;
    }
    SAMPLE_IVPS_GRP_T *pGrp = &gSampleIvpsGrp;
    pGrp->nIvpsGrp = nIvpsGrp;
    char *pFrameFile = FrameInfoGet(pFrameInfo, &pGrp->tFrameInput);
    nRet = FrameBufGet(0, &pGrp->tFrameInput, pFrameFile);
    if (0 != nRet)
    {
        ALOGE("FrameBufGet error. ret=%d", nRet);
        return -2;
    }
    nRet = SAMPLE_IVPS_SendThreadStart(pGrp);
    if (0 != nRet)
    {
        ALOGE("SAMPLE_IVPS_SendThreadStart error. ret=%d", nRet);
        return -3;
    }
    return 0;
}

/* Get Frame, Inference and Draw */
AX_S32 SAMPLE_IVPS_GetFrame_and_Inference(AX_S32 nIvpsGrp)
{
    int nRet = 0;
    SAMPLE_IVPS_GRP_T *pGrp = &gSampleIvpsGrp;
    pGrp->nIvpsGrp = nIvpsGrp;
    nRet = SAMPLE_IVPS_GetThreadStart(pGrp);
    if (0 != nRet)
    {
        ALOGE("SAMPLE_IVPS_GetThreadStart error. ret=%d", nRet);
        return nRet;
    }
    return 0;
}