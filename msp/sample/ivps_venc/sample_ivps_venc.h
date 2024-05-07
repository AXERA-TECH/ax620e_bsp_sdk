/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_IVPS_VENC_H_
#define _SAMPLE_IVPS_VENC_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include "ax_venc_api.h"
#include "ax_ivps_api.h"
#include "common_venc.h"

#define ALIGN_UP_16(value) ((value + 0xF) & (~0xF))
#define ALIGN_UP_64(value) ((value + 0x3F) & (~0x3F))
#define SAMPLE_VENC_CHN_NUM_MAX   (2)

typedef struct _stVencGetStreamParam
{
    AX_S32 VeChn;
    AX_BOOL bThreadStart;
    AX_PAYLOAD_TYPE_E ePayloadType;
} VENC_GETSTREAM_PARAM_T;

typedef struct _stRCInfo
{
    SAMPLE_VENC_RC_E eRCType;
    AX_U32 nMinQp;
    AX_U32 nMaxQp;
    AX_U32 nMinIQp;
    AX_U32 nMaxIQp;
    AX_S32 nIntraQpDelta;
    AX_U32 nIpropMin;
    AX_U32 nIpropMax;
} RC_INFO_T;

typedef struct _stVideoConfig
{
    AX_PAYLOAD_TYPE_E ePayloadType;
    AX_U32 nGOP;
    AX_U32 nSrcFrameRate;
    AX_U32 nDstFrameRate;
    AX_U32 nStride;
    AX_S32 nInWidth;
    AX_S32 nInHeight;
    AX_S32 nOutWidth;
    AX_S32 nOutHeight;
    AX_IMG_FORMAT_E eImgFormat;
    RC_INFO_T stRCInfo;
    AX_S32 nBitrate;
} VIDEO_CONFIG_T;

typedef struct {
    AX_U32 nStride;
    AX_S32 nWidth;
    AX_S32 nHeight;
    AX_IMG_FORMAT_E eImgFormat;
    AX_COMPRESS_MODE_E eFbcMode;
} SAMPLE_CHN_ATTR_T;

typedef struct {
    AX_U32 nInWidth;
    AX_U32 nInHeight;

    AX_U32 nEncWidth;
    AX_U32 nEncHeight;

    AX_U32 nRcMode;
    AX_U32 nBps[SAMPLE_VENC_CHN_NUM_MAX];
    AX_U32 nFps;

    AX_U32 nMinqp;
    AX_U32 nMaxqp;
    AX_U32 nMinIqp;
    AX_U32 nMaxIqp;

    AX_U32 nMinIpratio;
    AX_U32 nMaxIpratio;

    AX_S32 nGrpId;  /* For IVPS */
    AX_S32 nOutChnNum;
    char *pFileName;

    AX_U32 nFrameSize;
    AX_POOL nPoolId;

    AX_IMG_FORMAT_E eYuvFormat;
    AX_IVPS_ROTATION_E eRotAngle;

    AX_S32 encFrmNum;
    AX_BOOL eFbcMode;
} SAMPLE_VENC_PARAM_T;

#endif