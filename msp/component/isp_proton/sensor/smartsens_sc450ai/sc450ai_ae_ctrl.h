/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __SC450AI_AE_CTRL_H__
#define __SC450AI_AE_CTRL_H__

#include "ax_base_type.h"
#include "ax_sensor_struct.h"

#define SC450AI_MAX_VTS         (0x7FFF)
#define SC450AI_FRAME_RATE      (30)
#define SC450AI_MAX_RATIO       (32.0f)
#define SC450AI_MIN_RATIO       (1.0f)

#define SC450AI_MIN_AGAIN       (1.0f)
#define SC450AI_MAX_AGAIN       (60.523f)

#define SC450AI_MIN_DGAIN       (1.0f)
#define SC450AI_MAX_DGAIN       (15.875f)

#define SC450AI_SDR_EXP_LINE_MIN                                      (0.5f)
#define SC450AI_SDR_EXP_LINE_MAX(vts)                                 (2 * vts - 8)
#define SC450AI_SDR_INTEGRATION_TIME_STEP                             (0.5f)

#define SC450AI_HDR_2X_LONG_EXP_LINE_MIN                              (0.5f)
#define SC450AI_HDR_2X_LONG_EXP_LINE_MAX(vts, vts_s)                  (2 * (vts - vts_s) - 13)
#define SC450AI_HDR_2X_LONG_INTEGRATION_TIME_STEP                     (2.0f)

#define SC450AI_HDR_2X_SHORT_EXP_LINE_MIN                             (0.5f)
#define SC450AI_HDR_2X_SHORT_EXP_LINE_MAX(vts_s)                      (2 * vts_s - 11)
#define SC450AI_HDR_2X_SHORT_INTEGRATION_TIME_STEP                    (2.0f)

#define SC450AI_HDR_LINE_GAP(vts_s)                                   (vts_s)
#define SC450AI_HDR_LINE_STEP                                         (16)

typedef struct _SNSSC450AI_OBJ_T_ {
    AX_U32 vts;
    AX_U32 vts_s;
    AX_U32 setting_vts;
    AX_F32 setting_fps;
    AX_U32 vblank;      /* unit: line */
    AX_U32 linegap;     /* unit: line */
} SNSSC450AI_OBJ_T;

typedef struct _SC450AI_GAIN_TABLE_T_ {
    float gain;
    AX_U8 gain_in;
    AX_U8 gain_de;
} SC450AI_GAIN_TABLE_T;

typedef enum _AX_SNS_AE_REG_IDX_E_ {
    SC450AI_LONG_EXP_LINE_H_IDX = 0,
    SC450AI_LONG_EXP_LINE_M_IDX,
    SC450AI_LONG_EXP_LINE_L_IDX,
    SC450AI_SHORT_EXP_LINE_H_IDX,
    SC450AI_SHORT_EXP_LINE_M_IDX,
    SC450AI_SHORT_EXP_LINE_L_IDX,
    SC450AI_LONG_AGAIN_H_IDX,
    SC450AI_LONG_AGAIN_L_IDX,
    SC450AI_LONG_DGAIN_H_IDX,
    SC450AI_LONG_DGAIN_L_IDX,
    SC450AI_VSHORT_AGAIN_H_IDX,
    SC450AI_VSHORT_AGAIN_L_IDX,
    SC450AI_VSHORT_DGAIN_H_IDX,
    SC450AI_VSHORT_DGAIN_L_IDX,
    SC450AI_VTS_L_H_IDX,
    SC450AI_VTS_L_L_IDX,
    SC450AI_VTS_S_H_IDX,
    SC450AI_VTS_S_L_IDX,
} AX_SNS_AE_REG_IDX_E;

AX_S32 sc450ai_cfg_aec_param(ISP_PIPE_ID nPipeId);

AX_S32 sc450ai_get_sensor_gain_table(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_TABLE_T *params);
AX_S32 sc450ai_set_again(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptAGain);
AX_S32 sc450ai_set_dgain(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptDGain);
AX_S32 sc450ai_hcglcg_ctrl(ISP_PIPE_ID nPipeId, AX_U32 nSnsHcgLcg);

AX_S32 sc450ai_get_hw_exposure_params(ISP_PIPE_ID nPipeId, AX_SNS_EXP_CTRL_PARAM_T *ptAeCtrlParam);
AX_S32 sc450ai_get_integration_time_range(ISP_PIPE_ID nPipeId, AX_F32 fHdrRatio, AX_SNS_AE_INT_TIME_RANGE_T *ptIntTimeRange);
AX_S32 sc450ai_set_integration_time(ISP_PIPE_ID nPipeId, AX_SNS_AE_SHUTTER_CFG_T *ptIntTime);

AX_S32 sc450ai_set_slow_fps(ISP_PIPE_ID nPipeId, AX_F32 fFps);
AX_S32 sc450ai_get_fps(ISP_PIPE_ID nPipeId, AX_F32 *pFps);
AX_S32 sc450ai_set_fps(ISP_PIPE_ID nPipeId, AX_F32 fFps);
AX_S32 sc450ai_get_slow_shutter_param(ISP_PIPE_ID nPipeId, AX_SNS_AE_SLOW_SHUTTER_PARAM_T *ptSlowShutterParam);
AX_U32 sc450ai_sns_update_regidx_table(ISP_PIPE_ID nPipeId, AX_U8 nRegIdx, AX_U8 nRegValue);
AX_S32 sc450ai_ae_get_sensor_reg_info(ISP_PIPE_ID nPipeId, AX_SNS_REGS_CFG_TABLE_T *ptSnsRegsInfo);
AX_U32 sc450ai_sns_refresh_all_regs_from_tbl(ISP_PIPE_ID nPipeId);


#endif  //end __SC450AI_AE_CTRL_H__
