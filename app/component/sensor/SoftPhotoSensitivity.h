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

#include <thread>
#include <mutex>
#include "condition_variable.hpp"
#include "ax_global_type.h"
#include "GlobalDef.h"
#include "BaseSensor.h"
#include "SensorMgr.h"
#include "AXThread.hpp"
#include "IObserver.h"

#define SPS_DFEAULT_ONLIGHT_THRESHOLD 12819426304
#define SPS_DFEAULT_OFFLIGHT_THRESHOLD 456960000

typedef struct _SOFT_PHOTOSENSITIVITY_STATUS_T {
    AX_BOOL bMonitorStart;
    AX_BOOL bUpdateTrigger;
    AX_U64 onTicks;
    AX_U64 offTicks;
    AX_U64 onLightThreshold;
    AX_U64 offLightThreshold;
    AX_U32 curDayNightStatus;

    _SOFT_PHOTOSENSITIVITY_STATUS_T() {
        bMonitorStart = AX_FALSE;
        bUpdateTrigger = AX_FALSE;
        onTicks = 0;
        offTicks = 0;
        onLightThreshold = SPS_DFEAULT_ONLIGHT_THRESHOLD;
        offLightThreshold = SPS_DFEAULT_OFFLIGHT_THRESHOLD;
        curDayNightStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_UNKOWN;
    }
} SOFT_PHOTOSENSITIVITY_STATUS_T;

typedef struct _SOFT_PHOTOSENSITIVITY_RESULT_T {
    SNS_SOFT_PHOTOSENSITIVITY_TYPE_E eType;
    SNS_SOFT_PHOTOSENSITIVITY_STATUS_E eStatus;
    AX_VOID *pUserData;
    AX_VOID *pPrivateData;

    _SOFT_PHOTOSENSITIVITY_RESULT_T() {
        eType = SNS_SOFT_PHOTOSENSITIVITY_NONE;
        eStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_UNKOWN;
        pUserData = nullptr;
        pPrivateData = nullptr;
    }
} SOFT_PHOTOSENSITIVITY_RESULT_T, *SOFT_PHOTOSENSITIVITY_RESULT_PTR;

typedef AX_VOID (*SNS_SOFTPHOTOSENSITIVITY_CALLBACK)(AX_U8 nSnsId, const SOFT_PHOTOSENSITIVITY_RESULT_PTR pstResult);

class CSoftPhotoSensitivity {
public:
    CSoftPhotoSensitivity(CBaseSensor *Sensor);
    virtual ~CSoftPhotoSensitivity(AX_VOID) = default;

    AX_BOOL Start(const SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T& tAttr);
    AX_BOOL Stop(AX_VOID);

    AX_BOOL Update(const SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T& tAttr);

    AX_VOID NotifyAll(AX_U32 nSnsId, AX_U32 nChn, AX_VOID* ptResult);

    AX_VOID RegObserver(IObserver* pObserver);
    AX_VOID UnregObserver(IObserver* pObserver);

private:
    AX_VOID SetWarmLightAttr(const SENSOR_WARMLIGHT_ATTR_T& tWarmAttr);
    AX_VOID WarmLightMonitor(const SENSOR_WARMLIGHT_ATTR_T& tWarmAttr);
    AX_VOID SetIrAttr(const SENSOR_IRCUT_ATTR_T& tIrAttr);
    AX_VOID IrMonitor(const SENSOR_IRCUT_ATTR_T& tIrAttr);
    AX_BOOL StartMonitor();
    AX_S32 Monitor(AX_VOID* pArg);

private:
    std::vector<IObserver*> m_vecObserver;
    CBaseSensor* m_pSensorInst{nullptr};
    SOFT_PHOTOSENSITIVITY_STATUS_T m_tStatus;
    SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T m_tAttr;
    AX_U8 m_nSnsId{0};
    CAXThread m_SpsThread;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};
