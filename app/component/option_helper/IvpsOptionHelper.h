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
#include "IVPSGrpStage.h"

#define APP_IVPS_CONFIG(nGroup, tOutConfig) CIvpsOptionHelper::GetInstance()->GetIvpsConfig(nGroup, tOutConfig)

#define SET_APP_IVPS_CONFIG(nGroup, tOutConfig) CIvpsOptionHelper::GetInstance()->SetIvpsConfig(nGroup, tOutConfig)

/**
 * Load configuration
 */
class CIvpsOptionHelper final : public CAXSingleton<CIvpsOptionHelper> {
    friend class CAXSingleton<CIvpsOptionHelper>;

public:
    AX_BOOL GetIvpsConfig(AX_U32 nGroup, IVPS_GROUP_CFG_T& tOutConfig);
    AX_BOOL SetIvpsConfig(AX_U32 nGroup, const IVPS_GROUP_CFG_T& tOutConfig);

private:
    CIvpsOptionHelper(AX_VOID) = default;
    ~CIvpsOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    std::map<AX_U8, IVPS_GROUP_CFG_T> m_mapGrpSetting;
};
