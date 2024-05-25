/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "EncoderOptionHelper.h"
#include "CommonUtils.hpp"
#include "EncoderCfgParser.h"

#define ENC_OPTION_HELPER "ENC_HELPER"

AX_BOOL CEncoderOptionHelper::InitOnce() {
    return CEncoderCfgParser::GetInstance()->GetConfig(m_mapVencChnConfig, m_mapJencChnConfig);
}

AX_BOOL CEncoderOptionHelper::GetVencConfig(AX_U32 nIndex, VIDEO_CONFIG_T &tOutConfig) {
    auto it = m_mapVencChnConfig.find(nIndex);
    if (m_mapVencChnConfig.end() == it) {
        return AX_FALSE;
    }

    tOutConfig = it->second;

    return AX_TRUE;
}

AX_BOOL CEncoderOptionHelper::GetJencConfig(AX_U32 nIndex, JPEG_CONFIG_T &tOutConfig) {
    auto it = m_mapJencChnConfig.find(nIndex);
    if (m_mapJencChnConfig.end() == it) {
        return AX_FALSE;
    }

    tOutConfig = it->second;

    return AX_TRUE;
}

AX_BOOL CEncoderOptionHelper::SetVencConfig(AX_U32 nIndex, const VIDEO_CONFIG_T &tOutConfig) {
    m_mapVencChnConfig[nIndex] = tOutConfig;

    return AX_TRUE;
}

AX_BOOL CEncoderOptionHelper::SetJencConfig(AX_U32 nIndex, const JPEG_CONFIG_T &tOutConfig) {
    m_mapJencChnConfig[nIndex] = tOutConfig;

    return AX_TRUE;
}

AX_BOOL CEncoderOptionHelper::IsEncoderEnable() {
    return (m_mapVencChnConfig.size() + m_mapJencChnConfig.size() > 0) ? AX_TRUE : AX_FALSE;
}

AX_BOOL CEncoderOptionHelper::IsVencEnable() {
    return (m_mapVencChnConfig.size() > 0) ? AX_TRUE : AX_FALSE;
}

AX_BOOL CEncoderOptionHelper::IsJencEnable() {
    return (m_mapJencChnConfig.size() > 0) ? AX_TRUE : AX_FALSE;
}
