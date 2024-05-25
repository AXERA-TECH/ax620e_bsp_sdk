/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "PPLCfgParser.h"
#include <fstream>
#include "AppLogApi.h"
#include "CommonUtils.hpp"

using namespace ::std;

#define PPL_PARSER "PPL_PARSER"

AX_BOOL CPPLCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CPPLCfgParser::GetConfig(std::vector<IPC_MOD_RELATIONSHIP_T>& vecModRelations) {
#ifndef _OPAL_LIB_
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }

    string strPPLCfgFile = strConfigDir + "/ppl.json";

    ifstream ifs(strPPLCfgFile.c_str());
    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_M_E(PPL_PARSER, "Failed to load json config file: %s", strPPLCfgFile.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_M_E(PPL_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    if (!ParseFile(strPPLCfgFile, vecModRelations)) {
        return AX_FALSE;
    }

    return AX_TRUE;
#else
    return AX_TRUE;
#endif
}

AX_BOOL CPPLCfgParser::ParseFile(const std::string& strPath, std::vector<IPC_MOD_RELATIONSHIP_T>& vecModRelations) {
#ifndef _OPAL_LIB_
    picojson::value v;
    ifstream fIn(strPath.c_str());
    if (!fIn.is_open()) {
        return AX_FALSE;
    }

    string strParseRet = picojson::parse(v, fIn);
    if (!strParseRet.empty() || !v.is<picojson::object>()) {
        return AX_FALSE;
    }

    return ParseJson(v.get<picojson::object>(), vecModRelations);
#else
    return AX_TRUE;
#endif
}

AX_BOOL CPPLCfgParser::ParseJson(picojson::object& objJsonRoot, std::vector<IPC_MOD_RELATIONSHIP_T>& vecModRelations) {
#ifndef _OPAL_LIB_
    do {
        AX_S32 nScenario = 0;
        CCmdLineParser::GetInstance()->GetScenario(nScenario);
        string strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);
        if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
            return AX_FALSE;
        }

        // Links to other scenarios
        if (objJsonRoot[strScenario.c_str()].is<double>()) {
            nScenario = objJsonRoot[strScenario.c_str()].get<double>();
            LOG_MM_C(PPL_PARSER, "Links to scenario:%d", nScenario);
            strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);
            if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
                return AX_FALSE;
            }
        }

        picojson::array& arrRelations = objJsonRoot[strScenario.c_str()].get<picojson::array>();
        if (0 == arrRelations.size()) {
            return AX_FALSE;
        }

        for (size_t i = 0; i < arrRelations.size(); i++) {
            IPC_MOD_RELATIONSHIP_T tRelation;

            picojson::object objRelation = arrRelations[i].get<picojson::object>();

            tRelation.tSrcModChn.eModType = Str2Module(objRelation["src_mod"].get<std::string>());
            tRelation.tSrcModChn.nGroup = objRelation["src_grp"].get<double>();
            tRelation.tSrcModChn.nChannel = objRelation["src_chn"].get<double>();
            tRelation.tDstModChn.eModType = Str2Module(objRelation["dst_mod"].get<std::string>());
            tRelation.tDstModChn.nGroup = objRelation["dst_grp"].get<double>();
            tRelation.tDstModChn.nChannel = objRelation["dst_chn"].get<double>();
            tRelation.bLink = objRelation["link"].get<double>() == 0 ? AX_FALSE : AX_TRUE;

            vecModRelations.emplace_back(tRelation);
        }
    } while (0);

    return vecModRelations.size() > 0 ? AX_TRUE : AX_FALSE;
#else
    return AX_TRUE;
#endif
}

PPL_MODULE_TYPE_E CPPLCfgParser::Str2Module(string strModule) {
#ifndef _OPAL_LIB_
    if (strModule == "VIN") {
        return E_PPL_MOD_TYPE_VIN;
    } else if (strModule == "IVPS") {
        return E_PPL_MOD_TYPE_IVPS;
    } else if (strModule == "VENC") {
        return E_PPL_MOD_TYPE_VENC;
    } else if (strModule == "JENC") {
        return E_PPL_MOD_TYPE_JENC;
    } else if (strModule == "JDEC") {
        return E_PPL_MOD_TYPE_JDEC;
    } else if (strModule == "DETECT") {
        return E_PPL_MOD_TYPE_DETECT;
    } else if (strModule == "COLLECT") {
        return E_PPL_MOD_TYPE_COLLECT;
    } else if (strModule == "IVES") {
        return E_PPL_MOD_TYPE_IVES;
    } else if (strModule == "DSP") {
        return E_PPL_MOD_TYPE_DSP;
    } else if (strModule == "CAPTURE") {
        return E_PPL_MOD_TYPE_CAPTURE;
    } else if (strModule == "USER") {
        return E_PPL_MOD_TYPE_USER;
    } else if (strModule == "AVS") {
        return E_PPL_MOD_TYPE_AVS;
    } else if (strModule == "DUMMY_ENC") {
        return E_PPL_MOD_TYPE_DUMMYENC;
    } else if (strModule == "VDEC") {
        return E_PPL_MOD_TYPE_VDEC;
    } else if (strModule == "VO") {
        return E_PPL_MOD_TYPE_VO;
    } else {
        LOG_MM_E(PPL_PARSER, "Unrecognized module specification: %s", strModule.c_str());
    }

    return E_PPL_MOD_TYPE_MAX;
#else
    return E_PPL_MOD_TYPE_MAX;
#endif
}
