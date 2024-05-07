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

#include "IPPLConfig.h"
#include "ax_base_type.h"

class CIPCConfig : public IPPLConfig {
public:
    CIPCConfig(AX_VOID) = default;
    virtual ~CIPCConfig(AX_VOID) = default;

    AX_BOOL Init(AX_VOID);

private:
    AX_BOOL InitOsdConfig(AX_VOID);
    AX_VOID OsdVideoChnIndex2IvpsGrp(AX_VOID);
    std::string GetResPath();
};
