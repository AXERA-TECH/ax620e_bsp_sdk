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

#include <string>
#include "AXSingleton.h"
#include "AudioCfgParser.h"
#include "AudioWrapper.hpp"

#define APP_AUDIO_ATTR() CAudioOptionHelper::GetInstance()->GetAudioAttr()
#define APP_AUDIO_AVAILABLE() CAudioOptionHelper::GetInstance()->GetAudioAvailable()
#define APP_AUDIO_CAP_AVAILABLE() CAudioOptionHelper::GetInstance()->GetAudioCapAvailable()
#define APP_AUDIO_PLAY_AVAILABLE() CAudioOptionHelper::GetInstance()->GetAudioPlayAvailable()
#define APP_AUDIO_RTSP_CHANNEL() CAudioOptionHelper::GetInstance()->GetAudioRtspStreamingChannel()
#define APP_AUDIO_WEB_STREAM_CHANNEL() CAudioOptionHelper::GetInstance()->GetAudioWebStreamingChannel()
#define APP_AUDIO_MP4_CHANNEL() CAudioOptionHelper::GetInstance()->GetMp4RecordingChannel()
#define APP_AUDIO_WEB_TALK_CHANNEL() CAudioOptionHelper::GetInstance()->GetWebTalkingChannel()
#define APP_AUDIO_LOCAL_PLAY_CHANNEL() CAudioOptionHelper::GetInstance()->GetLocalPlayingChannel()
#define APP_AUDIO_WELCOME_CONFIG() CAudioOptionHelper::GetInstance()->GetWelcomeConfig()
#define APP_AUDIO_CFG() CAudioOptionHelper::GetInstance()->GetAudioCfg()

#define SET_APP_AUDIO_ATTR(_Attr_) CAudioOptionHelper::GetInstance()->SetAudioAttr(_Attr_)
#define SET_APP_AUDIO_CFG(_Cfg_) CAudioOptionHelper::GetInstance()->SetAudioCfg(_Cfg_)

/**
 * Load configuration
 */
class CAudioOptionHelper final : public CAXSingleton<CAudioOptionHelper> {
    friend class CAXSingleton<CAudioOptionHelper>;

public:
    const AX_APP_AUDIO_ATTR_T& GetAudioAttr();
    AX_BOOL GetAudioAvailable();
    AX_BOOL GetAudioCapAvailable();
    AX_BOOL GetAudioPlayAvailable();
    AX_APP_AUDIO_CHAN_E GetAudioRtspStreamingChannel();
    AX_APP_AUDIO_CHAN_E GetAudioWebStreamingChannel();
    AX_APP_AUDIO_CHAN_E GetMp4RecordingChannel();
    AX_APP_AUDIO_CHAN_E GetWebTalkingChannel();
    AX_APP_AUDIO_CHAN_E GetLocalPlayingChannel();
    const AX_APP_AUDIO_WELCOME_CFG_T& GetWelcomeConfig();
    const AX_APP_AUDIO_CFG_T& GetAudioCfg();

    AX_VOID SetAudioAttr(const AX_APP_AUDIO_ATTR_T& stAttr);
    AX_VOID SetAudioCfg(const AX_APP_AUDIO_CFG_T& stAttr);

private:
    CAudioOptionHelper(AX_VOID) = default;
    ~CAudioOptionHelper(AX_VOID) = default;

    AX_BOOL InitOnce() override;

private:
    AX_APP_AUDIO_ATTR_T m_stAudioAttr;
    AX_APP_AUDIO_CFG_T m_stAudioCfg;
};
