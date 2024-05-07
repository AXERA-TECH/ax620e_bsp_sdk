/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_VO_HAL_H_
#define _SAMPLE_VO_HAL_H_

#include "common_sys.h"
#include "ax_vo_api.h"

typedef struct axSAMPLE_VO_INIT_PARAM_S {
    AX_U16 nWidth;
    AX_U16 nHeight;
    AX_U32 voDev;
    AX_VO_INTF_TYPE_E enVoIntfType;
    AX_VO_INTF_SYNC_E enIntfSync;
} SAMPLE_VO_INIT_PARAM_S;

AX_S32 SAMPLE_VoInit(SAMPLE_VO_INIT_PARAM_S *pInitParam, AX_U16 nChnNum);
AX_VOID SAMPLE_VoDeInit(AX_VOID);
AX_VOID SAMPLE_VoPrintReso(AX_VOID);
AX_S32 SAMPLE_VoGetRes(AX_VO_INTF_SYNC_E enVoSync, AX_U32 *pWidth, AX_U32 *pHeight);

#endif /*_SAMPLE_VO_HAL_H_*/