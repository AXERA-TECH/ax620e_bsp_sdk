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
#include <string>
#include "AXSingleton.h"
#include "IniWrapper.hpp"

#include "AXAlgo.hpp"

#define ALGO_CONFIG_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetAlgoParam(_SnsId_)
#define ALGO_HVCFP_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetHvcfpParam(_SnsId_)
#define ALGO_IVES_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetIvesParam(_SnsId_)
#define ALGO_MD_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetMDParam(_SnsId_)
#define ALGO_OD_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetODParam(_SnsId_)
#define ALGO_SCD_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetSCDParam(_SnsId_)
#define ALGO_FACE_RECOGNIZE_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetFaceRecognizeParam(_SnsId_)
#define ALGO_AUDIO_PARAM() CAlgoOptionHelper::GetInstance()->GetAudioParam()
#define ALGO_SVC_PARAM(_SnsId_) CAlgoOptionHelper::GetInstance()->GetSvcParam(_SnsId_)

#define SET_ALGO_CONFIG_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetAlgoParam(_SnsId_, _Param_)
#define SET_ALGO_HVCFP_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetHvcfpParam(_SnsId_, _Param_)
#define SET_ALGO_IVES_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetIvesParam(_SnsId_, _Param_)
#define SET_ALGO_MD_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetMDParam(_SnsId_, _Param_)
#define SET_ALGO_OD_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetODParam(_SnsId_, _Param_)
#define SET_ALGO_SCD_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetSCDParam(_SnsId_, _Param_)
#define SET_ALGO_FACE_RECOGNIZE_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetFaceRecognizeParam(_SnsId_, _Param_)
#define SET_ALGO_AUDIO_PARAM(_Param_) CAlgoOptionHelper::GetInstance()->SetAudioParam(_Param_)
#define SET_ALGO_SVC_PARAM(_SnsId_, _Param_) CAlgoOptionHelper::GetInstance()->SetSvcParam(_SnsId_, _Param_)

/**
 * Load configuration
 */
class CAlgoOptionHelper final : public CAXSingleton<CAlgoOptionHelper> {
    friend class CAXSingleton<CAlgoOptionHelper>;

public:
    const AX_APP_ALGO_PARAM_T& GetAlgoParam(AX_U32 nSnsId);
    const AX_APP_ALGO_HVCFP_PARAM_T& GetHvcfpParam(AX_U32 nSnsId);
    const AX_APP_ALGO_IVES_PARAM_T& GetIvesParam(AX_U32 nSnsId);
    const AX_APP_ALGO_MOTION_PARAM_T& GetMDParam(AX_U32 nSnsId);
    const AX_APP_ALGO_OCCLUSION_PARAM_T& GetODParam(AX_U32 nSnsId);
    const AX_APP_ALGO_SCENE_CHANGE_PARAM_T& GetSCDParam(AX_U32 nSnsId);
    const AX_APP_ALGO_FACE_RECOGNIZE_PARAM_T& GetFaceRecognizeParam(AX_U32 nSnsId);
    const AX_APP_ALGO_AUDIO_PARAM_T& GetAudioParam(AX_VOID);
    const AX_APP_ALGO_SVC_PARAM_T& GetSvcParam(AX_U32 nSnsId);

    AX_U32 GetDetectAlgoType(AX_U32 nSnsId);
    AX_BOOL IsEnableMD(AX_U32 nSnsId);
    AX_BOOL IsEnableOD(AX_U32 nSnsId);
    AX_BOOL IsEnableSCD(AX_U32 nSnsId);

    AX_U32 GetDetectAlgoType(AX_VOID);
    AX_BOOL IsEnableMD(AX_VOID);
    AX_BOOL IsEnableOD(AX_VOID);
    AX_BOOL IsEnableSCD(AX_VOID);

    AX_VOID SetAlgoParam(AX_U32 nSnsId, const AX_APP_ALGO_PARAM_T& stParam);
    AX_VOID SetHvcfpParam(AX_U32 nSnsId, const AX_APP_ALGO_HVCFP_PARAM_T& stParam);
    AX_VOID SetIvesParam(AX_U32 nSnsId, const AX_APP_ALGO_IVES_PARAM_T& stParam);
    AX_VOID SetMDParam(AX_U32 nSnsId, const AX_APP_ALGO_MOTION_PARAM_T& stParam);
    AX_VOID SetODParam(AX_U32 nSnsId, const AX_APP_ALGO_OCCLUSION_PARAM_T& stParam);
    AX_VOID SetSCDParam(AX_U32 nSnsId, const AX_APP_ALGO_SCENE_CHANGE_PARAM_T& stParam);
    AX_VOID SetFaceRecognizeParam(AX_U32 nSnsId, const AX_APP_ALGO_FACE_RECOGNIZE_PARAM_T& stParam);
    AX_VOID SetAudioParam(const AX_APP_ALGO_AUDIO_PARAM_T& stParam);
    AX_VOID SetSvcParam(AX_U32 nSnsId, const AX_APP_ALGO_SVC_PARAM_T& stParam);

private:
    CAlgoOptionHelper(AX_VOID) = default;
    ~CAlgoOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    std::map<AX_U8, AX_APP_ALGO_PARAM_T> m_stAlgoParam;
    std::map<AX_U8, AX_APP_ALGO_SVC_PARAM_T> m_stAlgoSvcParam;
    AX_APP_ALGO_AUDIO_PARAM_T m_stAudioParam;
};
