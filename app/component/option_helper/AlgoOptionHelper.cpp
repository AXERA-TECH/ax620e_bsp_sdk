/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "AlgoOptionHelper.h"
#include "AlgoCfgParser.h"
#include "CommonUtils.hpp"

AX_BOOL CAlgoOptionHelper::InitOnce() {
    memset(&m_stAudioParam, 0x00, sizeof(m_stAudioParam));

    // default
    for (size_t i = 0; i < AX_APP_ALGO_SNS_MAX; i++) {
        // hvcfp
        m_stAlgoParam[i].stHvcfpParam.bEnable = AX_FALSE;
        m_stAlgoParam[i].stHvcfpParam.stPushStrategy.ePushMode = AX_APP_ALGO_PUSH_MODE_BEST;
        m_stAlgoParam[i].stHvcfpParam.stPushStrategy.nInterval = 2000;
        m_stAlgoParam[i].stHvcfpParam.stPushStrategy.nPushCount = 3;
        m_stAlgoParam[i].stHvcfpParam.nCropEncoderQpLevel = AX_APP_ALGO_DETECT_DEFAULT_QP_LEVEL;
        m_stAlgoParam[i].stHvcfpParam.nFramerate = AX_APP_ALGO_DETECT_DEFAULT_FRAMERATE;
        m_stAlgoParam[i].stHvcfpParam.nObjectTargetFlag = AX_APP_ALGO_DETECT_DEFAULT_OBJECT_FLITER;
        m_stAlgoParam[i].stHvcfpParam.nObjectPushTargetFlag = AX_APP_ALGO_DETECT_DEFAULT_OBJECT_PUSH_FLITER;
        m_stAlgoParam[i].stHvcfpParam.nObjectAnalyzerFlag = AX_APP_ALGO_DETECT_DEFAULT_ANALAYZER;
        m_stAlgoParam[i].stHvcfpParam.bTrackActive = AX_APP_ALGO_DETECT_DEFAULT_TRACK_STATUS;
        m_stAlgoParam[i].stHvcfpParam.bPushActive = AX_APP_ALGO_DETECT_DEFAULT_PUSH_STATUS;
        m_stAlgoParam[i].stHvcfpParam.bPushAttrAlways = AX_APP_ALGO_DETECT_DEFAULT_PUSH_ATTR_ALWAYS;
        m_stAlgoParam[i].stHvcfpParam.stPanoramaConfig.bEnable = AX_APP_ALGO_DETECT_DEFAULT_PANORAMA_STATUS;

        // ives
        m_stAlgoParam[i].stIvesParam.nFramerate = AX_APP_ALGO_IVES_DEFAULT_FRAMERATE;

        // motion
        m_stAlgoParam[i].stMotionParam.bEnable = AX_FALSE;
        m_stAlgoParam[i].stMotionParam.bCapture = AX_FALSE;
        m_stAlgoParam[i].stMotionParam.nRegionSize = 0;
        for (size_t j = 0; j < AX_APP_ALGO_IVES_MD_REGION_MAX; j++) {
            m_stAlgoParam[i].stMotionParam.stRegions[j].bEnable = AX_FALSE;
            m_stAlgoParam[i].stMotionParam.stRegions[j].nMbWidth = AX_APP_ALGO_IVES_MD_DEFAULT_BLOCK_WIDTH;
            m_stAlgoParam[i].stMotionParam.stRegions[j].nMbHeight = AX_APP_ALGO_IVES_MD_DEFAULT_BLOCK_HEIGHT;
            m_stAlgoParam[i].stMotionParam.stRegions[j].fThresholdY = AX_APP_ALGO_IVES_MD_DEFAULT_THRESHOLD_Y;
            m_stAlgoParam[i].stMotionParam.stRegions[j].fConfidence = AX_APP_ALGO_IVES_MD_DEFAULT_CONFIDENCE;
        }

        // Occlusion
        m_stAlgoParam[i].stOcclusionParam.bEnable = AX_FALSE;
        m_stAlgoParam[i].stOcclusionParam.fThreshold = AX_APP_ALGO_IVES_OD_DEFAULT_THRESHOLD_Y;
        m_stAlgoParam[i].stOcclusionParam.fConfidence = AX_APP_ALGO_IVES_OD_DEFAULT_CONFIDENCE_Y;
        m_stAlgoParam[i].stOcclusionParam.fLuxThreshold = AX_APP_ALGO_IVES_OD_DEFAULT_LUX_THRESHOLD;
        m_stAlgoParam[i].stOcclusionParam.fLuxConfidence = AX_APP_ALGO_IVES_OD_DEFAULT_LUX_DIFF;

        // Scene Change
        m_stAlgoParam[i].stSceneChangeParam.bEnable = AX_FALSE;
        m_stAlgoParam[i].stSceneChangeParam.fThreshold = AX_APP_ALGO_IVES_SCD_DEFAULT_THRESHOLD;
        m_stAlgoParam[i].stSceneChangeParam.fConfidence = AX_APP_ALGO_IVES_SCD_DEFAULT_CONFIDENCE;
    }

    return CAlgoCfgParser::GetInstance()->GetConfig(m_stAlgoParam, m_stAudioParam);
}

const AX_APP_ALGO_PARAM_T& CAlgoOptionHelper::GetAlgoParam(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId];
}

const AX_APP_ALGO_HVCFP_PARAM_T& CAlgoOptionHelper::GetHvcfpParam(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stHvcfpParam;
}

const AX_APP_ALGO_IVES_PARAM_T& CAlgoOptionHelper::GetIvesParam(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stIvesParam;
}

const AX_APP_ALGO_MOTION_PARAM_T& CAlgoOptionHelper::GetMDParam(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stMotionParam;
}

const AX_APP_ALGO_OCCLUSION_PARAM_T& CAlgoOptionHelper::GetODParam(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stOcclusionParam;
}

const AX_APP_ALGO_SCENE_CHANGE_PARAM_T& CAlgoOptionHelper::GetSCDParam(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stSceneChangeParam;
}

const AX_APP_ALGO_FACE_RECOGNIZE_PARAM_T& CAlgoOptionHelper::GetFaceRecognizeParam(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stFaceRecognizeParam;
}

const AX_APP_ALGO_AUDIO_PARAM_T& CAlgoOptionHelper::GetAudioParam(AX_VOID) {
    return m_stAudioParam;
}

AX_VOID CAlgoOptionHelper::SetAlgoParam(AX_U32 nSnsId, const AX_APP_ALGO_PARAM_T& stParam) {
    m_stAlgoParam[nSnsId] = stParam;
}

AX_VOID CAlgoOptionHelper::SetHvcfpParam(AX_U32 nSnsId, const AX_APP_ALGO_HVCFP_PARAM_T& stParam) {
    m_stAlgoParam[nSnsId].stHvcfpParam = stParam;
}

AX_VOID CAlgoOptionHelper::SetIvesParam(AX_U32 nSnsId, const AX_APP_ALGO_IVES_PARAM_T& stParam) {
    m_stAlgoParam[nSnsId].stIvesParam = stParam;
}

AX_VOID CAlgoOptionHelper::SetMDParam(AX_U32 nSnsId, const AX_APP_ALGO_MOTION_PARAM_T& stParam) {
    m_stAlgoParam[nSnsId].stMotionParam = stParam;
}

AX_VOID CAlgoOptionHelper::SetODParam(AX_U32 nSnsId, const AX_APP_ALGO_OCCLUSION_PARAM_T& stParam) {
    m_stAlgoParam[nSnsId].stOcclusionParam = stParam;
}

AX_VOID CAlgoOptionHelper::SetSCDParam(AX_U32 nSnsId, const AX_APP_ALGO_SCENE_CHANGE_PARAM_T& stParam) {
    m_stAlgoParam[nSnsId].stSceneChangeParam = stParam;
}

AX_VOID CAlgoOptionHelper::SetFaceRecognizeParam(AX_U32 nSnsId, const AX_APP_ALGO_FACE_RECOGNIZE_PARAM_T& stParam) {
    m_stAlgoParam[nSnsId].stFaceRecognizeParam = stParam;
}

AX_VOID CAlgoOptionHelper::SetAudioParam(const AX_APP_ALGO_AUDIO_PARAM_T& stParam) {
    m_stAudioParam = stParam;
}

AX_U32 CAlgoOptionHelper::GetDetectAlgoType(AX_U32 nSnsId) {
    AX_S32 nDetectAlgoType = 0;

    if (m_stAlgoParam[nSnsId].nAlgoType & (AX_APP_ALGO_FACE_DETECT | AX_APP_ALGO_FACE_RECOGNIZE)) {
        nDetectAlgoType = AX_SKEL_PPL_FH;
    } else if (m_stAlgoParam[nSnsId].nAlgoType & AX_APP_ALGO_LICENSE_PLATE_RECOGNIZE) {
        nDetectAlgoType = AX_SKEL_PPL_HVCP;
    } else if (m_stAlgoParam[nSnsId].nAlgoType & AX_APP_ALGO_TYPE_HVCP) {
        nDetectAlgoType = AX_SKEL_PPL_HVCP;
    }

    return nDetectAlgoType;
}

AX_BOOL CAlgoOptionHelper::IsEnableMD(AX_U32 nSnsId) {
    if (m_stAlgoParam[nSnsId].stMotionParam.bEnable) {
        return AX_TRUE;
    }

    return AX_FALSE;
}

AX_BOOL CAlgoOptionHelper::IsEnableOD(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stOcclusionParam.bEnable;
}

AX_BOOL CAlgoOptionHelper::IsEnableSCD(AX_U32 nSnsId) {
    return m_stAlgoParam[nSnsId].stSceneChangeParam.bEnable;
}

AX_U32 CAlgoOptionHelper::GetDetectAlgoType(AX_VOID) {
    for (AX_U32 i = 0; i < AX_APP_ALGO_SNS_MAX; i++) {
        AX_S32 nDetectAlgoType = GetDetectAlgoType(i);

        if (nDetectAlgoType != 0) {
            return nDetectAlgoType;
        }
    }

    return 0;
}

AX_BOOL CAlgoOptionHelper::IsEnableMD(AX_VOID) {
    for (AX_U32 i = 0; i < AX_APP_ALGO_SNS_MAX; i++) {
        AX_BOOL bEnable = IsEnableMD(i);

        if (bEnable) {
            return AX_TRUE;
        }
    }

    return AX_FALSE;
}

AX_BOOL CAlgoOptionHelper::IsEnableOD(AX_VOID) {
    for (AX_U32 i = 0; i < AX_APP_ALGO_SNS_MAX; i++) {
        AX_BOOL bEnable = IsEnableOD(i);

        if (bEnable) {
            return AX_TRUE;
        }
    }

    return AX_FALSE;
}

AX_BOOL CAlgoOptionHelper::IsEnableSCD(AX_VOID) {
    for (AX_U32 i = 0; i < AX_APP_ALGO_SNS_MAX; i++) {
        AX_BOOL bEnable = IsEnableSCD(i);

        if (bEnable) {
            return AX_TRUE;
        }
    }

    return AX_FALSE;
}
