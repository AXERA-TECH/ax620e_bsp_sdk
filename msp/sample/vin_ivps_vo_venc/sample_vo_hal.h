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

AX_S32 SAMPLE_VoInit(AX_U16 nWidth, AX_U16 nHeight);
AX_VOID SAMPLE_VoDeInit(AX_VOID);
AX_S32 SAMPLE_VoParsePubAttr(AX_CHAR *pStr, AX_S32 *pWidth, AX_S32 *pHeight);
AX_VOID SAMPLE_VoPrintReso(AX_VOID);

#endif /*_SAMPLE_VO_HAL_H_*/