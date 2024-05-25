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
#include "AXLockQ.hpp"
#include "AXSingleton.h"
#include "AXThread.hpp"
#include "IPPLBuilder.h"
#include "TestSuiteCfgParser.h"
#include "WebOptionHelper.h"

class IPPLBuilder;

class CTestSuite : public CAXSingleton<CTestSuite> {
    friend class CAXSingleton<CTestSuite>;

public:
    AX_VOID BindPPL(IPPLBuilder* pPPLBuilder) {
        m_pPPLBuilder = pPPLBuilder;
    };

    AX_BOOL Init();
    AX_BOOL DeInit();
    AX_BOOL Start();
    AX_BOOL Stop();

    AX_BOOL IsEnabled() {
        return m_bEnabled;
    }
    AX_VOID InitCameraAttr(AX_U8 nSnsID, AX_U8 nSnsType, WEB_CAMERA_ATTR_T& tCameraAttr);
    AX_VOID InitVideoAttr(AX_U8 nSnsID, AX_U8 nChnID, WEB_VIDEO_ATTR_T& tVideoAttr);
    AX_VOID InitAiAttr(AX_U8 nSnsID);
    AX_VOID InitIvesAttr(AX_U8 nSnsID);
    AX_VOID InitAudio(const WEB_AUDIO_ATTR_T& tAudio);

private:
    CTestSuite() = default;
    ~CTestSuite() = default;
    AX_VOID RunTest(AX_VOID* pArg);
    AX_BOOL Process(TESTSUITE_OPERATION_T& ops);
    AX_VOID PrintCaseParam(TESTSUITE_OPERATION_T& ops);
    AX_VOID SortCases(std::vector<TESTSUITE_OPERATION_T>& vecWebRequests);
    AX_VOID UpdateWebAttr(TESTSUITE_OPERATION_T& ops);
    AX_BOOL SkipOpera(TESTSUITE_OPERATION_T ops);
    AX_VOID SaveOpera(TESTSUITE_OPERATION_T ops);
    AX_VOID UpdateOsd(TESTSUITE_OPERATION_T& ops);

private:
    AX_BOOL m_bEnabled{AX_FALSE};
    AX_BOOL m_bInitState{AX_FALSE};
    CAXThread m_UtThread;
    IPPLBuilder* m_pPPLBuilder{nullptr};
    std::vector<TESTSUITE_OPERATION_T> m_vecTestCase;
    APP_TEST_SUITE_CONFIG_T m_tTestCfg;
    std::map<AX_U8, WEB_CAMERA_ATTR_T> m_mapSns2CameraSetting;
    std::map<AX_U8, std::map<AX_U8, WEB_VIDEO_ATTR_T>> m_mapSns2VideoAttr;
    std::map<AX_U8, AI_ATTR_T> m_mapSns2AiAttr;
    WEB_CAMERA_ATTR_T* m_pCurCameraAttr{nullptr};
    OSD_SENSOR_CONFIG_T* m_pCurOsdAttr{nullptr};
    WEB_VIDEO_ATTR_T* m_pCurVideoAttr{nullptr};
    AI_ATTR_T* m_pCurAiAttr{nullptr};
    WEB_AUDIO_ATTR_T m_AudioAttr;
    AX_U32 m_nDefInterVal{0};
};
