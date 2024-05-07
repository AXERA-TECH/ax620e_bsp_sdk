/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_VO_COMMON_H_
#define _SAMPLE_VO_COMMON_H_

#define SAMPLE_VO_LOSSY_YUV_LITE_WIDTH        128
#define SAMPLE_VO_LOSSY_YUV_LITE_HEIGHT       2
#define SAMPLE_VO_LOSSY_COMP_LEVEL_FACTOR     32

enum {
    SAMPLE_VO_LAYER_TEST = 1 << 0,
    SAMPLE_VO_LAYER_DISPLAY_TEST = 1 << 1,
    SAMPLE_VO_DISPLAY_MODE_QUERY_TEST = 1 << 2,
    SAMPLE_VO_PLAY_TEST = 1 << 3,
    SAMPLE_VO_CSC_TEST = 1 << 4,
};

AX_VOID SAMPLE_VO_SigInt(AX_S32 s32SigNo);
AX_VOID SAMPLE_VO_SigStop(AX_S32 s32SigNo);
AX_S32 SAMPLE_VO_CheckSig(AX_VOID);
AX_VOID SAMPLE_VO_Usage(AX_CHAR *name);
AX_S32 SAMPLE_VO_LAYER(SAMPLE_VO_LAYER_CONFIG_S *pstLayerConf);
AX_S32 SAMPLE_VO_LAYER_DISPLAY(SAMPLE_VO_CONFIG_S *pstVoConf);
AX_VOID SAMPLE_VO_DISPLAY_MODE_PRINT(AX_U32 u32DevId, AX_VO_DISPLAY_MODE_T *pstDisplayMode);
AX_S32 SAMPLE_VO_PLAY(SAMPLE_VO_CONFIG_S *pstVoConf);
AX_S32 SAMPLE_VO_CSC_PROCESS(void);


#endif