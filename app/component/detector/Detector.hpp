/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#pragma once
#include <vector>
#include <mutex>
#include "AXAlgo.hpp"
#include "AXFrame.hpp"
#include "AXLockQ.hpp"
#include "AXResource.hpp"
#include "AXThread.hpp"
#include "IObserver.h"
#include "WebServer.h"
#include "ax_skel_api.h"
#include "DetectResult.hpp"
#include "SensorMgr.h"

#define MAX_DETECTOR_GROUP_NUM (2)
#define MAX_DETECTOR_PRIVATE_DATA_NUM (8)

typedef struct DETECTOR_ATTR_S {
    AX_U8 nGrpCount{0};
    AX_S32 nGrp{0};
    std::string strModelPath;
    AX_SKEL_PPL_E ePPL{AX_SKEL_PPL_MAX};
    AX_U32 nFrameDepth;
    AX_U32 nWidth{0};
    AX_U32 nHeight{0};
    AX_F32 fFramerate{0};
    AX_S8 nSnsId[MAX_DETECTOR_GROUP_NUM]{-1};
} DETECTOR_ATTR_T;

typedef struct {
    AX_U64 nSeqNum{0};
    AX_S32 nGrpId{0};
    AX_S32 nChnId{0};
    AX_S8 nSnsId{0};
    AX_S8 nRefCnt{0};
} SKEL_FRAME_PRIVATE_DATA_T;

/**
 * @brief
 *
 */
class CDetector {
public:
    CDetector(AX_VOID) = default;
    virtual ~CDetector(AX_VOID) = default;

    AX_BOOL Init(const DETECTOR_ATTR_T& stAttr);
    AX_BOOL DeInit(AX_VOID);

    AX_BOOL Start(AX_VOID);
    AX_BOOL Stop(AX_VOID);

    AX_VOID BindSensorMgr(CSensorMgr* pSensorMgr) {
        m_pSensorMgr = pSensorMgr;
    };

    AX_BOOL SendFrame(AX_U32 nGrp, CAXFrame* axFrame);
    AX_S32 CheckCapacity(AX_S32 nTimeOut);

    AX_VOID RegObserver(IObserver* pObserver);
    AX_VOID UnregObserver(IObserver* pObserver);
    DETECTOR_ATTR_T* GetDetectorCfg() {
        return &m_stAttr;
    };

    AX_VOID Enable(AX_U8 nSnsId, AX_BOOL bEnable = AX_TRUE);

    SKEL_FRAME_PRIVATE_DATA_T* GetSkelPrivateData(AX_VOID) {
        std::lock_guard<std::mutex> lck(m_mtxSkelData);
        for (AX_U32 i = 0; i < MAX_DETECTOR_PRIVATE_DATA_NUM; i++) {
            if (m_skelData[i].nRefCnt == 0) {
                m_skelData[i].nRefCnt = 1;
                return &m_skelData[i];
            }
        }

        return nullptr;
    }

    AX_VOID ReleaseSkelPrivateData(SKEL_FRAME_PRIVATE_DATA_T* pData) {
        if (pData) {
            std::lock_guard<std::mutex> lck(m_mtxSkelData);
            pData->nRefCnt = 0;
        }
    }

    AX_VOID NotifyAll(AX_U32 nSnsId, AX_U32 nChn, AX_VOID* pStream);

    AX_S32 SetSkelPushMode(AX_U32 nSnsId, AI_PUSH_STATEGY_T& stStrategy);

    AX_BOOL SetRoi(AX_U32 nSnsId, const AX_APP_ALGO_ROI_CONFIG_T& stRoi, AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetPushStrategy(AX_U32 nSnsId, const AX_APP_ALGO_PUSH_STRATEGY_T& stPushStrategy, AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetObjectFilter(AX_U32 nSnsId, AX_APP_ALGO_HVCFP_TYPE_E eType, const AX_APP_ALGO_HVCFP_FILTER_CONFIG_T& stObjectFliter,
                            AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetTrackSize(AX_U32 nSnsId, const AX_APP_ALGO_TRACK_SIZE_T& stTrackSize, AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetPanorama(AX_U32 nSnsId, const AX_APP_ALGO_PANORAMA_T& stPanorama, AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetCropEncoderQpLevel(AX_U32 nSnsId, const AX_U32& nCropEncoderQpLevel, AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetCropThreshold(AX_U32 nSnsId, AX_APP_ALGO_HVCFP_TYPE_E eType, const AX_APP_ALGO_CROP_THRESHOLD_CONFIG_T& stCropThreshold,
                             AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetPushFilter(AX_U32 nSnsId, AX_APP_ALGO_HVCFP_TYPE_E eType, const AX_APP_ALGO_PUSH_FILTER_CONFIG_T& stPushFliter,
                          AX_BOOL bUpdateParam = AX_FALSE);
    AX_BOOL SetConfig(AX_S32 nSnsId, const AX_APP_ALGO_HVCFP_PARAM_T& stConfig, AX_BOOL bUpdateParam = AX_FALSE);

    AX_VOID UpdateAeRoi(AX_U32 nSnsId, const DETECT_RESULT_T& hvcfp);

    AX_BOOL SetAeRoiAttr(AX_U32 nSnsId, const AX_APP_ALGO_AE_ROI_CONFIG_T stAeRoiConfig[AX_APP_ALGO_HVCFP_TYPE_BUTT], AX_BOOL bUpdateParam = AX_FALSE);


protected:
    AX_VOID RunDetect(AX_VOID* pArg);
    AX_VOID ClearQueue(AX_S32 nGrp);

private:
    AX_VOID RestoreAeRoi(AX_U32 nSnsId);

    AX_VOID GetAeRoi(AX_U32 nSnsId, AX_U32 nItemSize,
                        const AX_APP_ALGO_HVCFP_ITEM_PTR stItems,
                        const AX_APP_ALGO_AE_ROI_CONFIG_T& stAeRoiConfig,
                        std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem);

protected:
    CAXLockQ<CAXFrame*>* m_arrFrameQ{nullptr};
    DETECTOR_ATTR_T m_stAttr;
    CAXThread m_DetectThread;
    AX_SKEL_HANDLE m_Skel{NULL};

private:
    std::vector<IObserver*> m_vecObserver;
    AX_BOOL m_initState{AX_FALSE};
    AX_BOOL m_arrSnsAiEnable[AX_APP_ALGO_SNS_MAX]{AX_TRUE, AX_TRUE};
    SKEL_FRAME_PRIVATE_DATA_T m_skelData[MAX_DETECTOR_PRIVATE_DATA_NUM];
    std::mutex  m_mtxSkelData;
    CSensorMgr* m_pSensorMgr{nullptr};
};
