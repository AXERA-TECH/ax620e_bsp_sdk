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

#include "AXStage.hpp"
#include "FramerateCtrlHelper.h"
#include "IObserver.h"

typedef struct stDummyCoderConfig {
    AX_S32 nPipeSrc;
    AX_S32 nChannel;

    stDummyCoderConfig() {
        memset(this, 0, sizeof(stDummyCoderConfig));
    }

} DUMMY_CODE_CONFIG_T, *DUMMY_CODE_CONFIG_PTR;

#define MAX_DUMMY_ENC_CHANNEL_NUM (8)

class CDummyEncoder : public CAXStage {
public:
    CDummyEncoder(DUMMY_CODE_CONFIG_T& tConfig);
    ~CDummyEncoder();

    AX_BOOL Init() override;
    AX_BOOL Start(STAGE_START_PARAM_PTR pStartParams) override;
    AX_BOOL Stop(AX_VOID) override;
    AX_BOOL ProcessFrame(CAXFrame* pFrame) override;

    AX_VOID RegObserver(IObserver* pObserver);
    AX_VOID UnregObserver(IObserver* pObserver);

private:
    AX_S32 GetChannel() {
        return m_stDummyEncoder.nChannel;
    }

private:
    DUMMY_CODE_CONFIG_T m_stDummyEncoder;
    std::vector<IObserver*> m_vecObserver;
};
