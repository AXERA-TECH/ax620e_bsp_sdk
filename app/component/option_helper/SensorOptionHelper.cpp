/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "SensorOptionHelper.h"
#include "CommonUtils.hpp"
#include "SensorCfgParser.h"

#define SNS_OPTION_HELPER "SNS_HELPER"

AX_BOOL CSensorOptionHelper::InitOnce() {
    return CSensorCfgParser::GetInstance()->GetConfig(m_mapSensorCfg, m_nSensorCount);
}

AX_BOOL CSensorOptionHelper::GetSensorConfig(AX_U8 nSnsIndex, SENSOR_CONFIG_T& tOutSensorCfg) {
    if (m_mapSensorCfg.find(nSnsIndex) == m_mapSensorCfg.end()) {
        return AX_FALSE;
    }

    tOutSensorCfg = m_mapSensorCfg[nSnsIndex];

    return AX_TRUE;
}

AX_BOOL CSensorOptionHelper::SetSensorConfig(AX_U8 nSnsIndex, const SENSOR_CONFIG_T& tOutSensorCfg) {
    m_mapSensorCfg[nSnsIndex] = tOutSensorCfg;

    return AX_TRUE;
}

/* Provided for dual-sensor stitching */
AX_VOID CSensorOptionHelper::SetSensorCount(AX_U32 nCount) {
    m_nSensorCount = nCount;
}

std::map<AX_U8, SENSOR_VINIVPS_CFG_T> CSensorOptionHelper::GetMapVinIvps(AX_VOID) {
    std::map<AX_U8, SENSOR_VINIVPS_CFG_T> m_mapVinIvps;
    SENSOR_VINIVPS_CFG_T stAttr;
    for (AX_U8 i = 0; i < m_mapSensorCfg.size(); i++) {
        for (AX_U8 j = 0; j < m_mapSensorCfg[i].nPipeCount; j++) {
            stAttr.nIvpsGrp = m_mapSensorCfg[i].arrPipeAttr[j].nIvpsGrp;
            stAttr.nVinIvpsMode = m_mapSensorCfg[i].arrPipeAttr[j].nVinIvpsMode;

            m_mapVinIvps[m_mapSensorCfg[i].arrPipeAttr[j].nPipeID] = stAttr;
        }
    }
    return m_mapVinIvps;
}