/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include "AlgoCfgParser.h"
#include <fstream>
#include "AppLogApi.h"
#include "CommonUtils.hpp"
#include "ax_skel_type.h"

using namespace std;

#define ALGO_PARSER "ALGO_PARSER"

#define ALGO_SETTINGS_KEY_STR "algo_settings"

AX_BOOL CAlgoCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CAlgoCfgParser::GetConfig(std::map<AX_U8, AX_APP_ALGO_PARAM_T>& stAlgoParam, AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam) {
#ifndef _OPAL_LIB_
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }

    string strAlgoCfgFile = strConfigDir + "/algo.json";

    ifstream ifs(strAlgoCfgFile.c_str());
    picojson::value v;
    ifs >> v;

    string err = picojson::get_last_error();
    if (!err.empty()) {
        LOG_M_E(ALGO_PARSER, "Failed to load json config file: %s", strAlgoCfgFile.c_str());
        return AX_FALSE;
    }

    if (!v.is<picojson::object>()) {
        LOG_M_E(ALGO_PARSER, "Loaded config file is not a well-formatted JSON.");
        return AX_FALSE;
    }

    if (!ParseFile(strAlgoCfgFile, stAlgoParam, stAudioParam)) {
        return AX_FALSE;
    }

    return AX_TRUE;
#else
    return AX_TRUE;
#endif
}

AX_BOOL CAlgoCfgParser::ParseFile(const string& strPath, std::map<AX_U8, AX_APP_ALGO_PARAM_T>& stAlgoParam,
                                  AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam) {
#ifndef _OPAL_LIB_
    picojson::value v;
    ifstream fIn(strPath.c_str());
    if (!fIn.is_open()) {
        return AX_TRUE;
    }

    string strParseRet = picojson::parse(v, fIn);
    if (!strParseRet.empty() || !v.is<picojson::object>()) {
        return AX_TRUE;
    }

    return ParseJson(v.get<picojson::object>(), stAlgoParam, stAudioParam);
#else
    return AX_TRUE;
#endif
}

AX_BOOL CAlgoCfgParser::ParseJson(picojson::object& objJsonRoot, std::map<AX_U8, AX_APP_ALGO_PARAM_T>& stAlgoParam,
                                  AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam) {
#ifndef _OPAL_LIB_
    // get algo settings
    if (objJsonRoot.end() == objJsonRoot.find(ALGO_SETTINGS_KEY_STR)) {
        return AX_TRUE;
    }

    picojson::array& arrGrpSettings = objJsonRoot[ALGO_SETTINGS_KEY_STR].get<picojson::array>();

    for (size_t i = 0; i < arrGrpSettings.size(); i++) {
        picojson::object objSettings = arrGrpSettings[i].get<picojson::object>();

        AX_U32 nIndex = i;

        if (objSettings.end() != objSettings.find("sns_id")) {
            nIndex = (AX_U32)objSettings["sns_id"].get<double>();
        }

        if (nIndex >= AX_APP_ALGO_SNS_MAX) {
            continue;
        }

        // skel attribute
        ParseSkelJson(objSettings, stAlgoParam[nIndex]);

        // ives attribute
        ParseIvesJson(objSettings, stAlgoParam[nIndex]);
    }

    // get audio attribute
    ParseAudioJson(objJsonRoot, stAudioParam);

    for (size_t i = 0; i < arrGrpSettings.size(); i++) {
        if (stAudioParam.bEnable) {
            stAlgoParam[i].nAlgoType |= AX_APP_ALGO_SOUND_DETECT;
        } else {
            stAlgoParam[i].nAlgoType &= ~AX_APP_ALGO_SOUND_DETECT;
        }
    }

    return AX_TRUE;
#else
    return AX_TRUE;
#endif
}

AX_BOOL CAlgoCfgParser::ParseSkelJson(picojson::object& objJsonRoot, AX_APP_ALGO_PARAM_T& stAlgoParam) {
#ifndef _OPAL_LIB_
    AX_BOOL bSucc = AX_TRUE;

    // get skel attribute
    do {
        // SKEL
        if (objJsonRoot.end() == objJsonRoot.find("SKEL")) {
            bSucc = AX_FALSE;
            break;
        }

        picojson::object& objSkel = objJsonRoot["SKEL"].get<picojson::object>();

        // SKEL.detect_algo_type
        AX_S32 nDetectAlgoType = objSkel["detect_algo_type"].get<double>();

        if (nDetectAlgoType == AX_SKEL_PPL_BODY) {
            stAlgoParam.nAlgoType |= AX_APP_ALGO_PERSON_DETECT;
        } else if (nDetectAlgoType == AX_SKEL_PPL_HVCP) {
            stAlgoParam.nAlgoType |= AX_APP_ALGO_TYPE_HVCP;
        } else if (nDetectAlgoType == AX_SKEL_PPL_FH) {
            stAlgoParam.nAlgoType |= AX_APP_ALGO_TYPE_FH;
        } else if (nDetectAlgoType == 0) {
            stAlgoParam.nAlgoType &= ~AX_APP_ALGO_TYPE_HVCP;
            stAlgoParam.nAlgoType &= ~AX_APP_ALGO_TYPE_FH;
        }

        auto& stHvcfpParam = stAlgoParam.stHvcfpParam;

        if (nDetectAlgoType > 0) {
            stHvcfpParam.bEnable = AX_TRUE;
        }
        else {
            stHvcfpParam.bEnable = AX_FALSE;
        }

        std::string strDetectModelsPath = objSkel["detect_models_path"].get<std::string>();
        strncpy(stHvcfpParam.strDetectModelsPath, strDetectModelsPath.c_str(), AX_APP_ALGO_PATH_LEN - 1);

        // detect track active
        if (objSkel.end() != objSkel.find("detect_track_active")) {
            stHvcfpParam.bTrackActive = (AX_BOOL)objSkel["detect_track_active"].get<bool>();
        }

        // push enabled
        if (objSkel.end() != objSkel.find("push_enabled")) {
            stHvcfpParam.bPushActive = (AX_BOOL)objSkel["push_enabled"].get<bool>();
        }

        // panorama enabled
        if (objSkel.end() != objSkel.find("panorama_enabled")) {
            stHvcfpParam.stPanoramaConfig.bEnable = (AX_BOOL)objSkel["panorama_enabled"].get<bool>();
        }

        // push attribut always
        if (objSkel.end() != objSkel.find("push_attr_always")) {
            stHvcfpParam.bPushAttrAlways = (AX_BOOL)objSkel["push_attr_always"].get<bool>();
        }

        // roi
        if (objSkel.end() != objSkel.find("roi")) {
            stHvcfpParam.stRoiConfig.bEnable = (AX_BOOL)objSkel["roi"].get<picojson::object>()["enable"].get<bool>();

            picojson::array& arrRoiSettings = objSkel["roi"].get<picojson::object>()["points"].get<picojson::array>();

            stHvcfpParam.stRoiConfig.stPolygon.nPointNum = (AX_U32)arrRoiSettings.size();
            stHvcfpParam.stRoiConfig.stPolygon.nPointNum = AX_MIN(stHvcfpParam.stRoiConfig.stPolygon.nPointNum, AX_SKEL_ROI_POINT_MAX);

            for (size_t i = 0; i < stHvcfpParam.stRoiConfig.stPolygon.nPointNum; i++) {
                picojson::object objPoints = arrRoiSettings[i].get<picojson::object>();

                stHvcfpParam.stRoiConfig.stPolygon.stPoints[i].fX = objPoints["x"].get<double>();
                stHvcfpParam.stRoiConfig.stPolygon.stPoints[i].fY = objPoints["y"].get<double>();
            }
        }

        // object filter
        if (objSkel.end() != objSkel.find("object_filter")) {
            stHvcfpParam.nObjectTargetFlag = 0x00;

            picojson::array& arrFliterSettings = objSkel["object_filter"].get<picojson::array>();

            AX_U32 nObjectFilterSize = arrFliterSettings.size();
            nObjectFilterSize = AX_MIN(nObjectFilterSize, AX_APP_ALGO_HVCFP_TYPE_BUTT);

            for (size_t i = 0; i < nObjectFilterSize; i++) {
                picojson::object objfilter = arrFliterSettings[i].get<picojson::object>();

                std::string strObjectCategory = objfilter["object_category"].get<std::string>();

                AX_APP_ALGO_HVCFP_TYPE_E eHvcfpType = AX_APP_ALGO_GET_HVCFP_TYPE(strObjectCategory);

                if (eHvcfpType < AX_APP_ALGO_HVCFP_TYPE_BUTT) {
                    stHvcfpParam.stObjectFliterConfig[i].nWidth = objfilter["width"].get<double>();
                    stHvcfpParam.stObjectFliterConfig[i].nHeight = objfilter["height"].get<double>();
                    stHvcfpParam.stObjectFliterConfig[i].fConfidence = objfilter["confidence"].get<double>();

                    stHvcfpParam.nObjectTargetFlag |= (1 << ((AX_S32)eHvcfpType));
                }
            }
        }

        // push object filter
        if (objSkel.end() != objSkel.find("push_object_filter")) {
            stHvcfpParam.nObjectPushTargetFlag = 0x00;

            picojson::array& arrFliterSettings = objSkel["push_object_filter"].get<picojson::array>();

            AX_U32 nObjectFilterSize = arrFliterSettings.size();
            nObjectFilterSize = AX_MIN(nObjectFilterSize, AX_APP_ALGO_HVCFP_TYPE_BUTT);

            for (size_t i = 0; i < nObjectFilterSize; i++) {
                picojson::object objfilter = arrFliterSettings[i].get<picojson::object>();

                std::string strObjectCategory = objfilter["object_category"].get<std::string>();

                AX_APP_ALGO_HVCFP_TYPE_E eHvcfpType = AX_APP_ALGO_GET_HVCFP_TYPE(strObjectCategory);

                if (eHvcfpType < AX_APP_ALGO_HVCFP_TYPE_BUTT) {
                    if (eHvcfpType == AX_APP_ALGO_HVCFP_FACE) {
                        stHvcfpParam.stPushFliterConfig[eHvcfpType].stFacePushFilterConfig.nWidth = objfilter["width"].get<double>();
                        stHvcfpParam.stPushFliterConfig[eHvcfpType].stFacePushFilterConfig.nHeight = objfilter["height"].get<double>();
                        stHvcfpParam.stPushFliterConfig[eHvcfpType].stFacePushFilterConfig.stFacePoseBlur.fPitch =
                            objfilter["pose_blur"].get<picojson::object>()["pitch"].get<double>();
                        stHvcfpParam.stPushFliterConfig[eHvcfpType].stFacePushFilterConfig.stFacePoseBlur.fYaw =
                            objfilter["pose_blur"].get<picojson::object>()["yaw"].get<double>();
                        stHvcfpParam.stPushFliterConfig[eHvcfpType].stFacePushFilterConfig.stFacePoseBlur.fRoll =
                            objfilter["pose_blur"].get<picojson::object>()["roll"].get<double>();
                        stHvcfpParam.stPushFliterConfig[eHvcfpType].stFacePushFilterConfig.stFacePoseBlur.fBlur =
                            objfilter["pose_blur"].get<picojson::object>()["blur"].get<double>();
                    } else {
                        stHvcfpParam.stPushFliterConfig[eHvcfpType].stCommonPushFilterConfig.fQuality = objfilter["quality"].get<double>();
                    }

                    stHvcfpParam.nObjectPushTargetFlag |= (1 << ((AX_S32)eHvcfpType));
                }
            }
        }

        // object crop scale
        if (objSkel.end() != objSkel.find("push_object_crop_scale")) {
            picojson::array& arrCropSettings = objSkel["push_object_crop_scale"].get<picojson::array>();

            AX_U32 nCropScaleSize = arrCropSettings.size();
            nCropScaleSize = AX_MIN(nCropScaleSize, AX_APP_ALGO_HVCFP_TYPE_BUTT);

            for (size_t i = 0; i < nCropScaleSize; i++) {
                picojson::object objCropScale = arrCropSettings[i].get<picojson::object>();

                std::string strObjectCategory = objCropScale["object_category"].get<std::string>();

                AX_APP_ALGO_HVCFP_TYPE_E eHvcfpType = AX_APP_ALGO_GET_HVCFP_TYPE(strObjectCategory);

                if (eHvcfpType < AX_APP_ALGO_HVCFP_TYPE_BUTT) {
                    stHvcfpParam.stCropThresholdConfig[eHvcfpType].fScaleLeft = objCropScale["scaleleft"].get<double>();
                    stHvcfpParam.stCropThresholdConfig[eHvcfpType].fScaleRight = objCropScale["scaleright"].get<double>();
                    stHvcfpParam.stCropThresholdConfig[eHvcfpType].fScaleTop = objCropScale["scaletop"].get<double>();
                    stHvcfpParam.stCropThresholdConfig[eHvcfpType].fScaleBottom = objCropScale["scalebottom"].get<double>();
                }
            }
        }

        // push strategy
        if (objSkel.end() != objSkel.find("push_strategy")) {
            picojson::object objPushStrategy = objSkel["push_strategy"].get<picojson::object>();

            stHvcfpParam.stPushStrategy.ePushMode = (AX_APP_ALGO_PUSH_MODE_E)objPushStrategy["push_mode"].get<double>();

            stHvcfpParam.stPushStrategy.nInterval = (AX_U32)objPushStrategy["interval_time"].get<double>();

            stHvcfpParam.stPushStrategy.nPushCount = (AX_U32)objPushStrategy["push_counts"].get<double>();
        }

        // ae roi object fliter
        if (objSkel.end() != objSkel.find("ae_roi_object_filter")) {
            picojson::array& arrAeRoiSettings = objSkel["ae_roi_object_filter"].get<picojson::array>();

            AX_U32 nAeRoiSize = arrAeRoiSettings.size();
            nAeRoiSize = AX_MIN(nAeRoiSize, AX_APP_ALGO_HVCFP_TYPE_BUTT);

            for (size_t i = 0; i < nAeRoiSize; i++) {
                picojson::object objAeRoi = arrAeRoiSettings[i].get<picojson::object>();

                std::string strObjectCategory = objAeRoi["object_category"].get<std::string>();

                AX_APP_ALGO_HVCFP_TYPE_E eHvcfpType = AX_APP_ALGO_GET_HVCFP_TYPE(strObjectCategory);

                if (eHvcfpType < AX_APP_ALGO_HVCFP_TYPE_BUTT) {
                    stHvcfpParam.stAeRoiConfig[eHvcfpType].bEnable = (AX_BOOL)objAeRoi["enable"].get<bool>();
                    stHvcfpParam.stAeRoiConfig[eHvcfpType].nWidth = objAeRoi["width"].get<double>();
                    stHvcfpParam.stAeRoiConfig[eHvcfpType].nHeight = objAeRoi["height"].get<double>();
                    stHvcfpParam.stAeRoiConfig[eHvcfpType].eMode = (AX_APP_ALGO_AE_ROI_MODE_E)objAeRoi["mode"].get<double>();
                }
            }
        }

        // analyzer
        if (objSkel.end() != objSkel.find("analyze_attribute")) {
            stHvcfpParam.nObjectAnalyzerFlag = 0;

            picojson::array& arrAnalyzeSettings = objSkel["analyze_attribute"].get<picojson::array>();

            for (size_t i = 0; i < arrAnalyzeSettings.size(); i++) {
                std::string strAnalyzer = arrAnalyzeSettings[i].get<std::string>();
                AX_SKEL_ANALYZER_ATTR_E eAnalyzeAttribute = AX_SKEL_ANALYZER_ATTR_NONE;

                if (strAnalyzer == "ANALYZE_ATTR_FACE_FEATURE") {
                    eAnalyzeAttribute = AX_SKEL_ANALYZER_ATTR_FACE_FEATURE;
                } else if (strAnalyzer == "ANALYZE_ATTR_FACE_ATTRIBUTE") {
                    eAnalyzeAttribute = AX_SKEL_ANALYZER_ATTR_FACE_ATTRIBUTE;
                } else if (strAnalyzer == "ANALYZE_ATTR_PLATE_ATTRIBUTE") {
                    eAnalyzeAttribute = AX_SKEL_ANALYZER_ATTR_PLATE_ATTRIBUTE;
                } else if (strAnalyzer == "ANALYZE_ATTR_NONE") {
                    eAnalyzeAttribute = AX_SKEL_ANALYZER_ATTR_NONE;
                    stHvcfpParam.nObjectAnalyzerFlag = 0;
                    break;
                } else {
                    continue;
                }

                stHvcfpParam.nObjectAnalyzerFlag |= (1 << ((AX_S32)eAnalyzeAttribute));
            }
        }

        if (objSkel.end() != objSkel.find("crop_encoder_qplevel")) {
            stAlgoParam.stHvcfpParam.nCropEncoderQpLevel = (AX_U8)objSkel["crop_encoder_qplevel"].get<double>();
        }

        if (objSkel.end() != objSkel.find("max_track_size")) {
            picojson::object objTrackSize = objSkel["max_track_size"].get<picojson::object>();
            stAlgoParam.stHvcfpParam.stTrackSize.nTrackHumanSize = objTrackSize["human"].get<double>();
            stAlgoParam.stHvcfpParam.stTrackSize.nTrackVehicleSize = objTrackSize["vehicle"].get<double>();
            stAlgoParam.stHvcfpParam.stTrackSize.nTrackCycleSize = objTrackSize["cycle"].get<double>();
        }
    } while (0);

    return bSucc;
#else
    return AX_TRUE;
#endif
}

AX_BOOL CAlgoCfgParser::ParseIvesJson(picojson::object& objJsonRoot, AX_APP_ALGO_PARAM_T& stAlgoParam) {
#ifndef _OPAL_LIB_
    AX_BOOL bSucc = AX_TRUE;

    // get ives attribute
    do {
        // IVES
        if (objJsonRoot.end() == objJsonRoot.find("IVES")) {
            bSucc = AX_FALSE;
            break;
        }

        picojson::object& objIves = objJsonRoot["IVES"].get<picojson::object>();

        // framerate
        if (objIves.end() != objIves.find("framerate")) {
            stAlgoParam.stIvesParam.nFramerate = objIves["framerate"].get<double>();
        }

        // MD
        if (objIves.end() != objIves.find("MD")) {
            picojson::object& objMD = objIves["MD"].get<picojson::object>();

            stAlgoParam.stMotionParam.bEnable = (AX_BOOL)objMD["enable"].get<bool>();

            if (stAlgoParam.stMotionParam.bEnable) {
                stAlgoParam.nAlgoType |= AX_APP_ALGO_MOTION_DETECT;
            } else {
                stAlgoParam.nAlgoType &= ~AX_APP_ALGO_MOTION_DETECT;
            }

            stAlgoParam.stMotionParam.nRegionSize = 1;
            stAlgoParam.stMotionParam.stRegions[0].bEnable = AX_TRUE;
            stAlgoParam.stMotionParam.stRegions[0].nMbWidth = AX_APP_ALGO_IVES_MD_DEFAULT_BLOCK_WIDTH;
            stAlgoParam.stMotionParam.stRegions[0].nMbHeight = AX_APP_ALGO_IVES_MD_DEFAULT_BLOCK_HEIGHT;

            stAlgoParam.stMotionParam.stRegions[0].fThresholdY = objMD["threshold Y"].get<double>();

            std::string strMb = objMD["mb"].get<std::string>();

            std::string::size_type pos = strMb.find('x');
            if (std::string::npos != pos) {
                AX_S32 nW = atoi(strMb.substr(0, pos).c_str());
                AX_S32 nH = atoi(strMb.substr(pos + 1, -1).c_str());
                if (nW > 0 && nH > 0) {
                    stAlgoParam.stMotionParam.stRegions[0].nMbWidth = nW;
                    stAlgoParam.stMotionParam.stRegions[0].nMbHeight = nH;
                }
            }

            stAlgoParam.stMotionParam.stRegions[0].fConfidence = objMD["confidence"].get<double>();
        }

        // OD
        if (objIves.end() != objIves.find("OD")) {
            picojson::object& objOD = objIves["OD"].get<picojson::object>();

            stAlgoParam.stOcclusionParam.bEnable = (AX_BOOL)objOD["enable"].get<bool>();

            if (stAlgoParam.stOcclusionParam.bEnable) {
                stAlgoParam.nAlgoType |= AX_APP_ALGO_OCCLUSION_DETECT;
            } else {
                stAlgoParam.nAlgoType &= ~AX_APP_ALGO_OCCLUSION_DETECT;
            }

            stAlgoParam.stOcclusionParam.fThreshold = objOD["threshold Y"].get<double>();
            stAlgoParam.stOcclusionParam.fConfidence = objOD["confidence Y"].get<double>();
            stAlgoParam.stOcclusionParam.fLuxThreshold = objOD["lux threshold"].get<double>();
            stAlgoParam.stOcclusionParam.fLuxConfidence = objOD["lux diff"].get<double>();
        }

        // SCD
        if (objIves.end() != objIves.find("SCD")) {
            picojson::object& objSCD = objIves["SCD"].get<picojson::object>();

            stAlgoParam.stSceneChangeParam.bEnable = (AX_BOOL)objSCD["enable"].get<bool>();

            if (stAlgoParam.stSceneChangeParam.bEnable) {
                stAlgoParam.nAlgoType |= AX_APP_ALGO_SCENE_CHANGE_DETECT;
            } else {
                stAlgoParam.nAlgoType &= ~AX_APP_ALGO_SCENE_CHANGE_DETECT;
            }

            stAlgoParam.stSceneChangeParam.fThreshold = objSCD["threshold"].get<double>();
            stAlgoParam.stSceneChangeParam.fConfidence = objSCD["confidence"].get<double>();
        }
    } while (0);

    return bSucc;
#else
    return AX_TRUE;
#endif
}

AX_BOOL CAlgoCfgParser::ParseAudioJson(picojson::object& objJsonRoot, AX_APP_ALGO_AUDIO_PARAM_T& stAudioParam) {
#ifndef _OPAL_LIB_
    AX_BOOL bSucc = AX_TRUE;

    // get audio attribute
    do {
        // AUDIO
        if (objJsonRoot.end() == objJsonRoot.find("AUDIO")) {
            bSucc = AX_FALSE;
            break;
        }

        picojson::object& objAudio = objJsonRoot["AUDIO"].get<picojson::object>();

        stAudioParam.bEnable = (AX_BOOL)objAudio["enable"].get<bool>();
        stAudioParam.fThreshold = (AX_F32)objAudio["threshold"].get<double>();
        stAudioParam.nInterval = (AX_U32)objAudio["interval"].get<double>();
    } while (0);

    return bSucc;
#else
    return AX_TRUE;
#endif
}
