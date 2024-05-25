/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "PoolOptionHelper.h"
#include "PoolCfgParser.h"

AX_BOOL CPoolOptionHelper::InitOnce() {
    return CPoolCfgParser::GetInstance()->GetConfig(m_mapPoolKeys);
}

AX_BOOL CPoolOptionHelper::GetPoolKeys(std::map<std::string, std::string>& mapKeys) {
    mapKeys = m_mapPoolKeys;

    return (m_mapPoolKeys.size() > 0) ? AX_TRUE : AX_FALSE;
}

AX_BOOL CPoolOptionHelper::SetPoolKeys(const std::map<std::string, std::string>& mapKeys) {
    m_mapPoolKeys = mapKeys;

    return (m_mapPoolKeys.size() > 0) ? AX_TRUE : AX_FALSE;
}
