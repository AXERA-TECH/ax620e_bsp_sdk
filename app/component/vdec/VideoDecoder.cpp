/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "VideoDecoder.h"
#include "GlobalDef.h"
#include "ax_buffer_tool.h"

#define VDEC "VDEC"
// #define START_RECV
CVideoDecoder::CVideoDecoder(VDEC_GRP_CONFIG_T &tConfig) : CAXStage((std::string)VDEC), m_tGrpInfo(tConfig), m_nGrp(tConfig.nGrp) {
}

AX_BOOL CVideoDecoder::Init() {
    LOG_MM_C(VDEC, "+++");
    memset(&m_stAttr, 0, sizeof(m_stAttr));
    m_stAttr.enCodecType = m_tGrpInfo.ePayloadType;
    m_stAttr.enOutOrder = AX_VDEC_OUTPUT_ORDER_DISP;
    m_stAttr.u32PicWidth = m_tGrpInfo.nWidth;   /* pic width */
    m_stAttr.u32PicHeight = m_tGrpInfo.nHeight; /* pic height */
    m_stAttr.u32FrameHeight = 0;                // m_tGrpInfo.nHeight; /*Max pic height*/
    m_stAttr.u32StreamBufSize = (m_tGrpInfo.nWidth * m_tGrpInfo.nHeight * 3 / 2);
    m_stAttr.enVdecVbSource = AX_POOL_SOURCE_USER;
    m_stAttr.u32FrameBufCnt = m_tGrpInfo.nFrameOutFifoDepth;
    m_stAttr.enInputMode = m_tGrpInfo.eInputMode;
    m_tGrpInfo.eVdecMode = m_tGrpInfo.eVdecMode;
    m_stAttr.enLinkMode = AX_LINK_MODE;

    AX_S32 ret = AX_SUCCESS;
    do {
        ret = AX_VDEC_CreateGrp(m_nGrp, &m_stAttr);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "AX_VDEC_CreateGrp failed! 0x%x \n", ret);
            break;
        }

        ret = InitPool();
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "InitPool failed! 0x%x \n", ret);
            break;
        }

        AX_VDEC_GRP_PARAM_T stGrpParam;
        ret = AX_VDEC_GetGrpParam(m_nGrp, &stGrpParam);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "AX_VDEC_GetGrpParam failed! 0x%x\n", ret);
            break;
        }

        stGrpParam.enVdecMode = m_tGrpInfo.eVdecMode;
        ret = AX_VDEC_SetGrpParam(m_nGrp, &stGrpParam);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "AX_VDEC_SetGrpParam failed! 0x%x\n", ret);
            break;
        }

        ret = AX_VDEC_SetDisplayMode(m_nGrp, m_tGrpInfo.eDisplayMode);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "AX_VDEC_SetDisplayMode failed! ret:0x%x\n", ret);
            break;
        }

    } while (0);
    LOG_MM_C(VDEC, "---");

    return ret == AX_SUCCESS ? AX_TRUE : AX_FALSE;
}

AX_BOOL CVideoDecoder::Start() {
    LOG_MM_C(VDEC, "+++");
    AX_S32 ret = 0;
    AX_VDEC_RECV_PIC_PARAM_T tRecvParam = {0};
    ret = AX_VDEC_StartRecvStream(m_nGrp, &tRecvParam);
    if (ret != AX_SUCCESS) {
        LOG_MM_E(VDEC, "AX_VDEC_StartRecvStream failed! ret:0x%x", ret);
        return AX_FALSE;
    }

#ifdef START_RECV
    if (!m_Thread.Start(std::bind(&CVideoDecoder::RecvThread, this, std::placeholders::_1), nullptr, "APP_FILESTREAM")) {
        LOG_MM_E(VDEC, "create parse thread fail");
        return AX_FALSE;
    }
#endif
    bRunning = AX_TRUE;
    LOG_MM_C(VDEC, "---");

    return AX_TRUE;
}

AX_BOOL CVideoDecoder::Send(AX_U8 *pData, AX_U32 nLen) {
    if (!bRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        return AX_TRUE;
    }
    AX_U32 nStep = 1000000 / m_tGrpInfo.fFrameRate;
    static AX_U64 u64PTS = 0;

    AX_VDEC_STREAM_T tStream;
    memset(&tStream, 0, sizeof(tStream));
    tStream.u32StreamPackLen = nLen;
    tStream.u64PTS = u64PTS;
    if (nLen) {
        tStream.pu8Addr = pData;
        tStream.bEndOfFrame = AX_TRUE;
        tStream.bEndOfStream = AX_FALSE;
    } else {
        tStream.pu8Addr = NULL;
        tStream.bEndOfFrame = AX_TRUE;
        tStream.bEndOfStream = AX_TRUE;
    }

    AX_S32 ret = AX_VDEC_SendStream(m_nGrp, &tStream, -1);
    if (ret != AX_SUCCESS) {
        LOG_MM_E(VDEC, "AX_VDEC_SendStream FAILED! ret:0x%x", ret);
        return AX_FALSE;
    }
    u64PTS += nStep;
    return AX_TRUE;
}

AX_BOOL CVideoDecoder::Stop() {
    LOG_MM_C(VDEC, "+++");
#ifdef START_RECV
    if (m_Thread.IsRunning()) {
        m_Thread.Stop();
        m_Thread.Join();
    }
#endif
    AX_S32 ret = AX_SUCCESS;
    bRunning = AX_FALSE;
    VdecSendEndOfStream();

    ret = AX_VDEC_StopRecvStream(m_nGrp);
    if (ret != AX_SUCCESS) {
        LOG_MM_E(VDEC, "AX_VDEC_StopRecvStream failed! ret:0x%x", ret);
    }

    ret = AX_VDEC_ResetGrp(m_nGrp);
    if (ret != AX_SUCCESS) {
        LOG_MM_E(VDEC, "AX_VDEC_ResetGrp failed! ret:0x%x", ret);
    }

    LOG_MM_C(VDEC, "---");

    return ret == AX_SUCCESS ? AX_TRUE : AX_FALSE;
}

AX_BOOL CVideoDecoder::DeInit() {
    LOG_MM_C(VDEC, "+++");
#ifdef START_RECV

    if (m_Thread.IsRunning()) {
        LOG_MM_E(VDEC, "Parse thread is running");
        return AX_FALSE;
    }
#endif
    AX_S32 ret = AX_SUCCESS;
    do {
        ret = AX_VDEC_DetachPool(m_nGrp);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "AX_VDEC_DetachPool failed! ret:0x%x", ret);
            break;
        }

        ret = AX_VDEC_DestroyGrp(m_nGrp);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "AX_VDEC_DestroyGrp failed! ret:0x%x", ret);
            break;
        }

        ret = AX_POOL_DestroyPool(m_nPool);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "AX_POOL_DestroyPool failed! ret:0x%x", ret);
            break;
        }
    } while (0);
    LOG_MM_C(VDEC, "---");

    return ret == AX_SUCCESS ? AX_TRUE : AX_FALSE;
}

AX_S32 CVideoDecoder::InitPool() {
    AX_S32 s32Ret = AX_SUCCESS;
    /* vdec use pool to alloc output buffer */
    AX_POOL_CONFIG_T stPoolConfig = {0};
    AX_U32 nStride = ALIGN_UP(m_stAttr.u32PicWidth, VDEC_WIDTH_ALIGN);
    AX_U32 nBufferSize = AX_VDEC_GetPicBufferSize(nStride, m_stAttr.u32PicHeight, m_stAttr.enCodecType);

    memset(&stPoolConfig, 0, sizeof(AX_POOL_CONFIG_T));
    stPoolConfig.MetaSize = 512;
    stPoolConfig.BlkCnt = m_tGrpInfo.nFrameOutFifoDepth;
    stPoolConfig.BlkSize = nBufferSize;
    stPoolConfig.CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    memset(stPoolConfig.PartitionName, 0, sizeof(stPoolConfig.PartitionName));
    strcpy((AX_CHAR *)stPoolConfig.PartitionName, "anonymous");
    do {
        m_nPool = AX_POOL_CreatePool(&stPoolConfig);
        if (AX_INVALID_POOLID == m_nPool) {
            LOG_MM_E(VDEC, "AX_POOL_CreatePool err");
            break;
        }

        s32Ret = AX_VDEC_AttachPool(m_nGrp, m_nPool);
        if (s32Ret != AX_SUCCESS) {
            AX_POOL_DestroyPool(m_nPool);
            LOG_MM_E(VDEC, "Attach pool err. 0x%x\n", s32Ret);
            break;
        }

        LOG_MM_I(VDEC, "FramePoolInit successfully m_nPool: %d nFrameOutFifoDepth:%d, nBufferSize:%d ", m_nPool,
                 m_tGrpInfo.nFrameOutFifoDepth, nBufferSize);
    } while (0);

    return s32Ret;
}

AX_VOID CVideoDecoder::VdecSendEndOfStream() {
    LOG_MM_C(VDEC, "+++");
    AX_S32 sRet = 0;
    AX_VDEC_STREAM_T tStrInfo = {0};
    tStrInfo.bEndOfStream = AX_TRUE;
    sRet = AX_VDEC_SendStream(m_nGrp, &tStrInfo, -1);
    if (sRet != AX_SUCCESS) {
        if (sRet != AX_ERR_VDEC_NOT_PERM && sRet != AX_ERR_VDEC_UNEXIST) {
            LOG_MM_E(VDEC, "m_nGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x ", m_nGrp, sRet);
        }
    }

    LOG_MM_C(VDEC, "---");
    return;
}

AX_VOID CVideoDecoder::RecvThread(AX_VOID *pArg) {
    AX_S32 ret;
    while (bRunning) {
        AX_VIDEO_FRAME_INFO_T stFrameInfo;
        ret = AX_VDEC_GetFrame(m_nGrp, &stFrameInfo, -1);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "m_nGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x ", m_nGrp, ret);
        }

        ret = AX_VDEC_ReleaseFrame(m_nGrp, &stFrameInfo);
        if (ret != AX_SUCCESS) {
            LOG_MM_E(VDEC, "m_nGrp=%d, AX_VDEC_ReleaseFrame FAILED! ret:0x%x ", m_nGrp, ret);
        }
    }
}