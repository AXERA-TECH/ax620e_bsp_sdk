/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "SensorFactory.hpp"
#include <exception>
#include "OS04a10.h"
#include "SC450AI.h"
#include "IMX678.h"
#include "SC200AI.h"
#include "SC500AI.h"
#include "SC850SL.h"
#include "C4395.h"
#include "GC4653.h"
#include "MIS2032.h"
#include "AppLogApi.h"

#define SENSORFACTORY "SENSOR_FACTORY"

ISensor *CSensorFactory::CreateSensor(const SENSOR_CONFIG_T &tSensorCfg) {
    ISensor *pSnsInstance{nullptr};
    switch (tSensorCfg.eSensorType) {
        case E_SNS_TYPE_OS04A10:
        case E_SNS_TYPE_OS04A10_LF:
        case E_SNS_TYPE_OS04A10_SF: {
#ifdef OS04A10_SUPPORT
            pSnsInstance = new COS04a10(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "OS04A10 not support");
#endif
            break;
        }
        case E_SNS_TYPE_SC450AI:
        case E_SNS_TYPE_SC450AI_LF:
        case E_SNS_TYPE_SC450AI_SF: {
#ifdef SC450AI_SUPPORT
            pSnsInstance = new CSC450AI(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "SC450AI not support");
#endif
            break;
        }
        case E_SNS_TYPE_IMX678:
        case E_SNS_TYPE_IMX678_LF:
        case E_SNS_TYPE_IMX678_SF: {
#ifdef IMX678_SUPPORT
            pSnsInstance = new CIMX678(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "IMX678 not support");
#endif
            break;
        }
        case E_SNS_TYPE_SC200AI:
        case E_SNS_TYPE_SC200AI_LF:
        case E_SNS_TYPE_SC200AI_SF: {
#ifdef SC200AI_SUPPORT
            pSnsInstance = new CSC200AI(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "SC200AI not support");
#endif
            break;
        }
        case E_SNS_TYPE_SC500AI:
        case E_SNS_TYPE_SC500AI_LF:
        case E_SNS_TYPE_SC500AI_SF: {
#ifdef SC500AI_SUPPORT
            pSnsInstance = new CSC500AI(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "SC500AI not support");
#endif
            break;
        }
        case E_SNS_TYPE_SC850SL:
        case E_SNS_TYPE_SC850SL_LF:
        case E_SNS_TYPE_SC850SL_SF: {
#ifdef SC850SL_SUPPORT
            pSnsInstance = new CSC850SL(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "SC850SL not support");
#endif
            break;
        }
        case E_SNS_TYPE_C4395:
        case E_SNS_TYPE_C4395_LF:
        case E_SNS_TYPE_C4395_SF: {
#ifdef C4395_SUPPORT
            pSnsInstance = new CC4395(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "C4395 not support");
#endif
            break;
        }
        case E_SNS_TYPE_GC4653:
        case E_SNS_TYPE_GC4653_LF:
        case E_SNS_TYPE_GC4653_SF: {
#ifdef GC4653_SUPPORT
            pSnsInstance = new CGC4653(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "GC4653 not support");
#endif
            break;
        }
        case E_SNS_TYPE_MIS2032:
        case E_SNS_TYPE_MIS2032_LF:
        case E_SNS_TYPE_MIS2032_SF: {
#ifdef MIS2032_SUPPORT
            pSnsInstance = new CMIS2032(tSensorCfg);
#else
            LOG_MM_E(SENSORFACTORY, "MIS2032 not support");
#endif
            break;
        }
        default: {
            return nullptr;
        }
    }

    return pSnsInstance;
}

AX_VOID CSensorFactory::DestorySensor(ISensor *&pSensor) {
    if (pSensor) {
        ((CBaseSensor *)pSensor)->DeInit();
        delete pSensor;
        pSensor = nullptr;
    }
}
