/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include "ax_sys_api.h"
#include "ax_base_type.h"
#include "ax_vo_api.h"

#include "common_vo.h"
#include "common_vo_pattern.h"
#include "sample_vo_common.h"

typedef struct axSAMPLE_VO_CHN_THREAD_PARAM {
    pthread_t ThreadID;

    AX_U32 u32Udelay;

    AX_FRAME_COMPRESS_INFO_T chnCompressInfo;
    AX_CHAR chnFileName[VO_NAME_LEN];
    AX_U32 u32SendCnt;
    AX_U32 u32ThreadForceStop;

    AX_U32 u32FrameRate;
    AX_U32 u32FrameMax;

    AX_U32 u32LayerID;
    AX_U32 u32ChnID;
    AX_POOL u32UserPoolId;
    AX_U32  u32FrameFmt;
} SAMPLE_VO_CHN_THREAD_PARAM_T;

typedef struct axSAMPLE_VO_VIDEOLAYER_THREAD_PARAM {
    SAMPLE_VO_CHN_THREAD_PARAM_T stVoChnThreadParm[AX_VO_CHN_MAX];

    AX_U32 u32ThreadForceStop;
    AX_U32 u32LayerID;
    AX_U32 u32ChnID;
    AX_U32 u32FrameCnt;

    pthread_t ThreadID;
} SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T;

typedef struct axSAMPLE_VO_WBC_THREAD_PARAM {
    AX_U32 u32ThreadForceStop;
    AX_U32 u32Wbc;
    AX_U32 u32FrameCnt;

    pthread_t ThreadID;
} SAMPLE_VO_WBC_THREAD_PARAM_T;

static int SAMPLE_VO_POOL_DESTROY(AX_U32 u32PoolID)
{
    return AX_POOL_DestroyPool(u32PoolID);
}

static const AX_CHAR *SAMPLE_VO_FORMAT2STRING(AX_S32 value)
{
    switch (value) {
    case AX_FORMAT_YUV400:
        return ("y");
    case AX_FORMAT_YUV420_SEMIPLANAR:
        return ("nv12");
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
        return ("nv21");
    case AX_FORMAT_YUV422_SEMIPLANAR:
        return ("nv16");
    case AX_FORMAT_RGB888:
        return ("rg24");
    default:
        return "null";
    }
}

AX_VOID SAMPLE_VO_SAVE_FILE(AX_U32 u32LayerID, AX_VIDEO_FRAME_T *tDstFrame, FILE **fp)
{
    AX_U32 nPixelSize;
    AX_S32 s32Ret1 = 0;
    AX_S32 s32Ret2 = 0;
    AX_S32 s32Ret3 = 0;
    AX_S32 bit_num = 0;
    AX_U8 nStoragePlanarNum = 0;
    char szOutImgFile[128] = {0};
    FILE *fp_out = NULL;
    AX_U32 tile_num = 0;
    AX_U32 y2uvRatio = 1;

    if (NULL == tDstFrame) {
        SAMPLE_PRT("layerid:%d, tDstFrame == NULL", u32LayerID);
        return;
    }

    nPixelSize = (AX_U32)tDstFrame->u32PicStride[0] * tDstFrame->u32Height;

    switch (tDstFrame->enImgFormat) {
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
        bit_num = 8;
        nStoragePlanarNum = 2;
        y2uvRatio = 2;
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
        SAMPLE_PRT("failed. not support fromat %d", tDstFrame->enImgFormat);
        return;
    }

    if (*fp == NULL) {
        if (AX_COMPRESS_MODE_NONE == tDstFrame->stCompressInfo.enCompressMode) {
            sprintf(szOutImgFile, "layer%d_%d_%d_stride%d.%s", u32LayerID, tDstFrame->u32Width,
                    tDstFrame->u32Height, tDstFrame->u32PicStride[0], SAMPLE_VO_FORMAT2STRING(tDstFrame->enImgFormat));
        } else if (AX_COMPRESS_MODE_LOSSY == tDstFrame->stCompressInfo.enCompressMode) {
            sprintf(szOutImgFile, "layer%d_%d_%d_stride%d_lossy_level%d.%s",  u32LayerID, tDstFrame->u32Width,
                    tDstFrame->u32Height, tDstFrame->u32PicStride[0], tDstFrame->stCompressInfo.u32CompressLevel,
                    SAMPLE_VO_FORMAT2STRING(tDstFrame->enImgFormat));
        } else {
            SAMPLE_PRT("enCompressMode is error. enCompressMode=%d\n", tDstFrame->stCompressInfo.enCompressMode);
            return;
        }
        fp_out = *fp = fopen(szOutImgFile, "wb");
        if (fp_out == NULL) {
            SAMPLE_PRT("failed open file:%s.", szOutImgFile);
            return;
        }
    } else {
        fp_out = *fp;
    }

    if (AX_COMPRESS_MODE_NONE == tDstFrame->stCompressInfo.enCompressMode) {
        switch (nStoragePlanarNum) {
        case 2:
            if (!tDstFrame->u64PhyAddr[1])
            tDstFrame->u64PhyAddr[1] = tDstFrame->u64PhyAddr[0] + tDstFrame->u32PicStride[0] * tDstFrame->u32Height;
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize);
            tDstFrame->u64VirAddr[1] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[1], nPixelSize / 2);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize, fp_out);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[1]), 1, nPixelSize / 2, fp_out);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[1], nPixelSize / 2);
            break;
        default:
            if (tDstFrame->u32FrameSize) {
                tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], tDstFrame->u32FrameSize);
                fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, tDstFrame->u32FrameSize, fp_out);
                s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], tDstFrame->u32FrameSize);
            } else {
                tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize );
                fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize, fp_out);
                s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize);
            }
            break;
        }
    } else {
        if (tDstFrame->u32FrameSize) {
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], tDstFrame->u32FrameSize);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, tDstFrame->u32FrameSize, fp_out);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], tDstFrame->u32FrameSize);
        } else {
            tile_num = nPixelSize / (SAMPLE_VO_LOSSY_YUV_LITE_HEIGHT * SAMPLE_VO_LOSSY_YUV_LITE_WIDTH);
            nPixelSize = (tile_num * SAMPLE_VO_LOSSY_COMP_LEVEL_FACTOR * tDstFrame->stCompressInfo.u32CompressLevel) * bit_num / 8;
            nPixelSize += nPixelSize / y2uvRatio;
            tDstFrame->u64VirAddr[0] = (AX_ULONG)AX_SYS_Mmap(tDstFrame->u64PhyAddr[0], nPixelSize);
            fwrite((AX_VOID *)((AX_ULONG)tDstFrame->u64VirAddr[0]), 1, nPixelSize, fp_out);
            s32Ret1 = AX_SYS_Munmap((AX_VOID *)(AX_ULONG)tDstFrame->u64VirAddr[0], nPixelSize);
        }
    }

    if (s32Ret1 || s32Ret2 || s32Ret3) {
        SAMPLE_PRT("AX_SYS_Munmap failed. s32Ret1=0x%x ,s32Ret2=0x%x ,s32Ret2=0x%x", s32Ret1, s32Ret2, s32Ret3);
    }
}

static AX_S32 SAMPLE_VO_FMT2ImgStoreInfo(AX_IMG_FORMAT_E enImgFormat, AX_U32 *bytesPerPixel, AX_U32 *nPlanes)
{
   switch (enImgFormat) {
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
    case AX_FORMAT_YUV422_SEMIPLANAR:
        *bytesPerPixel = 1;
        *nPlanes = 2;
        break;
    case AX_FORMAT_RGB888:
    case AX_FORMAT_BGR888:
    case AX_FORMAT_RGBA5658:
    case AX_FORMAT_ARGB8565:
    case AX_FORMAT_BGRA5658:
    case AX_FORMAT_ABGR8565:
        *bytesPerPixel = 3;
        *nPlanes = 1;
        break;
    case AX_FORMAT_RGB565:
    case AX_FORMAT_BGR565:
    case AX_FORMAT_ARGB1555:
    case AX_FORMAT_RGBA5551:
    case AX_FORMAT_ABGR1555:
    case AX_FORMAT_BGRA5551:
    case AX_FORMAT_ARGB4444:
    case AX_FORMAT_RGBA4444:
    case AX_FORMAT_ABGR4444:
    case AX_FORMAT_BGRA4444:
        *bytesPerPixel = 2;
        *nPlanes = 1;
        break;
    case AX_FORMAT_RGBA8888:
    case AX_FORMAT_ARGB8888:
    case AX_FORMAT_ABGR8888:
    case AX_FORMAT_BGRA8888:
        *bytesPerPixel = 2;
        *nPlanes = 1;
        break;
    case AX_FORMAT_YUV400:
        *bytesPerPixel = 1;
        *nPlanes = 1;
    default:
        SAMPLE_PRT("not support fromat %d", enImgFormat);
        return -1;
    }

    return 0;
}
static AX_S32 SAMPLE_VO_CREATE_POOL(AX_U32 u32BlkCnt, AX_U64 u64BlkSize, AX_U64 u64MetaSize, AX_U32 *pPoolID)
{
    AX_POOL_CONFIG_T stPoolCfg = {0};

    stPoolCfg.MetaSize = u64MetaSize;
    stPoolCfg.BlkCnt = u32BlkCnt;
    stPoolCfg.BlkSize = u64BlkSize;
    stPoolCfg.CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    strcpy((char *)stPoolCfg.PartitionName, "anonymous");

    *pPoolID = AX_POOL_CreatePool(&stPoolCfg);
    if (*pPoolID == AX_INVALID_POOLID) {
        SAMPLE_PRT("AX_POOL_CreatePool failed, u32BlkCnt = %d, u64BlkSize = 0x%llx, u64MetaSize = 0x%llx\n", u32BlkCnt,
                   u64BlkSize, u64MetaSize);
        return -1;
    }

    SAMPLE_PRT("u32BlkCnt = %d, u64BlkSize = 0x%llx, pPoolID = %d\n", u32BlkCnt, u64BlkSize, *pPoolID);

    return 0;
}

static AX_S32 SAMPLE_VO_FB_CONF(AX_U32 u32Type, SAMPLE_FB_CONFIG_S *pstFbConf)
{
    AX_S32 i, j, s32Fd, s32Ret = 0;
    AX_U16 *u16Pixel;
    AX_U32 *u32Pixel;
    AX_U32 u32FbIndex, u32Width, u32Height, u32Fmt;
    AX_CHAR fbPath[32];
    AX_U8 *pShowScreen;
    struct fb_fix_screeninfo stFix;
    struct fb_var_screeninfo stVar;
    struct fb_bitfield r = {16, 8, 0};
    struct fb_bitfield g = {8, 8, 0};
    struct fb_bitfield b = {0, 8, 0};
    struct fb_bitfield a = {24, 8, 0};
    #if 0
    AX_IVPS_RGN_CANVAS_INFO_T stCanvas = {0,};
    AX_IVPS_GDI_ATTR_T stAttr = {0,};
    AX_IVPS_RECT_T stRect = {0,};
    #endif
    AX_FB_COLORKEY_T stColorKey;

    u32FbIndex = pstFbConf->u32Index;
    u32Width = pstFbConf->u32ResoW;
    u32Height = pstFbConf->u32ResoH;
    u32Fmt = pstFbConf->u32Fmt;

    stColorKey.bEnable = pstFbConf->u32ColorKeyEn;
    stColorKey.bInv = pstFbConf->u32ColorKeyInv;
    stColorKey.nKeyLow = pstFbConf->u32ColorKey;
    stColorKey.nKeyHigh = pstFbConf->u32ColorKey;

    if (u32Fmt == AX_FORMAT_ARGB1555) {
        r.offset = 10;
        r.length = 5;
        g.offset = 5;
        g.length = 5;
        b.offset = 0;
        b.length = 5;
        a.offset = 15;
        a.length = 1;
    }

    /* 1.Open framebuffer device */
    snprintf(fbPath, sizeof(fbPath), "/dev/fb%d", u32FbIndex);
    s32Fd = open(fbPath, O_RDWR);
    if (s32Fd < 0) {
        SAMPLE_PRT("open %s failed, err:%s\n", fbPath, strerror(errno));
        return s32Fd;
    }

    /* 2.Get the variable screen info */
    s32Ret = ioctl(s32Fd, FBIOGET_VSCREENINFO, &stVar);
    if (s32Ret < 0) {
        SAMPLE_PRT("get variable screen info from fb%d failed\n", u32FbIndex);
        goto exit;
    }

    /* 3.Modify the variable screen info, the screen size: u32Width*u32Height, the
     * virtual screen size: u32Width*(u32Height*2), the pixel format: ARGB8888
     */
    stVar.xres = stVar.xres_virtual = u32Width;
    stVar.yres = u32Height;
    stVar.yres_virtual = u32Height * 2;
    stVar.transp = r;
    stVar.red = g;
    stVar.green = b;
    stVar.blue = a;
    stVar.bits_per_pixel = (u32Fmt == AX_FORMAT_ARGB1555) ? 16 : 32;

    /* 4.Set the variable screeninfo */
    s32Ret = ioctl(s32Fd, FBIOPUT_VSCREENINFO, &stVar);
    if (s32Ret < 0) {
        SAMPLE_PRT("put variable screen info to fb%d failed\n", u32FbIndex);
        goto exit;
    }

    /* 5.Get the fix screen info */
    s32Ret = ioctl(s32Fd, FBIOGET_FSCREENINFO, &stFix);
    if (s32Ret < 0) {
        SAMPLE_PRT("get fix screen info from fb%d failed\n", u32FbIndex);
        goto exit;
    }

    /* 6.Map the physical video memory for user use */
    pShowScreen = mmap(NULL, stFix.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, s32Fd, 0);
    if (pShowScreen == (AX_U8 *) - 1) {
        SAMPLE_PRT("map fb%d failed\n", u32FbIndex);
        goto exit;
    }

    if (u32Type) { /* GUI */
        if (u32Fmt != AX_FORMAT_ARGB8888) {
            SAMPLE_PRT("fb%d fmt(0x%x) invalid\n", u32FbIndex, u32Fmt);
            s32Ret = -1;
            goto exit;
        }

        SAMPLE_Fill_Color(u32Fmt, u32Width, u32Height * 2, u32Width * 4, pShowScreen);

        for (i = u32Height / 4; i < u32Height * 3 / 4; i++) {
            u32Pixel = (AX_U32 *)(pShowScreen + i * u32Width * 4);
            for (j = u32Width / 3; j < u32Width * 2 / 3; j++) {
                if (stColorKey.bEnable) {
                    u32Pixel[j] &= ~(0xff << 24);
                } else {
                    u32Pixel[j] = stColorKey.nKeyLow;
                }
            }
        }

    } else { /* Track Frame */
        for (i = 0; i < u32Height; i++) {
            if (u32Fmt == AX_FORMAT_ARGB8888) {
                u32Pixel = (AX_U32 *)(pShowScreen + i * u32Width * 4);
                for (j = 0; j < u32Width; j++) {
                    u32Pixel[j] = (0xFF << 24) | (((stColorKey.nKeyLow >> 16) & 0xFF) << 16) |
                                  (((stColorKey.nKeyLow >> 8) & 0xFF) << 8) |
                                  (((stColorKey.nKeyLow >> 0) & 0xFF) << 0);
                }

            } else {
                u16Pixel = (AX_U16 *)(pShowScreen + i * u32Width * 2);
                for (j = 0; j < u32Width; j++) {
                    u16Pixel[j] = (0x1 << 15) | (((stColorKey.nKeyLow >> 16) & 0x1F) << 10) |
                                  (((stColorKey.nKeyLow >> 8) & 0x1F) << 5) |
                                  (((stColorKey.nKeyLow >> 0) & 0x1F) << 0);
                }
            }
        }
#if 0
        stCanvas.pVirAddr = pShowScreen;
        stCanvas.nPhyAddr = stFix.smem_start;
        stCanvas.nStride = u32Width;
        stCanvas.nW = u32Width;
        stCanvas.nH = u32Height;
        stCanvas.eFormat = u32Fmt;

        stAttr.nThick = 4;
        stAttr.nAlpha = 0xFF;
        stAttr.nColor = 0xFF;

        stRect.nX = u32Width / 2;
        stRect.nY = u32Height / 2;
        stRect.nW = 50;
        stRect.nH = 30;

        s32Ret = AX_IVPS_DrawRect(&stCanvas, stAttr, stRect);
        if (s32Ret) {
            SAMPLE_PRT("draw rect to fb%d failed\n", u32FbIndex);
            goto exit;
        }
#endif

    }

    munmap(pShowScreen, stFix.smem_len);

    /* 7.set colorkey */
    s32Ret = ioctl(s32Fd, AX_FBIOPUT_COLORKEY, &stColorKey);
    if (s32Ret < 0) {
        SAMPLE_PRT("set fb%d colorkey failed!\n", u32FbIndex);
        goto exit;
    }

    SAMPLE_PRT("init fb%d done\n", u32FbIndex);

exit:
    close(s32Fd);

    return s32Ret;
}

static AX_S32 SAMPLE_VO_CURSOR_INIT(AX_U32 u32StartX, AX_U32 u32StartY, AX_U32 u32Width, AX_U32 u32Height,
                                    AX_U32 u32FbIndex)
{
    AX_S32 i, j, s32Fd, s32Ret = 0;
    AX_U32 *u32Pixel;
    AX_CHAR fbPath[32];
    AX_U8 *pShowScreen;
    struct fb_fix_screeninfo stFix;
    struct fb_var_screeninfo stVar;
    struct fb_bitfield stR32 = {24, 8, 0};
    struct fb_bitfield stG32 = {16, 8, 0};
    struct fb_bitfield stB32 = {8, 8, 0};
    struct fb_bitfield stA32 = {0, 8, 0};
    AX_FB_CURSOR_POS_T stPos;
    AX_FB_CURSOR_RES_T stRes;
    AX_U16 show = 1;

    /* 1.Open framebuffer device */
    snprintf(fbPath, sizeof(fbPath), "/dev/fb%d", u32FbIndex);
    s32Fd = open(fbPath, O_RDWR);
    if (s32Fd < 0) {
        SAMPLE_PRT("open %s failed, err:%s\n", fbPath, strerror(errno));
        return s32Fd;
    }

    /* 2.Get the fix screen info */
    s32Ret = ioctl(s32Fd, FBIOGET_FSCREENINFO, &stFix);
    if (s32Ret < 0) {
        SAMPLE_PRT("get fix screen info from fb%d failed\n", u32FbIndex);
        goto exit;
    }

     SAMPLE_PRT("cursor fb%d smem_len:%d line_length:%d\n", u32FbIndex, stFix.smem_len, stFix.line_length);

    /* 3.Get the variable screen info */
    s32Ret = ioctl(s32Fd, FBIOGET_VSCREENINFO, &stVar);
    if (s32Ret < 0) {
        SAMPLE_PRT("get variable screen info from fb%d failed\n", u32FbIndex);
        goto exit;
    }

    /* 4.Modify the variable screen info, the screen size: u32Width*u32Height, the
     * virtual screen size: u32Width*(u32Height*2), the pixel format: ARGB8888
     */
    stVar.xres = stVar.xres_virtual = stFix.line_length / 4;
    stVar.yres = stFix.smem_len / stFix.line_length;
    stVar.yres_virtual = stVar.yres ;
    stVar.transp = stA32;
    stVar.red = stR32;
    stVar.green = stG32;
    stVar.blue = stB32;
    stVar.bits_per_pixel = 32;

    if (u32Width > stVar.xres || u32Height > stVar.yres) {
        SAMPLE_PRT("invaild param u32Width:%d u32Height:%d\n", u32Width, u32Height);
        goto exit;
    }

    /* 5.Set the variable screeninfo */
    s32Ret = ioctl(s32Fd, FBIOPUT_VSCREENINFO, &stVar);
    if (s32Ret < 0) {
        SAMPLE_PRT("put variable screen info to fb%d failed\n", u32FbIndex);
        goto exit;
    }

    /* 6.Map the physical video memory for user use , fill red color */
    pShowScreen = mmap(NULL, stFix.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, s32Fd, 0);
    if (pShowScreen == (AX_U8 *) - 1) {
        SAMPLE_PRT("map fb%d failed,err:%s\n", u32FbIndex, strerror(errno));
        goto exit;
    }

    for (i = 0; i < u32Height; i++) {
        u32Pixel = (AX_U32 *)(pShowScreen + i * stFix.line_length);
        for (j = 0; j < u32Width; j++) {
            u32Pixel[j] = 0xff << 24 | 0xc0 << 16 ;
        }
    }

    munmap(pShowScreen, stFix.smem_len);

    /* 7.set the cursor display pos */
    stPos.u16X = u32StartX;
    stPos.u16Y = u32StartY;
    s32Ret = ioctl(s32Fd, AX_FBIOPUT_CURSOR_POS, &stPos);
    if (s32Ret < 0) {
        SAMPLE_PRT("put cursor pos fb%d failed\n", u32FbIndex);
        goto exit;
    }

    stRes.u32Width = u32Width;
    stRes.u32Height = u32Height;
    s32Ret = ioctl(s32Fd, AX_FBIOPUT_CURSOR_RES, &stRes);
    if (s32Ret < 0) {
        SAMPLE_PRT("put cursor res fb%d failed\n", u32FbIndex);
        goto exit;
    }

    /* 8.set the cursor show flag */
     s32Ret = ioctl(s32Fd, AX_FBIOPUT_CURSOR_SHOW, &show);
    if (s32Ret < 0) {
        SAMPLE_PRT("put cursor show fb%d failed\n", u32FbIndex);
        goto exit;
    }

    SAMPLE_PRT("init cursor fb%d done rect [%d %d %d %d] line_length:%d\n", u32FbIndex, u32StartX, u32StartY, u32Width, u32Height, stFix.line_length);

exit:
    close(s32Fd);
    return s32Ret;
}

static AX_S32 load_img_file(AX_VOID *u64VirAddr, AX_U32 frameSize, AX_CHAR *img_name)
{
    AX_S32 ret = AX_SUCCESS;
    FILE *filep = NULL;
     AX_U32 nmemb;

    filep = fopen(img_name, "r");
    if (filep == NULL) {
        SAMPLE_PRT("Error! failed to open file %s.\n", img_name);
        return -ENOENT;
    }

    nmemb = (frameSize + VO_FILE_BLOCK_SIZE - 1) / VO_FILE_BLOCK_SIZE;
    fread(u64VirAddr, VO_FILE_BLOCK_SIZE, nmemb, filep);
    if (ferror(filep)) {
        SAMPLE_PRT("Error! failed to read file %s.\n", img_name);
        ret = -EBADF;
    }

    fclose(filep);

    return ret;
}

static AX_VOID *SAMPLE_VO_CHN_THREAD(AX_VOID *pData)
{
    AX_S32 s32Ret = 0;
    AX_VIDEO_FRAME_T stFrame = {0};
    AX_U32 u32FrameSize;
    AX_U32 u32LayerID, u32ChnID;
    AX_BLK BlkId;
    AX_VO_CHN_ATTR_T stChnAttr;
    AX_VOID *u64VirAddr;
    AX_U64 u64PhysAddr;
    AX_VO_QUERY_STATUS_T stStatus = {0};
    AX_U32 bytesPerPixel = 0, nPlanes = 0;
    SAMPLE_VO_CHN_THREAD_PARAM_T *pstChnThreadParam = (SAMPLE_VO_CHN_THREAD_PARAM_T *)pData;

    u32LayerID = pstChnThreadParam->u32LayerID;
    u32ChnID = pstChnThreadParam->u32ChnID;

    s32Ret = AX_VO_GetChnAttr(u32LayerID, u32ChnID, &stChnAttr);
    if (s32Ret) {
        SAMPLE_PRT("layer%d-chn%d AX_VO_GetChnAttr failed, s32Ret = 0x%x\n", u32LayerID, u32ChnID, s32Ret);
        goto exit;
    }
    SAMPLE_PRT("layer%d-chn%d u32Width = %d, u32Height = %d enImgFormat:0x%x, chnCompressInfo:%d %d\n",
               u32LayerID, u32ChnID,
               stChnAttr.stRect.u32Width,
               stChnAttr.stRect.u32Height,
               pstChnThreadParam->u32FrameFmt,
               pstChnThreadParam->chnCompressInfo.enCompressMode,
               pstChnThreadParam->chnCompressInfo.u32CompressLevel);

    stFrame.stCompressInfo = pstChnThreadParam->chnCompressInfo;
    stFrame.enImgFormat = pstChnThreadParam->u32FrameFmt;
    stFrame.u32Width = stChnAttr.stRect.u32Width;
    stFrame.u32Height = stChnAttr.stRect.u32Height;
    s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(stFrame.enImgFormat, &bytesPerPixel, &nPlanes);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, layer%d-chn%d , enImgFormat:0x%x\n", u32LayerID, u32ChnID, stFrame.enImgFormat);
        goto exit;
    }

    stFrame.u32PicStride[0] = ALIGN_UP(stChnAttr.stRect.u32Width, 8) * bytesPerPixel;
    if (nPlanes == 2) {
        if (AX_FORMAT_YUV422_SEMIPLANAR == stFrame.enImgFormat)
            u32FrameSize = stFrame.u32PicStride[0] * stFrame.u32Height * 4 / nPlanes;
        else
            u32FrameSize = stFrame.u32PicStride[0] * stFrame.u32Height * 3 / nPlanes;
    }
    else
        u32FrameSize = stFrame.u32PicStride[0] * stFrame.u32Height;

    while (!pstChnThreadParam->u32ThreadForceStop) {
        if (!pstChnThreadParam->u32SendCnt) {
            usleep(10000);
            continue;
        }

        BlkId = AX_POOL_GetBlock(pstChnThreadParam->u32UserPoolId, u32FrameSize, NULL);
        if (AX_INVALID_BLOCKID == BlkId) {
            //SAMPLE_PRT("layer%d-chn%d AX_POOL_GetBlock failed\n", u32LayerID, u32ChnID);
            usleep(10000);
            continue;
        }

        stFrame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(BlkId);
        stFrame.u64VirAddr[0] = 0;

        u64PhysAddr = AX_POOL_Handle2PhysAddr(BlkId);
        if (!u64PhysAddr) {
            SAMPLE_PRT("AX_POOL_Handle2PhysAddr failed, BlkId = 0x%x\n", BlkId);
            goto lbl0;
        }

        u64VirAddr = AX_SYS_Mmap(u64PhysAddr, u32FrameSize);
        if (!u64VirAddr) {
            SAMPLE_PRT("AX_SYS_Mmap failed, u64PhysAddr = 0x%llx, u32FrameSize = 0x%x\n", u64PhysAddr, u32FrameSize);
            goto lbl0;
        }

        if ((stFrame.stCompressInfo.enCompressMode == AX_COMPRESS_MODE_NONE)
            && (strcmp(pstChnThreadParam->chnFileName,"") == 0)) {
            SAMPLE_Fill_Color(stFrame.enImgFormat,
                              stFrame.u32Width,
                              stFrame.u32Height,
                              stFrame.u32PicStride[0],
                              u64VirAddr);
        } else {
            s32Ret = load_img_file(u64VirAddr, u32FrameSize, pstChnThreadParam->chnFileName);
            if (s32Ret) {
                SAMPLE_PRT("layer%d-chn%d load file failed, s32Ret = 0x%x\n",
                           u32LayerID, u32ChnID, s32Ret);
            }
        }

        stFrame.u32BlkId[0] = BlkId;
        stFrame.u32BlkId[1] = AX_INVALID_BLOCKID;
        s32Ret = AX_VO_SendFrame(u32LayerID, u32ChnID, &stFrame, -1);
        if (s32Ret)
            SAMPLE_PRT("layer%d-chn%d AX_VO_SendFrame failed, s32Ret = 0x%x\n", u32LayerID, u32ChnID, s32Ret);

        AX_SYS_Munmap(u64VirAddr, u32FrameSize);

        pstChnThreadParam->u32SendCnt -= 1;

        /* Query Channel Status */
        s32Ret = AX_VO_QueryChnStatus(u32LayerID, u32ChnID, &stStatus);
        if (s32Ret)
            SAMPLE_PRT("layer%d-chn%d AX_VO_QueryChnStatus failed, s32Ret = 0x%x\n", u32LayerID, u32ChnID, s32Ret);

        usleep(pstChnThreadParam->u32Udelay);

lbl0:
        AX_POOL_ReleaseBlock(BlkId);
    }

exit:
    SAMPLE_PRT("layer%d-chn%d exit, s32Ret = 0x%x\n", u32LayerID, u32ChnID, s32Ret);

    return NULL;
}

static AX_S32 SAMPLE_Fill_IMG(AX_S32 s32Fd, AX_U32 u32FrameSize, AX_U8 *u8Mem)
{
    AX_S32 s32Ret;

retry:
    s32Ret = read(s32Fd, u8Mem, u32FrameSize);
    if (s32Ret != u32FrameSize) {
        if (s32Ret < 0) {
            SAMPLE_PRT("read file failed, err: %s\n", strerror(errno));
            return s32Ret;
        }

        lseek(s32Fd, 0, SEEK_SET);
        goto retry;
    }

    return 0;
}

static AX_S32 SAMPLE_VO_POOL_FILL_IMG(SAMPLE_VO_CHN_THREAD_PARAM_T *pstChnThreadParam, AX_U32 u32Width, AX_U32 u32Height,
                                      AX_U32 u32FNum, AX_VIDEO_FRAME_T *pstFrames)
{
    AX_S32 i, s32Fd, s32Ret;
    AX_U32 u32FrameSize;
    AX_BLK BlkId;
    AX_VOID *u64VirAddr;
    AX_U64 u64PhysAddr;
    AX_CHAR *pPath;
    AX_U32 u32PoolId = -1;
    AX_U32 u32Stride = 0;
    AX_IMG_FORMAT_E enImgFormat = AX_FORMAT_INVALID;
    AX_U32 bytesPerPixel = 0, nPlanes = 0;


    if (pstChnThreadParam == NULL) {
        SAMPLE_PRT("pstChnThreadParam == NULL\n");
        return -1;
    }

    pPath = pstChnThreadParam->chnFileName;
    u32PoolId = pstChnThreadParam->u32UserPoolId;
    enImgFormat = pstChnThreadParam->u32FrameFmt;

    s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(enImgFormat, &bytesPerPixel, &nPlanes);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, enImgFormat:0x%x\n", enImgFormat);
        return -1;
    }

    u32Stride = ALIGN_UP(u32Width, 8) * bytesPerPixel;
    if (nPlanes == 2) {
        if (AX_FORMAT_YUV422_SEMIPLANAR == enImgFormat)
            u32FrameSize = u32Stride * u32Height * 4 / nPlanes;
        else
            u32FrameSize = u32Stride * u32Height * 3 / nPlanes;
    }
    else
        u32FrameSize = u32Stride * u32Height;

    s32Fd = open(pPath, O_RDONLY);
    if (s32Fd < 0) {
        SAMPLE_PRT("open %s failed, %s\n", pPath, strerror(errno));
        return -1;
    }

    for (i = 0; i < u32FNum; i++) {
        BlkId = AX_POOL_GetBlock(u32PoolId, u32FrameSize, NULL);
        if (AX_INVALID_BLOCKID == BlkId) {
            s32Ret = -1;
            SAMPLE_PRT("get block failed from pool%d, i = %d\n", u32PoolId, i);
            goto exit;
        }

        u64PhysAddr = AX_POOL_Handle2PhysAddr(BlkId);
        if (!u64PhysAddr) {
            s32Ret = -1;
            SAMPLE_PRT("AX_POOL_Handle2PhysAddr failed, BlkId = 0x%x\n", BlkId);
            goto exit;
        }

        u64VirAddr = AX_SYS_Mmap(u64PhysAddr, u32FrameSize);
        if (!u64VirAddr) {
            s32Ret = -1;
            SAMPLE_PRT("AX_SYS_Mmap failed, u64PhysAddr = 0x%llx, u32FrameSize = 0x%x\n", u64PhysAddr, u32FrameSize);
            goto exit;
        }

        s32Ret = SAMPLE_Fill_IMG(s32Fd, u32FrameSize, u64VirAddr);
        if (s32Ret) {
            s32Ret = -1;
            SAMPLE_PRT("SAMPLE_Fill_IMG failed, i = %d\n", i);
            goto exit;
        }

        AX_SYS_Munmap(u64VirAddr, u32FrameSize);

        pstFrames[i].enImgFormat = enImgFormat;
        pstFrames[i].u32Width = u32Width;
        pstFrames[i].u32Height = u32Height;
        pstFrames[i].u32PicStride[0] = u32Stride;
        pstFrames[i].u64PhyAddr[0] = u64PhysAddr;
        pstFrames[i].u32BlkId[0] = BlkId;
        pstFrames[i].u32BlkId[1] = AX_INVALID_BLOCKID;
    }

exit:
    close(s32Fd);

    return s32Ret;
}

static AX_VOID *SAMPLE_VO_PLAY_THREAD(AX_VOID *pData)
{
    AX_S32 i = 0, s32Ret = 0;
    AX_VIDEO_FRAME_T stFrames[SAMPLE_VO_FRAME_MAX] = {0}, *pstFrame;
    AX_U32 u32LayerID, u32ChnID;
    AX_U32 u32FrameRate, u32FrameMax = SAMPLE_VO_FRAME_MAX;
    AX_U64 u64PTS, u64SeqNum = 0;
    AX_VO_CHN_ATTR_T stChnAttr;
    SAMPLE_VO_CHN_THREAD_PARAM_T *pstChnThreadParam = (SAMPLE_VO_CHN_THREAD_PARAM_T *)pData;

    u32LayerID = pstChnThreadParam->u32LayerID;
    u32ChnID = pstChnThreadParam->u32ChnID;

    s32Ret = AX_VO_GetChnAttr(u32LayerID, u32ChnID, &stChnAttr);
    if (s32Ret) {
        SAMPLE_PRT("layer%d-chn%d AX_VO_GetChnAttr failed, s32Ret = 0x%x\n", u32LayerID, u32ChnID, s32Ret);
        goto exit;
    }
    SAMPLE_PRT("layer%d-chn%d u32Width = %d, u32Height = %d\n",
               u32LayerID, u32ChnID,
               stChnAttr.stRect.u32Width,
               stChnAttr.stRect.u32Height);

    if ((pstChnThreadParam->u32FrameMax > 0) && (pstChnThreadParam->u32FrameMax < SAMPLE_VO_FRAME_MAX)) {
        u32FrameMax = pstChnThreadParam->u32FrameMax;
    }

    s32Ret = SAMPLE_VO_POOL_FILL_IMG(pstChnThreadParam,
                                     stChnAttr.stRect.u32Width, stChnAttr.stRect.u32Height,
                                     u32FrameMax, stFrames);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_POOL_FILL_IMG failed\n");
        goto exit;
    }

    u32FrameRate = pstChnThreadParam->u32FrameRate ? pstChnThreadParam->u32FrameRate : 30;

    SAMPLE_PRT("u32FrameRate = %d, u32FrameMax = %d\n", u32FrameRate, u32FrameMax);

    while (!pstChnThreadParam->u32ThreadForceStop) {
        pstFrame = &stFrames[i % u32FrameMax];
        pstFrame->u64PTS = u64PTS;
        pstFrame->u64SeqNum = u64SeqNum;
        pstFrame->u32FrameFlag |= AX_FRM_FLG_FR_CTRL;

        s32Ret = AX_VO_SendFrame(u32LayerID, u32ChnID, pstFrame, -1);
        if (s32Ret) {
            SAMPLE_PRT("layer%d-chn%d AX_VO_SendFrame failed, s32Ret = 0x%x\n", u32LayerID, u32ChnID, s32Ret);
        }

        u64PTS += 1000000 / u32FrameRate;
        u64SeqNum += 1;
        i++;
    }

exit:
    SAMPLE_PRT("layer%d-chn%d exit, s32Ret = 0x%x\n", u32LayerID, u32ChnID, s32Ret);

    return NULL;
}

static AX_VOID *SAMPLE_VO_GET_LAYER_FRAME_THREAD(AX_VOID *pData)
{
    AX_S32 i, s32Ret = 0;
    AX_VIDEO_FRAME_T stFrame = {0};
    AX_U32 u32LayerID;
    AX_U32 u32GetCnt = 0;
    AX_S32 s32Fd = -1;
    fd_set fds;
    FILE *pstFile = NULL;
    struct timeval timeout = { .tv_sec = 1, .tv_usec = 0 };
    SAMPLE_VO_CHN_THREAD_PARAM_T *pstChnThreadParam;
    SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T *pstThreadParam = (SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T *)pData;
    u32LayerID = pstThreadParam->u32LayerID;

    s32Ret = AX_VO_GetLayerFd(u32LayerID, &s32Fd);
    if (s32Ret) {
        SAMPLE_PRT("AX_VO_GetLayerFd failed, s32Ret = 0x%x\n", s32Ret);
        return NULL;
    }

    FD_ZERO(&fds);
    FD_SET(s32Fd, &fds);

    while (!pstThreadParam->u32ThreadForceStop) {
        s32Ret = select(s32Fd + 1, &fds, NULL, NULL, &timeout);
        if (s32Ret < 0) {
            SAMPLE_PRT("select err\n");
            break;

        } else if (0 == s32Ret) {
            FD_SET(s32Fd, &fds);
            continue;

        } else {
            if (FD_ISSET(s32Fd, &fds)) {
                memset(&stFrame, 0, sizeof(stFrame));
                s32Ret = AX_VO_GetLayerFrame(u32LayerID, &stFrame, 0);
                if (s32Ret)
                    continue;

                SAMPLE_VO_SAVE_FILE(u32LayerID, &stFrame, &pstFile);

                u32GetCnt += 1;
                s32Ret = AX_VO_ReleaseLayerFrame(u32LayerID, &stFrame);
                if (s32Ret)
                    SAMPLE_PRT("AX_VO_ReleaseLayerFrame failed, u32LayerID = %d, s32Ret = 0x%x\n", u32LayerID, s32Ret);

                if (u32GetCnt == pstThreadParam->u32FrameCnt)
                    break;
            }
        }
    }

    for (i = 0; i < AX_VO_CHN_MAX; i++) {
        pstChnThreadParam = &pstThreadParam->stVoChnThreadParm[i];
        if (pstChnThreadParam->ThreadID)
            pstChnThreadParam->u32ThreadForceStop = 1;
        else
            break;
    }

    if (pstFile)
        fclose(pstFile);
    SAMPLE_PRT("layer%d exit\n", u32LayerID);

    return NULL;
}

static AX_VOID *SAMPLE_VO_GET_CHN_FRAME_THREAD(AX_VOID *pData)
{
    AX_S32 s32Ret = 0;
    AX_VIDEO_FRAME_T stFrame;
    AX_U32 u32LayerID, u32ChnID;
    AX_VOID *pVirAddr;
    AX_U32 u32GetCnt = 0, u32FrameSize = 0;
    AX_CHAR OutFile[128] = {0};
    FILE *pstFile = NULL;
    SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T *pstThreadParam = (SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T *)pData;

    u32LayerID = pstThreadParam->u32LayerID;
    u32ChnID = pstThreadParam->u32ChnID;

    SAMPLE_PRT("layer%d-chn%d enter\n", u32LayerID, u32ChnID);

    while (!pstThreadParam->u32ThreadForceStop) {
        memset(&stFrame, 0, sizeof(stFrame));
        s32Ret = AX_VO_GetChnFrame(u32LayerID, u32ChnID, &stFrame, -1);
        if (s32Ret)
            continue;

        if (stFrame.enImgFormat == AX_FORMAT_YUV420_SEMIPLANAR)
            u32FrameSize = stFrame.u32PicStride[0] * stFrame.u32Height * 3 / 2;

        pVirAddr = AX_SYS_Mmap(stFrame.u64PhyAddr[0], u32FrameSize);
        if (!pVirAddr) {
            SAMPLE_PRT("AX_SYS_Mmap failed\n");
            goto lbl0;
        }

        SAMPLE_PRT("pVirAddr: 0x%px, u64PhyAddr: 0x%llx, u32FrameSize: 0x%x\n", pVirAddr, stFrame.u64PhyAddr[0], u32FrameSize);

        sprintf(OutFile, "layer%d_chn%d_%d_%d_%d.yuv", u32LayerID, u32ChnID, stFrame.u32Width, stFrame.u32Height, u32GetCnt);
        pstFile = fopen(OutFile, "wb");
        if (pstFile) {
            fwrite(pVirAddr, u32FrameSize, 1, pstFile);
            fclose(pstFile);
            SAMPLE_PRT("write %s done\n", OutFile);
        }

        s32Ret = AX_SYS_Munmap(pVirAddr, u32FrameSize);
        if (s32Ret)
            SAMPLE_PRT("AX_SYS_Munmap failed, s32Ret=0x%x\n", s32Ret);

lbl0:
        u32GetCnt += 1;
        s32Ret = AX_VO_ReleaseChnFrame(u32LayerID, u32ChnID, &stFrame);
        if (s32Ret)
            SAMPLE_PRT("AX_VO_ReleaseLayerFrame failed, u32LayerID = %d, s32Ret = 0x%x\n", u32LayerID, s32Ret);

        if (u32GetCnt == pstThreadParam->u32FrameCnt)
            break;
    }

    SAMPLE_PRT("layer%d exit\n", u32LayerID);

    return NULL;
}

static AX_VOID *SAMPLE_VO_WBC_THREAD(AX_VOID *pData)
{
    AX_S32 s32Ret = 0;
    AX_U32 u32WbcId = 0;
    AX_U32 u32GetCnt = 0, u32FrameSize = 0;
    AX_S32 s32Fd = -1;
    AX_VIDEO_FRAME_T stFrame = {0};
    AX_VOID *pVirAddr;
    AX_CHAR OutFile[128] = {0};
    fd_set fds;
    FILE *pstFile = NULL;
    struct timeval timeout = { .tv_sec = 1, .tv_usec = 0 };
    SAMPLE_VO_WBC_THREAD_PARAM_T *pstThreadParam = (SAMPLE_VO_WBC_THREAD_PARAM_T *)pData;

    u32WbcId = pstThreadParam->u32Wbc;

    s32Ret = AX_VO_GetWbcFd(u32WbcId, &s32Fd);
    if (s32Ret) {
        SAMPLE_PRT("AX_VO_GetLayerFd failed, s32Ret = 0x%x\n", s32Ret);
        return NULL;
    }

    FD_ZERO(&fds);
    FD_SET(s32Fd, &fds);

    while (!pstThreadParam->u32ThreadForceStop) {
        s32Ret = select(s32Fd + 1, &fds, NULL, NULL, &timeout);
        if (s32Ret < 0) {
            SAMPLE_PRT("select err\n");
            break;

        } else if (0 == s32Ret) {
            FD_SET(s32Fd, &fds);
            continue;

        } else {
            if (FD_ISSET(s32Fd, &fds)) {
                memset(&stFrame, 0, sizeof(stFrame));
                s32Ret = AX_VO_GetWBCFrame(u32WbcId, &stFrame, 0);
                if (s32Ret) {
                    continue;
                }

                if (stFrame.enImgFormat == AX_FORMAT_YUV420_SEMIPLANAR) {
                    u32FrameSize = stFrame.u32PicStride[0] * stFrame.u32Height * 3 / 2;
                } else if (stFrame.enImgFormat == AX_FORMAT_RGB888) {
                    u32FrameSize = stFrame.u32PicStride[0] * stFrame.u32Height * 3;
                } else if (stFrame.enImgFormat == AX_FORMAT_ARGB8888) {
                    u32FrameSize = stFrame.u32PicStride[0] * stFrame.u32Height * 4;
                } else {
                    SAMPLE_PRT("save of this data format is not supported, fmt: 0x%x\n", stFrame.enImgFormat);
                    goto lbl0;
                }

                pVirAddr = AX_SYS_Mmap(stFrame.u64PhyAddr[0], u32FrameSize);
                if (!pVirAddr) {
                    SAMPLE_PRT("AX_SYS_Mmap failed\n");
                    goto lbl0;
                }

                SAMPLE_PRT("pVirAddr: 0x%px, u64PhyAddr: 0x%llx, u32FrameSize: 0x%x\n", pVirAddr, stFrame.u64PhyAddr[0], u32FrameSize);

                if (!pstFile) {
                    sprintf(OutFile, "wbc%d_%d_%d_%d.yuv", u32WbcId, stFrame.u32Width, stFrame.u32Height, pstThreadParam->u32FrameCnt);
                    pstFile = fopen(OutFile, "wb");
                    if (!pstFile) {
                        SAMPLE_PRT("fopen %s failed, err: %s\n", OutFile, strerror(errno));
                        goto lbl1;
                    }
                }

                fwrite(pVirAddr, u32FrameSize, 1, pstFile);

lbl1:
                s32Ret = AX_SYS_Munmap(pVirAddr, u32FrameSize);
                if (s32Ret) {
                    SAMPLE_PRT("AX_SYS_Munmap failed, s32Ret=0x%x\n", s32Ret);
                }

lbl0:
                u32GetCnt += 1;
                s32Ret = AX_VO_ReleaseWBCFrame(u32WbcId, &stFrame);
                if (s32Ret)
                    SAMPLE_PRT("AX_VO_ReleaseLayerFrame failed, u32WbcId = %d, s32Ret = 0x%x\n", u32WbcId, s32Ret);

                if (pstThreadParam->u32FrameCnt && u32GetCnt == pstThreadParam->u32FrameCnt) {
                    break;
                }
            }
        }
    }

    if (pstFile) {
        fclose(pstFile);
    }

    SAMPLE_PRT("Wbc%d exit\n", u32WbcId);

    return NULL;
}

static AX_S32 gLoopExit = 0;

AX_VOID SAMPLE_VO_SigInt(AX_S32 s32SigNo)
{
    SAMPLE_PRT("Catch signal %d\n", s32SigNo);
    gLoopExit = 1;
}

AX_VOID SAMPLE_VO_SigStop(AX_S32 s32SigNo)
{
    SAMPLE_PRT("Catch signal %d\n", s32SigNo);
    gLoopExit = 1;
}

AX_S32 SAMPLE_VO_CheckSig(AX_VOID)
{
    return gLoopExit;
}

AX_VOID SAMPLE_VO_Usage(AX_CHAR *name)
{
    SAMPLE_PRT("command:\n");
    SAMPLE_PRT("\t-p: play\n");
    SAMPLE_PRT("\tnumber: select test case number for play in /opt/etc/vo.ini\n");
    SAMPLE_PRT("Example:\n");
    SAMPLE_PRT("\tsample_vo -p 10\n");
    SAMPLE_PRT("\n");

    SAMPLE_PRT("\t-l: get videolayer Image\n");
    SAMPLE_PRT("\tnumber: select test case number for videolayer in /opt/etc/vo.ini\n");
    SAMPLE_PRT("Example:\n");
    SAMPLE_PRT("\tsample_vo -l 1\n");
    SAMPLE_PRT("\n");

    SAMPLE_PRT("\t-d: videolayer dispaly test\n");
    SAMPLE_PRT("\tnumber: select test case number for display in /opt/etc/vo.ini\n");;
    SAMPLE_PRT("Example:\n");
    SAMPLE_PRT("\tsample_vo -d 0\n");
    SAMPLE_PRT("\n");

    SAMPLE_PRT("\t-e: enumerate resolutions of dispaly device.\n");
    SAMPLE_PRT("\tnumber: supported display device number which is 0 1 or 2\n");;
    SAMPLE_PRT("Example:\n");
    SAMPLE_PRT("\tsample_vo -e 0\n");
    SAMPLE_PRT("\n");

    SAMPLE_PRT("\t-c: AX_VO_CscMatrix use sample\n");
    SAMPLE_PRT("Example:\n");
    SAMPLE_PRT("\tsample_vo -c\n");
    SAMPLE_PRT("\n");
}

AX_S32 SAMPLE_VO_LAYER(SAMPLE_VO_LAYER_CONFIG_S *pstLayerConf)
{
    AX_S32 i, s32Chns, s32Ret = 0;
    AX_U32 u32Row, u32Col;
    AX_U32 u32ChnWidth, u32ChnHeight;
    AX_U32 u32LayerWidth = 0;
    AX_U32 u32LayerHeight = 0;
    AX_U64 u64BlkSize = 0, u64PixSize = 0;
    AX_VO_VIDEO_LAYER_ATTR_T *pstVoLayerAttr = &pstLayerConf->stVoLayerAttr;
    SAMPLE_VO_CHN_THREAD_PARAM_T *pstChnThreadParam;
    SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T stLayerThreadParam = {.u32FrameCnt = 1,};
    AX_U32 bytesPerPixel = 0, nPlanes = 0;

    u32LayerWidth = pstVoLayerAttr->stImageSize.u32Width;
    u32LayerHeight = pstVoLayerAttr->stImageSize.u32Height;

    s32Ret = SAMPLE_VO_WIN_INFO(u32LayerWidth, u32LayerHeight, pstLayerConf->enVoMode, &u32Row, &u32Col,
                                &u32ChnWidth, &u32ChnHeight);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_WIN_INFO failed, s32Ret = 0x%x\n", s32Ret);
        goto exit0;
    }

    SAMPLE_PRT("enPixFmt:0x%x, enChnFrmFmt:0x%x\n", pstVoLayerAttr->enPixFmt, pstLayerConf->enChnFrmFmt);
    u64PixSize = (AX_U64)ALIGN_UP(u32LayerWidth, 8) * u32LayerHeight;
    s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(pstVoLayerAttr->enPixFmt, &bytesPerPixel, &nPlanes);
    if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, enPixFmt:0x%x\n", pstVoLayerAttr->enPixFmt);
            goto exit0;
    }

    if (AX_FORMAT_YUV422_SEMIPLANAR == pstVoLayerAttr->enPixFmt)
        u64BlkSize = u64PixSize * 4 / nPlanes;
    else
        u64BlkSize = u64PixSize * 3 / nPlanes;

    s32Ret = SAMPLE_VO_CREATE_POOL(3, u64BlkSize, 512, &pstLayerConf->u32LayerPoolId);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, s32Ret = 0x%x\n", s32Ret);
        goto exit0;
    }

    s32Chns = u32Row * u32Col;
    u64PixSize = (AX_U64)ALIGN_UP(u32ChnWidth, 8) * u32ChnHeight;
    s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(pstLayerConf->enChnFrmFmt, &bytesPerPixel, &nPlanes);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, enChnFrmFmt:0x%x\n", pstLayerConf->enChnFrmFmt);
        goto exit0;
    }

    if (AX_FORMAT_YUV422_SEMIPLANAR == pstLayerConf->enChnFrmFmt)
        u64BlkSize = u64PixSize * 4 / nPlanes;
    else
        u64BlkSize = u64PixSize * 3 / nPlanes;

    s32Ret = SAMPLE_VO_CREATE_POOL(s32Chns * 2, u64BlkSize, 512, &pstLayerConf->u32ChnPoolId);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, s32Ret = 0x%x\n", s32Ret);
        goto exit1;
    }

    pstVoLayerAttr->u32PoolId = pstLayerConf->u32LayerPoolId;

    SAMPLE_PRT("u32LayerPoolId = %d, u32ChnPoolId = %d\n", pstLayerConf->u32LayerPoolId, pstLayerConf->u32ChnPoolId);

    s32Ret = SAMPLE_COMM_VO_StartLayer(pstLayerConf);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartLayer failed\n");
        goto exit2;
    }

    s32Ret = SAMPLE_COMM_VO_StartChn(pstLayerConf);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartChn failed, layer = %d\n", pstLayerConf->u32VoLayer);
        goto exit3;
    }

    stLayerThreadParam.u32LayerID = pstLayerConf->u32VoLayer;
    stLayerThreadParam.u32ThreadForceStop = 0;
    pthread_create(&stLayerThreadParam.ThreadID, NULL, SAMPLE_VO_GET_LAYER_FRAME_THREAD, &stLayerThreadParam);

    for (i = 0; i < pstLayerConf->u32ChnNr; i++) {
        pstChnThreadParam = &stLayerThreadParam.stVoChnThreadParm[i];
        pstChnThreadParam->u32LayerID = pstLayerConf->u32VoLayer;
        pstChnThreadParam->u32ChnID = i;
        pstChnThreadParam->u32Udelay = 20000;
        pstChnThreadParam->chnCompressInfo = pstLayerConf->chnCompressInfo;
        strcpy(pstChnThreadParam->chnFileName, pstLayerConf->chnFileName);
        pstChnThreadParam->u32SendCnt = stLayerThreadParam.u32FrameCnt;
        pstChnThreadParam->u32ThreadForceStop = 0;
        pstChnThreadParam->u32UserPoolId = pstLayerConf->u32ChnPoolId;
        pstChnThreadParam->u32FrameFmt = pstLayerConf->enChnFrmFmt;
        pthread_create(&pstChnThreadParam->ThreadID, NULL, SAMPLE_VO_CHN_THREAD, pstChnThreadParam);
    }

    while (!gLoopExit) {
        sleep(1);
    }

    stLayerThreadParam.u32ThreadForceStop = 1;
    pthread_join(stLayerThreadParam.ThreadID, NULL);
    SAMPLE_PRT("layer%d-thread get frame done\n", pstLayerConf->u32VoLayer);

    for (i = 0; i < s32Chns; i++) {
        pstChnThreadParam = &stLayerThreadParam.stVoChnThreadParm[i];
        if (pstChnThreadParam->ThreadID) {
            pstChnThreadParam->u32ThreadForceStop = 1;
            pthread_join(pstChnThreadParam->ThreadID, NULL);
            SAMPLE_PRT("layer%d-chn%d-thread send frame done\n", pstLayerConf->u32VoLayer, i);
        }
    }

    SAMPLE_PRT("VO test Finished success!\n");

    SAMPLE_COMM_VO_StopChn(pstLayerConf);

exit3:
    SAMPLE_COMM_VO_StopLayer(pstLayerConf);
exit2:
    SAMPLE_VO_POOL_DESTROY(pstLayerConf->u32LayerPoolId);
exit1:
    SAMPLE_VO_POOL_DESTROY(pstLayerConf->u32ChnPoolId);
exit0:
    SAMPLE_PRT("layer%d exit done\n", pstLayerConf->u32VoLayer);

    return s32Ret;
}

AX_S32 SAMPLE_VO_LAYER_DISPLAY(SAMPLE_VO_CONFIG_S *pstVoConf)
{
    AX_BOOL bNeedWbc = AX_FALSE;
    AX_S32 i, j, s32Chns, s32Ret = 0;
    AX_U32 u32Row, u32Col;
    AX_U32 u32ChnWidth, u32ChnHeight;
    AX_U32 u32LayerWidth = 0;
    AX_U32 u32LayerHeight = 0;
    AX_U64 u64BlkSize = 0, u64PixSize = 0, u64BlkNr;
    SAMPLE_VO_DEV_CONFIG_S *pstVoDevConf;
    SAMPLE_VO_LAYER_CONFIG_S *pstVoLayerConf;
    AX_VO_VIDEO_LAYER_ATTR_T *pstVoLayerAttr;
    SAMPLE_VO_CHN_THREAD_PARAM_T *pstChnThreadParam;
    SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T stLayerThreadParam[SAMPLE_VO_DEV_MAX];
    SAMPLE_VO_WBC_THREAD_PARAM_T stWbcThreadParam[SAMPLE_VO_DEV_MAX] = {0,};
    AX_U32 bytesPerPixel = 0, nPlanes = 0;

    s32Ret = AX_VO_Init();
    if (s32Ret) {
        SAMPLE_PRT("AX_VO_Init failed, s32Ret = 0x%x\n", s32Ret);
        return s32Ret;
    }

    pstVoConf->u32LayerNr = pstVoConf->u32VDevNr;
    if (pstVoConf->u32BindMode) {
        pstVoConf->u32LayerNr = 1;
    }

    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoDevConf = &pstVoConf->stVoDev[i];
        pstVoLayerConf = &pstVoConf->stVoLayer[i];

        pstVoLayerConf->u64KeepChnPrevFrameBitmap0 = ~0x0UL;
        pstVoLayerConf->u64KeepChnPrevFrameBitmap1 = ~0x0UL;
        if (pstVoConf->u32BindMode) {
            for (j = 0; j < pstVoConf->u32VDevNr; j++) {
                pstVoLayerConf->bindVoDev[j] = pstVoConf->stVoDev[j].u32VoDev;
                if (pstVoConf->stVoDev[j].bWbcEn) {
                    bNeedWbc = pstVoConf->stVoDev[j].bWbcEn;
                }
            }
        } else {
            pstVoLayerConf->bindVoDev[0] = pstVoDevConf->u32VoDev;
            bNeedWbc = pstVoDevConf->bWbcEn;
        }

        pstVoLayerAttr = &pstVoLayerConf->stVoLayerAttr;

        u32LayerWidth = pstVoLayerAttr->stImageSize.u32Width;
        u32LayerHeight = pstVoLayerAttr->stImageSize.u32Height;

        SAMPLE_VO_WIN_INFO(u32LayerWidth, u32LayerHeight, pstVoLayerConf->enVoMode,
                           &u32Row, &u32Col, &u32ChnWidth, &u32ChnHeight);

        s32Chns = u32Row * u32Col;
        u64PixSize = (AX_U64)ALIGN_UP(u32ChnWidth, 8) * u32ChnHeight;
        s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(pstVoLayerConf->enChnFrmFmt, &bytesPerPixel, &nPlanes);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, i:%d, enChnFrmFmt:0x%x\n", i, pstVoLayerConf->enChnFrmFmt);
            goto exit0;
        }

        if (AX_FORMAT_YUV422_SEMIPLANAR == pstVoLayerConf->enChnFrmFmt)
            u64BlkSize = u64PixSize * 4 / nPlanes;
        else
            u64BlkSize = u64PixSize * 3 / nPlanes;

        s32Ret = SAMPLE_VO_CREATE_POOL(s32Chns * 2, u64BlkSize, 512, &pstVoLayerConf->u32ChnPoolId);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, s32Ret = 0x%x\n", s32Ret);
            goto exit0;
        }

        u64PixSize = (AX_U64)ALIGN_UP(u32LayerWidth, 8) * ALIGN_UP(u32LayerHeight, 2);
        s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(pstVoLayerConf->stVoLayerAttr.enPixFmt, &bytesPerPixel, &nPlanes);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, i:%d, enPixFmt:0x%x\n", i, pstVoLayerConf->stVoLayerAttr.enPixFmt);
            goto exit0;
        }

        if (AX_FORMAT_YUV422_SEMIPLANAR == pstVoLayerConf->stVoLayerAttr.enPixFmt)
            u64BlkSize = u64PixSize * 4 / nPlanes;
        else
            u64BlkSize = u64PixSize * 3 / nPlanes;
        u64BlkNr = bNeedWbc ? 8 : 4;
        s32Ret = SAMPLE_VO_CREATE_POOL(u64BlkNr, u64BlkSize, 512, &pstVoLayerConf->u32LayerPoolId);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, i:%d, s32Ret:0x%x\n", i, s32Ret);
            goto exit0;
        }

        pstVoLayerAttr->u32FifoDepth = pstVoLayerConf->u32FifoDepth;
        pstVoLayerAttr->u32PoolId = pstVoLayerConf->u32LayerPoolId;

        SAMPLE_PRT("u32LayerPoolId = %d, u32ChnPoolId = %d\n", pstVoLayerConf->u32LayerPoolId, pstVoLayerConf->u32ChnPoolId);
    }

    s32Ret = SAMPLE_COMM_VO_StartVO(pstVoConf);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartVO failed, i:%d, s32Ret:0x%x\n", i, s32Ret);
        goto exit0;
    }

    for (i = 0; i < pstVoConf->u32VDevNr; i++) {
        pstVoDevConf = &pstVoConf->stVoDev[i];
        if (pstVoDevConf->bWbcEn) {
            stWbcThreadParam[i].u32Wbc = pstVoDevConf->u32VoDev;
            stWbcThreadParam[i].u32FrameCnt = pstVoDevConf->u32WbcFrmaeNr;
            pthread_create(&stWbcThreadParam[i].ThreadID, NULL, SAMPLE_VO_WBC_THREAD, &stWbcThreadParam[i]);
        }
    }

    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoLayerConf = &pstVoConf->stVoLayer[i];
        pstVoLayerAttr = &pstVoLayerConf->stVoLayerAttr;

        for (j = 0; j < s32Chns; j++) {
            stLayerThreadParam[i].u32FrameCnt = ~0;
            pstChnThreadParam = &stLayerThreadParam[i].stVoChnThreadParm[j];
            pstChnThreadParam->u32LayerID = pstVoLayerConf->u32VoLayer;
            pstChnThreadParam->u32ChnID = j;
            pstChnThreadParam->u32Udelay = 5000;
            pstChnThreadParam->u32SendCnt = stLayerThreadParam[i].u32FrameCnt;
            pstChnThreadParam->u32ThreadForceStop = 0;
            pstChnThreadParam->chnCompressInfo = pstVoLayerConf->chnCompressInfo;
            strcpy(pstChnThreadParam->chnFileName, pstVoLayerConf->chnFileName);
            pstChnThreadParam->u32UserPoolId = pstVoLayerConf->u32ChnPoolId;
            pstChnThreadParam->u32FrameFmt = pstVoLayerConf->enChnFrmFmt;
            pthread_create(&pstChnThreadParam->ThreadID, NULL, SAMPLE_VO_CHN_THREAD, pstChnThreadParam);
        }
    }

    while (!gLoopExit) {
        sleep(1);
    }

    for (i = 0; i < pstVoConf->u32VDevNr; i++) {
        pstVoDevConf = &pstVoConf->stVoDev[i];
        if (pstVoDevConf->bWbcEn && stWbcThreadParam[i].ThreadID) {
            stWbcThreadParam[i].u32ThreadForceStop = 1;
            pthread_join(stWbcThreadParam[i].ThreadID, NULL);
            SAMPLE_PRT("wbc%d done\n", stWbcThreadParam[i].u32Wbc);
        }
    }

    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoLayerConf = &pstVoConf->stVoLayer[i];
        pstVoLayerAttr = &pstVoLayerConf->stVoLayerAttr;

        for (j = 0; j < s32Chns; j++) {
            pstChnThreadParam = &stLayerThreadParam[i].stVoChnThreadParm[j];
            if (pstChnThreadParam->ThreadID) {
                pstChnThreadParam->u32ThreadForceStop = 1;
                pthread_join(pstChnThreadParam->ThreadID, NULL);
                SAMPLE_PRT("layer%d-chn%d-thread send frame done\n", pstVoLayerConf->u32VoLayer, j);
            }
        }
    }

    SAMPLE_COMM_VO_StopVO(pstVoConf);

    SAMPLE_PRT("VO test Finished success!\n");

exit0:
    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoLayerConf = &pstVoConf->stVoLayer[i];
        SAMPLE_VO_POOL_DESTROY(pstVoLayerConf->u32ChnPoolId);
        SAMPLE_VO_POOL_DESTROY(pstVoLayerConf->u32LayerPoolId);
    }

    AX_VO_Deinit();

    return s32Ret;
}

AX_VOID SAMPLE_VO_DISPLAY_MODE_PRINT(AX_U32 u32DevId, AX_VO_DISPLAY_MODE_T *pstDisplayMode)
{
    AX_S32 i, s32Offs, s32Len;
    AX_CHAR cBuf[128];
    AX_U32 u32Width, u32Height, u32Refresh, u32Type, u32Flags;

    for (i = 0; i < pstDisplayMode->u16ModesNum; i++) {
        u32Width = pstDisplayMode->stModes[i].u16Width;
        u32Height = pstDisplayMode->stModes[i].u16Height;
        u32Refresh = pstDisplayMode->stModes[i].u16Refresh;
        u32Type = pstDisplayMode->stModes[i].u16Type;
        u32Flags = pstDisplayMode->stModes[i].u32Flags;

        s32Offs = 0;
        s32Len = sizeof(cBuf);

        if (!(u32Flags & VO_DISPLAY_MODE_FLAG_INTERLACE))
            s32Offs = snprintf(cBuf + s32Offs, s32Len - s32Offs, "display%d-mode: %dx%d", u32DevId, u32Width, u32Height);
        else
            s32Offs = snprintf(cBuf + s32Offs, s32Len - s32Offs, "display%d-mode: %dx%di", u32DevId, u32Width, u32Height);

        if (u32Type == VO_DISPLAY_TYPE_VIRTUAL)
            s32Offs = snprintf(cBuf + s32Offs, s32Len - s32Offs, "@%d, DPI-BT\n", u32Refresh);
        else if (u32Type == VO_DISPLAY_TYPE_DSI)
            s32Offs = snprintf(cBuf + s32Offs, s32Len - s32Offs, "@%d, DSI\n", u32Refresh);
        else
            s32Offs = snprintf(cBuf + s32Offs, s32Len - s32Offs, "@%d, unsupported\n", u32Refresh);

        printf("%s", cBuf);
    }
    SAMPLE_PRT("VO test Finished success!\n");
}

AX_S32 SAMPLE_VO_PLAY(SAMPLE_VO_CONFIG_S *pstVoConf)
{
    AX_BOOL bNeedWbc = AX_FALSE;
    AX_S32 i, j, s32Chns, s32Ret = 0;
    AX_U32 u32ChnFrameNr;
    AX_U32 u32Row, u32Col;
    AX_U32 u32ChnWidth, u32ChnHeight;
    AX_U32 u32LayerWidth = 0;
    AX_U32 u32LayerHeight = 0;
    AX_U64 u64BlkSize = 0, u64PixSize = 0, u64BlkNr;
    SAMPLE_VO_DEV_CONFIG_S *pstVoDevConf;
    SAMPLE_VO_LAYER_CONFIG_S *pstVoLayerConf;
    SAMPLE_VO_GRAPHIC_CONFIG_S *pstGraphicConf;
    SAMPLE_VO_CURSOR_CONFIG_S *pstCursorLayerConf;
    AX_VO_VIDEO_LAYER_ATTR_T *pstVoLayerAttr;
    SAMPLE_VO_CHN_THREAD_PARAM_T *pstChnThreadParam;
    SAMPLE_VO_VIDEOLAYER_THREAD_PARAM_T stLayerThreadParam[SAMPLE_VO_DEV_MAX] = {0,};
    SAMPLE_VO_WBC_THREAD_PARAM_T stWbcThreadParam[SAMPLE_VO_DEV_MAX] = {0,};
    AX_U32 bytesPerPixel = 0, nPlanes = 0;

    s32Ret = AX_VO_Init();
    if (s32Ret) {
        SAMPLE_PRT("AX_VO_Init failed, s32Ret = 0x%x\n", s32Ret);
        return s32Ret;
    }

    pstVoConf->u32LayerNr = pstVoConf->u32VDevNr;
    if (pstVoConf->u32BindMode) {
        pstVoConf->u32LayerNr = 1;
    }

    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoDevConf = &pstVoConf->stVoDev[i];
        pstVoLayerConf = &pstVoConf->stVoLayer[i];
        pstVoLayerAttr = &pstVoLayerConf->stVoLayerAttr;

        if (pstVoConf->u32BindMode) {
            for (j = 0; j < pstVoConf->u32VDevNr; j++) {
                pstVoLayerConf->bindVoDev[j] = pstVoConf->stVoDev[j].u32VoDev;
                if (pstVoConf->stVoDev[j].bWbcEn) {
                    bNeedWbc = pstVoConf->stVoDev[j].bWbcEn;
                }
            }
        } else {
            pstVoLayerConf->bindVoDev[0] = pstVoDevConf->u32VoDev;
            bNeedWbc = pstVoDevConf->bWbcEn;
        }

        /* Forced settings */
        pstVoLayerConf->enVoMode = VO_MODE_1MUX;
        pstVoLayerConf->u64KeepChnPrevFrameBitmap0 = 0x0UL;
        pstVoLayerConf->u64KeepChnPrevFrameBitmap1 = 0x0UL;
        pstVoLayerAttr->enPixFmt = pstVoLayerConf->stVoLayerAttr.enPixFmt;
        pstVoLayerAttr->enSyncMode = AX_VO_LAYER_SYNC_NORMAL;
        pstVoLayerAttr->enWBMode = AX_VO_LAYER_WB_POOL;
        pstVoLayerAttr->u32DispatchMode = AX_VO_LAYER_OUT_TO_LINK;
        pstVoLayerAttr->enPartMode = AX_VO_PART_MODE_SINGLE;
        pstVoLayerConf->u32ChnNr = 1;

        u32LayerWidth = pstVoLayerAttr->stImageSize.u32Width;
        u32LayerHeight = pstVoLayerAttr->stImageSize.u32Height;

        SAMPLE_VO_WIN_INFO(u32LayerWidth, u32LayerHeight, pstVoLayerConf->enVoMode,
                           &u32Row, &u32Col, &u32ChnWidth, &u32ChnHeight);

        s32Chns = u32Row * u32Col;
        u32ChnFrameNr = pstVoLayerConf->u32ChnFrameNr;
        if (!u32ChnFrameNr || u32ChnFrameNr > SAMPLE_VO_FRAME_MAX) {
            u32ChnFrameNr = SAMPLE_VO_FRAME_MAX;
        }
        u64PixSize = (AX_U64)ALIGN_UP(u32ChnWidth, 8) * u32ChnHeight;
        s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(pstVoLayerConf->enChnFrmFmt, &bytesPerPixel, &nPlanes);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, i:%d, enChnFrmFmt:0x%x\n", i, pstVoLayerConf->enChnFrmFmt);
            goto exit0;
        }

        if (AX_FORMAT_YUV422_SEMIPLANAR == pstVoLayerConf->enChnFrmFmt)
            u64BlkSize = u64PixSize * 4 / nPlanes;
        else
            u64BlkSize = u64PixSize * 3 / nPlanes;
        s32Ret = SAMPLE_VO_CREATE_POOL(u32ChnFrameNr, u64BlkSize, 512, &pstVoLayerConf->u32ChnPoolId);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, s32Ret = 0x%x\n", s32Ret);
            goto exit0;
        }

        u64PixSize = (AX_U64)ALIGN_UP(u32LayerWidth, 8) * ALIGN_UP(u32LayerHeight, 2);
        s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(pstVoLayerConf->stVoLayerAttr.enPixFmt, &bytesPerPixel, &nPlanes);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, i:%d, enPixFmt:0x%x\n", i, pstVoLayerConf->stVoLayerAttr.enPixFmt);
            goto exit0;
        }

        if (AX_FORMAT_YUV422_SEMIPLANAR == pstVoLayerConf->stVoLayerAttr.enPixFmt)
            u64BlkSize = u64PixSize * 4 / nPlanes;
        else
            u64BlkSize = u64PixSize * 3 / nPlanes;
        u64BlkNr = bNeedWbc ? 8 : 5;
        s32Ret = SAMPLE_VO_CREATE_POOL(u64BlkNr, u64BlkSize, 512, &pstVoLayerConf->u32LayerPoolId);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, i:%d, s32Ret:0x%x\n", i, s32Ret);
            goto exit0;
        }

        pstVoLayerAttr->u32FifoDepth = pstVoLayerConf->u32FifoDepth;
        pstVoLayerAttr->u32PoolId = pstVoLayerConf->u32LayerPoolId;

        SAMPLE_PRT("u32LayerPoolId = %d, u32ChnPoolId = %d\n", pstVoLayerConf->u32LayerPoolId, pstVoLayerConf->u32ChnPoolId);
    }

    for (i = 0; i < pstVoConf->u32VDevNr; i++) {
        pstVoDevConf = &pstVoConf->stVoDev[i];
        pstGraphicConf = &pstVoConf->stGraphicLayer[i];
        if (pstGraphicConf->u32FbNum) {
            AX_U32 u32Type = 1;

            pstGraphicConf->bindVoDev = pstVoDevConf->u32VoDev;

            for (j = 0; j < pstGraphicConf->u32FbNum; j += 1) {
                if (pstGraphicConf->u32FbNum > 1) {
                    u32Type = j ? 1 : 0;
                }

                s32Ret = SAMPLE_VO_FB_CONF(u32Type, &pstGraphicConf->stFbConf[j]);
                if (s32Ret) {
                    SAMPLE_PRT("SAMPLE_VO_FB_INIT failed, s32Ret:0x%x\n", s32Ret);
                    goto exit0;
                }
            }
        }
    }

    pstCursorLayerConf = &pstVoConf->stCursorLayer;
    if (pstCursorLayerConf->u32CursorLayerEn) {
        pstCursorLayerConf->bindVoDev = pstVoConf->stVoDev[0].u32VoDev;
        s32Ret = SAMPLE_VO_CURSOR_INIT(pstCursorLayerConf->u32X, pstCursorLayerConf->u32Y,
                                       pstCursorLayerConf->u32Width,pstCursorLayerConf->u32Height,
                                       pstCursorLayerConf->u32FBIndex);
        if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_CURSOR_INIT failed, s32Ret:0x%x\n", s32Ret);
            goto exit0;
        }
    }

    s32Ret = SAMPLE_COMM_VO_StartVO(pstVoConf);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_COMM_VO_StartVO failed, i:%d, s32Ret:0x%x\n", i, s32Ret);
        goto exit0;
    }

    for (i = 0; i < pstVoConf->u32VDevNr; i++) {
        pstVoDevConf = &pstVoConf->stVoDev[i];
        if (pstVoDevConf->bWbcEn) {
            stWbcThreadParam[i].u32Wbc = pstVoDevConf->u32VoDev;
            stWbcThreadParam[i].u32FrameCnt = pstVoDevConf->u32WbcFrmaeNr;
            pthread_create(&stWbcThreadParam[i].ThreadID, NULL, SAMPLE_VO_WBC_THREAD, &stWbcThreadParam[i]);
        }
    }

    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoLayerConf = &pstVoConf->stVoLayer[i];
        pstVoLayerAttr = &pstVoLayerConf->stVoLayerAttr;

        for (j = 0; j < s32Chns; j++) {
            pstChnThreadParam = &stLayerThreadParam[i].stVoChnThreadParm[j];
            pstChnThreadParam->u32LayerID = pstVoLayerConf->u32VoLayer;
            pstChnThreadParam->u32ChnID = j;
            pstChnThreadParam->u32FrameRate = pstVoLayerConf->u32ChnFrameRate;
            pstChnThreadParam->u32FrameMax = u32ChnFrameNr;
            strcpy(pstChnThreadParam->chnFileName, pstVoLayerConf->chnFileName);
            pstChnThreadParam->u32ThreadForceStop = 0;
            pstChnThreadParam->u32UserPoolId = pstVoLayerConf->u32ChnPoolId;
            pstChnThreadParam->u32FrameFmt = pstVoLayerConf->enChnFrmFmt;
            pthread_create(&pstChnThreadParam->ThreadID, NULL, SAMPLE_VO_PLAY_THREAD, pstChnThreadParam);
            if ((pstVoLayerConf->u32ChnFrameOut - 1) == j) {
                stLayerThreadParam[i].u32LayerID = pstChnThreadParam->u32LayerID;
                stLayerThreadParam[i].u32ChnID = j;
                stLayerThreadParam[i].u32FrameCnt = 5;
                stLayerThreadParam[i].u32ThreadForceStop = 0;
                pthread_create(&stLayerThreadParam[i].ThreadID, NULL, SAMPLE_VO_GET_CHN_FRAME_THREAD, &stLayerThreadParam[i]);
            }
        }
    }

    while (!gLoopExit) {
        sleep(1);
    }

    for (i = 0; i < pstVoConf->u32VDevNr; i++) {
        pstVoDevConf = &pstVoConf->stVoDev[i];
        if (pstVoDevConf->bWbcEn && stWbcThreadParam[i].ThreadID) {
            stWbcThreadParam[i].u32ThreadForceStop = 1;
            pthread_join(stWbcThreadParam[i].ThreadID, NULL);
            SAMPLE_PRT("wbc%d done\n", stWbcThreadParam[i].u32Wbc);
        }
    }

    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoLayerConf = &pstVoConf->stVoLayer[i];
        pstVoLayerAttr = &pstVoLayerConf->stVoLayerAttr;

        for (j = 0; j < s32Chns; j++) {
            pstChnThreadParam = &stLayerThreadParam[i].stVoChnThreadParm[j];
            if (pstChnThreadParam->ThreadID) {
                pstChnThreadParam->u32ThreadForceStop = 1;
                pthread_join(pstChnThreadParam->ThreadID, NULL);
                SAMPLE_PRT("layer%d-chn%d-thread send frame done\n", pstVoLayerConf->u32VoLayer, j);
            }

            if (stLayerThreadParam[i].ThreadID) {
                stLayerThreadParam[i].u32ThreadForceStop = 1;
                pthread_join(stLayerThreadParam[i].ThreadID, NULL);
                SAMPLE_PRT("layer%d-thread get chn frame done\n", pstVoLayerConf->u32VoLayer);
            }
        }
    }

    SAMPLE_COMM_VO_StopVO(pstVoConf);

    SAMPLE_PRT("VO test Finished success!\n");

exit0:
    for (i = 0; i < pstVoConf->u32LayerNr; i++) {
        pstVoLayerConf = &pstVoConf->stVoLayer[i];
        SAMPLE_VO_POOL_DESTROY(pstVoLayerConf->u32ChnPoolId);
        SAMPLE_VO_POOL_DESTROY(pstVoLayerConf->u32LayerPoolId);
    }

    AX_VO_Deinit();

    return s32Ret;
}

AX_S32 SAMPLE_VO_CSC_PROCESS(void)
{
    AX_S32 s32Ret = 0;
    AX_U32 u32Width = 3072, u32Height = 1080;
    AX_IMG_FORMAT_E enInPixFmt = AX_FORMAT_YUV420_SEMIPLANAR;
    AX_IMG_FORMAT_E enOutPixFmt = AX_FORMAT_YUV420_SEMIPLANAR;
    AX_U64 u64BlkSize = 0, u64PixSize = 0;
    AX_U32 bytesPerPixel = 0, nPlanes = 0;
    AX_U32 u32InPoolId,u32OutPoolId;
    AX_U32 u32SendCnt = 10;
    AX_VIDEO_FRAME_T stInrame = {0};
    AX_VIDEO_FRAME_T stOutrame = {0};
    AX_BLK InBlkId,OutBlkId;
    AX_VOID *u64VirAddr;
    AX_CSC_MATRIX_T stCscMatrix = {0};
    struct timeval start_tv, end_tv;

    stCscMatrix.nType = AX_CSC_MATRIX_USER;
    stCscMatrix.nMatrix[0] = 0x100;
    stCscMatrix.nMatrix[1] = 0;
    stCscMatrix.nMatrix[2] = 0;
    stCscMatrix.nMatrix[3] = 0;
    stCscMatrix.nMatrix[4] = 0x100;
    stCscMatrix.nMatrix[5] = 0;
    stCscMatrix.nMatrix[6] = 0;
    stCscMatrix.nMatrix[7] = 0;
    stCscMatrix.nMatrix[8] = 0x100;

    SAMPLE_PRT("enInPixFmt:0x%x, enOutPixFmt:0x%x\n", enInPixFmt, enOutPixFmt);
    u64PixSize = (AX_U64)ALIGN_UP(u32Width, 8) * u32Height;
    s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(enInPixFmt, &bytesPerPixel, &nPlanes);
    if (s32Ret) {
            SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, enInPixFmt:0x%x\n", enInPixFmt);
            goto exit0;
    }

    if (AX_FORMAT_YUV422_SEMIPLANAR == enInPixFmt)
        u64BlkSize = u64PixSize * 4 / nPlanes;
    else
        u64BlkSize = u64PixSize * 3 / nPlanes;

    s32Ret = SAMPLE_VO_CREATE_POOL(5, u64BlkSize, 512, &u32InPoolId);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, s32Ret = 0x%x\n", s32Ret);
        goto exit0;
    }

    s32Ret = SAMPLE_VO_FMT2ImgStoreInfo(enOutPixFmt, &bytesPerPixel, &nPlanes);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_FMT2ImgStoreInfo failed, enOutPixFmt:0x%x\n", enOutPixFmt);
        goto exit0;
    }

    if (AX_FORMAT_YUV422_SEMIPLANAR == enOutPixFmt)
        u64BlkSize = u64PixSize * 4 / nPlanes;
    else
        u64BlkSize = u64PixSize * 3 / nPlanes;

    s32Ret = SAMPLE_VO_CREATE_POOL(3, u64BlkSize, 512, &u32OutPoolId);
    if (s32Ret) {
        SAMPLE_PRT("SAMPLE_VO_CREATE_POOL failed, s32Ret = 0x%x\n", s32Ret);
        goto exit1;
    }

    SAMPLE_PRT("u32InPoolId = %d, u32OutPoolId = %d\n", u32InPoolId, u32OutPoolId);
    stInrame.stCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
    stInrame.enImgFormat = enInPixFmt;
    stInrame.u32Width = u32Width;
    stInrame.u32Height = u32Height;
    stInrame.u32PicStride[0] = ALIGN_UP(u32Width, 8) * bytesPerPixel;
    if (nPlanes == 2) {
        stInrame.u32PicStride[1] = stInrame.u32PicStride[0];
    }

    stOutrame.stCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
    stOutrame.enImgFormat = enOutPixFmt;
    stOutrame.u32Width = u32Width;
    stOutrame.u32Height = u32Height;
    stOutrame.u32PicStride[0] = ALIGN_UP(u32Width, 8) * bytesPerPixel;
    if (nPlanes == 2) {
        stOutrame.u32PicStride[1] = stOutrame.u32PicStride[0];
    }

    while (!gLoopExit) {
         if (!u32SendCnt) {
            SAMPLE_PRT("sample_vo exit\n");
            return 0;
        }

        InBlkId = AX_POOL_GetBlock(u32InPoolId, u64BlkSize, NULL);
        if (AX_INVALID_BLOCKID == InBlkId) {
            //SAMPLE_PRT("layer%d-chn%d AX_POOL_GetBlock failed\n", u32LayerID, u32ChnID);
            usleep(10000);
            continue;
        }

        stInrame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(InBlkId);
        stInrame.u64VirAddr[0] = 0;

        u64VirAddr = AX_SYS_Mmap(stInrame.u64PhyAddr[0], u64BlkSize);
        if (!u64VirAddr) {
            SAMPLE_PRT("AX_SYS_Mmap failed, u64PhysAddr = 0x%llx, u32FrameSize = 0x%llx\n", stInrame.u64PhyAddr[0], u64BlkSize);
            goto lbl0;
        }

        if (stInrame.stCompressInfo.enCompressMode == AX_COMPRESS_MODE_NONE) {
            SAMPLE_Fill_Color(stInrame.enImgFormat,
                              stInrame.u32Width,
                              stInrame.u32Height,
                              stInrame.u32PicStride[0],
                              u64VirAddr);
        }

        stInrame.u32BlkId[0] = InBlkId;
        stInrame.u32BlkId[1] = AX_INVALID_BLOCKID;
        if (nPlanes == 2) {
            stInrame.u64PhyAddr[1] = stInrame.u64PhyAddr[0] + u64PixSize;
        }

        AX_SYS_Munmap(u64VirAddr, u64BlkSize);

        OutBlkId = AX_POOL_GetBlock(u32OutPoolId, u64BlkSize, NULL);
        if (AX_INVALID_BLOCKID == OutBlkId) {
            //SAMPLE_PRT("layer%d-chn%d AX_POOL_GetBlock failed\n", u32LayerID, u32ChnID);
            usleep(10000);
            continue;
        }

        stOutrame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(OutBlkId);
        stOutrame.u64VirAddr[0] = 0;
        stOutrame.u32BlkId[0] = OutBlkId;
        stOutrame.u32BlkId[1] = AX_INVALID_BLOCKID;
        if (nPlanes == 2) {
            stOutrame.u64PhyAddr[1] = stOutrame.u64PhyAddr[0] + u64PixSize;
        }

        gettimeofday(&start_tv, NULL);
        s32Ret = AX_VO_CscMatrix(&stInrame, &stOutrame, &stCscMatrix);
        gettimeofday(&end_tv, NULL);
        SAMPLE_PRT("AX_VO_CscMatrix (%dx%d) elapsed: %ldms\n",  u32Width, u32Height, (end_tv.tv_sec*1000 + end_tv.tv_usec/1000 - start_tv.tv_sec*1000 - start_tv.tv_usec/1000));

        u32SendCnt -= 1;
        AX_POOL_ReleaseBlock(InBlkId);
        AX_POOL_ReleaseBlock(OutBlkId);

        usleep(40000);

lbl0:
        AX_POOL_ReleaseBlock(InBlkId);
    }

    SAMPLE_VO_POOL_DESTROY(u32OutPoolId);
exit1:
    SAMPLE_VO_POOL_DESTROY(u32InPoolId);
exit0:
    SAMPLE_PRT("csc process exit done\n");

    return s32Ret;
}


