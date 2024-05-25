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

#include "BaseSensor.h"

class CIMX678 : public CBaseSensor {
public:
    CIMX678(SENSOR_CONFIG_T tSensorConfig);
    virtual ~CIMX678(AX_VOID);

public:
    virtual AX_SNS_HDR_MODE_E GetMaxHdrMode();

protected:
    virtual AX_VOID InitSnsLibraryInfo(AX_VOID) override;
    virtual AX_VOID InitSnsAttr() override;
    virtual AX_VOID InitSnsClkAttr() override;
    virtual AX_VOID InitDevAttr() override;
    virtual AX_VOID InitPipeAttr() override;
    virtual AX_VOID InitMipiRxAttr() override;
    virtual AX_VOID InitChnAttr() override;
    virtual AX_VOID InitAbilities() override;
};
