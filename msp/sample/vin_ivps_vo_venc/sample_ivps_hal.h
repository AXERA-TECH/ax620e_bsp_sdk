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

#define ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
typedef struct
{
	AX_S32 nIvpsGrp;
	AX_VIDEO_FRAME_T tFrameInput;
	char *pFilePath;
	char *pFileName;
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

AX_VOID ThreadLoopStateSet(AX_BOOL bValue);
AX_BOOL ThreadLoopStateGet(AX_VOID);
AX_S32 SAMPLE_IVPS_SendFrame(AX_S32 nIvpsGrp, char *pFrameInfo);
#endif