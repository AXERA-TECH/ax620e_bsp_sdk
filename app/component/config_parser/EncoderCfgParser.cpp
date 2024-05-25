/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "EncoderCfgParser.h"
#include <fstream>
#include "AXTypeConverter.hpp"
#include "AppLogApi.h"
#include "CommonUtils.hpp"

using namespace std;

#define ENC_PARSER "ENC_PARSER"

AX_BOOL CEncoderCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CEncoderCfgParser::GetConfig(std::map<AX_U8, VIDEO_CONFIG_T> &mapVencChnConfig, std::map<AX_U8, JPEG_CONFIG_T> &mapJencChnConfig) {
#ifndef _OPAL_LIB_
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }

    string strEncoderCfgFile = strConfigDir + "/encoder.json";

    ifstream ifs(strEncoderCfgFile.c_str());
    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_M_E(ENC_PARSER, "Failed to load json config file: %s", strEncoderCfgFile.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_M_E(ENC_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    if (!ParseFile(strEncoderCfgFile, mapVencChnConfig, mapJencChnConfig)) {
        return AX_FALSE;
    }

    return AX_TRUE;
#else
    return AX_TRUE;
#endif
}

AX_BOOL CEncoderCfgParser::ParseFile(const string &strPath, std::map<AX_U8, VIDEO_CONFIG_T> &mapVencChnConfig,
                                     std::map<AX_U8, JPEG_CONFIG_T> &mapJencChnConfig) {
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

    return ParseJson(v.get<picojson::object>(), mapVencChnConfig, mapJencChnConfig);
#else
    return AX_TRUE;
#endif
}

AX_BOOL CEncoderCfgParser::ParseJson(picojson::object &objJsonRoot, std::map<AX_U8, VIDEO_CONFIG_T> &mapVencChnConfig,
                                     std::map<AX_U8, JPEG_CONFIG_T> &mapJencChnConfig) {
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
            LOG_MM_C(ENC_PARSER, "Links to scenario:%d", nScenario);
            strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);
            if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
                return AX_FALSE;
            }
        }
        std::vector<APP_ENC_RC_CONFIG> vecEncRc;
        /* Parse VENC settings */
        picojson::object &objEncoder = objJsonRoot[strScenario.c_str()].get<picojson::object>();
        picojson::array &arrChnSettings = objEncoder["instance"].get<picojson::array>();
        picojson::array &rcInfoSettings = objEncoder["enc_rc_info"].get<picojson::array>();

        {
            for (size_t k = 0; k < rcInfoSettings.size(); k++) {
                picojson::object &objEncSetting = rcInfoSettings[k].get<picojson::object>();
                AX_U32 nEncodeType = objEncSetting["type"].get<double>();
                APP_ENC_RC_CONFIG stEncRc;
                stEncRc.ePayloadType = CAXTypeConverter::Int2EncoderType(nEncodeType);
                picojson::array &arrRc = rcInfoSettings[k].get<picojson::object>()["rc"].get<picojson::array>();
                for (size_t index = 0; index < arrRc.size(); index++) {
                    picojson::object objRcInfo = arrRc[index].get<picojson::object>();
                    AX_U32 nRcType = objRcInfo["type"].get<double>();
                    stEncRc.stRCInfo[index].eRcType = CAXTypeConverter::FormatRcMode(nEncodeType, nRcType);
                    stEncRc.stRCInfo[index].nMinQp = objRcInfo["min_qp"].get<double>();
                    stEncRc.stRCInfo[index].nMaxQp = objRcInfo["max_qp"].get<double>();
                    if (objRcInfo.end() != objRcInfo.find("fixed_qp")) {
                        stEncRc.stRCInfo[index].nFixQp = objRcInfo["fixed_qp"].get<double>();
                    }

                    if (PT_MJPEG == stEncRc.ePayloadType) {
                        continue;
                    }

                    if (0 == nRcType) {
                        /*cbr*/
                        stEncRc.stRCInfo[index].nMinIQp = objRcInfo["min_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nMaxIQp = objRcInfo["max_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nMinIProp = objRcInfo["min_i_prop"].get<double>();
                        stEncRc.stRCInfo[index].nMaxIProp = objRcInfo["max_i_prop"].get<double>();
                        stEncRc.stRCInfo[index].nIntraQpDelta = objRcInfo["intra_qp_delta"].get<double>();
                        stEncRc.stRCInfo[index].nIdrQpDeltaRange = objRcInfo["idr_qp_delta_range"].get<double>();
                        stEncRc.stRCInfo[index].nDeBreathQpDelta = objRcInfo["de_breath_qp_delta"].get<double>();
                    } else if (1 == nRcType) {
                        /*vbr*/
                        stEncRc.stRCInfo[index].nMinIQp = objRcInfo["min_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nMaxIQp = objRcInfo["max_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nIntraQpDelta = objRcInfo["intra_qp_delta"].get<double>();
                        stEncRc.stRCInfo[index].nIdrQpDeltaRange = objRcInfo["idr_qp_delta_range"].get<double>();
                        stEncRc.stRCInfo[index].nDeBreathQpDelta = objRcInfo["de_breath_qp_delta"].get<double>();
                    } else if (2 == nRcType) {
                    } else if (3 == nRcType) {
                        /* AVBR */
                        stEncRc.stRCInfo[index].nMinIQp = objRcInfo["min_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nMaxIQp = objRcInfo["max_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nIntraQpDelta = objRcInfo["intra_qp_delta"].get<double>();
                        stEncRc.stRCInfo[index].nIdrQpDeltaRange = objRcInfo["idr_qp_delta_range"].get<double>();
                        stEncRc.stRCInfo[index].nDeBreathQpDelta = objRcInfo["de_breath_qp_delta"].get<double>();
                    } else if (4 == nRcType) {
                        /* CVBR */
                        stEncRc.stRCInfo[index].nMinIQp = objRcInfo["min_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nMaxIQp = objRcInfo["max_iqp"].get<double>();
                        stEncRc.stRCInfo[index].nMinIProp = objRcInfo["min_i_prop"].get<double>();
                        stEncRc.stRCInfo[index].nMaxIProp = objRcInfo["max_i_prop"].get<double>();

                        stEncRc.stRCInfo[index].nMinQpDelta = objRcInfo["min_qp_delta"].get<double>();
                        stEncRc.stRCInfo[index].nMaxQpDelta = objRcInfo["max_qp_delta"].get<double>();
                        stEncRc.stRCInfo[index].nShtStaTime = objRcInfo["short_term_time"].get<double>();
                        stEncRc.stRCInfo[index].nLtStaTime = objRcInfo["long_term_time"].get<double>();
                        stEncRc.stRCInfo[index].nLtMinBitrate = objRcInfo["min_long_term_bitrate"].get<double>();
                        stEncRc.stRCInfo[index].nLtMaxBitrate = objRcInfo["max_long_term_bitrate"].get<double>();
                        stEncRc.stRCInfo[index].nIntraQpDelta = objRcInfo["intra_qp_delta"].get<double>();
                        stEncRc.stRCInfo[index].nIdrQpDeltaRange = objRcInfo["idr_qp_delta_range"].get<double>();
                        stEncRc.stRCInfo[index].nDeBreathQpDelta = objRcInfo["de_breath_qp_delta"].get<double>();
                    } else {
                        LOG_MM_E(ENC_PARSER, "rcType unsupport.");
                    }
                }

                vecEncRc.emplace_back(stEncRc);
            }
        }

        if (arrChnSettings.size() > 0) {
            for (size_t j = 0; j < arrChnSettings.size(); j++) {
                picojson::object objSetting = arrChnSettings[j].get<picojson::object>();
                picojson::array &arrBitrate = objSetting["bitrate"].get<picojson::array>();

                if (arrBitrate.size() < APP_ENCODER_TYPE_MAX) {
                    LOG_MM_E(ENC_PARSER, "bitrate settings invalid");
                    return AX_FALSE;
                }

                VIDEO_CONFIG_T tOutConfig;
                tOutConfig.bEnable = AX_TRUE;
                tOutConfig.nChannel = objSetting["channel"].get<double>();
                AX_U32 nEncodeType = objSetting["encoder_type"].get<double>();
                tOutConfig.ePayloadType = CAXTypeConverter::Int2EncoderType(nEncodeType);
                tOutConfig.nBufSize = ENC_MAX_BUF_SIZE;
                if (3 == nEncodeType) {
                    /* Parse JENC settings */
                    JPEG_CONFIG_T tOutConfig;
                    tOutConfig.bEnable = AX_TRUE;
                    tOutConfig.nChannel = objSetting["channel"].get<double>();
                    tOutConfig.nPipeSrc = objSetting["pipe_src"].get<double>();
                    tOutConfig.nInFifoDepth = objSetting["in_fifo_depth"].get<double>();
                    tOutConfig.nOutFifoDepth = objSetting["out_fifo_depth"].get<double>();
                    tOutConfig.eMemSource = (AX_MEMORY_SOURCE_E)objSetting["mem_source"].get<double>();
                    tOutConfig.nQpLevel = objSetting["qp_level"].get<double>();
                    tOutConfig.fDstFrameRate = objSetting["frame_rate"].get<double>();
                    tOutConfig.nBufSize = ENC_MAX_BUF_SIZE;
                    mapJencChnConfig[tOutConfig.nChannel] = tOutConfig;
                    continue;
                }

                tOutConfig.nBitrate = arrBitrate[nEncodeType].get<double>();

                tOutConfig.nPipeSrc = objSetting["pipe_src"].get<double>();
                tOutConfig.nInFifoDepth = objSetting["in_fifo_depth"].get<double>();
                tOutConfig.nOutFifoDepth = objSetting["out_fifo_depth"].get<double>();
                tOutConfig.eMemSource = (AX_MEMORY_SOURCE_E)objSetting["mem_source"].get<double>();
                tOutConfig.nGop = objSetting["gop"].get<double>();
                tOutConfig.fDstFrameRate = objSetting["frame_rate"].get<double>();

                AX_U32 nRcType = objSetting["rc_type"].get<double>();
                tOutConfig.eRcType = CAXTypeConverter::FormatRcMode(nEncodeType, nRcType);
                for (size_t k = 0; k < vecEncRc.size(); k++) {
                    tOutConfig.stEncodeCfg[k] = vecEncRc[k];
                    for (size_t m = 0; m < APP_RC_TYPE_MAX; m++) {
                        AX_U32 nEncodeType = CAXTypeConverter::EncoderType2Int(tOutConfig.stEncodeCfg[k].ePayloadType);
                        tOutConfig.stEncodeCfg[k].stRCInfo[m].nBitrate = arrBitrate[nEncodeType].get<double>();
                    }
                }

                mapVencChnConfig[tOutConfig.nChannel] = tOutConfig;
            }
        }
    } while (0);

    return mapVencChnConfig.size() + mapJencChnConfig.size() > 0 ? AX_TRUE : AX_FALSE;
#else
    return AX_TRUE;
#endif
}
