/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_VIN_H_
#define _SAMPLE_VIN_H_

#include "common_vin.h"

typedef enum {
    SAMPLE_VIN_NONE  = -1,
    SAMPLE_VIN_SINGLE_DUMMY  = 0,
    SAMPLE_VIN_SINGLE_OS04A10 = 1,
    SAMPLE_VIN_DOUBLE_OS04A10 = 2,
    SAMPLE_VIN_SINGLE_SC450AI = 3,
    SAMPLE_VIN_DOUBLE_SC450AI = 4,
    SAMPLE_VIN_DOUBLE_OS04A10_AND_BT656 = 5,
    SAMPLE_VIN_SINGLE_S5KJN1SQ03 = 6,
    SAMPLE_VIN_SINGLE_OS04A10_DCG_HDR = 7,
    SAMPLE_VIN_SINGLE_OS04A10_DCG_VS_HDR = 8,
    SYS_CASE_SINGLE_DVP = 20,
    SYS_CASE_SINGLE_BT601 = 21,
    SYS_CASE_SINGLE_BT656= 22,
    SYS_CASE_SINGLE_BT1120 = 23,
    SYS_CASE_SINGLE_LVDS = 24,
    SAMPLE_VIN_BUTT
} SAMPLE_VIN_CASE_E;

typedef struct {
    SAMPLE_VIN_CASE_E eSysCase;
    COMMON_VIN_MODE_E eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode;
    SAMPLE_LOAD_RAW_NODE_E eLoadRawNode;
    AX_BOOL bAiispEnable;
    AX_S32 nDumpFrameNum;
} SAMPLE_VIN_PARAM_T;

#endif
