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
#include <map>
#include <vector>
#include "AXThread.hpp"
#include "IObserver.h"
#include "ax_global_type.h"
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

typedef struct STREAM_ATTR_S {
    std::string strPath; /* stream path for RTSP URL or file */
} STREAM_ATTR_T;

enum class STREAM_TYPE_E { FILE = 0, RTSP = 1 };

typedef struct STREAMER_INFO_S {
    std::string strPath;
    STREAM_TYPE_E eStreamType;
    AX_U32 nWidth;
    AX_U32 nHeight;

    STREAMER_INFO_S(AX_VOID) {
        eStreamType = STREAM_TYPE_E::FILE;
        nWidth = 0;
        nHeight = 0;
    }
} STREAMER_INFO_T;

#define MAX_BUFFER_SIZE (1024 * 10)

class CFileStreamer {
public:
    CFileStreamer(STREAM_ATTR_T &stAttr);
    virtual ~CFileStreamer(AX_VOID) = default;

    AX_BOOL Init();
    AX_BOOL DeInit(AX_VOID);

    AX_BOOL Start(AX_VOID);
    AX_BOOL Stop(AX_VOID);

    AX_VOID RegObserver(IObserver *pObserver);
    AX_VOID UnregObserver(IObserver *pObserver);

private:
    AX_VOID ParseThread(AX_VOID *pArg);
    AX_VOID NotifyAll(const AX_U8 *pData, AX_U32 nLen);

private:
    CAXThread m_Thread;
    STREAM_ATTR_T m_stAttr;
    AX_BOOL m_bThreadRunning{AX_TRUE};
    std::vector<IObserver *> m_vecObserver;
    std::mutex m_mtxObserver;
    STREAMER_INFO_T m_stInfo;
    AVFormatContext *m_pAvFmtCtx{nullptr};
    AVBSFContext *m_pAvBSFCtx{nullptr};
    AVPacket *m_pAvPkt{nullptr};
    AX_U32 m_nMaxSendNaluIntervalMilliseconds{0};
    AX_S32 m_nVideoIndex{-1};
};
