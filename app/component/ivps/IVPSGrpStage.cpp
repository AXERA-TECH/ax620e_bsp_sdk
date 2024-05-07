/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "IVPSGrpStage.h"
#include <sys/prctl.h>
#include <chrono>
#include <map>
#include "AXFrame.hpp"
#include "AXThread.hpp"
#include "AppLogApi.h"
#include "CmdLineParser.h"
#include "CommonUtils.hpp"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include "IvpsOptionHelper.h"
#include "OptionHelper.h"
#include "SensorOptionHelper.h"
#define IVPS "IVPS"

#define MAX_IPC_IVPS_FRAME_TIMEOUT (1000)
#define MAX_REGION_GROUP (3)
#define TDP_CROP_RESIZE_APPLY_GRP (3)
#define TDP_CROP_RESIZE_APPLY_CHN (0)

namespace {
static constexpr AX_S32 g_ivps_nMinFBCWidth = 512;
static constexpr AX_S32 g_ivps_nMinFBCWidthFor4K = 1280; // AX620E TODO: WA
}  // namespace

CIVPSGrpStage::CIVPSGrpStage(IVPS_GROUP_CFG_T& tGrpConfig) : CAXStage(IVPS), m_tIvpsGrpCfg(tGrpConfig), m_nIvpsGrp(tGrpConfig.nGrp) {
}

AX_BOOL CIVPSGrpStage::Init() {
    SetCapacity(AX_APP_LOCKQ_CAPACITY);

    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::DeInit() {
    LOG_MM_C(IVPS, "[%d] +++", m_nIvpsGrp);

    if (m_bStarted) {
        Stop();
    }

    CAXStage::DeInit();
    LOG_MM_C(IVPS, "[%d] ---", m_nIvpsGrp);
    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::Start(STAGE_START_PARAM_PTR pStartParams) {
    IVPS_GRP_T& tGrp = m_tIvpsGrp;

    LOG_MM_I(IVPS, "[%d] +++", m_nIvpsGrp);

    if (0 == m_tIvpsGrp.tPipelineAttr.nOutChnNum) {
        return AX_FALSE;
    }

    AX_U16 nIvpsGrp = tGrp.nGroup;
    AX_S32 ret = AX_IVPS_CreateGrp(nIvpsGrp, &tGrp.tGroupAttr);
    if (AX_SUCCESS != ret) {
        LOG_M_E(IVPS, "AX_IVPS_CreateGrp(Grp: %d) failed, ret=0x%x", nIvpsGrp, ret);
        return AX_FALSE;
    }

    ret = AX_IVPS_SetPipelineAttr(nIvpsGrp, &tGrp.tPipelineAttr);
    if (AX_SUCCESS != ret) {
        LOG_MM_E(IVPS, "AX_IVPS_SetPipelineAttr(Grp: %d) failed, ret=0x%x", nIvpsGrp, ret);
        return AX_FALSE;
    }

    for (AX_U8 nChn = 0; nChn < tGrp.tPipelineAttr.nOutChnNum; ++nChn) {
        ret = AX_IVPS_EnableChn(nIvpsGrp, nChn);
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVPS, "AX_IVPS_EnableChn(Grp: %d, Chn: %d) failed, ret=0x%x", nIvpsGrp, nChn, ret);
            return AX_FALSE;
        }
        m_mapChnState[nChn] = AX_TRUE;
        LOG_M(IVPS, "Enable channel (Grp: %d, Chn: %d)", nIvpsGrp, nChn);
    }

    ret = AX_IVPS_StartGrp(nIvpsGrp);
    if (AX_SUCCESS != ret) {
        LOG_M_E(IVPS, "AX_IVPS_StartGrp(Grp: %d) failed, ret=0x%x", nIvpsGrp, ret);
        return AX_FALSE;
    }

    StartWorkThread();

    if (!StartOSD()) {
        return AX_FALSE;
    }

    m_bStarted = AX_TRUE;

    LOG_MM_I(IVPS, "[%d] ---", m_nIvpsGrp);

    return CAXStage::Start(pStartParams);
}

AX_BOOL CIVPSGrpStage::Stop() {
    LOG_MM_C(IVPS, "[%d] +++", m_nIvpsGrp);

    AX_S32 ret = AX_SUCCESS;
    if (0 == m_tIvpsGrp.tPipelineAttr.nOutChnNum) {
        return AX_FALSE;
    }

    if (!StopOSD()) {
        return AX_FALSE;
    }

    StopWorkThread();

    ret = AX_IVPS_StopGrp(m_nIvpsGrp);
    if (AX_SUCCESS != ret) {
        LOG_M_E(IVPS, "AX_IVPS_StopGrp(Grp: %d) failed, ret=0x%x", m_nIvpsGrp, ret);
    }

    for (AX_U8 chn = 0; chn < m_tIvpsGrp.tPipelineAttr.nOutChnNum; ++chn) {
        ret = AX_IVPS_DisableChn(m_nIvpsGrp, chn);
        if (AX_SUCCESS != ret) {
            LOG_M_E(IVPS, "AX_IVPS_DisableChn(Grp: %d, Channel: %d) failed, ret=0x%x", m_nIvpsGrp, chn, ret);
        }
        m_mapChnState[chn] = AX_FALSE;
    }

    ret = AX_IVPS_DestoryGrp(m_nIvpsGrp);
    if (AX_SUCCESS != ret) {
        LOG_M_E(IVPS, "AX_IVPS_DestoryGrp(Grp: %d) failed, ret=0x%x", m_nIvpsGrp, ret);
    }

    m_bStarted = AX_FALSE;

    LOG_MM_C(IVPS, "[%d] ---", m_nIvpsGrp);

    return CAXStage::Stop();
}

AX_VOID CIVPSGrpStage::FrameGetThreadFunc(IVPS_GET_THREAD_PARAM_PTR pThreadParam) {
    AX_S32 nRet = AX_SUCCESS;

    AX_U8 nIvpsGrp = pThreadParam->nIvpsGrp;
    AX_U8 nIvpsChn = pThreadParam->nIvpsChn;

    AX_CHAR szName[50] = {0};
    sprintf(szName, "APP_IVPS_Get_%d%d", nIvpsGrp, nIvpsChn);
    prctl(PR_SET_NAME, szName);

    AX_BOOL bLink = m_tIvpsGrpCfg.arrChnLinkFlag[nIvpsChn] == 0 ? AX_FALSE : AX_TRUE;

    LOG_MM_I(IVPS, "[%d][%d] +++ bLink:%d ", nIvpsGrp, nIvpsChn, bLink);

    pThreadParam->bExit = AX_FALSE;
    while (!pThreadParam->bExit) {
        if (!pThreadParam->nChnEnable) {
            CElapsedTimer::GetInstance()->mSleep(100);
            continue;
        }

        AX_BOOL bNeedDispatchFrame = AX_FALSE;
        if (bLink) {
            bLink = m_tIvpsGrpCfg.arrChnLinkFlag[nIvpsChn] == 0 ? AX_FALSE : AX_TRUE;
            auto& vecObserver = m_mapChnObserver[nIvpsChn];
            for (auto item : vecObserver) {
                if (item && item->IsReadyForRecv(E_OBS_TARGET_TYPE_IVPS, nIvpsGrp, nIvpsChn)) {
                    bNeedDispatchFrame = AX_TRUE;
                    break;
                }
            }
            if (!bNeedDispatchFrame) {
                CElapsedTimer::GetInstance()->mSleep(200);
                continue;
            }
        }

        if (bNeedDispatchFrame) {
            AX_IVPS_PIPELINE_ATTR_T tPipelineAttr = {0};
            AX_S32 nRet = AX_IVPS_GetPipelineAttr(m_tIvpsGrpCfg.nGrp, &tPipelineAttr);
            if (AX_SUCCESS == nRet) {
                tPipelineAttr.nOutFifoDepth[nIvpsChn] = 1;
                AX_IVPS_SetPipelineAttr(m_tIvpsGrpCfg.nGrp, &tPipelineAttr);
            }
        }

        CAXFrame* pFrame = new (std::nothrow) CAXFrame();
        if (!pFrame) {
            LOG_M_E(IVPS, "alloc MediaFrame instance fail");
            continue;
        }

        nRet = AX_IVPS_GetChnFrame(nIvpsGrp, nIvpsChn, &pFrame->stFrame.stVFrame.stVFrame, 95);
        constexpr AX_S32 nMaxRetrytimes = 10;
        if (bNeedDispatchFrame) {
            AX_S32 nGetTimes = 0;
            while (AX_SUCCESS != nRet && nGetTimes++ < nMaxRetrytimes) {
                nRet = AX_IVPS_GetChnFrame(nIvpsGrp, nIvpsChn, &pFrame->stFrame.stVFrame.stVFrame, 95);
                CElapsedTimer::GetInstance()->mSleep(100);
            }
            AX_IVPS_PIPELINE_ATTR_T tPipelineAttr = {0};
            AX_S32 nRet = AX_IVPS_GetPipelineAttr(m_tIvpsGrpCfg.nGrp, &tPipelineAttr);
            if (AX_SUCCESS == nRet) {
                tPipelineAttr.nOutFifoDepth[nIvpsChn] = 0;
                AX_IVPS_SetPipelineAttr(m_tIvpsGrpCfg.nGrp, &tPipelineAttr);
            }
        }
        if (AX_SUCCESS != nRet) {
            if (AX_ERR_IVPS_BUF_EMPTY == nRet) {
                delete pFrame;
                CElapsedTimer::GetInstance()->mSleep(1);
                continue;
            }
            delete pFrame;
            LOG_M(IVPS, "[%d][%d] Get ivps frame failed. ret=0x%x", nIvpsGrp, nIvpsChn, nRet);

            CElapsedTimer::GetInstance()->mSleep(1);
            continue;
        }
        LOG_MM_D(IVPS, "[%d][%d] Seq: %lld, w:%d, h:%d, size:%u, release:%p,PhyAddr:%lld", nIvpsGrp, nIvpsChn,
                 pFrame->stFrame.stVFrame.stVFrame.u64SeqNum, pFrame->stFrame.stVFrame.stVFrame.u32Width,
                 pFrame->stFrame.stVFrame.stVFrame.u32Height, pFrame->stFrame.stVFrame.stVFrame.u32FrameSize, pThreadParam->pReleaseStage,
                 pFrame->stFrame.stVFrame.stVFrame.u64PhyAddr[0]);

        pFrame->nGrp = nIvpsGrp;
        pFrame->nChn = nIvpsChn;
        pFrame->pFrameRelease = pThreadParam->pReleaseStage;
        NotifyAll(nIvpsGrp, nIvpsChn, pFrame);
    }

    LOG_MM(IVPS, "[%d][%d] ---", nIvpsGrp, nIvpsChn);
}

AX_VOID CIVPSGrpStage::VideoFrameRelease(CAXFrame* pFrame) {
    if (pFrame) {
        if (!pFrame->bMultiplex || pFrame->DecFrmRef() == 0) {
            LOG_M_D(IVPS, "[%d][%d] AX_IVPS_ReleaseChnFrame, seq=%lld, pFrqame:%p", pFrame->nGrp, pFrame->nChn,
                    pFrame->stFrame.stVFrame.stVFrame.u64SeqNum, pFrame);
            AX_IVPS_ReleaseChnFrame(pFrame->nGrp, pFrame->nChn, &pFrame->stFrame.stVFrame.stVFrame);
            delete pFrame;
        }
    }
}

AX_BOOL CIVPSGrpStage::RecvFrame(CAXFrame* pFrame) {
    if (!EnqueueFrame(pFrame)) {
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::ProcessFrame(CAXFrame* pFrame) {
    if (!pFrame) {
        return AX_FALSE;
    }

    std::unique_lock<std::mutex> lck(m_mutxSend, std::defer_lock);
    if (!lck.try_lock()) {
        return AX_TRUE;
    }
    AX_S32 ret = AX_IVPS_SendFrame(m_nIvpsGrp, &pFrame->stFrame.stVFrame.stVFrame, MAX_IPC_IVPS_FRAME_TIMEOUT);

    if (AX_SUCCESS != ret) {
        LOG_M_E(IVPS, "AX_IVPS_SendFrame(Grp %d, size:%u, Seq %d) failed, ret=0x%x", m_nIvpsGrp,
                pFrame->stFrame.stVFrame.stVFrame.u32FrameSize, pFrame->stFrame.stVFrame.stVFrame.u64SeqNum, ret);
        return AX_FALSE;
    } else {
        LOG_MM_D(IVPS, "[%d] AX_IVPS_SendFrame successfully, PhyAddr:0x%llx ,size:%u, seq=%d, bMux=%d.", m_nIvpsGrp,
                 pFrame->stFrame.stVFrame.stVFrame.u64PhyAddr[0], pFrame->stFrame.stVFrame.stVFrame.u32FrameSize,
                 pFrame->stFrame.stVFrame.stVFrame.u64SeqNum, pFrame->bMultiplex);
    }

    return AX_TRUE;
}

AX_VOID CIVPSGrpStage::StartWorkThread() {
    LOG_MM_I(IVPS, "[%d] +++", m_tIvpsGrpCfg.nGrp);

    /* Start frame get thread */
    for (AX_U8 nChn = 0; nChn < m_tIvpsGrp.tPipelineAttr.nOutChnNum; ++nChn) {
        const auto& vecObserver = m_mapChnObserver[nChn];
        if (vecObserver.empty()) {
            continue;
        }

        /* get thread param */
        m_tGetThreadParam[nChn].nChnEnable = AX_TRUE;
        m_tGetThreadParam[nChn].nIvpsGrp = m_nIvpsGrp;
        m_tGetThreadParam[nChn].nIvpsChn = nChn;
        m_tGetThreadParam[nChn].pReleaseStage = this;
        m_tGetThreadParam[nChn].bExit = AX_FALSE;
        m_hGetThread[nChn] = std::thread(&CIVPSGrpStage::FrameGetThreadFunc, this, &m_tGetThreadParam[nChn]);
    }

    LOG_MM_I(IVPS, "[%d] ---", m_tIvpsGrpCfg.nGrp);
}

AX_VOID CIVPSGrpStage::StopWorkThread() {
    LOG_MM_I(IVPS, "[%d] +++", m_tIvpsGrpCfg.nGrp);

    for (AX_U8 nChn = 0; nChn < m_tIvpsGrp.tPipelineAttr.nOutChnNum; ++nChn) {
        m_tGetThreadParam[nChn].bExit = AX_TRUE;
    }

    for (AX_U8 nChn = 0; nChn < m_tIvpsGrp.tPipelineAttr.nOutChnNum; ++nChn) {
        if (m_hGetThread[nChn].joinable()) {
            m_hGetThread[nChn].join();
        }
    }

    LOG_MM_I(IVPS, "[%d] ---", m_tIvpsGrpCfg.nGrp);
}

AX_BOOL CIVPSGrpStage::InitParams() {
    m_tIvpsGrp = IVPS_GRP_T{};
    m_tIvpsGrp.nGroup = m_nIvpsGrp;
    /* Config group attr */
    m_tIvpsGrp.tGroupAttr.nInFifoDepth = m_tIvpsGrpCfg.nGrpInFifoDepth;
    m_tIvpsGrp.tGroupAttr.ePipeline = AX_IVPS_PIPELINE_DEFAULT;

    /* Config pipeline attr */
    m_tIvpsGrp.tPipelineAttr.nOutChnNum = m_tIvpsGrpCfg.nGrpChnNum;
    m_tIvpsGrp.tPipelineAttr.nInDebugFifoDepth = 0;
    for (AX_U8 i = 0; i < m_tIvpsGrpCfg.nGrpChnNum; i++) {
        m_tIvpsGrp.tPipelineAttr.nOutFifoDepth[i] = m_tIvpsGrpCfg.arrChnOutFifoDepth[i];
    }

    SENSOR_CONFIG_T tSensorCfg;
    APP_SENSOR_CONFIG(m_tIvpsGrpCfg.nSnsSrc, tSensorCfg);

    m_eRotation = (AX_IVPS_ROTATION_E)tSensorCfg.eRotation;

    /* Config group filter 0 */
    m_tIvpsGrp.tPipelineAttr.tFilter[0][0].eEngine = m_tIvpsGrpCfg.eGrpEngineType0;
    if (m_tIvpsGrpCfg.eGrpEngineType0 != AX_IVPS_ENGINE_BUTT) {
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].bEngage = AX_TRUE;
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].nDstPicWidth = m_tIvpsGrpCfg.arrGrpResolution[0];
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].nDstPicHeight = m_tIvpsGrpCfg.arrGrpResolution[1];
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].nDstPicStride =
            ALIGN_UP(m_tIvpsGrpCfg.arrGrpResolution[0], AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL);
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tFRC.fSrcFrameRate = m_tIvpsGrpCfg.arrGrpFramerate[0];
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tFRC.fDstFrameRate = m_tIvpsGrpCfg.arrGrpFramerate[1];
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tCompressInfo.enCompressMode = (AX_COMPRESS_MODE_E)m_tIvpsGrpCfg.arrGrpFBC[0];
        m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tCompressInfo.u32CompressLevel = m_tIvpsGrpCfg.arrGrpFBC[1];

        if (AX_IVPS_ENGINE_GDC == m_tIvpsGrp.tPipelineAttr.tFilter[0][0].eEngine) {
            m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tGdcCfg.eDewarpType = AX_IVPS_DEWARP_BYPASS;
        } else if (AX_IVPS_ENGINE_TDP == m_tIvpsGrp.tPipelineAttr.tFilter[0][0].eEngine) {
            m_tIvpsGrp.tPipelineAttr.tFilter[0][0].bInplace = m_tIvpsGrpCfg.arrGrpInplace[0];
        }
        m_arrChnResolution[0][0] = m_tIvpsGrpCfg.arrGrpResolution[0];
        m_arrChnResolution[0][1] = m_tIvpsGrpCfg.arrGrpResolution[1];
        LOG_M(IVPS, "[%d] Grp filter 0x00: engine:%d, w:%d, h:%d, s:%d, frameRate[%f,%f]", m_tIvpsGrp.nGroup, m_tIvpsGrpCfg.eGrpEngineType0,
              m_tIvpsGrp.tPipelineAttr.tFilter[0][0].nDstPicWidth, m_tIvpsGrp.tPipelineAttr.tFilter[0][0].nDstPicHeight,
              m_tIvpsGrp.tPipelineAttr.tFilter[0][0].nDstPicStride, m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tFRC.fSrcFrameRate,
              m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tFRC.fDstFrameRate);
    }

    /* Config group filter 1 */
    m_tIvpsGrp.tPipelineAttr.tFilter[0][1].eEngine = m_tIvpsGrpCfg.eGrpEngineType1;
    if (m_tIvpsGrpCfg.eGrpEngineType1 != AX_IVPS_ENGINE_BUTT) {
        m_tIvpsGrp.tPipelineAttr.tFilter[0][1].bEngage = AX_TRUE;
        m_tIvpsGrp.tPipelineAttr.tFilter[0][1].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        m_tIvpsGrp.tPipelineAttr.tFilter[0][1].nDstPicWidth =
            m_tIvpsGrpCfg.arrGrpResolution[0]; /* Group filter 1 has not ability of resizing, just use group filter0's out resolution */
        m_tIvpsGrp.tPipelineAttr.tFilter[0][1].nDstPicHeight = m_tIvpsGrpCfg.arrGrpResolution[1];
        m_tIvpsGrp.tPipelineAttr.tFilter[0][1].nDstPicStride =
            ALIGN_UP(m_tIvpsGrpCfg.arrGrpResolution[0], AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL);
        m_tIvpsGrp.tPipelineAttr.tFilter[0][1].tCompressInfo.enCompressMode = (AX_COMPRESS_MODE_E)m_tIvpsGrpCfg.arrGrpFBC[0];
        m_tIvpsGrp.tPipelineAttr.tFilter[0][1].tCompressInfo.u32CompressLevel = m_tIvpsGrpCfg.arrGrpFBC[1];

        if (AX_IVPS_ENGINE_VPP == m_tIvpsGrp.tPipelineAttr.tFilter[0][1].eEngine) {
            m_tIvpsGrp.tPipelineAttr.tFilter[0][1].bInplace = m_tIvpsGrpCfg.arrGrpInplace[1];
        }

        m_arrChnResolution[0][0] = m_tIvpsGrpCfg.arrGrpResolution[0];
        m_arrChnResolution[0][1] = m_tIvpsGrpCfg.arrGrpResolution[1];
        LOG_M(IVPS, "[%d] Grp filter 0x01: engine:%d, w:%d, h:%d, s:%d, frameRate[%f,%f]", m_tIvpsGrp.nGroup, m_tIvpsGrpCfg.eGrpEngineType1,
              m_tIvpsGrp.tPipelineAttr.tFilter[0][1].nDstPicWidth, m_tIvpsGrp.tPipelineAttr.tFilter[0][1].nDstPicHeight,
              m_tIvpsGrp.tPipelineAttr.tFilter[0][1].nDstPicStride, m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tFRC.fSrcFrameRate,
              m_tIvpsGrp.tPipelineAttr.tFilter[0][0].tFRC.fDstFrameRate);
    }

    /* Config channel filter 0 */
    for (AX_U8 i = 0; i < m_tIvpsGrpCfg.nGrpChnNum; i++) {
        if (m_tIvpsGrpCfg.arrChnEngineType0[i] != AX_IVPS_ENGINE_BUTT) {
            AX_U8 nChnFilter = i + 1;
            auto& tFilter0 = m_tIvpsGrp.tPipelineAttr.tFilter[nChnFilter][0];

            tFilter0.bEngage = AX_TRUE;
            tFilter0.eEngine = m_tIvpsGrpCfg.arrChnEngineType0[i];
            tFilter0.eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;

            if (tFilter0.eEngine == AX_IVPS_ENGINE_TDP) {
                tFilter0.bInplace = m_tIvpsGrpCfg.arrChnInplace[i][0];
            } else if (tFilter0.eEngine == AX_IVPS_ENGINE_VPP) {
                tFilter0.bInplace = m_tIvpsGrpCfg.arrChnInplace[i][0];
            } else if (tFilter0.eEngine == AX_IVPS_ENGINE_SCL) {
                tFilter0.eSclType = (AX_IVPS_SCL_TYPE_E)m_tIvpsGrpCfg.arrChnSCL[i];
            }

            tFilter0.nDstPicWidth = m_tIvpsGrpCfg.arrChnResolution[i][0];
            tFilter0.nDstPicHeight = m_tIvpsGrpCfg.arrChnResolution[i][1];
            tFilter0.tFRC.fSrcFrameRate = (m_tIvpsGrpCfg.arrChnFramerate[i][0]);
            tFilter0.tFRC.fDstFrameRate = (m_tIvpsGrpCfg.arrChnFramerate[i][1]);
            tFilter0.tCompressInfo.enCompressMode = (AX_COMPRESS_MODE_E)m_tIvpsGrpCfg.arrChnFBC[i][0];
            tFilter0.tCompressInfo.u32CompressLevel = m_tIvpsGrpCfg.arrChnFBC[i][1];

            /* Update compress info */
            UpdateCompressInfo(tFilter0.tCompressInfo, tFilter0.nDstPicWidth);

            AX_U32 nStride =
                tFilter0.tCompressInfo.enCompressMode > AX_COMPRESS_MODE_NONE ? AX_IVPS_FBC_STRIDE_ALIGN_VAL : AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL;
            tFilter0.nDstPicStride = ALIGN_UP(tFilter0.nDstPicWidth, nStride);

            m_arrChnResolution[i][0] = m_tIvpsGrpCfg.arrChnResolution[i][0];
            m_arrChnResolution[i][1] = m_tIvpsGrpCfg.arrChnResolution[i][1];
            LOG_MM(IVPS, "[%d][%d] ChnFilter0 0x%02x: engine:%d, w:%d, h:%d, s:%d,frameRate[%f,%f]", m_tIvpsGrp.nGroup, i,
                   (nChnFilter << 4) + 1, m_tIvpsGrpCfg.arrChnEngineType0[i], tFilter0.nDstPicWidth, tFilter0.nDstPicHeight,
                   tFilter0.nDstPicStride, m_tIvpsGrpCfg.arrChnFramerate[i][0], m_tIvpsGrpCfg.arrChnFramerate[i][1]);
        }
    }

    /* Config channel filter 1 */
    for (AX_U8 i = 0; i < m_tIvpsGrpCfg.nGrpChnNum; i++) {
        if (m_tIvpsGrpCfg.arrChnEngineType1[i] != AX_IVPS_ENGINE_BUTT) {
            AX_U8 nChnFilter = i + 1;
            auto& tFilter0 = m_tIvpsGrp.tPipelineAttr.tFilter[nChnFilter][0];
            auto& tFilter1 = m_tIvpsGrp.tPipelineAttr.tFilter[nChnFilter][1];
            tFilter1.bEngage = AX_TRUE;
            tFilter1.eEngine = m_tIvpsGrpCfg.arrChnEngineType1[i];
            tFilter1.eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
            tFilter1.nDstPicWidth = m_tIvpsGrpCfg.arrChnResolution[i][0];
            tFilter1.nDstPicHeight = m_tIvpsGrpCfg.arrChnResolution[i][1];
            if (!tFilter0.bEngage) {
                /* Make sure only one frameCtrl for channel filter */
                tFilter1.tFRC.fSrcFrameRate = m_tIvpsGrpCfg.arrChnFramerate[i][0];
                tFilter1.tFRC.fDstFrameRate = m_tIvpsGrpCfg.arrChnFramerate[i][1];
            }

            tFilter1.tCompressInfo.enCompressMode = (AX_COMPRESS_MODE_E)m_tIvpsGrpCfg.arrChnFBC[i][0];
            tFilter1.tCompressInfo.u32CompressLevel = m_tIvpsGrpCfg.arrChnFBC[i][1];

            /* Update compress info */
            UpdateCompressInfo(tFilter1.tCompressInfo, tFilter1.nDstPicWidth);

            AX_U32 nStride =
                tFilter1.tCompressInfo.enCompressMode > AX_COMPRESS_MODE_NONE ? AX_IVPS_FBC_STRIDE_ALIGN_VAL : AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL;
            tFilter1.nDstPicStride = ALIGN_UP(tFilter1.nDstPicWidth, nStride);

            m_arrChnResolution[i][0] = m_tIvpsGrpCfg.arrChnResolution[i][0];
            m_arrChnResolution[i][1] = m_tIvpsGrpCfg.arrChnResolution[i][1];
            if (tFilter1.eEngine == AX_IVPS_ENGINE_TDP) {
                tFilter1.bInplace = m_tIvpsGrpCfg.arrChnInplace[i][1];
                tFilter1.tTdpCfg.bVoOsd = m_tIvpsGrpCfg.bArrChnVoOsdFlag[i];
            } else if (tFilter1.eEngine == AX_IVPS_ENGINE_VPP) {
                tFilter1.bInplace = m_tIvpsGrpCfg.arrChnInplace[i][1];
            }

            LOG_MM(IVPS, "[%d][%d] ChnFilter1 0x%02x: engine:%d, w:%d, h:%d, s:%d,frameRate[%f,%f]", m_tIvpsGrp.nGroup, i,
                   (nChnFilter << 4) + 1, m_tIvpsGrpCfg.arrChnEngineType1[i], tFilter1.nDstPicWidth, tFilter1.nDstPicHeight,
                   tFilter1.nDstPicStride, m_tIvpsGrpCfg.arrChnFramerate[i][0], m_tIvpsGrpCfg.arrChnFramerate[i][1]);
        }
    }

    return AX_TRUE;
}

AX_VOID CIVPSGrpStage::SetChnInplace(AX_S32 nChannel, AX_BOOL bEnable) {
    AX_S32 nChnFilter = nChannel + 1;
    m_tIvpsGrp.tPipelineAttr.tFilter[nChnFilter][1].bInplace = bEnable;
}

AX_VOID CIVPSGrpStage::RegObserver(AX_S32 nChannel, IObserver* pObserver) {
    if (nullptr != pObserver) {
        OBS_TRANS_ATTR_T tTransAttr;
        tTransAttr.fSrcFramerate = m_tIvpsGrpCfg.arrChnFramerate[nChannel][0]; /*0: src framerate*/
        tTransAttr.fFramerate = m_tIvpsGrpCfg.arrChnFramerate[nChannel][1];    /* 1: Out framerate */
        tTransAttr.nWidth = m_tIvpsGrpCfg.arrChnResolution[nChannel][0];
        tTransAttr.nHeight = m_tIvpsGrpCfg.arrChnResolution[nChannel][1];
        tTransAttr.bEnableFBC = m_tIvpsGrpCfg.arrChnFBC[nChannel][0] == 0 ? AX_FALSE : AX_TRUE;
        tTransAttr.bLink = m_tIvpsGrpCfg.arrChnLinkFlag[nChannel] == 0 ? AX_FALSE : AX_TRUE;
        tTransAttr.nSnsSrc = m_tIvpsGrpCfg.nSnsSrc;
        if (pObserver->OnRegisterObserver(E_OBS_TARGET_TYPE_IVPS, m_nIvpsGrp, nChannel, &tTransAttr)) {
            std::lock_guard<std::mutex> lock(m_mtxObserver);
            auto& vecObserver = m_mapChnObserver[nChannel];
            vecObserver.emplace_back(pObserver);
        }
    }
}

AX_VOID CIVPSGrpStage::UnregObserver(AX_S32 nChannel, IObserver* pObserver) {
    if (nullptr == pObserver) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mtxObserver);
    auto& vecObserver = m_mapChnObserver[nChannel];
    for (vector<IObserver*>::iterator it = vecObserver.begin(); it != vecObserver.end(); it++) {
        if (*it == pObserver) {
            vecObserver.erase(it);
            break;
        }
    }
}

AX_VOID CIVPSGrpStage::NotifyAll(AX_U32 nGrp, AX_U32 nChn, CAXFrame* pFrame) {
    std::lock_guard<std::mutex> lock(m_mtxObserver);
    auto& vecObserver = m_mapChnObserver[nChn];
    if (vecObserver.empty()) {
        pFrame->FreeMem();
        return;
    }

    if (!pFrame->bMultiplex) {
        pFrame->IncFrmRef();
    }
    pFrame->bMultiplex = AX_TRUE;
    for (auto it : vecObserver) {
        pFrame->IncFrmRef();
        it->OnRecvData(E_OBS_TARGET_TYPE_IVPS, m_nIvpsGrp, nChn, pFrame);
    }
    pFrame->FreeMem();
}

AX_BOOL CIVPSGrpStage::EnableChannel(AX_U8 nChn, AX_BOOL bEnable /*= AX_TRUE*/) {
    std::lock_guard<std::mutex> lck(m_mutxRecv[nChn]);
    AX_S32 nRet = AX_SUCCESS;
    if (bEnable) {
        nRet = AX_IVPS_EnableChn(m_tIvpsGrpCfg.nGrp, nChn);
        if (AX_SUCCESS != nRet) {
            LOG_M_E(IVPS, "AX_IVPS_EnableChn(Grp:%d, Chn:%d) failed, ret=0x%x", m_tIvpsGrpCfg.nGrp, nChn, nRet);
            return AX_FALSE;
        } else {
            LOG_M(IVPS, "AX_IVPS_EnableChn(Grp:%d, Chn:%d) successfully", m_tIvpsGrpCfg.nGrp, nChn);
        }
    } else {
        nRet = AX_IVPS_DisableChn(m_tIvpsGrpCfg.nGrp, nChn);
        if (AX_SUCCESS != nRet) {
            LOG_M_E(IVPS, "AX_IVPS_DisableChn(Grp:%d, Chn:%d) failed, ret=0x%x", m_tIvpsGrpCfg.nGrp, nChn, nRet);
            return AX_FALSE;
        } else {
            LOG_M(IVPS, "AX_IVPS_DisableChn(Grp:%d, Chn:%d) successfully", m_tIvpsGrpCfg.nGrp, nChn);
        }
    }
    m_tGetThreadParam[nChn].nChnEnable = bEnable;
    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::UpdateRotationResolution(AX_IVPS_ROTATION_E eRotation, AX_U8 nChn, AX_U32 nWidth, AX_U32 nHeight) {
    AX_U32 nStrideAlign = 0;
    AX_IVPS_GetPipelineAttr(m_tIvpsGrpCfg.nGrp, &m_tIvpsGrp.tPipelineAttr);
    AX_IVPS_PIPELINE_ATTR_T& tPipelineAttr = m_tIvpsGrp.tPipelineAttr;

    AX_COMPRESS_MODE_E enCompressMode = (AX_COMPRESS_MODE_E)m_tIvpsGrpCfg.arrChnFBC[nChn][0];
    AX_U32 u32CompressLevel = m_tIvpsGrpCfg.arrChnFBC[nChn][1];

    tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.enCompressMode = enCompressMode;
    tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.u32CompressLevel = u32CompressLevel;

    /* Update compress info */
    UpdateCompressInfo(tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo, nWidth);
    tPipelineAttr.tFilter[nChn + 1][1].tCompressInfo = tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo;

    AX_BOOL bFBC = tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.enCompressMode > AX_COMPRESS_MODE_NONE ? AX_TRUE : AX_FALSE;

    if (0 == nChn) {
        /* Update Grp filter0 resolution */
        if (tPipelineAttr.tFilter[0][0].bEngage) {
            nStrideAlign = bFBC ? AX_IVPS_FBC_STRIDE_ALIGN_VAL : AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL;
            tPipelineAttr.tFilter[0][0].nDstPicWidth = nWidth;
            tPipelineAttr.tFilter[0][0].nDstPicHeight = nHeight;

            tPipelineAttr.tFilter[0][0].nDstPicStride = ALIGN_UP(nWidth, nStrideAlign);
            LOG_MM_C(IVPS, "GrpFilter0 Reset resolution for ivps (Grp: %d): w: %d, h: %d, s: %d compress[%d,%d].", m_tIvpsGrpCfg.nGrp,
                     tPipelineAttr.tFilter[0][0].nDstPicWidth, tPipelineAttr.tFilter[0][0].nDstPicHeight,
                     tPipelineAttr.tFilter[0][0].nDstPicStride, tPipelineAttr.tFilter[0][0].tCompressInfo.enCompressMode,
                     tPipelineAttr.tFilter[0][0].tCompressInfo.u32CompressLevel);
        }
        /* Update Grp filter1 resolution */
        if (tPipelineAttr.tFilter[0][1].bEngage) {
            nStrideAlign = bFBC ? AX_IVPS_FBC_STRIDE_ALIGN_VAL : AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL;
            tPipelineAttr.tFilter[0][1].nDstPicWidth = nWidth;
            tPipelineAttr.tFilter[0][1].nDstPicHeight = nHeight;

            tPipelineAttr.tFilter[0][1].nDstPicStride = ALIGN_UP(nWidth, nStrideAlign);
            LOG_MM_C(IVPS, "GrpFilter1 Reset resolution for ivps (Grp: %d): w: %d, h: %d, s: %d compress[%d,%d].", m_tIvpsGrpCfg.nGrp,
                     tPipelineAttr.tFilter[0][1].nDstPicWidth, tPipelineAttr.tFilter[0][1].nDstPicHeight,
                     tPipelineAttr.tFilter[0][1].nDstPicStride, tPipelineAttr.tFilter[0][0].nDstPicStride,
                     tPipelineAttr.tFilter[0][1].tCompressInfo.enCompressMode, tPipelineAttr.tFilter[0][1].tCompressInfo.u32CompressLevel);
        }
    }
    /* Update resolution of channel filter 0 */
    if (tPipelineAttr.tFilter[nChn + 1][0].bEngage) {
        nStrideAlign = bFBC ? AX_IVPS_FBC_STRIDE_ALIGN_VAL : AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL;

        tPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth = nWidth;
        tPipelineAttr.tFilter[nChn + 1][0].nDstPicHeight = nHeight;
        tPipelineAttr.tFilter[nChn + 1][0].nDstPicStride = ALIGN_UP(nWidth, nStrideAlign);

        LOG_MM_C(IVPS, "ChnFilter0 reset resolution for ivps (Grp: %d, Chn: %d): w: %d, h: %d, s: %d strdeAlign:%d, widthAlign:%d.",
                 m_tIvpsGrpCfg.nGrp, nChn, tPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth,
                 tPipelineAttr.tFilter[nChn + 1][0].nDstPicHeight, tPipelineAttr.tFilter[nChn + 1][0].nDstPicStride, nStrideAlign,
                 AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL);
    }

    /* Update resolution of channel filter 1 */
    if (tPipelineAttr.tFilter[nChn + 1][1].bEngage) {
        nStrideAlign = bFBC ? AX_IVPS_FBC_STRIDE_ALIGN_VAL : AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL;

        tPipelineAttr.tFilter[nChn + 1][1].nDstPicWidth = nWidth;
        tPipelineAttr.tFilter[nChn + 1][1].nDstPicHeight = nHeight;
        tPipelineAttr.tFilter[nChn + 1][1].nDstPicStride = ALIGN_UP(nWidth, nStrideAlign);

        LOG_MM_C(IVPS, "ChnFilter1 reset resolution for ivps (Grp: %d, Chn: %d): w: %d, h: %d, s: %d strdeAlign:%d, widthAlign:%d.",
                 m_tIvpsGrpCfg.nGrp, nChn, tPipelineAttr.tFilter[nChn + 1][1].nDstPicWidth,
                 tPipelineAttr.tFilter[nChn + 1][1].nDstPicHeight, tPipelineAttr.tFilter[nChn + 1][1].nDstPicStride, nStrideAlign,
                 AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL);
    }

    AX_S32 nRet = AX_IVPS_SetPipelineAttr(m_tIvpsGrpCfg.nGrp, &tPipelineAttr);
    if (AX_SUCCESS != nRet) {
        LOG_M_E(IVPS, "AX_IVPS_SetPipelineAttr(Grp %d) failed, ret=0x%x", m_tIvpsGrpCfg.nGrp, nRet);
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::UpdateChnResolution(AX_U8 nChn, AX_S32 nWidth, AX_S32 nHeight) {
    AX_IVPS_GetPipelineAttr(m_tIvpsGrpCfg.nGrp, &m_tIvpsGrp.tPipelineAttr);
    AX_IVPS_PIPELINE_ATTR_T& tPipelineAttr = m_tIvpsGrp.tPipelineAttr;

    AX_COMPRESS_MODE_E enCompressMode = (AX_COMPRESS_MODE_E)m_tIvpsGrpCfg.arrChnFBC[nChn][0];
    AX_U32 u32CompressLevel = m_tIvpsGrpCfg.arrChnFBC[nChn][1];

    tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.enCompressMode = enCompressMode;
    tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.u32CompressLevel = u32CompressLevel;

    /* Update compress info */
    UpdateCompressInfo(tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo, nWidth);
    tPipelineAttr.tFilter[nChn + 1][1].tCompressInfo = tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo;

    AX_BOOL bFBC = tPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.enCompressMode > AX_COMPRESS_MODE_NONE ? AX_TRUE : AX_FALSE;
    AX_U32 nStrideAlign = bFBC ? AX_IVPS_FBC_STRIDE_ALIGN_VAL : AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL;

    m_arrChnResolution[nChn][0] = nWidth;
    m_arrChnResolution[nChn][1] = nHeight;

    if (AX_IVPS_ROTATION_90 == m_eRotation || AX_IVPS_ROTATION_270 == m_eRotation) {
        std::swap(nWidth, nHeight);
    }

    if (AX_FALSE == tPipelineAttr.tFilter[nChn + 1][0].bEngage) {
        /* Enable channel filter 0 */
        tPipelineAttr.tFilter[nChn + 1][0].bEngage = AX_TRUE;
        tPipelineAttr.tFilter[nChn + 1][0].eEngine = AX_IVPS_ENGINE_VPP;

        tPipelineAttr.tFilter[nChn + 1][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        tPipelineAttr.tFilter[nChn + 1][0].bInplace = AX_FALSE;
        tPipelineAttr.tFilter[nChn + 1][0].tFRC.fSrcFrameRate = tPipelineAttr.tFilter[nChn + 1][1].tFRC.fSrcFrameRate;
        tPipelineAttr.tFilter[nChn + 1][0].tFRC.fDstFrameRate = tPipelineAttr.tFilter[nChn + 1][1].tFRC.fSrcFrameRate;
    }

    /* Update resolution of channel filter 0 */
    tPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth = nWidth;
    tPipelineAttr.tFilter[nChn + 1][0].nDstPicHeight = nHeight;
    tPipelineAttr.tFilter[nChn + 1][0].nDstPicStride = ALIGN_UP(nWidth, nStrideAlign);

    /* Update resolution of channel filter 1 */
    tPipelineAttr.tFilter[nChn + 1][1].nDstPicWidth = nWidth;
    tPipelineAttr.tFilter[nChn + 1][1].nDstPicHeight = nHeight;
    tPipelineAttr.tFilter[nChn + 1][1].nDstPicStride = ALIGN_UP(nWidth, nStrideAlign);

    LOG_MM(IVPS, "ChnFilter reset resolution for ivps (Grp: %d, Chn: %d): w: %d, h: %d, s: %d WIDTH_STRIDE:%d nStrideAlign:%d.",
           m_tIvpsGrpCfg.nGrp, nChn, tPipelineAttr.tFilter[nChn + 1][1].nDstPicWidth, tPipelineAttr.tFilter[nChn + 1][1].nDstPicHeight,
           tPipelineAttr.tFilter[nChn + 1][1].nDstPicStride, AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL, nStrideAlign);

    AX_S32 nRet = AX_IVPS_SetPipelineAttr(m_tIvpsGrpCfg.nGrp, &tPipelineAttr);
    if (AX_SUCCESS != nRet) {
        LOG_M_E(IVPS, "AX_IVPS_SetPipelineAttr(Grp %d) failed, ret=0x%x", m_tIvpsGrpCfg.nGrp, nRet);
        return AX_FALSE;
    }
    m_tIvpsGrpCfg.arrChnResolution[nChn][0] = tPipelineAttr.tFilter[nChn + 1][1].nDstPicWidth;
    m_tIvpsGrpCfg.arrChnResolution[nChn][1] = tPipelineAttr.tFilter[nChn + 1][1].nDstPicHeight;

    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::UpdateRotation(AX_IVPS_ROTATION_E eRotation) {
    if (!m_bEnableRotation) {
        LOG_MM_W(IVPS, "[%d] don't have to rotation.", m_nIvpsGrp);
        return AX_TRUE;
    }
    LOG_MM_I(IVPS, "UpdateRotation+++ nGrp:%d, eRotation:%d", m_tIvpsGrpCfg.nGrp, eRotation);
    std::lock_guard<std::mutex> lck(m_mutxSend);
    if (!ClearQueue()) {
        LOG_MM_W(IVPS, "[%d] CAXStage clear lockQueue Failed.", m_tIvpsGrpCfg.nGrp);
    }
    AX_IVPS_PIPELINE_ATTR_T& tPipelineAttr = m_tIvpsGrp.tPipelineAttr;
    AX_U8 nOutChnNum = tPipelineAttr.nOutChnNum;
    for (AX_U8 nChn = 0; nChn < nOutChnNum; nChn++) {
        AX_U32 nNewWidth = 0;
        AX_U32 nNewHeight = 0;
        if (!GetResolutionByRotate(nChn, eRotation, nNewWidth, nNewHeight)) {
            LOG_MM_E(IVPS, "[%d][%d] Can not get new resolution for rotate operation.", m_tIvpsGrpCfg.nGrp, nChn);
            continue;
        }
        if (AX_FALSE == m_tIvpsGrpCfg.nMaskEnable) {
            UpdateRotationResolution(eRotation, nChn, nNewWidth, nNewHeight);
        }

        m_eRotation = eRotation;
    }
    LOG_MM_I(IVPS, "UpdateRotation--- nGrp:%d, eRotation:%d", m_tIvpsGrpCfg.nGrp, eRotation);

    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::UpdateGrpLDC(AX_BOOL bLdcEnable, AX_BOOL bAspect, AX_S16 nXRatio, AX_S16 nYRatio, AX_S16 nXYRatio,
                                    AX_S16 nDistorRatio) {
    AX_IVPS_PIPELINE_ATTR_T& tPipelineAttr = m_tIvpsGrp.tPipelineAttr;
    if (AX_IVPS_ENGINE_GDC == tPipelineAttr.tFilter[0][0].eEngine) {
        if (bLdcEnable) {
            tPipelineAttr.tFilter[0][0].tGdcCfg.eDewarpType = AX_IVPS_DEWARP_LDC;
            tPipelineAttr.tFilter[0][0].tGdcCfg.tLdcAttr.bAspect = bAspect;
            tPipelineAttr.tFilter[0][0].tGdcCfg.tLdcAttr.nXRatio = nXRatio;
            tPipelineAttr.tFilter[0][0].tGdcCfg.tLdcAttr.nYRatio = nYRatio;
            tPipelineAttr.tFilter[0][0].tGdcCfg.tLdcAttr.nXYRatio = nXYRatio;
            tPipelineAttr.tFilter[0][0].tGdcCfg.tLdcAttr.nDistortionRatio = nDistorRatio;
        } else {
            tPipelineAttr.tFilter[0][0].tGdcCfg.eDewarpType = AX_IVPS_DEWARP_BYPASS;
        }

        AX_S32 nRet = AX_IVPS_SetPipelineAttr(m_tIvpsGrpCfg.nGrp, &tPipelineAttr);
        if (AX_SUCCESS != nRet) {
            LOG_MM_E(IVPS, "AX_IVPS_SetPipelineAttr(Grp %d) failed, ret=0x%x", m_tIvpsGrpCfg.nGrp, nRet);
            return AX_FALSE;
        }

        return AX_TRUE;
    } else {
        return AX_FALSE;
    }
}

AX_BOOL CIVPSGrpStage::UpdateChnFRC(AX_F32 fSnsCurFrameRate, AX_F32 fSnsFrameRate) {
    for (AX_U8 i = 0; i < m_tIvpsGrpCfg.nGrpChnNum; i++) {
        AX_U8 nChnFilter = 0;
        AX_IVPS_CHN_ATTR_T tChnAttr;
        // chn filter0
        if (m_tIvpsGrpCfg.arrChnEngineType0[i] != AX_IVPS_ENGINE_BUTT) {
            AX_S32 nRet = AX_IVPS_GetChnAttr(m_tIvpsGrpCfg.nGrp, i, nChnFilter, &tChnAttr);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(IVPS, "AX_IVPS_GetChnAttr[%d %d]  failed, ret=0x%x", m_tIvpsGrpCfg.nGrp, i, nRet);
                return AX_FALSE;
            }

            if (tChnAttr.tFRC.fSrcFrameRate == tChnAttr.tFRC.fDstFrameRate && fSnsCurFrameRate == tChnAttr.tFRC.fSrcFrameRate) {
                tChnAttr.tFRC.fSrcFrameRate = tChnAttr.tFRC.fDstFrameRate = fSnsFrameRate;
            } else if (fSnsCurFrameRate == tChnAttr.tFRC.fSrcFrameRate) {
                tChnAttr.tFRC.fSrcFrameRate = fSnsFrameRate;
            }
            LOG_MM_I(IVPS, "nGrp:%d, nChn:%d, filter:%d, [%f %f]", m_tIvpsGrpCfg.nGrp, i, nChnFilter, tChnAttr.tFRC.fSrcFrameRate,
                     tChnAttr.tFRC.fDstFrameRate);
            nRet = AX_IVPS_SetChnAttr(m_tIvpsGrpCfg.nGrp, i, nChnFilter, &tChnAttr);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(IVPS, "AX_IVPS_SetChnAttr[%d %d] failed, ret=0x%x", m_tIvpsGrpCfg.nGrp, i, nRet);
                return AX_FALSE;
            } else {
                LOG_MM_D(IVPS, "AX_IVPS_SetChnAttr[%d %d] success", m_tIvpsGrpCfg.nGrp, i);
            }
        }
    }

    return AX_TRUE;
}

AX_VOID CIVPSGrpStage::RefreshOSDByResChange() {
    if (m_pOsdHelper) {
        m_pOsdHelper->Refresh();
    }
}

AX_BOOL CIVPSGrpStage::GetCurResolution(AX_U8 nChn, AX_U32& nWidth, AX_U32& nHeight) {
    return GetResolutionByRotate(nChn, m_eRotation, nWidth, nHeight);
}
AX_BOOL CIVPSGrpStage::GetResolutionByRotate(AX_U8 nChn, AX_IVPS_ROTATION_E eRotation, AX_U32& nWidth, AX_U32& nHeight) {
    nWidth = m_arrChnResolution[nChn][0];
    nHeight = m_arrChnResolution[nChn][1];

    if (AX_IVPS_ROTATION_90 == eRotation || AX_IVPS_ROTATION_270 == eRotation) {
        std::swap(nWidth, nHeight);
    }

    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::StartOSD() {
    LOG_MM_I(IVPS, "[%d]StartOSD ...", m_tIvpsGrpCfg.nGrp);
    if (m_pOsdHelper && !m_pOsdHelper->StartOSD(this)) {
        LOG_M_E(IVPS, "Start OSD failed.");
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CIVPSGrpStage::StopOSD() {
    LOG_MM_C(IVPS, "[%d] +++", m_tIvpsGrpCfg.nGrp);

    if (m_pOsdHelper && !m_pOsdHelper->StopOSD()) {
        LOG_M_E(IVPS, "Stop OSD failed.");
        return AX_FALSE;
    }
    LOG_MM_C(IVPS, "[%d] ---", m_tIvpsGrpCfg.nGrp);
    return AX_TRUE;
}

AX_VOID CIVPSGrpStage::UpdateCompressInfo(AX_FRAME_COMPRESS_INFO_T& tCompressInfo, AX_U16 nChnWidth) {
    SENSOR_CONFIG_T tSensorCfg;
    APP_SENSOR_CONFIG(m_tIvpsGrpCfg.nSnsSrc, tSensorCfg);

    if (tCompressInfo.enCompressMode > AX_COMPRESS_MODE_NONE) {
        if (nChnWidth < g_ivps_nMinFBCWidth
            // AX620E TODO: WA
            || (tSensorCfg.arrPipeAttr[0].arrChannelAttr[0].nWidth >= 3840 && nChnWidth <= g_ivps_nMinFBCWidthFor4K)) {
            tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
            tCompressInfo.u32CompressLevel = 0;
        }
    }
}
