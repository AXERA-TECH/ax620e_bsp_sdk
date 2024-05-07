/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_IVPS_HAL_H_
#define _SAMPLE_IVPS_HAL_H_

#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <sys/epoll.h>
#include "ax_sys_api.h"
#include "ax_ivps_api.h"


/* #define __SAMPLE_LOG_EN__ */

#ifdef __SAMPLE_LOG_EN__
#define ALOGI(fmt, ...) printf("\033[1;30;32mINFO   :[%s:%d] " fmt "\033[0m\n", __func__, __LINE__, ##__VA_ARGS__) // green
#else
#define ALOGI(fmt, ...) \
    do                  \
    {                   \
    } while (0)
#endif
#define ALOGI2(fmt, ...) printf("\033[1;30;33mINFO   :[%s:%d] " fmt "\033[0m\n", __func__, __LINE__, ##__VA_ARGS__) // yellow
#define ALOGE(fmt, ...) printf("\033[1;30;31mERROR  :[%s:%d] " fmt "\033[0m\n", __func__, __LINE__, ##__VA_ARGS__) // red


#define SAMPLE_PHY_MEM_ALIGN_SIZE (16)

#define ARRAY_SIZE(array) sizeof(array) / sizeof(array[0])
#define ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))

typedef struct
{
    AX_S32 nIvpsGrp;
    AX_S32 nIvpsChn;
    AX_VIDEO_FRAME_T tFrameInput;
    char *pFilePath;
    char *pFileName;
    pthread_t region_tid;
    pthread_t crop_resize_tid;
} SAMPLE_IVPS_GRP_T;

typedef struct
{
    AX_U16 nW;
    AX_U16 nH;
    AX_U32 nStride;
    AX_IMG_FORMAT_E eFormat;
    AX_U32 nPhyAddr;
    AX_VOID *pVirAddr;
    AX_POOL PoolId;
    AX_BLK BlkId;
} SAMPLE_IMAGE_T;

typedef struct
{
    char *pImgFile;
    SAMPLE_IMAGE_T tImage;
    AX_IVPS_RECT_T tRect;

    AX_U32 nAlpha;
    AX_U32 nChn;
    AX_U32 nColor; /* for rectangle */
    AX_U32 nLineW; /* for rectangle */
    AX_IVPS_MOSAIC_BLK_SIZE_E eBlkSize;
} SAMPLE_IMAGE_INFO_T;

typedef struct
{
    IVPS_RGN_HANDLE handle;
    IVPS_GRP IvpsGrp;
    IVPS_FILTER IvpsFilter;
    AX_IVPS_RGN_DISP_GROUP_T tRegionGrp;
} SAMPLE_REGION_INFO_T;

AX_VOID ThreadLoopStateSet(AX_BOOL bValue);
AX_BOOL ThreadLoopStateGet(AX_VOID);
AX_S32 SAMPLE_IVPS_SendFrame(AX_S32 nIvpsGrp, char *pFrameInfo);
AX_S32 SAMPLE_IVPS_RegionStart(AX_S32 nIvpsGrp, AX_U32 nRegionNum);
AX_S32 SAMPLE_IVPS_RegionStop(AX_VOID);
AX_S32 SAMPLE_IVPS_RegionUpdateStart(AX_S32 nRegionNum);
AX_S32 SAMPLE_IVPS_RegionUpdateStop(AX_VOID);
AX_S32 IVPS_CropResizeThreadStart(AX_S32 GrpId, AX_S32 ChnId);
AX_S32 IVPS_CropResizeThreadStop(AX_VOID);
#endif