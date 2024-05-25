/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "AudioAedAlgo.hpp"
#include "AppLogApi.h"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"

#include "PrintHelper.h"

#define AEDALGO "AED"

#define AED_DB_VAULE_BASE 100

using namespace std;

CAudioAedAlgo::CAudioAedAlgo(const AED_ALGO_CONFIG_T& stConfig) : m_stAedConfig(stConfig) {
}

CAudioAedAlgo::~CAudioAedAlgo() {
}

AX_BOOL CAudioAedAlgo::Init() {
    return AX_TRUE;
}

AX_BOOL CAudioAedAlgo::DeInit() {
    if (m_bStart) {
        Stop();
    }

    return AX_TRUE;
}

AX_BOOL CAudioAedAlgo::Start() {
    if (!m_stAedConfig.stAlgoAttr.bEnable) {
        return AX_TRUE;
    }

    if (!m_bStart) {
        StartWorkThread();

        m_bStart = AX_TRUE;
    }

    return AX_TRUE;
}

AX_BOOL CAudioAedAlgo::Stop() {
    if (m_bStart) {
        StopWorkThread();

        m_bStart = AX_FALSE;
    }

    return AX_TRUE;
}

AX_VOID CAudioAedAlgo::StartWorkThread() {
    if (!m_bGetThreadRunning) {
        m_bGetThreadRunning = AX_TRUE;
        m_hGetThread = std::thread(&CAudioAedAlgo::FrameGetThreadFunc, this, this);
    }
}

AX_VOID CAudioAedAlgo::StopWorkThread() {
    m_bGetThreadRunning = AX_FALSE;

    if (m_hGetThread.joinable()) {
        m_hGetThread.join();
    }
}

AX_VOID CAudioAedAlgo::FrameGetThreadFunc(CAudioAedAlgo* pCaller) {
    LOG_MM_I(AEDALGO, "[%d] +++");

    CAudioAedAlgo* pThis = (CAudioAedAlgo*)pCaller;

    prctl(PR_SET_NAME, "APP_AED_Get");

    AX_S32 nRet = AX_SUCCESS;
    AX_AED_RESULT_INFO stAedResultInfo;
    AX_U32& nCardId = m_stAedConfig.nCardId;
    AX_U32& nDeviceId = m_stAedConfig.nDeviceId;
    AED_ALGO_ATTR_T& stAlgoAttr = m_stAedConfig.stAlgoAttr;

    m_nEventTicks = 0;

    while (pThis->m_bGetThreadRunning) {
        nRet = AX_AI_GetAedResult(nCardId, nDeviceId, &stAedResultInfo);

        if (0 != nRet) {
            if (AX_ERR_AI_UNEXIST == nRet) {
                LOG_MM_N(AEDALGO, "AX_AI_GetAedResult[%d][%d] failed, ret=%08X", nCardId, nDeviceId, nRet);
            } else {
                LOG_MM_E(AEDALGO, "AX_AI_GetAedResult[%d][%d] failed, ret=%08X", nCardId, nDeviceId, nRet);
            }
            break;
        }

        stAedResultInfo.s32Db += AED_DB_VAULE_BASE;

        if (stAedResultInfo.s32Db >= (AX_S32)stAlgoAttr.fThreshold) {
            AX_U64 ticks = CElapsedTimer::GetTickCount();

            if (m_nEventTicks == 0 ||
                ticks - m_nEventTicks >= stAlgoAttr.nInterval) {
                AED_ALGO_RESULT_T stRelsut;
                stRelsut.fDb = stAedResultInfo.s32Db;

                NotifyAll(&stRelsut);

                m_nEventTicks = ticks;
            }
        } else {
            m_nEventTicks = 0;
        }
    }

    LOG_MM_I(AEDALGO, "[%d] ---");
}

AX_BOOL CAudioAedAlgo::GetAttr(AED_ALGO_CONFIG_T& stAttr) {
    stAttr = m_stAedConfig;

    return AX_TRUE;
}

AX_BOOL CAudioAedAlgo::SetAttr(const AED_ALGO_CONFIG_T& stAttr) {
    if (stAttr.stAlgoAttr.bEnable != m_stAedConfig.stAlgoAttr.bEnable) {
        m_stAedConfig = stAttr;
        m_nEventTicks = 0;

        if (!stAttr.stAlgoAttr.bEnable) {
            Stop();
        } else {
            Stop();

            Start();
        }
    } else if (stAttr.stAlgoAttr.fThreshold != m_stAedConfig.stAlgoAttr.fThreshold
                || stAttr.stAlgoAttr.nInterval != m_stAedConfig.stAlgoAttr.nInterval) {
        m_stAedConfig = stAttr;
        m_nEventTicks = 0;
    }

    return AX_TRUE;
}

AX_VOID CAudioAedAlgo::RegObserver(IObserver* pObserver) {
    if (nullptr != pObserver) {
        OBS_TRANS_ATTR_T tTransAttr;
        AX_U32 nGroup = m_stAedConfig.nCardId;
        AX_U32 nChn = m_stAedConfig.nDeviceId;
        tTransAttr.nGroup = nGroup;
        tTransAttr.nChannel = nChn;

        if (pObserver->OnRegisterObserver(E_OBS_TARGET_TYPE_AED, nGroup, nChn, &tTransAttr)) {
            m_vecObserver.emplace_back(pObserver);
        }
    }
}

AX_VOID CAudioAedAlgo::UnregObserver(IObserver* pObserver) {
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

AX_VOID CAudioAedAlgo::NotifyAll(AX_VOID* pstStream) {
    if (nullptr == pstStream) {
        return;
    }

    AX_U32 nGroup = m_stAedConfig.nCardId;
    AX_U32 nChn = m_stAedConfig.nDeviceId;

    for (vector<IObserver*>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        (*it)->OnRecvData(E_OBS_TARGET_TYPE_AED, nGroup, nChn, pstStream);
    }
}
