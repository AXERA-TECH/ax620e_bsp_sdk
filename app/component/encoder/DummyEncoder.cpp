/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "DummyEncoder.h"
#include "AppLogApi.h"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include "PrintHelper.h"
#include "ax_venc_api.h"

#define DUMMY_ENCODER "DUMMY_ENC"

CDummyEncoder::CDummyEncoder(DUMMY_CODE_CONFIG_T& tConfig)
    : CAXStage((string)DUMMY_ENCODER + (char)('0' + tConfig.nChannel)), m_stDummyEncoder(tConfig) {
}

CDummyEncoder::~CDummyEncoder() {
}

AX_BOOL CDummyEncoder::Start(STAGE_START_PARAM_PTR pStartParams) {
    LOG_MM_I(DUMMY_ENCODER, "[%d] +++", GetChannel());
    AX_BOOL ret = CAXStage::Start(pStartParams);
    LOG_MM_I(DUMMY_ENCODER, "[%d] ---", GetChannel());
    return ret;
}

AX_BOOL CDummyEncoder::Stop(AX_VOID) {
    LOG_MM_C(DUMMY_ENCODER, "[%d] +++", GetChannel());
    CAXStage::Stop();
    LOG_MM_C(DUMMY_ENCODER, "[%d] ---", GetChannel());
    return AX_TRUE;
}

AX_BOOL CDummyEncoder::Init() {
    SetCapacity(AX_APP_LOCKQ_CAPACITY);
    return AX_TRUE;
}

AX_VOID CDummyEncoder::RegObserver(IObserver* pObserver) {
    if (nullptr != pObserver) {
        OBS_TRANS_ATTR_T tTransAttr;
        if (pObserver->OnRegisterObserver(E_OBS_TARGET_TYPE_DUMMY_ENCODER, m_stDummyEncoder.nPipeSrc, m_stDummyEncoder.nChannel,
                                          &tTransAttr)) {
            m_vecObserver.emplace_back(pObserver);
        }
    }
}

AX_VOID CDummyEncoder::UnregObserver(IObserver* pObserver) {
    if (nullptr == pObserver) {
        return;
    }

    for (vector<IObserver*>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        if (*it == pObserver) {
            m_vecObserver.erase(it);
            break;
        }
    }
}

AX_BOOL CDummyEncoder::ProcessFrame(CAXFrame* pFrame) {
    CPrintHelper::GetInstance()->Add(E_PH_MOD_DUMMY_ENCODER, GetChannel());
    return AX_TRUE;
}
