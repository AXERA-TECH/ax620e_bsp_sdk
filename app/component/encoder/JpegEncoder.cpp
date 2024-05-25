/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "JpegEncoder.h"
#include "AppLogApi.h"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include "PrintHelper.h"
#include "ax_buffer_tool.h"
#include "ax_vdec_api.h"
#include "ax_vdec_type.h"
#include "ax_venc_api.h"

#define JENC "JENC"

using namespace std;

namespace {
#ifdef JDEC_SUPPORT
#define AX_VDEC_WIDTH_ALIGN (16)
#define AX_VDEC_HEIGHT_ALIGN (16)

static AX_VOID JpegDecodeOneFrame(JPEG_CONFIG_PTR pJpegConfig, const AX_VENC_STREAM_T* pStream) {
    if (!pStream || !pStream->stPack.u32Len) {
        return;
    }

    AX_U64 outPhyAddrDst = 0;
    AX_VOID* poutVirAddrDst = NULL;
    AX_VDEC_DEC_ONE_FRM_T decOneFrmParam;

    static AX_U32 nFrameTotalCnt = 0;
    static AX_U32 nFrameCnt = 0;
    static AX_U32 nSumMs = 0;

    AX_S32 uPixBits = 8;
    AX_S32 frmStride = AX_COMM_ALIGN(pJpegConfig->nWidth * uPixBits, AX_VDEC_WIDTH_ALIGN * 8) / 8;
    AX_S32 heightAlign = ALIGN_UP(pJpegConfig->nHeight, 16);
    AX_S32 uBufSize = AX_VDEC_GetPicBufferSize(frmStride, heightAlign, PT_JPEG);
    memset(&decOneFrmParam, 0x0, sizeof(AX_VDEC_DEC_ONE_FRM_T));
    AX_S32 nRet = AX_SYS_MemAlloc(&outPhyAddrDst, (AX_VOID**)&poutVirAddrDst, uBufSize, 0x1000, (AX_S8*)"JENC_VDEC");

    if (nRet != AX_SUCCESS) {
        LOG_MM_E(JENC, "[%d] AX_SYS_MemAlloc fail, ret=0x%x", pJpegConfig->nChannel, nRet);
        return;
    }

    decOneFrmParam.stStream.pu8Addr = pStream->stPack.pu8Addr;
    decOneFrmParam.stStream.u64PhyAddr = pStream->stPack.ulPhyAddr;
    decOneFrmParam.stStream.u32StreamPackLen = pStream->stPack.u32Len;

    decOneFrmParam.stFrame.u64VirAddr[0] = (AX_U64)poutVirAddrDst;
    decOneFrmParam.stFrame.u64VirAddr[1] = (AX_U64)poutVirAddrDst + frmStride * heightAlign;
    decOneFrmParam.stFrame.u64PhyAddr[0] = outPhyAddrDst;
    decOneFrmParam.stFrame.u64PhyAddr[1] = outPhyAddrDst + frmStride * heightAlign;

    AX_U64 nStart = CElapsedTimer::GetTickCount();
    nRet = AX_VDEC_JpegDecodeOneFrame(&decOneFrmParam);
    AX_U64 nEnd = CElapsedTimer::GetTickCount();

    if (outPhyAddrDst != 0) {
        AX_SYS_MemFree(outPhyAddrDst, poutVirAddrDst);
    }

    if (nRet != AX_SUCCESS) {
        LOG_MM_W(JENC, "[%d] AX_VDEC_JpegDecodeOneFrame fail, ret=0x%x, data length:%d", pJpegConfig->nChannel, nRet,
                 pStream->stPack.u32Len);
        return;
    } else {
        nFrameCnt++;
        nFrameTotalCnt ++;
        nSumMs += (AX_U32)(nEnd - nStart);
        if (20 <= nFrameCnt) {
            LOG_M_C("JDEC", "[X] avr %5.2fms, proc %d", (AX_F32)nSumMs / nFrameCnt, nFrameTotalCnt);
            nFrameCnt = 0;
            nSumMs = 0;
        }
        return;
    }

    return;
}
#endif  // JDEC_SUPPORT

}  // namespace

CJpegEncoder::CJpegEncoder(JPEG_CONFIG_T& tConfig) : CAXStage((string)JENC + (char)('0' + tConfig.nChannel)), m_tJpegConfig(tConfig) {
}

CJpegEncoder::~CJpegEncoder() {
}

AX_BOOL CJpegEncoder::Start(STAGE_START_PARAM_PTR pStartParams) {
    LOG_MM_I(JENC, "[%d] +++", GetChannel());
    AX_S32 nRet = AX_VENC_CreateChn(m_tJpegConfig.nChannel, &m_tJencChnAttr);
    if (AX_SUCCESS != nRet) {
        LOG_M_E(JENC, "[%d] AX_VENC_CreateChn failed, nRet=0x%x!", m_tJpegConfig.nChannel, nRet);
        return AX_FALSE;
    }

    ResetQFactor(m_tJpegConfig.nQpLevel);

    StartRecv();

    StartWorkThread();

    return CAXStage::Start(pStartParams);
}

AX_BOOL CJpegEncoder::Stop() {
    LOG_MM_C(JENC, "[%d] +++", GetChannel());
    AX_S32 nRetry = 5;
    AX_S32 nRet = 0;

    CAXStage::Stop();

    StopRecv();

    LOG_MM_I(JENC, "[%d] AX_VENC_DestroyChn ...", GetChannel());
    do {
        nRet = AX_VENC_DestroyChn(GetChannel());
        if (AX_ERR_VENC_BUSY == nRet) {
            CElapsedTimer::GetInstance()->mSleep(100);
            --nRetry;
        } else {
            break;
        }
    } while(nRetry >= 0);

    if (nRetry == -1) {
       LOG_MM_E(JENC, "[%d] AX_VENC_DestroyChn retry 5 times failed", GetChannel());
    }

    StopWorkThread();

    LOG_MM_C(JENC, "[%d] ---", GetChannel());
    return AX_TRUE;
}

AX_VOID CJpegEncoder::StartRecv() {
    LOG_M_I(JENC, "[%d] JENC start receive", m_tJpegConfig.nChannel);

    AX_VENC_RECV_PIC_PARAM_T tRecvParam;
    tRecvParam.s32RecvPicNum = -1;
    AX_S32 s32Ret = AX_VENC_StartRecvFrame(m_tJpegConfig.nChannel, &tRecvParam);
    if (AX_SUCCESS != s32Ret) {
        LOG_MM_E(JENC, "[%d] AX_VENC_StartRecvFrame failed. ret=0x%02x", s32Ret);
    }

    return;
}

AX_VOID CJpegEncoder::StopRecv() {
    LOG_M_I(JENC, "[%d] JENC stop receive ", m_tJpegConfig.nChannel);

    AX_S32 ret = AX_VENC_StopRecvFrame((VENC_CHN)m_tJpegConfig.nChannel);
    if (AX_SUCCESS != ret) {
        LOG_M_E(JENC, "[%d] AX_VENC_StopRecvFrame failed, ret=0x%x", m_tJpegConfig.nChannel, ret);
    }
}

AX_VOID CJpegEncoder::ResetChn() {
    LOG_M_C(JENC, "[%d] JENC reset chn", m_tJpegConfig.nChannel);
    AX_S32 ret = AX_VENC_ResetChn((VENC_CHN)m_tJpegConfig.nChannel);
    if (AX_SUCCESS != ret) {
        LOG_M_E(JENC, "[%d] AX_VENC_ResetChn failed, ret=0x%x", m_tJpegConfig.nChannel, ret);
    }
    return;
}

AX_VOID CJpegEncoder::StartWorkThread() {
    m_bGetThreadRunning = AX_TRUE;
    m_hGetThread = new std::thread(&CJpegEncoder::FrameGetThreadFunc, this, this);
}

AX_VOID CJpegEncoder::StopWorkThread() {
    LOG_MM_I(JENC, "[%d] +++", m_tJpegConfig.nChannel);

    m_bGetThreadRunning = AX_FALSE;
    if (m_hGetThread && m_hGetThread->joinable()) {
        m_hGetThread->join();
        delete m_hGetThread;
        m_hGetThread = nullptr;
    }

    LOG_MM_I(JENC, "[%d] ---", m_tJpegConfig.nChannel);
}

AX_BOOL CJpegEncoder::Init() {
    SetCapacity(AX_APP_LOCKQ_CAPACITY);
    return AX_TRUE;
}

AX_BOOL CJpegEncoder::DeInit() {
    LOG_MM_C(JENC, "[%d] +++", GetChannel());

    if (m_bGetThreadRunning) {
        Stop();
    }
    if (m_pFramectrl) {
        delete m_pFramectrl;
    }

    CAXStage::DeInit();
    LOG_MM_C(JENC, "[%d] ---", GetChannel());
    return AX_TRUE;
}

AX_VOID CJpegEncoder::RegObserver(IObserver* pObserver) {
    if (nullptr != pObserver) {
        OBS_TRANS_ATTR_T tTransAttr;
        tTransAttr.nWidth = m_tJpegConfig.nWidth;
        tTransAttr.nHeight = m_tJpegConfig.nHeight;

        if (pObserver->OnRegisterObserver(E_OBS_TARGET_TYPE_JENC, m_tJpegConfig.nPipeSrc, m_tJpegConfig.nChannel, &tTransAttr)) {
            m_vecObserver.emplace_back(pObserver);
        }
    }
}

AX_VOID CJpegEncoder::UnregObserver(IObserver* pObserver) {
    if (nullptr == pObserver) {
        return;
    }

    for (vector<IObserver*>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        if (*it == pObserver) {
            m_vecObserver.erase(it);
            break;
        }
    }
}

AX_VOID CJpegEncoder::NotifyAll(AX_U32 nChannel, AX_VOID* pStream) {
    if (nullptr == pStream) {
        return;
    }
    CPrintHelper::GetInstance()->Add(E_PH_MOD_JENC, nChannel);

#ifdef JDEC_SUPPORT
    // JDEC performance
    JpegDecodeOneFrame(&m_tJpegConfig, (AX_VENC_STREAM_T*)pStream);
#endif  // JDEC_SUPPORT

    // To prevent lag in the web page, control the frame rate sent to the web page.
    if (AX_FALSE == m_pFramectrl->FramerateCtrl()) {
        for (vector<IObserver*>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
            (*it)->OnRecvData(E_OBS_TARGET_TYPE_JENC, m_tJpegConfig.nPipeSrc, nChannel, pStream);
        }
    }
}

AX_BOOL CJpegEncoder::InitParams() {
    memset(&m_tJencChnAttr, 0, sizeof(AX_VENC_CHN_ATTR_T));

    m_tJencChnAttr.stVencAttr.enMemSource = m_tJpegConfig.eMemSource;

    m_tJencChnAttr.stVencAttr.u32MaxPicWidth = ALIGN_UP(m_tJpegConfig.nWidth, AX_ENCODER_FBC_STRIDE_ALIGN_VAL);
    m_tJencChnAttr.stVencAttr.u32MaxPicHeight = m_tJencChnAttr.stVencAttr.u32MaxPicWidth;

    m_tJencChnAttr.stVencAttr.u32PicWidthSrc = m_tJpegConfig.nWidth;
    m_tJencChnAttr.stVencAttr.u32PicHeightSrc = m_tJpegConfig.nHeight;
    m_tJencChnAttr.stVencAttr.u32BufSize = m_tJpegConfig.nBufSize; /*stream buffer size*/

    m_tJencChnAttr.stVencAttr.u8InFifoDepth = m_tJpegConfig.nInFifoDepth;
    m_tJencChnAttr.stVencAttr.u8OutFifoDepth = m_tJpegConfig.nOutFifoDepth;
    m_tJencChnAttr.stVencAttr.enLinkMode = m_tJpegConfig.bLink ? AX_LINK_MODE : AX_UNLINK_MODE;

    m_tJencChnAttr.stVencAttr.enType = PT_JPEG;
    m_tJencChnAttr.stRcAttr.stFrameRate.fSrcFrameRate = m_tJpegConfig.fSrcFrameRate;
    m_tJencChnAttr.stRcAttr.stFrameRate.fDstFrameRate =
        (-1 == m_tJpegConfig.fDstFrameRate) ? m_tJpegConfig.fSrcFrameRate : m_tJpegConfig.fDstFrameRate;
    m_pFramectrl = new CFramerateCtrlHelper(m_tJpegConfig.fSrcFrameRate, m_tJpegConfig.fDstFrameRate);
    LOG_MM(JENC, "JENC attr: chn:%d, w:%d, h:%d, link:%d, memSrc:%d,frameRate[%f, %f]", m_tJpegConfig.nChannel,
           m_tJencChnAttr.stVencAttr.u32PicWidthSrc, m_tJencChnAttr.stVencAttr.u32PicHeightSrc,
           m_tJencChnAttr.stVencAttr.enLinkMode == AX_LINK_MODE ? AX_TRUE : AX_FALSE, m_tJencChnAttr.stVencAttr.enMemSource,
           m_tJpegConfig.fSrcFrameRate, m_tJpegConfig.fDstFrameRate);

    return AX_TRUE;
}

AX_BOOL CJpegEncoder::ResetQFactor(AX_U32 nQFactor) {
    AX_S32 nRet = AX_SUCCESS;

    AX_VENC_JPEG_PARAM_T stJpegParam;
    memset(&stJpegParam, 0, sizeof(AX_VENC_JPEG_PARAM_T));

    nRet = AX_VENC_GetJpegParam(m_tJpegConfig.nChannel, &stJpegParam);
    if (AX_SUCCESS != nRet) {
        LOG_M_E(JENC, "[%d] AX_VENC_GetJpegParam failed!", m_tJpegConfig.nChannel, nRet);
        return AX_FALSE;
    }

    stJpegParam.u32Qfactor = nQFactor;

    nRet = AX_VENC_SetJpegParam(m_tJpegConfig.nChannel, &stJpegParam);
    if (AX_SUCCESS != nRet) {
        LOG_M_E(JENC, "[%d] AX_VENC_SetJpegParam failed!", m_tJpegConfig.nChannel, nRet);
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CJpegEncoder::ProcessFrame(CAXFrame* pFrame) {
    AX_S32 nRet = 0;

    nRet = AX_VENC_SendFrame(m_tJpegConfig.nChannel, &pFrame->stFrame.stVFrame, -1);
    if (AX_SUCCESS != nRet) {
        LOG_M_E(JENC, "[%d] AX_VENC_SendFrame failed, nRet=0x%x", m_tJpegConfig.nChannel, nRet);
        return AX_FALSE;
    } else {
        LOG_M_D(JENC, "[%d] AX_VENC_SendFrame successfully.", m_tJpegConfig.nChannel);
    }

    return AX_TRUE;
}

AX_VOID CJpegEncoder::FrameGetThreadFunc(AX_VOID* pCaller) {
    AX_S32 nRet = AX_SUCCESS;

    CJpegEncoder* pThis = (CJpegEncoder*)pCaller;
    AX_S32 nChannel = pThis->m_tJpegConfig.nChannel;

    AX_CHAR szName[50] = {0};
    sprintf(szName, "APP_JENC_Get_%d", nChannel);
    prctl(PR_SET_NAME, szName);

    AX_VENC_STREAM_T stStream;
    memset(&stStream, 0, sizeof(AX_VENC_STREAM_T));

    while (pThis->m_bGetThreadRunning) {
        m_mtx.lock();
        if (m_bPauseGet) {
            CElapsedTimer::GetInstance()->mSleep(10);
            m_mtx.unlock();
            continue;
        }
        m_mtx.unlock();

        nRet = AX_VENC_GetStream(nChannel, &stStream, -1);
        if (AX_SUCCESS != nRet) {
            if (AX_ERR_VENC_FLOW_END == nRet) {
                pThis->m_bGetThreadRunning = AX_FALSE;
                break;
            }

            if (AX_ERR_VENC_QUEUE_EMPTY == nRet) {
                CElapsedTimer::GetInstance()->mSleep(1);
                continue;
            }

            LOG_M_E(JENC, "[%d] AX_VENC_GetStream failed, ret=%#x", nChannel, nRet);
            continue;
        }

        if (stStream.stPack.pu8Addr && stStream.stPack.u32Len > 0) {
            LOG_MM_D(JENC, "[%d] Get jenc out stream, size=%d.", nChannel, stStream.stPack.u32Len);
            NotifyAll(nChannel, &stStream);
        }

        nRet = AX_VENC_ReleaseStream(nChannel, &stStream);
        if (AX_SUCCESS != nRet) {
            LOG_M_E(JENC, "[%d] AX_VENC_ReleaseStream failed, ret=%#x", nChannel, nRet);
            continue;
        }
    }
}

AX_BOOL CJpegEncoder::UpdateRotation(AX_U8 nRotation) {
    LOG_MM_C(JENC, "+++");
    AX_U32 nNewWidth = 0;
    AX_U32 nNewHeight = 0;

    if (!GetResolutionByRotate(nRotation, nNewWidth, nNewHeight)) {
        LOG_MM_E(JENC, "[%d] Can not get new resolution for rotate operation.", GetChannel());
        return AX_FALSE;
    }
    AX_U32 nWidthAlign = 2;

    AX_VENC_CHN_ATTR_T tAttr;
    AX_VENC_GetChnAttr(GetChannel(), &tAttr);
    tAttr.stVencAttr.u32PicWidthSrc = ALIGN_UP(nNewWidth, nWidthAlign);
    tAttr.stVencAttr.u32PicHeightSrc = nNewHeight;

    AX_VENC_SetChnAttr(GetChannel(), &tAttr);

    LOG_MM_C(JENC, "[%d] Reset res: (w: %d, h: %d) (MAX w: %d, h:%d)", GetChannel(), tAttr.stVencAttr.u32PicWidthSrc,
             tAttr.stVencAttr.u32PicHeightSrc, tAttr.stVencAttr.u32MaxPicWidth, tAttr.stVencAttr.u32MaxPicHeight);
    m_nRotation = nRotation;
    return AX_TRUE;
}

AX_BOOL CJpegEncoder::GetResolutionByRotate(AX_U8 nRotation, AX_U32& nWidth, AX_U32& nHeight) {
    nWidth = m_tJpegConfig.nWidth;
    nHeight = m_tJpegConfig.nHeight;

    if (1 == nRotation || 3 == nRotation) {
        std::swap(nWidth, nHeight);
    }

    return AX_TRUE;
}

AX_BOOL CJpegEncoder::UpdateChnResolution(const JPEG_CONFIG_T& tNewConfig) {
    AX_U32 nStride = 2;
    AX_U32 nWidth = tNewConfig.nWidth;
    AX_U32 nHeight = tNewConfig.nHeight;
    if (1 == m_nRotation || 3 == m_nRotation) {
        std::swap(nWidth, nHeight);
    }

    AX_VENC_CHN_ATTR_T tAttr;
    AX_VENC_GetChnAttr(GetChannel(), &tAttr);
    tAttr.stVencAttr.u32PicWidthSrc = ALIGN_UP(nWidth, nStride);
    tAttr.stVencAttr.u32PicHeightSrc = nHeight;

    AX_VENC_SetChnAttr(GetChannel(), &tAttr);

    LOG_MM_W(JENC, "[%d] Reset res: (w: %d, h: %d) max(w:%d, h:%d)", GetChannel(), tAttr.stVencAttr.u32PicWidthSrc,
             tAttr.stVencAttr.u32PicHeightSrc, tAttr.stVencAttr.u32MaxPicWidth, tAttr.stVencAttr.u32MaxPicHeight);

    return AX_TRUE;
}

AX_VOID CJpegEncoder::SetPauseFlag(AX_BOOL bPause) {
    std::lock_guard<std::mutex> lck(m_mtx);
    m_bPauseGet = bPause;
}