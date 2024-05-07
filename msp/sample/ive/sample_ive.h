/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __SAMPLE_IVE_H__
#define __SAMPLE_IVE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

#include "sample_ive_common.h"

AX_VOID SAMPLE_IVE_DMA_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_DMA_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_DualPicCalc_TEST(AX_U32 u32Mode, AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_DualPicCalc_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_EdgeDetection_TEST(AX_U32 u32Mode, AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_EdgeDetection_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_CCL_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_CCL_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_ED_TEST(AX_U32 u32Mode, AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_ED_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Filter_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Filter_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Hist_TEST(AX_U32 u32Mode, AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Hist_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Integ_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Integ_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_MagAng_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc);

AX_VOID SAMPLE_IVE_MagAng_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Sobel_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Sobel_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_GMM2_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_GMM2_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Thresh_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Thresh_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_16To8Bit_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_16To8Bit_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_CropResize_TEST(AX_U32 u32Engine, AX_U32 u32Mode, AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_CropResize_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_CSC_TEST(AX_U32 u32Engine, AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc);

AX_VOID SAMPLE_IVE_CSC_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_CropResize2_TEST(AX_U32 u32Engine, AX_U32 u32Mode, AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_CropResize2_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Map_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Map_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Lbp_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Lbp_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_OrdStatFltBern_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_OrdStatFltBern_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Corner_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Corner_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_LkOpticalFlow_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_LkOpticalFlow_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Ncc_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc);

AX_VOID SAMPLE_IVE_Ncc_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_Sad_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_Sad_TEST_HandleSig(AX_VOID);

AX_VOID SAMPLE_IVE_LkOpticalFlowPyr_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList);

AX_VOID SAMPLE_IVE_LkOpticalFlowPyr_TEST_HandleSig(AX_VOID);

#endif