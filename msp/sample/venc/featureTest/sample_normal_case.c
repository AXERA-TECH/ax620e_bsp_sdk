/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <assert.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "ax_sys_api.h"
#include "ax_venc_comm.h"
#include "common_venc.h"
#include "sample_cmd_params.h"
#include "sample_global.h"
#include "sample_unit_test.h"
#include "sample_venc_log.h"

static AX_BOOL gLoopExit = AX_FALSE;
static AX_S32 syncGet = 0;
static AX_U32 u32StartChan = 0, u32ChnNum = 0;

static SAMPLE_VENC_SENDFRAME_PARA_T gstFrmParam[AX_MAX_VENC_CHN_NUM];
static SAMPLE_VENC_GETSTREAM_PARA_T gstStrmParam[AX_MAX_VENC_CHN_NUM];

static void SigHandler(AX_S32 signo)
{
    AX_S32 chnIdx;
    SAMPLE_LOG("catch signal(%d).\n", signo);
    gLoopExit = AX_TRUE;

    /* if GetStream is block mode, we should call DestroyChn here when receiving Ctrl+C */
    if (syncGet == -1) {
        for (chnIdx = u32StartChan; chnIdx < u32ChnNum + u32StartChan; chnIdx++) {
            COMMON_VENC_Stop(chnIdx);
        }
        syncGet = 0;
    }
}

AX_S32 UTestNormal(SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret = 0;
    AX_U32 chnNum;
    AX_S32 chnIdx;
    chnNum = pCml->chnNum;
    AX_PAYLOAD_TYPE_E enType;
    SAMPLE_VENC_RC_E enRcMode = pCml->rcMode;
    AX_U64 gVencCaseLoopExit = 0;

    signal(SIGINT, SigHandler);

    if (pCml->qpMapQpType || pCml->qpMapBlkType) {
        SAMPLE_LOG_ERR(" This UT not support QpMap!\n");
        return -1;
    }
    /* set partition name is VENC*/
    if(pCml->bSetPartition) {
        AX_MOD_INFO_T modInfo = { 0 };
        modInfo.enModId = AX_ID_VENC;
        modInfo.s32GrpId = 0;
        modInfo.s32ChnId = 0;
        /* set new partition name */
        s32Ret = AX_SYS_MemSetConfig(&modInfo, (AX_S8 *)"VENC");
        if (s32Ret) {
            SAMPLE_LOG_ERR("AX_SYS_MemSetConfig failed,ret=0x%x\n", s32Ret);
            return -1;
        }
    }

    for (chnIdx = pCml->u32StartChan; chnIdx < chnNum + pCml->u32StartChan; chnIdx++) {
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

        s32Ret = COMMON_VENC_StartSendFrame(&gstFrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_StartSendFrame err.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        sleep(1);

        SampleGetStreamInit(chnIdx, enType, &gstStrmParam[chnIdx], pCml);

        if (pCml->ut == UT_CASE_BLOCK_NOBLOCK_TIMEOUT) {
            syncGet = pCml->syncGet;
            u32ChnNum = pCml->chnNum;
            u32StartChan = pCml->u32StartChan;
        }

        s32Ret = COMMON_VENC_StartGetStream(&gstStrmParam[chnIdx]);
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

    for (chnIdx = pCml->u32StartChan; chnIdx < chnNum + pCml->u32StartChan; chnIdx++) {
        COMMON_VENC_StopSendFrame(&gstFrmParam[chnIdx]);
        COMMON_VENC_StopGetStream(&gstStrmParam[chnIdx]);
        if ((pCml->syncGet != -1) || (pCml->ut != UT_CASE_BLOCK_NOBLOCK_TIMEOUT)) {
            COMMON_VENC_Stop(chnIdx);
        }
    }

    pCml->vencLoopExit = 0;

    return s32Ret;
}