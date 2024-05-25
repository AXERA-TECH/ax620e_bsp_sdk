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

#include "AXSingleton.h"
#include "WebServer.h"
#include "picojson.h"

struct TESTSUITE_OPERATION_T : public WEB_REQ_OPERATION_T {
    std::string strDesc;
};

typedef struct _APP_TEST_SUITE_CONFIG_T {
    AX_S64 nLoopNum{0};
    AX_U32 nDefIntervalMs{0};
    AX_BOOL bRandomEnable{AX_FALSE};
} APP_TEST_SUITE_CONFIG_T;

class CTestSuiteCfgParser : public CAXSingleton<CTestSuiteCfgParser> {
    friend class CAXSingleton<CTestSuiteCfgParser>;

public:
    AX_BOOL GetUTCase(std::vector<TESTSUITE_OPERATION_T>& vecOutConfig);
    AX_BOOL GetTestAttr(APP_TEST_SUITE_CONFIG_T& tTestCfg);

private:
    CTestSuiteCfgParser(AX_VOID) = default;
    ~CTestSuiteCfgParser(AX_VOID) = default;

    AX_BOOL InitOnce() override;

    AX_BOOL ParseFile(const std::string& strPath);
    AX_BOOL ParseJson(picojson::object& objJsonRoot);

    AX_BOOL ParseVINJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq);
    AX_BOOL ParseVENCJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq);
    AX_BOOL ParseAIJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq);
    AX_BOOL ParseOSDJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq);
    AX_BOOL ParseAUDIOJson(picojson::object& objSetting, std::vector<TESTSUITE_OPERATION_T>& vecReq);

private:
    std::vector<TESTSUITE_OPERATION_T> m_vecGrpSetting;
    APP_TEST_SUITE_CONFIG_T m_TestCfg;
};