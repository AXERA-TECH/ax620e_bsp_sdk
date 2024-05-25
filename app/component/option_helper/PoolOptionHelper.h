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
#include <string>
#include "AXSingleton.h"

#define APP_POOL_KEYS(mapKeys) CPoolOptionHelper::GetInstance()->GetPoolKeys(mapKeys)

#define SET_APP_POOL_KEYS(mapKeys) CPoolOptionHelper::GetInstance()->SetPoolKeys(mapKeys)

/**
 * Load configuration
 */
class CPoolOptionHelper final : public CAXSingleton<CPoolOptionHelper> {
    friend class CAXSingleton<CPoolOptionHelper>;

public:
    AX_BOOL GetPoolKeys(std::map<std::string, std::string>& mapKeys);
    AX_BOOL SetPoolKeys(const std::map<std::string, std::string>& mapKeys);

private:
    CPoolOptionHelper(AX_VOID) = default;
    ~CPoolOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    std::map<std::string, std::string> m_mapPoolKeys;
};
