/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <signal.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include "sample_global.h"
#include "sample_unit_test.h"
#include <assert.h>

#define SAMPLE_TEST_GRP_NUM (1)

static SAMPLE_VENC_SENDFRAME_PARA_T gstFrmParam[AX_MAX_VENC_CHN_NUM];
static SAMPLE_VENC_GETSTREAM_PARA_T gstStrmParam[AX_MAX_VENC_CHN_NUM];

#define SAMPLE_STRM_NAME_LEN (20)

static AX_CHAR gSelectStrmName[AX_MAX_VENC_CHN_NUM][SAMPLE_STRM_NAME_LEN];
static FILE *gStrmFile[AX_MAX_VENC_CHN_NUM] = {NULL};

static AX_BOOL gLoopExit = AX_FALSE;
static void SigHandler(AX_S32 signo)
{
    SAMPLE_LOG("catch signal(%d).\n", signo);
    gLoopExit = AX_TRUE;
}

static AX_VOID *SAMPLE_VENC_EpollGetStreamProc(AX_VOID *arg);
static AX_S32 SAMPLE_VENC_EpollStartGetStream(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg);
static AX_S32 SAMPLE_VENC_EpollStopGetStream(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg);
static AX_VOID SampleEpollGetStreamInit(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg, SAMPLE_VENC_CMD_PARA_T *pCml);

AX_S32 UTestEpoll(SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret;
    AX_U32 chnNum;
    AX_S32 chnIdx;
    AX_PAYLOAD_TYPE_E enType;
    SAMPLE_VENC_RC_E enRcMode = pCml->rcMode;
    AX_U64 gVencCaseLoopExit = 0;

    chnNum = (pCml->defaultUt == VENC_TEST_ALL_CASE) ? UT_DEFAULT_ENC_NUM : pCml->chnNum;

    signal(SIGINT, SigHandler);

    if (chnNum < 1)
        return -1;

    for (chnIdx = 0; chnIdx < chnNum; chnIdx++) {
        memset(&gstFrmParam[chnIdx], 0, sizeof(SAMPLE_VENC_SENDFRAME_PARA_T));
        memset(&gstStrmParam[chnIdx], 0, sizeof(SAMPLE_VENC_GETSTREAM_PARA_T));

        if (pCml->bChnCustom)
            enType = SampleGetCodecType(pCml->codecType);
        else
            enType = SampleGetCodecType(chnIdx % SAMPLE_ALL_CODEC_TYPE);

        if (PT_H264 == enType)
            sprintf(gSelectStrmName[chnIdx], "es_chn%d_ut%d.264", chnIdx, pCml->ut);
        else if (PT_H265 == enType)
            sprintf(gSelectStrmName[chnIdx], "es_chn%d_ut%d.265", chnIdx, pCml->ut);
        else if (PT_MJPEG == enType)
            sprintf(gSelectStrmName[chnIdx], "es_chn%d_ut%d.mjpg", chnIdx, pCml->ut);
        else if (PT_JPEG == enType)
            sprintf(gSelectStrmName[chnIdx], "es_chn%d_ut%d.jpg", chnIdx, pCml->ut);

        if (SampleInvalidEnType(pCml->ut, enType, pCml->rcMode))
            continue;

        if (PT_BUTT == enType) {
            SAMPLE_LOG_ERR("chn-%d: Invalid codec type!\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        s32Ret = COMMON_VENC_Start(chnIdx, enType, enRcMode, pCml);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_Start failed.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        SampleSendFrameInit(chnIdx, enType, &gstFrmParam[chnIdx], pCml);
        s32Ret = SAMPLE_VENC_StartSendFrame(&gstFrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: SAMPLE_VENC_StartSendFrame err.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        COMMON_VENC_AdjustLoopExit(&gVencCaseLoopExit, chnIdx);
        sleep(1);
    }


    SampleEpollGetStreamInit(&gstStrmParam[0], pCml);


    s32Ret = SAMPLE_VENC_EpollStartGetStream(&gstStrmParam[0]);
    if (AX_SUCCESS != s32Ret) {
        s32Ret = -1;
        goto FREE;
    }


    while ((!gLoopExit) && (gVencCaseLoopExit != pCml->vencLoopExit)) {
        sleep(2);
    }
FREE:

    for (AX_S32 chnIdx = 0; chnIdx < chnNum; chnIdx++) {
        SAMPLE_VENC_StopSendFrame(&gstFrmParam[chnIdx]);
        COMMON_VENC_Stop(chnIdx);
    }

    for (AX_S32 chnIdx = 0; chnIdx < chnNum; chnIdx++) {
        SAMPLE_VENC_EpollStopGetStream(&gstStrmParam[chnIdx]);
    }

    pCml->vencLoopExit = 0;

    return s32Ret;
}


static AX_VOID *SAMPLE_VENC_EpollGetStreamProc(AX_VOID *arg)
{
    AX_S32 s32Ret = -1;
    AX_VENC_STREAM_T stStream;

    AX_S32 maxFd = 0;
    AX_S32 VencFd[AX_MAX_VENC_CHN_NUM];
    AX_U64 totalGetStream = 0;
    SAMPLE_VENC_GETSTREAM_PARA_T *pstArg = (SAMPLE_VENC_GETSTREAM_PARA_T *)arg;
    SAMPLE_VENC_CMD_PARA_T *pCml = (SAMPLE_VENC_CMD_PARA_T *)pstArg->ptrPrivate;
    int chnNum = pstArg->chnNum;
    memset(&stStream, 0, sizeof(stStream));
    int epoll_fd = epoll_create(10);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        assert(0);
    }
    struct epoll_event event[10];
    for (AX_S32 i = 0; i < chnNum; i++) {
        VencFd[i] = AX_VENC_GetFd(i);
        if (VencFd[i] <= 0) {
            SAMPLE_LOG_ERR("VencFd[%d]=%d is invalid.\n", i, VencFd[i]);
            goto EXIT;
        }
        if (maxFd < VencFd[i])
            maxFd = VencFd[i];
        event[i].events = EPOLLIN; // 监听读事件
        event[i].data.fd = VencFd[i];

        // 将套接字添加到epoll实例中
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, VencFd[i], &event[i]) == -1) {
            perror("epoll_ctl");
            close(epoll_fd);
            return 0;
        }

    }

    // 准备要监听的事件
    while (pstArg->bGetStrmStart) {
        struct epoll_event events[10];
        int num_events = epoll_wait(epoll_fd, events, 10, pstArg->syncType);
        if (num_events < 0) {
            perror("epoll_wait");
            return 0;
        }

        for (int idx = 0; idx < chnNum; idx++) {
            if(num_events > 0) {
                for (int i = 0; i < num_events; i++) {
                    int fd = events[i].data.fd;
                    if (fd == VencFd[idx]) {
                        // 处理VencFd[idx]的读事件
                        s32Ret = AX_VENC_GetStream(idx, &stStream, 0);
                        if (AX_SUCCESS == s32Ret) {
                            if (NULL == gStrmFile[idx])
                                gStrmFile[idx] = fopen(gSelectStrmName[idx], "wb");

                            SAMPLE_VENC_FWRITE(stStream.stPack.pu8Addr, 1, stStream.stPack.u32Len, gStrmFile[idx],
                            pstArg->bSaveStrm);
                            fflush(gStrmFile[idx]);

                            totalGetStream++;

                            SAMPLE_LOG_INFO("chn-%d: get stream success, addr=%p, len=%u, codeType=%d, seqNum=%llu.\n", idx,
                            stStream.stPack.pu8Addr, stStream.stPack.u32Len, stStream.stPack.enCodingType,
                            stStream.stPack.u64SeqNum);

                            s32Ret = AX_VENC_ReleaseStream(idx, &stStream);
                            if (AX_SUCCESS != s32Ret) {
                                SAMPLE_LOG("chn-%d: AX_VENC_ReleaseStream failed!\n", idx);
                                goto EXIT;
                            }
                        } else {
                            SAMPLE_LOG("chn-%d: get stream failed, ret=0x%x\n", idx, s32Ret);
                        }
                    }
                }
            }
        }
    }

EXIT:

    for (AX_S32 i = 0; i < pCml->chnNum; i++) {
        if (gStrmFile[i] != NULL) {
            fclose(gStrmFile[i]);
            gStrmFile[i] = NULL;
        }
    }

    return (void *)(intptr_t)s32Ret;
}

static AX_S32 SAMPLE_VENC_EpollStartGetStream(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg)
{
    AX_S32 s32Ret = 0;

    s32Ret = pthread_create(&pstArg->getStrmPid, 0, SAMPLE_VENC_EpollGetStreamProc, (AX_VOID *)pstArg);
    if (s32Ret) {
        SAMPLE_LOG_ERR("Select: pthread create err, ret=%d!\n", s32Ret);
        return s32Ret;
    }

    return s32Ret;
}

static AX_S32 SAMPLE_VENC_EpollStopGetStream(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg)
{

    if (pstArg->bGetStrmStart) {
        pstArg->bGetStrmStart = AX_FALSE;
        pthread_join(pstArg->getStrmPid, 0);
    }

    return AX_SUCCESS;
}

static AX_VOID SampleEpollGetStreamInit(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg, SAMPLE_VENC_CMD_PARA_T *pCml)
{
    pstArg->bGetStrmStart = AX_TRUE;
    /* 100ms */
    pstArg->syncType = pCml->syncGet;
    pstArg->testId = pCml->ut;
    pstArg->gopMode = pCml->gopMode;
    pstArg->temporalID = pCml->temporalID;
    pstArg->bGetStrmBufInfo = pCml->bGetStrmBufInfo;
    pstArg->bQueryStatus = pCml->bQueryStatus;
    pstArg->bSaveStrm = pCml->bSaveStrm;
    pstArg->chnNum = pCml->chnNum;
    pstArg->grpId = pCml->grpId;
    pstArg->startChn = 0;
    pstArg->ptrPrivate = (AX_VOID *)pCml;
}