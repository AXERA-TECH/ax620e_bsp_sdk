/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifdef VO_SUPPORT
#pragma once

#include <map>
#include "AXSingleton.h"
#include "VideoDecoder.h"
#include "picojson.h"

class CDecoderCfgParser : public CAXSingleton<CDecoderCfgParser> {
    friend class CAXSingleton<CDecoderCfgParser>;

public:
    AX_BOOL GetConfig(std::map<AX_U8, VDEC_GRP_CONFIG_T> &m_mapVdecChnConfig);

private:
    CDecoderCfgParser(AX_VOID) = default;
    ~CDecoderCfgParser(AX_VOID) = default;

    AX_BOOL InitOnce() override;
    AX_BOOL ParseFile(const std::string &strPath, std::map<AX_U8, VDEC_GRP_CONFIG_T> &m_mapVdecChnConfig);
    AX_BOOL ParseJson(picojson::object &objJsonRoot, std::map<AX_U8, VDEC_GRP_CONFIG_T> &m_mapVdecChnConfig);
};

#endif