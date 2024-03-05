/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_ivps_hal.h"
#include "sample_vin_ivps_vo_venc.h"

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
                tImage->tImage.eFormat = atoi(ppToken[1]);
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
        tImage->eBlkSize = strtoul(p, &end, 10);
    }
    else
    {
        tImage->eBlkSize = 1;
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

        sleep(1);
        ALOGI("AX_IVPS_SendFrame(Grp:%d) ---, ret: 0x%x", pThis->nIvpsGrp, ret);
        if (IVPS_SUCC != ret)
        {
            ALOGE("AX_IVPS_SendFrame(Grp:%d) failed, ret=0x%x.", pThis->nIvpsGrp, ret);
            continue;
        }
    }
    return (AX_VOID *)0;
}

/* IVPS frame send and get can be done separately in different threads */
static AX_S32 SAMPLE_IVPS_ThreadStart(AX_VOID *src)
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
    nRet = SAMPLE_IVPS_ThreadStart(pGrp);
    if (0 != nRet)
    {
        ALOGE("SAMPLE_IVPS_ThreadStart error. ret=%d", nRet);
        return -3;
    }
    return 0;
}