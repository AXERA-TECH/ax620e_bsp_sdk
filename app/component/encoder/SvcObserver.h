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
#include "ax_venc_comm.h"
#include "DetectResult.hpp"
#include "IObserver.h"
#include "VideoEncoder.h"
#include "AlgoOptionHelper.h"

#define SVC_OBS "SVC_OBS"

class CSvcObserver : public IObserver {
public:
CSvcObserver(CVideoEncoder* pSink) : m_pSink(pSink){};
    virtual ~CSvcObserver(AX_VOID) = default;

public:
    AX_BOOL IsSame(AX_U32 nGrp, AX_U32 nChn) const {
        return (m_nGroup == nGrp && m_nChannel == nChn) ? AX_TRUE : AX_FALSE;
    }

public:
    AX_BOOL OnRecvData(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, AX_VOID* pData) override {
        if (!m_pSink) {
            return AX_TRUE;
        }

        if (E_OBS_TARGET_TYPE_DETECT == eTarget) {
            DETECT_RESULT_T* rlt = (DETECT_RESULT_T*)pData;
            const AX_APP_ALGO_SVC_PARAM_T &tSvc = ALGO_SVC_PARAM(rlt->nSnsId);
            CVideoEncoder *vencInst = (CVideoEncoder *)m_pSink;

            if (tSvc.bEnable
                && (rlt->nSnsId == vencInst->GetSensorSrc())
                && (vencInst->GetChnCfg()->ePayloadType == PT_H264
                    || vencInst->GetChnCfg()->ePayloadType == PT_H265)) {
                AX_VENC_SVC_REGION_T tRegion;
                AX_U32 &nRegionCnt = tRegion.u32RectNum;

                memset(&tRegion, 0x00, sizeof(tRegion));

                // pts
                tRegion.u64Pts = rlt->u64Pts;

                // face
                if (tSvc.tQpCfg[AX_APP_ALGO_HVCFP_FACE].bEnable && rlt->nFaceCount > 0) {
                    for (AX_U32 i = 0; i < rlt->nFaceCount; ++i) {
                        if (rlt->stFaces[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_NEW ||
                            rlt->stFaces[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_UPDATE) {
                            tRegion.stRect[nRegionCnt].fX = rlt->stFaces[i].stBox.fX;
                            tRegion.stRect[nRegionCnt].fY = rlt->stFaces[i].stBox.fY;
                            tRegion.stRect[nRegionCnt].fWidth = rlt->stFaces[i].stBox.fW;
                            tRegion.stRect[nRegionCnt].fHeight = rlt->stFaces[i].stBox.fH;
                            tRegion.enRectType[nRegionCnt] = (AX_VENC_SVC_RECT_TYPE_E)AX_APP_ALGO_HVCFP_FACE; // AX_APP_ALGO_SVC_REGION_TYPE3
                            nRegionCnt ++;
                        }
                    }
                }

                // plate
                if (tSvc.tQpCfg[AX_APP_ALGO_HVCFP_PLATE].bEnable && rlt->nPlateCount > 0) {
                    for (AX_U32 i = 0; i < rlt->nPlateCount; ++i) {
                        if (rlt->stPlates[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_NEW ||
                            rlt->stPlates[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_UPDATE) {
                            tRegion.stRect[nRegionCnt].fX = rlt->stPlates[i].stBox.fX;
                            tRegion.stRect[nRegionCnt].fY = rlt->stPlates[i].stBox.fY;
                            tRegion.stRect[nRegionCnt].fWidth = rlt->stPlates[i].stBox.fW;
                            tRegion.stRect[nRegionCnt].fHeight = rlt->stPlates[i].stBox.fH;
                            tRegion.enRectType[nRegionCnt] = (AX_VENC_SVC_RECT_TYPE_E)AX_APP_ALGO_HVCFP_PLATE; // AX_APP_ALGO_SVC_REGION_TYPE4
                            nRegionCnt ++;
                        }
                    }
                }

                // body
                if (tSvc.tQpCfg[AX_APP_ALGO_HVCFP_BODY].bEnable && rlt->nBodyCount > 0) {
                    for (AX_U32 i = 0; i < rlt->nBodyCount; ++i) {
                        if (rlt->stBodys[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_NEW ||
                            rlt->stBodys[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_UPDATE) {
                            tRegion.stRect[nRegionCnt].fX = rlt->stBodys[i].stBox.fX;
                            tRegion.stRect[nRegionCnt].fY = rlt->stBodys[i].stBox.fY;
                            tRegion.stRect[nRegionCnt].fWidth = rlt->stBodys[i].stBox.fW;
                            tRegion.stRect[nRegionCnt].fHeight = rlt->stBodys[i].stBox.fH;
                            tRegion.enRectType[nRegionCnt] = (AX_VENC_SVC_RECT_TYPE_E)AX_APP_ALGO_HVCFP_BODY; // AX_APP_ALGO_SVC_REGION_TYPE0
                            nRegionCnt ++;
                        }
                    }
                }

                // vehicle
                if (tSvc.tQpCfg[AX_APP_ALGO_HVCFP_VEHICLE].bEnable && rlt->nVehicleCount > 0) {
                    for (AX_U32 i = 0; i < rlt->nVehicleCount; ++i) {
                        if (rlt->stVehicles[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_NEW ||
                            rlt->stVehicles[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_UPDATE) {
                            tRegion.stRect[nRegionCnt].fX = rlt->stVehicles[i].stBox.fX;
                            tRegion.stRect[nRegionCnt].fY = rlt->stVehicles[i].stBox.fY;
                            tRegion.stRect[nRegionCnt].fWidth = rlt->stVehicles[i].stBox.fW;
                            tRegion.stRect[nRegionCnt].fHeight = rlt->stVehicles[i].stBox.fH;
                            tRegion.enRectType[nRegionCnt] = (AX_VENC_SVC_RECT_TYPE_E)AX_APP_ALGO_HVCFP_VEHICLE; // AX_APP_ALGO_SVC_REGION_TYPE1
                            nRegionCnt ++;
                        }
                    }
                }

                // cycle
                if (tSvc.tQpCfg[AX_APP_ALGO_HVCFP_CYCLE].bEnable && rlt->nCycleCount > 0) {
                    for (AX_U32 i = 0; i < rlt->nCycleCount; ++i) {
                        if (rlt->stCycles[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_NEW ||
                            rlt->stCycles[i].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_UPDATE) {
                            tRegion.stRect[nRegionCnt].fX = rlt->stCycles[i].stBox.fX;
                            tRegion.stRect[nRegionCnt].fY = rlt->stCycles[i].stBox.fY;
                            tRegion.stRect[nRegionCnt].fWidth = rlt->stCycles[i].stBox.fW;
                            tRegion.stRect[nRegionCnt].fHeight = rlt->stCycles[i].stBox.fH;
                            tRegion.enRectType[nRegionCnt] = (AX_VENC_SVC_RECT_TYPE_E)AX_APP_ALGO_HVCFP_CYCLE; // AX_APP_ALGO_SVC_REGION_TYPE2
                            nRegionCnt ++;
                        }
                    }
                }

                vencInst->UpdateSvcRegion(tRegion);
            }
        }

        return AX_TRUE;
    }

    AX_BOOL OnRegisterObserver(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, OBS_TRANS_ATTR_PTR pParams) override {
        if (nullptr == pParams) {
            return AX_FALSE;
        }
        m_nGroup = nGrp;
        m_nChannel = nChn;

        if (E_OBS_TARGET_TYPE_DETECT == eTarget) {
            // do nothing
        }

        return AX_TRUE;
    }

private:
    CVideoEncoder* m_pSink{nullptr};
    AX_U32 m_nGroup{0};
    AX_U32 m_nChannel{0};
};
