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
#include <vector>
#include "condition_variable.hpp"
#include "ax_global_type.h"
#include "GlobalDef.h"
#include "BaseSensor.h"
#include "SensorMgr.h"
#include "AXThread.hpp"
#include "AXAlgo.hpp"

typedef struct _ISP_ALGO_AE_ROI_STATUS_T {
    AX_BOOL bMonitorStart;
    AX_BOOL bUpdateTrigger;

    _ISP_ALGO_AE_ROI_STATUS_T() {
        bMonitorStart = AX_FALSE;
        bUpdateTrigger = AX_FALSE;
    }
} ISP_ALGO_AE_ROI_STATUS_T;

class CIspAlgoAeRoi {
public:
    CIspAlgoAeRoi(CBaseSensor *Sensor);
    virtual ~CIspAlgoAeRoi(AX_VOID) = default;

    AX_BOOL Start(const SENSOR_AE_ROI_ATTR_T& tAttr);
    AX_BOOL Stop(AX_VOID);

    AX_BOOL Update(const SENSOR_AE_ROI_ATTR_T& tAttr);
    AX_BOOL UpdateAeRoi(const std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem);

private:
    AX_BOOL StartMonitor();
    AX_S32 Monitor(AX_VOID* pArg);

private:
    CBaseSensor* m_pSensorInst{nullptr};
    ISP_ALGO_AE_ROI_STATUS_T m_tStatus;
    SENSOR_AE_ROI_ATTR_T m_tAttr;
    std::vector<AX_APP_ALGO_AE_ROI_ITEM_T> m_stVecItem;
    AX_U8 m_nSnsId{0};
    CAXThread m_Thread;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};
