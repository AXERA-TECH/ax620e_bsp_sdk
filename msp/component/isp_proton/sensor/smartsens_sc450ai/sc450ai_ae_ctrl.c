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

#include "isp_sensor_types.h"
#include "isp_sensor_internal.h"

#include "sc450ai_reg.h"
#include "sc450ai_ae_ctrl.h"

extern SNS_STATE_OBJ *g_szsc450aiCtx[AX_VIN_MAX_PIPE_NUM];
#define SENSOR_GET_CTX(dev, pstCtx) (pstCtx = g_szsc450aiCtx[dev])

static SNSSC450AI_OBJ_T sns_sc450aiparams[AX_VIN_MAX_PIPE_NUM];
static AX_F32 nAgainTable[SENSOR_MAX_GAIN_STEP];
static AX_F32 nDgainTable[SENSOR_MAX_GAIN_STEP];
extern AX_U8 gSc450aiSlaveAddr[AX_VIN_MAX_PIPE_NUM];

static AX_S32 sc450ai_set_exp_limit(ISP_PIPE_ID nPipeId, AX_F32 fHdrRatio);

/*user config*/
static AX_F32 gFpsGear[] = {1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00,
                            11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 19.00, 20.00,
                            21.00, 22.00, 23.00, 24.00, 25.00, 26.00, 27.00, 28.00, 29.00, 30.00
                           };



static AX_SNS_DRV_DELAY_TABLE_T gsc450aiAeRegsTable[] = {
    /* regs index */          /* regs addr */                /*regs value*/        /*Delay Frame Num*/
    {SC450AI_LONG_EXP_LINE_H_IDX, SC450AI_LONG_EXP_LINE_H,        0,          0},
    {SC450AI_LONG_EXP_LINE_M_IDX, SC450AI_LONG_EXP_LINE_M,        0,          0},
    {SC450AI_LONG_EXP_LINE_L_IDX, SC450AI_LONG_EXP_LINE_L,        0,          0},
    {SC450AI_SHORT_EXP_LINE_H_IDX,SC450AI_SHORT_EXP_LINE_H,       0,          0},
    {SC450AI_SHORT_EXP_LINE_M_IDX,SC450AI_SHORT_EXP_LINE_M,       0,          0},
    {SC450AI_SHORT_EXP_LINE_L_IDX,SC450AI_SHORT_EXP_LINE_L,       0,          0},
    {SC450AI_LONG_AGAIN_H_IDX,    SC450AI_LONG_AGAIN_H,           0,          0},
    {SC450AI_LONG_AGAIN_L_IDX,    SC450AI_LONG_AGAIN_L,           0,          0},
    {SC450AI_LONG_DGAIN_H_IDX,    SC450AI_LONG_DGAIN_H,           0,          0},
    {SC450AI_LONG_DGAIN_L_IDX,    SC450AI_LONG_DGAIN_L,           0,          0},
    {SC450AI_VSHORT_AGAIN_H_IDX, SC450AI_VSHORT_AGAIN_H,         0,          0},
    {SC450AI_VSHORT_AGAIN_L_IDX, SC450AI_VSHORT_AGAIN_L,         0,          0},
    {SC450AI_VSHORT_DGAIN_H_IDX, SC450AI_VSHORT_DGAIN_H,         0,          0},
    {SC450AI_VSHORT_DGAIN_L_IDX, SC450AI_VSHORT_DGAIN_L,         0,          0},
    {SC450AI_VTS_L_H_IDX,        SC450AI_VTS_L_H,                0,          0},
    {SC450AI_VTS_L_L_IDX,        SC450AI_VTS_L_L,                0,          0},
    {SC450AI_VTS_S_H_IDX,        SC450AI_VTS_S_H,                0,          0},
    {SC450AI_VTS_S_L_IDX,        SC450AI_VTS_S_L,                0,          0},
};


const SC450AI_GAIN_TABLE_T sc450ai_again_table[] = {
    {1.000, 0x03, 0x40},
    {1.016, 0x03, 0x41},
    {1.031, 0x03, 0x42},
    {1.047, 0x03, 0x43},
    {1.063, 0x03, 0x44},
    {1.078, 0x03, 0x45},
    {1.094, 0x03, 0x46},
    {1.109, 0x03, 0x47},
    {1.125, 0x03, 0x48},
    {1.141, 0x03, 0x49},
    {1.156, 0x03, 0x4a},
    {1.172, 0x03, 0x4b},
    {1.188, 0x03, 0x4c},
    {1.203, 0x03, 0x4d},
    {1.219, 0x03, 0x4e},
    {1.234, 0x03, 0x4f},
    {1.250, 0x03, 0x50},
    {1.266, 0x03, 0x51},
    {1.281, 0x03, 0x52},
    {1.297, 0x03, 0x53},
    {1.313, 0x03, 0x54},
    {1.328, 0x03, 0x55},
    {1.344, 0x03, 0x56},
    {1.359, 0x03, 0x57},
    {1.375, 0x03, 0x58},
    {1.391, 0x03, 0x59},
    {1.406, 0x03, 0x5a},
    {1.422, 0x03, 0x5b},
    {1.438, 0x03, 0x5c},
    {1.453, 0x03, 0x5d},
    {1.469, 0x03, 0x5e},
    {1.484, 0x03, 0x5f},
    {1.500, 0x03, 0x60},
    {1.516, 0x03, 0x61},
    {1.531, 0x03, 0x62},
    {1.547, 0x03, 0x63},
    {1.563, 0x03, 0x64},
    {1.578, 0x03, 0x65},
    {1.594, 0x03, 0x66},
    {1.609, 0x03, 0x67},
    {1.625, 0x03, 0x68},
    {1.641, 0x03, 0x69},
    {1.656, 0x03, 0x6a},
    {1.672, 0x03, 0x6b},
    {1.688, 0x03, 0x6c},
    {1.703, 0x03, 0x6d},
    {1.719, 0x03, 0x6e},
    {1.734, 0x03, 0x6f},
    {1.750, 0x03, 0x70},
    {1.766, 0x03, 0x71},
    {1.781, 0x03, 0x72},
    {1.797, 0x03, 0x73},
    {1.813, 0x03, 0x74},
    {1.828, 0x03, 0x75},
    {1.844, 0x03, 0x76},
    {1.859, 0x03, 0x77},
    {1.875, 0x03, 0x78},
    {1.891, 0x03, 0x79},
    {1.906, 0x03, 0x7a},
    {1.922, 0x03, 0x7b},
    {1.938, 0x03, 0x7c},
    {1.953, 0x03, 0x7d},
    {1.969, 0x03, 0x7e},
    {1.984, 0x03, 0x7f},
    {2.000, 0x07, 0x40},
    {2.031, 0x07, 0x41},
    {2.063, 0x07, 0x42},
    {2.094, 0x07, 0x43},
    {2.125, 0x07, 0x44},
    {2.156, 0x07, 0x45},
    {2.188, 0x07, 0x46},
    {2.219, 0x07, 0x47},
    {2.250, 0x07, 0x48},
    {2.281, 0x07, 0x49},
    {2.313, 0x07, 0x4a},
    {2.344, 0x07, 0x4b},
    {2.375, 0x07, 0x4c},
    {2.406, 0x07, 0x4d},
    {2.438, 0x07, 0x4e},
    {2.469, 0x07, 0x4f},
    {2.500, 0x07, 0x50},
    {2.531, 0x07, 0x51},
    {2.563, 0x07, 0x52},
    {2.594, 0x07, 0x53},
    {2.625, 0x07, 0x54},
    {2.656, 0x07, 0x55},
    {2.688, 0x07, 0x56},
    {2.719, 0x07, 0x57},
    {2.750, 0x07, 0x58},
    {2.781, 0x07, 0x59},
    {2.813, 0x07, 0x5a},
    {2.844, 0x07, 0x5b},
    {2.875, 0x07, 0x5c},
    {2.906, 0x07, 0x5d},
    {2.938, 0x07, 0x5e},
    {2.969, 0x07, 0x5f},
    {3.000, 0x07, 0x60},
    {3.031, 0x07, 0x61},
    {3.063, 0x07, 0x62},
    {3.094, 0x07, 0x63},
    {3.125, 0x07, 0x64},
    {3.156, 0x07, 0x65},
    {3.188, 0x07, 0x66},
    {3.219, 0x07, 0x67},
    {3.250, 0x07, 0x68},
    {3.281, 0x07, 0x69},
    {3.313, 0x07, 0x6a},
    {3.344, 0x07, 0x6b},
    {3.375, 0x07, 0x6c},
    {3.406, 0x07, 0x6d},
    {3.438, 0x07, 0x6e},
    {3.469, 0x07, 0x6f},
    {3.500, 0x07, 0x70},
    {3.531, 0x07, 0x71},
    {3.563, 0x07, 0x72},
    {3.594, 0x07, 0x73},
    {3.625, 0x07, 0x74},
    {3.656, 0x07, 0x75},
    {3.688, 0x07, 0x76},
    {3.719, 0x07, 0x77},
    {3.750, 0x07, 0x78},
    {3.781, 0x07, 0x79},
    // {3.813, 0x23, 0x40}, //fae suggests to remove abnormal points
    // {3.872, 0x23, 0x41}, //fae suggests to remove abnormal points
    {3.932, 0x23, 0x42},
    {3.991, 0x23, 0x43},
    {4.051, 0x23, 0x44},
    {4.110, 0x23, 0x45},
    {4.170, 0x23, 0x46},
    {4.229, 0x23, 0x47},
    {4.289, 0x23, 0x48},
    {4.349, 0x23, 0x49},
    {4.408, 0x23, 0x4a},
    {4.468, 0x23, 0x4b},
    {4.527, 0x23, 0x4c},
    {4.587, 0x23, 0x4d},
    {4.646, 0x23, 0x4e},
    {4.706, 0x23, 0x4f},
    {4.766, 0x23, 0x50},
    {4.825, 0x23, 0x51},
    {4.885, 0x23, 0x52},
    {4.944, 0x23, 0x53},
    {5.004, 0x23, 0x54},
    {5.063, 0x23, 0x55},
    {5.123, 0x23, 0x56},
    {5.183, 0x23, 0x57},
    {5.242, 0x23, 0x58},
    {5.302, 0x23, 0x59},
    {5.361, 0x23, 0x5a},
    {5.421, 0x23, 0x5b},
    {5.480, 0x23, 0x5c},
    {5.540, 0x23, 0x5d},
    {5.600, 0x23, 0x5e},
    {5.659, 0x23, 0x5f},
    {5.719, 0x23, 0x60},
    {5.778, 0x23, 0x61},
    {5.838, 0x23, 0x62},
    {5.897, 0x23, 0x63},
    {5.957, 0x23, 0x64},
    {6.017, 0x23, 0x65},
    {6.076, 0x23, 0x66},
    {6.136, 0x23, 0x67},
    {6.195, 0x23, 0x68},
    {6.255, 0x23, 0x69},
    {6.314, 0x23, 0x6a},
    {6.374, 0x23, 0x6b},
    {6.434, 0x23, 0x6c},
    {6.493, 0x23, 0x6d},
    {6.553, 0x23, 0x6e},
    {6.612, 0x23, 0x6f},
    {6.672, 0x23, 0x70},
    {6.731, 0x23, 0x71},
    {6.791, 0x23, 0x72},
    {6.851, 0x23, 0x73},
    {6.910, 0x23, 0x74},
    {6.970, 0x23, 0x75},
    {7.029, 0x23, 0x76},
    {7.089, 0x23, 0x77},
    {7.148, 0x23, 0x78},
    {7.208, 0x23, 0x79},
    {7.268, 0x23, 0x7a},
    {7.327, 0x23, 0x7b},
    {7.387, 0x23, 0x7c},
    {7.446, 0x23, 0x7d},
    {7.506, 0x23, 0x7e},
    {7.565, 0x23, 0x7f},
    {7.625, 0x27, 0x40},
    {7.744, 0x27, 0x41},
    {7.863, 0x27, 0x42},
    {7.982, 0x27, 0x43},
    {8.102, 0x27, 0x44},
    {8.221, 0x27, 0x45},
    {8.340, 0x27, 0x46},
    {8.459, 0x27, 0x47},
    {8.578, 0x27, 0x48},
    {8.697, 0x27, 0x49},
    {8.816, 0x27, 0x4a},
    {8.936, 0x27, 0x4b},
    {9.055, 0x27, 0x4c},
    {9.174, 0x27, 0x4d},
    {9.293, 0x27, 0x4e},
    {9.412, 0x27, 0x4f},
    {9.531, 0x27, 0x50},
    {9.650, 0x27, 0x51},
    {9.770, 0x27, 0x52},
    {9.889, 0x27, 0x53},
    {10.008, 0x27, 0x54},
    {10.127, 0x27, 0x55},
    {10.246, 0x27, 0x56},
    {10.365, 0x27, 0x57},
    {10.484, 0x27, 0x58},
    {10.604, 0x27, 0x59},
    {10.723, 0x27, 0x5a},
    {10.842, 0x27, 0x5b},
    {10.961, 0x27, 0x5c},
    {11.080, 0x27, 0x5d},
    {11.199, 0x27, 0x5e},
    {11.318, 0x27, 0x5f},
    {11.438, 0x27, 0x60},
    {11.557, 0x27, 0x61},
    {11.676, 0x27, 0x62},
    {11.795, 0x27, 0x63},
    {11.914, 0x27, 0x64},
    {12.033, 0x27, 0x65},
    {12.152, 0x27, 0x66},
    {12.271, 0x27, 0x67},
    {12.391, 0x27, 0x68},
    {12.510, 0x27, 0x69},
    {12.629, 0x27, 0x6a},
    {12.748, 0x27, 0x6b},
    {12.867, 0x27, 0x6c},
    {12.986, 0x27, 0x6d},
    {13.105, 0x27, 0x6e},
    {13.225, 0x27, 0x6f},
    {13.344, 0x27, 0x70},
    {13.463, 0x27, 0x71},
    {13.582, 0x27, 0x72},
    {13.701, 0x27, 0x73},
    {13.820, 0x27, 0x74},
    {13.939, 0x27, 0x75},
    {14.059, 0x27, 0x76},
    {14.178, 0x27, 0x77},
    {14.297, 0x27, 0x78},
    {14.416, 0x27, 0x79},
    {14.535, 0x27, 0x7a},
    {14.654, 0x27, 0x7b},
    {14.773, 0x27, 0x7c},
    {14.893, 0x27, 0x7d},
    {15.012, 0x27, 0x7e},
    {15.131, 0x27, 0x7f},
    {15.250, 0x2f, 0x40},
    {15.488, 0x2f, 0x41},
    {15.727, 0x2f, 0x42},
    {15.965, 0x2f, 0x43},
    {16.203, 0x2f, 0x44},
    {16.441, 0x2f, 0x45},
    {16.680, 0x2f, 0x46},
    {16.918, 0x2f, 0x47},
    {17.156, 0x2f, 0x48},
    {17.395, 0x2f, 0x49},
    {17.633, 0x2f, 0x4a},
    {17.871, 0x2f, 0x4b},
    {18.109, 0x2f, 0x4c},
    {18.348, 0x2f, 0x4d},
    {18.586, 0x2f, 0x4e},
    {18.824, 0x2f, 0x4f},
    {19.063, 0x2f, 0x50},
    {19.301, 0x2f, 0x51},
    {19.539, 0x2f, 0x52},
    {19.777, 0x2f, 0x53},
    {20.016, 0x2f, 0x54},
    {20.254, 0x2f, 0x55},
    {20.492, 0x2f, 0x56},
    {20.730, 0x2f, 0x57},
    {20.969, 0x2f, 0x58},
    {21.207, 0x2f, 0x59},
    {21.445, 0x2f, 0x5a},
    {21.684, 0x2f, 0x5b},
    {21.922, 0x2f, 0x5c},
    {22.160, 0x2f, 0x5d},
    {22.398, 0x2f, 0x5e},
    {22.637, 0x2f, 0x5f},
    {22.875, 0x2f, 0x60},
    {23.113, 0x2f, 0x61},
    {23.352, 0x2f, 0x62},
    {23.590, 0x2f, 0x63},
    {23.828, 0x2f, 0x64},
    {24.066, 0x2f, 0x65},
    {24.305, 0x2f, 0x66},
    {24.543, 0x2f, 0x67},
    {24.781, 0x2f, 0x68},
    {25.020, 0x2f, 0x69},
    {25.258, 0x2f, 0x6a},
    {25.496, 0x2f, 0x6b},
    {25.734, 0x2f, 0x6c},
    {25.973, 0x2f, 0x6d},
    {26.211, 0x2f, 0x6e},
    {26.449, 0x2f, 0x6f},
    {26.688, 0x2f, 0x70},
    {26.926, 0x2f, 0x71},
    {27.164, 0x2f, 0x72},
    {27.402, 0x2f, 0x73},
    {27.641, 0x2f, 0x74},
    {27.879, 0x2f, 0x75},
    {28.117, 0x2f, 0x76},
    {28.355, 0x2f, 0x77},
    {28.594, 0x2f, 0x78},
    {28.832, 0x2f, 0x79},
    {29.070, 0x2f, 0x7a},
    {29.309, 0x2f, 0x7b},
    {29.547, 0x2f, 0x7c},
    {29.785, 0x2f, 0x7d},
    {30.023, 0x2f, 0x7e},
    {30.262, 0x2f, 0x7f},
    {30.500, 0x3f, 0x40},
    {30.977, 0x3f, 0x41},
    {31.453, 0x3f, 0x42},
    {31.930, 0x3f, 0x43},
    {32.406, 0x3f, 0x44},
    {32.883, 0x3f, 0x45},
    {33.359, 0x3f, 0x46},
    {33.836, 0x3f, 0x47},
    {34.313, 0x3f, 0x48},
    {34.789, 0x3f, 0x49},
    {35.266, 0x3f, 0x4a},
    {35.742, 0x3f, 0x4b},
    {36.219, 0x3f, 0x4c},
    {36.695, 0x3f, 0x4d},
    {37.172, 0x3f, 0x4e},
    {37.648, 0x3f, 0x4f},
    {38.125, 0x3f, 0x50},
    {38.602, 0x3f, 0x51},
    {39.078, 0x3f, 0x52},
    {39.555, 0x3f, 0x53},
    {40.031, 0x3f, 0x54},
    {40.508, 0x3f, 0x55},
    {40.984, 0x3f, 0x56},
    {41.461, 0x3f, 0x57},
    {41.938, 0x3f, 0x58},
    {42.414, 0x3f, 0x59},
    {42.891, 0x3f, 0x5a},
    {43.367, 0x3f, 0x5b},
    {43.844, 0x3f, 0x5c},
    {44.320, 0x3f, 0x5d},
    {44.797, 0x3f, 0x5e},
    {45.273, 0x3f, 0x5f},
    {45.750, 0x3f, 0x60},
    {46.227, 0x3f, 0x61},
    {46.703, 0x3f, 0x62},
    {47.180, 0x3f, 0x63},
    {47.656, 0x3f, 0x64},
    {48.133, 0x3f, 0x65},
    {48.609, 0x3f, 0x66},
    {49.086, 0x3f, 0x67},
    {49.563, 0x3f, 0x68},
    {50.039, 0x3f, 0x69},
    {50.516, 0x3f, 0x6a},
    {50.992, 0x3f, 0x6b},
    {51.469, 0x3f, 0x6c},
    {51.945, 0x3f, 0x6d},
    {52.422, 0x3f, 0x6e},
    {52.898, 0x3f, 0x6f},
    {53.375, 0x3f, 0x70},
    {53.852, 0x3f, 0x71},
    {54.328, 0x3f, 0x72},
    {54.805, 0x3f, 0x73},
    {55.281, 0x3f, 0x74},
    {55.758, 0x3f, 0x75},
    {56.234, 0x3f, 0x76},
    {56.711, 0x3f, 0x77},
    {57.188, 0x3f, 0x78},
    {57.664, 0x3f, 0x79},
    {58.141, 0x3f, 0x7a},
    {58.617, 0x3f, 0x7b},
    {59.094, 0x3f, 0x7c},
    {59.570, 0x3f, 0x7d},
    {60.047, 0x3f, 0x7e},
    {60.523, 0x3f, 0x7f},
};

const SC450AI_GAIN_TABLE_T sc450ai_dgain_table[] = {
    {1.000, 0x00, 0x80},
    {1.016, 0x00, 0x82},
    {1.031, 0x00, 0x84},
    {1.047, 0x00, 0x86},
    {1.063, 0x00, 0x88},
    {1.078, 0x00, 0x8A},
    {1.094, 0x00, 0x8C},
    {1.109, 0x00, 0x8E},
    {1.125, 0x00, 0x90},
    {1.141, 0x00, 0x92},
    {1.156, 0x00, 0x94},
    {1.172, 0x00, 0x96},
    {1.188, 0x00, 0x98},
    {1.203, 0x00, 0x9A},
    {1.219, 0x00, 0x9C},
    {1.234, 0x00, 0x9E},
    {1.250, 0x00, 0xA0},
    {1.266, 0x00, 0xA2},
    {1.281, 0x00, 0xA4},
    {1.297, 0x00, 0xA6},
    {1.313, 0x00, 0xA8},
    {1.328, 0x00, 0xAA},
    {1.344, 0x00, 0xAC},
    {1.359, 0x00, 0xAE},
    {1.375, 0x00, 0xB0},
    {1.391, 0x00, 0xB2},
    {1.406, 0x00, 0xB4},
    {1.422, 0x00, 0xB6},
    {1.438, 0x00, 0xB8},
    {1.453, 0x00, 0xBA},
    {1.469, 0x00, 0xBC},
    {1.484, 0x00, 0xBE},
    {1.500, 0x00, 0xC0},
    {1.516, 0x00, 0xC2},
    {1.531, 0x00, 0xC4},
    {1.547, 0x00, 0xC6},
    {1.563, 0x00, 0xC8},
    {1.578, 0x00, 0xCA},
    {1.594, 0x00, 0xCC},
    {1.609, 0x00, 0xCE},
    {1.625, 0x00, 0xD0},
    {1.641, 0x00, 0xD2},
    {1.656, 0x00, 0xD4},
    {1.672, 0x00, 0xD6},
    {1.688, 0x00, 0xD8},
    {1.703, 0x00, 0xDA},
    {1.719, 0x00, 0xDC},
    {1.734, 0x00, 0xDE},
    {1.750, 0x00, 0xE0},
    {1.766, 0x00, 0xE2},
    {1.781, 0x00, 0xE4},
    {1.797, 0x00, 0xE6},
    {1.813, 0x00, 0xE8},
    {1.828, 0x00, 0xEA},
    {1.844, 0x00, 0xEC},
    {1.859, 0x00, 0xEE},
    {1.875, 0x00, 0xF0},
    {1.891, 0x00, 0xF2},
    {1.906, 0x00, 0xF4},
    {1.922, 0x00, 0xF6},
    {1.938, 0x00, 0xF8},
    {1.953, 0x00, 0xFA},
    {1.969, 0x00, 0xFC},
    {1.984, 0x00, 0xFE},
    {2.000, 0x01, 0x80},
    {2.031, 0x01, 0x82},
    {2.063, 0x01, 0x84},
    {2.094, 0x01, 0x86},
    {2.125, 0x01, 0x88},
    {2.156, 0x01, 0x8A},
    {2.188, 0x01, 0x8C},
    {2.219, 0x01, 0x8E},
    {2.250, 0x01, 0x90},
    {2.281, 0x01, 0x92},
    {2.313, 0x01, 0x94},
    {2.344, 0x01, 0x96},
    {2.375, 0x01, 0x98},
    {2.406, 0x01, 0x9A},
    {2.438, 0x01, 0x9C},
    {2.469, 0x01, 0x9E},
    {2.500, 0x01, 0xA0},
    {2.531, 0x01, 0xA2},
    {2.563, 0x01, 0xA4},
    {2.594, 0x01, 0xA6},
    {2.625, 0x01, 0xA8},
    {2.656, 0x01, 0xAA},
    {2.688, 0x01, 0xAC},
    {2.719, 0x01, 0xAE},
    {2.750, 0x01, 0xB0},
    {2.781, 0x01, 0xB2},
    {2.813, 0x01, 0xB4},
    {2.844, 0x01, 0xB6},
    {2.875, 0x01, 0xB8},
    {2.906, 0x01, 0xBA},
    {2.938, 0x01, 0xBC},
    {2.969, 0x01, 0xBE},
    {3.000, 0x01, 0xC0},
    {3.031, 0x01, 0xC2},
    {3.063, 0x01, 0xC4},
    {3.094, 0x01, 0xC6},
    {3.125, 0x01, 0xC8},
    {3.156, 0x01, 0xCA},
    {3.188, 0x01, 0xCC},
    {3.219, 0x01, 0xCE},
    {3.250, 0x01, 0xD0},
    {3.281, 0x01, 0xD2},
    {3.313, 0x01, 0xD4},
    {3.344, 0x01, 0xD6},
    {3.375, 0x01, 0xD8},
    {3.406, 0x01, 0xDA},
    {3.438, 0x01, 0xDC},
    {3.469, 0x01, 0xDE},
    {3.500, 0x01, 0xE0},
    {3.531, 0x01, 0xE2},
    {3.563, 0x01, 0xE4},
    {3.594, 0x01, 0xE6},
    {3.625, 0x01, 0xE8},
    {3.656, 0x01, 0xEA},
    {3.688, 0x01, 0xEC},
    {3.719, 0x01, 0xEE},
    {3.750, 0x01, 0xF0},
    {3.781, 0x01, 0xF2},
    {3.813, 0x01, 0xF4},
    {3.844, 0x01, 0xF6},
    {3.875, 0x01, 0xF8},
    {3.906, 0x01, 0xFA},
    {3.938, 0x01, 0xFC},
    {3.969, 0x01, 0xFE},
    {4.000, 0x03, 0x80},
    {4.063, 0x03, 0x82},
    {4.125, 0x03, 0x84},
    {4.188, 0x03, 0x86},
    {4.250, 0x03, 0x88},
    {4.313, 0x03, 0x8A},
    {4.375, 0x03, 0x8C},
    {4.438, 0x03, 0x8E},
    {4.500, 0x03, 0x90},
    {4.563, 0x03, 0x92},
    {4.625, 0x03, 0x94},
    {4.688, 0x03, 0x96},
    {4.750, 0x03, 0x98},
    {4.813, 0x03, 0x9A},
    {4.875, 0x03, 0x9C},
    {4.938, 0x03, 0x9E},
    {5.000, 0x03, 0xA0},
    {5.063, 0x03, 0xA2},
    {5.125, 0x03, 0xA4},
    {5.188, 0x03, 0xA6},
    {5.250, 0x03, 0xA8},
    {5.313, 0x03, 0xAA},
    {5.375, 0x03, 0xAC},
    {5.438, 0x03, 0xAE},
    {5.500, 0x03, 0xB0},
    {5.563, 0x03, 0xB2},
    {5.625, 0x03, 0xB4},
    {5.688, 0x03, 0xB6},
    {5.750, 0x03, 0xB8},
    {5.813, 0x03, 0xBA},
    {5.875, 0x03, 0xBC},
    {5.938, 0x03, 0xBE},
    {6.000, 0x03, 0xC0},
    {6.063, 0x03, 0xC2},
    {6.125, 0x03, 0xC4},
    {6.188, 0x03, 0xC6},
    {6.250, 0x03, 0xC8},
    {6.313, 0x03, 0xCA},
    {6.375, 0x03, 0xCC},
    {6.438, 0x03, 0xCE},
    {6.500, 0x03, 0xD0},
    {6.563, 0x03, 0xD2},
    {6.625, 0x03, 0xD4},
    {6.688, 0x03, 0xD6},
    {6.750, 0x03, 0xD8},
    {6.813, 0x03, 0xDA},
    {6.875, 0x03, 0xDC},
    {6.938, 0x03, 0xDE},
    {7.000, 0x03, 0xE0},
    {7.063, 0x03, 0xE2},
    {7.125, 0x03, 0xE4},
    {7.188, 0x03, 0xE6},
    {7.250, 0x03, 0xE8},
    {7.313, 0x03, 0xEA},
    {7.375, 0x03, 0xEC},
    {7.438, 0x03, 0xEE},
    {7.500, 0x03, 0xF0},
    {7.563, 0x03, 0xF2},
    {7.625, 0x03, 0xF4},
    {7.688, 0x03, 0xF6},
    {7.750, 0x03, 0xF8},
    {7.813, 0x03, 0xFA},
    {7.875, 0x03, 0xFC},
    {7.938, 0x03, 0xFE},
    {8.000, 0x07, 0x80},
    {8.125, 0x07, 0x82},
    {8.250, 0x07, 0x84},
    {8.375, 0x07, 0x86},
    {8.500, 0x07, 0x88},
    {8.625, 0x07, 0x8A},
    {8.750, 0x07, 0x8C},
    {8.875, 0x07, 0x8E},
    {9.000, 0x07, 0x90},
    {9.125, 0x07, 0x92},
    {9.250, 0x07, 0x94},
    {9.375, 0x07, 0x96},
    {9.500, 0x07, 0x98},
    {9.625, 0x07, 0x9A},
    {9.750, 0x07, 0x9C},
    {9.875, 0x07, 0x9E},
    {10.000, 0x07, 0xA0},
    {10.125, 0x07, 0xA2},
    {10.250, 0x07, 0xA4},
    {10.375, 0x07, 0xA6},
    {10.500, 0x07, 0xA8},
    {10.625, 0x07, 0xAA},
    {10.750, 0x07, 0xAC},
    {10.875, 0x07, 0xAE},
    {11.000, 0x07, 0xB0},
    {11.125, 0x07, 0xB2},
    {11.250, 0x07, 0xB4},
    {11.375, 0x07, 0xB6},
    {11.500, 0x07, 0xB8},
    {11.625, 0x07, 0xBA},
    {11.750, 0x07, 0xBC},
    {11.875, 0x07, 0xBE},
    {12.000, 0x07, 0xC0},
    {12.125, 0x07, 0xC2},
    {12.250, 0x07, 0xC4},
    {12.375, 0x07, 0xC6},
    {12.500, 0x07, 0xC8},
    {12.625, 0x07, 0xCA},
    {12.750, 0x07, 0xCC},
    {12.875, 0x07, 0xCE},
    {13.000, 0x07, 0xD0},
    {13.125, 0x07, 0xD2},
    {13.250, 0x07, 0xD4},
    {13.375, 0x07, 0xD6},
    {13.500, 0x07, 0xD8},
    {13.625, 0x07, 0xDA},
    {13.750, 0x07, 0xDC},
    {13.875, 0x07, 0xDE},
    {14.000, 0x07, 0xE0},
    {14.125, 0x07, 0xE2},
    {14.250, 0x07, 0xE4},
    {14.375, 0x07, 0xE6},
    {14.500, 0x07, 0xE8},
    {14.625, 0x07, 0xEA},
    {14.750, 0x07, 0xEC},
    {14.875, 0x07, 0xEE},
    {15.000, 0x07, 0xF0},
    {15.125, 0x07, 0xF2},
    {15.250, 0x07, 0xF4},
    {15.375, 0x07, 0xF6},
    {15.500, 0x07, 0xF8},
    {15.625, 0x07, 0xFA},
    {15.750, 0x07, 0xFC},
    {15.875, 0x07, 0xFE},
};

static AX_S32 sc450ai_again2value(AX_F32 gain, AX_U8 *again_in, AX_U8 *again_de, AX_F32 *gain_value)
{
    AX_U32 i;
    AX_U32 count;
    AX_U32 ret_value = 0;

    if (!again_in || !again_de)
        return AX_SNS_ERR_NULL_PTR;

    count = sizeof(sc450ai_again_table) / sizeof(sc450ai_again_table[0]);

    for (i = 0; i < count; i++) {
        if (gain > sc450ai_again_table[i].gain) {
            continue;
        } else {
            *again_in = sc450ai_again_table[i].gain_in;
            *again_de = sc450ai_again_table[i].gain_de;
            *gain_value = sc450ai_again_table[i].gain;
            SNS_DBG("again=%f, again_in=0x%x, again_de=0x%x\n", gain, *again_in, *again_de);
            return AX_SNS_SUCCESS;
        }
    }

    return AX_SNS_ERR_NOT_MATCH;
}

static AX_S32 sc450ai_dgain2value(AX_F32 gain, AX_U8 *dgain_in, AX_U8 *dgain_de, AX_U8 *dgain_de2, AX_F32 *gain_value)
{
    AX_U32 i;
    AX_U32 count;
    AX_U32 ret_value = 0;

    if (!dgain_in || !dgain_de)
        return AX_SNS_ERR_NULL_PTR;

    count = sizeof(sc450ai_dgain_table) / sizeof(sc450ai_dgain_table[0]);

    for (i = 0; i < count; i++) {
        if (gain > sc450ai_dgain_table[i].gain) {
            continue;
        } else {
            *dgain_in = sc450ai_dgain_table[i].gain_in;
            *dgain_de = sc450ai_dgain_table[i].gain_de;
            *gain_value = sc450ai_dgain_table[i].gain;
            SNS_DBG("dgain=%f, dgain_in=0x%x, dgain_de=0x%x\n", gain, *dgain_in, *dgain_de);
            return AX_SNS_SUCCESS;
        }
    }

    return AX_SNS_ERR_NOT_MATCH;
}


static AX_S32 sc450ai_get_gain_table(AX_SNS_AE_GAIN_TABLE_T *params)
{
    AX_U32 i;
    AX_S32 ret = 0;
    if (!params)
        return AX_SNS_ERR_NULL_PTR;

    params->nAgainTableSize = sizeof(sc450ai_again_table) / sizeof(sc450ai_again_table[0]);
    params->nDgainTableSize = sizeof(sc450ai_dgain_table) / sizeof(sc450ai_dgain_table[0]);

    for (i = 0; i < params->nAgainTableSize ; i++) {
        nAgainTable[i] = sc450ai_again_table[i].gain;
        params->pAgainTable = nAgainTable;
    }

    for (i = 0; i < params->nDgainTableSize ; i++) {
        nDgainTable[i] = sc450ai_dgain_table[i].gain;
        params->pDgainTable = nDgainTable;
    }

    return ret;
}


/****************************************************************************
 * exposure control external function
 ****************************************************************************/
static AX_S32 sc450ai_set_exp_limit(ISP_PIPE_ID nPipeId, AX_F32 fHdrRatio)
{
    AX_U32 vts_s = 0;
    AX_F32 ratio = 1.0;
    SNS_STATE_OBJ *sns_obj = NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if (sns_obj->sns_mode_obj.eHDRMode == AX_SNS_LINEAR_MODE) {
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX] = SC450AI_SDR_EXP_LINE_MIN;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] = SC450AI_SDR_EXP_LINE_MAX(sns_sc450aiparams[nPipeId].vts) / 2.0f;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_LONG_FRAME_IDX] = SC450AI_SDR_INTEGRATION_TIME_STEP;
    } else if (sns_obj->sns_mode_obj.eHDRMode == AX_SNS_HDR_2X_MODE) {
        vts_s = (2 * sns_sc450aiparams[nPipeId].vts + 11 * fHdrRatio - 13) / (2 * (fHdrRatio + 1));
        SNS_DBG("hdr vts_s:%d, vts:%d, ratio:%f\n", vts_s, sns_sc450aiparams[nPipeId].vts ,fHdrRatio);

        sns_sc450aiparams[nPipeId].vts_s = vts_s;
        sc450ai_set_vts_s(nPipeId, sns_sc450aiparams[nPipeId].vts_s);

        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX] = SC450AI_HDR_2X_LONG_EXP_LINE_MIN;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX] = SC450AI_HDR_2X_SHORT_EXP_LINE_MIN;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] = SC450AI_HDR_2X_LONG_EXP_LINE_MAX(sns_sc450aiparams[nPipeId].vts, vts_s) / 2.0f;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX] = SC450AI_HDR_2X_SHORT_EXP_LINE_MAX(vts_s) / 2.0f;

        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_LONG_FRAME_IDX] = SC450AI_HDR_2X_LONG_INTEGRATION_TIME_STEP;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_MEDIUM_FRAME_IDX] = SC450AI_HDR_2X_SHORT_INTEGRATION_TIME_STEP;

        ratio = (float)sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] /
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX];
    }

    SNS_DBG("userRatio:%.2f, userVts:0x%x, userVts_s:0x%x, limitRatio:%.2f, limitExp:%.2f-%.2f-%.2f-%.2f\n",
            fHdrRatio, sns_sc450aiparams[nPipeId].vts, sns_sc450aiparams[nPipeId].vts_s, ratio,
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX]);

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_get_params_from_setting(ISP_PIPE_ID nPipeId)
{
    AX_S32 ret = 0;
    AX_U32 reg_cnt = 0;
    camera_i2c_reg_array *setting = AX_NULL;
    AX_U32 vts = 0;

    ret = sc450ai_select_setting(nPipeId, &setting, &reg_cnt);
    if (ret) {
        return ret;
    }

    ret = sc450ai_get_vts_from_setting(nPipeId, setting, reg_cnt, &vts);
    if (ret) {
        return ret;
    }

    sns_sc450aiparams[nPipeId].vts = vts;

    SNS_DBG("pipe:%d, get setting params vts:0x%x\n", nPipeId, sns_sc450aiparams[nPipeId].vts);

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_cfg_aec_param(ISP_PIPE_ID nPipeId)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    sc450ai_get_params_from_setting(nPipeId);
    sns_obj->sns_mode_obj.nVts = sns_sc450aiparams[nPipeId].vts;
    sns_sc450aiparams[nPipeId].setting_vts = sns_obj->sns_mode_obj.nVts;
    sns_sc450aiparams[nPipeId].setting_fps = sns_obj->sns_mode_obj.fFrameRate;

    sns_obj->ae_ctrl_param.fTimePerLine =
        (float)1 * SNS_1_SECOND_UNIT_US / (sns_obj->sns_mode_obj.nVts * sns_obj->sns_mode_obj.fFrameRate);

    /* sensor again  limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_LONG_FRAME_IDX] = SC450AI_MIN_AGAIN;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_LONG_FRAME_IDX] = SC450AI_MAX_AGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fAGainIncrement[HDR_LONG_FRAME_IDX] = (AX_F32)1 / 1024;

    /* sensor dgain  limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_LONG_FRAME_IDX] = SC450AI_MIN_DGAIN;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_LONG_FRAME_IDX] = SC450AI_MAX_DGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fDGainIncrement[HDR_LONG_FRAME_IDX] = (AX_F32)1 / 1024;

    /* sensor medium again  limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_MEDIUM_FRAME_IDX] = SC450AI_MIN_AGAIN;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_MEDIUM_FRAME_IDX] = SC450AI_MAX_AGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fAGainIncrement[HDR_MEDIUM_FRAME_IDX] = (AX_F32)1 / 1024;

    /* sensor medium dgain  limit*/
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_MEDIUM_FRAME_IDX] = SC450AI_MIN_DGAIN;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_MEDIUM_FRAME_IDX] = SC450AI_MAX_DGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fDGainIncrement[HDR_MEDIUM_FRAME_IDX] = (AX_F32)1 / 1024;

    sns_obj->ae_ctrl_param.sns_ae_limit.fMinRatio = SC450AI_MIN_RATIO;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxRatio = SC450AI_MAX_RATIO;
    sc450ai_set_exp_limit(nPipeId, SC450AI_MAX_RATIO);

    sns_obj->ae_ctrl_param.sns_ae_param.fCurRatio = SC450AI_MAX_RATIO;
    sns_obj->ae_ctrl_param.eSnsHcgLcgMode = AX_LCG_NOTSUPPORT_MODE;

    return AX_SNS_SUCCESS;
}


AX_S32 sc450ai_get_sensor_gain_table(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_TABLE_T *params)
{
    AX_S32 result = 0;
    SNS_CHECK_PTR_VALID(params);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    result = sc450ai_get_gain_table(params);
    return result;

    return AX_SNS_SUCCESS;
}


AX_S32 sc450ai_set_again(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptAGain)
{
    AX_U8 Gain_in;
    AX_U8 Gain_de;
    AX_S32 result = 0;
    AX_F32 gain_value = 0;
    AX_F32 nGainFromUser = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptAGain);

    /* long gain seting */
    nGainFromUser = ptAGain->fGain[HDR_LONG_FRAME_IDX];
    nGainFromUser = AXSNS_CLIP3(nGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_LONG_FRAME_IDX],
                                sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_LONG_FRAME_IDX]);

    result =  sc450ai_again2value(nGainFromUser, &Gain_in, &Gain_de, &gain_value);
    if (result) {
        SNS_ERR("new gain match failed \n");
        return result;
    } else {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_LONG_FRAME_IDX] = gain_value;
        result = sc450ai_sns_update_regidx_table(nPipeId, SC450AI_LONG_AGAIN_H_IDX, (Gain_in & 0xFF));
        result |= sc450ai_sns_update_regidx_table(nPipeId, SC450AI_LONG_AGAIN_L_IDX, (Gain_de & 0xFF));
        if (result != 0) {
            SNS_ERR("write hw failed %d \n", result);
            return result;
        }
    }

    /* short gain seting */
    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        nGainFromUser = ptAGain->fGain[HDR_MEDIUM_FRAME_IDX];
        nGainFromUser = AXSNS_CLIP3(nGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_MEDIUM_FRAME_IDX],
                                    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_MEDIUM_FRAME_IDX]);

        result =  sc450ai_again2value(nGainFromUser, &Gain_in, &Gain_de, &gain_value);
        if (result) {
            SNS_ERR("new gain match failed \n");
            return result;
        } else {
            sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_MEDIUM_FRAME_IDX] = gain_value;
            result = sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VSHORT_AGAIN_H_IDX, (Gain_in & 0xFF));
            result |= sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VSHORT_AGAIN_L_IDX, (Gain_de & 0xFF));
            if (result != 0) {
                SNS_ERR("write hw failed %d \n", result);
                return result;
            }
        }
    }

    SNS_DBG("again: long frame %f, short frame %f\n",
            ptAGain->fGain[HDR_LONG_FRAME_IDX],
            ptAGain->fGain[HDR_MEDIUM_FRAME_IDX]);

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_set_dgain(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptDGain)
{
    AX_U8 Gain_in;
    AX_U8 Gain_de;
    AX_U8 Gain_de2;
    AX_S32 result = 0;
    AX_F32 gain_value = 0;
    AX_F32 nGainFromUser = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptDGain);

    /* long frame digital gain seting */
    nGainFromUser = ptDGain->fGain[HDR_LONG_FRAME_IDX];
    nGainFromUser = AXSNS_CLIP3(nGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_LONG_FRAME_IDX],
                                sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_LONG_FRAME_IDX]);

    result = sc450ai_dgain2value(nGainFromUser, &Gain_in, &Gain_de, &Gain_de2, &gain_value);
    if (result) {
        SNS_ERR("new gain match failed \n");
        return result;
    } else {
        sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_LONG_FRAME_IDX] = gain_value;
        result = sc450ai_sns_update_regidx_table(nPipeId, SC450AI_LONG_DGAIN_H_IDX, Gain_in);
        result = sc450ai_sns_update_regidx_table(nPipeId, SC450AI_LONG_DGAIN_L_IDX, Gain_de);
        if (result != 0) {
            SNS_ERR("write hw failed %d \n", result);
            return result;
        }
        sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_LONG_FRAME_IDX] = gain_value;
    }

    /* short frame digital gain seting */
    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        nGainFromUser = ptDGain->fGain[HDR_MEDIUM_FRAME_IDX];
        nGainFromUser = AXSNS_CLIP3(nGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_MEDIUM_FRAME_IDX],
                                    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_MEDIUM_FRAME_IDX]);

        result = sc450ai_dgain2value(nGainFromUser, &Gain_in, &Gain_de, &Gain_de2, &gain_value);
        if (result) {
            SNS_ERR("new gain match failed \n");
            return result;
        } else {
            sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_MEDIUM_FRAME_IDX] = gain_value;
            result = sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VSHORT_DGAIN_H_IDX, Gain_in);
            result = sc450ai_sns_update_regidx_table(nPipeId, SC450AI_VSHORT_DGAIN_L_IDX, Gain_de);
            if (result != 0) {
                SNS_ERR("write hw failed %d \n", result);
                return result;
            }
            sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_MEDIUM_FRAME_IDX] = gain_value;
        }

    }

    SNS_DBG("dgain: long frame %f, short frame %f\n",
            ptDGain->fGain[HDR_LONG_FRAME_IDX],
            ptDGain->fGain[HDR_MEDIUM_FRAME_IDX]);

    return AX_SNS_SUCCESS;
}

/* Calculate the max int time according to the exposure ratio */
AX_S32 sc450ai_get_integration_time_range(ISP_PIPE_ID nPipeId, AX_F32 fHdrRatio,
        AX_SNS_AE_INT_TIME_RANGE_T *ptIntTimeRange)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_F32 ratio = 0.0f;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptIntTimeRange);

    if (fabs(fHdrRatio) < EPS) {
        SNS_ERR("hdr ratio is error \n");
        return AX_SNS_ERR_ILLEGAL_PARAM;
    }

    if (AX_SNS_LINEAR_MODE == sns_obj->sns_mode_obj.eHDRMode) {
        ptIntTimeRange->fMaxIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX];
        ptIntTimeRange->fMinIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX];
    } else if (AX_SNS_HDR_2X_MODE == sns_obj->sns_mode_obj.eHDRMode) {
        ratio = fHdrRatio;
        ratio = AXSNS_CLIP3(ratio, sns_obj->ae_ctrl_param.sns_ae_limit.fMinRatio, sns_obj->ae_ctrl_param.sns_ae_limit.fMaxRatio);
        sns_obj->ae_ctrl_param.sns_ae_param.fCurRatio = ratio;
        if (fabs(ratio) <= EPS) {
            SNS_ERR("hdr ratio is error \n");
        }

        sc450ai_set_exp_limit(nPipeId, ratio);

        ptIntTimeRange->fMaxIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX];
        ptIntTimeRange->fMinIntegrationTime[HDR_LONG_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX];
        ptIntTimeRange->fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX];
        ptIntTimeRange->fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX];
    } else {
        // do nothing
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_set_integration_time(ISP_PIPE_ID nPipeId, AX_SNS_AE_SHUTTER_CFG_T *ptIntTime)
{
    AX_U8 ex_h;
    AX_U8 ex_l;
    AX_U32 ex_ival = 0;
    AX_S32 result = 0;
    AX_F32 ratio = 1.0f;
    AX_F32 fExpLineFromUser = 0;
    AX_U32 LineGap = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptIntTime);

    SNS_DBG("Exptime:%f-%f-%f-%f, Hdrratio:%f-%f-%f-%f\n",
            ptIntTime->fIntTime[0], ptIntTime->fIntTime[1], ptIntTime->fIntTime[2], ptIntTime->fIntTime[3],
            ptIntTime->fHdrRatio[0], ptIntTime->fHdrRatio[1], ptIntTime->fHdrRatio[2], ptIntTime->fHdrRatio[3]);

    fExpLineFromUser = ptIntTime->fIntTime[HDR_LONG_FRAME_IDX];

    fExpLineFromUser = AXSNS_CLIP3(fExpLineFromUser,
                                       sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX],
                                       sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX]);

    ex_ival = fExpLineFromUser * 2;
    ex_l = REG_LOW_8BITS(ex_ival);
    ex_h = REG_HIGH_8BITS(ex_ival);

    sc450ai_sns_update_regidx_table(nPipeId, SC450AI_LONG_EXP_LINE_H_IDX, (ex_h & 0xf0) >> 4);
    sc450ai_sns_update_regidx_table(nPipeId, SC450AI_LONG_EXP_LINE_M_IDX, ((ex_h & 0xf) << 4) | ((ex_l & 0xf0) >> 4));
    sc450ai_sns_update_regidx_table(nPipeId, SC450AI_LONG_EXP_LINE_L_IDX, ((ex_l & 0xf) << 4));

    sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX] = ex_ival / 2.0f;

    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        fExpLineFromUser = ptIntTime->fIntTime[HDR_MEDIUM_FRAME_IDX];

        fExpLineFromUser = AXSNS_CLIP3(fExpLineFromUser,
                                        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX],
                                        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX]);

        ex_ival = fExpLineFromUser * 2;

        //LineGap < Height
        LineGap = sc450ai_get_vts_s(nPipeId) / 2;
        if(LineGap > sns_obj->sns_mode_obj.nHeight) {
            ex_ival = sns_obj->sns_mode_obj.nHeight - 1;
        }

        ex_l = REG_LOW_8BITS(ex_ival);
        ex_h = REG_HIGH_8BITS(ex_ival);

        sc450ai_sns_update_regidx_table(nPipeId, SC450AI_SHORT_EXP_LINE_H_IDX, (ex_h & 0xf0) >> 4);
        sc450ai_sns_update_regidx_table(nPipeId, SC450AI_SHORT_EXP_LINE_M_IDX, ((ex_h & 0xf) << 4) | ((ex_l & 0xf0) >> 4));
        sc450ai_sns_update_regidx_table(nPipeId, SC450AI_SHORT_EXP_LINE_L_IDX, ((ex_l & 0xf) << 4));

        sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX] = ex_ival / 2.0f;
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_get_hw_exposure_params(ISP_PIPE_ID nPipeId, AX_SNS_EXP_CTRL_PARAM_T *ptAeCtrlParam)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(ptAeCtrlParam);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    memcpy(ptAeCtrlParam, &sns_obj->ae_ctrl_param, sizeof(AX_SNS_EXP_CTRL_PARAM_T));
    memcpy(&ptAeCtrlParam->sns_dev_attr, &sns_obj->sns_attr_param, sizeof(AX_SNS_ATTR_T));

    return AX_SNS_SUCCESS;
}

AX_U32 sc450ai_sns_update_regidx_table(ISP_PIPE_ID nPipeId, AX_U8 nRegIdx, AX_U8 nRegValue)
{
    AX_S32 i = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    sns_obj->sztRegsInfo[0].sztData.sztI2cData[nRegIdx].nData = nRegValue;

    SNS_DBG("Idx = %d, reg addr 0x%x, reg data 0x%x\n",
        nRegIdx, sns_obj->sztRegsInfo[0].sztData.sztI2cData[nRegIdx].nRegAddr, nRegValue);

    return AX_SNS_SUCCESS;
}

AX_U32 sc450ai_sns_refresh_all_regs_from_tbl(ISP_PIPE_ID nPipeId)
{
    AX_S32 i = 0;
    AX_U32 nNum = 0;
    AX_U32  nRegValue;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);

    nNum = sizeof(gsc450aiAeRegsTable) / sizeof(gsc450aiAeRegsTable[0]);

    for (i = 0; i < nNum; i++) {
        nRegValue = sc450ai_reg_read(nPipeId, gsc450aiAeRegsTable[i].nRegAddr);
        sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr = gsc450aiAeRegsTable[i].nRegAddr;
        sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData = nRegValue;

        SNS_DBG(" nRegAddr 0x%x, nRegValue 0x%x\n", sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData);
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_sns_update_init_exposure_reg(ISP_PIPE_ID nPipeId)
{
    int i = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    for (i = 0; i < sns_obj->sztRegsInfo[0].nRegNum; i++) {
        sc450ai_write_register(nPipeId, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData);
        SNS_DBG("Idx = %d, reg addr 0x%x, reg data 0x%x\n",
            i, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData);
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_ae_get_sensor_reg_info(ISP_PIPE_ID nPipeId, AX_SNS_REGS_CFG_TABLE_T *ptSnsRegsInfo)
{
    AX_S32 i = 0;
    AX_S32 nRet = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_BOOL bUpdateReg = AX_FALSE;

    SNS_CHECK_PTR_VALID(ptSnsRegsInfo);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if ((AX_FALSE == sns_obj->bSyncInit) || (AX_FALSE == ptSnsRegsInfo->bConfig)) {
        /* sync config */
        SNS_DBG(" bSyncInit %d, bConfig %d\n", sns_obj->bSyncInit, ptSnsRegsInfo->bConfig);
        sns_obj->sztRegsInfo[0].eSnsType = ISP_SNS_CONNECT_I2C_TYPE;
        sns_obj->sztRegsInfo[0].tComBus.I2cDev = sc450ai_get_bus_num(nPipeId);
        sns_obj->sztRegsInfo[0].nRegNum = sizeof(gsc450aiAeRegsTable) / sizeof(gsc450aiAeRegsTable[0]);
        sns_obj->sztRegsInfo[0].nCfg2ValidDelayMax = 2;

        for (i = 0; i < sns_obj->sztRegsInfo[0].nRegNum; i++) {
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].bUpdate = AX_TRUE;
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nDevAddr = gSc450aiSlaveAddr[nPipeId];
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nAddrByteNum = SC450AI_ADDR_BYTE;
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nDataByteNum = SC450AI_DATA_BYTE;
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nDelayFrmNum = gsc450aiAeRegsTable[i].nDelayFrmNum;
            if (IS_LINEAR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
                sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nIntPos = AX_SNS_L_FSOF;
            } else {
                sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nIntPos = AX_SNS_S_FSOF;
            }
            SNS_DBG("pipe %d, [%2d] nRegAddr 0x%x, nRegValue 0x%x\n", nPipeId, i,
                    gsc450aiAeRegsTable[i].nRegAddr, gsc450aiAeRegsTable[i].nRegValue);
        }

        bUpdateReg = AX_TRUE;
        sns_obj->bSyncInit = AX_TRUE;
        sc450ai_sns_update_init_exposure_reg(nPipeId);
    } else {
        for (i = 0; i < sns_obj->sztRegsInfo[0].nRegNum; i++) {
            if (sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData == sns_obj->sztRegsInfo[1].sztData.sztI2cData[i].nData) {
                sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].bUpdate = AX_FALSE;
            } else {
                sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].bUpdate = AX_TRUE;
                bUpdateReg = AX_TRUE;
                SNS_DBG("pipe %d, [%2d] nRegAddr 0x%x, nRegValue 0x%x\n", nPipeId, i,
                        sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData);
            }
        }
    }

    if (AX_TRUE == bUpdateReg) {
        sns_obj->sztRegsInfo[0].bConfig = AX_FALSE;
    } else {
        sns_obj->sztRegsInfo[0].bConfig = AX_TRUE;
    }

    memcpy(ptSnsRegsInfo, &sns_obj->sztRegsInfo[0], sizeof(AX_SNS_REGS_CFG_TABLE_T));
    /* Save the current register table */
    memcpy(&sns_obj->sztRegsInfo[1], &sns_obj->sztRegsInfo[0], sizeof(AX_SNS_REGS_CFG_TABLE_T));

    return nRet;
}

AX_S32 sc450ai_get_slow_shutter_param(ISP_PIPE_ID nPipeId, AX_SNS_AE_SLOW_SHUTTER_PARAM_T *ptSlowShutterParam)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_S32 framerate = SNS_MAX_FRAME_RATE;
    AX_U32 nfps = 0;
    AX_U32 nVts = 0;
    AX_U32 se = 0;

    SNS_CHECK_PTR_VALID(ptSlowShutterParam);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    framerate = sns_obj->sns_mode_obj.fFrameRate;
    if (framerate > SNS_MAX_FRAME_RATE) {
        SNS_ERR(" framerate out of range %d \n", framerate);
        return AX_SNS_ERR_ILLEGAL_PARAM;
    }

    if (sns_obj->ae_ctrl_param.fTimePerLine == 0) {
        SNS_ERR("line_period is zero : %f\n", sns_obj->ae_ctrl_param.fTimePerLine);
        return AX_SNS_ERR_ILLEGAL_PARAM;
    }

    ptSlowShutterParam->nGroupNum = AXSNS_MIN((sizeof(gFpsGear) / sizeof(AX_F32)), framerate);
    //ax_sns_quick_sort_float(gFpsGear, ptSlowShutterParam->nGroupNum);
    ptSlowShutterParam->fMinFps = AXSNS_MAX(gFpsGear[0],
                                            (1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * SC450AI_MAX_VTS)));

    for (nfps = 0 ; nfps < ptSlowShutterParam->nGroupNum; nfps++) {
        nVts = 1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * gFpsGear[nfps]);
        if ((AX_S32)gFpsGear[nfps] >= framerate) {
            nVts = sns_obj->sns_mode_obj.nVts;
        }
        if (nVts > SC450AI_MAX_VTS) {
            nVts = SC450AI_MAX_VTS;
            SNS_WRN("Beyond minmum fps  %f\n", ptSlowShutterParam->fMinFps);
        }

        if (IS_LINEAR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
            ptSlowShutterParam->tSlowShutterTbl[nfps].fMaxIntTime = SC450AI_SDR_EXP_LINE_MAX(nVts)/2.0f;
        } else if (IS_2DOL_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
            ptSlowShutterParam->tSlowShutterTbl[nfps].fMaxIntTime = SC450AI_HDR_2X_LONG_EXP_LINE_MAX(nVts, (2 * nVts + 11 * SC450AI_MAX_RATIO - 13) / (SC450AI_MAX_RATIO + 1)) / 2.0f;
        }

        ptSlowShutterParam->tSlowShutterTbl[nfps].fRealFps = 1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * nVts);
        ptSlowShutterParam->fMaxFps  =  ptSlowShutterParam->tSlowShutterTbl[nfps].fRealFps;

        SNS_INFO("pipe=%d, fps=%f, max_expline=%.2f(%.2f), vts=0x%x\n",
                nPipeId,
                ptSlowShutterParam->tSlowShutterTbl[nfps].fRealFps,
                ptSlowShutterParam->tSlowShutterTbl[nfps].fMaxIntTime,
                ptSlowShutterParam->tSlowShutterTbl[nfps].fMaxIntTime * sns_obj->ae_ctrl_param.fTimePerLine,
                nVts);
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc450ai_get_fps(ISP_PIPE_ID nPipeId, AX_F32 *pFps)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(pFps);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    *pFps = sns_obj->ae_ctrl_param.sns_ae_param.fCurFps;

    return AX_SNS_SUCCESS;
}


AX_S32 sc450ai_set_fps(ISP_PIPE_ID nPipeId, AX_F32 fFps)
{
    AX_U32 vts = 0;
    AX_S32 result = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if(AXSNS_CAMPARE_FLOAT(AX_SNS_FPS_MIN, fFps) || AXSNS_CAMPARE_FLOAT(fFps, AX_SNS_FPS_MAX)) {
        SNS_ERR("pipe:%d, fps:%f is not supported, range:[%f-%f]\n", nPipeId, fFps, AX_SNS_FPS_MIN, AX_SNS_FPS_MAX);
        return AX_SNS_ERR_NOT_SUPPORT;
    }

    if (IS_SNS_FPS_EQUAL(fFps, sns_sc450aiparams[nPipeId].setting_fps)) {
        vts = sns_sc450aiparams[nPipeId].setting_vts;
    } else {
        vts = 1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * fFps);
        if (vts > SC450AI_MAX_VTS){
            vts = SC450AI_MAX_VTS;
            SNS_WRN("Beyond max vts:0x%x\n", vts);
        }
    }

    if(fFps > sns_obj->ae_ctrl_param.sns_ae_param.fCurFps) {
        sns_sc450aiparams[nPipeId].vts = vts;
        if (IS_SNS_FPS_EQUAL(fFps, sns_obj->sns_attr_param.fFrameRate)) {
            sns_obj->sns_mode_obj.nVts = vts;
            sns_obj->sns_mode_obj.fFrameRate = sns_obj->sns_attr_param.fFrameRate;
        }
        sc450ai_set_exp_limit(nPipeId, sns_obj->ae_ctrl_param.sns_ae_param.fCurRatio);
        result = sc450ai_set_vts(nPipeId, vts);
        if (result != 0) {
            vts = 1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * sns_obj->ae_ctrl_param.sns_ae_param.fCurFps);
            sns_sc450aiparams[nPipeId].vts = vts;
            sc450ai_set_exp_limit(nPipeId, sns_obj->ae_ctrl_param.sns_ae_param.fCurRatio);
            SNS_ERR("sc450ai_set_vts failed %d \n", result);
            return result;
        }
    } else {
        result = sc450ai_set_vts(nPipeId, vts);
        if (result != 0) {
            SNS_ERR("sc450ai_set_vts failed %d \n", result);
            return result;
        }
        sns_sc450aiparams[nPipeId].vts = vts;
        if (IS_SNS_FPS_EQUAL(fFps, sns_obj->sns_attr_param.fFrameRate)) {
            sns_obj->sns_mode_obj.nVts = vts;
            sns_obj->sns_mode_obj.fFrameRate = sns_obj->sns_attr_param.fFrameRate;
        }
        sc450ai_set_exp_limit(nPipeId, sns_obj->ae_ctrl_param.sns_ae_param.fCurRatio);
    }

    sns_obj->ae_ctrl_param.sns_ae_param.fCurFps = 1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * vts);

    SNS_INFO("pipe:%d, userFps:%f, curFps:%f, vts:0x%x\n",
        nPipeId, fFps, sns_obj->ae_ctrl_param.sns_ae_param.fCurFps, vts);

    return AX_SNS_SUCCESS;
}