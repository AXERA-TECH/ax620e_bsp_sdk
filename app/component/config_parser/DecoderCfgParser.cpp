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
#include "DecoderCfgParser.h"
#include <fstream>
#include "AXTypeConverter.hpp"
#include "AppLogApi.h"
#include "CommonUtils.hpp"

#define DEC_PARSER "DEC_PARSER"
using namespace std;

AX_BOOL CDecoderCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CDecoderCfgParser::GetConfig(std::map<AX_U8, VDEC_GRP_CONFIG_T> &m_mapVdecChnConfig) {
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }
    string strDecoderCfgFile = strConfigDir + "/decoder.json";

    ifstream ifs(strDecoderCfgFile.c_str());
    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_MM_E(DEC_PARSER, "Failed to load json config file: %s", strDecoderCfgFile.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_MM_E(DEC_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    if (!ParseFile(strDecoderCfgFile, m_mapVdecChnConfig)) {
        LOG_MM_E(DEC_PARSER, "Failed to parse json config file. %s", strDecoderCfgFile.c_str());
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CDecoderCfgParser::ParseFile(const string &strPath, std::map<AX_U8, VDEC_GRP_CONFIG_T> &m_mapVdecChnConfig) {
    picojson::value v;
    ifstream fIn(strPath.c_str());
    if (!fIn.is_open()) {
        return AX_FALSE;
    }

    string strParseRet = picojson::parse(v, fIn);
    if (!strParseRet.empty() || !v.is<picojson::object>()) {
        return AX_FALSE;
    }

    return ParseJson(v.get<picojson::object>(), m_mapVdecChnConfig);
}

AX_BOOL CDecoderCfgParser::ParseJson(picojson::object &objJsonRoot, std::map<AX_U8, VDEC_GRP_CONFIG_T> &m_mapVdecChnConfig) {
    do {
        AX_S32 nScenario = 0;
        CCmdLineParser::GetInstance()->GetScenario(nScenario);
        string strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);

        /* VDEC moudule is not necessary, so return true */
        if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
            return AX_TRUE;
        }

        // Links to other scenarios
        if (objJsonRoot[strScenario.c_str()].is<double>()) {
            nScenario = objJsonRoot[strScenario.c_str()].get<double>();
            LOG_MM_C(DEC_PARSER, "Links to scenario:%d", nScenario);
            strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);
            if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
                return AX_FALSE;
            }
        }

        /* Parse vdec settings */
        picojson::object &objEncoder = objJsonRoot[strScenario.c_str()].get<picojson::object>();
        picojson::array &arrGrpSettings = objEncoder["instance"].get<picojson::array>();

        for (AX_U8 i = 0; i < arrGrpSettings.size(); i++) {
            picojson::object objSetting = arrGrpSettings[i].get<picojson::object>();
            VDEC_GRP_CONFIG_T tConfig;
            tConfig.bEnable = AX_TRUE;
            AX_U32 nDecodeType = objSetting["decoder_type"].get<double>();
            tConfig.ePayloadType = CAXTypeConverter::Int2EncoderType(nDecodeType);
            picojson::object &objGrpResolution = objSetting["resolution"].get<picojson::object>();
            tConfig.nWidth = objGrpResolution["w"].get<double>();
            tConfig.nHeight = objGrpResolution["h"].get<double>();
            tConfig.nFrameOutFifoDepth = objSetting["out_fifo_depth"].get<double>();
            tConfig.strPath = objSetting["path"].get<std::string>();
            tConfig.eDisplayMode = (AX_VDEC_DISPLAY_MODE_E)objSetting["display_mode"].get<double>();
            tConfig.eInputMode = (AX_VDEC_INPUT_MODE_E)objSetting["input_mode"].get<double>();
            tConfig.eVdecMode = (AX_VDEC_MODE_E)objSetting["vdec_mode"].get<double>();
            tConfig.fFrameRate = objSetting["framerate"].get<double>();
            LOG_MM_I(DEC_PARSER, "resolution[%d, %d], nFrameOutFifoDepth:%d, strPath:%s, eDiaplayMode:%d, eInputMode:%d, eVdecMode:%d",
                     tConfig.nWidth, tConfig.nHeight, tConfig.nFrameOutFifoDepth, tConfig.strPath.c_str(), tConfig.eDisplayMode,
                     tConfig.eInputMode, tConfig.eVdecMode);
            m_mapVdecChnConfig[i] = tConfig;
        }

    } while (0);

    return m_mapVdecChnConfig.size() > 0 ? AX_TRUE : AX_FALSE;
}

#endif