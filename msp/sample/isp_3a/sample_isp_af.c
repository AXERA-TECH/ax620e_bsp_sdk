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
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include "ax_isp_api.h"
#include "ax_sys_api.h"
#include "sample_isp_af.h"
#include <pthread.h>
#include <assert.h>
#include "ax_isp_3a_api.h"
#include "common_cam.h"
#include "common_type.h"

extern AX_CAMERA_T gCams[MAX_CAMERAS];
static AX_ISP_IQ_AF_STAT_PARAM_T af_ife_param = {
    /* nAfEnable */
    1,
    /* eAfStatPos */
    /* 0:AX_ISP_AF_STAT_ITP_PSTHDR_RLTM, 1:AX_ISP_AF_STAT_ITP_PSTHDR_WBC, 2:AX_ISP_AF_STAT_ITP_PSTHDR_HDR, 3:AX_ISP_AF_STAT_ITP_PREHDR_BPC_LONG_FRMAE,
	   4:AX_ISP_AF_STAT_ITP_PREHDR_BPC_SHORT_FRMAE 5:AX_ISP_AF_STAT_IFE_PREHDR_LONG_FRMAE 6:AX_ISP_AF_STAT_IFE_PREHDR_SHORT_FRMAE*/
    AX_ISP_AF_STAT_ITP_PREHDR_DPC_LONG_FRAME,
    /* tAfMode */
    {
        /* nfv_mode[4] */
        {0, 0, 0, 0, /*0 - 3*/},
    },
    /* tAfBayer2Y */
    {
        /* nCoeffR */
        1024,
        /* nCoeffGb */
        1024,
        /* nCoeffGr */
        1024,
        /* nCoeffB */
        1024,
    },
    /* tAfGamma */
    {
        /* nGammaEnable */
        1,
        /* nGammaLut[33] */
        {
            0, 861, 1176, 1412, 1607, 1777, 1928, 2067, 2195, 2314,
            2427, 2533, 2634, 2731, 2824, 2913, 2998, 3081, 3162, 3240, 3315, 3389,
            3460, 3530, 3599, 3665, 3731, 3795, 3857, 3919, 3979, 4038, 4095},
    },
    /* tAfScaler */
    {
        /* nScaleEnable */
        1,
        /* nScaleFactor */
        1,
        /* nScaleWeight[8] */
        {64, 64, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
    },
    /* tAfFilter */
    {
        /* nFirEnable[2] */
        {1, 1, /*0 - 1*/},
        /* nV1iirRefId */
        1,
        /* nV2iirRefId */
        1,
        /* nH1IirRefId */
        1,
        /* nH2IirRefId */
        1,
    },
    /* tAfCoring */
    {
        /* nCoringThr[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nCoringGain[4] */
        {16, 16, 16, 16, /*0 - 3*/},
        /* nCoringLut[4][16] */
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16},
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16},
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16},
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16}},
        /* nCoringPixSumflg[4] */
        {1, 1, 1, 1, /*0 - 3*/},
    },
    /* tAfBrightPix */
    {
        /* nLdgRange[2] */
        //{1, 1, /*0 - 1*/},
        /* nLdgEnable[4] */
        //{1, 1, 1, 1, /*0 - 3*/},
        /* nLdgSlope[4] */
        //{32, 32, 32, 32, /*0 - 3*/},
        /* nLdgLimit[4] */
        //{0, 0, 0, 0, /*0 - 3*/},
        /* nLdgThr[4] */
        //{2400, 2400, 2400, 2400, /*0 - 3*/},
        /* nbrightpixCountThr[4] */
        //{2048, 2048, 2048, 2048, /*0 - 3*/},
                /* nLdgRange[2] */
        {0, 0, /*0 - 1*/},
        /* nLdgEnable[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nLdgSlope[4] */
        {32, 32, 32, 32, /*0 - 3*/},
        /* nLdgLimit[4] */
        {128, 128, 128, 128, /*0 - 3*/},
        /* nLdgThr[4] */
        {4095, 4095, 4095, 4095, /*0 - 3*/},
        /* nbrightpixCountThr[4] */
        {4095, 4095, 4095, 4095, /*0 - 3*/},
    },
    /* tAfDrc */
    {
        /* nDrcEnable */
        0,
        /* nDrcLut[17] */
        {0, 38, 52, 71, 97, 133, 181, 247, 338, 461, 630, 861, 1176, 1607, 2195, 2998, 4095},
    },
    /* tAfRoi */
    {
        /* nRoiOffsetH */
        64,
        /* nRoiOffsetV */
        40,
        /* nRoiRegionNumH */
        18,
        /* nRoiRegionNumV */
        10,
        /* nRoiRegionW */
        160,
        /* nRoiRegionH */
        144,
    },
    /* tAfLumaSuppress */
    {
        /* nSuppressMode */
        0,
        /* tLumaSuppressUserCurve */
        {
            /* nLumaLowStartTh */
            0,
            /* nLumaLowEndTh */
            0,
            /* nLumaHighStartTh */
            0,
            /* nLumaHighEndTh */
            0,
            /* nLumaLowMinRatio */
            0,
            /* nLumaHighMinRatio */
            0,
        },
    },
    /* tAfPeakEnhance */
    {
        /* nSquareMode */
        0,
    },
};


static AX_ISP_IQ_AF_STAT_PARAM_T af_stat_rltm_param = {
    /* nAfEnable */
    1,
    /* eAfStatPos */
    /* 0:AX_ISP_AF_STAT_ITP_PSTHDR_RLTM, 1:AX_ISP_AF_STAT_ITP_PSTHDR_WBC, 2:AX_ISP_AF_STAT_ITP_PSTHDR_HDR, 3:AX_ISP_AF_STAT_ITP_PREHDR_BPC_LONG_FRMAE,
	   4:AX_ISP_AF_STAT_ITP_PREHDR_BPC_SHORT_FRMAE 5:AX_ISP_AF_STAT_IFE_PREHDR_LONG_FRMAE 6:AX_ISP_AF_STAT_IFE_PREHDR_SHORT_FRMAE*/
    AX_ISP_AF_STAT_ITP_PSTHDR_RLTM,
    /* tAfMode */
    {
        /* nfv_mode[4] */
        {0, 0, 0, 0, /*0 - 3*/},
    },
    /* tAfBayer2Y */
    {
        /* nCoeffR */
        1024,
        /* nCoeffGb */
        1024,
        /* nCoeffGr */
        1024,
        /* nCoeffB */
        1024,
    },
    /* tAfGamma */
    {
        /* nGammaEnable */
        1,
        /* nGammaLut[33] */
        {
            0, 861, 1176, 1412, 1607, 1777, 1928, 2067, 2195, 2314,
        2427, 2533, 2634, 2731, 2824, 2913, 2998, 3081, 3162, 3240, 3315, 3389,
        3460, 3530, 3599, 3665, 3731, 3795, 3857, 3919, 3979, 4038, 4095
        },
    },
    /* tAfScaler */
    {
        /* nScaleEnable */
        1,
        /* nScaleFactor */
        1,
        /* nScaleWeight[8] */
        {64, 64, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
    },
    /* tAfFilter */
    {
        /* nFirEnable[2] */
        {1, 1, /*0 - 1*/},
        /* nV1iirRefId */
        0,
        /* nV2iirRefId */
        0,
        /* nH1IirRefId */
        0,
        /* nH2IirRefId */
        0,
    },
    /* tAfCoring */
    {
        /* nCoringThr[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nCoringGain[4] */
        {16, 16, 16, 16, /*0 - 3*/},
        /* nCoringLut[4][16] */
        {
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16},
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16},
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16},
            {1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 7, 9, 13, 16}
        },
        /* nCoringPixSumflg[4] */
        {1, 1, 1, 1, /*0 - 3*/},
    },
    /* tAfBrightPix */
    {
        /* nLdgRange[2] */
        {0, 0, /*0 - 1*/},
        /* nLdgEnable[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nLdgSlope[4] */
        {32, 32, 32, 32, /*0 - 3*/},
        /* nLdgLimit[4] */
        {128, 128, 128, 128, /*0 - 3*/},
        /* nLdgThr[4] */
        {4095, 4095, 4095, 4095, /*0 - 3*/},
        /* nbrightpixCountThr[4] */
        {4095, 4095, 4095, 4095, /*0 - 3*/},
    },
    /* tAfDrc */
    {
        /* nDrcEnable */
        1,
        /* nDrcLut[17] */
        {0, 0, 0, 1, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4095},

    },
    /* tAfRoi */
    {
        /* nRoiOffsetH */
        64,
        /* nRoiOffsetV */
        40,
        /* nRoiRegionNumH */
        18,
        /* nRoiRegionNumV */
        10,
        /* nRoiRegionW */
        160,
        /* nRoiRegionH */
        144,
    },
    /* tAfLumaSuppress */
    {
        /* nSuppressMode */
        0,
        /* tLumaSuppressUserCurve */
        {
            /* nLumaLowStartTh */
            0,
            /* nLumaLowEndTh */
            0,
            /* nLumaHighStartTh */
            0,
            /* nLumaHighEndTh */
            0,
            /* nLumaLowMinRatio */
            0,
            /* nLumaHighMinRatio */
            0,
        },
    },
    /* tAfPeakEnhance */
    {
        /* nSquareMode */
        0,
    },
};


static AX_ISP_IQ_AF_IIR_REF_LIST_T af_iir_ref_list_param =
{
    /* nV1iirRefNum */
    21,
    /* nV2iirRefNum */
    21,
    /* nH1IirRefNum */
    21,
    /* nH2IirRefNum */
    21,
    /* tV1IirRefList[32] */
    {
        /* 0 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 1 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 2 */
        {
            /* nStartFreq */
            209715,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 2617, -5233, 2617, 4682, -1690, /*0 - 9*/},
        },
        /* 3 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            419430,
            /* nIirCoefList[10] */
            {846, 1692, 846, 1514, -801, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 4 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 5 */
        {
            /* nStartFreq */
            419430,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 1603, -3205, 1603, 1514, -801, /*0 - 9*/},
        },
        /* 6 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            629146,
            /* nIirCoefList[10] */
            {1603, 3206, 1603, -1513, -801, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 7 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            734003,
            /* nIirCoefList[10] */
            {2068, 4137, 2068, -3062, -1114, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 8 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 9 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 10 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 11 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 12 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 13 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 14 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 15 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 16 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 17 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 18 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 19 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 20 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 21 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 22 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 23 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 24 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 25 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 26 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 27 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 28 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 29 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 30 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 31 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
    },
     /* tV2IirRefList[32] */
    {
        /* 0 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 1 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 2 */
        {
            /* nStartFreq */
            209715,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 2617, -5233, 2617, 4682, -1690, /*0 - 9*/},
        },
        /* 3 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            419430,
            /* nIirCoefList[10] */
            {846, 1692, 846, 1514, -801, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 4 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 5 */
        {
            /* nStartFreq */
            419430,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 1603, -3205, 1603, 1514, -801, /*0 - 9*/},
        },
        /* 6 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            629146,
            /* nIirCoefList[10] */
            {1603, 3206, 1603, -1513, -801, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 7 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            734003,
            /* nIirCoefList[10] */
            {2068, 4137, 2068, -3062, -1114, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 8 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 9 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 10 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 11 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 12 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 13 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 14 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 15 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 16 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 17 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 18 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 19 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 20 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 21 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 22 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 23 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 24 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 25 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 26 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 27 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 28 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 29 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 30 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 31 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
    },
    /* tH1IirRefList[32] */
    {
        /* 0 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 1 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 2 */
        {
            /* nStartFreq */
            209715,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 2617, -5233, 2617, 4682, -1690, /*0 - 9*/},
        },
        /* 3 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            419430,
            /* nIirCoefList[10] */
            {846, 1692, 846, 1514, -801, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 4 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 5 */
        {
            /* nStartFreq */
            419430,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 1603, -3205, 1603, 1514, -801, /*0 - 9*/},
        },
        /* 6 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            629146,
            /* nIirCoefList[10] */
            {1603, 3206, 1603, -1513, -801, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 7 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            734003,
            /* nIirCoefList[10] */
            {2068, 4137, 2068, -3062, -1114, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 8 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 9 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 10 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 11 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 12 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 13 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 14 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 15 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 16 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 17 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 18 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 19 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 20 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 21 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 22 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 23 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 24 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 25 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 26 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 27 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 28 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 29 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 30 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 31 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
    },
    /* tH2IirRefList[32] */
    {
        /* 0 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 1 */
        {
            /* nStartFreq */
            104858,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 3279, -6557, 3279, 6394, -2626, /*0 - 9*/},
        },
        /* 2 */
        {
            /* nStartFreq */
            209715,
            /* nEndFreq */
            314573,
            /* nIirCoefList[10] */
            {537, 1074, 537, 3063, -1114, 2617, -5233, 2617, 4682, -1690, /*0 - 9*/},
        },
        /* 3 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            419430,
            /* nIirCoefList[10] */
            {846, 1692, 846, 1514, -801, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 4 */
        {
            /* nStartFreq */
            314573,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 2068, -4136, 2068, 3063, -1114, /*0 - 9*/},
        },
        /* 5 */
        {
            /* nStartFreq */
            419430,
            /* nEndFreq */
            524288,
            /* nIirCoefList[10] */
            {1200, 2399, 1200, 0, -702, 1603, -3205, 1603, 1514, -801, /*0 - 9*/},
        },
        /* 6 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            629146,
            /* nIirCoefList[10] */
            {1603, 3206, 1603, -1513, -801, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 7 */
        {
            /* nStartFreq */
            524288,
            /* nEndFreq */
            734003,
            /* nIirCoefList[10] */
            {2068, 4137, 2068, -3062, -1114, 1200, -2398, 1200, 0, -702, /*0 - 9*/},
        },
        /* 8 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 9 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 10 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 11 */
        {
            /* nStartFreq */
            10486,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 4006, -8011, 4006, 8010, -3917, /*0 - 9*/},
        },
        /* 12 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 13 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            41943,
            /* nIirCoefList[10] */
            {15, 30, 15, 7466, -3428, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 14 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            52429,
            /* nIirCoefList[10] */
            {23, 45, 23, 7285, -3279, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 15 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 16 */
        {
            /* nStartFreq */
            20972,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3918, -7835, 3918, 7828, -3747, /*0 - 9*/},
        },
        /* 17 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            62915,
            /* nIirCoefList[10] */
            {32, 64, 32, 7105, -3137, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 18 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            83886,
            /* nIirCoefList[10] */
            {55, 109, 55, 6748, -2870, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 19 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            209715,
            /* nIirCoefList[10] */
            {276, 553, 276, 4682, -1690, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 20 */
        {
            /* nStartFreq */
            41943,
            /* nEndFreq */
            104858,
            /* nIirCoefList[10] */
            {82, 165, 82, 6394, -2626, 3748, -7494, 3748, 7466, -3428, /*0 - 9*/},
        },
        /* 21 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 22 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 23 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 24 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 25 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 26 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 27 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 28 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 29 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 30 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* 31 */
        {
            /* nStartFreq */
            0,
            /* nEndFreq */
            0,
            /* nIirCoefList[10] */
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
    },
};

enum AF_STAT { V_STAT_1 = 0, V_STAT_2 = 1, H_STAT_1 = 2, H_STAT_2 = 3, STAT_NUM = 4};
#define DEF_AF_GAMMA_LUT_NUM       (33)
#define DEF_AF_WEIGHT_LUT_NUM      (16)
#define DEF_AF_VIIR_LUT_NUM        (10)
#define DEF_AF_H1IIR_LUT_NUM       (10)
#define DEF_AF_H2IIR_LUT_NUM       (10)
#define DEF_AF_H1FIR_LUT_NUM       (13)
#define DEF_AF_H2FIR_LUT_NUM       (13)
#define DEF_AF_CORING_LUT_NUM      (16)
#define DEF_AF_DRC_LUT_NUM         (17)
#define DEF_AF_IIR_REF_LIST_SIZE   (32)
#define DEF_AF_IIR_COEF_NUM        (10)
#define DEF_AF_USED(value)         (void)value
#define DEF_AF_0_TO_1(a)           ( (0 == (a)) ? 1 : (a) )


extern volatile AX_S32 gLoopExit;
AX_S32 sample_af_init_afparams
(
    AX_U8                         pipe,
    AX_ISP_IQ_AF_STAT_PARAM_T    *pAfInitPara,
    AX_ISP_IQ_AF_STAT_PARAM_T    *pAfStatParam
)
{
    pAfInitPara->nAfEnable = pAfStatParam->nAfEnable;
    pAfInitPara->eAfStatPos = pAfStatParam->eAfStatPos;

    pAfInitPara->tAfBayer2Y.nCoeffR = pAfStatParam->tAfBayer2Y.nCoeffR;
    pAfInitPara->tAfBayer2Y.nCoeffGr = pAfStatParam->tAfBayer2Y.nCoeffGr;
    pAfInitPara->tAfBayer2Y.nCoeffGb = pAfStatParam->tAfBayer2Y.nCoeffGb;
    pAfInitPara->tAfBayer2Y.nCoeffB = pAfStatParam->tAfBayer2Y.nCoeffB;
    pAfInitPara->tAfGamma.nGammaEnable = pAfStatParam->tAfGamma.nGammaEnable;

    for (int i = 0; i < DEF_AF_GAMMA_LUT_NUM; i++)
    {
        pAfInitPara->tAfGamma.nGammaLut[i] = pAfStatParam->tAfGamma.nGammaLut[i];
    }

    pAfInitPara->tAfScaler.nScaleEnable = pAfStatParam->tAfScaler.nScaleEnable;
    pAfInitPara->tAfScaler.nScaleRatio = pAfStatParam->tAfScaler.nScaleRatio;
    for (int i = 0; i < AX_AF_WEIGHT_LUT_NUM; i++)
    {
        pAfInitPara->tAfScaler.nScaleWeight[i] = pAfStatParam->tAfScaler.nScaleWeight[i];
    }

    pAfInitPara->tAfFilter.nFirEnable[0] = pAfStatParam->tAfFilter.nFirEnable[0];
    pAfInitPara->tAfFilter.nFirEnable[1] = pAfStatParam->tAfFilter.nFirEnable[1];
    pAfInitPara->tAfFilter.nV1iirRefId = pAfStatParam->tAfFilter.nV1iirRefId;
    pAfInitPara->tAfFilter.nV2iirRefId = pAfStatParam->tAfFilter.nV2iirRefId;
    pAfInitPara->tAfFilter.nH1IirRefId = pAfStatParam->tAfFilter.nH1IirRefId;
    pAfInitPara->tAfFilter.nH2IirRefId = pAfStatParam->tAfFilter.nH2IirRefId;

    for(AX_U8 i = 0; i < AX_AF_STAT_NUM; i++ ){
        pAfInitPara->tAfCoring.nCoringThr[i] = af_ife_param.tAfCoring.nCoringThr[i];
        pAfInitPara->tAfCoring.nCoringGain[i] = af_ife_param.tAfCoring.nCoringGain[i];
    }

    memcpy(pAfInitPara->tAfCoring.nCoringLut, pAfStatParam->tAfCoring.nCoringLut, AX_AF_STAT_NUM * DEF_AF_CORING_LUT_NUM* sizeof(AX_U8));

    pAfInitPara->tAfDrc.nDrcEnable = pAfStatParam->tAfDrc.nDrcEnable;
    memcpy(pAfInitPara->tAfDrc.nDrcLut, pAfStatParam->tAfDrc.nDrcLut, DEF_AF_DRC_LUT_NUM * sizeof(AX_U16));

    pAfInitPara->tAfRoi.nRoiOffsetH = pAfStatParam->tAfRoi.nRoiOffsetH;
    pAfInitPara->tAfRoi.nRoiOffsetV = pAfStatParam->tAfRoi.nRoiOffsetV;
    pAfInitPara->tAfRoi.nRoiRegionNumH = pAfStatParam->tAfRoi.nRoiRegionNumH;
    pAfInitPara->tAfRoi.nRoiRegionNumV = pAfStatParam->tAfRoi.nRoiRegionNumV;
    pAfInitPara->tAfRoi.nRoiRegionW = pAfStatParam->tAfRoi.nRoiRegionW;
    pAfInitPara->tAfRoi.nRoiRegionH = pAfStatParam->tAfRoi.nRoiRegionH;

    pAfInitPara->tAfLumaSuppress = pAfStatParam->tAfLumaSuppress;
    pAfInitPara->tAfPeakEnhance = pAfStatParam->tAfPeakEnhance;
    pAfInitPara->tAfBrightPix   = pAfStatParam->tAfBrightPix;

    return 0;

}


AX_S32 sample_af_init_afiirref
(
    AX_U8                         pipe,
    AX_ISP_IQ_AF_IIR_REF_LIST_T *pAfRefListPara
)
{
    AX_S32 axRet;
    memcpy(pAfRefListPara, &af_iir_ref_list_param, sizeof(AX_ISP_IQ_AF_IIR_REF_LIST_T));

    axRet = AX_ISP_IQ_SetAfIirRefList(pipe, pAfRefListPara);
    if (0 != axRet)
    {
        printf("AX_ISP_GetAfAttr failed!\n");
        return -1;
    }
    return 0;
}

AX_S32 sample_af_init
(
    AX_U8                         pipe
)
{
    AX_S32 axRet;
    AX_ISP_IQ_AF_STAT_PARAM_T     tafStatParams;
    AX_ISP_IQ_AF_IIR_REF_LIST_T   tAfRefListPara;
    //DEF_AF_USED(af_itp_wbc_param_hdr);
    //DEF_AF_USED(af_itp_wbc_param_sdr);

    axRet = sample_af_init_afiirref(pipe, &tAfRefListPara);
    if (0 != axRet)
    {
        printf("sample_af_init_afiirref failed!\n");
        return -1;
    }
    axRet = sample_af_init_afparams(pipe, &tafStatParams, &af_stat_rltm_param);
    if (0 != axRet)
    {
        printf("sample_af_init_afparams failed!\n");
        return -1;
    }

    axRet = sample_af_init_afparams(pipe, &tafStatParams, &af_ife_param);
    if (0 != axRet)
    {
        printf("sample_af_init_afparams failed!\n");
        return -1;
    }

    axRet = AX_ISP_IQ_SetAfStatParam(pipe, &tafStatParams);
    if (0 != axRet)
    {
        printf("AX_ISP_IQ_SetAfStatParam failed!\n");
        return -1;
    }

    return 0;
}

AX_S32 sample_af_stats
(
    AX_U8                          pipe,
    AX_ISP_AF_STAT_INFO_T         *pAfStats,
    AX_ISP_IQ_AF_STAT_PARAM_T     *pAfParams,
    AfRes                         *Res
)
{
    AX_S32 axRet = 0;
    AX_U32 regions = 0;
    AX_U64 focusValue[STAT_NUM] = {0};
    AX_U64 pixSum[STAT_NUM] = {0};
    AX_U64 pixCount[STAT_NUM] = {0};

    AX_U64 focusValueAll = 0, lumaAll = 0;
    axRet = AX_ISP_IQ_GetAfStatistics(gCams[pipe].nPipeId, pAfStats);
    if (0 != axRet)
    {
        COMM_ISP_PRT("get pipe: 0 statistics failed!\n");
        return -1;
    }

    regions = (pAfStats->tAfStatInfo.nZoneColSize * pAfStats->tAfStatInfo.nZoneRowSize);

    for (int k = 0; k < regions; k++) {
        pixCount[V_STAT_1] += pAfStats->tAfStatInfo.tAfRoiV1[k].nPixCount;
        pixSum[V_STAT_1]  +=  pAfStats->tAfStatInfo.tAfRoiV1[k].nPixSum;
        focusValue[V_STAT_1] += pAfStats->tAfStatInfo.tAfRoiV1[k].nFocusValue;

        pixCount[V_STAT_2] += pAfStats->tAfStatInfo.tAfRoiV2[k].nPixCount;
        pixSum[V_STAT_2]  +=  pAfStats->tAfStatInfo.tAfRoiV2[k].nPixSum;
        focusValue[V_STAT_2] += pAfStats->tAfStatInfo.tAfRoiV2[k].nFocusValue;

        pixCount[H_STAT_1] += pAfStats->tAfStatInfo.tAfRoiH1[k].nPixCount;
        pixSum[H_STAT_1]  +=  pAfStats->tAfStatInfo.tAfRoiH1[k].nPixSum;
        focusValue[H_STAT_1] += pAfStats->tAfStatInfo.tAfRoiH1[k].nFocusValue;

        pixCount[H_STAT_2] += pAfStats->tAfStatInfo.tAfRoiH2[k].nPixCount;
        pixSum[H_STAT_2]  +=  pAfStats->tAfStatInfo.tAfRoiH2[k].nPixSum;
        focusValue[H_STAT_2] += pAfStats->tAfStatInfo.tAfRoiH2[k].nFocusValue;
    }

    for(int ind = 0; ind < STAT_NUM; ind++) {
        focusValueAll += focusValue[ind];
        lumaAll     += pixSum[ind] / DEF_AF_0_TO_1(pixCount[ind]);
        //COMM_ISP_PRT("ind:%d fv:%llu, pixCount:%llu, pixSum:%llu\n", ind, focusValue[ind], pixCount[ind], pixSum[ind]);
    }

    Res->V = focusValueAll / (STAT_NUM * regions);
    Res->Y = lumaAll / (STAT_NUM );

    return axRet;
}


AX_S32 sample_af_deinit(AX_U8 pipe)
{
    return 0;
}

void *AfRun(void *args)
{
    AX_U32 i = (AX_U32)(AX_ULONG)args;
    AX_ISP_AF_STAT_INFO_T afStat = {0};
    AX_S32 axRet = 0;
    AX_ISP_IQ_AF_STAT_PARAM_T tParams;
    AfRes Res;
    AX_U32 count =0;
    COMM_ISP_PRT("3A %d is running...\n", i);

    while (!gLoopExit) {
        if (gCams[i].bOpen) {
            axRet = AX_ISP_GetIrqTimeOut(gCams[i].nPipeId, 2, 200);
            if (axRet == 0) {

                axRet = sample_af_stats(gCams[i].nPipeId, &afStat, &tParams, &Res);
                if (0 == axRet) {
                    count ++;
                    if (count % 16 == 0)
                    {
                        COMM_PRT("AF[pipe=%d]:  Y: %llu   FV: %llu\n", gCams[i].nPipeId, Res.Y, Res.V);
                        count = 0;
                    }
                } else {
                    COMM_ISP_PRT("sample_af_stats failed\n");
                }
            }

        }

    }

    return NULL;
}