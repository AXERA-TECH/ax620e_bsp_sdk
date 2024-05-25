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
#include "picojson.h"

class CVOCfgParser : public CAXSingleton<CVOCfgParser> {
    friend class CAXSingleton<CVOCfgParser>;

public:
    AX_BOOL GetConfig(std::map<AX_U8, VO_ATTR_T> &mapVoChnConfig);

private:
    CVOCfgParser(AX_VOID) = default;
    ~CVOCfgParser(AX_VOID) = default;

    AX_BOOL InitOnce() override;
    AX_BOOL ParseFile(const std::string &strPath, std::map<AX_U8, VO_ATTR_T> &mapVoChnConfig);
    AX_BOOL ParseJson(picojson::object &objJsonRoot, std::map<AX_U8, VO_ATTR_T> &mapVoChnConfig);
};

#endif