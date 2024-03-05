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

#include <mutex>
#include "Capture.hpp"
#include "Collector.h"
#include "Detector.hpp"
#include "DummyEncoder.h"
#include "IPPLBuilder.h"
#include "IPPLConfig.h"
#include "IVESStage.h"
#include "IVPSGrpStage.h"
#include "JpegEncoder.h"
#include "Linkage.h"
#include "PoolConfig.h"
#include "SensorMgr.h"
#include "VideoEncoder.h"

class COPALBuilder : public IPPLBuilder {
public:
    COPALBuilder(AX_VOID) = default;
    ~COPALBuilder(AX_VOID) = default;

public:
    virtual AX_BOOL Init(AX_VOID);
    virtual AX_BOOL Deinit(AX_VOID);
    virtual AX_BOOL Construct(AX_VOID);
    virtual AX_BOOL Destroy(AX_VOID);
    virtual AX_BOOL Start(AX_VOID);
    virtual AX_BOOL Stop(AX_VOID);

    /* Web relative interfaces */
    virtual AX_BOOL ProcessWebOprs(WEB_REQUEST_TYPE_E eReqType, const AX_VOID* pJsonReq, AX_VOID** pResult = nullptr) override;
    virtual AX_BOOL ProcessTestSuiteOpers(WEB_REQ_OPERATION_T& tOperation) override;

    virtual CSensorMgr* GetSensorMgr() {
        return &m_mgrSensor;
    };
    virtual vector<CIVPSGrpStage*> GetIvpsInst() {
        return m_vecIvpsInstance;
    };
    virtual vector<CVideoEncoder*> GetVencInst() {
        return m_vecVencInstance;
    };
    virtual vector<CJpegEncoder*> GetJencInst() {
        return m_vecJencInstance;
    };
    virtual CDetector* GetDetectorInst() {
        return &m_detector;
    };
    virtual vector<CIVESStage*> GetIvesInst() {
        return m_vecIvesInstance;
    };
    virtual CCapture* GetCaptureInst() {
        return &m_capture;
    };
    virtual CLinkage* GetLinkageInst() {
        return &m_linkage;
    };

protected:
    AX_BOOL InitSysMods(AX_VOID);
    AX_BOOL DeInitSysMods(AX_VOID);

    AX_S32 APP_LOG_Init(AX_VOID);
    AX_S32 APP_LOG_DeInit(AX_VOID);
    AX_S32 APP_SYS_Init(AX_VOID);
    AX_S32 APP_SYS_DeInit(AX_VOID);
    AX_S32 APP_VENC_Init(AX_VOID);
    AX_S32 APP_VENC_DeInit(AX_VOID);
    AX_S32 APP_NPU_Init(AX_VOID);
    AX_S32 APP_NPU_DeInit(AX_VOID);

    AX_S32 APP_ACAP_Init(AX_VOID);
    AX_S32 APP_ACAP_DeInit(AX_VOID);
    AX_S32 APP_APLAY_Init(AX_VOID);
    AX_S32 APP_APLAY_DeInit(AX_VOID);

private:
    AX_BOOL InitSensor();
    AX_BOOL InitIvps();
    AX_BOOL InitVenc();
    AX_BOOL InitJenc();
    AX_BOOL InitCollector();
    AX_BOOL InitDetector();
    AX_BOOL InitCapture();
    AX_BOOL InitPoolConfig();

    AX_BOOL GetRelationsBySrcMod(IPC_MOD_INFO_T& tSrcMod, vector<IPC_MOD_RELATIONSHIP_T>& vecOutRelations,
                                 AX_BOOL bIgnoreChn = AX_FALSE) const;
    AX_BOOL GetRelationsByDstMod(IPC_MOD_INFO_T& tDstMod, vector<IPC_MOD_RELATIONSHIP_T>& vecOutRelations,
                                 AX_BOOL bIgnoreChn = AX_FALSE) const;
    AX_BOOL GetPrecedingMod(const IPC_MOD_INFO_T& tDstMod, IPC_MOD_INFO_T& tPrecedingMod);

    AX_VOID PostStartProcess(AX_VOID);
    AX_BOOL InitAudio();
    AX_BOOL ConstructIves();
    AX_BOOL InitIves();

    AX_BOOL UpdateRotation(AX_U8 nSnsID, AX_U8 nRotation);

public:
    CSensorMgr m_mgrSensor;
    vector<CIVPSGrpStage*> m_vecIvpsInstance;
    vector<CVideoEncoder*> m_vecVencInstance;
    vector<CCollector*> m_vecCollectorInstance;
    vector<CIVESStage*> m_vecIvesInstance;
    vector<CJpegEncoder*> m_vecJencInstance;
    CDetector m_detector;
    CCapture m_capture;

    std::vector<std::unique_ptr<IObserver>> m_vecCollectorObs;
    std::vector<std::unique_ptr<IObserver>> m_vecDetectorObs;
    std::vector<std::unique_ptr<IObserver>> m_vecIvesObs;
    std::vector<std::unique_ptr<IObserver>> m_vecIvpsObs;
    std::vector<std::unique_ptr<IObserver>> m_vecMpeg4Obs;
    std::vector<std::unique_ptr<IObserver>> m_vecCaptureObs;
    std::vector<std::unique_ptr<IObserver>> m_vecOsdObs;

    CLinkage m_linkage;
    CPoolConfig* m_pPoolConfig{nullptr};

private:
    typedef struct {
        AX_BOOL bInited;
        std::string strName;
        std::function<AX_S32(AX_VOID)> Init;
        std::function<AX_S32(AX_VOID)> DeInit;
    } SYS_MOD_T;
    std::vector<SYS_MOD_T> m_arrMods;
    AX_S32 m_nScenario{0};
    std::mutex m_muxWebOperation;
};
