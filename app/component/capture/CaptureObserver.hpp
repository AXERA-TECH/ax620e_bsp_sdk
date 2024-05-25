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
#include "Capture.hpp"
#include "IObserver.h"

class CAXFrame;

class CCaptureObserver : public IObserver {
public:
    CCaptureObserver(CCapture* pSink) : m_pSink(pSink){};

public:
    AX_BOOL OnRecvData(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, AX_VOID* pData) override {
        CAXFrame* pFrame = static_cast<CAXFrame*>(pData);
        if (!pFrame) {
            return AX_FALSE;
        }

        if (m_nTargetPipeChannel != (eTarget << 24 | nGrp << 16 | nChn)) {
            pFrame->FreeMem();
            return AX_TRUE;
        }

        return m_pSink->SendFrame(pFrame, m_nSnsID, nChn);
    }

    AX_BOOL OnRegisterObserver(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, OBS_TRANS_ATTR_PTR pParams) override {
        m_nSnsID = pParams->nSnsSrc;
        m_nTargetPipeChannel = eTarget << 24 | nGrp << 16 | nChn;
        return AX_TRUE;
    }

    AX_BOOL IsReadyForRecv(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn) override {
        return m_pSink->IsCapturing(m_nSnsID, nChn);
    }

private:
    CCapture* m_pSink{nullptr};
    AX_U32 m_nSnsID{0};
    AX_U32 m_nTargetPipeChannel{0};
};