/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_case.h"
#include "sample_unit_test.h"

static SAMPLE_VENC_SENDFRAME_PARA_T gstFrmParam[AX_MAX_VENC_CHN_NUM];
static SAMPLE_VENC_GETSTREAM_PARA_T gstStrmParam[AX_MAX_VENC_CHN_NUM];
static AX_S32 gCaseFail = 0;

static AX_BOOL gLoopExit = AX_FALSE;
static void SigHandler(AX_S32 signo)
{
    SAMPLE_LOG("catch signal(%d).\n", signo);
    gLoopExit = AX_TRUE;
}

static AX_VOID *SAMPLE_VENC_SendFramec_ResetChn_Proc(AX_VOID *arg)
{
    AX_BOOL bLoopEncode;
    AX_U32 encFrmNum;
    const AX_CHAR *fileInput;
    AX_S32 syncType;
    AX_IMG_FORMAT_E eFmt;
    AX_U32 width;
    AX_U32 height;
    AX_U32 strideY, strideU, strideV;
    AX_VIDEO_FRAME_INFO_T stFrame;
    SAMPLE_VENC_SENDFRAME_PARA_T *pstArg;
    AX_S32 readSize;
    AX_S32 s32Ret;
    AX_U64 totalInputFrames = 0;
    pstArg = (SAMPLE_VENC_SENDFRAME_PARA_T *)arg;

    VENC_CHN VeChn = pstArg->VeChn;
    bLoopEncode = pstArg->bLoopEncode;
    encFrmNum = pstArg->encFrmNum;
    syncType = pstArg->syncType;
    eFmt = pstArg->eFmt;
    width = pstArg->width;
    height = pstArg->height;
    strideY = pstArg->strideY;
    strideU = pstArg->strideU;
    strideV = pstArg->strideV;
    fileInput = pstArg->fileInput;
    AX_S32 frameSize = pstArg->frameSize;
    AX_S32 poolId = pstArg->poolId;
    FILE *fFileIn = NULL;
    AX_BLK blkId = AX_INVALID_BLOCKID;
    SAMPLE_VENC_CMD_PARA_T *pCml = (SAMPLE_VENC_CMD_PARA_T *)pstArg->ptrPrivate;
    AX_VENC_RECV_PIC_PARAM_T stRecvParam;

    memset(&stFrame, 0, sizeof(stFrame));

    fFileIn = fopen(fileInput, "rb");
    if (fFileIn == NULL) {
        SAMPLE_LOG_ERR("chn-%d: Open input file error!\n", VeChn);
        gCaseFail = 1;
        return NULL;
    }

    while (pstArg->bSendFrmStart) {
        /* get block from user pool */
        blkId = AX_POOL_GetBlock(poolId, frameSize, NULL);
        if (AX_INVALID_BLOCKID == blkId) {
            usleep(5000);
            continue;
        }

        stFrame.stVFrame.u32FrameSize = frameSize;
        stFrame.stVFrame.u64PhyAddr[0] = AX_POOL_Handle2PhysAddr(blkId);
        stFrame.stVFrame.u64VirAddr[0] = (AX_ULONG)AX_POOL_GetBlockVirAddr(blkId);
        stFrame.stVFrame.u32BlkId[0] = blkId;
        stFrame.stVFrame.u32BlkId[1] = 0;
        stFrame.stVFrame.u32BlkId[2] = 0;

        /* read frame data from yuv file */
        readSize = COMMON_VENC_ReadFile(fFileIn, width, strideY, height, eFmt, (void *)(AX_ULONG)stFrame.stVFrame.u64VirAddr[0]);

        if (!bLoopEncode && (readSize <= 0))
            SAMPLE_LOG_WARN("chn-%d: Warning: read frame size : %d less than %d\n", VeChn, readSize, frameSize);

        if (feof(fFileIn)) {
            if (bLoopEncode) {
                fseek(fFileIn, 0, SEEK_SET);
                COMMON_VENC_ReadFile(fFileIn, pstArg->width, pstArg->strideY, pstArg->height, eFmt,
                                     (void *)(AX_ULONG)stFrame.stVFrame.u64VirAddr[0]);
            } else {
                SAMPLE_LOG_WARN("chn-%d: End of input file!\n", VeChn);
                /* no more frames, stop encoder */
                goto EXIT;
            }
        }

        stFrame.stVFrame.u64SeqNum = totalInputFrames + 1;
        stFrame.stVFrame.enImgFormat = eFmt;
        stFrame.stVFrame.u32Width = width;
        stFrame.stVFrame.u32Height = height;
        stFrame.stVFrame.u32PicStride[0] = strideY;
        stFrame.stVFrame.u32PicStride[1] = strideU;
        stFrame.stVFrame.u32PicStride[2] = strideV;

        if ((totalInputFrames + 1) == pstArg->dynAttrIdx) {
            SAMPLE_LOG_DEBUG("chn-%d: totalInputFrames %llu dynAttrIdx %d \n", VeChn, totalInputFrames,
                             pstArg->dynAttrIdx);
            s32Ret = AX_VENC_StopRecvFrame(VeChn);
            if (AX_SUCCESS != s32Ret) {
                SAMPLE_LOG_ERR("chn-%d: stop recving frame error, ret=%x\n", VeChn, s32Ret);
                gCaseFail = 1;
                goto EXIT;
            }
            s32Ret = AX_VENC_ResetChn(VeChn);
            if (AX_SUCCESS != s32Ret) {
                SAMPLE_LOG_ERR("chn-%d: reset channel error, ret=%x\n", VeChn, s32Ret);
                gCaseFail = 1;
                goto EXIT;
            }
             stRecvParam.s32RecvPicNum = -1;
            s32Ret = AX_VENC_StartRecvFrame(VeChn, &stRecvParam);
            if (AX_SUCCESS != s32Ret) {
                SAMPLE_LOG_ERR("chn-%d: stop recving frame error, ret=%x\n", VeChn, s32Ret);
                gCaseFail = 1;
                goto EXIT;
            }
        }

        s32Ret = AX_VENC_SendFrame(VeChn, &stFrame, syncType);
        if (AX_SUCCESS != s32Ret) {

            if (AX_ERR_VENC_FLOW_END == s32Ret) {
                SAMPLE_LOG_WARN("chn-%d: AX_VENC_SendFrame AX_ERR_VENC_FLOW_END, ret=%x\n", VeChn, s32Ret);
                goto EXIT;
            }

            SAMPLE_LOG_WARN("chn-%d: AX_VENC_SendFrame failed, ret=%x\n", VeChn, s32Ret);
        }

        totalInputFrames++;

        if (totalInputFrames == encFrmNum) {
            SAMPLE_LOG("chn-%d: Want to encode %llu frames, exit!\n", VeChn, totalInputFrames);
            goto EXIT;
        }

        if (AX_INVALID_BLOCKID != blkId)
            AX_POOL_ReleaseBlock(blkId);
    }


EXIT:

    if (NULL != fFileIn) {
        fclose(fFileIn);
        fFileIn = NULL;
    }

    if (AX_INVALID_BLOCKID != blkId)
        AX_POOL_ReleaseBlock(blkId);

    SAMPLE_LOG("chn-%d - Total input %llu frames, Encoder exit!\n", VeChn, totalInputFrames);

    gCaseFail = 0;
    COMMON_VENC_AdjustLoopExit(&pCml->vencLoopExit, VeChn);

    return NULL;
}

static AX_S32 SAMPLE_VENC_StartSendFrame_ResetChn(SAMPLE_VENC_SENDFRAME_PARA_T *pstArg)
{
    AX_S32 s32Ret;

    s32Ret = pthread_create(&pstArg->sendFrmPid, 0, SAMPLE_VENC_SendFramec_ResetChn_Proc, (AX_VOID *)pstArg);

    return s32Ret;
}

AX_S32 UTestResetChn(SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret = 0;
    AX_U32 chnNum;
    AX_S32 chnIdx;
    chnNum = pCml->chnNum;
    AX_PAYLOAD_TYPE_E enType;
    SAMPLE_VENC_RC_E enRcMode = pCml->rcMode;
    AX_U64 gVencCaseLoopExit = 0;

    signal(SIGINT, SigHandler);

    for (chnIdx = 0; chnIdx < chnNum; chnIdx++) {
        memset(&gstFrmParam[chnIdx], 0, sizeof(SAMPLE_VENC_SENDFRAME_PARA_T));
        memset(&gstStrmParam[chnIdx], 0, sizeof(SAMPLE_VENC_GETSTREAM_PARA_T));

        if (pCml->bChnCustom)
            enType = SampleGetCodecType(pCml->codecType);
        else
            enType = SampleGetCodecType(chnIdx % SAMPLE_ALL_CODEC_TYPE);

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

        s32Ret = SAMPLE_VENC_StartSendFrame_ResetChn(&gstFrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_StartSendFrame err.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        sleep(1);

        SampleGetStreamInit(chnIdx, enType, &gstStrmParam[chnIdx], pCml);

        s32Ret = SAMPLE_VENC_StartGetStream(&gstStrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_StartGetStream err.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        COMMON_VENC_AdjustLoopExit(&gVencCaseLoopExit, chnIdx);
        sleep(1);
    }

    while ((!gLoopExit) && (gVencCaseLoopExit != pCml->vencLoopExit))
        sleep(1);

FREE:

    for (chnIdx = 0; chnIdx < chnNum; chnIdx++) {
        SAMPLE_VENC_StopSendFrame(&gstFrmParam[chnIdx]);
        SAMPLE_VENC_StopGetStream(&gstStrmParam[chnIdx]);
        COMMON_VENC_Stop(chnIdx);
    }

    pCml->vencLoopExit = 0;

    return s32Ret | gCaseFail;
}
