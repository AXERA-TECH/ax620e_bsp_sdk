/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "AudioAedDev.hpp"
#include <string.h>
#include "AppLogApi.h"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include "ax_ai_api.h"

#define AEDDEV "AED"

using namespace std;

CAudioAedDev::CAudioAedDev(const AUDIO_AED_DEV_ATTR_T &stAttr) : m_stAedDevAttr(stAttr) {
}

CAudioAedDev::~CAudioAedDev() {
}

AX_BOOL CAudioAedDev::Init() {
    return AX_TRUE;
}

AX_BOOL CAudioAedDev::DeInit() {
    if (m_bStart) {
        Stop();
    }

    return AX_TRUE;
}

AX_BOOL CAudioAedDev::Start() {
    if (!m_stAedDevAttr.bEnable) {
        return AX_TRUE;
    }

    if (!m_bStart) {
        if (!Create()) {
            return AX_FALSE;
        }

        m_bStart = AX_TRUE;
    }

    return AX_TRUE;
}

AX_BOOL CAudioAedDev::Stop() {
    if (m_bStart) {
        m_bStart = AX_FALSE;

        Destroy();
    }

    return AX_TRUE;
}

AX_BOOL CAudioAedDev::Create() {
    if (!m_stAedDevAttr.bEnable) {
        return AX_FALSE;
    }

    AX_S32 nRet = 0;

    AX_U32 &nCardId = m_stAedDevAttr.nCardId;
    AX_U32 &nDeviceId = m_stAedDevAttr.nDeviceId;

    AX_AED_ATTR_T stAttr;
    stAttr.bDbDetection = AX_TRUE;

    // STEP 1: set aed device attribute
    nRet = AX_AI_SetAedAttr(nCardId, nDeviceId, &stAttr);

    if (0 != nRet) {
        LOG_MM_E(AEDDEV, "AX_AI_SetAedAttr[%d][%d] failed ret=%08X", nCardId, nDeviceId, nRet);
        goto EXIT1;
    }

    // STEP 2: enable device
    nRet = AX_AI_EnableAed(nCardId, nDeviceId);

    if (0 != nRet) {
        LOG_MM_E(AEDDEV, "AX_AI_EnableAed[%d][%d] failed ret=%08X", nCardId, nDeviceId, nRet);
        goto EXIT1;
    }

    return AX_TRUE;

EXIT1:
    return AX_FALSE;
}

AX_BOOL CAudioAedDev::Destroy() {
    AX_U32 &nCardId = m_stAedDevAttr.nCardId;
    AX_U32 &nDeviceId = m_stAedDevAttr.nDeviceId;

    // STEP1: disbale dev
    AX_AI_DisableAed(nCardId, nDeviceId);

    return AX_TRUE;
}

AX_BOOL CAudioAedDev::GetAttr(AUDIO_AED_DEV_ATTR_T &stAttr) {
    stAttr = m_stAedDevAttr;

    return AX_TRUE;
}

AX_BOOL CAudioAedDev::SetAttr(const AUDIO_AED_DEV_ATTR_T &stAttr) {
    if (stAttr.bEnable != m_stAedDevAttr.bEnable) {
        m_stAedDevAttr = stAttr;

        if (!stAttr.bEnable) {
            Stop();
        } else {
            Stop();

            Start();
        }
    } else {
        m_stAedDevAttr = stAttr;
    }

    return AX_TRUE;
}
