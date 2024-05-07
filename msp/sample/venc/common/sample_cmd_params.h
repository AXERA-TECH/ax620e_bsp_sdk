/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __SAMPLE_CMD_PARAMS_H__
#define __SAMPLE_CMD_PARAMS_H__

#include <stdio.h>

#include "common_venc.h"


#ifdef __cplusplus
extern "C" {
#endif /* End of #ifdef __cplusplus */
#define VENCMAX(a,b) ((a) > (b) ? (a) : (b))
#define VENCMAX3(a,b,c) VENCMAX(VENCMAX(a,b),c)
AX_S32 SampleCmdLineParse(AX_S32 argc, AX_CHAR **argv, SAMPLE_VENC_CMD_PARA_T *pCml);
AX_VOID SampleSetDefaultParams(SAMPLE_VENC_CMD_PARA_T *pstPara);

#ifdef __cplusplus
}
#endif /* End of #ifdef __cplusplus */

#endif
