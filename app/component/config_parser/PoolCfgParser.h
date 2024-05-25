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

#include <vector>
#include "AXSingleton.h"
#include "IPPLBuilder.h"
#include "IniWrapper.hpp"

class CPoolCfgParser : public CAXSingleton<CPoolCfgParser> {
    friend class CAXSingleton<CPoolCfgParser>;

public:
    AX_BOOL GetConfig(std::map<std::string, std::string>& mapKeys);

private:
    CPoolCfgParser(AX_VOID) = default;
    ~CPoolCfgParser(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    CIniWrapper m_iniParser;
};
