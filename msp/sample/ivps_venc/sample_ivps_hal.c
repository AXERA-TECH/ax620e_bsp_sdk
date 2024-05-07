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

static void FrameInfoGet(SAMPLE_IMAGE_INFO_T tImage, AX_VIDEO_FRAME_T *ptFrame)
{
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

    return;
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
static volatile AX_BOOL bThreadLoopExit = AX_FALSE;
static volatile AX_BOOL bFrmReadFinish = AX_FALSE;
static AX_U64 totalFrames = 0;
static SAMPLE_IVPS_GRP_T gSampleIvpsGrp = {0};

AX_VOID ThreadLoopStateSet(AX_BOOL bValue)
{
    bThreadLoopExit = bValue;
}

AX_BOOL ThreadLoopStateGet(AX_VOID)
{
    return bThreadLoopExit;
}

AX_U64 SendFrameNumGet(AX_VOID)
{
    return totalFrames;
}

AX_VOID SendFrameNumUpdate(AX_U64 val)
{
    totalFrames = val;
}

AX_BOOL SendFrmStateGet(AX_VOID)
{
    return bFrmReadFinish;
}

AX_VOID SendFrmStateSet(AX_BOOL bValue)
{
    bFrmReadFinish = bValue;
}

AX_S32 IVPS_ReadFile(FILE *pFileIn, AX_S32 widthSrc, AX_S32 strideSrc, AX_S32 heightSrc, AX_IMG_FORMAT_E eFmt,
                            AX_VOID *pVaddr)
{
    AX_U32 i, rows, realRead, readSize;

    if (!pFileIn)
        return -1;

    if (!pVaddr)
        return -1;

    readSize = 0;

    switch (eFmt) {
    case AX_FORMAT_YUV420_PLANAR:
        rows = heightSrc;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, strideSrc, pFileIn);
            if (realRead < strideSrc)
                break;
            readSize += realRead;
            pVaddr += strideSrc;
        }
        rows = heightSrc;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, strideSrc >> 1, pFileIn);
            if (realRead < (strideSrc >> 1))
                break;
            readSize += realRead;
            pVaddr += (strideSrc >> 1);
        }
        break;
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
        rows = heightSrc * 3 / 2;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, strideSrc, pFileIn);
            if (realRead < strideSrc)
                break;
            readSize += realRead;
            pVaddr += strideSrc;
        }
        break;
    case AX_FORMAT_YUV422_INTERLEAVED_YUYV:
    case AX_FORMAT_YUV422_INTERLEAVED_UYVY:
        rows = heightSrc;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, strideSrc, pFileIn);
            if (realRead < strideSrc)
                break;
            readSize += realRead;
            pVaddr += strideSrc;
        }
        break;
    case AX_FORMAT_YUV420_PLANAR_10BIT_I010:
        rows = heightSrc;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, strideSrc, pFileIn);
            if (realRead < strideSrc)
                break;
            readSize += realRead;
            pVaddr += strideSrc;
        }
        rows = heightSrc;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, strideSrc >> 1, pFileIn);
            if (realRead < (strideSrc >> 1))
                break;
            readSize += realRead;
            pVaddr += (strideSrc >> 1);
        }
        break;
    case AX_FORMAT_YUV420_SEMIPLANAR_10BIT_P010:
        rows = heightSrc * 3 / 2;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, strideSrc, pFileIn);
            if (realRead < strideSrc)
                break;
            readSize += realRead;
            pVaddr += strideSrc;
        }
        break;
    default:
        ALOGI2("Invalid format, eFmt = %d\n", eFmt);
    }

    return readSize;
}

AX_VOID *IVPS_SendFrameThread(AX_VOID *pArg)
{
    SAMPLE_IVPS_GRP_T *pstArg = (SAMPLE_IVPS_GRP_T *)pArg;
    AX_S32 loopNum = 1;
    AX_S32 encFrmNum = pstArg->encFrmNum;
    const AX_CHAR *fileInput = pstArg->pFileName;
    AX_IMG_FORMAT_E eFmt = pstArg->tFrameInput.enImgFormat;
    AX_U32 width = pstArg->tFrameInput.u32Width;
    AX_U32 height = pstArg->tFrameInput.u32Height;
    AX_U32 strideY = pstArg->tFrameInput.u32PicStride[0];
    AX_U32 strideU = eFmt == AX_FORMAT_YUV420_PLANAR ? strideY / 2 : strideY;
    AX_VIDEO_FRAME_T stFrame;
    AX_S32 readSize;
    AX_S32 s32Ret;
    AX_S32 frameSize = pstArg->tFrameInput.u32FrameSize;
    AX_S32 poolId = pstArg->nPoolId;
    FILE *fFileIn = NULL;
    AX_BLK blkId = AX_INVALID_BLOCKID;
    AX_S32 totalInputFrames = 0;

    memset(&stFrame, 0, sizeof(stFrame));
    ALOGI2("+++IVPS Grp: %d", pstArg->nIvpsGrp);

    fFileIn = fopen(fileInput, "rb");
    if (fFileIn == NULL) {
        ALOGE("ivps grp-%d: Open input file %s error!\n", pstArg->nIvpsGrp, fileInput);
        return NULL;
    }

    while (!ThreadLoopStateGet()) {
        /* get block from user pool */
        blkId = AX_POOL_GetBlock(poolId, frameSize, NULL);
        if (AX_INVALID_BLOCKID == blkId) {
            usleep(5000);
            continue;
        }

        stFrame.u32FrameSize = frameSize;
        stFrame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(blkId);
        stFrame.u64VirAddr[0] = (AX_ULONG)AX_POOL_GetBlockVirAddr(blkId);
        stFrame.u32BlkId[0] = blkId;
        stFrame.u32BlkId[1] = 0;
        stFrame.u32BlkId[2] = 0;
        /* read frame data from yuv file */
        readSize = IVPS_ReadFile(fFileIn, width, strideY, height, eFmt, (void *)(AX_ULONG)stFrame.u64VirAddr[0]);
        if (readSize <= 0)
            ALOGI2("ivps grp-%d: file finished, loopNum %d\n", pstArg->nIvpsGrp, loopNum);

        if (feof(fFileIn)) {
            if (totalInputFrames < encFrmNum) {
                fseek(fFileIn, 0, SEEK_SET);
                IVPS_ReadFile(fFileIn,  width, strideY, height, eFmt,
                              (void *)(AX_ULONG)stFrame.u64VirAddr[0]);
                loopNum++;
            } else {
                ALOGI2("ivps grp-%d: End of input file!\n", pstArg->nIvpsGrp);
                /* no more frames, stop encoder */
                goto EXIT;
            }
        }

        stFrame.u64SeqNum = totalInputFrames + 1;
        stFrame.u64PTS = GetTickCount();
        stFrame.enImgFormat = eFmt;
        stFrame.u32Width = width;
        stFrame.u32Height = height;
        stFrame.u32PicStride[0] = strideY;
        stFrame.u32PicStride[1] = strideU;
        stFrame.u32PicStride[2] = strideU;

        s32Ret = AX_IVPS_SendFrame(pstArg->nIvpsGrp, &stFrame, -1);
        if (IVPS_SUCC != s32Ret) {
            ALOGE("AX_IVPS_SendFrame(Grp:%d) failed, ret=0x%x.", pstArg->nIvpsGrp, s32Ret);
            sleep(1);
            continue;
        }

        usleep(20000);

        totalInputFrames++;

        if (totalInputFrames == encFrmNum) {
            ALOGI2("ipvs grp-%d: Want to encode %d frames, exit!\n", pstArg->nIvpsGrp, totalInputFrames);
            goto EXIT;
        }

        if (AX_INVALID_BLOCKID != blkId)
            AX_POOL_ReleaseBlock(blkId);
    }

EXIT:

    if (NULL != fFileIn) {
        fclose(fFileIn);
        fFileIn = NULL;
    }

    if (AX_INVALID_BLOCKID != blkId)
        AX_POOL_ReleaseBlock(blkId);

    SendFrameNumUpdate(totalInputFrames);
    SendFrmStateSet(AX_TRUE);

    ALOGI2("ivps grp-%d - Total input %d frames, Encoder exit!\n", pstArg->nIvpsGrp, totalInputFrames);

    return NULL;
}
/* IVPS frame send and get can be done separately in different threads */
static AX_S32 SAMPLE_IVPS_ThreadStart(AX_VOID *src)
{
    pthread_t tid = 0;
    if (src) {
        if (0 != pthread_create(&tid, NULL, IVPS_SendFrameThread, src)) {
            return -1;
        }
        pthread_detach(tid);
    }
    return 0;
}

/* Send frame without VIN */
AX_S32 SAMPLE_IVPS_SendFrame(AX_S32 nIvpsGrp, SAMPLE_IMAGE_INFO_T tImage)
{
    int nRet;

    SAMPLE_IVPS_GRP_T *pGrp = &gSampleIvpsGrp;
    pGrp->nIvpsGrp = nIvpsGrp;
    pGrp->pFileName = tImage.pImgFile;
    pGrp->nPoolId = tImage.nPoolId;
    pGrp->encFrmNum = tImage.encFrmNum;

    FrameInfoGet(tImage, &pGrp->tFrameInput);

    nRet = SAMPLE_IVPS_ThreadStart(pGrp);
    if (0 != nRet) {
        ALOGE("SAMPLE_IVPS_ThreadStart error. ret=%d", nRet);
        return -3;
    }
    return 0;
}
