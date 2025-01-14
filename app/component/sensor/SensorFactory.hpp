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
#include "AXSingleton.h"
#include "ISensor.hpp"

class CSensorFactory : public CAXSingleton<CSensorFactory> {
    friend class CAXSingleton<CSensorFactory>;

public:
    ISensor *CreateSensor(const SENSOR_CONFIG_T &tSensorCfg);
    AX_VOID DestorySensor(ISensor *&pSensor);

public:
    CSensorFactory(AX_VOID) noexcept = default;
    virtual ~CSensorFactory(AX_VOID) = default;
};