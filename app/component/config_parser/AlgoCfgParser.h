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
#include "AXAlgo.hpp"
#include "AXSingleton.h"
#include "picojson.h"

class CAlgoCfgParser : public CAXSingleton<CAlgoCfgParser> {
    friend class CAXSingleton<CAlgoCfgParser>;

public:
    AX_BOOL GetConfig(std::map<AX_U8, AX_APP_ALGO_PARAM_T>& stAlgoParam,
                        std::map<AX_U8, AX_APP_ALGO_SVC_PARAM_T>& stAlgoSvcParam,
                        AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam);

private:
    CAlgoCfgParser(AX_VOID) = default;
    ~CAlgoCfgParser(AX_VOID) = default;

    AX_BOOL InitOnce() override;
    AX_BOOL ParseFile(const std::string& strPath,
                        std::map<AX_U8, AX_APP_ALGO_PARAM_T>& stAlgoParam,
                        std::map<AX_U8, AX_APP_ALGO_SVC_PARAM_T>& stAlgoSvcParam,
                        AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam);
    AX_BOOL ParseJson(picojson::object& objJsonRoot,
                        std::map<AX_U8, AX_APP_ALGO_PARAM_T>& stAlgoParam,
                        std::map<AX_U8, AX_APP_ALGO_SVC_PARAM_T>& stAlgoSvcParam,
                        AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam);
    AX_BOOL ParseSkelJson(picojson::object& objJsonRoot, AX_APP_ALGO_PARAM_T& stAlgoParam);
    AX_BOOL ParseIvesJson(picojson::object& objJsonRoot, AX_APP_ALGO_PARAM_T& stAlgoParam);
    AX_BOOL ParseSvcJson(picojson::object& objJsonRoot, AX_APP_ALGO_SVC_PARAM_T& stAlgoSvcParam);
    AX_BOOL ParseAudioJson(picojson::object& objJsonRoot, AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam);
};
