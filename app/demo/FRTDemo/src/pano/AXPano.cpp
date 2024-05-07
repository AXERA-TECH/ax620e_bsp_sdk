/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "AXPano.h"
#include "PanoConfig.h"

AX_BOOL CAXPano::Init(AX_VOID) {
    m_spConfigInst = std::make_unique<CPanoConfig>();
    BindPPLConfig(m_spConfigInst.get());
    return AX_TRUE;
}

AX_BOOL CAXPano::Deinit(AX_VOID) {
    m_spConfigInst.reset();
    return AX_TRUE;
}
