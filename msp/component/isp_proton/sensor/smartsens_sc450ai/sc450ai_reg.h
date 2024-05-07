/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __SC450AI_REG_H__
#define __SC450AI_REG_H__

#include "ax_base_type.h"


#define SC450AI_SLAVE_ADDR1      (0x30)    /**< i2c slave address of the SC450AI camera sensor sid0: 0 sid1: 0*/
#define SC450AI_SLAVE_ADDR2      (0x31)    /**< i2c slave address of the SC450AI camera sensor sid0: 1 sid1: 0*/
#define SC450AI_SLAVE_ADDR3      (0x32)    /**< i2c slave address of the SC450AI camera sensor sid0: 0 sid1: 1*/
#define SC450AI_SLAVE_ADDR4      (0x33)    /**< i2c slave address of the SC450AI camera sensor sid0: 1 sid1: 0*/
#define SC450AI_SENSOR_CHIP_ID  (0xbd2f)
#define SC450AI_ADDR_BYTE       (2)
#define SC450AI_DATA_BYTE       (1)
#define SC450AI_SWAP_BYTES      (1)
#define SC450AI_INCK_24M        (24)

/* Exposure control related registers */
#define     SC450AI_LONG_EXP_LINE_H     (0x3e00)  /* bit[3:0], long frame exposure in unit of rows */
#define     SC450AI_LONG_EXP_LINE_M     (0x3e01)  /* bit[7:0], long frame exposure in unit of rows */
#define     SC450AI_LONG_EXP_LINE_L     (0x3e02)  /* bit[7:4], long frame exposure in unit of rows */

#define     SC450AI_SHORT_EXP_LINE_H    (0x3e22)  /* bit[4:0], short frame exposure in unit of rows */
#define     SC450AI_SHORT_EXP_LINE_M    (0x3e04)  /* bit[7:0], short frame exposure in unit of rows */
#define     SC450AI_SHORT_EXP_LINE_L    (0x3e05)  /* bit[7:4], short frame exposure in unit of rows */

#define     SC450AI_LONG_AGAIN_H        (0x3e08)  /* bit[5:0], real gain[13:8] long frame */
#define     SC450AI_LONG_AGAIN_L        (0x3e09)  /* bit[7:0], real gain[7:0] long frame */
#define     SC450AI_LONG_DGAIN_H        (0x3e06)  /* bit[3:0], real gain[13:10] long frame */
#define     SC450AI_LONG_DGAIN_L        (0x3e07)  /* bit[7:0], real gain[9:2] long frame */

#define     SC450AI_SHORT_AGAIN_H       (0x3e58)  /* bit[5:0], real gain[13:8] short frame */
#define     SC450AI_SHORT_AGAIN_L       (0x3e59)  /* bit[7:0], real gain[7:0] short frame */
#define     SC450AI_SHORT_DGAIN_H       (0x3e56)  /* bit[3:0], real gain[13:10] short frame */
#define     SC450AI_SHORT_DGAIN_L       (0x3e57)  /* bit[7:0], real gain[9:2] short frame */

#define     SC450AI_VSHORT_AGAIN_H       (0x3e12)  /* bit[5:0], real gain[13:8] short frame */
#define     SC450AI_VSHORT_AGAIN_L       (0x3e13)  /* bit[7:0], real gain[7:0] short frame */
#define     SC450AI_VSHORT_DGAIN_H       (0x3e10)  /* bit[3:0], real gain[13:10] short frame */
#define     SC450AI_VSHORT_DGAIN_L       (0x3e11)  /* bit[7:0], real gain[9:2] short frame */

#define     SC450AI_VTS_L_H               (0x320E)  /* bit[6:0], vts[15:8] */
#define     SC450AI_VTS_L_L               (0x320F)  /* bit[7:0], vts[7:0] */
#define     SC450AI_VTS_S_H               (0x3E23)  /* bit[6:0], vts[15:8] */
#define     SC450AI_VTS_S_L               (0x3E24)  /* bit[7:0], vts[7:0] */


AX_S32 sc450ai_reset(ISP_PIPE_ID nPipeId, AX_U32 nResetGpio);
AX_S32 sc450ai_sensor_i2c_init(ISP_PIPE_ID nPipeId);
AX_S32 sc450ai_sensor_i2c_exit(ISP_PIPE_ID nPipeId);
AX_S32 sc450ai_read_register(ISP_PIPE_ID nPipeId, AX_U32 nAddr, AX_U32 *pData);
AX_S32 sc450ai_reg_read(ISP_PIPE_ID nPipeId, AX_U32 addr);
AX_S32 sc450ai_write_register(ISP_PIPE_ID nPipeId, AX_U32 addr, AX_U32 data);

AX_U32 sc450ai_get_vts(ISP_PIPE_ID nPipeId);
AX_U32 sc450ai_set_vts(ISP_PIPE_ID nPipeId, AX_U32 vts);
AX_U32 sc450ai_get_vts_s(ISP_PIPE_ID nPipeId);
AX_U32 sc450ai_set_vts_s(ISP_PIPE_ID nPipeId, AX_U32 vts_s);

AX_S32 sc450ai_get_vts_from_setting(ISP_PIPE_ID nPipeId, camera_i2c_reg_array *setting, AX_U32 reg_cnt, AX_U32 *vts);

AX_S32 sc450ai_select_setting(ISP_PIPE_ID nPipeId, camera_i2c_reg_array **setting, AX_U32 *cnt);
AX_S32 sc450ai_write_settings(ISP_PIPE_ID nPipeId);

AX_S32 sc450ai_set_bus_info(ISP_PIPE_ID nPipeId, AX_SNS_COMMBUS_T tSnsBusInfo);
AX_S32 sc450ai_get_bus_num(ISP_PIPE_ID nPipeId);
AX_S32 sc450ai_set_slaveaddr(ISP_PIPE_ID nPipeId, AX_U8 nslaveaddr);

#endif  //end __SC450AI_REG_H__
