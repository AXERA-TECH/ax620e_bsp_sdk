/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include "ax_venc_api.h"
#include "ax_ivps_api.h"

#define SAMPLE_LOG(str, arg...)    \
    do {    \
        printf("%s:%d "str"\n", __func__, __LINE__, ##arg); \
    } while(0)

#define SAMPLE_ERR_LOG(str, arg...)   \
    do{  \
        printf("%s:%d Error! "str"\n", __func__, __LINE__, ##arg); \
    } while(0)

//#define SAMPLE_IVPS_DEBUG

#define JENC_NUM_COMM 64
#define MAX_HEIGHT_DEFAULT 16384
#define MAX_WIDTH_DEFAULT 16384
#define MAX_PATH   256

#define ALIGN_DOWN(x,align)  (((x) / (align)) * (align))
#define ALIGN_UP(x,align)  ((((x) +(align) - 1) / (align)) * (align))
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))

typedef struct _SAMPLE_JENC_ENCODE_PARA
{
    AX_BOOL bThreadStart;
    VENC_CHN VeChn;
    AX_IMG_FORMAT_E enFrameFormat;
} SAMPLE_JENC_ENCODE_PARA_T;

typedef struct _SAMPLE_JENC_GETSTREAM_PARA
{
    AX_BOOL bThreadStart;
    VENC_CHN VeChn;
} SAMPLE_JENC_GETSTREAM_PARA_T;

static AX_S32 gLoopExit = 0;
static AX_S32 gLoopEncode = 0;
static AX_S32 gEncodeFrmNum = 1;
static AX_S32 gWriteToFile = 1;
static SAMPLE_JENC_ENCODE_PARA_T gEncodePara[JENC_NUM_COMM];
static pthread_t gEncodePid[JENC_NUM_COMM];
static SAMPLE_JENC_GETSTREAM_PARA_T gGetStreamPara[JENC_NUM_COMM];
static pthread_t gGetStreamPid[JENC_NUM_COMM];
static AX_U32 gSrcWidth = 0;
static AX_U32 gSrcHeight = 0;
static AX_U32 gDstWidth = 0;
static AX_U32 gDstHeight = 0;
static AX_U32 gJencChnNum = 1;
static AX_U32 gSliceNum = 1;
static AX_U32 gSliceHeight = 512;
static AX_CHAR gFileInput[MAX_PATH];

AX_VOID SaveFileExt(AX_VIDEO_FRAME_T *tDstFrame, AX_S32 nGrpIdx, AX_S32 nChnIdx, char *pFilePath, char *pFileName)
{
    AX_U32 nPixelSize;
    AX_S32 s32Ret1 = 0;
    AX_S32 s32Ret2 = 0;
    AX_S32 s32Ret3 = 0;
    AX_U8 nStoragePlanarNum = 0;
    char szOutImgFile[128] = { 0 };

    nPixelSize = (AX_U32)tDstFrame->u32PicStride[0] * tDstFrame->u32Height;

    switch (tDstFrame->enImgFormat)
    {
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
    case AX_FORMAT_YUV420_PLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR:
        nStoragePlanarNum = 2;
        break;
    case AX_FORMAT_YUV422_INTERLEAVED_YUYV:
    case AX_FORMAT_YUV422_INTERLEAVED_UYVY:
        nStoragePlanarNum = 3;
        break;
    case AX_FORMAT_YUV444_PACKED:
    case AX_FORMAT_RGB888:
        nStoragePlanarNum = 1;
        break;
    case AX_FORMAT_RGBA8888:
        nStoragePlanarNum = 1;
        break;
    default:
        nStoragePlanarNum = 1;
        break;
    }

    printf("SaveFileExt nPixelSize: %d PhyAddr:%llx PhyAddr_UV:%llx\n", nPixelSize, tDstFrame->u64PhyAddr[0], tDstFrame->u64PhyAddr[1]);
    printf("PhyAddr:0x%x PhyAddr_UV:0x%x\n", (AX_U32)tDstFrame->u64PhyAddr[0], (AX_U32)tDstFrame->u64PhyAddr[1]);
    printf("VirAddr:0x%x VirAddr_UV:0x%x\n", (AX_U32)tDstFrame->u64VirAddr[0], (AX_U32)tDstFrame->u64VirAddr[1]);

    sprintf(szOutImgFile, "%s/%soutput_grp%d_chn%d_%dx%d.fmt_%x", pFilePath, pFileName, nGrpIdx, nChnIdx, tDstFrame->u32PicStride[0], tDstFrame->u32Height, tDstFrame->enImgFormat);
    FILE *fp = fopen(szOutImgFile, "wb");

    if (fp) {
        switch (nStoragePlanarNum) {
        case 2:
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize);
            tDstFrame->u64VirAddr[1] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[1], nPixelSize / 2);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize, fp);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[1]), 1, nPixelSize / 2, fp);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[1], nPixelSize / 2);
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
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize * 3);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize * 3, fp);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize * 3);
            break;
        }
        fclose(fp);
        printf("%s is saved!\n", szOutImgFile);
        if (s32Ret1 || s32Ret2 || s32Ret3) {
            printf("AX_SYS_Munmap failed,s32Ret1=0x%x ,s32Ret2=0x%x ,s32Ret2=0x%x\n", s32Ret1, s32Ret2, s32Ret3);
        }
    }
}

static int LoadFrameFromFile(FILE *pFileIn, AX_S32 widthSrc, AX_S32 *strideSrc,
                            AX_S32 heightSrc, AX_IMG_FORMAT_E eFmt, AX_VIDEO_FRAME_T *stFrame)
{
    AX_U64 pVaddr[3] = {0};
    AX_S32 stride[3] = {0};
    AX_S32 i, j, rows, realRead, readSize;

    if (!pFileIn)
        return -1;

    readSize = 0;
    for (i = 0; i < 3; i++) {
        pVaddr[i] = stFrame->u64VirAddr[i];
        stride[i] = strideSrc[i];
    }

    switch(eFmt) {
    case AX_FORMAT_YUV420_PLANAR:
        for (i = 0; i < 3; i++) {
            if (i == 0) {
                rows = heightSrc;
            } else {
                rows = heightSrc / 2;
            }
            for (j = 0; j < rows; j++) {
                realRead = fread((AX_CHAR *)pVaddr[i], 1, stride[i], pFileIn);
                if (realRead < stride[i]) {
                    break;
                }
                readSize += realRead;
                pVaddr[i] += stride[i];
            }
        }
        break;
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
        for (i = 0; i < 2; i++) {
            if (i == 0) {
                rows = heightSrc;
            } else {
                rows = heightSrc / 2;
            }
            for (j = 0; j < rows; j++) {
                realRead = fread((AX_CHAR *)pVaddr[i], 1, stride[i], pFileIn);
                if (realRead < stride[i]) {
                    break;
                }
                readSize += realRead;
                pVaddr[i] += stride[i];
            }
        }
        break;
    case AX_FORMAT_YUV422_INTERLEAVED_YUYV:
    case AX_FORMAT_YUV422_INTERLEAVED_UYVY:
        rows = heightSrc;
        for (i = 0; i < rows; i++) {
            realRead = fread(pVaddr, 1, stride[0], pFileIn);
            if (realRead < widthSrc) {
                break;
            }
            readSize += realRead;
            pVaddr[0] += stride[0];
        }
        break;
    default:
        SAMPLE_ERR_LOG("invalid format, eFmt = %d\n", eFmt);
    }

    return readSize;
}

/* get stream thread */
static void *JpegencGetStreamProc(void *arg)
{
    AX_S32 s32Ret = -1;
    SAMPLE_JENC_GETSTREAM_PARA_T *pstPara;
    pstPara = (SAMPLE_JENC_GETSTREAM_PARA_T *)arg;
    AX_VENC_STREAM_T stStream;
    AX_U64 timeEndFrame = 0;
    struct timeval timeFrameEnd;
    AX_U64 totalGetFrames = 0;
    AX_CHAR esName[50] = { 0 };
    FILE *fOut = NULL;

    memset(&stStream, 0, sizeof(AX_VENC_STREAM_T));

    while (AX_TRUE == pstPara->bThreadStart) {

        s32Ret = AX_VENC_GetStream(pstPara->VeChn, &stStream, -1);
        switch (s32Ret) {
        case AX_SUCCESS:
            gettimeofday(&timeFrameEnd, NULL);

            timeEndFrame = timeFrameEnd.tv_sec * 1000000 + timeFrameEnd.tv_usec;

            SAMPLE_LOG("Encoded jpeg cost time(us %lld HW +SW), pts %lld, seq %lld",
                       timeEndFrame - stStream.stPack.u64PTS, stStream.stPack.u64PTS, stStream.stPack.u64SeqNum);

            if (gWriteToFile) {
                sprintf(esName, "./jenc_chn%d_frame%lld.jpg", pstPara->VeChn, stStream.stPack.u64SeqNum);

                fOut = fopen(esName, "wb");
                if (fOut == NULL) {
                    SAMPLE_ERR_LOG("ChnId:%d: open output file error!\n", pstPara->VeChn);
                } else {
                    /* save encode data */
                    fwrite(stStream.stPack.pu8Addr, 1, stStream.stPack.u32Len, fOut);
                    fflush(fOut);
                    fclose(fOut);
                    fOut = NULL;
                }
            }

            s32Ret = AX_VENC_ReleaseStream(pstPara->VeChn, &stStream);
            if (AX_SUCCESS != s32Ret) {
                SAMPLE_ERR_LOG("ChnId:%d: AX_JENC_ReleaseStream failed!\n", pstPara->VeChn);
                break;
            }

            totalGetFrames++;
            if (totalGetFrames >= gEncodeFrmNum && gEncodeFrmNum > 0) {
                SAMPLE_LOG("Want to get %u frames, exit!\n", gEncodeFrmNum);
                goto EXIT;
            }

            break;
        case AX_ERR_VENC_FLOW_END:
            SAMPLE_LOG("ChnId:%d: getStream thread exit.\n", pstPara->VeChn);
            /* end of stream, getStream exit. */
            goto EXIT;
            break;
        case AX_ERR_VENC_BUF_EMPTY:
        case AX_ERR_VENC_TIMEOUT:
            SAMPLE_ERR_LOG("ChnId:%d: error type 0x%x.\n", pstPara->VeChn, s32Ret);
            break;
        default:
            SAMPLE_ERR_LOG("ChnId:%d: error type 0x%x.\n", pstPara->VeChn, s32Ret);
            goto EXIT;
        }
    }

EXIT:

    SAMPLE_LOG("ChnId:%d: GetStreamProc exit!Total get %lld frames.", pstPara->VeChn, totalGetFrames);
    gLoopExit = 1;

    return (void *)(intptr_t)s32Ret;
}

/* encode thread */
static void *JpegencEncodeProc(void *arg)
{
    AX_S32 s32Ret = 0;
    AX_S32 i = 0;
    AX_U64 totalEncodedFrames = 0;
    AX_U32 frameSize = 0;
    struct timeval timeFrameStart;
    SAMPLE_JENC_ENCODE_PARA_T *pEncodePara = (SAMPLE_JENC_ENCODE_PARA_T *)arg;
    AX_VENC_RECV_PIC_PARAM_T stRecvParam;
    AX_VIDEO_FRAME_INFO_T stFrame;
    AX_VIDEO_FRAME_T tSrcFrame = {0}, tDstFrame = { 0 };
    AX_U64 baseSrcFramePhyAddr_Y = 0;
    AX_U64 baseSrcFramePhyAddr_UV = 0;
     AX_IVPS_CROP_RESIZE_ATTR_T tCropResizeAttr = { 0 };
    AX_U32 SrcFrameOffset;
    AX_BLK inBlkId = AX_INVALID_BLOCKID;
    AX_BLK outBlkId = AX_INVALID_BLOCKID;
    FILE *fFileIn = NULL;
#ifdef SAMPLE_IVPS_DEBUG
    AX_CHAR sliceFileName[50] = { 0 };
#endif

    fFileIn = fopen((AX_CHAR *)gFileInput, "rb");

    if (fFileIn == NULL) {
        SAMPLE_ERR_LOG("ChnId:%d: open input file error!\n", pEncodePara->VeChn);
        return NULL;
    }

    s32Ret = AX_VENC_StartRecvFrame(pEncodePara->VeChn, &stRecvParam);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("Encoder thread exit, ret=%x\n", s32Ret);
        goto EXIT;
    }

    while (pEncodePara->bThreadStart) {

        /* step1:get a block to save input yuv */

        tSrcFrame.enImgFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        tSrcFrame.u32Width = gSrcWidth;
        tSrcFrame.u32Height = gSrcHeight;
        tSrcFrame.u32PicStride[0] = tSrcFrame.u32Width;
        tSrcFrame.u32PicStride[1] = tSrcFrame.u32Width;
        tSrcFrame.u32PicStride[2] = 0;

        /* AX_FORMAT_YUV420_SEMIPLANAR */
        frameSize = tSrcFrame.u32Width * tSrcFrame.u32Height * 3 / 2;

        inBlkId = AX_POOL_GetBlock(AX_INVALID_POOLID, frameSize, NULL);
        if (AX_INVALID_POOLID == inBlkId) {
            SAMPLE_ERR_LOG("Get block fail.\n");
            goto EXIT;
        }

        tSrcFrame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(inBlkId);
        tSrcFrame.u64VirAddr[0] = (AX_U64)AX_POOL_GetBlockVirAddr(inBlkId);

        /* AX_FORMAT_YUV420_SEMIPLANAR */
        tSrcFrame.u64PhyAddr[1] = tSrcFrame.u64PhyAddr[0] + tSrcFrame.u32PicStride[0] * tSrcFrame.u32Height;
        tSrcFrame.u64PhyAddr[2] = 0;
        tSrcFrame.u64VirAddr[1] = tSrcFrame.u64VirAddr[0] + tSrcFrame.u32PicStride[0] * tSrcFrame.u32Height;
        tSrcFrame.u64VirAddr[2] = 0;

        baseSrcFramePhyAddr_Y = tSrcFrame.u64PhyAddr[0];
        baseSrcFramePhyAddr_UV = tSrcFrame.u64PhyAddr[1];

        /* read frame data from yuv file */
        LoadFrameFromFile(fFileIn, tSrcFrame.u32Width, (AX_S32 *)tSrcFrame.u32PicStride,
                                    tSrcFrame.u32Height, tSrcFrame.enImgFormat,
                                    &tSrcFrame);

        if (feof(fFileIn)) {
            if (gLoopEncode) {
                fseek(fFileIn, 0, SEEK_SET);
            } else {
                SAMPLE_LOG("ChnId:%d: End of input file!\n", pEncodePara->VeChn);
                goto EXIT;
            }
        }

        tDstFrame.enImgFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        tDstFrame.u32Width = gDstWidth;
        tDstFrame.u32Height = gDstHeight;
        tDstFrame.u32PicStride[0] = tDstFrame.u32Width;
        tDstFrame.u32PicStride[1] = tDstFrame.u32Width;
        tDstFrame.u32PicStride[2] = 0;

        tDstFrame.u32Height = gSliceHeight;
        tSrcFrame.u32Height = ALIGN_DOWN(tSrcFrame.u32Height * gSliceHeight / gDstHeight, 2);

        SAMPLE_LOG("gSliceNum=%d,Src SliceHeight=%d,Dst SliceHeight=%d\n", gSliceNum, tSrcFrame.u32Height, gSliceHeight);

        gettimeofday(&timeFrameStart, NULL);

        for (i = 0; i < gSliceNum; i++)
        {
            /* step2:get a block to save output yuv */
            frameSize = tDstFrame.u32Width * tDstFrame.u32Height * 3 / 2;
            do {
                outBlkId = AX_POOL_GetBlock(AX_INVALID_POOLID, frameSize, NULL);
                if (AX_INVALID_BLOCKID == outBlkId) {
                    //SAMPLE_ERR_LOG("Get outBlock fail,try next time.\n");
                } else {
                    tDstFrame.u32BlkId[0] = outBlkId;
                    tDstFrame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(outBlkId);
                    tDstFrame.u64VirAddr[0] = (AX_U64)AX_POOL_GetBlockVirAddr(outBlkId);

                    /* AX_FORMAT_YUV420_SEMIPLANAR */
                    tDstFrame.u64PhyAddr[1] = tDstFrame.u64PhyAddr[0] + tDstFrame.u32PicStride[0] * tDstFrame.u32Height;
                    tDstFrame.u64PhyAddr[2] = 0;
                    tDstFrame.u64VirAddr[1] = tDstFrame.u64VirAddr[0] + tDstFrame.u32PicStride[0] * tDstFrame.u32Height;
                    tDstFrame.u64VirAddr[2] = 0;
                }
            } while(AX_INVALID_BLOCKID == outBlkId);

            SrcFrameOffset = tSrcFrame.u32PicStride[0] * tSrcFrame.u32Height * i;
            tSrcFrame.u64PhyAddr[0] = baseSrcFramePhyAddr_Y + SrcFrameOffset;
            tSrcFrame.u64PhyAddr[1] = baseSrcFramePhyAddr_UV + (SrcFrameOffset >> 1);
            tSrcFrame.u64PhyAddr[2] = 0;

#ifdef SAMPLE_IVPS_DEBUG
            SAMPLE_LOG("Src: stride:%d width:%d height:%d\n", tSrcFrame.u32PicStride[0], tSrcFrame.u32Width, tSrcFrame.u32Height);
            SAMPLE_LOG("Dst: stride:%d width:%d height:%d\n", tDstFrame.u32PicStride[0], tDstFrame.u32Width, tDstFrame.u32Height);
            SAMPLE_LOG("Src: inBlkId:0x%x Yaddr:%llx UVaddr:%llx\n", inBlkId, tSrcFrame.u64PhyAddr[0], tSrcFrame.u64PhyAddr[1]);
            SAMPLE_LOG("Dst: outBlkId:0x%x Yaddr:%llx UVaddr:%llx\n", outBlkId, tDstFrame.u64PhyAddr[0], tDstFrame.u64PhyAddr[1]);
#endif

            tCropResizeAttr.tAspectRatio.eMode = AX_IVPS_ASPECT_RATIO_STRETCH;
            AX_IVPS_CropResizeTdp(&tSrcFrame, &tDstFrame, &tCropResizeAttr);

#ifdef SAMPLE_IVPS_DEBUG
            sprintf(sliceFileName, "CropResizeSrcSlice%d_", i);
            SaveFileExt(&tSrcFrame, 0, 0, "./", sliceFileName);
            sprintf(sliceFileName, "CropResizeDstSlice%d_", i);
            SaveFileExt(&tDstFrame, 0, 0, "./", sliceFileName);
#endif

            tDstFrame.u64PTS = timeFrameStart.tv_sec * 1000000 + timeFrameStart.tv_usec;
            tDstFrame.u64SeqNum = totalEncodedFrames + 1;

            memset(&stFrame, 0, sizeof(stFrame));

            stFrame.stVFrame = tDstFrame;
            /* config crop param!!! */
            stFrame.stVFrame.u32Height = gDstHeight;
            stFrame.stVFrame.s16CropX = 0;
            stFrame.stVFrame.s16CropY = 0;
            stFrame.stVFrame.s16CropHeight = gDstHeight;
            stFrame.stVFrame.s16CropWidth = gDstWidth;

            /* send slice data to jpeg using blocking mode */
            s32Ret = AX_VENC_SendFrame(pEncodePara->VeChn, &stFrame, -1);

            if (AX_SUCCESS != s32Ret) {
                SAMPLE_ERR_LOG("AX_VENC_SendFrame failed, ret=0x%x\n", s32Ret);

                s32Ret = AX_POOL_ReleaseBlock(outBlkId);
                if (s32Ret){
                    SAMPLE_ERR_LOG("ChnId:%d: AX_POOL_ReleaseBlock failed, ret=0x%x\n", pEncodePara->VeChn, s32Ret);
                }
                goto EXIT;
            }

            s32Ret = AX_POOL_ReleaseBlock(outBlkId);
            if (s32Ret){
                SAMPLE_ERR_LOG("ChnId:%d: AX_POOL_ReleaseBlock failed, ret=0x%x\n", pEncodePara->VeChn, s32Ret);
                goto EXIT;
            }
        }

        totalEncodedFrames++;

        if (totalEncodedFrames >= gEncodeFrmNum && gEncodeFrmNum > 0) {
            SAMPLE_LOG("Want to encode %u frames, exit!\n", gEncodeFrmNum);
            goto EXIT;
        }

        s32Ret = AX_POOL_ReleaseBlock(inBlkId);
        if (s32Ret) {
            SAMPLE_ERR_LOG("ChnId:%d: AX_POOL_ReleaseBlock failed, ret=0x%x\n", pEncodePara->VeChn, s32Ret);
        } else {
            SAMPLE_LOG("ChnId:%d: AX_POOL_ReleaseBlock inBlkId=0x%x\n", pEncodePara->VeChn, inBlkId);
        }
    }

EXIT:
    if (AX_INVALID_BLOCKID != inBlkId) {
        AX_POOL_ReleaseBlock(inBlkId);
    }

    if (NULL != fFileIn) {
        fclose(fFileIn);
        fFileIn = NULL;
    }

    SAMPLE_LOG("Chn %d - Total encode %llu frames, Encoder exit!\n", pEncodePara->VeChn, totalEncodedFrames);

    return (void *)(intptr_t)s32Ret;
}

static AX_S32 SampleCommPoolInit()
{
    AX_POOL_FLOORPLAN_T PoolFloorPlan;
    AX_S32 s32Ret;

    memset(&PoolFloorPlan, 0, sizeof(AX_POOL_FLOORPLAN_T));
    PoolFloorPlan.CommPool[0].MetaSize   = 0x1000;
    PoolFloorPlan.CommPool[0].BlkSize   = gSrcHeight * gSrcWidth * 3 / 2;
    PoolFloorPlan.CommPool[0].BlkCnt    = 2 * gJencChnNum;
    PoolFloorPlan.CommPool[0].CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    PoolFloorPlan.CommPool[1].MetaSize   = 0x1000;
    PoolFloorPlan.CommPool[1].BlkSize   = gSliceHeight * gDstWidth * 3 / 2;
    PoolFloorPlan.CommPool[1].BlkCnt    = 2 * gJencChnNum * gSliceNum;
    PoolFloorPlan.CommPool[1].CacheMode = AX_POOL_CACHE_MODE_NONCACHE;

    memset(PoolFloorPlan.CommPool[0].PartitionName, 0 ,sizeof(PoolFloorPlan.CommPool[0].PartitionName));
    strcpy((char *)PoolFloorPlan.CommPool[0].PartitionName, "anonymous");

    s32Ret = AX_POOL_SetConfig(&PoolFloorPlan);
    if (s32Ret) {
        SAMPLE_ERR_LOG("Create common pool err! BlkSize:%lld,BlkCnt:%d.\n",
                       PoolFloorPlan.CommPool[0].BlkSize, PoolFloorPlan.CommPool[0].BlkCnt);
        return -1;
    }

    s32Ret = AX_POOL_Init();
    if(s32Ret){
        SAMPLE_ERR_LOG("AX_POOL_Init fail!!ret:0x%X\n", s32Ret);
        return -1;
    }

    SAMPLE_LOG("Create common pool success! BlkSize:%lld,BlkCnt:%d.\n",
               PoolFloorPlan.CommPool[0].BlkSize, PoolFloorPlan.CommPool[0].BlkCnt);
    return 0;
}

static AX_S32 SampleJencStart()
{
    AX_S32 s32Ret, s32Retry = 5;
    AX_U32 cid;
    AX_VENC_JPEG_PARAM_T stJpegParam;
    AX_VENC_CHN_ATTR_T stVencChnAttr;

    for (cid = 0; cid < gJencChnNum; cid++) {
        /* JENC channel arams */

        memset(&stVencChnAttr, 0, sizeof(stVencChnAttr));

        stVencChnAttr.stVencAttr.enType = PT_JPEG;
        stVencChnAttr.stVencAttr.u32MaxPicHeight = MAX_HEIGHT_DEFAULT;
        stVencChnAttr.stVencAttr.u32MaxPicWidth = MAX_WIDTH_DEFAULT;
        stVencChnAttr.stVencAttr.enLinkMode = AX_UNLINK_MODE;
        stVencChnAttr.stVencAttr.u8InFifoDepth = 4;
        stVencChnAttr.stVencAttr.u8OutFifoDepth = 4;
        stVencChnAttr.stVencAttr.u32PicWidthSrc = gDstWidth;
        stVencChnAttr.stVencAttr.u32PicHeightSrc = gDstHeight;
        stVencChnAttr.stVencAttr.u32BufSize = gDstWidth * gDstHeight * 2;

        stVencChnAttr.stVencAttr.u32SliceNum = gSliceNum;

        s32Ret = AX_VENC_CreateChn(cid, &stVencChnAttr);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_ERR_LOG("AX_JENC_CreateChn:%d failed!s32Ret=0x%x\n", cid, s32Ret);
            goto END;
        }

        memset(&stJpegParam, 0, sizeof(stJpegParam));
        s32Ret = AX_VENC_GetJpegParam(cid, &stJpegParam);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_ERR_LOG("AX_VENC_GetJpegParam:%d failed!\n", cid);
            goto END;
        }

        stJpegParam.u32Qfactor = 90;

        s32Ret = AX_VENC_SetJpegParam(cid, &stJpegParam);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_ERR_LOG("AX_VENC_SetJpegParam:%d failed!\n", cid);
            goto END;
        }

        /* init frame/stream buffer parameters */
        gEncodePara[cid].bThreadStart = AX_TRUE;
        gEncodePara[cid].VeChn = cid;
        gEncodePara[cid].enFrameFormat = AX_FORMAT_YUV420_SEMIPLANAR;

        gGetStreamPara[cid].bThreadStart = AX_TRUE;
        gGetStreamPara[cid].VeChn = cid;

        /* create get output stream thread */
        pthread_create(&gGetStreamPid[cid], NULL, JpegencGetStreamProc, (void *)&gGetStreamPara[cid]);
        pthread_create(&gEncodePid[cid], NULL, JpegencEncodeProc, (void *)&gEncodePara[cid]);
    }

    while (!gLoopExit) {
        sleep(2);
    }

END:
    /* release encoder resource */
    for (cid = 0; cid < gJencChnNum; cid++) {
        if (AX_TRUE == gEncodePara[cid].bThreadStart) {
            gEncodePara[cid].bThreadStart = AX_FALSE;
            pthread_join(gEncodePid[cid], NULL);
        }

        AX_VENC_StopRecvFrame(cid);

        s32Retry = 5;
        do {
            s32Ret = AX_VENC_DestroyChn(cid);
            if (AX_ERR_VENC_BUSY == s32Ret) {
                SAMPLE_ERR_LOG("VencChn %d:AX_VENC_DestroyChn return AX_ERR_VENC_BUSY,retry...", cid);
                --s32Retry;
                usleep(100 * 1000);
            } else {
                break;
            }
        } while (s32Retry >= 0);

        if (s32Retry == -1 || AX_SUCCESS != s32Ret) {
            SAMPLE_ERR_LOG("VencChn %d: AX_VENC_DestroyChn failed, s32Retry=%d, s32Ret=0x%x\n", cid, s32Retry, s32Ret);
        }

        SAMPLE_LOG("JencChn %d exit!\n", cid);
    }

    gLoopExit = 0;
    return AX_SUCCESS;
}

static void SigInt(AX_S32 sigNo)
{
    SAMPLE_LOG("Catch signal %d\n", sigNo);
    gLoopExit = 1;
}

static AX_VOID PrintHelp(char *testApp)
{
    printf("Usage:%s h for help\n\n", testApp);
    printf("\te.g: sample_ivps_jenc_slice -w 2688 -h 1520 -W 4608 -H 2592 -i nv12_2688x1520.yuv -j 1 -n 2\n\n");

    printf("\tw: width of src frame\n");
    printf("\th: height of src frame\n");
    printf("\tW: width of dst frame\n");
    printf("\tH: height of dst frame\n");
    printf("\ti: input yuv file path\n");
    printf("\tj: jenc channel count,default 1\n");
    printf("\tl: enable loop encode,0:disable 1:enable,default 0\n");
    printf("\tm: want to encode how many frames,default 1\n");
    printf("\tn: slice number,default 1,which means one full frame\n");
    printf("\ts: whether write output stream to file,0:don't write 1:write,default 1\n");

    exit(0);
}

int main(int argc, char *argv[])
{
    AX_S32 s32Ret = -1, ch;
    AX_S32 isExit = -1;
    AX_VENC_MOD_ATTR_T stModAttr = {
        .enVencType = AX_VENC_MULTI_ENCODER,
        .stModThdAttr.u32TotalThreadNum = 1,
        .stModThdAttr.bExplicitSched = AX_FALSE,
    };

    printf("sample_ivps_jenc_slice. Build at %s %s\n", __DATE__, __TIME__);

    signal(SIGINT, SigInt);

    if (argc < 2) {
        PrintHelp(argv[0]);
        exit(0);
    }

    while ((ch = getopt(argc, argv, "w:h:W:H:i:j:l:m:n:s:")) != -1) {
        isExit = 0;
        switch (ch) {
        case 'w':
            gSrcWidth = atoi(optarg);
            break;
        case 'h':
            gSrcHeight = atoi(optarg);
            break;
        case 'W':
            gDstWidth = atoi(optarg);
            break;
        case 'H':
            gDstHeight = atoi(optarg);
            break;
        case 'i':
            if (strlen(optarg) < MAX_PATH) {
                strcpy(gFileInput, optarg);
            } else {
                SAMPLE_ERR_LOG("strlen(optarg):%ld >= MAX_PATH:%d", strlen(optarg), MAX_PATH);
                isExit = 1;
            }
            break;
        case 'j':
            gJencChnNum = atoi(optarg);
            break;
        case 'l':
            gLoopEncode = atoi(optarg);
            break;
        case 'm':
            gEncodeFrmNum = atoi(optarg);
            break;
        case 'n':
            gSliceNum = atoi(optarg);
            break;
        case 's':
            gWriteToFile = atoi(optarg);
            break;
        default:
            isExit = 1;
            break;
        }
    }

    if (isExit) {
        PrintHelp(argv[0]);
        exit(0);
    }

    printf("input param:gSrcWidth=%d,gSrcHeight=%d,gDstHeight=%d,gDstWidth=%d,gJencChnNum=%d,gSliceNum=%d,gFileInput=%s\n",
           gSrcWidth, gSrcHeight, gDstHeight, gDstWidth, gJencChnNum, gSliceNum, gFileInput);

    /* TODO: param check */
    if (!gSrcWidth || !gSrcHeight || !gDstHeight || !gDstWidth || !gJencChnNum || !gSliceNum || !gEncodeFrmNum) {
        PrintHelp(argv[0]);
        exit(0);
    }

    if (gDstWidth >= 8192) {
        SAMPLE_ERR_LOG("IVPS CropResize not support gDstWidth=%d\n", gDstWidth);
        PrintHelp(argv[0]);
        exit(0);
    }

    /* slice height must 16 align */
    gSliceHeight = ALIGN_UP(DIV_ROUND_UP(gDstHeight, gSliceNum), 16);

    s32Ret = AX_SYS_Init();
    if(s32Ret) {
        SAMPLE_ERR_LOG("AX_SYS_Init failed! ret:0x%x\n", s32Ret);
        goto SYS_DEINIT;
    }

    s32Ret = AX_POOL_Exit();
    if(s32Ret) {
        SAMPLE_ERR_LOG("AX_POOL_Exit failed! ret:0x%x\n", s32Ret);
        goto SYS_DEINIT;
    }

    s32Ret = SampleCommPoolInit();
    if(s32Ret) {
        SAMPLE_ERR_LOG("AX_POOL_Exit failed! ret:0x%x\n", s32Ret);
        goto SYS_DEINIT;
    }

    s32Ret = AX_IVPS_Init();
    if (s32Ret) {
        SAMPLE_ERR_LOG("AX_IVPS_Init failed! ret:0x%x\n", s32Ret);
        goto POOL_EXIT;
    }

    s32Ret = AX_VENC_Init(&stModAttr);
    if (s32Ret) {
        SAMPLE_ERR_LOG("AX_VENC_Init failed! ret:0x%x\n", s32Ret);
        goto IVPS_DEINIT;
    }

    s32Ret = SampleJencStart();
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("SampleJencStart failed! ret:0x%x\n", s32Ret);
        goto JENC_DEINIT;
    }

    s32Ret = AX_IVPS_Deinit();
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("AX_IVPS_Deinit failed! ret:0x%x\n", s32Ret);
    }

    s32Ret = AX_VENC_Deinit();
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("AX_VENC_Deinit failed! ret:0x%x\n", s32Ret);
    }

    s32Ret = AX_SYS_Deinit();
    if(s32Ret) {
        SAMPLE_ERR_LOG("AX_SYS_Deinit failed! ret:0x%x\n", s32Ret);
    }

    printf("sample_ivps_jenc_slice end success.\n");
    return 0;

JENC_DEINIT:
    AX_VENC_Deinit();

IVPS_DEINIT:
    AX_IVPS_Deinit();

POOL_EXIT:
    AX_POOL_Exit();

SYS_DEINIT:
    AX_SYS_Deinit();

    printf("sample_ivps_jenc_slice end failed.\n");
    return -1;
}
