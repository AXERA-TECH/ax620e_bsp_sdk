/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include "OSDHelper.h"
#include <sys/prctl.h>
#include <chrono>
#include <map>
#include "AXFrame.hpp"
#include "AXThread.hpp"
#include "AppLogApi.h"
#include "CmdLineParser.h"
#include "CommonUtils.hpp"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include "IvpsOptionHelper.h"
#include "OptionHelper.h"
#include "OsdOptionHelper.h"
#include "SensorOptionHelper.h"
#include "unicode.h"

#define OSD "OSD"

COSDHelper::COSDHelper() {
}

AX_BOOL COSDHelper::StartOSD(CIVPSGrpStage* pIvpsInstance) {
    LOG_MM_I(OSD, "+++");
    AX_S32 nRet = AX_SUCCESS;
    m_pIvpsGrpInstance = pIvpsInstance;
    IVPS_GROUP_CFG_T* pGrpConfig = m_pIvpsGrpInstance->GetGrpCfg();
    AX_U8 nRgnIndex = 0;
    IVPS_GRP_T* pGrpAttr = m_pIvpsGrpInstance->GetGrpPPLAttr();

    for (AX_U32 nChn = 0; nChn < pGrpConfig->nGrpChnNum; nChn++) {
        AX_U8 nChnFilter = nChn + 1;
        if (AX_TRUE != pGrpAttr->tPipelineAttr.tFilter[nChnFilter][APP_OSD_CHANNEL_FILTER_1].bEngage) {
            /* FIXME: As OSD applies on channel filter 1 now, check engine of this filter whether configured always. */
            LOG_MM_W(OSD, "[%d][%d] Engine not configured. Please check the engine_filter_3 configuration in ivps.json.", pGrpConfig->nGrp,
                     nChn);
            continue;
        }
        std::vector<OSD_CFG_T> vecOsdCfg;
        CWebOptionHelper::GetInstance()->GetOsdConfig(pGrpConfig->nSnsSrc, pGrpConfig->nGrp, nChn, vecOsdCfg);
        for (AX_U32 i = 0; i < vecOsdCfg.size(); i++) {
            OSD_CFG_T& tCfg = vecOsdCfg[i];
            IVPS_RGN_HANDLE hRgn = AX_IVPS_RGN_Create();
            if (AX_IVPS_INVALID_REGION_HANDLE != hRgn) {
                AX_U32 nIvpsGrp = pGrpConfig->nGrp;
                AX_S32 nFilter;
                if (tCfg.eType == OSD_TYPE_PRIVACY) {
                    nFilter = APP_OSD_GROUP_FILTER_1;   // must be grop filter 1 for gdc online vpp,
                } else {
                    nFilter = ((nChn + 1) << 4) + APP_OSD_CHANNEL_FILTER_1;
                }
                nRet = AX_IVPS_RGN_AttachToFilter(hRgn, nIvpsGrp, nFilter);
                if (AX_SUCCESS != nRet) {
                    LOG_MM_E(OSD, "[%d] AX_IVPS_RGN_AttachToFilter(Grp: %d, Filter: 0x%x, Handle: %d) failed, ret=0x%x", nChn, nIvpsGrp,
                             nFilter, hRgn, nRet);
                    AX_IVPS_RGN_Destroy(hRgn);
                    break;
                }
                m_arrRgnThreadParam[nRgnIndex].nGroup = nIvpsGrp;
                m_arrRgnThreadParam[nRgnIndex].nChn = nChn;
                m_arrRgnThreadParam[nRgnIndex].hRgn = hRgn;
                m_arrRgnThreadParam[nRgnIndex].nFilter = nFilter;
                m_arrRgnThreadParam[nRgnIndex].tOsdCfg = tCfg;
                UpdateOSD(&m_arrRgnThreadParam[nRgnIndex]);
                nRgnIndex++;
            }

            tCfg.hRgn = (AX_S32)hRgn;
        }

        // update
        CWebOptionHelper::GetInstance()->SetOsdConfig(pGrpConfig->nSnsSrc, pGrpConfig->nGrp, nChn, vecOsdCfg);
    }
    m_nRgnCount = nRgnIndex;

    AX_CHAR threadName[32];
    sprintf(threadName, "APP_RGN_UPDATE%d_%d", pGrpConfig->nSnsSrc, pGrpConfig->nGrp);
    m_updateThread.Start(std::bind(&COSDHelper::PerformUpdateOSD, this), nullptr, threadName);

    return AX_TRUE;
}

AX_BOOL COSDHelper::UpdateOSD(OSD_REGION_PARAM_T* pThreadParam) {
    if (nullptr == pThreadParam) {
        return AX_FALSE;
    }
    AX_CHAR threadName[32];
    switch (pThreadParam->tOsdCfg.eType) {
        case OSD_TYPE_TIME: {
            sprintf(threadName, "APP_RGN_TIME%d_%d", pThreadParam->nGroup, pThreadParam->nChn);
            if (!pThreadParam->m_EventThread.Start(std::bind(&COSDHelper::TimeThreadFunc, this, pThreadParam), nullptr, threadName)) {
                LOG_MM_E(OSD, "start RgnThreadFunc  failed!");
                AX_IVPS_RGN_Destroy(pThreadParam->hRgn);
                break;
            }
            break;
        };
        case OSD_TYPE_PICTURE: {
            UpdateOSDPic(pThreadParam);
            break;
        };
        case OSD_TYPE_STRING_CHANNEL:
        case OSD_TYPE_STRING_LOCATION: {
            UpdateOSDStr(pThreadParam);
            break;
        };
        case OSD_TYPE_PRIVACY: {
            UpdateOSDPri(pThreadParam);
            break;
        };
        case OSD_TYPE_RECT: {
            sprintf(threadName, "APP_RGN_RECT%d_%d", pThreadParam->nGroup, pThreadParam->nChn);
            if (!pThreadParam->m_EventThread.Start(std::bind(&COSDHelper::RectThreadFunc, this, pThreadParam), nullptr, threadName)) {
                LOG_MM_E(OSD, "start RgnThreadFunc  failed!");
                AX_IVPS_RGN_Destroy(pThreadParam->hRgn);
                break;
            }
            break;
        }
        default: {
            LOG_MM_E(OSD, "Unknown OSD type: %d", pThreadParam->tOsdCfg.eType);
            break;
        }
    }

    return AX_TRUE;
}

AX_VOID COSDHelper::TimeThreadFunc(OSD_REGION_PARAM_T* pThreadParam) {
    AX_U32 nIvpsChn = pThreadParam->nChn;
    while (!pThreadParam->bExit) {
        if (!m_pIvpsGrpInstance->GetChannelState(pThreadParam->nChn)) {
            for (int i = 0; i < 25 && !pThreadParam->bExit; i++) {
                CElapsedTimer::mSleep(20);
            }
            continue;
        }

        AX_IVPS_RGN_DISP_GROUP_T tDisp;
        AX_U16* pArgbData = nullptr;

        memset(&tDisp, 0, sizeof(AX_IVPS_RGN_DISP_GROUP_T));
        AX_U32 nRGB = pThreadParam->tOsdCfg.tTimeAttr.nColor;

        tDisp.nNum = 1;
        tDisp.tChnAttr.nAlpha = 255;
        tDisp.tChnAttr.nZindex = pThreadParam->tOsdCfg.nZIndex;
        tDisp.tChnAttr.bSingleCanvas = AX_FALSE;

        COSDHandler* pOsdHandle = m_osdWrapper.NewInstance();
        if (nullptr == pOsdHandle) {
            LOG_MM_E(OSD, "Get osd handle failed.");
            break;
        }

        static AX_CHAR strTtfFile[128] = {0};
        sprintf(strTtfFile, "%s/GB2312.ttf", GetResPath().c_str());

        if (AX_FALSE == m_osdWrapper.InitHandler(pOsdHandle, strTtfFile)) {
            LOG_MM_E(OSD, "AX_OSDInitHandler failed, ttf: %s.", strTtfFile);
            m_osdWrapper.ReleaseInstance(&pOsdHandle);
            break;
        }
        wchar_t wszOsdDate[MAX_OSD_TIME_CHAR_LEN] = {0};

        memset(&wszOsdDate[0], 0, sizeof(wchar_t) * MAX_OSD_TIME_CHAR_LEN);

        AX_S32 nCharLen = 0;
        if (nullptr == CElapsedTimer::GetCurrDateStr(&wszOsdDate[0], pThreadParam->tOsdCfg.tTimeAttr.eFormat, nCharLen)) {
            LOG_MM_E(OSD, "Failed to get current date string.");
            m_osdWrapper.ReleaseInstance(&pOsdHandle);
            break;
        }
        AX_U8 nIvpsGrp = m_pIvpsGrpInstance->GetGrpCfg()->nGrp;
        AX_U32 nSrcWidth = m_pIvpsGrpInstance->GetGrpPPLAttr()->tPipelineAttr.tFilter[nIvpsChn + 1][APP_OSD_CHANNEL_FILTER_1].nDstPicWidth;
        AX_U32 nSrcHeight =
            m_pIvpsGrpInstance->GetGrpPPLAttr()->tPipelineAttr.tFilter[nIvpsChn + 1][APP_OSD_CHANNEL_FILTER_1].nDstPicHeight;
        AX_U32 nSrcOffset = 0;
        AX_U8 nRotation = AX_IVPS_ROTATION_0;
        AX_U8 nMirror = 0;
        if (AX_IVPS_ROTATION_90 == nRotation || AX_IVPS_ROTATION_270 == nRotation) {
            ::std::swap(nSrcWidth, nSrcHeight);
        }

        if (nMirror || AX_IVPS_ROTATION_180 == nRotation) {
            nSrcOffset = ALIGN_UP(nSrcWidth, ROTATION_WIDTH_ALIGEMENT) - nSrcHeight;
        }

        AX_U32 nFontSize = COSDStyle::GetInstance()->GetTimeFontSize(nSrcWidth, nSrcHeight);
        nFontSize = ALIGN_UP(nFontSize, BASE_FONT_SIZE);

        AX_U32 nMarginX = pThreadParam->tOsdCfg.nBoundaryX;
        AX_U32 nMarginY = pThreadParam->tOsdCfg.nBoundaryY;

        OSD_ALIGN_TYPE_E eAlign = pThreadParam->tOsdCfg.eAlign;
        AX_U32 nPicOffset = nMarginX % OSD_ALIGN_WIDTH;
        AX_U32 nPicOffsetBlock = nMarginX / OSD_ALIGN_WIDTH;

        AX_U32 nPixWidth = ALIGN_UP(nFontSize / 2 * nCharLen, BASE_FONT_SIZE);
        AX_U32 nPixHeight = ALIGN_UP(nFontSize, OSD_ALIGN_HEIGHT);
        m_osdWrapper.CalcStrSize(pOsdHandle, wszOsdDate, nFontSize, nPixWidth, nPixHeight);

        nPixWidth = ALIGN_UP(nPixWidth + nPicOffset, 8);
        AX_U32 nPicSize = nPixWidth * nPixHeight * 2;
        AX_U32 nFontColor = nRGB;
        nFontColor |= (1 << 24);
        AX_U32 nOffsetX = nSrcOffset + CCommonUtils::OverlayOffsetX(
                                           nSrcWidth, nPixWidth, (nPicOffset > 0 ? nPicOffsetBlock * OSD_ALIGN_WIDTH : nMarginX), eAlign);
        AX_U32 nOffsetY = CCommonUtils::OverlayOffsetY(nSrcHeight, nPixHeight, nMarginY, eAlign);
        LOG_MM_D(OSD, "PixWidth:%d, nPixHeight:%d, nOffsetX:%d, nOffsetY:%d, nCharLen:%d", nPixWidth, nPixHeight, nOffsetX, nOffsetY,
                 nCharLen);

        tDisp.arrDisp[0].eType = AX_IVPS_RGN_TYPE_OSD;
        tDisp.arrDisp[0].bShow = pThreadParam->tOsdCfg.bEnable;
        tDisp.arrDisp[0].uDisp.tOSD.u16Alpha = (AX_F32)(nRGB >> 24) / 0xFF * 1024;
        tDisp.arrDisp[0].uDisp.tOSD.u32BmpHeight = nPixHeight;
        tDisp.arrDisp[0].uDisp.tOSD.u32BmpWidth = nPixWidth;

        tDisp.arrDisp[0].uDisp.tOSD.u64PhyAddr = 0;
        if (pThreadParam->tOsdCfg.tTimeAttr.bInvEnable) {
            /* Bitmap */
            nPicSize /= 8;
            pArgbData = (AX_U16*)AX_MALLOC(nPicSize);
            memset(pArgbData, 0x0, nPicSize);

            if (nullptr == m_osdWrapper.GenBitmap(pOsdHandle, (wchar_t*)&wszOsdDate[0], (AX_U8*)pArgbData, nPixWidth, nPixHeight,
                                                  nPicOffset, 0, nFontSize, eAlign)) {
                LOG_MM_E(OSD, "Failed to generate bitmap for date string.");
                m_osdWrapper.ReleaseInstance(&pOsdHandle);
                if (pArgbData) {
                    AX_FREE(pArgbData);
                    pArgbData = nullptr;
                }
                break;
            }
            tDisp.tChnAttr.eFormat = AX_FORMAT_BITMAP;
            tDisp.arrDisp[0].uDisp.tOSD.enRgbFormat = AX_FORMAT_BITMAP;
            tDisp.tChnAttr.nBitColor.nColor = nRGB;
            tDisp.tChnAttr.nBitColor.bColorInv = AX_TRUE;
            tDisp.tChnAttr.nBitColor.nColorInv = pThreadParam->tOsdCfg.tTimeAttr.nColorInv;
            tDisp.tChnAttr.nBitColor.nColorInvThr = 0x808080;
            tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset = ALIGN_UP(nOffsetX, OSD_BMP_ALIGN_X_OFFSET);
            tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset = ALIGN_UP(nOffsetY, OSD_BMP_ALIGN_Y_OFFSET);
        } else {
            /* ARGB1555 */
            pArgbData = (AX_U16*)AX_MALLOC(nPicSize);
            memset(pArgbData, 0x0, nPicSize);

            if (nullptr == m_osdWrapper.GenARGB(pOsdHandle, (wchar_t*)&wszOsdDate[0], pArgbData, nPixWidth, nPixHeight, nPicOffset, 0,
                                                nFontSize, AX_TRUE, nFontColor, 0xFFFFFF, 0xFF000000, eAlign)) {
                LOG_MM_E(OSD, "Failed to generate bitmap for date string.");
                m_osdWrapper.ReleaseInstance(&pOsdHandle);
                if (pArgbData) {
                    AX_FREE(pArgbData);
                    pArgbData = nullptr;
                }
                break;
            }

            tDisp.tChnAttr.eFormat = AX_FORMAT_ARGB1555;
            tDisp.arrDisp[0].uDisp.tOSD.enRgbFormat = AX_FORMAT_ARGB1555;
            tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset = ALIGN_UP(nOffsetX, OSD_ALIGN_X_OFFSET);
            tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset = ALIGN_UP(nOffsetY, OSD_ALIGN_Y_OFFSET);
        }

        tDisp.arrDisp[0].uDisp.tOSD.pBitmap = (AX_U8*)pArgbData;
        AX_S32 ret = AX_IVPS_RGN_Update(pThreadParam->hRgn, &tDisp);
        if (AX_SUCCESS != ret) {
            LOG_MM_E(OSD, "AX_IVPS_RGN_Update fail, ret=0x%x, hRgn=%d", ret, pThreadParam->hRgn);
        }
        LOG_MM_D(OSD,
                 "[%d][%d] OSD (TIME):hRgn:%d bEnable:%d,  nSrcWidth:%d, nSrcHeight:%d, u32BmpWidth: %d, u32BmpHeight: %d, xOffset: %d, "
                 "yOffset: "
                 "%d, alpha: %d, eFormat:%d, bInvEnable:%d",
                 nIvpsGrp, nIvpsChn, pThreadParam->hRgn, tDisp.arrDisp[0].bShow, nSrcWidth, nSrcHeight,
                 tDisp.arrDisp[0].uDisp.tOSD.u32BmpWidth, tDisp.arrDisp[0].uDisp.tOSD.u32BmpHeight,
                 tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset, tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset, tDisp.arrDisp[0].uDisp.tOSD.u16Alpha,
                 tDisp.tChnAttr.eFormat, pThreadParam->tOsdCfg.tTimeAttr.bInvEnable);
        m_osdWrapper.ReleaseInstance(&pOsdHandle);

        if (pArgbData) {
            AX_FREE(pArgbData);
            pArgbData = nullptr;
        }

        for (int i = 0; i < 25 && !pThreadParam->bExit; i++) {
            CElapsedTimer::mSleep(10);
        }
        // {
        //     std::unique_lock<std::mutex> lck(m_mtxTime);
        //     m_cvTime.wait_for(lck, std::chrono::milliseconds(500), [pThreadParam]() -> bool { return pThreadParam->bExit; });
        // }
    }
}

AX_VOID COSDHelper::RectThreadFunc(OSD_REGION_PARAM_T* pThreadParam) {
    AX_IVPS_RGN_DISP_GROUP_T tDisp;
    memset(&tDisp, 0, sizeof(AX_IVPS_RGN_DISP_GROUP_T));

    AX_U32 nLastNum = (AX_U32)-1;

    while (!pThreadParam->bExit) {
        if (!m_pIvpsGrpInstance->GetChannelState(pThreadParam->nChn)) {
            for (int i = 0; i < 25 && !pThreadParam->bExit; i++) {
                CElapsedTimer::mSleep(20);
            }
            continue;
        }

        tDisp.nNum = 1;
        tDisp.tChnAttr.nAlpha = 255;
        tDisp.tChnAttr.eFormat = AX_FORMAT_ARGB1555;
        tDisp.tChnAttr.nZindex = pThreadParam->tOsdCfg.nZIndex;
        tDisp.tChnAttr.bSingleCanvas = AX_TRUE;

        std::vector<AX_IVPS_RGN_POLYGON_T> stRgn;
        AX_U32 index = 0;
        if (APP_OSD_RECT(pThreadParam->hRgn, stRgn)) {
            for (AX_U32 i = 0; i < stRgn.size() && index < AX_IVPS_REGION_MAX_DISP_NUM; ++i) {
                tDisp.arrDisp[index].eType = AX_IVPS_RGN_TYPE_RECT;
                tDisp.arrDisp[index].bShow = pThreadParam->tOsdCfg.bEnable;
                tDisp.arrDisp[index].uDisp.tPolygon = stRgn[i];
                index++;
            }
        }

        stRgn.clear();
        if (APP_OSD_POLYGON(pThreadParam->hRgn, stRgn)) {
            tDisp.nNum += stRgn.size();
            for (AX_U32 i = 0; i < stRgn.size() && index < AX_IVPS_REGION_MAX_DISP_NUM; ++i) {
                tDisp.arrDisp[index].eType = AX_IVPS_RGN_TYPE_POLYGON;
                tDisp.arrDisp[index].bShow = pThreadParam->tOsdCfg.bEnable;
                tDisp.arrDisp[index].uDisp.tPolygon = stRgn[i];
                index++;
            }
        }
        tDisp.nNum = index;

        if (!(nLastNum == tDisp.nNum && nLastNum == 0)) {
            AX_S32 ret = AX_IVPS_RGN_Update(pThreadParam->hRgn, &tDisp);
            if (AX_SUCCESS != ret) {
                LOG_MM_E(OSD, "AX_IVPS_RGN_Update fail, ret=0x%x, hRgn=%d", ret, pThreadParam->hRgn);
                for (int i = 0; i < 50 && !pThreadParam->bExit; i++) {
                    CElapsedTimer::mSleep(20);
                }
            }
        }

        nLastNum = tDisp.nNum;

        CElapsedTimer::mSleep(33);
    }
}

AX_VOID COSDHelper::UpdateOSDPic(OSD_REGION_PARAM_T* pThreadParam) {
    if (!m_pIvpsGrpInstance) {
        return;
    }

    AX_U32 nIvpsChn = pThreadParam->nChn;
    AX_IVPS_RGN_DISP_GROUP_T tDisp;
    memset(&tDisp, 0, sizeof(AX_IVPS_RGN_DISP_GROUP_T));
    tDisp.nNum = 1;
    tDisp.tChnAttr.nAlpha = 255;
    tDisp.tChnAttr.eFormat = AX_FORMAT_ARGB1555;
    tDisp.tChnAttr.nZindex = pThreadParam->tOsdCfg.nZIndex;
    tDisp.tChnAttr.bSingleCanvas = AX_TRUE;

    std::string szFileName = pThreadParam->tOsdCfg.tPicAttr.szFileName;
    if (szFileName == "") {
        return;
    }

    AX_U8 nIvpsGrp = m_pIvpsGrpInstance->GetGrpCfg()->nGrp;
    AX_U32 nSrcWidth = 0;
    AX_U32 nSrcHeight = 0;
    m_pIvpsGrpInstance->GetCurResolution(nIvpsChn, nSrcWidth, nSrcHeight);
    LOG_MM_I(OSD, "ivpsGrp:%d, chn:%d, width:%d, height:%d", nIvpsGrp, nIvpsChn, nSrcWidth, nSrcHeight);

    AX_U32 nSrcOffset = 0;

    AX_U32 nPicWidth = ALIGN_UP(pThreadParam->tOsdCfg.tPicAttr.nWidth, OSD_ALIGN_HEIGHT);
    AX_U32 nPicHeight = ALIGN_UP(pThreadParam->tOsdCfg.tPicAttr.nHeight, OSD_ALIGN_HEIGHT);

    /* Config picture OSD */
    AX_U32 nPicMarginX = pThreadParam->tOsdCfg.nBoundaryX;
    AX_U32 nPicMarginY = pThreadParam->tOsdCfg.nBoundaryY;

    OSD_ALIGN_TYPE_E eAlign = pThreadParam->tOsdCfg.eAlign;

    AX_U32 nSrcBlock = nSrcWidth / OSD_ALIGN_X_OFFSET;
    AX_U32 nGap = nSrcWidth % OSD_ALIGN_X_OFFSET;

    AX_U32 nBlockBollowed = ceil((AX_F32)(nPicWidth + nPicMarginX - nGap) / OSD_ALIGN_X_OFFSET);
    if (nBlockBollowed < 0) {
        nBlockBollowed = 0;
    }
    AX_U32 nOffsetX = nSrcOffset + (nSrcBlock - nBlockBollowed) * OSD_ALIGN_X_OFFSET;
    AX_U32 nOffsetY = CCommonUtils::OverlayOffsetY(nSrcHeight, nPicHeight, nPicMarginY, eAlign);
    if (AX_FALSE ==
        CCommonUtils::LoadImage(szFileName.c_str(), (AX_VOID**)&tDisp.arrDisp[0].uDisp.tOSD.pBitmap, nPicWidth * nPicHeight * 2)) {
        LOG_MM_E(OSD, "Load logo(%s) failed.", szFileName.c_str());
        return;
    }

    tDisp.arrDisp[0].eType = AX_IVPS_RGN_TYPE_OSD;
    tDisp.arrDisp[0].bShow = pThreadParam->tOsdCfg.bEnable;
    tDisp.arrDisp[0].uDisp.tOSD.enRgbFormat = AX_FORMAT_ARGB1555;
    tDisp.arrDisp[0].uDisp.tOSD.u16Alpha = 50;
    tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset = nOffsetX;
    tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset = nOffsetY;
    tDisp.arrDisp[0].uDisp.tOSD.u32BmpWidth = nPicWidth;
    tDisp.arrDisp[0].uDisp.tOSD.u32BmpHeight = nPicHeight;
    AX_S32 ret = AX_IVPS_RGN_Update(pThreadParam->hRgn, &tDisp);
    if (AX_SUCCESS != ret) {
        LOG_MM_E(OSD, "AX_IVPS_RGN_Update fail, ret=0x%x, hRgn=%d", ret, pThreadParam->hRgn);
    }

    if (tDisp.arrDisp[0].uDisp.tOSD.pBitmap) {
        AX_FREE(tDisp.arrDisp[0].uDisp.tOSD.pBitmap);
    }
    LOG_MM_I(OSD,
             "[%d][%d] rgn:%d , OSD(PICTURE): nSrcWidth:%d, nSrcHeight:%d, u32BmpWidth: %d, u32BmpHeight: %d, xOffset: %d, yOffset: %d, "
             "alpha: %d",
             nIvpsGrp, nIvpsChn, pThreadParam->hRgn, nSrcWidth, nSrcHeight, tDisp.arrDisp[0].uDisp.tOSD.u32BmpWidth,
             tDisp.arrDisp[0].uDisp.tOSD.u32BmpHeight, tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset, tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset,
             tDisp.arrDisp[0].uDisp.tOSD.u16Alpha);
    return;
}

AX_VOID COSDHelper::UpdateOSDStr(OSD_REGION_PARAM_T* pThreadParam) {
    if (!m_pIvpsGrpInstance) {
        return;
    }

    AX_S32 nRet = -1;
    AX_U32 nIvpsChn = pThreadParam->nChn;
    COSDHandler* pOsdHandle = m_osdWrapper.NewInstance();
    if (nullptr == pOsdHandle) {
        LOG_MM_E(OSD, "Get osd handle failed.");
        return;
    }

    static AX_CHAR strTtfFile[128] = {0};
    sprintf(strTtfFile, "%s/GB2312.ttf", GetResPath().c_str());

    if (AX_FALSE == m_osdWrapper.InitHandler(pOsdHandle, strTtfFile)) {
        LOG_MM_E(OSD, "AX_OSDInitHandler failed, ttf: %s.", strTtfFile);
        m_osdWrapper.ReleaseInstance(&pOsdHandle);
        return;
    }

    AX_U16* pArgbData = nullptr;

    wchar_t wszOsdStr[MAX_OSD_STR_CHAR_LEN] = {0};
    memset(&wszOsdStr[0], 0, sizeof(wchar_t) * MAX_OSD_STR_CHAR_LEN);

    IVPS_GRP nIvpsGrp = pThreadParam->nGroup;

    AX_IVPS_RGN_DISP_GROUP_T tDisp;
    memset(&tDisp, 0, sizeof(AX_IVPS_RGN_DISP_GROUP_T));

    tDisp.nNum = 1;
    tDisp.tChnAttr.nAlpha = 255;
    tDisp.tChnAttr.nZindex = pThreadParam->tOsdCfg.nZIndex;
    tDisp.tChnAttr.bSingleCanvas = AX_TRUE;

    const AX_U8 *pStart = (AX_U8 *)pThreadParam->tOsdCfg.tStrAttr.szStr;
    const AX_U8 *pEnd = nullptr;
    AX_U32 nCharSize = 0;
    while (nCharSize < MAX_OSD_STR_CHAR_LEN - 1) {
        AX_S32 chOut = utf8_to_ucs2(pStart, &pEnd);
        if (chOut < 0 || pEnd == nullptr) {
            break;
        } else {
            wszOsdStr[nCharSize++] = chOut;
            pStart = pEnd;
            pEnd = nullptr;
        }
    }

    AX_U8 nMirror = 0;

    AX_U32 nSrcWidth = 0;
    AX_U32 nSrcHeight = 0;
    m_pIvpsGrpInstance->GetCurResolution(nIvpsChn, nSrcWidth, nSrcHeight);

    AX_U32 nSrcOffsetX = 0;
    if (nMirror) {
        nSrcOffsetX = ALIGN_UP(nSrcWidth, ROTATION_WIDTH_ALIGEMENT) - nSrcWidth;
    }

    AX_U32 nFontSize = pThreadParam->tOsdCfg.tStrAttr.nFontSize;
    AX_U32 nMarginX = pThreadParam->tOsdCfg.nBoundaryX;
    AX_U32 nMarginY = pThreadParam->tOsdCfg.nBoundaryY;
    AX_U32 nPixWidth = 0;
    AX_U32 nPixHeight = 0;
    m_osdWrapper.CalcStrSize(pOsdHandle, wszOsdStr, nFontSize, nPixWidth, nPixHeight);

    {
        std::vector<OSD_CFG_T> vecOsdCfg;
        IVPS_GROUP_CFG_T* pGrpConfig = m_pIvpsGrpInstance->GetGrpCfg();
        CWebOptionHelper::GetInstance()->GetOsdConfig(pGrpConfig->nSnsSrc, pGrpConfig->nGrp, nIvpsChn, vecOsdCfg);
        for (AX_U32 i = 0; i < vecOsdCfg.size(); i++) {
            if (pThreadParam->tOsdCfg.eType == vecOsdCfg[i].eType) {
                vecOsdCfg[i].nBoundaryW = nPixWidth;
                vecOsdCfg[i].nBoundaryH = nPixHeight;
            }
        }
        CWebOptionHelper::GetInstance()->SetOsdConfig(pGrpConfig->nSnsSrc, pGrpConfig->nGrp, nIvpsChn, vecOsdCfg);
    }

    OSD_ALIGN_TYPE_E eAlign = pThreadParam->tOsdCfg.eAlign;

    AX_U32 nPicOffset = nMarginX % OSD_ALIGN_WIDTH;
    AX_U32 nPicOffsetBlock = nMarginX / OSD_ALIGN_WIDTH;

    nPixWidth = ALIGN_UP(nPixWidth + nPicOffset, OSD_ALIGN_WIDTH);
    nPixHeight = ALIGN_UP(nPixHeight, OSD_ALIGN_HEIGHT);

    AX_U32 nOffsetX = nSrcOffsetX + CCommonUtils::OverlayOffsetX(nSrcWidth, nPixWidth,
                                                                 (nPicOffset > 0 ? nPicOffsetBlock * OSD_ALIGN_WIDTH : nMarginX), eAlign);
    AX_U32 nOffsetY = CCommonUtils::OverlayOffsetY(nSrcHeight, nPixHeight, nMarginY, eAlign);

    nPixWidth = (nOffsetX + nPixWidth) > nSrcWidth ? nSrcWidth - nOffsetX : nPixWidth;
    nPixHeight = (nOffsetY + nPixHeight) > nSrcHeight ? nSrcHeight - nOffsetY : nPixHeight;

    AX_U32 nPicSize = nPixWidth * nPixHeight * 2;
    AX_U32 nFontColor = pThreadParam->tOsdCfg.tStrAttr.nColor;
    nFontColor |= (1 << 24);

    do {
        tDisp.arrDisp[0].eType = AX_IVPS_RGN_TYPE_OSD;
        tDisp.arrDisp[0].bShow = pThreadParam->tOsdCfg.bEnable;
        tDisp.arrDisp[0].uDisp.tOSD.u16Alpha = (AX_F32)(nFontColor >> 24) / 0xFF * 1024;
        tDisp.arrDisp[0].uDisp.tOSD.u32BmpWidth = nPixWidth;
        tDisp.arrDisp[0].uDisp.tOSD.u32BmpHeight = nPixHeight;
        tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset = nOffsetX;
        tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset = nOffsetY;
        tDisp.arrDisp[0].uDisp.tOSD.u64PhyAddr = 0;

        if (pThreadParam->tOsdCfg.tStrAttr.bInvEnable) {
            /* Bitmap */
            nPicSize /= 16;
            pArgbData = (AX_U16*)AX_MALLOC(nPicSize);
            memset(pArgbData, 0x0, nPicSize);

            if (nullptr == m_osdWrapper.GenBitmap(pOsdHandle, (wchar_t*)&wszOsdStr[0], (AX_U8*)pArgbData, nPixWidth, nPixHeight, nPicOffset,
                                                  0, nFontSize, eAlign)) {
                LOG_MM_E(OSD, "Failed to generate bitmap for date string.");
                m_osdWrapper.ReleaseInstance(&pOsdHandle);
                if (pArgbData) {
                    AX_FREE(pArgbData);
                    pArgbData = nullptr;
                }
                break;
            }

            tDisp.tChnAttr.eFormat = AX_FORMAT_BITMAP;
            tDisp.arrDisp[0].uDisp.tOSD.u32Color = pThreadParam->tOsdCfg.tStrAttr.nColor;
            tDisp.arrDisp[0].uDisp.tOSD.enRgbFormat = AX_FORMAT_BITMAP;
            tDisp.tChnAttr.nBitColor.bColorInv = AX_TRUE;
            tDisp.tChnAttr.nBitColor.nColor = pThreadParam->tOsdCfg.tStrAttr.nColor;
            tDisp.tChnAttr.nBitColor.nColorInv = pThreadParam->tOsdCfg.tStrAttr.nColorInv;
            tDisp.tChnAttr.nBitColor.nColorInvThr = 0x808080;

            tDisp.arrDisp[0].uDisp.tOSD.u32BmpWidth = ALIGN_UP(nPixWidth, OSD_ALIGN_WIDTH);
            tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset = ALIGN_UP(nOffsetX, OSD_BMP_ALIGN_X_OFFSET);
            tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset = ALIGN_UP(nOffsetY, OSD_BMP_ALIGN_Y_OFFSET);

        } else {
            pArgbData = (AX_U16*)AX_MALLOC(nPicSize);
            memset(pArgbData, 0x0, nPicSize);
            tDisp.tChnAttr.eFormat = AX_FORMAT_ARGB1555;
            tDisp.arrDisp[0].uDisp.tOSD.enRgbFormat = AX_FORMAT_ARGB1555;

            if (nullptr == m_osdWrapper.GenARGB(pOsdHandle, (wchar_t*)&wszOsdStr[0], (AX_U16*)pArgbData, nPixWidth, nPixHeight, nPicOffset,
                                                0, nFontSize, AX_TRUE, nFontColor, 0xFFFFFF, 0xFF000000, eAlign)) {
                LOG_MM_E(OSD, "[%d][%d]Failed to generate bitmap for string: %s.", nIvpsGrp, pThreadParam->tOsdCfg.nZIndex,
                         pThreadParam->tOsdCfg.tStrAttr.szStr);
                break;
            }
        }

        tDisp.arrDisp[0].uDisp.tOSD.pBitmap = (AX_U8*)pArgbData;

        LOG_MM_I(OSD, "[%d] hRgn: %d, srcWidth: %d, srcHeight: %d, u32BmpWidth: %d, u32BmpHeight: %d, xOffset: %d, yOffset: %d, alpha: %d",
                 nIvpsGrp, pThreadParam->hRgn, nSrcWidth, nSrcHeight, tDisp.arrDisp[0].uDisp.tOSD.u32BmpWidth,
                 tDisp.arrDisp[0].uDisp.tOSD.u32BmpHeight, tDisp.arrDisp[0].uDisp.tOSD.u32DstXoffset,
                 tDisp.arrDisp[0].uDisp.tOSD.u32DstYoffset, tDisp.arrDisp[0].uDisp.tOSD.u16Alpha);

        /* Region update */
        nRet = AX_IVPS_RGN_Update(pThreadParam->hRgn, &tDisp);
        if (AX_SUCCESS != nRet) {
            LOG_MM_E(OSD, "[%d][0x%02x] AX_IVPS_RGN_Update fail, ret=0x%x, handle=%d", nIvpsGrp, pThreadParam->nFilter, nRet,
                     pThreadParam->hRgn);
        }

    } while (0);

    /* Free osd resource */
    if (nullptr != pArgbData) {
        AX_FREE(pArgbData);
        pArgbData = nullptr;
    }

    if (nullptr != pOsdHandle) {
        m_osdWrapper.ReleaseInstance(&pOsdHandle);
    }

    return;
}

AX_VOID COSDHelper::UpdateOSDPri(OSD_REGION_PARAM_T* pThreadParam) {
    if (!m_pIvpsGrpInstance) {
        return;
    }

    if (!m_pIvpsGrpInstance->IsMaskGroup()) {
        LOG_MM_W(OSD, "Do nothing.");
        return;
    }

    AX_S32 nRet = -1;

    IVPS_GRP nIvpsGrp = pThreadParam->nGroup;

    AX_IVPS_RGN_DISP_GROUP_T tDisp;
    memset(&tDisp, 0, sizeof(AX_IVPS_RGN_DISP_GROUP_T));

    tDisp.nNum = 1;
    tDisp.tChnAttr.nAlpha = 255;
    tDisp.tChnAttr.eFormat = AX_FORMAT_ARGB1555;
    tDisp.tChnAttr.nZindex = pThreadParam->tOsdCfg.nZIndex;
    tDisp.tChnAttr.bSingleCanvas = AX_TRUE;

    do {
        tDisp.arrDisp[0].eType = (AX_IVPS_RGN_TYPE_E)(pThreadParam->tOsdCfg.tPrivacyAttr.eType);
        tDisp.arrDisp[0].bShow = pThreadParam->tOsdCfg.bEnable;
        if (tDisp.arrDisp[0].eType == AX_IVPS_RGN_TYPE_LINE) {
            tDisp.arrDisp[0].uDisp.tLine.nLineWidth = pThreadParam->tOsdCfg.tPrivacyAttr.nLineWidth;
            tDisp.arrDisp[0].uDisp.tLine.nColor = pThreadParam->tOsdCfg.tPrivacyAttr.nColor;
            tDisp.arrDisp[0].uDisp.tLine.nAlpha = 255;
            tDisp.arrDisp[0].uDisp.tLine.tPTs[0].nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].x;
            tDisp.arrDisp[0].uDisp.tLine.tPTs[0].nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].y;
            tDisp.arrDisp[0].uDisp.tLine.tPTs[1].nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[1].x;
            tDisp.arrDisp[0].uDisp.tLine.tPTs[1].nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[1].y;
        } else if (tDisp.arrDisp[0].eType == AX_IVPS_RGN_TYPE_RECT) {
            tDisp.arrDisp[0].uDisp.tPolygon.nLineWidth = 0;
            tDisp.arrDisp[0].uDisp.tPolygon.nColor = pThreadParam->tOsdCfg.tPrivacyAttr.nColor;
            tDisp.arrDisp[0].uDisp.tPolygon.nAlpha = 255;
            tDisp.arrDisp[0].uDisp.tPolygon.bSolid = pThreadParam->tOsdCfg.tPrivacyAttr.bSolid;

            if (pThreadParam->tOsdCfg.tPrivacyAttr.bSolid) {
                tDisp.arrDisp[0].uDisp.tPolygon.nLineWidth = 0;
            } else {
                tDisp.arrDisp[0].uDisp.tPolygon.nLineWidth = pThreadParam->tOsdCfg.tPrivacyAttr.nLineWidth;
            }

            tDisp.arrDisp[0].uDisp.tPolygon.tRect.nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].x;
            tDisp.arrDisp[0].uDisp.tPolygon.tRect.nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].y;
            tDisp.arrDisp[0].uDisp.tPolygon.tRect.nW =
                pThreadParam->tOsdCfg.tPrivacyAttr.tPt[2].x - pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].x;
            tDisp.arrDisp[0].uDisp.tPolygon.tRect.nH =
                pThreadParam->tOsdCfg.tPrivacyAttr.tPt[2].y - pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].y;
        } else if (tDisp.arrDisp[0].eType == AX_IVPS_RGN_TYPE_POLYGON) {
            tDisp.arrDisp[0].uDisp.tPolygon.nColor = pThreadParam->tOsdCfg.tPrivacyAttr.nColor;
            tDisp.arrDisp[0].uDisp.tPolygon.nAlpha = 255;
            tDisp.arrDisp[0].uDisp.tPolygon.bSolid = pThreadParam->tOsdCfg.tPrivacyAttr.bSolid;
            if (pThreadParam->tOsdCfg.tPrivacyAttr.bSolid) {
                tDisp.arrDisp[0].uDisp.tPolygon.nLineWidth = 0;
            } else {
                tDisp.arrDisp[0].uDisp.tPolygon.nLineWidth = pThreadParam->tOsdCfg.tPrivacyAttr.nLineWidth;
            }

            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[0].nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].x;
            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[0].nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].y;
            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[1].nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[1].x;
            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[1].nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[1].y;
            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[2].nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[2].x;
            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[2].nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[2].y;
            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[3].nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[3].x;
            tDisp.arrDisp[0].uDisp.tPolygon.tPTs[3].nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[3].y;
        } else if (tDisp.arrDisp[0].eType == AX_IVPS_RGN_TYPE_MOSAIC) {
            tDisp.arrDisp[0].uDisp.tMosaic.eBklSize = (AX_IVPS_MOSAIC_BLK_SIZE_E)pThreadParam->tOsdCfg.tPrivacyAttr.nLineWidth;
            tDisp.arrDisp[0].uDisp.tMosaic.tRect.nX = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].x;
            tDisp.arrDisp[0].uDisp.tMosaic.tRect.nY = pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].y;
            tDisp.arrDisp[0].uDisp.tMosaic.tRect.nW =
                pThreadParam->tOsdCfg.tPrivacyAttr.tPt[2].x - pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].x;
            tDisp.arrDisp[0].uDisp.tMosaic.tRect.nH =
                pThreadParam->tOsdCfg.tPrivacyAttr.tPt[2].y - pThreadParam->tOsdCfg.tPrivacyAttr.tPt[0].y;
        }
        LOG_MM_I(OSD, "nGrp:%d, nRgn:%d, nZindex:%d", nIvpsGrp, pThreadParam->hRgn, pThreadParam->tOsdCfg.nZIndex);
        /* Region update */
        nRet = AX_IVPS_RGN_Update(pThreadParam->hRgn, &tDisp);
        if ((AX_SUCCESS != nRet) && (static_cast<int>(0x800d0229) != nRet)) {
            LOG_MM_E(OSD, "[%d][0x%02x] AX_IVPS_RGN_Update fail, ret=0x%x, handle=%d", nIvpsGrp, pThreadParam->nFilter, nRet,
                     pThreadParam->hRgn);
        }

    } while (0);

    return;
}

std::string COSDHelper::GetResPath() {
    return "./res/";
}

AX_BOOL COSDHelper::StopOSD() {
    LOG_MM_C(OSD, "+++");

    AX_S32 nRet = AX_SUCCESS;

    m_bExited = AX_TRUE;
    m_cv.notify_one();
    m_updateThread.Join();

    for (AX_U32 i = 0; i < m_nRgnCount; i++) {
        if (AX_IVPS_INVALID_REGION_HANDLE != m_arrRgnThreadParam[i].hRgn) {
            if (OSD_TYPE_TIME == m_arrRgnThreadParam[i].tOsdCfg.eType || OSD_TYPE_RECT == m_arrRgnThreadParam[i].tOsdCfg.eType) {
                {
                    m_arrRgnThreadParam[i].bExit = AX_TRUE;
                }
                m_arrRgnThreadParam[i].m_EventThread.Join();
            }
            nRet = AX_IVPS_RGN_DetachFromFilter(m_arrRgnThreadParam[i].hRgn, m_arrRgnThreadParam[i].nGroup, m_arrRgnThreadParam[i].nFilter);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(OSD, "AX_IVPS_RGN_DetachFromFilter(Grp: %d, Filter: %x, Handle: %d) failed, ret=0x%x",
                         m_arrRgnThreadParam[i].nGroup, m_arrRgnThreadParam[i].nFilter, m_arrRgnThreadParam[i].hRgn, nRet);
                return AX_FALSE;
            } else {
                LOG_M_I(OSD, "AX_IVPS_RGN_DetachFromFilter(Grp: %d, Filter: %x, Handle: %d) successfully.", m_arrRgnThreadParam[i].nGroup,
                        m_arrRgnThreadParam[i].nFilter, m_arrRgnThreadParam[i].hRgn);
            }
            nRet = AX_IVPS_RGN_Destroy(m_arrRgnThreadParam[i].hRgn);
            if (AX_SUCCESS != nRet) {
                LOG_MM_E(OSD, "AX_IVPS_RGN_Destroy(Handle: %d) failed, ret=0x%x", m_arrRgnThreadParam[i].hRgn, nRet);
                return AX_FALSE;
            } else {
                LOG_M_I(OSD, "AX_IVPS_RGN_Destroy(Handle: %d) successfully.", m_arrRgnThreadParam[i].hRgn, nRet);
            }
            m_arrRgnThreadParam[i].hRgn = AX_IVPS_INVALID_REGION_HANDLE;
        }
    }

    LOG_MM_C(OSD, "---");
    return AX_TRUE;
}

AX_BOOL COSDHelper::Refresh() {
    std::unique_lock<std::mutex> lck(m_mtx);
    ++m_nUpdateOSDTasks;
    m_cv.notify_one();
    return AX_TRUE;
}

AX_VOID COSDHelper::PerformUpdateOSD(AX_VOID) {
    LOG_MM_C(OSD, "+++");
    if (!m_pIvpsGrpInstance) {
        return;
    }
    IVPS_GROUP_CFG_T* pGrpConfig = m_pIvpsGrpInstance->GetGrpCfg();
    while (!m_bExited) {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_cv.wait(lck, [this] { return ((m_nUpdateOSDTasks > 0) || m_bExited); });
        if (m_bExited) {
            break;
        }

        --m_nUpdateOSDTasks;

        for (AX_U8 nChn = 0; nChn < pGrpConfig->nGrpChnNum; nChn++) {
            std::vector<OSD_CFG_T> vecOsdCfg;
            CWebOptionHelper::GetInstance()->GetOsdConfig(pGrpConfig->nSnsSrc, pGrpConfig->nGrp, nChn, vecOsdCfg);
            for (AX_U32 i = 0; i < vecOsdCfg.size(); i++) {
                OSD_TYPE_E eType = vecOsdCfg[i].eType;
                for (AX_U32 j = 0; j < m_nRgnCount; j++) {
                    if (nChn == m_arrRgnThreadParam[j].nChn && m_arrRgnThreadParam[j].tOsdCfg.eType == eType && OSD_TYPE_RECT != eType) {
                        m_arrRgnThreadParam[j].tOsdCfg = vecOsdCfg[i];
                        if (OSD_TYPE_TIME != eType) {
                            UpdateOSD(&m_arrRgnThreadParam[j]);
                        }
                    }
                }
            }
        }
    }
    LOG_MM_C(OSD, "---");
}

AX_BOOL COSDHelper::EnableAiRegion(AX_BOOL bEnable) {
    for (AX_U32 j = 0; j < m_nRgnCount; j++) {
        if (m_arrRgnThreadParam[j].tOsdCfg.eType == OSD_TYPE_RECT) {
            m_arrRgnThreadParam[j].tOsdCfg.bEnable = bEnable;
        }
    }
    return AX_TRUE;
}

AX_U8 COSDHelper::GetAttachedFilter() {
    return 0;
}

AX_BOOL COSDHelper::UpdateOSDRect(const std::vector<AX_IVPS_RGN_POLYGON_T>& vecRgn) {
    for (AX_U32 i = 0; i < m_nRgnCount; ++i) {
        if (m_arrRgnThreadParam[i].tOsdCfg.eType == OSD_TYPE_RECT) {
            SET_APP_OSD_RECT(m_arrRgnThreadParam[i].hRgn, vecRgn);
        }
    }

    return AX_TRUE;
}

AX_BOOL COSDHelper::UpdateOSDRect(const std::vector<AX_APP_OSD_BOX_T>& vecBox) {
    if (!m_pIvpsGrpInstance) {
        return AX_FALSE;
    }

    for (AX_U32 i = 0; i < m_nRgnCount; i++) {
        if (m_arrRgnThreadParam[i].tOsdCfg.eType == OSD_TYPE_RECT) {
            std::vector<AX_IVPS_RGN_POLYGON_T> vecRgn;
            AX_IVPS_RGN_POLYGON_T stPolygon;
            memset(&stPolygon, 0x00, sizeof(stPolygon));

            AX_U32 nIvpsChn = m_arrRgnThreadParam[i].nChn;
            AX_U32 nSrcWidth ;
            AX_U32 nSrcHeight ;
            m_pIvpsGrpInstance->GetCurResolution(nIvpsChn, nSrcWidth, nSrcHeight);

            AX_U32 nRectLineWidth = COSDStyle::GetInstance()->GetRectLineWidth(nSrcWidth, nSrcHeight);

            stPolygon.bSolid = AX_TRUE;
            stPolygon.nLineWidth = nRectLineWidth;
            stPolygon.nAlpha = 255;

            for (auto& tBox : vecBox) {
                stPolygon.nColor = tBox.nColor;
                stPolygon.tRect.nX = tBox.tBox.fX * nSrcWidth;
                stPolygon.tRect.nY = tBox.tBox.fY * nSrcHeight;
                stPolygon.tRect.nW = tBox.tBox.fW * nSrcWidth;
                stPolygon.tRect.nH = tBox.tBox.fH * nSrcHeight;

                vecRgn.push_back(stPolygon);
            }

            SET_APP_OSD_RECT(m_arrRgnThreadParam[i].hRgn, vecRgn);
        }
    }

    return AX_TRUE;
}
