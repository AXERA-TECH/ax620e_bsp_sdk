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

#include <string>
#include "ax_base_type.h"

typedef struct _PPL_CONFIG_T {
    std::string strAppName;
    std::string strPPLName;

    _PPL_CONFIG_T() {
        strAppName = "FRTDemo";
        strPPLName = "IPC";
    }
} PPL_CONFIG_T;

class IPPLConfig {
public:
    IPPLConfig(AX_VOID) = default;
    virtual ~IPPLConfig(AX_VOID) = default;

    virtual AX_BOOL Init(AX_VOID) = 0;
    virtual AX_BOOL InitPost() {
        return AX_TRUE;
    }
    virtual AX_BOOL GetPPLConfig(PPL_CONFIG_T &tPPLConfig) {
        tPPLConfig = m_tPPLConfig;
        return AX_TRUE;
    };

public:
    PPL_CONFIG_T m_tPPLConfig;
};
