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
#include <map>
#include "IObserver.h"
#include "VideoDecoder.h"
#define VDEC_OBS "VDEC_obs"

class CVdecObserver : public IObserver {
public:
    CVdecObserver(CVideoDecoder* pSink) : m_pSink(pSink){};
    virtual ~CVdecObserver(AX_VOID) = default;

public:
    AX_BOOL OnRecvData(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nLen, AX_VOID* pData) override {
        if (!m_pSink) {
            return AX_TRUE;
        }

        AX_U8* pStream = (AX_U8*)pData;
        if (!pStream) {
            return AX_TRUE;
        }

        return m_pSink->Send(pStream, nLen);
    }

    AX_BOOL OnRegisterObserver(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nMaxStreamSize, OBS_TRANS_ATTR_PTR pParams) override {
        return AX_TRUE;
    }

private:
    CVideoDecoder* m_pSink{nullptr};
};
