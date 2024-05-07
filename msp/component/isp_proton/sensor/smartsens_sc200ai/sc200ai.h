/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __SC200AI_H__
#define __SC200AI_H__

#include "ax_base_type.h"
#include "ax_sensor_struct.h"
#include "isp_sensor_internal.h"

extern SNS_STATE_OBJ *g_szsc200aiCtx[AX_VIN_MAX_PIPE_NUM];

#define SENSOR_GET_CTX(dev, pstCtx) (pstCtx = g_szsc200aiCtx[dev])
#define SENSOR_SET_CTX(dev, pstCtx) (g_szsc200aiCtx[dev] = pstCtx)
#define SENSOR_RESET_CTX(dev) (g_szsc200aiCtx[dev] = NULL)

AX_S32 sc200ai_get_chipid(ISP_PIPE_ID nPipeId, AX_S32 *pSnsId);
AX_S32 sc200ai_streaming_ctrl(ISP_PIPE_ID nPipeId, AX_U32 on);
AX_S32 sc200ai_get_mode(ISP_PIPE_ID nPipeId, AX_SNS_ATTR_T *pSnsMode);
AX_S32 sc200ai_sleep_wakeup(ISP_PIPE_ID nPipeId, AX_SNS_SLEEP_WAKEUP_E eSleepWakeup);

AX_S32 sc200ai_get_black_level(ISP_PIPE_ID nPipeId, AX_SNS_BLACK_LEVEL_T *ptBlackLevel);

#endif  //end __SC200AI_H__
