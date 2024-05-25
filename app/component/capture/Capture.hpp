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
#include "AXThread.hpp"
#include "IObserver.h"

/**
 * @brief
 *
 */

#define MAX_CAPTURE_GROUP_NUM 2

class CCapture {
public:
    CCapture(AX_VOID) = default;
    ~CCapture(AX_VOID) = default;

    AX_BOOL DeInit(AX_VOID);
    AX_BOOL SendFrame(CAXFrame* axFrame, AX_U32 nSnsID, AX_U32 nChn);
    AX_BOOL CapturePicture(AX_U32 nSnsID, AX_U32 nChn, AX_U32 nQpLevel, AX_VOID** ppCallbackData);
    AX_BOOL IsCapturing(AX_U32 nSnsID, AX_U32 nChn);

private:
    AX_VOID ResetCaptureStatus(AX_VOID);

private:
    CAXFrame* m_pAXFrame{nullptr};
    std::mutex m_mutexStat;
    std::mutex m_mutexCapture;
    std::condition_variable m_cvCapture;

    AX_BOOL m_bCapture{AX_FALSE};
    AX_U32 m_nSnsID{0};
    // ivps channel id
    AX_U32 m_nChn{0};
};