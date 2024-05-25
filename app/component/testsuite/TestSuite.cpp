/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "TestSuite.h"
#include <algorithm>
#include "AXTypeConverter.hpp"
#include "AlgoOptionHelper.h"
#include "AppLog.hpp"
#include "CmdLineParser.h"
#include "ElapsedTimer.hpp"
#include "OptionHelper.h"
#include "WebOptionHelper.h"

#define INTERVAL_MS_MIN 1000
#define TESTSUITE "TestSuite"

AX_VOID CTestSuite::RunTest(AX_VOID* pArg) {
    LOG_MM_C(TESTSUITE, "+++");
    AX_S64 const nLoop = m_tTestCfg.nLoopNum;
    m_nDefInterVal = m_tTestCfg.nDefIntervalMs < INTERVAL_MS_MIN ? INTERVAL_MS_MIN : m_tTestCfg.nDefIntervalMs;
    AX_S64 cnt = 0;
    AX_ULONG nIndex;
    AX_U32 vecSize = m_vecTestCase.size();
    while (m_UtThread.IsRunning()) {
        std::vector<TESTSUITE_OPERATION_T> vecReq = m_vecTestCase;
        TESTSUITE_OPERATION_T reqOps;
        if (!m_tTestCfg.bRandomEnable) {
            for (nIndex = 0; nIndex < vecSize; nIndex++) {
                reqOps = vecReq[nIndex];
                if (!Process(reqOps)) {
                    break;
                }
            }
        } else {
            srand(unsigned(time(0)));
            random_shuffle(vecReq.begin(), vecReq.end());
            for (nIndex = 0; nIndex < vecSize; nIndex++) {
                reqOps = vecReq.back();
                if (!Process(reqOps)) {
                    break;
                }
                vecReq.pop_back();
            }
        }
        cnt++;
        LOG_MM_C(TESTSUITE, "Executed %d times.", cnt);
        if (nLoop >= 0 && cnt >= nLoop) {
            break;
        }
    }

    LOG_MM_C(TESTSUITE, "---");
}

AX_BOOL CTestSuite::Process(TESTSUITE_OPERATION_T& ops) {
    if (!SkipOpera(ops)) {
        PrintCaseParam(ops);
        if (m_pPPLBuilder->ProcessTestSuiteOpers(ops)) {
            if (E_REQ_TYPE_VIDEO == ops.eReqType || E_REQ_TYPE_CAMERA == ops.eReqType) {
                WEB_EVENTS_DATA_T event;
                event.eType = E_WEB_EVENTS_TYPE_ReStartPreview;
                event.nReserved = ops.nSnsID;
                CWebServer::GetInstance()->SendEventsData(&event);
                CWebServer::GetInstance()->SendEventsData(&event);
            }
            SaveOpera(ops);
        } else {
            LOG_MM_E(TESTSUITE, "m_pPPLBuilder->ProcessTestSuiteOpers Failed.");
        }
        if (ops.nIntervalMs > 0) {
            CElapsedTimer::mSleep(ops.nIntervalMs);
        } else {
            CElapsedTimer::mSleep(m_nDefInterVal);
        }
        if (!m_UtThread.IsRunning()) {
            return AX_FALSE;
        }
    }
    return AX_TRUE;
}

AX_VOID CTestSuite::SaveOpera(TESTSUITE_OPERATION_T ops) {
    LOG_MM_I(TESTSUITE, "+++");
    UpdateWebAttr(ops);
    switch (ops.eReqType) {
        case E_REQ_TYPE_VIDEO:
            if (E_WEB_OPERATION_TYPE_CHANNEL_SWITCH == ops.GetOperationType()) {
                m_pCurVideoAttr->bEnable = ops.tChnSwitch.bOn;
                m_pCurVideoAttr->nEncoderType = ops.tChnSwitch.nEncoderType;
            } else if (E_WEB_OPERATION_TYPE_RESOLUTION == ops.GetOperationType()) {
                m_pCurVideoAttr->nWidth = ops.tResolution.nWidth;
                m_pCurVideoAttr->nHeight = ops.tResolution.nHeight;
                m_pCurVideoAttr->nEncoderType = ops.tResolution.nEncoderType;
            } else if (E_WEB_OPERATION_TYPE_RC_INFO == ops.GetOperationType()) {
                m_pCurVideoAttr->nRcType = CAXTypeConverter::RcMode2Int(ops.tRcInfo.eRcType);
                m_pCurVideoAttr->nEncoderType = ops.tRcInfo.nEncoderType;
            } else if (E_WEB_OPERATION_TYPE_VENC_LINK_ENABLE == ops.GetOperationType()) {
                m_pCurVideoAttr->bLink = ops.tVencLinkEnable.bLinkEnable;
            } else if (E_WEB_OPERATION_TYPE_ENC_TYPE == ops.GetOperationType()) {
                m_pCurVideoAttr->nEncoderType = ops.tEncType.nEncoderType;
            }
            break;
        case E_REQ_TYPE_CAMERA:
            if (E_WEB_OPERATION_TYPE_CAPTURE_ENABLE == ops.GetOperationType()) {
                m_pCurCameraAttr->bCaptureEnable = ops.tCapEnable.bOn;
            } else if (E_WEB_OPERATION_TYPE_DAYNIGHT == ops.GetOperationType()) {
                m_pCurCameraAttr->nDayNightMode = ops.tDaynight.nDayNightMode;
            } else if (E_WEB_OPERATION_TYPE_CAMERA_FPS == ops.GetOperationType()) {
                m_pCurCameraAttr->fFramerate = ops.tSnsFpsAttr.fSnsFrameRate;
            } else if (E_WEB_OPERATION_TYPE_ROTATION == ops.GetOperationType()) {
                m_pCurCameraAttr->nRotation = ops.tRotation.nRotation;
            } else if (E_WEB_OPERATION_TYPE_SNS_MIRROR_FLIP == ops.GetOperationType()) {
                m_pCurCameraAttr->bMirror = ops.tSnsMirrorFlip.bMirror;
                m_pCurCameraAttr->bFlip = ops.tSnsMirrorFlip.bFlip;
            } else if (E_WEB_OPERATION_TYPE_EZOOM == ops.GetOperationType()) {
                m_pCurCameraAttr->tEZoomAttr.nEZoomRatio = ops.tEZoom.nEZoomRatio;
            } else if (E_WEB_OPERATION_TYPE_IMAGE_ATTR == ops.GetOperationType()) {
                m_pCurCameraAttr->tImageAttr.nAutoMode = ops.tImageAttr.nAutoMode;
            } else if (E_WEB_OPERATION_TYPE_LDC_ATTR == ops.GetOperationType()) {
                m_pCurCameraAttr->tLdcAttr.bLdcEnable = ops.tLdcAttr.bLdcEnable;
            } else if (E_WEB_OPERATION_TYPE_SNS_MODE == ops.GetOperationType()) {
                m_pCurCameraAttr->nSnsMode = ops.tSnsMode.nSnsMode;
            }
            break;
        case E_REQ_TYPE_AI:
            if (E_WEB_OPERATION_TYPE_AI_ENABLE == ops.GetOperationType()) {
                m_pCurAiAttr->bEnable = ops.tAiEnable.bOn;
            } else if (E_WEB_OPERATION_TYPE_AI_PUSH_MODE == ops.GetOperationType()) {
                m_pCurAiAttr->tPushStategy = ops.tAiPushStategy;
            } else if (E_WEB_OPERATION_TYPE_AI_EVENT == ops.GetOperationType()) {
                m_pCurAiAttr->tEvents = ops.tEvent;
            } else if (E_WEB_OPERATION_TYPE_AI_AE_ROI == ops.GetOperationType()) {
                m_pCurAiAttr->tAeRoiBody.bEnable = ops.tAiAeRoi.bEnable;
            }
            break;
        case E_REQ_TYPE_OSD:
            if (E_WEB_OPERATION_TYPE_OSD_ATTR == ops.GetOperationType()) {
                // CWebOptionHelper::GetInstance()->GetOsdConfig();
                // m_pCurOsdAttr->bEnable = ops.tOsdEnable.bOn;
            }
            break;
        case E_REQ_TYPE_AUDIO:
            if (E_WEB_OPERATION_TYPE_AUDIO_ATTR == ops.GetOperationType()) {
                m_AudioAttr.bAedEnable = (AX_BOOL)ops.tAudioAttr.nAedEnable;
            }
            break;
        default:
            break;
    }
    LOG_MM_I(TESTSUITE, "---");
}

/**
 * Skip operation when the following occurs
 * 1. The value of operation is equal to the current value
 * 2. when eReqType is E_REQ_TYPE_VIDEO, the value of opeation's encode type unequal current encode type.
 *    And the channel for opeation is closed
 */
AX_BOOL CTestSuite::SkipOpera(TESTSUITE_OPERATION_T ops) {
    LOG_MM_I(TESTSUITE, "+++");

    AX_BOOL ret = AX_FALSE;
    AX_U32 nSnsID = ops.nSnsID;
    AX_U32 nChn;
    switch (ops.eReqType) {
        case E_REQ_TYPE_VIDEO:
            nChn = ops.nChannel;
            m_pCurVideoAttr = &m_mapSns2VideoAttr[nSnsID][nChn];
            if (E_WEB_OPERATION_TYPE_CHANNEL_SWITCH == ops.GetOperationType()) {
                if (m_pCurVideoAttr->nEncoderType != ops.tChnSwitch.nEncoderType || m_pCurVideoAttr->bEnable == ops.tChnSwitch.bOn) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_RESOLUTION == ops.GetOperationType()) {
                if (AX_FALSE == m_pCurVideoAttr->bEnable || m_pCurVideoAttr->nEncoderType != ops.tResolution.nEncoderType ||
                    (m_pCurVideoAttr->nWidth == ops.tResolution.nWidth && m_pCurVideoAttr->nHeight == ops.tResolution.nHeight)) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_RC_INFO == ops.GetOperationType()) {
                RC_INFO_T tRcInfo;
                m_pCurVideoAttr->GetEncRcCfg(tRcInfo);
                if (AX_FALSE == m_pCurVideoAttr->bEnable || m_pCurVideoAttr->nEncoderType != ops.tRcInfo.nEncoderType ||
                    (m_pCurVideoAttr->nRcType == CAXTypeConverter::RcMode2Int(ops.tRcInfo.eRcType) &&
                     tRcInfo.nMaxIProp == ops.tRcInfo.nMaxIProp && tRcInfo.nMinIProp == ops.tRcInfo.nMinIProp)) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_VENC_LINK_ENABLE == ops.GetOperationType()) {
                if (m_pCurVideoAttr->bLink == ops.tVencLinkEnable.bLinkEnable) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_ENC_TYPE == ops.GetOperationType()) {
                if (AX_FALSE == m_pCurVideoAttr->bEnable || m_pCurVideoAttr->nEncoderType == ops.tEncType.nEncoderType) {
                    ret = AX_TRUE;
                }
            }

            break;
        case E_REQ_TYPE_CAMERA:
            m_pCurCameraAttr = &m_mapSns2CameraSetting[nSnsID];
            if (E_WEB_OPERATION_TYPE_CAPTURE_ENABLE == ops.GetOperationType()) {
                if (m_pCurCameraAttr->bCaptureEnable == ops.tCapEnable.bOn) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_DAYNIGHT == ops.GetOperationType()) {
                if (m_pCurCameraAttr->nDayNightMode == ops.tDaynight.nDayNightMode) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_CAMERA_FPS == ops.GetOperationType()) {
                if (m_pCurCameraAttr->fFramerate == ops.tSnsFpsAttr.fSnsFrameRate) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_ROTATION == ops.GetOperationType()) {
                if (m_pCurCameraAttr->nRotation == ops.tRotation.nRotation) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_SNS_MIRROR_FLIP == ops.GetOperationType()) {
                if (m_pCurCameraAttr->bMirror == ops.tSnsMirrorFlip.bMirror && m_pCurCameraAttr->bFlip == ops.tSnsMirrorFlip.bFlip) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_EZOOM == ops.GetOperationType()) {
                if (m_pCurCameraAttr->tEZoomAttr.nEZoomRatio == ops.tEZoom.nEZoomRatio) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_IMAGE_ATTR == ops.GetOperationType()) {
                if (m_pCurCameraAttr->tImageAttr.nAutoMode == ops.tImageAttr.nAutoMode) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_LDC_ATTR == ops.GetOperationType()) {
                if (m_pCurCameraAttr->tLdcAttr.bLdcEnable == ops.tLdcAttr.bLdcEnable) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_SNS_MODE == ops.GetOperationType()) {
                if (m_pCurCameraAttr->nSnsMode == ops.tSnsMode.nSnsMode) {
                    ret = AX_TRUE;
                }
            }
            break;
        case E_REQ_TYPE_AI:
            m_pCurAiAttr = &m_mapSns2AiAttr[nSnsID];
            if (E_WEB_OPERATION_TYPE_AI_ENABLE == ops.GetOperationType()) {
                if (m_pCurAiAttr->bEnable == ops.tAiEnable.bOn) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_AI_PUSH_MODE == ops.GetOperationType()) {
                if (m_pCurAiAttr->tPushStategy.ePushMode == ops.tAiPushStategy.ePushMode &&
                    m_pCurAiAttr->tPushStategy.nPushCounts == ops.tAiPushStategy.nPushCounts &&
                    m_pCurAiAttr->tPushStategy.nPushIntervalMs == ops.tAiPushStategy.nPushIntervalMs) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_AI_EVENT == ops.GetOperationType()) {
                if (m_pCurAiAttr->tEvents.tMD.bEnable == ops.tEvent.tMD.bEnable &&
                    m_pCurAiAttr->tEvents.tOD.bEnable == ops.tEvent.tOD.bEnable &&
                    m_pCurAiAttr->tEvents.tSCD.bEnable == ops.tEvent.tSCD.bEnable) {
                    ret = AX_TRUE;
                }
            } else if (E_WEB_OPERATION_TYPE_AI_AE_ROI == ops.GetOperationType()) {
                if (m_pCurAiAttr->tAeRoiBody.bEnable == ops.tAiAeRoi.bEnable) {
                    ret = AX_TRUE;
                }
            }
            break;
        case E_REQ_TYPE_OSD:
            // m_pCurOsdAttr = &m_mapSns2OsdConfig[nSnsID];
            // if (E_WEB_OPERATION_TYPE_OSD_ATTR == ops.GetOperationType()) {
            //     if (m_pCurOsdAttr->bEnable == ops.tOsdEnable.bOn) {
            //         ret = AX_TRUE;
            //     }
            // }
            break;
        case E_REQ_TYPE_AUDIO:
            if (E_WEB_OPERATION_TYPE_AUDIO_ATTR == ops.GetOperationType()) {
                if (m_AudioAttr.bAedEnable == (AX_BOOL)ops.tAudioAttr.nAedEnable) {
                    ret = AX_TRUE;
                }
            }
        default:
            break;
    }
    return ret;
}

AX_VOID CTestSuite::SortCases(std::vector<TESTSUITE_OPERATION_T>& vecWebRequests) {
    std::sort(vecWebRequests.begin(), vecWebRequests.end(),
              [](TESTSUITE_OPERATION_T t1, TESTSUITE_OPERATION_T t2) { return t1.nPriority > t2.nPriority; });
}

AX_VOID CTestSuite::UpdateWebAttr(TESTSUITE_OPERATION_T& ops) {
    if (E_WEB_OPERATION_TYPE_RESOLUTION == ops.GetOperationType()) {
        WEB_VIDEO_ATTR_T attr;
        attr.nWidth = ops.tResolution.nWidth;
        attr.nHeight = ops.tResolution.nHeight;
        attr.nUniChn = ops.nChannel;
        LOG_MM_I(TESTSUITE, "nSnsID:%d, nUniChn:%d, nWidth:%d, nHeight:%d", ops.nSnsID, ops.nChannel, attr.nWidth, attr.nHeight);
        CWebOptionHelper::GetInstance()->SetVideoByUniChn(ops.nSnsID, attr);
    } else if (E_WEB_OPERATION_TYPE_AI_EVENT == ops.GetOperationType()) {
        if (-1 == ops.nSnsID) {
            CWebOptionHelper::GetInstance()->SetAiEvent(0, ops.tEvent);
            CWebOptionHelper::GetInstance()->SetAiEvent(1, ops.tEvent);
        } else {
            CWebOptionHelper::GetInstance()->SetAiEvent(ops.nSnsID, ops.tEvent);
        }
    }
}

AX_VOID CTestSuite::PrintCaseParam(TESTSUITE_OPERATION_T& ops) {
    LOG_MM_I(TESTSUITE, "+++");
    LOG_MM_I(TESTSUITE, "operaType:%d", ops.GetOperationType());
    RC_INFO_T tRcInfo;
    if (E_REQ_TYPE_VIDEO == ops.eReqType) {
        if (nullptr != m_pCurVideoAttr) {
            m_pCurVideoAttr->GetEncRcCfg(tRcInfo);
        } else {
            LOG_MM_E(TESTSUITE, "m_pCurVideoAttr is nullptr.");
            return;
        }
    }

    switch (ops.GetOperationType()) {
        case E_WEB_OPERATION_TYPE_ROTATION:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, rotation: (%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID, m_pCurCameraAttr->nRotation,
                     ops.tRotation.nRotation);
            break;
        case E_WEB_OPERATION_TYPE_SNS_MODE:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, sensor mode: (%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID, m_pCurCameraAttr->nSnsMode,
                     ops.tSnsMode.nSnsMode);
            break;
        case E_WEB_OPERATION_TYPE_RESOLUTION:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, nChn:%d, encoderType:%d, resolution (%d*%d ---> %d*%d)]", ops.strDesc.c_str(), ops.nSnsID,
                     ops.nChannel, ops.tResolution.nEncoderType, m_pCurVideoAttr->nWidth, m_pCurVideoAttr->nHeight, ops.tResolution.nWidth,
                     ops.tResolution.nHeight);
            break;
        case E_WEB_OPERATION_TYPE_ENC_TYPE:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, nChn:%d, encoderType:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID, ops.nChannel,
                     m_pCurVideoAttr->nEncoderType, ops.tResolution.nEncoderType);
            break;
        case E_WEB_OPERATION_TYPE_RC_INFO:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, nChn:%d, encoderType:%d, rcType(%d ---> %d)min_iprop/max_ipror(%d/%d ---> %d/%d)]",
                     ops.strDesc.c_str(), ops.nSnsID, ops.nChannel, ops.tRcInfo.nEncoderType, m_pCurVideoAttr->nRcType,
                     CAXTypeConverter::RcMode2Int(ops.tRcInfo.eRcType), tRcInfo.nMinIProp, tRcInfo.nMaxIProp, ops.tRcInfo.nMinIProp,
                     ops.tRcInfo.nMaxIProp);
            break;
        case E_WEB_OPERATION_TYPE_DAYNIGHT:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, dayNightMode:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurCameraAttr->nDayNightMode, ops.tDaynight.nDayNightMode);
            break;
        case E_WEB_OPERATION_TYPE_NR_MODE:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, nrMode:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID, m_pCurCameraAttr->nNrMode,
                     ops.tNR.nNRMode);
            break;
        case E_WEB_OPERATION_TYPE_CAPTURE_ENABLE:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, capture_enable:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurCameraAttr->bCaptureEnable, ops.tCapEnable.bOn);
            break;
        case E_WEB_OPERATION_TYPE_AI_ENABLE:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, ai_enable:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID, m_pCurAiAttr->bEnable,
                     ops.tAiEnable.bOn);
            break;
        case E_WEB_OPERATION_TYPE_AI_PUSH_MODE:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, ai_push_mode,ai_push_count, ai_push_intervalMs (%d/%d/%d ---> %d/%d/%d)]",
                     ops.strDesc.c_str(), ops.nSnsID, m_pCurAiAttr->tPushStategy.ePushMode, m_pCurAiAttr->tPushStategy.nPushCounts,
                     m_pCurAiAttr->tPushStategy.nPushIntervalMs, ops.tAiPushStategy.ePushMode, ops.tAiPushStategy.nPushCounts,
                     ops.tAiPushStategy.nPushIntervalMs);
            break;
        case E_WEB_OPERATION_TYPE_AI_AE_ROI:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, ai_aeRoi_enable:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurAiAttr->tAeRoiBody.bEnable, ops.tAiAeRoi.bEnable);
            break;
        case E_WEB_OPERATION_TYPE_AI_EVENT:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, ives enable (%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurAiAttr->tEvents.tSCD.bEnable, ops.tEvent.tSCD.bEnable);
            break;
        case E_WEB_OPERATION_TYPE_OSD_ATTR:
            UpdateOsd(ops);
            break;
        case E_WEB_OPERATION_TYPE_CHANNEL_SWITCH:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, nChn:%d tChnSwitch.bOn:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID, ops.nChannel,
                     m_pCurVideoAttr->bEnable, ops.tChnSwitch.bOn);
            break;
        case E_WEB_OPERATION_TYPE_VENC_LINK_ENABLE:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, nChn:%d tVencLinkEnable.bLinkEnable:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     ops.nChannel, m_pCurVideoAttr->bLink, ops.tVencLinkEnable.bLinkEnable);
            break;
        case E_WEB_OPERATION_TYPE_CAMERA_FPS:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, sensor frameRate:(%f ---> %f)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurCameraAttr->fFramerate, ops.tSnsFpsAttr.fSnsFrameRate);
            break;
        case E_WEB_OPERATION_TYPE_SNS_MIRROR_FLIP:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, sensor Mirror:(%d ---> %d),  Flip:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurCameraAttr->bMirror, ops.tSnsMirrorFlip.bMirror, m_pCurCameraAttr->bFlip, ops.tSnsMirrorFlip.bFlip);
            break;
        case E_WEB_OPERATION_TYPE_EZOOM:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, sensor eZoomRatio:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurCameraAttr->tEZoomAttr.nEZoomRatio, ops.tEZoom.nEZoomRatio);
            break;
        case E_WEB_OPERATION_TYPE_IMAGE_ATTR:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, sensor autoMode:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurCameraAttr->tImageAttr.nAutoMode, ops.tImageAttr.nAutoMode);
            break;
        case E_WEB_OPERATION_TYPE_LDC_ATTR:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, sensor ldc enable:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID,
                     m_pCurCameraAttr->tLdcAttr.bLdcEnable, ops.tLdcAttr.bLdcEnable);
            break;
        case E_WEB_OPERATION_TYPE_AUDIO_ATTR:
            LOG_MM_C(TESTSUITE, "%s: [SnsID:%d, sensor ldc enable:(%d ---> %d)]", ops.strDesc.c_str(), ops.nSnsID, m_AudioAttr.bAedEnable,
                     ops.tAudioAttr.nAedEnable);
            break;
        default:
            LOG_MM_C(TESTSUITE, "GetOperationType()%d: not support yet", ops.GetOperationType());
            break;
    }
}

AX_BOOL CTestSuite::Init() {
    if (CTestSuiteCfgParser::GetInstance()->GetUTCase(m_vecTestCase) && CTestSuiteCfgParser::GetInstance()->GetTestAttr(m_tTestCfg)) {
        m_bEnabled = AX_TRUE;
        return AX_TRUE;
    }
    return AX_FALSE;
}

AX_VOID CTestSuite::InitCameraAttr(AX_U8 nSnsID, AX_U8 nSnsType, WEB_CAMERA_ATTR_T& tCameraAttr) {
    m_mapSns2CameraSetting[nSnsID] = tCameraAttr;
}

AX_VOID CTestSuite::InitAiAttr(AX_U8 nSnsID) {
    m_mapSns2AiAttr[nSnsID].bEnable = AX_TRUE;
    m_mapSns2AiAttr[nSnsID].tPushStategy.ePushMode = (E_AI_DETECT_PUSH_MODE_TYPE)ALGO_HVCFP_PARAM(nSnsID).stPushStrategy.ePushMode;
    m_mapSns2AiAttr[nSnsID].tPushStategy.nPushCounts = ALGO_HVCFP_PARAM(nSnsID).stPushStrategy.nPushCount;
    m_mapSns2AiAttr[nSnsID].tPushStategy.nPushIntervalMs = ALGO_HVCFP_PARAM(nSnsID).stPushStrategy.nInterval;
}

AX_VOID CTestSuite::InitAudio(const WEB_AUDIO_ATTR_T& tAudio) {
    m_AudioAttr = tAudio;
}

AX_VOID CTestSuite::InitIvesAttr(AX_U8 nSnsID) {
    m_mapSns2AiAttr[nSnsID].tEvents.tOD.bEnable = CAlgoOptionHelper::GetInstance()->IsEnableOD(nSnsID);
    m_mapSns2AiAttr[nSnsID].tEvents.tMD.bEnable = CAlgoOptionHelper::GetInstance()->IsEnableMD(nSnsID);
    m_mapSns2AiAttr[nSnsID].tEvents.tSCD.bEnable = CAlgoOptionHelper::GetInstance()->IsEnableSCD(nSnsID);
}

AX_VOID CTestSuite::UpdateOsd(TESTSUITE_OPERATION_T& ops) {
    std::pair<AX_U8, AX_U8> pairIndex;
    if (CWebOptionHelper::GetInstance()->OverlayChnIndex2IvpsGrp(ops.nSnsID, ops.tOsdAttr.nVideoIndex, pairIndex)) {
        AX_U32 nIvpsGrp = pairIndex.first;
        AX_U32 nIvpsChn = pairIndex.second;
        ops.nGroup = nIvpsGrp;
        LOG_MM_I(TESTSUITE, "nSnsID:%d, nVideoIndex:%d, ivpsGrp:%d, nIvpsChn:%d", ops.nSnsID, ops.tOsdAttr.nVideoIndex, nIvpsGrp, nIvpsChn);
        std::vector<OSD_CFG_T> vecOsdCfg;
        if (CWebOptionHelper::GetInstance()->GetOsdConfig(ops.nSnsID, nIvpsGrp, nIvpsChn, vecOsdCfg)) {
            for (AX_U32 i = 0; i < vecOsdCfg.size(); i++) {
                OSD_CFG_T& tOsdConfig = vecOsdCfg[i];
                if (ops.tOsdAttr.nOsdIndex != tOsdConfig.eType) {
                    continue;
                }

                if (tOsdConfig.bEnable == ops.tOsdAttr.bOn) {
                    continue;
                }

                OSD_TYPE_E eType = tOsdConfig.eType;
                if (OSD_TYPE_TIME == eType) {
                    LOG_MM_C(TESTSUITE, "%s nSnsID(%d) nVideoIndex(%d) OSD Time bShow:%d ---> %d", ops.strDesc.c_str(), ops.nSnsID,
                             ops.tOsdAttr.nVideoIndex, tOsdConfig.bEnable, ops.tOsdAttr.bOn);
                } else if (OSD_TYPE_PICTURE == eType) {
                    LOG_MM_C(TESTSUITE, "%s nSnsID(%d) nVideoIndex(%d) OSD Logo bShow:%d ---> %d", ops.strDesc.c_str(), ops.nSnsID,
                             ops.tOsdAttr.nVideoIndex, tOsdConfig.bEnable, ops.tOsdAttr.bOn);
                } else if (OSD_TYPE_STRING_CHANNEL == eType) {
                    LOG_MM_C(TESTSUITE, "%s nSnsID(%d) nVideoIndex(%d) OSD Channel bShow:%d ---> %d", ops.strDesc.c_str(), ops.nSnsID,
                             ops.tOsdAttr.nVideoIndex, tOsdConfig.bEnable, ops.tOsdAttr.bOn);
                } else if (OSD_TYPE_STRING_LOCATION == eType) {
                    LOG_MM_C(TESTSUITE, "%s nSnsID(%d) nVideoIndex(%d) OSD Location bShow:%d ---> %d", ops.strDesc.c_str(), ops.nSnsID,
                             ops.tOsdAttr.nVideoIndex, tOsdConfig.bEnable, ops.tOsdAttr.bOn);
                } else if (OSD_TYPE_PRIVACY == eType) {
                    LOG_MM_C(TESTSUITE, "%s nSnsID(%d) nVideoIndex(%d) OSD Privacy bShow:%d ---> %d", ops.strDesc.c_str(), ops.nSnsID,
                             ops.tOsdAttr.nVideoIndex, tOsdConfig.bEnable, ops.tOsdAttr.bOn);
                } else {
                    break;
                }
                tOsdConfig.bChanged = AX_TRUE;
                tOsdConfig.bEnable = ops.tOsdAttr.bOn;
                if (OSD_TYPE_PRIVACY == ops.tOsdAttr.nOsdIndex) {
                    tOsdConfig.tPrivacyAttr.eType = (OSD_PRIVACY_TYPE_E)ops.tOsdAttr.nPrivType;
                    tOsdConfig.tPrivacyAttr.bSolid = AX_TRUE;
                    tOsdConfig.tPrivacyAttr.nLineWidth = 5;
                    tOsdConfig.tPrivacyAttr.nColor = 0xff0000;
                }
            }
            CWebOptionHelper::GetInstance()->SetOsdConfig(ops.nSnsID, nIvpsGrp, nIvpsChn, vecOsdCfg);
        }
    }
}

AX_VOID CTestSuite::InitVideoAttr(AX_U8 nSnsID, AX_U8 nChnID, WEB_VIDEO_ATTR_T& tVideoAttr) {
    m_mapSns2VideoAttr[nSnsID][nChnID] = tVideoAttr;
}

AX_BOOL CTestSuite::Start() {
    if (!m_UtThread.Start(std::bind(&CTestSuite::RunTest, this, std::placeholders::_1), nullptr, "AppTestSuite")) {
        LOG_MM_E(TESTSUITE, "create UTThread failed");
        return AX_FALSE;
    }
    return AX_TRUE;
}

AX_BOOL CTestSuite::DeInit() {
    return AX_TRUE;
}
AX_BOOL CTestSuite::Stop() {
    if (m_UtThread.IsRunning()) {
        m_UtThread.Stop();
        m_UtThread.Join();
    }
    return AX_TRUE;
}
