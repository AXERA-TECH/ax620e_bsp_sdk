/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_IVPS_HAL_H_
#define _SAMPLE_IVPS_HAL_H_

#include <signal.h>
#include "ax_sys_api.h"
#include "ax_ivps_api.h"

AX_S32 SampleIVPS_Init(AX_U32 u32GrpNum, AX_U32 u32StartGrp, AX_U32 width, AX_U32 height);
AX_S32 SampleIvpsExit();

#endif /* _SAMPLE_IVPS_HAL_H_ */
