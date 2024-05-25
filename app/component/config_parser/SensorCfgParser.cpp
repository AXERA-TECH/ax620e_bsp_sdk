/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "SensorCfgParser.h"
#include <fstream>
#include "AXStringHelper.hpp"
#include "AppLogApi.h"
#include "CommonUtils.hpp"

using namespace std;

#define SNS_PARSER "SNS_PARSER"

AX_BOOL CSensorCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CSensorCfgParser::GetConfig(std::map<AX_U8, SENSOR_CONFIG_T>& mapSensorCfg, AX_U32& nSensorCount) {
#ifndef _OPAL_LIB_
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }

    AX_S32 nLoadType = E_LOAD_TYPE_MAX;
    if (!CCmdLineParser::GetInstance()->GetLoadType(nLoadType)) {
        return AX_FALSE;
    }

    string strFileName = LoadType2FileName(nLoadType);
    string strFilePath = CAXStringHelper::Format("%s/sensor/%s", strConfigDir.c_str(), strFileName.c_str());
    LOG_MM_D(SNS_PARSER, "strFilePath:%s", strFilePath.c_str());
    ifstream ifs(strFilePath.c_str());
    if (!ifs.good()) {
        LOG_M_E(SNS_PARSER, "Sensor config file: %s parse failed.", strFilePath.c_str());
        return AX_FALSE;
    }

    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_M_E(SNS_PARSER, "Failed to load json config file: %s", strFilePath.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_M_E(SNS_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    if (!ParseFile(strFilePath, mapSensorCfg)) {
        return AX_FALSE;
    } else {
        LOG_M(SNS_PARSER, "Parse sensor config file: %s successfully.", strFilePath.c_str());
    }

    AX_S32 nCfgScenario = 0;
    if (!CCmdLineParser::GetInstance()->GetScenario(nCfgScenario)) {
        LOG_MM(SNS_PARSER, "Apply default scenario %d.", nCfgScenario);
    }

    switch (nCfgScenario) {
        case E_APP_SCENARIO_DUAL_SENSOR:
        case E_APP_SCENARIO_DUAL_WITH_VO:
        case E_APP_SCENARIO_DUAL_10_1_WITH_VO:
            nSensorCount = 2;
            break;
        case E_APP_SCENARIO_SINGLE:
        case E_APP_SCENARIO_SINGLE_WITH_VO:
        case E_APP_SCENARIO_SINGLE_10_1__WITH_VO:
            nSensorCount = 1;
            break;
        default:
            nSensorCount = 2;
            break;
    }

#ifdef FRTTESTLP_SUPPORT
    LOG_M_W(SNS_PARSER, "FRTTESTLP_SUPPORT sensor count equal 1");
    nSensorCount = 1;
#endif
    return AX_TRUE;
#else
    return AX_TRUE;
#endif
}

AX_BOOL CSensorCfgParser::ParseFile(const string& strPath, std::map<AX_U8, SENSOR_CONFIG_T>& mapSensorCfg) {
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

    return ParseJson(v.get<picojson::object>(), mapSensorCfg);
#else
    return AX_TRUE;
#endif
}

AX_BOOL CSensorCfgParser::ParseJson(picojson::object& objJsonRoot, std::map<AX_U8, SENSOR_CONFIG_T>& mapSensorCfg) {
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
            LOG_MM_C(SNS_PARSER, "Links to scenario:%d", nScenario);
            strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);
            if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
                return AX_FALSE;
            }
        }

        picojson::array& arrSettings = objJsonRoot[strScenario.c_str()].get<picojson::array>();
        if (0 == arrSettings.size()) {
            return AX_FALSE;
        }

        std::map<AX_U8, SENSOR_CONFIG_T>& mapDev2SnsSetting = mapSensorCfg;
        picojson::object objSetting;
        for (size_t nSettingIndex = 0; nSettingIndex < arrSettings.size(); nSettingIndex++) {
            auto& objSetting = arrSettings[nSettingIndex].get<picojson::object>();

            SENSOR_CONFIG_T tSensorCfg;
            tSensorCfg.nSnsID = objSetting["sns_id"].get<double>();
            tSensorCfg.nDevID = objSetting["dev_id"].get<double>();
            tSensorCfg.nClkId = objSetting["clk_id"].get<double>();
            if (objSetting.end() != objSetting.find("mirror")) {
                tSensorCfg.bMirror = (AX_BOOL)objSetting["mirror"].get<bool>();
            }
            if (objSetting.end() != objSetting.find("flip")) {
                tSensorCfg.bFlip = (AX_BOOL)objSetting["flip"].get<bool>();
            }
            if (objSetting.end() != objSetting.find("rotation")) {
                tSensorCfg.eRotation = (AX_ROTATION_E)objSetting["rotation"].get<double>();
            }
            tSensorCfg.fFrameRate = objSetting["sns_framerate"].get<double>();
            tSensorCfg.eSensorType = (SNS_TYPE_E)objSetting["sns_type"].get<double>();
            tSensorCfg.eSensorMode = (AX_SNS_HDR_MODE_E)objSetting["sns_mode"].get<double>();
            tSensorCfg.eDevMode = (AX_VIN_DEV_MODE_E)objSetting["dev_run_mode"].get<double>();
            tSensorCfg.eSnsOutputMode = (AX_SNS_OUTPUT_MODE_E)objSetting["sns_output_mode"].get<double>();
            tSensorCfg.nResetGpioNum = objSetting["reset_gpio_num"].get<double>();
            tSensorCfg.nLaneNum = objSetting["lane_num"].get<double>();
            tSensorCfg.nBusType = objSetting["bus_type"].get<double>();
            tSensorCfg.nDevNode = objSetting["dev_node"].get<double>();
            tSensorCfg.nI2cAddr = objSetting["i2c_addr"].get<double>();

            if (objSetting.end() != objSetting.find("hdr_ratio")) {
                picojson::object& objHdrRatio = objSetting["hdr_ratio"].get<picojson::object>();

                tSensorCfg.tHdrRatioAttr.bEnable = (AX_BOOL)objHdrRatio["enable"].get<bool>();
                tSensorCfg.tHdrRatioAttr.nRatio = objHdrRatio["ratio"].get<double>();
                tSensorCfg.tHdrRatioAttr.strHdrRatioDefaultBin = objHdrRatio["hdr_ratio_default_bin"].get<std::string>();
                tSensorCfg.tHdrRatioAttr.strHdrRatioModeBin = objHdrRatio["hdr_ratio_mode_bin"].get<std::string>();
            }

            picojson::array& arrSettingIndex = objSetting["setting_index"].get<picojson::array>();
            for (size_t i = 0; i < 3; i++) {
                tSensorCfg.arrSettingIndex[i] = arrSettingIndex[i].get<double>();
            }
            PIPE_CONFIG_T tPipeConfig;
            tPipeConfig.nPipeID = objSetting["pipe_id"].get<double>();
            if (objSetting.end() != objSetting.find("pipe_framerate")) {
                AX_F32 fValue = objSetting["pipe_framerate"].get<double>();
                tPipeConfig.fPipeFramerate = (-1 == fValue) ? tSensorCfg.fFrameRate : fValue;
            }
            picojson::array& arrChnResInfo = objSetting["resolution"].get<picojson::array>();
            for (size_t i = 0; i < arrChnResInfo.size(); i++) {
                if (i >= AX_VIN_CHN_ID_MAX) {
                    continue;
                }
                tPipeConfig.arrChannelAttr[i].nWidth = arrChnResInfo[i].get<picojson::array>()[0].get<double>();
                tPipeConfig.arrChannelAttr[i].nHeight = arrChnResInfo[i].get<picojson::array>()[1].get<double>();
            }

            picojson::array& arrYuvDepth = objSetting["yuv_depth"].get<picojson::array>();
            for (size_t i = 0; i < arrYuvDepth.size(); i++) {
                if (i >= AX_VIN_CHN_ID_MAX) {
                    continue;
                }

                tPipeConfig.arrChannelAttr[i].nYuvDepth = arrYuvDepth[i].get<double>();
            }

            if (objSetting.end() != objSetting.find("chn_framerate")) {
                picojson::array& arrChnFrameRate = objSetting["chn_framerate"].get<picojson::array>();
                for (size_t i = 0; i < arrChnFrameRate.size(); i++) {
                    if (i >= AX_VIN_CHN_ID_MAX) {
                        continue;
                    }

                    AX_F32 fValue = arrChnFrameRate[i].get<double>();
                    tPipeConfig.arrChannelAttr[i].fFrameRate = (-1 == fValue) ? tPipeConfig.fPipeFramerate : fValue;
                }
            }

            picojson::array& arrChnEnable = objSetting["enable_channel"].get<picojson::array>();
            for (size_t i = 0; i < arrChnEnable.size(); i++) {
                if (i >= AX_VIN_CHN_ID_MAX) {
                    continue;
                }

                tPipeConfig.arrChannelAttr[i].bChnEnable = arrChnEnable[i].get<double>() == 0 ? AX_FALSE : AX_TRUE;
            }

            if (objSetting.end() != objSetting.find("chn_frm_mode")) {
                picojson::array& arrChnFrmMode = objSetting["chn_frm_mode"].get<picojson::array>();
                for (size_t i = 0; i < arrChnFrmMode.size(); i++) {
                    if (i >= AX_VIN_CHN_ID_MAX) {
                        continue;
                    }
                    tPipeConfig.arrChannelAttr[i].eFrmMode = (AX_VIN_FRAME_MODE_E)(arrChnFrmMode[i].get<double>() == 0 ? 0 : 1);
                }
            }

            picojson::array& arrChnCompressInfo = objSetting["chn_compress"].get<picojson::array>();
            for (size_t i = 0; i < arrChnCompressInfo.size(); i++) {
                if (i >= AX_VIN_CHN_ID_MAX) {
                    continue;
                }
                tPipeConfig.arrChannelAttr[i].tChnCompressInfo.enCompressMode =
                    (AX_COMPRESS_MODE_E)arrChnCompressInfo[i].get<picojson::array>()[0].get<double>();
                tPipeConfig.arrChannelAttr[i].tChnCompressInfo.u32CompressLevel =
                    arrChnCompressInfo[i].get<picojson::array>()[1].get<double>();
            }

            tPipeConfig.eAiIspMode = (SNS_AIISP_MODE_E)objSetting["enable_aiisp"].get<double>();

            if (objSetting.end() != objSetting.find("ife_compress")) {
                picojson::array& arrIfeCompressInfo = objSetting["ife_compress"].get<picojson::array>();
                for (size_t i = 0; i < arrIfeCompressInfo.size(); i++) {
                    if (i >= AX_SNS_HDR_MODE_MAX) {
                        continue;
                    }
                    tPipeConfig.tIfeCompress[i].enCompressMode =
                        (AX_COMPRESS_MODE_E)arrIfeCompressInfo[i].get<picojson::array>()[0].get<double>();
                    tPipeConfig.tIfeCompress[i].u32CompressLevel =
                        arrIfeCompressInfo[i].get<picojson::array>()[1].get<double>();
                }
            }

            if (objSetting.end() != objSetting.find("ainr_compress")) {
                picojson::array& arrAiNrCompressInfo = objSetting["ainr_compress"].get<picojson::array>();
                for (size_t i = 0; i < arrAiNrCompressInfo.size(); i++) {
                    if (i >= AX_SNS_HDR_MODE_MAX) {
                        continue;
                    }
                    tPipeConfig.tAiNrCompress[i].enCompressMode =
                        (AX_COMPRESS_MODE_E)arrAiNrCompressInfo[i].get<picojson::array>()[0].get<double>();
                    tPipeConfig.tAiNrCompress[i].u32CompressLevel =
                        arrAiNrCompressInfo[i].get<picojson::array>()[1].get<double>();
                }
            }

            if (objSetting.end() != objSetting.find("3dnr_compress")) {
                picojson::array& arr3DNrCompressInfo = objSetting["3dnr_compress"].get<picojson::array>();
                for (size_t i = 0; i < arr3DNrCompressInfo.size(); i++) {
                    if (i >= AX_SNS_HDR_MODE_MAX) {
                        continue;
                    }
                    tPipeConfig.t3DNrCompress[i].enCompressMode =
                        (AX_COMPRESS_MODE_E)arr3DNrCompressInfo[i].get<picojson::array>()[0].get<double>();
                    tPipeConfig.t3DNrCompress[i].u32CompressLevel =
                        arr3DNrCompressInfo[i].get<picojson::array>()[1].get<double>();
                }
            }

            if (objSetting.end() != objSetting.find("master_slave_select")) {
                tSensorCfg.nMasterSlaveSel = (AX_SNS_MASTER_SLAVE_E)objSetting["master_slave_select"].get<double>();
            }

            tPipeConfig.bTuning = objSetting["tuning_ctrl"].get<double>() == 0 ? AX_FALSE : AX_TRUE;
            tPipeConfig.nTuningPort = objSetting["tuning_port"].get<double>();

            picojson::array& arrTuningBin = objSetting["tuning_bin"].get<picojson::array>();
            for (size_t i = 0; i < arrTuningBin.size(); i++) {
                tPipeConfig.vecTuningBin.push_back(arrTuningBin[i].get<string>());
            }

            if (objSetting.end() != objSetting.find("ivps_grp") && objSetting.end() != objSetting.find("vin_ivps_mode")) {
                tPipeConfig.nIvpsGrp = objSetting["ivps_grp"].get<double>();
                tPipeConfig.nVinIvpsMode = objSetting["vin_ivps_mode"].get<double>();
            }

            if (objSetting.end() != objSetting.find("dis")) {
                picojson::object& objDis = objSetting["dis"].get<picojson::object>();
                if (objDis.end() != objDis.find("dis_enable")) {
                    tPipeConfig.tDisAttr.bDisEnable = (AX_BOOL)objDis["dis_enable"].get<double>();
                }
                if (objDis.end() != objDis.find("dis_delay_num")) {
                    tPipeConfig.tDisAttr.nDelayFrameNum = (AX_U8)objDis["dis_delay_num"].get<double>();
                }
                if (objDis.end() != objDis.find("dis_motion_share")) {
                    tPipeConfig.tDisAttr.bMotionShare = (AX_BOOL)objDis["dis_motion_share"].get<double>();
                }
                if (objDis.end() != objDis.find("dis_motion_est")) {
                    tPipeConfig.tDisAttr.bMotionEst = (AX_BOOL)objDis["dis_motion_est"].get<double>();
                }
            }

            if (objSetting.end() != objSetting.find("gdc")) {
                picojson::object& objGDC = objSetting["gdc"].get<picojson::object>();
                if (objGDC.end() != objGDC.find("ldc_enable") && objGDC.end() != objGDC.find("ldc_aspect") &&
                    objGDC.end() != objGDC.find("ldc_x_ratio") && objGDC.end() != objGDC.find("ldc_y_ratio") &&
                    objGDC.end() != objGDC.find("ldc_xy_ratio") && objGDC.end() != objGDC.find("ldc_distor_ratio")) {
                    tPipeConfig.tLdcAttr.bLdcEnable = (AX_BOOL)objGDC["ldc_enable"].get<double>();
                    tPipeConfig.tLdcAttr.bLdcAspect = (AX_BOOL)objGDC["ldc_aspect"].get<double>() ? AX_TRUE : AX_FALSE;
                    tPipeConfig.tLdcAttr.nLdcXRatio = objGDC["ldc_x_ratio"].get<double>();
                    tPipeConfig.tLdcAttr.nLdcYRatio = objGDC["ldc_y_ratio"].get<double>();
                    tPipeConfig.tLdcAttr.nLdcXYRatio = objGDC["ldc_xy_ratio"].get<double>();
                    tPipeConfig.tLdcAttr.nLdcDistortionRatio = objGDC["ldc_distor_ratio"].get<double>();
                }
            }

            // hot noise normal balance
            if (objSetting.end() != objSetting.find("hot_noise_balance")) {
                picojson::object& objHotNoiseBalance = objSetting["hot_noise_balance"].get<picojson::object>();

                tSensorCfg.tHotNoiseBalanceAttr.bEnable = (AX_BOOL)objHotNoiseBalance["enable"].get<bool>();
                tSensorCfg.tHotNoiseBalanceAttr.fNormalThreshold = (AX_F32)objHotNoiseBalance["normal_threshold"].get<double>();
                tSensorCfg.tHotNoiseBalanceAttr.fBalanceThreshold = (AX_F32)objHotNoiseBalance["balance_threshold"].get<double>();
                if (objHotNoiseBalance.end() != objHotNoiseBalance.find("sdr_hot_noise_normal_mode_bin")) {
                    tSensorCfg.tHotNoiseBalanceAttr.strSdrHotNoiseNormalModeBin = objHotNoiseBalance["sdr_hot_noise_normal_mode_bin"].get<std::string>();
                }
                if (objHotNoiseBalance.end() != objHotNoiseBalance.find("sdr_hot_noise_balance_mode_bin")) {
                    tSensorCfg.tHotNoiseBalanceAttr.strSdrHotNoiseBalanceModeBin = objHotNoiseBalance["sdr_hot_noise_balance_mode_bin"].get<std::string>();
                }
                if (objHotNoiseBalance.end() != objHotNoiseBalance.find("hdr_hot_noise_normal_mode_bin")) {
                    tSensorCfg.tHotNoiseBalanceAttr.strHdrHotNoiseNormalModeBin = objHotNoiseBalance["hdr_hot_noise_normal_mode_bin"].get<std::string>();
                }
                if (objHotNoiseBalance.end() != objHotNoiseBalance.find("hdr_hot_noise_balance_mode_bin")) {
                    tSensorCfg.tHotNoiseBalanceAttr.strHdrHotNoiseBalanceModeBin = objHotNoiseBalance["hdr_hot_noise_balance_mode_bin"].get<std::string>();
                }
            }

            /* Merge multiple pipe configs to single sensor config with same sensor id */
            if (mapDev2SnsSetting.find(tSensorCfg.nSnsID) != mapDev2SnsSetting.end()) {
                if (MAX_PIPE_PER_DEVICE == mapDev2SnsSetting[tSensorCfg.nSnsID].nPipeCount) {
                    LOG_M_E(SNS_PARSER, "Configured sensor count exceeding the max number %d\n", MAX_PIPE_PER_DEVICE);
                    return AX_FALSE;
                }

                mapDev2SnsSetting[tSensorCfg.nSnsID].arrPipeAttr[mapDev2SnsSetting[tSensorCfg.nSnsID].nPipeCount] = tPipeConfig;
                mapDev2SnsSetting[tSensorCfg.nSnsID].nPipeCount++;
            } else {
                tSensorCfg.arrPipeAttr[tSensorCfg.nPipeCount] = tPipeConfig;
                tSensorCfg.nPipeCount++;
                mapDev2SnsSetting[tSensorCfg.nSnsID] = tSensorCfg;
            }
        }
    } while (0);

    return mapSensorCfg.size() > 0 ? AX_TRUE : AX_FALSE;
#else
    return AX_TRUE;
#endif
}

string CSensorCfgParser::LoadType2FileName(AX_S32 nLoadType) {
#ifndef _OPAL_LIB_
    AX_IPC_LOAD_TYPE_E eLoadType = (AX_IPC_LOAD_TYPE_E)nLoadType;
    switch (eLoadType) {
        case E_LOAD_TYPE_OS04A10: {
            return "os04a10.json";
        }
        case E_LOAD_TYPE_SC450AI: {
            return "sc450ai.json";
        }
        case E_LOAD_TYPE_IMX678: {
            return "imx678.json";
        }
        case E_LOAD_TYPE_SC200AI: {
            return "sc200ai.json";
        }
        case E_LOAD_TYPE_SC500AI: {
            return "sc500ai.json";
        }
        case E_LOAD_TYPE_SC850SL: {
            return "sc850sl.json";
        }
        case E_LOAD_TYPE_C4395: {
            return "c4395.json";
        }
        case E_LOAD_TYPE_GC4653: {
            return "gc4653.json";
        }
        case E_LOAD_TYPE_MIS2032: {
            return "mis2032.json";
        }
        case E_LOAD_TYPE_OS04A10_SC200AI: {
            return "os04a10_sc200ai.json";
        }
        case E_LOAD_TYPE_SC450AI_SC200AI: {
            return "sc450ai_sc200ai.json";
        }
        case E_LOAD_TYPE_GC4653_SC200AI: {
            return "gc4653_sc200ai.json";
        }
        default: {
            return "os04a10.json";
        }
    }
#else
    return "";
#endif
}
