/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include "BaseSensor.h"
#include <dlfcn.h>
#include <sys/prctl.h>
#include "AppLogApi.h"
#include "CommonUtils.hpp"
#include "ElapsedTimer.hpp"
#include "AXTypeConverter.hpp"
#include "SensorOptionHelper.h"
#include "SoftPhotoSensitivity.h"
#include "HotNoiseBalance.h"
#include "IspAlgoAeRoi.h"

#define SENSOR "SENSOR"
#define SDRKEY "sdr"
#define HDRKEY "hdr"
#define BOARD_ID_LEN 128

#define SENSOR_BRIGHTNESS_LOW 0
#define SENSOR_BRIGHTNESS_MEDIUM 0x100
#define SENSOR_BRIGHTNESS_HIGH 4095

#define SENSOR_CONTRAST_LOW -4096
#define SENSOR_CONTRAST_MEDIUM 0x100
#define SENSOR_CONTRAST_HIGH 4095

#define SENSOR_SATURATION_LOW 0
#define SENSOR_SATURATION_MEDIUM 0x1000
#define SENSOR_SATURATION_HIGH 65535

#define SENSOR_SHARPNESS_LOW 16
#define SENSOR_SHARPNESS_MEDIUM 0x20
#define SENSOR_SHARPNESS_HIGH 255

CBaseSensor::CBaseSensor(SENSOR_CONFIG_T tSensorConfig)
    : m_tSnsCfg(tSensorConfig), m_eImgFormatSDR(AX_FORMAT_BAYER_RAW_10BPP), m_eImgFormatHDR(AX_FORMAT_BAYER_RAW_10BPP) {
}

AX_BOOL CBaseSensor::InitISP(AX_VOID) {
    memset(&m_tSnsAttr, 0, sizeof(AX_SNS_ATTR_T));
    memset(&m_tDevAttr, 0, sizeof(AX_VIN_DEV_ATTR_T));
    memset(&m_tMipiRxDev, 0, sizeof(AX_MIPI_RX_DEV_T));

    InitMipiRxAttr();
    InitSnsAttr();
    InitSnsClkAttr();
    InitDevAttr();
    InitPipeAttr();
    InitChnAttr();
    InitSnsLibraryInfo();
    InitAbilities();

    if (m_cbAttrUpd) {
        m_cbAttrUpd(this);
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::Init() {
    if (!InitISP()) {
        LOG_M_E(SENSOR, "Sensor %d init failed.", m_tSnsCfg.nSnsID);
        return AX_FALSE;
    }

#ifndef USE_STATIC_LIBS
    if (!m_pSnsLib) {
        AX_DLOPEN(m_pSnsLib, m_tSnsLibInfo.strLibName.c_str());
    }

    if (!m_pSnsLib) {
        LOG_M_E(SENSOR, "Load %s fail, %s", m_tSnsLibInfo.strLibName.c_str(), strerror(errno));
        return AX_FALSE;
    }

    AX_DLVAR_LOAD(m_pSnsObj, m_pSnsLib, m_tSnsLibInfo.strObjName.c_str(), AX_SENSOR_REGISTER_FUNC_T);

    if (!m_pSnsObj) {
        LOG_M_E(SENSOR, "Find symbol(%s) fail, %s", m_tSnsLibInfo.strObjName.c_str(), strerror(errno));
        return AX_FALSE;
    }
#endif

    if (!m_pSps) {
        m_pSps = new CSoftPhotoSensitivity(this);
    }

    if (!m_pHnb) {
        m_pHnb = new CHotNoiseBalance(this);
    }

    if (!m_pAeRoi) {
        m_pAeRoi = new CIspAlgoAeRoi(this);
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::DeInit() {
    LOG_MM_C(SENSOR, "[Dev:%d] +++", m_tSnsCfg.nDevID);

    memset(&m_tSnsAttr, 0, sizeof(AX_SNS_ATTR_T));
    memset(&m_tDevAttr, 0, sizeof(AX_VIN_DEV_ATTR_T));
    memset(&m_tMipiRxDev, 0, sizeof(AX_MIPI_RX_DEV_T));

    m_cbAttrUpd = nullptr;

#ifndef USE_STATIC_LIBS
    AX_DLCLOSE(m_pSnsLib);
#endif

    m_pSnsObj = nullptr;

    SAFE_DELETE_PTR(m_pSps);

    SAFE_DELETE_PTR(m_pHnb);

    SAFE_DELETE_PTR(m_pAeRoi);

    LOG_MM_C(SENSOR, "[Dev:%d] ---", m_tSnsCfg.nDevID);
    return AX_TRUE;
}

AX_BOOL CBaseSensor::Open() {
    if (!OpenAll()) {
        return AX_FALSE;
    }

    if (!RestoreSnsAttr()) {
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::Close() {
    if (!CloseAll()) {
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::OpenAll() {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    LOG_MM_C(SENSOR, "[Dev:%d] +++", m_tSnsCfg.nDevID);

    LOG_MM(SENSOR, "Sensor Attr => w:%d h:%d framerate:%.2f sensor mode:%d rawType:%d", m_tSnsAttr.nWidth, m_tSnsAttr.nHeight,
           m_tSnsAttr.fFrameRate, m_tSnsAttr.eSnsMode, m_tSnsAttr.eRawType);

    AX_S32 nRet = 0;
    AX_U8 nDevID = m_tSnsCfg.nDevID;

    // SNS reset sensor obj
    for (auto &m : m_mapPipe2Attr) {
        AX_U8 nPipeID = m.first;
        if ((AX_U8)(-1) != m_tSnsCfg.nResetGpioNum) {
            if (!ResetSensorObj(nPipeID, m_tSnsCfg.nResetGpioNum)) {
                LOG_M_E(SENSOR, "ResetSensorObj failed, ret=0x%x.", nRet);
                return AX_FALSE;
            }
        }
    }

    // step 1: AX_MIPI_RX_SetLaneCombo
    if (m_tMipiRxDev.eInputMode == AX_INPUT_MODE_MIPI && m_tMipiRxDev.tMipiAttr.eLaneNum == AX_MIPI_DATA_LANE_4)
        nRet = AX_MIPI_RX_SetLaneCombo(AX_LANE_COMBO_MODE_0);
    else
        nRet = AX_MIPI_RX_SetLaneCombo(AX_LANE_COMBO_MODE_1);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "AX_MIPI_RX_SetLaneCombo failed, ret=0x%x.", nRet);
        return AX_FALSE;
    }

    // step 2: AX_MIPI_RX_SetAttr
    nRet = AX_MIPI_RX_SetAttr(nDevID, &m_tMipiRxDev);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_MIPI_RX_SetAttr failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    }

    // step 3: AX_MIPI_RX_Reset
    nRet = AX_MIPI_RX_Reset(nDevID);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_MIPI_RX_Reset failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    }

    // step 4: AX_MIPI_RX_Start
    nRet = AX_MIPI_RX_Start(nDevID);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_MIPI_RX_Start failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    } else {
        LOG_M_C(SENSOR, "[%d] AX_MIPI_RX_Start", nDevID);
    }

    // step 5: AX_VIN_CreateDev
    nRet = AX_VIN_CreateDev(nDevID, &m_tDevAttr);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_VIN_CreateDev failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    } else {
        LOG_M_C(SENSOR, "[%d] AX_VIN_CreateDev", nDevID);
    }

    // step 6: AX_VIN_SetDevAttr
    nRet = AX_VIN_SetDevAttr(nDevID, &m_tDevAttr);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_VIN_SetDevAttr failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    }

    // if (AX_VIN_DEV_OFFLINE == m_tDevAttr.eDevMode) {
    //     AX_VIN_DUMP_ATTR_T tDumpAttr;
    //     tDumpAttr.bEnable = AX_TRUE;
    //     tDumpAttr.nDepth = 3;
    //     nRet = AX_VIN_SetDevDumpAttr(nDevID, AX_VIN_DUMP_QUEUE_TYPE_DEV, &tDumpAttr);
    //     if (0 != nRet) {
    //         LOG_M_E(SENSOR, "AX_VIN_SetDevDumpAttr failed, ret=0x%x.", nRet);
    //         return AX_FALSE;
    //     }
    // }

    AX_VIN_DEV_BIND_PIPE_T tDevBindPipe = {0};
    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        tDevBindPipe.nPipeId[i] = nPipeID;
        tDevBindPipe.nNum += 1;

        switch (m_tSnsAttr.eSnsMode) {
            case AX_SNS_LINEAR_MODE:
                tDevBindPipe.nHDRSel[i] = 0x1;
                break;
            case AX_SNS_HDR_2X_MODE:
                tDevBindPipe.nHDRSel[i] = 0x1 | 0x2;
                break;
            case AX_SNS_HDR_3X_MODE:
                tDevBindPipe.nHDRSel[i] = 0x1 | 0x2 | 0x4;
                break;
            case AX_SNS_HDR_4X_MODE:
                tDevBindPipe.nHDRSel[i] = 0x1 | 0x2 | 0x4 | 0x8;
                break;
            default:
                tDevBindPipe.nHDRSel[i] = 0x1;
                break;
        }
    }

    // step 7: AX_VIN_SetDevBindPipe
    nRet = AX_VIN_SetDevBindPipe(nDevID, &tDevBindPipe);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "AX_VIN_SetDevBindPipe failed, ret=0x%x.", nRet);
        return AX_FALSE;
    }

    for (auto &m : m_mapPipe2Attr) {
        AX_U8 nPipeID = m.first;
        AX_VIN_PIPE_ATTR_T &tPipeAttr = m.second;

        // step 8: AX_VIN_CreatePipe
        nRet = AX_VIN_CreatePipe(nPipeID, &tPipeAttr);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_VIN_CreatePipe failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_VIN_CreatePipe", nPipeID);
        }

        // step 9: AX_VIN_SetPipeAttr
        AX_VIN_PIPE_ATTR_T tPipeAttr2 = tPipeAttr;
        nRet = AX_VIN_SetPipeAttr(nPipeID, &tPipeAttr2);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_VIN_SetPipeAttr failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        }

        // step 10: AX_VIN_SetPipeFrameSource
        if (tPipeAttr.ePipeWorkMode == AX_VIN_PIPE_NORMAL_MODE1) {
            nRet = AX_VIN_SetPipeFrameSource(nPipeID, AX_VIN_FRAME_SOURCE_ID_IFE, AX_VIN_FRAME_SOURCE_TYPE_DEV);

            if (0 != nRet) {
                LOG_M_E(SENSOR, "[%d] AX_VIN_SetPipeFrameSource failed, ret=0x%x.", nPipeID, nRet);
                return AX_FALSE;
            }

            // AX_VIN_DUMP_ATTR_T tPipeDumpAttr;
            // memset(&tPipeDumpAttr, 0, sizeof(tPipeDumpAttr));

            // tPipeDumpAttr.bEnable = AX_TRUE;
            // tPipeDumpAttr.nDepth = 3;
            // nRet = AX_VIN_SetPipeDumpAttr(nPipeID, AX_VIN_PIPE_DUMP_NODE_IFE, AX_VIN_DUMP_QUEUE_TYPE_DEV, &tPipeDumpAttr);
            // if (nRet) {
            //     LOG_M_E(SENSOR, "pipe %d node %d dump attr set failed....\n", nPipeID, AX_VIN_PIPE_DUMP_NODE_IFE);
            // }

            // nRet = AX_VIN_SetPipeFrameSource(nPipeID, AX_VIN_FRAME_SOURCE_ID_ITP, AX_VIN_FRAME_SOURCE_TYPE_USER);
            // if (nRet) {
            //     LOG_M_E(SENSOR, "pipe %d src %d  frame source set failed....\n", nPipeID, AX_VIN_FRAME_SOURCE_ID_ITP);
            // }
            // tPipeDumpAttr.bEnable = AX_TRUE;
            // tPipeDumpAttr.nDepth = 3;
            // nRet = AX_VIN_SetPipeDumpAttr(nPipeID, AX_VIN_PIPE_DUMP_NODE_MAIN, AX_VIN_DUMP_QUEUE_TYPE_DEV, &tPipeDumpAttr);
            // if (nRet) {
            //     LOG_M_E(SENSOR, "pipe %d src %d  dump attr set failed....\n", nPipeID, AX_VIN_PIPE_DUMP_NODE_MAIN);
            // }
        }
    }

    // step 11: RegisterSensor
    for (auto &m : m_mapPipe2Attr) {
        AX_U8 nPipeID = m.first;
        if (!RegisterSensor(nPipeID, m_tSnsCfg.nBusType, m_tSnsCfg.nDevNode, m_tSnsCfg.nI2cAddr)) {
            LOG_M_E(SENSOR, "RegisterSensor failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }
    }

    for (auto &m : m_mapPipe2Attr) {
        AX_U8 nPipeID = m.first;
        /* Todo: SDR=4 ; HDR=5*/
        m_tSnsAttr.nSettingIndex = m_tSnsCfg.arrSettingIndex[m_tSnsCfg.eSensorMode];

        // step 12: SetSnsAttr
        if (!SetSnsAttr(nPipeID, m_tSnsAttr)) {
            return AX_FALSE;
        }

        // step 13: AX_ISP_OpenSnsClk
        nRet = AX_ISP_OpenSnsClk(m_tSnsClkAttr.nSnsClkIdx, m_tSnsClkAttr.eSnsClkRate);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_OpenSnsClk[%d] failed, ret=0x%x.", nPipeID, m_tSnsClkAttr.nSnsClkIdx, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_OpenSnsClk[%d]", nPipeID, m_tSnsClkAttr.nSnsClkIdx);
        }

        // step 14: AX_ISP_ResetSensor
        AX_U32 nResetGpio = m_tSnsCfg.nResetGpioNum;  // COMMON_HW_GetSensorResetGpioNum(nDevID)
        nRet = AX_ISP_ResetSensor(nPipeID, nResetGpio);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "AX_ISP_ResetSensor failed, ret=0x%x.\n", nRet);
            return AX_FALSE;
        }
    }

    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;
        vector<string> vecPipeTuningBin = GetSnsConfig().arrPipeAttr[i].vecTuningBin;

        // step 15: AX_ISP_Create
        nRet = AX_ISP_Create(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_Create failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_Create", nPipeID);
        }

        // step 16: RegisterAlgo Callback
        if (!m_algWrapper.RegisterAlgoToSensor(m_pSnsObj, nPipeID)) {
            LOG_M_E(SENSOR, "RegisterAlgoToSensor failed.");
            return AX_FALSE;
        }

        // step 17: AX_ISP_LoadBinParams
        for (AX_U8 j = 0; j < vecPipeTuningBin.size(); j++) {
            std::string strKey = m_tSnsCfg.eSensorMode == AX_SNS_LINEAR_MODE ? SDRKEY : HDRKEY;
            if (!vecPipeTuningBin[j].empty()) {
                LOG_MM_I(SENSOR, "Try load %s",vecPipeTuningBin[j].c_str());
                if (0 != access(vecPipeTuningBin[j].data(), F_OK)) {
                    LOG_MM_E(SENSOR, "%s is not exist.",vecPipeTuningBin[j].data());
                    continue;
                }

                if (std::string::npos == vecPipeTuningBin[j].find(strKey)) {
                    LOG_MM_W(SENSOR, "hdrMode and bin do not match");
                    continue;
                }

                nRet = AX_ISP_LoadBinParams(nPipeID, vecPipeTuningBin[j].c_str());
                if (AX_SUCCESS != nRet) {
                    LOG_M_E(SENSOR, "pipe[%d], %d tuning bin , AX_ISP_LoadBinParams ret=0x%x %s. The parameters in sensor.h will be used\n",
                            i, j, nRet, vecPipeTuningBin[j].c_str());
                }
            }
        }

        // step 18: AX_ISP_Open
        nRet = AX_ISP_Open(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_Open failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_Open", nPipeID);
        }
    }

    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        for (AX_U8 j = AX_VIN_CHN_ID_MAIN; j < AX_VIN_CHN_ID_MAX; j++) {
            AX_VIN_CHN_ATTR_T &tChnAttr = m_mapPipe2ChnAttr[nPipeID][j];

            AX_VIN_CHN_ATTR_T tChnAttr2 = tChnAttr;
            // step 19: AX_VIN_SetChnAttr
            nRet = AX_VIN_SetChnAttr(nPipeID, (AX_VIN_CHN_ID_E)j, &tChnAttr2);
            if (0 != nRet) {
                LOG_M_E(SENSOR, "[%d] AX_VIN_SetChnAttr failed, ret=0x%x.", nPipeID, nRet);
                return AX_FALSE;
            }

            if (m_tSnsCfg.bMirror) {
                nRet = AX_VIN_SetPipeMirror(nPipeID, AX_TRUE);
                if (0 != nRet) {
                    LOG_M_E(SENSOR, "[%d] AX_VIN_SetPipeMirror failed, ret=0x%x.", nPipeID, nRet);
                    return AX_FALSE;
                }
            }

            if (m_tSnsCfg.arrPipeAttr[i].arrChannelAttr[j].bChnEnable) {
                if (m_tSnsCfg.bFlip) {
                    nRet = AX_VIN_SetChnFlip(nPipeID, (AX_VIN_CHN_ID_E)j, AX_TRUE);
                    if (0 != nRet) {
                        LOG_M_E(SENSOR, "[%d] AX_VIN_SetChnFlip failed, ret=0x%x.", nPipeID, nRet);
                        return AX_FALSE;
                    }
                }

                // step 20: AX_VIN_EnableChn
                LOG_M_I(SENSOR, "AX_VIN_EnableChn [%d] ...", j);
                nRet = AX_VIN_EnableChn(nPipeID, (AX_VIN_CHN_ID_E)j);
                if (0 != nRet) {
                    LOG_M_E(SENSOR, "[%d] AX_VIN_EnableChn[%d] failed, ret=0x%x.", nPipeID, j, nRet);
                    return AX_FALSE;
                } else {
                    LOG_M_C(SENSOR, "[%d] AX_VIN_EnableChn[%d]", nPipeID, j);
                }
            }
        }
    }

    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        // step 21: AX_VIN_StartPipe
        nRet = AX_VIN_StartPipe(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "AX_VIN_StartPipe failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }

        // step 22: AX_ISP_Start
        nRet = AX_ISP_Start(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_Start failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_Start", nPipeID);
        }
    }

    // step 23: AX_VIN_EnableDev
    nRet = AX_VIN_EnableDev(nDevID);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_VIN_EnableDev failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    } else {
        LOG_M_C(SENSOR, "[%d] AX_VIN_EnableDev", nDevID);
    }

    if (IsSnsSync()) {
        SetMultiSnsSync(AX_TRUE);
    }

    // step 24: AX_ISP_StreamOn
    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;
        nRet = AX_ISP_StreamOn(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_StreamOn failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_StreamOn", nPipeID);
        }
    }

    m_bSensorStarted = AX_TRUE;

    // get shutter mode
    m_tSnsCfg.eShutterMode = GetShutterMode();

    LOG_MM_C(SENSOR, "[Dev:%d] ---", m_tSnsCfg.nDevID);
    return AX_TRUE;
}

AX_BOOL CBaseSensor::CloseAll() {
    LOG_MM_C(SENSOR, "[Dev:%d] +++", m_tSnsCfg.nDevID);
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    AX_S32 nRet = AX_SUCCESS;

    m_bSensorStarted = AX_FALSE;

    // stop sensor soft photo sensitivity
    if (m_pSps) {
        m_pSps->Stop();
    }

    // stop hot noise balance
    if (m_pHnb) {
        m_pHnb->Stop();
    }

    // stop ae roi
    if (m_pAeRoi) {
        m_pAeRoi->Stop();
    }

    // step 1: AX_ISP_Stop
    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;
        nRet = AX_ISP_Stop(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_Stop failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_Stop", nPipeID);
        }
    }

    // step 2: AX_VIN_DisableDev
    AX_U8 nDevID = m_tSnsCfg.nDevID;
    nRet = AX_VIN_DisableDev(nDevID);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_VIN_DisableDev failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    } else {
        LOG_M_C(SENSOR, "[%d] AX_VIN_DisableDev", nDevID);
    }

    // if (AX_VIN_DEV_OFFLINE == m_tSnsCfg.eDevMode) {
    //     AX_VIN_DUMP_ATTR_T tDumpAttr;
    //     tDumpAttr.bEnable = AX_FALSE;
    //     nRet = AX_VIN_SetDevDumpAttr(nDevID, AX_VIN_DUMP_QUEUE_TYPE_DEV, &tDumpAttr);
    //     if (0 != nRet) {
    //         LOG_M_E(SENSOR, "AX_VIN_SetDevDumpAttr failed, ret=0x%x.", nRet);
    //         return AX_FALSE;
    //     }
    // }

    // step 3: AX_ISP_StreamOff
    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;
        nRet = AX_ISP_StreamOff(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_StreamOff failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_StreamOff", nPipeID);
        }
    }

    // step 4: AX_ISP_CloseSnsClk
    nRet = AX_ISP_CloseSnsClk(m_tSnsClkAttr.nSnsClkIdx);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "AX_ISP_CloseSnsClk[%d] failed, ret=0x%x.", m_tSnsClkAttr.nSnsClkIdx, nRet);
        return AX_FALSE;
    } else {
        LOG_M_C(SENSOR, "AX_ISP_CloseSnsClk[%d]", m_tSnsClkAttr.nSnsClkIdx);
    }

    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        // step 5: AX_VIN_StopPipe
        nRet = AX_VIN_StopPipe(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_VIN_StopPipe failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_VIN_StopPipe", nPipeID);
        }

        // step 6: AX_VIN_DisableChn
        for (AX_U8 j = AX_VIN_CHN_ID_MAIN; j < AX_VIN_CHN_ID_MAX; j++) {
            if (m_tSnsCfg.arrPipeAttr[i].arrChannelAttr[j].bChnEnable) {
                nRet = AX_VIN_DisableChn(nPipeID, (AX_VIN_CHN_ID_E)j);
                if (0 != nRet) {
                    LOG_M_E(SENSOR, "[%d] AX_VIN_DisableChn[%d] failed, ret=0x%x.", nPipeID, j, nRet);
                    return AX_FALSE;
                } else {
                    LOG_M_C(SENSOR, "[%d] AX_VIN_DisableChn[%d]", nPipeID, j);
                }
            }
        }

        // step 6: AX_ISP_Close
        nRet = AX_ISP_Close(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_Close failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_Close", nPipeID);
        }

        // step 7: UnRegister Algo
        if (!m_algWrapper.UnRegisterAlgoFromSensor(nPipeID)) {
            LOG_M_E(SENSOR, "UnRegisterAlgoFromSensor failed.");
            return AX_FALSE;
        }

        // step 8: AX_ISP_Destroy
        nRet = AX_ISP_Destroy(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_ISP_Destroy failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_ISP_Destroy", nPipeID);
        }

        // step 9: UnRegisterSensor
        if (!UnRegisterSensor(nPipeID)) {
            LOG_M_E(SENSOR, "UnRegisterSensor failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }

        // step 10: AX_VIN_DestroyPipe
        nRet = AX_VIN_DestroyPipe(nPipeID);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d] AX_VIN_DestroyPipe failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        } else {
            LOG_M_C(SENSOR, "[%d] AX_VIN_DestroyPipe", nPipeID);
        }
    }

    // step 11: AX_VIN_DestroyPipe
    nRet = AX_MIPI_RX_Stop(nDevID);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_MIPI_RX_Stop failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    } else {
        LOG_M_C(SENSOR, "[%d] AX_MIPI_RX_Stop", nDevID);
    }

    // step 12: AX_VIN_DestroyPipe
    nRet = AX_VIN_DestroyDev(nDevID);
    if (0 != nRet) {
        LOG_M_E(SENSOR, "[%d] AX_VIN_DestroyDev failed, ret=0x%x.", nDevID, nRet);
        return AX_FALSE;
    } else {
        LOG_M_C(SENSOR, "[%d] AX_VIN_DestroyDev", nDevID);
    }

    LOG_MM_C(SENSOR, "[Dev:%d] ---", m_tSnsCfg.nDevID);
    return AX_TRUE;
}

AX_BOOL CBaseSensor::RestoreSnsAttr() {
    // scene mode
    UpdateSceneMode();

    // ldc
    if (m_tSnsCfg.arrPipeAttr[0].tLdcAttr.bLdcEnable) {
        UpdateLDC(m_tSnsCfg.arrPipeAttr[0].tLdcAttr.bLdcEnable,
                    m_tSnsCfg.arrPipeAttr[0].tLdcAttr.bLdcAspect,
                    m_tSnsCfg.arrPipeAttr[0].tLdcAttr.nLdcXRatio,
                    m_tSnsCfg.arrPipeAttr[0].tLdcAttr.nLdcYRatio,
                    m_tSnsCfg.arrPipeAttr[0].tLdcAttr.nLdcXYRatio,
                    m_tSnsCfg.arrPipeAttr[0].tLdcAttr.nLdcDistortionRatio);
    }

    // DIS
    if (m_tSnsCfg.arrPipeAttr[0].tDisAttr.bDisEnable) {
        UpdateDIS(m_tSnsCfg.arrPipeAttr[0].tDisAttr.bDisEnable);
    }

    {
        // rotation
        if (m_tSnsCfg.eRotation != AX_ROTATION_0) {
            UpdateRotation((AX_VIN_ROTATION_E)m_tSnsCfg.eRotation);
        } else {
            // zoom
            {
                if (m_tSnsCfg.tEZoomAttr.nEZoomRatio != 0) {
                    EZoom(m_tSnsCfg.tEZoomAttr.nEZoomRatio, m_tSnsCfg.tEZoomAttr.nCenterOffsetX, m_tSnsCfg.tEZoomAttr.nCenterOffsetY);
                }
            }
        }
    }

    // fps
    // fps.2: update initial fps
    {
        if (m_tSnsCfg.fFrameRate != m_tSnsAttr.fFrameRate
            || m_tSnsAttr.fFrameRate < m_tAbilities.fShutterSlowFpsThr) {
            m_tSnsAttr.fFrameRate = m_tSnsCfg.fFrameRate;

            UpdateSnsAttr();
        }
    }

    // day night
    {
        if (m_tSnsCfg.eDayNight == AX_DAYNIGHT_MODE_NIGHT) {
            ChangeDaynightMode(m_tSnsCfg.eDayNight);
        }
    }

    // color
    {
        if (m_tSnsCfg.tColorAttr.bColorManual) {
            APP_ISP_IMAGE_ATTR_T tAttr;

            tAttr.nAutoMode = m_tSnsCfg.tColorAttr.bColorManual ? 0 : 1;
            tAttr.nBrightness = (AX_U8)m_tSnsCfg.tColorAttr.fBrightness;
            tAttr.nSharpness = (AX_U8)m_tSnsCfg.tColorAttr.fSharpness;
            tAttr.nContrast = (AX_U8)m_tSnsCfg.tColorAttr.fContrast;
            tAttr.nSaturation = (AX_U8)m_tSnsCfg.tColorAttr.fSaturation;

            SetIspImageAttr(tAttr);
        }
    }

    // start sensor soft photo sensitivity
    if (m_pSps) {
        m_pSps->Start(m_tSnsCfg.tSoftPhotoSensitivityAttr);
    }

    // start hot noise balance
    if (m_pHnb) {
        m_pHnb->Start(m_tSnsCfg.tHotNoiseBalanceAttr);
    }

    // ae roi
    if (m_tSnsCfg.tAeRoiAttr.bEnable) {
        SetAeRoiAttr(m_tSnsCfg.tAeRoiAttr.bEnable);
    }

    // start ae roi
    if (m_pAeRoi) {
        m_pAeRoi->Start(m_tSnsCfg.tAeRoiAttr);
    }

    return AX_TRUE;
}

const AX_SNS_ATTR_T &CBaseSensor::GetSnsAttr(AX_VOID) const {
    return m_tSnsAttr;
}

AX_VOID CBaseSensor::SetSnsAttr(const AX_SNS_ATTR_T &tSnsAttr) {
    // fps.3: update fps
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    // restore shutter mode
    if (m_tSnsAttr.fFrameRate < m_tAbilities.fShutterSlowFpsThr
        && tSnsAttr.fFrameRate >= m_tAbilities.fShutterSlowFpsThr
        && m_tSnsCfg.eShutterMode == E_SNS_SHUTTER_SLOW_SHUTTER_MODE_E) {
        SNS_SHUTTER_MODE_E eShutterMode = GetShutterMode();

        if (eShutterMode != E_SNS_SHUTTER_SLOW_SHUTTER_MODE_E) {
            SetShutterMode(E_SNS_SHUTTER_SLOW_SHUTTER_MODE_E);
        }
    }

    m_tSnsAttr = tSnsAttr;
    m_tSnsCfg.fFrameRate = tSnsAttr.fFrameRate;

    UpdateSnsAttr();
}

const SNS_CLK_ATTR_T &CBaseSensor::GetSnsClkAttr(AX_VOID) const {
    return m_tSnsClkAttr;
}

AX_VOID CBaseSensor::SetSnsClkAttr(const SNS_CLK_ATTR_T &tClkAttr) {
    m_tSnsClkAttr = tClkAttr;
}

const AX_VIN_DEV_ATTR_T &CBaseSensor::GetDevAttr(AX_VOID) const {
    return m_tDevAttr;
}

AX_VOID CBaseSensor::SetDevAttr(const AX_VIN_DEV_ATTR_T &tDevAttr) {
    m_tDevAttr = tDevAttr;
}

const AX_MIPI_RX_DEV_T &CBaseSensor::GetMipiRxAttr(AX_VOID) const {
    return m_tMipiRxDev;
}

AX_VOID CBaseSensor::SetMipiRxAttr(const AX_MIPI_RX_DEV_T &tMipiRxAttr) {
    m_tMipiRxDev = tMipiRxAttr;
}

const AX_VIN_PIPE_ATTR_T &CBaseSensor::GetPipeAttr(AX_U8 nPipe) const {
    std::map<AX_U8, AX_VIN_PIPE_ATTR_T>::const_iterator itFinder = m_mapPipe2Attr.find(nPipe);
    if (itFinder == m_mapPipe2Attr.end()) {
        LOG_MM_E(SENSOR, "[Dev:%d] Pipe %d not configured.", m_tSnsCfg.nDevID, nPipe);
    }

    return itFinder->second;
}

AX_VOID CBaseSensor::SetPipeAttr(AX_U8 nPipe, const AX_VIN_PIPE_ATTR_T &tPipeAttr) {
    m_mapPipe2Attr[nPipe] = tPipeAttr;
}

const AX_VIN_CHN_ATTR_T &CBaseSensor::GetChnAttr(AX_U8 nPipe, AX_U8 nChannel) const {
    std::map<AX_U8, std::map<AX_U8, AX_VIN_CHN_ATTR_T>>::const_iterator itFinder = m_mapPipe2ChnAttr.find(nPipe);
    if (itFinder == m_mapPipe2ChnAttr.end()) {
        LOG_MM_E(SENSOR, "[Dev:%d] Pipe %d not configured.", m_tSnsCfg.nDevID, nPipe);
    }

    return itFinder->second.find(nChannel)->second;
}

AX_VOID CBaseSensor::SetChnAttr(AX_U8 nPipe, AX_U8 nChannel, const AX_VIN_CHN_ATTR_T &tChnAttr) {
    m_mapPipe2ChnAttr[nPipe][nChannel] = tChnAttr;
}

const SNS_ABILITY_T &CBaseSensor::GetAbilities(AX_VOID) const {
    return m_tAbilities;
}

const SENSOR_CONFIG_T &CBaseSensor::GetSnsConfig(AX_VOID) const {
    return m_tSnsCfg;
}

AX_U32 CBaseSensor::GetPipeCount() {
    return m_mapPipe2Attr.size();
}

AX_VOID CBaseSensor::RegisterIspAlgo(const ISP_ALGO_INFO_T &tAlg) {
    m_algWrapper.SetupAlgoInfo(tAlg);
}

AX_BOOL CBaseSensor::RegisterSensor(AX_U8 nPipe, AX_U8 nBusType, AX_U8 nDevNode, AX_U8 nI2cAddr)  {
    AX_S32 ret;
    AX_SNS_COMMBUS_T tSnsBusInfo;
    memset(&tSnsBusInfo, 0, sizeof(tSnsBusInfo));

    ret = AX_ISP_RegisterSensor(nPipe, m_pSnsObj);
    if (ret) {
        LOG_M_E(SENSOR, "AX_ISP_RegisterSensor(pipe: %d), ret = 0x%08X", nPipe, ret);
        goto __FAIL0__;
    }

    if (ISP_SNS_CONNECT_I2C_TYPE == nBusType) {
        tSnsBusInfo.I2cDev = nDevNode;
    } else {
        tSnsBusInfo.SpiDev.bit4SpiDev = nDevNode;
        tSnsBusInfo.SpiDev.bit4SpiCs = 0;
    }

    if (m_pSnsObj->pfn_sensor_set_bus_info) {
        ret = m_pSnsObj->pfn_sensor_set_bus_info(nPipe, tSnsBusInfo);
        if (0 != ret) {
            LOG_M_E(SENSOR, "Sensor set bus info fail, ret = 0x%08X.", ret);
            goto __FAIL1__;
        } else {
            LOG_M_I(SENSOR, "set sensor bus idx %d", tSnsBusInfo.I2cDev);
        }
    } else {
        LOG_M_E(SENSOR, "sensor set buf info is not supported!");
        goto __FAIL1__;
    }

    if (NULL != m_pSnsObj->pfn_sensor_set_slaveaddr && (AX_U8)(-1) != nI2cAddr) {
        ret = m_pSnsObj->pfn_sensor_set_slaveaddr(nPipe, nI2cAddr);
        if (0 != ret) {
            LOG_M_E(SENSOR, "set sensor slave addr failed with %#x!\n", ret);
            goto __FAIL1__;
        }
        LOG_M_I(SENSOR, "set sensor slave addr %d\n", nI2cAddr);
    }

    return AX_TRUE;

__FAIL1__:
    AX_ISP_UnRegisterSensor(nPipe);

__FAIL0__:
    return AX_FALSE;
}

AX_BOOL CBaseSensor::UnRegisterSensor(AX_U8 nPipe) {
    AX_S32 ret = AX_ISP_UnRegisterSensor(nPipe);
    if (0 != ret) {
        LOG_M_E(SENSOR, "AX_ISP_UnRegisterSensor(pipe: %d) fail, ret = 0x%08X", nPipe, ret);
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::ResetSensorObj(AX_U8 nPipe, AX_U8 nResetGpio) {
    AX_BOOL ret = AX_TRUE;

    if (m_pSnsObj && m_pSnsObj->pfn_sensor_reset) {
        if (0 != m_pSnsObj->pfn_sensor_reset(nPipe, nResetGpio)) {
            LOG_M_E(SENSOR, "sensor reset fail, ret = 0x%08X.", ret);
            ret = AX_FALSE;
            goto __FAIL__;
        }
    } else {
        LOG_M_E(SENSOR, "sensor reset is not supported!");
        ret = AX_FALSE;
        goto __FAIL__;
    }

    return AX_TRUE;

__FAIL__:
    return ret;
}

AX_VOID CBaseSensor::InitSensor(AX_U8 nPipe) {
    if (m_pSnsObj && m_pSnsObj->pfn_sensor_init) {
        m_pSnsObj->pfn_sensor_init(nPipe);
    }

    m_algWrapper.RegisterAlgoToSensor(m_pSnsObj, nPipe);
}

AX_VOID CBaseSensor::ExitSensor(AX_U8 nPipe) {
    m_algWrapper.UnRegisterAlgoFromSensor(nPipe);

    if (m_pSnsObj && m_pSnsObj->pfn_sensor_exit) {
        m_pSnsObj->pfn_sensor_exit(nPipe);
    }
}

AX_VOID CBaseSensor::RegAttrUpdCallback(SensorAttrUpdCallback callback) {
    if (nullptr == callback) {
        return;
    }

    m_cbAttrUpd = callback;
}

AX_IMG_FORMAT_E CBaseSensor::GetMaxImgFmt() {
    return m_eImgFormatSDR >= m_eImgFormatHDR ? m_eImgFormatSDR : m_eImgFormatHDR;
}

AX_SNS_HDR_MODE_E CBaseSensor::GetMaxHdrMode() {
    if (!GetAbilities().bSupportHDR) {
        return AX_SNS_LINEAR_MODE;
    }

    return AX_SNS_HDR_4X_MODE;
}


AX_BOOL CBaseSensor::ChangeDaynightMode(AX_DAYNIGHT_MODE_E eDaynightMode) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U8 i = 0; i < tSnsCfg.nPipeCount; i++) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_U8 nPipId = tSnsCfg.arrPipeAttr[i].nPipeID;

        for (AX_U8 j = 0; j < AX_VIN_CHN_ID_MAX; j++) {
            if (!tSnsCfg.arrPipeAttr[i].arrChannelAttr[j].bChnEnable) {
                continue;
            }

            AX_S32 nRet = AX_VIN_SetChnDayNightMode(nPipId, (AX_VIN_CHN_ID_E)j, eDaynightMode);
            if (0 != nRet) {
                LOG_M_E(SENSOR, "[%d][%d] AX_VIN_SetChnDayNightMode failed, ret=0x%x.", nPipId, j, nRet);
                return AX_FALSE;
            } else {
                LOG_M_W(SENSOR, "[%d][%d] AX_VIN_SetChnDayNightMode OK.", nPipId, j);
            }
        }
    }

    m_tSnsCfg.eDayNight = eDaynightMode;

    return AX_TRUE;
}

AX_VOID CBaseSensor::ChangeHdrMode(AX_U32 nSnsMode) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    m_tSnsCfg.eSensorMode = (AX_SNS_HDR_MODE_E)nSnsMode;
    return;
}

AX_BOOL CBaseSensor::ChangeSnsMirrorFlip(AX_BOOL bMirror, AX_BOOL bFlip) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    LOG_M_W(SENSOR, "SNS[%d] change mirror=%d, flip=%d.", m_tSnsCfg.nSnsID, bMirror, bFlip);
    AX_S32 nRet = 0;
    AX_BOOL bSucces = AX_TRUE;
    for (auto &m : m_mapPipe2Attr) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_U8 nPipeID = m.first;
        AX_BOOL bValue = AX_FALSE;
        nRet = AX_VIN_GetPipeMirror(nPipeID, &bValue);
        if (nRet == 0 && bMirror != bValue) {
            LOG_M_W(SENSOR, "SNS[%d] change pipe[%d] mirror=%d.", m_tSnsCfg.nSnsID, nPipeID, bMirror);
            nRet = AX_VIN_SetPipeMirror(nPipeID, bMirror);
        } else if (nRet != 0) {
            LOG_M_E(SENSOR, "AX_VIN_GetPipeMirror failed, ret=0x%x.", nRet);
            LOG_M_W(SENSOR, "SNS[%d] change pipe[%d] mirror=%d.", m_tSnsCfg.nSnsID, nPipeID, bMirror);
            nRet = AX_VIN_SetPipeMirror(nPipeID, bMirror);
        }
        if (nRet != 0) {
            bSucces = AX_FALSE;
        }
    }

    for (AX_U8 i = 0; i < GetPipeCount(); i++) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;
        for (AX_U8 j = AX_VIN_CHN_ID_MAIN; j < AX_VIN_CHN_ID_MAX; j++) {
            if (m_tSnsCfg.arrPipeAttr[i].arrChannelAttr[j].bChnEnable) {
                AX_BOOL bValue = AX_FALSE;
                nRet = AX_VIN_GetChnFlip(nPipeID, (AX_VIN_CHN_ID_E)j, &bValue);
                if (nRet == 0 && bFlip != bValue) {
                    LOG_M_W(SENSOR, "SNS[%d] change pipe[%d] chn[%d] flip=%d.", m_tSnsCfg.nSnsID, nPipeID, j, bFlip);
                    nRet = AX_VIN_SetChnFlip(nPipeID, (AX_VIN_CHN_ID_E)j, bFlip);
                } else if (nRet != 0) {
                    LOG_M_E(SENSOR, "AX_VIN_GetChnFlip failed, ret=0x%x.", nRet);
                    LOG_M_W(SENSOR, "SNS[%d] change pipe[%d] chn[%d] flip=%d.", m_tSnsCfg.nSnsID, nPipeID, j, bFlip);
                    nRet = AX_VIN_SetChnFlip(nPipeID, (AX_VIN_CHN_ID_E)j, bFlip);
                }
                if (nRet != 0) {
                    bSucces = AX_FALSE;
                }
            }
        }
    }

    m_tSnsCfg.bMirror = bMirror;
    m_tSnsCfg.bFlip = bFlip;

    return bSucces;
}

AX_BOOL CBaseSensor::GetIspImageAttr(APP_ISP_IMAGE_ATTR_T &tAttr) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    AX_S32 ret = 0;
    // restore sharpness
    AX_ISP_IQ_SHARPEN_PARAM_T IspShpParam;
    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U32 i = 0; i < tSnsCfg.nPipeCount; i++) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_U8 nPipId = tSnsCfg.arrPipeAttr[i].nPipeID;
        ret = AX_ISP_IQ_GetShpParam(nPipId, &IspShpParam);

        tAttr.nSharpness =
            CalcIspIQToValue(IspShpParam.tManualParam.nShpGain[0], SENSOR_SHARPNESS_LOW, SENSOR_SHARPNESS_MEDIUM, SENSOR_SHARPNESS_HIGH);

        // restore Ycproc
        AX_ISP_IQ_YCPROC_PARAM_T IspYcprocParam;

        ret = AX_ISP_IQ_GetYcprocParam(nPipId, &IspYcprocParam);

        if (0 != ret) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_GetYcprocParam failed, ret=0x%x.", ret);
            return AX_FALSE;
        }

        tAttr.nBrightness =
            CalcIspIQToValue(IspYcprocParam.nBrightness, SENSOR_BRIGHTNESS_LOW, SENSOR_BRIGHTNESS_MEDIUM, SENSOR_BRIGHTNESS_HIGH);
        tAttr.nContrast = CalcIspIQToValue(IspYcprocParam.nContrast, SENSOR_CONTRAST_LOW, SENSOR_CONTRAST_MEDIUM, SENSOR_CONTRAST_HIGH);
        tAttr.nSaturation =
            CalcIspIQToValue(IspYcprocParam.nSaturation, SENSOR_SATURATION_LOW, SENSOR_SATURATION_MEDIUM, SENSOR_SATURATION_HIGH);
        tAttr.nAutoMode = IspShpParam.nAutoMode;
        LOG_MM_I(SENSOR, "autoMode:%d, tAttr.nSharpness:%d, tAttr.nBrightness:%d, tAttr.nContrast:%d,tAttr.nSaturation:%d",
                 IspShpParam.nAutoMode, tAttr.nSharpness, tAttr.nBrightness, tAttr.nContrast, tAttr.nSaturation);
        memcpy(&m_tImageAttr, &tAttr, sizeof(APP_ISP_IMAGE_ATTR_T));

        m_tSnsCfg.tColorAttr.bColorManual = (tAttr.nAutoMode == 0) ? AX_TRUE : AX_FALSE;
        m_tSnsCfg.tColorAttr.fBrightness = (AX_F32)tAttr.nBrightness;
        m_tSnsCfg.tColorAttr.fSharpness = (AX_F32)tAttr.nSharpness;
        m_tSnsCfg.tColorAttr.fContrast = (AX_F32)tAttr.nContrast;
        m_tSnsCfg.tColorAttr.fSaturation = (AX_F32)tAttr.nSaturation;
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::SetIspImageAttr(const APP_ISP_IMAGE_ATTR_T &tAttr) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    LOG_MM_C(SENSOR, "+++");
    AX_S32 ret = 0;
    AX_S32 nShpGain = CalcValueToIspIQ(tAttr.nSharpness, SENSOR_SHARPNESS_LOW, SENSOR_SHARPNESS_MEDIUM, SENSOR_SHARPNESS_HIGH);
    AX_S32 nBrightness = CalcValueToIspIQ(tAttr.nBrightness, SENSOR_BRIGHTNESS_LOW, SENSOR_BRIGHTNESS_MEDIUM, SENSOR_BRIGHTNESS_HIGH);
    AX_S32 nContrast = CalcValueToIspIQ(tAttr.nContrast, SENSOR_CONTRAST_LOW, SENSOR_CONTRAST_MEDIUM, SENSOR_CONTRAST_HIGH);
    AX_S32 nSaturation = CalcValueToIspIQ(tAttr.nSaturation, SENSOR_SATURATION_LOW, SENSOR_SATURATION_MEDIUM, SENSOR_SATURATION_HIGH);
    // set sharpness
    AX_ISP_IQ_SHARPEN_PARAM_T IspShpParam;
    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U32 i = 0; i < tSnsCfg.nPipeCount; i++) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_U8 nPipId = tSnsCfg.arrPipeAttr[i].nPipeID;
        ret = AX_ISP_IQ_GetShpParam(nPipId, &IspShpParam);
        IspShpParam.nAutoMode = tAttr.nAutoMode;

        IspShpParam.tManualParam.nShpGain[0] = nShpGain;
        IspShpParam.tManualParam.nShpGain[1] = nShpGain;

        ret = AX_ISP_IQ_SetShpParam(nPipId, &IspShpParam);

        if (0 != ret) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_SetShpParam failed, ret=0x%x.", ret);
            return AX_FALSE;
        }

        // set Ycproc
        AX_ISP_IQ_YCPROC_PARAM_T IspYcprocParam;

        ret = AX_ISP_IQ_GetYcprocParam(nPipId, &IspYcprocParam);

        if (0 != ret) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_GetYcprocParam failed, ret=0x%x.", ret);
            return AX_FALSE;
        }
        LOG_MM_I(SENSOR, "nSharpness:%d, nBrightness:%d, nContrast:%d,nSaturation:%d", tAttr.nSharpness, tAttr.nBrightness, tAttr.nContrast,
                 tAttr.nSaturation);
        IspYcprocParam.nBrightness = nBrightness;
        IspYcprocParam.nContrast = nContrast;
        IspYcprocParam.nSaturation = nSaturation;
        IspYcprocParam.nYCprocEn = AX_TRUE;

        ret = AX_ISP_IQ_SetYcprocParam(nPipId, &IspYcprocParam);

        if (0 != ret) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_SetYcprocParam failed, ret=0x%x.", ret);

            return AX_FALSE;
        }
    }

    {
        m_tSnsCfg.tColorAttr.bColorManual = (tAttr.nAutoMode == 0) ? AX_TRUE : AX_FALSE;
        m_tSnsCfg.tColorAttr.fBrightness = (AX_F32)tAttr.nBrightness;
        m_tSnsCfg.tColorAttr.fSharpness = (AX_F32)tAttr.nSharpness;
        m_tSnsCfg.tColorAttr.fContrast = (AX_F32)tAttr.nContrast;
        m_tSnsCfg.tColorAttr.fSaturation = (AX_F32)tAttr.nSaturation;
    }

    LOG_MM_C(SENSOR, "---");

    return AX_TRUE;
}

AX_BOOL CBaseSensor::RestoreIspImageAttr(APP_ISP_IMAGE_ATTR_T &tAttr) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    LOG_MM_C(SENSOR, "+++");

    AX_S32 ret = 0;
    // restore sharpness
    AX_ISP_IQ_SHARPEN_PARAM_T IspShpParam;
    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U32 i = 0; i < tSnsCfg.nPipeCount; i++) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_U8 nPipId = tSnsCfg.arrPipeAttr[i].nPipeID;
        ret = AX_ISP_IQ_GetShpParam(nPipId, &IspShpParam);

        // AX620 TODO: sharpness not support auto mode?
        // IspShpParam.nAutoMode = tAttr.nAutoMode;
        AX_S32 nShpGain = CalcValueToIspIQ(m_tImageAttr.nSharpness, SENSOR_SHARPNESS_LOW, SENSOR_SHARPNESS_MEDIUM, SENSOR_SHARPNESS_HIGH);

        IspShpParam.tManualParam.nShpGain[0] = nShpGain;
        IspShpParam.tManualParam.nShpGain[1] = nShpGain;

        ret = AX_ISP_IQ_SetShpParam(nPipId, &IspShpParam);

        if (0 != ret) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_SetShpParam failed, ret=0x%x.", ret);
            return AX_FALSE;
        }

        // restore Ycproc
        AX_ISP_IQ_YCPROC_PARAM_T IspYcprocParam;
        ret = AX_ISP_IQ_GetYcprocParam(nPipId, &IspYcprocParam);
        if (0 != ret) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_GetYcprocParam failed, ret=0x%x.", ret);
            return AX_FALSE;
        }
        IspYcprocParam.nBrightness =
            CalcValueToIspIQ(m_tImageAttr.nBrightness, SENSOR_BRIGHTNESS_LOW, SENSOR_BRIGHTNESS_MEDIUM, SENSOR_BRIGHTNESS_HIGH);
        IspYcprocParam.nContrast =
            CalcValueToIspIQ(m_tImageAttr.nContrast, SENSOR_CONTRAST_LOW, SENSOR_CONTRAST_MEDIUM, SENSOR_CONTRAST_HIGH);
        IspYcprocParam.nSaturation =
            CalcValueToIspIQ(m_tImageAttr.nSaturation, SENSOR_SATURATION_LOW, SENSOR_SATURATION_MEDIUM, SENSOR_SATURATION_HIGH);
        IspYcprocParam.nYCprocEn = AX_TRUE;
        m_tImageAttr.nAutoMode = tAttr.nAutoMode;

        tAttr = m_tImageAttr;

        ret = AX_ISP_IQ_SetYcprocParam(nPipId, &IspYcprocParam);
        LOG_MM_I(SENSOR, "nPipId:%d, nSharpness:%d, nBrightness:%d, nContrast:%d, nSaturation:%d", nPipId, m_tImageAttr.nSharpness,
                 m_tImageAttr.nBrightness, m_tImageAttr.nContrast, m_tImageAttr.nSaturation);
    }

    {
        m_tSnsCfg.tColorAttr.bColorManual = (tAttr.nAutoMode == 0) ? AX_TRUE : AX_FALSE;
        m_tSnsCfg.tColorAttr.fBrightness = tAttr.nBrightness;
        m_tSnsCfg.tColorAttr.fSharpness = tAttr.nSharpness;
        m_tSnsCfg.tColorAttr.fContrast = tAttr.nContrast;
        m_tSnsCfg.tColorAttr.fSaturation = tAttr.nSaturation;
    }

    LOG_MM_C(SENSOR, "---");

    return AX_TRUE;
}

// Linear: ([low, 0], [medium, 50]); ([medium, 50], [max, 100])
AX_S32 CBaseSensor::CalcValueToIspIQ(AX_F32 fVal, AX_S32 nLow, AX_S32 nMedium, AX_S32 nHigh) {
    AX_S32 nIQ = 0;

    if (nIQ < 0.) {
        nIQ = nLow;
    } else if (fVal <= 50.) {
        nIQ = nLow + fVal * (nMedium - nLow) / 50;
    } else if (fVal <= 100.) {
        nIQ = 2 * nMedium - nHigh + fVal * (nHigh - nMedium) / 50;
    } else {
        nIQ = nHigh;
    }

    return nIQ;
}

AX_F32 CBaseSensor::CalcIspIQToValue(AX_S32 nIQ, AX_S32 nLow, AX_S32 nMedium, AX_S32 nHigh) {
    AX_F32 fVal = 0;

    if (nIQ < nLow) {
        fVal = 0.;
    } else if (nIQ <= nMedium) {
        fVal = 50. * (nIQ - nLow) / (nMedium - nLow);
    } else if (nIQ <= nHigh) {
        fVal = 50. * (nIQ + nHigh - 2 * nMedium) / (nHigh - nMedium);
    } else {
        fVal = 100.;
    }

    return fVal;
}

AX_BOOL CBaseSensor::SetSnsAttr(AX_U8 nPipeId, const AX_SNS_ATTR_T &tSnsAttr) {
    AX_SNS_ATTR_T tAttr = tSnsAttr;

    if (tAttr.fFrameRate < m_tAbilities.fShutterSlowFpsThr) {
        tAttr.fFrameRate = m_tAbilities.fShutterSlowFpsThr;
    }

    AX_S32 nRet = AX_ISP_SetSnsAttr(nPipeId, &tAttr);

    if (0 != nRet) {
        LOG_MM_E(SENSOR, "pipe:[%d] AX_ISP_SetSnsAttr failed, ret=0x%x.", nPipeId, nRet);
        return AX_FALSE;
    } else {
        LOG_MM_I(SENSOR, "pipe:[%d] AX_ISP_SetSnsAttr OK.", nPipeId);
    }

    if (m_bSensorStarted) {
        if (tSnsAttr.fFrameRate != tAttr.fFrameRate) {
            SNS_SHUTTER_MODE_E eShutterMode = GetShutterMode();

            if (eShutterMode != E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E) {
                SetShutterMode(E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E);
            }

            if (m_pSnsObj && m_pSnsObj->pfn_sensor_set_slow_fps) {
                GetShutterMode();
                m_pSnsObj->pfn_sensor_set_slow_fps(nPipeId, tSnsAttr.fFrameRate);
            }
        }
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::UpdateSnsAttr() {
    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipeId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        if (!SetSnsAttr(nPipeId, m_tSnsAttr)) {
            return AX_FALSE;
        }
    }
    return AX_TRUE;
}

AX_BOOL CBaseSensor::SetAeRoiAttr(AX_BOOL bEnable) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U8 i = 0; i < tSnsCfg.nPipeCount; i++) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_U8 nPipeId = tSnsCfg.arrPipeAttr[i].nPipeID;

        AX_ISP_IQ_AE_PARAM_T tAeParam;
        memset(&tAeParam, 0x00, sizeof(tAeParam));

        AX_S32 nRet = AX_ISP_IQ_GetAeParam(nPipeId, &tAeParam);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "AX_ISP_IQ_GetAeParam failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }

        tAeParam.tAeAlgAuto.tFaceUIParam.nEnable = bEnable;

        nRet = AX_ISP_IQ_SetAeParam(nPipeId, &tAeParam);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "AX_ISP_IQ_SetAeParam failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }
    }

    m_tSnsCfg.tAeRoiAttr.bEnable = bEnable;

    return AX_TRUE;
}

AX_BOOL CBaseSensor::SetAeRoi(const std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    if (!m_tSnsCfg.tAeRoiAttr.bEnable) {
        return AX_TRUE;
    }

    AX_BOOL bUpdate = AX_FALSE;
    AX_ISP_AE_FACE_DETECTION_PARAM_T tAeParam;

    if (stVecItem.size() > 0) {
        bUpdate = AX_TRUE;
        memset(&tAeParam, 0x00, sizeof(tAeParam));

        AX_U32 nAeRoiCnt = stVecItem.size();

        auto& nFaceIndex = tAeParam.nFaceNum;
        for (AX_U32 i = 0; i < nAeRoiCnt && nFaceIndex < AX_AE_FACE_DETECTION_MAX_NUM; i ++) {
            tAeParam.nFaceID[nFaceIndex] = stVecItem[i].u64TrackId;
            tAeParam.nFaceConfidence[nFaceIndex] = CAXTypeConverter::AeFloat2Int(stVecItem[i].fConfidence, 1, 10, AX_FALSE);
            tAeParam.tFaceInfos[nFaceIndex].nFaceStartX = CAXTypeConverter::AeFloat2Int(stVecItem[i].tBox.fX, 1, 10, AX_FALSE);
            tAeParam.tFaceInfos[nFaceIndex].nFaceStartY = CAXTypeConverter::AeFloat2Int(stVecItem[i].tBox.fY, 1, 10, AX_FALSE);
            tAeParam.tFaceInfos[nFaceIndex].nFaceWidth = CAXTypeConverter::AeFloat2Int(stVecItem[i].tBox.fW, 1, 10, AX_FALSE);
            tAeParam.tFaceInfos[nFaceIndex].nFaceHeight = CAXTypeConverter::AeFloat2Int(stVecItem[i].tBox.fH, 1, 10, AX_FALSE);
            nFaceIndex ++;
        }

        m_bAeRoiManual = AX_TRUE;
    } else {
        if (m_bAeRoiManual) {
            bUpdate = AX_TRUE;
            m_bAeRoiManual = AX_FALSE;
            memset(&tAeParam, 0x00, sizeof(tAeParam));
        }
    }

    if (bUpdate) {
        SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
        for (AX_U8 i = 0; i < tSnsCfg.nPipeCount; i++) {
            if (!m_bSensorStarted) {
                continue;
            }

            AX_U8 nPipeId = tSnsCfg.arrPipeAttr[i].nPipeID;

            AX_S32 nRet = AX_ISP_IQ_SetAeFaceROI(nPipeId, &tAeParam);
            if (0 != nRet) {
                LOG_M_E(SENSOR, "AX_ISP_IQ_SetAeFaceROI failed, ret=0x%08X.", nRet);
                return AX_FALSE;
            }
        }
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::UpdateLDC(AX_BOOL bLdcEnable, AX_BOOL bAspect, AX_S16 nXRatio, AX_S16 nYRatio, AX_S16 nXYRatio, AX_S16 nDistorRatio) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    LOG_MM_I(SENSOR, "UpdateLDC+++");
    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipId = m_tSnsCfg.arrPipeAttr[i].nPipeID;
        AX_ISP_IQ_LDC_PARAM_T tLdcAttr;
        AX_ISP_IQ_GetLdcParam(nPipId, &tLdcAttr);
        tLdcAttr = {.nLdcEnable = bLdcEnable,
                    .nType = AX_ISP_IQ_LDC_TYPE_V1,
                    .tLdcV1Param =
                        {
                            .bAspect = bAspect,
                            .nXRatio = nXRatio,
                            .nYRatio = nYRatio,
                            .nXYRatio = nXYRatio,
                            .nCenterXOffset = 0,
                            .nCenterYOffset = 0,
                            .nDistortionRatio = nDistorRatio,
                            .nSpreadCoef = 0,
                        },
                    .tLdcV2Param = {.nMatrix =
                                        {
                                            {0, 0, 0, /*0 - 2*/},
                                            {0, 0, 0, /*0 - 2*/},
                                            {0, 0, 1, /*0 - 2*/},
                                        },
                                    .nDistortionCoeff = {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/}}};

        if (m_bSensorStarted) {
            AX_S32 nRet = AX_ISP_IQ_SetLdcParam(nPipId, &tLdcAttr);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(SENSOR, "AX_ISP_IQ_SetLdcParam failed ret=0x%x", nRet);
                return AX_FALSE;
            }
        }

        m_tSnsCfg.arrPipeAttr[i].tLdcAttr.bLdcEnable = bLdcEnable;
        m_tSnsCfg.arrPipeAttr[i].tLdcAttr.bLdcAspect = bAspect;
        m_tSnsCfg.arrPipeAttr[i].tLdcAttr.nLdcXRatio = nXRatio;
        m_tSnsCfg.arrPipeAttr[i].tLdcAttr.nLdcYRatio = nYRatio;
        m_tSnsCfg.arrPipeAttr[i].tLdcAttr.nLdcXYRatio = nXYRatio;
        m_tSnsCfg.arrPipeAttr[i].tLdcAttr.nLdcDistortionRatio = nDistorRatio;
    }

    LOG_MM_I(SENSOR, "UpdateLDC---");
    return AX_TRUE;
}

AX_BOOL CBaseSensor::UpdateDIS(AX_BOOL bDisEnable) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);
    LOG_MM_I(SENSOR, "UpdateDIS+++");
    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipId = m_tSnsCfg.arrPipeAttr[i].nPipeID;
        AX_ISP_IQ_DIS_PARAM_T tDisAttr;
        AX_ISP_IQ_GetDisParam(nPipId, &tDisAttr);

        if (m_bSensorStarted) {
            tDisAttr.bDisEnable = bDisEnable;
            if (tDisAttr.bDisEnable &&
                m_tSnsCfg.arrPipeAttr[0].tDisAttr.nDelayFrameNum > 0) {
                tDisAttr.tDisV1Param.nDelayFrameNum = m_tSnsCfg.arrPipeAttr[0].tDisAttr.nDelayFrameNum;
            }
            AX_S32 nRet = AX_ISP_IQ_SetDisParam(nPipId, &tDisAttr);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(SENSOR, "AX_ISP_IQ_SetDisParam failed ret=0x%x", nRet);
                return AX_FALSE;
            }
        }

        m_tSnsCfg.arrPipeAttr[i].tDisAttr.bDisEnable = bDisEnable;
    }

    LOG_MM_I(SENSOR, "UpdateDIS---");

    return AX_TRUE;
}

AX_BOOL CBaseSensor::UpdateRotation(AX_VIN_ROTATION_E eRotation) {
    LOG_MM_I(SENSOR, "UpdateRotation+++");
    AX_S32 nRet = 0;
    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        AX_VIN_ROTATION_E eRotionOld = AX_VIN_ROTATION_0;

        nRet = AX_VIN_GetChnRotation(nPipId, AX_VIN_CHN_ID_MAIN, &eRotionOld);
        if (AX_SUCCESS != nRet) {
            LOG_MM_E(SENSOR, "AX_VIN_GetChnRotation failed ret=0x%x", nRet);
        }

        if (eRotation != eRotionOld) {
            nRet = AX_VIN_SetChnRotation(nPipId, AX_VIN_CHN_ID_MAIN, eRotation);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(SENSOR, "AX_VIN_SetChnRotation failed ret=0x%x", nRet);
                return AX_FALSE;
            }
        } else {
            LOG_MM_I(SENSOR, "Ratation %d not changed", eRotation);
        }
    }

    m_tSnsCfg.eRotation = (AX_ROTATION_E)eRotation;

    if (m_tSnsCfg.tEZoomAttr.nEZoomRatio) {
        EZoom(m_tSnsCfg.tEZoomAttr.nEZoomRatio, m_tSnsCfg.tEZoomAttr.nCenterOffsetX, m_tSnsCfg.tEZoomAttr.nCenterOffsetY);
    }

    LOG_MM_I(SENSOR, "UpdateRotation---");
    return AX_TRUE;
}

AX_BOOL CBaseSensor::EnableChn(AX_BOOL bEnable)  {
    LOG_MM_I(SENSOR, "EnableChn +++, enable=%d", bEnable);
    AX_S32 nRet = 0;
    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        if (bEnable) {
            nRet = AX_VIN_EnableChn(nPipId, AX_VIN_CHN_ID_MAIN);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(SENSOR, "AX_VIN_EnableChn failed ret=0x%x", nRet);
                return AX_FALSE;
            }
        } else {
            nRet = AX_VIN_DisableChn(nPipId, AX_VIN_CHN_ID_MAIN);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(SENSOR, "AX_VIN_DisableChn failed ret=0x%x", nRet);
                return AX_FALSE;
            }
        }
    }

    LOG_MM_I(SENSOR, "EnableChn ---, enable=%d", bEnable);
    return AX_TRUE;
}

AX_BOOL CBaseSensor::UpdateSnsFps(AX_S32 nFps) {
    if (0 >= nFps || 30 < nFps) {
        return AX_TRUE;
    }

    SNS_SHUTTER_MODE_E eShutterMode = GetShutterMode();

    if (eShutterMode != E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E) {
        SetShutterMode(E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E);
    }

    if (m_pSnsObj && m_pSnsObj->pfn_sensor_set_slow_fps) {
        for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
            AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;
            m_pSnsObj->pfn_sensor_set_slow_fps(nPipeID, nFps);
        }
    }
    return AX_TRUE;
}

AX_BOOL CBaseSensor::GetAeStatus(AX_ISP_IQ_AE_STATUS_T& tAeStatus) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    if (!m_bSensorStarted) {
        return AX_FALSE;
    }

    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U8 i = 0; i < tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipeId = tSnsCfg.arrPipeAttr[i].nPipeID;

        AX_S32 nRet = AX_ISP_IQ_GetAeStatus(nPipeId, &tAeStatus);

        if (0 != nRet) {
            LOG_M_E(SENSOR, "AX_ISP_IQ_GetAeStatus failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }

        return AX_TRUE;
    }

    return AX_FALSE;
}

AX_BOOL CBaseSensor::GetDayNightStatus(AX_DAYNIGHT_MODE_E& eDayNightStatus) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    if (!m_bSensorStarted) {
        return AX_FALSE;
    }

    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U8 i = 0; i < tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipeId = tSnsCfg.arrPipeAttr[i].nPipeID;

        for (AX_U8 j = AX_VIN_CHN_ID_MAIN; j < AX_VIN_CHN_ID_MAX; j++) {
            if (tSnsCfg.arrPipeAttr[i].arrChannelAttr[j].bChnEnable) {
                AX_S32 nRet = AX_VIN_GetChnDayNightMode(nPipeId, (AX_VIN_CHN_ID_E)j, &eDayNightStatus);

                if (0 != nRet) {
                    LOG_M_E(SENSOR, "AX_VIN_GetChnDayNightMode failed, ret=0x%x.", nRet);
                    return AX_FALSE;
                }

                return AX_TRUE;
            }
        }
    }

    return AX_FALSE;
}

AX_BOOL CBaseSensor::SetIrAttr(const SENSOR_IRCUT_ATTR_T& tIrAttr) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    SENSOR_CONFIG_T tSnsCfg = GetSnsConfig();
    for (AX_U8 i = 0; i < tSnsCfg.nPipeCount; i++) {
        if (!m_bSensorStarted) {
            continue;
        }

        AX_DAYNIGHT_MODE_E eDayNightStatus = AX_DAYNIGHT_MODE_DAY;
        AX_ISP_IQ_IR_PARAM_T tIrParam;
        memset(&tIrParam, 0x00, sizeof(tIrParam));

        AX_U8 nPipeId = tSnsCfg.arrPipeAttr[i].nPipeID;

        for (AX_U8 j = AX_VIN_CHN_ID_MAIN; j < AX_VIN_CHN_ID_MAX; j++) {
            if (tSnsCfg.arrPipeAttr[i].arrChannelAttr[j].bChnEnable) {
                AX_S32 nRet = AX_VIN_GetChnDayNightMode(nPipeId, (AX_VIN_CHN_ID_E)j, &eDayNightStatus);

                if (0 != nRet) {
                    LOG_M_E(SENSOR, "AX_VIN_GetChnDayNightMode failed, ret=0x%x.", nRet);
                    return AX_FALSE;
                }

                return AX_TRUE;
            }
        }

        tIrParam.nIrCalibR                = CAXTypeConverter::AeFloat2Int(tIrAttr.fIrCalibR, 8, 10, AX_FALSE);
        tIrParam.nIrCalibG                = CAXTypeConverter::AeFloat2Int(tIrAttr.fIrCalibG, 8, 10, AX_FALSE);
        tIrParam.nIrCalibB                = CAXTypeConverter::AeFloat2Int(tIrAttr.fIrCalibB, 8, 10, AX_FALSE);
        tIrParam.nNight2DayIrStrengthTh   = CAXTypeConverter::AeFloat2Int(tIrAttr.fNight2DayIrStrengthTh, 8, 10, AX_FALSE);
        tIrParam.nNight2DayIrDetectTh     = CAXTypeConverter::AeFloat2Int(tIrAttr.fNight2DayIrDetectTh, 8, 10, AX_FALSE);
        tIrParam.nDay2NightLuxTh          = CAXTypeConverter::AeFloat2Int(tIrAttr.fDay2NightLuxTh, 22, 10, AX_FALSE);
        tIrParam.nNight2DayLuxTh          = CAXTypeConverter::AeFloat2Int(tIrAttr.fNight2DayLuxTh, 22, 10, AX_FALSE);
        tIrParam.nNight2DayBrightTh       = CAXTypeConverter::AeFloat2Int(tIrAttr.fNight2DayBrightTh, 8, 10, AX_FALSE);
        tIrParam.nNight2DayDarkTh         = CAXTypeConverter::AeFloat2Int(tIrAttr.fNight2DayDarkTh, 8, 10, AX_FALSE);
        tIrParam.nNight2DayUsefullWpRatio = CAXTypeConverter::AeFloat2Int(tIrAttr.fNight2DayUsefullWpRatio, 8, 10, AX_FALSE);
        tIrParam.nCacheTime               = tIrAttr.nCacheTime;
        tIrParam.nInitDayNightMode        = eDayNightStatus;

        AX_S32 nRet = AX_ISP_IQ_SetIrParam(nPipeId, &tIrParam);

        if (0 != nRet) {
            LOG_M_E(SENSOR, "AX_ISP_IQ_SetIrParam failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }

        return AX_TRUE;
    }

    return AX_FALSE;
}

AX_VOID CBaseSensor::UpdateSps(const SENSOR_SOFT_PHOTOSENSITIVITY_ATTR_T& tAttr) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    m_tSnsCfg.tSoftPhotoSensitivityAttr = tAttr;

    if (m_pSps) {
        m_pSps->Update(tAttr);
    }
}

AX_VOID CBaseSensor::UpdateHnb(const SENSOR_HOTNOISEBALANCE_T& tAttr) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    m_tSnsCfg.tHotNoiseBalanceAttr = tAttr;

    if (m_pHnb) {
        m_pHnb->Update(tAttr);
    }
}

AX_VOID CBaseSensor::UpdateAeRoi(const SENSOR_AE_ROI_ATTR_T& tAttr) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    m_tSnsCfg.tAeRoiAttr = tAttr;

    if (m_pAeRoi) {
        m_pAeRoi->Update(tAttr);
    }
}

AX_VOID CBaseSensor::UpdateAeRoi(const std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    if (m_pAeRoi) {
        m_pAeRoi->UpdateAeRoi(stVecItem);
    }
}

AX_BOOL CBaseSensor::EZoom(AX_S32 nEZoomRatio, AX_S32 nCenterOffsetX, AX_S32 nCenterOffsetY) {
    LOG_MM_I(SENSOR, "EZoom +++, EZoomRatio=%d", nEZoomRatio);
    if (nEZoomRatio < 0 || nEZoomRatio > AX_EZOOM_MAX) {
        return AX_FALSE;
    }

    AX_S32 nRet = 0;
    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        AX_VIN_CROP_INFO_T tCropInfo;
        AX_VIN_GetChnCrop(nPipId, AX_VIN_CHN_ID_MAIN, &tCropInfo);
        if (nEZoomRatio == 0) {
            if (tCropInfo.bEnable) {
                tCropInfo.bEnable = AX_FALSE;
                nRet = AX_VIN_SetChnCrop(nPipId, AX_VIN_CHN_ID_MAIN, &tCropInfo);
                if (AX_SUCCESS != nRet) {
                    LOG_MM_E(SENSOR, "AX_VIN_SetChnCrop failed ret=0x%x", nRet);
                    return AX_FALSE;
                }
            }
            m_tSnsCfg.tEZoomAttr.nEZoomRatio = nEZoomRatio;
        } else {
            AX_VIN_ROTATION_E eRotation;
            nRet = AX_VIN_GetChnRotation(nPipId, AX_VIN_CHN_ID_MAIN, &eRotation);
            AX_U32 nWidth = m_tSnsAttr.nWidth;
            AX_U32 nHeight = m_tSnsAttr.nHeight;
            if (AX_VIN_ROTATION_90 == eRotation || AX_VIN_ROTATION_270 == eRotation) {
                std::swap(nWidth, nHeight);
            }
            AX_U32 nStepW = nWidth / AX_EZOOM_MAX;
            AX_U32 nStepH = nHeight / AX_EZOOM_MAX;

            tCropInfo.bEnable = AX_TRUE;
            tCropInfo.eCoordMode = AX_VIN_COORD_ABS;
            tCropInfo.tCropRect.nWidth = nStepW * (AX_EZOOM_MAX - nEZoomRatio + 1);
            tCropInfo.tCropRect.nHeight = nStepH * (AX_EZOOM_MAX - nEZoomRatio + 1);
            tCropInfo.tCropRect.nStartX = (nWidth - tCropInfo.tCropRect.nWidth) / 2;
            tCropInfo.tCropRect.nStartY = (nHeight - tCropInfo.tCropRect.nHeight) / 2;

            LOG_MM_I(SENSOR, "crop info enable=%d, coord_mode=%d, rect=[%d, %d, %d, %d]", tCropInfo.bEnable, tCropInfo.eCoordMode,
              tCropInfo.tCropRect.nStartX, tCropInfo.tCropRect.nStartY, tCropInfo.tCropRect.nWidth, tCropInfo.tCropRect.nHeight);

            nRet = AX_VIN_SetChnCrop(nPipId, AX_VIN_CHN_ID_MAIN, &tCropInfo);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(SENSOR, "AX_VIN_SetChnCrop failed ret=0x%x", nRet);
                return AX_FALSE;
            }
            m_tSnsCfg.tEZoomAttr.nEZoomRatio = nEZoomRatio;
            m_tSnsCfg.tEZoomAttr.nCenterOffsetX = nCenterOffsetX;
            m_tSnsCfg.tEZoomAttr.nCenterOffsetY = nCenterOffsetY;
        }

    }

    LOG_MM_I(SENSOR, "EZoom ---, nZoom=%d", nEZoomRatio);
    return AX_TRUE;
}

AX_BOOL CBaseSensor::UpdateSceneMode() {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    if (!m_bSensorStarted) {
        return AX_FALSE;
    }

    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipeId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        if (E_SNS_TISP_MODE_E == m_tSnsCfg.arrPipeAttr[i].eAiIspMode
            || E_SNS_AIISP_DEFAULT_SCENE_MODE_E == m_tSnsCfg.arrPipeAttr[i].eAiIspMode) {
            continue;
        }

        AX_ISP_IQ_SCENE_PARAM_T tIspSceneParam;
        memset(&tIspSceneParam, 0x00, sizeof(tIspSceneParam));

        AX_S32 nRet = AX_ISP_IQ_GetSceneParam(nPipeId, &tIspSceneParam);

        if (0 != nRet) {
            LOG_MM_E(SENSOR, "pipe:[%d] AX_ISP_IQ_GetSceneParam failed, ret=0x%x.", nPipeId, nRet);
            return AX_FALSE;
        }

        switch (m_tSnsCfg.arrPipeAttr[i].eAiIspMode) {
            case E_SNS_AIISP_MANUAL_SCENE_AIISP_MODE_E:
                // manual mode
                tIspSceneParam.nAutoMode = 0;
                tIspSceneParam.tManualParam.nAiWorkMode = AX_AI_ENABLE;
                break;
            case E_SNS_AIISP_MANUAL_SCENE_TISP_MODE_E:
                // manual mode
                tIspSceneParam.nAutoMode = 0;
                tIspSceneParam.tManualParam.nAiWorkMode = AX_AI_DISABLE;
                break;
            case E_SNS_AIISP_AUTO_SCENE_MODE_E:
                // auto mode
                tIspSceneParam.nAutoMode = 1;
                // AX620E TODO for auto mode param settings
                break;
            default:
                break;
        }

        nRet = AX_ISP_IQ_SetSceneParam(nPipeId, &tIspSceneParam);

        if (0 != nRet) {
            LOG_MM_E(SENSOR, "pipe:[%d] AX_ISP_IQ_SetSceneParam failed, ret=0x%x.", nPipeId, nRet);
            return AX_FALSE;
        } else {
            LOG_MM_I(SENSOR, "pipe:[%d] AX_ISP_IQ_SetSceneParam OK.", nPipeId);
        }
    }

    return AX_TRUE;
}

SNS_SHUTTER_MODE_E CBaseSensor::GetShutterMode(AX_VOID) {
    SNS_SHUTTER_MODE_E eShutterMode = E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E;

    if (!m_bSensorStarted) {
        return eShutterMode;
    }

    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipeId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        AX_ISP_IQ_AE_PARAM_T tIspAeParam;
        memset(&tIspAeParam, 0x00, sizeof(tIspAeParam));

        AX_S32 nRet = AX_ISP_IQ_GetAeParam(nPipeId, &tIspAeParam);

        if (0 != nRet) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_GetAeParam failed, ret=0x%x.", nRet);
            return eShutterMode;
        }

        /* 0: FIX FRAME RATE MODE; 1: SLOW SHUTTER MODE */
        switch(tIspAeParam.tAeAlgAuto.tSlowShutterParam.nFrameRateMode) {
        case 0:
            eShutterMode = E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E;
            break;
        case 1:
            eShutterMode = E_SNS_SHUTTER_SLOW_SHUTTER_MODE_E;
            break;
        default:
            break;
        }

        return eShutterMode;
    }

    return eShutterMode;
}

AX_BOOL CBaseSensor::SetShutterMode(SNS_SHUTTER_MODE_E eShutterMode) {
    if (!m_bSensorStarted) {
        return AX_FALSE;
    }

    LOG_MM_C(SENSOR, "set shutter mode: %d", eShutterMode);

    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipeId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        AX_ISP_IQ_AE_PARAM_T tIspAeParam;
        memset(&tIspAeParam, 0x00, sizeof(tIspAeParam));

        AX_S32 nRet = AX_ISP_IQ_GetAeParam(nPipeId, &tIspAeParam);

        if (0 != nRet) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_GetAeParam failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }

        /* 0: FIX FRAME RATE MODE; 1: SLOW SHUTTER MODE */
        AX_U8 nFrameRateMode = 0;

        switch(eShutterMode) {
        case E_SNS_SHUTTER_FIX_FRAMERATE_MODE_E:
            nFrameRateMode = 0;
            break;
        case E_SNS_SHUTTER_SLOW_SHUTTER_MODE_E:
            nFrameRateMode = 1;
            break;
        default:
            break;
        }

        /* 0: FIX FRAME RATE MODE; 1: SLOW SHUTTER MODE */
        tIspAeParam.tAeAlgAuto.tSlowShutterParam.nFrameRateMode = nFrameRateMode;

        nRet = AX_ISP_IQ_SetAeParam(nPipeId, &tIspAeParam);

        if (0 != nRet) {
            LOG_MM_E(SENSOR, "AX_ISP_IQ_SetAeParam failed, ret=0x%x.", nRet);
            return AX_FALSE;
        }
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::LoadBinParams(const std::string &strBinName) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    if (access(strBinName.c_str(), F_OK) != 0) {
        LOG_MM_C(SENSOR, "(%s) not exist.", strBinName.c_str());
    } else {
        for (AX_U8 i = 0; i < GetPipeCount(); i++) {
            AX_U8 nPipeID = m_tSnsCfg.arrPipeAttr[i].nPipeID;

            AX_S32 nRet = AX_ISP_LoadBinParams(nPipeID, strBinName.c_str());

            if (0 != nRet) {
                LOG_M_E(SENSOR, "AX_ISP_LoadBinParams (%s) failed, ret=0x%x.", strBinName.c_str(), nRet);

                return AX_FALSE;
            } else {
                LOG_MM_C(SENSOR, "AX_ISP_LoadBinParams (%s) successfully.", strBinName.c_str());
            }
        }
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::GetSnsTemperature(AX_F32 &fTemperature) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    if (!m_bSensorStarted) {
        return AX_FALSE;
    }

#if 0
    for (AX_U32 i = 0; i < m_tSnsCfg.nPipeCount; i++) {
        AX_U8 nPipeId = m_tSnsCfg.arrPipeAttr[i].nPipeID;

        if (m_pSnsObj && m_pSnsObj->pfn_sensor_get_temperature_info) {
            AX_S32 nTemperature = 0;

            AX_S32 nRet = m_pSnsObj->pfn_sensor_get_temperature_info(nPipeId, &nTemperature);

            if (0 == nRet) {
                fTemperature = (AX_F32)nTemperature/1000.0;

                return AX_TRUE;
            }
        }
    }
#endif

    return AX_FALSE;
}

AX_VOID CBaseSensor::GetResolution(AX_U32 &nWidth, AX_U32 &nHeight) {
    std::lock_guard<std::mutex> _ApiLck(m_mtx);

    nWidth = m_tSnsResolution.nSnsOutWidth;
    nHeight = m_tSnsResolution.nSnsOutHeight;
}

AX_BOOL CBaseSensor::SetMultiSnsSync(AX_BOOL bSync)
{
    AX_S32 nRet = 0;

    for (auto &m : m_mapPipe2Attr) {
        AX_U8 nPipeID = m.first;

        AX_ISP_IQ_AWB_PARAM_T stIspAwbParam = {0};
        nRet = AX_ISP_IQ_GetAwbParam(nPipeID, &stIspAwbParam);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d]AX_ISP_IQ_GetAwbParam failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        }
        stIspAwbParam.nEnable = 1;
        stIspAwbParam.tAutoParam.nMultiCamSyncMode = bSync ? 1 : 0; /* 0：INDEPEND MODE； 1： MASTER SLAVE MODE; 2: OVERLAP MODE */
        nRet = AX_ISP_IQ_SetAwbParam(nPipeID, &stIspAwbParam);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d]AX_ISP_IQ_SetAwbParam failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        }

        AX_ISP_IQ_AE_PARAM_T stIspAeParam = {0};
        nRet = AX_ISP_IQ_GetAeParam(nPipeID, &stIspAeParam);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d]AX_ISP_IQ_GetAeParam failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        }
        stIspAeParam.nEnable = 1;
        stIspAeParam.tAeAlgAuto.nMultiCamSyncMode = bSync ? 3 : 0; /* 0：INDEPEND MODE； 1： MASTER SLAVE MODE; 2: OVERLAP MODE; 3: SPLICE MODE */
        nRet = AX_ISP_IQ_SetAeParam(nPipeID, &stIspAeParam);
        if (0 != nRet) {
            LOG_M_E(SENSOR, "[%d]AX_ISP_IQ_SetAeParam failed, ret=0x%x.", nPipeID, nRet);
            return AX_FALSE;
        }
    }

    return AX_TRUE;
}

AX_BOOL CBaseSensor::IsSnsSync() {
    if (AX_SNS_SYNC_MASTER == (AX_SNS_MASTER_SLAVE_E)m_tSnsCfg.nMasterSlaveSel
        || AX_SNS_SYNC_SLAVE == (AX_SNS_MASTER_SLAVE_E)m_tSnsCfg.nMasterSlaveSel) {
        return AX_TRUE;
    }

    return AX_FALSE;
}
