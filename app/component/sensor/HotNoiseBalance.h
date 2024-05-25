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
#include "AXThread.hpp"

// sensor hot noise balance status
typedef enum {
    HNB_STATUS_NORMAL_E,
    HNB_STATUS_BALANCE_E,
    HNB_STATUS_BUTT
} HNB_STATUS_E;

typedef struct _HOT_NOISE_BALANCE_STATUS_T {
    AX_BOOL bMonitorStart;
    AX_BOOL bUpdateTrigger;
    HNB_STATUS_E eStatus;

    _HOT_NOISE_BALANCE_STATUS_T() {
        bMonitorStart = AX_FALSE;
        bUpdateTrigger = AX_FALSE;
        eStatus = HNB_STATUS_NORMAL_E;
    }
} HOT_NOISE_BALANCE_STATUS_T;

class CHotNoiseBalance {
public:
    CHotNoiseBalance(CBaseSensor *Sensor);
    virtual ~CHotNoiseBalance(AX_VOID) = default;

    AX_BOOL Start(const SENSOR_HOTNOISEBALANCE_T& tAttr);
    AX_BOOL Stop(AX_VOID);

    AX_BOOL Update(const SENSOR_HOTNOISEBALANCE_T& tAttr);

private:
    AX_BOOL StartMonitor();
    AX_S32 Monitor(AX_VOID* pArg);
    AX_BOOL Process(AX_F32 fThermal);

private:
    CBaseSensor* m_pSensorInst{nullptr};
    SENSOR_HOTNOISEBALANCE_T m_tAttr;
    HOT_NOISE_BALANCE_STATUS_T m_tStatus;
    AX_U8 m_nSnsId{0};
    CAXThread m_HnbThread;
    std::mutex m_mtx;
    std::condition_variable m_cv;
};
