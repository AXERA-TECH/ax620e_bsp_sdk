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

/*
 * AX_IVPS_CmmCopy()
 * Function: Move a piece of memory data.
 * Note: When copy, the nMemSize should be 64K Byte aligned, 256M maximum.
 */
static AX_S32 AX_IVPS_CmmCopy(IVPS_ENGINE_ID_E eEngineId, AX_U64 nSrcPhyAddr, AX_U64 nDstPhyAddr, AX_U64 nMemSize)
{
    AX_S32 ret = 0;

    switch (eEngineId)
    {
    case IVPS_ENGINE_ID_TDP:
        break;
    case IVPS_ENGINE_ID_VPP:
        break;
    case IVPS_ENGINE_ID_VGP:
        break;
    default:
        ret = -1;
        break;
    }

    if (ret)
    {
        ALOGE("AX_IVPS_CmmCopy fail, engine id:%d ret=0x%x", eEngineId, ret);
        return ret;
    }
    return 0;
}

/*
 * AX_IVPS_Csc()
 * Function: Color space conversion.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set. If format is AX_YUV420_SEMIPLANAR.
 */
static AX_S32 AX_IVPS_Csc(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrc, AX_VIDEO_FRAME_T *ptDst)
{
    AX_S32 ret = 0;

    switch (eEngineId)
    {
    case IVPS_ENGINE_ID_TDP:
        ret = AX_IVPS_CscTdp(ptSrc, ptDst);
        break;
    case IVPS_ENGINE_ID_VPP:
        /*  ret = AX_IVPS_CscVpp(ptSrc, ptDst); */
        break;
    case IVPS_ENGINE_ID_VGP:
        break;
    default:
        ret = -1;
        break;
    }

    if (ret)
    {
        ALOGE("AX_IVPS_Csc fail, engine id:%d ret=0x%x", eEngineId, ret);
        return ret;
    }
    return 0;
}

/*
 * AX_IVPS_CropResize
 * Function: Crop and Resize.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set.
 *       If crop is enabled, s16OffsetTop/s16OffsetBottom/s16OffsetRight/s16OffsetLeft should be set.
 */
static AX_S32 AX_IVPS_CropResize(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrc,
                                 AX_VIDEO_FRAME_T *ptDst, const AX_IVPS_ASPECT_RATIO_T *ptAspectRatio)
{
    AX_S32 ret = 0;
    AX_IVPS_CROP_RESIZE_ATTR_T tCropResizeAttr = {0};

    tCropResizeAttr.tAspectRatio = *ptAspectRatio;
    switch (eEngineId)
    {
    case IVPS_ENGINE_ID_TDP:
        ret = AX_IVPS_CropResizeTdp(ptSrc, ptDst, &tCropResizeAttr);
        break;
    case IVPS_ENGINE_ID_VPP:
        ret = AX_IVPS_CropResizeVpp(ptSrc, ptDst, &tCropResizeAttr);
        break;
    case IVPS_ENGINE_ID_VGP:
        break;
    default:
        ret = -1;
        break;
    }

    if (ret)
    {
        ALOGE("AX_IVPS_CropResize fail, engine id:%d ret=0x%x", eEngineId, ret);
        return ret;
    }
    return 0;
}

/*
 * AX_IVPS_CropResizeV2
 * Function: Crop and Resize in multi-task.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set.
 *       If crop is enabled, s16OffsetTop/s16OffsetBottom/s16OffsetRight/s16OffsetLeft should be set.
 */
static AX_S32 AX_IVPS_CropResizeV2(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrc, AX_U8 nCropNum, const AX_IVPS_RECT_T tBox[],
                                   AX_VIDEO_FRAME_T ptDst[], const AX_IVPS_CROP_RESIZE_ATTR_T *ptAttr)
{
    AX_S32 ret = 0;

    switch (eEngineId)
    {
    case IVPS_ENGINE_ID_TDP:
        ret = AX_IVPS_CropResizeV2Tdp(ptSrc, nCropNum, tBox, ptDst, ptAttr);
        break;
    case IVPS_ENGINE_ID_VPP:
        ret = AX_IVPS_CropResizeV2Vpp(ptSrc, nCropNum, tBox, ptDst, ptAttr);
        break;
    case IVPS_ENGINE_ID_VGP:
        break;
    default:
        ret = -1;
        break;
    }

    if (ret)
    {
        ALOGE("AX_IVPS_CropResizeV2 fail, engine id:%d ret=0x%x", eEngineId, ret);
        return ret;
    }
    return 0;
}

/*
 * AX_IVPS_AlphaBlending
 * Function: Overlay two images.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set.
 */
static AX_S32 AX_IVPS_AlphaBlending(IVPS_ENGINE_ID_E eEngineId,
                                    const AX_VIDEO_FRAME_T *ptSrc,
                                    const AX_VIDEO_FRAME_T *ptOverlay,
                                    const AX_IVPS_POINT_T tOffset, AX_U8 nAlpha,
                                    AX_VIDEO_FRAME_T *ptDst)
{
    AX_S32 ret = 0;

    switch (eEngineId)
    {
    case IVPS_ENGINE_ID_TDP:
        ret = AX_IVPS_AlphaBlendingTdp(ptSrc, ptOverlay, tOffset, nAlpha, ptDst);
        break;
    case IVPS_ENGINE_ID_VGP:
        break;
    default:
        ret = -1;
        break;
    }

    if (ret)
    {
        ALOGE("AX_IVPS_AlphaBlending fail, engine id:%d ret=0x%x", eEngineId, ret);
        return ret;
    }
    return 0;
}


/*
 * SAMPLE_IVPS_Mosaic()
 * Function: Draw mosaic and save output file.
 * Note: Stride should be 16 Byte aligned.
 *       Draw up to 32 mosaics at once.
 */
static AX_S32 AX_IVPS_DrawMosaic(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrc, AX_IVPS_RGN_MOSAIC_T tMosaic[], AX_U32 nNum)
{
    AX_S32 ret = 0;
    switch (eEngineId)
    {
    case IVPS_ENGINE_ID_VPP:
        /* ret = AX_IVPS_DrawMosaicVpp(ptSrc, tMosaic, nNum); */
        break;
    case IVPS_ENGINE_ID_VGP:
        /* ret = AX_IVPS_DrawMosaicVgp(ptSrc, tMosaic, nNum); */
        break;
    case IVPS_ENGINE_ID_TDP:
        ret = AX_IVPS_DrawMosaicTdp(ptSrc, tMosaic, nNum);
        break;
    default:
        ret = -1;
        break;
    }
    if (ret)
    {
        ALOGE("AX_IVPS_DrawMosaic fail, engine id:%d ret=0x%x", eEngineId, ret);
        return ret;
    }
    return 0;
}

/*
* SAMPLE_IVPS_DrawOsd
* Function: Draw OSD in cavans.
* Note: Stride and width should be 16 Byte aligned.
*/
static AX_S32 AX_IVPS_DrawOsd(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrc,
                            AX_IVPS_RGN_CANVAS_INFO_T *tCanvas, AX_OSD_BMP_ATTR_T arrBmp[], AX_VIDEO_FRAME_T *ptDst)
{
    AX_S32 ret = 0;

    switch (eEngineId)
    {
    case IVPS_ENGINE_ID_TDP:
        ret = AX_IVPS_DrawOsdTdp(ptSrc, tCanvas, arrBmp, 32, ptDst);
        break;
    default:
        ret = -1;
        break;
    }

    if (ret)
    {
        ALOGE("AX_IVPS_DrawOsd fail, engine id:%d ret=0x%x", eEngineId, ret);
        return ret;
    }
    return 0;
}

/*
 * SAMPLE_IVPS_CmmCopy()
 * Function: Move a piece of memory data and save output file.
 * Note: When copy, the nMemSize should be 64K Byte aligned, 256M maximum.
 */
AX_S32 SAMPLE_IVPS_CmmCopy(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, char *strFilePath)
{
    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tDstFrame = {0};
    AX_BLK BlkId;
    AX_U32 nImgSize = ptSrcFrame->u32Height * ptSrcFrame->u32PicStride[0] * 3; /* assume format is rgb888 */

    nImgSize = ALIGN_UP(nImgSize, 0x10000); /* nImgSize should be 0x10000 aligned */
    ALOGI("nImgSize=%d", nImgSize);

    CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &tDstFrame.u64PhyAddr[0],
                                     (AX_VOID **)&tDstFrame.u64VirAddr[0], &BlkId));
    ALOGI("src=%llx dst=%llx", ptSrcFrame->u64PhyAddr[0], tDstFrame.u64PhyAddr[0]);
    ret = AX_IVPS_CmmCopy(eEngineId, ptSrcFrame->u64PhyAddr[0], tDstFrame.u64PhyAddr[0], nImgSize);
    if (ret)
    {
        ALOGE("AX_IVPS_CmmCopy fail ! ret=0x%x", ret);
        return ret;
    }
    ALOGI("src=%llx dst=%llx", ptSrcFrame->u64PhyAddr[0], tDstFrame.u64PhyAddr[0]);

    tDstFrame.enImgFormat = ptSrcFrame->enImgFormat;
    tDstFrame.u32PicStride[0] = ptSrcFrame->u32PicStride[0];
    tDstFrame.u32Height = ptSrcFrame->u32Height;

    /* sprintf(strFileName, "CmmCopy_%d_", eEngineId); */
    SaveFile(&tDstFrame, 0, 0, strFilePath, "CmmCopy");
    ret = AX_POOL_ReleaseBlock(BlkId);
    if (ret)
    {
        ALOGE("Rls BlkId fail, ret=0x%x", ret);
    }

    return ret;
}

/*
 * SAMPLE_IVPS_Csc()
 * Function: Color space conversion and save output file.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set. If format is AX_YUV420_SEMIPLANAR.
 */
AX_S32 SAMPLE_IVPS_Csc(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, char *strFilePath)
{
    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tDstFrame = {0};
    AX_BLK BlkId;
    AX_U32 nImgSize;

    ALOGI("CSC input u32Width =%d Height:%d", ptSrcFrame->u32Width, ptSrcFrame->u32Height);
    ALOGI("CSC input format =%d ", ptSrcFrame->enImgFormat);

    tDstFrame.enImgFormat = AX_FORMAT_YUV422_INTERLEAVED_YUYV;
    tDstFrame.u32Height = ptSrcFrame->u32Height;
    tDstFrame.u32Width = ptSrcFrame->u32Width;
    tDstFrame.u32PicStride[0] = ptSrcFrame->u32PicStride[0];
    tDstFrame.stCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE; /*AX_COMPRESS_MODE_LOSSLESS*/
    nImgSize = CalcImgSize(ptSrcFrame->u32PicStride[0], ptSrcFrame->u32Width,
                           ptSrcFrame->u32Height, ptSrcFrame->enImgFormat, 16);
    ALOGI("CSC nImgSize =%d", nImgSize);
    ALOGI("CSC ptSrcFrame->u32PicStride[0]=%d", ptSrcFrame->u32PicStride[0]);
    if (tDstFrame.stCompressInfo.enCompressMode)
    {
        /* If enable compress, add header information to the address of Y and UV.
        Y headers size = H/2*128
        UV header size = H/2*64 */
        nImgSize = nImgSize + DIV_ROUND_UP(ptSrcFrame->u32Height, 2) * 64 * 3;
    }
    CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &tDstFrame.u64PhyAddr[0],
                                     (AX_VOID **)&tDstFrame.u64VirAddr[0], &BlkId));

    ALOGI("tDstFrame.u64PhyAddr[1] =0x%llx", tDstFrame.u64PhyAddr[1]);
    ALOGI("CSC ptSrcFrame->u32PicStride[0] =%d  ptSrcFrame->u32Height:%d", ptSrcFrame->u32PicStride[0], ptSrcFrame->u32Height);
    tDstFrame.u64PhyAddr[1] = tDstFrame.u64PhyAddr[0] + ptSrcFrame->u32PicStride[0] * ptSrcFrame->u32Height; // for dstFormat nv12
    ALOGI("tDstFrame.u64PhyAddr[1] =0x%llx", tDstFrame.u64PhyAddr[1]);

    if (tDstFrame.stCompressInfo.enCompressMode)
    {
        tDstFrame.u64PhyAddr[0] += DIV_ROUND_UP(ptSrcFrame->u32Height, 2) * 64 * 2;
        tDstFrame.u64PhyAddr[1] += DIV_ROUND_UP(ptSrcFrame->u32Height, 2) * 64 * 3;
    }

    ALOGI("AX_IVPS_CscTdp src=%llx dst=%llx", ptSrcFrame->u64PhyAddr[0], tDstFrame.u64PhyAddr[0]);
    ALOGI("AX_IVPS_CscTdp src=%llx dst=%llx", ptSrcFrame->u64PhyAddr[1], tDstFrame.u64PhyAddr[1]);
    ret = AX_IVPS_Csc(eEngineId, ptSrcFrame, &tDstFrame);
    if (ret)
    {
        ALOGE("ret=0x%x", ret);
        return ret;
    }

    tDstFrame.u32PicStride[0] = ptSrcFrame->u32PicStride[0];
    tDstFrame.u32Height = ptSrcFrame->u32Height;
    SaveFile(&tDstFrame, 0, 0, strFilePath, "CSC_");
    ret = AX_POOL_ReleaseBlock(BlkId);
    if (ret)
    {
        ALOGE("Rls BlkId fail, ret=0x%x", ret);
    }
    return ret;
}

/*
 * SAMPLE_IVPS_FlipAndRotation
 * Function: Flip/Mirror/Rotate 0/90/180/270 and save output file.
 * Note: Stride and width should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set. If format is AX_YUV420_SEMIPLANAR, u64PhyAddr[1] should be set.
 */
AX_S32 SAMPLE_IVPS_FlipAndRotation(const AX_VIDEO_FRAME_T *ptSrcFrame,
                                   AX_S32 nFlipCode, AX_S32 nRotation, AX_S32 nFormat, char *strFilePath)
{
    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tDstFrame = {0};
    AX_BLK BlkId;
    AX_U32 nImgSize;

    printf("nFlipCode:%d nRotation:%d nFormat:%d\n", nFlipCode, nRotation, nFormat);
    tDstFrame.enImgFormat = nFormat;
    if (nRotation == AX_IVPS_ROTATION_90 || nRotation == AX_IVPS_ROTATION_270)
    {
        tDstFrame.u32Height = ptSrcFrame->u32Width;
        tDstFrame.u32Width = ptSrcFrame->u32Height;
        tDstFrame.u32PicStride[0] = ptSrcFrame->u32Height;
    }
    else
    {
        tDstFrame.u32Width = ptSrcFrame->u32Width;
        tDstFrame.u32Height = ptSrcFrame->u32Height;
        tDstFrame.u32PicStride[0] = ptSrcFrame->u32PicStride[0];
    }

    nImgSize = CalcImgSize(tDstFrame.u32PicStride[0], tDstFrame.u32Width,tDstFrame.enImgFormat, tDstFrame.enImgFormat, 2);
    CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &tDstFrame.u64PhyAddr[0], (AX_VOID **)&tDstFrame.u64VirAddr[0], &BlkId));
    tDstFrame.u64PhyAddr[1] = tDstFrame.u64PhyAddr[0] + tDstFrame.u32PicStride[0] * tDstFrame.u32Height;

    ret = AX_IVPS_FlipAndRotationTdp(ptSrcFrame, nFlipCode, nRotation, &tDstFrame);
    if (ret)
    {
        ALOGE("FlipAndRotationTdp, ret=0x%x", ret);
        return ret;
    }

    SaveFile(&tDstFrame, 0, 0, strFilePath, "FlipRotate_");
    ret = AX_POOL_ReleaseBlock(BlkId);
    if (ret)
    {
        ALOGE("Rls BlkId fail, ret=0x%x", ret);
    }
    return ret;
}

/*
 * SAMPLE_IVPS_AlphaBlending
 * Function: Overlay two images and save output file.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set.
 */
AX_S32 SAMPLE_IVPS_AlphaBlending(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame,
                                 AX_VIDEO_FRAME_T *ptOverlay, AX_U8 nAlpha, char *strFilePath)
{

    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tDstFrame = {0};
    AX_BLK BlkId;
    AX_U32 nImgSize;
    AX_IVPS_POINT_T tOffset;

    tOffset.nX = 128;
    tOffset.nY = 80;
    tDstFrame.enImgFormat = ptSrcFrame->enImgFormat;
    tDstFrame.u32Height = ptSrcFrame->u32Height;
    tDstFrame.u32Width = ptSrcFrame->u32Width;
    tDstFrame.u32PicStride[0] = ptSrcFrame->u32PicStride[0];
    nImgSize = CalcImgSize(ptSrcFrame->u32PicStride[0], ptSrcFrame->u32Width,
                           ptSrcFrame->u32Height, ptSrcFrame->enImgFormat, 16);
    CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &tDstFrame.u64PhyAddr[0],
                                     (AX_VOID **)(&tDstFrame.u64VirAddr[0]), &BlkId));

    tDstFrame.u64PhyAddr[1] = tDstFrame.u64PhyAddr[0] + ptSrcFrame->u32PicStride[0] * ptSrcFrame->u32Height;
    /* width and height should align 2 piexl, stride should align 16 piexl */
    if (ptOverlay->u32PicStride[0] & 0xf) {
        ALOGE("overlay picture stride:%d is not align 16 piexl!", ptOverlay->u32PicStride[0]);
        return AX_ERROR_IVPS(AX_ERR_ILLEGAL_PARAM);
    }

    ret = AX_IVPS_AlphaBlending(eEngineId, ptSrcFrame, ptOverlay, tOffset, nAlpha, &tDstFrame);
    if (ret)
    {
        ALOGE("ret=0x%x", ret);
        return ret;
    }

    SaveFile(&tDstFrame, 0, 0, strFilePath, "AlphaBlend_");
    ret = AX_POOL_ReleaseBlock(BlkId);
    if (ret)
    {
        ALOGE("Rls BlkId fail, ret=0x%x", ret);
    }
    return ret;
}

/*
 * SAMPLE_IVPS_CropResize
 * Function: Crop and Resize and save output file.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set.
 *       If crop is enabled, s16OffsetTop/s16OffsetBottom/s16OffsetRight/s16OffsetLeft should be set.
 */
AX_S32 SAMPLE_IVPS_CropResize(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, char *strFilePath)
{

    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tDstFrame = {0};
    AX_BLK BlkId;
    AX_U32 nImgSize;
    AX_IVPS_ASPECT_RATIO_T tAspectRatio;
    AX_U32 WidthTemp, HeightTemp;

    tAspectRatio.eMode = AX_IVPS_ASPECT_RATIO_STRETCH;
    tAspectRatio.eAligns[0] = AX_IVPS_ASPECT_RATIO_HORIZONTAL_CENTER;
    tAspectRatio.eAligns[1] = AX_IVPS_ASPECT_RATIO_VERTICAL_CENTER;
    tAspectRatio.nBgColor = 0x0000FF;

    tDstFrame.u32PicStride[0] = 1024;
    WidthTemp = tDstFrame.u32Width = 1024;
    HeightTemp = tDstFrame.u32Height = 1024;
    tDstFrame.enImgFormat = ptSrcFrame->enImgFormat;
    ALOGI("tDstFrame stride:%d, width: %d, height: %d, format: %d",
          tDstFrame.u32PicStride[0], tDstFrame.u32Width, tDstFrame.u32Height,
          tDstFrame.enImgFormat);

    nImgSize = CalcImgSize(tDstFrame.u32PicStride[0], tDstFrame.u32Width,
                           tDstFrame.u32Height, tDstFrame.enImgFormat, 16);
    CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &tDstFrame.u64PhyAddr[0],
                                     (AX_VOID **)(&tDstFrame.u64VirAddr[0]), &BlkId));

    /* memset((AX_VOID *)((AX_U32)tDstFrame.u64VirAddr[0]), tAspectRatio.nBgColor, nImgSize * 2); */

    ALOGI("tAspectRatio.eMode =%d", tAspectRatio.eMode);

    ret = AX_IVPS_CropResize(eEngineId, ptSrcFrame, &tDstFrame, &tAspectRatio);
    if (ret)
    {
        ALOGE("ret=0x%x", ret);
        return ret;
    }

    tDstFrame.u32Width = WidthTemp;
    tDstFrame.u32Height = HeightTemp;
    printf("OFFSET X0:%d Y0:%d W:%d H:%d", tDstFrame.s16CropX, tDstFrame.s16CropWidth,
           tDstFrame.s16CropY, tDstFrame.s16CropHeight);
    SaveFile(&tDstFrame, 0, 0, strFilePath, "CropResize");
    ret = AX_POOL_ReleaseBlock(BlkId);
    if (ret)
    {
        ALOGE("Rls BlkId fail, ret=0x%x", ret);
    }
    return ret;
}

/*
 * SAMPLE_IVPS_CropResizeV2
 * Function: Crop and Resize.Support max 1 in and 32 out.
 * Note: Stride and width should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set. If format is AX_YUV420_SEMIPLANAR, u64PhyAddr[1] should be set.
 *       If enable crop, s16OffsetTop/s16OffsetBottom/s16OffsetRight/s16OffsetLeft should be set.
 */
AX_S32 SAMPLE_IVPS_CropResizeV2(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, char *strFilePath)
{

    AX_S32 i, ret = 0;
    AX_BLK BlkId[32];
    AX_U32 nImgSize;
    AX_IVPS_CROP_RESIZE_ATTR_T tCropResizeAttr;
    AX_U32 WidthTemp[32], HeightTemp[32];
    AX_U8 nNum = 5;
    AX_VIDEO_FRAME_T tDstFrame[32] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
    AX_S32 nDstWidth[32] = {256, 512, 512, 256,
                            256, 256, 256, 256,
                            256, 256, 256, 256,
                            256, 256, 256, 256,
                            256, 256, 256, 256,
                            256, 256, 256, 256,
                            256, 256, 256, 256,
                            256, 256, 256, 256};
    AX_S32 nDstHeight[32] = {512, 256, 512, 512,
                             256, 256, 256, 256,
                             256, 256, 256, 256,
                             256, 256, 256, 256,
                             256, 256, 256, 256,
                             256, 256, 256, 256,
                             256, 256, 256, 256,
                             256, 256, 256, 256};
    AX_IVPS_RECT_T tBox[32] = {{0, 0, 1024, 1024},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512},
                               {0, 0, 512, 512}};

    tCropResizeAttr.tAspectRatio.eMode = AX_IVPS_ASPECT_RATIO_STRETCH;
    tCropResizeAttr.tAspectRatio.eAligns[0] = AX_IVPS_ASPECT_RATIO_HORIZONTAL_CENTER;
    tCropResizeAttr.tAspectRatio.eAligns[1] = AX_IVPS_ASPECT_RATIO_VERTICAL_CENTER;
    tCropResizeAttr.tAspectRatio.nBgColor = 0x0000FF;
    printf("tAspectRatio.eMode =%d", tCropResizeAttr.tAspectRatio.eMode);

    for (i = 0; i < nNum; i++)
    {
        tDstFrame[i].u32PicStride[0] = ALIGN_UP(nDstWidth[i], 16);
        tDstFrame[i].u32Width = nDstWidth[i];
        tDstFrame[i].u32Height = nDstHeight[i];
        tDstFrame[i].enImgFormat = ptSrcFrame->enImgFormat;
        printf("tDstFrame[%d] stride:%d, width: %d, height: %d, format: %d",
              i, tDstFrame[i].u32PicStride[0], tDstFrame[i].u32Width, tDstFrame[i].u32Height,
              tDstFrame[i].enImgFormat);

        WidthTemp[i] = tDstFrame[i].u32Width;
        HeightTemp[i] = tDstFrame[i].u32Height;
        nImgSize = CalcImgSize(tDstFrame[i].u32PicStride[0], tDstFrame[i].u32Width,
                               tDstFrame[i].u32Height, tDstFrame[i].enImgFormat, 16);

        CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &(tDstFrame[i].u64PhyAddr[0]),
                                         (AX_VOID **)(&(tDstFrame[i].u64VirAddr[0])), &BlkId[i]));
    }

    ret = AX_IVPS_CropResizeV2(eEngineId, ptSrcFrame, nNum, tBox, tDstFrame, &tCropResizeAttr);
    if (ret)
    {
        ALOGE("ret=0x%x\n", ret);
        return ret;
    }

    for (i = 0; i < nNum; i++)
    {
        tDstFrame[i].u32Width = WidthTemp[i];
        tDstFrame[i].u32Height = HeightTemp[i];
        ALOGI("CHN:%d OFFSET X0:%d Y0:%d W:%d H:%d", i, tDstFrame[i].s16CropX, tDstFrame[i].s16CropY,
              tDstFrame[i].s16CropWidth, tDstFrame[i].s16CropHeight);
        SaveFile(&tDstFrame[i], 0, i, strFilePath, "CropResizeV2");
        ret = AX_POOL_ReleaseBlock(BlkId[i]);
        if (ret)
        {
            ALOGE("Rls BlkId[%d] fail, ret=0x%x", i, ret);
        }
    }

    return ret;
}

/*
 * SAMPLE_IVPS_CropResizeV3
 * Function: Crop and Resize.Support one in and four out.
 * Note: Stride should be 16 Byte aligned.
 *       The u64PhyAddr[0] of ptDst should be set.
 *       If crop is enabled, s16OffsetTop/s16OffsetBottom/s16OffsetRight/s16OffsetLeft should be set.
 */
AX_S32 SAMPLE_IVPS_CropResizeV3(const AX_VIDEO_FRAME_T *ptSrcFrame,
                                AX_S32 nDstStride[], AX_S32 nDstWidth[],
                                AX_S32 nDstHeight[], AX_U32 nNum, char *strFilePath)
{

    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tDstFrame[4] = {{0}, {0}, {0}, {0}};
    AX_VIDEO_FRAME_T *ptDstFrame[4];
    AX_BLK BlkId[4];
    AX_U32 nImgSize;
    AX_IVPS_CROP_RESIZE_ATTR_T tCropResizeAttr;
    AX_U32 WidthTemp[4], HeightTemp[4];
    AX_U32 i;
    tCropResizeAttr.tAspectRatio.eMode = AX_IVPS_ASPECT_RATIO_AUTO;
    tCropResizeAttr.tAspectRatio.eAligns[0] = AX_IVPS_ASPECT_RATIO_HORIZONTAL_CENTER;
    tCropResizeAttr.tAspectRatio.eAligns[1] = AX_IVPS_ASPECT_RATIO_VERTICAL_CENTER;
    tCropResizeAttr.tAspectRatio.nBgColor = 0x0000FF;
    ALOGI("tAspectRatio.eMode =%d", tCropResizeAttr.tAspectRatio.eMode);

    for (i = 0; i < nNum; i++)
    {
        ptDstFrame[i] = &tDstFrame[i]; /* ptDstFrame is only for passing parameters */
        tDstFrame[i].u32PicStride[0] = nDstStride[i];
        tDstFrame[i].u32Width = nDstWidth[i];
        tDstFrame[i].u32Height = nDstHeight[i];
        tDstFrame[i].enImgFormat = ptSrcFrame->enImgFormat;
        ALOGI("tDstFrame[%d] stride:%d, width: %d, height: %d, format: %d",
              i, tDstFrame[i].u32PicStride[0], tDstFrame[i].u32Width, tDstFrame[i].u32Height,
              tDstFrame[i].enImgFormat);

        WidthTemp[i] = tDstFrame[i].u32Width;
        HeightTemp[i] = tDstFrame[i].u32Height;
        nImgSize = CalcImgSize(tDstFrame[i].u32PicStride[0], tDstFrame[i].u32Width,
                               tDstFrame[i].u32Height, tDstFrame[i].enImgFormat, 16);

        CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &(tDstFrame[i].u64PhyAddr[0]),
                                         (AX_VOID **)(&(tDstFrame[i].u64VirAddr[0])), &BlkId[i]));
    }

    /*
        ret = AX_IVPS_CropResizeV3Vpp(ptSrcFrame, ptDstFrame, nNum, &tCropResizeAttr);
        if (ret)
        {
            ALOGE("ret=0x%x", ret);
            return ret;
        }
    */
    for (i = 0; i < nNum; i++)
    {
        tDstFrame[i].u32Width = WidthTemp[i];
        tDstFrame[i].u32Height = HeightTemp[i];
        ALOGI("CHN:%d OFFSET X0:%d Y0:%d W:%d H:%d", i, tDstFrame[i].s16CropX, tDstFrame[i].s16CropY,
              tDstFrame[i].s16CropWidth, tDstFrame[i].s16CropHeight);
        SaveFile(&tDstFrame[i], 0, i, strFilePath, "CropResizeV3_");
        ret = AX_POOL_ReleaseBlock(BlkId[i]);
        if (ret)
        {
            ALOGE("Rls BlkId[%d] fail, ret=0x%x", i, ret);
        }
    }

    return ret;
}

/*
 * SAMPLE_IVPS_Mosaic()
 * Function: Draw mosaic and save output file.
 * Note: Stride should be 16 Byte aligned.
 *       Draw up to 32 mosaics at once.
 */
AX_S32 SAMPLE_IVPS_DrawMosaic(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, AX_IVPS_RGN_MOSAIC_T tMosaic[], AX_U32 nNum, char *strFilePath)
{
    AX_S32 ret = 0;
    AX_VIDEO_FRAME_T tDstFrame = {0};
    ret = AX_IVPS_DrawMosaic(eEngineId, ptSrcFrame, tMosaic, nNum);
    if (ret)
    {
        ALOGE("ret=0x%x", ret);
        return ret;
    }

    tDstFrame.u32PicStride[0] = ptSrcFrame->u32PicStride[0];
    tDstFrame.u32Width = ptSrcFrame->u32Width;
    tDstFrame.u32Height = ptSrcFrame->u32Height;
    tDstFrame.enImgFormat = ptSrcFrame->enImgFormat;
    tDstFrame.u64PhyAddr[0] = ptSrcFrame->u64PhyAddr[0];
    tDstFrame.u64PhyAddr[1] = ptSrcFrame->u64PhyAddr[1];
    SaveFile(&tDstFrame, 0, 0, strFilePath, "Mosaic_");

    return ret;
}

/*
* SAMPLE_IVPS_DrawOsd
* Function: Draw OSD in cavans.
* Note: Stride and width should be 16 Byte aligned.
*/
AX_S32 SAMPLE_IVPS_DrawOsd(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame,
                            AX_VIDEO_FRAME_T *ptOverlay, char *strFilePath)
{
    AX_S32 ret = 0;
    AX_OSD_BMP_ATTR_T tBmpAttr[32];
    AX_IVPS_RGN_CANVAS_INFO_T tCanvas;
    AX_VIDEO_FRAME_T tDstFrame = {0};
    AX_S32 i;
    AX_U32 nImgSize;
    AX_BLK BlkId;

    tCanvas.nPhyAddr = ptSrcFrame->u64PhyAddr[0];
    tCanvas.nStride = ptSrcFrame->u32PicStride[0];
    tCanvas.nW = ptSrcFrame->u32Width;
    tCanvas.nH = ptSrcFrame->u32Height;
    tCanvas.eFormat = ptSrcFrame->enImgFormat;
    tCanvas.nUVOffset = 0;

    tDstFrame.enImgFormat = ptSrcFrame->enImgFormat;
    tDstFrame.u32Height = ptSrcFrame->u32Height;
    tDstFrame.u32Width = ptSrcFrame->u32Width;
    tDstFrame.u32PicStride[0] = ptSrcFrame->u32PicStride[0];
    nImgSize = CalcImgSize(ptSrcFrame->u32PicStride[0], ptSrcFrame->u32Width,
                               ptSrcFrame->u32Height, ptSrcFrame->enImgFormat, 16);
    CHECK_RESULT(BufPoolBlockAddrGet(-1, nImgSize, &tDstFrame.u64PhyAddr[0],
                                     (AX_VOID **)(&tDstFrame.u64VirAddr[0]), &BlkId));

    tDstFrame.u64PhyAddr[1] = tDstFrame.u64PhyAddr[0] + ptSrcFrame->u32PicStride[0] * ptSrcFrame->u32Height;

    for (i = 0; i < 32; i++)
    {
        tBmpAttr[i].u16Alpha = 200;
        tBmpAttr[i].enRgbFormat = ptOverlay->enImgFormat;
        tBmpAttr[i].u32BmpWidth = ptOverlay->u32Width;
        tBmpAttr[i].u32BmpHeight = ptOverlay->u32Height;
        tBmpAttr[i].u32DstXoffset = 128 + i * 16;
        tBmpAttr[i].u32DstYoffset = 80 +  i * 8;
        tBmpAttr[i].u64PhyAddr = ptOverlay->u64PhyAddr[0];
    }
    ret = AX_IVPS_DrawOsd(eEngineId, ptSrcFrame, &tCanvas, tBmpAttr, &tDstFrame);
    if (ret)
    {
        ALOGE("ret=0x%x", ret);
        return ret;
    }
    tDstFrame.u32Width = tCanvas.nW;
    tDstFrame.u32Height = tCanvas.nH;
    SaveFile(&tDstFrame, 0, 0, strFilePath, "DrawOSD_"); /*Frame will be changed*/
    return ret;
}
