/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ax_base_type.h"
#include "ax_isp_common.h"

#include "i2c.h"
#include "isp_sensor_types.h"
#include "isp_sensor_internal.h"

#include "sc450ai_reg.h"
#include "sc450ai_settings.h"
#include "sc450ai_ae_ctrl.h"


extern SNS_STATE_OBJ *g_szsc450aiCtx[AX_VIN_MAX_PIPE_NUM];
#define SENSOR_GET_CTX(dev, pstCtx) (pstCtx = g_szsc450aiCtx[dev])

static AX_SNS_COMMBUS_T gsc450aiBusInfo[AX_VIN_MAX_PIPE_NUM] = { {{0}}, {{2}},};
AX_U8 gSc450aiSlaveAddr[AX_VIN_MAX_PIPE_NUM] = {0x30, 0x30};

AX_S32 sc450ai_set_bus_info(ISP_PIPE_ID nPipeId, AX_SNS_COMMBUS_T tSnsBusInfo)
{
    gsc450aiBusInfo[nPipeId].I2cDev = tSnsBusInfo.I2cDev;

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_get_bus_num(ISP_PIPE_ID nPipeId)
{
    return gsc450aiBusInfo[nPipeId].I2cDev;
}

AX_S32 sc450ai_set_slaveaddr(ISP_PIPE_ID nPipeId, AX_U8 nslaveaddr)
{
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    if (nslaveaddr == SC450AI_SLAVE_ADDR1 || nslaveaddr == SC450AI_SLAVE_ADDR2 ||
        nslaveaddr == SC450AI_SLAVE_ADDR3 || nslaveaddr == SC450AI_SLAVE_ADDR4)
        gSc450aiSlaveAddr[nPipeId] = nslaveaddr;
    else
        gSc450aiSlaveAddr[nPipeId] = SC450AI_SLAVE_ADDR1;

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_sensor_i2c_init(ISP_PIPE_ID nPipeId)
{
    AX_S32 ret = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_S32 snsId = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    sns_obj->sns_i2c_obj.sns_i2c_fd = -1;
    sns_obj->sns_i2c_obj.slave_addr = gSc450aiSlaveAddr[nPipeId];
    sns_obj->sns_i2c_obj.address_byte = SC450AI_ADDR_BYTE;
    sns_obj->sns_i2c_obj.data_byte = SC450AI_DATA_BYTE;
    sns_obj->sns_i2c_obj.swap_byte = SC450AI_SWAP_BYTES;

    sns_obj->sns_i2c_obj.sns_i2c_bnum = sc450ai_get_bus_num(nPipeId);

    sns_obj->sns_i2c_obj.sns_i2c_fd = i2c_init(sns_obj->sns_i2c_obj.sns_i2c_bnum,
                                      sns_obj->sns_i2c_obj.slave_addr);

    SNS_DBG("sc450ai i2c init finish, i2c bus %d \n", sns_obj->sns_i2c_obj.sns_i2c_bnum);

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_sensor_i2c_exit(ISP_PIPE_ID nPipeId)
{
    AX_S32 ret = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    ret = i2c_exit(sns_obj->sns_i2c_obj.sns_i2c_fd);

    return ret;
}

AX_S32 sc450ai_read_register(ISP_PIPE_ID nPipeId, AX_U32 nAddr, AX_U32 *pData)
{
    AX_U8 data;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_S32 nRet = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if (-1 == sns_obj->sns_i2c_obj.sns_i2c_fd)
        return AX_SNS_ERR_NOT_INIT;

    nRet = i2c_read(sns_obj->sns_i2c_obj.sns_i2c_fd,
             sns_obj->sns_i2c_obj.slave_addr,
             nAddr,
             sns_obj->sns_i2c_obj.address_byte,
             (AX_U8 *)(pData),
             sns_obj->sns_i2c_obj.data_byte,
             sns_obj->sns_i2c_obj.swap_byte);

    return nRet;
}

AX_S32 sc450ai_reg_read(ISP_PIPE_ID nPipeId, AX_U32 addr)
{
    AX_U8 data;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_S32 nRet = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if (-1 == sns_obj->sns_i2c_obj.sns_i2c_fd)
        return AX_SNS_ERR_NOT_INIT;

    i2c_read(sns_obj->sns_i2c_obj.sns_i2c_fd,
             sns_obj->sns_i2c_obj.slave_addr,
             addr,
             sns_obj->sns_i2c_obj.address_byte,
             (AX_U8 *)(&data),
             sns_obj->sns_i2c_obj.data_byte,
             sns_obj->sns_i2c_obj.swap_byte);

    return data;
}

AX_S32 sc450ai_write_register(ISP_PIPE_ID nPipeId, AX_U32 addr, AX_U32 data)
{
    AX_S32 nRet = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if (-1 == sns_obj->sns_i2c_obj.sns_i2c_fd)
        return AX_SNS_ERR_NOT_INIT;

    nRet = i2c_write(sns_obj->sns_i2c_obj.sns_i2c_fd, sns_obj->sns_i2c_obj.slave_addr, addr,
                     sns_obj->sns_i2c_obj.address_byte,
                     (AX_U8 *)(&data), sns_obj->sns_i2c_obj.data_byte, sns_obj->sns_i2c_obj.swap_byte);

    return nRet;
}


AX_S32 sc450ai_hw_reset(unsigned int gpio_num, unsigned int gpio_out_val)
{
    FILE *fp = AX_NULL;
    char file_name[50];
    char buf[10];

    sprintf(file_name, "/sys/class/gpio/gpio%d", gpio_num);
    if (0 != access(file_name, F_OK)) {
        sprintf(file_name, "/sys/class/gpio/export");
        fp = fopen(file_name, "w");
        if (fp == AX_NULL) {
            SNS_ERR("Cannot open %s.\n", file_name);
            return AX_SNS_ERR_ILLEGAL_PARAM;
        }
        fprintf(fp, "%d", gpio_num);
        fclose(fp);

        sprintf(file_name, "/sys/class/gpio/gpio%d/direction", gpio_num);
        fp = fopen(file_name, "w");
        if (fp == AX_NULL) {
            SNS_ERR("Cannot open %s.\n", file_name);
            return AX_SNS_ERR_ILLEGAL_PARAM;
        }
        fprintf(fp, "out");
        fclose(fp);
    }

    sprintf(file_name, "/sys/class/gpio/gpio%d/value", gpio_num);
    fp = fopen(file_name, "w");
    if (fp == AX_NULL) {
        SNS_ERR("Cannot open %s.\n", file_name);
        return AX_SNS_ERR_ILLEGAL_PARAM;
    }
    if (gpio_out_val) {
        strcpy(buf, "1");
    } else {
        strcpy(buf, "0");
    }
    fprintf(fp, "%s", buf);
    fclose(fp);

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_group_prepare(ISP_PIPE_ID nPipeId)
{
    AX_S32 result = 0;

    return result;
}


AX_S32 sc450ai_reset(ISP_PIPE_ID nPipeId, AX_U32 nResetGpio)
{
    AX_S32 result = 0;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    result |= sc450ai_hw_reset(nResetGpio, 0);
    usleep(5);
    result |= sc450ai_hw_reset(nResetGpio, 1);
    usleep(5 * 1000);

    return result;
}

AX_U32 sc450ai_get_hts(ISP_PIPE_ID nPipeId)
{
    AX_U8 hts_l = 0;
    AX_U8 hts_h = 0;
    AX_U32 hts = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    hts_h = sc450ai_reg_read(nPipeId, SC450AI_HTS_L_H);
    hts_l = sc450ai_reg_read(nPipeId, SC450AI_HTS_L_L);

    hts = hts_h << 8 | hts_l;

    return hts;
}

AX_U32 sc450ai_get_vs_hts(ISP_PIPE_ID nPipeId)
{
    AX_U8 frame_length_l = 0;
    AX_U8 frame_length_h = 0;
    AX_U16 frame_length = 0;
    AX_U32 hts = 0;
    AX_U32 fps = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    // one line time = 1 / (fps * frame_length)
    frame_length_h = sc450ai_reg_read(nPipeId, SC450AI_VTS_S_H);
    frame_length_l = sc450ai_reg_read(nPipeId, SC450AI_VTS_S_L);
    frame_length = (frame_length_h << 8) | frame_length_l;
    fps = (AX_U32)sns_obj->sns_mode_obj.fFrameRate;

    hts = 1000000 / (fps * frame_length);

    return hts;
}

AX_U32 sc450ai_set_hts(ISP_PIPE_ID nPipeId, AX_U32 hts)
{
    AX_U8 frame_length_l = 0;
    AX_U8 frame_length_h = 0;
    AX_U16 frame_length = 0;
    AX_U32 fps = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    // one line time = 1 / (fps * frame_length)
    fps = (AX_U32)sns_obj->sns_mode_obj.fFrameRate;
    frame_length = 1000000 / (fps * hts);

    frame_length_h = (frame_length >> 8) & 0xff;
    frame_length_l = frame_length & 0xff;
    sc450ai_write_register(nPipeId, SC450AI_VTS_L_H, frame_length_h);
    sc450ai_write_register(nPipeId, SC450AI_VTS_L_L, frame_length_l);

    return AX_SNS_SUCCESS;
}

AX_U32 sc450ai_set_vs_hts(ISP_PIPE_ID nPipeId, AX_U32 hts)
{
    AX_U8 frame_length_l = 0;
    AX_U8 frame_length_h = 0;
    AX_U16 frame_length = 0;
    AX_U32 fps = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    // one line time = 1 / (fps * frame_length)
    fps = (AX_U32)sns_obj->sns_mode_obj.fFrameRate;
    frame_length = 1000000 / (fps * hts);

    frame_length_h = (frame_length >> 8) & 0xff;
    frame_length_l = frame_length & 0xff;
    sc450ai_write_register(nPipeId, SC450AI_VTS_S_H, frame_length_h);
    sc450ai_write_register(nPipeId, SC450AI_VTS_S_L, frame_length_l);

    return AX_SNS_SUCCESS;
}

AX_U32 sc450ai_get_vts(ISP_PIPE_ID nPipeId)
{
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_U32 vts = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_h = sc450ai_reg_read(nPipeId, SC450AI_VTS_L_H);
    vts_l = sc450ai_reg_read(nPipeId, SC450AI_VTS_L_L);
    vts = (AX_U32)(((vts_h & 0xFF) << 8) | (AX_U32)(vts_l & 0xFF));

    return vts;
}

AX_U32 sc450ai_get_vts_s(ISP_PIPE_ID nPipeId)
{
    AX_U8 vts_s_h = 0;
    AX_U8 vts_s_l = 0;
    AX_U32 vts_s = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_s_h = sc450ai_reg_read(nPipeId, SC450AI_VTS_S_H);
    vts_s_l = sc450ai_reg_read(nPipeId, SC450AI_VTS_S_L);

    vts_s = vts_s_h << 8 | vts_s_l;

    return vts_s;
}

AX_U32 sc450ai_set_vts(ISP_PIPE_ID nPipeId, AX_U32 vts)
{
    AX_U8 vts_h;
    AX_U8 vts_l;
    AX_S32 result = 0;
    AX_U8 rb_rows_h;
    AX_U8 rb_rows_l;
    AX_U32 rb_rows = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    vts_l = vts & 0xFF;
    vts_h = (vts & 0xFF00) >> 8;

    result |= sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VTS_L_H_IDX, vts_h);
    result |= sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VTS_L_L_IDX, vts_l);

    return result;
}

AX_U32 sc450ai_set_vts_s(ISP_PIPE_ID nPipeId, AX_U32 vts_s)
{
    AX_U8 vts_s_h = 0;
    AX_U8 vts_s_l = 0;
    AX_S32 result = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_s_h = (vts_s & 0xFF00) >> 8;
    vts_s_l = vts_s & 0xFF;

    result |= sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VTS_S_H_IDX, vts_s_h);
    result |= sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VTS_S_L_IDX, vts_s_l);

    return result;
}

AX_U32 sc450ai_get_s_vts(ISP_PIPE_ID nPipeId)
{
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_U32 vts = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_h = sc450ai_reg_read(nPipeId, SC450AI_VTS_S_H);
    vts_l = sc450ai_reg_read(nPipeId, SC450AI_VTS_S_L);
    vts = (AX_U32)(((vts_h & 0xFF) << 8) | (AX_U32)(vts_l & 0xFF));

    return vts;
}

AX_U32 sc450ai_set_s_vts(ISP_PIPE_ID nPipeId, AX_U32 vts)
{
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_S32 result = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_h = (vts >> 8) & 0xff;
    vts_l = vts & 0xff;
    result |= sc450ai_write_register(nPipeId, SC450AI_VTS_S_H, vts_h);
    result |= sc450ai_write_register(nPipeId, SC450AI_VTS_S_L, vts_l);


    return result;
}

AX_F32 sc450ai_get_exp_offset(ISP_PIPE_ID nPipeId)
{
    AX_F32 offset = 0.0f;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    offset += (sc450ai_reg_read(nPipeId, 0x3301) & 0x3) * 2.0f;
    offset += sc450ai_reg_read(nPipeId, 0x3302);
    offset += (sc450ai_reg_read(nPipeId, 0x3303) & 0x1f);
    offset += sc450ai_reg_read(nPipeId, 0x3304);
    offset += ((sc450ai_reg_read(nPipeId, 0x3305) & 0xFF) << 8) |
              (sc450ai_reg_read(nPipeId, 0x3306) & 0xFF);
    offset += (sc450ai_reg_read(nPipeId, 0x3307) & 0x1f);
    offset += sc450ai_reg_read(nPipeId, 0x3308) * 2.0f;
    offset += sc450ai_reg_read(nPipeId, 0x330d);

    offset /= (AX_F32)sc450ai_get_hts(nPipeId);

    return offset;
}

AX_S32 sc450ai_get_vts_from_setting(ISP_PIPE_ID nPipeId, camera_i2c_reg_array *setting, AX_U32 reg_cnt, AX_U32 *vts)
{
    AX_U32 i = 0;
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_U8 mask = 0;

    for (i = 0; i < reg_cnt; i++) {
        if ((setting + i)->addr == SC450AI_VTS_L_H) {
            vts_h = (setting + i)->value;
            mask |= 1;
        } else if ((setting + i)->addr == SC450AI_VTS_L_L) {
            vts_l = (setting + i)->value;
            mask |= 1 << 1;
        }

        if (mask == 0x3) break;
    }

    if (mask != 0x3) {
        SNS_ERR("get setting vts fail, mask:0x%x\n", mask);
        return AX_SNS_ERR_NOT_MATCH;
    }

    *vts = vts_h << 8 | vts_l;

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_select_setting(ISP_PIPE_ID nPipeId, camera_i2c_reg_array **setting, AX_U32 *cnt)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    switch (sns_obj->eImgMode) {
    case e_SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_4LANE_24M_360Mbps:
        *setting = SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_4LANE_24M_360Mbps;
        *cnt = sizeof(SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_4LANE_24M_360Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_HDR_10bit_RGGB_30FPS_4LANE_24M_720Mbps:
        *setting = SC450AI_2688X1520_HDR_10bit_RGGB_30FPS_4LANE_24M_720Mbps;
        *cnt = sizeof(SC450AI_2688X1520_HDR_10bit_RGGB_30FPS_4LANE_24M_720Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_LINEAR_10bit_RGGB_25FPS_2LANE_24M_720Mbps:
        *setting = SC450AI_2688X1520_LINEAR_10bit_RGGB_25FPS_2LANE_24M_720Mbps;
        *cnt = sizeof(SC450AI_2688X1520_LINEAR_10bit_RGGB_25FPS_2LANE_24M_720Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_2LANE_24M_720Mbps:
        *setting = SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_2LANE_24M_720Mbps;
        *cnt = sizeof(SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_2LANE_24M_720Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_HDR_10bit_RGGB_25FPS_2LANE_24M_1120Mbps:
        *setting = SC450AI_2688X1520_HDR_10bit_RGGB_25FPS_2LANE_24M_1120Mbps;
        *cnt = sizeof(SC450AI_2688X1520_HDR_10bit_RGGB_25FPS_2LANE_24M_1120Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_LINEAR_10bit_RGGB_25FPS_4LANE_27M_360Mbps:
        *setting = SC450AI_2688X1520_LINEAR_10bit_RGGB_25FPS_4LANE_27M_360Mbps;
        *cnt = sizeof(SC450AI_2688X1520_LINEAR_10bit_RGGB_25FPS_4LANE_27M_360Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_4LANE_27M_360Mbps:
        *setting = SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_4LANE_27M_360Mbps;
        *cnt = sizeof(SC450AI_2688X1520_LINEAR_10bit_RGGB_30FPS_4LANE_27M_360Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_HDR_10bit_RGGB_25FPS_4LANE_27M_720Mbps:
        *setting = SC450AI_2688X1520_HDR_10bit_RGGB_25FPS_4LANE_27M_720Mbps;
        *cnt = sizeof(SC450AI_2688X1520_HDR_10bit_RGGB_25FPS_4LANE_27M_720Mbps) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC450AI_2688X1520_HDR_10bit_RGGB_30FPS_4LANE_27M_720Mbps:
        *setting = SC450AI_2688X1520_HDR_10bit_RGGB_30FPS_4LANE_27M_720Mbps;
        *cnt = sizeof(SC450AI_2688X1520_HDR_10bit_RGGB_30FPS_4LANE_27M_720Mbps) / sizeof(camera_i2c_reg_array);
        break;
    default:
        SNS_ERR("it's not supported. pipe=%d, setting mode=%d\n", nPipeId, sns_obj->eImgMode);
        return AX_SNS_ERR_NOT_SUPPORT;
    }

    SNS_INFO("pipe=%d, setting mode=%d\n", nPipeId, sns_obj->eImgMode);

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_write_settings(ISP_PIPE_ID nPipeId)
{
    AX_U32 i = 0;
    AX_S32 ret = 0;
    AX_U32 reg_cnt = 0;
    camera_i2c_reg_array *setting = AX_NULL;

    ret = sc450ai_select_setting(nPipeId, &setting, &reg_cnt);
    if (ret) {
        return ret;
    }

    for (i = 0; i < reg_cnt; i++) {
        sc450ai_write_register(nPipeId, (setting + i)->addr, ((setting + i)->value));
#ifdef SENSOR_DEBUG
        usleep(2 * 1000);
        AX_U8 val = sc450ai_reg_read(nPipeId, (default_setting + i)->addr);
        SNS_DBG(" addr: 0x%04x write:0x%02x read:0x%02x \r\n",
                (default_setting + i)->addr, (default_setting + i)->value, val);
#endif
    }

    return AX_SNS_SUCCESS;
}
