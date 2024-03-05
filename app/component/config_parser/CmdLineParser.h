/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#pragma once

#include <map>
#include "AXSingleton.h"
#include "ax_base_type.h"
#include "cmdline.hpp"

#define AX_APP_CMD_KEY_PPL "ppl"
#define AX_APP_CMD_KEY_TYPE "type"
#define AX_APP_CMD_KEY_SCENARIO "scenario"
#define AX_APP_CMD_KEY_LOG_LEVEL "loglv"
#define AX_APP_CMD_KEY_LOG_TARGET "logTarget"
#define AX_APP_CMD_KEY_GDB_DEBUG "gdb"
#define AX_APP_CMD_KEY_CONFIG_PATH "configPath"
#define AX_APP_CMD_KEY_STATIC_LIB "staticlib"
#define AX_APP_SCENARIO_DEFAULT "scenario_0"
#define AX_APP_SCENARIO_SINGLE "scenario_1"
#define AX_APP_SCENARIO_DUAL_WITH_VO "scenario_2"
#define AX_APP_SCENARIO_SINGLE_WITH_VO "scenario_3"
#define AX_APP_SCENARIO_SLT "scenario_slt"
#define AX_APP_UT "unit_test"

#ifdef FRTTESTLP_SUPPORT
#define AX_APP_CMD_KEY_VENC_ENABLE "venc"
#define AX_APP_CMD_KEY_JENC_ENABLE "jenc"
#define AX_APP_CMD_KEY_DETECT_ENABLE "detect"
#define AX_APP_CMD_KEY_SNS_FPS "sensor_fps"

#endif
#define AX_APP_CMD_KEY_DELAY_EXIT "delay_exit"
#define AX_APP_SCENARIO_INVALID "scenario_invalid"

typedef enum {
    E_LOAD_TYPE_OS04A10, /* E_SNS_TYPE_OS04A10 */
    E_LOAD_TYPE_SC450AI, /* E_SNS_TYPE_SC450AI */
    E_LOAD_TYPE_IMX678, /* E_SNS_TYPE_IMX678 */
    E_LOAD_TYPE_SC200AI, /* E_SNS_TYPE_SC200AI */
    E_LOAD_TYPE_SC500AI, /* E_SNS_TYPE_SC500AI */
    E_LOAD_TYPE_SC850SL, /* E_SNS_TYPE_SC850SL */
    E_LOAD_TYPE_C4395, /* E_SNS_TYPE_C4395 */
    E_LOAD_TYPE_GC4653, /* E_SNS_TYPE_GC4653 */
    E_LOAD_TYPE_MIS2032, /* E_SNS_TYPE_MIS2032 */

    // Sensor Combo
    E_LOAD_TYPE_COMBO_BASE = 100,
    E_LOAD_TYPE_OS04A10_SC200AI = 103, /* E_SNS_TYPE_OS04A10 + E_LOAD_TYPE_OS04A10_SC200AI */
    E_LOAD_TYPE_SC450AI_SC200AI = 113, /* E_SNS_TYPE_SC450AI + E_LOAD_TYPE_OS04A10_SC200AI */
    E_LOAD_TYPE_GC4653_SC200AI = 173, /* E_SNS_TYPE_GC4653 + E_LOAD_TYPE_OS04A10_SC200AI */
    E_LOAD_TYPE_MAX
} AX_IPC_LOAD_TYPE_E;

class CCmdLineParser : public CAXSingleton<CCmdLineParser> {
    friend class CAXSingleton<CCmdLineParser>;

public:
    AX_S32 Parse(int argc, const char* const argv[]);

    AX_BOOL GetPPLIndex(AX_S32& nIndex);
    AX_BOOL GetLoadType(AX_S32& nType);
    AX_BOOL GetScenario(AX_S32& nScenario);
    AX_BOOL GetLogLevel(AX_S32& nLevel);
    AX_BOOL GetLogTarget(AX_S32& nLogTarget);
    AX_BOOL GetConfigPath(std::string& configPath);
    AX_BOOL GetDelayExitTime(AX_S32& nDelayExitTime);

    static std::string ScenarioEnum2Str(AX_U8 nScenario);
    AX_BOOL isDulSnsMode();
    AX_BOOL isUTEnabled();

#ifdef FRTTESTLP_SUPPORT
    AX_BOOL GetVencEnable(AX_S32& nIndex);
    AX_BOOL GetJencEnable(AX_S32& nIndex);
    AX_BOOL GetDteEnable(AX_S32& nIndex);
    AX_BOOL GetSnsFps(AX_S32& nIndex);
#endif
private:
    CCmdLineParser(AX_VOID) = default;
    ~CCmdLineParser(AX_VOID) = default;

    AX_BOOL GetIntValue(const std::string& strKey, AX_S32& nOutVal);
    AX_BOOL GetStrValue(const std::string& strKey, std::string& strOutVal);

private:
    std::map<std::string, std::string> m_mapParams;
};
