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
#include "Avs.h"
#ifdef MP4ENC_SUPPORT
#include "Mpeg4Encoder.h"
#endif

#include "TestSuite.h"

class CPanoBuilder : public IPPLBuilder {
public:
    CPanoBuilder(AX_VOID) = default;
    ~CPanoBuilder(AX_VOID) = default;

public:
    virtual AX_BOOL Init(AX_VOID);
    virtual AX_BOOL Deinit(AX_VOID);
    virtual AX_BOOL Construct(AX_VOID);
    virtual AX_BOOL Destroy(AX_VOID);
    virtual AX_BOOL Start(AX_VOID);
    virtual AX_BOOL Stop(AX_VOID);

    virtual AX_BOOL BindPPLConfig(IPPLConfig* pPPLConfig);

    virtual AX_BOOL BindTestSuite(CTestSuite* pTestSuite);

#ifndef SLT
    /* Web relative interfaces */
    virtual AX_BOOL ProcessWebOprs(WEB_REQUEST_TYPE_E eReqType, const AX_VOID* pJsonReq, AX_VOID** pResult = nullptr) override;
    virtual AX_BOOL ProcessTestSuiteOpers(WEB_REQ_OPERATION_T& tOperation) override;
#endif  // SLT

static AX_VOID CalibrateDone(AX_S32 result, AX_AVSCALI_AVS_PARAMS_T* pAVSParams, AX_AVSCALI_3A_SYNC_RATIO_T* pSyncRatio, AX_VOID* pPrivData);

protected:
    virtual AX_BOOL InitSysMods(AX_VOID);
    virtual AX_BOOL DeInitSysMods(AX_VOID);
    virtual AX_BOOL InitIvps();
    virtual AX_BOOL InitVenc();
    virtual AX_BOOL InitJenc();
    virtual AX_BOOL InitCollector();
    virtual AX_VOID PostStartProcess(AX_VOID);

    AX_BOOL InitSensor();

    AX_BOOL InitDetector();
    AX_BOOL InitCapture();

    AX_S32 APP_LOG_Init(AX_VOID);
    AX_S32 APP_LOG_DeInit(AX_VOID);
    AX_S32 APP_SYS_Init(AX_VOID);
    AX_S32 APP_SYS_DeInit(AX_VOID);
    AX_S32 APP_VENC_Init(AX_VOID);
    AX_S32 APP_VENC_DeInit(AX_VOID);
    AX_S32 APP_VDEC_Init(AX_VOID);
    AX_S32 APP_VDEC_DeInit(AX_VOID);
    AX_S32 APP_NPU_Init(AX_VOID);
    AX_S32 APP_NPU_DeInit(AX_VOID);

#ifndef SLT
    AX_S32 APP_ACAP_Init(AX_VOID);
    AX_S32 APP_ACAP_DeInit(AX_VOID);
    AX_S32 APP_APLAY_Init(AX_VOID);
    AX_S32 APP_APLAY_DeInit(AX_VOID);
#endif  // SLT

    AX_BOOL InitPoolConfig();
    AX_BOOL InitAvs();

    AX_BOOL GetRelationsBySrcMod(IPC_MOD_INFO_T& tSrcMod, vector<IPC_MOD_RELATIONSHIP_T>& vecOutRelations,
                                 AX_BOOL bIgnoreChn = AX_FALSE) const;
    AX_BOOL GetRelationsByDstMod(IPC_MOD_INFO_T& tDstMod, vector<IPC_MOD_RELATIONSHIP_T>& vecOutRelations,
                                 AX_BOOL bIgnoreChn = AX_FALSE) const;
    AX_BOOL GetPrecedingMod(const IPC_MOD_INFO_T& tDstMod, IPC_MOD_INFO_T& tPrecedingMod);

private:
#ifndef SLT
    AX_BOOL DispatchOpr(WEB_REQ_OPERATION_T& tOperation, AX_VOID** pResult /*= nullptr*/);
    AX_VOID SortOperations(vector<WEB_REQ_OPERATION_T>& vecWebRequests);
    AX_BOOL InitAudio();
#endif  // SLT

    AX_BOOL ConstructIves();
    AX_BOOL InitIves();
    AX_BOOL InitDummyEnc(AX_VOID);
    AX_VOID InitIVPSMaxResolutionChnInfo();
    AX_S32  APP_VIN_Stitch_Attr_Init();
    AX_S32  APP_VIN_Stitch_Attr_DeInit();

    AX_BOOL UpdateRotation(AX_U8 nSnsID, AX_U8 nRotation);

    AX_BOOL IsNeedUpdate(AX_U8 nGrp, AX_U8 nChn, AX_BOOL bIgnorChn = AX_FALSE);
    AX_BOOL GetEncoder(AX_VOID **ppEncoder, AX_BOOL *pIsJenc, AX_S32 encoderChn);
    AX_VOID UpdateEncoderResolution(AX_VOID *pEncoder, AX_BOOL bJenc, AX_S32 nSrcGrp, AX_S32 srcChn);

    template<typename T1, typename T2>
    AX_VOID UpdateEncoderResolution(T1* pEncoder, T2* pConfig, AX_S32 nSrcGrp, AX_S32 srcChn);

    AX_BOOL UpdateIVPSResolution(const PPL_MOD_INFO_T tSrcMod, const AX_U32 newWidth, const AX_U32 newHeight, AX_BOOL bIgnoreChn);

public:
    CSensorMgr m_mgrSensor;
    vector<CIVPSGrpStage*> m_vecIvpsInstance;
    vector<CVideoEncoder*> m_vecVencInstance;
    vector<CCollector*> m_vecCollectorInstance;
    vector<CIVESStage*> m_vecIvesInstance;
#ifdef MP4ENC_SUPPORT
    vector<CMPEG4Encoder*> m_vecMpeg4Instance;
#endif
    vector<CDummyEncoder*> m_vecDummyEncInstance;
    vector<CJpegEncoder*> m_vecJencInstance;
    CDetector m_detector;
    CCapture m_capture;
    CAvs m_avs;

    std::vector<std::unique_ptr<IObserver>> m_vecRtspObs;
    std::vector<std::unique_ptr<IObserver>> m_vecWebObs;
    std::vector<std::unique_ptr<IObserver>> m_vecCollectorObs;
    std::vector<std::unique_ptr<IObserver>> m_vecDetectorObs;
    std::vector<std::unique_ptr<IObserver>> m_vecIvesObs;
    std::vector<std::unique_ptr<IObserver>> m_vecIvpsObs;
    std::vector<std::unique_ptr<IObserver>> m_vecMpeg4Obs;
    std::vector<std::unique_ptr<IObserver>> m_vecCaptureObs;
    std::vector<std::unique_ptr<IObserver>> m_vecOsdObs;
    std::vector<std::unique_ptr<IObserver>> m_vecDummyEncObs;
    std::vector<std::unique_ptr<IObserver>> m_vecVencObs;
    std::vector<std::unique_ptr<IObserver>> m_vecJencObs;

    CLinkage m_linkage;
    CPoolConfig* m_pPoolConfig{nullptr};

    IPPLConfig* m_pPPLConfig{nullptr};

    CTestSuite* m_pTestSuite{nullptr};
    AX_S32 m_nScenario{0};
    typedef struct {
        AX_BOOL bInited;
        std::string strName;
        std::function<AX_S32(AX_VOID)> Init;
        std::function<AX_S32(AX_VOID)> DeInit;
    } SYS_MOD_T;
    std::vector<SYS_MOD_T> m_arrMods;

private:
    std::mutex m_muxWebOperation;
    std::multimap<AX_U8, AX_U8> m_mmapIVPSMaxResolutionChn;
};
