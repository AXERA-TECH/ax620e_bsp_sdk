/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "IvpsOptionHelper.h"
#include "CommonUtils.hpp"
#include "IvpsCfgParser.h"

AX_BOOL CIvpsOptionHelper::InitOnce() {
    return CIvpsCfgParser::GetInstance()->GetConfig(m_mapGrpSetting);
}

AX_BOOL CIvpsOptionHelper::GetIvpsConfig(AX_U32 nGroup, IVPS_GROUP_CFG_T &tOutConfig) {
    auto it = m_mapGrpSetting.find(nGroup);
    if (m_mapGrpSetting.end() == it) {
        return AX_FALSE;
    }

    tOutConfig = it->second;

    return AX_TRUE;
}

AX_BOOL CIvpsOptionHelper::SetIvpsConfig(AX_U32 nGroup, const IVPS_GROUP_CFG_T &tOutConfig) {
    m_mapGrpSetting[nGroup] = tOutConfig;

    return AX_TRUE;
}
