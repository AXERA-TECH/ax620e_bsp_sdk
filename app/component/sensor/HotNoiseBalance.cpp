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
#include <fcntl.h>

#include "OptionHelper.h"
#include "HotNoiseBalance.h"
#include "ElapsedTimer.hpp"
#include "AppLogApi.h"

#define HNB_MONITOR "HNB"

#define HOT_NOISE_INVALID_HANDLE (-1)
#define HOT_NOISE_THERMAL_NODE_NAME "/sys/class/thermal/thermal_zone0/temp"

#define HNB_MONITOR_INTERVAL                       (5000) // 5s

CHotNoiseBalance::CHotNoiseBalance(CBaseSensor *Sensor) : m_pSensorInst(Sensor) {
    m_nSnsId = m_pSensorInst->GetSnsConfig().nSnsID;
}

AX_BOOL CHotNoiseBalance::Start(const SENSOR_HOTNOISEBALANCE_T& tAttr) {
    if (!m_tStatus.bMonitorStart && m_pSensorInst) {
        m_tAttr = tAttr;

        StartMonitor();
    }

    return AX_TRUE;
}

AX_BOOL CHotNoiseBalance::Stop() {
    LOG_MM_C(HNB_MONITOR, "[%d] +++", m_nSnsId);

    {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_HnbThread.Stop();
        m_cv.notify_one();
    }

    m_HnbThread.Join();

    m_tStatus.bMonitorStart = AX_FALSE;
    m_tStatus.bUpdateTrigger = AX_FALSE;
    m_tStatus.eStatus = HNB_STATUS_NORMAL_E;

    LOG_MM_C(HNB_MONITOR, "[%d] ---", m_nSnsId);

    return AX_TRUE;
}

AX_BOOL CHotNoiseBalance::StartMonitor() {
    if (m_tAttr.bEnable) {
        std::string threadName = "APP_HnbMoni_" + std::to_string(m_nSnsId);
        if (!m_HnbThread.Start([this](AX_VOID* pArg) -> AX_VOID { Monitor(pArg); }, nullptr, threadName.c_str())) {
            return AX_FALSE;
        }

        m_tStatus.bMonitorStart = AX_TRUE;
    }

    return AX_TRUE;
}

AX_BOOL CHotNoiseBalance::Update(const SENSOR_HOTNOISEBALANCE_T& tAttr) {
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

AX_S32 CHotNoiseBalance::Monitor(AX_VOID* pArg) {
    AX_S32 nThermalHandle = HOT_NOISE_INVALID_HANDLE;

    while (m_HnbThread.IsRunning()) {
        {
            std::unique_lock<std::mutex> lck(m_mtx);
            m_cv.wait_for(lck, std::chrono::milliseconds(HNB_MONITOR_INTERVAL), [this]() -> bool { return !this->m_HnbThread.IsRunning() || this->m_tStatus.bUpdateTrigger; });

            if (!m_HnbThread.IsRunning()) {
                break;
            }

            if (m_tStatus.bUpdateTrigger) {
                m_tStatus.bUpdateTrigger = AX_FALSE;

                if (!m_tAttr.bEnable) {
                    m_HnbThread.Stop();
                    m_tStatus.bMonitorStart = AX_FALSE;
                    break;
                }
            }
        }

        if (!m_pSensorInst) {
            continue;
        }

        AX_F32 fTemperature = 0;

        // get sensor temperature
        if (!m_pSensorInst->GetSnsTemperature(fTemperature)) {
            // get temperature from chip
            if (nThermalHandle == HOT_NOISE_INVALID_HANDLE) {
                nThermalHandle = open(HOT_NOISE_THERMAL_NODE_NAME, O_RDONLY);
            }

            if (nThermalHandle != HOT_NOISE_INVALID_HANDLE) {
                AX_CHAR strThermal[50] = {0};

                lseek(nThermalHandle, 0, SEEK_SET);

                if (read(nThermalHandle, strThermal, 50) > 0) {
                    AX_S32 nThermal = atoi(strThermal);
                    fTemperature = (AX_F32)nThermal/1000.0;
                } else {
                    LOG_M_C(HNB_MONITOR, "read %s fail", HOT_NOISE_THERMAL_NODE_NAME);

                    close(nThermalHandle);

                    nThermalHandle = HOT_NOISE_INVALID_HANDLE;
                }
            } else {
                LOG_MM_C(HNB_MONITOR, "open %s fail", HOT_NOISE_THERMAL_NODE_NAME);
            }

            if (COptionHelper::GetInstance()->GetSnsHnbPrintTemperature()) {
                LOG_MM_C(HNB_MONITOR, "real time sensor temperature(C): %.2f", fTemperature);
            }
        } else {
            if (COptionHelper::GetInstance()->GetSnsHnbPrintTemperature()) {
                LOG_MM_C(HNB_MONITOR, "real time sensor temperature(S): %.2f", fTemperature);
            }
        }

        // process
        Process(fTemperature);
    }

    return 0;
}

AX_BOOL CHotNoiseBalance::Process(AX_F32 fThermal) {
    if (!m_pSensorInst) {
        return AX_FALSE;
    }

    if (m_tAttr.bEnable) {
        if (!COptionHelper::GetInstance()->GetSnsHnbTestMode()) {
            if (fThermal >= m_tAttr.fBalanceThreshold) {
                // Escape
                if (m_tStatus.eStatus == HNB_STATUS_NORMAL_E) {
                    LOG_MM_C(HNB_MONITOR, "Thermal: %.2f", fThermal);

                    std::string strBinName;
                    if (IS_SNS_HDR_MODE(m_pSensorInst->GetSnsConfig().eSensorMode)) {
                        strBinName = (AX_CHAR *)m_tAttr.strHdrHotNoiseBalanceModeBin.c_str();
                    } else {
                        strBinName = (AX_CHAR *)m_tAttr.strSdrHotNoiseBalanceModeBin.c_str();
                    }

                    if (m_pSensorInst->LoadBinParams(strBinName)) {
                        std::unique_lock<std::mutex> lck(m_mtx);
                        m_tStatus.eStatus = HNB_STATUS_BALANCE_E;
                    }
                }
            } else if (fThermal <= m_tAttr.fNormalThreshold) {
                // Recovery
                if (m_tStatus.eStatus == HNB_STATUS_BALANCE_E) {
                    LOG_MM_C(HNB_MONITOR, "Thermal: %.2f", fThermal);

                    std::string strBinName;
                    if (IS_SNS_HDR_MODE(m_pSensorInst->GetSnsConfig().eSensorMode)) {
                        strBinName = (AX_CHAR *)m_tAttr.strHdrHotNoiseNormalModeBin.c_str();
                    } else {
                        strBinName = (AX_CHAR *)m_tAttr.strSdrHotNoiseNormalModeBin.c_str();
                    }

                    if (m_pSensorInst->LoadBinParams(strBinName)) {
                        std::unique_lock<std::mutex> lck(m_mtx);
                        m_tStatus.eStatus = HNB_STATUS_NORMAL_E;
                    }
                }
            }
        } else {
            // Escape
            if (m_tStatus.eStatus == HNB_STATUS_NORMAL_E) {
                LOG_MM_C(HNB_MONITOR, "Thermal: %.2f", fThermal);

                std::string strBinName;
                if (IS_SNS_HDR_MODE(m_pSensorInst->GetSnsConfig().eSensorMode)) {
                    strBinName = (AX_CHAR *)m_tAttr.strHdrHotNoiseBalanceModeBin.c_str();
                } else {
                    strBinName = (AX_CHAR *)m_tAttr.strSdrHotNoiseBalanceModeBin.c_str();
                }

                if (m_pSensorInst->LoadBinParams(strBinName)) {
                    std::unique_lock<std::mutex> lck(m_mtx);
                    m_tStatus.eStatus = HNB_STATUS_BALANCE_E;
                }
            } else {
                LOG_MM_C(HNB_MONITOR, "Thermal: %.2f", fThermal);

                std::string strBinName;
                if (IS_SNS_HDR_MODE(m_pSensorInst->GetSnsConfig().eSensorMode)) {
                    strBinName = (AX_CHAR *)m_tAttr.strHdrHotNoiseNormalModeBin.c_str();
                } else {
                    strBinName = (AX_CHAR *)m_tAttr.strSdrHotNoiseNormalModeBin.c_str();
                }

                if (m_pSensorInst->LoadBinParams(strBinName)) {
                    std::unique_lock<std::mutex> lck(m_mtx);
                    m_tStatus.eStatus = HNB_STATUS_NORMAL_E;
                }
            }
        }
    }

    return AX_TRUE;
}
