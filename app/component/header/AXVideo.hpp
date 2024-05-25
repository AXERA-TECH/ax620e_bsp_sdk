/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#pragma once

#include <string>
#include "ax_global_type.h"
#include "ax_venc_comm.h"

#define ENC_MAX_BUF_SIZE (3840 * 2160 * 3 / 2)

#define VENC_DEFAULT_GOP_SETTINGS(fps) ((AX_U32)(4 * (fps)))

// video packet
typedef struct axAPP_VIDEO_PKT_T {
    AX_U32 nSnsId;
    AX_U32 nChan;
    AX_PAYLOAD_TYPE_E eType;
    AX_VENC_DATA_TYPE_U uNaluType;
    AX_BOOL bIFrame;
    AX_U8 *pData;
    AX_U32 nDataSize;
    AX_U64 u64Pts;
    AX_VOID *pUserData;
    AX_VOID *pPrivateData;
} AX_APP_VIDEO_PKT_T, *AX_APP_VIDEO_PKT_PTR;

// video frame
typedef struct axAPP_VIDEO_FRAME_T {
    AX_U32 nSnsId;
    AX_U32 nChan;
    AX_VIDEO_FRAME_T stFrame;
    AX_VOID *pUserData;
    AX_VOID *pPrivateData;
} AX_APP_VIDEO_FRAME_T, *AX_APP_VIDEO_FRAME_PTR;

// video packet callback
typedef AX_VOID (*AX_APP_VIDEO_PKT_CALLBACK)(AX_U32 nSnsId, AX_U32 nChan, const AX_APP_VIDEO_PKT_PTR pstPkt);

// video frame callback
typedef AX_VOID (*AX_APP_VIDEO_FRAME_CALLBACK)(AX_U32 nSnsId, AX_U32 nChan, const AX_APP_VIDEO_FRAME_PTR pstFrame);
