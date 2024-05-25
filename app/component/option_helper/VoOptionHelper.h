/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifdef VO_SUPPORT
#pragma once

#include <map>
#include "AXSingleton.h"
#include "Vo.hpp"

#define APP_VO_CONFIG(nIndex, tOutConfig) CVoOptionHelper::GetInstance()->GetVoConfig(nIndex, tOutConfig)
#define IS_APP_VO_ENABLE() CVoOptionHelper::GetInstance()->IsVoEnable()

/**
 * Load configuration
 */
class CVoOptionHelper final : public CAXSingleton<CVoOptionHelper> {
    friend class CAXSingleton<CVoOptionHelper>;

public:
    AX_BOOL GetVoConfig(AX_U32 nIndex, VO_ATTR_T& tOutConfig);
    AX_BOOL SetVoConfig(AX_U32 nIndex, const VO_ATTR_T& tOutConfig);

    AX_BOOL IsVoEnable();

private:
    CVoOptionHelper(AX_VOID) = default;
    ~CVoOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    std::map<AX_U8, VO_ATTR_T> m_mapVoChnConfig;
};
#endif