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
#include <atomic>
#include <string>
#include <vector>
#include "AXFrame.hpp"
#include "ax_vo_api.h"

#define PRIMARY_CHN (0)
#define MAX_VO_CHN_NUM (AX_VO_CHN_MAX)
#define INVALID_LAYER_ID ((VO_LAYER)-1)

typedef struct VO_CHN_INFO_S {
    AX_U32 nDepth{0};
    AX_U32 nPriority{0};
    AX_S16 nChnResolution[2]{0};
} VO_CHN_INFO_T;

typedef struct VO_ATTR_S {
    VO_DEV voDev;
    AX_VO_MODE_E enMode;
    VO_LAYER voLayer;
    VO_LAYER fbLayer;
    AX_VO_INTF_TYPE_E enIntfType;
    AX_VO_INTF_SYNC_E enIntfSync;
    AX_VO_LAYER_SYNC_MODE_E enLayerSync;
    AX_U32 nW;
    AX_U32 nH;
    AX_U32 nHz;
    AX_U32 nBgClr;
    AX_U32 nLayerDepth;
    AX_U32 nTolerance;
    std::vector<VO_CHN_INFO_T> arrChns; /* video channels */

    VO_ATTR_S(AX_VOID) {
        voDev = 0;
        enMode = AX_VO_MODE_OFFLINE;
        voLayer = 0;
        fbLayer = INVALID_LAYER_ID;
        enIntfType = AX_VO_INTF_LVDS;
        enIntfSync = AX_VO_OUTPUT_1080P60;
        nW = 0;
        nH = 0;
        nHz = 0;
        nBgClr = 0x000000; /* RGB888 black */
        nLayerDepth = 0;
        nTolerance = 0;
    }
} VO_ATTR_T;

/*
 * @brief: no graphic layer, just video layer
 *
 */
class CVO {
public:
    CVO(AX_VOID);
    virtual ~CVO(AX_VOID) = default;

    AX_BOOL Init(const VO_ATTR_T& stAttr);
    AX_BOOL DeInit(AX_VOID);

    std::vector<AX_VO_RECT_T> GetVideoLayout(AX_VOID);

    AX_BOOL Start(AX_VOID);
    AX_BOOL Stop(AX_VOID);

    AX_BOOL SendFrame(VO_CHN voChn, CAXFrame& axFrame, AX_S32 nTimeOut = -1);
    const VO_ATTR_T& GetAttr(AX_VOID) const;
    VO_LAYER GetVideoLayer(AX_VOID) const;

    /**
     * @brief :Enable/Disable screen
     *
     * @param bEnable
     * @return AX_BOOL
     */
    AX_BOOL EnableScreen(AX_BOOL bEnable);

protected:
    AX_BOOL InitLayout(AX_U32 nVideoCount);
    AX_VOID InitSyncInfo();
    AX_BOOL GetDispInfoFromIntfSync(AX_VO_INTF_SYNC_E eIntfSync, AX_VO_RECT_T& stArea, AX_U32& nHz);

    AX_BOOL CreatePools(AX_U32 nLayerFifoDepth);
    AX_BOOL DestroyPool(AX_POOL& pool);

protected:
    VO_ATTR_T m_stAttr;
    AX_BOOL m_bInited{AX_FALSE};
    std::atomic<AX_BOOL> m_bStarted = {AX_FALSE};
    AX_U32 m_nVideoChnCount{0};
    std::vector<AX_VO_CHN_ATTR_T> m_arrChns;
    AX_POOL m_LayerPool{AX_INVALID_POOLID};
    AX_BOOL m_bDpmsOn = {AX_TRUE};
    AX_VO_SYNC_INFO_T m_stSyncInfos;

    /* logo and nonsignal resouce files */
    struct VO_RES_INFO_T {
        AX_BOOL bShow;
        std::string strPath;
        AX_U32 nW;
        AX_U32 nH;
        AX_IMG_FORMAT_E eImgFormat;
        AX_POOL pool;
        VO_RES_INFO_T(AX_VOID) {
            bShow = AX_FALSE;
            nW = 0;
            nH = 0;
            eImgFormat = AX_FORMAT_YUV420_SEMIPLANAR;
            pool = AX_INVALID_POOLID;
        }
    } m_rcNoVideo;
};

inline const VO_ATTR_T& CVO::GetAttr(AX_VOID) const {
    return m_stAttr;
}

inline VO_LAYER CVO::GetVideoLayer(AX_VOID) const {
    return m_stAttr.voLayer;
}
