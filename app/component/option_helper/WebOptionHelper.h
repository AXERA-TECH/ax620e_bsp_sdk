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

#include <iostream>
#include <map>
#include <mutex>
#include <vector>
#include "AXSingleton.h"
#include "AXTypeConverter.hpp"
#include "OSDHandler.h"
#include "SensorMgr.h"
#include "VideoEncoder.h"
#include "picojson.h"
#include "IVESStage.h"
#include "WebServer.h"

#define MAX_VIDEO_ATTR_NUM 4
#define MAX_REGION_NUM (32)

struct MprJson;

typedef struct _WEB_CAMERA_ATTR_T {
    AX_U8 nSnsMode;
    AX_U8 nRotation;
    AX_F32 fFramerate;
    AX_U8 nDayNightMode;
    AX_U8 nNrMode;
    AX_U8 nHdrRatio;
    AX_BOOL bMirror;
    AX_BOOL bFlip;
    AX_BOOL bCapture;
    AX_BOOL bCaptureEnable;
    AX_BOOL bFlashEnable;
    AX_BOOL bSnsModeEnable;
    AX_BOOL bPNModeEnable;
    AX_BOOL bTriggerEnable;
    AX_BOOL bMirrorFlipEnable;
    AX_BOOL bRotationEnable;
    AX_BOOL bLdcEnable;
    AX_BOOL bDisSupport;
    AX_BOOL bEZoomEnable;
    AX_BOOL bHdrRatioEnable;
    WEB_OPR_IMAGE_ATTR_T tImageAttr;
    WEB_OPR_LDC_ATTR_T tLdcAttr;
    WEB_OPR_DIS_ATTR_T tDisAttr;
    WEB_OPR_EZOOM_ATTR_T tEZoomAttr;
    _WEB_CAMERA_ATTR_T() {
        nSnsMode = 0;  /* 0: SDR; 1: HDR; 2: SDR/HDR Split */
        nRotation = 0; /* 0:0°; 1:90°; 2:180°; 3:270° */
        fFramerate = 15.0;
        nDayNightMode = 0;         /* 0: Day mode; 1: Night Mode */
        nNrMode = 1;               /* 0: Dummy mode; 1: Nr Mode */
        nHdrRatio = 0;             /* 0: default; 1: 1:1 fusion*/
        bSnsModeEnable = AX_FALSE; /*Switch SDR/HDR */
        bPNModeEnable = AX_FALSE;  /* Switch sensor fps*/
        bCaptureEnable = AX_FALSE; /* Switch capture */
        bFlashEnable = AX_FALSE;   /* flash */
        bTriggerEnable = AX_FALSE; /* Trigger flash */
        bMirror = AX_FALSE;
        bFlip = AX_FALSE;
        bCapture = AX_FALSE;
        bMirrorFlipEnable = AX_FALSE;
        bRotationEnable = AX_FALSE;
        bLdcEnable = AX_FALSE;
        bDisSupport = AX_FALSE;
        bEZoomEnable = AX_FALSE;
        bHdrRatioEnable = AX_FALSE;
    }

} WEB_CAMERA_ATTR_T, *WEB_CAMERA_ATTR_PTR;

typedef struct _WEB_AUDIO_ATTR_T {
    AX_F32 fCapture_volume{0.00f};
    AX_F32 fPlay_volume{0.00f};
    AX_BOOL bAedEnable{AX_FALSE};
    AX_F32 fAedThreshold{0};
    AX_U32 nAedInterval{0};
} WEB_AUDIO_ATTR_T, *WEB_AUDIO_ATTR_PTR;

typedef struct _WEB_VIDEO_ATTR_T {
    AX_U8 nUniChn;
    AX_BOOL bEnable;
    AX_U8 nEncoderType; /* 0: H264; 1: MJpeg 2: H265 */
    AX_U32 nBitrate;
    AX_U32 nGop;
    AX_U32 nWidth;
    AX_U32 nHeight;
    AX_BOOL bLink;
    APP_ENC_RC_CONFIG stEncodeCfg[APP_ENCODER_TYPE_MAX];
    AX_U8 nRcType;
    _WEB_VIDEO_ATTR_T() {
        nUniChn = 0;
        bEnable = AX_TRUE;
        bLink = AX_TRUE;
        nEncoderType = 0;
        nBitrate = 4096;
        nGop = 0;
        nWidth = 0;
        nHeight = 0;
        nRcType = 0;
    }

    AX_BOOL IsSwitcherChanged(const _WEB_VIDEO_ATTR_T tAnother) {
        return (this->bEnable == tAnother.bEnable) ? AX_FALSE : AX_TRUE;
    }

    AX_BOOL IsResolutionChanged(const _WEB_VIDEO_ATTR_T tAnother) {
        return (this->nWidth == tAnother.nWidth && this->nHeight == tAnother.nHeight) ? AX_FALSE : AX_TRUE;
    }

    AX_BOOL IsAttrChanged(const _WEB_VIDEO_ATTR_T tAnother) {
        return (this->nEncoderType == tAnother.nEncoderType && this->nBitrate == tAnother.nBitrate && this->nWidth == tAnother.nWidth &&
                this->nHeight == tAnother.nHeight)
                   ? AX_FALSE
                   : AX_TRUE;
    }
    AX_VOID SetEncRcCfg(RC_INFO_T& tRcInfo) {
        for (int i = 0; i < APP_ENCODER_TYPE_MAX; i++) {
            if (nEncoderType == CAXTypeConverter::EncoderType2Int(stEncodeCfg[i].ePayloadType)) {
                stEncodeCfg[i].SetRcInfo(tRcInfo.eRcType, tRcInfo);
            }
        }
    }
    AX_VOID GetEncRcCfg(RC_INFO_T& tRcInfo) {
        for (int i = 0; i < APP_ENCODER_TYPE_MAX; i++) {
            if (nEncoderType == CAXTypeConverter::EncoderType2Int(stEncodeCfg[i].ePayloadType)) {
                stEncodeCfg[i].GetRcInfo(CAXTypeConverter::FormatRcMode(nEncoderType, nRcType), tRcInfo);
            }
        }
    }

} WEB_VIDEO_ATTR_T, *WEB_VIDEO_ATTR_PTR;

typedef struct _AI_ATTR_T {
    AX_BOOL bEnable{AX_FALSE};
    AI_PUSH_STATEGY_T tPushStategy;
    // AX_U16                  nDetectOnly;
    // AI_CONFIG_T             tConfig;
    // AI_DETECT_MODEL_TYPE_E  eDetectModel;
    AI_EVENTS_OPTION_T tEvents;
    // union {
    //     AI_MODEL_FALCEHUMAN_ATTR_T tHumanFaceSetting;
    //     AI_MODEL_HVCFP_ATTR_T      tHvcfpSetting;
    // };
    AI_AE_ROI_OPTION_T tAeRoiBody;
    AI_SVC_OPTION_T tSvcParam;

    _AI_ATTR_T() {
        // tConfig.nWidth = DETECT_DEFAULT_WIDTH;
        // tConfig.nHeight = DETECT_DEFAULT_HEIGHT;
        // tConfig.nDetectFps = DETECT_DEFAULT_FRAMERATE_CTRL;
        // tConfig.nAiFps = DETECT_DEFAULT_AI_FRAMERATE_CTRL;
        // tConfig.nIvesFps = DETECT_DEFAULT_IVES_FRAMERATE_CTRL;
    }
} AI_ATTR_T, *AI_ATTR_PTR;

typedef struct _STATISTICS_INFO_T {
    AX_U64 nStartTick;
    AX_U32 nVencOutBytes;
    AX_F32 fBitrate;

    _STATISTICS_INFO_T() {
        memset(this, 0, sizeof(_STATISTICS_INFO_T));
    }
} STATISTICS_INFO_T, *STATISTICS_INFO_PTR;

typedef struct _WEB_OSD_CONFIG_T {
    OSD_TYPE_E eType;  // 0：图片，1字符串，2：时间，3矩形框
    AX_U32 nSleepMs;
    _WEB_OSD_CONFIG_T() {
        eType = OSD_TYPE_MAX;
        nSleepMs = 1000;
    }
} WEB_OSD_CONFIG_T;

typedef struct _WEB_AI_SENSOR_CONFIG_T {
    AX_BOOL bEnable;
} WEB_AI_SENSOR_CONFIG_T;

class CWebOptionHelper : public CAXSingleton<CWebOptionHelper> {
    friend class CAXSingleton<CWebOptionHelper>;

public:
    AX_VOID InitCameraAttr(AX_U8 nSnsID, AX_U8 nSnsType, const WEB_CAMERA_ATTR_T& tCameraAttr);
    AX_VOID InitVideoAttr(AX_U8 nSnsID, AX_U8 nChnID, const WEB_VIDEO_ATTR_T& tVideoAttr);
    AX_BOOL InitAiAttr(AX_U8 nSnsID);
    AX_VOID InitIvesAttr(AX_U8 nSnsID, CIVESStage* pIves);
    AX_BOOL GetCapSettingStr(AX_CHAR* pOutBuf, AX_U32 nSize);
    WEB_CAMERA_ATTR_T& GetCamera(AX_U8 nSnsID);
    AX_VOID SetCamera(AX_U8 nSnsID, const WEB_CAMERA_ATTR_T& tCamera);
    MprJson* GetCameraJson(AX_U8 nSnsID);
    AX_BOOL GetImageStr(AX_U8 nSnsID, AX_CHAR* pOutBuf, AX_U32 nSize);
    AX_BOOL GetLdcStr(AX_U8 nSnsID, AX_CHAR* pOutBuf, AX_U32 nSize);
    AX_U8 GetVideoCount(AX_U8 nSnsID);
    WEB_VIDEO_ATTR_T& GetVideo(AX_U8 nSnsID, AX_U32 nChnID);
    AX_VOID SetVideo(AX_U8 nSnsID, AX_U32 nChnID, WEB_VIDEO_ATTR_T& tVideo);
    picojson::object GetVideoJsonObj(AX_U8 nSnsID, AX_U32 nChnID);
    picojson::object GetVideoAttrJsonObj(AX_U8 nSnsID, AX_U32 nChnID);
    AX_BOOL GetVideoByUniChn(AX_U8 nSnsID, AX_U32 nUniChn, WEB_VIDEO_ATTR_T& tVideoAttr);
    AX_VOID SetVideoByUniChn(AX_U8 nSnsID, const WEB_VIDEO_ATTR_T& tVideo);
    std::string GetFramerateOptStr(AX_U8 nSnsID);
    AX_BOOL GetOsdConfig(AX_U8 nSnsId, AX_S32 nGroup, AX_S32 nChn, std::vector<OSD_CFG_T>& vec_osdCfg);
    AX_BOOL SetOsdConfig(AX_U8 nSnsId, AX_S32 nGroup, AX_S32 nChn, std::vector<OSD_CFG_T>& vec_osdCfg);
    MprJson* GetOsdJson(AX_S32 nSnsID);
    MprJson* GetPrivacyJson(AX_S32 nSnsID);
    AX_BOOL IsOsdSwitchOpen(AX_S32 nIvpsGroup);
    AX_BOOL GetDisStr(AX_U8 nSnsID, AX_CHAR* pOutBuf, AX_U32 nSize);

    WEB_AUDIO_ATTR_T& GetAudio();
    AX_VOID SetAudio(const WEB_AUDIO_ATTR_T& tAudio);

    /* AI functions */
    AX_BOOL GetAiInfoStr(AX_U8 nSnsID, AX_CHAR* pOutBuf, AX_U32 nSize);
    std::string GetDetectModelStr();
    AX_BOOL GetPushStrgyStr(AX_U8 nSnsID, AX_CHAR* pOutBuf, AX_U32 nSize);
    std::string GetPushModeStr(AX_S32 mode);
    AX_BOOL GetDetectModelAttrStr(AX_CHAR* pOutBuf, AX_U32 nSize);
    AX_BOOL GetEventsStr(AX_U8 nSnsID, AX_CHAR* pOutBuf, AX_U32 nSize);
    AX_BOOL GetAlgoSvcStr(AX_U8 nSnsID, AX_CHAR* pOutBuf, AX_U32 nSize);
    E_AI_DETECT_PUSH_MODE_TYPE ParseResAiStr(std::string& strAiPushMode);

    AX_BOOL StatVencOutBytes(AX_U8 nSnsID, AX_U32 nUniChn, AX_U32 nBytes);
    AX_BOOL GetAssistBitrateStr(AX_U8 nSnsID, AX_U32 nUniChn, AX_CHAR* pOutBuf, AX_U32 nSize);

    AX_BOOL ParseWebRequest(WEB_REQUEST_TYPE_E eReqType, const AX_VOID* pJsonReq, std::vector<WEB_REQ_OPERATION_T>& vecWebOpr);

    AI_EVENTS_OPTION_T& GetAiEvent(AX_U8 nSnsID);
    AX_VOID SetAiEvent(AX_U8 nSnsID, AI_EVENTS_OPTION_T& tAiEvent);
    AX_VOID SetIvpsGrp2VideoIndex(std::map<std::pair<AX_U8, AX_U8>, std::pair<AX_U8, AX_U8>> pairVideo2Ivps);

    AX_VOID GenerateChnResolutionList(CSensorMgr* snsMgr, std::vector<CVideoEncoder*> vecVencInstance, AX_BOOL bPano = AX_FALSE);

    AX_BOOL SetSnsTypeMainResolution(SNS_TYPE_E eSnsType, AX_U32 nWidth, AX_U32 nHeight);
    AX_BOOL OverlayChnIndex2IvpsGrp(AX_S32 nSnsID, AX_U32 nIndex, std::pair<AX_U8, AX_U8>& ret);

private:
    CWebOptionHelper(AX_VOID);
    ~CWebOptionHelper(AX_VOID);

    virtual AX_BOOL InitOnce() override;

    AX_BOOL CheckRequest(WEB_REQUEST_TYPE_E eReqType, const AX_VOID* pJsonReq);
    AX_BOOL ParseResStr(std::string& strResolution, AX_U32& nWidth, AX_U32& nHeight);
    std::vector<std::string> GetChnResolutionList(AX_U8 nSnsID, AX_U32 nChnID);
    std::string GenResStr(AX_U32 nWidth, AX_U32 nHeight);
    AX_S32 OverlayOffsetX(AX_S32 nWidth, AX_S32 nOsdWidth, AX_S32 nXMargin, OSD_ALIGN_TYPE_E eAlign, OSD_TYPE_E eType);
    AX_S32 OverlayOffsetY(AX_S32 nHeight, AX_S32 nOsdHeight, AX_S32 nYMargin, OSD_ALIGN_TYPE_E eAlign, OSD_TYPE_E eType);
    AX_S32 OverlayBoudingX(AX_S32 nWidth, AX_S32 nOsdWidth, AX_S32 nBoudingX, OSD_ALIGN_TYPE_E eAlign, OSD_TYPE_E eType);
    AX_S32 OverlayBoudingY(AX_S32 nHeight, AX_S32 nOsdHeight, AX_S32 nBoudingY, OSD_ALIGN_TYPE_E eAlign, OSD_TYPE_E eType);

private:
    std::map<AX_U8, std::mutex> m_mapSns2MtxOption;
    std::map<AX_U8, std::mutex> m_mapSns2MtxAi;
    std::mutex m_mtxOverlay;
    std::map<AX_U8, AX_U8> m_mapSnsID2Type;
    std::map<AX_U8, std::string> m_mapSns2FramerateOpt;
    // sensor id : camera attribute
    std::map<AX_U8, WEB_CAMERA_ATTR_T> m_mapSns2CameraSetting;
    // sensor id : <preview index : video attribute>
    std::map<AX_U8, std::map<AX_U8, WEB_VIDEO_ATTR_T>> m_mapSns2VideoAttr;
    std::map<AX_U8, AI_ATTR_T> m_mapSns2AiAttr;
    std::map<std::string, AX_U8> m_mapCapabilities;
    std::map<AX_U8, std::map<AX_U8, std::vector<std::string>>> m_mapSnsType2ResOptions;
    std::map<AX_U8, std::map<AX_U8, STATISTICS_INFO_T>> m_mapSns2ChnStatInfo;
    std::mutex m_mtxChnStat;
    std::map<AX_U8, OSD_SENSOR_CONFIG_T> m_mapSns2OsdConfig;
    std::map<AX_U8, WEB_AUDIO_ATTR_T> m_mapSns2AudioAttr;

    /*pair[sensorID, videoIndex] = pair[ivpsGrp, ivpsChn] */
    std::map<std::pair<AX_U8, AX_U8>, std::pair<AX_U8, AX_U8>> m_pairVideo2Ivps;
    AX_U32 m_SrcResolution[2]{0};
};
