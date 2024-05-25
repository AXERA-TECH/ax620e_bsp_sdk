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
#include "AXAlgo.hpp"
#include "AXFrame.hpp"
#include "AXSingleton.h"
#include "WebServer.h"
#include "ax_ives_api.h"

class CSCD {
public:
    CSCD(AX_VOID) {
        InitOnce();
    }
    ~CSCD(AX_VOID) = default;

    AX_VOID SetWebServer(CWebServer *pWebServer);
    AX_BOOL Startup(AX_S32 nSnsId, AX_U32 nWidth, AX_U32 nHeight);
    AX_VOID Cleanup(AX_VOID);
    AX_BOOL ProcessFrame(const AX_U32 nSnsId, const CAXFrame *pFrame);
    AX_VOID SetThreshold(AX_U32 nSnsId, AX_S32 nThreshold, AX_S32 nConfidence);
    AX_VOID GetThreshold(AX_U32 nSnsId, AX_S32 &nThreshold, AX_S32 &nConfidence) const;
    AX_VOID SetConfig(const AX_APP_ALGO_SCENE_CHANGE_PARAM_T &stConfig, AX_BOOL bUpdateParam = AX_FALSE);
    AX_VOID UpdateResolution(AX_U32 w, AX_U32 h);

private:
    AX_BOOL LoadConfig(AX_S32 nSnsId);
    AX_BOOL InitOnce(AX_VOID) {
        memset(&m_stConfig, 0x00, sizeof(m_stConfig));
        return AX_TRUE;
    };

private:
    AX_U32 m_scdImgW{0};
    AX_U32 m_scdImgH{0};
    AX_S32 m_nSnsID{0};
    SCD_CHN m_chn{-1};
    AX_APP_ALGO_SCENE_CHANGE_PARAM_T m_stConfig;
};
