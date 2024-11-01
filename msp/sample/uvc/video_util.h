/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __VIDEO_UTIL_H
#define __VIDEO_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>

#include "ax_sys_api.h"
#include "ax_venc_api.h"

#include "common_venc.h"
#include "ax_global_type.h"

#include "uvc.h"
#include "common_vin.h"
#include "common_cam.h"
#include "common_sys.h"

static const AX_U32 u32StrideAlign = 64;
static const AX_F32 f32SrcVideoFrameRate = 30.0;
static const AX_F32 f32DstVideoFrameRate = 30.0;

/*QP:0-51, QPLevel:0-99, the lower qp/qp level value, the higher quality*/
static const AX_U32 gU32QPMin = 10;
static const AX_U32 gU32QPMax = 22;
static const AX_U32 gU32FixedQP = 22;
static const AX_S32 gS32QPLevel = 90;

static const AX_S32 gS32QTableEnable = 0;

static const AX_S32 gTimeout = -1;

#define UVC_SNS_OS04A10_MAX_WIDTH  2688
#define UVC_SNS_OS04A10_MAX_HEIGHT 1520

#define MAX_UVC_CAMERAS 2

#define UVC_ENCODER_FBC_WIDTH_ALIGN_VAL (128)
#define ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))


extern UVC_DEVICE_T * udev[MAX_UVC_CAMERAS];

typedef struct _YUV_T {
    AX_U8 y;
    AX_U8 u;
    AX_U8 v;
}YUV_T;

typedef enum _SAMPLE_JPEGENC_RCMODE
{
    JPEGENC_RC_NONE,
    JPEGENC_CBR = 1,
    JPEGENC_VBR = 2,
    JPEGENC_FIXQP,
    JPEGENC_RC_BUTT
} SAMPLE_JPEGENC_RCMODE;

typedef enum {
    UVC_SYS_CASE_NONE  = -1,
    UVC_SYS_CASE_SINGLE_OS04A10 = 0,
    UVC_SYS_CASE_DUAL_OS04A10 = 1,
    UVC_SYS_CASE_SINGLE_DUMMY = 2,
    UVC_SYS_CASE_DUAL_DUMMY = 3,
    UVC_SYS_CASE_SINGLE_SC450AI = 4,
    UVC_SYS_CASE_DUAL_SC450AI= 5,
    UVC_SYS_CASE_BUTT
} UVC_SYS_CASE_E;

typedef struct _SAMPLE_JENC_GETSTREAM_PARA
{
    AX_BOOL bThreadStart;
    VENC_CHN VeChn;
    AX_MOD_INFO_S ispMod;
    AX_MOD_INFO_S jencMod;
    AX_PAYLOAD_TYPE_E enCodecFormat;
} SAMPLE_JENC_GETSTREAM_PARA_T;

typedef enum RcType_
{
    VENC_RC_NONE = -1,
    VENC_RC_CBR = 1,
    VENC_RC_VBR = 2,
    VENC_RC_AVBR = 3,
    VENC_RC_QPMAP = 4,
    VENC_RC_FIXQP = 5,
    VENC_RC_MAX
}RcType;

typedef struct _stRCInfo
{
    RcType eRCType;
    AX_U32 nMinQp;
    AX_U32 nMaxQp;
    AX_U32 nMinIQp;
    AX_U32 nMaxIQp;
    AX_U32 nMaxIProp;
    AX_U32 nMinIProp;
    AX_S32 nIntraQpDelta;
} RC_INFO_T;

typedef struct _stVideoConfig
{
    AX_PAYLOAD_TYPE_E ePayloadType;
    AX_U32 nGOP;
    AX_F32 nSrcFrameRate;
    AX_F32 nDstFrameRate;
    AX_U32 nStride;
    AX_S32 nWidth;
    AX_S32 nHeight;
    RC_INFO_T stRCInfo;
    AX_S32 nBitrate;
} VIDEO_CONFIG_T;

typedef enum {
    E_VIN_TISP_MODE_E = 0,
    E_VIN_AIISP_DEFAULT_SCENE_MODE_E = 1,
    E_VIN_AIISP_MANUAL_SCENE_AIISP_MODE_E = 2,
    E_VIN_AIISP_MANUAL_SCENE_TISP_MODE_E = 3,
    E_VIN_AIISP_AUTO_SCENE_MODE_E = 4,
    E_VIN_AIISP_BUTT_MODE_E,
} VIN_AIISP_MODE_E;

typedef struct _UVC_VIN_PARAM_T{
    UVC_SYS_CASE_E eSysCase;
    SAMPLE_SNS_TYPE_E eSnsType;
    COMMON_VIN_MODE_E eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode;
    SAMPLE_LOAD_RAW_NODE_E eLoadRawNode;
    AX_VIN_IVPS_MODE_E eMode;
    AX_S32 nAiispMode;
    AX_BOOL bTuningEnable;
    AX_S32 nDumpFrameNum;
    AX_S32 nPipeId; /* For VIN */
    AX_S32 nGrpId;  /* For IVPS */
    AX_S32 nOutChnNum;
    AX_S32 nCamCount;
    char * pImgPath;

} UVC_VIN_PARAM_T;

AX_S32 video_init(UVC_DEVICE_T** dev, UVC_VIN_PARAM_T *pParam);
AX_S32 video_deinit(UVC_VIN_PARAM_T *pParam);

AX_S32 venc_init(AX_VOID);
AX_S32 venc_deinit(AX_VOID);


AX_S32 jenc_chn_init(UVC_DEVICE_T* dev, AX_S32 width, AX_S32 height, AX_U32 bitrate);
AX_S32 venc_chn_init(UVC_DEVICE_T* dev, AX_S32 width, AX_S32 height, AX_U32 bitrate, AX_PAYLOAD_TYPE_E payload_type);
AX_S32 venc_chn_deinit(UVC_DEVICE_T* dev, AX_S32 enc_format);

AX_S32 yuv2_chn_init(UVC_DEVICE_T* dev, AX_S32 width, AX_S32 height);
AX_S32 yuv2_chn_deinit(UVC_DEVICE_T* dev);

AX_S32 ivps_init(AX_S32 nSnsCount);
AX_S32 ivps_deinit(AX_S32 nSnsCount);
AX_S32 ivps_update_resolution(AX_U8 nGrp, AX_U8 nChn, AX_S32 nWidth, AX_S32 nHeight, AX_S32 nFps);

AX_S32 link_to_venc(UVC_DEVICE_T* dev, AX_BOOL bLink);

AX_S32 uvc_draw_yuv422_color_stripe(AX_S32 width, AX_S32 height, AX_U8* img);
#endif
