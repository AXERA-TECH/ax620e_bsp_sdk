/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "PoolCfgParser.h"
#include <fstream>
#include "AppLogApi.h"
#include "CmdLineParser.h"
#include "CommonUtils.hpp"

using namespace ::std;

#define POOL_PARSER "POOL_PARSER"

#define POOL_PARSER_KEY_LEN 32

AX_BOOL CPoolCfgParser::InitOnce() {
    return AX_TRUE;
}

AX_BOOL CPoolCfgParser::GetConfig(std::map<std::string, std::string>& mapKeys) {
#ifndef _OPAL_LIB_
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        LOG_MM_E(POOL_PARSER, "ppl config dir is empty");
        return AX_FALSE;
    }

    string strPoolCfgFile = strConfigDir + "/pool.ini";

    if (!m_iniParser.Load(strPoolCfgFile)) {
        LOG_MM_E(POOL_PARSER, "load %s fail", strPoolCfgFile.c_str());
        return AX_FALSE;
    }

    AX_S32 nLoadType = E_LOAD_TYPE_MAX;
    if (!CCmdLineParser::GetInstance()->GetLoadType(nLoadType)) {
        LOG_MM_E(POOL_PARSER, "get sns type fail");
        return AX_FALSE;
    }

    AX_S32 nCfgScenario = 0;
    CCmdLineParser::GetInstance()->GetScenario(nCfgScenario);

    AX_CHAR strPoolKey[POOL_PARSER_KEY_LEN] = {0};
    sprintf(strPoolKey, "S%dN%d", nLoadType, nCfgScenario);

    m_iniParser.GetAllKeys(strPoolKey, mapKeys);

    if (mapKeys.size() == 0) {
        string strScenario = CCmdLineParser::ScenarioEnum2Str((AX_U8)nCfgScenario);
        nCfgScenario = m_iniParser.GetIntValue("N-LINK", strScenario.c_str(), 1);
        sprintf(strPoolKey, "S%dN%d", nLoadType, nCfgScenario);
        LOG_MM_C(POOL_PARSER, "Links to %d, strPoolKey:%s", nCfgScenario, strPoolKey);
        m_iniParser.GetAllKeys(strPoolKey, mapKeys);
        if (mapKeys.size() == 0) {
            return AX_FALSE;
        }
    }

    return AX_TRUE;
#else
    return AX_TRUE;
#endif
}
