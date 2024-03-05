/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#pragma once
#include <string.h>
#include <string>
#include <vector>
#include "ax_isp_api.h"
#include "ax_mipi_rx_api.h"
#include "ax_vin_api.h"
#include "ax_isp_3a_plus.h"

#define MAX_PIPE_PER_DEVICE (3)

using std::string;
using std::vector;

typedef enum {
    /* New sensors should be append to the last */
    E_SNS_TYPE_OS04A10 = 0,
    E_SNS_TYPE_SC450AI = 1,
    E_SNS_TYPE_IMX678 = 2,
    E_SNS_TYPE_SC200AI = 3,
    E_SNS_TYPE_SC500AI = 4,
    E_SNS_TYPE_SC850SL = 5,
    E_SNS_TYPE_C4395 = 6,
    E_SNS_TYPE_GC4653 = 7,
    E_SNS_TYPE_MIS2032 = 8,
    /* HDR Split Mode: Long Frame */
    E_SNS_TYPE_LF_START = 100,
    E_SNS_TYPE_OS04A10_LF = 101,
    E_SNS_TYPE_SC450AI_LF = 102,
    E_SNS_TYPE_IMX678_LF = 103,
    E_SNS_TYPE_SC200AI_LF = 104,
    E_SNS_TYPE_SC500AI_LF = 105,
    E_SNS_TYPE_SC850SL_LF = 106,
    E_SNS_TYPE_C4395_LF = 107,
    E_SNS_TYPE_GC4653_LF = 108,
    E_SNS_TYPE_MIS2032_LF = 109,
    E_SNS_TYPE_LF_END = 199,
    /* HDR Split Mode: Short Frame */
    E_SNS_TYPE_SF_START = 200,
    E_SNS_TYPE_OS04A10_SF = 201,
    E_SNS_TYPE_SC450AI_SF = 202,
    E_SNS_TYPE_IMX678_SF = 203,
    E_SNS_TYPE_SC200AI_SF = 204,
    E_SNS_TYPE_SC500AI_SF = 205,
    E_SNS_TYPE_SC850SL_SF = 206,
    E_SNS_TYPE_C4395_SF = 207,
    E_SNS_TYPE_GC4653_SF = 208,
    E_SNS_TYPE_MIS2032_SF = 209,
    E_SNS_TYPE_SF_END = 299,
    E_SNS_TYPE_MAX,
} SNS_TYPE_E;

typedef enum {
    E_DEPURPLE_MODE_NOCHANGE = -1,
    E_DEPURPLE_MODE_OFF,
    E_DEPURPLE_MODE_ON,
} DEPURPLE_MODE_E;

typedef enum {
    E_SNS_TISP_MODE_E = 0,
    E_SNS_AIISP_DEFAULT_SCENE_MODE_E = 1,
    E_SNS_AIISP_MANUAL_SCENE_AIISP_MODE_E = 2,
    E_SNS_AIISP_MANUAL_SCENE_TISP_MODE_E = 3,
    E_SNS_AIISP_AUTO_SCENE_MODE_E = 4,
    E_SNS_AIISP_BUTT_MODE_E,
} SNS_AIISP_MODE_E;

typedef enum {
    E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E = 0,
    E_SNS_SHUTTER_SLOW_SHUTTER_MODE_E = 1,
    E_SNS_SHUTTER_BUTT_MODE_E,
} SNS_SHUTTER_MODE_E;

// sensor soft photosensitivity status
typedef enum _SNS_SOFT_PHOTOSENSITIVITY_STATUS_E {
    SNS_SOFT_PHOTOSENSITIVITY_STATUS_DAY,
    SNS_SOFT_PHOTOSENSITIVITY_STATUS_NIGHT,
    SNS_SOFT_PHOTOSENSITIVITY_STATUS_UNKOWN,
    SNS_SOFT_PHOTOSENSITIVITY_STATUS_BUTT
} SNS_SOFT_PHOTOSENSITIVITY_STATUS_E;

// sensor soft photosensitivity type
typedef enum {
    SNS_SOFT_PHOTOSENSITIVITY_NONE,
    SNS_SOFT_PHOTOSENSITIVITY_IR,
    SNS_SOFT_PHOTOSENSITIVITY_WARMLIGHT,
    SNS_SOFT_PHOTOSENSITIVITY_TYPE_BUTT
} SNS_SOFT_PHOTOSENSITIVITY_TYPE_E;

typedef struct axSNS_ABILITY_T {
    AX_BOOL bSupportHDR;
    AX_BOOL bSupportHDRSplit;
    AX_F32 fShutterSlowFpsThr;

    axSNS_ABILITY_T(AX_VOID) {
        bSupportHDR = AX_TRUE;
        bSupportHDRSplit = AX_TRUE;
        fShutterSlowFpsThr = -1;
    }
} SNS_ABILITY_T;

typedef struct axSNS_CLK_ATTR_T {
    AX_U8 nSnsClkIdx;
    AX_SNS_CLK_RATE_E eSnsClkRate;

    axSNS_CLK_ATTR_T(AX_VOID) {
        nSnsClkIdx = 0;
        eSnsClkRate = AX_SNS_CLK_24M;
    }
} SNS_CLK_ATTR_T;

typedef struct axISP_ALGO_INFO_T {
    AX_BOOL bActiveAe;
    AX_BOOL bUserAe;
    AX_BOOL bActiveAwb;
    AX_BOOL bUserAwb;
    AX_BOOL bActiveLsc;
    AX_BOOL bUserLsc;
    AX_ISP_AE_REGFUNCS_T tAeFns;
    AX_ISP_AWB_REGFUNCS_T tAwbFns;
    AX_ISP_LSC_REGFUNCS_T tLscFns;

    axISP_ALGO_INFO_T(AX_VOID) {
        memset(this, 0, sizeof(*this));
    }
} ISP_ALGO_INFO_T;

typedef struct _SNS_COLOR_ATTR_T {
    AX_BOOL bColorManual;
    AX_F32 fBrightness;
    AX_F32 fSharpness;
    AX_F32 fContrast;
    AX_F32 fSaturation;

    _SNS_COLOR_ATTR_T() {
        bColorManual = AX_FALSE;
        fBrightness = 0;
        fSharpness = 0;
        fContrast = 0;
        fSaturation = 0;
    }
} SENSOR_COLOR_ATTR_T;

// sensor ldc attribute
typedef struct _SENSOR_LDC_ATTR_T {
    // LDC
    AX_BOOL bLdcEnable;
    AX_BOOL bLdcAspect;
    AX_S16 nLdcXRatio;
    AX_S16 nLdcYRatio;
    AX_S16 nLdcXYRatio;
    AX_S16 nLdcDistortionRatio;

    _SENSOR_LDC_ATTR_T() {
        bLdcEnable = AX_FALSE;
        bLdcAspect = AX_FALSE;
        nLdcXRatio = 0;
        nLdcYRatio = 0;
        nLdcXYRatio = 0;
        nLdcDistortionRatio = 0;
    }
} SENSOR_LDC_ATTR_T;

// sensor DIS attribute
typedef struct _SENSOR_DIS_ATTR_T {
    // DIS
    AX_BOOL bDisEnable;
    AX_BOOL bMotionShare;
    AX_BOOL bMotionEst;
    AX_U8 nDelayFrameNum;
    _SENSOR_DIS_ATTR_T() {
        memset(this, 0, sizeof(*this));
    }
} SENSOR_DIS_ATTR_T;

// sensor ircut attribute
typedef struct _SENSOR_IRCUT_ATTR_T {
    AX_F32 fIrCalibR;
    AX_F32 fIrCalibG;
    AX_F32 fIrCalibB;
    AX_F32 fNight2DayIrStrengthTh;
    AX_F32 fNight2DayIrDetectTh;
    AX_U32 nInitDayNightMode;
    AX_F32 fDay2NightLuxTh;
    AX_F32 fNight2DayLuxTh;
    AX_F32 fNight2DayBrightTh;
    AX_F32 fNight2DayDarkTh;
    AX_F32 fNight2DayUsefullWpRatio;
    AX_U32 nCacheTime;
} SENSOR_IRCUT_ATTR_T;

// sensor warm light attribute
typedef struct _SENSOR_WARMLIGHT_ATTR_T {
    AX_U64 nOnLightSensitivity;
    AX_U64 nOnLightExpValMax;
    AX_U64 nOnLightExpValMid;
    AX_U64 nOnLightExpValMin;
    AX_U64 nOffLightSensitivity;
    AX_U64 nOffLightExpValMax;
    AX_U64 nOffLightExpValMid;
    AX_U64 nOffLightExpValMin;
} SENSOR_WARMLIGHT_ATTR_T;

// sensor soft photo sensitivity
typedef struct _SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T {
    AX_BOOL bAutoCtrl;
    SNS_SOFT_PHOTOSENSITIVITY_TYPE_E eType;

    union {
        SENSOR_IRCUT_ATTR_T tIrAttr;
        SENSOR_WARMLIGHT_ATTR_T tWarmAttr;
    };

    _SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T() {
        bAutoCtrl = AX_FALSE;
        eType = SNS_SOFT_PHOTOSENSITIVITY_NONE;
        memset(&tIrAttr, 0x00, sizeof(tIrAttr));
        memset(&tWarmAttr, 0x00, sizeof(tWarmAttr));
    }
} SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T;

typedef struct _SENSOR_AE_ROI_ATTR_T {
    AX_BOOL bEnable;

    _SENSOR_AE_ROI_ATTR_T() {
        bEnable = AX_FALSE;
    }
} SENSOR_AE_ROI_ATTR_T;

typedef struct _SENSOR_EZOOM_ATTR_T {
    AX_S32 nEZoomRatio;
    AX_S16 nCenterOffsetX;  // offset x from horizental center, not used
    AX_S16 nCenterOffsetY;  // offset y from veritcal center, not used

    _SENSOR_EZOOM_ATTR_T() {
        nEZoomRatio = 0;
        nCenterOffsetX = 0;
        nCenterOffsetX = 0;
    }
} SENSOR_EZOOM_ATTR_T;

typedef struct _SENSOR_HOTNOISEBALANCE_T {
    AX_BOOL bEnable;
    AX_F32 fBalanceThreshold;
    AX_F32 fNormalThreshold;
    string strSdrHotNoiseNormalModeBin;
    string strSdrHotNoiseBalanceModeBin;
    string strHdrHotNoiseNormalModeBin;
    string strHdrHotNoiseBalanceModeBin;

    _SENSOR_HOTNOISEBALANCE_T() {
        bEnable = AX_FALSE;
        fBalanceThreshold = 0;
        fNormalThreshold = 0;
    }
} SENSOR_HOTNOISEBALANCE_T;

typedef struct _SENSOR_PIPE_MAPPING {
    AX_U8 nPipeSeq;
    AX_U8 nPipeID;

    _SENSOR_PIPE_MAPPING() {
        nPipeSeq = 0;
        nPipeID = 0;
    }
} SENSOR_PIPE_MAPPING_T;

typedef struct _CHANNEL_CONFIG_T {
    AX_S32 nWidth;
    AX_S32 nHeight;
    AX_U8 nYuvDepth;
    AX_BOOL bChnEnable;
    AX_F32 fFrameRate;
    AX_FRAME_COMPRESS_INFO_T tChnCompressInfo;

    _CHANNEL_CONFIG_T() {
        nWidth = 0;
        nHeight = 0;
        nYuvDepth = 0;
        fFrameRate = 0;
        bChnEnable = AX_FALSE;
        tChnCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
        tChnCompressInfo.u32CompressLevel = 0;
    }
} CHANNEL_CONFIG_T, *CHANNEL_CONFIG_PTR;

typedef struct _PIPE_CONFIG_T {
    AX_U8 nPipeID;
    AX_F32 fPipeFramerate;
    CHANNEL_CONFIG_T arrChannelAttr[AX_VIN_CHN_ID_MAX];
    SNS_AIISP_MODE_E eAiIspMode;
    AX_FRAME_COMPRESS_INFO_T tIfeCompress[AX_SNS_HDR_MODE_MAX];
    AX_FRAME_COMPRESS_INFO_T tAiNrCompress[AX_SNS_HDR_MODE_MAX];
    AX_FRAME_COMPRESS_INFO_T t3DNrCompress[AX_SNS_HDR_MODE_MAX];
    AX_BOOL bTuning;
    AX_U32 nTuningPort;
    SENSOR_LDC_ATTR_T tLdcAttr;
    SENSOR_DIS_ATTR_T tDisAttr;
    AX_S8 nVinIvpsMode;
    AX_U8 nIvpsGrp;

    vector<string> vecTuningBin{};

    _PIPE_CONFIG_T() {
        nPipeID = 0;
        fPipeFramerate = 30;
        eAiIspMode = E_SNS_AIISP_DEFAULT_SCENE_MODE_E;
        memset(tIfeCompress, 0, sizeof(tIfeCompress));
        memset(tAiNrCompress, 0, sizeof(tAiNrCompress));
        memset(t3DNrCompress, 0, sizeof(t3DNrCompress));
        bTuning = AX_TRUE;
        nTuningPort = 8082;
        nVinIvpsMode = -1;
        nIvpsGrp = 0;
    }
} PIPE_CONFIG_T, *PIPE_CONFIG_PTR;

typedef struct _SENSOR_CONFIG_T {
    AX_U8 nSnsID;
    AX_U8 nDevID;
    AX_BOOL bMirror;
    AX_BOOL bFlip;
    SNS_TYPE_E eSensorType;
    AX_ROTATION_E eRotation;
    AX_SNS_HDR_MODE_E eSensorMode;
    AX_SNS_MASTER_SLAVE_E nMasterSlaveSel;
    AX_DAYNIGHT_MODE_E eDayNight;
    AX_VIN_DEV_MODE_E eDevMode;
    AX_SNS_OUTPUT_MODE_E eSnsOutputMode;
    AX_VIN_IVPS_MODE_E eVinIvpsMode;
    AX_F32 fFrameRate;
    AX_U32 nPipeCount;
    PIPE_CONFIG_T arrPipeAttr[MAX_PIPE_PER_DEVICE];
    SENSOR_COLOR_ATTR_T tColorAttr;
    SENSOR_AE_ROI_ATTR_T tAeRoiAttr;
    SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T tSoftPhotoSensitivityAttr;
    SENSOR_EZOOM_ATTR_T tEZoomAttr;
    SENSOR_HOTNOISEBALANCE_T tHotNoiseBalanceAttr;
    AX_U8 nResetGpioNum;
    AX_U8 nClkId;
    AX_U8 nLaneNum;
    AX_U8 nBusType;
    AX_U8 nDevNode;
    AX_U8 nI2cAddr;
    AX_S8 arrSettingIndex[3];
    SNS_SHUTTER_MODE_E eShutterMode;

    _SENSOR_CONFIG_T() {
        nSnsID = 0;
        nDevID = 0;
        bMirror = AX_FALSE;
        bFlip = AX_FALSE;
        eRotation = AX_ROTATION_0;
        fFrameRate = 30;
        eDevMode = AX_VIN_DEV_OFFLINE;
        eSnsOutputMode = AX_SNS_NORMAL;
        eSensorType = E_SNS_TYPE_MAX;
        eSensorMode = AX_SNS_LINEAR_MODE;
        eDayNight = AX_DAYNIGHT_MODE_DAY;
        nMasterSlaveSel = AX_SNS_MASTER;
        nPipeCount = 0;
        nResetGpioNum = 0;
        nClkId = 0;
        nLaneNum = 0;
        nBusType = 0; // i2c
        nI2cAddr = -1;
        nI2cAddr = 0;
        eVinIvpsMode = AX_GDC_ONLINE_VPP;
        eShutterMode = E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E;
    }
} SENSOR_CONFIG_T, *SENSOR_CONFIG_PTR;

typedef struct _SENSOR_RESOLUTION_T {
    AX_U32 nSnsAttrWidth;
    AX_U32 nSnsAttrHeight;
    AX_U32 nSnsOutWidth;
    AX_U32 nSnsOutHeight;

    _SENSOR_RESOLUTION_T() {
        nSnsAttrWidth = 0;
        nSnsAttrHeight = 0;
        nSnsOutWidth = 0;
        nSnsOutHeight = 0;
    }
} SENSOR_RESOLUTION_T, *SENSOR_RESOLUTION_PTR;

class ISensor {
public:
    virtual ~ISensor(AX_VOID) = default;

    /*
        @brief: initialize and lanuch ISP pipe line
    */
    virtual AX_BOOL Open(AX_VOID) = 0;
    virtual AX_BOOL Close(AX_VOID) = 0;

    /*
        @brief: ISP algorithm including AE, AF, AWB, LSC ...
                by default, AE and AWB is actived with Axera algorithm.
    */
    virtual AX_VOID RegisterIspAlgo(const ISP_ALGO_INFO_T& tAlg) = 0;

    /*
        @brief: sensor and ISP properties set and get
                NOTE: property should be set before Start()
     */
    virtual const AX_SNS_ATTR_T& GetSnsAttr(AX_VOID) const = 0;
    virtual AX_VOID SetSnsAttr(const AX_SNS_ATTR_T& tSnsAttr) = 0;

    virtual const SNS_CLK_ATTR_T& GetSnsClkAttr(AX_VOID) const = 0;
    virtual AX_VOID SetSnsClkAttr(const SNS_CLK_ATTR_T& tClkAttr) = 0;

    virtual const AX_VIN_DEV_ATTR_T& GetDevAttr(AX_VOID) const = 0;
    virtual AX_VOID SetDevAttr(const AX_VIN_DEV_ATTR_T& tDevAttr) = 0;

    virtual const AX_MIPI_RX_DEV_T& GetMipiRxAttr(AX_VOID) const = 0;
    virtual AX_VOID SetMipiRxAttr(const AX_MIPI_RX_DEV_T& tMipiRxAttr) = 0;

    virtual const AX_VIN_PIPE_ATTR_T& GetPipeAttr(AX_U8 nPipe) const = 0;
    virtual AX_VOID SetPipeAttr(AX_U8 nPipe, const AX_VIN_PIPE_ATTR_T& tPipeAttr) = 0;

    virtual const AX_VIN_CHN_ATTR_T& GetChnAttr(AX_U8 nPipe, AX_U8 nChannel) const = 0;
    virtual AX_VOID SetChnAttr(AX_U8 nPipe, AX_U8 nChannel, const AX_VIN_CHN_ATTR_T& tChnAttr) = 0;

    virtual const SNS_ABILITY_T& GetAbilities(AX_VOID) const = 0;
};
