/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_ivps_venc.h"
#include "sample_ivps_hal.h"
#include "common_sys.h"
#include "ax_buffer_tool.h"

#define FILE_NAME_SIZE 128

static VENC_GETSTREAM_PARAM_T gGetStreamPara[SAMPLE_VENC_CHN_NUM_MAX];
static pthread_t gGetStreamPid[SAMPLE_VENC_CHN_NUM_MAX];
static AX_U32 g_exit = 0;

COMMON_SYS_POOL_CFG_T gtDefMemCfg[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 4, AX_COMPRESS_MODE_LOSSY, 4},
};

/* venc get stream task */
static void *VencGetStreamProc(void *arg)
{
    AX_S32 s32Ret = -1;
    AX_VENC_RECV_PIC_PARAM_T stRecvParam;
    VENC_GETSTREAM_PARAM_T *pstPara = (VENC_GETSTREAM_PARAM_T *)arg;
    AX_VENC_STREAM_T stStream = {0};
    AX_S16 syncType = 1000;
    FILE *pStrm = NULL;
    AX_S8 esName[FILE_NAME_SIZE];
    AX_U32 totalGetStream = 0;

    s32Ret = AX_VENC_StartRecvFrame(pstPara->VeChn, &stRecvParam);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_VENC_StartRecvFrame failed, s32Ret:0x%x", s32Ret);
        return NULL;
    }

    memset(esName, 0, FILE_NAME_SIZE);

    if (pstPara->ePayloadType == PT_H265)
        sprintf((char*)esName, "enc_%d.265", pstPara->VeChn);
    else if (pstPara->ePayloadType == PT_H264)
        sprintf((char*)esName, "enc_%d.264", pstPara->VeChn);

    pStrm = fopen((char*)esName, "wb");

    if (pStrm == NULL) {
        ALOGE("Open output file error!");
    }

    while (AX_TRUE == pstPara->bThreadStart && !ThreadLoopStateGet()) {
        s32Ret = AX_VENC_GetStream(pstPara->VeChn, &stStream, syncType);

        if (AX_SUCCESS == s32Ret) {
            totalGetStream++;

            if (pStrm) {
                fwrite(stStream.stPack.pu8Addr, 1, stStream.stPack.u32Len, pStrm);
                fflush(pStrm);
            }

            s32Ret = AX_VENC_ReleaseStream(pstPara->VeChn, &stStream);
            if (AX_SUCCESS != s32Ret) {
                ALOGE("VencChn %d: AX_VENC_ReleaseStream failed!s32Ret:0x%x", pstPara->VeChn, s32Ret);
                goto EXIT;
            }
        } else if (AX_ERR_VENC_FLOW_END == s32Ret) {
            ALOGI2("VencChn %d: AX_VENC_GetStream end flow,exit!", pstPara->VeChn);
            goto EXIT;
        }

        if(SendFrmStateGet() && (totalGetStream == SendFrameNumGet())) {
            ALOGI2("VencChn %d: AX_VENC_GetStream num %d, finish!", pstPara->VeChn, totalGetStream);
            goto EXIT;
        }
    }

EXIT:
    if (pStrm != NULL) {
        fclose(pStrm);
        pStrm = NULL;
    }

    ALOGI2("VencChn %d: Total get %u encoded frames. getStream Exit!", pstPara->VeChn, totalGetStream);
    g_exit++;

    return NULL;
}

static AX_S32 SAMPLE_VENC_Init(SAMPLE_VENC_PARAM_T *pVencParam)
{
    AX_VENC_CHN_ATTR_T stVencChnAttr;
    VIDEO_CONFIG_T config = { 0 };
    AX_S32 VencChn = 0,s32Ret = 0;
    AX_VENC_MOD_ATTR_T stModAttr = {
        .enVencType = AX_VENC_MULTI_ENCODER,
        .stModThdAttr.u32TotalThreadNum = 2,
        .stModThdAttr.bExplicitSched = AX_FALSE,
    };

    s32Ret = AX_VENC_Init(&stModAttr);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_VENC_Init failed, s32Ret:0x%x", s32Ret);
        return s32Ret;
    }

    config.stRCInfo.eRCType = pVencParam->nRcMode;
    config.nGOP = pVencParam->nFps * 4;
    config.stRCInfo.nMinQp = pVencParam->nMinqp;
    config.stRCInfo.nMaxQp = pVencParam->nMaxqp;
    config.stRCInfo.nMinIQp =pVencParam->nMinIqp;
    config.stRCInfo.nMaxIQp = pVencParam->nMaxIqp;
    config.stRCInfo.nIpropMin = pVencParam->nMinIpratio;
    config.stRCInfo.nIpropMax = pVencParam->nMaxIpratio;
    config.stRCInfo.nIntraQpDelta = -2;

    config.nSrcFrameRate = pVencParam->nFps;
    config.nDstFrameRate = pVencParam->nFps;

    for (VencChn = 0; VencChn < pVencParam->nOutChnNum; VencChn++) {
        config.ePayloadType = (VencChn & 1) ? PT_H265 : PT_H264;
        config.nInWidth = pVencParam->nEncWidth;
        config.nInHeight = pVencParam->nEncHeight;

        if (pVencParam->eFbcMode)
            config.nStride = ALIGN_UP(pVencParam->nEncWidth, 128);
        else
            config.nStride = ALIGN_UP(pVencParam->nEncWidth, 16);

        config.nBitrate = pVencParam->nBps[VencChn];

        memset(&stVencChnAttr, 0, sizeof(AX_VENC_CHN_ATTR_T));

        stVencChnAttr.stVencAttr.u32MaxPicWidth = config.nInWidth;
        stVencChnAttr.stVencAttr.u32MaxPicHeight = config.nInHeight;
        stVencChnAttr.stVencAttr.u8InFifoDepth = 4;
        stVencChnAttr.stVencAttr.u8OutFifoDepth = 4;
        stVencChnAttr.stVencAttr.u32PicWidthSrc = config.nInWidth;
        stVencChnAttr.stVencAttr.u32PicHeightSrc = config.nInHeight;
        stVencChnAttr.stRcAttr.stFrameRate.fSrcFrameRate  = config.nSrcFrameRate;
        stVencChnAttr.stRcAttr.stFrameRate.fDstFrameRate = config.nDstFrameRate;

        ALOGI2("VencChn %d:w:%d, h:%d, s:%d, rcType:%d, payload:%d", VencChn,
               stVencChnAttr.stVencAttr.u32PicWidthSrc,
               stVencChnAttr.stVencAttr.u32PicHeightSrc,
               config.nStride,
               config.stRCInfo.eRCType,
               config.ePayloadType);

        stVencChnAttr.stVencAttr.u32BufSize = config.nStride * config.nInHeight * 3 / 2;
        stVencChnAttr.stVencAttr.enLinkMode = AX_LINK_MODE;

        /* GOP Setting */
        stVencChnAttr.stGopAttr.enGopMode = AX_VENC_GOPMODE_NORMALP;

        stVencChnAttr.stVencAttr.enType = config.ePayloadType;
        switch (stVencChnAttr.stVencAttr.enType) {
            case PT_H265: {
                stVencChnAttr.stVencAttr.enProfile = AX_VENC_HEVC_MAIN_PROFILE;
                stVencChnAttr.stVencAttr.enLevel = AX_VENC_HEVC_LEVEL_5_1;
                stVencChnAttr.stVencAttr.enTier = AX_VENC_HEVC_MAIN_TIER;

                if (config.stRCInfo.eRCType == SAMPLE_RC_CBR) {
                    AX_VENC_H265_CBR_T stH265Cbr = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265CBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH265Cbr.u32Gop = config.nGOP;
                    stH265Cbr.u32BitRate = config.nBitrate;
                    stH265Cbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH265Cbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH265Cbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH265Cbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH265Cbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    stH265Cbr.u32MinIprop = config.stRCInfo.nIpropMin;
                    stH265Cbr.u32MaxIprop = config.stRCInfo.nIpropMax;
                    memcpy(&stVencChnAttr.stRcAttr.stH265Cbr, &stH265Cbr, sizeof(AX_VENC_H265_CBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_VBR) {
                    AX_VENC_H265_VBR_T stH265Vbr = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265VBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH265Vbr.u32Gop = config.nGOP;
                    stH265Vbr.u32MaxBitRate = config.nBitrate;
                    stH265Vbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH265Vbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH265Vbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH265Vbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH265Vbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    memcpy(&stVencChnAttr.stRcAttr.stH265Vbr, &stH265Vbr, sizeof(AX_VENC_H265_VBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_AVBR) {
                    AX_VENC_H265_AVBR_T stH265AVbr = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265AVBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH265AVbr.u32Gop = config.nGOP;
                    stH265AVbr.u32MaxBitRate = config.nBitrate;
                    stH265AVbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH265AVbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH265AVbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH265AVbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH265AVbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    memcpy(&stVencChnAttr.stRcAttr.stH265Vbr, &stH265AVbr, sizeof(AX_VENC_H265_AVBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_FIXQP) {
                    AX_VENC_H265_FIXQP_T stH265FixQp = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H265FIXQP;
                    stH265FixQp.u32Gop = config.nGOP;
                    stH265FixQp.u32IQp = 25;
                    stH265FixQp.u32PQp = 30;
                    stH265FixQp.u32BQp = 32;
                    memcpy(&stVencChnAttr.stRcAttr.stH265FixQp, &stH265FixQp, sizeof(AX_VENC_H265_FIXQP_T));
                }
                break;
            }
            case PT_H264: {
                stVencChnAttr.stVencAttr.enProfile = AX_VENC_H264_MAIN_PROFILE;
                stVencChnAttr.stVencAttr.enLevel = AX_VENC_H264_LEVEL_5_2;

                if (config.stRCInfo.eRCType == SAMPLE_RC_CBR) {
                    AX_VENC_H264_CBR_T stH264Cbr = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264CBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH264Cbr.u32Gop = config.nGOP;
                    stH264Cbr.u32BitRate = config.nBitrate;
                    stH264Cbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH264Cbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH264Cbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH264Cbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH264Cbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    stH264Cbr.u32MinIprop = 10;//config.stRCInfo.nIpropMin;
                    stH264Cbr.u32MaxIprop = config.stRCInfo.nIpropMax;
                    memcpy(&stVencChnAttr.stRcAttr.stH264Cbr, &stH264Cbr, sizeof(AX_VENC_H264_CBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_VBR) {
                    AX_VENC_H264_VBR_T stH264Vbr = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264VBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH264Vbr.u32Gop = config.nGOP;
                    stH264Vbr.u32MaxBitRate = config.nBitrate;
                    stH264Vbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH264Vbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH264Vbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH264Vbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH264Vbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    memcpy(&stVencChnAttr.stRcAttr.stH264Vbr, &stH264Vbr, sizeof(AX_VENC_H264_VBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_AVBR) {
                    AX_VENC_H264_AVBR_T stH264AVbr = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264AVBR;
                    stVencChnAttr.stRcAttr.s32FirstFrameStartQp = -1;
                    stH264AVbr.u32Gop = config.nGOP;
                    stH264AVbr.u32MaxBitRate = config.nBitrate;
                    stH264AVbr.u32MinQp = config.stRCInfo.nMinQp;
                    stH264AVbr.u32MaxQp = config.stRCInfo.nMaxQp;
                    stH264AVbr.u32MinIQp = config.stRCInfo.nMinIQp;
                    stH264AVbr.u32MaxIQp = config.stRCInfo.nMaxIQp;
                    stH264AVbr.s32IntraQpDelta = config.stRCInfo.nIntraQpDelta;
                    memcpy(&stVencChnAttr.stRcAttr.stH264Vbr, &stH264AVbr, sizeof(AX_VENC_H264_AVBR_T));
                } else if (config.stRCInfo.eRCType == SAMPLE_RC_FIXQP) {
                    AX_VENC_H264_FIXQP_T stH264FixQp = {0};
                    stVencChnAttr.stRcAttr.enRcMode = AX_VENC_RC_MODE_H264FIXQP;
                    stH264FixQp.u32Gop = config.nGOP;
                    stH264FixQp.u32IQp = 25;
                    stH264FixQp.u32PQp = 30;
                    stH264FixQp.u32BQp = 32;
                    memcpy(&stVencChnAttr.stRcAttr.stH264FixQp, &stH264FixQp, sizeof(AX_VENC_H264_FIXQP_T));
                }
                break;
            }
            default:
                ALOGE("VencChn %d:Payload type unrecognized.",VencChn);
                return -1;
        }

        AX_S32 ret = AX_VENC_CreateChn(VencChn, &stVencChnAttr);
        if (AX_SUCCESS != ret) {
            ALOGE("VencChn %d: AX_VENC_CreateChn failed, s32Ret:0x%x", VencChn, ret);
            return -1;
        }

        /* create get output stream thread */
        gGetStreamPara[VencChn].VeChn = VencChn;
        gGetStreamPara[VencChn].bThreadStart = AX_TRUE;
        gGetStreamPara[VencChn].ePayloadType = config.ePayloadType;
        pthread_create(&gGetStreamPid[VencChn], NULL, VencGetStreamProc, (void *)&gGetStreamPara[VencChn]);
        pthread_detach(gGetStreamPid[VencChn]);
    }

    return 0;
}

static AX_S32 SampleVencDeInit(AX_S32 nChnNum)
{
    AX_S32 VencChn = 0, s32Ret = 0, s32Retry = 5;

    for (VencChn = 0; VencChn < nChnNum; VencChn++) {

        s32Ret = AX_VENC_StopRecvFrame(VencChn);
        if (0 != s32Ret) {
            ALOGE("VencChn %d:AX_VENC_StopRecvFrame failed,s32Ret:0x%x", VencChn, s32Ret);
            return s32Ret;
        }

        s32Retry = 5;
        do {
            s32Ret = AX_VENC_DestroyChn(VencChn);
            if (AX_ERR_VENC_BUSY == s32Ret) {
                ALOGE("VencChn %d:AX_VENC_DestroyChn return AX_ERR_VENC_BUSY,retry...", VencChn);
                --s32Retry;
                usleep(100 * 1000);
            } else {
                break;
            }
        } while (s32Retry >= 0);

        if (s32Retry == -1 || AX_SUCCESS != s32Ret) {
            ALOGE("VencChn %d: AX_VENC_DestroyChn failed, s32Retry=%d, s32Ret=0x%x\n", VencChn, s32Retry, s32Ret);
        }

        if (AX_TRUE == gGetStreamPara[VencChn].bThreadStart) {
            gGetStreamPara[VencChn].bThreadStart = AX_FALSE;
            pthread_join(gGetStreamPid[VencChn], NULL);
        }
    }
    s32Ret = AX_VENC_Deinit();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_VENC_Deinit failed, s32Ret=0x%x", s32Ret);
        return s32Ret;
    }

    return 0;
}

static int SAMPLE_IVPS_Init(SAMPLE_VENC_PARAM_T *pVencParam)
{
    AX_S32 s32Ret = 0, nChn;
    AX_IVPS_GRP_ATTR_T stGrpAttr = { 0 };
    AX_IVPS_PIPELINE_ATTR_T stPipelineAttr = { 0 };
    AX_IVPS_POOL_ATTR_T PoolAttr = {0};

    s32Ret = AX_IVPS_Init();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_Init failed,s32Ret:0x%x", s32Ret);
        return s32Ret;
    }

    stGrpAttr.nInFifoDepth = 4;
    stGrpAttr.ePipeline = AX_IVPS_PIPELINE_DEFAULT;
    s32Ret = AX_IVPS_CreateGrp(pVencParam->nGrpId, &stGrpAttr);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_CreateGrp failed,nGrp %d,s32Ret:0x%x", pVencParam->nGrpId, s32Ret);
        return s32Ret;
    }

    stPipelineAttr.nOutChnNum = pVencParam->nOutChnNum;
    for (nChn = 0; nChn < pVencParam->nOutChnNum; nChn++) {
        stPipelineAttr.tFilter[nChn + 1][0].bEngage = AX_TRUE;
        stPipelineAttr.tFilter[nChn + 1][0].tFRC.fSrcFrameRate = pVencParam->nFps;
        stPipelineAttr.tFilter[nChn + 1][0].tFRC.fDstFrameRate = pVencParam->nFps;
        stPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth = pVencParam->nEncWidth;
        stPipelineAttr.tFilter[nChn + 1][0].nDstPicHeight = pVencParam->nEncHeight;
        stPipelineAttr.tFilter[nChn + 1][0].nDstPicStride = ALIGN_UP(stPipelineAttr.tFilter[nChn + 1][0].nDstPicWidth, 128);
        stPipelineAttr.tFilter[nChn + 1][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
        stPipelineAttr.tFilter[nChn + 1][0].eEngine = AX_IVPS_ENGINE_TDP;
        stPipelineAttr.tFilter[nChn + 1][0].tTdpCfg.eRotation = pVencParam->eRotAngle;
        stPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_LOSSY;
        stPipelineAttr.tFilter[nChn + 1][0].tCompressInfo.u32CompressLevel = 4;
        stPipelineAttr.nOutFifoDepth[nChn] = 4;
    }

    s32Ret = AX_IVPS_SetPipelineAttr(pVencParam->nGrpId, &stPipelineAttr);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_SetPipelineAttr failed,nGrp %d,s32Ret:0x%x", pVencParam->nGrpId, s32Ret);
        return s32Ret;
    }

    PoolAttr.ePoolSrc = AX_POOL_SOURCE_PRIVATE;
    PoolAttr.nFrmBufNum = 6;
    for (nChn = 0; nChn < stPipelineAttr.nOutChnNum; nChn++) {
        s32Ret = AX_IVPS_SetChnPoolAttr(pVencParam->nGrpId, nChn, &PoolAttr);
        if (IVPS_SUCC != s32Ret) {
            ALOGE("AX_IVPS_SetGrpPoolAttr(Grp: %d) failed, ret=0x%x.", pVencParam->nGrpId, s32Ret);
            return s32Ret;
        }

        s32Ret = AX_IVPS_EnableChn(pVencParam->nGrpId, nChn);
        if (AX_SUCCESS != s32Ret) {
            ALOGE("AX_IVPS_EnableChn failed,nGrp %d,nChn %d,s32Ret:0x%x", pVencParam->nGrpId, nChn, s32Ret);
            return s32Ret;
        }
    }

    s32Ret = AX_IVPS_StartGrp(pVencParam->nGrpId);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_StartGrp failed,nGrp %d,s32Ret:0x%x", pVencParam->nGrpId, s32Ret);
        return s32Ret;
    }

    return 0;
}

static AX_S32 SampleIvpsDeInit(AX_S32 nGrpId, AX_S32 nChnNum)
{
    AX_S32 s32Ret = 0, nChn = 0;

    s32Ret = AX_IVPS_StopGrp(nGrpId);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_StopGrp failed,nGrp %d,s32Ret:0x%x", nGrpId, s32Ret);
        return s32Ret;
    }

    for (nChn = 0; nChn < nChnNum; nChn++) {
        s32Ret = AX_IVPS_DisableChn(nGrpId, nChn);
        if (AX_SUCCESS != s32Ret) {
            ALOGE("AX_IVPS_DisableChn failed,nGrp %d,nChn %d,s32Ret:0x%x", nGrpId, nChn, s32Ret);
            return s32Ret;
        }
    }

    s32Ret = AX_IVPS_DestoryGrp(nGrpId);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_DestoryGrp failed,nGrp %d,s32Ret:0x%x", nGrpId, s32Ret);
        return s32Ret;
    }

    s32Ret = AX_IVPS_Deinit();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_IVPS_Deinit failed,s32Ret:0x%x", s32Ret);
        return s32Ret;
    }

    return 0;
}

static AX_S32 SAMPLE_SYS_LinkInit(AX_S32 nGrpId, AX_U8 nChnNum)
{
    AX_S32 i = 0;

    /*
    IVPS --> VENC
    (ModId   GrpId   ChnId) | (ModId   GrpId   ChnId)
    --------------------------------------------------
    (IVPS       0       0) -> (VENC     0       0)
    (IVPS       0       1) -> (VENC     0       1)
    (IVPS       0       2) -> (VENC     0       2)
    */

    AX_MOD_INFO_T srcMod, dstMod;

    for (i = 0; i < SAMPLE_VENC_CHN_NUM_MAX; i++) {
        srcMod.enModId = AX_ID_IVPS;
        srcMod.s32GrpId = nGrpId;
        srcMod.s32ChnId = i;

        dstMod.enModId = AX_ID_VENC;
        dstMod.s32GrpId = 0;
        dstMod.s32ChnId = i;
        AX_SYS_Link(&srcMod, &dstMod);
    }

    return 0;
}

static AX_S32 SampleLinkDeInit(AX_S32 nGrpId, AX_U8 nChnNum)
{
    AX_S32 i = 0;

    AX_MOD_INFO_T srcMod, dstMod;

    for (i = 0; i < SAMPLE_VENC_CHN_NUM_MAX; i++) {
        srcMod.enModId = AX_ID_IVPS;
        srcMod.s32GrpId = nGrpId;
        srcMod.s32ChnId = i;

        dstMod.enModId = AX_ID_VENC;
        dstMod.s32GrpId = 0;
        dstMod.s32ChnId = i;
        AX_SYS_UnLink(&srcMod, &dstMod);
    }

    return 0;
}

AX_U32 SampleAddPlan(AX_POOL_FLOORPLAN_T *pPoolFloorPlan, AX_U32 nCfgCnt, AX_POOL_CONFIG_T *pPoolConfig)
{
    AX_U32 i, done = 0;
    AX_POOL_CONFIG_T *pPC;

    for (i = 0; i < nCfgCnt; i++) {
        pPC = &pPoolFloorPlan->CommPool[i];
        if (pPC->BlkSize == pPoolConfig->BlkSize) {
            pPC->BlkCnt += pPoolConfig->BlkCnt;
            done = 1;
        }
    }

    if (!done) {
        pPoolFloorPlan->CommPool[i] = *pPoolConfig;
        nCfgCnt += 1;
    }

    return nCfgCnt;
}

AX_S32 SampleCaluPool(COMMON_SYS_POOL_CFG_T *pPoolCfg, AX_U32 nCommPoolCnt, AX_POOL_FLOORPLAN_T *pPoolFloorPlan)
{
    AX_S32 i, nCfgCnt = 0;
    AX_FRAME_COMPRESS_INFO_T tCompressInfo = {0};
    AX_POOL_CONFIG_T tPoolConfig = {
        .MetaSize  = 10 * 1024,
        .CacheMode = AX_POOL_CACHE_MODE_NONCACHE,
        .PartitionName = "anonymous"
    };

    for (i = 0; i < nCommPoolCnt; i++) {
        tCompressInfo.enCompressMode = pPoolCfg->enCompressMode;
        tCompressInfo.u32CompressLevel = pPoolCfg->u32CompressLevel;
        tPoolConfig.BlkSize = AX_VIN_GetImgBufferSize(pPoolCfg->nHeight, pPoolCfg->nWidthStride, pPoolCfg->nFmt, &tCompressInfo, 0);
        tPoolConfig.BlkCnt  = pPoolCfg->nBlkCnt;
        nCfgCnt = SampleAddPlan(pPoolFloorPlan, nCfgCnt, &tPoolConfig);
        pPoolCfg += 1;
    }

    return 0;
}

AX_S32 SampleMemInit(SAMPLE_VENC_PARAM_T *pCml)
{
    AX_S32 s32Ret = -1;
    AX_POOL_CONFIG_T stPoolConfig;
#if 0
    AX_U32 u32PoolCnt = sizeof(gtDefMemCfg) / sizeof(gtDefMemCfg[0]);
    COMMON_SYS_POOL_CFG_T *pstPoolConfig = gtDefMemCfg;
    AX_POOL_FLOORPLAN_T tPoolFloorPlan = {0};

    pstPoolConfig->nWidth = pCml->nEncWidth;
    pstPoolConfig->nHeight = pCml->nEncHeight;
    pstPoolConfig->nWidthStride = ALIGN_UP(pCml->nEncWidth, 128);
    ALOGI2("pool res %d %d stride %d\n", pstPoolConfig->nWidth, pstPoolConfig->nHeight, pstPoolConfig->nWidthStride);
#endif

    s32Ret = AX_SYS_Init();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_SYS_Init failed! Error Code:0x%X\n", s32Ret);
        return -1;
    }

    /* Release last Pool */
    s32Ret = AX_POOL_Exit();
    if (0 != s32Ret) {
        ALOGI2("AX_POOL_Exit fail!!Error Code:0x%X\n", s32Ret);
    }
#if 0
    /* Calc Pool BlkSize/BlkCnt */
    s32Ret = SampleCaluPool(pstPoolConfig, u32PoolCnt, &tPoolFloorPlan);
    if (0 != s32Ret) {
        ALOGE("SampleCaluPool failed, ret=0x%x.\n", s32Ret);
        return -1;
    }

    s32Ret = AX_POOL_SetConfig(&tPoolFloorPlan);
    if (0 != s32Ret) {
        ALOGE("AX_POOL_SetConfig fail!Error Code:0x%X\n", s32Ret);
        return -1;
    } else {
        ALOGI2("AX_POOL_SetConfig success!\n");
    }

    s32Ret = AX_POOL_Init();
    if (0 != s32Ret) {
        ALOGE("AX_POOL_Init fail!!Error Code:0x%X\n", s32Ret);
        return -1;
    } else {
        ALOGI2("AX_POOL_Init success!\n");
    }
#endif

    /* use user pool */
    memset(&stPoolConfig, 0, sizeof(AX_POOL_CONFIG_T));
    stPoolConfig.MetaSize = 0x128000;
    stPoolConfig.BlkCnt = 8;
    stPoolConfig.BlkSize = pCml->nFrameSize;
    stPoolConfig.IsMergeMode = AX_TRUE;
    stPoolConfig.CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    memset(stPoolConfig.PartitionName, 0, sizeof(stPoolConfig.PartitionName));
    strcpy((AX_CHAR *)stPoolConfig.PartitionName, "anonymous");

    pCml->nPoolId = AX_POOL_CreatePool(&stPoolConfig);
    if (AX_INVALID_POOLID == pCml->nPoolId) {
        ALOGE("Create pool err.\n");
        goto FREE_SYS;
    }

    return 0;

FREE_SYS:
    s32Ret = AX_SYS_Deinit();
    if (AX_SUCCESS != s32Ret) {
        ALOGE("AX_SYS_Deinit failed! Error Code:0x%X\n", s32Ret);
        s32Ret = -1;
    }

    return s32Ret;
}

AX_S32 SampleMemDeinit(SAMPLE_VENC_PARAM_T *pCml)
{
    AX_S32 s32Ret = -1;

    if (AX_INVALID_POOLID != pCml->nPoolId) {
        s32Ret = AX_POOL_DestroyPool(pCml->nPoolId);
        if (s32Ret) {
            ALOGE("Pool destroy error, ret=%d.\n", s32Ret);
            return -1;
        }
    }

    /* exit pool */
    s32Ret = AX_POOL_Exit();
    if (0 != s32Ret) {
        ALOGI2("AX_POOL_Exit fail!!Error Code:0x%X\n", s32Ret);
    }

    s32Ret = AX_SYS_Deinit();
    if (s32Ret) {
        ALOGE("AX_SYS_Deinit failed! Error Code:0x%X\n", s32Ret);
        return -1;
    }

    return 0;
}
/*
 *                  |--> VENC0 --> RTSP0 (2688x1520)
 *                  |
 *   VIN --> IVPS --|--> VENC1 --> RTSP1 (1920x1080)
 *                  |
 *                  |--> VENC2 --> RTSP2 (720x576)
 */
static AX_S32 SAMPLE_IVPS_VENC(SAMPLE_VENC_PARAM_T *pVencParam)
{
    AX_S32 s32Ret = 0;
    SAMPLE_IMAGE_INFO_T tImageInfo = {0};

    s32Ret = SampleMemInit(pVencParam);
    if (s32Ret) {
        ALOGE("AX_SYS_SetIVPSMode failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL;
    }

    /* Step3: link init */
    s32Ret = SAMPLE_SYS_LinkInit(pVencParam->nGrpId, pVencParam->nOutChnNum);
    if (s32Ret) {
        ALOGE("SAMPLE_SYS_LinkInit failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL1;
    }

    /* Step5: IVPS init */
    s32Ret = SAMPLE_IVPS_Init(pVencParam);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("SAMPLE_IVPS_Init failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL2;
    }

    /* Step6: VENC init */
    s32Ret = SAMPLE_VENC_Init(pVencParam);
    if (AX_SUCCESS != s32Ret) {
        ALOGE("SAMPLE_VENC_Init failed, ret:0x%x", s32Ret);
        goto EXIT_FAIL3;
    }

    tImageInfo.pImgFile = pVencParam->pFileName;
    tImageInfo.nPoolId = pVencParam->nPoolId;
    tImageInfo.encFrmNum = pVencParam->encFrmNum;

    tImageInfo.tImage.eFormat = pVencParam->eYuvFormat;
    tImageInfo.tImage.nW = pVencParam->nInWidth;
    tImageInfo.tImage.nH = pVencParam->nInHeight;
    tImageInfo.tImage.nStride = pVencParam->nInWidth;

    tImageInfo.tRect.nX = 0;
    tImageInfo.tRect.nY = 0;
    tImageInfo.tRect.nW = tImageInfo.tImage.nW;
    tImageInfo.tRect.nH = tImageInfo.tImage.nH;

    SAMPLE_IVPS_SendFrame(pVencParam->nGrpId, tImageInfo);

    while (!ThreadLoopStateGet()) {
        sleep(1);
        if (g_exit >= SAMPLE_VENC_CHN_NUM_MAX)
            break;
    }

    SampleVencDeInit(pVencParam->nOutChnNum);
EXIT_FAIL3:
    SampleIvpsDeInit(pVencParam->nGrpId, pVencParam->nOutChnNum);
EXIT_FAIL2:
    SampleLinkDeInit(pVencParam->nGrpId, pVencParam->nOutChnNum);
EXIT_FAIL1:
    SampleMemDeinit(pVencParam);
EXIT_FAIL:
    return s32Ret;
}

AX_VOID PrintHelp()
{
    printf("\nNOTE:\n");
    printf("\n\t1. input yuv support nv12 only!!!\n");
    printf("\n\t2. chan 0 -> 264 chan 1 -> 265\n");

    printf("\nCMD:\n");
    printf("\n\t-w: in width\n");
    printf("\n\t-h: in height\n");
    printf("\n\t-W: enc widht\n");
    printf("\n\t-H: enc height\n");

    printf("\n\t-m: rc mode: 0 cbr 1 vbr 2 avbr 5 cvbr; only support cbr/vbr/avbr\n");
    printf("\n\t-b: chan 0 bps: Kbps\n");
    printf("\n\t-B: chan 1 bps: Kbps\n");
    printf("\n\t-f: fps\n");

    printf("\n\t-q: min qp, def min qp 10\n");
    printf("\n\t-Q: max qp, def max qp cbr/cvbr 51 vbr/avbr 42\n");

    printf("\n\t-p: min i qp, def min i qp cbr/cvbr 10 vbr/avbr 24\n");
    printf("\n\t-P: max i qp, def max i qp 51\n");

    printf("\n\t-r: min ip ratio for h265, h264 def 10\n");
    printf("\n\t-R: max ip ratio\n");

    printf("\n\t-i: input file name/path\n");
    printf("\n\t-n: enc frm num, def -1 (repeat read yuv when yuv in frms < n)\n");

    printf("\n\texample1\n");
    printf("\t\t/opt/bin/sample_ivps_venc -i 2688x1520.nv12 -w 2688 -h 1520 -W 2688 -H 1520\n");
}

static AX_VOID SigInt(AX_S32 signo)
{
    ALOGI2("SigInt Catch signal %d", signo);
    ThreadLoopStateSet(AX_TRUE);
}

static AX_VOID SigStop(AX_S32 signo)
{
    ALOGI2("SigStop Catch signal %d", signo);
    ThreadLoopStateSet(AX_TRUE);
}

int main(int argc, char *argv[])
{
    ALOGI2("IVPS_VENC Sample. Build at %s %s", __DATE__, __TIME__);

    int c;
    int isExit = 0;
    SAMPLE_VENC_PARAM_T tVencParam = {0};

    /* def prm */
    tVencParam.nMinIpratio = 30;
    tVencParam.nMaxIpratio = 40;

    tVencParam.nMinqp = 0;
    tVencParam.nMaxqp = 0;
    tVencParam.nMinIqp = 0;
    tVencParam.nMaxIqp = 0;

    tVencParam.nFps = 25;
    tVencParam.nRcMode = 0; /* def cbr */
    tVencParam.nBps[0] = 2048;
    tVencParam.nBps[1] = 2048;
    tVencParam.eFbcMode = AX_TRUE;

    tVencParam.eYuvFormat = AX_FORMAT_YUV420_SEMIPLANAR;
    tVencParam.encFrmNum = -1;

    tVencParam.eRotAngle = AX_IVPS_ROTATION_0;

    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, SigInt);
    signal(SIGTSTP, SigStop);

    if (argc < 3) {
        PrintHelp();
        exit(0);
    }

    while ((c = getopt(argc, argv, "w:h:W:H:m:b:B:f:q:Q:p:P:r:R:t:i:n:")) != -1) {
        isExit = 0;
        switch (c) {
        case 'w':
            tVencParam.nInWidth = atoi(optarg);
            break;
        case 'h':
            tVencParam.nInHeight = atoi(optarg);
            break;
        case 'W':
            tVencParam.nEncWidth = atoi(optarg);
            break;
        case 'H':
            tVencParam.nEncHeight = atoi(optarg);
            break;
        case 'm':
            tVencParam.nRcMode = atoi(optarg);
            break;
        case 'b':
            tVencParam.nBps[0] = atoi(optarg);
            break;
        case 'B':
            tVencParam.nBps[1] = atoi(optarg);
            break;
        case 'f':
            tVencParam.nFps = atoi(optarg);
            break;
        case 'q':
            tVencParam.nMinqp = atoi(optarg);
            break;
        case 'Q':
            tVencParam.nMaxqp = atoi(optarg);
            break;
        case 'p':
            tVencParam.nMinIqp = atoi(optarg);
            break;
        case 'P':
            tVencParam.nMaxIqp = atoi(optarg);
            break;
        case 'r':
            tVencParam.nMinIpratio = atoi(optarg);
            break;
        case 'R':
            tVencParam.nMaxIpratio = atoi(optarg);
            break;
        case 'i':
            tVencParam.pFileName = optarg;
            break;
        case 'n':
            tVencParam.encFrmNum = (AX_S32)atoi(optarg);;
            break;
        default:
            isExit = 1;
            break;
        }
    }

    if ((0 == tVencParam.nRcMode) || (5 == tVencParam.nRcMode)) {
        if (0 == tVencParam.nMinqp)
            tVencParam.nMinqp = 10;

        if (0 == tVencParam.nMaxqp)
            tVencParam.nMaxqp = 51;

        if (0 == tVencParam.nMinIqp)
            tVencParam.nMinIqp = 10;

        if (0 == tVencParam.nMaxIqp)
            tVencParam.nMaxIqp = 51;
    } else {
        if (0 == tVencParam.nMinqp)
            tVencParam.nMinqp = 31;

        if (0 == tVencParam.nMaxqp)
            tVencParam.nMaxqp = 46;

        if (0 == tVencParam.nMinIqp)
            tVencParam.nMinIqp = 31;

        if (0 == tVencParam.nMaxIqp)
            tVencParam.nMaxIqp = 46;
    }

    tVencParam.nOutChnNum = SAMPLE_VENC_CHN_NUM_MAX;
    tVencParam.nGrpId = 0;
    tVencParam.nFrameSize = tVencParam.nInWidth * tVencParam.nInHeight * 3 / 2;

    ALOGI2("in prm: res %dx%d enc %dx%d rcmod %d bps %d-%d fps %d \n",
            tVencParam.nInWidth, tVencParam.nInHeight,
            tVencParam.nEncWidth, tVencParam.nEncHeight, tVencParam.nRcMode,
            tVencParam.nBps[0], tVencParam.nBps[1], tVencParam.nFps);
    ALOGI2("in prm qp %d-%d iqp %d-%d ipratio %d-%d fmt %d input file %s\n",
            tVencParam.nMinqp, tVencParam.nMaxqp,
            tVencParam.nMinIqp, tVencParam.nMaxIqp,
            tVencParam.nMinIpratio, tVencParam.nMaxIpratio,
            tVencParam.eYuvFormat, tVencParam.pFileName);

    if (isExit) {
        PrintHelp();
        exit(0);
    }

    SAMPLE_IVPS_VENC(&tVencParam);

    ALOGI2("Sample Completed");

    exit(0);
}
