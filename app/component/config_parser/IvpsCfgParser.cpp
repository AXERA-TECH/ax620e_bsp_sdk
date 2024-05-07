/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "IvpsCfgParser.h"
#include <fstream>
#include "AppLogApi.h"
#include "CommonUtils.hpp"

using namespace std;

#define IVPS_PARSER "IVPS_PARSER"

AX_BOOL CIvpsCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CIvpsCfgParser::GetConfig(std::map<AX_U8, IVPS_GROUP_CFG_T> &mapGrpSetting) {
#ifndef _OPAL_LIB_
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }

    string strIvpsCfgFile = strConfigDir + "/ivps.json";

    ifstream ifs(strIvpsCfgFile.c_str());
    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_M_E(IVPS_PARSER, "Failed to load json config file: %s", strIvpsCfgFile.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_M_E(IVPS_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    return ParseFile(strIvpsCfgFile, mapGrpSetting);
#else
    return AX_TRUE;
#endif
}

AX_BOOL CIvpsCfgParser::ParseFile(const string &strPath, std::map<AX_U8, IVPS_GROUP_CFG_T> &mapGrpSetting) {
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

    return ParseJson(v.get<picojson::object>(), mapGrpSetting);
#else
    return AX_TRUE;
#endif
}

AX_BOOL CIvpsCfgParser::ParseJson(picojson::object &objJsonRoot, std::map<AX_U8, IVPS_GROUP_CFG_T> &mapGrpSetting) {
#ifndef _OPAL_LIB_
    do {
        AX_S32 nScenario = 0;
        CCmdLineParser::GetInstance()->GetScenario(nScenario);
        string strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);
        if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
            return AX_FALSE;
        }

        picojson::array &arrGrpSetting = objJsonRoot[strScenario.c_str()].get<picojson::array>();
        if (0 == arrGrpSetting.size()) {
            return AX_FALSE;
        }

        for (size_t i = 0; i < arrGrpSetting.size(); i++) {
            IVPS_GROUP_CFG_T tOutConfig;

            picojson::object objSetting = arrGrpSetting[i].get<picojson::object>();
            tOutConfig.nGrp = objSetting["grp_id"].get<double>();

            picojson::object objGroupInfo = objSetting["grp_info"].get<picojson::object>();
            tOutConfig.nGrpChnNum = objGroupInfo["grp_chn_num"].get<double>();
            tOutConfig.eGrpEngineType0 = Str2Engine(objGroupInfo["engine_filter_0"].get<std::string>());
            tOutConfig.eGrpEngineType1 = Str2Engine(objGroupInfo["engine_filter_1"].get<std::string>());

            picojson::array &arrEngineType2 = objGroupInfo["engine_filter_2"].get<picojson::array>();
            for (size_t i = 0; i < arrEngineType2.size(); i++) {
                tOutConfig.arrChnEngineType0[i] = Str2Engine(arrEngineType2[i].get<std::string>());
            }

            picojson::array &arrEngineType3 = objGroupInfo["engine_filter_3"].get<picojson::array>();
            for (size_t i = 0; i < arrEngineType3.size(); i++) {
                tOutConfig.arrChnEngineType1[i] = Str2Engine(arrEngineType3[i].get<std::string>());
            }

            picojson::object &objGrpFramerate = objGroupInfo["grp_framerate"].get<picojson::object>();
            tOutConfig.arrGrpFramerate[0] = objGrpFramerate["src"].get<double>();
            tOutConfig.arrGrpFramerate[1] = objGrpFramerate["dst"].get<double>();

            picojson::array &arrChnFramerate = objGroupInfo["chn_framerate"].get<picojson::array>();
            for (size_t i = 0; i < arrChnFramerate.size(); i++) {
                tOutConfig.arrChnFramerate[i][0] = arrChnFramerate[i].get<picojson::object>()["src"].get<double>();
                tOutConfig.arrChnFramerate[i][1] = arrChnFramerate[i].get<picojson::object>()["dst"].get<double>();

                if (-1 == tOutConfig.arrChnFramerate[i][0] && -1 != tOutConfig.arrGrpFramerate[1]) {
                    tOutConfig.arrChnFramerate[i][0] = tOutConfig.arrGrpFramerate[1];
                }
            }

            picojson::object &objGrpResolution = objGroupInfo["grp_resolution"].get<picojson::object>();
            tOutConfig.arrGrpResolution[0] = objGrpResolution["w"].get<double>();
            tOutConfig.arrGrpResolution[1] = objGrpResolution["h"].get<double>();

            picojson::array &arrChnResolution = objGroupInfo["chn_resolution"].get<picojson::array>();
            for (size_t i = 0; i < arrChnResolution.size(); i++) {
                tOutConfig.arrChnResolution[i][0] = arrChnResolution[i].get<picojson::object>()["w"].get<double>();
                tOutConfig.arrChnResolution[i][1] = arrChnResolution[i].get<picojson::object>()["h"].get<double>();
            }

            picojson::array &arrChnLinkFlag = objGroupInfo["chn_link_flag"].get<picojson::array>();
            for (size_t i = 0; i < arrChnLinkFlag.size(); i++) {
                tOutConfig.arrChnLinkFlag[i] = arrChnLinkFlag[i].get<double>();
            }

            if (objGroupInfo.end() != objGroupInfo.find("grp_fbc")) {
                picojson::object &objGrpFBC = objGroupInfo["grp_fbc"].get<picojson::object>();
                tOutConfig.arrGrpFBC[0] = objGrpFBC["mode"].get<double>();
                tOutConfig.arrGrpFBC[1] = objGrpFBC["level"].get<double>();
            }
            picojson::array &arrChnFBC = objGroupInfo["chn_fbc"].get<picojson::array>();
            for (size_t i = 0; i < arrChnFBC.size(); i++) {
                tOutConfig.arrChnFBC[i][0] = arrChnFBC[i].get<picojson::object>()["mode"].get<double>();
                tOutConfig.arrChnFBC[i][1] = arrChnFBC[i].get<picojson::object>()["level"].get<double>();
            }

            picojson::array &arrGrpInplace = objGroupInfo["grp_inplace"].get<picojson::array>();
            for (size_t i = 0; i < arrGrpInplace.size() && i < 2; i++) {
                AX_U32 nInplace = arrGrpInplace[i].get<double>();
                tOutConfig.arrGrpInplace[i] = nInplace ? AX_TRUE : AX_FALSE;
            }

            picojson::array &arrChnInplace = objGroupInfo["chn_inplace"].get<picojson::array>();
            for (size_t i = 0; i < arrChnInplace.size() && i < IVPS_MAX_CHANNEL_PER_GROUP; i++) {
                picojson::array &arrChnFilters = arrChnInplace[i].get<picojson::array>();
                AX_U32 nInplace0 = arrChnFilters[0].get<double>();
                tOutConfig.arrChnInplace[i][0] = nInplace0 ? AX_TRUE : AX_FALSE;
                AX_U32 nInplace1 = arrChnFilters[1].get<double>();
                tOutConfig.arrChnInplace[i][1] = nInplace1 ? AX_TRUE : AX_FALSE;
            }

            picojson::array &arrChnSCL = objGroupInfo["chn_scl"].get<picojson::array>();
            for (size_t i = 0; i < arrChnSCL.size(); i++) {
                tOutConfig.arrChnSCL[i] = arrChnSCL[i].get<double>();
            }

            if (objGroupInfo.end() != objGroupInfo.find("chn_voosd_flag")) {
                picojson::array &arryChnVoOsdFlag = objGroupInfo["chn_voosd_flag"].get<picojson::array>();
                for (size_t i = 0; i < arryChnVoOsdFlag.size(); i++) {
                    AX_S32 nVoOsd = arryChnVoOsdFlag[i].get<double>();
                    tOutConfig.bArrChnVoOsdFlag[i] = nVoOsd ? AX_TRUE : AX_FALSE;
                }
            }

            if (objGroupInfo.end() != objGroupInfo.find("grp_in_fifo_depth")) {
                tOutConfig.nGrpInFifoDepth = objGroupInfo["grp_in_fifo_depth"].get<double>();
            }

            if (objGroupInfo.end() != objGroupInfo.find("chn_out_fifo_depth")) {
                picojson::array &arryChnOutFifoDepth = objGroupInfo["chn_out_fifo_depth"].get<picojson::array>();
                for (size_t i = 0; i < arryChnOutFifoDepth.size(); i++) {
                    tOutConfig.arrChnOutFifoDepth[i] = arryChnOutFifoDepth[i].get<double>();
                }
            }

            if (objGroupInfo.end() != objGroupInfo.find("spec_engine_config")) {
                picojson::object &objEngineCfg = objGroupInfo["spec_engine_config"].get<picojson::object>();
                if (objEngineCfg.end() != objEngineCfg.find("mask_enable")) {
                    tOutConfig.nMaskEnable = objEngineCfg["mask_enable"].get<double>();
                }
            }

            mapGrpSetting[tOutConfig.nGrp] = tOutConfig;
        }
    } while (0);

    return mapGrpSetting.size() > 0 ? AX_TRUE : AX_FALSE;
#else
    return AX_TRUE;
#endif
}

AX_IVPS_ENGINE_E CIvpsCfgParser::Str2Engine(string strEngine) {
#ifndef _OPAL_LIB_
    if (strEngine == "TDP") {
        return AX_IVPS_ENGINE_TDP;
    } else if (strEngine == "GDC") {
        return AX_IVPS_ENGINE_GDC;
    } else if (strEngine == "VPP") {
        return AX_IVPS_ENGINE_VPP;
    } else if (strEngine == "VO") {
        return AX_IVPS_ENGINE_VO;
    } else if (strEngine == "SCL") {
        return AX_IVPS_ENGINE_SCL;
    }

    return AX_IVPS_ENGINE_BUTT;
#else
    return AX_IVPS_ENGINE_BUTT;
#endif
}
