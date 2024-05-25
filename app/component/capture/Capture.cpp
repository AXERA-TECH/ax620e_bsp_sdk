/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "Capture.hpp"
#include "AppLog.hpp"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include <algorithm>
#include <chrono>
#include "ax_venc_api.h"

#define CAPTURE "CAPTURE"

namespace {
using AXLockGuard = std::unique_lock<std::mutex>;
constexpr AX_U32 g_capture_nReceiveWaitTimeoutMilliseconds = 2000;
constexpr AX_S8 JPEG_ENCODE_ONCE_NAME[] = "JENC_CAP";
constexpr AX_U32 g_capture_nMaxOutBufferSize = 1572864; // 1.5 * 1024 * 1024

static AX_S32 MallocJpegOutBuffer(AX_JPEG_ENCODE_ONCE_PARAMS_T* pStJpegEncodeOnceParam, AX_U32 u32Width, AX_U32 u32Height) {
    AX_U64 phyBuff = 0;
    AX_VOID* virBuff = NULL;
    AX_S32 s32Ret = AX_SUCCESS;

    AX_U32 maxFrameSize = AX_MAX(g_capture_nMaxOutBufferSize, u32Width * u32Height * 3 / 16);
    AX_U32 minFrameSize = AX_MIN(g_capture_nMaxOutBufferSize, u32Width * u32Height * 3 / 16);

    AX_U32 frameSize = maxFrameSize;
    s32Ret = AX_SYS_MemAlloc(&phyBuff, &virBuff, frameSize, 0, (AX_S8*)JPEG_ENCODE_ONCE_NAME);

    if (s32Ret) {
        frameSize = minFrameSize;
        s32Ret = AX_SYS_MemAlloc(&phyBuff, &virBuff, frameSize, 0, (AX_S8*)JPEG_ENCODE_ONCE_NAME);
    }

    if (s32Ret) {
        LOG_MM_E(CAPTURE, "alloc mem err, size(%d).\n", frameSize);
        return -1;
    }

    pStJpegEncodeOnceParam->u32OutBufSize = frameSize;
    pStJpegEncodeOnceParam->ulPhyAddr = phyBuff;
    pStJpegEncodeOnceParam->pu8Addr = (AX_U8*)virBuff;

    return AX_SUCCESS;
}

}  // namespace

AX_BOOL CCapture::SendFrame(CAXFrame* axFrame, AX_U32 nSnsID, AX_U32 nChn) {
    if (!IsCapturing(nSnsID, nChn)) {
        axFrame->FreeMem();
        return AX_TRUE;
    }

    {
        AXLockGuard lck(m_mutexStat);
        m_bCapture = AX_FALSE;
        m_pAXFrame = axFrame;
    }

    AXLockGuard lck(m_mutexCapture);
    m_cvCapture.notify_one();
    return AX_TRUE;
}

AX_BOOL CCapture::CapturePicture(AX_U32 nSnsID, AX_U32 nChn, AX_U32 nQpLevel, AX_VOID** ppCallbackData) {
    LOG_MM_I(CAPTURE, "+++");
    if (m_bCapture) {
        LOG_MM_W(CAPTURE, "[%d] Capture is running, please wait, and try again", nSnsID);
        return AX_FALSE;
    }

    if (m_pAXFrame) {
        LOG_M_W(CAPTURE, "[%d] Capture frame should be free", nSnsID);
        return AX_FALSE;
    }

    {
        AXLockGuard lck(m_mutexStat);
        m_bCapture = AX_TRUE;
        m_nSnsID = nSnsID;
        m_nChn = nChn;
        m_pAXFrame = nullptr;
    }

    AXLockGuard lck(m_mutexCapture);
    auto ret = m_cvCapture.wait_for(lck, std::chrono::milliseconds(g_capture_nReceiveWaitTimeoutMilliseconds), [this]() -> bool { return m_pAXFrame != nullptr; });
    if (!ret || !m_pAXFrame) {
        LOG_MM_E(CAPTURE, "[%d] [%d] Capture frame timeout.", m_nSnsID, m_nChn);
        ResetCaptureStatus();
        return AX_FALSE;
    }

    AX_JPEG_ENCODE_ONCE_PARAMS_T stJpegEncodeOnceParam;
    memset(&stJpegEncodeOnceParam, 0, sizeof(stJpegEncodeOnceParam));
    const AX_VIDEO_FRAME_INFO_T& stVFrame = m_pAXFrame->stFrame.stVFrame;
    for (AX_U8 i = 0; i < 3; ++i) {
        stJpegEncodeOnceParam.u64PhyAddr[i] = stVFrame.stVFrame.u64PhyAddr[i];
        stJpegEncodeOnceParam.u32PicStride[i] = stVFrame.stVFrame.u32PicStride[i];
    }

    stJpegEncodeOnceParam.stJpegParam.u32Qfactor = nQpLevel;
    stJpegEncodeOnceParam.u32Width = stVFrame.stVFrame.u32Width;
    stJpegEncodeOnceParam.u32Height = stVFrame.stVFrame.u32Height;
    stJpegEncodeOnceParam.enImgFormat = stVFrame.stVFrame.enImgFormat;
    stJpegEncodeOnceParam.stCompressInfo = stVFrame.stVFrame.stCompressInfo;

    using AXSnapshotDataCallback = std::function<AX_VOID(AX_VOID* data, AX_U32 size, AX_VOID* conn)>;
    std::pair<AX_VOID*, AXSnapshotDataCallback>* pSnapshotData = (std::pair<AX_VOID*, AXSnapshotDataCallback>*)ppCallbackData;
    AX_S32 s32Ret = MallocJpegOutBuffer(&stJpegEncodeOnceParam, stVFrame.stVFrame.u32Width, stVFrame.stVFrame.u32Height);
    if (AX_SUCCESS == s32Ret) {
        s32Ret = AX_VENC_JpegEncodeOneFrame(&stJpegEncodeOnceParam);
        if (AX_SUCCESS == s32Ret) {
            const AX_U32 uDataSize = stJpegEncodeOnceParam.u32Len;
            LOG_MM_I(CAPTURE, "[%d] [%d] Capture imagesize:%d", m_nSnsID, m_nChn, uDataSize);
            pSnapshotData->second(stJpegEncodeOnceParam.pu8Addr, uDataSize, pSnapshotData->first);
        } else {
            LOG_MM_E(CAPTURE, "[%d] [%d] Capture failed: 0x%08X", m_nSnsID, m_nChn, s32Ret);
        }

        AX_SYS_MemFree(stJpegEncodeOnceParam.ulPhyAddr, stJpegEncodeOnceParam.pu8Addr);
    }

    ResetCaptureStatus();

    LOG_MM_I(CAPTURE, "---");

    return AX_TRUE;
}

AX_BOOL CCapture::DeInit(AX_VOID) {
    LOG_MM_C(CAPTURE, "[%d][%d] +++", m_nSnsID, m_nChn);

    ResetCaptureStatus();

    LOG_MM_C(CAPTURE, "[%d][%d] ---", m_nSnsID, m_nChn);
    return AX_TRUE;
}

AX_VOID CCapture::ResetCaptureStatus(AX_VOID) {
    AXLockGuard lck(m_mutexStat);
    m_bCapture = AX_FALSE;
    m_nSnsID = 0;
    m_nChn = 0;
    if (m_pAXFrame) {
        m_pAXFrame->FreeMem();
        m_pAXFrame = nullptr;
    }
}

AX_BOOL CCapture::IsCapturing(AX_U32 nSnsID, AX_U32 nChn) {
    if ((nSnsID == m_nSnsID) && (nChn == m_nChn)) {
        return m_bCapture;
    } else {
        return AX_FALSE;
    }
}
