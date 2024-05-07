/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "OpalBuilder.h"

#include "AXTypeConverter.hpp"
#include "AlgoOptionHelper.h"
#include "AppLogApi.h"
#include "AudioOptionHelper.h"
#include "AudioWrapper.hpp"
#include "CaptureObserver.hpp"
#include "CmdLineParser.h"
#include "CollectorObserver.h"
#include "CommonUtils.hpp"
#include "DetectObserver.hpp"
#include "EncoderOptionHelper.h"
#include "GlobalDef.h"
#include "IvesObserver.hpp"
#include "IvpsObserver.h"
#include "IvpsOptionHelper.h"
#include "OSDHandler.h"
#include "OSDHelper.h"
#include "OptionHelper.h"
#include "OsdObserver.h"
#include "PrintHelper.h"
#include "SensorOptionHelper.h"
#include "WebOptionHelper.h"
#include "ax_engine_api.h"
#include "ax_venc_api.h"

#define PPL "OPAL_PPL"

AX_BOOL COPALBuilder::Init(AX_VOID) {
    return AX_TRUE;
}

AX_BOOL COPALBuilder::Deinit(AX_VOID) {
    return AX_TRUE;
}

AX_BOOL COPALBuilder::Construct(AX_VOID) {
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

    /*Step-4: Audio initialize */
    if (AX_FALSE == InitAudio()) {
        LOG_MM_E(PPL, "Initailize Audio failed.");
        return AX_FALSE;
    }

    /*Step-5: Ivps initialize */
    if (AX_FALSE == InitIvps()) {
        LOG_MM_E(PPL, "Initailize Ivps failed.");
        return AX_FALSE;
    }

    /*Step-6: venc initialize */
    if (AX_FALSE == InitVenc()) {
        LOG_MM_E(PPL, "Initailize Venc failed.");
        return AX_FALSE;
    }

    /*Step-7: capture initialize */
    if (AX_FALSE == InitCapture()) {
        LOG_MM_E(PPL, "Initailize capture failed.");
        return AX_FALSE;
    }

    /*Step-8: collector initialize */
    if (AX_FALSE == InitCollector()) {
        LOG_MM_E(PPL, "Initailize Ivps failed.");
        return AX_FALSE;
    }

    /*Step-9: jenc initialize */
    if (AX_FALSE == InitJenc()) {
        LOG_MM_E(PPL, "Initailize Jenc failed.");
        return AX_FALSE;
    }

    /*Step-10: detector initialize */
    if (AX_FALSE == InitDetector()) {
        LOG_MM_E(PPL, "Initailize detector failed.");
        return AX_FALSE;
    }

    /*Step-11: ives initialize */
    if (AX_FALSE == InitIves()) {
        LOG_MM_E(PPL, "Initailize ives failed.");
        return AX_FALSE;
    }

    /*Step-12: PPL pool initialize */
    if (AX_FALSE == InitPoolConfig()) {
        LOG_MM_E(PPL, "Initailize Pool failed.");
        return AX_FALSE;
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitAudio() {
    LOG_MM(PPL, "+++");
    // audio
    AX_APP_AUDIO_ATTR_T stAudioAttr = APP_AUDIO_ATTR();
    AX_APP_Audio_Init(&stAudioAttr);

    LOG_MM(PPL, "---");

    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitSensor() {
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
        tCamera.nRotation = 0;
        tCamera.fFramerate = tSnsConfig.fFrameRate;
        tCamera.nDayNightMode = 0; // 0: day, 1: night; 2: auto
        tCamera.nNrMode = 1;
        tCamera.bCapture = AX_TRUE;
        tCamera.bCaptureEnable = AX_TRUE;
        tCamera.bSnsModeEnable = AX_TRUE;
        tCamera.bPNModeEnable = AX_TRUE;
        tCamera.bMirrorFlipEnable = AX_TRUE;
        tCamera.bRotationEnable = AX_FALSE;
        tCamera.bLdcEnable = AX_TRUE;
        tCamera.bDisSupport = AX_FALSE;
        tCamera.bEZoomEnable = AX_TRUE;
        CWebOptionHelper::GetInstance()->InitCameraAttr(nSnsID, tSnsConfig.eSensorType, tCamera);
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitIvps() {
    LOG_MM(PPL, "+++");
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

        {
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
                LOG_MM_N(PPL, "Can not link AVS to IVPS, please check ppl.json.");
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
                CIVPSGrpStage* pSrcInstance = m_vecIvpsInstance[tRelation.tSrcModChn.nGroup];
                IVPS_GROUP_CFG_T* pSrcConfig = pSrcInstance->GetGrpCfg();
                AX_U32 nWidth = pSrcConfig->arrChnResolution[tRelation.tSrcModChn.nChannel][0];
                AX_U32 nHeight = pSrcConfig->arrChnResolution[tRelation.tSrcModChn.nChannel][1];
                AX_U8 nOutChannels = tIvpsGrpCfg.nGrpChnNum;
                for (AX_U8 j = 0; j < nOutChannels; j++) {
                    if (-1 == pConfig->arrGrpResolution[0]) {
                        pConfig->arrGrpResolution[0] = nWidth;
                    }

                    if (-1 == pConfig->arrGrpResolution[1]) {
                        pConfig->arrGrpResolution[1] = nHeight;
                    }

                    if (-1 == pConfig->arrChnResolution[j][0]) {
                        pConfig->arrChnResolution[j][0] = nWidth;
                    }

                    if (-1 == pConfig->arrChnResolution[j][1]) {
                        pConfig->arrChnResolution[j][1] = nHeight;
                    }

                    if (-1 == pConfig->arrGrpFramerate[0]) {
                        pConfig->arrGrpFramerate[0] = pSrcConfig->arrGrpFramerate[0];
                    }

                    if (-1 == pConfig->arrGrpFramerate[1]) {
                        pConfig->arrGrpFramerate[1] = pConfig->arrGrpFramerate[0];
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

    for (auto pInstance : m_vecIvpsInstance) {
        IVPS_GROUP_CFG_T* pCfg = pInstance->GetGrpCfg();
        if (pCfg) {
            WEB_CAMERA_ATTR_T tCamera = CWebOptionHelper::GetInstance()->GetCamera(pCfg->nSnsSrc);
            /* update web ldcAttr value */
            tCamera.tLdcAttr.bLdcEnable = pCfg->nLdcEnable ? AX_TRUE : AX_FALSE;
            tCamera.tLdcAttr.bLdcAspect = pCfg->bLdcAspect;
            tCamera.tLdcAttr.nXRatio = pCfg->nLdcXRatio;
            tCamera.tLdcAttr.nYRatio = pCfg->nLdcYRatio;
            tCamera.tLdcAttr.nXYRatio = pCfg->nLdcXYRatio;
            tCamera.tLdcAttr.nDistorRatio = pCfg->nLdcDistortionRatio;
            CWebOptionHelper::GetInstance()->SetCamera(pCfg->nSnsSrc, tCamera);
        }
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitVenc() {
    LOG_MM(PPL, "+++");

    AX_APP_AUDIO_ATTR_T stAudioAttr = APP_AUDIO_ATTR();

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

                if (pConfig->nMaxWidth == -1
                    || pConfig->nMaxHeight == -1) {
                    pConfig->nMaxWidth = pConfig->nWidth;
                    pConfig->nMaxHeight = pConfig->nHeight;
                }

                if (!pVencInstance->InitParams()) {
                    LOG_MM_E(PPL, "Init venc %d failed.", tConfig.nChannel);
                    return AX_FALSE;
                }

                /* initialize web's video setting */
                WEB_VIDEO_ATTR_T tVideoAttr;
                AX_U8 nEncoderType = CAXTypeConverter::EncoderType2Int(tConfig.ePayloadType);
                // AX620E TODO:
                AX_U8 nPrevChn = tConfig.nChannel;
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

                m_vecVencInstance.emplace_back(pVencInstance);
            }
        } while (0);
    }

    {
        WEB_AUDIO_ATTR_T tAudioAttr;
        tAudioAttr.fCapture_volume = (AX_F32)stAudioAttr.stCapAttr.stDevAttr.fVolume;
        tAudioAttr.fPlay_volume = (AX_F32)stAudioAttr.stPlayAttr.stDevAttr.fVolume;

        CWebOptionHelper::GetInstance()->SetAudio(tAudioAttr);
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitJenc() {
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

                /* Step-8-5: Save instance */
                m_vecJencInstance.emplace_back(pJencInstance);

                LOG_M_I(PPL, "Init jenc channel %d successfully.", i);
            }
        } while (0);
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitDetector() {
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
    }

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL COPALBuilder::ConstructIves() {
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

AX_BOOL COPALBuilder::InitIves() {
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
                } else if (E_PPL_MOD_TYPE_COLLECT == relation.tSrcModChn.eModType) {
                    CIVESStage* pIves = m_vecIvesInstance[i];

                    CWebOptionHelper::GetInstance()->InitIvesAttr(tDstMod.nGroup, pIves);

                    pIves->Init(tDstMod.nGroup);
                }
            }
        }
    }
    LOG_MM(PPL, "---");

    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitCapture() {
    // capture on every ivps channel.
    for (auto pInstance : m_vecIvpsInstance) {
        IVPS_GROUP_CFG_T* pSrcConfig = pInstance->GetGrpCfg();
        for (AX_U8 nChn = 0; nChn < pSrcConfig->nGrpChnNum; ++nChn) {
            m_vecCaptureObs.emplace_back(CObserverMaker::CreateObserver<CCaptureObserver>(&m_capture));
            pInstance->RegObserver(nChn, m_vecCaptureObs[m_vecCaptureObs.size() - 1].get());
        }
    }
    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitCollector() {
    LOG_MM(PPL, "+++");

    ConstructIves();

    for (AX_U8 i = 0; i < MAX_COLLECT_GROUP_NUM; i++) {
        IPC_MOD_INFO_T tDstMod = {E_PPL_MOD_TYPE_COLLECT, i, 0};
        vector<PPL_MOD_RELATIONSHIP_T> vecRelations;
        if (!GetRelationsByDstMod(tDstMod, vecRelations, AX_TRUE)) {
            LOG_MM_W(PPL, "Can not find relation for dest module: (Module:%s, Grp:%d, Chn:%d)",
                     CAXTypeConverter::ModType2String(tDstMod.eModType).c_str(), tDstMod.nGroup, tDstMod.nChannel);
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
            LOG_MM_W(PPL, "Can not find relation for dest module: (Module:%s, Grp:%d, Chn:%d)",
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
            LOG_MM_W(PPL, "Can not find relation for dest module: (Module:%s, Grp:%d, Chn:%d)",
                     CAXTypeConverter::ModType2String(tSrcMod.eModType).c_str(), tSrcMod.nGroup, tSrcMod.nChannel);
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

AX_BOOL COPALBuilder::InitPoolConfig() {
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

AX_BOOL COPALBuilder::Start(AX_VOID) {
    LOG_MM(PPL, "+++");

    if (!m_pPoolConfig->Start()) {
        LOG_M(PPL, "pool start failed.");
        return AX_FALSE;
    }

    if (!m_detector.Start()) {
        return AX_FALSE;
    }

    for (auto& pInstance : m_vecIvesInstance) {
        if (!pInstance->Start()) {
            return AX_FALSE;
        }
    }

    for (auto& pInstance : m_vecVencInstance) {
        STAGE_START_PARAM_T tStartParam;
        tStartParam.bStartProcessingThread = AX_FALSE;
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

    if (AX_FALSE == m_mgrSensor.Start()) {
        LOG_MM_E(PPL, "Start sensor failed.");

        return AX_FALSE;
    }

    AX_APP_Audio_Start();

    CPrintHelper::GetInstance()->Start();

    PostStartProcess();

    // refresh osd
    for (auto pInstance : m_vecIvpsInstance) {
        if (pInstance->GetOsdHelper()) {
            pInstance->GetOsdHelper()->Refresh();
        }
    }

    LOG_MM(PPL, "---");

    return AX_TRUE;
}

AX_BOOL COPALBuilder::Stop(AX_VOID) {
    LOG_MM(PPL, "+++");

    CPrintHelper::GetInstance()->Stop();

    AX_APP_Audio_Stop();

    for (auto& pInstance : m_vecIvesInstance) {
        if (!pInstance->Stop()) {
            return AX_FALSE;
        }
    }

    if (!m_mgrSensor.Stop()) {
        return AX_FALSE;
    }

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

    if (!m_pPoolConfig->Stop()) {
        return AX_FALSE;
    }

    LOG_MM(PPL, "---");

    return AX_TRUE;
}

AX_BOOL COPALBuilder::Destroy(AX_VOID) {
    LOG_MM(PPL, "+++");

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

    if (!m_mgrSensor.DeInit()) {
        return AX_FALSE;
    }

    AX_APP_Audio_Deinit();

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
        pInstance->DetachOsdHelper();

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

    LOG_MM(PPL, "---");
    return AX_TRUE;
}

AX_BOOL COPALBuilder::UpdateRotation(AX_U8 nSnsID, AX_U8 nRotation) {
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

AX_VOID COPALBuilder::PostStartProcess(AX_VOID) {
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

        SENSOR_CONFIG_T tSensorCfg;
        APP_SENSOR_CONFIG(i, tSensorCfg);

        // manual
        if (tSensorCfg.tColorAttr.bColorManual) {
            APP_ISP_IMAGE_ATTR_T tImgAttr;
            tImgAttr.nSharpness = (AX_U8)tSensorCfg.tColorAttr.fSharpness;
            tImgAttr.nBrightness = (AX_U8)tSensorCfg.tColorAttr.fBrightness;
            tImgAttr.nContrast = (AX_U8)tSensorCfg.tColorAttr.fContrast;
            tImgAttr.nSaturation = (AX_U8)tSensorCfg.tColorAttr.fSaturation;

            pSensor->SetIspImageAttr(tImgAttr);
        } else {
            tSensorCfg.tColorAttr.fBrightness = tImgAttr.nBrightness;
            tSensorCfg.tColorAttr.fSharpness = tImgAttr.nSharpness;
            tSensorCfg.tColorAttr.fContrast = tImgAttr.nContrast;
            tSensorCfg.tColorAttr.fSaturation = tImgAttr.nSaturation;

            SET_APP_SENSOR_CONFIG(i, tSensorCfg);
        }

        // day night
        if (tSensorCfg.eDayNight == AX_DAYNIGHT_MODE_NIGHT) {
            m_mgrSensor.ChangeDaynightMode(i, tSensorCfg.eDayNight);
        }
    }
}

AX_BOOL COPALBuilder::ProcessWebOprs(WEB_REQUEST_TYPE_E eReqType, const AX_VOID* pJsonReq, AX_VOID** pResult /*= nullptr*/) {
    return AX_TRUE;
}

AX_BOOL COPALBuilder::ProcessTestSuiteOpers(WEB_REQ_OPERATION_T& tOperation) {
    return AX_TRUE;
}

AX_BOOL COPALBuilder::InitSysMods(AX_VOID) {
    LOG_MM(PPL, "+++");

    m_arrMods.clear();
    m_arrMods.push_back({AX_FALSE, "LOG", bind(&COPALBuilder::APP_LOG_Init, this), bind(&COPALBuilder::APP_LOG_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "SYS", bind(&COPALBuilder::APP_SYS_Init, this), bind(&COPALBuilder::APP_SYS_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "NPU", bind(&COPALBuilder::APP_NPU_Init, this), bind(&COPALBuilder::APP_NPU_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "VIN", AX_VIN_Init, AX_VIN_Deinit});
    m_arrMods.push_back({AX_FALSE, "MIPI_RX", AX_MIPI_RX_Init, AX_MIPI_RX_DeInit});
    m_arrMods.push_back({AX_FALSE, "IVPS", AX_IVPS_Init, AX_IVPS_Deinit});
    m_arrMods.push_back({AX_FALSE, "VENC", bind(&COPALBuilder::APP_VENC_Init, this), bind(&COPALBuilder::APP_VENC_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "ACAP", bind(&COPALBuilder::APP_ACAP_Init, this), bind(&COPALBuilder::APP_ACAP_DeInit, this)});
    m_arrMods.push_back({AX_FALSE, "APLAY", bind(&COPALBuilder::APP_APLAY_Init, this), bind(&COPALBuilder::APP_APLAY_DeInit, this)});

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

AX_BOOL COPALBuilder::GetRelationsBySrcMod(IPC_MOD_INFO_T& tSrcMod, vector<PPL_MOD_RELATIONSHIP_T>& vecOutRelations,
                                           AX_BOOL bIgnoreChn /*= AX_FALSE*/) const {
    return m_linkage.GetRelationsBySrcMod(tSrcMod, vecOutRelations, bIgnoreChn);
}

AX_BOOL COPALBuilder::GetRelationsByDstMod(IPC_MOD_INFO_T& tDstMod, vector<PPL_MOD_RELATIONSHIP_T>& vecOutRelations,
                                           AX_BOOL bIgnoreChn /*= AX_FALSE*/) const {
    return m_linkage.GetRelationsByDstMod(tDstMod, vecOutRelations, bIgnoreChn);
}

AX_BOOL COPALBuilder::GetPrecedingMod(const IPC_MOD_INFO_T& tDstMod, IPC_MOD_INFO_T& tPrecedingMod) {
    return m_linkage.GetPrecedingMod(tDstMod, tPrecedingMod);
}

AX_BOOL COPALBuilder::DeInitSysMods(AX_VOID) {
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
    return AX_TRUE;
}

AX_S32 COPALBuilder::APP_SYS_Init() {
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

AX_S32 COPALBuilder::APP_SYS_DeInit() {
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

AX_S32 COPALBuilder::APP_VENC_Init() {
    AX_S32 nRet = AX_SUCCESS;

    if (IS_APP_ENCODER_ENABLE()) {
        AX_VENC_MOD_ATTR_T tModAttr;
        memset(&tModAttr, 0, sizeof(AX_VENC_MOD_ATTR_T));
        tModAttr.enVencType = AX_VENC_MULTI_ENCODER;
        tModAttr.stModThdAttr.bExplicitSched = AX_FALSE;
        tModAttr.stModThdAttr.u32TotalThreadNum = COptionHelper::GetInstance()->GetVencThreadNum();

        nRet = AX_VENC_Init(&tModAttr);
        if (AX_SUCCESS != nRet) {
            return nRet;
        }
    }

    return AX_SUCCESS;
}

AX_S32 COPALBuilder::APP_VENC_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    if (IS_APP_ENCODER_ENABLE()) {
        nRet = AX_VENC_Deinit();
        if (AX_SUCCESS != nRet) {
            return nRet;
        }
    }

    return AX_SUCCESS;
}

AX_S32 COPALBuilder::APP_NPU_Init() {
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

AX_S32 COPALBuilder::APP_NPU_DeInit() {
    AX_S32 nRet = AX_SUCCESS;

    nRet = AX_ENGINE_Deinit();
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 COPALBuilder::APP_LOG_Init(AX_VOID) {
    AX_S32 nRet = AX_SUCCESS;

    APP_LOG_ATTR_T tLogAttr;
    AX_CHAR* pEnv = NULL;
    memset(&tLogAttr, 0, sizeof(APP_LOG_ATTR_T));

    pEnv = getenv("OPAL_LOG_target");
    if (pEnv) {
        tLogAttr.nTarget = atoi(pEnv);
    } else {
        tLogAttr.nTarget = APP_LOG_TARGET_STDOUT;
    }

    pEnv = getenv("OPAL_LOG_level");
    if (pEnv) {
        tLogAttr.nLv = atoi(pEnv);
    } else {
        tLogAttr.nLv = APP_LOG_ERROR;
    }

    sprintf(tLogAttr.szAppName, "%s", "OPAL");

    nRet = AX_APP_Log_Init(&tLogAttr);
    if (AX_SUCCESS != nRet) {
        return nRet;
    }

    return AX_SUCCESS;
}

AX_S32 COPALBuilder::APP_LOG_DeInit() {
    AX_APP_Log_DeInit();

    return AX_SUCCESS;
}

AX_S32 COPALBuilder::APP_ACAP_Init() {
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

AX_S32 COPALBuilder::APP_ACAP_DeInit() {
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

AX_S32 COPALBuilder::APP_APLAY_Init() {
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

AX_S32 COPALBuilder::APP_APLAY_DeInit() {
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
