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
#include "AXFrame.hpp"
#include "IObserver.h"
#include "IVESStage.h"

#define IVES_OBS "ives_obs"

typedef struct _IVES_GRP_CHN_ATTR_T {
    AX_U32 nGrp{0};
    AX_U32 nChn{0};
    AX_U32 nSnsSrc{0};
} IVES_GRP_CHN_ATTR_T;

class CIvesObserver : public IObserver {
public:
    CIvesObserver(CIVESStage* pSink) : m_pSink(pSink){};
    ~CIvesObserver(AX_VOID) = default;

public:
    AX_BOOL OnRecvData(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, AX_VOID* pData) override {
        if (!m_pSink) {
            return AX_TRUE;
        }

        CAXFrame* pFrame = (CAXFrame*)pData;

        if (!pFrame) {
            return AX_TRUE;
        }
        if (nGrp != m_ChnAttr.nGrp || nChn != m_ChnAttr.nChn) {
            return AX_TRUE;
        }

        m_pSink->SendFrame(m_ChnAttr.nSnsSrc, pFrame);

        return AX_TRUE;
    }

    AX_BOOL OnRegisterObserver(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, OBS_TRANS_ATTR_PTR pParams) override {
        IVES_ATTR_T* pAttr = m_pSink->GetIVESCfg();
        pAttr->nWidth = pParams->nWidth;
        pAttr->nHeight = pParams->nHeight;

        // AX620E TODO: different from AX650
        pAttr->fSrcFramerate = pParams->fFramerate;
        pAttr->nGrpCount = 1;
        pAttr->nSnsSrc = pParams->nSnsSrc;

        m_ChnAttr.nGrp = nGrp;
        m_ChnAttr.nChn = nChn;
        m_ChnAttr.nSnsSrc = pParams->nSnsSrc;

        return AX_TRUE;
    }

private:
    CIVESStage* m_pSink{nullptr};
    IVES_GRP_CHN_ATTR_T m_ChnAttr;
};
