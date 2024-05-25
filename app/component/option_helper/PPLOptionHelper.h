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

#define APP_PPL_MOD_RELATIONS(vecModRelations) CPPLOptionHelper::GetInstance()->GetModRelations(vecModRelations)

#define SET_APP_PPL_MOD_RELATIONS(vecModRelations) CPPLOptionHelper::GetInstance()->SetModRelations(vecModRelations)

/**
 * Load configuration
 */
class CPPLOptionHelper final : public CAXSingleton<CPPLOptionHelper> {
    friend class CAXSingleton<CPPLOptionHelper>;

public:
    AX_BOOL GetModRelations(std::vector<IPC_MOD_RELATIONSHIP_T>& vecModRelations);
    AX_BOOL SetModRelations(const std::vector<IPC_MOD_RELATIONSHIP_T>& vecModRelations);

private:
    CPPLOptionHelper(AX_VOID) = default;
    ~CPPLOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    std::vector<IPC_MOD_RELATIONSHIP_T> m_vecModRelations;
};
