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
#include "AudioEncoder.hpp"
#include "AudioAedAlgo.hpp"
#include "DetectResult.hpp"
#include "IObserver.h"
#include "IvesResult.hpp"
#include "OptionHelper.h"
#include "PrintHelper.h"
#include "WebOptionHelper.h"
#include "WebServer.h"

#define WEB_OBS "WEB_OBS"

class CWebObserver : public IObserver {
public:
    CWebObserver(CWebServer* pSink) : m_pSink(pSink){};
    virtual ~CWebObserver(AX_VOID) = default;

public:
    AX_BOOL IsSame(AX_U32 nGrp, AX_U32 nChn) const {
        return (m_nGroup == nGrp && m_nChannel == nChn) ? AX_TRUE : AX_FALSE;
    }

public:
    AX_BOOL OnRecvData(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, AX_VOID* pData) override {
        if (!m_pSink) {
            return AX_TRUE;
        }

        if (E_OBS_TARGET_TYPE_VENC == eTarget) {
            AX_VENC_PACK_T* pVencPack = &((AX_VENC_STREAM_T*)pData)->stPack;
            if (nullptr == pVencPack->pu8Addr || 0 == pVencPack->u32Len) {
                LOG_M_E(WEB_OBS, "Invalid H264 data(chn=%d, buff=0x%08X, len=%d).", nChn, pVencPack->pu8Addr, pVencPack->u32Len);
                return AX_FALSE;
            }

            CWebOptionHelper::GetInstance()->StatVencOutBytes(nGrp, nChn, pVencPack->u32Len);
            m_pSink->SendPreviewData(nChn, pVencPack);
        } else if (E_OBS_TARGET_TYPE_JENC == eTarget) {
            AX_VENC_PACK_T* pVencPack = &((AX_VENC_STREAM_T*)pData)->stPack;
            if (nullptr == pVencPack->pu8Addr || 0 == pVencPack->u32Len) {
                LOG_M_E(WEB_OBS, "Invalid Jpeg data(chn=%d, buff=0x%08X, len=%d).", nChn, pVencPack->pu8Addr, pVencPack->u32Len);
                return AX_FALSE;
            }

            JPEG_DATA_INFO_T tJpegInfo;
            tJpegInfo.tCaptureInfo.tHeaderInfo.nSnsSrc = nGrp;
            tJpegInfo.tCaptureInfo.tHeaderInfo.nChannel = nChn;
            tJpegInfo.tCaptureInfo.tHeaderInfo.nWidth = 3840;
            tJpegInfo.tCaptureInfo.tHeaderInfo.nHeight = 2160;

            m_pSink->SendCaptureData(nGrp, nChn, (AX_U8*)pVencPack->pu8Addr, pVencPack->u32Len, 0, AX_TRUE, &tJpegInfo);
        } else if (E_OBS_TARGET_TYPE_DETECT == eTarget) {
            DETECT_RESULT_T* rlt = (DETECT_RESULT_T*)pData;

            AX_U32 nCount[AX_APP_ALGO_HVCFP_TYPE_BUTT] = {rlt->nBodyCount, rlt->nVehicleCount, rlt->nCycleCount, rlt->nFaceCount,
                                                          rlt->nPlateCount};
            AX_APP_ALGO_HVCFP_ITEM_PTR pItems[AX_APP_ALGO_HVCFP_TYPE_BUTT] = {rlt->stBodys, rlt->stVehicles, rlt->stCycles, rlt->stFaces,
                                                                              rlt->stPlates};

            std::vector<AX_IVPS_RGN_POLYGON_T> stRgn;
            for (AX_U32 i = 0; i < AX_APP_ALGO_HVCFP_TYPE_BUTT; ++i) {
                for (AX_U32 j = 0; j < nCount[i]; ++j) {
                    if (pItems[i][j].eTrackStatus == AX_APP_ALGO_TRACK_STATUS_SELECT) {
                        if (pItems[i][j].stImg.bExist && pItems[i][j].stImg.pData) {
                            JPEG_DATA_INFO_T tJpegInfo;
                            tJpegInfo.eType = (JPEG_TYPE_E)i;
                            if (tJpegInfo.eType == JPEG_TYPE_PLATE) {
                                strncpy(tJpegInfo.tPlateInfo.szNum, pItems[i][j].stAttr.stPlateAttr.strPlateCode,
                                        sizeof(tJpegInfo.tPlateInfo.szNum) - 1);
                                strncpy(tJpegInfo.tPlateInfo.szColor,
                                        AX_APP_ALGO_GET_PLATE_COLOR(pItems[i][j].stAttr.stPlateAttr.ePlateColor).c_str(),
                                        sizeof(tJpegInfo.tPlateInfo.szColor) - 1);
                            } else if (tJpegInfo.eType == JPEG_TYPE_FACE) {
                                tJpegInfo.tFaceInfo.nGender = pItems[i][j].stAttr.stFaceAttr.nGender;
                                tJpegInfo.tFaceInfo.nAge = pItems[i][j].stAttr.stFaceAttr.nAge;
                                strncpy(tJpegInfo.tFaceInfo.szMask,
                                        AX_APP_ALGO_GET_RESPIRATOR(pItems[i][j].stAttr.stFaceAttr.eRespirator).c_str(),
                                        sizeof(tJpegInfo.tFaceInfo.szMask) - 1);
                                strncpy(tJpegInfo.tFaceInfo.szInfo, "unknown", sizeof(tJpegInfo.tFaceInfo.szInfo) - 1);
                            } else {
                                tJpegInfo.tCaptureInfo.tHeaderInfo.nSnsSrc = nGrp;
                                tJpegInfo.tCaptureInfo.tHeaderInfo.nChannel = 0;
                                tJpegInfo.tCaptureInfo.tHeaderInfo.nWidth = pItems[i][j].stImg.nWidth;
                                tJpegInfo.tCaptureInfo.tHeaderInfo.nHeight = pItems[i][j].stImg.nHeight;
                            }

                            m_pSink->SendPushImgData(nGrp, nChn, (AX_U8*)pItems[i][j].stImg.pData, pItems[i][j].stImg.nDataSize, 0, AX_TRUE,
                                                     &tJpegInfo);
                        }

                        if (pItems[i][j].stPanoramaImg.bExist && pItems[i][j].stPanoramaImg.pData) {
                            JPEG_DATA_INFO_T tJpegInfo;
                            tJpegInfo.eType = JPEG_TYPE_CAPTURE;
                            tJpegInfo.tCaptureInfo.tHeaderInfo.nSnsSrc = nGrp;
                            tJpegInfo.tCaptureInfo.tHeaderInfo.nChannel = 0;
                            tJpegInfo.tCaptureInfo.tHeaderInfo.nWidth = pItems[i][j].stPanoramaImg.nWidth;
                            tJpegInfo.tCaptureInfo.tHeaderInfo.nHeight = pItems[i][j].stPanoramaImg.nHeight;

                            m_pSink->SendPushImgData(nGrp, nChn, (AX_U8*)pItems[i][j].stPanoramaImg.pData,
                                                     pItems[i][j].stPanoramaImg.nDataSize, 0, AX_TRUE, &tJpegInfo);
                        }
                    }
                }
            }
        } else if (E_OBS_TARGET_TYPE_AENC == eTarget) {
            AX_U32 nBitRate = ((AENC_STREAM_T*)pData)->nBitRate;
            AX_PAYLOAD_TYPE_E eType = ((AENC_STREAM_T*)pData)->eType;
            AX_AUDIO_STREAM_T* pAencPack = &((AENC_STREAM_T*)pData)->stPack;
            if (nullptr == pAencPack->pStream || 0 == pAencPack->u32Len) {
                LOG_M_E(WEB_OBS, "Invalid Aenc data(chn=%d, buff=0x%08X, len=%d, type=%d, bitrate=%d).", nChn, pAencPack->pStream,
                        pAencPack->u32Len, eType, nBitRate);
                return AX_FALSE;
            }

            // TODO: check audio type, we can read type from audio data.
            m_pSink->SendAudioData(nChn, pAencPack->pStream, pAencPack->u32Len, pAencPack->u64TimeStamp);
        } else if (E_OBS_TARGET_TYPE_EVENT == eTarget) {
            IVES_RESULT_T* rlt = (IVES_RESULT_T*)pData;

            for (AX_U32 i = 0; i < rlt->nMdCount; i++) {
                WEB_EVENTS_DATA_T stEvent;

                stEvent.eType = E_WEB_EVENTS_TYPE_MD;
                stEvent.nReserved = nGrp;
                stEvent.tMD.nAreaID = i;
                m_pSink->SendEventsData(&stEvent);
            }

            for (AX_U32 i = 0; i < rlt->nOdCount; i++) {
                WEB_EVENTS_DATA_T stEvent;

                stEvent.eType = E_WEB_EVENTS_TYPE_OD;
                stEvent.nReserved = nGrp;
                stEvent.tOD.nAreaID = i;
                m_pSink->SendEventsData(&stEvent);
            }

            for (AX_U32 i = 0; i < rlt->nScdCount; i++) {
                WEB_EVENTS_DATA_T stEvent;

                stEvent.eType = E_WEB_EVENTS_TYPE_SCD;
                stEvent.nReserved = nGrp;
                stEvent.tSCD.nAreaID = i;
                m_pSink->SendEventsData(&stEvent);
            }
        } else if (E_OBS_TARGET_TYPE_AED == eTarget) {
            AED_ALGO_RESULT_PTR rlt = (AED_ALGO_RESULT_PTR)pData;
            WEB_EVENTS_DATA_T stEvent;

            stEvent.eType = E_WEB_EVENTS_TYPE_AED;
            stEvent.nReserved = nGrp;
            stEvent.tAED.nDb = (AX_S32)rlt->fDb;
            m_pSink->SendEventsData(&stEvent);
        }

        return AX_TRUE;
    }

    AX_BOOL OnRegisterObserver(OBS_TARGET_TYPE_E eTarget, AX_U32 nGrp, AX_U32 nChn, OBS_TRANS_ATTR_PTR pParams) override {
        if (nullptr == pParams) {
            return AX_FALSE;
        }
        m_nGroup = nGrp;
        m_nChannel = nChn;
        AX_CHAR szName[64] = {0};
        if (E_OBS_TARGET_TYPE_VENC == eTarget) {
            AX_U32 nWidth = pParams->nWidth;
            AX_U32 nHeight = pParams->nHeight;
            AX_U32 nBuffSize = COptionHelper::GetInstance()->GetWebVencRingBufSize(nWidth, nHeight);
            AX_U32 nCount = COptionHelper::GetInstance()->GetWebVencRingBufCount(nWidth, nHeight);
            sprintf(szName, "VENC_CH%d", nChn);
            return m_pSink->RequestRingbuf(nChn, nBuffSize, nCount, szName);
        } else if (E_OBS_TARGET_TYPE_JENC == eTarget) {
            AX_U32 nWidth = pParams->nWidth;
            AX_U32 nHeight = pParams->nHeight;
            AX_F32 fRatio = COptionHelper::GetInstance()->GetJencOutBuffRatio();
            AX_U32 nBuffSize = nWidth * nHeight * 3 / 2 * fRatio;
            nBuffSize += sizeof(JpegHead);
            sprintf(szName, "JENC_CH%d", nChn);

            return m_pSink->RequestRingbuf(nChn, nBuffSize, COptionHelper::GetInstance()->GetWebJencRingBufCount(), szName);
        } else if (E_OBS_TARGET_TYPE_AENC == eTarget) {
            AX_U32 nBuffSize = COptionHelper::GetInstance()->GetAencOutFrmSize();
            sprintf(szName, "AENC_CH%d", nChn);
            return m_pSink->RequestRingbuf(m_pSink->GetAencChannel(), nBuffSize, COptionHelper::GetInstance()->GetWebAencRingBufCount(),
                                           szName);
        } else if (E_OBS_TARGET_TYPE_DETECT == eTarget) {
            // nJencChn: Unique capture channel from webserver
            AX_U32 nJencChn = m_pSink->GetCaptureChannel();
            AX_U32 nWidth = pParams->nWidth;
            AX_U32 nHeight = pParams->nHeight;
            AX_F32 fRatio = COptionHelper::GetInstance()->GetJencOutBuffRatio();
            AX_U32 nBuffSize = nWidth * nHeight * 3 / 2 * fRatio;
            nBuffSize += sizeof(JpegHead);
            sprintf(szName, "JENC_CH%d", nJencChn);

            return m_pSink->RequestRingbuf(nJencChn, nBuffSize, COptionHelper::GetInstance()->GetWebJencRingBufCount(), szName);
        } else if (E_OBS_TARGET_TYPE_EVENT == eTarget) {
            // do nothing
        } else if (E_OBS_TARGET_TYPE_AED == eTarget) {
            // do nothing
        }

        return AX_TRUE;
    }

private:
    CWebServer* m_pSink{nullptr};
    AX_U32 m_nGroup{0};
    AX_U32 m_nChannel{0};
};
