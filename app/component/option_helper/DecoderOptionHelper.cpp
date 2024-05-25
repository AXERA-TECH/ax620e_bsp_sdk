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

#include "DecoderOptionHelper.h"
#include "CommonUtils.hpp"
#include "DecoderCfgParser.h"

#define ENC_OPTION_HELPER "ENC_HELPER"

AX_BOOL CDecoderOptionHelper::InitOnce() {
    return CDecoderCfgParser::GetInstance()->GetConfig(m_mapVdecChnConfig);
}

AX_BOOL CDecoderOptionHelper::GetVdecConfig(AX_U32 nIndex, VDEC_GRP_CONFIG_T &tOutConfig) {
    auto it = m_mapVdecChnConfig.find(nIndex);
    if (m_mapVdecChnConfig.end() == it) {
        return AX_FALSE;
    }

    tOutConfig = it->second;

    return AX_TRUE;
}

AX_BOOL CDecoderOptionHelper::SetVdecConfig(AX_U32 nIndex, const VDEC_GRP_CONFIG_T &tOutConfig) {
    m_mapVdecChnConfig[nIndex] = tOutConfig;

    return AX_TRUE;
}

AX_BOOL CDecoderOptionHelper::IsDecoderEnable() {
    return m_mapVdecChnConfig.size() > 0 ? AX_TRUE : AX_FALSE;
}

#endif