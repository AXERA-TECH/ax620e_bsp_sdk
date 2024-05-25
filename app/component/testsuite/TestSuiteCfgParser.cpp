/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "TestSuiteCfgParser.h"
#include <fstream>
#include "AXTypeConverter.hpp"
#include "AppLogApi.h"
#include "CommonUtils.hpp"
#define TEST_PARSER "TEST_PARSER"
#define SEARCHKEY(obj, key) (obj.find(key) != obj.end())

using namespace std;

AX_BOOL CTestSuiteCfgParser::InitOnce() {
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }

    string strUTCfgFile = strConfigDir + "/testsuite.json";

    ifstream ifs(strUTCfgFile.c_str());
    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_M_E(TEST_PARSER, "Failed to load json config file: %s", strUTCfgFile.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_M_E(TEST_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    return ParseFile(strUTCfgFile);
}

AX_BOOL CTestSuiteCfgParser::ParseFile(const std::string& strPath) {
    picojson::value v;
    ifstream fIn(strPath.c_str());
    if (!fIn.is_open()) {
        return AX_FALSE;
    }

    string strParseRet = picojson::parse(v, fIn);
    if (!strParseRet.empty() || !v.is<picojson::object>()) {
        return AX_FALSE;
    }
    return ParseJson(v.get<picojson::object>());
}

AX_BOOL CTestSuiteCfgParser::ParseJson(picojson::object& objJsonRoot) {
    LOG_MM_C(TEST_PARSER, "+++");
    picojson::array arrGrpSetting;
    picojson::object moduleSetting;

    vector<TESTSUITE_OPERATION_T>& vecReq = m_vecGrpSetting;

    do {
        AX_S32 nScenario = 0;
        CCmdLineParser::GetInstance()->GetScenario(nScenario);
        string strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nScenario);
        if (objJsonRoot.end() == objJsonRoot.find(strScenario.c_str())) {
            LOG_MM_E(TEST_PARSER, "scenario:%s not found ,please check file!", strScenario.c_str());
            break;
        }
        picojson::object objSetting = objJsonRoot[strScenario.c_str()].get<picojson::object>();
        if (SEARCHKEY(objSetting, "LoopNum") && SEARCHKEY(objSetting, "DefIntervalMs")) {
            m_TestCfg.nLoopNum = objSetting["LoopNum"].get<double>();

            m_TestCfg.nDefIntervalMs = objSetting["DefIntervalMs"].get<double>();
            m_TestCfg.bRandomEnable = (AX_BOOL)objSetting["RandomEnable"].get<double>();

            if (SEARCHKEY(objSetting, "VIN")) {
                ParseVINJson(objSetting, vecReq);
            }
            if (SEARCHKEY(objSetting, "VENC")) {
                ParseVENCJson(objSetting, vecReq);
            }

            if (SEARCHKEY(objSetting, "AI")) {
                ParseAIJson(objSetting, vecReq);
            }

            if (SEARCHKEY(objSetting, "OSD")) {
                ParseOSDJson(objSetting, vecReq);
            }

            if (SEARCHKEY(objSetting, "AUDIO")) {
                ParseAUDIOJson(objSetting, vecReq);
            }
        }
    } while (0);
    LOG_MM_C(TEST_PARSER, "---");
    return m_vecGrpSetting.size() > 0 ? AX_TRUE : AX_FALSE;
}

AX_BOOL CTestSuiteCfgParser::ParseVINJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq) {
    picojson::array arrGrpSns;
    picojson::array arrOpt;
    picojson::object moduleSetting, operObj;
    TESTSUITE_OPERATION_T tOperation;
    AX_U32 nSnsID = 0;
    std::string strOperDes;
    moduleSetting = objSetting["VIN"].get<picojson::object>();
    tOperation.eReqType = E_REQ_TYPE_CAMERA;

    if (SEARCHKEY(moduleSetting, "snsMode")) {
        AX_U32 nSize = moduleSetting["snsMode"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["snsMode"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "sensor_mode_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["sensor_mode_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 nSnsMode = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_SNS_MODE);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tSnsMode.nSnsMode = nSnsMode;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s,nSnsID:%d, snsMode:%f", strOperDes.c_str(), nSnsID,
                                 tOperation.tSnsMode.nSnsMode);
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "frameRate")) {
        AX_U32 nSize = moduleSetting["frameRate"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["frameRate"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "framerate_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["framerate_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 nFrameRate = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_CAMERA_FPS);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tSnsFpsAttr.fSnsFrameRate = nFrameRate;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s,nSnsID:%d, frameRate:%f", strOperDes.c_str(), nSnsID,
                                 tOperation.tSnsFpsAttr.fSnsFrameRate);
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "daynight")) {
        AX_U32 nSize = moduleSetting["daynight"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["daynight"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "daynight_mode_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["daynight_mode_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 nDayNight = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_DAYNIGHT);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tDaynight.nDayNightMode = nDayNight;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_I(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "rotation")) {
        AX_U32 nSize = moduleSetting["rotation"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["rotation"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "rotation_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["rotation_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U8 nRotation = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_ROTATION);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tRotation.nRotation = nRotation;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_I(TEST_PARSER, "operaDesc:%s,nSnsID:%d, nRotation:%d", strOperDes.c_str(), nSnsID,
                                 tOperation.tRotation.nRotation);
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "mirrorFlip")) {
        AX_U32 nSize = moduleSetting["mirrorFlip"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["mirrorFlip"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "mirror_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["mirror_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U8 nMirror = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_SNS_MIRROR_FLIP);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tSnsMirrorFlip.bMirror = (AX_BOOL)nMirror;
                        tOperation.tSnsMirrorFlip.bFlip = (AX_BOOL)(!nMirror);

                        vecReq.emplace_back(tOperation);
                        LOG_MM_I(TEST_PARSER, "operaDesc:%s,nSnsID:%d, bMirror:%d", strOperDes.c_str(), nSnsID,
                                 tOperation.tSnsMirrorFlip.bMirror);
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "eZoom")) {
        AX_U32 nSize = moduleSetting["eZoom"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["eZoom"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "ratio")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["ratio"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U8 nRatio = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_EZOOM);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tEZoom.nEZoomRatio = (AX_BOOL)nRatio;
                        tOperation.tEZoom.nCenterOffsetX = 0;
                        tOperation.tEZoom.nCenterOffsetY = 0;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_I(TEST_PARSER, "operaDesc:%s,nSnsID:%d, nRatio:%d", strOperDes.c_str(), nSnsID,
                                 tOperation.tEZoom.nEZoomRatio);
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "imageAttr")) {
        AX_U32 nSize = moduleSetting["imageAttr"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["imageAttr"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "auto_mode")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["auto_mode"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U8 nAutoMode = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_IMAGE_ATTR);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tImageAttr.nAutoMode = nAutoMode;
                        tOperation.tImageAttr.nBrightness = operObj["brightness"].get<double>();
                        tOperation.tImageAttr.nContrast = operObj["contrast"].get<double>();
                        tOperation.tImageAttr.nSaturation = operObj["saturation"].get<double>();
                        tOperation.tImageAttr.nSharpness = operObj["sharpness"].get<double>();

                        vecReq.emplace_back(tOperation);
                        LOG_MM_I(TEST_PARSER, "operaDesc:%s,nSnsID:%d, nAutoMode:%f", strOperDes.c_str(), nSnsID,
                                 tOperation.tImageAttr.nAutoMode);
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "ldc")) {
        AX_U32 nSize = moduleSetting["ldc"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["ldc"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["enable_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U8 nEnable = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_LDC_ATTR);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tLdcAttr.bLdcEnable = (AX_BOOL)nEnable;
                        tOperation.tLdcAttr.bLdcAspect = AX_FALSE;
                        tOperation.tLdcAttr.nXRatio = operObj["x_ratio"].get<double>();
                        tOperation.tLdcAttr.nYRatio = operObj["y_ratio"].get<double>();
                        tOperation.tLdcAttr.nXYRatio = 0;
                        tOperation.tLdcAttr.nDistorRatio = operObj["distor_ratio"].get<double>();

                        vecReq.emplace_back(tOperation);
                        LOG_MM_I(TEST_PARSER, "operaDesc:%s,nSnsID:%d, nXRatio:%d, nYRatio:%d, nDistorRatio:%d", strOperDes.c_str(), nSnsID,
                                 tOperation.tLdcAttr.nXRatio, tOperation.tLdcAttr.nYRatio, tOperation.tLdcAttr.nDistorRatio);
                    }
                }
            }
        }
    }

    return AX_TRUE;
}

AX_BOOL CTestSuiteCfgParser::ParseVENCJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq) {
    picojson::array arrSnsChn;
    picojson::array arrOpt, appType;
    picojson::object moduleSetting, operObj;
    TESTSUITE_OPERATION_T tOperation;
    AX_U32 nSnsID = 0;
    AX_U32 nChn = 0;
    AX_U8 nEncodeTYpe = 0;
    std::string strOperDes;
    moduleSetting = objSetting["VENC"].get<picojson::object>();
    tOperation.eReqType = E_REQ_TYPE_VIDEO;

    if (SEARCHKEY(moduleSetting, "channelSwitch")) {
        AX_U32 nSize = moduleSetting["channelSwitch"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["channelSwitch"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_channel_option") && SEARCHKEY(operObj, "encode_type_option") &&
                SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrSnsChn = operObj["sns_channel_option"].get<picojson::array>();
                appType = operObj["encode_type_option"].get<picojson::array>();
                for (AX_U32 ti = 0; ti < appType.size(); ti++) {
                    nEncodeTYpe = appType[ti].get<double>();
                    for (AX_U32 j = 0; j < arrSnsChn.size(); j++) {
                        nSnsID = arrSnsChn[j].get<picojson::array>()[0].get<double>();
                        nChn = arrSnsChn[j].get<picojson::array>()[1].get<double>();
                        arrOpt = operObj["enable_option"].get<picojson::array>();
                        for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                            AX_U32 enable = arrOpt[index].get<double>();
                            tOperation.nSnsID = nSnsID;
                            tOperation.nGroup = 0;
                            tOperation.nChannel = nChn;
                            tOperation.SetOperaType(E_WEB_OPERATION_TYPE_CHANNEL_SWITCH);
                            tOperation.tChnSwitch.bOn = (AX_BOOL)enable;
                            tOperation.tChnSwitch.nEncoderType = nEncodeTYpe;
                            vecReq.emplace_back(tOperation);
                            LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                        }
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "resolution")) {
        AX_U32 nSize = moduleSetting["resolution"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["resolution"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_channel_option") && SEARCHKEY(operObj, "encode_type_option") &&
                SEARCHKEY(operObj, "resolution_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrSnsChn = operObj["sns_channel_option"].get<picojson::array>();
                appType = operObj["encode_type_option"].get<picojson::array>();
                for (AX_U32 ti = 0; ti < appType.size(); ti++) {
                    nEncodeTYpe = appType[ti].get<double>();
                    for (AX_U32 j = 0; j < arrSnsChn.size(); j++) {
                        nSnsID = arrSnsChn[j].get<picojson::array>()[0].get<double>();
                        nChn = arrSnsChn[j].get<picojson::array>()[1].get<double>();
                        arrOpt = operObj["resolution_option"].get<picojson::array>();
                        for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                            AX_U32 nWidth = arrOpt[index].get<picojson::array>()[0].get<double>();
                            AX_U32 nHeight = arrOpt[index].get<picojson::array>()[1].get<double>();
                            tOperation.nSnsID = nSnsID;
                            tOperation.nGroup = 0;
                            tOperation.nChannel = nChn;
                            tOperation.SetOperaType(E_WEB_OPERATION_TYPE_RESOLUTION);
                            tOperation.tResolution.nWidth = nWidth;
                            tOperation.tResolution.nHeight = nHeight;
                            tOperation.tResolution.nEncoderType = nEncodeTYpe;
                            vecReq.emplace_back(tOperation);
                            LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                        }
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "rcType")) {
        AX_U32 nSize = moduleSetting["rcType"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["rcType"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_channel_option") && SEARCHKEY(operObj, "encode_type_option") &&
                SEARCHKEY(operObj, "rc_type_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrSnsChn = operObj["sns_channel_option"].get<picojson::array>();
                appType = operObj["encode_type_option"].get<picojson::array>();
                for (AX_U32 ti = 0; ti < appType.size(); ti++) {
                    nEncodeTYpe = appType[ti].get<double>();
                    for (AX_U32 j = 0; j < arrSnsChn.size(); j++) {
                        nSnsID = arrSnsChn[j].get<picojson::array>()[0].get<double>();
                        nChn = arrSnsChn[j].get<picojson::array>()[1].get<double>();
                        arrOpt = operObj["rc_type_option"].get<picojson::array>();
                        for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                            AX_U32 nRctype = arrOpt[index].get<double>();
                            tOperation.nSnsID = nSnsID;
                            tOperation.nGroup = 0;
                            tOperation.nChannel = nChn;
                            tOperation.SetOperaType(E_WEB_OPERATION_TYPE_RC_INFO);
                            tOperation.tRcInfo.nEncoderType = nEncodeTYpe;
                            tOperation.tRcInfo.eRcType = CAXTypeConverter::FormatRcMode(nEncodeTYpe, nRctype);
                            tOperation.tRcInfo.nMinQp = operObj["min_qp"].get<double>();
                            tOperation.tRcInfo.nMaxQp = operObj["max_qp"].get<double>();
                            tOperation.tRcInfo.nMinIQp = operObj["min_iqp"].get<double>();
                            tOperation.tRcInfo.nMaxIQp = operObj["max_iqp"].get<double>();
                            tOperation.tRcInfo.nMinIProp = operObj["min_iprop"].get<double>();
                            tOperation.tRcInfo.nMaxIProp = operObj["max_iprop"].get<double>();
                            tOperation.tRcInfo.nBitrate = operObj["bitRate"].get<double>();
                            tOperation.tRcInfo.nGop = operObj["gop"].get<double>();
                            vecReq.emplace_back(tOperation);
                        }
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "iprop")) {
        AX_U32 nSize = moduleSetting["iprop"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["iprop"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_channel_option") && SEARCHKEY(operObj, "encode_type_option") &&
                SEARCHKEY(operObj, "iprop_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                AX_U32 nRctype = operObj["rc_type"].get<double>();
                arrSnsChn = operObj["sns_channel_option"].get<picojson::array>();
                appType = operObj["encode_type_option"].get<picojson::array>();
                for (AX_U32 ti = 0; ti < appType.size(); ti++) {
                    nEncodeTYpe = appType[ti].get<double>();
                    for (AX_U32 j = 0; j < arrSnsChn.size(); j++) {
                        nSnsID = arrSnsChn[j].get<picojson::array>()[0].get<double>();
                        nChn = arrSnsChn[j].get<picojson::array>()[1].get<double>();
                        arrOpt = operObj["iprop_option"].get<picojson::array>();
                        for (AX_U32 iIndex = 0; iIndex < arrOpt.size(); iIndex++) {
                            for (AX_U32 jIndex = 0; jIndex < arrOpt.size(); jIndex++) {
                                AX_U32 min_iprop = arrOpt[iIndex].get<double>();
                                AX_U32 max_iprop = arrOpt[jIndex].get<double>();
                                if (max_iprop > min_iprop) {
                                    tOperation.nSnsID = nSnsID;
                                    tOperation.nGroup = 0;
                                    tOperation.nChannel = nChn;
                                    tOperation.SetOperaType(E_WEB_OPERATION_TYPE_RC_INFO);
                                    tOperation.tRcInfo.nEncoderType = nEncodeTYpe;
                                    tOperation.tRcInfo.eRcType = CAXTypeConverter::FormatRcMode(nEncodeTYpe, nRctype);
                                    tOperation.tRcInfo.nMaxIProp = max_iprop;
                                    tOperation.tRcInfo.nMinIProp = min_iprop;
                                    vecReq.emplace_back(tOperation);
                                    LOG_MM_D(TEST_PARSER, "operaDesc:%s, min:%d, max:%d", strOperDes.c_str(), min_iprop, max_iprop);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "linkEnable")) {
        AX_U32 nSize = moduleSetting["linkEnable"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["linkEnable"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_channel_option") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }

                arrSnsChn = operObj["sns_channel_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrSnsChn.size(); j++) {
                    nSnsID = arrSnsChn[j].get<picojson::array>()[0].get<double>();
                    nChn = arrSnsChn[j].get<picojson::array>()[1].get<double>();
                    arrOpt = operObj["enable_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 enable = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_VENC_LINK_ENABLE);
                        tOperation.nSnsID = nSnsID;
                        tOperation.nGroup = 0;
                        tOperation.nChannel = nChn;
                        tOperation.tVencLinkEnable.bLinkEnable = (AX_BOOL)enable;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s, bLinkEnable:%d", strOperDes.c_str(), enable);
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "encodeType")) {
        AX_U32 nSize = moduleSetting["encodeType"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["encodeType"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_channel_option") && SEARCHKEY(operObj, "encode_type_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrSnsChn = operObj["sns_channel_option"].get<picojson::array>();
                appType = operObj["encode_type_option"].get<picojson::array>();
                for (AX_U32 ti = 0; ti < appType.size(); ti++) {
                    nEncodeTYpe = appType[ti].get<double>();
                    for (AX_U32 j = 0; j < arrSnsChn.size(); j++) {
                        nSnsID = arrSnsChn[j].get<picojson::array>()[0].get<double>();
                        nChn = arrSnsChn[j].get<picojson::array>()[1].get<double>();
                        tOperation.nSnsID = nSnsID;
                        tOperation.nGroup = 0;
                        tOperation.nChannel = nChn;
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_ENC_TYPE);
                        tOperation.tEncType.nEncoderType = nEncodeTYpe;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                    }
                }
            }
        }
    }
    return AX_TRUE;
}

AX_BOOL CTestSuiteCfgParser::ParseAIJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq) {
    picojson::array arrGrpSns;
    picojson::array arrOpt;
    picojson::object moduleSetting, operObj;
    TESTSUITE_OPERATION_T tOperation;
    AX_U32 nSnsID = 0;
    std::string strOperDes;
    moduleSetting = objSetting["AI"].get<picojson::object>();
    tOperation.eReqType = E_REQ_TYPE_AI;

    if (SEARCHKEY(moduleSetting, "rectSwitch")) {
        AX_U32 nSize = moduleSetting["rectSwitch"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["rectSwitch"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["enable_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 enable = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_AI_ENABLE);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tAiEnable.bOn = (AX_BOOL)enable;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "pushMode")) {
        AX_U32 nSize = moduleSetting["pushMode"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["pushMode"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "push_mode_option") &&
                SEARCHKEY(operObj, "push_interval_option") && SEARCHKEY(operObj, "push_count")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                arrOpt = operObj["push_mode_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 nMode = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_AI_PUSH_MODE);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tAiPushStategy.ePushMode = (E_AI_DETECT_PUSH_MODE_TYPE)nMode;
                        tOperation.tAiPushStategy.nPushIntervalMs = operObj["push_interval_option"].get<double>();
                        tOperation.tAiPushStategy.nPushCounts = operObj["push_count"].get<double>();
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "bodyRoi")) {
        AX_U32 nSize = moduleSetting["bodyRoi"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["bodyRoi"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["enable_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 enable = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_AI_AE_ROI);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tAiAeRoi.bEnable = (AX_BOOL)enable;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "ives")) {
        AX_U32 nSize = moduleSetting["ives"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["ives"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["enable_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_BOOL bEnable = (AX_BOOL)arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_AI_EVENT);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tEvent.tMD.bEnable = bEnable;
                        tOperation.tEvent.tMD.nThrsHoldY = 20;
                        tOperation.tEvent.tMD.nConfidence = 50;

                        tOperation.tEvent.tOD.bEnable = bEnable;
                        tOperation.tEvent.tOD.nThrsHoldY = 100;
                        tOperation.tEvent.tOD.nConfidence = 80;

                        tOperation.tEvent.tSCD.bEnable = bEnable;
                        tOperation.tEvent.tSCD.nThrsHoldY = 60;
                        tOperation.tEvent.tSCD.nConfidence = 60;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                    }
                }
            }
        }
    }
    return AX_TRUE;
}

AX_BOOL CTestSuiteCfgParser::ParseOSDJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq) {
    picojson::array arrIndexSns;
    picojson::array arrOpt;
    picojson::array arrindex;
    picojson::object moduleSetting, operObj;
    TESTSUITE_OPERATION_T tOperation;
    AX_U32 nSnsID = 0;
    AX_U32 nVideoIndex = 0;
    std::string strOperDes;
    moduleSetting = objSetting["OSD"].get<picojson::object>();
    tOperation.eReqType = E_REQ_TYPE_OSD;

    if (SEARCHKEY(moduleSetting, "overlaySwitch")) {
        AX_U32 nSize = moduleSetting["overlaySwitch"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["overlaySwitch"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_video_index_option") && SEARCHKEY(operObj, "index") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrIndexSns = operObj["sns_video_index_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrIndexSns.size(); j++) {
                    nSnsID = arrIndexSns[j].get<picojson::array>()[0].get<double>();
                    nVideoIndex = arrIndexSns[j].get<picojson::array>()[1].get<double>();
                    arrindex = operObj["index"].get<picojson::array>();
                    for (AX_U32 indexI = 0; indexI < arrindex.size(); indexI++) {
                        arrOpt = operObj["enable_option"].get<picojson::array>();
                        for (AX_U32 indexO = 0; indexO < arrOpt.size(); indexO++) {
                            AX_U32 nEnable = arrOpt[indexO].get<double>();
                            tOperation.SetOperaType(E_WEB_OPERATION_TYPE_OSD_ATTR);
                            AX_U8 nIndex = arrindex[indexI].get<double>();
                            tOperation.nSnsID = nSnsID;
                            tOperation.tOsdAttr.nVideoIndex = (AX_BOOL)nVideoIndex;
                            tOperation.tOsdAttr.nOsdIndex = nIndex;
                            tOperation.tOsdAttr.bOn = (AX_BOOL)nEnable;
                            LOG_MM_I(TEST_PARSER, "[%d %d] operaDesc:%s, nOsdIndex:%d, nEnable:%d", nSnsID, nVideoIndex, strOperDes.c_str(),
                                     nIndex, nEnable);
                            vecReq.emplace_back(tOperation);
                        }
                    }
                }
            }
        }
    }

    if (SEARCHKEY(moduleSetting, "privacySwitch")) {
        AX_U32 nSize = moduleSetting["privacySwitch"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["privacySwitch"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_video_index_option") && SEARCHKEY(operObj, "priv_type") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrIndexSns = operObj["sns_video_index_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrIndexSns.size(); j++) {
                    nSnsID = arrIndexSns[j].get<picojson::array>()[0].get<double>();
                    nVideoIndex = arrIndexSns[j].get<picojson::array>()[1].get<double>();
                    arrindex = operObj["priv_type"].get<picojson::array>();
                    for (AX_U32 indexI = 0; indexI < arrindex.size(); indexI++) {
                        arrOpt = operObj["enable_option"].get<picojson::array>();
                        for (AX_U32 indexO = 0; indexO < arrOpt.size(); indexO++) {
                            AX_U32 nEnable = arrOpt[indexO].get<double>();
                            tOperation.SetOperaType(E_WEB_OPERATION_TYPE_OSD_ATTR);
                            AX_U8 nType = arrindex[indexI].get<double>();
                            tOperation.nSnsID = nSnsID;
                            tOperation.tOsdAttr.nVideoIndex = (AX_BOOL)nVideoIndex;
                            tOperation.tOsdAttr.nPrivType = nType;
                            tOperation.tOsdAttr.nOsdIndex = 4;
                            tOperation.tOsdAttr.bOn = (AX_BOOL)nEnable;
                            LOG_MM_I(TEST_PARSER, "[%d %d] operaDesc:%s, nPrivType:%d, nEnable:%d", nSnsID, nVideoIndex, strOperDes.c_str(),
                                     nType, nEnable);
                            vecReq.emplace_back(tOperation);
                        }
                    }
                }
            }
        }
    }
    return AX_TRUE;
}

AX_BOOL CTestSuiteCfgParser::ParseAUDIOJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq) {
    picojson::array arrGrpSns;
    picojson::array arrOpt;
    picojson::object moduleSetting, operObj;
    TESTSUITE_OPERATION_T tOperation;
    AX_U32 nSnsID = 0;
    std::string strOperDes;
    moduleSetting = objSetting["AUDIO"].get<picojson::object>();
    tOperation.eReqType = E_REQ_TYPE_AUDIO;

    if (SEARCHKEY(moduleSetting, "aed_attr")) {
        AX_U32 nSize = moduleSetting["aed_attr"].get<picojson::array>().size();
        for (AX_U32 index = 0; index < nSize; index++) {
            operObj = moduleSetting["aed_attr"].get<picojson::array>()[index].get<picojson::object>();
            if (SEARCHKEY(operObj, "sns_id_option") && SEARCHKEY(operObj, "enable_option")) {
                if (SEARCHKEY(operObj, "description")) {
                    strOperDes = tOperation.strDesc = operObj["description"].get<std::string>();
                }
                arrGrpSns = operObj["sns_id_option"].get<picojson::array>();
                for (AX_U32 j = 0; j < arrGrpSns.size(); j++) {
                    nSnsID = arrGrpSns[j].get<double>();
                    arrOpt = operObj["enable_option"].get<picojson::array>();
                    for (AX_U32 index = 0; index < arrOpt.size(); index++) {
                        AX_U32 enable = arrOpt[index].get<double>();
                        tOperation.SetOperaType(E_WEB_OPERATION_TYPE_AUDIO_ATTR);
                        tOperation.nSnsID = nSnsID;
                        tOperation.tAudioAttr.nAedEnable = (AX_BOOL)enable;
                        vecReq.emplace_back(tOperation);
                        LOG_MM_D(TEST_PARSER, "operaDesc:%s", strOperDes.c_str());
                    }
                }
            }
        }
    }
    return AX_TRUE;
}
AX_BOOL CTestSuiteCfgParser::GetUTCase(std::vector<TESTSUITE_OPERATION_T>& vecOutConfig) {
    vecOutConfig = m_vecGrpSetting;
    return AX_TRUE;
}

AX_BOOL CTestSuiteCfgParser::GetTestAttr(APP_TEST_SUITE_CONFIG_T& tTestCfg) {
    tTestCfg = m_TestCfg;
    return AX_TRUE;
}
