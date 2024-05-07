/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "ax_sys_api.h"
#include "ax_venc_api.h"
#include "common_venc.h"
#include "common_venc_log.h"

AX_U32 gU32ChnNum = 0;
AX_U32 gU32StartChn = 0;

static SAMPLE_VENC_GETSTREAM_PARA_T gstStrmParam[AX_MAX_VENC_CHN_NUM];
AX_VENC_MOD_ATTR_T stModAttr = {
    .enVencType = AX_VENC_MULTI_ENCODER,
    .stModThdAttr.u32TotalThreadNum = 3, /* max venc thread num is 3 */
    .stModThdAttr.bExplicitSched = AX_FALSE,
};

static AX_VOID SAMPLE_SetDefaultVencParams(SAMPLE_VENC_CMD_PARA_T *pstPara, AX_U16 width, AX_U16 height)
{
    pstPara->output = "stream.h264";

    pstPara->picW = width;
    pstPara->picH = height;
    pstPara->maxPicW = width;
    pstPara->maxPicH = height;
    pstPara->rcMode = SAMPLE_RC_CBR;
    pstPara->chnNum = 1;
    pstPara->srcFrameRate = 30;
    pstPara->dstFrameRate = 30;
    pstPara->maxIprop = 10;
    pstPara->minIprop = 10;

    pstPara->gopLen = 30;
    pstPara->virILen = pstPara->gopLen / 2;
    pstPara->bitRate = 2000;
    pstPara->qpMin = 22;
    pstPara->qpMax = 51;
    pstPara->qpMinI = 10;
    pstPara->qpMaxI = 51;
    pstPara->bLinkMode = AX_TRUE;
    pstPara->startQp = -1;
}

static AX_VOID SAMPLE_GetStreamInit(VENC_CHN VeChn, AX_PAYLOAD_TYPE_E enType, AX_BOOL bSaveStrm, SAMPLE_VENC_GETSTREAM_PARA_T *pstArg)
{
    pstArg->bGetStrmStart = AX_TRUE;
    pstArg->enType = enType;
    pstArg->syncType = 100;
    pstArg->VeChn = VeChn;
    pstArg->bSaveStrm = bSaveStrm;
}

static AX_S32 SAMPLE_VencStreamSave(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg, AX_U64 totalStream, FILE *pFile,
                                    AX_VENC_STREAM_T *pstStream)
{
    if ((NULL == pstArg) || (NULL == pstStream))
    {
        SAMPLE_LOG_ERR("pstStream or pstArg is NULL!");
        return -1;
    }
    if (NULL == pFile)
    {
        SAMPLE_LOG_ERR("chn-%d: pFile is NULL!", pstArg->VeChn);
        return -2;
    }

    printf("Venc Stream Save, SeqNum:%lld gopMode:%d temporalID:%d\n", pstStream->stPack.u64SeqNum, pstArg->gopMode, pstArg->temporalID);

    if (pstArg->gopMode != AX_VENC_GOPMODE_SVC_T)
    {
        fwrite(pstStream->stPack.pu8Addr, 1, pstStream->stPack.u32Len, pFile);
    }
    else
    {
        if (((0 == pstArg->temporalID) && (0 == pstStream->stPack.u32TemporalID)) ||
            ((1 == pstArg->temporalID) &&
             ((0 == pstStream->stPack.u32TemporalID) || (1 == pstStream->stPack.u32TemporalID))) ||
            ((2 == pstArg->temporalID) &&
             ((0 == pstStream->stPack.u32TemporalID) || (1 == pstStream->stPack.u32TemporalID) ||
              (2 == pstStream->stPack.u32TemporalID))))
            fwrite(pstStream->stPack.pu8Addr, 1, pstStream->stPack.u32Len, pFile);
    }
    fflush(pFile);
    return 0;
}

static AX_VOID *SAMPLE_VencGetStreamProc(AX_VOID *arg)
{
    AX_S32 s32Ret = -1;
    AX_VENC_STREAM_T stStream;
    FILE *pStrm = NULL;
    AX_U64 totalGetStream = 0;
    SAMPLE_VENC_GETSTREAM_PARA_T *pstArg = (SAMPLE_VENC_GETSTREAM_PARA_T *)arg;
    VENC_CHN VeChn = pstArg->VeChn;
    AX_S32 testId = pstArg->testId;
    AX_PAYLOAD_TYPE_E enType = pstArg->enType;
    AX_CHAR esName[50];

    memset(&stStream, 0, sizeof(stStream));
    memset(esName, 0, 50);

    if (pstArg->bSaveStrm) {
        if (PT_H264 == enType)
            sprintf(esName, "ivps_venc_chn%d_ut%d.264", VeChn, testId);
        else if (PT_H265 == enType)
            sprintf(esName, "ivps_venc_chn%d_ut%d.265", VeChn, testId);
        else if (PT_MJPEG == enType)
            sprintf(esName, "ivps_venc_chn%d_ut%d.mjpg", VeChn, testId);
        else if (PT_JPEG == enType)
            sprintf(esName, "ivps_venc_chn%d_ut%d.jpg", VeChn, testId);

        pStrm = fopen(esName, "wb");
        if (NULL == pStrm) {
            SAMPLE_LOG_ERR("CHN[%d] Open output file error!", VeChn);
        }
    }

    while (pstArg->bGetStrmStart)
    {
        s32Ret = AX_VENC_GetStream(VeChn, &stStream, pstArg->syncType);
        if (AX_SUCCESS == s32Ret) {

            if (pstArg->bSaveStrm && pStrm) {
                s32Ret = SAMPLE_VencStreamSave(pstArg, totalGetStream, pStrm, &stStream);
                if (0 != s32Ret)
                    SAMPLE_LOG_ERR("CHN[%d] SAMPLE_VencStreamSave error", VeChn);
            }

            totalGetStream++;

            SAMPLE_LOG_INFO("CHN[%d] Get stream success, addr=%p, len=%u, codeType=%d. seqNum %lld pts %lld\n", VeChn,
                  stStream.stPack.pu8Addr, stStream.stPack.u32Len, stStream.stPack.enCodingType,
                  stStream.stPack.u64SeqNum, stStream.stPack.u64PTS);

            s32Ret = AX_VENC_ReleaseStream(VeChn, &stStream);
            if (AX_SUCCESS != s32Ret) {
                SAMPLE_LOG_ERR("CHN[%d] AX_VENC_ReleaseStream failed!", VeChn);
                goto EXIT;
            }
        } else if (AX_ERR_VENC_FLOW_END == s32Ret) {
            SAMPLE_LOG_WARN("CHN[%d] AX_VENC_GetStream AX_ERR_VENC_FLOW_END, ret=%x\n", VeChn, s32Ret);
            goto EXIT;
        }
    }
EXIT:
    if (pStrm != NULL)
    {
        fclose(pStrm);
        pStrm = NULL;
    }

    SAMPLE_LOG_INFO("CHN[%d] Total get %llu encoded frames. getStream Exit!\n", VeChn, totalGetStream);
    return (void *)(intptr_t)s32Ret;
}

static AX_S32 SAMPLE_VencStartGetStream(SAMPLE_VENC_GETSTREAM_PARA_T *pstArg)
{
    AX_S32 s32Ret;

    s32Ret = pthread_create(&pstArg->getStrmPid, 0, SAMPLE_VencGetStreamProc, (AX_VOID *)pstArg);

    return s32Ret;
}

AX_S32 SAMPLE_VencInit(AX_S32 chnNum, AX_S32 u32StartChn, AX_U16 width, AX_U16 height, AX_PAYLOAD_TYPE_E enType, AX_BOOL bSaveStrm)
{
    int i = 0;
    VENC_CHN chn = 0;
    AX_S32 s32Ret = AX_SUCCESS;
    SAMPLE_VENC_RC_E enRcMode = 0;
    SAMPLE_VENC_CMD_PARA_T stCmdPara;

    memset(&stCmdPara, 0x0, sizeof(SAMPLE_VENC_CMD_PARA_T));
    SAMPLE_SetDefaultVencParams(&stCmdPara, width, height);
    enRcMode = stCmdPara.rcMode;

    s32Ret = AX_VENC_Init(&stModAttr);
    if (AX_SUCCESS != s32Ret)
    {
        SAMPLE_LOG_ERR("AX_VENC_Init error");
        return s32Ret;
    }

    for(i = 0; i < chnNum; i++)
    {
        chn = i + u32StartChn;
        s32Ret = COMMON_VENC_Start(chn, enType, enRcMode, &stCmdPara);
        if (AX_SUCCESS != s32Ret)
        {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_Start failed", chn);
            s32Ret = -1;
            goto FREE;
        }

        SAMPLE_GetStreamInit(chn, enType, bSaveStrm, &gstStrmParam[chn]);
        s32Ret = SAMPLE_VencStartGetStream(&gstStrmParam[chn]);
        if (AX_SUCCESS != s32Ret)
        {
            SAMPLE_LOG_ERR("chn-%d: COMMON_VENC_StartGetStream err", chn);
            s32Ret = -1;
            goto FREE;
        }
    }

    gU32ChnNum = chnNum;
    gU32StartChn = u32StartChn;

    return s32Ret;

FREE:
    for (i = 0; i < chnNum; i++) {
        chn = i + u32StartChn;
        COMMON_VENC_StopGetStream(&gstStrmParam[chn]);
        COMMON_VENC_Stop(chn);
    }

    return s32Ret;
}

AX_S32 SAMPLE_VencDeinit(void)
{
    AX_S32 s32Ret = AX_SUCCESS;
    VENC_CHN chn = 0;
    int i = 0;

    for (i = 0; i < gU32ChnNum; i++) {
        chn = i + gU32StartChn;
        COMMON_VENC_StopGetStream(&gstStrmParam[chn]);
        COMMON_VENC_Stop(chn);
    }

    s32Ret = AX_VENC_Deinit();
    if (AX_SUCCESS != s32Ret)
    {
        SAMPLE_LOG_ERR("AX_VENC_Deinit failed! Error Code:0x%X", s32Ret);
        return -1;
    }

    return s32Ret;
}
