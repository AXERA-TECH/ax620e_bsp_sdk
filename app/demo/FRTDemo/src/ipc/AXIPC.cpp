/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "AXIPC.h"
#include "IPCConfig.h"

AX_BOOL CAXIPC::Init(AX_VOID) {
    m_spConfigInst = std::make_unique<CIPCConfig>();
    BindPPLConfig(m_spConfigInst.get());

    return AX_TRUE;
}

AX_BOOL CAXIPC::Deinit(AX_VOID) {
    m_spConfigInst.reset();
    return AX_TRUE;
}
