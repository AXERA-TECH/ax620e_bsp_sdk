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
#include "AXFrame.hpp"
#include "DummyEncoder.h"
#include "IObserver.h"

class CDummyEncoderObserver : public IObserver {
public:
    CDummyEncoderObserver(CDummyEncoder* pSink) : m_pSink(pSink){};
    virtual ~CDummyEncoderObserver(AX_VOID) = default;

public:
    AX_BOOL OnRecvData(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, AX_VOID* pData) override {
        if (!m_pSink) {
            return AX_TRUE;
        }

        CAXFrame* pFrame = (CAXFrame*)pData;
        if (!pFrame) {
            return AX_TRUE;
        }

        if (m_nTargetPipeChannel != (eTarget << 24 | nGrp << 16 | nChn)) {
            return AX_TRUE;
        }
        return m_pSink->EnqueueFrame(pFrame);
    }

    AX_BOOL OnRegisterObserver(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, OBS_TRANS_ATTR_PTR pParams) override {
        m_nTargetPipeChannel = eTarget << 24 | nGrp << 16 | nChn;
        return AX_TRUE;
    }

private:
    CDummyEncoder* m_pSink{nullptr};
    AX_U32 m_nTargetPipeChannel{0};
};