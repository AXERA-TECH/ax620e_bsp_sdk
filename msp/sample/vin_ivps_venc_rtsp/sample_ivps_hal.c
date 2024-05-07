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

static AX_VOID SaveFile(AX_VIDEO_FRAME_T *tDstFrame, AX_S32 nGrpIdx, AX_S32 nChnIdx,
                        char *pFilePath, char *pFileName)
{
    AX_U32 nPixelSize;
    AX_S32 s32Ret1 = 0;
    AX_S32 s32Ret2 = 0;
    AX_S32 s32Ret3 = 0;
    AX_S32 bit_num = 0;
    AX_U8 nStoragePlanarNum = 0;
    char szOutImgFile[256] = {0};

    if (!pFilePath)
    {
        printf("[WARN] File path is null, no need to save file\n");
        return;
    }

    nPixelSize = (AX_U32)tDstFrame->u32PicStride[0] * tDstFrame->u32Height;

    switch (tDstFrame->enImgFormat)
    {
    case AX_FORMAT_YUV420_PLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
    case AX_FORMAT_YUV422_SEMIPLANAR: /* NV16 */
    case AX_FORMAT_YUV422_SEMIPLANAR_VU:
    case AX_FORMAT_YUV422_INTERLEAVED_YUYV:
        bit_num = 8;
        nStoragePlanarNum = 2;
        break;
    case AX_FORMAT_YUV420_SEMIPLANAR_10BIT_P101010:
    case AX_FORMAT_YUV422_SEMIPLANAR_10BIT_P101010:
        bit_num = 10;
        nStoragePlanarNum = 2;
        break;
    case AX_FORMAT_YUV420_SEMIPLANAR_10BIT_P010:
    case AX_FORMAT_YUV422_SEMIPLANAR_10BIT_P010:
        bit_num = 16;
        nStoragePlanarNum = 2;
        break;
    case AX_FORMAT_YUV444_PACKED:
    case AX_FORMAT_RGB888:
    case AX_FORMAT_BGR888:
    case AX_FORMAT_RGB565:
    case AX_FORMAT_BGR565:
    case AX_FORMAT_RGBA8888:
    case AX_FORMAT_ARGB8888:
    case AX_FORMAT_ARGB4444:
    case AX_FORMAT_ARGB1555:
    case AX_FORMAT_ARGB8565:
    case AX_FORMAT_RGBA5551:
    case AX_FORMAT_RGBA4444:
    case AX_FORMAT_RGBA5658:
    case AX_FORMAT_ABGR4444:
    case AX_FORMAT_ABGR1555:
    case AX_FORMAT_ABGR8888:
    case AX_FORMAT_ABGR8565:
    case AX_FORMAT_BGRA8888:
    case AX_FORMAT_BGRA5551:
    case AX_FORMAT_BGRA4444:
    case AX_FORMAT_BGRA5658:
    case AX_FORMAT_YUV400:
        nStoragePlanarNum = 1;
        break;
    default:
        ALOGE("Not support fromat %d", tDstFrame->enImgFormat);
        return;
        break;
    }

    printf("SaveFile nPixelSize: %d u32FrameSize: %d Height:%d Width:%d PhyAddrY:%llx PhyAddrUV:%llx Format:%d\n",
           nPixelSize, tDstFrame->u32FrameSize, tDstFrame->u32Height, tDstFrame->u32Width,
           tDstFrame->u64PhyAddr[0], tDstFrame->u64PhyAddr[1], tDstFrame->enImgFormat);

    sprintf(szOutImgFile, "%s/%s_GRP%dCHN%d_%dx%d.0x%x", pFilePath, pFileName,
            nGrpIdx, nChnIdx, tDstFrame->u32PicStride[0], tDstFrame->u32Height, tDstFrame->enImgFormat);

    FILE *fp = fopen(szOutImgFile, "wb");
    if (!fp)
    {
        ALOGE("Fail to open file:%s!", szOutImgFile);
        return;
    }

    printf("Save file(%s)!\n", szOutImgFile);
    switch (nStoragePlanarNum)
    {
    case 2:
        if (!tDstFrame->u64PhyAddr[1])
        {
            if (tDstFrame->stCompressInfo.enCompressMode)
                tDstFrame->u64PhyAddr[1] = tDstFrame->u64PhyAddr[0] + tDstFrame->u32PicStride[0] * tDstFrame->u32Height * tDstFrame->stCompressInfo.u32CompressLevel / 8;
            else
                tDstFrame->u64PhyAddr[1] = tDstFrame->u64PhyAddr[0] + tDstFrame->u32PicStride[0] * tDstFrame->u32Height;
        }
        if (tDstFrame->stCompressInfo.enCompressMode)
            nPixelSize = nPixelSize * bit_num / 8 * tDstFrame->stCompressInfo.u32CompressLevel / 8;
        else
            nPixelSize = nPixelSize * bit_num / 8;

        if (AX_FORMAT_YUV422_SEMIPLANAR == tDstFrame->enImgFormat || AX_FORMAT_YUV422_SEMIPLANAR_VU == tDstFrame->enImgFormat || AX_FORMAT_YUV422_SEMIPLANAR_10BIT_P101010 == tDstFrame->enImgFormat || AX_FORMAT_YUV422_SEMIPLANAR_10BIT_P010 == tDstFrame->enImgFormat)
        {
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize);
            tDstFrame->u64VirAddr[1] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[1], nPixelSize);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize, fp);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[1]), 1, nPixelSize, fp);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[1], nPixelSize);
        }
        else
        {
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize);
            tDstFrame->u64VirAddr[1] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[1], nPixelSize / 2);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize, fp);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[1]), 1, nPixelSize / 2, fp);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[1], nPixelSize / 2);
        }
        break;
    case 3:
        tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize);
        tDstFrame->u64VirAddr[1] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[1], nPixelSize / 2);
        tDstFrame->u64VirAddr[2] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[2], nPixelSize / 2);
        fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize, fp);
        fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[1]), 1, nPixelSize / 2, fp);
        fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[2]), 1, nPixelSize / 2, fp);
        s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize);
        s32Ret2 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[1], nPixelSize / 2);
        s32Ret3 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[2], nPixelSize / 2);
        break;
    default:
        if (tDstFrame->u32FrameSize)
        {
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], tDstFrame->u32FrameSize);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, tDstFrame->u32FrameSize, fp);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], tDstFrame->u32FrameSize);
        }
        else
        {
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize * 3);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize * 3, fp);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize * 3);
        }
        break;
    }
    fclose(fp);
    printf("Save success!\n");

    if (s32Ret1 || s32Ret2 || s32Ret3)
    {
        printf("AX_SYS_Munmap s32Ret1=0x%x ,s32Ret2=0x%x ,s32Ret2=0x%x", s32Ret1, s32Ret2, s32Ret3);
    }
}

static AX_VOID SaveFileExt(AX_VIDEO_FRAME_T *ptDstFrame, AX_S32 nGrpIdx, AX_S32 nChnIdx,
                           char *pFilePath, char *pFileName, int nInputW, int nInputH)
{
    char szOutImgName[128] = {0};
    sprintf(szOutImgName, "%s_%dx%d", pFileName, nInputW, nInputH);
    SaveFile(ptDstFrame, nGrpIdx, nChnIdx, pFilePath, szOutImgName);
}

/***********************************************************************************/
/*                                  HAL                                            */
/***********************************************************************************/
static volatile AX_BOOL bThreadLoopExit;
SAMPLE_IVPS_GRP_T gSampleIvpsGrp;

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

    printf("+++IVPS Grp: %d\n", pThis->nIvpsGrp);

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

/***********************************************************************************/
/*                                  REGION                                         */
/***********************************************************************************/

static SAMPLE_REGION_INFO_T gRegions[] = {
    {
        .handle = AX_IVPS_INVALID_REGION_HANDLE,
        .IvpsGrp = -1,
        .IvpsFilter = 0x11, /* CHN0 FILTER1 */
    },
    {
        .handle = AX_IVPS_INVALID_REGION_HANDLE,
        .IvpsGrp = -1,
        .IvpsFilter = 0x21, /* CHN1 FILTER1 */
    },
    {
        .handle = AX_IVPS_INVALID_REGION_HANDLE,
        .IvpsGrp = -1,
        .IvpsFilter = 0x31, /* CHN2 FILTER1 */
    },
    {
        .handle = AX_IVPS_INVALID_REGION_HANDLE,
        .IvpsGrp = -1,
        .IvpsFilter = 0x41, /* CHN3 FILTER1 */
    },
};

/*
 * SAMPLE_IVPS_RegionStart()
 * Create a region handle, attach the handle to filter.
 */
AX_S32 SAMPLE_IVPS_RegionStart(AX_S32 nIvpsGrp, AX_U32 nRegionNum)
{
    for (AX_S32 i = 0; i < nRegionNum; i++)
    {
        gRegions[i].IvpsGrp = nIvpsGrp;
        gRegions[i].handle = AX_IVPS_RGN_Create();
        ALOGI("gRegions[%d].handle:%d", i, gRegions[i].handle);
        if (AX_IVPS_INVALID_REGION_HANDLE == gRegions[i].handle)
        {
            ALOGE("AX_IVPS_CreateRegion(%d) fail", i);
            return -1;
        }

        AX_S32 ret = AX_IVPS_RGN_AttachToFilter(gRegions[i].handle, gRegions[i].IvpsGrp, gRegions[i].IvpsFilter);
        if (ret)
        {
            ALOGE("AX_IVPS_RGN_DetachFromFilter(handle %d => Grp %d Filter %x) fail, ret=0x%x",
                  gRegions[i].handle, gRegions[i].IvpsGrp, gRegions[i].IvpsFilter, ret);

            /* detach and destroy overlay */
            for (; i >= 0; i--)
            {
                if (AX_IVPS_INVALID_REGION_HANDLE != gRegions[i].handle)
                {
                    AX_IVPS_RGN_DetachFromFilter(gRegions[i].handle, gRegions[i].IvpsGrp, gRegions[i].IvpsFilter);
                    AX_IVPS_RGN_Destroy(gRegions[i].handle);
                    gRegions[i].handle = AX_IVPS_INVALID_REGION_HANDLE;
                }
            }
            return -1;
        }
    }

    return 0;
}

/*
 * SAMPLE_IVPS_RegionStop()
 * Detach the handle from filter, then destroy the handle.
 */
AX_S32 SAMPLE_IVPS_RegionStop(AX_VOID)
{
    ALOGI("IVPS_StopRegion num:%ld", sizeof(gRegions) / sizeof(gRegions[0]));

    for (AX_S32 j = 0; j < sizeof(gRegions) / sizeof(gRegions[0]); ++j)
    {
        if (AX_IVPS_INVALID_REGION_HANDLE != gRegions[j].handle)
        {
            AX_IVPS_RGN_DetachFromFilter(gRegions[j].handle, gRegions[j].IvpsGrp, gRegions[j].IvpsFilter);
            AX_IVPS_RGN_Destroy(gRegions[j].handle);
            gRegions[j].handle = AX_IVPS_INVALID_REGION_HANDLE;
        }
    }

    return 0;
}

/*
 * ByteReverse()
 * Arrange each bit in reverse order for one byte.
 */
static AX_S32 ByteReverse(AX_U8 *ptBitmap, AX_S32 nSize)
{
    int idx;
    unsigned char data;
    for (idx = 0; idx < nSize; idx++)
    {
        data = *(ptBitmap + idx);
        data = (data & 0x55) << 1 | (data & 0xAA) >> 1; // swap 12,34,56,78
        data = (data & 0x33) << 2 | (data & 0xCC) >> 2; // swap (21 43),(65 87)
        data = (data & 0x0F) << 4 | (data & 0xF0) >> 4; // swap 4bit
        *(ptBitmap + idx) = data;
    }
    return IVPS_SUCC;
}

#include "cursor_bitmap_text.h"
static AX_VOID SAMPLE_IVPS_OsdCfg1(AX_IVPS_RGN_DISP_GROUP_T *ptRegion)
{
    /*
    nZindex: Required
            Indicates which layer to draw OSD on.
            If in inplace mode, nZindex is in [0, 31]. If not, nZindex = 0.
    nAlpha: Required
            [0, 255], 0: transparent, 255: opaque.
    eFormat: Required
            Support AX_FORMAT_ARGB1555/AX_FORMAT_RGBA5551/AX_FORMAT_BITMAP.
            The sub arrDisp's format should be the same as the for format.
    Note:   u64PhyAddr of tOSD is not required. But pBitmap is required.
            Engine should be in inplace mode.
    */
    ByteReverse(&bitmap_cursor[0], sizeof(bitmap_cursor));
    ptRegion->nNum = 1;
    ptRegion->tChnAttr.nZindex = 0;
    ptRegion->tChnAttr.nAlpha = 200; /*0 - 255, 0: transparent, 255: opaque*/
    ptRegion->tChnAttr.eFormat = AX_FORMAT_BITMAP;
    ptRegion->tChnAttr.nBitColor.nColor = 0xFF0000;
    ptRegion->tChnAttr.nBitColor.bColorInv = AX_TRUE;
    ptRegion->tChnAttr.nBitColor.nColorInv = 0xFF;
    ptRegion->tChnAttr.nBitColor.nColorInvThr = 0xA0A0A0;
    ptRegion->arrDisp[0].bShow = AX_TRUE;
    ptRegion->arrDisp[0].eType = AX_IVPS_RGN_TYPE_OSD;
    ptRegion->arrDisp[0].uDisp.tOSD.u16Alpha = 512;
    ptRegion->arrDisp[0].uDisp.tOSD.enRgbFormat = AX_FORMAT_BITMAP;
    ptRegion->arrDisp[0].uDisp.tOSD.u32BmpWidth = 240;
    ptRegion->arrDisp[0].uDisp.tOSD.u32BmpHeight = 227;
    ptRegion->arrDisp[0].uDisp.tOSD.u32DstXoffset = 0;
    ptRegion->arrDisp[0].uDisp.tOSD.u32DstYoffset = 0;
    ptRegion->arrDisp[0].uDisp.tOSD.pBitmap = &bitmap_cursor[0];
}

static AX_S32 SAMPLE_IVPS_RegionUpdate(AX_U32 nRgnNum)
{
    int ret, index;

    for (index = 0; index < nRgnNum; index++)
    {
        ret = AX_IVPS_RGN_Update(gRegions[index].handle, &gRegions[index].tRegionGrp);
        if (IVPS_SUCC != ret)
        {
            ALOGE("AX_IVPS_RGN_Update fail, ret=0x%x", ret);
        }
    }
    return ret;
}

static AX_VOID *SAMPLE_IVPS_RegionUpdateThread(AX_VOID *pArg)
{
    int index;
    int nRgnNum = (AX_LONG)pArg;

    if (!nRgnNum)
    {
        return (AX_VOID *)1;
    }

    for (index = 0; index < nRgnNum; index++)
    {
        SAMPLE_IVPS_OsdCfg1(&gRegions[index].tRegionGrp);
    }

    while (!ThreadLoopStateGet())
    {
        SAMPLE_IVPS_RegionUpdate(nRgnNum);
        sleep(1);
    }

    return (AX_VOID *)0;
}

/*
 * SAMPLE_IVPS_RegionUpdateStart()
 * Create a thread to update the region canvas every time.
 */
AX_S32 SAMPLE_IVPS_RegionUpdateStart(AX_S32 nRegionNum)
{
    ALOGI("Update nRegionNum:%d", nRegionNum);

    if (0 != pthread_create(&gSampleIvpsGrp.region_tid, NULL, SAMPLE_IVPS_RegionUpdateThread, (AX_VOID *)(AX_LONG)nRegionNum))
    {
        return -1;
    }

    return 0;
}

AX_S32 SAMPLE_IVPS_RegionUpdateStop(AX_VOID)
{
    pthread_join(gSampleIvpsGrp.region_tid, NULL);
    return 0;
}

/***********************************************************************************/
/*                                  CROP RESIZE                                    */
/***********************************************************************************/

static AX_VOID *IVPS_CropResizeThread(AX_VOID *pArg)
{

    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tSrcFrame, tDstFrame;
    SAMPLE_IVPS_GRP_T *pThis = (SAMPLE_IVPS_GRP_T *)pArg;
    AX_IVPS_CROP_RESIZE_ATTR_T tCropResizeAttr = {0};
    AX_BLK BlkId;
    AX_U32 nImgSize;

    ALOGI("IVPS Grp: %d, Chn: %d", pThis->nIvpsGrp, pThis->nIvpsChn);
#ifdef SAMPLE_IVPS_CROPRESIZE_MANUAL_MODE
    tCropResizeAttr.tAspectRatio.eMode = AX_IVPS_ASPECT_RATIO_MANUAL;
    tCropResizeAttr.tAspectRatio.eAligns[0] = AX_IVPS_ASPECT_RATIO_HORIZONTAL_CENTER;
    tCropResizeAttr.tAspectRatio.eAligns[1] = AX_IVPS_ASPECT_RATIO_VERTICAL_CENTER;
    tCropResizeAttr.tAspectRatio.nBgColor = 0x00FFFF;
    tCropResizeAttr.tAspectRatio.tRect.nX = 0;
    tCropResizeAttr.tAspectRatio.tRect.nY = 0;
    tCropResizeAttr.tAspectRatio.tRect.nW = 640;
    tCropResizeAttr.tAspectRatio.tRect.nH = 360;
    tDstFrame.u32PicStride[0] = 1280;
    tDstFrame.u32Width = 1280;
    tDstFrame.u32Height = 360;
    tDstFrame.stCompressInfo.enCompressMode = 2;
    tDstFrame.stCompressInfo.u32CompressLevel = 4;
#else
    tCropResizeAttr.tAspectRatio.eMode = AX_IVPS_ASPECT_RATIO_STRETCH;
    tCropResizeAttr.tAspectRatio.eAligns[0] = AX_IVPS_ASPECT_RATIO_HORIZONTAL_CENTER;
    tCropResizeAttr.tAspectRatio.eAligns[1] = AX_IVPS_ASPECT_RATIO_VERTICAL_CENTER;
    tCropResizeAttr.tAspectRatio.nBgColor = 0x0000FF;
    tDstFrame.u32PicStride[0] = 1920;
    tDstFrame.u32Width = 1920;
    tDstFrame.u32Height = 1080;
#endif

    while (!ThreadLoopStateGet())
    {
        sleep(1);
        ret = AX_IVPS_GetChnFrame(pThis->nIvpsGrp, pThis->nIvpsChn, &tSrcFrame, -1);
        if (ret)
        {
            /* reach EOF */
            printf("[WARN] CHN[%d] is empty ret:0x%x\n", pThis->nIvpsChn, ret);
            continue;
        }

        printf("AX_IVPS_GetChnFrame(%lld): Chn:%d, (%d x %d) Stride:%d, Phy:%llx, UserData:%llx, PTS:%llx, BlockId:%x\n",
               tSrcFrame.u64SeqNum, pThis->nIvpsChn, tSrcFrame.u32Width, tSrcFrame.u32Height, tSrcFrame.u32PicStride[0],
               tSrcFrame.u64PhyAddr[0], tSrcFrame.u64UserData, tSrcFrame.u64PTS, tSrcFrame.u32BlkId[0]);
        tSrcFrame.s16CropWidth = 1920;
        tSrcFrame.s16CropHeight = 1080;
        tDstFrame.enImgFormat = tSrcFrame.enImgFormat;

        printf("FBC:%d", tSrcFrame.stCompressInfo.enCompressMode);
        nImgSize = CalcImgSize(tDstFrame.u32PicStride[0], tDstFrame.u32Width,
                               tDstFrame.u32Height, tDstFrame.enImgFormat, 16);
        ret = BufPoolBlockAddrGet(-1, nImgSize, &tDstFrame.u64PhyAddr[0], (AX_VOID **)(&tDstFrame.u64VirAddr[0]), &BlkId);
        if (ret)
        {
            ALOGE("Alloc BlkId fail, ret=0x%x", ret);
            goto ERR1;
        }
        AX_IVPS_CropResizeVpp(&tSrcFrame, &tDstFrame, &tCropResizeAttr);
        SaveFileExt(&tDstFrame, pThis->nIvpsGrp, pThis->nIvpsChn, ".", "CropResize",
                    tSrcFrame.s16CropWidth, tSrcFrame.s16CropHeight);
        ret = AX_POOL_ReleaseBlock(BlkId);
        if (ret)
        {
            ALOGE("Rls BlkId fail, ret=0x%x", ret);
        }
    ERR1:
        ret = AX_IVPS_ReleaseChnFrame(pThis->nIvpsGrp, pThis->nIvpsChn, &tSrcFrame);
        if (ret)
        {
            ALOGE("AX_IVPS_ReleaseFrame fail, ret=0x%x", ret);
            return (AX_VOID *)-1;
        }

        ALOGI("AX_IVPS_GetFrame");
    }

    ALOGI("IVPS END");
    return (AX_VOID *)0;
}

/*
 * IVPS_CropResizeThreadStart()
 * IVPS frame send and get can be done separately in different threads.
 */
AX_S32 IVPS_CropResizeThreadStart(AX_S32 GrpId, AX_S32 ChnId)
{

    gSampleIvpsGrp.nIvpsGrp = GrpId;
    gSampleIvpsGrp.nIvpsChn = ChnId;
    if (0 != pthread_create(&gSampleIvpsGrp.crop_resize_tid, NULL, IVPS_CropResizeThread, &gSampleIvpsGrp))
    {
        gSampleIvpsGrp.crop_resize_tid = 0;
        return -1;
    }

    return 0;
}

AX_S32 IVPS_CropResizeThreadStop(AX_VOID)
{
    if (gSampleIvpsGrp.crop_resize_tid)
    {
        pthread_join(gSampleIvpsGrp.crop_resize_tid, NULL);
        gSampleIvpsGrp.crop_resize_tid = 0;
    }
    return 0;
}