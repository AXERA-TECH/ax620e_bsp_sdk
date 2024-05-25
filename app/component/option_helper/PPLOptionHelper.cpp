/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "PPLOptionHelper.h"
#include "CommonUtils.hpp"
#include "PPLCfgParser.h"

AX_BOOL CPPLOptionHelper::InitOnce() {
    return CPPLCfgParser::GetInstance()->GetConfig(m_vecModRelations);
}

AX_BOOL CPPLOptionHelper::GetModRelations(std::vector<IPC_MOD_RELATIONSHIP_T>& vecModRelations) {
    vecModRelations = m_vecModRelations;

    return AX_TRUE;
}

AX_BOOL CPPLOptionHelper::SetModRelations(const std::vector<IPC_MOD_RELATIONSHIP_T>& vecModRelations) {
    m_vecModRelations = vecModRelations;

    return AX_TRUE;
}
