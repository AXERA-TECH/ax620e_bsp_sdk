/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifdef VO_SUPPORT
#include "VoCfgParser.h"
#include <fstream>
#include "AXTypeConverter.hpp"
#include "AppLogApi.h"
#include "CommonUtils.hpp"

#define VO_PARSER "VO_PARSER"
using namespace std;

AX_BOOL CVOCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CVOCfgParser::GetConfig(std::map<AX_U8, VO_ATTR_T> &mapVoChnConfig) {
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }
    string strDecoderCfgFile = strConfigDir + "/vo.json";

    ifstream ifs(strDecoderCfgFile.c_str());
    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_MM_E(VO_PARSER, "Failed to load json config file: %s", strDecoderCfgFile.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_MM_E(VO_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    if (!ParseFile(strDecoderCfgFile, mapVoChnConfig)) {
        LOG_MM_E(VO_PARSER, "Failed to parse json config file. %s", strDecoderCfgFile.c_str());
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CVOCfgParser::ParseFile(const string &strPath, std::map<AX_U8, VO_ATTR_T> &mapVoChnConfig) {
    picojson::value v;
    ifstream fIn(strPath.c_str());
    if (!fIn.is_open()) {
        return AX_FALSE;
    }

    string strParseRet = picojson::parse(v, fIn);
    if (!strParseRet.empty() || !v.is<picojson::object>()) {
        return AX_FALSE;
    }

    return ParseJson(v.get<picojson::object>(), mapVoChnConfig);
}

AX_BOOL CVOCfgParser::ParseJson(picojson::object &objJsonRoot, std::map<AX_U8, VO_ATTR_T> &mapVoChnConfig) {
    do {
        AX_S32 nScenario = 0;
        CCmdLineParser::GetInstance()->GetScenario(nScenario);
        string strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);

        /* VO moudule is not necessary, so return true */
        if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
            return AX_TRUE;
        }

        /* Parse vo settings */
        picojson::object &objEncoder = objJsonRoot[strScenario.c_str()].get<picojson::object>();
        picojson::array &arrGrpSettings = objEncoder["instance"].get<picojson::array>();

        for (AX_U8 i = 0; i < arrGrpSettings.size(); i++) {
            picojson::object objSetting = arrGrpSettings[i].get<picojson::object>();
            VO_ATTR_T tConfig;
            tConfig.voDev = objSetting["dev_id"].get<double>();
            tConfig.voLayer = objSetting["layer_id"].get<double>();
            tConfig.nLayerDepth = objSetting["layer_depth"].get<double>();
            tConfig.enIntfType = (AX_VO_INTF_TYPE_E)objSetting["interface_type"].get<double>();
            tConfig.enIntfSync = (AX_VO_INTF_SYNC_E)objSetting["interface_sync"].get<double>();
            tConfig.enLayerSync = (AX_VO_LAYER_SYNC_MODE_E)objSetting["layer_sync_mode"].get<double>();
            AX_U8 nNum = objSetting["chn_num"].get<double>();
            tConfig.arrChns.resize(nNum);
            AX_U32 nChnDepth = objSetting["chn_depth"].get<double>();
            for (size_t i = 0; i < nNum; i++) {
                tConfig.arrChns[i].nDepth = nChnDepth;
            }
            mapVoChnConfig[i] = tConfig;
        }

    } while (0);

    return mapVoChnConfig.size() > 0 ? AX_TRUE : AX_FALSE;
}

#endif