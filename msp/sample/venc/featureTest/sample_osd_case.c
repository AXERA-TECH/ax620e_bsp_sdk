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
static AX_U64 osdLumaPhyAddr[AX_MAX_VENC_CHN_NUM][AX_MAX_VENC_OSD_NUM] = { 0 };
static AX_VOID *osdLumaVirAddr[AX_MAX_VENC_CHN_NUM][AX_MAX_VENC_OSD_NUM] = { NULL };
static SAMPLE_VENC_SENDFRAME_PARA_T gstFrmParam[AX_MAX_VENC_CHN_NUM];
static SAMPLE_VENC_GETSTREAM_PARA_T gstStrmParam[AX_MAX_VENC_CHN_NUM];

static AX_VOID SigHandler(AX_S32 signo)
{
    SAMPLE_LOG("catch signal(%d).\n", signo);
    gLoopExit = AX_TRUE;
}

static AX_S32 SampleOSDConfig(AX_S32 VencChn, SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret = AX_SUCCESS;
    AX_S32 i = 0;
    AX_VENC_OSD_ATTR_T stVencOsdAttr;
    AX_S32 osdFileSize = 0;
    FILE * fp = NULL;

    memset(&stVencOsdAttr, 0, sizeof(AX_VENC_OSD_ATTR_T));
    s32Ret = AX_VENC_GetOsdAttr(VencChn, &stVencOsdAttr);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("AX_VENC_GetOsdAttr:%d failed! ret=0x%x\n", VencChn, s32Ret);
        return -1;
    }

    for (i = 0; i < AX_MAX_VENC_OSD_NUM; i++) {

        if (!pCml->osdEnable) {
            goto exit;
        }

        if (pCml->osdWidth[i] == 0 || pCml->osdHeight[i] == 0) {
            stVencOsdAttr.bEnable[i] = AX_FALSE;
            continue;
        }

        switch (pCml->osdFormat[i]) {
            case AX_FORMAT_YUV420_PLANAR:
            case AX_FORMAT_YUV420_SEMIPLANAR:
            case AX_FORMAT_YUV420_SEMIPLANAR_VU:
                osdFileSize = pCml->osdHeight[i] * pCml->osdWidth[i] * 3 / 2;
                break;
            case AX_FORMAT_ARGB4444:
            case AX_FORMAT_RGBA4444:
            case AX_FORMAT_ABGR4444:
            case AX_FORMAT_BGRA4444:
            case AX_FORMAT_RGBA5551:
            case AX_FORMAT_ABGR1555:
            case AX_FORMAT_BGRA5551:
            case AX_FORMAT_ARGB1555:
                osdFileSize = pCml->osdHeight[i] * pCml->osdWidth[i] * 2;
                break;
            case AX_FORMAT_ARGB8565:
            case AX_FORMAT_RGBA5658:
            case AX_FORMAT_ABGR8565:
            case AX_FORMAT_BGRA5658:
                osdFileSize = pCml->osdHeight[i] * pCml->osdWidth[i] * 3;
                break;
            case AX_FORMAT_RGBA8888:
            case AX_FORMAT_ARGB8888:
            case AX_FORMAT_BGRA8888:
            case AX_FORMAT_ABGR8888:
                osdFileSize = pCml->osdHeight[i] * pCml->osdWidth[i] * 4;
                break;
            default:
                SAMPLE_LOG_ERR("osd %d unsupported format %d\n", i ,pCml->osdFormat[i]);
                s32Ret = -1;
                goto exit;
        }

        if (pCml->fbcType == AX_COMPRESS_MODE_LOSSY) {
            osdFileSize = osdFileSize / 2;
        }

        s32Ret = AX_SYS_MemAlloc(&osdLumaPhyAddr[VencChn][i], &osdLumaVirAddr[VencChn][i], osdFileSize , 0x1000, (AX_S8 *)"osd_data");
        if (s32Ret) {
            SAMPLE_LOG_ERR("AX_SYS_MemAlloc osd %d failed\n", i);
            s32Ret = -1;
            goto exit;
        }

        fp = fopen(pCml->osdInput[i], "rb");
        if (fp == NULL) {
            SAMPLE_LOG_ERR("open osd file %s failed\n", pCml->osdInput[i]);
            s32Ret = -1;
            goto exit;
        }

        fseeko(fp, 0, SEEK_SET);
        fread((void *)osdLumaVirAddr[VencChn][i], 1, osdFileSize, fp);
        fclose(fp);
        fp = NULL;

        stVencOsdAttr.bEnable[i] = AX_TRUE;
        stVencOsdAttr.stOsdBmpAttr[i].u16Alpha = 128;
        stVencOsdAttr.stOsdBmpAttr[i].enRgbFormat = pCml->osdFormat[i];
        stVencOsdAttr.stOsdBmpAttr[i].u64PhyAddr = osdLumaPhyAddr[VencChn][i];
        stVencOsdAttr.stOsdBmpAttr[i].u32BmpWidth = pCml->osdWidth[i];
        stVencOsdAttr.stOsdBmpAttr[i].u32BmpHeight = pCml->osdHeight[i];
        stVencOsdAttr.stOsdBmpAttr[i].u32DstXoffset = pCml->osdXoffset[i];
        stVencOsdAttr.stOsdBmpAttr[i].u32DstYoffset = pCml->osdYoffset[i];

        SAMPLE_LOG_DEBUG("osd_%d: input_file:%s, format:%d, width:%d, height:%d, Xoffset:%d, Yoffset:%d, fbcType:%d\n",
                        i, pCml->osdInput[i], pCml->osdFormat[i], pCml->osdWidth[i], pCml->osdHeight[i],
                        pCml->osdXoffset[i], pCml->osdYoffset[i], pCml->fbcType);
    }

    s32Ret = AX_VENC_SetOsdAttr(VencChn, &stVencOsdAttr);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("AX_VENC_SetOsdAttr:%d failed! ret=0x%x\n", VencChn, s32Ret);
        return -1;
    }

exit:

    return s32Ret;
}

static AX_S32 SampleChnAttr(AX_S32 VencChn, SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret = AX_SUCCESS;
    AX_VENC_CHN_ATTR_T stChnAttr;

    memset(&stChnAttr, 0, sizeof(AX_VENC_CHN_ATTR_T));
    s32Ret = AX_VENC_GetChnAttr(VencChn, &stChnAttr);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("AX_VENC_GetChnAttr:%d failed! ret=0x%x\n", VencChn, s32Ret);
        return -1;
    }

    if (pCml->bCrop) {
        stChnAttr.stVencAttr.stCropCfg.stRect.s32X = pCml->cropX;
        stChnAttr.stVencAttr.stCropCfg.stRect.s32Y = pCml->cropY;
        stChnAttr.stVencAttr.stCropCfg.stRect.u32Width = pCml->cropW;
        stChnAttr.stVencAttr.stCropCfg.stRect.u32Height = pCml->cropH;
    } else {
        return 0;
    }

    s32Ret = AX_VENC_SetChnAttr(VencChn, &stChnAttr);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_LOG_ERR("AX_VENC_SetChnAttr:%d failed! ret=0x%x\n", VencChn, s32Ret);
        return -1;
    }

    SAMPLE_LOG_DEBUG("CropX:%d,CropY:%d,CropW:%d,CropH:%d\n", pCml->cropX, pCml->cropY, pCml->cropW, pCml->cropH);
    return AX_SUCCESS;
}

AX_S32 UTestOSD(SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret = 0;
    AX_U32 chnNum;
    AX_S32 chnIdx;
    AX_U8 osdIdx;
    chnNum = pCml->chnNum;
    AX_PAYLOAD_TYPE_E enType;
    SAMPLE_VENC_RC_E enRcMode = pCml->rcMode;
    AX_U64 gVencCaseLoopExit = 0;

    signal(SIGINT, SigHandler);

    if (pCml->qpMapQpType || pCml->qpMapBlkType) {
        SAMPLE_LOG_ERR(" This UT not support QpMap!\n");
        return -1;
    }

    pCml->syncGet = 100;

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

        /* Set Chn Attr */
        s32Ret = SampleChnAttr(chnIdx, pCml);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: SampleChnAttr failed.\n", chnIdx);
            goto FREE;
        }

        /* Set OSD config */
        s32Ret = SampleOSDConfig(chnIdx, pCml);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: SampleOSDConfig failed.\n", chnIdx);
            goto FREE;
        }

        SampleSendFrameInit(chnIdx, enType, &gstFrmParam[chnIdx], pCml);

        s32Ret = SAMPLE_VENC_StartSendFrame(&gstFrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: SAMPLE_VENC_StartSendFrame err.\n", chnIdx);
            s32Ret = -1;
            goto FREE;
        }

        sleep(1);

        SampleGetStreamInit(chnIdx, enType, &gstStrmParam[chnIdx], pCml);

        s32Ret = SAMPLE_VENC_StartGetStream(&gstStrmParam[chnIdx]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_LOG_ERR("chn-%d: SAMPLE_VENC_StartGetStream err.\n", chnIdx);
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

        for (osdIdx = 0; osdIdx < AX_MAX_VENC_OSD_NUM; osdIdx++) {
            if (osdLumaPhyAddr[chnIdx][osdIdx])
                AX_SYS_MemFree(osdLumaPhyAddr[chnIdx][osdIdx], osdLumaVirAddr[chnIdx][osdIdx]);
        }
    }

    pCml->vencLoopExit = 0;

    return s32Ret;
}