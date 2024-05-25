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

#include "Collector.h"
#include "IObserver.h"

#define COMB_OBS "COMB_OBS"

class CCollectorObserver : public IObserver {
public:
    CCollectorObserver(CCollector* pSink) : m_pSink(pSink){};
    virtual ~CCollectorObserver(AX_VOID) = default;

public:
    AX_BOOL OnRecvData(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, AX_VOID* pData) override {
        if (!m_pSink) {
            return AX_TRUE;
        }
        if (nullptr == pData) {
            LOG_M_E(COMB_OBS, "Invalid collector data(pipe=%d, chn=%d, pData=0x%08X).", nGrp, nChn, pData);
            return AX_FALSE;
        }
        CAXFrame* pFrame = (CAXFrame*)pData;
        if (E_OBS_TARGET_TYPE_IVPS == eTarget) {
            return m_pSink->RecvFrame(nGrp, nChn, (CAXFrame*)pData);
        } else {
            pFrame->FreeMem();
        }

        return AX_TRUE;
    }

    AX_BOOL OnRegisterObserver(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, OBS_TRANS_ATTR_PTR pParams) override {
        COLLECTOR_ATTR_T* pConfig = m_pSink->GetCollectorCfg();
        pConfig->nWidth = pParams->nWidth;
        pConfig->nHeight = pParams->nHeight;
        pConfig->nSnsSrc = pParams->nSnsSrc;
        pConfig->bEnableFBC = pParams->bEnableFBC;
        pConfig->fFramerate = pParams->fFramerate;
        LOG_MM_I(COMB_OBS, "nGrp:%d, nChn:%d, width:%d, height:%d, sensorSrc:%d, frameRate:%lf", nGrp, nChn, pParams->nWidth,
                 pParams->nHeight, pParams->nSnsSrc, pParams->fFramerate);

        return AX_TRUE;
    }

private:
    CCollector* m_pSink{nullptr};
};
