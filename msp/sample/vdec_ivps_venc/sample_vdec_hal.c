/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/prctl.h>

//#include "openssl/md5.h"
#include "ax_vdec_api.h"
#include "ax_base_type.h"
#include "ax_sys_api.h"
#include "ax_buffer_tool.h"
#include "sample_vdec_hal.h"

#include "common_vdec_api.h"

extern AX_S32 gLoopDecodeNumber;
extern AX_S32 gLoopExit;
extern AX_S32 gWriteFrames;
AX_S32 gVdecFrmExit;

AX_POOL GrpPoolId[AX_VDEC_MAX_GRP_NUM];
static SAMPLE_VDEC_CONTEXT_T stVdecCtx;


AX_S32 FramePoolInit(AX_VDEC_GRP VdGrp, AX_U32 FrameSize, AX_POOL *PoolId, AX_U32 u32FrameBufCnt)
{
    AX_S32 s32Ret = AX_SUCCESS;
    /* vdec use pool to alloc output buffer */
    AX_POOL_CONFIG_T stPoolConfig = {0};
    AX_POOL s32PoolId;

    memset(&stPoolConfig, 0, sizeof(AX_POOL_CONFIG_T));
    stPoolConfig.MetaSize = 512;
    stPoolConfig.BlkCnt = u32FrameBufCnt;
    stPoolConfig.BlkSize = FrameSize;
    stPoolConfig.CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    memset(stPoolConfig.PartitionName, 0, sizeof(stPoolConfig.PartitionName));
    strcpy((AX_CHAR *)stPoolConfig.PartitionName, "anonymous");

    s32PoolId = AX_POOL_CreatePool(&stPoolConfig);
    if (AX_INVALID_POOLID == s32PoolId) {
        SAMPLE_CRIT_LOG("Create pool err.\n");
        return AX_ERR_VDEC_NULL_PTR;
    }

    *PoolId = s32PoolId;

    s32Ret = AX_VDEC_AttachPool(VdGrp, s32PoolId);
    if (s32Ret != AX_SUCCESS) {
        AX_POOL_DestroyPool(s32PoolId);
        SAMPLE_CRIT_LOG("Attach pool err. 0x%x\n", s32Ret);
    }

    SAMPLE_LOG_TMP("FramePoolInit successfully s32PoolId %d cnt %#x size %d\n", s32PoolId, u32FrameBufCnt, FrameSize);

    return s32Ret;
}

static AX_S32 __VdecInitUsrPicArgs(SAMPLE_VDEC_FUNC_ARGS_T *pstFuncArgs, SAMPLE_VDEC_USERPIC_T *pstVdecUserPic)
{
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_USRPIC_ARGS_T *pstUsrPicArgs = NULL;
    AX_VDEC_GRP VdGrp = 0;
    AX_S32 s32Ret = AX_SUCCESS;

    if (pstFuncArgs == NULL) {
        s32Ret = -1;
        SAMPLE_CRIT_LOG("pstFuncArgs == NULL\n");
        goto ERR_RET;
    }

    VdGrp = pstFuncArgs->VdecGrp;
    if (pstVdecUserPic == NULL) {
        s32Ret = -1;
        SAMPLE_CRIT_LOG("pstVdecUserPic == NULL\n");
        goto ERR_RET;
    }

    pstCmd = pstFuncArgs->pstCmd;
    if (NULL == pstCmd) {
        s32Ret = -1;
        SAMPLE_CRIT_LOG("VdGrp=%d, pstCmd == NULL\n", VdGrp);
         goto ERR_RET;
    }

    pstUsrPicArgs = &pstFuncArgs->tUsrPicArgs;
    pstUsrPicArgs->VdGrp = VdGrp;
    pstVdecUserPic->recvStmAfUsrPic = pstCmd->recvStmAfUsrPic;
    pstUsrPicArgs->bUsrInstant = pstCmd->bUsrInstant;
    pstUsrPicArgs->enDecType = pstCmd->enDecType;
    pstUsrPicArgs->pstVdecUserPic = pstVdecUserPic;
    pstUsrPicArgs->tPicParam.u32PicWidth = pstCmd->u32PicWidth;
    pstUsrPicArgs->tPicParam.u32PicHeight = pstCmd->u32PicHeight;
    pstUsrPicArgs->tPicParam.enImgFormat = pstCmd->enImgFormat;
    pstUsrPicArgs->tPicParam.pUsrPicFilePath = pstCmd->pUsrPicFilePath;
    pstUsrPicArgs->tPicParam.bUserPicEnable = pstCmd->bUserPicEnable;

    SAMPLE_LOG("VdGrp=%d, --- %d %d %d %d %d %d %s\n", VdGrp, pstCmd->bUsrInstant,
                pstCmd->enDecType, pstCmd->u32PicWidth,
                pstCmd->u32PicHeight, pstCmd->enImgFormat,
                pstCmd->bUserPicEnable, pstCmd->pUsrPicFilePath);
ERR_RET:
    return s32Ret;
}

static AX_VOID __VdecSendEndOfStream(AX_VDEC_GRP VdGrp)
{
    AX_S32 sRet = 0;
    AX_VDEC_STREAM_T tStrInfo = {0};
    tStrInfo.bEndOfStream = AX_TRUE;
    sRet = AX_VDEC_SendStream(VdGrp, &tStrInfo, -1);
    if (sRet != AX_SUCCESS) {
        if (sRet != AX_ERR_VDEC_NOT_PERM && sRet != AX_ERR_VDEC_UNEXIST) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x %s\n",
                            VdGrp, sRet, SampleVdecRetStr(sRet));
            goto ERR_RET;
        }
    }

ERR_RET:
    return;
}

void *VdecFrameFunc(void *arg)
{
    if (arg == NULL) {
        SAMPLE_CRIT_LOG("arg == NULL\n");
        return NULL;
    }

    SAMPLE_VDEC_FUNC_ARGS_T *pstFunPara = (SAMPLE_VDEC_FUNC_ARGS_T *)arg;
    AX_S32 sRet = 0;
    AX_S32 s32Ret = 0;
    AX_VDEC_GRP_ATTR_T tVdecAttr = {0};
    AX_VDEC_STREAM_T tStrInfo = {0};
    AX_U32 FrameSize = 0;
    AX_POOL PoolId;
    AX_U32 id = 0;
    SAMPLE_STREAM_BUF_T tStreamBuf = {0};
    SAMPLE_STREAM_BUF_T *pstStreamBuf = &tStreamBuf;
    AX_VDEC_GRP VdGrp = pstFunPara->VdecGrp;
    AX_PAYLOAD_TYPE_E enDecType = PT_H264;
    AX_CHAR *sFile = pstFunPara->sFile;
    AX_U8 *pstStreamMem = NULL;
    size_t sReadLen = 0;
    AX_S32 sLoopDecNum = 0;
#ifdef AX_VDEC_FFMPEG_ENABLE
    SAMPLE_FFMPEG_T stFfmpeg;
    SAMPLE_FFMPEG_T *pstFfmpeg = &stFfmpeg;
#endif
    SAMPLE_BITSTREAM_INFO_T stBitStreamInfo;
    SAMPLE_BITSTREAM_INFO_T *pstBitStreamInfo = &stBitStreamInfo;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = pstFunPara->pstCmd;
    SAMPLE_VDEC_USERPIC_T stVdecUserPic;
    AX_U32 uSendPicNum = 0;
    AX_BOOL bUsrPicEnable = AX_FALSE;
    AX_BOOL bContSendStm = AX_TRUE;
    off_t inputFileSize = 0;
    size_t read_size = 0;
    FILE *fInput = NULL;
    AX_U32 u32FrameStride = 0;
    AX_U32 uWidth = 0;
    AX_BOOL pollingEna = AX_FALSE;
    AX_BOOL bPoolingLock = AX_FALSE;
    AX_U32 uBufSize = 0;
    AX_BOOL bPerfTest = AX_FALSE;
    SAMPLE_VDEC_POLLING_ARGS_T *pstPollingArgs = NULL;
    AX_U32 u32FrameBufCnt = 0;
    AX_U64 u64FrameCnt = 0;

    SAMPLE_VDEC_CONTEXT_T *pstCtx = &stVdecCtx;

    SAMPLE_LOG_TMP("VDEC Creat Grp %d enDecType %d\n", VdGrp, enDecType);

    AX_CHAR cPthreadName[16];
    snprintf(cPthreadName, 16, "SampleVdec%d", VdGrp);
    prctl(PR_SET_NAME, cPthreadName);

    if (pstCmd == NULL) {
        SAMPLE_CRIT_LOG("pstCmd == NULL\n");
        return NULL;;
    }

    if (sFile == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, Please input pInputFilePath\n", VdGrp);
        return NULL;
    }

    pollingEna = pstCmd->pollingEna;
    pstPollingArgs = pstFunPara->pstPollingArgs;

    memset(&stVdecUserPic, 0x0, sizeof(SAMPLE_VDEC_USERPIC_T));
    memset(pstCtx, 0x0, sizeof(SAMPLE_VDEC_CONTEXT_T));

    sLoopDecNum = pstCmd->sLoopDecNum;
    /*GROUP VDEC ATTR*/
    tVdecAttr.enCodecType = pstCmd->enDecType;
    tVdecAttr.enInputMode = pstCmd->enInputMode;
    tVdecAttr.enLinkMode = AX_LINK_MODE;
    tVdecAttr.enOutOrder = AX_VDEC_OUTPUT_ORDER_DISP;
    tVdecAttr.u32PicWidth = pstCmd->u32PicWidth; /* pic width */
    tVdecAttr.u32PicHeight = pstCmd->u32PicHeight; /* pic height */
    tVdecAttr.u32FrameHeight = pstCmd->u32FrameHeight;  /*Max pic height*/
    tVdecAttr.u32StreamBufSize = 4*1024*1024;
    tVdecAttr.enVdecVbSource = pstCmd->enFrameBufSrc;
    tVdecAttr.u32FrameBufCnt = pstCmd->u32FrameBufCnt;

    enDecType = pstCmd->enDecType;

    fInput = fopen(sFile, "rb");
    if (fInput == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, Unable to open input file:%s\n", VdGrp, sFile);
        return NULL;
    }

    sRet = fseek(fInput, 0L, SEEK_END);
    if (sRet) {
        SAMPLE_CRIT_LOG("VdGrp=%d, fseek FAILED! ret:%d\n", VdGrp, sRet);
        goto ERR_RET_FCLOSE;
    }

    inputFileSize = ftello(fInput);
    rewind(fInput);
    if (inputFileSize == -1) {
        SAMPLE_LOG_TMP("note:---------------file size err!!!!!!--------------\n");
    }

    tStreamBuf.uBufSize = STREAM_BUFFER_MAX_SIZE_HIGH_RES / 2;
    if (pstCmd->highRes) {
        tStreamBuf.uBufSize = STREAM_BUFFER_MAX_SIZE_HIGH_RES;
    }
    else {
        if (pstCmd->enDecType == PT_JPEG) {
            uBufSize = inputFileSize > STREAM_BUFFER_MIN_SIZE ? inputFileSize : STREAM_BUFFER_MIN_SIZE;
            tStreamBuf.uBufSize = uBufSize > STREAM_BUFFER_MAX_SIZE ? STREAM_BUFFER_MAX_SIZE : uBufSize;
        } else {
            tStreamBuf.uBufSize = inputFileSize > STREAM_BUFFER_MAX_SIZE ? STREAM_BUFFER_MAX_SIZE : inputFileSize;
        }
    }

    s32Ret = AX_SYS_MemAlloc(&tStreamBuf.tBufAddr.u64PhyAddr, (AX_VOID **)&tStreamBuf.tBufAddr.pVirAddr,
                             tStreamBuf.uBufSize, 0x100, (AX_S8 *)"VdecInputStream");
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemAlloc FAILED! uBufSize:0x%x ret:0x%x\n",
                         VdGrp, tStreamBuf.uBufSize, s32Ret);
        goto ERR_RET_FCLOSE;
    } else {
        if ((tStreamBuf.tBufAddr.pVirAddr == NULL) || (tStreamBuf.tBufAddr.u64PhyAddr == 0)) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemAlloc FAILED! uBufSize:%d",
                            VdGrp, tStreamBuf.uBufSize);
            goto ERR_RET_FCLOSE;
        }
    }

    SAMPLE_LOG_TMP("grp %d str buf size %#x\n", VdGrp, tStreamBuf.uBufSize);

    pstStreamMem = (AX_U8 *)tStreamBuf.tBufAddr.pVirAddr;
    if (enDecType == PT_H264) {
        SAMPLE_H264_SPS_DATA_T sps_data;
        AX_U32 parse_len = inputFileSize >= SEEK_NALU_MAX_LEN ? SEEK_NALU_MAX_LEN : inputFileSize;
        memset(&sps_data, 0, sizeof(SAMPLE_H264_SPS_DATA_T));

        read_size = fread(pstStreamMem, sizeof(AX_U8), (size_t)parse_len, fInput);
        if (read_size != parse_len) {
            SAMPLE_CRIT_LOG("fread FAILED! read_size:0x%x != parse_len:0x%x\n",
                            (AX_U32)read_size, parse_len);
            goto ERR_RET_FREE;
        }
        rewind(fInput);

        sRet = h264_parse_sps(pstStreamMem, parse_len, &sps_data);
        SAMPLE_LOG_TMP("h264_parse_sps sRet:0x%x sps_data.height:%d, sps_data.width:%d parse_len:%d",
                   sRet, sps_data.height, sps_data.width, parse_len);
    }

    uWidth = pstCmd->u32PicWidth;
    u32FrameStride = AX_COMM_ALIGN(uWidth, AX_VDEC_WIDTH_ALIGN);

    /*GROUP CREATE FOR 16 PATH*/
    s32Ret = AX_VDEC_CreateGrp(VdGrp, &tVdecAttr);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_CreateGrp failed! 0x%x %s\n", s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_FREE;
    }

    pstCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_CREATED;

    if (pstCmd->enFrameBufSrc == AX_POOL_SOURCE_USER) {
        FrameSize = AX_VDEC_GetPicBufferSize(u32FrameStride, pstCmd->u32PicHeight, pstCmd->enDecType);
        u32FrameBufCnt = pstCmd->u32FrameBufCnt;
        SAMPLE_LOG("Get pool mem size is %d, u32FrameBufCnt:%d.\n", FrameSize, u32FrameBufCnt);
        sRet = FramePoolInit(VdGrp, FrameSize, &PoolId, u32FrameBufCnt);
        if (sRet != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("FramePoolInit failed! Error:%x\n", sRet);
            goto ERR_RET_DESTROY_GRP;
        }

        GrpPoolId[VdGrp] = PoolId;
    }

    sRet = __VdecInitUsrPicArgs(pstFunPara, &stVdecUserPic);
    if (sRet != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, __VdecInitUsrPicArgs failed. ret:0x%x %s\n",
                         VdGrp, sRet, SampleVdecRetStr(sRet));
        goto ERR_RET_DESTROY_POOL;
    }

    sRet = __VdecUsrPicCreat(&pstFunPara->tUsrPicArgs, &stVdecUserPic);
    if (sRet != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, __VdecUsrPicCreat failed. ret:0x%x %s\n",
                         VdGrp, sRet, SampleVdecRetStr(sRet));
        goto ERR_RET_DESTROY_POOL;
    }

    AX_VDEC_GRP_PARAM_T stGrpParam;
    s32Ret = AX_VDEC_GetGrpParam(VdGrp, &stGrpParam);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_GetGrpParam failed! 0x%x %s\n", s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_DESTROY_USER_PIC;
    }

    stGrpParam.enVdecMode = pstCmd->enVideoMode;
    s32Ret = AX_VDEC_SetGrpParam(VdGrp, &stGrpParam);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_SetGrpParam failed! 0x%x %s\n", s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_DESTROY_USER_PIC;
    }

    s32Ret = AX_VDEC_SetDisplayMode(VdGrp, pstCmd->enDisplayMode);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_SetDisplayMode failed! ret:0x%x %s\n", s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_DESTROY_USER_PIC;
    }

    AX_VDEC_RECV_PIC_PARAM_T tRecvParam = {0};
    s32Ret = AX_VDEC_StartRecvStream(VdGrp, &tRecvParam);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_StartRecvStream failed! ret:0x%x %s\n", s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_DESTROY_USER_PIC;
    } else {
        pstCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_START_RECV;
    }

    while (1) {
        tStreamBuf.pBufBeforeFill = tStreamBuf.tBufAddr.pVirAddr;
        tStreamBuf.pBufAfterFill = tStreamBuf.tBufAddr.pVirAddr;
        tStreamBuf.bRingbuf = AX_FALSE;
        pstStreamMem = (AX_U8 *)tStreamBuf.tBufAddr.pVirAddr;

        pstBitStreamInfo->VdGrp = VdGrp;
        pstBitStreamInfo->stBsInfo.fInput = fInput;
        pstBitStreamInfo->stBsInfo.curPos = 0;
        pstBitStreamInfo->stBsInfo.sFileSize = inputFileSize;
        pstBitStreamInfo->stBsInfo.enDecType = enDecType;
#ifdef AX_VDEC_FFMPEG_ENABLE
        if ((enDecType == PT_H264) || (enDecType == PT_H265)) {
            if (pstCmd->bFfmpegEnable) {
                s32Ret = SampleVdecFfmpegInit(pstFfmpeg, sFile, pstBitStreamInfo);
                if (s32Ret != AX_SUCCESS) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegInit FAILED! ret:0x%x\n",
                                    VdGrp, s32Ret);
                    goto ERR_RET_STOP_RECV;
                }
                SAMPLE_LOG_TMP("grp %d ffmpeg init %s size %lld\n", VdGrp, sFile, (AX_U64)inputFileSize);
            } else {
                fseek(pstBitStreamInfo->stBsInfo.fInput, 0, SEEK_SET);
            }
        } else {
            fseek(pstBitStreamInfo->stBsInfo.fInput, 0, SEEK_SET);
        }
#else
        fseek(pstBitStreamInfo->stBsInfo.fInput, 0, SEEK_SET);
#endif
        SAMPLE_LOG_TMP("grp %d start read file %s size %lld\n", VdGrp, sFile, (AX_U64)inputFileSize);

        do {
            if ((enDecType == PT_H264) || (enDecType == PT_H265)) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                if (pstCmd->bFfmpegEnable) {
                    s32Ret = SampleVdecFfmpegExtractOnePic(pstFfmpeg, pstBitStreamInfo, pstStreamBuf, &sReadLen);
                    if (s32Ret) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegExtractOnePic FAILED! ret:0x%x\n", VdGrp, s32Ret);
                        goto ERR_RET_STOP_RECV;
                    }
                } else {
                    s32Ret = StreamFileParserReadFrame(&pstBitStreamInfo->stBsInfo, pstStreamBuf, &sReadLen);
                    if (s32Ret) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameJpeg FAILED! ret:0x%x\n", VdGrp, sRet);
                        goto ERR_RET_STOP_RECV;
                    }
                }
#else
                    s32Ret = StreamFileParserReadFrame(&pstBitStreamInfo->stBsInfo, pstStreamBuf, &sReadLen);
                    if (s32Ret) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameJpeg FAILED! ret:0x%x\n", VdGrp, sRet);
                        goto ERR_RET_STOP_RECV;
                    }
#endif
            } else if (enDecType == PT_JPEG) {
                if (!(bPerfTest && uSendPicNum)) {
                    s32Ret = StreamParserReadFrameJpeg(&pstBitStreamInfo->stBsInfo, pstStreamBuf, &sReadLen);
                    if (s32Ret) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameJpeg FAILED! ret:0x%x\n", VdGrp, sRet);
                        goto ERR_RET_STOP_RECV;
                    }
                }
            }

            SAMPLE_LOG_TMP("send stream VdGrp:%d sLen: %d, id: %d\n", VdGrp, (AX_U32)sReadLen, id);
            id++;

            if (sReadLen) {
                tStrInfo.pu8Addr = pstStreamBuf->tBufAddr.pVirAddr;
                tStrInfo.u64PhyAddr = pstStreamBuf->tBufAddr.u64PhyAddr;
                tStrInfo.u32StreamPackLen = (AX_U32)sReadLen;  /*stream len*/
                tStrInfo.bEndOfFrame = AX_TRUE;
                tStrInfo.bEndOfStream = AX_FALSE;
                tStrInfo.u64PTS = 0;
            } else {
                if (sLoopDecNum == 1) {
                    tStrInfo.pu8Addr = NULL;
                    tStrInfo.u32StreamPackLen = 0x0;  /*stream len*/
                    tStrInfo.bEndOfFrame = AX_TRUE;
                    tStrInfo.bEndOfStream = AX_TRUE;
                }
            }

            if (pollingEna && pstPollingArgs->pollingStat != SAMPLE_VDEC_POLLING_STATUS_EXIT) {
                SAMPLE_VDEC_MUTEXT_LOCK(&pstPollingArgs->pollingMutex[VdGrp]);
                bPoolingLock = AX_TRUE;
                if (pstPollingArgs->pollingStat == SAMPLE_VDEC_POLLING_STATUS_START) {
                    usleep(10 *1000);
                    SAMPLE_VDEC_MUTEXT_UNLOCK(&pstPollingArgs->pollingMutex[VdGrp]);
                    bPoolingLock = AX_FALSE;
                    continue;
                } else if(pstPollingArgs->pollingStat == SAMPLE_VDEC_POLLING_STATUS_END) {
                    if (pstPollingArgs->reSendStream[VdGrp]) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                        if ((pstCmd->bFfmpegEnable) && ((enDecType == PT_H264) || (enDecType == PT_H265))) {
                            s32Ret = SampleVdecFfmpegDeinit(pstFfmpeg, VdGrp);
                            if (s32Ret != AX_SUCCESS) {
                                SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegDeinit FAILED! ret:0x%x\n",
                                                VdGrp, s32Ret);
                                goto ERR_RET_STOP_RECV;
                            }
                            pstBitStreamInfo->VdGrp = VdGrp;
                            s32Ret = SampleVdecFfmpegInit(pstFfmpeg, sFile, pstBitStreamInfo);
                            if (s32Ret != AX_SUCCESS) {
                                SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegInit FAILED! ret:0x%x\n",
                                                VdGrp, s32Ret);
                                goto ERR_RET_STOP_RECV;
                            }
                        } else {
                            pstBitStreamInfo->VdGrp = VdGrp;
                            fseek(pstBitStreamInfo->stBsInfo.fInput, 0, SEEK_SET);
                            pstBitStreamInfo->stBsInfo.curPos = 0;
                        }
#else
                        pstBitStreamInfo->VdGrp = VdGrp;
                        fseek(pstBitStreamInfo->stBsInfo.fInput, 0, SEEK_SET);
                        pstBitStreamInfo->stBsInfo.curPos = 0;
#endif
                        pstPollingArgs->reSendStream[VdGrp] = AX_FALSE;
                        SAMPLE_VDEC_MUTEXT_UNLOCK(&pstPollingArgs->pollingMutex[VdGrp]);
                        bPoolingLock = AX_FALSE;
                        continue;
                   }
                }
            }

            u64FrameCnt++;
            if (pstCmd->bSkipFrms && (u64FrameCnt & 1))
                tStrInfo.u64PTS = -1; /* dec not out put */
            else if (pstCmd->u32StreamFps)
                tStrInfo.u64PTS = u64FrameCnt * 1000000 / pstCmd->u32StreamFps;
            else
                tStrInfo.u64PTS = u64FrameCnt;

            s32Ret = AX_VDEC_SendStream(VdGrp, &tStrInfo, -1);
            if (s32Ret != AX_SUCCESS) {
                if ((s32Ret == AX_ERR_VDEC_BUF_FULL)
                        || (s32Ret == AX_ERR_VDEC_QUEUE_FULL)
                        || (s32Ret == AX_ERR_VDEC_NOT_PERM)
                        || (s32Ret == AX_ERR_VDEC_UNEXIST)) {
                    SAMPLE_WARN_LOG("VdGrp=%d, AX_VDEC_SendStream ret:0x%x %s\n",
                                    VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
                }
                else {
                    SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x %s\n",
                                    VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
                }
            }

            usleep(33 *1000);
            uSendPicNum ++;

            if (VdGrp == pstCmd->uStartGrpId) {
                printf("%-8d", uSendPicNum);
                if ((uSendPicNum % 16) == 0) {
                    printf("\n");
                }
                fflush(stdout);
            }

            if (uSendPicNum == pstCmd->usrPicIdx) {
                sRet = VdecUserPicEnable(VdGrp, pstFunPara->tUsrPicArgs.pstVdecUserPic, &bContSendStm, pstCtx);
                if (sRet != AX_SUCCESS) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, VdecUserPicEnable FAILED! ret:0x%x %s",
                                        VdGrp, sRet, SampleVdecRetStr(sRet));
                    goto ERR_RET_STOP_RECV;
                }

                if (!bContSendStm) {
                    bUsrPicEnable = AX_TRUE;
                    sReadLen = 0;
                    if(bPoolingLock == AX_TRUE) {
                        SAMPLE_VDEC_MUTEXT_UNLOCK(&pstPollingArgs->pollingMutex[VdGrp]);
                        bPoolingLock = AX_FALSE;
                    }

                    break;
                }
            }

            /*add CTRL+C*/
            if (gLoopExit) {
                __VdecSendEndOfStream(VdGrp);
                break;
            }

            if(bPoolingLock == AX_TRUE) {
                SAMPLE_VDEC_MUTEXT_UNLOCK(&pstPollingArgs->pollingMutex[VdGrp]);
                bPoolingLock = AX_FALSE;
            }
        } while (sReadLen);

#ifdef AX_VDEC_FFMPEG_ENABLE
        if ((enDecType == PT_H264) || (enDecType == PT_H265)) {
            s32Ret = SampleVdecFfmpegDeinit(pstFfmpeg, VdGrp);
            if (s32Ret != AX_SUCCESS) {
                SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegDeinit FAILED! ret:0x%x\n",
                                VdGrp, s32Ret);
                goto ERR_RET_DESTROY_USER_PIC;
            }
        } else {
            pstBitStreamInfo->VdGrp = VdGrp;
            fseek(pstBitStreamInfo->stBsInfo.fInput, 0, SEEK_SET);
            pstBitStreamInfo->stBsInfo.curPos = 0;
        }
#else
        pstBitStreamInfo->VdGrp = VdGrp;
        fseek(pstBitStreamInfo->stBsInfo.fInput, 0, SEEK_SET);
        pstBitStreamInfo->stBsInfo.curPos = 0;
#endif
        if (bUsrPicEnable) {
            while (!gLoopExit) {
                sleep(1);
            }
            break;
        } else {
            if (gLoopExit)
                break;
        }

        if (sLoopDecNum == 1) {
            break;
        } else if (sLoopDecNum > 1) {
            sLoopDecNum--;
        }
    }

    if (pstStreamMem) {
        if (tStreamBuf.tBufAddr.u64PhyAddr != 0) {
            sRet = AX_SYS_MemFree(tStreamBuf.tBufAddr.u64PhyAddr, tStreamBuf.tBufAddr.pVirAddr);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemFree FAILED! ret:0x%x", VdGrp, sRet);
            }
        }

        memset(&tStreamBuf, 0, sizeof(tStreamBuf));
        pstStreamMem = NULL;
    }

    VdecUserPicDestroy(VdGrp, pstFunPara->tUsrPicArgs.pstVdecUserPic);

    SAMPLE_LOG_TMP("VDEC Grp %d END!\n", VdGrp);
    return (void *)AX_SUCCESS;

ERR_RET_STOP_RECV:
    s32Ret = AX_VDEC_StopRecvStream(VdGrp);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_StopRecvStream failed! ret:0x%x %s\n", s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_DESTROY_USER_PIC;
    } else {
        pstCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_STOP_RECV;
    }
ERR_RET_DESTROY_USER_PIC:
    VdecUserPicDestroy(VdGrp, pstFunPara->tUsrPicArgs.pstVdecUserPic);
ERR_RET_DESTROY_POOL:
    if (pstCmd->enFrameBufSrc == AX_POOL_SOURCE_USER) {
        AX_VDEC_DetachPool(VdGrp);

        AX_POOL_DestroyPool(PoolId);
    }
ERR_RET_DESTROY_GRP:
    while (1) {
        s32Ret = AX_VDEC_DestroyGrp(VdGrp);
        if (s32Ret == AX_ERR_VDEC_BUSY) {
            SAMPLE_WARN_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                           VdGrp, sRet, SampleVdecRetStr(sRet));
            usleep(10000);
            if (pstCmd->sWriteFrames) {
                sleep(1);
            }
            continue;
        }

        if (s32Ret != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                            VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
        }

        break;
    }

    pstCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_DESTROYED;

ERR_RET_FREE:
    if (pstStreamMem) {
        if (tStreamBuf.tBufAddr.u64PhyAddr != 0) {
            sRet = AX_SYS_MemFree(tStreamBuf.tBufAddr.u64PhyAddr, tStreamBuf.tBufAddr.pVirAddr);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemFree FAILED! ret:0x%x", VdGrp, sRet);
            }
        }

        memset(&tStreamBuf, 0, sizeof(tStreamBuf));
        pstStreamMem = NULL;
    }

ERR_RET_FCLOSE:
    if (fInput) {
        fclose(fInput);
        fInput = NULL;
    }

ERR_RET:
    if(bPoolingLock == AX_TRUE)
        SAMPLE_VDEC_MUTEXT_UNLOCK(&pstPollingArgs->pollingMutex[VdGrp]);

    return NULL;
}

static AX_S32 __VdecRecvFrame(AX_VDEC_GRP VdGrp, SAMPLE_VDEC_CMD_PARAM_T *pstCmd)
{
    AX_S32 ret;
    AX_S32 sRet = AX_SUCCESS;
    AX_VIDEO_FRAME_INFO_T stFrameInfo[SAMPLE_VDEC_FRAME_CNT];
    AX_VIDEO_FRAME_INFO_T *pstFrameInfo;
    AX_S32 sMilliSec = -1;
    int ii = 0;

    if (pstCmd == NULL) {
        SAMPLE_LOG("VdGrp=%d, pstCmd == NULL", VdGrp);
        return -1;
    }

    sMilliSec = pstCmd->sMilliSec;

    // sleep(10000); // just for test

    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];

        memset(pstFrameInfo, 0, sizeof(AX_VIDEO_FRAME_INFO_T));
        SAMPLE_LOG_N("VdGrp=%d\n", VdGrp);

        ret = AX_VDEC_GetFrame(VdGrp, pstFrameInfo, sMilliSec);
        if (ret != AX_SUCCESS) {
            if (ret == AX_ERR_VDEC_QUEUE_EMPTY) {
                /* no data in unblock mode or timeout mode */
                SAMPLE_LOG("VdGrp=%d, AX_VDEC_GetChnFrame AX_ERR_VDEC_QUEUE_EMPTY\n",
                            VdGrp);
                usleep(20 * 1000);
                sRet = ret;
                goto ERR_RET;
            } else if (ret == AX_ERR_VDEC_UNEXIST) {
                SAMPLE_WARN_LOG("VdGrp=%d, AX_VDEC_GetChnFrame AX_ERR_VDEC_UNEXIST \n",
                                VdGrp);
                usleep(20 * 1000);
                sRet = ret;
                goto ERR_RET;
            } else if (ret == AX_ERR_VDEC_FLOW_END) {
                SAMPLE_LOG("VdGrp=%d, AX_VDEC_GetChnFrame AX_ERR_VDEC_FLOW_END\n",
                            VdGrp);
                sRet = ret;
                goto ERR_RET;
            } else if (AX_ERR_VDEC_NOT_PERM == ret) {
                SAMPLE_WARN_LOG("VdGrp=%d, AX_VDEC_GetChnFrame AX_ERR_VDEC_NOT_PERM\n",
                                VdGrp);
                sRet = ret;
                goto ERR_RET;
            }

            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_GetChnFrame FAILED! ret=0x%x %s\n",
                            VdGrp, ret, SampleVdecRetStr(ret));
            sRet = ret;
            goto ERR_RET;
        }

        SAMPLE_LOG("VdGrp=%d, before AX_VDEC_ReleaseFrame "
                    ".u32Width:%d, .bEndOfStream:%d, .u64PhyAddr[0]:0x%llx, "
                    ".u64VirAddr[0]:0x%llx, BlkId[0]:0x%x, u64PTS:%lld, .u64PrivateData:0x%llx\n",
                    VdGrp, pstFrameInfo->stVFrame.u32Width, pstFrameInfo->bEndOfStream,
                    pstFrameInfo->stVFrame.u64PhyAddr[0], pstFrameInfo->stVFrame.u64VirAddr[0],
                    pstFrameInfo->stVFrame.u32BlkId[0], pstFrameInfo->stVFrame.u64PTS,
                    pstFrameInfo->stVFrame.u64PrivateData);
    }

    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];
        if (pstFrameInfo->bEndOfStream == AX_FALSE) {
            if (pstFrameInfo->stVFrame.u64PhyAddr[0] == 0) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_GetChnFrame FAILED! "
                                "pstFrameInfo->stVFrame.u64PhyAddr[0] == 0\n",
                                VdGrp);
                sRet = AX_ERR_VDEC_BAD_ADDR;
                goto ERR_RET;
            }
        }
    }

#if 0
    AX_U32 uStartGrpId = 0;
    uStartGrpId = pstCmd->uStartGrpId;
    if (VdGrp == uStartGrpId) {
        if (pstFrameInfo->stVFrame.u64PhyAddr[0]) {
            printf("%-8lld", pstFrameInfo->stVFrame.u64SeqNum);
            if ((pstFrameInfo->stVFrame.u64SeqNum % 16) == 0) {
                printf("\n");
            }
            fflush(stdout);
        }
    }
#endif



    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];

        if (!pstFrameInfo->stVFrame.u64PhyAddr[0])
            continue;

        SAMPLE_LOG("VdGrp=%d, before AX_VDEC_ReleaseFrame "
                    ".u64PhyAddr[0]:0x%llx, BlkId[0]:0x%x, u64SeqNum:%lld\n",
                    VdGrp, pstFrameInfo->stVFrame.u64PhyAddr[0],
                    pstFrameInfo->stVFrame.u32BlkId[0], pstFrameInfo->stVFrame.u64SeqNum);

        ret = AX_VDEC_ReleaseFrame(VdGrp, pstFrameInfo);
        if (ret) {
            if (AX_ERR_VDEC_FLOW_END != ret) {
                if (ret == AX_ERR_VDEC_UNEXIST || ret == AX_ERR_VDEC_NOT_PERM) {
                    SAMPLE_WARN_LOG("VdGrp=%d, AX_VDEC_GetChnFrame AX_ERR_VDEC_UNEXIST \n",
                                VdGrp);
                    sRet = ret;
                    goto ERR_RET;
                }
                sRet = ret;
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_ReleaseFrame FAILED! res:0x%x %s \n"
                                "u64PhyAddr[0]:0x%llX, BlkId[0]:0x%x, BlkId[1]:0x%x\n",
                                VdGrp, ret, SampleVdecRetStr(ret), pstFrameInfo->stVFrame.u64PhyAddr[0],
                                pstFrameInfo->stVFrame.u32BlkId[0], pstFrameInfo->stVFrame.u32BlkId[1]);
                goto ERR_RET;
            }
        }

        if (pstFrameInfo->bEndOfStream == AX_TRUE) {
            SAMPLE_LOG("VdGrp=%d, bEndOfStream == AX_TRUE, ret AX_ERR_VDEC_FLOW_END", VdGrp);
            sRet = AX_ERR_VDEC_FLOW_END;
        }
    }

ERR_RET:
    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];
        SAMPLE_LOG_N("VdGrp=%d, .u64PTS:%lld, sRet0x%x %s\n",
                    VdGrp, pstFrameInfo->stVFrame.u64PTS, sRet, SampleVdecRetStr(sRet));
    }

    return sRet;
}

void *_VdecRecvThread(void *arg)
{
    AX_S32 sRet = 0;
    AX_S32 ret = 0;
    SAMPLE_VDEC_RECV_ARGS_T *pstRecvArgs = (SAMPLE_VDEC_RECV_ARGS_T *)arg;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_POLLING_ARGS_T *pstPollingArgs = NULL;
    AX_VDEC_GRP_SET_INFO_T stGrpSet;
    AX_VDEC_GRP_SET_INFO_T *pstGrpSet = &stGrpSet;
    int gi;
    AX_VDEC_GRP VdGrp = 0;
    int flow_end_total_cnt = 0;
    AX_U32 uGrpCount = 0;
    AX_U32 uLinkGrpCount = 0;
    AX_BOOL bRecvFlowEnd[AX_VDEC_MAX_GRP_NUM] = {0};
    AX_U32 uStartGrpId;
    AX_U64 u64SelectFrameCnt = 0;

    if (arg == NULL) {
        SAMPLE_CRIT_LOG("arg == NULL");
        return NULL;
    }

    AX_CHAR cPthreadName[16];
    snprintf(cPthreadName, 16, "SampleVdecRecv");
    prctl(PR_SET_NAME, cPthreadName);

    pstCmd = pstRecvArgs->pstCmd;
    pstPollingArgs = pstRecvArgs->pstPollingArgs;
    if (pstCmd == NULL) {
        SAMPLE_CRIT_LOG("pstCmd == NULL");
        return NULL;
    }

    if (pstCmd->pollingEna && NULL == pstPollingArgs) {
        SAMPLE_CRIT_LOG("pstPollingArgs == NULL");
        return NULL;
    }

    uLinkGrpCount = 1;
    if (pstCmd->uGrpCount <= uLinkGrpCount) {
        return NULL;
    } else {
        uGrpCount = pstCmd->uGrpCount - uLinkGrpCount;
    }

    uStartGrpId = pstCmd->uStartGrpId;
    SAMPLE_LOG_TMP("uGrpCount:%d Enter while(1) SelectGrp \n", uGrpCount);

    while (1) {
        if (gLoopExit && (flow_end_total_cnt == uGrpCount)) {
            SAMPLE_LOG("gLoopExit:%d, so break\n", gLoopExit);
            break;
        }

        if (flow_end_total_cnt == uGrpCount) {
            flow_end_total_cnt = 0;
            memset(bRecvFlowEnd, 0x0, AX_VDEC_MAX_GRP_NUM * sizeof(AX_BOOL));
        }

        SAMPLE_LOG("before SelectGrp \n");

        sRet = AX_VDEC_SelectGrp(pstGrpSet, -1);
        if (sRet == AX_SUCCESS) {
            if (pstGrpSet->u32GrpCount == 0) {
                SAMPLE_ERR_LOG("AX_VDEC_SelectGrp AX_SUCCESS u32GrpCount:0");
            } else {
                SAMPLE_LOG_TMP("AX_VDEC_SelectGrp u32GrpCount:%d", pstGrpSet->u32GrpCount);
            }
        }
        else if (AX_ERR_VDEC_TIMED_OUT == sRet) {
            SAMPLE_NOTICE_LOG("AX_VDEC_SelectGrp AX_ERR_VDEC_TIMED_OUT u32GrpCount:%d",
                              pstGrpSet->u32GrpCount);

            if (pstGrpSet->u32GrpCount == 0) {
                continue;
            }
        }
        else if (AX_ERR_VDEC_NOT_INIT == sRet) {
            SAMPLE_NOTICE_LOG("AX_ERR_VDEC_NOT_INIT, Need Call AX_VDEC_Init first");
            goto ERR_RET;
        }
        else if (AX_ERR_VDEC_FLOW_END == sRet) {
            SAMPLE_NOTICE_LOG("AX_VDEC_SelectGrp AX_ERR_VDEC_FLOW_END");
            goto ERR_RET;
        }
        else {
            SAMPLE_CRIT_LOG("AX_VDEC_SelectGrp FAILED! ret:0x%x %s",
                            sRet, SampleVdecRetStr(sRet));
            goto ERR_RET;
        }

        SAMPLE_LOG("after SelectGrp, u32GrpCount:%d", pstGrpSet->u32GrpCount);
        if (pstGrpSet->u32GrpCount > 0 && pstCmd->pollingEna) {
            pstPollingArgs->pollingStart = AX_TRUE;
        }

        for (gi = 0; gi < pstGrpSet->u32GrpCount; gi++) {
            VdGrp = pstGrpSet->VdGrp[gi];
            if (VdGrp < uStartGrpId) {
                SAMPLE_CRIT_LOG("VdGrp:%d < uStartGrpId:%d", VdGrp, uStartGrpId);
                goto ERR_RET;
            } else if (VdGrp == uStartGrpId) {
                continue;
            }

            SAMPLE_LOG_N("u32GrpCount:%d, u32ChnCount:%d, VdGrp=%d, gi:%d\n",
                        pstGrpSet->u32GrpCount, pstGrpSet->stChnSet[gi].u32ChnCount,
                        VdGrp, gi);
            ret = __VdecRecvFrame(VdGrp, pstCmd);
            if (ret == AX_SUCCESS) {
                u64SelectFrameCnt++;
            } else if (ret == AX_ERR_VDEC_STRM_ERROR) {
                SAMPLE_ERR_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s\n",
                            VdGrp, ret, SampleVdecRetStr(ret));
                continue;
            } else if (ret == AX_ERR_VDEC_QUEUE_EMPTY) {
                SAMPLE_ERR_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s\n",
                                VdGrp, ret, SampleVdecRetStr(ret));
                    continue;
            } else if (ret == AX_ERR_VDEC_UNEXIST) {
                    SAMPLE_ERR_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s \n",
                                    VdGrp, ret, SampleVdecRetStr(ret));
                    continue;
            } else if (AX_ERR_VDEC_NOT_PERM == ret) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s \n",
                                    VdGrp, ret, SampleVdecRetStr(ret));
                    continue;
            } else if (ret == AX_ERR_VDEC_FLOW_END) {
                    u64SelectFrameCnt++;
                    SAMPLE_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s\n",
                                VdGrp, ret, SampleVdecRetStr(ret));
                    continue;
            } else {
                    SAMPLE_LOG_TMP("VdGrp=%d, __VdecRecvFrame FAILED! ret=0x%x %s\n",
                                    VdGrp, ret, SampleVdecRetStr(ret));
                    goto ERR_RET;
            }

            if (ret == AX_ERR_VDEC_FLOW_END) {
                SAMPLE_LOG("VdGrp=%d, gi:%d, flow_end_total_cnt:%d, ->bRecvFlowEnd[VdGrp]:%d\n",
                            VdGrp, gi, flow_end_total_cnt, bRecvFlowEnd[VdGrp]);

                if (bRecvFlowEnd[VdGrp] == AX_FALSE) {
                    flow_end_total_cnt++;
                    bRecvFlowEnd[VdGrp] = AX_TRUE;
                    SAMPLE_LOG("VdGrp=%d, gi:%d, flow_end_total_cnt:%d, ->bRecvFlowEnd[VdGrp]:%d\n",
                               VdGrp, gi, flow_end_total_cnt, bRecvFlowEnd[VdGrp]);
                }
            }
        }

        if (flow_end_total_cnt == uGrpCount) {
            SAMPLE_LOG_TMP("flow_end_total_cnt:%d flow end!\n", flow_end_total_cnt);
        }
    }

ERR_RET:
    SAMPLE_LOG_TMP(" RecvThread exit, last VdGrp=%d\n", VdGrp);
    return NULL;
}

AX_S32 VdecExitFunc(AX_VDEC_GRP VdGrp)
{
    AX_S32 s32Ret = 0;

    if (stVdecCtx.GrpStatus[VdGrp] == AX_VDEC_GRP_START_RECV) {
        s32Ret = AX_VDEC_StopRecvStream(VdGrp);
        if (s32Ret) {
            SAMPLE_CRIT_LOG("VdGrp:%d, AX_VDEC_StopRecvStream fail! Error Code:0x%X\n", VdGrp, s32Ret);
            goto ERR_RET;
        }
    }


    while (1) {
        s32Ret = AX_VDEC_DestroyGrp(VdGrp);
        if (s32Ret == AX_ERR_VDEC_BUSY) {
            SAMPLE_WARN_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                           VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
            usleep(10000);

            continue;
        }

        if (s32Ret != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                            VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
            goto ERR_RET;
        }

        break;
    }

    return AX_SUCCESS;

ERR_RET:
    return s32Ret;
}

AX_S32 VdecUserPoolExitFunc(AX_VDEC_GRP VdGrp)
{
    AX_S32 s32Ret = 0;

    s32Ret = AX_VDEC_StopRecvStream(VdGrp);
    if (s32Ret) {
        SAMPLE_CRIT_LOG("AX_VDEC_StopRecvStream fail! Error Code:0x%X\n", s32Ret);
        goto ERR_RET;
    }

    s32Ret = AX_VDEC_DetachPool(VdGrp);
    if (s32Ret) {
        SAMPLE_CRIT_LOG("AX_VDEC_DetachPool fail! Error Code:0x%X\n", s32Ret);
        goto ERR_RET;
    }

    while (1) {
        s32Ret = AX_VDEC_DestroyGrp(VdGrp);
        if (s32Ret == AX_ERR_VDEC_BUSY) {
            SAMPLE_WARN_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                           VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
            usleep(10000);

            continue;
        }

        if (s32Ret != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                            VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
            goto ERR_RET;
        }

        break;
    }

    s32Ret = AX_POOL_DestroyPool(GrpPoolId[VdGrp]);
    if (s32Ret) {
        SAMPLE_CRIT_LOG("AX_POOL_DestroyPool fail! Error Code:0x%X\n", s32Ret);
        goto ERR_RET;
    }

    return AX_SUCCESS;

ERR_RET:
    return s32Ret;
}
