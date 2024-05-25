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
#include <math.h>

#include "ax_base_type.h"
#include "ax_isp_common.h"

#include "isp_sensor_types.h"
#include "isp_sensor_internal.h"

#include "sc200ai.h"
#include "sc200ai_reg.h"
#include "sc200ai_ae_ctrl.h"
#include "sc200ai_settings.h"


extern AX_U8 gSc200aiSlaveAddr[AX_VIN_MAX_PIPE_NUM];

static SNSSC200AI_OBJ_T gSc200aiParams[AX_VIN_MAX_PIPE_NUM];

static AX_F32 gAgainTable[SENSOR_MAX_GAIN_STEP];
static AX_F32 gDgainTable[SENSOR_MAX_GAIN_STEP];

/*user config*/
static AX_F32 gFpsGear[] = {1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00,
                            11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 19.00, 20.00,
                            21.00, 22.00, 23.00, 24.00, 25.00, 26.00, 27.00, 28.00, 29.00, 30.00, 60.00
                           };

static AX_SNS_DRV_DELAY_TABLE_T gSc200aiAeRegsTable[] = {
    /* regs index */       /* regs addr */        /*regs value*/  /*Delay Frame Num*/
    {SC200AI_EXPLINE_LONG_H_IDX,    SC200AI_EXPLINE_LONG_H,     0,      0},
    {SC200AI_EXPLINE_LONG_M_IDX,    SC200AI_EXPLINE_LONG_M,     0,      0},
    {SC200AI_EXPLINE_LONG_L_IDX,    SC200AI_EXPLINE_LONG_L,     0,      0},
    {SC200AI_EXPLINE_SHORT_H_IDX,   SC200AI_EXPLINE_SHORT_H,    0,      0},
    {SC200AI_EXPLINE_SHORT_M_IDX,   SC200AI_EXPLINE_SHORT_M,    0,      0},
    {SC200AI_EXPLINE_SHORT_L_IDX,   SC200AI_EXPLINE_SHORT_L,    0,      0},
    {SC200AI_AGAIN_LONG_H_IDX,      SC200AI_AGAIN_LONG_H,       0,      0},
    {SC200AI_AGAIN_LONG_L_IDX,      SC200AI_AGAIN_LONG_L,       0,      0},
    {SC200AI_AGAIN_SHORT_H_IDX,     SC200AI_AGAIN_SHORT_H,      0,      0},
    {SC200AI_AGAIN_SHORT_L_IDX,     SC200AI_AGAIN_SHORT_L,      0,      0},
    {SC200AI_DGAIN_LONG_H_IDX,      SC200AI_DGAIN_LONG_H,       0,      0},
    {SC200AI_DGAIN_LONG_L_IDX,      SC200AI_DGAIN_LONG_L,       0,      0},
    {SC200AI_DGAIN_SHORT_H_IDX,     SC200AI_DGAIN_SHORT_H,      0,      0},
    {SC200AI_DGAIN_SHORT_L_IDX,     SC200AI_DGAIN_SHORT_L,      0,      0},
    {SC200AI_VTS_LONG_H_IDX,        SC200AI_VTS_LONG_H,         0,      0},
    {SC200AI_VTS_LONG_L_IDX,        SC200AI_VTS_LONG_L,         0,      0},
    {SC200AI_VTS_SHORT_H_IDX,       SC200AI_VTS_SHORT_H,        0,      0},
    {SC200AI_VTS_SHORT_L_IDX,       SC200AI_VTS_SHORT_L,        0,      0},
};

const SC200AI_GAIN_TABLE_T sc200ai_again_table[] = {
    {1.000,  0x03, 0x40},
    {1.016,  0x03, 0x41},
    {1.031,  0x03, 0x42},
    {1.047,  0x03, 0x43},
    {1.063,  0x03, 0x44},
    {1.078,  0x03, 0x45},
    {1.094,  0x03, 0x46},
    {1.109,  0x03, 0x47},
    {1.125,  0x03, 0x48},
    {1.141,  0x03, 0x49},
    {1.156,  0x03, 0x4A},
    {1.172,  0x03, 0x4B},
    {1.188,  0x03, 0x4C},
    {1.203,  0x03, 0x4D},
    {1.219,  0x03, 0x4E},
    {1.234,  0x03, 0x4F},
    {1.250,  0x03, 0x50},
    {1.266,  0x03, 0x51},
    {1.281,  0x03, 0x52},
    {1.297,  0x03, 0x53},
    {1.313,  0x03, 0x54},
    {1.328,  0x03, 0x55},
    {1.344,  0x03, 0x56},
    {1.359,  0x03, 0x57},
    {1.375,  0x03, 0x58},
    {1.391,  0x03, 0x59},
    {1.406,  0x03, 0x5A},
    {1.422,  0x03, 0x5B},
    {1.438,  0x03, 0x5C},
    {1.453,  0x03, 0x5D},
    {1.469,  0x03, 0x5E},
    {1.484,  0x03, 0x5F},
    {1.500,  0x03, 0x60},
    {1.516,  0x03, 0x61},
    {1.531,  0x03, 0x62},
    {1.547,  0x03, 0x63},
    {1.563,  0x03, 0x64},
    {1.578,  0x03, 0x65},
    {1.594,  0x03, 0x66},
    {1.609,  0x03, 0x67},
    {1.625,  0x03, 0x68},
    {1.641,  0x03, 0x69},
    {1.656,  0x03, 0x6A},
    {1.672,  0x03, 0x6B},
    {1.688,  0x03, 0x6C},
    {1.703,  0x03, 0x6D},
    {1.719,  0x03, 0x6E},
    {1.734,  0x03, 0x6F},
    {1.750,  0x03, 0x70},
    {1.766,  0x03, 0x71},
    {1.781,  0x03, 0x72},
    {1.797,  0x03, 0x73},
    {1.813,  0x03, 0x74},
    {1.828,  0x03, 0x75},
    {1.844,  0x03, 0x76},
    {1.859,  0x03, 0x77},
    {1.875,  0x03, 0x78},
    {1.891,  0x03, 0x79},
    {1.906,  0x03, 0x7A},
    {1.922,  0x03, 0x7B},
    {1.938,  0x03, 0x7C},
    {1.953,  0x03, 0x7D},
    {1.969,  0x03, 0x7E},
    {1.984,  0x03, 0x7F},
    {2.000,  0x07, 0x40},
    {2.031,  0x07, 0x41},
    {2.063,  0x07, 0x42},
    {2.094,  0x07, 0x43},
    {2.125,  0x07, 0x44},
    {2.156,  0x07, 0x45},
    {2.188,  0x07, 0x46},
    {2.219,  0x07, 0x47},
    {2.250,  0x07, 0x48},
    {2.281,  0x07, 0x49},
    {2.313,  0x07, 0x4A},
    {2.344,  0x07, 0x4B},
    {2.375,  0x07, 0x4C},
    {2.406,  0x07, 0x4D},
    {2.438,  0x07, 0x4E},
    {2.469,  0x07, 0x4F},
    {2.500,  0x07, 0x50},
    {2.531,  0x07, 0x51},
    {2.563,  0x07, 0x52},
    {2.594,  0x07, 0x53},
    {2.625,  0x07, 0x54},
    {2.656,  0x07, 0x55},
    {2.688,  0x07, 0x56},
    {2.719,  0x07, 0x57},
    {2.750,  0x07, 0x58},
    {2.781,  0x07, 0x59},
    {2.813,  0x07, 0x5A},
    {2.844,  0x07, 0x5B},
    {2.875,  0x07, 0x5C},
    {2.906,  0x07, 0x5D},
    {2.938,  0x07, 0x5E},
    {2.969,  0x07, 0x5F},
    {3.000,  0x07, 0x60},
    {3.031,  0x07, 0x61},
    {3.063,  0x07, 0x62},
    {3.094,  0x07, 0x63},
    {3.125,  0x07, 0x64},
    {3.156,  0x07, 0x65},
    {3.188,  0x07, 0x66},
    {3.219,  0x07, 0x67},
    {3.250,  0x07, 0x68},
    {3.281,  0x07, 0x69},
    {3.313,  0x07, 0x6A},
    {3.344,  0x07, 0x6B},
    {3.375,  0x07, 0x6C},
    // {3.400,  0x23, 0x40}, //bad
    // {3.453,  0x23, 0x41},
    // {3.506,  0x23, 0x42},
    {3.559,  0x23, 0x43},
    {3.613,  0x23, 0x44},
    {3.666,  0x23, 0x45},
    {3.719,  0x23, 0x46},
    {3.772,  0x23, 0x47},
    {3.825,  0x23, 0x48},
    {3.878,  0x23, 0x49},
    {3.931,  0x23, 0x4A},
    {3.984,  0x23, 0x4B},
    {4.038,  0x23, 0x4C},
    {4.091,  0x23, 0x4D},
    {4.144,  0x23, 0x4E},
    {4.197,  0x23, 0x4F},
    {4.250,  0x23, 0x50},
    {4.303,  0x23, 0x51},
    {4.356,  0x23, 0x52},
    {4.409,  0x23, 0x53},
    {4.463,  0x23, 0x54},
    {4.516,  0x23, 0x55},
    {4.569,  0x23, 0x56},
    {4.622,  0x23, 0x57},
    {4.675,  0x23, 0x58},
    {4.728,  0x23, 0x59},
    {4.781,  0x23, 0x5A},
    {4.834,  0x23, 0x5B},
    {4.888,  0x23, 0x5C},
    {4.941,  0x23, 0x5D},
    {4.994,  0x23, 0x5E},
    {5.047,  0x23, 0x5F},
    {5.100,  0x23, 0x60},
    {5.153,  0x23, 0x61},
    {5.206,  0x23, 0x62},
    {5.259,  0x23, 0x63},
    {5.313,  0x23, 0x64},
    {5.366,  0x23, 0x65},
    {5.419,  0x23, 0x66},
    {5.472,  0x23, 0x67},
    {5.525,  0x23, 0x68},
    {5.578,  0x23, 0x69},
    {5.631,  0x23, 0x6A},
    {5.684,  0x23, 0x6B},
    {5.738,  0x23, 0x6C},
    {5.791,  0x23, 0x6D},
    {5.844,  0x23, 0x6E},
    {5.897,  0x23, 0x6F},
    {5.950,  0x23, 0x70},
    {6.003,  0x23, 0x71},
    {6.056,  0x23, 0x72},
    {6.109,  0x23, 0x73},
    {6.163,  0x23, 0x74},
    {6.216,  0x23, 0x75},
    {6.269,  0x23, 0x76},
    {6.322,  0x23, 0x77},
    {6.375,  0x23, 0x78},
    {6.428,  0x23, 0x79},
    {6.481,  0x23, 0x7A},
    {6.534,  0x23, 0x7B},
    {6.588,  0x23, 0x7C},
    {6.641,  0x23, 0x7D},
    {6.694,  0x23, 0x7E},
    {6.747,  0x23, 0x7F},
    {6.800,  0x27, 0x40},
    {6.906,  0x27, 0x41},
    {7.013,  0x27, 0x42},
    {7.119,  0x27, 0x43},
    {7.225,  0x27, 0x44},
    {7.331,  0x27, 0x45},
    {7.438,  0x27, 0x46},
    {7.544,  0x27, 0x47},
    {7.650,  0x27, 0x48},
    {7.756,  0x27, 0x49},
    {7.863,  0x27, 0x4A},
    {7.969,  0x27, 0x4B},
    {8.075,  0x27, 0x4C},
    {8.181,  0x27, 0x4D},
    {8.288,  0x27, 0x4E},
    {8.394,  0x27, 0x4F},
    {8.500,  0x27, 0x50},
    {8.606,  0x27, 0x51},
    {8.713,  0x27, 0x52},
    {8.819,  0x27, 0x53},
    {8.925,  0x27, 0x54},
    {9.031,  0x27, 0x55},
    {9.138,  0x27, 0x56},
    {9.244,  0x27, 0x57},
    {9.350,  0x27, 0x58},
    {9.456,  0x27, 0x59},
    {9.563,  0x27, 0x5A},
    {9.669,  0x27, 0x5B},
    {9.775,  0x27, 0x5C},
    {9.881,  0x27, 0x5D},
    {9.988,  0x27, 0x5E},
    {10.094, 0x27, 0x5F},
    {10.200, 0x27, 0x60},
    {10.306, 0x27, 0x61},
    {10.413, 0x27, 0x62},
    {10.519, 0x27, 0x63},
    {10.625, 0x27, 0x64},
    {10.731, 0x27, 0x65},
    {10.838, 0x27, 0x66},
    {10.944, 0x27, 0x67},
    {11.050, 0x27, 0x68},
    {11.156, 0x27, 0x69},
    {11.263, 0x27, 0x6A},
    {11.369, 0x27, 0x6B},
    {11.475, 0x27, 0x6C},
    {11.581, 0x27, 0x6D},
    {11.688, 0x27, 0x6E},
    {11.794, 0x27, 0x6F},
    {11.900, 0x27, 0x70},
    {12.006, 0x27, 0x71},
    {12.113, 0x27, 0x72},
    {12.219, 0x27, 0x73},
    {12.325, 0x27, 0x74},
    {12.431, 0x27, 0x75},
    {12.538, 0x27, 0x76},
    {12.644, 0x27, 0x77},
    {12.750, 0x27, 0x78},
    {12.856, 0x27, 0x79},
    {12.963, 0x27, 0x7A},
    {13.069, 0x27, 0x7B},
    {13.175, 0x27, 0x7C},
    {13.281, 0x27, 0x7D},
    {13.388, 0x27, 0x7E},
    {13.494, 0x27, 0x7F},
    {13.600, 0x2F, 0x40},
    {13.813, 0x2F, 0x41},
    {14.025, 0x2F, 0x42},
    {14.238, 0x2F, 0x43},
    {14.450, 0x2F, 0x44},
    {14.663, 0x2F, 0x45},
    {14.875, 0x2F, 0x46},
    {15.088, 0x2F, 0x47},
    {15.300, 0x2F, 0x48},
    {15.513, 0x2F, 0x49},
    {15.725, 0x2F, 0x4A},
    {15.938, 0x2F, 0x4B},
    {16.150, 0x2F, 0x4C},
    {16.363, 0x2F, 0x4D},
    {16.575, 0x2F, 0x4E},
    {16.788, 0x2F, 0x4F},
    {17.000, 0x2F, 0x50},
    {17.213, 0x2F, 0x51},
    {17.425, 0x2F, 0x52},
    {17.638, 0x2F, 0x53},
    {17.850, 0x2F, 0x54},
    {18.063, 0x2F, 0x55},
    {18.275, 0x2F, 0x56},
    {18.488, 0x2F, 0x57},
    {18.700, 0x2F, 0x58},
    {18.913, 0x2F, 0x59},
    {19.125, 0x2F, 0x5A},
    {19.338, 0x2F, 0x5B},
    {19.550, 0x2F, 0x5C},
    {19.763, 0x2F, 0x5D},
    {19.975, 0x2F, 0x5E},
    {20.188, 0x2F, 0x5F},
    {20.400, 0x2F, 0x60},
    {20.613, 0x2F, 0x61},
    {20.825, 0x2F, 0x62},
    {21.038, 0x2F, 0x63},
    {21.250, 0x2F, 0x64},
    {21.463, 0x2F, 0x65},
    {21.675, 0x2F, 0x66},
    {21.888, 0x2F, 0x67},
    {22.100, 0x2F, 0x68},
    {22.313, 0x2F, 0x69},
    {22.525, 0x2F, 0x6A},
    {22.738, 0x2F, 0x6B},
    {22.950, 0x2F, 0x6C},
    {23.163, 0x2F, 0x6D},
    {23.375, 0x2F, 0x6E},
    {23.588, 0x2F, 0x6F},
    {23.800, 0x2F, 0x70},
    {24.013, 0x2F, 0x71},
    {24.225, 0x2F, 0x72},
    {24.438, 0x2F, 0x73},
    {24.650, 0x2F, 0x74},
    {24.863, 0x2F, 0x75},
    {25.075, 0x2F, 0x76},
    {25.288, 0x2F, 0x77},
    {25.500, 0x2F, 0x78},
    {25.713, 0x2F, 0x79},
    {25.925, 0x2F, 0x7A},
    {26.138, 0x2F, 0x7B},
    {26.350, 0x2F, 0x7C},
    {26.563, 0x2F, 0x7D},
    {26.775, 0x2F, 0x7E},
    {26.988, 0x2F, 0x7F},
    {27.200, 0x3F, 0x40},
    {27.625, 0x3F, 0x41},
    {28.050, 0x3F, 0x42},
    {28.475, 0x3F, 0x43},
    {28.900, 0x3F, 0x44},
    {29.325, 0x3F, 0x45},
    {29.750, 0x3F, 0x46},
    {30.175, 0x3F, 0x47},
    {30.600, 0x3F, 0x48},
    {31.025, 0x3F, 0x49},
    {31.450, 0x3F, 0x4A},
    {31.875, 0x3F, 0x4B},
    {32.300, 0x3F, 0x4C},
    {32.725, 0x3F, 0x4D},
    {33.150, 0x3F, 0x4E},
    {33.575, 0x3F, 0x4F},
    {34.000, 0x3F, 0x50},
    {34.425, 0x3F, 0x51},
    {34.850, 0x3F, 0x52},
    {35.275, 0x3F, 0x53},
    {35.700, 0x3F, 0x54},
    {36.125, 0x3F, 0x55},
    {36.550, 0x3F, 0x56},
    {36.975, 0x3F, 0x57},
    {37.400, 0x3F, 0x58},
    {37.825, 0x3F, 0x59},
    {38.250, 0x3F, 0x5A},
    {38.675, 0x3F, 0x5B},
    {39.100, 0x3F, 0x5C},
    {39.525, 0x3F, 0x5D},
    {39.950, 0x3F, 0x5E},
    {40.375, 0x3F, 0x5F},
    {40.800, 0x3F, 0x60},
    {41.225, 0x3F, 0x61},
    {41.650, 0x3F, 0x62},
    {42.075, 0x3F, 0x63},
    {42.500, 0x3F, 0x64},
    {42.925, 0x3F, 0x65},
    {43.350, 0x3F, 0x66},
    {43.775, 0x3F, 0x67},
    {44.200, 0x3F, 0x68},
    {44.625, 0x3F, 0x69},
    {45.050, 0x3F, 0x6A},
    {45.475, 0x3F, 0x6B},
    {45.900, 0x3F, 0x6C},
    {46.325, 0x3F, 0x6D},
    {46.750, 0x3F, 0x6E},
    {47.175, 0x3F, 0x6F},
    {47.600, 0x3F, 0x70},
    {48.025, 0x3F, 0x71},
    {48.450, 0x3F, 0x72},
    {48.875, 0x3F, 0x73},
    {49.300, 0x3F, 0x74},
    {49.725, 0x3F, 0x75},
    {50.150, 0x3F, 0x76},
    {50.575, 0x3F, 0x77},
    {51.000, 0x3F, 0x78},
    {51.425, 0x3F, 0x79},
    {51.850, 0x3F, 0x7A},
    {52.275, 0x3F, 0x7B},
    {52.700, 0x3F, 0x7C},
    {53.125, 0x3F, 0x7D},
    {53.550, 0x3F, 0x7E},
    {53.975, 0x3F, 0x7F},
};

const SC200AI_GAIN_TABLE_T sc200ai_dgain_table[] = {
    {1.000,  0x00, 0x80},
    // {1.016,  0x00, 0x82},
    {1.031,  0x00, 0x84},
    {1.047,  0x00, 0x86},
    {1.063,  0x00, 0x88},
    {1.078,  0x00, 0x8a},
    {1.094,  0x00, 0x8c},
    {1.109,  0x00, 0x8e},
    {1.125,  0x00, 0x90},
    {1.141,  0x00, 0x92},
    {1.156,  0x00, 0x94},
    {1.172,  0x00, 0x96},
    {1.188,  0x00, 0x98},
    {1.203,  0x00, 0x9a},
    {1.219,  0x00, 0x9c},
    {1.234,  0x00, 0x9e},
    {1.250,  0x00, 0xa0},
    {1.266,  0x00, 0xa2},
    {1.281,  0x00, 0xa4},
    {1.297,  0x00, 0xa6},
    {1.313,  0x00, 0xa8},
    {1.328,  0x00, 0xaa},
    {1.344,  0x00, 0xac},
    {1.359,  0x00, 0xae},
    {1.375,  0x00, 0xb0},
    {1.391,  0x00, 0xb2},
    {1.406,  0x00, 0xb4},
    {1.422,  0x00, 0xb6},
    {1.438,  0x00, 0xb8},
    {1.453,  0x00, 0xba},
    {1.469,  0x00, 0xbc},
    {1.484,  0x00, 0xbe},
    // {1.500,  0x00, 0xc0},
    {1.516,  0x00, 0xc2},
    {1.531,  0x00, 0xc4},
    {1.547,  0x00, 0xc6},
    {1.563,  0x00, 0xc8},
    {1.578,  0x00, 0xca},
    {1.594,  0x00, 0xcc},
    {1.609,  0x00, 0xce},
    {1.625,  0x00, 0xd0},
    {1.641,  0x00, 0xd2},
    {1.656,  0x00, 0xd4},
    {1.672,  0x00, 0xd6},
    {1.688,  0x00, 0xd8},
    {1.703,  0x00, 0xda},
    {1.719,  0x00, 0xdc},
    {1.734,  0x00, 0xde},
    {1.750,  0x00, 0xe0},
    {1.766,  0x00, 0xe2},
    {1.781,  0x00, 0xe4},
    {1.797,  0x00, 0xe6},
    {1.813,  0x00, 0xe8},
    {1.828,  0x00, 0xea},
    {1.844,  0x00, 0xec},
    {1.859,  0x00, 0xee},
    {1.875,  0x00, 0xf0},
    {1.891,  0x00, 0xf2},
    {1.906,  0x00, 0xf4},
    {1.922,  0x00, 0xf6},
    {1.938,  0x00, 0xf8},
    {1.953,  0x00, 0xfa},
    {1.969,  0x00, 0xfc},
    {1.984,  0x00, 0xfe},
    // {2.000,  0x01, 0x80},//bad
    {2.031,  0x01, 0x82},
    {2.063,  0x01, 0x84},
    {2.094,  0x01, 0x86},
    {2.125,  0x01, 0x88},
    {2.156,  0x01, 0x8a},
    {2.188,  0x01, 0x8c},
    {2.219,  0x01, 0x8e},
    {2.250,  0x01, 0x90},
    {2.281,  0x01, 0x92},
    {2.313,  0x01, 0x94},
    {2.344,  0x01, 0x96},
    {2.375,  0x01, 0x98},
    {2.406,  0x01, 0x9a},
    {2.438,  0x01, 0x9c},
    {2.469,  0x01, 0x9e},
    {2.500,  0x01, 0xa0},
    {2.531,  0x01, 0xa2},
    {2.563,  0x01, 0xa4},
    {2.594,  0x01, 0xa6},
    {2.625,  0x01, 0xa8},
    {2.656,  0x01, 0xaa},
    {2.688,  0x01, 0xac},
    {2.719,  0x01, 0xae},
    {2.750,  0x01, 0xb0},
    {2.781,  0x01, 0xb2},
    {2.813,  0x01, 0xb4},
    {2.844,  0x01, 0xb6},
    {2.875,  0x01, 0xb8},
    {2.906,  0x01, 0xba},
    {2.938,  0x01, 0xbc},
    {2.969,  0x01, 0xbe},
    // {3.000,  0x01, 0xc0},
    {3.031,  0x01, 0xc2},
    {3.063,  0x01, 0xc4},
    {3.094,  0x01, 0xc6},
    {3.125,  0x01, 0xc8},
    {3.156,  0x01, 0xca},
    {3.188,  0x01, 0xcc},
    {3.219,  0x01, 0xce},
    {3.250,  0x01, 0xd0},
    {3.281,  0x01, 0xd2},
    {3.313,  0x01, 0xd4},
    {3.344,  0x01, 0xd6},
    {3.375,  0x01, 0xd8},
    {3.406,  0x01, 0xda},
    {3.438,  0x01, 0xdc},
    {3.469,  0x01, 0xde},
    {3.500,  0x01, 0xe0},
    {3.531,  0x01, 0xe2},
    {3.563,  0x01, 0xe4},
    {3.594,  0x01, 0xe6},
    {3.625,  0x01, 0xe8},
    {3.656,  0x01, 0xea},
    {3.688,  0x01, 0xec},
    {3.719,  0x01, 0xee},
    {3.750,  0x01, 0xf0},
    {3.781,  0x01, 0xf2},
    {3.813,  0x01, 0xf4},
    {3.844,  0x01, 0xf6},
    {3.875,  0x01, 0xf8},
    {3.906,  0x01, 0xfa},
    {3.938,  0x01, 0xfc},
    {3.969,  0x01, 0xfe},
    // {4.000,  0x03, 0x80}, //bad
    {4.063,  0x03, 0x82},
    {4.125,  0x03, 0x84},
    {4.188,  0x03, 0x86},
    {4.250,  0x03, 0x88},
    {4.313,  0x03, 0x8a},
    {4.375,  0x03, 0x8c},
    {4.438,  0x03, 0x8e},
    {4.500,  0x03, 0x90},
    {4.563,  0x03, 0x92},
    {4.625,  0x03, 0x94},
    {4.688,  0x03, 0x96},
    {4.750,  0x03, 0x98},
    {4.813,  0x03, 0x9a},
    {4.875,  0x03, 0x9c},
    {4.938,  0x03, 0x9e},
    {5.000,  0x03, 0xa0},
    {5.063,  0x03, 0xa2},
    {5.125,  0x03, 0xa4},
    {5.188,  0x03, 0xa6},
    {5.250,  0x03, 0xa8},
    {5.313,  0x03, 0xaa},
    {5.375,  0x03, 0xac},
    {5.438,  0x03, 0xae},
    {5.500,  0x03, 0xb0},
    {5.563,  0x03, 0xb2},
    {5.625,  0x03, 0xb4},
    {5.688,  0x03, 0xb6},
    {5.750,  0x03, 0xb8},
    {5.813,  0x03, 0xba},
    {5.875,  0x03, 0xbc},
    {5.938,  0x03, 0xbe},
    {6.000,  0x03, 0xc0},
    {6.063,  0x03, 0xc2},
    {6.125,  0x03, 0xc4},
    {6.188,  0x03, 0xc6},
    {6.250,  0x03, 0xc8},
    {6.313,  0x03, 0xca},
    {6.375,  0x03, 0xcc},
    {6.438,  0x03, 0xce},
    {6.500,  0x03, 0xd0},
    {6.563,  0x03, 0xd2},
    {6.625,  0x03, 0xd4},
    {6.688,  0x03, 0xd6},
    {6.750,  0x03, 0xd8},
    {6.813,  0x03, 0xda},
    {6.875,  0x03, 0xdc},
    {6.938,  0x03, 0xde},
    {7.000,  0x03, 0xe0},
    {7.063,  0x03, 0xe2},
    {7.125,  0x03, 0xe4},
    {7.188,  0x03, 0xe6},
    {7.250,  0x03, 0xe8},
    {7.313,  0x03, 0xea},
    {7.375,  0x03, 0xec},
    {7.438,  0x03, 0xee},
    {7.500,  0x03, 0xf0},
    {7.563,  0x03, 0xf2},
    {7.625,  0x03, 0xf4},
    {7.688,  0x03, 0xf6},
    {7.750,  0x03, 0xf8},
    {7.813,  0x03, 0xfa},
    {7.875,  0x03, 0xfc},
    {7.938,  0x03, 0xfe},
    {8.000,  0x07, 0x80},
    {8.125,  0x07, 0x82},
    {8.250,  0x07, 0x84},
    {8.375,  0x07, 0x86},
    {8.500,  0x07, 0x88},
    {8.625,  0x07, 0x8a},
    {8.750,  0x07, 0x8c},
    {8.875,  0x07, 0x8e},
    {9.000,  0x07, 0x90},
    {9.125,  0x07, 0x92},
    {9.250,  0x07, 0x94},
    {9.375,  0x07, 0x96},
    {9.500,  0x07, 0x98},
    {9.625,  0x07, 0x9a},
    {9.750,  0x07, 0x9c},
    {9.875,  0x07, 0x9e},
    {10.000, 0x07, 0xa0},
    {10.125, 0x07, 0xa2},
    {10.250, 0x07, 0xa4},
    {10.375, 0x07, 0xa6},
    {10.500, 0x07, 0xa8},
    {10.625, 0x07, 0xaa},
    {10.750, 0x07, 0xac},
    {10.875, 0x07, 0xae},
    {11.000, 0x07, 0xb0},
    {11.125, 0x07, 0xb2},
    {11.250, 0x07, 0xb4},
    {11.375, 0x07, 0xb6},
    {11.500, 0x07, 0xb8},
    {11.625, 0x07, 0xba},
    {11.750, 0x07, 0xbc},
    {11.875, 0x07, 0xbe},
    {12.000, 0x07, 0xc0},
    {12.125, 0x07, 0xc2},
    {12.250, 0x07, 0xc4},
    {12.375, 0x07, 0xc6},
    {12.500, 0x07, 0xc8},
    {12.625, 0x07, 0xca},
    {12.750, 0x07, 0xcc},
    {12.875, 0x07, 0xce},
    {13.000, 0x07, 0xd0},
    {13.125, 0x07, 0xd2},
    {13.250, 0x07, 0xd4},
    {13.375, 0x07, 0xd6},
    {13.500, 0x07, 0xd8},
    {13.625, 0x07, 0xda},
    {13.750, 0x07, 0xdc},
    {13.875, 0x07, 0xde},
    {14.000, 0x07, 0xe0},
    {14.125, 0x07, 0xe2},
    {14.250, 0x07, 0xe4},
    {14.375, 0x07, 0xe6},
    {14.500, 0x07, 0xe8},
    {14.625, 0x07, 0xea},
    {14.750, 0x07, 0xec},
    {14.875, 0x07, 0xee},
    {15.000, 0x07, 0xf0},
    {15.125, 0x07, 0xf2},
    {15.250, 0x07, 0xf4},
    {15.375, 0x07, 0xf6},
    {15.500, 0x07, 0xf8},
    {15.625, 0x07, 0xfa},
    {15.750, 0x07, 0xfc},
    {15.875, 0x07, 0xfe},
    {16.000, 0x0f, 0x80},
    {16.250, 0x0f, 0x82},
    {16.500, 0x0f, 0x84},
    {16.750, 0x0f, 0x86},
    {17.000, 0x0f, 0x88},
    {17.250, 0x0f, 0x8a},
    {17.500, 0x0f, 0x8c},
    {17.750, 0x0f, 0x8e},
    {18.000, 0x0f, 0x90},
    {18.250, 0x0f, 0x92},
    {18.500, 0x0f, 0x94},
    {18.750, 0x0f, 0x96},
    {19.000, 0x0f, 0x98},
    {19.250, 0x0f, 0x9a},
    {19.500, 0x0f, 0x9c},
    {19.750, 0x0f, 0x9e},
    {20.000, 0x0f, 0xa0},
    {20.250, 0x0f, 0xa2},
    {20.500, 0x0f, 0xa4},
    {20.750, 0x0f, 0xa6},
    {21.000, 0x0f, 0xa8},
    {21.250, 0x0f, 0xaa},
    {21.500, 0x0f, 0xac},
    {21.750, 0x0f, 0xae},
    {22.000, 0x0f, 0xb0},
    {22.250, 0x0f, 0xb2},
    {22.500, 0x0f, 0xb4},
    {22.750, 0x0f, 0xb6},
    {23.000, 0x0f, 0xb8},
    {23.250, 0x0f, 0xba},
    {23.500, 0x0f, 0xbc},
    {23.750, 0x0f, 0xbe},
    {24.000, 0x0f, 0xc0},
    {24.250, 0x0f, 0xc2},
    {24.500, 0x0f, 0xc4},
    {24.750, 0x0f, 0xc6},
    {25.000, 0x0f, 0xc8},
    {25.250, 0x0f, 0xca},
    {25.500, 0x0f, 0xcc},
    {25.750, 0x0f, 0xce},
    {26.000, 0x0f, 0xd0},
    {26.250, 0x0f, 0xd2},
    {26.500, 0x0f, 0xd4},
    {26.750, 0x0f, 0xd6},
    {27.000, 0x0f, 0xd8},
    {27.250, 0x0f, 0xda},
    {27.500, 0x0f, 0xdc},
    {27.750, 0x0f, 0xde},
    {28.000, 0x0f, 0xe0},
    {28.250, 0x0f, 0xe2},
    {28.500, 0x0f, 0xe4},
    {28.750, 0x0f, 0xe6},
    {29.000, 0x0f, 0xe8},
    {29.250, 0x0f, 0xea},
    {29.500, 0x0f, 0xec},
    {29.750, 0x0f, 0xee},
    {30.000, 0x0f, 0xf0},
    {30.250, 0x0f, 0xf2},
    {30.500, 0x0f, 0xf4},
    {30.750, 0x0f, 0xf6},
    {31.000, 0x0f, 0xf8},
    {31.250, 0x0f, 0xfa},
    {31.500, 0x0f, 0xfc},
    {31.750, 0x0f, 0xfe},
};


static AX_S32 sc200ai_again2value(AX_F32 gain, AX_U8 *again_in, AX_U8 *again_de, AX_F32 *gain_value)
{
    AX_U32 i;
    AX_U32 count;

    if (!again_in || !again_de)
        return AX_SNS_ERR_NULL_PTR;

    count = sizeof(sc200ai_again_table) / sizeof(sc200ai_again_table[0]);

    for (i = 0; i < count; i++) {
        if (AXSNS_CAMPARE_FLOAT(gain, sc200ai_again_table[i].gain)) {
            continue;
        } else {
            *again_in = sc200ai_again_table[i].gain_in;
            *again_de = sc200ai_again_table[i].gain_de;
            *gain_value = sc200ai_again_table[i].gain;
            SNS_DBG("again=%f, again_in=0x%x, again_de=0x%x\n", gain, *again_in, *again_de);
            return AX_SNS_SUCCESS;
        }
    }

    return AX_SNS_ERR_NOT_MATCH;
}

static AX_S32 sc200ai_dgain2value(AX_F32 gain, AX_U8 *dgain_in, AX_U8 *dgain_de, AX_F32 *gain_value)
{
    AX_U32 i;
    AX_U32 count;
    AX_U32 ret_value = 0;

    if (!dgain_in || !dgain_de)
        return AX_SNS_ERR_NULL_PTR;

    count = sizeof(sc200ai_dgain_table) / sizeof(sc200ai_dgain_table[0]);

    for (i = 0; i < count; i++) {
        if (AXSNS_CAMPARE_FLOAT(gain, sc200ai_dgain_table[i].gain)) {
            continue;
        } else {
            *dgain_in = sc200ai_dgain_table[i].gain_in;
            *dgain_de = sc200ai_dgain_table[i].gain_de;
            *gain_value = sc200ai_dgain_table[i].gain;
            SNS_DBG("dgain=%f, dgain_in=0x%x, dgain_de=0x%x\n", gain, *dgain_in, *dgain_de);
            return AX_SNS_SUCCESS;
        }
    }

    return AX_SNS_ERR_NOT_MATCH;
}

AX_S32 sc200ai_get_gain_table(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_TABLE_T *params)
{
    AX_U32 i;
    AX_S32 ret = 0;
    if (!params)
        return AX_SNS_ERR_NULL_PTR;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    params->nAgainTableSize = sizeof(sc200ai_again_table) / sizeof(sc200ai_again_table[0]);
    params->nDgainTableSize = sizeof(sc200ai_dgain_table) / sizeof(sc200ai_dgain_table[0]);

    for (i = 0; i < params->nAgainTableSize; i++) {
        gAgainTable[i] = sc200ai_again_table[i].gain;
        params->pAgainTable = gAgainTable;
    }

    for (i = 0; i < params->nDgainTableSize; i++) {
        gDgainTable[i] = sc200ai_dgain_table[i].gain;
        params->pDgainTable = gDgainTable;
    }

    return ret;
}


/****************************************************************************
 * exposure control external function
 ****************************************************************************/
static AX_S32 sc200ai_set_exp_limit(ISP_PIPE_ID nPipeId, AX_F32 fHdrRatio)
{
    AX_U32 vts_s = 0;
    SNS_STATE_OBJ *sns_obj = NULL;
    AX_F32 ratio_limit = 1.0f;

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if (IS_LINEAR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] = (2 * gSc200aiParams[nPipeId].vts - 8) / 2.0;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX] = 1 / 2.0;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_LONG_FRAME_IDX] = 1 / 2.0;
    } else if (IS_2DOL_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        if(IS_FLOAT_ZERO(fHdrRatio)) {
            SNS_ERR("pipe:%d, fHdrRatio:%f is zero !\n", nPipeId, fHdrRatio);
        }
        //2*vts - 2*vts_s - 10 = (2*vts_s - 10) * fHdrRatio
        vts_s = (gSc200aiParams[nPipeId].vts + 5 * fHdrRatio - 5) / (fHdrRatio + 1);
        sc200ai_set_vts_s(nPipeId, vts_s);
        SNS_DBG("pipe:%d, user_ratio:%f, user_vts:0x%x, vts_s:0x%x\n", nPipeId, fHdrRatio, gSc200aiParams[nPipeId].vts, vts_s);

        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] = (2 * gSc200aiParams[nPipeId].vts - 2 * vts_s - 10) / 2.0;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX] = 1 / 2.0;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_LONG_FRAME_IDX] = 4 / 2.0;

        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX] = (2 * vts_s - 10) / 2.0;
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX] = 1 / 2.0;
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeIncrement[HDR_MEDIUM_FRAME_IDX] = 4 / 2.0;

        ratio_limit = sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] /
                      sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX];

    } else {
        // wrong hdr mode
    }

    SNS_DBG("pipe:%d, ratio_limit:%f, expline_limit:%.2f-%.2f-%.2f-%.2f(%.2f-%.2f-%.2f-%.2f)\n",
            nPipeId, ratio_limit,
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX] * sns_obj->ae_ctrl_param.fTimePerLine,
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX] * sns_obj->ae_ctrl_param.fTimePerLine,
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX] * sns_obj->ae_ctrl_param.fTimePerLine,
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX] * sns_obj->ae_ctrl_param.fTimePerLine);

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_get_params_from_setting(ISP_PIPE_ID nPipeId)
{
    AX_S32 ret = 0;
    AX_U32 reg_cnt = 0;
    camera_i2c_reg_array *setting = AX_NULL;
    AX_U32 vts = 0;

    ret = sc200ai_select_setting(nPipeId, &setting, &reg_cnt);
    if(ret) {
        return ret;
    }

    ret = sc200ai_get_vts_from_setting(nPipeId, setting, reg_cnt, &vts);
    if(ret) {
        return ret;
    }

    gSc200aiParams[nPipeId].vts = vts;

    SNS_DBG("pipe:%d, get setting params vts:0x%x\n", nPipeId, gSc200aiParams[nPipeId].vts);

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_cfg_aec_param(ISP_PIPE_ID nPipeId)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    sc200ai_get_params_from_setting(nPipeId);
    sns_obj->sns_mode_obj.nVts = gSc200aiParams[nPipeId].vts;
    gSc200aiParams[nPipeId].setting_vts = gSc200aiParams[nPipeId].vts;
    gSc200aiParams[nPipeId].setting_fps = sns_obj->sns_mode_obj.fFrameRate;

    /* update initial vts to reg table */
    sc200ai_set_vts(nPipeId, sns_obj->sns_mode_obj.nVts);

    sns_obj->ae_ctrl_param.fTimePerLine = SNS_1_SECOND_UNIT_US / sns_obj->sns_mode_obj.fFrameRate / sns_obj->sns_mode_obj.nVts;

    SNS_INFO("pipe:%d, setting fps:%f, vts:0x%x, fTimePerLine:%f\n", nPipeId,
        sns_obj->sns_mode_obj.fFrameRate, sns_obj->sns_mode_obj.nVts, sns_obj->ae_ctrl_param.fTimePerLine);

    /* exp limit */
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinRatio = SC200AI_MIN_RATIO;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxRatio = SC200AI_MAX_RATIO;
    sc200ai_set_exp_limit(nPipeId, SC200AI_MAX_RATIO);

    /* gain limit */
    sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_LONG_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_LONG_FRAME_IDX] = SC200AI_MAX_AGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fAGainIncrement[HDR_LONG_FRAME_IDX] = 1 / 256.0;

    sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_LONG_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_LONG_FRAME_IDX] = SC200AI_MAX_DGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fDGainIncrement[HDR_LONG_FRAME_IDX] = 1 / 128.0;

    sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_MEDIUM_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_MEDIUM_FRAME_IDX] = SC200AI_MAX_AGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fAGainIncrement[HDR_MEDIUM_FRAME_IDX] = 1 / 256.0;

    sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_MEDIUM_FRAME_IDX] = 1.0f;
    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_MEDIUM_FRAME_IDX] = SC200AI_MAX_DGAIN;
    sns_obj->ae_ctrl_param.sns_ae_param.fDGainIncrement[HDR_MEDIUM_FRAME_IDX] = 1 / 128.0;

    /* hcglcg */
    sns_obj->ae_ctrl_param.eSnsHcgLcgMode = AX_LCG_NOTSUPPORT_MODE;

    if (sns_obj->sns_mode_obj.eHDRMode == AX_SNS_LINEAR_MODE) {
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeOffset[HDR_LONG_FRAME_IDX] = sc200ai_get_exp_offset(nPipeId);
    } else if (sns_obj->sns_mode_obj.eHDRMode == AX_SNS_HDR_2X_MODE) {
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeOffset[HDR_LONG_FRAME_IDX] = sc200ai_get_exp_offset(nPipeId);
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeOffset[HDR_MEDIUM_FRAME_IDX] = sc200ai_get_exp_offset(nPipeId);
    } else {
        sns_obj->ae_ctrl_param.sns_ae_param.fIntegrationTimeOffset[HDR_LONG_FRAME_IDX] = sc200ai_get_exp_offset(nPipeId);
    }

    /* current fps */
    sns_obj->ae_ctrl_param.sns_ae_param.fCurFps = sns_obj->sns_mode_obj.fFrameRate;

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_set_again(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptAGain)
{
    AX_S32 result = 0;
    AX_U8 gain_in;
    AX_U8 gain_de;
    AX_F32 gain_value = 0;
    AX_F32 fGainFromUser = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptAGain);

    /* long gain seting */
    fGainFromUser = ptAGain->fGain[HDR_LONG_FRAME_IDX];
    fGainFromUser = AXSNS_CLIP3(fGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_LONG_FRAME_IDX],
                                sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_LONG_FRAME_IDX]);

    result = sc200ai_again2value(fGainFromUser, &gain_in, &gain_de, &gain_value);
    if (result) {
        SNS_ERR("new gain match failed \n");
        return result;
    } else {
        sc200ai_update_regidx_table(nPipeId, SC200AI_AGAIN_LONG_H_IDX, gain_in);
        sc200ai_update_regidx_table(nPipeId, SC200AI_AGAIN_LONG_L_IDX, gain_de);
        sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_LONG_FRAME_IDX] = gain_value;
    }

    /* short gain seting */
    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        fGainFromUser = ptAGain->fGain[HDR_MEDIUM_FRAME_IDX];
        fGainFromUser = AXSNS_CLIP3(fGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinAgain[HDR_MEDIUM_FRAME_IDX],
                                    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxAgain[HDR_MEDIUM_FRAME_IDX]);

        result = sc200ai_again2value(fGainFromUser, &gain_in, &gain_de, &gain_value);
        if (result) {
            SNS_ERR("new gain match failed \n");
            return result;
        } else {
            sc200ai_update_regidx_table(nPipeId, SC200AI_AGAIN_SHORT_H_IDX, gain_in);
            sc200ai_update_regidx_table(nPipeId, SC200AI_AGAIN_SHORT_L_IDX, gain_de);
            sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_MEDIUM_FRAME_IDX] = gain_value;
        }
    }

    SNS_INFO("pipe:%d, userAgain:%f-%f, curAgain:%f-%f\n", nPipeId,
            ptAGain->fGain[HDR_LONG_FRAME_IDX], ptAGain->fGain[HDR_MEDIUM_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_param.fCurAGain[HDR_MEDIUM_FRAME_IDX]);

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_set_dgain(ISP_PIPE_ID nPipeId, AX_SNS_AE_GAIN_CFG_T *ptDGain)
{
    AX_S32 result = 0;
    AX_U8 gain_in;
    AX_U8 gain_de;
    AX_F32 gain_value = 0;
    AX_F32 fGainFromUser = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptDGain);

    /* long frame digital gain seting */
    fGainFromUser = ptDGain->fGain[HDR_LONG_FRAME_IDX];
    fGainFromUser = AXSNS_CLIP3(fGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_LONG_FRAME_IDX],
                                sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_LONG_FRAME_IDX]);

    result = sc200ai_dgain2value(fGainFromUser, &gain_in, &gain_de, &gain_value);
    if (result) {
        SNS_ERR("new gain match failed \n");
        return result;
    } else {
        sc200ai_update_regidx_table(nPipeId, SC200AI_DGAIN_LONG_H_IDX, gain_in);
        sc200ai_update_regidx_table(nPipeId, SC200AI_DGAIN_LONG_L_IDX, gain_de);
        sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_LONG_FRAME_IDX] = gain_value;
    }

    /* short frame digital gain seting */
    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        fGainFromUser = ptDGain->fGain[HDR_MEDIUM_FRAME_IDX];
        fGainFromUser = AXSNS_CLIP3(fGainFromUser, sns_obj->ae_ctrl_param.sns_ae_limit.fMinDgain[HDR_MEDIUM_FRAME_IDX],
                                    sns_obj->ae_ctrl_param.sns_ae_limit.fMaxDgain[HDR_MEDIUM_FRAME_IDX]);

        result = sc200ai_dgain2value(fGainFromUser, &gain_in, &gain_de, &gain_value);
        if (result) {
            SNS_ERR("new gain match failed \n");
            return result;
        } else {
            sc200ai_update_regidx_table(nPipeId, SC200AI_DGAIN_SHORT_H_IDX, gain_in);
            sc200ai_update_regidx_table(nPipeId, SC200AI_DGAIN_SHORT_L_IDX, gain_de);
            sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_MEDIUM_FRAME_IDX] = gain_value;
        }
    }

    SNS_INFO("pipe:%d, userDgain:%f-%f, curDgain:%f-%f\n", nPipeId,
            ptDGain->fGain[HDR_LONG_FRAME_IDX], ptDGain->fGain[HDR_MEDIUM_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_param.fCurDGain[HDR_MEDIUM_FRAME_IDX]);

    return AX_SNS_SUCCESS;
}

/* Calculate the max int time according to the exposure ratio */
AX_S32 sc200ai_get_integration_time_range(ISP_PIPE_ID nPipeId, AX_F32 fHdrRatio,
        AX_SNS_AE_INT_TIME_RANGE_T *ptIntTimeRange)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptIntTimeRange);

    sc200ai_set_exp_limit(nPipeId, fHdrRatio);

    ptIntTimeRange->fMaxIntegrationTime[HDR_LONG_FRAME_IDX] =
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX];
    ptIntTimeRange->fMinIntegrationTime[HDR_LONG_FRAME_IDX] =
        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX];
    if (AX_SNS_HDR_2X_MODE == sns_obj->sns_mode_obj.eHDRMode) {
        ptIntTimeRange->fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX];
        ptIntTimeRange->fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX] =
            sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX];
    }

    return AX_SNS_SUCCESS;
}


AX_S32 sc200ai_set_integration_time(ISP_PIPE_ID nPipeId, AX_SNS_AE_SHUTTER_CFG_T *ptIntTime)
{
    AX_U8 exp_h = 0, exp_m = 0, exp_l = 0;
    AX_U32 exp_reg = 0;
    AX_F32 fExpLineFromUser = 0;
    AX_F32 ratio = 1.0f;
    AX_U32 LineGap = 0;

    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);
    SNS_CHECK_PTR_VALID(ptIntTime);

    fExpLineFromUser = ptIntTime->fIntTime[HDR_LONG_FRAME_IDX];
    fExpLineFromUser = AXSNS_CLIP3(fExpLineFromUser,
                                   sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_LONG_FRAME_IDX],
                                   sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_LONG_FRAME_IDX]);

    exp_reg = 2 * fExpLineFromUser;
    exp_h = (exp_reg & 0xF000) >> 12;
    exp_m = (exp_reg & 0xFF0) >> 4;
    exp_l = (exp_reg & 0xF) << 4;

    sc200ai_update_regidx_table(nPipeId, SC200AI_EXPLINE_LONG_H_IDX, exp_h);
    sc200ai_update_regidx_table(nPipeId, SC200AI_EXPLINE_LONG_M_IDX, exp_m);
    sc200ai_update_regidx_table(nPipeId, SC200AI_EXPLINE_LONG_L_IDX, exp_l);

    sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX] = exp_reg / 2.0;

    if (IS_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
        fExpLineFromUser = ptIntTime->fIntTime[HDR_MEDIUM_FRAME_IDX];
        fExpLineFromUser = AXSNS_CLIP3(fExpLineFromUser,
                                        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMinIntegrationTime[HDR_MEDIUM_FRAME_IDX],
                                        sns_obj->ae_ctrl_param.sns_ae_limit.tIntTimeRange.fMaxIntegrationTime[HDR_MEDIUM_FRAME_IDX]);

        exp_reg = 2 * fExpLineFromUser;

        //LineGap < Height
        LineGap = sc200ai_get_vts_s(nPipeId) / 2;
        if(LineGap > sns_obj->sns_mode_obj.nHeight) {
            exp_reg = sns_obj->sns_mode_obj.nHeight - 1;
        }

        exp_h = (exp_reg & 0xF000) >> 12;
        exp_m = (exp_reg & 0xFF0) >> 4;
        exp_l = (exp_reg & 0xF) << 4;

        sc200ai_update_regidx_table(nPipeId, SC200AI_EXPLINE_SHORT_H_IDX, exp_h);
        sc200ai_update_regidx_table(nPipeId, SC200AI_EXPLINE_SHORT_M_IDX, exp_m);
        sc200ai_update_regidx_table(nPipeId, SC200AI_EXPLINE_SHORT_L_IDX, exp_l);

        sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX] = exp_reg / 2.0;

        ratio = sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX] /
                sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX];
    }

    SNS_INFO("pipe:%d, userExpline:%f-%f, userRatio:%.2f, curExpline:%f-%f(%f-%f), curRatio:%.2f, line_period:%f\n",
            nPipeId, ptIntTime->fIntTime[0], ptIntTime->fIntTime[1], ptIntTime->fHdrRatio[0],
            sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX],
            sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_LONG_FRAME_IDX] * sns_obj->ae_ctrl_param.fTimePerLine,
            sns_obj->ae_ctrl_param.sns_ae_param.fCurIntegrationTime[HDR_MEDIUM_FRAME_IDX] * sns_obj->ae_ctrl_param.fTimePerLine,
            ratio, sns_obj->ae_ctrl_param.fTimePerLine);

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_get_hw_exposure_params(ISP_PIPE_ID nPipeId, AX_SNS_EXP_CTRL_PARAM_T *ptAeCtrlParam)
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

AX_U32 sc200ai_refresh_all_regs_from_tbl(ISP_PIPE_ID nPipeId)
{
    AX_S32 i = 0;
    AX_U32 nNum = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);

    nNum = sizeof(gSc200aiAeRegsTable) / sizeof(gSc200aiAeRegsTable[0]);

    for (i = 0; i < nNum; i++) {
        sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr = gSc200aiAeRegsTable[i].nRegAddr;
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_update_init_exposure_reg(ISP_PIPE_ID nPipeId)
{
    int i = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    for (i = 0; i < sns_obj->sztRegsInfo[0].nRegNum; i++) {
        sc200ai_write_register(nPipeId, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData);
        SNS_INFO("pipe %d, [%2d] nRegAddr 0x%x, nRegValue 0x%x\n", nPipeId, i,
                sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData);
    }

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_ae_get_sensor_reg_info(ISP_PIPE_ID nPipeId, AX_SNS_REGS_CFG_TABLE_T *ptSnsRegsInfo)
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
        sns_obj->sztRegsInfo[0].tComBus.I2cDev = sc200ai_get_bus_num(nPipeId);
        sns_obj->sztRegsInfo[0].nRegNum = sizeof(gSc200aiAeRegsTable) / sizeof(gSc200aiAeRegsTable[0]);
        sns_obj->sztRegsInfo[0].nCfg2ValidDelayMax = 2;

        for (i = 0; i < sns_obj->sztRegsInfo[0].nRegNum; i++) {
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].bUpdate = AX_TRUE;
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nDevAddr = gSc200aiSlaveAddr[nPipeId];
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nAddrByteNum = SC200AI_ADDR_BYTE;
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nDataByteNum = SC200AI_DATA_BYTE;
            sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nDelayFrmNum = gSc200aiAeRegsTable[i].nDelayFrmNum;

            SNS_INFO("pipe %d, [%2d] nRegAddr 0x%x, nRegValue 0x%x\n", nPipeId, i,
                        sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nRegAddr, sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData);
        }

        bUpdateReg = AX_TRUE;
        sns_obj->bSyncInit = AX_TRUE;
        sc200ai_update_init_exposure_reg(nPipeId);
    } else {
        for (i = 0; i < sns_obj->sztRegsInfo[0].nRegNum; i++) {
            if (sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].nData == sns_obj->sztRegsInfo[1].sztData.sztI2cData[i].nData) {
                sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].bUpdate = AX_FALSE;
            } else {
                sns_obj->sztRegsInfo[0].sztData.sztI2cData[i].bUpdate = AX_TRUE;
                bUpdateReg = AX_TRUE;

                SNS_INFO("pipe %d, [%2d] nRegAddr 0x%x, nRegValue 0x%x\n", nPipeId, i,
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

AX_S32 sc200ai_get_fps(ISP_PIPE_ID nPipeId, AX_F32 *pFps)
{
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_PTR_VALID(pFps);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    *pFps = sns_obj->ae_ctrl_param.sns_ae_param.fCurFps;

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_set_fps(ISP_PIPE_ID nPipeId, AX_F32 fFps)
{
    AX_U32 vts = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;

    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);
    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if(AXSNS_CAMPARE_FLOAT(AX_SNS_FPS_MIN, fFps) || AXSNS_CAMPARE_FLOAT(fFps, AX_SNS_FPS_MAX)) {
        SNS_ERR("pipe:%d, fps:%f is not supported, range:[%f-%f]\n", nPipeId, fFps, AX_SNS_FPS_MIN, AX_SNS_FPS_MAX);
        return AX_SNS_ERR_NOT_SUPPORT;
    }
    if (IS_SNS_FPS_EQUAL(fFps, gSc200aiParams[nPipeId].setting_fps)) {
        vts = gSc200aiParams[nPipeId].setting_vts;
    } else {
        vts = 1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * fFps);
        if (vts > SC200AI_MAX_VTS){
            vts = SC200AI_MAX_VTS;
            SNS_WRN("Beyond max vts:0x%x\n", vts);
        }
    }

    sc200ai_set_vts(nPipeId, vts);
    gSc200aiParams[nPipeId].vts = vts;
    if (IS_SNS_FPS_EQUAL(fFps, sns_obj->sns_attr_param.fFrameRate)) {
        sns_obj->sns_mode_obj.nVts = vts;
        sns_obj->sns_mode_obj.fFrameRate = sns_obj->sns_attr_param.fFrameRate;
    }

    sc200ai_set_exp_limit(nPipeId, SC200AI_MAX_RATIO);
    sns_obj->ae_ctrl_param.sns_ae_param.fCurFps = 1 * SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * vts);

    SNS_INFO("pipe:%d, userFps:%f, curFps:%f, vts:0x%x\n",
        nPipeId, fFps, sns_obj->ae_ctrl_param.sns_ae_param.fCurFps, vts);

    return AX_SNS_SUCCESS;
}

AX_S32 sc200ai_get_slow_shutter_param(ISP_PIPE_ID nPipeId, AX_SNS_AE_SLOW_SHUTTER_PARAM_T *ptSlowShutterParam)
{
    AX_U32 i = 0;
    AX_U32 vts = 0;
    AX_U32 vts_s = 0;
    AX_S32 result = 0;
    SNS_STATE_OBJ *sns_obj = AX_NULL;
    AX_U32 nFrameRate = 0;

    SNS_CHECK_PTR_VALID(ptSlowShutterParam);
    SNS_CHECK_VALUE_RANGE_VALID(nPipeId, 0, AX_VIN_MAX_PIPE_NUM - 1);

    SENSOR_GET_CTX(nPipeId, sns_obj);
    SNS_CHECK_PTR_VALID(sns_obj);

    if (AXSNS_CAMPARE_FLOAT(sns_obj->sns_mode_obj.fFrameRate, SNS_MAX_FRAME_RATE)) {
        SNS_ERR("framerate:%f out of range:%d\n", sns_obj->sns_mode_obj.fFrameRate, SNS_MAX_FRAME_RATE);
        return AX_SNS_ERR_ILLEGAL_PARAM;
    }

    SNS_INFO("pipe:%d, line_period:%f, max_ratio:%.2f\n", nPipeId, sns_obj->ae_ctrl_param.fTimePerLine, SC200AI_MAX_RATIO);

    if(AXSNS_CAMPARE_FLOAT(sns_obj->sns_mode_obj.fFrameRate, (AX_U32)sns_obj->sns_mode_obj.fFrameRate)) {
        nFrameRate = (AX_U32)ceil(sns_obj->sns_mode_obj.fFrameRate);
    } else {
        nFrameRate = (AX_U32)sns_obj->sns_mode_obj.fFrameRate;
    }

    ptSlowShutterParam->nGroupNum = AXSNS_MIN((sizeof(gFpsGear) / sizeof(AX_F32)), nFrameRate);
    //ax_sns_quick_sort_float(gFpsGear, ptSlowShutterParam->nGroupNum);
    ptSlowShutterParam->fMinFps = AXSNS_MAX(gFpsGear[0],
                                            (SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * SC200AI_MAX_VTS)));

    for (i = 0; i < ptSlowShutterParam->nGroupNum; i++) {
        if (AXSNS_CAMPARE_FLOAT(gFpsGear[i], sns_obj->sns_mode_obj.fFrameRate) ||
            IS_SNS_FPS_EQUAL(gFpsGear[i], sns_obj->sns_mode_obj.fFrameRate)) {
            vts = sns_obj->sns_mode_obj.nVts;
        } else {
            vts = SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * gFpsGear[i]);
        }
        if (vts > SC200AI_MAX_VTS) {
            vts = SC200AI_MAX_VTS;
            SNS_WRN("Beyond minmum fps:%f\n", ptSlowShutterParam->fMinFps);
        }

        if (IS_LINEAR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
            ptSlowShutterParam->tSlowShutterTbl[i].fMaxIntTime = (2 * vts - 8) / 2.0;
        } else if (IS_2DOL_HDR_MODE(sns_obj->sns_mode_obj.eHDRMode)) {
            vts_s = (vts + 5 * SC200AI_MAX_RATIO - 5) / (SC200AI_MAX_RATIO + 1);
            ptSlowShutterParam->tSlowShutterTbl[i].fMaxIntTime = (2 * vts - 2 * vts_s - 10) / 2.0;
        }

        ptSlowShutterParam->tSlowShutterTbl[i].fRealFps = SNS_1_SECOND_UNIT_US / (sns_obj->ae_ctrl_param.fTimePerLine * vts);
        ptSlowShutterParam->fMaxFps = ptSlowShutterParam->tSlowShutterTbl[i].fRealFps;

        SNS_INFO("fps = %f, max_expline = %.2f(%.2f), vts = 0x%x, vts_s = 0x%x\n",
                ptSlowShutterParam->tSlowShutterTbl[i].fRealFps,
                ptSlowShutterParam->tSlowShutterTbl[i].fMaxIntTime,
                ptSlowShutterParam->tSlowShutterTbl[i].fMaxIntTime * sns_obj->ae_ctrl_param.fTimePerLine,
                vts, vts_s);
    }

    return AX_SNS_SUCCESS;
}
