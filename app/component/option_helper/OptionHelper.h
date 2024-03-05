/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#pragma once

#include <string>
#include "AXSingleton.h"
#include "IniWrapper.hpp"

/**
 * Load configuration
 */
class COptionHelper final : public CAXSingleton<COptionHelper> {
    friend class CAXSingleton<COptionHelper>;

public:
    AX_F32 GetJencOutBuffRatio();
    AX_U32 GetAencOutFrmSize();
    AX_U32 GetWebJencRingBufCount();
    AX_U32 GetWebMjencRingBufCount();
    AX_U32 GetWebEventsRingBufCount();
    AX_U32 GetWebAencRingBufCount();
    AX_U32 GetRTSPMaxFrmSize();
    AX_U32 GetRTSPRingBufCount();
    AX_U32 GetSnapShotQpLevel();
    AX_BOOL IsEnableMp4Record();
    AX_BOOL IsEnableOSD();
    std::string GetMp4SavedPath();
    /* SLT functions */
    AX_U32 GetSLTRunTime();
    AX_U32 GetSLTFpsCheckFreq();
    AX_U32 GetSLTFpsDiff();

    AX_U32 GetVencThreadNum();
    AX_BOOL IsEnableVencDebreath();
    AX_BOOL IsEnableVencRefRingbuf();

    AX_BOOL GetInterpolationResolution(AX_U32 &nWidth, AX_U32 &nHeight);
    AX_BOOL SetInterpolationResolution(const AX_U32 &nWidth, const AX_U32 &nHeight);

    AX_BOOL GetSnsHnbTestMode();
    AX_BOOL GetSnsHnbPrintTemperature();

    AX_BOOL IsEnableWebServerStatusCheck();

    AX_U32 GetWebVencRingBufSize(AX_U32 width, AX_U32 height);
    AX_U32 GetWebVencRingBufCount(AX_U32 width, AX_U32 height);
private:
    COptionHelper(AX_VOID) = default;
    ~COptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    CIniWrapper m_iniWrapper;
    AX_U32 m_InterpolationResolutionWidth;
    AX_U32 m_InterpolationResolutionHeight;
};
