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

#include <vector>
#include "ax_ai_api.h"
#include "ax_codec_comm.h"
#include "ax_comm_aio.h"

typedef struct audioAed_DEV_ATTR_T {
    AX_BOOL bEnable;
    AX_U32 nCardId;
    AX_U32 nDeviceId;

    audioAed_DEV_ATTR_T() {
        nCardId = 0;
        nDeviceId = 0;
    }
} AUDIO_AED_DEV_ATTR_T, *AUDIO_AED_DEV_ATTR_PTR;

class CAudioAedDev {
public:
    CAudioAedDev(const AUDIO_AED_DEV_ATTR_T &stAttr);
    ~CAudioAedDev();

    AX_BOOL Init();
    AX_BOOL DeInit();
    AX_BOOL Start();
    AX_BOOL Stop();

    AX_BOOL GetAttr(AUDIO_AED_DEV_ATTR_T &stAttr);
    AX_BOOL SetAttr(const AUDIO_AED_DEV_ATTR_T &stAttr);

private:
    AX_BOOL Create();
    AX_BOOL Destroy();

private:
    AUDIO_AED_DEV_ATTR_T m_stAedDevAttr;

    AX_BOOL m_bStart{AX_FALSE};
};
