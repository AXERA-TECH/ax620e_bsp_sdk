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
#pragma once

#include <map>
#include "AXSingleton.h"
#include "VideoDecoder.h"

#define APP_VDEC_CONFIG(nIndex, tOutConfig) CDecoderOptionHelper::GetInstance()->GetVdecConfig(nIndex, tOutConfig)
#define IS_APP_DECODER_ENABLE() CDecoderOptionHelper::GetInstance()->IsDecoderEnable()
#define SET_APP_VDEC_CONFIG(nIndex, tOutConfig) CDecoderOptionHelper::GetInstance()->SetVdecConfig(nIndex, tOutConfig)

/**
 * Load configuration
 */
class CDecoderOptionHelper final : public CAXSingleton<CDecoderOptionHelper> {
    friend class CAXSingleton<CDecoderOptionHelper>;

public:
    AX_BOOL GetVdecConfig(AX_U32 nIndex, VDEC_GRP_CONFIG_T& tOutConfig);
    AX_BOOL SetVdecConfig(AX_U32 nIndex, const VDEC_GRP_CONFIG_T& tOutConfig);

    AX_BOOL IsDecoderEnable();

private:
    CDecoderOptionHelper(AX_VOID) = default;
    ~CDecoderOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    std::map<AX_U8, VDEC_GRP_CONFIG_T> m_mapVdecChnConfig;
};
#endif