/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_VIN_IVPS_VO_VENC_H_
#define _SAMPLE_VIN_IVPS_VO_VENC_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include "ax_venc_api.h"
#include "ax_ivps_api.h"
#include "ax_isp_api.h"
#include "common_sys.h"
#include "common_venc.h"
#include "common_vin.h"
#include "common_cam.h"
#include "common_nt.h"
#include "common_isp.h"
#include "AXRtspWrapper.h"

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
#define DIV_ROUND_UP(n, d) (((n) + (d)-1) / (d))
#define ALIGN_UP_16(value) ((value + 0xF) & (~0xF))
#define ALIGN_UP_64(value) ((value + 0x3F) & (~0x3F))
#define SAMPLE_VENC_CHN_NUM_MAX   (3)

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

typedef enum {
    SAMPLE_VIN_NONE  = -1,
    SAMPLE_VIN_SINGLE_DUMMY  = 0,
    SAMPLE_VIN_SINGLE_OS08A20  = 1,
    SAMPLE_VIN_SINGLE_OS04A10 = 2,
    SAMPLE_VIN_BUTT
} SAMPLE_VIN_CASE_E;

typedef struct {
    AX_U32 nStride;
    AX_S32 nWidth;
    AX_S32 nHeight;
    AX_IMG_FORMAT_E eImgFormat;
} SAMPLE_CHN_ATTR_T;

typedef struct {
    SAMPLE_VIN_CASE_E eSysCase;
    COMMON_VIN_MODE_E eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode;
    SAMPLE_LOAD_RAW_NODE_E eLoadRawNode;
    AX_BOOL bAiispEnable;
    AX_S32 nDumpFrameNum;
    AX_S32 nGrpId;
    AX_S32 nOutChnNum;
    char *pFrameInfo;
} SAMPLE_VIN_PARAM_T;


typedef struct {
    AX_BOOL bEnable;
    AX_RTSP_HANDLE pRtspHandle;
} SAMPLE_RTSP_PARAM_T;

#endif
