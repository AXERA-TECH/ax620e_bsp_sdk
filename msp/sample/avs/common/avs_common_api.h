/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __AVS_COMMON_API_H__
#define __AVS_COMMON_API_H__

#include "ax_base_type.h"
#include "avs_common_utils.h"
#include "ini_parser.h"

#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */

#define SAMPLE_AVS_PIPE_NUM_MAX 4

typedef struct _SAMPLE_AVS_BASE_PARA
{
    AX_S32 s32GroupId;
    AX_S32 s32PipeNum;
    AX_S8 *pInput[SAMPLE_AVS_PIPE_NUM_MAX];
    AX_S32 s32InputWidth;
    AX_S32 s32InputHeight;
    AX_S32 s32InputFrameSize;
    AX_S8 *pOutput;
    AX_S32 s32PanoWidth;
    AX_S32 s32PanoHeight;
    AX_S32 s32OutputWidth;
    AX_S32 s32OutputHeight;
    AX_S8 *pMesh[SAMPLE_AVS_PIPE_NUM_MAX];
    AX_S8 *pMask[SAMPLE_AVS_PIPE_NUM_MAX - 1];
    AX_S32 s32MaskWidth;
    AX_S32 s32MaskHeight;
    AX_S32 s32MaskX;
    AX_S32 s32MaskY;
    AX_S32 s32LoopNum;
    AX_POOL s32UserPoolId;
    AX_BOOL bSendThreadStart;
    AX_BOOL bGetThreadStart;
    AX_BOOL bDumpYUV;
    AX_BOOL bDynamicSeam;
    AX_S32 s32BlendMode;
    AX_BOOL bFrameSync;
    AX_S32 s32CalibrationMode;
    AX_F32 f32InputFOV[SAMPLE_AVS_PIPE_NUM_MAX];
    AX_F32 f32PanoFOV;
    AX_S8 *pCalibrationFile;
    AX_S32 s32PrjMode;
    AX_BOOL bInputCompress;
    AX_S32 s32InputComLevel;
    AX_BOOL bOutputCompress;
    AX_S32 s32OutputComLevel;
    INI_DICT *ini;
}SAMPLE_AVS_BASE_PARA_T;

AX_VOID AVSParameterDefault(SAMPLE_AVS_BASE_PARA_T* pAVSBaseParam);
AX_S32 AVSParameterGet(AX_S32 argc, AX_CHAR **argv, SAMPLE_AVS_BASE_PARA_T* pAVSBaseParam);
AX_VOID AVSParameterFree(SAMPLE_AVS_BASE_PARA_T* pAVSBaseParam);
AX_S32 SampleAVSUsage(SAMPLE_AVS_BASE_PARA_T* pAVSBaseParam);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif