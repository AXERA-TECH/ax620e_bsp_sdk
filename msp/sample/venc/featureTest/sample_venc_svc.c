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

extern AX_U64 gVencLoopExit;

static AX_VENC_SVC_PARAM_T stSvcParam = {0};
static AX_VENC_SVC_REGION_T stSvcRegion = {0};

AX_S32 SampleVencSvc(AX_S32 VencChn, AX_VOID *handle)
{
    AX_S32 s32Ret = AX_SUCCESS;
    int i = 0;
    float fStep = 0.0;
    SAMPLE_VENC_SENDFRAME_PARA_T *pCml = (SAMPLE_VENC_SENDFRAME_PARA_T *)handle;

    if (pCml->enType == PT_JPEG || pCml->enType == PT_MJPEG)
        return AX_SUCCESS;

    if ((pCml->svcRegionNum > AX_VENC_SVC_MAX_RECT_NUM) || (pCml->svcRegionNum == 0)) {
        SAMPLE_LOG_ERR("Chn %d: svcRegionNum %d inv\n", VencChn, pCml->svcRegionNum);
        return AX_ERR_VENC_ILLEGAL_PARAM;
    }

    s32Ret = AX_VENC_EnableSvc(VencChn, AX_TRUE);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("Chn %d: AX_VENC_EnableSvc failed, ret=%#x\n", VencChn, s32Ret);
        return -1;
    }

    s32Ret = AX_VENC_GetSvcParam(VencChn, &stSvcParam);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("Chn %d: AX_VENC_GetSvcParam failed, ret=%#x\n", VencChn, s32Ret);
        return -1;
    }

    stSvcParam.u32RectTypeNum = AX_VENC_SVC_RECT_TYPE_BUTT;

    if (pCml->svcQpMod) {
        stSvcParam.bAbsQp = AX_TRUE;
        stSvcParam.bSync = AX_FALSE;
        stSvcParam.stBgQpCfg.iQp = 40;
        stSvcParam.stBgQpCfg.pQp = 40;

        for (i = 0; i < AX_VENC_SVC_RECT_TYPE_BUTT; i++) {
            stSvcParam.stQpCfg[i].iQp = 20 + i * 2;
            stSvcParam.stQpCfg[i].pQp = 20 + i * 2;
        }
    } else {
        stSvcParam.bAbsQp = AX_FALSE;
        stSvcParam.bSync = AX_FALSE;
        stSvcParam.stBgQpCfg.iQp = 10;
        stSvcParam.stBgQpCfg.pQp = 10;

        for (i = 0; i < AX_VENC_SVC_RECT_TYPE_BUTT; i++) {
            stSvcParam.stQpCfg[i].iQp = -3 - i * 2;
            stSvcParam.stQpCfg[i].pQp = -3 - i * 2;
        }
    }

    s32Ret = AX_VENC_SetSvcParam(VencChn, &stSvcParam);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("Chn %d: AX_VENC_SetSvcParam failed, ret=%#x\n", VencChn, s32Ret);
        return s32Ret;
    }

    s32Ret = AX_VENC_GetSvcParam(VencChn, &stSvcParam);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("Chn %d: AX_VENC_GetSvcParam failed, ret=%#x\n", VencChn, s32Ret);
        return s32Ret;
    }

    SAMPLE_LOG_WARN("chn %d svc param:\n", VencChn);
    SAMPLE_LOG_WARN("bAbsQp: %d\n", stSvcParam.bAbsQp);
    SAMPLE_LOG_WARN("bSync: %d\n", stSvcParam.bSync);
    SAMPLE_LOG_WARN("stBgQpCfg: iqp %d pqp %d\n", stSvcParam.stBgQpCfg.iQp, stSvcParam.stBgQpCfg.pQp);
    SAMPLE_LOG_WARN("stQpCfg 0: iqp %d pqp %d\n", stSvcParam.stQpCfg[0].iQp, stSvcParam.stQpCfg[0].pQp);
    SAMPLE_LOG_WARN("stQpCfg 1: iqp %d pqp %d\n", stSvcParam.stQpCfg[1].iQp, stSvcParam.stQpCfg[1].pQp);
    SAMPLE_LOG_WARN("stQpCfg 2: iqp %d pqp %d\n", stSvcParam.stQpCfg[2].iQp, stSvcParam.stQpCfg[2].pQp);
    SAMPLE_LOG_WARN("stQpCfg 3: iqp %d pqp %d\n", stSvcParam.stQpCfg[3].iQp, stSvcParam.stQpCfg[3].pQp);
    SAMPLE_LOG_WARN("stQpCfg 4: iqp %d pqp %d\n", stSvcParam.stQpCfg[4].iQp, stSvcParam.stQpCfg[4].pQp);

    stSvcRegion.u32RectNum = pCml->svcRegionNum;
    fStep = 1.0 / (pCml->svcRegionNum + 1);
    for (i = 0; i < stSvcRegion.u32RectNum; i++) {
        stSvcRegion.stRect[i].fX = fStep * i;
        stSvcRegion.stRect[i].fY = fStep * i;
        stSvcRegion.stRect[i].fWidth = fStep;
        stSvcRegion.stRect[i].fHeight = fStep;
        stSvcRegion.enRectType[i] = i % AX_VENC_SVC_RECT_TYPE_BUTT;
    }

    SAMPLE_LOG_WARN("chn %d svc region cnt: %d\n", VencChn, stSvcRegion.u32RectNum);
    for (i = 0; i< stSvcRegion.u32RectNum; i++) {
        SAMPLE_LOG_WARN("region %d param: type %d rect %f %f %f %f\n", i, stSvcRegion.enRectType[i],
            stSvcRegion.stRect[i].fX, stSvcRegion.stRect[i].fY,
            stSvcRegion.stRect[i].fWidth, stSvcRegion.stRect[i].fHeight);
    }

    stSvcRegion.u64Pts = USER_SET_PTS_VALUE;

    s32Ret = AX_VENC_SetSvcRegion(VencChn, &stSvcRegion);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("Chn %d: AX_VENC_SetSvcRegion failed, ret=%#x\n", VencChn, s32Ret);
        return s32Ret;
    }

    s32Ret = AX_VENC_GetSvcRegion(VencChn, &stSvcRegion);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("Chn %d: AX_VENC_GetSvcRegion failed, ret=%#x\n", VencChn, s32Ret);
        return s32Ret;
    }

    return AX_SUCCESS;
}