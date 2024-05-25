/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "FileStreamer.h"
#include <chrono>
#include <random>
#include "AppLogApi.h"
#include "GlobalDef.h"

#define STREAM "STREAM"

CFileStreamer::CFileStreamer(STREAM_ATTR_T& stAttr) : m_stAttr(stAttr) {
}

// AX_VOID CFileStreamer::ParseThread(AX_VOID* pArg) {
//     LOG_MM_C(STREAM, "+++");
//     FILE* fp = NULL;
//     size_t result;
//     fp = fopen(m_stAttr.strPath.data(), "r");
//     if (NULL == fp) {
//         LOG_MM_E(STREAM, "Open %s Failed.", m_stAttr.strPath.c_str());
//         return;
//     }
//     AX_CHAR* buffer;
//     buffer = new AX_CHAR[MAX_BUFFER_SIZE];
//     while (m_Thread.IsRunning()) {
//         if (feof(fp)) {
//             LOG_MM_E(STREAM, "End of file.\n");
//             fseek(fp, 0, SEEK_SET);
//         }
//         result = fread(buffer, 1, MAX_BUFFER_SIZE - 1, fp);
//         if (result >= 0) {
//             NotifyAll(buffer, result);
//         } else {
//             LOG_MM_E(STREAM, "Read file eror. result:%d", result);
//         }
//     }
//     fclose(fp);
//     delete[] buffer;
//     LOG_MM_C(STREAM, "---");
// }

AX_VOID CFileStreamer::ParseThread(AX_VOID* pArg) {
    AX_S32 ret;

    std::default_random_engine e(time(0));
    std::uniform_int_distribution<unsigned> u(0, m_nMaxSendNaluIntervalMilliseconds);

    while (m_Thread.IsRunning()) {
        ret = av_read_frame(m_pAvFmtCtx, m_pAvPkt);
        if (ret < 0) {
            if (AVERROR_EOF == ret) {
                LOG_MM_C(STREAM, "End of file");
                /* AVSEEK_FLAG_BACKWARD may fail (example: zhuheqiao.mp4), use AVSEEK_FLAG_ANY, but not guarantee seek to I frame */
                av_bsf_flush(m_pAvBSFCtx);
                ret = av_seek_frame(m_pAvFmtCtx, m_nVideoIndex, 0, AVSEEK_FLAG_ANY /* AVSEEK_FLAG_BACKWARD */);
                if (ret < 0) {
                    LOG_M_W(STREAM, "retry to seek stream  to begin");
                    ret = avformat_seek_file(m_pAvFmtCtx, m_nVideoIndex, INT64_MIN, 0, INT64_MAX, AVSEEK_FLAG_BYTE);
                    if (ret < 0) {
                        LOG_M_E(STREAM, "fail to seek stream  to begin, error: %d", ret);
                        break;
                    }
                }
                continue;

            } else {
                LOG_M_E(STREAM, "av_read_frame fail, error: %d", ret);
                break;
            }

        } else {
            if (m_pAvPkt->stream_index == m_nVideoIndex) {
                ret = av_bsf_send_packet(m_pAvBSFCtx, m_pAvPkt);
                if (ret < 0) {
                    av_packet_unref(m_pAvPkt);
                    LOG_M_E(STREAM, "av_bsf_send_packet(stream) fail, error: %d", ret);
                    break;
                }

                while (ret >= 0) {
                    ret = av_bsf_receive_packet(m_pAvBSFCtx, m_pAvPkt);
                    if (ret < 0) {
                        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
                            break;
                        }

                        av_packet_unref(m_pAvPkt);
                        LOG_M_E(STREAM, "av_bsf_receive_packet(stream) fail, error: %d", ret);

                        return;
                    }

                    NotifyAll(m_pAvPkt->data, m_pAvPkt->size);

                    if (m_nMaxSendNaluIntervalMilliseconds > 0) {
                        AX_U32 ms = u(e);
                        if (ms > 10) {
                            //  LOG_M_C(STREAM, "sleep for %d ms", ms);
                            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                        }
                    }
                }
            }

            av_packet_unref(m_pAvPkt);
        }
    }

    LOG_M_C(STREAM, "stop stream ---");
}

AX_BOOL CFileStreamer::Init() {
    LOG_MM_C(STREAM, "+++");

    m_stInfo.strPath = m_stAttr.strPath;

    AVCodecID eCodecID{AV_CODEC_ID_H264};

    AX_S32 ret = 0;
    m_pAvFmtCtx = avformat_alloc_context();
    if (!m_pAvFmtCtx) {
        LOG_M_E(STREAM, "avformat_alloc_context(stream) failed!");
        return AX_FALSE;
    }

    ret = avformat_open_input(&m_pAvFmtCtx, m_stInfo.strPath.c_str(), nullptr, nullptr);
    if (ret < 0) {
        AX_CHAR szError[64] = {0};
        av_strerror(ret, szError, 64);
        LOG_M_E(STREAM, "open %s fail, error: %d, %s", m_stInfo.strPath.c_str(), ret, szError);
        goto __FAIL__;
    }

    ret = avformat_find_stream_info(m_pAvFmtCtx, nullptr);
    if (ret < 0) {
        LOG_M_E(STREAM, "avformat_find_stream_info(stream) fail, error = %d", ret);
        goto __FAIL__;
    }

    for (AX_U32 i = 0; i < m_pAvFmtCtx->nb_streams; i++) {
        if (AVMEDIA_TYPE_VIDEO == m_pAvFmtCtx->streams[i]->codecpar->codec_type) {
            m_nVideoIndex = i;
            break;
        }
    }

    if (-1 == m_nVideoIndex) {
        LOG_M_E(STREAM, "%s has no video stream !", m_stInfo.strPath.c_str());
        goto __FAIL__;
    } else {
        AVStream* pAvs = m_pAvFmtCtx->streams[m_nVideoIndex];
        eCodecID = pAvs->codecpar->codec_id;

        m_stInfo.nWidth = pAvs->codecpar->width;
        m_stInfo.nHeight = pAvs->codecpar->height;

        LOG_M_I(STREAM, "stream %dx%d", m_stInfo.nWidth, m_stInfo.nHeight);
    }

    m_pAvPkt = av_packet_alloc();
    if (!m_pAvPkt) {
        LOG_M_E(STREAM, "Create packet(stream) fail!");
        goto __FAIL__;
    }

    if ((AV_CODEC_ID_H264 == eCodecID) || (AV_CODEC_ID_HEVC == eCodecID)) {
        const AVBitStreamFilter* m_pBSFilter = av_bsf_get_by_name((AV_CODEC_ID_H264 == eCodecID) ? "h264_mp4toannexb" : "hevc_mp4toannexb");
        if (!m_pBSFilter) {
            LOG_M_E(STREAM, "av_bsf_get_by_name(stream) fail!");
            goto __FAIL__;
        }

        ret = av_bsf_alloc(m_pBSFilter, &m_pAvBSFCtx);
        if (ret < 0) {
            LOG_M_E(STREAM, "av_bsf_alloc(stream) fail, error:%d", ret);
            goto __FAIL__;
        }

        ret = avcodec_parameters_copy(m_pAvBSFCtx->par_in, m_pAvFmtCtx->streams[m_nVideoIndex]->codecpar);
        if (ret < 0) {
            LOG_M_E(STREAM, "avcodec_parameters_copy(stream) fail, error:%d", ret);
            goto __FAIL__;
        } else {
            m_pAvBSFCtx->time_base_in = m_pAvFmtCtx->streams[m_nVideoIndex]->time_base;
        }

        ret = av_bsf_init(m_pAvBSFCtx);
        if (ret < 0) {
            LOG_M_E(STREAM, "av_bsf_init(stream) fail, error:%d", ret);
            goto __FAIL__;
        }
    }

    LOG_MM_C(STREAM, "---");
    return AX_TRUE;

__FAIL__:
    DeInit();
    return AX_FALSE;
}

AX_BOOL CFileStreamer::DeInit(AX_VOID) {
    LOG_MM_D(STREAM, "+++");

    if (m_Thread.IsRunning()) {
        LOG_M_E(STREAM, "%s: STREAM thread is still running", __func__);
        return AX_FALSE;
    }

    if (m_pAvPkt) {
        av_packet_free(&m_pAvPkt);
        m_pAvPkt = nullptr;
    }

    if (m_pAvBSFCtx) {
        av_bsf_free(&m_pAvBSFCtx);
        m_pAvBSFCtx = nullptr;
    }

    if (m_pAvFmtCtx) {
        avformat_close_input(&m_pAvFmtCtx);
        /*  avformat_close_input will free ctx
            http://ffmpeg.org/doxygen/trunk/STREAM_8c_source.html
        */
        // avformat_free_context(m_pAvFmtCtx);
        m_pAvFmtCtx = nullptr;
    }

    LOG_MM_C(STREAM, "---");
    return AX_TRUE;
}

AX_BOOL CFileStreamer::Start(AX_VOID) {
    LOG_MM_C(STREAM, "+++");
    if (!m_Thread.Start(std::bind(&CFileStreamer::ParseThread, this, std::placeholders::_1), nullptr, "APP_FILESTREAM")) {
        LOG_MM_E(STREAM, "create parse thread fail");
        return AX_FALSE;
    }
    LOG_MM_C(STREAM, "---");
    return AX_TRUE;
}

AX_BOOL CFileStreamer::Stop(AX_VOID) {
    LOG_MM_C(STREAM, "+++");
    if (m_Thread.IsRunning()) {
        m_Thread.Stop();
        m_Thread.Join();
    }
    LOG_MM_C(STREAM, "---");

    return AX_TRUE;
}

AX_VOID CFileStreamer::RegObserver(IObserver* pObserver) {
    LOG_MM_C(STREAM, "+++");

    if (nullptr != pObserver) {
        _OBS_TRANS_ATTR_T stTransAttr;
        if (pObserver->OnRegisterObserver(E_OBS_TARGET_TYPE_STREAM, 0, 0, &stTransAttr)) {
            std::lock_guard<std::mutex> lock(m_mtxObserver);
            m_vecObserver.emplace_back(pObserver);
        }
    }
    LOG_MM_C(STREAM, "---");
}

AX_VOID CFileStreamer::UnregObserver(IObserver* pObserver) {
    if (nullptr == pObserver) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mtxObserver);
    for (auto it = m_vecObserver.begin(); it != m_vecObserver.end(); it++) {
        if (*it == pObserver) {
            m_vecObserver.erase(it);
            break;
        }
    }
}

AX_VOID CFileStreamer::NotifyAll(const AX_U8* pData, AX_U32 nLen) {
    std::lock_guard<std::mutex> lock(m_mtxObserver);
    if (m_vecObserver.empty()) {
        LOG_MM_E(STREAM, "Observer is empty.");
        return;
    }

    for (auto it : m_vecObserver) {
        it->OnRecvData(E_OBS_TARGET_TYPE_STREAM, 0, nLen, (AX_VOID*)pData);
    }
}