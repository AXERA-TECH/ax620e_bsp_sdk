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
#include "picojson.h"

class CPPLCfgParser : public CAXSingleton<CPPLCfgParser> {
    friend class CAXSingleton<CPPLCfgParser>;

public:
    AX_BOOL GetConfig(std::vector<IPC_MOD_RELATIONSHIP_T>& vencRelations);

private:
    CPPLCfgParser(AX_VOID) = default;
    ~CPPLCfgParser(AX_VOID) = default;

    AX_BOOL InitOnce() override;

    AX_BOOL ParseFile(const std::string& strPath, std::vector<IPC_MOD_RELATIONSHIP_T>& vencRelations);
    AX_BOOL ParseJson(picojson::object& objJsonRoot, std::vector<IPC_MOD_RELATIONSHIP_T>& vencRelations);
    PPL_MODULE_TYPE_E Str2Module(std::string strModule);
};
