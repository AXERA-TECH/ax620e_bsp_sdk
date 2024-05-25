/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "AudioAed.hpp"
#include "AppLogApi.h"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"

#define AAED "AAED"

using namespace std;

CAudioAed::CAudioAed() {
}

CAudioAed::~CAudioAed() {
}

AX_BOOL CAudioAed::Init(const AUDIO_AED_DEV_ATTR_PTR pstCapDevAttr, const AED_ALGO_CONFIG_PTR pstAedAlgoConfig) {
    AX_BOOL bRet = AX_FALSE;

    if (!pstCapDevAttr || !pstAedAlgoConfig) {
        LOG_MM_E(AAED, "Invalid input(dev:%p, algo:%p", pstCapDevAttr, pstAedAlgoConfig);
        return bRet;
    }

    // STEP1: construct audio aed device
    {
        AUDIO_AED_DEV_ATTR_T stAedDevAttr = pstCapDevAttr[0];

        m_pAedDev = new CAudioAedDev(stAedDevAttr);

        if (!m_pAedDev) {
            goto EXIT;
        }

        bRet = m_pAedDev->Init();

        if (!bRet) {
            goto EXIT;
        }
    }

    // STEP2: construct audio aed result
    {
        AED_ALGO_CONFIG_T stAlgoConfig = pstAedAlgoConfig[0];

        m_pAedAlgo = new CAudioAedAlgo(stAlgoConfig);

        if (!m_pAedAlgo) {
            goto EXIT;
        }

        bRet = m_pAedAlgo->Init();

        if (!bRet) {
            goto EXIT;
        }
    }

EXIT:
    if (!bRet) {
        DeInit();
    }

    return bRet;
}

AX_BOOL CAudioAed::DeInit() {
    LOG_MM_I(AAED, "+++");

    // STEP 1: deinit aed algo
    if (m_pAedAlgo) {
        m_pAedAlgo->DeInit();
        delete m_pAedAlgo;
        m_pAedAlgo = nullptr;
    }

    // STEP 2: deinit dev
    if (m_pAedDev) {
        m_pAedDev->DeInit();
        delete m_pAedDev;
        m_pAedDev = nullptr;
    }

    LOG_MM_I(AAED, "---");

    return AX_TRUE;
}

AX_BOOL CAudioAed::Start() {
    AX_BOOL bRet = AX_FALSE;

    // start audio aed device
    {
        if (m_pAedDev) {
            bRet = m_pAedDev->Start();

            if (!bRet) {
                goto EXIT;
            }
        }
    }

    // start audio aed result
    {
        if (m_pAedAlgo) {
            bRet = m_pAedAlgo->Start();

            if (!bRet) {
                goto EXIT;
            }
        }
    }

EXIT:
    if (!bRet) {
        Stop();
    }

    return bRet;
}

AX_BOOL CAudioAed::Stop() {
    // STEP 1: deinit aed dev
    if (m_pAedDev) {
        m_pAedDev->Stop();
    }

    // STEP 2: stop aed algo
    if (m_pAedAlgo) {
        m_pAedAlgo->Stop();
    }

    return AX_TRUE;
}

AX_BOOL CAudioAed::GetDevAttr(AUDIO_AED_DEV_ATTR_T &stAttr) {
    if (m_pAedDev) {
        return m_pAedDev->GetAttr(stAttr);
    }

    return AX_FALSE;
}

AX_BOOL CAudioAed::SetDevAttr(const AUDIO_AED_DEV_ATTR_T &stAttr) {
    if (m_pAedDev) {
        return m_pAedDev->SetAttr(stAttr);
    }

    return AX_FALSE;
}

AX_BOOL CAudioAed::GetAlgoAttr(AED_ALGO_CONFIG_T &stAttr) {
    if (m_pAedAlgo) {
        return m_pAedAlgo->GetAttr(stAttr);
    }

    return AX_FALSE;
}

AX_BOOL CAudioAed::SetAlgoAttr(const AED_ALGO_CONFIG_T &stAttr) {
    if (m_pAedAlgo) {
        return m_pAedAlgo->SetAttr(stAttr);
    }

    return AX_FALSE;
}

AX_VOID CAudioAed::RegObserver(IObserver *pObserver) {
    if (nullptr != pObserver) {
        if (m_pAedAlgo) {
            m_pAedAlgo->RegObserver(pObserver);
        }
    }
}

AX_VOID CAudioAed::UnregObserver(IObserver *pObserver) {
    if (nullptr != pObserver) {
        if (m_pAedAlgo) {
            m_pAedAlgo->UnregObserver(pObserver);
        }
    }
}
