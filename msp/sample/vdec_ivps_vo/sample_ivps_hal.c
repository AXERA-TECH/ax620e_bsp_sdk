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
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include "ax_base_type.h"
#include "ax_sys_api.h"
#include "ax_buffer_tool.h"
#include "ax_ivps_api.h"


#ifndef AX_SUCCESS
    #define AX_SUCCESS                          0
#endif

extern AX_S32 gLoopExit;

AX_U32 gU32GrpNum = 0;
AX_U32 gU32StartGrp = 0;

#define SAMPLE_LOG(str, arg...)    \
    do {    \
        printf("%s: %s:%d "str"\n", "sample_vdec_ivps.c", __func__, __LINE__, ##arg); \
    } while(0)

#define SAMPLE_ERR_LOG(str, arg...)   \
    do{  \
        printf("%s: %s:%d Error! "str"\n", "sample_vdec_ivps.c", __func__, __LINE__, ##arg); \
    }while(0)


#define IVPS_BUF_POOL_MEM_SIZE (0x100000 * 40) // 40M
#define VDEC_ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))

typedef struct {
    AX_U32 nSize;
    AX_U32 nCnt;
} BLK_INFO_S;


AX_U32 CalcImgSize(AX_U32 nStride, AX_U32 nW, AX_U32 nH, AX_IMG_FORMAT_E eType, AX_U32 nAlign)
{
    AX_U32 nBpp = 0;
    if (nW == 0 || nH == 0) {
        SAMPLE_LOG("Invalid width %d or height %d!", nW, nH);
        return 0;
    }

    if (0 == nStride) {
        nStride = (0 == nAlign) ? nW : VDEC_ALIGN_UP(nW, nAlign);
    } else {
        if (nAlign > 0) {
            if (nStride % nAlign) {
                SAMPLE_ERR_LOG(" stride: %u not %u aligned.!", nStride, nAlign);
                return 0;
            }
        }
    }

    switch (eType) {
    case AX_FORMAT_YUV420_PLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR:
    case AX_FORMAT_YUV420_SEMIPLANAR_VU:
        nBpp = 12;
        break;
    case AX_FORMAT_YUV422_INTERLEAVED_YUYV:
    case AX_FORMAT_YUV422_INTERLEAVED_UYVY:
        nBpp = 16;
        break;
    case AX_FORMAT_YUV444_PACKED:
    case AX_FORMAT_RGB888:
    case AX_FORMAT_BGR888:
        nBpp = 24;
        break;
    case AX_FORMAT_RGBA8888:
    case AX_FORMAT_ARGB8888:
        nBpp = 32;
        break;
    default:
        SAMPLE_ERR_LOG(" ERR eType : %d!",  eType);
        nBpp = 0;
        break;
    }

    return nStride * nH * nBpp / 8;
}

AX_S32 SampleIVPS_Init(AX_U32 u32GrpNum, AX_U32 u32StartGrp, AX_U32 width, AX_U32 height)
{
    AX_S32 axRet = 0;
    int index = 0;
    AX_IVPS_GRP_ATTR_T  stGrpAttr = {0};
    AX_IVPS_PIPELINE_ATTR_T  stPipelineAttr = {0};
    int ch = 0;
    AX_IVPS_POOL_ATTR_T PoolAttr = {0};
    IVPS_GRP ivpsGrpId = 0;

    /****************************IVPS Prepare*********************************/
    /*
     * 1. Create memory pool for IVPS
     */

    axRet = AX_IVPS_Init();
    if (0 != axRet) {
        SAMPLE_ERR_LOG("AX_IVPS_Init axRet:%#x\n", axRet);
        return -1;
    }

    ch = 0;
    stPipelineAttr.nOutChnNum = 1;
    stPipelineAttr.tFilter[ch][0].bEngage = AX_TRUE;
    stPipelineAttr.tFilter[ch][0].tFRC.fSrcFrameRate = 30;
    stPipelineAttr.tFilter[ch][0].tFRC.fDstFrameRate = 30;
    stPipelineAttr.tFilter[ch][0].nDstPicWidth = width;
    stPipelineAttr.tFilter[ch][0].nDstPicHeight = height;
    stPipelineAttr.tFilter[ch][0].nDstPicStride = VDEC_ALIGN_UP(width, 16);
    stPipelineAttr.tFilter[ch][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
    stPipelineAttr.tFilter[ch][0].eEngine = AX_IVPS_ENGINE_GDC;
    stPipelineAttr.tFilter[ch][0].tTdpCfg.eRotation = AX_IVPS_ROTATION_0;
    stPipelineAttr.tFilter[ch][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;

    ch++;
    stPipelineAttr.tFilter[ch][0].bEngage = AX_TRUE;
    stPipelineAttr.tFilter[ch][0].tFRC.fSrcFrameRate = 30;
    stPipelineAttr.tFilter[ch][0].tFRC.fDstFrameRate = 30;
    stPipelineAttr.tFilter[ch][0].nDstPicWidth = width;
    stPipelineAttr.tFilter[ch][0].nDstPicHeight = height;
    stPipelineAttr.tFilter[ch][0].nDstPicStride = VDEC_ALIGN_UP(width, 16);
    stPipelineAttr.tFilter[ch][0].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
    stPipelineAttr.tFilter[ch][0].eEngine = AX_IVPS_ENGINE_SCL;
    stPipelineAttr.tFilter[ch][0].tTdpCfg.eRotation = AX_IVPS_ROTATION_0;
    stPipelineAttr.tFilter[ch][0].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;

    stPipelineAttr.tFilter[ch][1].bEngage = AX_TRUE;
    stPipelineAttr.tFilter[ch][1].tFRC.fSrcFrameRate = 30;
    stPipelineAttr.tFilter[ch][1].tFRC.fDstFrameRate = 30;
    stPipelineAttr.tFilter[ch][1].nDstPicWidth = width;
    stPipelineAttr.tFilter[ch][1].nDstPicHeight = height;
    stPipelineAttr.tFilter[ch][1].nDstPicStride = VDEC_ALIGN_UP(width, 16);
    stPipelineAttr.tFilter[ch][1].eDstPicFormat = AX_FORMAT_YUV420_SEMIPLANAR;
    stPipelineAttr.tFilter[ch][1].eEngine = AX_IVPS_ENGINE_TDP;
    stPipelineAttr.tFilter[ch][1].tTdpCfg.eRotation = AX_IVPS_ROTATION_0;
    stPipelineAttr.tFilter[ch][1].tTdpCfg.bVoOsd = AX_FALSE;
    stPipelineAttr.tFilter[ch][1].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;

    stPipelineAttr.nOutFifoDepth[ch - 1] = 0;

    stGrpAttr.ePipeline = AX_IVPS_PIPELINE_DEFAULT;
    for(index = 0; index < u32GrpNum; index++) {
        ivpsGrpId = index + u32StartGrp;
        axRet = AX_IVPS_CreateGrp(ivpsGrpId, &stGrpAttr);
        if (0 != axRet) {
            SAMPLE_ERR_LOG("AX_IVPS_CreateGrp axRet:%#x\n", axRet);
            return -2;
        }
        axRet = AX_IVPS_SetPipelineAttr(ivpsGrpId, &stPipelineAttr);
        if (0 != axRet) {
            SAMPLE_ERR_LOG("AX_IVPS_SetPipelineAttr axRet:%#x\n", axRet);
            return -20;
        }

        PoolAttr.ePoolSrc = AX_POOL_SOURCE_PRIVATE;
        PoolAttr.nFrmBufNum = 12;

        axRet = AX_IVPS_SetGrpPoolAttr(ivpsGrpId, &PoolAttr);
        if (IVPS_SUCC != axRet)
        {
            SAMPLE_ERR_LOG("AX_IVPS_SetGrpPoolAttr(Grp: %d) failed, ret=0x%x.", ivpsGrpId, axRet);
            return -3;
        }

        axRet = AX_IVPS_SetChnPoolAttr(ivpsGrpId, 0, &PoolAttr);
        if (IVPS_SUCC != axRet)
        {
            SAMPLE_ERR_LOG("AX_IVPS_SetChnPoolAttr(Grp: %d) failed, ret=0x%x.", ivpsGrpId, axRet);
            return -3;
        }

        axRet = AX_IVPS_EnableChn(ivpsGrpId, 0);
        if (0 != axRet) {
            SAMPLE_ERR_LOG("AX_IVPS_EnableChn ch.%d, axRet:%#x\n", 0, axRet);
            return -3;
        }

#ifdef IVPS_EZOOM_TEST_EN
        /* min_nFifoDepth: tdp:4 other engine: 3 */
        axRet = AX_IVPS_EnableBackupFrame(ivpsGrpId, 4);
        if (IVPS_SUCC != axRet)
        {
            SAMPLE_ERR_LOG("AX_IVPS_EnableBackupFrame(Grp: %d) failed, ret=0x%x.", ivpsGrpId, axRet);
            return -3;
        }
#endif

        axRet = AX_IVPS_StartGrp(ivpsGrpId);
        if (0 != axRet) {
            SAMPLE_ERR_LOG("AX_IVPS_StartGrp axRet:%#x\n", axRet);
            return -3;
        }
    }

    gU32GrpNum = u32GrpNum;
    gU32StartGrp = u32StartGrp;

    return 0;
}

AX_S32 SampleIvpsExit(void)
{
    AX_S32 axRet = 0;
    int ch = 0;
    int index = 0;
    IVPS_GRP ivpsGrpId = 0;

    for(index = 0; index < gU32GrpNum; index++) {
        ch = 0;
        ivpsGrpId = index + gU32StartGrp;
        axRet = AX_IVPS_DisableChn(ivpsGrpId, ch);
        if (0 != axRet) {
            SAMPLE_ERR_LOG("AX_IVPS_DisableChn ch.%d, axRet:%#x\n", ch, axRet);
        }
#ifdef IVPS_EZOOM_TEST_EN
        axRet = AX_IVPS_DisableBackupFrame(ivpsGrpId);
        if (IVPS_SUCC != axRet)
        {
            SAMPLE_ERR_LOG("AX_IVPS_DisableBackupFrame(Grp: %d) failed, ret=0x%x.", ivpsGrpId, axRet);
            return -3;
        }
#endif

        axRet = AX_IVPS_StopGrp(ivpsGrpId);
        if (0 != axRet) {
            SAMPLE_ERR_LOG("AX_IVPS_StopGrp axRet:%#x\n", axRet);
        }
        axRet = AX_IVPS_DestoryGrp(ivpsGrpId);
        if (0 != axRet) {
            SAMPLE_ERR_LOG("AX_IVPS_DestoryGrp axRet:%#x\n", axRet);
        }
    }

    axRet = AX_IVPS_Deinit();
    if (0 != axRet) {
        SAMPLE_ERR_LOG("AX_IVPS_Deinit axRet:%#x\n", axRet);
    }

    return 0;
}
