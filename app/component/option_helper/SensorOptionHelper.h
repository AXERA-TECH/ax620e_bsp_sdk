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

#include <map>
#include "AXSingleton.h"
#include "IPPLBuilder.h"
#include "ISensor.hpp"

#define APP_SENSOR_CONFIG(nSnsIndex, tOutConfig) CSensorOptionHelper::GetInstance()->GetSensorConfig(nSnsIndex, tOutConfig)
#define APP_SENSOR_COUNT() CSensorOptionHelper::GetInstance()->GetSensorCount()
#define SET_APP_SENSOR_CONFIG(nSnsIndex, tOutConfig) CSensorOptionHelper::GetInstance()->SetSensorConfig(nSnsIndex, tOutConfig)
#define SET_APP_SENSOR_COUNT(_Count_) CSensorOptionHelper::GetInstance()->SetSensorCount(_Count_)

/**
 * Load configuration
 */

typedef struct _SENSOR_VINIVPS_CFG_T {
    AX_U8 nIvpsGrp{0};
    AX_S8 nVinIvpsMode{-1};
} SENSOR_VINIVPS_CFG_T;

class CSensorOptionHelper final : public CAXSingleton<CSensorOptionHelper> {
    friend class CAXSingleton<CSensorOptionHelper>;

public:
    AX_BOOL GetSensorConfig(AX_U8 nSnsIndex, SENSOR_CONFIG_T& tOutSensorCfg);

    AX_U32 GetSensorCount() {
        return m_nSensorCount;
    };

    AX_BOOL SetSensorConfig(AX_U8 nSnsIndex, const SENSOR_CONFIG_T& tOutSensorCfg);
    AX_VOID SetSensorCount(AX_U32 nCount);
    std::map<AX_U8, SENSOR_VINIVPS_CFG_T> GetMapVinIvps(AX_VOID);

private:
    CSensorOptionHelper(AX_VOID) = default;
    ~CSensorOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    AX_U32 m_nSensorCount{0};

    std::map<AX_U8, SENSOR_CONFIG_T> m_mapSensorCfg;
};
