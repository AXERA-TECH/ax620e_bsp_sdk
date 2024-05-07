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

#include "sc200ai.h"
#include "sc200ai_ae_ctrl.h"
#include "sc200ai_reg.h"
#include "sc200ai_settings.h"

static AX_SNS_COMMBUS_T gsc200aiBusInfo[AX_VIN_MAX_PIPE_NUM] = {0};

AX_U8 gSc200aiSlaveAddr[AX_VIN_MAX_PIPE_NUM] = {SC200AI_SLAVE_ADDR1, SC200AI_SLAVE_ADDR2};

AX_S32 sc200ai_set_bus_info(ISP_PIPE_ID nPipeId, AX_SNS_COMMBUS_T tSnsBusInfo)
{
    gsc200aiBusInfo[nPipeId].I2cDev = tSnsBusInfo.I2cDev;

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_get_bus_num(ISP_PIPE_ID nPipeId)
{
    return gsc200aiBusInfo[nPipeId].I2cDev;
}

AX_S32 sc200ai_set_slaveaddr(ISP_PIPE_ID nPipeId, AX_U8 nslaveaddr)
{
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    if (nslaveaddr == SC200AI_SLAVE_ADDR1 || nslaveaddr == SC200AI_SLAVE_ADDR2)
        gSc200aiSlaveAddr[nPipeId] = nslaveaddr;
    else
        gSc200aiSlaveAddr[nPipeId] = SC200AI_SLAVE_ADDR1;

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_i2c_init(ISP_PIPE_ID nPipeId)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    sns_obj->sns_i2c_obj.sns_i2c_fd = -1;
    sns_obj->sns_i2c_obj.slave_addr = gSc200aiSlaveAddr[nPipeId];
    sns_obj->sns_i2c_obj.address_byte = SC200AI_ADDR_BYTE;
    sns_obj->sns_i2c_obj.data_byte = SC200AI_DATA_BYTE;
    sns_obj->sns_i2c_obj.swap_byte = SC200AI_SWAP_BYTES;

    sns_obj->sns_i2c_obj.sns_i2c_bnum = sc200ai_get_bus_num(nPipeId);

    sns_obj->sns_i2c_obj.sns_i2c_fd = i2c_init(sns_obj->sns_i2c_obj.sns_i2c_bnum,
                                      sns_obj->sns_i2c_obj.slave_addr);

    SNS_DBG("pipe %d sc200ai i2c init finish, i2c bus %d \n", nPipeId, sns_obj->sns_i2c_obj.sns_i2c_bnum);

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_i2c_exit(ISP_PIPE_ID nPipeId)
{
    AX_S32 ret = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    ret = i2c_exit(sns_obj->sns_i2c_obj.sns_i2c_fd);

    return ret;
}

AX_S32 sc200ai_read_register(ISP_PIPE_ID nPipeId, AX_U32 nAddr, AX_U32 *pData)
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

AX_S32 sc200ai_reg_read(ISP_PIPE_ID nPipeId, AX_U32 addr)
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

AX_S32 sc200ai_write_register(ISP_PIPE_ID nPipeId, AX_U32 addr, AX_U32 data)
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


AX_S32 sc200ai_hw_reset(unsigned int gpio_num, unsigned int gpio_out_val)
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


AX_S32 sc200ai_reset(ISP_PIPE_ID nPipeId, AX_U32 nResetGpio)
{
    AX_S32 result = 0;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    result |= sc200ai_hw_reset(nResetGpio, 0);
    usleep(5);
    result |= sc200ai_hw_reset(nResetGpio, 1);
    usleep(5 * 1000);

    return result;
}

AX_S32 sc200ai_update_regidx_table(ISP_PIPE_ID nPipeId, AX_U8 nRegIdx, AX_U8 nRegValue)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    sns_obj->sztRegsInfo[0].sztData.sztI2cData[nRegIdx].nData = nRegValue;

    SNS_DBG("Idx = %d, reg addr = 0x%x, reg data = 0x%x\n",
        nRegIdx, sns_obj->sztRegsInfo[0].sztData.sztI2cData[nRegIdx].nRegAddr, nRegValue);

    return AX_SNS_SUCCESS;
}

#if 0
AX_U32 sc200ai_get_hts(ISP_PIPE_ID nPipeId)
{
    AX_U8 hts_l = 0;
    AX_U8 hts_h = 0;
    AX_U32 hts = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    hts_h = sc200ai_reg_read(nPipeId, SC200AI_HTS_LONG_H);
    hts_l = sc200ai_reg_read(nPipeId, SC200AI_HTS_LONG_L);

    hts = hts_h << 8 | hts_l;

    return hts;
}

AX_U32 sc200ai_set_hts(ISP_PIPE_ID nPipeId, AX_U32 hts)
{
    AX_U8 hts_l = 0;
    AX_U8 hts_h = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    hts_h = (hts >> 8) & 0xff;
    hts_l = hts & 0xff;

    sc200ai_write_register(nPipeId, SC200AI_HTS_LONG_H, hts_h);
    sc200ai_write_register(nPipeId, SC200AI_HTS_LONG_L, hts_l);

    return AX_SNS_SUCCESS;
}
#endif

AX_U32 sc200ai_get_vts(ISP_PIPE_ID nPipeId)
{
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_U32 vts = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_h = sc200ai_reg_read(nPipeId, SC200AI_VTS_LONG_H);
    vts_l = sc200ai_reg_read(nPipeId, SC200AI_VTS_LONG_L);

    vts = (vts_h & 0x7f) << 8 | vts_l;

    return vts;
}

AX_U32 sc200ai_set_vts(ISP_PIPE_ID nPipeId, AX_U32 vts)
{
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_S32 result = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_h = (vts >> 8) & 0x7f;
    vts_l = vts & 0xff;

    result |= sc200ai_update_regidx_table(nPipeId, SC200AI_VTS_LONG_H_IDX, vts_h);
    result |= sc200ai_update_regidx_table(nPipeId, SC200AI_VTS_LONG_L_IDX, vts_l);

    return result;
}

AX_U32 sc200ai_get_vts_s(ISP_PIPE_ID nPipeId)
{
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_U32 vts = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_h = sc200ai_reg_read(nPipeId, SC200AI_VTS_SHORT_H);
    vts_l = sc200ai_reg_read(nPipeId, SC200AI_VTS_SHORT_L);

    vts = (vts_h & 0x7f) << 8 | vts_l;

    return vts;
}

AX_U32 sc200ai_set_vts_s(ISP_PIPE_ID nPipeId, AX_U32 vts)
{
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_S32 result = 0;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    vts_h = (vts >> 8) & 0x7f;
    vts_l = vts & 0xff;

    result |= sc200ai_update_regidx_table(nPipeId, SC200AI_VTS_SHORT_H_IDX, vts_h);
    result |= sc200ai_update_regidx_table(nPipeId, SC200AI_VTS_SHORT_L_IDX, vts_l);

    return result;
}

AX_S32 sc200ai_get_vts_from_setting(ISP_PIPE_ID nPipeId, camera_i2c_reg_array *setting, AX_U32 reg_cnt, AX_U32 *vts)
{
    AX_U32 i = 0;
    AX_U8 vts_h = 0;
    AX_U8 vts_l = 0;
    AX_U8 mask = 0;

    for (i = 0; i < reg_cnt; i++) {
        if((setting + i)->addr == SC200AI_VTS_LONG_H) {
            vts_h = (setting + i)->value;
            mask |= 1;
        } else if((setting + i)->addr == SC200AI_VTS_LONG_L) {
            vts_l = (setting + i)->value;
            mask |= 1 << 1;
        }

        if(mask == 0x3) break;
    }

    //default value
    if((mask & 1) == 0) {
        vts_h = 0x4;
        mask |= 1;
    }
    if((mask & (1 << 1)) == 0) {
        vts_l = 0x65;
        mask |= 1 << 1;
    }

    if(mask != 0x3) {
        SNS_ERR("get setting vts fail, mask:0x%x\n", mask);
        return AX_SNS_ERR_NOT_MATCH;
    }

    *vts = vts_h << 8 | vts_l;

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_select_setting(ISP_PIPE_ID nPipeId, camera_i2c_reg_array **setting, AX_U32 *cnt)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    switch (sns_obj->eImgMode) {
    case e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS:
        *setting = SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS;
        *cnt = sizeof(SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS:
        *setting = SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS;
        *cnt = sizeof(SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1088_10BIT_SDR_30FPS:
        *setting = SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1088_10BIT_SDR_30FPS;
        *cnt = sizeof(SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1088_10BIT_SDR_30FPS) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1088_10BIT_HDR_30FPS:
        *setting = SC200AI_MIPI_24M_792MBPS_2LANE_1920x1088_10BIT_HDR_30FPS;
        *cnt = sizeof(SC200AI_MIPI_24M_792MBPS_2LANE_1920x1088_10BIT_HDR_30FPS) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_MASTER:
        *setting = SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_MASTER;
        *cnt = sizeof(SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_MASTER) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_MASTER:
        *setting = SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_MASTER;
        *cnt = sizeof(SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_MASTER) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_SLAVE:
        *setting = SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_SLAVE;
        *cnt = sizeof(SC200AI_MIPI_24M_371P25MBPS_2LANE_1920x1080_10BIT_SDR_30FPS_SYNC_SLAVE) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_SLAVE:
        *setting = SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_SLAVE;
        *cnt = sizeof(SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_HDR_30FPS_SYNC_SLAVE) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_742P5MBPS_1LANE_1920x1080_10BIT_SDR_30FPS:
        *setting = SC200AI_MIPI_24M_742P5MBPS_1LANE_1920x1080_10BIT_SDR_30FPS;
        *cnt = sizeof(SC200AI_MIPI_24M_742P5MBPS_1LANE_1920x1080_10BIT_SDR_30FPS) / sizeof(camera_i2c_reg_array);
        break;
    case e_SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_SDR_60FPS:
        *setting = SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_SDR_60FPS;
        *cnt = sizeof(SC200AI_MIPI_24M_792MBPS_2LANE_1920x1080_10BIT_SDR_60FPS) / sizeof(camera_i2c_reg_array);
        break;
    default:
        SNS_ERR("it's not supported. pipe=%d, setting mode=%d\n", nPipeId, sns_obj->eImgMode);
        return AX_SNS_ERR_NOT_SUPPORT;
    }

    SNS_INFO("pipe=%d, setting mode=%d\n", nPipeId, sns_obj->eImgMode);

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_write_settings(ISP_PIPE_ID nPipeId)
{
    AX_U32 i = 0;
    AX_S32 ret = 0;
    AX_U32 reg_cnt = 0;
    camera_i2c_reg_array *setting = AX_NULL;

    ret = sc200ai_select_setting(nPipeId, &setting, &reg_cnt);
    if(ret) {
        return ret;
    }

    for (i = 0; i < reg_cnt; i++) {
        sc200ai_write_register(nPipeId, (setting + i)->addr, ((setting + i)->value));
#ifdef SENSOR_DEBUG
        usleep(2 * 1000);
        AX_U8 val = sc200ai_reg_read(nPipeId, (default_setting + i)->addr);
        SNS_DBG(" addr: 0x%04x write:0x%02x read:0x%02x \r\n",
                (default_setting + i)->addr, (default_setting + i)->value, val);
#endif
    }

    return AX_SNS_SUCCESS;
}
