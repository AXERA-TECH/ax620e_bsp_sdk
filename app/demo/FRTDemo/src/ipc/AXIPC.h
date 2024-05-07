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

#include <memory>
#include "IPCBuilder.h"

class IPPLConfig;

class CAXIPC : public CIPCBuilder {
public:
    CAXIPC(AX_VOID) = default;
    ~CAXIPC(AX_VOID) = default;

    AX_BOOL Init(AX_VOID) override;
    AX_BOOL Deinit(AX_VOID) override;

private:
    std::unique_ptr<IPPLConfig> m_spConfigInst;
};
