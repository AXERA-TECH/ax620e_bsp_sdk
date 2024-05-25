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
#include "AudioAedDev.hpp"
#include "AudioAedAlgo.hpp"
#include "IObserver.h"
#include "ax_codec_comm.h"

class CAudioAed {
public:
    CAudioAed();
    virtual ~CAudioAed();

    AX_BOOL Init(const AUDIO_AED_DEV_ATTR_PTR pstCapDevAttr, const AED_ALGO_CONFIG_PTR pstAedAlgoConfig);
    AX_BOOL DeInit();

    AX_BOOL Start();
    AX_BOOL Stop();

    AX_BOOL GetDevAttr(AUDIO_AED_DEV_ATTR_T &stAttr);
    AX_BOOL SetDevAttr(const AUDIO_AED_DEV_ATTR_T &stAttr);

    AX_BOOL GetAlgoAttr(AED_ALGO_CONFIG_T &stAttr);
    AX_BOOL SetAlgoAttr(const AED_ALGO_CONFIG_T &stAttr);

    AX_VOID RegObserver(IObserver *pObserver);
    AX_VOID UnregObserver(IObserver *pObserver);

private:
    CAudioAedDev *m_pAedDev{nullptr};
    CAudioAedAlgo *m_pAedAlgo{nullptr};
};
