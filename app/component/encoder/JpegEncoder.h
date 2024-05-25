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
#include "ax_venc_comm.h"

#define MAX_JENC_CHANNEL_NUM (16)

typedef struct stJpegConfig {
    AX_IMG_FORMAT_E eImgFormat;
    AX_U8 nPipeSrc;
    AX_S32 nChannel;
    AX_S32 nWidth;
    AX_S32 nHeight;
    AX_U32 nStride;
    AX_U32 nBufSize;
    AX_U8 nInFifoDepth;
    AX_U8 nOutFifoDepth;
    AX_MEMORY_SOURCE_E eMemSource;
    AX_S32 nQpLevel;
    AX_BOOL bLink;
    AX_BOOL bEnable;
    AX_F32 fSrcFrameRate;
    AX_F32 fDstFrameRate;

    stJpegConfig() {
        memset(this, 0, sizeof(stJpegConfig));
        eImgFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        nQpLevel = 90;
        bEnable = AX_FALSE;
    }

} JPEG_CONFIG_T, *JPEG_CONFIG_PTR;

class CJpegEncoder : public CAXStage {
public:
    CJpegEncoder(JPEG_CONFIG_T& tConfig);
    ~CJpegEncoder();

    AX_BOOL Init() override;
    AX_BOOL DeInit() override;
    AX_BOOL Start(STAGE_START_PARAM_PTR pStartParams) override;
    AX_BOOL Stop(AX_VOID) override;

    AX_BOOL InitParams();

    AX_VOID RegObserver(IObserver* pObserver);
    AX_VOID UnregObserver(IObserver* pObserver);

    AX_VOID StartRecv();
    AX_VOID StopRecv();
    AX_VOID ResetChn();
    AX_BOOL UpdateRotation(AX_U8 nRotation);
    AX_BOOL UpdateChnResolution(const JPEG_CONFIG_T& tNewConfig);

    JPEG_CONFIG_T* GetChnCfg() {
        return &m_tJpegConfig;
    }

    AX_U8 GetRotation() {
        return m_nRotation;
    }

    AX_VOID SetChnCfg(JPEG_CONFIG_T& tConfig) {
        m_tJpegConfig = tConfig;
    }

    AX_S32 GetChannel() {
        return m_tJpegConfig.nChannel;
    }

    AX_U8 GetSensorSrc() {
        return m_tJpegConfig.nPipeSrc;
    }

    AX_BOOL ResetQFactor(AX_U32 nQFactor);
    AX_VOID SetPauseFlag(AX_BOOL bGetFlag);

protected:
    virtual AX_BOOL ProcessFrame(CAXFrame* pFrame) override;
    AX_VOID NotifyAll(AX_U32 nChannel, AX_VOID* pStream);

    AX_VOID FrameGetThreadFunc(AX_VOID* pCaller);
    AX_VOID StartWorkThread();
    AX_VOID StopWorkThread();

private:
    AX_BOOL GetResolutionByRotate(AX_U8 nRotation, AX_U32& nWidth, AX_U32& nHeight);

private:
    JPEG_CONFIG_T m_tJpegConfig;
    AX_VENC_CHN_ATTR_T m_tJencChnAttr;

    std::thread* m_hGetThread{nullptr};
    AX_BOOL m_bGetThreadRunning;

    std::vector<IObserver*> m_vecObserver;
    CFramerateCtrlHelper* m_pFramectrl{nullptr};
    AX_U8 m_nRotation{0};
    AX_BOOL m_bPauseGet{AX_FALSE};
    std::mutex m_mtx;
};
