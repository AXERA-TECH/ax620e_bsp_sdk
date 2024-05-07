/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "IVESStage.h"
#include "AlgoOptionHelper.h"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include "IvesResult.hpp"

#define IVES "IVES"

CIVESStage::CIVESStage(AX_VOID) : CAXStage(IVES) {
}

AX_BOOL CIVESStage::Init(AX_U32 nGrp) {
    SetCapacity(AX_APP_LOCKQ_CAPACITY);

    if (0 == m_stAttr.nGrpCount) {
        LOG_MM_E(IVES, "invalid nGrpCount");
        return AX_FALSE;
    }
    AX_U32 nFrmW = m_stAttr.nWidth;
    AX_U32 nFrmH = m_stAttr.nHeight;
    AX_U8 nSnsID = m_stAttr.nSnsSrc;

    m_bMDEnable = CAlgoOptionHelper::GetInstance()->IsEnableMD(nSnsID);
    m_bODEnable = CAlgoOptionHelper::GetInstance()->IsEnableOD(nSnsID);
    m_bSCDEnable = CAlgoOptionHelper::GetInstance()->IsEnableSCD(nSnsID);
    LOG_MM_I(IVES, "nSnsID:%d, width:%d, height:%d, frameRate:%f, %d, %d, %d", nSnsID, m_stAttr.nWidth, m_stAttr.nHeight,
             m_stAttr.fSrcFramerate, m_bMDEnable, m_bODEnable, m_bSCDEnable);
    /*init MD */
    if (m_bMDEnable) {
        m_spMDInstance.reset(new CMD());
        if (!m_spMDInstance->Startup(nSnsID, nFrmW, nFrmH)) {
            return AX_FALSE;
        }

        AX_APP_ALGO_MOTION_PARAM_T stParam = ALGO_MD_PARAM(nSnsID);
        m_spMDInstance->SetConfig(stParam);
    }

    /*init OD */
    if (m_bODEnable) {
        m_spODInstance.reset(new COD());
        if (!m_spODInstance->Startup(nSnsID, (AX_U32)m_stAttr.fSrcFramerate, nFrmW, nFrmH)) {
            return AX_FALSE;
        }

        AX_APP_ALGO_OCCLUSION_PARAM_T stParam = ALGO_OD_PARAM(nSnsID);
        m_spODInstance->SetConfig(stParam);
    }

    /*init SCD */
    if (m_bSCDEnable) {
        m_spSCDInstance.reset(new CSCD());
        if (!m_spSCDInstance->Startup(nSnsID, nFrmW, nFrmH)) {
            return AX_FALSE;
        }

        AX_APP_ALGO_SCENE_CHANGE_PARAM_T stParam = ALGO_SCD_PARAM(nSnsID);
        m_spSCDInstance->SetConfig(stParam);
    }
    m_nGroup = nGrp;

    AX_APP_ALGO_IVES_PARAM_T stAlgoIVESParam = ALGO_IVES_PARAM(nSnsID);
    if (!m_spFramectrl && (stAlgoIVESParam.nFramerate > 0)) {
        m_spFramectrl.reset(new CFramerateCtrlHelper((AX_U32)m_stAttr.fSrcFramerate, (AX_U32)stAlgoIVESParam.nFramerate));
    }

    return AX_TRUE;
}

AX_BOOL CIVESStage::SetMdConfig(const AX_APP_ALGO_MOTION_PARAM_T &stConfig) {
    if (m_spMDInstance) {
        SetMDCapacity(stConfig.bEnable);

        m_spMDInstance->SetConfig(stConfig);
    }

    return AX_TRUE;
}

AX_BOOL CIVESStage::SetOdConfig(const AX_APP_ALGO_OCCLUSION_PARAM_T &stConfig) {
    if (m_spODInstance) {
        SetODCapacity(stConfig.bEnable);

        m_spODInstance->SetConfig(stConfig);
    }

    return AX_TRUE;
}

AX_BOOL CIVESStage::SetScdConfig(const AX_APP_ALGO_SCENE_CHANGE_PARAM_T &stConfig) {
    if (m_spSCDInstance) {
        SetSCDCapacity(stConfig.bEnable);

        m_spSCDInstance->SetConfig(stConfig);
    }

    return AX_TRUE;
}

AX_BOOL CIVESStage::InitModule() {
    AX_S32 ret = AX_SUCCESS;

    if (CAlgoOptionHelper::GetInstance()->IsEnableMD()) {
        ret = AX_IVES_MD_Init();
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVES, "AX_IVES_MD_Init() fail, ret = 0x%x", ret);
            return AX_FALSE;
        }
    }
    if (CAlgoOptionHelper::GetInstance()->IsEnableOD()) {
        ret = AX_IVES_OD_Init();
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVES, "AX_IVES_OD_Init() fail, ret = 0x%x", ret);
            return AX_FALSE;
        }
    }
    if (CAlgoOptionHelper::GetInstance()->IsEnableSCD()) {
        ret = AX_IVES_SCD_Init();
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVES, "AX_IVES_SCD_Init() fail, ret = 0x%x", ret);
            return AX_FALSE;
        }
    }

    return AX_TRUE;
}

AX_BOOL CIVESStage::DeinitModule() {
    LOG_MM_C(IVES, "+++");

    AX_S32 ret = AX_SUCCESS;
    // AX620E TODO: for deinit module?
    if (CAlgoOptionHelper::GetInstance()->IsEnableMD()) {
        ret = AX_IVES_MD_DeInit();
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVES, "AX_IVES_MD_Init() fail, ret = 0x%x", ret);
            return AX_FALSE;
        }
    }
    if (CAlgoOptionHelper::GetInstance()->IsEnableOD()) {
        ret = AX_IVES_OD_DeInit();
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVES, "AX_IVES_OD_Init() fail, ret = 0x%x", ret);
            return AX_FALSE;
        }
    }
    if (CAlgoOptionHelper::GetInstance()->IsEnableSCD()) {
        ret = AX_IVES_SCD_DeInit();
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVES, "AX_IVES_SCD_Init() fail, ret = 0x%x", ret);
            return AX_FALSE;
        }
    }

    LOG_MM_C(IVES, "---");
    return AX_TRUE;
}

AX_BOOL CIVESStage::Start(AX_VOID) {
    AX_CHAR cThreadName[32];
    sprintf(cThreadName, "APP_IVES_%d", m_nGroup);
    m_strStageName = cThreadName;
    STAGE_START_PARAM_T tStartParams = {.bStartProcessingThread = AX_TRUE};
    return CAXStage::Start(&tStartParams);
}

AX_BOOL CIVESStage::SendFrame(AX_U32 nSnsID, CAXFrame *pAxFrame) {
    if (m_spFramectrl && m_spFramectrl->FramerateCtrl()) {
        pAxFrame->FreeMem();
        return AX_TRUE;
    }

    return EnqueueFrame(pAxFrame);
}

AX_BOOL CIVESStage::ProcessFrame(CAXFrame *pAxFrame) {
    std::unique_lock<std::mutex> lck(m_mutx, std::defer_lock);
    if (!lck.try_lock()) {
        return AX_TRUE;
    }

    AX_U8 nSnsID = m_stAttr.nSnsSrc;
    do {
        if (m_bReseting) {
            /* clean queue*/
            LOG_MM_W(IVES, "Drop one frame");
            break;
        }

        IVES_RESULT_T ives;
        ives.nSeqNum = pAxFrame->stFrame.stVFrame.stVFrame.u64SeqNum;
        ives.nW = pAxFrame->stFrame.stVFrame.stVFrame.u32Width;
        ives.nH = pAxFrame->stFrame.stVFrame.stVFrame.u32Height;
        ives.nGrpId = nSnsID;
        CIvesResult::GetInstance()->Set(nSnsID, ives);

        if (m_bMDEnable) {
            m_spMDInstance->ProcessFrame(nSnsID, pAxFrame);
        }
        if (m_bODEnable) {
            m_spODInstance->ProcessFrame(nSnsID, pAxFrame);
        }
        if (m_bSCDEnable) {
            m_spSCDInstance->ProcessFrame(nSnsID, pAxFrame);
        }

        CIvesResult::GetInstance()->Get(nSnsID, ives);
        NotifyAll(nSnsID, 0, &ives);
        LOG_MM_D(IVES, " Seq: %lld, w:%d, h:%d, size:%u, PhyAddr:%lld", pAxFrame->stFrame.stVFrame.stVFrame.u64SeqNum,
                 pAxFrame->stFrame.stVFrame.stVFrame.u32Width, pAxFrame->stFrame.stVFrame.stVFrame.u32Height,
                 pAxFrame->stFrame.stVFrame.stVFrame.u32FrameSize, pAxFrame->stFrame.stVFrame.stVFrame.u64PhyAddr[0]);
    } while (0);

    return AX_FALSE;
}

AX_BOOL CIVESStage::Stop(AX_VOID) {
    LOG_MM_C(IVES, "[%d] +++", m_nGroup);

    CAXStage::Stop();

    if (m_spMDInstance) {
        m_spMDInstance->Cleanup();
    }
    if (m_spODInstance) {
        m_spODInstance->Cleanup();
    }
    if (m_spSCDInstance) {
        m_spSCDInstance->Cleanup();
    }

    LOG_MM_C(IVES, "[%d] ---", m_nGroup);
    return AX_TRUE;
}

AX_BOOL CIVESStage::DeInit(AX_VOID) {
    LOG_MM_C(IVES, "[%d] +++", m_nGroup);

    CAXStage::DeInit();

    m_spMDInstance.reset();
    m_spODInstance.reset();
    m_spSCDInstance.reset();
    m_spFramectrl.reset();

    LOG_MM_C(IVES, "[%d] ---", m_nGroup);
    return AX_TRUE;
}

AX_BOOL CIVESStage::UpdateRotation(AX_U8 nRotation) {
    LOG_MM_C(IVES, "+++");

    std::lock_guard<std::mutex> lck(m_mutx);
    if (!ClearQueue()) {
        LOG_MM_W(IVES, "[%d] CAXStage clear lockQueue Failed.", m_stAttr.nSnsSrc);
    }
    m_bReseting = AX_TRUE;
    AX_U8 nSnsID = m_stAttr.nSnsSrc;
    AX_U32 nFrmW = 0;
    AX_U32 nFrmH = 0;
    GetResolutionByRotate(nRotation, nFrmW, nFrmH);
    LOG_MM_I(IVES, "IVES nSnsID:%d, Newwidth:%d, Newheight:%d, frameRate:%f", nSnsID, nFrmW, nFrmH, m_stAttr.fSrcFramerate);

    AX_BOOL ret = AX_TRUE;
    /*init MD */
    if (m_spMDInstance) {
        m_spMDInstance->UpdateResolution(nRotation, nFrmW, nFrmH);

        ret = AX_TRUE;
    }

    /*init OD */
    if (m_spODInstance) {
        m_spODInstance->UpdateResolution(nFrmW, nFrmH);

        ret = AX_TRUE;
    }

    /*init SCD */
    if (m_spSCDInstance) {
        m_spSCDInstance->UpdateResolution(nFrmW, nFrmH);

        ret = AX_TRUE;
    }

    m_bReseting = AX_FALSE;
    LOG_MM_C(IVES, "---");
    return ret;
}

AX_BOOL CIVESStage::GetResolutionByRotate(AX_U8 nRotation, AX_U32 &nWidth, AX_U32 &nHeight) {
    nWidth = m_stAttr.nWidth;
    nHeight = m_stAttr.nHeight;

    // nRotation 0: 0; 1: 90; 2: 180; 3: 270
    if (1 == nRotation || 3 == nRotation) {
        std::swap(nWidth, nHeight);
    }

    return AX_TRUE;
}

AX_VOID CIVESStage::RegObserver(IObserver *pObserver) {
    if (nullptr != pObserver) {
        OBS_TRANS_ATTR_T tTransAttr;
        tTransAttr.nGroup = m_stAttr.nSnsSrc;
        tTransAttr.nChannel = 0;

        if (pObserver->OnRegisterObserver(E_OBS_TARGET_TYPE_EVENT, tTransAttr.nGroup, 0, &tTransAttr)) {
            m_vecObserver.emplace_back(pObserver);
        }
    }
}

AX_VOID CIVESStage::UnregObserver(IObserver *pObserver) {
    if (nullptr == pObserver) {
        return;
    }

    for (std::vector<IObserver *>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        if (*it == pObserver) {
            m_vecObserver.erase(it);
            break;
        }
    }
}

AX_VOID CIVESStage::NotifyAll(AX_U32 nGrp, AX_U32 nChn, AX_VOID *pStream) {
    for (std::vector<IObserver *>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        (*it)->OnRecvData(E_OBS_TARGET_TYPE_EVENT, nGrp, nChn, pStream);
    }
}
