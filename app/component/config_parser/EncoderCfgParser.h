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

#include <map>
#include "AXSingleton.h"
#include "AXVideo.hpp"
#include "JpegEncoder.h"
#include "VideoEncoder.h"
#include "picojson.h"

class CEncoderCfgParser : public CAXSingleton<CEncoderCfgParser> {
    friend class CAXSingleton<CEncoderCfgParser>;

public:
    AX_BOOL GetConfig(std::map<AX_U8, VIDEO_CONFIG_T>& mapVencChnConfig, std::map<AX_U8, JPEG_CONFIG_T>& mapJencChnConfig);

private:
    CEncoderCfgParser(AX_VOID) = default;
    ~CEncoderCfgParser(AX_VOID) = default;

    AX_BOOL InitOnce() override;
    AX_BOOL ParseFile(const std::string& strPath, std::map<AX_U8, VIDEO_CONFIG_T>& mapVencChnConfig,
                      std::map<AX_U8, JPEG_CONFIG_T>& mapJencChnConfig);
    AX_BOOL ParseJson(picojson::object& objJsonRoot, std::map<AX_U8, VIDEO_CONFIG_T>& mapVencChnConfig,
                      std::map<AX_U8, JPEG_CONFIG_T>& mapJencChnConfig);
};
