/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#pragma once

#include <map>
#include <vector>
#include <mutex>
#include <string>
#include <thread>
#include "GlobalDef.h"
#include "AXAlgo.hpp"
#include "IModule.h"
#include "IspAlgoWrapper.hpp"
#include "AXAlgo.hpp"

typedef struct axSNS_LIB_INFO_T {
    std::string strLibName;
    std::string strObjName;
} SNS_LIB_INFO_T;

typedef struct _APP_ISP_IMAGE_ATTR_T {
    AX_U8 nAutoMode{0}; /*1:Auto; 0:Manual*/
    AX_U8 nSharpness{0};
    AX_U8 nBrightness{0};
    AX_U8 nContrast{0};
    AX_U8 nSaturation{0};
} APP_ISP_IMAGE_ATTR_T;

typedef AX_BOOL (*SensorAttrUpdCallback)(ISensor* pInstance);

class CSoftPhotoSensitivity;
class CHotNoiseBalance;
class CIspAlgoAeRoi;

using namespace std;
class CBaseSensor : public ISensor {
public:
    CBaseSensor(SENSOR_CONFIG_T tSensorConfig);
    virtual ~CBaseSensor(AX_VOID) = default;

public:
    virtual AX_BOOL Init(AX_VOID);
    virtual AX_BOOL DeInit(AX_VOID);

    virtual AX_BOOL Open() override;
    virtual AX_BOOL Close() override;

    AX_BOOL OpenAll();
    AX_BOOL CloseAll();

    virtual AX_VOID RegisterIspAlgo(const ISP_ALGO_INFO_T& tAlg) override;

    virtual AX_IMG_FORMAT_E GetMaxImgFmt();
    virtual AX_SNS_HDR_MODE_E GetMaxHdrMode();

    const AX_SNS_ATTR_T& GetSnsAttr(AX_VOID) const override;
    AX_VOID SetSnsAttr(const AX_SNS_ATTR_T& tSnsAttr) override;

    const SNS_CLK_ATTR_T& GetSnsClkAttr(AX_VOID) const override;
    AX_VOID SetSnsClkAttr(const SNS_CLK_ATTR_T& tClkAttr);

    const AX_VIN_DEV_ATTR_T& GetDevAttr(AX_VOID) const override;
    AX_VOID SetDevAttr(const AX_VIN_DEV_ATTR_T& tDevAttr) override;

    const AX_MIPI_RX_DEV_T& GetMipiRxAttr(AX_VOID) const override;
    AX_VOID SetMipiRxAttr(const AX_MIPI_RX_DEV_T& tMipiRxAttr) override;

    const AX_VIN_PIPE_ATTR_T& GetPipeAttr(AX_U8 nPipe) const override;
    AX_VOID SetPipeAttr(AX_U8 nPipe, const AX_VIN_PIPE_ATTR_T& tPipeAttr) override;

    const AX_VIN_CHN_ATTR_T& GetChnAttr(AX_U8 nPipe, AX_U8 nChannel) const override;
    AX_VOID SetChnAttr(AX_U8 nPipe, AX_U8 nChannel, const AX_VIN_CHN_ATTR_T& tChnAttr) override;

    const SNS_ABILITY_T& GetAbilities(AX_VOID) const override;

    const SENSOR_CONFIG_T& GetSnsConfig(AX_VOID) const;

    AX_U32 GetPipeCount();
    AX_VOID RegAttrUpdCallback(SensorAttrUpdCallback callback);

    AX_VOID InitSensor(AX_U8 nPipe);
    AX_VOID ExitSensor(AX_U8 nPipe);

    AX_BOOL RestoreIspImageAttr(APP_ISP_IMAGE_ATTR_T& tAttr);
    AX_BOOL GetIspImageAttr(APP_ISP_IMAGE_ATTR_T& tAttr);
    AX_BOOL SetIspImageAttr(const APP_ISP_IMAGE_ATTR_T& tAttr);
    AX_BOOL ChangeDaynightMode(AX_DAYNIGHT_MODE_E eDaynightMode);
    AX_VOID ChangeHdrMode(AX_U32 nSnsMode);
    AX_BOOL ChangeSnsMirrorFlip(AX_BOOL bMirror, AX_BOOL bFlip);
    AX_BOOL SetAeRoiAttr(AX_BOOL bEnable);
    AX_BOOL SetAeRoi(const std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem);
    AX_VOID UpdateAeRoi(const SENSOR_AE_ROI_ATTR_T& tAttr);
    AX_VOID UpdateAeRoi(const std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem);
    AX_BOOL UpdateLDC(AX_BOOL bLdcEnable, AX_BOOL bAspect, AX_S16 nXRatio, AX_S16 nYRatio, AX_S16 nXYRatio, AX_S16 nDistorRatio);
    AX_BOOL UpdateDIS(AX_BOOL bDisEnable);
    AX_BOOL UpdateSnsFps(AX_S32 nFps);
    AX_BOOL GetAeStatus(AX_ISP_IQ_AE_STATUS_T& tAeStatus);
    AX_BOOL GetDayNightStatus(AX_DAYNIGHT_MODE_E& eDayNightStatus);
    AX_BOOL SetIrAttr(const SENSOR_IRCUT_ATTR_T& tIrAttr);
    AX_VOID UpdateSps(const SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T& tAttr);
    CSoftPhotoSensitivity* GetSpsInst() { return m_pSps; };
    AX_VOID UpdateHnb(const SENSOR_HOTNOISEBALANCE_T& tAttr);
    AX_BOOL UpdateRotation(AX_VIN_ROTATION_E eRotation);
    AX_BOOL EnableChn(AX_BOOL bEnable);
    AX_BOOL EZoom(AX_S32 nEZoomRatio, AX_S32 nCenterOffsetX=0, AX_S32 nCenterOffsetY=0);
    AX_BOOL UpdateSceneMode();
    AX_BOOL LoadBinParams(const std::string &strBinName);
    AX_BOOL GetSnsTemperature(AX_F32 &fTemperature);
    AX_VOID GetResolution(AX_U32 &nWidth, AX_U32 &nHeight);

    AX_BOOL SetMultiSnsSync(AX_BOOL bSync);
    AX_BOOL IsSnsSync();

protected:
    virtual AX_VOID InitSnsLibraryInfo(AX_VOID) = 0;
    virtual AX_VOID InitSnsAttr() = 0;
    virtual AX_VOID InitSnsClkAttr() = 0;
    virtual AX_VOID InitDevAttr() = 0;
    virtual AX_VOID InitPipeAttr() = 0;
    virtual AX_VOID InitMipiRxAttr() = 0;
    virtual AX_VOID InitChnAttr() = 0;
    virtual AX_VOID InitAbilities() = 0;

protected:
    virtual AX_BOOL RegisterSensor(AX_U8 nPipe, AX_U8 nBusType, AX_U8 nDevNode, AX_U8 nI2cAddr);
    virtual AX_BOOL UnRegisterSensor(AX_U8 nPipe);
    virtual AX_BOOL ResetSensorObj(AX_U8 nPipe, AX_U8 nRestGpio);

private:
    AX_BOOL InitISP();
    SNS_SHUTTER_MODE_E GetShutterMode();
    AX_BOOL SetShutterMode(SNS_SHUTTER_MODE_E eShutterMode);
    AX_BOOL SetSnsAttr(AX_U8 nPipeId, const AX_SNS_ATTR_T &tSnsAttr);
    AX_BOOL UpdateSnsAttr();
    AX_BOOL RestoreSnsAttr();
    AX_S32 CalcValueToIspIQ(AX_F32 fVal, AX_S32 nLow, AX_S32 nMedium, AX_S32 nHigh);
    AX_F32 CalcIspIQToValue(AX_S32 nIQ, AX_S32 nLow, AX_S32 nMedium, AX_S32 nHigh);

protected:
    SENSOR_CONFIG_T m_tSnsCfg;
    SENSOR_RESOLUTION_T m_tSnsResolution;
    AX_VOID* m_pSnsLib{nullptr};
    AX_SENSOR_REGISTER_FUNC_T* m_pSnsObj{nullptr};
    SNS_LIB_INFO_T m_tSnsLibInfo;

    AX_SNS_ATTR_T m_tSnsAttr;
    SNS_CLK_ATTR_T m_tSnsClkAttr;
    AX_VIN_DEV_ATTR_T m_tDevAttr;
    std::map<AX_U8, AX_VIN_PIPE_ATTR_T> m_mapPipe2Attr;
    AX_MIPI_RX_DEV_T m_tMipiRxDev;
    std::map<AX_U8, std::map<AX_U8, AX_VIN_CHN_ATTR_T>> m_mapPipe2ChnAttr;
    SNS_ABILITY_T m_tAbilities;

    AX_IMG_FORMAT_E m_eImgFormatSDR;
    AX_IMG_FORMAT_E m_eImgFormatHDR;

    CIspAlgoWrapper m_algWrapper;

    SensorAttrUpdCallback m_cbAttrUpd{nullptr};

    SENSOR_PIPE_MAPPING_T m_arrPipeMapping[MAX_PIPE_PER_DEVICE];
    APP_ISP_IMAGE_ATTR_T m_tImageAttr;

    AX_BOOL m_bSensorStarted{AX_FALSE};

    AX_BOOL m_bAeRoiManual{AX_FALSE};

    std::mutex m_mtx;

    CSoftPhotoSensitivity *m_pSps{nullptr};
    CHotNoiseBalance *m_pHnb{nullptr};
    CIspAlgoAeRoi *m_pAeRoi{nullptr};
};
