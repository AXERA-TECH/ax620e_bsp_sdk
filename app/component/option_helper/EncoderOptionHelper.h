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

#include <map>
#include "AXSingleton.h"
#include "JpegEncoder.h"
#include "VideoEncoder.h"

#define APP_VENC_CONFIG(nIndex, tOutConfig) CEncoderOptionHelper::GetInstance()->GetVencConfig(nIndex, tOutConfig)
#define APP_JENC_CONFIG(nIndex, tOutConfig) CEncoderOptionHelper::GetInstance()->GetJencConfig(nIndex, tOutConfig)
#define IS_APP_ENCODER_ENABLE() CEncoderOptionHelper::GetInstance()->IsEncoderEnable()
#define IS_APP_VENC_ENABLE() CEncoderOptionHelper::GetInstance()->IsVencEnable()
#define IS_APP_JENC_ENABLE() CEncoderOptionHelper::GetInstance()->IsJencEnable()

#define SET_APP_VENC_CONFIG(nIndex, tOutConfig) CEncoderOptionHelper::GetInstance()->SetVencConfig(nIndex, tOutConfig)
#define SET_APP_JENC_CONFIG(nIndex, tOutConfig) CEncoderOptionHelper::GetInstance()->SetJencConfig(nIndex, tOutConfig)

/**
 * Load configuration
 */
class CEncoderOptionHelper final : public CAXSingleton<CEncoderOptionHelper> {
    friend class CAXSingleton<CEncoderOptionHelper>;

public:
    AX_BOOL GetVencConfig(AX_U32 nIndex, VIDEO_CONFIG_T& tOutConfig);
    AX_BOOL GetJencConfig(AX_U32 nIndex, JPEG_CONFIG_T& tOutConfig);

    AX_BOOL SetVencConfig(AX_U32 nIndex, const VIDEO_CONFIG_T& tOutConfig);
    AX_BOOL SetJencConfig(AX_U32 nIndex, const JPEG_CONFIG_T& tOutConfig);

    AX_BOOL IsEncoderEnable();
    AX_BOOL IsVencEnable();
    AX_BOOL IsJencEnable();

private:
    CEncoderOptionHelper(AX_VOID) = default;
    ~CEncoderOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    std::map<AX_U8, VIDEO_CONFIG_T> m_mapVencChnConfig;
    std::map<AX_U8, JPEG_CONFIG_T> m_mapJencChnConfig;
};
