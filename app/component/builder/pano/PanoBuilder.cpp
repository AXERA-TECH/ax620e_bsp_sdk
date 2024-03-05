/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include "PanoBuilder.h"

#include "AXTypeConverter.hpp"
#include "AlgoOptionHelper.h"
#include "AppLogApi.h"
#include "ax_engine_api.h"
#include "ax_venc_api.h"
#ifdef JDEC_SUPPORT
#include "ax_vdec_api.h"
#endif
#include "CaptureObserver.hpp"
#include "CmdLineParser.h"
#include "CollectorObserver.h"
#include "CommonUtils.hpp"
#include "DetectObserver.hpp"
#include "DummyEncoderObserver.h"
#include "EncoderOptionHelper.h"
#include "GlobalDef.h"
#include "IvesObserver.hpp"
#include "IvpsObserver.h"
#include "IvpsOptionHelper.h"
#include "JencObserver.h"
#include "OSDHandler.h"
#include "OSDHelper.h"
#include "OptionHelper.h"
#include "OsdObserver.h"
#include "PrintHelper.h"
#include "SensorOptionHelper.h"
#include "VencObserver.h"
#include "WebOptionHelper.h"
#ifndef SLT
#include "AXRtspObserver.h"
#include "AXRtspServer.h"
#include "AudioOptionHelper.h"
#include "AudioWrapper.hpp"
#include "WebObserver.h"
#include "WebServer.h"
#endif  // SLT

#ifdef MP4ENC_SUPPORT
#include "MpegObserver.h"
#endif

#include "AvsOptionHelper.h"

#define PPL "PANO_PPL"

#define PANO_VENC_MAX_WIDTH  (5120)
#define PANO_VENC_MAX_HEIGHT (1520)

#define APP_VIN_STITCH_GRP (0)

#ifndef SLT
namespace {
AX_VOID AudioPlayCallback(AX_APP_AUDIO_CHAN_E eChan, const AX_APP_AUDIO_PLAY_FILE_RESULT_PTR pstResult) {
    if (pstResult) {
        LOG_MM(PPL, "[%d] %s play complete, status: %d", eChan, pstResult->pstrFileName, pstResult->eStatus);
    }
}
}  // namespace
#endif  // SLT

AX_BOOL CPanoBuilder::Init(AX_VOID) {
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::Deinit(AX_VOID) {
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::BindPPLConfig(IPPLConfig* pPPLConfig) {
    m_pPPLConfig = pPPLConfig;

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::BindTestSuite(CTestSuite* pTestSuite) {
    m_pTestSuite = pTestSuite;

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::Construct(AX_VOID) {
    LOG_MM(PPL, "+++");
    /* Step-1: Global initialization */
    if (AX_FALSE == InitSysMods()) {
        return AX_FALSE;
    }

    if (!CCmdLineParser::GetInstance()->GetScenario(m_nScenario)) {
        LOG_MM(PPL, "Apply default scenario %d.", m_nScenario);
    }

    /* Step-2: Linkage initialization */
    if (m_linkage.Setup()) {
        LOG_MM_W(PPL, "Linkage setup.");
    } else {
        LOG_MM_W(PPL, "No linkage setup.");
    }

    /*Step-3: Sensor initialize */
    if (AX_FALSE == InitSensor()) {
        LOG_MM_E(PPL, "Initailize SensorMgr failed.");
        return AX_FALSE;
    }

#ifndef SLT
    /*Step-4: Audio initialize */
    if (AX_FALSE == InitAudio()) {
        LOG_MM_E(PPL, "Initailize Audio failed.");
        return AX_FALSE;
    }
#endif  // SLT

    /*Step-5: AVS initialize, make sure init before ivps*/
    if (AX_FALSE == InitAvs()) {
        LOG_MM_E(PPL, "Initailize AVS failed.");
        return AX_FALSE;
    }

    /*Step-6: Ivps initialize */
    if (AX_FALSE == InitIvps()) {
        LOG_MM_E(PPL, "Initailize Ivps failed.");
        return AX_FALSE;
    }

    /*Step-7: venc initialize */
    if (AX_FALSE == InitVenc()) {
        LOG_MM_E(PPL, "Initailize Venc failed.");
        return AX_FALSE;
    }

    /*Step-8: capture initialize */
    if (AX_FALSE == InitCapture()) {
        LOG_MM_E(PPL, "Initailize capture failed.");
        return AX_FALSE;
    }

    /*Step-9: collector initialize */
    if (AX_FALSE == InitCollector()) {
        LOG_MM_E(PPL, "Initailize Ivps failed.");
        return AX_FALSE;
    }

    /*Step-10: jenc initialize */
    if (AX_FALSE == InitJenc()) {
        LOG_MM_E(PPL, "Initailize Jenc failed.");
        return AX_FALSE;
    }

    /*Step-11: detector initialize */
    if (AX_FALSE == InitDetector()) {
        LOG_MM_E(PPL, "Initailize detector failed.");
        return AX_FALSE;
    }

    /*Step-12: ives initialize */
    if (AX_FALSE == InitIves()) {
        LOG_MM_E(PPL, "Initailize ives failed.");
        return AX_FALSE;
    }

    /*Step-13: dummy encoder initialize */
    if (AX_FALSE == InitDummyEnc()) {
        LOG_MM_E(PPL, "Initailize dummy encoder failed.");
        return AX_FALSE;
    }

    /*Step-14: PPL pool initialize */
    if (AX_FALSE == InitPoolConfig()) {
        LOG_MM_E(PPL, "Initailize Pool failed.");
        return AX_FALSE;
    }

#ifndef SLT
    /* Step-15: Initialize RTSP */
    if (!CAXRtspServer::GetInstance()->Init()) {
        return AX_FALSE;
    }
    LOG_M_I(PPL, "Init Rtsp successfully.");

    /*Step-16: Bind PPL*/
    if (CWebServer::GetInstance()->Init()) {
        CWebServer::GetInstance()->BindPPL(this);
    } else {
        return AX_FALSE;
    }
    LOG_M_I(PPL, "Init Webserver successfully.");
#endif  // SLT

#ifdef MP4ENC_SUPPORT
    /*Step-17: Initialize MPEG4*/
    for (auto pInstance : m_vecMpeg4Instance) {
        if (!pInstance->Init()) {
            return AX_FALSE;
        }
    }
    LOG_M_I(PPL, "Init MPEG4 successfully.");
#endif

    /*Step-18: Initialize UT*/
    if (CCmdLineParser::GetInstance()->isUTEnabled()) {
        if (m_pTestSuite && m_pTestSuite->Init()) {
            m_pTestSuite->BindPPL(this);
        }
    }

    InitIVPSMaxResolutionChnInfo();

    m_pPPLConfig->InitPost();

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

#ifndef SLT
AX_BOOL CPanoBuilder::InitAudio() {
    LOG_MM(PPL, "+++");
    // audio
    AX_APP_AUDIO_ATTR_T stAudioAttr = APP_AUDIO_ATTR();
    AX_APP_Audio_Init(&stAudioAttr);

    m_vecWebObs.emplace_back(CObserverMaker::CreateObserver<CWebObserver>(CWebServer::GetInstance()));
    AX_APP_Audio_RegDetectResultObserver(m_vecWebObs[m_vecWebObs.size() - 1].get());

    LOG_MM(PPL, "---");

    return AX_TRUE;
}
#endif  // SLT

AX_BOOL CPanoBuilder::InitSensor() {
    LOG_MM(PPL, "+++");

    if (AX_FALSE == m_mgrSensor.Init()) {
        LOG_MM_E(PPL, "Initailize SensorMgr failed.");
        return AX_FALSE;
    }

    AX_U32 nSnsCnt = m_mgrSensor.GetSensorCount();
    for (AX_U32 i = 0; i < nSnsCnt; i++) {
        CBaseSensor* pSensor = m_mgrSensor.GetSnsInstance(i);
        SENSOR_CONFIG_T tSnsConfig = pSensor->GetSnsConfig();
        AX_U8 nSnsID = tSnsConfig.nSnsID;
        WEB_CAMERA_ATTR_T tCamera;
        tCamera.nSnsMode = tSnsConfig.eSensorMode;
        tCamera.nRotation = tSnsConfig.eRotation;
        tCamera.fFramerate = tSnsConfig.fFrameRate;
        tCamera.nDayNightMode = tSnsConfig.eDayNight; // 0: day, 1: night; 2: auto
        tCamera.nNrMode = 1;
        tCamera.bCapture = AX_TRUE;
        tCamera.bCaptureEnable = AX_TRUE;
        tCamera.bSnsModeEnable = AX_FALSE;
        tCamera.bPNModeEnable = AX_TRUE;
        tCamera.bMirrorFlipEnable = AX_FALSE;
        tCamera.bRotationEnable = AX_FALSE;
        tCamera.bLdcEnable = AX_FALSE;
        tCamera.bDisSupport = AX_FALSE;
        tCamera.bEZoomEnable = AX_FALSE;
        CWebOptionHelper::GetInstance()->InitCameraAttr(nSnsID, tSnsConfig.eSensorType, tCamera);
        if (m_pTestSuite) {
            m_pTestSuite->InitCameraAttr(nSnsID, tSnsConfig.eSensorType, tCamera);
        }
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitIvps() {
    LOG_MM(PPL, "+++");
    AX_APP_AVS_RESOLUTION_T stAvsResolution = m_avs.GetAvsResolution();
    for (AX_U8 i = 0; i < MAX_IVPS_GROUP_NUM; i++) {
        IVPS_GROUP_CFG_T tIvpsGrpCfg;
        /* Step 1: Get configurations  */
        if (!APP_IVPS_CONFIG(i, tIvpsGrpCfg)) {
            /* Not configured for this group */
            break;
        }

        /* Step 2: Copy configurations and do initialization */
        CIVPSGrpStage* pIvpsInstance = new CIVPSGrpStage(tIvpsGrpCfg);
        if (!pIvpsInstance->Init()) {
            break;
        }

        if (COptionHelper::GetInstance()->IsEnableOSD()) {
            IOSDHelper* pHelper = new COSDHelper();
            pIvpsInstance->AttachOsdHelper(pHelper);
        }

        /* Step-3: Register IVPS observers and fill attributes from source modules */
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_IVPS, i, 0};
        vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
        if (!GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
            LOG_MM_N(PPL, "Can not find relation for dest module: (Module:%s, Grp:%d, Chn:%d)",
                     CAXTypeConverter::ModType2String(tDstMod.eModType).c_str(), tDstMod.nGroup, tDstMod.nChannel);
            continue;
            // return AX_FALSE;
        }
        /* NOTICE: Suppose each ivps group has only one frame source */
        PPL_MOD_RELATIONSHIP_T& tRelation = vecRelations[0];
        m_vecIvpsObs.emplace_back(CObserverMaker::CreateObserver<CIvpsObserver>(pIvpsInstance));
        if (!tRelation.bLink) {
            if (E_PPL_MOD_TYPE_IVPS == tRelation.tSrcModChn.eModType) {
                m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->RegObserver(tRelation.tSrcModChn.nChannel,
                                                                            m_vecIvpsObs[m_vecIvpsObs.size() - 1].get());
            } else {
                LOG_MM_W(PPL, "Non-Link mode is not supported");
            }
        } else {
            IVPS_GROUP_CFG_T* pConfig = pIvpsInstance->GetGrpCfg();

            if (E_PPL_MOD_TYPE_AVS == tRelation.tSrcModChn.eModType) {
                CBaseSensor* pSensor = m_mgrSensor.GetSnsInstance(0);
                AX_U8 nPipeID = pSensor->GetSnsConfig().arrPipeAttr->nPipeID;
                AX_F32 fFrameRate = pSensor->GetPipeAttr(nPipeID).tFrameRateCtrl.fDstFrameRate;
                AX_U8 nOutChannels = tIvpsGrpCfg.nGrpChnNum;
				pConfig->nSnsSrc = 0;

                if (-1 == pConfig->arrGrpResolution[0]) {
                    pConfig->arrGrpResolution[0] = stAvsResolution.u32Width;
                }

                if (-1 == pConfig->arrGrpResolution[1]) {
                    pConfig->arrGrpResolution[1] = stAvsResolution.u32Height;
                }

                if (-1 == pConfig->arrGrpFramerate[0]) {
                    pConfig->arrGrpFramerate[0] = fFrameRate;
                }

                if (-1 == pConfig->arrGrpFramerate[1]) {
                    pConfig->arrGrpFramerate[1] = fFrameRate;
                }

                for (AX_U8 j = 0; j < nOutChannels; j++) {
                    if (-1 == pConfig->arrChnResolution[j][0]) {
                        pConfig->arrChnResolution[j][0] = stAvsResolution.u32Width;
                    }

                    if (-1 == pConfig->arrChnResolution[j][1]) {
                        pConfig->arrChnResolution[j][1] = stAvsResolution.u32Height;
                    }

                    if (-1 == pConfig->arrChnFramerate[j][0]) {
                        pConfig->arrChnFramerate[j][0] = pConfig->arrGrpFramerate[0];
                    }

                    if (-1 == pConfig->arrChnFramerate[j][1]) {
                        pConfig->arrChnFramerate[j][1] = pConfig->arrGrpFramerate[1];
                    }
                }
            } else if (E_PPL_MOD_TYPE_VIN == tRelation.tSrcModChn.eModType) {
                AX_U8 nOutChannels = tIvpsGrpCfg.nGrpChnNum;
                for (AX_U8 j = 0; j < nOutChannels; j++) {
                    AX_S32 nSnsID = tRelation.tSrcModChn.nGroup;
                    CBaseSensor* pSensor = m_mgrSensor.GetSnsInstance(nSnsID);
                    if (-1 == nSnsID) {
                        LOG_MM_E(PPL, "[IVPS] Pipe %d does not configured in sensor.json", tRelation.tSrcModChn.nGroup);
                        return AX_FALSE;
                    }

                    pConfig->nSnsSrc = nSnsID;
                    if (-1 == pConfig->arrGrpResolution[0]) {
                        pConfig->arrGrpResolution[0] =
                            pSensor->GetChnAttr(tRelation.tSrcModChn.nGroup, tRelation.tSrcModChn.nChannel).nWidth;
                    }

                    if (-1 == pConfig->arrGrpResolution[1]) {
                        pConfig->arrGrpResolution[1] =
                            pSensor->GetChnAttr(tRelation.tSrcModChn.nGroup, tRelation.tSrcModChn.nChannel).nHeight;
                    }

                    if (-1 == pConfig->arrChnResolution[j][0]) {
                        pConfig->arrChnResolution[j][0] =
                            pSensor->GetChnAttr(tRelation.tSrcModChn.nGroup, tRelation.tSrcModChn.nChannel).nWidth;
                    }

                    if (-1 == pConfig->arrChnResolution[j][1]) {
                        pConfig->arrChnResolution[j][1] =
                            pSensor->GetChnAttr(tRelation.tSrcModChn.nGroup, tRelation.tSrcModChn.nChannel).nHeight;
                    }

                    if (-1 == pConfig->arrGrpFramerate[0]) {
                        pConfig->arrGrpFramerate[0] =
                            m_mgrSensor.GetSnsInstance(nSnsID)->GetPipeAttr(tRelation.tSrcModChn.nGroup).tFrameRateCtrl.fDstFrameRate;
                    }
                    if (-1 == pConfig->arrGrpFramerate[1]) {
                        pConfig->arrGrpFramerate[1] = pConfig->arrGrpFramerate[0];
                    }

                    if (-1 == pConfig->arrChnFramerate[j][0]) {
                        pConfig->arrChnFramerate[j][0] =
                            m_mgrSensor.GetSnsInstance(nSnsID)->GetPipeAttr(tRelation.tSrcModChn.nGroup).tFrameRateCtrl.fDstFrameRate;
                    }
                    if (-1 == pConfig->arrChnFramerate[j][1]) {
                        pConfig->arrChnFramerate[j][1] = pConfig->arrChnFramerate[j][0];
                    }
                }
            } else if (E_PPL_MOD_TYPE_IVPS == tRelation.tSrcModChn.eModType) {
                // Source Mmodule is uninitialized
                if (tRelation.tSrcModChn.nGroup > i) {
                    LOG_MM_E(PPL, "nonsupport,please check ppl.json.");
                    return AX_FALSE;
                }
                IVPS_GROUP_CFG_T* pSrcConfig = m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->GetGrpCfg();
                AX_U32 nWidth = pSrcConfig->arrChnResolution[tRelation.tSrcModChn.nChannel][0];
                AX_U32 nHeight = pSrcConfig->arrChnResolution[tRelation.tSrcModChn.nChannel][1];
                AX_U8 nOutChannels = tIvpsGrpCfg.nGrpChnNum;

                if (-1 == pConfig->arrGrpResolution[0]) {
                    pConfig->arrGrpResolution[0] = nWidth;
                }

                if (-1 == pConfig->arrGrpResolution[1]) {
                    pConfig->arrGrpResolution[1] = nHeight;
                }

                if (-1 == pConfig->arrGrpFramerate[0]) {
                    pConfig->arrGrpFramerate[0] = pSrcConfig->arrGrpFramerate[0];
                }

                if (-1 == pConfig->arrGrpFramerate[1]) {
                    pConfig->arrGrpFramerate[1] = pConfig->arrGrpFramerate[0];
                }
                for (AX_U8 j = 0; j < nOutChannels; j++) {
                    if (-1 == pConfig->arrChnResolution[j][0]) {
                        pConfig->arrChnResolution[j][0] = nWidth;
                    }

                    if (-1 == pConfig->arrChnResolution[j][1]) {
                        pConfig->arrChnResolution[j][1] = nHeight;
                    }

                    if (-1 == pConfig->arrChnFramerate[j][0]) {
                        pConfig->arrChnFramerate[j][0] = pSrcConfig->arrChnFramerate[tRelation.tSrcModChn.nChannel][1];
                    }

                    if (-1 == pConfig->arrChnFramerate[j][1]) {
                        pConfig->arrChnFramerate[j][1] = pConfig->arrChnFramerate[j][0];
                    }
                }

            } else {
                LOG_MM_E(PPL, "nonsupport,please check ppl.json.");
            }

            pConfig->nGrpLinkFlag = AX_TRUE;
        }

        /* Step-4: initialize IVPS with latest attributes */
        if (!pIvpsInstance->InitParams()) {
            return AX_FALSE;
        }

        /* Step-5: Save instance */
        m_vecIvpsInstance.emplace_back(pIvpsInstance);

        LOG_M_I(PPL, "Init ivps group %d successfully.", i);
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitVenc() {
    LOG_MM(PPL, "+++");

    for (AX_U8 i = 0; i < MAX_VENC_CHANNEL_NUM; i++) {
        VIDEO_CONFIG_T tConfig;
        do {
            if (APP_VENC_CONFIG(i, tConfig)) {
                CVideoEncoder* pVencInstance = new CVideoEncoder(tConfig);
                if (!pVencInstance->Init()) {
                    break;
                }
                PPL_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_VENC, 0, pVencInstance->GetChannel()};
                vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
                if (!GetRelationsByDstMod(tDstMod, vecRelations)) {
                    LOG_MM_N(PPL, "Can not find relation for dst module: (Module:%s, Grp:%d, Chn:%d)",
                             CAXTypeConverter::ModType2String(tDstMod.eModType).c_str(), tDstMod.nGroup, tDstMod.nChannel);
                    break;
                }
                VIDEO_CONFIG_T* pConfig = pVencInstance->GetChnCfg();
                PPL_MOD_RELATIONSHIP_T& tRelation = vecRelations[0];

                m_vecVencObs.emplace_back(CObserverMaker::CreateObserver<CVencObserver>(pVencInstance));
                if (tRelation.bLink) {
                    /* Under link mode, any module must transfer attributes, like resolution info, to venc instance. */
                    if (E_PPL_MOD_TYPE_IVPS == tRelation.tSrcModChn.eModType) {
                        pConfig->nWidth =
                            m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->GetGrpCfg()->arrChnResolution[tRelation.tSrcModChn.nChannel][0];
                        pConfig->nHeight =
                            m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->GetGrpCfg()->arrChnResolution[tRelation.tSrcModChn.nChannel][1];
                        pConfig->fSrcFrameRate =
                            m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->GetGrpCfg()->arrChnFramerate[tRelation.tSrcModChn.nChannel][1];
                        LOG_MM_I(PPL, "IVPS[nGrp:%d, nChn:%d], VENC[nGrp:0, nChn:%d]", tRelation.tSrcModChn.nGroup,
                                 tRelation.tSrcModChn.nChannel, pVencInstance->GetChannel());
                        LOG_MM_I(PPL, "nWidth:%d, nHeight:%d, fSrcFrameRate:%f", pConfig->nWidth, pConfig->nHeight, pConfig->fSrcFrameRate);
                    } else {
                        LOG_MM_E(PPL, "nonsupport Module:%s -> VENC",
                                 CAXTypeConverter::ModType2String(tRelation.tSrcModChn.eModType).c_str());
                        return AX_FALSE;
                    }
                    pConfig->bLink = AX_TRUE;
                }

                pConfig->nMaxWidth  = PANO_VENC_MAX_WIDTH;
                pConfig->nMaxHeight = PANO_VENC_MAX_HEIGHT;

                pConfig->bDeBreathEffect = COptionHelper::GetInstance()->IsEnableVencDebreath();
                pConfig->bRefRingbuf = COptionHelper::GetInstance()->IsEnableVencRefRingbuf();

                if (!pVencInstance->InitParams()) {
                    LOG_MM_E(PPL, "Init venc %d failed.", tConfig.nChannel);
                    return AX_FALSE;
                }

#ifndef SLT
                /* initialize web's video setting */
                WEB_VIDEO_ATTR_T tVideoAttr;
                AX_U8 nEncoderType = CAXTypeConverter::EncoderType2Int(tConfig.ePayloadType);
                AX_U8 nPrevChn =
                    CWebServer::GetInstance()->RegistPreviewChnMappingInOrder(tConfig.nPipeSrc, tConfig.nChannel, nEncoderType);
                tVideoAttr.nUniChn = tConfig.nChannel;
                tVideoAttr.bEnable = AX_TRUE;
                tVideoAttr.nEncoderType = nEncoderType; /* 0: H264; 1: MJpeg; 2: H265 */
                tVideoAttr.nBitrate = pConfig->nBitrate;
                tVideoAttr.nWidth = pConfig->nWidth;
                tVideoAttr.nHeight = pConfig->nHeight;
                tVideoAttr.nRcType = CAXTypeConverter::RcMode2Int(tConfig.eRcType);
                memcpy(tVideoAttr.stEncodeCfg, tConfig.stEncodeCfg, sizeof(APP_ENC_RC_CONFIG) * APP_ENCODER_TYPE_MAX);
                tVideoAttr.bLink = pConfig->bLink;

                CWebOptionHelper::GetInstance()->InitVideoAttr(tConfig.nPipeSrc, nPrevChn, tVideoAttr);
                if (m_pTestSuite) {
                    m_pTestSuite->InitVideoAttr(tConfig.nPipeSrc, tConfig.nChannel, tVideoAttr);
                }
                /* register rtsp  */
                m_vecRtspObs.emplace_back(CObserverMaker::CreateObserver<CAXRtspObserver>(CAXRtspServer::GetInstance()));
                // audio for rtsp
                AX_APP_Audio_RegPacketObserver(APP_AUDIO_RTSP_CHANNEL(), m_vecRtspObs[m_vecRtspObs.size() - 1].get());
                pVencInstance->RegObserver(m_vecRtspObs[m_vecRtspObs.size() - 1].get());

                /* register web */
                m_vecWebObs.emplace_back(CObserverMaker::CreateObserver<CWebObserver>(CWebServer::GetInstance()));
                pVencInstance->RegObserver(m_vecWebObs[m_vecWebObs.size() - 1].get());
                // audio for webserver
                if (0 == tConfig.nChannel) {
                    m_vecWebObs.emplace_back(CObserverMaker::CreateObserver<CWebObserver>(CWebServer::GetInstance()));
                    AX_APP_Audio_RegPacketObserver(APP_AUDIO_WEB_STREAM_CHANNEL(), m_vecWebObs[m_vecWebObs.size() - 1].get());
                }

#ifdef MP4ENC_SUPPORT
                if ((0 == tConfig.nChannel) && (COptionHelper::GetInstance()->IsEnableMp4Record())) {
                    CMPEG4Encoder* pMp4Instance = new CMPEG4Encoder();
                    VIDEO_CONFIG_T* pConfig = pVencInstance->GetChnCfg();
                    MPEG4EC_INFO_T tMpeg4Info;
                    tMpeg4Info.nchn = pConfig->nChannel;
                    tMpeg4Info.nMaxFileInMBytes = 64;

                    AX_U32 nBuffSize = COptionHelper::GetInstance()->GetWebVencRingBufSize(pConfig->nWidth, pConfig->nHeight);
                    tMpeg4Info.stVideoAttr.bEnable = AX_TRUE;
                    tMpeg4Info.stVideoAttr.ePt = pConfig->ePayloadType;
                    tMpeg4Info.stVideoAttr.nfrWidth = pConfig->nWidth;
                    tMpeg4Info.stVideoAttr.nfrHeight = pConfig->nHeight;
                    tMpeg4Info.stVideoAttr.nFrameRate = (AX_U32)pConfig->fDstFrameRate;
                    tMpeg4Info.stVideoAttr.nBitrate = pConfig->nBitrate;
                    tMpeg4Info.stVideoAttr.nMaxFrmSize = nBuffSize;

                    AX_APP_AUDIO_CHAN_E nAudioMp4Chn = APP_AUDIO_MP4_CHANNEL();
                    AX_APP_AUDIO_ENCODER_ATTR_T stAttr;
                    if (0 == AX_APP_Audio_GetEncoderAttr(nAudioMp4Chn, &stAttr)) {
                        tMpeg4Info.stAudioAttr.bEnable = AX_TRUE;
                        tMpeg4Info.stAudioAttr.ePt = (AX_PAYLOAD_TYPE_E)stAttr.eType;
                        tMpeg4Info.stAudioAttr.nBitrate = stAttr.nBitRate;
                        tMpeg4Info.stAudioAttr.nSampleRate = (AX_U32)stAttr.eSampleRate;
                        tMpeg4Info.stAudioAttr.nChnCnt = (AX_APP_AUDIO_SOUND_MODE_MONO == stAttr.eSoundMode) ? 1 : 2;
                        tMpeg4Info.stAudioAttr.nAOT = (AX_S32)stAttr.nAOT;
                        tMpeg4Info.stAudioAttr.nMaxFrmSize = COptionHelper::GetInstance()->GetAencOutFrmSize();
                    } else {
                        tMpeg4Info.stAudioAttr.bEnable = AX_FALSE;
                    }

                    tMpeg4Info.strSavePath = COptionHelper::GetInstance()->GetMp4SavedPath();
                    if (AX_FALSE == pMp4Instance->InitParam(tMpeg4Info)) {
                        LOG_MM_E(PPL, "MP4 InitParam failed");
                        return AX_FALSE;
                    }

                    //  m_vecMpeg4Obs.emplace_back(CMPEG4Observer::NewInstance(pMp4Instance));
                    m_vecMpeg4Obs.emplace_back(CObserverMaker::CreateObserver<CMPEG4Observer>(pMp4Instance));
                    AX_APP_Audio_RegPacketObserver(nAudioMp4Chn, m_vecMpeg4Obs[m_vecMpeg4Obs.size() - 1].get());
                    pVencInstance->RegObserver(m_vecMpeg4Obs[m_vecMpeg4Obs.size() - 1].get());
                    m_vecMpeg4Instance.emplace_back(pMp4Instance);
                }
#endif  // MP4ENC_SUPPORT
#else
                if (0 == tConfig.nChannel) {
                    CPrintHelper::GetInstance()->SetSLTTargetFPS(E_PH_MOD_VENC, 0, pConfig->fFramerate);
                }
#endif  // SLT

                m_vecVencInstance.emplace_back(pVencInstance);
            }
        } while (0);
    }

    CWebOptionHelper::GetInstance()->GenerateChnResolutionList(&m_mgrSensor, m_vecVencInstance, AX_TRUE);

#ifndef SLT
    AX_APP_ALGO_AUDIO_PARAM_T stAlgoParam = ALGO_AUDIO_PARAM();
    WEB_AUDIO_ATTR_T tAudioAttr;
    AX_APP_AUDIO_ATTR_T stAudioAttr = APP_AUDIO_ATTR();
    tAudioAttr.fCapture_volume = (AX_F32)stAudioAttr.stCapAttr.stDevAttr.fVolume;
    tAudioAttr.fPlay_volume = (AX_F32)stAudioAttr.stPlayAttr.stDevAttr.fVolume;
    tAudioAttr.bAedEnable = stAlgoParam.bEnable;
    tAudioAttr.fAedThreshold = stAlgoParam.fThreshold;
    tAudioAttr.nAedInterval = stAlgoParam.nInterval;
    CWebServer::GetInstance()->EnableAudioPlay(APP_AUDIO_PLAY_AVAILABLE());
    CWebServer::GetInstance()->EnableAudioCapture(APP_AUDIO_CAP_AVAILABLE());
    CWebOptionHelper::GetInstance()->SetAudio(tAudioAttr);
#endif  // SLT

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitJenc() {
    LOG_MM(PPL, "+++");

    for (AX_U8 i = 0; i < MAX_JENC_CHANNEL_NUM; i++) {
        JPEG_CONFIG_T tJencCfg;

        do {
            if (APP_JENC_CONFIG(i, tJencCfg)) {
                CJpegEncoder* pJencInstance = new CJpegEncoder(tJencCfg);
                if (!pJencInstance->Init()) {
                    break;
                }

                /* Step-8-2: IVPS register JENC observers and init JENC attributes according to IVPS attributes */
                IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_JENC, 0, pJencInstance->GetChannel()};
                vector<IPC_MOD_RELATIONSHIP_T> vecRelations;
                if (!GetRelationsByDstMod(tDstMod, vecRelations)) {
                    LOG_MM_N(PPL, "Can not find relation for dest module: (Module:%s, Grp:%d, Chn:%d)",
                             CAXTypeConverter::ModType2String(tDstMod.eModType).c_str(), tDstMod.nGroup, tDstMod.nChannel);
                    return AX_FALSE;
                }

                IPC_MOD_RELATIONSHIP_T& tRelation = vecRelations[0];
                m_vecJencObs.emplace_back(CObserverMaker::CreateObserver<CJencObserver>(pJencInstance));
                if (tRelation.bLink) {
                    /* Under link mode, any module must transfer attributes, like resolution info, to jenc instance. */
                    JPEG_CONFIG_T* pConfig = pJencInstance->GetChnCfg();
                    if (E_PPL_MOD_TYPE_IVPS == tRelation.tSrcModChn.eModType) {
                        pConfig->nWidth =
                            m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->GetGrpCfg()->arrChnResolution[tRelation.tSrcModChn.nChannel][0];
                        pConfig->nHeight =
                            m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->GetGrpCfg()->arrChnResolution[tRelation.tSrcModChn.nChannel][1];
                        pConfig->fSrcFrameRate =
                            m_vecIvpsInstance[tRelation.tSrcModChn.nGroup]->GetGrpCfg()->arrChnFramerate[tRelation.tSrcModChn.nChannel][1];
                    }
                    pConfig->bLink = AX_TRUE;
                } else {
                    if (E_PPL_MOD_TYPE_IVPS == tRelation.tSrcModChn.eModType) {
                        LOG_MM_E(PPL, "Unspport unlink mode");
                    }
                }

                /* Step-8-3: Initialize JENC with latest attributes */
                if (!pJencInstance->InitParams()) {
                    return AX_FALSE;
                }

#ifndef SLT
                /* Register unique capture channel, only the first setting will be effective */
                CWebServer::GetInstance()->RegistUniCaptureChn(pJencInstance->GetChannel());

                /* Step-8-4: Register observers */
                m_vecWebObs.emplace_back(CObserverMaker::CreateObserver<CWebObserver>(CWebServer::GetInstance()));
                pJencInstance->RegObserver(m_vecWebObs[m_vecWebObs.size() - 1].get());
#endif  // SLT
                /* Step-8-5: Save instance */
                m_vecJencInstance.emplace_back(pJencInstance);

                LOG_M_I(PPL, "Init jenc channel %d successfully.", i);
            }
        } while (0);
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitDetector() {
    LOG_MM(PPL, "+++");
    AX_U8 DetectFlag = 0;

    AX_U8 nGrpCount = 0;
    IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_DETECT, 0, 0};
    vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
    if (GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
        for (auto& relation : vecRelations) {
            if (!relation.bLink) {
                if (E_PPL_MOD_TYPE_IVPS == relation.tSrcModChn.eModType) {
                    DetectFlag = 1;
                    nGrpCount ++;
                    m_vecDetectorObs.emplace_back(CObserverMaker::CreateObserver<CDetectObserver>(&m_detector));
                    m_vecIvpsInstance[relation.tSrcModChn.nGroup]->RegObserver(relation.tSrcModChn.nChannel,
                                                                               m_vecDetectorObs[m_vecDetectorObs.size() - 1].get());

                    CWebOptionHelper::GetInstance()->InitAiAttr(m_vecIvpsInstance[relation.tSrcModChn.nGroup]->GetGrpCfg()->nSnsSrc);
                } else if (E_PPL_MOD_TYPE_COLLECT == relation.tSrcModChn.eModType) {
                    /* Call InitAiAttr in the InitCollector function*/
                    DetectFlag = 1;
                    nGrpCount ++;
                } else {
                    LOG_MM_E(PPL, "Unsupport from %s to DETECTOR , please check the ppl.json configuration.",
                             CAXTypeConverter::ModType2String(relation.tSrcModChn.eModType));
                }
            } else {
                LOG_MM_E(PPL, "Detector does not support link mode, please check the ppl.json configuration.");
            }
        }
    }
    if (DetectFlag && CAlgoOptionHelper::GetInstance()->GetDetectAlgoType(0) > 0) {
        DETECTOR_ATTR_T tDetectAttr;
        tDetectAttr.strModelPath = ALGO_HVCFP_PARAM(0).strDetectModelsPath;
        tDetectAttr.ePPL = (AX_SKEL_PPL_E)CAlgoOptionHelper::GetInstance()->GetDetectAlgoType(0);
        tDetectAttr.nGrpCount = nGrpCount;
        tDetectAttr.nGrp = tDstMod.nGroup;

        // bind sensor
        m_detector.BindSensorMgr(&m_mgrSensor);

        if (AX_FALSE == m_detector.Init(tDetectAttr)) {
            LOG_M_E(PPL, "Init detector failed.");
            return AX_FALSE;
        }

#ifndef SLT
        /* Register unique capture channel, only the first setting will be effective */
        CWebServer::GetInstance()->RegistUniCaptureChn(CWebServer::GetInstance()->GetCaptureChannel());

        /* Register detector web observers */
        m_vecWebObs.emplace_back(CObserverMaker::CreateObserver<CWebObserver>(CWebServer::GetInstance()));
        m_detector.RegObserver(m_vecWebObs[m_vecWebObs.size() - 1].get());
#endif  // SLT

        m_vecOsdObs.emplace_back(CObserverMaker::CreateObserver<COsdObserver>(&m_vecIvpsInstance));
        m_detector.RegObserver(m_vecOsdObs[m_vecOsdObs.size() - 1].get());
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::ConstructIves() {
    for (int i = 0; i < MAX_IVES_GROUP_NUM; i++) {
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_IVES, i, 0};

        vector<IPC_MOD_RELATIONSHIP_T> vecRelations;
        if (GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
            for (auto& relation : vecRelations) {
                if (E_PPL_MOD_TYPE_IVPS == relation.tSrcModChn.eModType) {
                    CIVESStage* pIves = new CIVESStage();
                    m_vecIvesInstance.emplace_back(pIves);

                    m_vecIvesObs.emplace_back(CObserverMaker::CreateObserver<CIvesObserver>(pIves));
                    m_vecIvpsInstance[relation.tSrcModChn.nGroup]->RegObserver(relation.tSrcModChn.nChannel,
                                                                               m_vecIvesObs[m_vecIvesObs.size() - 1].get());
                    /*fixme: IVES requires a 640*360 resulution ,but INPLACE mode does not support resize */
                    m_vecIvpsInstance[relation.tSrcModChn.nGroup]->SetChnInplace(relation.tSrcModChn.nChannel, AX_FALSE);
                } else if (E_PPL_MOD_TYPE_COLLECT == relation.tSrcModChn.eModType) {
                    CIVESStage* pIves = new CIVESStage();
                    m_vecIvesInstance.emplace_back(pIves);
                    m_vecIvesObs.emplace_back(CObserverMaker::CreateObserver<CIvesObserver>(pIves));
                }
            }
        }
    }

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitIves() {
    LOG_MM(PPL, "+++");
    for (int i = 0; i < MAX_IVES_GROUP_NUM; i++) {
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_IVES, i, 0};

        vector<IPC_MOD_RELATIONSHIP_T> vecRelations;
        if (GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
            // AX_U32 index = 0;
            for (auto& relation : vecRelations) {
                if (E_PPL_MOD_TYPE_IVPS == relation.tSrcModChn.eModType) {
                    CIVESStage* pIves = m_vecIvesInstance[i];

                    CWebOptionHelper::GetInstance()->InitIvesAttr(tDstMod.nGroup, pIves);
                    pIves->Init(tDstMod.nGroup);

                    if (m_pTestSuite) {
                        m_pTestSuite->InitIvesAttr(tDstMod.nGroup);
                    }

#ifndef SLT
                    // web event
                    m_vecWebObs.emplace_back(CObserverMaker::CreateObserver<CWebObserver>(CWebServer::GetInstance()));
                    pIves->RegObserver(m_vecWebObs[m_vecWebObs.size() - 1].get());
#endif  // SLT
                } else if (E_PPL_MOD_TYPE_COLLECT == relation.tSrcModChn.eModType) {
                    CIVESStage* pIves = m_vecIvesInstance[i];

                    CWebOptionHelper::GetInstance()->InitIvesAttr(tDstMod.nGroup, pIves);
                    pIves->Init(tDstMod.nGroup);
                    if (m_pTestSuite) {
                        m_pTestSuite->InitIvesAttr(tDstMod.nGroup);
                    }

#ifndef SLT
                    // web event
                    m_vecWebObs.emplace_back(CObserverMaker::CreateObserver<CWebObserver>(CWebServer::GetInstance()));
                    pIves->RegObserver(m_vecWebObs[m_vecWebObs.size() - 1].get());
#endif  // SLT
                }
            }
        }
    }
    LOG_MM(PPL, "---");

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitDummyEnc(AX_VOID) {
    for (AX_S32 i = 0; i < MAX_DUMMY_ENC_CHANNEL_NUM; ++i) {
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_DUMMYENC, i, 0};

        vector<IPC_MOD_RELATIONSHIP_T> vecRelations;
        if (GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
            for (auto& relation : vecRelations) {
                if (relation.bLink) {
                    LOG_M_E(PPL, "Dummy encoder was not supported in link mode, channel: %d", relation.tSrcModChn.nChannel);
                    continue;
                }

                if (E_PPL_MOD_TYPE_IVPS == relation.tSrcModChn.eModType) {
                    DUMMY_CODE_CONFIG_T stConfig;
                    stConfig.nPipeSrc = relation.tDstModChn.nGroup;
                    stConfig.nChannel = relation.tDstModChn.nChannel;
                    CDummyEncoder* pDummyEnc = new CDummyEncoder(stConfig);
                    m_vecDummyEncInstance.emplace_back(pDummyEnc);

                    pDummyEnc->Init();

                    m_vecDummyEncObs.emplace_back(CObserverMaker::CreateObserver<CDummyEncoderObserver>(pDummyEnc));
                    pDummyEnc->RegObserver(m_vecDummyEncObs[m_vecDummyEncObs.size() - 1].get());
                    m_vecIvpsInstance[relation.tSrcModChn.nGroup]->RegObserver(relation.tSrcModChn.nChannel,
                                                                               m_vecDummyEncObs[m_vecDummyEncObs.size() - 1].get());
                }
            }
        }
    }

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitCapture() {
    for (AX_S32 i = 0; i < MAX_CAPTURE_GROUP_NUM; ++i) {
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_CAPTURE, i, 0};
        vector<IPC_MOD_RELATIONSHIP_T> vecRelations;
        if (!GetRelationsByDstMod(tDstMod, vecRelations)) {
            continue;
        }
        for (const auto& relation : vecRelations) {
            if (E_PPL_MOD_TYPE_IVPS == relation.tSrcModChn.eModType) {
                m_vecCaptureObs.emplace_back(CObserverMaker::CreateObserver<CCaptureObserver>(&m_capture));
                m_vecIvpsInstance[relation.tSrcModChn.nGroup]->RegObserver(relation.tSrcModChn.nChannel,
                                                                           m_vecCaptureObs[m_vecCaptureObs.size() - 1].get());
            }
        }
    }

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::InitCollector() {
    LOG_MM(PPL, "+++");

    ConstructIves();

    for (AX_U8 i = 0; i < MAX_COLLECT_GROUP_NUM; i++) {
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_COLLECT, i, 0};
        vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
        if (!GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
            break;
        }
        CCollector* pCollectorInstance = new CCollector(i);
        if (!pCollectorInstance->Init()) {
            SAFE_DELETE_PTR(pCollectorInstance);
            return AX_FALSE;
        }
        m_vecCollectorInstance.emplace_back(pCollectorInstance);
    }

    /* Mulit Module to a Collect */
    for (AX_U8 i = 0; i < MAX_COLLECT_GROUP_NUM; i++) {
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_COLLECT, i, 0};
        vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
        if (!GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
            LOG_MM_I(PPL, "Can not find relation for other module to collect (Module:%s, Grp:%d, Chn:%d)",
                     CAXTypeConverter::ModType2String(tDstMod.eModType).c_str(), tDstMod.nGroup, tDstMod.nChannel);
            break;
        }

        for (auto& relation : vecRelations) {
            if (!relation.bLink) {
                /* Step-2*/
                if (E_PPL_MOD_TYPE_IVPS == relation.tSrcModChn.eModType) {
                    m_vecCollectorInstance[i]->RegTargetChannel(relation.tSrcModChn.nGroup, relation.tSrcModChn.nChannel);
                    m_vecCollectorObs.emplace_back(CObserverMaker::CreateObserver<CCollectorObserver>(m_vecCollectorInstance[i]));
                    m_vecIvpsInstance[relation.tSrcModChn.nGroup]->RegObserver(relation.tSrcModChn.nChannel,
                                                                               m_vecCollectorObs[m_vecCollectorObs.size() - 1].get());
                    IVPS_GROUP_CFG_T* pIvpsConfig = m_vecIvpsInstance[relation.tSrcModChn.nGroup]->GetGrpCfg();
                    COLLECTOR_ATTR_T* pCollConfig = m_vecCollectorInstance[i]->GetCollectorCfg();
                    pCollConfig->nWidth = pIvpsConfig->arrChnResolution[relation.tSrcModChn.nChannel][0];
                    pCollConfig->nHeight = pIvpsConfig->arrChnResolution[relation.tSrcModChn.nChannel][1];
                    pCollConfig->fFramerate = pIvpsConfig->arrChnFramerate[relation.tSrcModChn.nChannel][1];
                    pCollConfig->bEnableFBC = pIvpsConfig->arrChnFBC[relation.tSrcModChn.nChannel][0] == 0 ? AX_FALSE : AX_TRUE;
                    pCollConfig->nSnsSrc = pIvpsConfig->nSnsSrc;
                    LOG_MM_I(PPL, "collect  width:%d, height:%d, sensorSrc:%d, frameRate:%lf", pCollConfig->nWidth, pCollConfig->nHeight,
                             pCollConfig->nSnsSrc, pCollConfig->fFramerate);
                } else {
                    LOG_MM_W(PPL, "Collector only receives IVPS out frames now, please check the ppl.json configuration.");
                }
            } else {
                LOG_MM_E(PPL, "Collector not support link mode, please check the ppl.json configuration.");
            }
        }
    }

    /* A collect to mulit Module */
    for (AX_U8 i = 0; i < MAX_COLLECT_GROUP_NUM; i++) {
        IPC_MOD_INFO_T tSrcMod = {E_PPL_MOD_TYPE_COLLECT, i, 0};
        vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
        if (!GetRelationsBySrcMod(tSrcMod, vecRelations, AX_TRUE)) {
            LOG_MM_I(PPL, "Can not find relation for collect module: ( Grp:%d, Chn:%d) to other module", tSrcMod.nGroup, tSrcMod.nChannel);
            break;
        }

        for (auto& relation : vecRelations) {
            if (!relation.bLink) {
                if (E_PPL_MOD_TYPE_DETECT == relation.tDstModChn.eModType) {
                    m_vecDetectorObs.emplace_back(CObserverMaker::CreateObserver<CDetectObserver>(&m_detector));

                    if (!m_vecDetectorObs.empty()) {
                        m_vecCollectorInstance[i]->RegObserver(m_vecDetectorObs[m_vecDetectorObs.size() - 1].get());
                        /* fixme: The group of Collector is not equal to the sensor id*/
                        CWebOptionHelper::GetInstance()->InitAiAttr(m_vecCollectorInstance[i]->GetGroup());
                    }
                } else if (E_PPL_MOD_TYPE_CAPTURE == relation.tDstModChn.eModType) {
                    m_vecCollectorInstance[i]->RegObserver(m_vecCaptureObs[m_vecCaptureObs.size() - 1].get());
                } else if (E_PPL_MOD_TYPE_IVES == relation.tDstModChn.eModType) {
                    m_vecCollectorInstance[i]->RegObserver(m_vecIvesObs[relation.tDstModChn.nGroup].get());
                } else if (E_PPL_MOD_TYPE_IVPS == relation.tDstModChn.eModType) {
                    /*fixme:*/
                    m_vecCollectorInstance[i]->RegObserver(m_vecIvpsObs[relation.tDstModChn.nGroup].get());
                    m_vecIvpsInstance[relation.tDstModChn.nGroup]->InitParams();
                } else {
                    LOG_MM_E(PPL, "Unsupport from COLLECTOR to %s , please check the ppl.json configuration.",
                             CAXTypeConverter::ModType2String(relation.tDstModChn.eModType));
                }
            } else {
                LOG_MM_E(PPL, "Collector not support link mode, please check the ppl.json configuration.");
            }
        }
    }
    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_VOID CPanoBuilder::InitIVPSMaxResolutionChnInfo() {
    IVPS_GROUP_CFG_T* pConfig = nullptr;
    AX_APP_AVS_RESOLUTION_T stAvsResolution = m_avs.GetAvsResolution();
    for (auto& pInstance : m_vecIvpsInstance) {
        pConfig = pInstance->GetGrpCfg();
        for (AX_U8 i = 0; i < pConfig->nGrpChnNum; i++) {
            if (pConfig->arrChnResolution[i][0] == (AX_S16)stAvsResolution.u32Width
                && pConfig->arrChnResolution[i][1] == (AX_S16)stAvsResolution.u32Height) {
                m_mmapIVPSMaxResolutionChn.insert(std::make_pair(pConfig->nGrp, i));
            }
        }
    }
}

AX_BOOL CPanoBuilder::InitPoolConfig() {
    LOG_MM(PPL, "+++");
    std::map<AX_U8, POOL_ATTR_T> tAttr;
    AX_U32 nSnsCnt = m_mgrSensor.GetSensorCount();
    for (AX_U8 i = 0; i < nSnsCnt; i++) {
        if (m_mgrSensor.GetSnsInstance(i)) {
            tAttr[i].nMaxWidth = m_mgrSensor.GetSnsInstance(i)->GetSnsAttr().nWidth;
            tAttr[i].nMaxHeight = m_mgrSensor.GetSnsInstance(i)->GetSnsAttr().nHeight;
            tAttr[i].bRotatetion = AX_TRUE;
        }
    }

    m_pPoolConfig = new CPoolConfig(tAttr);
    if (nullptr == m_pPoolConfig) {
        return AX_FALSE;
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::Start(AX_VOID) {
    LOG_MM(PPL, "+++");

    if (!m_pPoolConfig->Start()) {
        LOG_M(PPL, "pool start failed.");
        return AX_FALSE;
    }

#ifndef SLT
    if (!CWebServer::GetInstance()->Start()) {
        return AX_FALSE;
    }

    if (!CAXRtspServer::GetInstance()->Start()) {
        LOG_M_E(PPL, "Start rtsp server failed.");
        return AX_FALSE;
    }
#endif  // SLT

#ifdef MP4ENC_SUPPORT
    for (auto& pInstance : m_vecMpeg4Instance) {
        if (!pInstance->Start()) {
            return AX_FALSE;
        }
    }
#endif

    if (!m_detector.Start()) {
        return AX_FALSE;
    }

    for (auto& pInstance : m_vecIvesInstance) {
        if (!pInstance->Start()) {
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecDummyEncInstance) {
        STAGE_START_PARAM_T tStartParam;
        tStartParam.bStartProcessingThread = AX_TRUE;
        if (!pInstance->Start(&tStartParam)) {
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecVencInstance) {
        STAGE_START_PARAM_T tStartParam;
        AX_BOOL bLinkMode = pInstance->GetChnCfg()->bLink;
        tStartParam.bStartProcessingThread = bLinkMode ? AX_FALSE : AX_TRUE;
        if (!pInstance->Start(&tStartParam)) {
            LOG_MM_E(PPL, "Start venc failed.");
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecJencInstance) {
        AX_BOOL bLinkMode = pInstance->GetChnCfg()->bLink;

        STAGE_START_PARAM_T tStartParam;
        tStartParam.bStartProcessingThread = bLinkMode ? AX_FALSE : AX_TRUE;
        if (!pInstance->Start(&tStartParam)) {
            LOG_MM_E(PPL, "Start jenc failed.");
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecIvpsInstance) {
        AX_BOOL bLinkMode = pInstance->GetGrpCfg()->nGrpLinkFlag == 0 ? AX_FALSE : AX_TRUE;

        STAGE_START_PARAM_T tStartParam;
        tStartParam.bStartProcessingThread = bLinkMode ? AX_FALSE : AX_TRUE;
        if (!pInstance->Start(&tStartParam)) {
            LOG_MM_E(PPL, "Start ivps failed.");
            return AX_FALSE;
        }
    }

    m_avs.Start();

    if (AX_FALSE == m_mgrSensor.Start()) {
        LOG_MM_E(PPL, "Start sensor failed.");

        return AX_FALSE;
    }

#ifndef SLT
    AX_APP_Audio_Start();

    if (APP_AUDIO_PLAY_AVAILABLE()) {
        AX_APP_AUDIO_WELCOME_CFG_T stWelcomeConfig = APP_AUDIO_WELCOME_CONFIG();
        if (stWelcomeConfig.bEnable) {
            AX_APP_Audio_PlayFile(APP_AUDIO_LOCAL_PLAY_CHANNEL(), stWelcomeConfig.eType, stWelcomeConfig.strFileName.c_str(), 1,
                                  AudioPlayCallback, this);
        }
    }
#endif  // SLT

    CPrintHelper::GetInstance()->Start();

    if (AX_FALSE == m_avs.StartAVSCalibrate()) {
        LOG_MM_E(PPL, "Start AVS calibrate failed.");
        return AX_FALSE;
    }

    PostStartProcess();

    LOG_MM(PPL, "---");

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::Stop(AX_VOID) {
    LOG_MM_C(PPL, "+++");

    CPrintHelper::GetInstance()->Stop();

#ifdef MP4ENC_SUPPORT
    for (auto& pInstance : m_vecMpeg4Instance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }
#endif

#ifndef SLT
    AX_APP_Audio_Stop();
#endif  // SLT

    for (auto& pInstance : m_vecIvesInstance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecDummyEncInstance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }
    if (!m_mgrSensor.Stop()) {
        return AX_FALSE;
    }

    m_avs.StopAVSCalibrate();
    m_avs.Stop();

    for (auto& pInstance : m_vecIvpsInstance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecVencInstance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecJencInstance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }

    if (!m_detector.Stop()) {
        return AX_FALSE;
    }

    for (auto& pInstance : m_vecCollectorInstance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }

#ifndef SLT
    if (!CWebServer::GetInstance()->Stop()) {
        return AX_FALSE;
    }

    if (!CAXRtspServer::GetInstance()->Stop()) {
        return AX_FALSE;
    }
#endif  // SLT

    if (!m_pPoolConfig->Stop()) {
        return AX_FALSE;
    }

    LOG_MM_C(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::Destroy(AX_VOID) {
    LOG_MM_C(PPL, "+++");

#ifndef SLT
    if (!CWebServer::GetInstance()->DeInit()) {
        return AX_FALSE;
    }

    if (!CAXRtspServer::GetInstance()->DeInit()) {
        return AX_FALSE;
    }
#endif  // SLT

#ifdef MP4ENC_SUPPORT
    for (auto& pInstance : m_vecMpeg4Instance) {
        if (!pInstance->DeInit()) {
            return AX_FALSE;
        }
        SAFE_DELETE_PTR(pInstance);
    }
#endif

    for (auto& pInstance : m_vecVencInstance) {
        if (!pInstance->DeInit()) {
            return AX_FALSE;
        }
        SAFE_DELETE_PTR(pInstance);
    }

    for (auto& pInstance : m_vecJencInstance) {
        if (!pInstance->DeInit()) {
            return AX_FALSE;
        }
        SAFE_DELETE_PTR(pInstance);
    }

    for (auto& pInstance : m_vecDummyEncInstance) {
        if (!pInstance->DeInit()) {
            return AX_FALSE;
        }
        SAFE_DELETE_PTR(pInstance);
    }

    m_avs.DeInit();

    if (!m_mgrSensor.DeInit()) {
        return AX_FALSE;
    }

#ifndef SLT
    AX_APP_Audio_Deinit();
#endif  // SLT

    m_capture.DeInit();

    if (!m_detector.DeInit()) {
        return AX_FALSE;
    }

    for (auto& pInstance : m_vecIvesInstance) {
        if (!pInstance->DeInit()) {
            return AX_FALSE;
        }
        SAFE_DELETE_PTR(pInstance);
    }

    for (auto& pInstance : m_vecCollectorInstance) {
        if (!pInstance->DeInit()) {
            return AX_FALSE;
        }
        SAFE_DELETE_PTR(pInstance);
    }

    for (auto& pInstance : m_vecIvpsInstance) {
        if (COptionHelper::GetInstance()->IsEnableOSD()) {
            pInstance->DetachOsdHelper();
        }

        if (!pInstance->DeInit()) {
            return AX_FALSE;
        }
        SAFE_DELETE_PTR(pInstance);
    }

    if (!m_linkage.Release()) {
        return AX_FALSE;
    }

    SAFE_DELETE_PTR(m_pPoolConfig);

    if (!DeInitSysMods()) {
        return AX_FALSE;
    }

    LOG_MM_C(PPL, "---");
    return AX_TRUE;
}

AX_BOOL CPanoBuilder::UpdateRotation(AX_U8 nSnsID, AX_U8 nRotation) {
    //m_mgrSensor.EnableChn(nSnsID, AX_FALSE);

    for (auto pInstance : m_vecVencInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->StopRecv();
        }
    }

    for (auto pInstance : m_vecJencInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->StopRecv();
        }
    }

    m_mgrSensor.UpdateRotation(nSnsID, (AX_VIN_ROTATION_E)nRotation);

    for (auto pInstance : m_vecIvpsInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            for (AX_U8 nChn = 0; nChn < pInstance->GetGrpCfg()->nGrpChnNum; nChn++) {
                /* GDC_ONLINE_VPP mode ,the mask engine don't need enable/disable ivps channel */
                if (AX_FALSE == pInstance->GetGrpCfg()->nMaskEnable) {
                    pInstance->EnableChannel(nChn, AX_FALSE);
                }
            }
        }
    }

    for (auto pInstance : m_vecVencInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->UpdateRotation(nRotation);
        }
    }

    for (auto pInstance : m_vecIvpsInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->UpdateRotation((AX_IVPS_ROTATION_E)nRotation);
        }
    }

    for (auto pInstance : m_vecJencInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->UpdateRotation(nRotation);
        }
    }

    for (auto pInstance : m_vecIvesInstance) {
        if (pInstance->GetGrp() == nSnsID) {
            pInstance->UpdateRotation((AX_IVPS_ROTATION_E)nRotation);
        }
    }

    for (auto pInstance : m_vecVencInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->StartRecv();
        }
    }

    for (auto pInstance : m_vecJencInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->StartRecv();
        }
    }

    for (auto pInstance : m_vecIvpsInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            for (AX_U8 nChn = 0; nChn < pInstance->GetGrpCfg()->nGrpChnNum; nChn++) {
                /* GDC_ONLINE_VPP mode ,the mask engine don't need enable/disable ivps channel */
                if (AX_FALSE == pInstance->GetGrpCfg()->nMaskEnable) {
                    pInstance->EnableChannel(nChn, AX_TRUE);
                }
            }
        }
    }
    for (auto pInstance : m_vecIvpsInstance) {
        if (pInstance->GetSensorSrc() == nSnsID) {
            pInstance->GetOsdHelper()->Refresh();
        }
    }

    //m_mgrSensor.EnableChn(nSnsID, AX_TRUE);

    return AX_TRUE;
}

#ifndef SLT
AX_BOOL CPanoBuilder::ProcessWebOprs(WEB_REQUEST_TYPE_E eReqType, const AX_VOID* pJsonReq, AX_VOID** pResult /*= nullptr*/) {
    std::unique_lock<std::mutex> guard(m_muxWebOperation, std::defer_lock);
    if (!guard.try_lock()) {
        LOG_MM_I(PPL, "Web Operation is processing.");
        return AX_FALSE;
    }
    vector<WEB_REQ_OPERATION_T> vecWebOpr;
    vecWebOpr.clear();
    if (!CWebOptionHelper::GetInstance()->ParseWebRequest(eReqType, pJsonReq, vecWebOpr)) {
        LOG_MM_E(PPL, "Parse web request failed.");
        return AX_FALSE;
    }

    SortOperations(vecWebOpr);

    AX_U32 nOprSize = vecWebOpr.size();
    for (AX_U32 i = 0; i < nOprSize; i++) {
        /* Here only get the last operation results now */
        if (!DispatchOpr(vecWebOpr[i], pResult)) {
            LOG_MM_E(PPL, "Dispatch web operation failed.");
        }
    }

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::DispatchOpr(WEB_REQ_OPERATION_T& tOperation, AX_VOID** pResult /*= nullptr*/) {
    AX_BOOL ret = AX_TRUE;
    WEB_OPERATION_TYPE_E eOperaType = tOperation.GetOperationType();
    switch (eOperaType) {
        case E_WEB_OPERATION_TYPE_SNS_MODE: {
            m_mgrSensor.SwitchSnsMode(tOperation.nSnsID, tOperation.tSnsMode.nSnsMode);
            break;
        }
        case E_WEB_OPERATION_TYPE_CAMERA_FPS: {
            for (AX_U8 i = 0; i < m_mgrSensor.GetSensorCount(); i++) {
                m_mgrSensor.ChangeSnsFps(i, tOperation.tSnsFpsAttr.fSnsFrameRate);
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_SNS_MIRROR_FLIP: {
            m_mgrSensor.ChangeSnsMirrorFlip(tOperation.nSnsID, tOperation.tSnsMirrorFlip.bMirror, tOperation.tSnsMirrorFlip.bFlip);
            break;
        }
        case E_WEB_OPERATION_TYPE_EZOOM: {
            WEB_CAMERA_ATTR_T tCamera = CWebOptionHelper::GetInstance()->GetCamera(tOperation.nSnsID);
            m_mgrSensor.EZoom(tOperation.nSnsID, tOperation.tEZoom.nEZoomRatio, tOperation.tEZoom.nCenterOffsetX, tOperation.tEZoom.nCenterOffsetY);

            /* update web ezoom value */
            tCamera.tEZoomAttr.nEZoomRatio = tOperation.tEZoom.nEZoomRatio;
            tCamera.tEZoomAttr.nCenterOffsetX = tOperation.tEZoom.nCenterOffsetX;
            tCamera.tEZoomAttr.nCenterOffsetY = tOperation.tEZoom.nCenterOffsetY;
            CWebOptionHelper::GetInstance()->SetCamera(tOperation.nSnsID, tCamera);
            break;
        }
        case E_WEB_OPERATION_TYPE_ROTATION: {
            UpdateRotation(tOperation.nSnsID, tOperation.tRotation.nRotation);
            break;
        }
        case E_WEB_OPERATION_TYPE_ENC_TYPE: {
            const AX_U8 nEncoderType = tOperation.tEncType.nEncoderType;
            AX_PAYLOAD_TYPE_E ePayloadType = CAXTypeConverter::Int2EncoderType(nEncoderType);

            for (auto& pVideoInstance : m_vecVencInstance) {
                if (pVideoInstance->GetChannel() == tOperation.nChannel) {
                    VIDEO_CONFIG_T tConfig;
                    tConfig.nWidth = pVideoInstance->GetResolution().nWidth;
                    tConfig.nHeight = pVideoInstance->GetResolution().nHeight;
                    pVideoInstance->Stop();
                    CWebServer::GetInstance()->UpdateMediaTypeInPreviewChnMap(tOperation.nSnsID, tOperation.nChannel, nEncoderType);
                    pVideoInstance->UpdatePayloadType(ePayloadType);

                    pVideoInstance->StopRecv();
                    for (auto& obs : m_vecRtspObs) {
                        CAXRtspObserver* pRtstpObserver = static_cast<CAXRtspObserver*>(obs.get());
                        if (pRtstpObserver->IsSame(tOperation.nGroup, tOperation.nChannel)) {
                            pRtstpObserver->UpdateVideoPayloadType(AX_TRUE, ePayloadType);
                            break;
                        }
                    }

                    pVideoInstance->UpdateChnResolution(tConfig);
                    pVideoInstance->StartRecv();
                    break;
                }
            }

            CAXRtspServer::GetInstance()->RestartSessions();

            ret = AX_TRUE;
            break;
        }
        case E_WEB_OPERATION_TYPE_RESOLUTION: {
            /* Change IVPS & VENC channel's resolution */
            IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_VENC, 0, tOperation.nChannel};
            IPC_MOD_INFO_T tPrecedingMod;
            tPrecedingMod.eModType = E_PPL_MOD_TYPE_IVPS;
            if (GetPrecedingMod(tDstMod, tPrecedingMod)) {
                CVideoEncoder* pVencInstance = nullptr;
                for (auto& pInstance : m_vecVencInstance) {
                    if (pInstance->GetChannel() == tOperation.nChannel) {
                        pVencInstance = pInstance;
                        break;
                    }
                }

                /* IVPS disable channel */
                m_vecIvpsInstance[tPrecedingMod.nGroup]->EnableChannel(tPrecedingMod.nChannel, AX_FALSE);

                /* VENC stop receive */
                pVencInstance->StopRecv();

                /*Reset chn fifo*/
                pVencInstance->ResetChn();

                /* IVPS update resolution */
                m_vecIvpsInstance[tPrecedingMod.nGroup]->UpdateChnResolution(tPrecedingMod.nChannel, tOperation.tResolution.nWidth,
                                                                             tOperation.tResolution.nHeight);

                /* VENC update resolution */
                VIDEO_CONFIG_T tConfig;
                tConfig.nWidth = tOperation.tResolution.nWidth;
                tConfig.nHeight = tOperation.tResolution.nHeight;
                pVencInstance->UpdateChnResolution(tConfig);

                /* VENC start receive */
                pVencInstance->StartRecv();

                /* IVPS enable channel */
                m_vecIvpsInstance[tPrecedingMod.nGroup]->EnableChannel(tPrecedingMod.nChannel, AX_TRUE);

                /* OSD update position and size */
                m_vecIvpsInstance[tPrecedingMod.nGroup]->RefreshOSDByResChange();

            } else {
                LOG_MM_N(PPL, "Can not find preceding ivps module for venc unique channel %d.", tOperation.nChannel);
                ret = AX_FALSE;
            }

            break;
        }
        case E_WEB_OPERATION_TYPE_RC_INFO: {
            WEB_VIDEO_ATTR_T tAttr;
            AX_BOOL bFound = CWebOptionHelper::GetInstance()->GetVideoByUniChn(tOperation.nSnsID, tOperation.nChannel, tAttr);
            if (!bFound) {
                LOG_MM_N(PPL, "Can not find vodeo information for venc unique channel %d.", tOperation.nChannel);
                ret = AX_FALSE;
                break;
            }
            /* Change VENC channel's rc info */
            CVideoEncoder* pVencInstance = nullptr;
            for (auto& pInstance : m_vecVencInstance) {
                if (pInstance->GetChannel() == tOperation.nChannel) {
                    pVencInstance = pInstance;
                }
            }

            if (nullptr != pVencInstance) {
                RC_INFO_T tRcInfo;

                tRcInfo.eRcType = tOperation.tRcInfo.eRcType;
                tRcInfo.nMinQp = tOperation.tRcInfo.nMinQp;
                tRcInfo.nMaxQp = tOperation.tRcInfo.nMaxQp;
                tRcInfo.nMinIQp = tOperation.tRcInfo.nMinIQp;
                tRcInfo.nMaxIQp = tOperation.tRcInfo.nMaxIQp;
                tRcInfo.nMinIProp = tOperation.tRcInfo.nMinIProp;
                tRcInfo.nMaxIProp = tOperation.tRcInfo.nMaxIProp;
                tRcInfo.nBitrate = tOperation.tRcInfo.nBitrate;
                LOG_MM_D(PPL, "rcInfo [eRcType:%d, nMinQp:%d,nMaxQp:%d,nMinIQp:%d,nMaxIQp:%d ,nMinIProp:%d,nMaxIProp:%d]", tRcInfo.eRcType,
                         tRcInfo.nMinQp, tRcInfo.nMaxQp, tRcInfo.nMinIQp, tRcInfo.nMaxIQp, tRcInfo.nMinIProp, tRcInfo.nMaxIProp);
                ret = pVencInstance->UpdateRcInfo(tRcInfo);
                tAttr.SetEncRcCfg(tRcInfo);
                CWebOptionHelper::GetInstance()->SetVideoByUniChn(tOperation.nSnsID, tAttr);
            } else {
                ret = AX_FALSE;
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_DAYNIGHT: {
            if (0 == tOperation.tDaynight.nDayNightMode
                || 1 == tOperation.tDaynight.nDayNightMode) {
                for (AX_U8 i = 0; i < m_mgrSensor.GetSensorCount(); i++) {
                    ret = m_mgrSensor.ChangeDaynightMode(i, (AX_DAYNIGHT_MODE_E)tOperation.tDaynight.nDayNightMode);

                    SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T tAttr;

                    tAttr.eType = SNS_SOFT_PHOTOSENSITIVITY_NONE;
                    m_mgrSensor.UpdateSps(i, tAttr);
                }
            }
            else {
                SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T tAttr;

                tAttr.bAutoCtrl = AX_TRUE;
                tAttr.eType = SNS_SOFT_PHOTOSENSITIVITY_WARMLIGHT;
                tAttr.tWarmAttr.nOnLightSensitivity  = 50;
                tAttr.tWarmAttr.nOnLightExpValMax    = 10000446016;//21475403776;
                tAttr.tWarmAttr.nOnLightExpValMid    = 5417253376;//10000446016;
                tAttr.tWarmAttr.nOnLightExpValMin    = 1740800000;
                tAttr.tWarmAttr.nOffLightSensitivity = 50;
                tAttr.tWarmAttr.nOffLightExpValMax   = 939488256;
                tAttr.tWarmAttr.nOffLightExpValMid   = 456960000;
                tAttr.tWarmAttr.nOffLightExpValMin   = 101807424;

                for (AX_U8 i = 0; i < m_mgrSensor.GetSensorCount(); i++) {
                    m_mgrSensor.UpdateSps(i, tAttr);
                }
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_IMAGE_ATTR: {
            CBaseSensor* pSensor = m_mgrSensor.GetSnsInstance(tOperation.nSnsID);
            if (nullptr != pSensor) {
                if (0 == tOperation.tImageAttr.nAutoMode) {
                    /* manual mode*/
                    APP_ISP_IMAGE_ATTR_T tImgAttr;
                    tImgAttr.nAutoMode = tOperation.tImageAttr.nAutoMode;
                    tImgAttr.nSharpness = tOperation.tImageAttr.nSharpness;
                    tImgAttr.nBrightness = tOperation.tImageAttr.nBrightness;
                    tImgAttr.nContrast = tOperation.tImageAttr.nContrast;
                    tImgAttr.nSaturation = tOperation.tImageAttr.nSaturation;

                    ret = pSensor->SetIspImageAttr(tImgAttr);
                } else {
                    /* auto mode */
                    WEB_CAMERA_ATTR_T tCamera = CWebOptionHelper::GetInstance()->GetCamera(tOperation.nSnsID);

                    APP_ISP_IMAGE_ATTR_T tImgAttr;
                    tImgAttr.nAutoMode = tOperation.tImageAttr.nAutoMode;
                    ret = pSensor->RestoreIspImageAttr(tImgAttr);

                    /* update web imageAttr value */
                    tCamera.tImageAttr.nAutoMode = tOperation.tImageAttr.nAutoMode;
                    tCamera.tImageAttr.nSharpness = tImgAttr.nSharpness;
                    tCamera.tImageAttr.nBrightness = tImgAttr.nBrightness;
                    tCamera.tImageAttr.nContrast = tImgAttr.nContrast;
                    tCamera.tImageAttr.nSaturation = tImgAttr.nSaturation;
                    CWebOptionHelper::GetInstance()->SetCamera(tOperation.nSnsID, tCamera);
                }
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_LDC_ATTR: {
            m_mgrSensor.UpdateLDC(tOperation.nSnsID, tOperation.tLdcAttr.bLdcEnable, tOperation.tLdcAttr.bLdcAspect,
                                  tOperation.tLdcAttr.nXRatio, tOperation.tLdcAttr.nYRatio, tOperation.tLdcAttr.nXYRatio,
                                  tOperation.tLdcAttr.nDistorRatio);
            break;
        }
        case E_WEB_OPERATION_TYPE_DIS_ATTR: {
            m_mgrSensor.UpdateDIS(tOperation.nSnsID, tOperation.tDisAttr.bDisEnable);
            break;
        }
        case E_WEB_OPERATION_TYPE_NR_MODE: {
            // m_mgrSensor.ChangeNRMode(tOperation.tNR.nNRMode);
            LOG_MM_W(PPL, "E_WEB_OPERATION_TYPE_NR_MODE unsupport.");
            ret = AX_FALSE;
            break;
        }
        case E_WEB_OPERATION_TYPE_CAPTURE_ENABLE: {
            CWebServer::GetInstance()->EnableCaptrue(tOperation.nSnsID, tOperation.tCapEnable.bOn);
            break;
        }
        case E_WEB_OPERATION_TYPE_AI_ENABLE: {
            m_detector.Enable(tOperation.nSnsID, tOperation.tAiEnable.bOn);

            for (auto& pInstance : m_vecIvpsInstance) {
                if (pInstance->GetGrpCfg()->nSnsSrc == tOperation.nSnsID) {
                    if (pInstance->GetOsdHelper()) {
                        pInstance->GetOsdHelper()->EnableAiRegion(tOperation.tAiEnable.bOn);
                    }
                }
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_AI_PUSH_MODE: {
            m_detector.SetSkelPushMode(tOperation.nSnsID, tOperation.tAiPushStategy);
            break;
        }
        case E_WEB_OPERATION_TYPE_AI_EVENT: {
            if (-1 == tOperation.nSnsID) {
                for (auto& pInstance : m_vecIvesInstance) {
                    if (!((tOperation.tEvent.tMD.bEnable == AX_FALSE) && (pInstance->GetMDCapacity() == tOperation.tEvent.tMD.bEnable))) {
                        pInstance->SetMDCapacity((AX_BOOL)tOperation.tEvent.tMD.bEnable);
                        if (AX_TRUE == pInstance->GetMDCapacity()) {
                            for (AX_S32 i = 0; i < pInstance->GetMDInstance()->GetAreaCount(); i++) {
                                pInstance->GetMDInstance()->SetThresholdY(tOperation.nSnsID, i, tOperation.tEvent.tMD.nThrsHoldY,
                                                                          tOperation.tEvent.tMD.nConfidence);
                            }
                        }
                    }

                    if (!((tOperation.tEvent.tOD.bEnable == AX_FALSE) && (pInstance->GetODCapacity() == tOperation.tEvent.tOD.bEnable))) {
                        pInstance->SetODCapacity((AX_BOOL)tOperation.tEvent.tOD.bEnable);
                        if (AX_TRUE == pInstance->GetODCapacity()) {
                            for (AX_S32 i = 0; i < pInstance->GetODInstance()->GetAreaCount(); i++) {
                                pInstance->GetODInstance()->SetThresholdY(tOperation.nSnsID, i, tOperation.tEvent.tOD.nThrsHoldY,
                                                                          tOperation.tEvent.tOD.nConfidence);
                            }
                        }
                    }

                    if (!((tOperation.tEvent.tOD.bEnable == AX_FALSE) && (pInstance->GetSCDCapacity() == tOperation.tEvent.tSCD.bEnable))) {
                        pInstance->SetSCDCapacity((AX_BOOL)tOperation.tEvent.tSCD.bEnable);
                        if (AX_TRUE == pInstance->GetSCDCapacity()) {
                            pInstance->GetSCDInstance()->SetThreshold(tOperation.nSnsID, tOperation.tEvent.tSCD.nThrsHoldY,
                                                                      tOperation.tEvent.tSCD.nConfidence);
                        }
                    }
                }
            } else {
                CIVESStage* pInstance{nullptr};
                try {
                    pInstance = m_vecIvesInstance.at(tOperation.nSnsID);
                } catch (std::out_of_range& e) {
                    LOG_MM_E(PPL, "nSnsID out of range %d. error: %s", tOperation.nSnsID, e.what());
                    ret = AX_FALSE;
                    break;
                }

                if (!((tOperation.tEvent.tMD.bEnable == AX_FALSE) && (pInstance->GetMDCapacity() == tOperation.tEvent.tMD.bEnable))) {
                    pInstance->SetMDCapacity((AX_BOOL)tOperation.tEvent.tMD.bEnable);
                    if (AX_TRUE == pInstance->GetMDCapacity()) {
                        for (AX_S32 i = 0; i < pInstance->GetMDInstance()->GetAreaCount(); i++) {
                            pInstance->GetMDInstance()->SetThresholdY(tOperation.nSnsID, i, tOperation.tEvent.tMD.nThrsHoldY,
                                                                      tOperation.tEvent.tMD.nConfidence);
                        }
                    }
                }

                if (!((tOperation.tEvent.tOD.bEnable == AX_FALSE) && (pInstance->GetODCapacity() == tOperation.tEvent.tOD.bEnable))) {
                    pInstance->SetODCapacity((AX_BOOL)tOperation.tEvent.tOD.bEnable);
                    if (AX_TRUE == pInstance->GetODCapacity()) {
                        for (AX_S32 i = 0; i < pInstance->GetODInstance()->GetAreaCount(); i++) {
                            pInstance->GetODInstance()->SetThresholdY(tOperation.nSnsID, i, tOperation.tEvent.tOD.nThrsHoldY,
                                                                      tOperation.tEvent.tOD.nConfidence);
                        }
                    }
                }

                if (!((tOperation.tEvent.tOD.bEnable == AX_FALSE) && (pInstance->GetSCDCapacity() == tOperation.tEvent.tSCD.bEnable))) {
                    pInstance->SetSCDCapacity((AX_BOOL)tOperation.tEvent.tSCD.bEnable);
                    if (AX_TRUE == pInstance->GetSCDCapacity()) {
                        pInstance->GetSCDInstance()->SetThreshold(tOperation.nSnsID, tOperation.tEvent.tSCD.nThrsHoldY,
                                                                  tOperation.tEvent.tSCD.nConfidence);
                    }
                }
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_AI_AE_ROI: {
            AX_APP_ALGO_HVCFP_PARAM_T stParam = ALGO_HVCFP_PARAM(tOperation.nSnsID);

            stParam.stAeRoiConfig[AX_APP_ALGO_HVCFP_BODY].bEnable = tOperation.tAiAeRoi.bEnable;
            stParam.stAeRoiConfig[AX_APP_ALGO_HVCFP_BODY].nWidth = tOperation.tAiAeRoi.nWidth;
            stParam.stAeRoiConfig[AX_APP_ALGO_HVCFP_BODY].nHeight = tOperation.tAiAeRoi.nHeight;

            SET_ALGO_HVCFP_PARAM(tOperation.nSnsID, stParam);

            m_detector.SetAeRoiAttr(tOperation.nSnsID, stParam.stAeRoiConfig);
            break;
        }
        case E_WEB_OPERATION_TYPE_OSD_ATTR: {
            for (auto& pInstance : m_vecIvpsInstance) {
                if (pInstance->GetGrpCfg()->nSnsSrc == tOperation.nSnsID && pInstance->GetGrpCfg()->nGrp == tOperation.nGroup) {
                    if (pInstance->GetOsdHelper()) {
                        pInstance->GetOsdHelper()->Refresh();
                    }
                }
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_CHANNEL_SWITCH: {
            /* Open or Close IVPS channel */
            IPC_MOD_INFO_T tDstMod;
            if (1 == tOperation.tChnSwitch.nEncoderType) {
                tDstMod = {E_PPL_MOD_TYPE_MJENC, 0, tOperation.nChannel};
            } else {
                tDstMod = {E_PPL_MOD_TYPE_VENC, 0, tOperation.nChannel};
            }

            IPC_MOD_INFO_T tPrecedingMod;
            tPrecedingMod.eModType = E_PPL_MOD_TYPE_IVPS;
            if (GetPrecedingMod(tDstMod, tPrecedingMod)) {
                /* IVPS disable channel */
                m_vecIvpsInstance[tPrecedingMod.nGroup]->EnableChannel(tPrecedingMod.nChannel, tOperation.tChnSwitch.bOn);
            } else {
                LOG_MM_N(PPL, "Can not find preceding ivps module for venc/mjpeg unique channel %d.", tOperation.nChannel);
                ret = AX_FALSE;
            }

            WEB_VIDEO_ATTR_T tAttr;
            AX_BOOL bFound = CWebOptionHelper::GetInstance()->GetVideoByUniChn(tOperation.nSnsID, tOperation.nChannel, tAttr);
            if (!bFound) {
                LOG_MM_N(PPL, "Can not find vodeo information for venc unique channel %d.", tOperation.nChannel);
                ret = AX_FALSE;
                break;
            }
            /* Change VENC channel's bitrate */
            CVideoEncoder* pVencInstance = nullptr;
            for (auto& pInstance : m_vecVencInstance) {
                if (pInstance->GetChannel() == tAttr.nUniChn) {
                    pVencInstance = pInstance;
                }
            }

            if (nullptr != pVencInstance) {
                pVencInstance->GetChnCfg()->bEnable = tOperation.tChnSwitch.bOn;
                break;
            } else {
                ret = AX_FALSE;
            }
            break;
        }
        case E_WEB_OPERATION_TYPE_GET_RESOLUTION: {
            WEB_VIDEO_ATTR_T tAttr;
            AX_BOOL bFound = CWebOptionHelper::GetInstance()->GetVideoByUniChn(tOperation.nSnsID, tOperation.nChannel, tAttr);
            if (!bFound) {
                LOG_MM_N(PPL, "Can not find vodeo information for venc unique channel %d.", tOperation.nChannel);
                ret = AX_FALSE;
                break;
            }

            AX_U8 nRotation = CWebOptionHelper::GetInstance()->GetCamera(tOperation.nSnsID).nRotation;
            if (AX_IVPS_ROTATION_90 == nRotation || AX_IVPS_ROTATION_270 == nRotation) {
                ::swap(tAttr.nWidth, tAttr.nHeight);
            }

            /* TODO: Resolution relies on rotation and fbc configurations */
            tOperation.tGetResolution.nWidth = tAttr.nWidth;
            tOperation.tGetResolution.nHeight = tAttr.nHeight;

            sprintf((AX_CHAR*)pResult, "%dx%d", tAttr.nWidth, tAttr.nHeight);

            break;
        }
        case E_WEB_OPERATION_TYPE_GET_TITLE: {
            PPL_CONFIG_T tPPLConfig;
            m_pPPLConfig->GetPPLConfig(tPPLConfig);
            std::string szTitleName = tPPLConfig.strAppName + "-" + tPPLConfig.strPPLName;
            sprintf((AX_CHAR*)pResult, "%s", szTitleName.c_str());
            break;
        }
        case E_WEB_OPERATION_TYPE_CAPTURE: {
            IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_CAPTURE, 0, 0};
            std::vector<IPC_MOD_RELATIONSHIP_T> vecCaptureRelations;
            if (!GetRelationsByDstMod(tDstMod, vecCaptureRelations, AX_TRUE)) {
                ret = AX_FALSE;
                break;
            }
            AX_BOOL bFound = AX_FALSE;
            AX_S32 nIvpsGroup = -1;
            AX_S32 nIvpsChannel = -1;
            for (auto& captureRelation : vecCaptureRelations) {
                for (auto& pInstance : m_vecIvpsInstance) {
                    if ((pInstance->GetGrpCfg()->nSnsSrc == tOperation.nSnsID) &&
                        (pInstance->GetGrpCfg()->nGrp == captureRelation.tSrcModChn.nGroup)) {
                        nIvpsGroup = captureRelation.tSrcModChn.nGroup;
                        nIvpsChannel = captureRelation.tSrcModChn.nChannel;
                        bFound = AX_TRUE;
                    }
                }
            }
            if (!bFound) {
                ret = AX_FALSE;
                break;
            }
            IPC_MOD_INFO_T tIvpsMod = {E_PPL_MOD_TYPE_IVPS, nIvpsGroup, nIvpsChannel};
            AX_U32 nQpLevel = COptionHelper::GetInstance()->GetSnapShotQpLevel();
            std::vector<IPC_MOD_RELATIONSHIP_T> vecIvpsRelations;
            if (GetRelationsBySrcMod(tIvpsMod, vecIvpsRelations, AX_TRUE)) {
                for (auto& ivpsRelation : vecIvpsRelations) {
                    if (ivpsRelation.tDstModChn.eModType == E_PPL_MOD_TYPE_VENC) {
                        m_linkage.SetLinkMode(E_PPL_MOD_TYPE_VENC, ivpsRelation.tDstModChn.nChannel, AX_FALSE);
                        m_capture.CapturePicture(tOperation.nSnsID, nIvpsChannel, nQpLevel, pResult);
                        m_linkage.SetLinkMode(E_PPL_MOD_TYPE_VENC, ivpsRelation.tDstModChn.nChannel, AX_TRUE);
                        break;
                    }
                }
            }

            ret = AX_TRUE;
            break;
        }
        case E_WEB_OPERATION_TYPE_AUDIO_ATTR: {
            AX_APP_ALGO_AUDIO_PARAM_T stAttr;

            AX_APP_Audio_GetAedAttr(&stAttr);

            stAttr.bEnable = (AX_BOOL)tOperation.tAudioAttr.nAedEnable;
            stAttr.fThreshold = (AX_F32)tOperation.tAudioAttr.nAedThreshold;
            stAttr.nInterval = (AX_U32)tOperation.tAudioAttr.nAedInterval;

            AX_APP_Audio_SetAedAttr(&stAttr);

            AX_APP_Audio_SetCapVolume((AX_F32)tOperation.tAudioAttr.nCapture_volume);
            AX_APP_Audio_SetPlayVolume((AX_F32)tOperation.tAudioAttr.nPlay_volume);
            ret = AX_TRUE;
            break;
        }
        case E_WEB_OPERATION_TYPE_SWITCH_3A_SYNC: {
            m_mgrSensor.SetMuliSns3ASync(tOperation.b3ASyncOn);
            break;
        }

        default:
            LOG_MM_E(PPL, "eReqType:%d is nonsupport.", eOperaType);
            ret = AX_FALSE;
            break;
    }

    if (ret && ((E_REQ_TYPE_CAMERA == tOperation.eReqType && (E_WEB_OPERATION_TYPE_SNS_MODE == tOperation.GetOperationType() ||
            E_WEB_OPERATION_TYPE_ROTATION == tOperation.GetOperationType())) || E_REQ_TYPE_VIDEO == tOperation.eReqType)) {
        /*notify web restart preview*/
        WEB_EVENTS_DATA_T event;
        event.eType = E_WEB_EVENTS_TYPE_ReStartPreview;
        event.nReserved = tOperation.nSnsID;
        CWebServer::GetInstance()->SendEventsData(&event);
    }

    return ret;
}

AX_BOOL CPanoBuilder::ProcessTestSuiteOpers(WEB_REQ_OPERATION_T& tOperation) {
    return DispatchOpr(tOperation, nullptr);
}

AX_VOID CPanoBuilder::SortOperations(vector<WEB_REQ_OPERATION_T>& vecWebRequests) {
    std::sort(vecWebRequests.begin(), vecWebRequests.end(),
              [](WEB_REQ_OPERATION_T t1, WEB_REQ_OPERATION_T t2) { return t1.nPriority > t2.nPriority; });
}
#endif  // SLT

AX_VOID CPanoBuilder::PostStartProcess(AX_VOID) {
    AX_U32 nSnsCnt = m_mgrSensor.GetSensorCount();

    // update rotation
    for (AX_U32 i = 0; i < nSnsCnt; i++) {
        SENSOR_CONFIG_T tSensorCfg;
        APP_SENSOR_CONFIG(i, tSensorCfg);

        if (tSensorCfg.eRotation != AX_ROTATION_0) {
            UpdateRotation(i, tSensorCfg.eRotation);
        }
    }

    for (AX_U32 i = 0; i < nSnsCnt; i++) {
        CBaseSensor* pSensor = m_mgrSensor.GetSnsInstance(i);

        WEB_CAMERA_ATTR_T tCamera = CWebOptionHelper::GetInstance()->GetCamera(i);
        APP_ISP_IMAGE_ATTR_T tImgAttr;
        pSensor->GetIspImageAttr(tImgAttr);
        tCamera.tImageAttr.nAutoMode = tImgAttr.nAutoMode;
        tCamera.tImageAttr.nSharpness = tImgAttr.nSharpness;
        tCamera.tImageAttr.nBrightness = tImgAttr.nBrightness;
        tCamera.tImageAttr.nContrast = tImgAttr.nContrast;
        tCamera.tImageAttr.nSaturation = tImgAttr.nSaturation;
        CWebOptionHelper::GetInstance()->SetCamera(i, tCamera);
    }
}

AX_BOOL CPanoBuilder::InitSysMods(AX_VOID) {
    LOG_MM(PPL, "+++");

    m_arrMods.clear();
    m_arrMods.push_back({AX_FALSE, "LOG", bind(&CPanoBuilder::APP_LOG_Init, this), bind(&CPanoBuilder::APP_LOG_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "SYS", bind(&CPanoBuilder::APP_SYS_Init, this), bind(&CPanoBuilder::APP_SYS_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "NPU", bind(&CPanoBuilder::APP_NPU_Init, this), bind(&CPanoBuilder::APP_NPU_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "VIN", AX_VIN_Init, AX_VIN_Deinit});
    m_arrMods.push_back({AX_FALSE, "VIN_Stitch", bind(&CPanoBuilder::APP_VIN_Stitch_Attr_Init, this), bind(&CPanoBuilder::APP_VIN_Stitch_Attr_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "MIPI_RX", AX_MIPI_RX_Init, AX_MIPI_RX_DeInit});
    m_arrMods.push_back({AX_FALSE, "IVPS", AX_IVPS_Init, AX_IVPS_Deinit});
    m_arrMods.push_back({AX_FALSE, "VENC", bind(&CPanoBuilder::APP_VENC_Init, this), bind(&CPanoBuilder::APP_VENC_DeInit, this)});
#ifdef JDEC_SUPPORT
    m_arrMods.push_back({AX_FALSE, "VDEC", bind(&CPanoBuilder::APP_VDEC_Init, this), bind(&CPanoBuilder::APP_VDEC_DeInit, this)});
#endif

#ifndef SLT
    m_arrMods.push_back({AX_FALSE, "ACAP", bind(&CPanoBuilder::APP_ACAP_Init, this), bind(&CPanoBuilder::APP_ACAP_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "APLAY", bind(&CPanoBuilder::APP_APLAY_Init, this), bind(&CPanoBuilder::APP_APLAY_DeInit, this)});
#endif  // SLT

    for (auto& m : m_arrMods) {
        AX_S32 ret = m.Init();
        if (0 != ret) {
            LOG_MM_E(PPL, "%s: init module %s fail, ret = 0x%x", __func__, m.strName.c_str(), ret);
            return AX_FALSE;
        } else {
            LOG_MM_W(PPL, "%s: init module %s OK", __func__, m.strName.c_str());
            m.bInited = AX_TRUE;
        }
    }

    m_pPPLConfig->Init();
    CIVESStage::InitModule();

    std::map<AX_U8, SENSOR_VINIVPS_CFG_T> mapVinIvps = CSensorOptionHelper::GetInstance()->GetMapVinIvps();
    for (auto& m : mapVinIvps) {
        AX_U8 nVinId = m.first;
        AX_U8 nIvpsId = m.second.nIvpsGrp;
        AX_S8 nVinIvpsMode = m.second.nVinIvpsMode;
        if (-1 != nVinIvpsMode) {
            AX_SYS_SetVINIVPSMode(nVinId, nIvpsId, (AX_VIN_IVPS_MODE_E)nVinIvpsMode);
            LOG_MM_I(PPL, "AX_SYS_SetVINIVPSMode nVinId:%d, nIvpsId:%d, nVinIvpsMode:%d", nVinId, nIvpsId, nVinIvpsMode);
        }
    }
    LOG_MM(PPL, "---");

    return AX_TRUE;
}

AX_BOOL CPanoBuilder::GetRelationsBySrcMod(IPC_MOD_INFO_T& tSrcMod, vector<PPL_MOD_RELATIONSHIP_T>& vecOutRelations,
                                          AX_BOOL bIgnoreChn /*= AX_FALSE*/) const {
    return m_linkage.GetRelationsBySrcMod(tSrcMod, vecOutRelations, bIgnoreChn);
}

AX_BOOL CPanoBuilder::GetRelationsByDstMod(IPC_MOD_INFO_T& tDstMod, vector<PPL_MOD_RELATIONSHIP_T>& vecOutRelations,
                                          AX_BOOL bIgnoreChn /*= AX_FALSE*/) const {
    return m_linkage.GetRelationsByDstMod(tDstMod, vecOutRelations, bIgnoreChn);
}

AX_BOOL CPanoBuilder::GetPrecedingMod(const IPC_MOD_INFO_T& tDstMod, IPC_MOD_INFO_T& tPrecedingMod) {
    return m_linkage.GetPrecedingMod(tDstMod, tPrecedingMod);
}

AX_BOOL CPanoBuilder::DeInitSysMods(AX_VOID) {
    LOG_MM_C(PPL, "+++");

    CIVESStage::DeinitModule();
    const auto nSize = m_arrMods.size();
    if (0 == nSize) {
        return AX_TRUE;
    }

    for (AX_S32 i = (AX_S32)(nSize - 1); i >= 0; --i) {
        if (m_arrMods[i].bInited) {
            AX_S32 ret = m_arrMods[i].DeInit();
            if (0 != ret) {
                LOG_MM_E(PPL, "%s: deinit module %s fail, ret = 0x%x", __func__, m_arrMods[i].strName.c_str(), ret);
                return AX_FALSE;
            } else {
                LOG_MM_W(PPL, "%s: deinit module %s OK", __func__, m_arrMods[i].strName.c_str());
            }

            m_arrMods[i].bInited = AX_FALSE;
        }
    }

    m_arrMods.clear();

    LOG_MM_C(PPL, "---");
    return AX_TRUE;
}

AX_S32 CPanoBuilder::APP_SYS_Init() {
    AX_S32 nRet = AX_SUCCESS;

    nRet = AX_SYS_Init();
    if (0 != nRet) {
        return nRet;
    }

    AX_APP_Log_SetSysModuleInited(AX_TRUE);

    nRet = AX_POOL_Exit();
    if (0 != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_SYS_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    nRet = AX_POOL_Exit();
    if (0 != nRet) {
        return nRet;
    }

    AX_APP_Log_SetSysModuleInited(AX_FALSE);

    nRet = AX_SYS_Deinit();
    if (0 != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_VENC_Init() {
    AX_S32 nRet = AX_SUCCESS;

    AX_VENC_MOD_ATTR_T tModAttr;
    memset(&tModAttr, 0, sizeof(AX_VENC_MOD_ATTR_T));
    tModAttr.enVencType = AX_VENC_MULTI_ENCODER;
    tModAttr.stModThdAttr.bExplicitSched = AX_FALSE;
    tModAttr.stModThdAttr.u32TotalThreadNum = COptionHelper::GetInstance()->GetVencThreadNum();

    nRet = AX_VENC_Init(&tModAttr);
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_VENC_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    nRet = AX_VENC_Deinit();
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

#ifdef JDEC_SUPPORT
AX_S32 CPanoBuilder::APP_VDEC_Init() {
    AX_S32 nRet = AX_SUCCESS;

    AX_VDEC_MOD_ATTR_T tModAttr;
    memset(&tModAttr, 0, sizeof(AX_VDEC_MOD_ATTR_T));
    tModAttr.u32MaxGroupCount = 1;

    nRet = AX_VDEC_Init(&tModAttr);
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_VDEC_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    nRet = AX_VDEC_Deinit();
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}
#endif

AX_S32 CPanoBuilder::APP_NPU_Init() {
    AX_S32 nRet = AX_SUCCESS;

    AX_ENGINE_NPU_ATTR_T attr;
    memset(&attr, 0, sizeof(AX_ENGINE_NPU_ATTR_T));
    attr.eHardMode = AX_ENGINE_VIRTUAL_NPU_ENABLE;
    nRet = AX_ENGINE_Init(&attr);


    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_NPU_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    nRet = AX_ENGINE_Deinit();
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_BOOL CPanoBuilder::GetEncoder(AX_VOID **ppEncoder, AX_BOOL *pIsJenc, AX_S32 encoderChn) {
    if (nullptr == ppEncoder) {
        LOG_M_E(PPL, "ppEncoder is null.");
        return AX_FALSE;
    }

    *pIsJenc = AX_FALSE;

    for (auto jencIns : m_vecJencInstance) {
        if (jencIns->GetChnCfg()->nChannel == encoderChn) {
            *ppEncoder = (AX_VOID *)jencIns;
            *pIsJenc = AX_TRUE;
            return AX_TRUE;
        }
    }

    for (auto vencIns : m_vecVencInstance) {
        if (vencIns->GetChnCfg()->nChannel == encoderChn) {
            *ppEncoder = (AX_VOID *)vencIns;
            return AX_TRUE;
        }
    }

    *ppEncoder = nullptr;
    return AX_FALSE;
}

AX_VOID CPanoBuilder::UpdateEncoderResolution(AX_VOID *pEncoder, AX_BOOL bJenc, AX_S32 nSrcGrp, AX_S32 srcChn) {
    if (nullptr == pEncoder) {
        LOG_M_E(PPL, "pEncoder is null.");
        return;
    }

    if (bJenc) {
        CJpegEncoder *pJenc = (CJpegEncoder *)pEncoder;
        JPEG_CONFIG_T* pConfig = pJenc->GetChnCfg();
        UpdateEncoderResolution((CJpegEncoder *)pEncoder, (JPEG_CONFIG_T *)pConfig, nSrcGrp, srcChn);
    } else {
        CVideoEncoder *pVenc = (CVideoEncoder *)pEncoder;
        VIDEO_CONFIG_T* pConfig = pVenc->GetChnCfg();
        UpdateEncoderResolution((CVideoEncoder *)pEncoder, (VIDEO_CONFIG_T *)pConfig, nSrcGrp, srcChn);
    }
}

template<typename T1, typename T2>
AX_VOID CPanoBuilder::UpdateEncoderResolution(T1* pEncoder, T2* pConfig, AX_S32 nSrcGrp, AX_S32 srcChn) {
    AX_APP_AVS_RESOLUTION_T stAvsResolution = m_avs.GetAvsResolution();
    pConfig->nWidth = stAvsResolution.u32Width;
    pConfig->nHeight = stAvsResolution.u32Height;
    m_vecIvpsInstance[nSrcGrp]->EnableChannel(srcChn, AX_FALSE);
    pEncoder->StopRecv();
    pEncoder->ResetChn();
    pEncoder->UpdateChnResolution(*pConfig);
    pEncoder->StartRecv();
    m_vecIvpsInstance[nSrcGrp]->EnableChannel(srcChn, AX_TRUE);
}

AX_BOOL CPanoBuilder::IsNeedUpdate(AX_U8 nGrp, AX_U8 nChn, AX_BOOL bIgnorChn /*= AX_FALSE*/) {
    AX_U32 nCount = m_mmapIVPSMaxResolutionChn.count(nGrp);
    if (0 == nCount) {
        return AX_FALSE;
    } else if (bIgnorChn) {
        return AX_TRUE;
    }

    std::multimap<AX_U8, AX_U8>::iterator it, itBegin, itEnd;
    itBegin = m_mmapIVPSMaxResolutionChn.lower_bound(nGrp);
    itEnd   = m_mmapIVPSMaxResolutionChn.upper_bound(nGrp);
    for (it = itBegin; it != itEnd; it++) {
        if ((*it).second == nChn) {
            return AX_TRUE;
        }
    }

    return AX_FALSE;
}

AX_BOOL CPanoBuilder::UpdateIVPSResolution(const PPL_MOD_INFO_T tSrcMod, const AX_U32 newWidth, const AX_U32 newHeight, AX_BOOL bIgnoreChn) {
    vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
    PPL_MOD_INFO_T tChildSrcMod = tSrcMod;
    if (!GetRelationsBySrcMod(tChildSrcMod, vecRelations, bIgnoreChn)){
        LOG_MM_E(PPL, "GetRelationsBySrcMod fail, tChildSrcMod(%d, %d, %d)",
                       tChildSrcMod.eModType, tChildSrcMod.nGroup, tChildSrcMod.nChannel);
        return AX_FALSE;
    }

    LOG_MM_N(PPL, "Src(%d, %d, %d), newWidth = %d, newHeight = %d",
                   tChildSrcMod.eModType, tChildSrcMod.nGroup,
                   tChildSrcMod.nChannel, newWidth, newHeight);

    for (auto e : vecRelations) {
        if (e.Valid()) {
            if (E_PPL_MOD_TYPE_IVPS == e.tDstModChn.eModType) {
                if (!IsNeedUpdate(e.tDstModChn.nGroup, e.tDstModChn.nChannel, AX_TRUE)) {
                    continue;
                }
                LOG_MM_N(PPL, "Update ivps Grp(%d)", e.tDstModChn.nGroup);
                IVPS_GROUP_CFG_T* pConfig = m_vecIvpsInstance[e.tDstModChn.nGroup]->GetGrpCfg();
                pConfig->arrGrpResolution[0] = newWidth;
                pConfig->arrGrpResolution[1] = newHeight;
                pConfig->arrChnResolution[0][0] = newWidth;
                pConfig->arrChnResolution[0][1] = newHeight;

                if (!m_vecIvpsInstance[e.tDstModChn.nGroup]->InitParams()) {
                    LOG_MM_E(PPL, "[%d]IVPS Group InitParams failed", e.tDstModChn.nGroup);
                    return AX_FALSE;
                }

                IVPS_GRP_T* pIVPSGrp = m_vecIvpsInstance[e.tDstModChn.nGroup]->GetGrpPPLAttr();
                if (AX_IVPS_SetPipelineAttr(e.tDstModChn.nGroup, &pIVPSGrp->tPipelineAttr)) {
                    LOG_MM_E(PPL, "AX_IVPS_GetPipelineAttr failed");
                    return AX_FALSE;
                }

                for (AX_U8 i = 0; i < pConfig->nGrpChnNum; i++) {
                    if (!IsNeedUpdate(e.tDstModChn.nGroup, i)) {
                        continue;
                    }
                    LOG_MM_N(PPL, "Update ivps(%d) with chn(%d)", e.tDstModChn.nGroup, i);
                    m_vecIvpsInstance[e.tDstModChn.nGroup]->EnableChannel(i, AX_FALSE);
                    m_vecIvpsInstance[e.tDstModChn.nGroup]->UpdateChnResolution(i, newWidth, newHeight);
                    m_vecIvpsInstance[e.tDstModChn.nGroup]->EnableChannel(i, AX_TRUE);
                    m_vecIvpsInstance[e.tDstModChn.nGroup]->RefreshOSDByResChange();

                    tChildSrcMod = {E_PPL_MOD_TYPE_IVPS, e.tDstModChn.nGroup, i};
                    UpdateIVPSResolution(tChildSrcMod, newWidth, newHeight, AX_FALSE);
                }
            } else if (E_PPL_MOD_TYPE_VENC == e.tDstModChn.eModType || E_PPL_MOD_TYPE_JENC == e.tDstModChn.eModType) {
                LOG_MM_N(PPL, "Update encoder(%d, %d) linked to ivps(%d, %d)",
                               e.tDstModChn.nGroup, e.tDstModChn.nChannel,
                               e.tSrcModChn.nGroup, e.tSrcModChn.nChannel);
                AX_VOID* pEncoder = nullptr;
                AX_BOOL bIsJpeg = AX_FALSE;
                if (!GetEncoder(&pEncoder, &bIsJpeg, e.tDstModChn.nChannel)) {
                    continue;
                }
                LOG_MM_N(PPL, "bIsJpeg: %d", bIsJpeg);
                UpdateEncoderResolution(pEncoder, bIsJpeg, tChildSrcMod.nGroup, tChildSrcMod.nChannel);
            } else if (E_PPL_MOD_TYPE_CAPTURE == e.tDstModChn.eModType) {
                LOG_MM_N(PPL, "Update Capture linked to ivps(%d, %d)", e.tSrcModChn.nGroup, e.tSrcModChn.nChannel);
                m_vecIvpsInstance[e.tSrcModChn.nGroup]->RegObserver(e.tSrcModChn.nChannel, m_vecCaptureObs[0].get());
            } else if (e.tDstModChn.eModType == E_PPL_MOD_TYPE_COLLECT) {
                COLLECTOR_ATTR_T* pCollConfig = m_vecCollectorInstance[e.tDstModChn.nGroup]->GetCollectorCfg();
                pCollConfig->nWidth = newWidth;
                pCollConfig->nHeight = newHeight;
                LOG_MM_N(PPL, "Update collect(%d) width:%d, height:%d", e.tDstModChn.nGroup, pCollConfig->nWidth, pCollConfig->nHeight);

                vector<PPL_MOD_RELATIONSHIP_T> vecRelationsCollect;
                tChildSrcMod = {E_PPL_MOD_TYPE_COLLECT, e.tDstModChn.nGroup, 0};
                if (!GetRelationsBySrcMod(tChildSrcMod, vecRelationsCollect, AX_FALSE)) {
                    LOG_MM_E(PPL, "GetRelationsBySrcMod(%d, %d, 0) failed", E_PPL_MOD_TYPE_COLLECT, e.tDstModChn.nGroup);
                    return AX_FALSE;
                }

                for (auto& e : vecRelationsCollect) {
                    if (e.Valid()) {
                        if (!e.bLink) {
                            if (E_PPL_MOD_TYPE_DETECT == e.tDstModChn.eModType) {
                                if (!m_vecDetectorObs.empty()) {
                                    LOG_MM_N(PPL, "Update Detector linked to collect");
                                    m_vecCollectorInstance[e.tSrcModChn.nGroup]->UnregObserver(m_vecDetectorObs[0].get());
                                    m_vecCollectorInstance[e.tSrcModChn.nGroup]->RegObserver(m_vecDetectorObs[0].get());
                                    CWebOptionHelper::GetInstance()->InitAiAttr(m_vecCollectorInstance[e.tSrcModChn.nGroup]->GetGroup());
                                }
                            }

                            if (E_PPL_MOD_TYPE_CAPTURE == e.tDstModChn.eModType) {
                                LOG_MM_N(PPL, "Update Capture linked to collect");
                                m_vecCollectorInstance[e.tSrcModChn.nGroup]->UnregObserver(m_vecCaptureObs[0].get());
                                m_vecCollectorInstance[e.tSrcModChn.nGroup]->RegObserver(m_vecCaptureObs[0].get());
                            }

                            if (E_PPL_MOD_TYPE_IVPS == e.tDstModChn.eModType) {
                                if (!IsNeedUpdate(e.tDstModChn.nGroup, e.tDstModChn.nChannel, AX_TRUE)) {
                                    continue;
                                }
                                LOG_MM_N(PPL, "Update ivps(%d) linked to collect", e.tDstModChn.nGroup);
                                IVPS_GROUP_CFG_T* pConfig = m_vecIvpsInstance[e.tDstModChn.nGroup]->GetGrpCfg();
                                pConfig->arrGrpResolution[0] = newWidth;
                                pConfig->arrGrpResolution[1] = newHeight;
                                pConfig->arrChnResolution[0][0] = newWidth;
                                pConfig->arrChnResolution[0][1] = newHeight;

                                if (!m_vecIvpsInstance[e.tDstModChn.nGroup]->InitParams()) {
                                    LOG_MM_E(PPL, "[%d]IVPS Group InitParams failed", e.tDstModChn.nGroup);
                                    return AX_FALSE;
                                }

                                IVPS_GRP_T* pIVPSGrp = m_vecIvpsInstance[e.tDstModChn.nGroup]->GetGrpPPLAttr();
                                if (AX_IVPS_SetPipelineAttr(e.tDstModChn.nGroup, &pIVPSGrp->tPipelineAttr)) {
                                    LOG_MM_E(PPL, "AX_IVPS_GetPipelineAttr failed");
                                    return AX_FALSE;
                                }

                                for (AX_U8 i = 0; i < pConfig->nGrpChnNum; i++) {
                                    if (!IsNeedUpdate(e.tDstModChn.nGroup, i)) {
                                        continue;
                                    }
                                    LOG_MM_N(PPL, "Update ivps(%d) with chn(%d) linked to collect", e.tDstModChn.nGroup, i);
                                    m_vecIvpsInstance[e.tDstModChn.nGroup]->EnableChannel(i, AX_FALSE);
                                    m_vecIvpsInstance[e.tDstModChn.nGroup]->UpdateChnResolution(i, newWidth, newHeight);
                                    m_vecIvpsInstance[e.tDstModChn.nGroup]->EnableChannel(i, AX_TRUE);
                                    m_vecIvpsInstance[e.tDstModChn.nGroup]->RefreshOSDByResChange();

                                    tChildSrcMod = {E_PPL_MOD_TYPE_IVPS, e.tDstModChn.nGroup, i};
                                    UpdateIVPSResolution(tChildSrcMod, newWidth, newHeight, AX_FALSE);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return AX_TRUE;
}

AX_VOID CPanoBuilder::CalibrateDone(AX_S32 s32Result, AX_AVSCALI_AVS_PARAMS_T* pAVSParams, AX_AVSCALI_3A_SYNC_RATIO_T* pSyncRatio, AX_VOID* pPrivData) {
    if (AX_SUCCESS != s32Result) {
        LOG_M_E(PPL, "AVS calibration failure, s32Result 0x%x", s32Result);
        return;
    }

    if (nullptr == pPrivData) {
        LOG_M_E(PPL, "Error, pPrivData in null!");
        return;
    }

    string strCaliDataPath = CCommonUtils::GetPathFromFileName(pAVSParams->tMeshFileInfo.strMeshFile[0]);
    if (strCaliDataPath.empty()) {
        LOG_MM_E(PPL, "Fail to get cali data path!");
        return;
    }

    CPanoBuilder* pPanoBuilder = (CPanoBuilder *)pPrivData;

    pPanoBuilder->m_avs.Stop();
    pPanoBuilder->m_avs.DeInit();
    pPanoBuilder->m_avs.LoadParam(strCaliDataPath);

    AX_APP_AVS_RESOLUTION_T stAvsResolution = pPanoBuilder->m_avs.GetAvsResolution();

    LOG_M_D(PPL, "Calibration completed, width = %d, height = %d", stAvsResolution.u32Width, stAvsResolution.u32Height);

    vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
    PPL_MOD_INFO_T tSrcMod = {E_PPL_MOD_TYPE_AVS, 0, 0};
    pPanoBuilder->UpdateIVPSResolution(tSrcMod, stAvsResolution.u32Width, stAvsResolution.u32Height, AX_TRUE);

    SNS_TYPE_E eSnsType = pPanoBuilder->m_mgrSensor.GetSnsInstance(0)->GetSnsConfig().eSensorType;
    CWebOptionHelper::GetInstance()->SetSnsTypeMainResolution(eSnsType,
                                                              stAvsResolution.u32Width,
                                                              stAvsResolution.u32Height);
    CWebOptionHelper::GetInstance()->GetVideo(0, 0).nWidth = stAvsResolution.u32Width;
    CWebOptionHelper::GetInstance()->GetVideo(0, 0).nHeight = stAvsResolution.u32Height;

    pPanoBuilder->m_avs.Start();

    WEB_EVENTS_DATA_T event;
    event.eType = E_WEB_EVENTS_TYPE_ReStartPreview;
    event.nReserved = 0;
    CWebServer::GetInstance()->SendEventsData(&event);
}

AX_BOOL CPanoBuilder::InitAvs() {
    AX_APP_AVS_ATTR_T stAvsAttr;
    AX_APP_AVS_CFG_T stAVSCfg = APP_AVS_ATTR();

    stAvsAttr.bSyncPipe = (AX_BOOL)APP_AVS_IS_SYNC_PIPE();
    stAvsAttr.enMode = (AX_AVS_MODE_E)APP_AVS_MODE();
    stAvsAttr.enBlendMode = (AX_AVS_BLEND_MODE_E)APP_AVS_BLEND_MODE();
    stAvsAttr.enParamType = (AX_APP_AVS_PARAM_TYPE_E)APP_AVS_PARAM_TYPE();
    stAvsAttr.bDynamicSeam =  APP_AVS_IS_DYNAMIC_SEAM();
    stAvsAttr.enProjectionType = APP_AVS_PROJECTION_TYPE();
    stAvsAttr.stAvsCompress = stAVSCfg.stAvsCompress;
    stAvsAttr.u8CaliEnable = stAVSCfg.u8CaliEnable;

    string strCaliDataPath = APP_AVS_PARAM_FILE_PATH();
    AX_U16 nPathLen = strCaliDataPath.length();
    if (strCaliDataPath.length() > (AX_AVSCALI_MAX_PATH_LEN - 1)) {
        LOG_M_E(PPL, "strCaliDataPath(%s) length(%d) exceed %d.",
                      strCaliDataPath.c_str(), nPathLen, (AX_AVSCALI_MAX_PATH_LEN - 1));
        return  AX_FALSE;
    }
    memcpy((void *)stAvsAttr.tCaliInitParam.strCaliDataPath, strCaliDataPath.c_str(), nPathLen);
    stAvsAttr.tCaliInitParam.tCallbacks.CaliDoneCb = &CPanoBuilder::CalibrateDone;
    stAvsAttr.tCaliInitParam.pPrivData = (AX_VOID *)this;

    AX_U32 nISPchn = 0;
    PPL_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_AVS, 0, 0};
    vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
    if (!GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
        LOG_MM_W(PPL, "Can not find relation for dest module: (Module:%s, Grp:%d, Chn:%d)", CAXTypeConverter::ModType2String(tDstMod.eModType).c_str(),
                    tDstMod.nGroup, tDstMod.nChannel);
    }

    if (vecRelations.size() > 0) {
        nISPchn = vecRelations[0].tSrcModChn.nChannel;
    } else {
        LOG_MM_W(PPL, "Can not find relation, set nISPchn to 0 by default.");
    }

    AX_U8 nAVSPipeNum = (vecRelations.size() >= AX_AVS_PIPE_NUM) ? AX_AVS_PIPE_NUM : vecRelations.size();
    LOG_M_D(PPL, "nAVSPipeNum: %d", nAVSPipeNum);

    stAvsAttr.tCaliInitParam.tSnsInfo.nSnsNum = stAvsAttr.u8PipeNum = nAVSPipeNum;

    for (auto& relation : vecRelations) {
        if ((AX_U32)relation.tDstModChn.nChannel < nAVSPipeNum) {
            stAvsAttr.tCaliInitParam.tSnsInfo.arrPipeId[relation.tDstModChn.nChannel] = relation.tSrcModChn.nGroup;
        } else {
            LOG_MM_E(PPL, "Invalid linked avs channel: %d", relation.tDstModChn.nChannel);
        }
    }

    CBaseSensor* pSensor = m_mgrSensor.GetSnsInstance(0); // Ref ppl
    AX_U8 nPipeID = pSensor->GetSnsConfig().arrPipeAttr->nPipeID;
    stAvsAttr.tCaliInitParam.tSnsInfo.nImgWidth  = pSensor->GetChnAttr(nPipeID, nISPchn).nWidth;
    stAvsAttr.tCaliInitParam.tSnsInfo.nImgHeight = pSensor->GetChnAttr(nPipeID, nISPchn).nHeight;
    stAvsAttr.tCaliInitParam.tSnsInfo.nChn       = nISPchn;

    for (AX_U8 j = 0; j < m_mgrSensor.GetSensorCount(); j++) {
        SENSOR_CONFIG_T tSnsCfg = m_mgrSensor.GetSnsInstance(j)->GetSnsConfig();
        if (AX_SNS_SYNC_MASTER == tSnsCfg.nMasterSlaveSel) {
            stAvsAttr.tCaliInitParam.tSnsInfo.nMasterPipeId = tSnsCfg.arrPipeAttr->nPipeID;
        }
    }

    LOG_M_I(PPL, "AVS in img size(%d, %d), Isp chn id: %d, master pipe id: %d, arrPipeId[0]: %d, arrPipeId[1]: %d",
                 stAvsAttr.tCaliInitParam.tSnsInfo.nImgWidth, stAvsAttr.tCaliInitParam.tSnsInfo.nImgHeight,
                 stAvsAttr.tCaliInitParam.tSnsInfo.nChn, stAvsAttr.tCaliInitParam.tSnsInfo.nMasterPipeId,
                 stAvsAttr.tCaliInitParam.tSnsInfo.arrPipeId[0],stAvsAttr.tCaliInitParam.tSnsInfo.arrPipeId[1]);

    stAvsAttr.strCaliServerIP = stAVSCfg.strCaliServerIP;
    stAvsAttr.u16CaliServerPort = stAVSCfg.u16CaliServerPort;

    LOG_M_I(PPL, "u8PipeNum=%d, bSyncPipe=%d, enMode=%d, enBlendMode=%d, enParamType=%d, bDynamicSeam=%d, enProjectionType=%d, avs param path: %s, compress(%d, %d)",
            stAvsAttr.u8PipeNum, stAvsAttr.bSyncPipe,stAvsAttr.enMode,stAvsAttr.enBlendMode,stAvsAttr.enParamType,
            stAvsAttr.bDynamicSeam, stAvsAttr.enProjectionType, stAvsAttr.tCaliInitParam.strCaliDataPath,
            stAvsAttr.stAvsCompress.enCompressMode, stAvsAttr.stAvsCompress.u32CompressLevel);

    if(!m_avs.Init(stAvsAttr)) {
        LOG_M_E(PPL, "Avs initializes failed!");
        return  AX_FALSE;
    }

    AX_AVSCALI_3A_SYNC_RATIO_T t3ASyncRatio = m_avs.Get3ASyncRatio();
    m_mgrSensor.SetAeSyncRatio(t3ASyncRatio.tAESyncRatio);
    m_mgrSensor.SetAwbSyncRatio(t3ASyncRatio.tAWBSyncRatio);

    return AX_TRUE;
}

AX_S32 CPanoBuilder::APP_LOG_Init(AX_VOID) {
    AX_S32 nRet = AX_SUCCESS;

    APP_LOG_ATTR_T tLogAttr;
    memset(&tLogAttr, 0, sizeof(APP_LOG_ATTR_T));
    AX_S32 nLogTarget = 0;
    if (CCmdLineParser::GetInstance()->GetLogTarget(nLogTarget)) {
        tLogAttr.nTarget = nLogTarget;
    } else {
        tLogAttr.nTarget = APP_LOG_TARGET_STDOUT;
    }

    AX_S32 nLogLevel = 0;
    if (CCmdLineParser::GetInstance()->GetLogLevel(nLogLevel)) {
        tLogAttr.nLv = nLogLevel;
    } else {
        tLogAttr.nLv = APP_LOG_ERROR;
    }

    PPL_CONFIG_T tPPLConfig;
    m_pPPLConfig->GetPPLConfig(tPPLConfig);
    std::string szAppName = tPPLConfig.strAppName + "-" + tPPLConfig.strPPLName;
    sprintf(tLogAttr.szAppName, "%s", szAppName.c_str());

    nRet = AX_APP_Log_Init(&tLogAttr);
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_LOG_DeInit() {
    AX_APP_Log_DeInit();

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_VIN_Stitch_Attr_Init() {
    AX_S32 nRet = AX_SUCCESS;
    AX_VIN_STITCH_GRP_ATTR_T tVinStitchAttr{0};

    AX_U32 nSensorCount = APP_SENSOR_COUNT();
    // only one pipe for each sensor, so pipe number equal to sensor number
    tVinStitchAttr.nPipeNum = (nSensorCount >= AX_VIN_STITCH_MAX_PIPE_NUM) ? AX_VIN_STITCH_MAX_PIPE_NUM : nSensorCount;
    LOG_MM_I(PPL, "nPipeNum: %d, nSensorCount: %d", tVinStitchAttr.nPipeNum, nSensorCount);

    SENSOR_CONFIG_T tSnsCfg;
    for (AX_U32 i = 0; i < tVinStitchAttr.nPipeNum; i++) {
        if (!APP_SENSOR_CONFIG(i, tSnsCfg)) {
            LOG_M_E(PPL, "Failed to get sensor config %d", i);
            return AX_FALSE;
        }

        // only one pipe for each sensor
        tVinStitchAttr.tPipeStitch[i].nPipeId = tSnsCfg.arrPipeAttr[0].nPipeID;
        if (AX_SNS_SYNC_MASTER == tSnsCfg.nMasterSlaveSel) {
            tVinStitchAttr.tPipeStitch[i].nMasterFlag = 1;
        }

        LOG_MM_I(PPL, "[sns:%d][pipe:%d] nMasterFlag: %d",
                      i,
                      tVinStitchAttr.tPipeStitch[i].nPipeId,
                      tVinStitchAttr.tPipeStitch[i].nMasterFlag);
    }

    tVinStitchAttr.bStitch = 1;
    nRet = AX_VIN_SetStitchGrpAttr(APP_VIN_STITCH_GRP, &tVinStitchAttr);
    if (AX_SUCCESS != nRet) {
        LOG_MM_E(PPL, "AX_VIN_SetStitchGrpAttr fail, ret:0x%x", nRet);
    }

    return nRet;
}

AX_S32 CPanoBuilder::APP_VIN_Stitch_Attr_DeInit() {
    return AX_SUCCESS;
}

#ifndef SLT
AX_S32 CPanoBuilder::APP_ACAP_Init() {
    AX_S32 nRet = AX_SUCCESS;

    if (APP_AUDIO_CAP_AVAILABLE()) {
        nRet = AX_AI_Init();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }

        nRet = AX_AENC_Init();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_ACAP_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    if (APP_AUDIO_CAP_AVAILABLE()) {
        nRet = AX_AI_DeInit();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }

        nRet = AX_AENC_DeInit();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_APLAY_Init() {
    AX_S32 nRet = AX_SUCCESS;

    if (APP_AUDIO_PLAY_AVAILABLE()) {
        nRet = AX_AO_Init();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }

        nRet = AX_ADEC_Init();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }
    }

    return AX_SUCCESS;
}

AX_S32 CPanoBuilder::APP_APLAY_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    if (APP_AUDIO_PLAY_AVAILABLE()) {
        nRet = AX_AO_DeInit();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }

        nRet = AX_ADEC_DeInit();

        if (AX_SUCCESS != nRet) {
            return nRet;
        }
    }

    return AX_SUCCESS;
}
#endif  // SLT
