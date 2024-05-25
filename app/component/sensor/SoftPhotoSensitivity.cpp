/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <string>
#include "SoftPhotoSensitivity.h"
#include "ElapsedTimer.hpp"
#include "AppLogApi.h"

#define SPS_MONITOR "SPS"

#define SPS_MONITOR_INTERVAL                       (5000) // 5s
#define SPS_STATUS_HOLD_TIME                       (15000) // 15s
#define SPS_WARM_DEFAULT_THRESHOLD                 (50)

CSoftPhotoSensitivity::CSoftPhotoSensitivity(CBaseSensor *Sensor) : m_pSensorInst(Sensor) {
    m_nSnsId = m_pSensorInst->GetSnsConfig().nSnsID;
}

AX_BOOL CSoftPhotoSensitivity::Start(const SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T& tAttr) {
    if (!m_tStatus.bMonitorStart && m_pSensorInst) {
        m_tAttr = tAttr;

        StartMonitor();
    }

    return AX_TRUE;
}

AX_BOOL CSoftPhotoSensitivity::Stop() {
    LOG_MM_C(SPS_MONITOR, "[%d] +++", m_nSnsId);

    {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_SpsThread.Stop();
        m_cv.notify_one();
    }

    m_SpsThread.Join();

    m_tStatus.bMonitorStart = AX_FALSE;
    m_tStatus.bUpdateTrigger = AX_FALSE;
    m_tStatus.onTicks = 0;
    m_tStatus.offTicks = 0;
    m_tStatus.curDayNightStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_UNKOWN;

    LOG_MM_C(SPS_MONITOR, "[%d] ---", m_nSnsId);

    return AX_TRUE;
}

AX_BOOL CSoftPhotoSensitivity::StartMonitor() {
    if (SNS_SOFT_PHOTOSENSITIVITY_IR == m_tAttr.eType
        || SNS_SOFT_PHOTOSENSITIVITY_WARMLIGHT == m_tAttr.eType) {
        std::string threadName = "APP_SpsMoni_" + std::to_string(m_nSnsId);
        if (!m_SpsThread.Start([this](AX_VOID* pArg) -> AX_VOID { Monitor(pArg); }, nullptr, threadName.c_str())) {
            return AX_FALSE;
        }

        m_tStatus.bMonitorStart = AX_TRUE;
    }

    return AX_TRUE;
}

AX_BOOL CSoftPhotoSensitivity::Update(const SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T& tAttr) {
    if (m_tStatus.bMonitorStart) {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_tAttr = tAttr;
        m_tStatus.bUpdateTrigger = AX_TRUE;
        m_cv.notify_one();
    } else {
        Start(tAttr);
    }

    return AX_TRUE;
}

AX_VOID CSoftPhotoSensitivity::SetWarmLightAttr(const SENSOR_WARMLIGHT_ATTR_T& tWarmAttr) {
    if (tWarmAttr.nOnLightSensitivity == SPS_WARM_DEFAULT_THRESHOLD) {
        m_tStatus.onLightThreshold = tWarmAttr.nOnLightExpValMid;
    } else if (tWarmAttr.nOnLightSensitivity > SPS_WARM_DEFAULT_THRESHOLD) {
        m_tStatus.onLightThreshold = tWarmAttr.nOnLightExpValMid - (((tWarmAttr.nOnLightSensitivity - SPS_WARM_DEFAULT_THRESHOLD) * 2) * (tWarmAttr.nOnLightExpValMid - tWarmAttr.nOnLightExpValMin) / 100);
    } else if (tWarmAttr.nOnLightSensitivity < SPS_WARM_DEFAULT_THRESHOLD) {
        m_tStatus.onLightThreshold = tWarmAttr.nOnLightExpValMid + (((SPS_WARM_DEFAULT_THRESHOLD - tWarmAttr.nOnLightSensitivity) * 2) * (tWarmAttr.nOnLightExpValMax - tWarmAttr.nOnLightExpValMid) / 100);
    } else {
        m_tStatus.onLightThreshold = tWarmAttr.nOnLightExpValMid;
    }

    if (tWarmAttr.nOffLightSensitivity == SPS_WARM_DEFAULT_THRESHOLD) {
        m_tStatus.offLightThreshold = tWarmAttr.nOffLightExpValMid;
    } else if (tWarmAttr.nOffLightSensitivity > SPS_WARM_DEFAULT_THRESHOLD) {
        m_tStatus.offLightThreshold = tWarmAttr.nOffLightExpValMid + (((tWarmAttr.nOffLightSensitivity - SPS_WARM_DEFAULT_THRESHOLD) * 2) * (tWarmAttr.nOffLightExpValMax - tWarmAttr.nOffLightExpValMid) / 100);
    } else if (tWarmAttr.nOffLightSensitivity < SPS_WARM_DEFAULT_THRESHOLD) {
        m_tStatus.offLightThreshold = tWarmAttr.nOffLightExpValMid - (((SPS_WARM_DEFAULT_THRESHOLD - tWarmAttr.nOffLightSensitivity) * 2) * (tWarmAttr.nOffLightExpValMid - tWarmAttr.nOffLightExpValMin) / 100);
    } else {
        m_tStatus.offLightThreshold = tWarmAttr.nOffLightExpValMid;
    }

    m_tStatus.onTicks = 0;
    m_tStatus.offTicks = 0;
    m_tStatus.curDayNightStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_UNKOWN;
}

AX_VOID CSoftPhotoSensitivity::SetIrAttr(const SENSOR_IRCUT_ATTR_T& tIrAttr) {
    if (!m_pSensorInst) {
        return;
    }

    AX_DAYNIGHT_MODE_E eDayNightStatus = AX_DAYNIGHT_MODE_DAY;

    if (!m_pSensorInst->GetDayNightStatus(eDayNightStatus)) {
        return;
    }

    if (!m_pSensorInst->SetIrAttr(tIrAttr)) {
        return;
    }

    m_tStatus.curDayNightStatus = eDayNightStatus;
}

AX_VOID CSoftPhotoSensitivity::WarmLightMonitor(const SENSOR_WARMLIGHT_ATTR_T& tWarmAttr) {
    if (!m_pSensorInst){
        return;
    }

    AX_ISP_IQ_AE_STATUS_T tAeStatus;
    if (!m_pSensorInst->GetAeStatus(tAeStatus)) {
        return;
    }

    AX_U64 ticks = CElapsedTimer::GetTickCount();

    // night mode
    if (tAeStatus.tAlgStatus.nExpVal >= m_tStatus.onLightThreshold) {
        m_tStatus.offTicks = 0;

        if (m_tStatus.onTicks == 0) {
            m_tStatus.onTicks = ticks;
        }

        if (ticks - m_tStatus.onTicks > SPS_STATUS_HOLD_TIME) {
            LOG_MM_N(SPS_MONITOR, "The current expval meets the night conditions.");

            if (SNS_SOFT_PHOTOSENSITIVITY_STATUS_NIGHT != m_tStatus.curDayNightStatus) {
                if (m_tAttr.bAutoCtrl && m_pSensorInst) {
                    m_pSensorInst->ChangeDaynightMode(AX_DAYNIGHT_MODE_NIGHT);
                }

                {
                    SOFT_PHOTOSENSITIVITY_RESULT_T tResult;
                    tResult.eType = SNS_SOFT_PHOTOSENSITIVITY_WARMLIGHT;
                    tResult.eStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_NIGHT;

                    NotifyAll(m_nSnsId, 0, &tResult);
                }
            }

            m_tStatus.onTicks = 0;
        }
    } else if (tAeStatus.tAlgStatus.nExpVal < m_tStatus.offLightThreshold) {
        m_tStatus.onTicks = 0;

        if (m_tStatus.offTicks == 0) {
            m_tStatus.offTicks = ticks;
        }

        if (ticks - m_tStatus.offTicks > SPS_STATUS_HOLD_TIME) {
            LOG_MM_N(SPS_MONITOR, "The current expval meets the day conditions.");

            if (SNS_SOFT_PHOTOSENSITIVITY_STATUS_DAY != m_tStatus.curDayNightStatus) {
                if (m_tAttr.bAutoCtrl && m_pSensorInst) {
                    m_pSensorInst->ChangeDaynightMode(AX_DAYNIGHT_MODE_DAY);
                }

                {
                    SOFT_PHOTOSENSITIVITY_RESULT_T tResult;
                    tResult.eType = SNS_SOFT_PHOTOSENSITIVITY_WARMLIGHT;
                    tResult.eStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_DAY;

                    NotifyAll(m_nSnsId, 0, &tResult);
                }
            }

            m_tStatus.offTicks = 0;
        }
    }

    AX_DAYNIGHT_MODE_E eDayNightStatus = AX_DAYNIGHT_MODE_DAY;
    if (!m_pSensorInst->GetDayNightStatus(eDayNightStatus)) {
        return;
    }

    m_tStatus.curDayNightStatus = eDayNightStatus;
}

AX_VOID CSoftPhotoSensitivity::IrMonitor(const SENSOR_IRCUT_ATTR_T& tIrAttr) {
    if (!m_pSensorInst){
        return;
    }

    AX_DAYNIGHT_MODE_E eDayNightStatus = AX_DAYNIGHT_MODE_DAY;
    if (!m_pSensorInst->GetDayNightStatus(eDayNightStatus)) {
        return;
    }

    if (eDayNightStatus != m_tStatus.curDayNightStatus) {
        switch(eDayNightStatus) {
            case AX_DAYNIGHT_MODE_DAY:
                /* night to day */
                if (m_tAttr.bAutoCtrl && m_pSensorInst) {
                    m_pSensorInst->ChangeDaynightMode(AX_DAYNIGHT_MODE_DAY);
                }

                {
                    SOFT_PHOTOSENSITIVITY_RESULT_T tResult;
                    tResult.eType = SNS_SOFT_PHOTOSENSITIVITY_IR;
                    tResult.eStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_DAY;

                    NotifyAll(m_nSnsId, 0, &tResult);
                }
                break;

            case AX_DAYNIGHT_MODE_NIGHT:
                /* day to night */
                if (m_tAttr.bAutoCtrl && m_pSensorInst) {
                    m_pSensorInst->ChangeDaynightMode(AX_DAYNIGHT_MODE_NIGHT);
                }

                {
                    SOFT_PHOTOSENSITIVITY_RESULT_T tResult;
                    tResult.eType = SNS_SOFT_PHOTOSENSITIVITY_IR;
                    tResult.eStatus = SNS_SOFT_PHOTOSENSITIVITY_STATUS_NIGHT;

                    NotifyAll(m_nSnsId, 0, &tResult);
                }
                break;

            default:
                LOG_MM_N(SPS_MONITOR, "Unkonw dayNightMode [%d]", eDayNightStatus);
                break;
        }

        if (!m_pSensorInst->GetDayNightStatus(eDayNightStatus)) {
            return;
        }

        m_tStatus.curDayNightStatus = eDayNightStatus;
    }
}

AX_S32 CSoftPhotoSensitivity::Monitor(AX_VOID* pArg) {
    if (SNS_SOFT_PHOTOSENSITIVITY_IR == m_tAttr.eType) {
        SetIrAttr(m_tAttr.tIrAttr);
    } else {
        SetWarmLightAttr(m_tAttr.tWarmAttr);
    }

    while (m_SpsThread.IsRunning()) {
        {
            std::unique_lock<std::mutex> lck(m_mtx);
            m_cv.wait_for(lck, std::chrono::milliseconds(SPS_MONITOR_INTERVAL), [this]() -> bool { return !this->m_SpsThread.IsRunning() || this->m_tStatus.bUpdateTrigger; });

            if (!m_SpsThread.IsRunning()) {
                break;
            }

            if (m_tStatus.bUpdateTrigger) {
                m_tStatus.bUpdateTrigger = AX_FALSE;

                if (SNS_SOFT_PHOTOSENSITIVITY_IR == m_tAttr.eType) {
                    SetIrAttr(m_tAttr.tIrAttr);
                } else if (SNS_SOFT_PHOTOSENSITIVITY_WARMLIGHT == m_tAttr.eType) {
                    SetWarmLightAttr(m_tAttr.tWarmAttr);
                } else {
                    m_SpsThread.Stop();
                    m_tStatus.bMonitorStart = AX_FALSE;
                    break;
                }
            }
        }

        if (SNS_SOFT_PHOTOSENSITIVITY_WARMLIGHT == m_tAttr.eType) {
            WarmLightMonitor(m_tAttr.tWarmAttr);
        } else if (SNS_SOFT_PHOTOSENSITIVITY_IR == m_tAttr.eType) {
            IrMonitor(m_tAttr.tIrAttr);
        } else {
            LOG_MM_E(SPS_MONITOR, "soft photosensitivity[%d] invalid ", m_tAttr.eType);
            break;
        }
    }

    return 0;
}

AX_VOID CSoftPhotoSensitivity::RegObserver(IObserver *pObserver) {
    if (nullptr != pObserver) {
        OBS_TRANS_ATTR_T tTransAttr;
        tTransAttr.nGroup = m_nSnsId;
        tTransAttr.nChannel = 0;
        tTransAttr.bLink = AX_FALSE;
        tTransAttr.nWidth = 0;
        tTransAttr.nHeight = 0;

        if (pObserver->OnRegisterObserver(E_OBS_TARGET_TYPE_SPS, m_nSnsId, 0, &tTransAttr)) {
            m_vecObserver.emplace_back(pObserver);
        }
    }
}

AX_VOID CSoftPhotoSensitivity::UnregObserver(IObserver *pObserver) {
    if (nullptr == pObserver) {
        return;
    }

    for (std::vector<IObserver *>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        if (*it == pObserver) {
            m_vecObserver.erase(it);
            break;
        }
    }
}

AX_VOID CSoftPhotoSensitivity::NotifyAll(AX_U32 nSnsId, AX_U32 nChn, AX_VOID *ptResult) {
    if (nullptr == ptResult) {
        return;
    }

    for (std::vector<IObserver *>::iterator it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        (*it)->OnRecvData(E_OBS_TARGET_TYPE_SPS, nSnsId, nChn, ptResult);
    }
}
