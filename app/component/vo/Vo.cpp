/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "Vo.hpp"
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "AXPoolManager.hpp"
#include "AppLogApi.h"
#include "GlobalDef.h"
#include "ax_ivps_api.h"
#include "fs.hpp"

using namespace std;
#define VO "VO"

CVO::CVO() {
    InitSyncInfo();
}

AX_BOOL CVO::Init(const VO_ATTR_T& stAttr) {
    LOG_M_D(VO, "%s: +++", __func__);

    AX_U32 nHz;
    AX_U32 u32ChnNr;
    AX_VO_RECT_T stArea;
    if (!GetDispInfoFromIntfSync(stAttr.enIntfSync, stArea, nHz)) {
        return AX_FALSE;
    }

    m_nVideoChnCount = stAttr.arrChns.size();
    m_stAttr = stAttr;
    m_stAttr.nW = stArea.u32Width;
    m_stAttr.nH = stArea.u32Height;
    m_stAttr.nHz = nHz;

    if (!InitLayout(m_nVideoChnCount)) {
        return AX_FALSE;
    }

    for (AX_U32 i = 0; i < m_nVideoChnCount; ++i) {
        m_arrChns[i].u32FifoDepth = m_stAttr.arrChns[i].nDepth;
        m_arrChns[i].u32Priority = m_stAttr.arrChns[i].nPriority;
    }

#ifdef __DUMMY_VO__
#else

    AX_S32 ret = AX_VO_CreateVideoLayer(&m_stAttr.voLayer);
    if (0 != ret) {
        LOG_M_E(VO, "AX_VO_CreateVideoLayer(layer %d) fail, ret = 0x%x", m_stAttr.voLayer, ret);
        return AX_FALSE;
    }

    enum { LAYER_CREATED = 0x1, VODEV_ENABLED = 0x2, LAYER_BINDED = 0x4, LAYER_ENABLED = 0x8, FBLAYER_BINDED = 0x10 };
    AX_U32 nState = LAYER_CREATED;

    try {
        AX_VO_PUB_ATTR_T stPubAttr;
        memset(&stPubAttr, 0, sizeof(stPubAttr));
        stPubAttr.enIntfType = m_stAttr.enIntfType;
        stPubAttr.enIntfSync = m_stAttr.enIntfSync;
        stPubAttr.enMode = m_stAttr.enMode;
        stPubAttr.enIntfFmt = AX_VO_OUT_FMT_YUV422;
        if (AX_VO_OUTPUT_USER == stAttr.enIntfSync) {
            stPubAttr.stSyncInfo = m_stSyncInfos;
        }
        ret = AX_VO_SetPubAttr(m_stAttr.voDev, &stPubAttr);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_SetPubAttr(dev %d) fail, ret = 0x%x", m_stAttr.voDev, ret);
            throw 1;
        }

        ret = AX_VO_Enable(m_stAttr.voDev);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_Enable(dev %d) fail, ret = 0x%x", m_stAttr.voDev, ret);
            throw 1;
        } else {
            nState |= VODEV_ENABLED;
        }

        if (!CreatePools(m_stAttr.nLayerDepth)) {
            LOG_M_E(VO, "%s: CreatePool() fail", __func__);
            throw 1;
        }

        AX_VO_VIDEO_LAYER_ATTR_T stLayerAttr;
        memset(&stLayerAttr, 0, sizeof(stLayerAttr));
        stLayerAttr.stImageSize.u32Width = stArea.u32Width;
        stLayerAttr.stImageSize.u32Height = stArea.u32Height;
        stLayerAttr.enPixFmt = AX_FORMAT_YUV420_SEMIPLANAR;

        /* if layer bind to dev, enSynMode is ignored */
        stLayerAttr.enSyncMode = m_stAttr.enLayerSync;
        stLayerAttr.f32FrmRate = (AX_F32)(nHz);
        stLayerAttr.u32FifoDepth = m_stAttr.nLayerDepth;
        u32ChnNr = m_arrChns.size();
        stLayerAttr.u32BkClr = m_stAttr.nBgClr;
        stLayerAttr.u32PrimaryChnId = PRIMARY_CHN;
        stLayerAttr.enWBMode = AX_VO_LAYER_WB_POOL;
        stLayerAttr.u32PoolId = m_LayerPool;
        stLayerAttr.u32DispatchMode = AX_VO_LAYER_OUT_TO_LINK;
        stLayerAttr.enPartMode = AX_VO_PART_MODE_SINGLE;
        stLayerAttr.enBlendMode = AX_VO_BLEND_MODE_DEFAULT;
        stLayerAttr.u32Toleration = m_stAttr.nTolerance;
        ret = AX_VO_SetVideoLayerAttr(m_stAttr.voLayer, &stLayerAttr);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_SetVideoLayerAttr(layer %d) fail, ret = 0x%x", m_stAttr.voLayer, ret);
            throw 1;
        } else {
            LOG_M_I(VO, "layer %d: [%dx%d], dispatch mode %d, layer depth %d, part mode %d, tolerance %d, u32ChnNr:%d", m_stAttr.voLayer,
                    stLayerAttr.stImageSize.u32Width, stLayerAttr.stImageSize.u32Height, stLayerAttr.u32DispatchMode,
                    stLayerAttr.u32FifoDepth, stLayerAttr.enPartMode, stLayerAttr.u32Toleration, u32ChnNr);
        }

        ret = AX_VO_BindVideoLayer(m_stAttr.voLayer, m_stAttr.voDev);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_BindVideoLayer(layer %d dev %d) fail, ret = 0x%x", m_stAttr.voLayer, m_stAttr.voDev, ret);
            throw 1;
        } else {
            nState |= LAYER_BINDED;
        }

        ret = AX_VO_EnableVideoLayer(m_stAttr.voLayer);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_EnableVideoLayer(layer %d) fail, ret = 0x%x", m_stAttr.voLayer, ret);
            throw 1;
        } else {
            nState |= LAYER_ENABLED;
        }

        auto DisableChns = [](VO_LAYER layer, VO_CHN i) -> AX_VOID {
            for (VO_CHN j = 0; j < i; ++j) {
                AX_VO_DisableChn(layer, j);
            }
        };

        for (VO_CHN voChn = 0; voChn < u32ChnNr; ++voChn) {
            ret = AX_VO_SetChnAttr(m_stAttr.voLayer, voChn, &m_arrChns[voChn]);
            if (0 != ret) {
                LOG_M_E(VO, "AX_VO_SetChnAttr(layer %d chn %d) fail, ret = 0x%x", m_stAttr.voLayer, voChn, ret);
                DisableChns(m_stAttr.voLayer, voChn);
                throw 1;
            }
        }
    } catch (...) {
        if (LAYER_ENABLED == (nState & LAYER_ENABLED)) {
            AX_VO_DisableVideoLayer(m_stAttr.voLayer);
        }

        if (LAYER_BINDED == (nState & LAYER_BINDED)) {
            AX_VO_UnBindVideoLayer(m_stAttr.voLayer, m_stAttr.voDev);
        }

        if (FBLAYER_BINDED == (nState & FBLAYER_BINDED)) {
            AX_VO_UnBindGraphicLayer(m_stAttr.fbLayer, m_stAttr.voDev);
        }

        if (VODEV_ENABLED == (nState & VODEV_ENABLED)) {
            AX_VO_Disable(m_stAttr.voDev);
        }

        if (LAYER_CREATED == (nState & LAYER_CREATED)) {
            AX_VO_DestroyVideoLayer(m_stAttr.voLayer);
        }

        return AX_FALSE;
    }
#endif

    m_bInited = AX_TRUE;
    LOG_M_D(VO, "%s: ---", __func__);
    return AX_TRUE;
}

AX_BOOL CVO::DeInit(AX_VOID) {
    LOG_M_D(VO, "%s: +++", __func__);

    if (!m_bInited) {
        return AX_TRUE;
    }
#ifdef __DUMMY_VO__
#else
    AX_S32 ret;
    ret = AX_VO_DisableVideoLayer(m_stAttr.voLayer);
    if (0 != ret) {
        LOG_M_E(VO, "AX_VO_DisableVideoLayer(layer %d) fail, ret = 0x%x", m_stAttr.voLayer, ret);
        return AX_FALSE;
    }

    ret = AX_VO_UnBindVideoLayer(m_stAttr.voLayer, m_stAttr.voDev);
    if (0 != ret) {
        LOG_M_E(VO, "AX_VO_UnBindVideoLayer(layer %d dev %d) fail, ret = 0x%x", m_stAttr.voLayer, m_stAttr.voDev, ret);
        return AX_FALSE;
    }

    if (m_stAttr.fbLayer != INVALID_LAYER_ID) {
        ret = AX_VO_UnBindGraphicLayer(m_stAttr.fbLayer, m_stAttr.voDev);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_UnBindGraphicLayer(layer %d dev %d) fail, ret = 0x%x", m_stAttr.fbLayer, m_stAttr.voDev, ret);
            return AX_FALSE;
        }
    }

    ret = AX_VO_Disable(m_stAttr.voDev);
    if (0 != ret) {
        LOG_M_E(VO, "AX_VO_Disable(dev %d) fail, ret = 0x%x", m_stAttr.voDev, ret);
        return AX_FALSE;
    }

    ret = AX_VO_DestroyVideoLayer(m_stAttr.voLayer);
    if (0 != ret) {
        LOG_M_E(VO, "AX_VO_DestroyVideoLayer(layer %d) fail, ret = 0x%x", m_stAttr.voLayer, ret);
        return AX_FALSE;
    }

    if (AX_INVALID_POOLID != m_LayerPool) {
        if (!DestroyPool(m_LayerPool)) {
            return AX_FALSE;
        }
    }

#endif

    m_bInited = AX_FALSE;
    LOG_M_D(VO, "%s: ---", __func__);
    return AX_TRUE;
}

AX_BOOL CVO::Start(AX_VOID) {
    LOG_M_D(VO, "%s: +++", __func__);

#ifdef __DUMMY_VO__
#else
    AX_S32 ret;
    const AX_U32 TOTAL_CHN_NUM = m_arrChns.size();
    for (VO_CHN voChn = 0; voChn < TOTAL_CHN_NUM; ++voChn) {
        LOG_MM_I(VO, "enable voChn %d: [(%d, %d) %dx%d], depth %d prior %d", voChn, m_arrChns[voChn].stRect.u32X,
                 m_arrChns[voChn].stRect.u32Y, m_arrChns[voChn].stRect.u32Width, m_arrChns[voChn].stRect.u32Height,
                 m_arrChns[voChn].u32FifoDepth, m_arrChns[voChn].u32Priority);

        ret = AX_VO_EnableChn(m_stAttr.voLayer, voChn);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_EnableChn(layer %d chn %d) fail, ret = 0x%x", m_stAttr.voLayer, voChn, ret);

            for (VO_CHN j = 0; j < voChn; ++j) {
                AX_VO_DisableChn(m_stAttr.voLayer, j);
            }
            return AX_FALSE;
        }
    }

    /* Small windows are hidden by default*/
    if (m_nVideoChnCount > 1) {
        EnableScreen(AX_FALSE);
    }
    m_bStarted = AX_TRUE;

#endif

    LOG_M_D(VO, "%s: ---", __func__);
    return AX_TRUE;
}

AX_BOOL CVO::Stop(AX_VOID) {
    LOG_M_D(VO, "%s: +++", __func__);

    AX_S32 ret;

    /* first, disable sending frame any more */
    m_bStarted = AX_FALSE;

    const AX_U32 TOTAL_CHN_NUM = m_arrChns.size();
    for (VO_CHN voChn = 0; voChn < TOTAL_CHN_NUM; ++voChn) {
        ret = AX_VO_DisableChn(m_stAttr.voLayer, voChn);
        if (0 != ret) {
            LOG_M_E(VO, "AX_VO_DisableChn(layer %d chn %d) fail, ret = 0x%x", m_stAttr.voLayer, voChn, ret);
            return AX_FALSE;
        }
    }

    LOG_M_D(VO, "%s: ---", __func__);
    return AX_TRUE;
}

AX_BOOL CVO::InitLayout(AX_U32 nVideoCount) {
    m_arrChns.clear();

    AX_VO_CHN_ATTR_T stChnAttr;
    memset(&stChnAttr, 0, sizeof(stChnAttr));
    stChnAttr.u32FifoDepth = 1; /* default depth: 1 */
    stChnAttr.u32Priority = 0;
    stChnAttr.bKeepPrevFr = AX_TRUE;

    for (AX_U8 i = 0; i < nVideoCount; i++) {
        stChnAttr.stRect.u32X = 0;
        stChnAttr.stRect.u32Y = 0;
        stChnAttr.stRect.u32Width = m_stAttr.arrChns[i].nChnResolution[0];
        stChnAttr.stRect.u32Height = m_stAttr.arrChns[i].nChnResolution[1];
        m_arrChns.push_back(stChnAttr);
    }

    return AX_TRUE;
}

AX_BOOL CVO::GetDispInfoFromIntfSync(AX_VO_INTF_SYNC_E eIntfSync, AX_VO_RECT_T& stArea, AX_U32& nHz) {
    stArea.u32X = 0;
    stArea.u32Y = 0;
    switch (eIntfSync) {
        case AX_VO_OUTPUT_1080P25:
            stArea.u32Width = 1920;
            stArea.u32Height = 1080;
            nHz = 25;
            break;
        case AX_VO_OUTPUT_1080P30:
            stArea.u32Width = 1920;
            stArea.u32Height = 1080;
            nHz = 30;
            break;
        case AX_VO_OUTPUT_1080P50:
            stArea.u32Width = 1920;
            stArea.u32Height = 1080;
            nHz = 50;
            break;
        case AX_VO_OUTPUT_1080P60:
            stArea.u32Width = 1920;
            stArea.u32Height = 1080;
            nHz = 60;
            break;
        case AX_VO_OUTPUT_3840x2160_25:
            stArea.u32Width = 3840;
            stArea.u32Height = 2160;
            nHz = 25;
            break;
        case AX_VO_OUTPUT_3840x2160_30:
            stArea.u32Width = 3840;
            stArea.u32Height = 2160;
            nHz = 30;
            break;
        case AX_VO_OUTPUT_3840x2160_50:
            stArea.u32Width = 3840;
            stArea.u32Height = 2160;
            nHz = 50;
            break;
        case AX_VO_OUTPUT_3840x2160_60:
            stArea.u32Width = 3840;
            stArea.u32Height = 2160;
            nHz = 60;
            break;
        case AX_VO_OUTPUT_4096x2160_25:
            stArea.u32Width = 4096;
            stArea.u32Height = 2160;
            nHz = 25;
            break;
        case AX_VO_OUTPUT_4096x2160_30:
            stArea.u32Width = 4096;
            stArea.u32Height = 2160;
            nHz = 30;
            break;
        case AX_VO_OUTPUT_4096x2160_50:
            stArea.u32Width = 4096;
            stArea.u32Height = 2160;
            nHz = 50;
            break;
        case AX_VO_OUTPUT_4096x2160_60:
            stArea.u32Width = 4096;
            stArea.u32Height = 2160;
            nHz = 60;
            break;
        case AX_VO_OUTPUT_1024x600_60:
            stArea.u32Width = 1024;
            stArea.u32Height = 600;
            nHz = 60;
            break;
        case AX_VO_OUTPUT_USER:
            stArea.u32Width = m_stSyncInfos.u16Hact;
            stArea.u32Height = m_stSyncInfos.u16Vact;
            nHz = m_stSyncInfos.u32Pclk * 1000 /
                  ((m_stSyncInfos.u16Vact + m_stSyncInfos.u16Vbb + m_stSyncInfos.u16Vfb + m_stSyncInfos.u16Vpw) *
                   (m_stSyncInfos.u16Hact + m_stSyncInfos.u16Hbb + m_stSyncInfos.u16Hfb + m_stSyncInfos.u16Hpw));
            break;
        default:
            LOG_M_E(VO, "%s: Nonsupport device %d", __func__, eIntfSync);
            return AX_FALSE;
    }

    return AX_TRUE;
}

vector<AX_VO_RECT_T> CVO::GetVideoLayout(AX_VOID) {
    vector<AX_VO_RECT_T> layout;
    AX_U32 nCount = m_arrChns.size();
    layout.reserve(nCount);
    for (AX_U32 voChn = 0; voChn < nCount; ++voChn) {
        layout.push_back(m_arrChns[voChn].stRect);
    }

    return layout;
}

AX_BOOL CVO::SendFrame(VO_CHN voChn, CAXFrame& axFrame, AX_S32 nTimeOut /* = -1 */) {
    if (!m_bStarted) {
        return AX_TRUE;
    }

    LOG_M_I(VO, "send2vo vdGrp %d vdChn %d frame %lld pts %lld phy 0x%llx to layer %d chn %d, blkId 0x%x, +++", axFrame.nGrp, axFrame.nChn,
            axFrame.stFrame.stVFrame.stVFrame.u64SeqNum, axFrame.stFrame.stVFrame.stVFrame.u64PTS,
            axFrame.stFrame.stVFrame.stVFrame.u64PhyAddr[0], m_stAttr.voLayer, voChn, axFrame.stFrame.stVFrame.stVFrame.u32BlkId[0]);

    AX_S32 ret = AX_VO_SendFrame(m_stAttr.voLayer, voChn, &axFrame.stFrame.stVFrame.stVFrame, -1);

    LOG_M_D(VO, "send2vo vdGrp %d vdChn %d frame %lld pts %lld phy 0x%llx to layer %d chn %d, blkId 0x%x, --- ret = 0x%x", axFrame.nGrp,
            axFrame.nChn, axFrame.stFrame.stVFrame.stVFrame.u64SeqNum, axFrame.stFrame.stVFrame.stVFrame.u64PTS,
            axFrame.stFrame.stVFrame.stVFrame.u64PhyAddr[0], m_stAttr.voLayer, voChn, axFrame.stFrame.stVFrame.stVFrame.u32BlkId[0], ret);
    if (0 != ret) {
        if (m_bStarted) {
            LOG_M_E(VO, "AX_VO_SendFrame(layer %d, chn %d, timeout %d): 0x%x", m_stAttr.voLayer, voChn, nTimeOut, ret);
        }
        return AX_FALSE;
    }

    return AX_TRUE;
}

AX_BOOL CVO::CreatePools(AX_U32 nLayerDepth) {
    AX_POOL_CONFIG_T stPoolCfg;
    memset(&stPoolCfg, 0, sizeof(stPoolCfg));
    stPoolCfg.MetaSize = 512;
    stPoolCfg.CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    strcpy((AX_CHAR*)stPoolCfg.PartitionName, "anonymous");

    if (AX_VO_MODE_OFFLINE == m_stAttr.enMode) {
        /* [0]: video layer pool */
        stPoolCfg.BlkSize = m_stAttr.nW * m_stAttr.nH * 3 / 2;
        stPoolCfg.BlkCnt = nLayerDepth;
        sprintf((AX_CHAR*)stPoolCfg.PoolName, "vo_dev%d_layer_pool", m_stAttr.voDev);
        m_LayerPool = CAXPoolManager::GetInstance()->CreatePool(stPoolCfg);
        if (AX_INVALID_POOLID == m_LayerPool) {
            return AX_FALSE;
        }
    } else {
        m_LayerPool = AX_INVALID_POOLID;
    }

    return AX_TRUE;
}

AX_BOOL CVO::DestroyPool(AX_POOL& pool) {
    if (AX_INVALID_POOLID == pool) {
        LOG_M_E(VO, "Invalid pool id");
        return AX_FALSE;
    }

    AX_S32 ret = AX_POOL_DestroyPool(pool);
    if (0 != ret) {
        LOG_MM_E(VO, "AX_POOL_DestroyPool(pool %d) fail, ret = 0x%x", pool, ret);
        return AX_FALSE;
    }

    pool = AX_INVALID_POOLID;
    return AX_TRUE;
}

AX_BOOL CVO::EnableScreen(AX_BOOL bEnable) {
    if (!m_bInited) {
        return AX_FALSE;
    }

    // The channel of small windosw is the last one
    VO_CHN nChn = m_nVideoChnCount - 1;
    if (bEnable) {
        AX_S32 ret = AX_VO_ShowChn(m_stAttr.voLayer, nChn);
        if (0 != ret) {
            LOG_MM_E(VO, "AX_VO_DisableChn(layer:%d, chn:%d) fail, ret = 0x%x", m_stAttr.voLayer, nChn, ret);
            return AX_FALSE;
        }
    } else {
        AX_S32 ret = AX_VO_HideChn(m_stAttr.voLayer, nChn);
        if (0 != ret) {
            LOG_MM_E(VO, "AX_VO_DisableChn(layer:%d, chn:%d) fail, ret = 0x%x", m_stAttr.voLayer, nChn, ret);
            return AX_FALSE;
        }
    }

    return AX_TRUE;
}
AX_VOID CVO::InitSyncInfo() {
    m_stSyncInfos.bSynm = AX_FALSE;
    m_stSyncInfos.bIop = AX_TRUE;
    m_stSyncInfos.u16Vact = 800;
    m_stSyncInfos.u16Vbb = 12;
    m_stSyncInfos.u16Vfb = 28;
    m_stSyncInfos.u16Hact = 1280;
    m_stSyncInfos.u16Hbb = 68;
    m_stSyncInfos.u16Hfb = 92;
    m_stSyncInfos.u16Hmid = 0;
    m_stSyncInfos.u16Bvact = 0;
    m_stSyncInfos.u16Bvbb = 0;
    m_stSyncInfos.u16Bvfb = 0;
    m_stSyncInfos.u16Hpw = 20;
    m_stSyncInfos.u16Vpw = 10;
    m_stSyncInfos.u32Pclk = 74250;
    m_stSyncInfos.bIdv = AX_TRUE;
    m_stSyncInfos.bIhs = AX_TRUE;
    m_stSyncInfos.bIvs = AX_TRUE;
}
