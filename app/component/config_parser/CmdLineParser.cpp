/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "CmdLineParser.h"
#include <utility>
#include "AppLogApi.h"
#include "IPPLBuilder.h"

using namespace std;

#define CMD_PARSER "CMD_PARSER"

AX_S32 CCmdLineParser::Parse(int argc, const char* const argv[]) {
#ifndef _OPAL_LIB_
    m_mapParams.clear();

    std::unique_ptr<cmdline::parser> pParser;
    pParser = make_unique<cmdline::parser>();

    pParser->add<string>(AX_APP_CMD_KEY_PPL, 'p', "ppl index", true, "0");
    pParser->add<string>(AX_APP_CMD_KEY_TYPE, 's', "sensor type", true, "0");
    pParser->add<string>(AX_APP_CMD_KEY_LOG_LEVEL, 'l', "log level", false, "3");
    pParser->add<string>(AX_APP_CMD_KEY_LOG_TARGET, 't', "log target", false, "4");
    pParser->add<string>(AX_APP_CMD_KEY_CONFIG_PATH, 'c', "config path", false, "./config");
    pParser->add(AX_APP_CMD_KEY_STATIC_LIB, 'a', "static lib");
    pParser->add<string>(AX_APP_UT, 'u', "ut case", false, "0");
    pParser->add<string>(AX_APP_CMD_KEY_DELAY_EXIT, 'z', "delay exit", false, "0");

#ifdef FRTTESTLP_SUPPORT
    pParser->add<string>(AX_APP_CMD_KEY_VENC_ENABLE, 'v', "venc", false, "1");
    pParser->add<string>(AX_APP_CMD_KEY_JENC_ENABLE, 'j', "jenc", false, "1");
    pParser->add<string>(AX_APP_CMD_KEY_DETECT_ENABLE, 'm', "detect", false, "1");
    pParser->add<string>(AX_APP_CMD_KEY_SNS_FPS, 'f', "sensor_fps", false, "0");
    pParser->add<string>(AX_APP_CMD_KEY_SCENARIO, 'n', "scenario", false, "0");

#else
    pParser->add(AX_APP_CMD_KEY_GDB_DEBUG, 'd', "gdb debug");
    pParser->add<string>(AX_APP_CMD_KEY_SCENARIO, 'n', "scenario", false, "1");

#endif

    if (!pParser->parse(argc, argv)) {
        printf("1CMDLine parameter parse failed. %s\n", pParser->error_full().c_str());
        // return -1;
    }

    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_PPL, pParser->get<string>(AX_APP_CMD_KEY_PPL)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_TYPE, pParser->get<string>(AX_APP_CMD_KEY_TYPE)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_SCENARIO, pParser->get<string>(AX_APP_CMD_KEY_SCENARIO)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_LOG_LEVEL, pParser->get<string>(AX_APP_CMD_KEY_LOG_LEVEL)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_LOG_TARGET, pParser->get<string>(AX_APP_CMD_KEY_LOG_TARGET)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_CONFIG_PATH, pParser->get<string>(AX_APP_CMD_KEY_CONFIG_PATH)));

#ifdef FRTTESTLP_SUPPORT
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_VENC_ENABLE, pParser->get<string>(AX_APP_CMD_KEY_VENC_ENABLE)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_JENC_ENABLE, pParser->get<string>(AX_APP_CMD_KEY_JENC_ENABLE)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_DETECT_ENABLE, pParser->get<string>(AX_APP_CMD_KEY_DETECT_ENABLE)));
    m_mapParams.insert(make_pair(AX_APP_CMD_KEY_SNS_FPS, pParser->get<string>(AX_APP_CMD_KEY_SNS_FPS)));

#endif

    if (pParser->exist(AX_APP_UT)) {
        m_mapParams.insert(make_pair(AX_APP_UT, pParser->get<string>(AX_APP_UT)));
    }

    if (pParser->exist(AX_APP_CMD_KEY_DELAY_EXIT)) {
        m_mapParams.insert(make_pair(AX_APP_CMD_KEY_DELAY_EXIT, pParser->get<string>(AX_APP_CMD_KEY_DELAY_EXIT)));
    }

    return 0;
#else
    return 0;
#endif
}

AX_BOOL CCmdLineParser::GetIntValue(const string& strKey, AX_S32& nOutVal) {
#ifndef _OPAL_LIB_
    std::map<string, string>::iterator it = m_mapParams.find(strKey);
    if (it != m_mapParams.end()) {
        nOutVal = atoi(it->second.c_str());
        return AX_TRUE;
    } else {
        LOG_MM_W(CMD_PARSER, "Can not get value for key: %s", strKey.c_str());
    }

    return AX_FALSE;
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::GetStrValue(const string& strKey, string& strOutVal) {
#ifndef _OPAL_LIB_
    std::map<string, string>::iterator it = m_mapParams.find(strKey);
    if (it != m_mapParams.end()) {
        strOutVal = it->second;
        return AX_TRUE;
    }

    return AX_FALSE;
#else
    return AX_FALSE;
#endif
}

string CCmdLineParser::ScenarioEnum2Str(AX_U8 nScenario) {
#ifndef _OPAL_LIB_
    switch ((AX_APP_SCENARIO_E)nScenario) {
        case E_APP_SCENARIO_DEFAULT: {
            return AX_APP_SCENARIO_DEFAULT;
        }
        case E_APP_SCENARIO_SINGLE: {
            return AX_APP_SCENARIO_SINGLE;
        }
        case E_APP_SCENARIO_DUAL_WITH_VO: {
            return AX_APP_SCENARIO_DUAL_WITH_VO;
        }
        case E_APP_SCENARIO_SINGLE_WITH_VO: {
            return AX_APP_SCENARIO_SINGLE_WITH_VO;
        }
        case E_APP_SCENARIO_DUAL_10_1_WITH_VO: {
            return AX_APP_SCENARIO_DUAL_10_1_WITH_VO;
        }
        case E_APP_SCENARIO_SINGLE_10_1__WITH_VO: {
            return AX_APP_SCENARIO_SINGLE_10_1_WITH_VO;
        }
        default:
            return AX_APP_SCENARIO_INVALID;
    }

    return AX_APP_SCENARIO_INVALID;
#else
    return AX_APP_SCENARIO_INVALID;
#endif
}

AX_BOOL CCmdLineParser::GetPPLIndex(AX_S32& nIndex) {
#ifndef _OPAL_LIB_
    return GetIntValue(AX_APP_CMD_KEY_PPL, nIndex);
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::GetLoadType(AX_S32& nType) {
#ifndef _OPAL_LIB_
    return GetIntValue(AX_APP_CMD_KEY_TYPE, nType);
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::GetScenario(AX_S32& nScenario) {
#ifndef _OPAL_LIB_
    return GetIntValue(AX_APP_CMD_KEY_SCENARIO, nScenario);
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::GetLogLevel(AX_S32& nLevel) {
#ifndef _OPAL_LIB_
    return GetIntValue(AX_APP_CMD_KEY_LOG_LEVEL, nLevel);
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::GetLogTarget(AX_S32& nLogTarget) {
#ifndef _OPAL_LIB_
    return GetIntValue(AX_APP_CMD_KEY_LOG_TARGET, nLogTarget);
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::GetConfigPath(std::string& configPath) {
#ifndef _OPAL_LIB_
    return GetStrValue(AX_APP_CMD_KEY_CONFIG_PATH, configPath);
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::GetDelayExitTime(AX_S32& nDelayExitTime) {
#ifndef _OPAL_LIB_
    return GetIntValue(AX_APP_CMD_KEY_DELAY_EXIT, nDelayExitTime);
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::isUTEnabled() {
#ifndef _OPAL_LIB_
    AX_S32 nIndex = 0;
    GetIntValue(AX_APP_UT, nIndex);
    return (nIndex == 0) ? AX_FALSE : AX_TRUE;
#else
    return AX_FALSE;
#endif
}

AX_BOOL CCmdLineParser::isDulSnsMode() {
#ifndef _OPAL_LIB_
    AX_S32 nType;
    GetIntValue(AX_APP_CMD_KEY_TYPE, nType);
    return nType % 2 ? AX_FALSE : AX_TRUE;
#else
    return AX_FALSE;
#endif
}

#ifdef FRTTESTLP_SUPPORT
AX_BOOL CCmdLineParser::GetVencEnable(AX_S32& nIndex) {
    return GetIntValue(AX_APP_CMD_KEY_VENC_ENABLE, nIndex);
}

AX_BOOL CCmdLineParser::GetJencEnable(AX_S32& nIndex) {
    return GetIntValue(AX_APP_CMD_KEY_JENC_ENABLE, nIndex);
}

AX_BOOL CCmdLineParser::GetDteEnable(AX_S32& nIndex) {
    return GetIntValue(AX_APP_CMD_KEY_DETECT_ENABLE, nIndex);
}

AX_BOOL CCmdLineParser::GetSnsFps(AX_S32& nIndex) {
    return GetIntValue(AX_APP_CMD_KEY_SNS_FPS, nIndex);
}

#endif