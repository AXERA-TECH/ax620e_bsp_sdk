/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_VENC_HAL_H_
#define _SAMPLE_VENC_HAL_H_

#include <signal.h>
#include "ax_sys_api.h"

AX_S32 SAMPLE_VencInit(AX_S32 chnNum, AX_S32 u32StartChn, AX_U16 width, AX_U16 height, AX_PAYLOAD_TYPE_E enType, AX_BOOL bSaveStrm);
AX_S32 SAMPLE_VencDeinit(void);

#endif /* _SAMPLE_IVPS_HAL_H_ */
