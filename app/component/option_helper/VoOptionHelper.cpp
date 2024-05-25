/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifdef VO_SUPPORT

#include "VoOptionHelper.h"
#include "CommonUtils.hpp"
#include "VoCfgParser.h"

AX_BOOL CVoOptionHelper::InitOnce() {
    return CVOCfgParser::GetInstance()->GetConfig(m_mapVoChnConfig);
}

AX_BOOL CVoOptionHelper::GetVoConfig(AX_U32 nIndex, VO_ATTR_T &tOutConfig) {
    auto it = m_mapVoChnConfig.find(nIndex);
    if (m_mapVoChnConfig.end() == it) {
        return AX_FALSE;
    }

    tOutConfig = it->second;

    return AX_TRUE;
}

AX_BOOL CVoOptionHelper::SetVoConfig(AX_U32 nIndex, const VO_ATTR_T &tOutConfig) {
    m_mapVoChnConfig[nIndex] = tOutConfig;

    return AX_TRUE;
}

AX_BOOL CVoOptionHelper::IsVoEnable() {
    return m_mapVoChnConfig.size() > 0 ? AX_TRUE : AX_FALSE;
}

#endif