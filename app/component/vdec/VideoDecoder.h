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
#include <string.h>
#include <list>
#include <map>
#include <vector>
#include "AXStage.hpp"
#include "ax_vdec_api.h"

#define MAX_VDEC_GRP_NUM AX_VDEC_MAX_GRP_NUM
#define MAX_VDEC_CHANNEL_NUM (3)
#define VDEC_WIDTH_ALIGN (16)
#define VDEC_HEIGHT_ALIGN (16)

typedef struct VDEC_GRP_CONFIG_S {
    AX_BOOL bEnable{AX_FALSE};
    AX_U32 nFrameOutFifoDepth{0};  // frame buffer number
    AX_U32 nGrp{0};
    AX_PAYLOAD_TYPE_E ePayloadType{PT_BUTT};
    AX_VDEC_DISPLAY_MODE_E eDisplayMode{AX_VDEC_DISPLAY_MODE_PREVIEW};
    AX_VDEC_INPUT_MODE_E eInputMode{AX_VDEC_INPUT_MODE_STREAM};
    AX_VDEC_MODE_E eVdecMode{VIDEO_DEC_MODE_IP};
    std::string strPath;
    AX_U32 nWidth{0};
    AX_U32 nHeight{0};
    AX_F32 fFrameRate{0};
} VDEC_GRP_CONFIG_T;

class CVideoDecoder : public CAXStage {
public:
    CVideoDecoder(VDEC_GRP_CONFIG_T& tConfig);
    virtual ~CVideoDecoder(AX_VOID) = default;

    virtual AX_BOOL Init(AX_VOID) override;
    virtual AX_BOOL DeInit(AX_VOID) override;

    virtual AX_BOOL Start(AX_VOID) override;
    virtual AX_BOOL Stop(AX_VOID) override;

    // AX_BOOL AttachPool(AX_VDEC_GRP vdGrp, AX_POOL pool);
    // AX_BOOL DetachPool(AX_VDEC_GRP vdGrp );
    AX_BOOL Send(AX_U8* pData, AX_U32 nLen);

private:
    AX_S32 InitPool();
    AX_VOID VdecSendEndOfStream();
    AX_VOID RecvThread(AX_VOID* pArg);

private:
    VDEC_GRP_CONFIG_T m_tGrpInfo;
    // AX_U32 m_nPool;
    AX_VDEC_GRP m_nGrp;
    AX_VDEC_GRP_ATTR_T m_stAttr;
    CAXThread m_Thread;
    std::atomic<AX_BOOL> bRunning{AX_FALSE};

    AX_U32 m_nPool;
};