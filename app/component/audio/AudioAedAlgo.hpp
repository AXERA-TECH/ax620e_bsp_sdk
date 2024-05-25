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

#include <thread>
#include <vector>
#include "IObserver.h"
#include "ax_ai_api.h"
#include "ax_comm_aio.h"

typedef struct aedALGO_ATTR_T {
    AX_BOOL bEnable;
    AX_F32 fThreshold;
    AX_U32 nInterval;

    aedALGO_ATTR_T() {
        bEnable = AX_FALSE;
        fThreshold = 0;
        nInterval = 0;
    }
} AED_ALGO_ATTR_T, *AED_ALGO_ATTR_PTR;

typedef struct aedALGO_CONFIG_T {
    AX_U32 nCardId;
    AX_U32 nDeviceId;
    AED_ALGO_ATTR_T stAlgoAttr;

    aedALGO_CONFIG_T() {
        nCardId = 0;
        nDeviceId = 0;
    }
} AED_ALGO_CONFIG_T, *AED_ALGO_CONFIG_PTR;

typedef struct aedALGO_RESULT_T {
    AX_F32 fDb;
} AED_ALGO_RESULT_T, *AED_ALGO_RESULT_PTR;

class CAudioAedAlgo {
public:
    CAudioAedAlgo(const AED_ALGO_CONFIG_T& stConfig);
    ~CAudioAedAlgo();

    AX_BOOL Init();
    AX_BOOL DeInit();
    AX_BOOL Start();
    AX_BOOL Stop();

    AX_BOOL GetAttr(AED_ALGO_CONFIG_T& stAttr);
    AX_BOOL SetAttr(const AED_ALGO_CONFIG_T& stAttr);

    AX_BOOL GetAlgoAttr(AED_ALGO_CONFIG_T& stAttr);
    AX_BOOL SetAlgoAttr(const AED_ALGO_CONFIG_T& stAttr);

    AX_VOID RegObserver(IObserver* pObserver);
    AX_VOID UnregObserver(IObserver* pObserver);

protected:
    AX_VOID FrameGetThreadFunc(CAudioAedAlgo* pCaller);
    AX_VOID StartWorkThread();
    AX_VOID StopWorkThread();

    AX_VOID NotifyAll(AX_VOID* pstResult);

private:
    AED_ALGO_CONFIG_T m_stAedConfig;

    AX_BOOL m_bStart{AX_FALSE};

    std::thread m_hGetThread;
    AX_BOOL m_bGetThreadRunning{AX_FALSE};

    AX_U64 m_nEventTicks{0};
    std::vector<IObserver*> m_vecObserver;
};
