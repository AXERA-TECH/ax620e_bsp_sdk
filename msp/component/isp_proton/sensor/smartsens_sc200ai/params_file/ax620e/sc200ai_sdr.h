#ifndef __SC200AI_SDR_H__
#define __SC200AI_SDR_H__

/********************************************************************
* Store the default parameters of the sdr mode
* warn: user need to add 'static' when defining global variables.
        Limit the scope of the variable to this sensor
*********************************************************************/

#include "ax_isp_iq_api.h"
#include "ax_isp_api.h"


const static AX_ISP_VERSION_T ax_isp_version_param_sdr = {
    /* nIspMajor */
    4,
    /* nIspMinor1 */
    0,
    /* nIspMinor2 */
    31,
    /* szBuildTime[32] */
    "Nov  2 2023 18:10:29",
    /* szIspVersion[64] */
    "AX620E_ISP_V4.0.31",
};

const static AX_ISP_IQ_SCENE_PARAM_T scene_param_sdr = {
    /* nAutoMode */
    1,
    /* tManualParam */
    {
        /* nAiWorkMode */
        1,
    },
    /* tAutoParam */
    {
        /* nSceneNum */
        2,
        /* nDelta */
        4096,
        /* nRefValStart[4] */
        {1024, 28672, /*0 - 1*/},
        /* nRefValEnd[4] */
        {28672, 884736, /*0 - 1*/},
        /* nAiWorkMode[4] */
        {0, 1, /*0 - 1*/},
    },
};

const static AX_ISP_IQ_AE_PARAM_T ae_param_sdr = {
    /* nEnable */
    1,
    /* tExpManual */
    {
        /* nIspGain */
        1024,
        /* nAGain */
        1024,
        /* nDgain */
        1024,
        /* nHcgLcg */
        2,
        /* nSnsTotalAGain */
        1024,
        /* nSysTotalGain */
        1024,
        /* nShutter */
        10000,
        /* nIrisPwmDuty */
        0,
        /* nPos */
        512,
        /* nHdrRealRatioLtoS */
        1024,
        /* nHdrRealRatioStoVS */
        1024,
        /* nLumaHdrRealRatioLtoS */
        1024,
        /* nSetPoint */
        25600,
        /* nShortAgain */
        0,
        /* nShortDgain */
        0,
        /* nShortShutter */
        0,
        /* nVsAgain */
        0,
        /* nVsDgain */
        0,
        /* nVsShutter */
        0,
        /* nHdrRatio */
        1024,
        /* nHdrMaxShutterHwLimit */
        970755,
        /* nRealMaxShutter */
        39880,
    },
    /* tAeAlgAuto */
    {
        /* nSetPoint */
        25600,
        /* nFaceTarget */
        35840,
        /* nTolerance */
        10485760,
        /* nAgainLcg2HcgTh */
        15872,
        /* nAgainHcg2LcgTh */
        1228,
        /* nAgainLcg2HcgRatio */
        1024,
        /* nAgainHcg2LcgRatio */
        1024,
        /* nLuxk */
        46397,
        /* nCompensationMode */
        1,
        /* nMaxIspGain */
        16384,
        /* nMinIspGain */
        1024,
        /* nMaxUserDgain */
        1024,
        /* nMinUserDgain */
        1024,
        /* nMaxUserTotalAgain */
        55270,
        /* nMinUserTotalAgain */
        1024,
        /* nMaxUserSysGain */
        884320,
        /* nMinUserSysGain */
        1024,
        /* nMaxShutter */
        166000,
        /* nMinShutter */
        30,
        /* nPositionWeightMode */
        1,
        /* nRoiStartX */
        0,
        /* nRoiStartY */
        0,
        /* nRoiWidth */
        0,
        /* nRoiHeight */
        0,
        /* nWeightRoi */
        1024,
        /* nWeightBackgnd */
        1024,
        /* nGridWeightRow */
        15,
        /* nGridWeightColumn */
        17,
        /* nGridWeightTable[54][72] */
        {
            {139, 175, 215, 255, 293, 327, 354, 371, 377, 371, 354, 327, 293, 255, 215, 175, 139, /*0 - 16*/},
            {181, 228, 280, 332, 383, 427, 461, 484, 491, 484, 461, 427, 383, 332, 280, 228, 181, /*0 - 16*/},
            {226, 286, 350, 416, 479, 534, 578, 605, 615, 605, 578, 534, 479, 416, 350, 286, 226, /*0 - 16*/},
            {272, 344, 421, 500, 575, 642, 694, 727, 739, 727, 694, 642, 575, 500, 421, 344, 272, /*0 - 16*/},
            {313, 396, 486, 577, 664, 740, 801, 839, 852, 839, 801, 740, 664, 577, 486, 396, 313, /*0 - 16*/},
            {347, 439, 538, 639, 735, 820, 887, 929, 944, 929, 887, 820, 735, 639, 538, 439, 347, /*0 - 16*/},
            {369, 467, 572, 679, 781, 872, 943, 988, 1003, 988, 943, 872, 781, 679, 572, 467, 369, /*0 - 16*/},
            {377, 476, 583, 693, 797, 890, 962, 1008, 1024, 1008, 962, 890, 797, 693, 583, 476, 377, /*0 - 16*/},
            {369, 467, 572, 679, 781, 872, 943, 988, 1003, 988, 943, 872, 781, 679, 572, 467, 369, /*0 - 16*/},
            {347, 439, 538, 639, 735, 820, 887, 929, 944, 929, 887, 820, 735, 639, 538, 439, 347, /*0 - 16*/},
            {313, 396, 486, 577, 664, 740, 801, 839, 852, 839, 801, 740, 664, 577, 486, 396, 313, /*0 - 16*/},
            {272, 344, 421, 500, 575, 642, 694, 727, 739, 727, 694, 642, 575, 500, 421, 344, 272, /*0 - 16*/},
            {226, 286, 350, 416, 479, 534, 578, 605, 615, 605, 578, 534, 479, 416, 350, 286, 226, /*0 - 16*/},
            {181, 228, 280, 332, 383, 427, 461, 484, 491, 484, 461, 427, 383, 332, 280, 228, 181, /*0 - 16*/},
            {139, 175, 215, 255, 293, 327, 354, 371, 377, 371, 354, 327, 293, 255, 215, 175, 139, /*0 - 16*/},
        },
        /* tAntiFlickerParam */
        {
            /* nEnable */
            1,
            /* nFlickerPeriod */
            0,
            /* nAntiFlickerTolerance */
            150,
            /* nOverExpMode */
            1,
            /* nUnderExpMode */
            1,
        },
        /* nSetPointMode */
        2,
        /* nFaceTargetMode */
        0,
        /* nStrategyMode */
        2,
        /* tAeRouteParam */
        {
            /* nTableNum */
            2,
            /* nUsedTableId */
            0,
            /* tRouteTable[8] */
            {
                /* 0 */
                {
                    /* sTableName[32] */
                    "DefaultAeRoute",
                    /* nRouteCurveNum */
                    7,
                    /* tRouteCurveList[16] */
                    {
                        /* 0 */
                        {
                            /* nIntergrationTime */
                            40,
                            /* nGain */
                            1024,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 1 */
                        {
                            /* nIntergrationTime */
                            39880,
                            /* nGain */
                            8192,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 2 */
                        {
                            /* nIntergrationTime */
                            49850,
                            /* nGain */
                            24576,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 3 */
                        {
                            /* nIntergrationTime */
                            66000,
                            /* nGain */
                            40960,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 3 */
                        {
                            /* nIntergrationTime */
                            80000,
                            /* nGain */
                            81920,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 4 */
                        {
                            /* nIntergrationTime */
                            110000,
                            /* nGain */
                            163840,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 5 */
                        {
                            /* nIntergrationTime */
                            166000,
                            /* nGain */
                            884320,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                    },
                },
                /* 1 */
                {
                    /* sTableName[32] */
                    "PirisAeRoute",
                    /* nRouteCurveNum */
                    5,
                    /* tRouteCurveList[16] */
                    {
                        /* 0 */
                        {
                            /* nIntergrationTime */
                            40,
                            /* nGain */
                            1024,
                            /* nAperture */
                            5,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 1 */
                        {
                            /* nIntergrationTime */
                            40,
                            /* nGain */
                            1024,
                            /* nAperture */
                            296,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 2 */
                        {
                            /* nIntergrationTime */
                            166000,
                            /* nGain */
                            1024,
                            /* nAperture */
                            296,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 3 */
                        {
                            /* nIntergrationTime */
                            166000,
                            /* nGain */
                            1024,
                             /* nAperture */
                            512,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 4 */
                        {
                            /* nIntergrationTime */
                            166000,
                            /* nGain */
                            884320,
                            /* nAperture */
                            512,
                            /* nIncrementPriority */
                            0,
                        },
                    },
                },
            },
        },
        /* tAeSetPointCurve */
        {
            /* nSize */
            6,
            /* nRefList[10] */
            {512, 1536, 20480, 102400, 409600, 2048000, /*0 - 5*/},
            /* nSetPointList[10] */
            {16384, 18432, 20480, 24576, 27648, 30720, /*0 - 5*/},
        },
        /* tFaceUIParam */
        {
            /* nEnable */
            0,
            /* tFaceTargetCurve */
            {
                /* nSize */
                6,
                /* nRefList[10] */
                {102, 1536, 10240, 51200, 307200, 2048000, /*0 - 5*/},
                /* nFaceTargetList[10] */
                {18432, 18432, 18432, 22528, 25600, 25600, /*0 - 5*/},
            },
            /* nFaceScoreList[6] */
            {0, 205, 410, 614, 819, 1024, /*0 - 5*/},
            /* nFaceScoreWeightList[6] */
            {0, 205, 410, 614, 819, 1024, /*0 - 5*/},
            /* nFaceDistanceList[6] */
            {0, 205, 410, 614, 819, 1024, /*0 - 5*/},
            /* nFaceDistanceWeightList[6] */
            {1024, 922, 768, 563, 307, 0, /*0 - 5*/},
            /* nFaceTargetWeight */
            512,
            /* nNoFaceFrameTh */
            20,
            /* nToNormalFrameTh */
            8,
            /* nWithFaceFrameTh */
            3,
            /* nToFaceAeFrameTh */
            8,
            /* tFaceWeightList */
            {
                /* nSize */
                5,
                /* nFaceLumaDiff[5] */
                {2048, 5120, 10240, 15360, 20480, /*0 - 4*/},
                /* nFaceWeight[5] */
                {0, 102, 154, 154, 205, /*0 - 4*/},
            },
            /* nFaceWeightDampRatio */
            870,
            /* nToleranceAdjustRatio */
            2048,
            /* nNoFaceDampRatio */
            512,
        },
        /* tAeHdrRatio */
        {
            /* nHdrMode */
            0,
            /* tRatioStrategyParam */
            {
                /* nShortNonSatAreaPercent */
                104438168,
                /* nTolerance */
                8388608,
                /* nConvergeCntFrameNum */
                3,
                /* nDampRatio */
                922,
                /* tHdrRatioParamCurve */
                {
                    /* nListSize */
                    6,
                    /* nRefList[10] */
                    {102, 10240, 30720, 102400, 204800, 1024000, /*0 - 5*/},
                    /* nSatLumaList[10] */
                    {153600, 122880, 61440, 40960, 20480, 10240, /*0 - 5*/},
                    /* nMinRatioList[10] */
                    {1024, 1024, 1024, 1024, 1024, 1024, /*0 - 5*/},
                    /* nMaxRatioList[10] */
                    {32768, 32768, 32768, 32768, 32768, 32768, /*0 - 5*/},
                },
            },
            /* nFixedHdrRatio */
            1024,
        },
        /* nMultiCamSyncMode */
        0,
        /* nMultiCamSyncRatio */
        1048576,
        /* tSlowShutterParam */
        {
            /* nFrameRateMode */
            1,
            /* nFpsIncreaseDelayFrame */
            0,
        },
        /* tIrisParam */
        {
            /* nIrisType */
            0,
            /* tDcIrisParam */
            {
                /* nBigStepFactor */
                104858,
                /* nSmallStepFactor */
                10486,
                /* nLumaDiffOverThresh */
                35840,
                /* nLumaDiffUnderThresh */
                35840,
                /* nLumaSpeedThresh */
                205,
                /* nSpeedDownFactor */
                209715,
                /* nMinUserPwmDuty */
                30720,
                /* nMaxUserPwmDuty */
                66560,
                /* nOpenPwmDuty */
                61440,
                /* nConvergeLumaDiffTolerance */
                52429,
                /* nConvergeFrameCntThresh */
                10,
            },
        },
        /* tLumaWeightParam */
        {
            /* nEnable */
            0,
            /* nLumaWeightNum */
            16,
            /* nLumaSplitList[64] */
            {0, 16384, 32768, 49152, 65535, 81920, 98304, 114688, 131072, 147456, 163840, 180224, 196608, 212992, 229376, 245760, /*0 - 15*/},
            /* nWeightList[64] */
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 15*/},
        },
        /* tTimeSmoothParam */
        {
            /* tStateMachineParam */
            {
                /* nToFastLumaThOver */
                1536,
                /* nToFastLumaThUnder */
                819,
                /* nToSlowFrameTh */
                8,
                /* nToConvergedFrameTh */
                2,
            },
            /* tConvergeSpeedParam */
            {
                /* nFastOverKneeCnt */
                14,
                /* nFastOverLumaDiffList[16] */
                {5120, 10240, 15360, 20480, 25600, 30720, 40960, 51200, 71680, 92160, 112640, 153600, 209920, 262144, /*0 - 13*/},
                /* nFastOverStepFactorList[16] */
                {102, 154, 184, 184, 205, 205, 205, 205, 256, 307, 358, 410, 512, 614, /*0 - 13*/},
                /* nFastOverSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 102, 102, 307, /*0 - 13*/},
                /* nFastOverSkipList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 13*/},
                /* nFastUnderKneeCnt */
                11,
                /* nFastUnderLumaDiffList[16] */
                {5120, 10240, 15360, 20480, 25600, 30720, 35840, 40960, 51200, 153600, 262144, /*0 - 10*/},
                /* nFastUnderStepFactorList[16] */
                {102, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, /*0 - 10*/},
                /* nFastUnderSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 10*/},
                /* nFastUnderSkipList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 10*/},
                /* nSlowOverKneeCnt */
                14,
                /* nSlowOverLumaDiffList[16] */
                {5120, 10240, 15360, 20480, 25600, 30720, 40960, 51200, 81920, 92160, 112640, 153600, 209920, 262144, /*0 - 13*/},
                /* nSlowOverStepFactorList[16] */
                {82, 102, 123, 154, 154, 174, 184, 184, 184, 184, 184, 184, 184, 184, /*0 - 13*/},
                /* nSlowOverSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 13*/},
                /* nSlowOverSkipList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 13*/},
                /* nSlowUnderKneeCnt */
                11,
                /* nSlowUnderLumaDiffList[16] */
                {5120, 10240, 15360, 20480, 25600, 30720, 35840, 40960, 51200, 153600, 262144, /*0 - 10*/},
                /* nSlowUnderStepFactorList[16] */
                {123, 154, 154, 154, 154, 154, 154, 154, 154, 154, 154, /*0 - 10*/},
                /* nSlowUnderSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 10*/},
                /* nSlowUnderSkipList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 10*/},
            },
        },
        /* tSleepWakeUpParam */
        {
            /* nEnableSleepSetting */
            0,
            /* nNoiseLevel */
            41,
            /* nLinearLumaTh */
            51,
            /* nAeStatsDelayFrame */
            4,
            /* tSleepSetting */
            {
                /* nAGain */
                1024,
                /* nDGain */
                1024,
                /* nIspGain */
                1024,
                /* nHcgLcg */
                1,
                /* nShutter */
                1000,
            },
            /* nOverExpCompLumaTh */
            102400,
            /* tOverExpCompLut */
            {
                /* nLutNum */
                5,
                /* nLumaSplitList[8] */
                {179200, 220160, 225280, 240640, 244736, /*0 - 4*/},
                /* nCompFactorList[8] */
                {1024, 1208, 1352, 2324, 2560, /*0 - 4*/},
            },
        },
        /* tHistPointCtrlParam */
        {
            /* nEnable */
            0,
            /* nHistPointLutNum */
            1,
            /* tHistPointCtrlLut[10] */
            {
                /* 0 */
                {
                    /* nLuxStart */
                    102400,
                    /* nLuxEnd */
                    204800,
                    /* tHistPointTh */
                    {
                        /* nLumaThList[2] */
                        {0, 0, /*0 - 1*/},
                        /* nPercentThList[2] */
                        {102400, 102400, /*0 - 1*/},
                    },
                },
            },
        },
    },
    /* nLogLevel */
    4,
    /* nLogTarget */
    2,
};

const static AX_ISP_IQ_AWB_PARAM_T awb_param_sdr = {
    /* nEnable */
    1,
    /* tManualParam */
    {
        /* nManualMode */
        0,
        /* tGain */
        {
            /* nGainR */
            442,
            /* nGainGr */
            256,
            /* nGainGb */
            256,
            /* nGainB */
            630,
        },
        /* tManualLightSource */
        {
            /* nLightSourceIndex */
            0,
            /* tLightSource[15] */
            {
                /* 0 */
                {
                    /* szName[32] */
                    "Shade",
                    /* nColorTemperature */
                    7500,
                    /* nGreenShift */
                    0,
                },
                /* 1 */
                {
                    /* szName[32] */
                    "Day",
                    /* nColorTemperature */
                    6500,
                    /* nGreenShift */
                    0,
                },
                /* 2 */
                {
                    /* szName[32] */
                    "Cloudy",
                    /* nColorTemperature */
                    5000,
                    /* nGreenShift */
                    0,
                },
                /* 3 */
                {
                    /* szName[32] */
                    "Flourescent",
                    /* nColorTemperature */
                    5000,
                    /* nGreenShift */
                    0,
                },
                /* 4 */
                {
                    /* szName[32] */
                    "Sunset",
                    /* nColorTemperature */
                    3500,
                    /* nGreenShift */
                    0,
                },
                /* 5 */
                {
                    /* szName[32] */
                    "Incandescent",
                    /* nColorTemperature */
                    2800,
                    /* nGreenShift */
                    0,
                },
                /* 6 */
                {
                    /* szName[32] */
                    "Candle",
                    /* nColorTemperature */
                    2000,
                    /* nGreenShift */
                    0,
                },
                /* 7 */
                {
                    /* szName[32] */
                    "Flash",
                    /* nColorTemperature */
                    3500,
                    /* nGreenShift */
                    0,
                },
                /* 8 */
                {
                    /* szName[32] */
                    "UserDefined-1",
                    /* nColorTemperature */
                    2800,
                    /* nGreenShift */
                    0,
                },
                /* 9 */
                {
                    /* szName[32] */
                    "UserDefined-2",
                    /* nColorTemperature */
                    2000,
                    /* nGreenShift */
                    0,
                },
                /* 10 */
                {
                    /* szName[32] */
                    "UserDefined-3",
                    /* nColorTemperature */
                    5000,
                    /* nGreenShift */
                    0,
                },
                /* 11 */
                {
                    /* szName[32] */
                    "UserDefined-4",
                    /* nColorTemperature */
                    5000,
                    /* nGreenShift */
                    0,
                },
                /* 12 */
                {
                    /* szName[32] */
                    "UserDefined-5",
                    /* nColorTemperature */
                    5000,
                    /* nGreenShift */
                    0,
                },
                /* 13 */
                {
                    /* szName[32] */
                    "UserDefined-6",
                    /* nColorTemperature */
                    5000,
                    /* nGreenShift */
                    0,
                },
                /* 14 */
                {
                    /* szName[32] */
                    "UserDefined-7",
                    /* nColorTemperature */
                    5000,
                    /* nGreenShift */
                    0,
                },
            },
        },
    },
    /* tAutoParam */
    {
        /* tCenterPnt */
        {
            /* nRg */
            1405966,
            /* nBg */
            1496629,
        },
        /* nCenterPntRadius */
        1255491,
        /* nLowCut */
        0,
        /* nHighCut */
        0,
        /* nCctMax */
        12000,
        /* nCctMin */
        1100,
        /* nPartCtrlPntNum */
        8,
        /* nCtrlPntNum */
        57,
        /* nCtrlSegKbNum */
        56,
        /* nCctList[512] */
        {
            1100, 1250, 1400, 1550, 1700, 1850, 2000, 2150, 2300, 2362, 2425, 2487, 2550, 2612, 2675, 2737, 2800, 2925, 3050, 3175, 3300, 3425, 3550, 3675, 3800, 3950, 4100, 4250, 4400, 4550, 4700, 4850,  /* 0 - 31*/
            5000, 5187, 5375, 5562, 5750, 5937, 6125, 6312, 6500, 6625, 6750, 6875, 7000, 7125, 7250, 7375, 7500, 8062, 8625, 9187, 9750, 10312, 10875, 11437, 12000, /*32 - 56*/
        },
        /* tChordKB */
        {
            /* nK */
            -562,
            /* nB */
            1228,
        },
        /* tChordPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1756742,
                /* nBg */
                291137,
            },
            /* 1 */
            {
                /* nRg */
                1666292,
                /* nBg */
                340913,
            },
            /* 2 */
            {
                /* nRg */
                1585216,
                /* nBg */
                385530,
            },
            /* 3 */
            {
                /* nRg */
                1511585,
                /* nBg */
                426047,
            },
            /* 4 */
            {
                /* nRg */
                1443931,
                /* nBg */
                463271,
            },
            /* 5 */
            {
                /* nRg */
                1381111,
                /* nBg */
                497843,
            },
            /* 6 */
            {
                /* nRg */
                1322170,
                /* nBg */
                530275,
            },
            /* 7 */
            {
                /* nRg */
                1266365,
                /* nBg */
                560978,
            },
            /* 8 */
            {
                /* nRg */
                1213066,
                /* nBg */
                590306,
            },
            /* 9 */
            {
                /* nRg */
                1191455,
                /* nBg */
                602197,
            },
            /* 10 */
            {
                /* nRg */
                1170148,
                /* nBg */
                613920,
            },
            /* 11 */
            {
                /* nRg */
                1149113,
                /* nBg */
                625497,
            },
            /* 12 */
            {
                /* nRg */
                1128310,
                /* nBg */
                636947,
            },
            /* 13 */
            {
                /* nRg */
                1107716,
                /* nBg */
                648282,
            },
            /* 14 */
            {
                /* nRg */
                1087300,
                /* nBg */
                659512,
            },
            /* 15 */
            {
                /* nRg */
                1067020,
                /* nBg */
                670669,
            },
            /* 16 */
            {
                /* nRg */
                1046867,
                /* nBg */
                681763,
            },
            /* 17 */
            {
                /* nRg */
                1024805,
                /* nBg */
                693906,
            },
            /* 18 */
            {
                /* nRg */
                1002827,
                /* nBg */
                705996,
            },
            /* 19 */
            {
                /* nRg */
                980880,
                /* nBg */
                718075,
            },
            /* 20 */
            {
                /* nRg */
                958933,
                /* nBg */
                730144,
            },
            /* 21 */
            {
                /* nRg */
                936966,
                /* nBg */
                742235,
            },
            /* 22 */
            {
                /* nRg */
                914925,
                /* nBg */
                754367,
            },
            /* 23 */
            {
                /* nRg */
                892789,
                /* nBg */
                766551,
            },
            /* 24 */
            {
                /* nRg */
                870507,
                /* nBg */
                778809,
            },
            /* 25 */
            {
                /* nRg */
                858637,
                /* nBg */
                785341,
            },
            /* 26 */
            {
                /* nRg */
                846715,
                /* nBg */
                791906,
            },
            /* 27 */
            {
                /* nRg */
                834729,
                /* nBg */
                798501,
            },
            /* 28 */
            {
                /* nRg */
                822671,
                /* nBg */
                805128,
            },
            /* 29 */
            {
                /* nRg */
                810549,
                /* nBg */
                811808,
            },
            /* 30 */
            {
                /* nRg */
                798344,
                /* nBg */
                818518,
            },
            /* 31 */
            {
                /* nRg */
                786055,
                /* nBg */
                825282,
            },
            /* 32 */
            {
                /* nRg */
                773671,
                /* nBg */
                832097,
            },
            /* 33 */
            {
                /* nRg */
                763951,
                /* nBg */
                837445,
            },
            /* 34 */
            {
                /* nRg */
                754178,
                /* nBg */
                842824,
            },
            /* 35 */
            {
                /* nRg */
                744332,
                /* nBg */
                848235,
            },
            /* 36 */
            {
                /* nRg */
                734423,
                /* nBg */
                853698,
            },
            /* 37 */
            {
                /* nRg */
                724430,
                /* nBg */
                859193,
            },
            /* 38 */
            {
                /* nRg */
                714374,
                /* nBg */
                864729,
            },
            /* 39 */
            {
                /* nRg */
                704224,
                /* nBg */
                870308,
            },
            /* 40 */
            {
                /* nRg */
                694000,
                /* nBg */
                875938,
            },
            /* 41 */
            {
                /* nRg */
                685244,
                /* nBg */
                880751,
            },
            /* 42 */
            {
                /* nRg */
                676426,
                /* nBg */
                885606,
            },
            /* 43 */
            {
                /* nRg */
                667544,
                /* nBg */
                890493,
            },
            /* 44 */
            {
                /* nRg */
                658579,
                /* nBg */
                895421,
            },
            /* 45 */
            {
                /* nRg */
                649551,
                /* nBg */
                900391,
            },
            /* 46 */
            {
                /* nRg */
                640449,
                /* nBg */
                905403,
            },
            /* 47 */
            {
                /* nRg */
                631264,
                /* nBg */
                910458,
            },
            /* 48 */
            {
                /* nRg */
                621994,
                /* nBg */
                915564,
            },
            /* 49 */
            {
                /* nRg */
                579202,
                /* nBg */
                939105,
            },
            /* 50 */
            {
                /* nRg */
                534407,
                /* nBg */
                963757,
            },
            /* 51 */
            {
                /* nRg */
                487263,
                /* nBg */
                989698,
            },
            /* 52 */
            {
                /* nRg */
                437393,
                /* nBg */
                1017140,
            },
            /* 53 */
            {
                /* nRg */
                384335,
                /* nBg */
                1046332,
            },
            /* 54 */
            {
                /* nRg */
                327533,
                /* nBg */
                1077590,
            },
            /* 55 */
            {
                /* nRg */
                266317,
                /* nBg */
                1111281,
            },
            /* 56 */
            {
                /* nRg */
                199901,
                /* nBg */
                1147824,
            },
        },
        /* tArcPointList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1733307,
                /* nBg */
                371678,
            },
            /* 1 */
            {
                /* nRg */
                1664572,
                /* nBg */
                348547,
            },
            /* 2 */
            {
                /* nRg */
                1594234,
                /* nBg */
                329630,
            },
            /* 3 */
            {
                /* nRg */
                1522532,
                /* nBg */
                315034,
            },
            /* 4 */
            {
                /* nRg */
                1449751,
                /* nBg */
                304853,
            },
            /* 5 */
            {
                /* nRg */
                1376162,
                /* nBg */
                299180,
            },
            /* 6 */
            {
                /* nRg */
                1302038,
                /* nBg */
                298068,
            },
            /* 7 */
            {
                /* nRg */
                1227662,
                /* nBg */
                301549,
            },
            /* 8 */
            {
                /* nRg */
                1153329,
                /* nBg */
                309665,
            },
            /* 9 */
            {
                /* nRg */
                1121725,
                /* nBg */
                311448,
            },
            /* 10 */
            {
                /* nRg */
                1090037,
                /* nBg */
                314069,
            },
            /* 11 */
            {
                /* nRg */
                1058307,
                /* nBg */
                317540,
            },
            /* 12 */
            {
                /* nRg */
                1026545,
                /* nBg */
                321860,
            },
            /* 13 */
            {
                /* nRg */
                994784,
                /* nBg */
                327040,
            },
            /* 14 */
            {
                /* nRg */
                963033,
                /* nBg */
                333080,
            },
            /* 15 */
            {
                /* nRg */
                931314,
                /* nBg */
                339980,
            },
            /* 16 */
            {
                /* nRg */
                899668,
                /* nBg */
                347750,
            },
            /* 17 */
            {
                /* nRg */
                867445,
                /* nBg */
                362493,
            },
            /* 18 */
            {
                /* nRg */
                835652,
                /* nBg */
                378148,
            },
            /* 19 */
            {
                /* nRg */
                804310,
                /* nBg */
                394694,
            },
            /* 20 */
            {
                /* nRg */
                773451,
                /* nBg */
                412111,
            },
            /* 21 */
            {
                /* nRg */
                743094,
                /* nBg */
                430399,
            },
            /* 22 */
            {
                /* nRg */
                713262,
                /* nBg */
                449525,
            },
            /* 23 */
            {
                /* nRg */
                683986,
                /* nBg */
                469500,
            },
            /* 24 */
            {
                /* nRg */
                655287,
                /* nBg */
                490283,
            },
            /* 25 */
            {
                /* nRg */
                640323,
                /* nBg */
                501618,
            },
            /* 26 */
            {
                /* nRg */
                625528,
                /* nBg */
                513184,
            },
            /* 27 */
            {
                /* nRg */
                610900,
                /* nBg */
                524959,
            },
            /* 28 */
            {
                /* nRg */
                596461,
                /* nBg */
                536965,
            },
            /* 29 */
            {
                /* nRg */
                582201,
                /* nBg */
                549171,
            },
            /* 30 */
            {
                /* nRg */
                568129,
                /* nBg */
                561596,
            },
            /* 31 */
            {
                /* nRg */
                554235,
                /* nBg */
                574232,
            },
            /* 32 */
            {
                /* nRg */
                540541,
                /* nBg */
                587077,
            },
            /* 33 */
            {
                /* nRg */
                529992,
                /* nBg */
                597227,
            },
            /* 34 */
            {
                /* nRg */
                519569,
                /* nBg */
                607493,
            },
            /* 35 */
            {
                /* nRg */
                509272,
                /* nBg */
                617884,
            },
            /* 36 */
            {
                /* nRg */
                499091,
                /* nBg */
                628391,
            },
            /* 37 */
            {
                /* nRg */
                489035,
                /* nBg */
                639023,
            },
            /* 38 */
            {
                /* nRg */
                479105,
                /* nBg */
                649761,
            },
            /* 39 */
            {
                /* nRg */
                469290,
                /* nBg */
                660624,
            },
            /* 40 */
            {
                /* nRg */
                459612,
                /* nBg */
                671602,
            },
            /* 41 */
            {
                /* nRg */
                451496,
                /* nBg */
                681008,
            },
            /* 42 */
            {
                /* nRg */
                443464,
                /* nBg */
                690487,
            },
            /* 43 */
            {
                /* nRg */
                435537,
                /* nBg */
                700061,
            },
            /* 44 */
            {
                /* nRg */
                427704,
                /* nBg */
                709697,
            },
            /* 45 */
            {
                /* nRg */
                419965,
                /* nBg */
                719418,
            },
            /* 46 */
            {
                /* nRg */
                412321,
                /* nBg */
                729222,
            },
            /* 47 */
            {
                /* nRg */
                404771,
                /* nBg */
                739089,
            },
            /* 48 */
            {
                /* nRg */
                397326,
                /* nBg */
                749040,
            },
            /* 49 */
            {
                /* nRg */
                365041,
                /* nBg */
                794684,
            },
            /* 50 */
            {
                /* nRg */
                334810,
                /* nBg */
                841734,
            },
            /* 51 */
            {
                /* nRg */
                306719,
                /* nBg */
                890073,
            },
            /* 52 */
            {
                /* nRg */
                280798,
                /* nBg */
                939618,
            },
            /* 53 */
            {
                /* nRg */
                257121,
                /* nBg */
                990265,
            },
            /* 54 */
            {
                /* nRg */
                235709,
                /* nBg */
                1041918,
            },
            /* 55 */
            {
                /* nRg */
                216625,
                /* nBg */
                1094472,
            },
            /* 56 */
            {
                /* nRg */
                199901,
                /* nBg */
                1147824,
            },
        },
        /* tRadiusLineList[512] */
        {
            /* 0 */
            {
                /* nK */
                -3518,
                /* nB */
                6180,
            },
            /* 1 */
            {
                /* nK */
                -4545,
                /* nB */
                7557,
            },
            /* 2 */
            {
                /* nK */
                -6346,
                /* nB */
                9972,
            },
            /* 3 */
            {
                /* nK */
                -10379,
                /* nB */
                15379,
            },
            /* 4 */
            {
                /* nK */
                -27869,
                /* nB */
                38830,
            },
            /* 5 */
            {
                /* nK */
                41142,
                /* nB */
                -53702,
            },
            /* 6 */
            {
                /* nK */
                11809,
                /* nB */
                -14372,
            },
            /* 7 */
            {
                /* nK */
                6863,
                /* nB */
                -7740,
            },
            /* 8 */
            {
                /* nK */
                4811,
                /* nB */
                -4988,
            },
            /* 9 */
            {
                /* nK */
                4270,
                /* nB */
                -4262,
            },
            /* 10 */
            {
                /* nK */
                3833,
                /* nB */
                -3677,
            },
            /* 11 */
            {
                /* nK */
                3473,
                /* nB */
                -3194,
            },
            /* 12 */
            {
                /* nK */
                3171,
                /* nB */
                -2789,
            },
            /* 13 */
            {
                /* nK */
                2913,
                /* nB */
                -2443,
            },
            /* 14 */
            {
                /* nK */
                2690,
                /* nB */
                -2144,
            },
            /* 15 */
            {
                /* nK */
                2495,
                /* nB */
                -1883,
            },
            /* 16 */
            {
                /* nK */
                2324,
                /* nB */
                -1653,
            },
            /* 17 */
            {
                /* nK */
                2157,
                /* nB */
                -1429,
            },
            /* 18 */
            {
                /* nK */
                2008,
                /* nB */
                -1230,
            },
            /* 19 */
            {
                /* nK */
                1875,
                /* nB */
                -1052,
            },
            /* 20 */
            {
                /* nK */
                1756,
                /* nB */
                -892,
            },
            /* 21 */
            {
                /* nK */
                1647,
                /* nB */
                -746,
            },
            /* 22 */
            {
                /* nK */
                1548,
                /* nB */
                -613,
            },
            /* 23 */
            {
                /* nK */
                1457,
                /* nB */
                -491,
            },
            /* 24 */
            {
                /* nK */
                1373,
                /* nB */
                -378,
            },
            /* 25 */
            {
                /* nK */
                1331,
                /* nB */
                -322,
            },
            /* 26 */
            {
                /* nK */
                1290,
                /* nB */
                -268,
            },
            /* 27 */
            {
                /* nK */
                1251,
                /* nB */
                -215,
            },
            /* 28 */
            {
                /* nK */
                1214,
                /* nB */
                -165,
            },
            /* 29 */
            {
                /* nK */
                1178,
                /* nB */
                -117,
            },
            /* 30 */
            {
                /* nK */
                1143,
                /* nB */
                -70,
            },
            /* 31 */
            {
                /* nK */
                1109,
                /* nB */
                -24,
            },
            /* 32 */
            {
                /* nK */
                1076,
                /* nB */
                19,
            },
            /* 33 */
            {
                /* nK */
                1051,
                /* nB */
                52,
            },
            /* 34 */
            {
                /* nK */
                1027,
                /* nB */
                84,
            },
            /* 35 */
            {
                /* nK */
                1003,
                /* nB */
                116,
            },
            /* 36 */
            {
                /* nK */
                980,
                /* nB */
                147,
            },
            /* 37 */
            {
                /* nK */
                958,
                /* nB */
                177,
            },
            /* 38 */
            {
                /* nK */
                936,
                /* nB */
                207,
            },
            /* 39 */
            {
                /* nK */
                914,
                /* nB */
                236,
            },
            /* 40 */
            {
                /* nK */
                893,
                /* nB */
                265,
            },
            /* 41 */
            {
                /* nK */
                875,
                /* nB */
                288,
            },
            /* 42 */
            {
                /* nK */
                858,
                /* nB */
                312,
            },
            /* 43 */
            {
                /* nK */
                841,
                /* nB */
                335,
            },
            /* 44 */
            {
                /* nK */
                824,
                /* nB */
                357,
            },
            /* 45 */
            {
                /* nK */
                807,
                /* nB */
                379,
            },
            /* 46 */
            {
                /* nK */
                791,
                /* nB */
                401,
            },
            /* 47 */
            {
                /* nK */
                775,
                /* nB */
                423,
            },
            /* 48 */
            {
                /* nK */
                759,
                /* nB */
                444,
            },
            /* 49 */
            {
                /* nK */
                691,
                /* nB */
                536,
            },
            /* 50 */
            {
                /* nK */
                626,
                /* nB */
                622,
            },
            /* 51 */
            {
                /* nK */
                565,
                /* nB */
                704,
            },
            /* 52 */
            {
                /* nK */
                507,
                /* nB */
                782,
            },
            /* 53 */
            {
                /* nK */
                451,
                /* nB */
                856,
            },
            /* 54 */
            {
                /* nK */
                398,
                /* nB */
                928,
            },
            /* 55 */
            {
                /* nK */
                346,
                /* nB */
                997,
            },
            /* 56 */
            {
                /* nK */
                296,
                /* nB */
                1064,
            },
        },
        /* tInLeftBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1759678,
                /* nBg */
                281071,
            },
            /* 1 */
            {
                /* nRg */
                1685313,
                /* nBg */
                256482,
            },
            /* 2 */
            {
                /* nRg */
                1609260,
                /* nBg */
                236454,
            },
            /* 3 */
            {
                /* nRg */
                1531802,
                /* nBg */
                221113,
            },
            /* 4 */
            {
                /* nRg */
                1453221,
                /* nBg */
                210544,
            },
            /* 5 */
            {
                /* nRg */
                1373813,
                /* nBg */
                204839,
            },
            /* 6 */
            {
                /* nRg */
                1293880,
                /* nBg */
                204042,
            },
            /* 7 */
            {
                /* nRg */
                1213737,
                /* nBg */
                208216,
            },
            /* 8 */
            {
                /* nRg */
                1133678,
                /* nBg */
                217370,
            },
            /* 9 */
            {
                /* nRg */
                1099715,
                /* nBg */
                219677,
            },
            /* 10 */
            {
                /* nRg */
                1065689,
                /* nBg */
                222896,
            },
            /* 11 */
            {
                /* nRg */
                1031621,
                /* nBg */
                227017,
            },
            /* 12 */
            {
                /* nRg */
                997542,
                /* nBg */
                232060,
            },
            /* 13 */
            {
                /* nRg */
                963484,
                /* nBg */
                238006,
            },
            /* 14 */
            {
                /* nRg */
                929458,
                /* nBg */
                244884,
            },
            /* 15 */
            {
                /* nRg */
                895494,
                /* nBg */
                252675,
            },
            /* 16 */
            {
                /* nRg */
                861615,
                /* nBg */
                261389,
            },
            /* 17 */
            {
                /* nRg */
                826970,
                /* nBg */
                277243,
            },
            /* 18 */
            {
                /* nRg */
                792786,
                /* nBg */
                294073,
            },
            /* 19 */
            {
                /* nRg */
                759085,
                /* nBg */
                311857,
            },
            /* 20 */
            {
                /* nRg */
                725908,
                /* nBg */
                330585,
            },
            /* 21 */
            {
                /* nRg */
                693266,
                /* nBg */
                350245,
            },
            /* 22 */
            {
                /* nRg */
                661190,
                /* nBg */
                370818,
            },
            /* 23 */
            {
                /* nRg */
                629712,
                /* nBg */
                392293,
            },
            /* 24 */
            {
                /* nRg */
                598852,
                /* nBg */
                414638,
            },
            /* 25 */
            {
                /* nRg */
                582767,
                /* nBg */
                426833,
            },
            /* 26 */
            {
                /* nRg */
                566860,
                /* nBg */
                439259,
            },
            /* 27 */
            {
                /* nRg */
                551142,
                /* nBg */
                451926,
            },
            /* 28 */
            {
                /* nRg */
                535613,
                /* nBg */
                464823,
            },
            /* 29 */
            {
                /* nRg */
                520282,
                /* nBg */
                477962,
            },
            /* 30 */
            {
                /* nRg */
                505141,
                /* nBg */
                491321,
            },
            /* 31 */
            {
                /* nRg */
                490209,
                /* nBg */
                504900,
            },
            /* 32 */
            {
                /* nRg */
                475487,
                /* nBg */
                518710,
            },
            /* 33 */
            {
                /* nRg */
                464152,
                /* nBg */
                529615,
            },
            /* 34 */
            {
                /* nRg */
                452943,
                /* nBg */
                540656,
            },
            /* 35 */
            {
                /* nRg */
                441870,
                /* nBg */
                551834,
            },
            /* 36 */
            {
                /* nRg */
                430923,
                /* nBg */
                563127,
            },
            /* 37 */
            {
                /* nRg */
                420112,
                /* nBg */
                574557,
            },
            /* 38 */
            {
                /* nRg */
                409427,
                /* nBg */
                586112,
            },
            /* 39 */
            {
                /* nRg */
                398889,
                /* nBg */
                597783,
            },
            /* 40 */
            {
                /* nRg */
                388476,
                /* nBg */
                609579,
            },
            /* 41 */
            {
                /* nRg */
                379752,
                /* nBg */
                619698,
            },
            /* 42 */
            {
                /* nRg */
                371123,
                /* nBg */
                629901,
            },
            /* 43 */
            {
                /* nRg */
                362598,
                /* nBg */
                640177,
            },
            /* 44 */
            {
                /* nRg */
                354167,
                /* nBg */
                650547,
            },
            /* 45 */
            {
                /* nRg */
                345841,
                /* nBg */
                661001,
            },
            /* 46 */
            {
                /* nRg */
                337631,
                /* nBg */
                671529,
            },
            /* 47 */
            {
                /* nRg */
                329515,
                /* nBg */
                682151,
            },
            /* 48 */
            {
                /* nRg */
                321504,
                /* nBg */
                692847,
            },
            /* 49 */
            {
                /* nRg */
                286796,
                /* nBg */
                741920,
            },
            /* 50 */
            {
                /* nRg */
                254301,
                /* nBg */
                792503,
            },
            /* 51 */
            {
                /* nRg */
                224091,
                /* nBg */
                844481,
            },
            /* 52 */
            {
                /* nRg */
                196231,
                /* nBg */
                897749,
            },
            /* 53 */
            {
                /* nRg */
                170761,
                /* nBg */
                952201,
            },
            /* 54 */
            {
                /* nRg */
                147744,
                /* nBg */
                1007734,
            },
            /* 55 */
            {
                /* nRg */
                127224,
                /* nBg */
                1064242,
            },
            /* 56 */
            {
                /* nRg */
                109241,
                /* nBg */
                1121609,
            },
        },
        /* tInRightBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1709871,
                /* nBg */
                452230,
            },
            /* 1 */
            {
                /* nRg */
                1646138,
                /* nBg */
                430378,
            },
            /* 2 */
            {
                /* nRg */
                1580875,
                /* nBg */
                412447,
            },
            /* 3 */
            {
                /* nRg */
                1514301,
                /* nBg */
                398511,
            },
            /* 4 */
            {
                /* nRg */
                1446678,
                /* nBg */
                388686,
            },
            /* 5 */
            {
                /* nRg */
                1378248,
                /* nBg */
                383045,
            },
            /* 6 */
            {
                /* nRg */
                1309283,
                /* nBg */
                381640,
            },
            /* 7 */
            {
                /* nRg */
                1240046,
                /* nBg */
                384523,
            },
            /* 8 */
            {
                /* nRg */
                1170788,
                /* nBg */
                391717,
            },
            /* 9 */
            {
                /* nRg */
                1141291,
                /* nBg */
                393017,
            },
            /* 10 */
            {
                /* nRg */
                1111690,
                /* nBg */
                395114,
            },
            /* 11 */
            {
                /* nRg */
                1082036,
                /* nBg */
                397998,
            },
            /* 12 */
            {
                /* nRg */
                1052330,
                /* nBg */
                401688,
            },
            /* 13 */
            {
                /* nRg */
                1022603,
                /* nBg */
                406176,
            },
            /* 14 */
            {
                /* nRg */
                992876,
                /* nBg */
                411482,
            },
            /* 15 */
            {
                /* nRg */
                963169,
                /* nBg */
                417585,
            },
            /* 16 */
            {
                /* nRg */
                933495,
                /* nBg */
                424516,
            },
            /* 17 */
            {
                /* nRg */
                903432,
                /* nBg */
                438273,
            },
            /* 18 */
            {
                /* nRg */
                873757,
                /* nBg */
                452880,
            },
            /* 19 */
            {
                /* nRg */
                844513,
                /* nBg */
                468315,
            },
            /* 20 */
            {
                /* nRg */
                815708,
                /* nBg */
                484568,
            },
            /* 21 */
            {
                /* nRg */
                787386,
                /* nBg */
                501639,
            },
            /* 22 */
            {
                /* nRg */
                759547,
                /* nBg */
                519486,
            },
            /* 23 */
            {
                /* nRg */
                732221,
                /* nBg */
                538119,
            },
            /* 24 */
            {
                /* nRg */
                705440,
                /* nBg */
                557517,
            },
            /* 25 */
            {
                /* nRg */
                691473,
                /* nBg */
                568098,
            },
            /* 26 */
            {
                /* nRg */
                677674,
                /* nBg */
                578887,
            },
            /* 27 */
            {
                /* nRg */
                664021,
                /* nBg */
                589887,
            },
            /* 28 */
            {
                /* nRg */
                650547,
                /* nBg */
                601086,
            },
            /* 29 */
            {
                /* nRg */
                637241,
                /* nBg */
                612484,
            },
            /* 30 */
            {
                /* nRg */
                624102,
                /* nBg */
                624070,
            },
            /* 31 */
            {
                /* nRg */
                611142,
                /* nBg */
                635867,
            },
            /* 32 */
            {
                /* nRg */
                598359,
                /* nBg */
                647842,
            },
            /* 33 */
            {
                /* nRg */
                588524,
                /* nBg */
                657321,
            },
            /* 34 */
            {
                /* nRg */
                578793,
                /* nBg */
                666905,
            },
            /* 35 */
            {
                /* nRg */
                569188,
                /* nBg */
                676594,
            },
            /* 36 */
            {
                /* nRg */
                559688,
                /* nBg */
                686408,
            },
            /* 37 */
            {
                /* nRg */
                550293,
                /* nBg */
                696317,
            },
            /* 38 */
            {
                /* nRg */
                541034,
                /* nBg */
                706352,
            },
            /* 39 */
            {
                /* nRg */
                531880,
                /* nBg */
                716481,
            },
            /* 40 */
            {
                /* nRg */
                522841,
                /* nBg */
                726726,
            },
            /* 41 */
            {
                /* nRg */
                515270,
                /* nBg */
                735503,
            },
            /* 42 */
            {
                /* nRg */
                507783,
                /* nBg */
                744353,
            },
            /* 43 */
            {
                /* nRg */
                500380,
                /* nBg */
                753276,
            },
            /* 44 */
            {
                /* nRg */
                493061,
                /* nBg */
                762283,
            },
            /* 45 */
            {
                /* nRg */
                485837,
                /* nBg */
                771353,
            },
            /* 46 */
            {
                /* nRg */
                478706,
                /* nBg */
                780497,
            },
            /* 47 */
            {
                /* nRg */
                471660,
                /* nBg */
                789704,
            },
            /* 48 */
            {
                /* nRg */
                464718,
                /* nBg */
                798983,
            },
            /* 49 */
            {
                /* nRg */
                434582,
                /* nBg */
                841587,
            },
            /* 50 */
            {
                /* nRg */
                406386,
                /* nBg */
                885491,
            },
            /* 51 */
            {
                /* nRg */
                380161,
                /* nBg */
                930601,
            },
            /* 52 */
            {
                /* nRg */
                355981,
                /* nBg */
                976832,
            },
            /* 53 */
            {
                /* nRg */
                333877,
                /* nBg */
                1024102,
            },
            /* 54 */
            {
                /* nRg */
                313902,
                /* nBg */
                1072295,
            },
            /* 55 */
            {
                /* nRg */
                296097,
                /* nBg */
                1121347,
            },
            /* 56 */
            {
                /* nRg */
                280484,
                /* nBg */
                1171134,
            },
        },
        /* tOutLeftBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1777252,
                /* nBg */
                220662,
            },
            /* 1 */
            {
                /* nRg */
                1699134,
                /* nBg */
                195109,
            },
            /* 2 */
            {
                /* nRg */
                1619284,
                /* nBg */
                174347,
            },
            /* 3 */
            {
                /* nRg */
                1537978,
                /* nBg */
                158503,
            },
            /* 4 */
            {
                /* nRg */
                1455528,
                /* nBg */
                147671,
            },
            /* 5 */
            {
                /* nRg */
                1372250,
                /* nBg */
                141946,
            },
            /* 6 */
            {
                /* nRg */
                1288448,
                /* nBg */
                141369,
            },
            /* 7 */
            {
                /* nRg */
                1204457,
                /* nBg */
                145983,
            },
            /* 8 */
            {
                /* nRg */
                1120582,
                /* nBg */
                155829,
            },
            /* 9 */
            {
                /* nRg */
                1085045,
                /* nBg */
                158492,
            },
            /* 10 */
            {
                /* nRg */
                1049446,
                /* nBg */
                162110,
            },
            /* 11 */
            {
                /* nRg */
                1013826,
                /* nBg */
                166671,
            },
            /* 12 */
            {
                /* nRg */
                978206,
                /* nBg */
                172187,
            },
            /* 13 */
            {
                /* nRg */
                942617,
                /* nBg */
                178656,
            },
            /* 14 */
            {
                /* nRg */
                907071,
                /* nBg */
                186080,
            },
            /* 15 */
            {
                /* nRg */
                871608,
                /* nBg */
                194469,
            },
            /* 16 */
            {
                /* nRg */
                836239,
                /* nBg */
                203822,
            },
            /* 17 */
            {
                /* nRg */
                799980,
                /* nBg */
                220411,
            },
            /* 18 */
            {
                /* nRg */
                764202,
                /* nBg */
                238027,
            },
            /* 19 */
            {
                /* nRg */
                728939,
                /* nBg */
                256639,
            },
            /* 20 */
            {
                /* nRg */
                694210,
                /* nBg */
                276247,
            },
            /* 21 */
            {
                /* nRg */
                660047,
                /* nBg */
                296820,
            },
            /* 22 */
            {
                /* nRg */
                626482,
                /* nBg */
                318348,
            },
            /* 23 */
            {
                /* nRg */
                593536,
                /* nBg */
                340819,
            },
            /* 24 */
            {
                /* nRg */
                561240,
                /* nBg */
                364212,
            },
            /* 25 */
            {
                /* nRg */
                544400,
                /* nBg */
                376963,
            },
            /* 26 */
            {
                /* nRg */
                527748,
                /* nBg */
                389976,
            },
            /* 27 */
            {
                /* nRg */
                511296,
                /* nBg */
                403230,
            },
            /* 28 */
            {
                /* nRg */
                495043,
                /* nBg */
                416736,
            },
            /* 29 */
            {
                /* nRg */
                479000,
                /* nBg */
                430482,
            },
            /* 30 */
            {
                /* nRg */
                463156,
                /* nBg */
                444460,
            },
            /* 31 */
            {
                /* nRg */
                447532,
                /* nBg */
                458679,
            },
            /* 32 */
            {
                /* nRg */
                432118,
                /* nBg */
                473128,
            },
            /* 33 */
            {
                /* nRg */
                420259,
                /* nBg */
                484547,
            },
            /* 34 */
            {
                /* nRg */
                408525,
                /* nBg */
                496102,
            },
            /* 35 */
            {
                /* nRg */
                396928,
                /* nBg */
                507794,
            },
            /* 36 */
            {
                /* nRg */
                385478,
                /* nBg */
                519622,
            },
            /* 37 */
            {
                /* nRg */
                374163,
                /* nBg */
                531576,
            },
            /* 38 */
            {
                /* nRg */
                362986,
                /* nBg */
                543676,
            },
            /* 39 */
            {
                /* nRg */
                351944,
                /* nBg */
                555892,
            },
            /* 40 */
            {
                /* nRg */
                341060,
                /* nBg */
                568234,
            },
            /* 41 */
            {
                /* nRg */
                331916,
                /* nBg */
                578824,
            },
            /* 42 */
            {
                /* nRg */
                322888,
                /* nBg */
                589499,
            },
            /* 43 */
            {
                /* nRg */
                313965,
                /* nBg */
                600268,
            },
            /* 44 */
            {
                /* nRg */
                305146,
                /* nBg */
                611110,
            },
            /* 45 */
            {
                /* nRg */
                296432,
                /* nBg */
                622057,
            },
            /* 46 */
            {
                /* nRg */
                287834,
                /* nBg */
                633078,
            },
            /* 47 */
            {
                /* nRg */
                279341,
                /* nBg */
                644182,
            },
            /* 48 */
            {
                /* nRg */
                270963,
                /* nBg */
                655381,
            },
            /* 49 */
            {
                /* nRg */
                234629,
                /* nBg */
                706751,
            },
            /* 50 */
            {
                /* nRg */
                200624,
                /* nBg */
                759683,
            },
            /* 51 */
            {
                /* nRg */
                169009,
                /* nBg */
                814083,
            },
            /* 52 */
            {
                /* nRg */
                139838,
                /* nBg */
                869836,
            },
            /* 53 */
            {
                /* nRg */
                113194,
                /* nBg */
                926826,
            },
            /* 54 */
            {
                /* nRg */
                89108,
                /* nBg */
                984948,
            },
            /* 55 */
            {
                /* nRg */
                67623,
                /* nBg */
                1044088,
            },
            /* 56 */
            {
                /* nRg */
                48801,
                /* nBg */
                1104130,
            },
        },
        /* tOutRightBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1692297,
                /* nBg */
                512638,
            },
            /* 1 */
            {
                /* nRg */
                1632318,
                /* nBg */
                491761,
            },
            /* 2 */
            {
                /* nRg */
                1570851,
                /* nBg */
                474554,
            },
            /* 3 */
            {
                /* nRg */
                1508125,
                /* nBg */
                461122,
            },
            /* 4 */
            {
                /* nRg */
                1444361,
                /* nBg */
                451559,
            },
            /* 5 */
            {
                /* nRg */
                1379811,
                /* nBg */
                445938,
            },
            /* 6 */
            {
                /* nRg */
                1314715,
                /* nBg */
                444313,
            },
            /* 7 */
            {
                /* nRg */
                1249326,
                /* nBg */
                446746,
            },
            /* 8 */
            {
                /* nRg */
                1183895,
                /* nBg */
                453257,
            },
            /* 9 */
            {
                /* nRg */
                1155961,
                /* nBg */
                454201,
            },
            /* 10 */
            {
                /* nRg */
                1127932,
                /* nBg */
                455889,
            },
            /* 11 */
            {
                /* nRg */
                1099830,
                /* nBg */
                458343,
            },
            /* 12 */
            {
                /* nRg */
                1071666,
                /* nBg */
                461552,
            },
            /* 13 */
            {
                /* nRg */
                1043469,
                /* nBg */
                465536,
            },
            /* 14 */
            {
                /* nRg */
                1015252,
                /* nBg */
                470276,
            },
            /* 15 */
            {
                /* nRg */
                987046,
                /* nBg */
                475791,
            },
            /* 16 */
            {
                /* nRg */
                958870,
                /* nBg */
                482083,
            },
            /* 17 */
            {
                /* nRg */
                930412,
                /* nBg */
                495106,
            },
            /* 18 */
            {
                /* nRg */
                902342,
                /* nBg */
                508926,
            },
            /* 19 */
            {
                /* nRg */
                874659,
                /* nBg */
                523533,
            },
            /* 20 */
            {
                /* nRg */
                847407,
                /* nBg */
                538916,
            },
            /* 21 */
            {
                /* nRg */
                820605,
                /* nBg */
                555064,
            },
            /* 22 */
            {
                /* nRg */
                794254,
                /* nBg */
                571967,
            },
            /* 23 */
            {
                /* nRg */
                768407,
                /* nBg */
                589593,
            },
            /* 24 */
            {
                /* nRg */
                743063,
                /* nBg */
                607954,
            },
            /* 25 */
            {
                /* nRg */
                729840,
                /* nBg */
                617968,
            },
            /* 26 */
            {
                /* nRg */
                716775,
                /* nBg */
                628170,
            },
            /* 27 */
            {
                /* nRg */
                703867,
                /* nBg */
                638572,
            },
            /* 28 */
            {
                /* nRg */
                691116,
                /* nBg */
                649173,
            },
            /* 29 */
            {
                /* nRg */
                678523,
                /* nBg */
                659953,
            },
            /* 30 */
            {
                /* nRg */
                666087,
                /* nBg */
                670931,
            },
            /* 31 */
            {
                /* nRg */
                653829,
                /* nBg */
                682088,
            },
            /* 32 */
            {
                /* nRg */
                641729,
                /* nBg */
                693423,
            },
            /* 33 */
            {
                /* nRg */
                632417,
                /* nBg */
                702389,
            },
            /* 34 */
            {
                /* nRg */
                623211,
                /* nBg */
                711459,
            },
            /* 35 */
            {
                /* nRg */
                614120,
                /* nBg */
                720634,
            },
            /* 36 */
            {
                /* nRg */
                605133,
                /* nBg */
                729914,
            },
            /* 37 */
            {
                /* nRg */
                596252,
                /* nBg */
                739299,
            },
            /* 38 */
            {
                /* nRg */
                587475,
                /* nBg */
                748788,
            },
            /* 39 */
            {
                /* nRg */
                578814,
                /* nBg */
                758372,
            },
            /* 40 */
            {
                /* nRg */
                570268,
                /* nBg */
                768061,
            },
            /* 41 */
            {
                /* nRg */
                563096,
                /* nBg */
                776376,
            },
            /* 42 */
            {
                /* nRg */
                556007,
                /* nBg */
                784754,
            },
            /* 43 */
            {
                /* nRg */
                549003,
                /* nBg */
                793195,
            },
            /* 44 */
            {
                /* nRg */
                542082,
                /* nBg */
                801710,
            },
            /* 45 */
            {
                /* nRg */
                535256,
                /* nBg */
                810298,
            },
            /* 46 */
            {
                /* nRg */
                528503,
                /* nBg */
                818948,
            },
            /* 47 */
            {
                /* nRg */
                521834,
                /* nBg */
                827662,
            },
            /* 48 */
            {
                /* nRg */
                515260,
                /* nBg */
                836449,
            },
            /* 49 */
            {
                /* nRg */
                486749,
                /* nBg */
                876767,
            },
            /* 50 */
            {
                /* nRg */
                460063,
                /* nBg */
                918301,
            },
            /* 51 */
            {
                /* nRg */
                435253,
                /* nBg */
                960988,
            },
            /* 52 */
            {
                /* nRg */
                412363,
                /* nBg */
                1004746,
            },
            /* 53 */
            {
                /* nRg */
                391444,
                /* nBg */
                1049467,
            },
            /* 54 */
            {
                /* nRg */
                372549,
                /* nBg */
                1095080,
            },
            /* 55 */
            {
                /* nRg */
                355687,
                /* nBg */
                1141501,
            },
            /* 56 */
            {
                /* nRg */
                340924,
                /* nBg */
                1188613,
            },
        },
        /* nIllumNum */
        6,
        /* tIllumList[16] */
        {
            /* 0 */
            {
                /* szName[32] */
                "H",
                /* nCct */
                2300,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    1149239,
                    /* nBg */
                    290456,
                },
            },
            /* 1 */
            {
                /* szName[32] */
                "A",
                /* nCct */
                2800,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    904921,
                    /* nBg */
                    359662,
                },
            },
            /* 2 */
            {
                /* szName[32] */
                "TL84",
                /* nCct */
                3800,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    607126,
                    /* nBg */
                    425722,
                },
            },
            /* 3 */
            {
                /* szName[32] */
                "D50",
                /* nCct */
                5000,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    532677,
                    /* nBg */
                    578814,
                },
            },
            /* 4 */
            {
                /* szName[32] */
                "D65",
                /* nCct */
                6500,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    485491,
                    /* nBg */
                    694157,
                },
            },
            /* 5 */
            {
                /* szName[32] */
                "D75",
                /* nCct */
                7500,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    415236,
                    /* nBg */
                    762315,
                },
            },
        },
        /* nExtIllumNum */
        1,
        /* tExtIllumList[32] */
        {
            /* 0 */
            {
                /* szName[32] */
                "CWF",
                /* nCct */
                4100,
                /* nRadius */
                31457,
                /* tCoord */
                {
                    /* nRg */
                    577765,
                    /* nBg */
                    460325,
                },
            },
        },
        /* nMLCNum */
        0,
        /* tMLCZoneList[15] */
        {
            /* 0 */
            {
                /* nEnable */
                0,
                /* szDescription[32] */
                "",
                /* nZoneType */
                0,
                /* tPoly */
                {
                    /* nPntCnt */
                    0,
                    /* tPntArray[15] */
                    {
                        /* 0 */
                        {
                            /* nRg */
                            0,
                            /* nBg */
                            0,
                        },
                    },
                },
                /* nDetectionZoneGroupNum */
                0,
                /* tGroupDetectionZoneList[10] */
                {
                    /* 0 */
                    {
                        /* nDetectionZoneNum */
                        0,
                        /* tDetectionZoneList[5] */
                        {
                            /* 0 */
                            {
                                /* szDescription[32] */
                                "",
                                /* nZoneType */
                                0,
                                /* tPoly */
                                {
                                    /* nPntCnt */
                                    0,
                                    /* tPntArray[15] */
                                    {
                                        /* 0 */
                                        {
                                            /* nRg */
                                            0,
                                            /* nBg */
                                            0,
                                        },
                                    },
                                },
                                /* nLux[2] */
                                {0, 0, /*0 - 1*/},
                            },
                        },
                    },
                },
                /* nTrigerType1st */
                0,
                /* nTrigerType2nd */
                0,
                /* nTrigerType3rd */
                0,
                /* nTrigerValue1st[2] */
                {0, 0, /*0 - 1*/},
                /* nTrigerValue2nd[2] */
                {0, 0, /*0 - 1*/},
                /* nTrigerValue3rd */
                0,
            },
        },
        /* tInitParam */
        {
            /* tGains */
            {
                /* nGainR */
                442,
                /* nGainGr */
                256,
                /* nGainGb */
                256,
                /* nGainB */
                630,
            },
            /* nDampRatio */
            100000,
        },
        /* nMode */
        0,
        /* nIndex */
        0,
        /* nDampRatio */
        943718,
        /* nToleranceRg */
        3145,
        /* nToleranceBg */
        3145,
        /* nLuxVeryDarkStart */
        0,
        /* nLuxVeryDarkEnd */
        205,
        /* nLuxDarkStart */
        307,
        /* nLuxDarkEnd */
        5120,
        /* nLuxIndoorStart */
        20480,
        /* nLuxIndoorEnd */
        409600,
        /* nLuxTransInStart */
        460800,
        /* nLuxTransInEnd */
        972800,
        /* nLuxTransOutStart */
        1024000,
        /* nLuxTransOutEnd */
        1894400,
        /* nLuxOutdoorStart */
        1945600,
        /* nLuxOutdoorEnd */
        4044800,
        /* nLuxBrightStart */
        4096000,
        /* nLuxBrightEnd */
        10137600,
        /* nLuxVeryBrightStart */
        10240000,
        /* nCctMinInner */
        1800,
        /* nCctMaxInner */
        8000,
        /* nCctMinOuter */
        1500,
        /* nCctMaxOuter */
        12000,
        /* nCctSplitHtoA */
        2700,
        /* nCctSplitAtoF */
        3300,
        /* nCctSplitFtoD5 */
        4600,
        /* nCctSplitD5toD6 */
        5400,
        /* nCctSplitD6toS */
        6800,
        /* nGridWeightEnable */
        0,
        /* nGridWeightRow */
        9,
        /* nGridWeightColumn */
        9,
        /* nGridWeightTable[54][72] */
        {
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 8*/},
        },
        /* nGrayZoneLuxWeight[24][8] */
        {
            {200, 200, 100, 50, 20, 10, 10, 10, /*0 - 7*/},
            {600, 500, 400, 400, 200, 100, 100, 100, /*0 - 7*/},
            {600, 500, 400, 400, 200, 100, 100, 100, /*0 - 7*/},
            {300, 300, 100, 50, 20, 10, 10, 10, /*0 - 7*/},
            {500, 300, 150, 150, 80, 30, 30, 30, /*0 - 7*/},
            {700, 700, 500, 400, 200, 100, 100, 100, /*0 - 7*/},
            {700, 700, 500, 400, 200, 100, 100, 100, /*0 - 7*/},
            {500, 300, 150, 150, 80, 30, 30, 30, /*0 - 7*/},
            {200, 200, 200, 100, 100, 50, 50, 50, /*0 - 7*/},
            {700, 700, 700, 700, 600, 500, 500, 500, /*0 - 7*/},
            {800, 900, 900, 800, 700, 600, 600, 600, /*0 - 7*/},
            {200, 100, 100, 50, 50, 50, 50, 50, /*0 - 7*/},
            {300, 200, 200, 200, 100, 100, 100, 100, /*0 - 7*/},
            {800, 800, 800, 800, 800, 800, 800, 800, /*0 - 7*/},
            {900, 1000, 1000, 1000, 900, 900, 900, 900, /*0 - 7*/},
            {400, 200, 200, 100, 50, 50, 50, 50, /*0 - 7*/},
            {200, 300, 400, 400, 300, 200, 200, 200, /*0 - 7*/},
            {800, 800, 800, 900, 900, 900, 900, 900, /*0 - 7*/},
            {900, 1000, 1000, 1000, 900, 900, 900, 900, /*0 - 7*/},
            {300, 200, 100, 80, 50, 50, 50, 50, /*0 - 7*/},
            {200, 200, 200, 200, 200, 100, 100, 100, /*0 - 7*/},
            {400, 500, 500, 500, 500, 500, 500, 500, /*0 - 7*/},
            {400, 500, 500, 500, 500, 500, 500, 500, /*0 - 7*/},
            {200, 300, 300, 300, 100, 50, 50, 50, /*0 - 7*/},
        },
        /* nExtIlllumLuxWeight[32][8] */
        {
            {1000, 1000, 900, 500, 100, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
        },
        /* nLumaWeightNum */
        8,
        /* nLumaSplitList[32] */
        {51, 819, 3072, 8192, 20480, 40960, 92160, 215040, /*0 - 7*/},
        /* nLumaWeightList[8][32] */
        {
            {256, 512, 512, 1024, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 102, 205, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
        },
        /* bMixLightEn */
        1,
        /* nMixLightProba_0_CctStd[8] */
        {400, 400, 400, 450, 600, 9998, 9998, 9998, /*0 - 7*/},
        /* nMixLightProba_100_CctStd[8] */
        {600, 700, 800, 800, 1000, 9999, 9999, 9999, /*0 - 7*/},
        /* nMixLightProba_100_SatDiscnt[8] */
        {100, 100, 100, 100, 100, 100, 100, 100, /*0 - 7*/},
        /* nMixLightKneeNum */
        8,
        /* nMixLightKneeCctList[32] */
        {2300, 2800, 3500, 4600, 5500, 6500, 7500, 8500, /*0 - 7*/},
        /* nMixLightKneeWtList[8][32] */
        {
            {820, 820, 820, 1024, 1024, 820, 410, 358, /*0 - 7*/},
            {614, 614, 614, 1024, 1024, 820, 410, 358, /*0 - 7*/},
            {205, 205, 307, 820, 1024, 820, 410, 358, /*0 - 7*/},
            {205, 205, 410, 922, 1024, 820, 410, 358, /*0 - 7*/},
            {307, 307, 512, 1024, 1024, 820, 410, 358, /*0 - 7*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 7*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 7*/},
            {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, /*0 - 7*/},
        },
        /* tDomParamList[4] */
        {
            /* 0 */
            {
                /* nDominantEnable */
                0,
                /* nDomMinCctThresh */
                2000,
                /* nDomMaxCctThresh */
                2500,
                /* nDom2AllRatioThresh */
                1024,
                /* nDom2MinorRatioThresh */
                4096,
                /* nMinorWeight */
                0,
                /* nSmoothPercent */
                204,
            },
            /* 1 */
            {
                /* nDominantEnable */
                0,
                /* nDomMinCctThresh */
                2700,
                /* nDomMaxCctThresh */
                3300,
                /* nDom2AllRatioThresh */
                1024,
                /* nDom2MinorRatioThresh */
                4096,
                /* nMinorWeight */
                0,
                /* nSmoothPercent */
                204,
            },
            /* 2 */
            {
                /* nDominantEnable */
                0,
                /* nDomMinCctThresh */
                3600,
                /* nDomMaxCctThresh */
                4400,
                /* nDom2AllRatioThresh */
                1024,
                /* nDom2MinorRatioThresh */
                4096,
                /* nMinorWeight */
                0,
                /* nSmoothPercent */
                204,
            },
            /* 3 */
            {
                /* nDominantEnable */
                0,
                /* nDomMinCctThresh */
                4600,
                /* nDomMaxCctThresh */
                7500,
                /* nDom2AllRatioThresh */
                409,
                /* nDom2MinorRatioThresh */
                4096,
                /* nMinorWeight */
                0,
                /* nSmoothPercent */
                204,
            },
        },
        /* nTmpoStabTriggerAvgBlkWt */
        10,
        /* nPlanckianLocusProjEn */
        0,
        /* nPlanckianLocusNotProjLux */
        4096000,
        /* nPlanckianLocusFullProjLux */
        10240000,
        /* nSpatialSegmetNum */
        2,
        /* nSpatialStartLux[32] */
        {4096000, 11264000, /*0 - 1*/},
        /* nSpatialEndLux[32] */
        {10240000, 1024000000, /*0 - 1*/},
        /* nSpatialRg[32] */
        {488636, 622854, /*0 - 1*/},
        /* nSpatialBg[32] */
        {636485, 615514, /*0 - 1*/},
        /* nFusionGrayZoneConfid_0_AvgBlkWeight */
        20,
        /* nFusionGrayZoneConfid_100_AvgBlkWeight */
        500,
        /* nFusionSpatialConfid_0_Lux */
        5120000,
        /* nFusionSpatialConfid_100_Lux */
        15360000,
        /* nFusionWeightGrayZone */
        1024,
        /* nFusionWeightSpatial */
        0,
        /* nPreferCctNum */
        10,
        /* nPreferSrcCctList[32] */
        {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
        /* nPreferDstCct[8][32] */
        {
            {1800, 2200, 2800, 3850, 4170, 5100, 6600, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2200, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
        },
        /* nPreferGrShift[8][32] */
        {
            {0, 0, 0, 0, 0, -10485, -10485, -10485, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, -10485, -10485, -10485, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, -10485, -10485, -10485, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
        },
        /* nGreenCutEn */
        1,
        /* nGreenCutConfid_0_Lx */
        512000,
        /* nGreenCutConfid_100_Lx */
        102400,
        /* nGreenCutWeight */
        768,
        /* nGreenCutBreakAngle */
        52429,
        /* nGreenCutOffsetRg */
        0,
        /* nGreenCutOffsetBg */
        0,
        /* nMultiCamSyncMode */
        0,
    },
    /* tLogParam */
    {
        /* nLogLevel */
        4,
        /* nLogTarget */
        2,
        /* nAlgoPrintInterval */
        0,
        /* nStatisticsPrintInterval */
        0,
    },
};

const static AX_ISP_IQ_CAF_PARAM_T caf_param_sdr = {
    /* nScanType */
    0,
    /* nGlobalScanStep */
    0,
    /* nSearchDownFrameTh */
    0,
    /* nSearchDownSerialSlopeTh */
    0,
    /* nSearchDownSingleSlopeTh */
    0,
    /* nSearchUpFrameTh */
    0,
    /* nSearchUpSerialSlopeTh */
    0,
    /* nSearchUpSingleSlopeTh */
    0,
    /* nSearchBigStepUpSlopeTh */
    0,
    /* nSearchBigStep */
    0,
    /* nSearchSmallStep */
    0,
    /* nSearchProbeStep */
    0,
    /* nSearchProbeFrameTh */
    0,
    /* bContinuousAfEn */
    0,
    /* nSceneChangeLumaTh */
    0,
    /* nSceneSettledLumaTh */
    0,
    /* nSceneSlowChangeLumaTh */
    0,
    /* nSceneFvChangeLumaTh */
    0,
    /* nSceneFvChangeRatioTh */
    0,
    /* nSpotlightZoomRatioTh */
    0,
    /* tWeight */
    {
        /* nMuX */
        0,
        /* nMuY */
        0,
        /* nSigmaX */
        0,
        /* nSigmaY */
        0,
        /* nCoeffV1 */
        0,
        /* nCoeffV2 */
        0,
        /* nCoeffH1 */
        0,
        /* nCoeffH2 */
        0,
    },
            /* zoom tracking */
    {
        /*nDefaultDistance*/
        0,
        /*nStepFactor*/
        1,
        /*nProbStepCoff*/
        0,
        /*nMaxProbeStep*/
        0,
        /*nMinProbeStep*/
        0,
        /*nFvDiffOverThresh*/
        0,
        /*nFvDiffMiddleThresh*/
        0,
        /*nFvDiffUnderThresh*/
        0,
        /*nHeightDistanceCoff*/
        0,
        /*nMiddleDistanceCoff*/
        0,
        /*nUnderDistanceCoff*/
        0,
        /*nProportionalCoff*/
        0,
        /*nIntegralCoff*/
        0,
        /*nDifferentialCoff*/
        0,
    },
};

const static AX_ISP_IQ_DPC_PARAM_T dpc_param_sdr = {
    /* nDpcEnable */
    1,
    /* nStaticDpcEnable */
    0,
    /* nDynamicDpcEnable */
    1,
    /* nColorLimitEnable */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tDpcParam */
    {
        /* tHcgTable */
        {
            /* nShotNoiseCoeffsA[4] */
            {154451139, 152870846, 153255590, 154699876, /*0 - 3*/},
            /* nShotNoiseCoeffsB[4] */
            {13840120, 20632215, 20876088, 12133979, /*0 - 3*/},
            /* nReadNoiseCoeffsA[4] */
            {6529576, 6532419, 6449761, 6498451, /*0 - 3*/},
            /* nReadNoiseCoeffsB[4] */
            {27818796, 27824017, 28471222, 28156829, /*0 - 3*/},
            /* nReadNoiseCoeffsC[4] */
            {29481682, 27445089, 27620499, 28535918, /*0 - 3*/},
        },
        /* tLcgTable */
        {
            /* nShotNoiseCoeffsA[4] */
            {36863371, 36889750, 36887419, 36784136, /*0 - 3*/},
            /* nShotNoiseCoeffsB[4] */
            {5747087, 6168625, 6705084, 5549101, /*0 - 3*/},
            /* nReadNoiseCoeffsA[4] */
            {1526043, 1569756, 1552586, 1544424, /*0 - 3*/},
            /* nReadNoiseCoeffsB[4] */
            {25445201, 24908808, 24845929, 25340783, /*0 - 3*/},
            /* nReadNoiseCoeffsC[4] */
            {15015910, 13550075, 15978964, 13922947, /*0 - 3*/},
        },
    },
    /* tManualParam */
    {
        /* nNoiseRatio */
        1024,
        /* nDpType */
        1,
        /* nNonChwiseEn */
        0,
        /* nChwiseStr */
        20,
        /* nDetCoarseStr */
        120,
        /* nDetFineStr */
        48,
        /* nDynamicDpcStr */
        128,
        /* nEdgeStr */
        102,
        /* nHotColdTypeStr */
        32,
        /* nSupWinkStr */
        16,
        /* nDynamicDpClrLimOffset */
        {
            /* nUpperLimit */
            65535,
            /* nLowerLimit */
            1024,
        },
        /* nStaticDpClrLimOffset */
        {
            /* nUpperLimit */
            65535,
            /* nLowerLimit */
            1024,
        },
        /* nNormalPixDpClrLimOffset */
        {
            /* nUpperLimit */
            65535,
            /* nLowerLimit */
            1024,
        },
        /* nDynamicDpClrLimStr */
        128,
        /* nStaticDpClrLimStr */
        128,
        /* nNormalPixDpClrLimStr */
        128,
        /* nPreDetLevelSlope */
        4,
        /* nPreDetLevelOffset */
        0,
        /* nPreDetLevelMax */
        256,
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        9,
        /* nRefVal[16] */
        {1024, 4096, 8192, 16384, 32768, 68096, 136192, 260096, 543744, /*0 - 8*/},
        /* nNoiseRatio[16] */
        {512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 8*/},
        /* nDpType[16] */
        {1, 1, 1, 1, 1, 1, 1, 1, 1, /*0 - 8*/},
        /* nNonChwiseEn[16] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
        /* nChwiseStr[16] */
        {20, 20, 20, 20, 20, 20, 20, 20, 20, /*0 - 8*/},
        /* nDetCoarseStr[16] */
        {80, 100, 120, 120, 140, 150, 170, 180, 190, /*0 - 8*/},
        /* nDetFineStr[16] */
        {48, 48, 48, 48, 48, 48, 48, 48, 48, /*0 - 8*/},
        /* nDynamicDpcStr[16] */
        {128, 256, 512, 512, 1024, 1024, 1532, 2048, 2048, /*0 - 8*/},
        /* nEdgeStr[16] */
        {255, 255, 255, 224, 192, 160, 128, 128, 128, /*0 - 8*/},
        /* nHotColdTypeStr[16] */
        {32, 32, 32, 32, 32, 32, 48, 56, 64, /*0 - 8*/},
        /* nSupWinkStr[16] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 8*/},
        /* nDynamicDpClrLimOffset[16] */
        {
            /* 0 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 1 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 2 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 3 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 4 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 5 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 6 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
            /* 7 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
            /* 8 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
        },
        /* nStaticDpClrLimOffset[16] */
        {
            /* 0 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 1 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 2 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 3 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 4 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 5 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 6 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
            /* 7 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
            /* 8 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
        },
        /* nNormalPixDpClrLimOffset[16] */
        {
            /* 0 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 1 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 2 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 3 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 4 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 5 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                1024,
            },
            /* 6 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
            /* 7 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
            /* 8 */
            {
                /* nUpperLimit */
                65535,
                /* nLowerLimit */
                256,
            },
        },
        /* nDynamicDpClrLimStr[16] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
        /* nStaticDpClrLimStr[16] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
        /* nNormalPixDpClrLimStr[16] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
        /* nPreDetLevelSlope[16] */
        {4, 4, 4, 4, 4, 4, 4, 4, 4, /*0 - 8*/},
        /* nPreDetLevelOffset[16] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
        /* nPreDetLevelMax[16] */
        {256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 8*/},
    },
};

const static AX_ISP_IQ_BLC_PARAM_T blc_param_sdr = {
    /* nBlcEnable */
    1,
    /* nSblEnable */
    1,
    /* nAutoMode */
    1,
    /* tManualParam[4] */
    {
        /* 0 */
        {
            /* nSblRValue */
            4096,
            /* nSblGrValue */
            4096,
            /* nSblGbValue */
            4096,
            /* nSblBValue */
            4096,
        },
        /* 1 */
        {
            /* nSblRValue */
            0,
            /* nSblGrValue */
            0,
            /* nSblGbValue */
            0,
            /* nSblBValue */
            0,
        },
        /* 2 */
        {
            /* nSblRValue */
            0,
            /* nSblGrValue */
            0,
            /* nSblGbValue */
            0,
            /* nSblBValue */
            0,
        },
        /* 3 */
        {
            /* nSblRValue */
            0,
            /* nSblGrValue */
            0,
            /* nSblGbValue */
            0,
            /* nSblBValue */
            0,
        },
    },
    /* tAutoParam */
    {
        /* tHcgAutoTable */
        {
            /* nGainGrpNum */
            12,
            /* nExposeTimeGrpNum */
            2,
            /* nGain[16] */
            {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
            /* nExposeTime[10] */
            {1000, 5000, /*0 - 1*/},
            /* nAutoSblRValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
            /* nAutoSblGrValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
            /* nAutoSblGbValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
            /* nAutoSblBValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
        },
        /* tLcgAutoTable */
        {
            /* nGainGrpNum */
            12,
            /* nExposeTimeGrpNum */
            2,
            /* nGain[16] */
            {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
            /* nExposeTime[10] */
            {1000, 5000, /*0 - 1*/},
            /* nAutoSblRValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
            /* nAutoSblGrValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
            /* nAutoSblGbValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
            /* nAutoSblBValue[16][10] */
            {
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
                {4096, 4096, /*0 - 1*/},
            },
        },
    },
};

const static AX_ISP_IQ_HDR_PARAM_T hdr_param_sdr = {
    /* nEnable */
    0,
    /* nAutoMode */
    0,
    /* nRefMode */
    0,
    /* nDebugMode */
    0,
    /* tMotDetParam */
    {
        /* nCoarseMotMaskRatio[2] */
        {0, 0, /*0 - 1*/},
        /* nMotIirRatio[2] */
        {0, 0, /*0 - 1*/},
    },
    /* tExpMaskParam */
    {
        /* nCoarseExpMaskRatio[2][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
        },
        /* nExpIirRatio[2][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
        },
        /* nExpYRatio[2] */
        {0, 0, /*0 - 1*/},
        /* nExpWeightLut[2][257] */
        {
            {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 0 - 31*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 32 - 63*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 64 - 95*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 96 - 127*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 128 - 159*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 160 - 191*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 192 - 223*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 224 - 255*/
                0, /*256 - 256*/
            },
            {
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 0 - 31*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 32 - 63*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 64 - 95*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 96 - 127*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 128 - 159*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 160 - 191*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 192 - 223*/
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 224 - 255*/
                0, /*256 - 256*/
            },
        },
        /* nExpWeightGain[2] */
        {0, 0, /*0 - 1*/},
    },
    /* tDgstParam */
    {
        /* nDeghostEnable */
        0,
        /* nDgstStrenThre[2] */
        {0, 0, /*0 - 1*/},
        /* nDgstStrenLimit[2] */
        {0, 0, /*0 - 1*/},
        /* nDgstBaseFid */
        0,
    },
    /* tFusionParam */
    {
        /* nFusionProtectThreshold[2][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
        },
    },
    /* tHdrManualParam */
    {
        /* nNoiseLutScale */
        0,
        /* nCoarseMotMaskNoiseLvl */
        0,
        /* nCoarseMotMaskSen */
        0,
        /* nCoarseExpMaskSen[2] */
        {0, 0, /*0 - 1*/},
    },
    /* tHdrAutoParam */
    {
        /* nParamGrpNum */
        0,
        /* nRefVal[16] */
        {0, /*0 - 0*/},
        /* nNoiseLutScale[16] */
        {0, /*0 - 0*/},
        /* nCoarseMotMaskNoiseLvl[16] */
        {0, /*0 - 0*/},
        /* nCoarseMotMaskSen[16] */
        {0, /*0 - 0*/},
        /* nCoarseExpMaskSen[16][2] */
        {
            {0, 0, /*0 - 1*/},
        },
    },
};

const static AX_ISP_IQ_AINR_PARAM_T ainr_param_sdr = {
    /* nEnable */
    1,
    /* nAutoMode */
    1,
    /* bUpdateTable */
    1,
    /* nRefMode */
    1,
    /* nHdrMode */
    1,
    /* tManualParam */
    {
        /* tMeta */
        {
            /* szModelPath[256] */
            "/opt/etc/models/aiisp/SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
            /* szModelName[256] */
            "SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
            /* szTemporalBaseNrName[256] */
            "",
            /* szSpatialBaseNrName[256] */
            "",
            /* nHcgMode */
            0,
            /* nIsoThresholdMin */
            0,
            /* nIsoThresholdMax */
            0,
            /* nBiasIn2D */
            {0, 0, 0, 0,},
            /* nBiasIn3D */
            {0, 0, 0, 0,},
        },
        /* tParams */
        {
             /*tBias[4][4]*/
            {
                 /* nBiasIn[4] */
                {0, 0, 0, 0, /*0 - 3*/},
                /* nBiasOut[4] */
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* tNonSens */
            {
                /* nTemporalFilterStrLut[17][2] */
                {
                    {0, 0, /*0 - 1*/},
                    {16, 256, /*0 - 1*/},
                    {32, 512, /*0 - 1*/},
                    {48, 768, /*0 - 1*/},
                    {64, 1024, /*0 - 1*/},
                    {80, 1280, /*0 - 1*/},
                    {96, 1536, /*0 - 1*/},
                    {112, 1792, /*0 - 1*/},
                    {128, 2048, /*0 - 1*/},
                    {144, 2304, /*0 - 1*/},
                    {160, 2560, /*0 - 1*/},
                    {176, 2816, /*0 - 1*/},
                    {192, 3072, /*0 - 1*/},
                    {208, 3328, /*0 - 1*/},
                    {224, 3584, /*0 - 1*/},
                    {240, 3840, /*0 - 1*/},
                    {255, 4096, /*0 - 1*/},
                },
                /* nVstTemporalFilterStrLut[17][2] */
                {
                    {0, 0, /*0 - 1*/},
                    {16, 256, /*0 - 1*/},
                    {32, 512, /*0 - 1*/},
                    {48, 768, /*0 - 1*/},
                    {64, 1024, /*0 - 1*/},
                    {80, 1280, /*0 - 1*/},
                    {96, 1536, /*0 - 1*/},
                    {112, 1792, /*0 - 1*/},
                    {128, 2048, /*0 - 1*/},
                    {144, 2304, /*0 - 1*/},
                    {160, 2560, /*0 - 1*/},
                    {176, 2816, /*0 - 1*/},
                    {192, 3072, /*0 - 1*/},
                    {208, 3328, /*0 - 1*/},
                    {224, 3584, /*0 - 1*/},
                    {240, 3840, /*0 - 1*/},
                    {255, 4096, /*0 - 1*/},
                },
            },
            /* tSens */
            {
                /* nSpatialNrStrLut[17][2] */
                {
                    {0, 4096, /*0 - 1*/},
                    {16, 4096, /*0 - 1*/},
                    {32, 4096, /*0 - 1*/},
                    {48, 4096, /*0 - 1*/},
                    {64,  4096, /*0 - 1*/},
                    {80,  4096, /*0 - 1*/},
                    {96,  4096, /*0 - 1*/},
                    {112, 4096, /*0 - 1*/},
                    {128, 4096, /*0 - 1*/},
                    {144, 4096, /*0 - 1*/},
                    {160, 4096, /*0 - 1*/},
                    {176, 4096, /*0 - 1*/},
                    {192, 4096, /*0 - 1*/},
                    {208, 4096, /*0 - 1*/},
                    {224, 4096, /*0 - 1*/},
                    {240, 4096, /*0 - 1*/},
                    {255, 4096, /*0 - 1*/},
                },
            },
        },
    },
    /* tAutoParam */
    {
        /* nAutoModelNum */
        2,
        /* tAutoModelTable[12] */
        {
            /* 0 */
            {
                /* tMata */
                {
                    /* szModelPath[256] */
                    "/opt/etc/models/aiisp/SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
                    /* szModelName[256] */
                    "SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
                    /* szTemporalBaseNrName[256] */
                    "",
                    /* szSpatialBaseNrName[256] */
                    "",
                    /* nHcgMode */
                    0,
                    /* nIsoThresholdMin */
                    2800,
                    /* nIsoThresholdMax */
                    5400,
                    /* nBiasIn2D */
                    {0, 0, 0, 0,},
                    /* nBiasIn3D */
                    {0, 0, 0, 0,},
                },
                /* tParams */
                {
                    /* tBias */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {6400, 8000, 9600, 11200, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {8000, 9600, 11200, 12800, /*0 - 3*/},
                        /* nBiasIn[4][4] */
                        {
                            /*  nBiasIn 0 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasIn 1 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasIn 2 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasIn 3 */
                            {0, 0, 0, 0, /*0 - 3*/},
                        },
                        /* nBiasOut[4][4] */
                        {
                            /*  nBiasOut 0 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 1 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 2 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 3 */
                            {0, 0, 0, 0, /*0 - 3*/},
                        },
                    },
                    /* tNonSens */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {24576, 32768, 40960, 49152, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {32768, 40960, 49152, 55296, /*0 - 3*/},
                        /* nTemporalFilterStrLut[4][17][2] */
                        {
                            /* nTemporalFilterStrLut 0 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nTemporalFilterStrLut 1 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nTemporalFilterStrLut 2 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nTemporalFilterStrLut 3 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                        },
                        /* nVstTemporalFilterStrLut[4][17][2] */
                        {
                            /* nVstTemporalFilterStrLut 0 */
                            {
                                {0, 1136, /*0 - 1*/},
                                {16, 1136, /*0 - 1*/},
                                {32, 1136, /*0 - 1*/},
                                {48, 1236, /*0 - 1*/},
                                {64,  1236, /*0 - 1*/},
                                {80,  1536, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nVstTemporalFilterStrLut 1 */
                            {
                                {0, 1136, /*0 - 1*/},
                                {16, 1136, /*0 - 1*/},
                                {32, 1136, /*0 - 1*/},
                                {48, 1236, /*0 - 1*/},
                                {64,  1236, /*0 - 1*/},
                                {80,  1536, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nVstTemporalFilterStrLut 2 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nVstTemporalFilterStrLut 3 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                        },
                    },
                    /* tSens */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {24576, 32768, 40960, 49152, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {32768, 40960, 49152, 55296, /*0 - 3*/},
                        /* nSpatialNrStrLut[4][17][2] */
                        {
                            /* nSpatialNrStrLut 0 */
                            {
                                {0, 1000, /*0 - 1*/},
                                {16, 1200, /*0 - 1*/},
                                {32, 1400, /*0 - 1*/},
                                {48, 1400, /*0 - 1*/},
                                {64,  1400, /*0 - 1*/},
                                {80,  1400, /*0 - 1*/},
                                {96,  1400, /*0 - 1*/},
                                {112, 1400, /*0 - 1*/},
                                {128, 1600, /*0 - 1*/},
                                {144, 1800, /*0 - 1*/},
                                {160, 1900, /*0 - 1*/},
                                {176, 2000, /*0 - 1*/},
                                {192, 2100, /*0 - 1*/},
                                {208, 2100, /*0 - 1*/},
                                {224, 2100, /*0 - 1*/},
                                {240, 2100, /*0 - 1*/},
                                {255, 2100, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 1 */
                            {
                                {0, 1000, /*0 - 1*/},
                                {16, 1200, /*0 - 1*/},
                                {32, 1400, /*0 - 1*/},
                                {48, 1400, /*0 - 1*/},
                                {64,  1400, /*0 - 1*/},
                                {80,  1400, /*0 - 1*/},
                                {96,  1400, /*0 - 1*/},
                                {112, 1400, /*0 - 1*/},
                                {128, 1600, /*0 - 1*/},
                                {144, 1800, /*0 - 1*/},
                                {160, 1900, /*0 - 1*/},
                                {176, 2000, /*0 - 1*/},
                                {192, 2100, /*0 - 1*/},
                                {208, 2100, /*0 - 1*/},
                                {224, 2100, /*0 - 1*/},
                                {240, 2100, /*0 - 1*/},
                                {255, 2100, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 2 */
                            {
                                {0, 1300, /*0 - 1*/},
                                {16, 1500, /*0 - 1*/},
                                {32, 1700, /*0 - 1*/},
                                {48, 1700, /*0 - 1*/},
                                {64,  1700, /*0 - 1*/},
                                {80,  1700, /*0 - 1*/},
                                {96,  1700, /*0 - 1*/},
                                {112, 1700, /*0 - 1*/},
                                {128, 1900, /*0 - 1*/},
                                {144, 2100, /*0 - 1*/},
                                {160, 2200, /*0 - 1*/},
                                {176, 2300, /*0 - 1*/},
                                {192, 2400, /*0 - 1*/},
                                {208, 2400, /*0 - 1*/},
                                {224, 2400, /*0 - 1*/},
                                {240, 2400, /*0 - 1*/},
                                {255, 2400, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 3 */
                            {
                                {0, 1500, /*0 - 1*/},
                                {16, 1700, /*0 - 1*/},
                                {32, 1900, /*0 - 1*/},
                                {48, 1900, /*0 - 1*/},
                                {64,  1900, /*0 - 1*/},
                                {80,  1900, /*0 - 1*/},
                                {96,  1900, /*0 - 1*/},
                                {112, 1900, /*0 - 1*/},
                                {128, 1900, /*0 - 1*/},
                                {144, 2300, /*0 - 1*/},
                                {160, 2400, /*0 - 1*/},
                                {176, 2500, /*0 - 1*/},
                                {192, 2600, /*0 - 1*/},
                                {208, 2600, /*0 - 1*/},
                                {224, 2600, /*0 - 1*/},
                                {240, 2600, /*0 - 1*/},
                                {255, 2600, /*0 - 1*/},
                            },
                        },
                    },
                },
            },
            /* 1 */
            {
                /* tMata */
                {
                    /* szModelPath[256] */
                    "/opt/etc/models/aiisp/SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
                    /* szModelName[256] */
                    "SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
                    /* szTemporalBaseNrName[256] */
                    "",
                    /* szSpatialBaseNrName[256] */
                    "",
                    /* nHcgMode */
                    0,
                    /* nIsoThresholdMin */
                    5400,
                    /* nIsoThresholdMax */
                    43200,
                    /* nBiasIn2D[4] */
                    {4096, 4096, 4096, 4096, /*0 - 3*/},
                    /* nBiasIn3D[4] */
                    {4096, 4096, 4096, 4096, /*0 - 3*/},
                },
                /* tParams */
                {
                    /* tBias */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {6400, 8000, 9600, 11200, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {8000, 9600, 11200, 12800, /*0 - 3*/},
                        /* nBiasIn[4][4] */
                        {
                            /*  nBiasIn 0 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasIn 1 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasIn 2 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasIn 3 */
                            {0, 0, 0, 0, /*0 - 3*/},
                        },
                        /* nBiasOut[4][4] */
                        {
                            /*  nBiasOut 0 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 1 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 2 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 3 */
                            {0, 0, 0, 0, /*0 - 3*/},
                        },
                    },
                    /* tNonSens */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {55296, 110592, 221184, 368640, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {110592, 221184, 368640, 442368, /*0 - 3*/},
                        /* nTemporalFilterStrLut[4][17][2] */
                        {
                            /* nTemporalFilterStrLut 0 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nTemporalFilterStrLut 1 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nTemporalFilterStrLut 2 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nTemporalFilterStrLut 3 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                        },
                        /* nVstTemporalFilterStrLut[4][17][2] */
                        {
                            /* nVstTemporalFilterStrLut 0 */
                            {
                                {0, 1136, /*0 - 1*/},
                                {16, 1136, /*0 - 1*/},
                                {32, 1136, /*0 - 1*/},
                                {48, 1236, /*0 - 1*/},
                                {64,  1236, /*0 - 1*/},
                                {80,  1536, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nVstTemporalFilterStrLut 1 */
                            {
                                {0, 1136, /*0 - 1*/},
                                {16, 1136, /*0 - 1*/},
                                {32, 1136, /*0 - 1*/},
                                {48, 1236, /*0 - 1*/},
                                {64,  1236, /*0 - 1*/},
                                {80,  1536, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nVstTemporalFilterStrLut 2 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                            /* nVstTemporalFilterStrLut 3 */
                            {
                                {0, 0, /*0 - 1*/},
                                {16, 256, /*0 - 1*/},
                                {32, 512, /*0 - 1*/},
                                {48, 768, /*0 - 1*/},
                                {64,  1024, /*0 - 1*/},
                                {80,  1280, /*0 - 1*/},
                                {96,  1536, /*0 - 1*/},
                                {112, 1792, /*0 - 1*/},
                                {128, 2048, /*0 - 1*/},
                                {144, 2304, /*0 - 1*/},
                                {160, 2560, /*0 - 1*/},
                                {176, 2816, /*0 - 1*/},
                                {192, 3072, /*0 - 1*/},
                                {208, 3328, /*0 - 1*/},
                                {224, 3584, /*0 - 1*/},
                                {240, 3840, /*0 - 1*/},
                                {255, 4096, /*0 - 1*/},
                            },
                        },
                    },
                    /* tSens */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {55296, 110592, 221184, 368640, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {110592, 221184, 368640, 442368, /*0 - 3*/},
                        /* nSpatialNrStrLut[4][17][2] */
                        {
                            /* nSpatialNrStrLut 0 */
                            {
                                {0, 2500, /*0 - 1*/},
                                {16, 2700, /*0 - 1*/},
                                {32, 2900, /*0 - 1*/},
                                {48, 3100, /*0 - 1*/},
                                {64,  3300, /*0 - 1*/},
                                {80,  3500, /*0 - 1*/},
                                {96,  3500, /*0 - 1*/},
                                {112, 3500, /*0 - 1*/},
                                {128, 3500, /*0 - 1*/},
                                {144, 3500, /*0 - 1*/},
                                {160, 3500, /*0 - 1*/},
                                {176, 3500, /*0 - 1*/},
                                {192, 3500, /*0 - 1*/},
                                {208, 3500, /*0 - 1*/},
                                {224, 3300, /*0 - 1*/},
                                {240, 3100, /*0 - 1*/},
                                {255, 3000, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 1 */
                            {
                                {0, 2600, /*0 - 1*/},
                                {16, 2800, /*0 - 1*/},
                                {32, 3100, /*0 - 1*/},
                                {48, 3400, /*0 - 1*/},
                                {64,  3600, /*0 - 1*/},
                                {80,  3600, /*0 - 1*/},
                                {96,  3600, /*0 - 1*/},
                                {112, 3600, /*0 - 1*/},
                                {128, 3600, /*0 - 1*/},
                                {144, 3600, /*0 - 1*/},
                                {160, 3600, /*0 - 1*/},
                                {176, 3600, /*0 - 1*/},
                                {192, 3600, /*0 - 1*/},
                                {208, 3600, /*0 - 1*/},
                                {224, 3500, /*0 - 1*/},
                                {240, 3300, /*0 - 1*/},
                                {255, 3200, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 2 */
                            {
                                {0, 2800, /*0 - 1*/},
                                {16, 3000, /*0 - 1*/},
                                {32, 3300, /*0 - 1*/},
                                {48, 3600, /*0 - 1*/},
                                {64,  3800, /*0 - 1*/},
                                {80,  3800, /*0 - 1*/},
                                {96,  3800, /*0 - 1*/},
                                {112, 3800, /*0 - 1*/},
                                {128, 3800, /*0 - 1*/},
                                {144, 3800, /*0 - 1*/},
                                {160, 3800, /*0 - 1*/},
                                {176, 3800, /*0 - 1*/},
                                {192, 3800, /*0 - 1*/},
                                {208, 3700, /*0 - 1*/},
                                {224, 3600, /*0 - 1*/},
                                {240, 3500, /*0 - 1*/},
                                {255, 3400, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 3 */
                            {
                                {0, 2800, /*0 - 1*/},
                                {16, 3000, /*0 - 1*/},
                                {32, 3300, /*0 - 1*/},
                                {48, 3600, /*0 - 1*/},
                                {64,  3800, /*0 - 1*/},
                                {80,  3800, /*0 - 1*/},
                                {96,  3800, /*0 - 1*/},
                                {112, 3800, /*0 - 1*/},
                                {128, 3800, /*0 - 1*/},
                                {144, 3800, /*0 - 1*/},
                                {160, 3800, /*0 - 1*/},
                                {176, 3800, /*0 - 1*/},
                                {192, 3800, /*0 - 1*/},
                                {208, 3700, /*0 - 1*/},
                                {224, 3600, /*0 - 1*/},
                                {240, 3500, /*0 - 1*/},
                                {255, 3400, /*0 - 1*/},
                            },
                        },
                    },
                },
            },
        },
    },
};

const static AX_ISP_IQ_RAW2DNR_PARAM_T raw2dnr_param_sdr = {
    /* nRaw2dnrEn */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tGlb */
    {
        /* nMfEnable */
        1,
        /* nHfEnable */
        1,
        /* nLutType */
        0,
        /* nMaskThreshold */
        16,
        /* nMaskLimit[2] */
        {0, 255, /*0 - 1*/},
    },
    /* tManual */
    {
        /* nEdgePreserveRatio */
        128,
        /* nNoiseProfileFactor */
        128,
        /* nHighFreqNrFactor[2][17] */
        {
            {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
        },
        /* nLowFreqNrFactor[2][17] */
        {
            {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
        },
        /* nInterChannelStrength */
        128,
        /* nHfNrStrength[2] */
        {64, 64, /*0 - 1*/},
        /* nMfNrStrength[2] */
        {64, 64, /*0 - 1*/},
    },
    /* tAuto */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nEdgePreserveRatio[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nNoiseProfileFactor[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nHighFreqNrFactor[12][2][17] */
        {
            /* nHighFreqNrFactor 0 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 1 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 2 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 3 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 4 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 5 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 6 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 7 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 8 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 9 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 10 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
            /* nHighFreqNrFactor 11 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 16*/},
            },
        },
        /* nLowFreqNrFactor[12][2][17] */
        {
            /* nLowFreqNrFactor 0 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 1 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 2 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 3 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 4 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 5 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 6 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 7 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 8 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 9 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 10 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
            /* nLowFreqNrFactor 11 */
            {
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
                {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            },
        },
        /* nInterChannelStrength[12] */
        {255, 255, 255, 255, 255, 255, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nHfNrStrength[12][2] */
        {
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {80, 80, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {40, 40, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {16, 16, /*0 - 1*/},
        },
        /* nMfNrStrength[12][2] */
        {
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {80, 80, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {40, 40, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
        },
    },
};

const static AX_ISP_IQ_LSC_PARAM_T lsc_param_sdr = {
    /* nLscEn */
    1,
    /* nRefMode */
    1,
    /* nMeshMode */
    1,
    /* nAutoMode */
    0,
    /* nAlgMode */
    0,
    /* tManualParam */
    {
        /* nLumaRatio */
        100,
        /* nColorRatio */
        100,
        /* nLumaMeshLut[15][19] */
        {
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
        },
        /* nRRMeshLut[15][19] */
        {
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
        },
        /* nGRMeshLut[15][19] */
        {
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
        },
        /* nGBMeshLut[15][19] */
        {
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
        },
        /* nBBMeshLut[15][19] */
        {
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
        },
    },
    /* tAutoParam */
    {
        /* nDampRatio */
        0,
        /* nToleranceRatio */
        0,
        /* tLumaParam */
        {
            /* nParamGrpNum */
            0,
            /* nRefValStart[12] */
            {0, /*0 - 0*/},
            /* nRefValEnd[12] */
            {0, /*0 - 0*/},
            /* nLumaRatio[12] */
            {0, /*0 - 0*/},
            /* nLumaMeshLut[15][19] */
            {
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
            },
        },
        /* tColTempParam */
        {
            /* nColTempNum */
            0,
            /* nRefColorTempStart[8] */
            {0, /*0 - 0*/},
            /* nRefColorTempEnd[8] */
            {0, /*0 - 0*/},
            /* nColorTemp[8] */
            {0, /*0 - 0*/},
            /* nColorRatio[8] */
            {0, /*0 - 0*/},
            /* nRRMeshLut[8][15][19] */
            {
                /* nRRMeshLut 0 */
                {
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                },
            },
            /* nGRMeshLut[8][15][19] */
            {
                /* nGRMeshLut 0 */
                {
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                },
            },
            /* nGBMeshLut[8][15][19] */
            {
                /* nGBMeshLut 0 */
                {
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                },
            },
            /* nBBMeshLut[8][15][19] */
            {
                /* nBBMeshLut 0 */
                {
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                    {16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384, /*0 - 18*/},
                },
            },
        },
    },
};

const static AX_ISP_IQ_RLTM_PARAM_T rltm_param_sdr = {
    /* nRltmEn */
    1,
    /* nMultiCamSyncMode */
    0,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* nAlgMode */
    0,
    /* tCommonGlb */
    {
        /* nGtmSwEn */
        0,
        /* nGtmSwDgain */
        256,
        /* nWinSize */
        512,
    },
    /* tTempoFilter */
    {
        /* nAlpha */
        32768,
        /* nReset */
        0,
        /* nStopUpdating */
        0,
    },
    /* tLumaWt */
    {
        /* nLumaWeight[5] */
        {37, 38, 38, 15, 0, /*0 - 4*/},
    },
    /* tMultiHistWt */
    {
        /* nMode */
        0,
        /* nRegionNum */
        0,
        /* nHistWtNum */
        1,
        /* tRoi */
        {
            /* nTop */
            0,
            /* nBottom */
            1520,
            /* nLeft */
            0,
            /* nRight */
            2688,
        },
        /* tHistWt */
        {
            /* nHistogramWeight[63] */
            {
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
            },
        },
        /* nFlagHistId[16][16] */
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
        },
    },
    /* tLfEnhGlb */
    {
        /* nDownSampleRatio */
        1,
        /* nCoeffWinRad */
        2,
        /* nCoeffEps */
        200,
    },
    /* tManualParam */
    {
        /* nLocalFactor */
        100,
        /* nHighlightSup */
        10,
        /* nKMax */
        65535,
        /* nPreGamma */
        32,
        /* nPostGamma */
        42,
        /* nExtraDgain */
        16,
        /* nRltmStrength */
        64,
        /* nLog10Offset */
        96,
        /* nContrastStrength */
        42,
        /* nBaseGain */
        64,
        /* nDitherMode */
        0,
        /* nDitherScale */
        4,
        /* nHistWtBrightLow[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nHistWtBrightHigh[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nHistWtThreshold[4] */
        {129, 129, 129, 129, /*0 - 3*/},
        /* nSCurveList[1025] */
        {
            0, 139, 235, 320, 398, 472, 542, 609, 674, 738, 799, 859, 918, 976, 1032, 1088, 1143, 1197, 1250, 1302, 1354, 1405, 1456, 1506, 1556, 1605, 1653, 1701, 1749, 1796, 1843, 1890,  /* 0 - 31*/
            1936, 1982, 2028, 2073, 2118, 2162, 2207, 2251, 2295, 2338, 2381, 2424, 2467, 2510, 2552, 2594, 2636, 2678, 2719, 2760, 2801, 2842, 2883, 2924, 2964, 3004, 3044, 3084, 3124, 3163, 3203, 3242,  /* 32 - 63*/
            3281, 3320, 3359, 3397, 3436, 3474, 3512, 3551, 3589, 3626, 3664, 3702, 3739, 3777, 3814, 3851, 3888, 3925, 3962, 3999, 4035, 4072, 4108, 4144, 4181, 4217, 4253, 4289, 4324, 4360, 4396, 4431,  /* 64 - 95*/
            4467, 4502, 4537, 4572, 4608, 4643, 4678, 4712, 4747, 4782, 4816, 4851, 4885, 4920, 4954, 4988, 5022, 5057, 5091, 5125, 5158, 5192, 5226, 5260, 5293, 5327, 5360, 5394, 5427, 5460, 5493, 5527,  /* 96 - 127*/
            5560, 5593, 5626, 5658, 5691, 5724, 5757, 5789, 5822, 5855, 5887, 5920, 5952, 5984, 6016, 6049, 6081, 6113, 6145, 6177, 6209, 6241, 6273, 6304, 6336, 6368, 6400, 6431, 6463, 6494, 6526, 6557,  /* 128 - 159*/
            6588, 6620, 6651, 6682, 6713, 6744, 6776, 6807, 6838, 6869, 6899, 6930, 6961, 6992, 7023, 7053, 7084, 7115, 7145, 7176, 7206, 7237, 7267, 7297, 7328, 7358, 7388, 7418, 7448, 7479, 7509, 7539,  /* 160 - 191*/
            7569, 7599, 7629, 7659, 7688, 7718, 7748, 7778, 7808, 7837, 7867, 7897, 7926, 7956, 7985, 8015, 8044, 8073, 8103, 8132, 8161, 8191, 8220, 8249, 8278, 8308, 8337, 8366, 8395, 8424, 8453, 8482,  /* 192 - 223*/
            8511, 8540, 8568, 8597, 8626, 8655, 8684, 8712, 8741, 8770, 8798, 8827, 8855, 8884, 8912, 8941, 8969, 8998, 9026, 9055, 9083, 9111, 9139, 9168, 9196, 9224, 9252, 9280, 9309, 9337, 9365, 9393,  /* 224 - 255*/
            9421, 9449, 9477, 9505, 9533, 9561, 9589, 9617, 9645, 9673, 9701, 9729, 9757, 9785, 9813, 9841, 9869, 9897, 9925, 9953, 9981, 10009, 10037, 10065, 10093, 10121, 10149, 10177, 10205, 10233, 10261, 10289,  /* 256 - 287*/
            10317, 10345, 10373, 10401, 10429, 10457, 10485, 10513, 10541, 10569, 10597, 10625, 10653, 10681, 10709, 10737, 10765, 10793, 10821, 10849, 10877, 10905, 10933, 10961, 10989, 11017, 11045, 11073, 11101, 11129, 11157, 11185,  /* 288 - 319*/
            11213, 11241, 11269, 11297, 11325, 11353, 11381, 11409, 11437, 11465, 11493, 11521, 11549, 11577, 11605, 11633, 11661, 11689, 11717, 11745, 11773, 11801, 11829, 11857, 11885, 11913, 11941, 11969, 11997, 12025, 12053, 12081,  /* 320 - 351*/
            12109, 12137, 12165, 12193, 12221, 12249, 12277, 12305, 12333, 12361, 12389, 12417, 12445, 12473, 12501, 12529, 12557, 12585, 12613, 12641, 12669, 12697, 12725, 12753, 12781, 12809, 12837, 12865, 12893, 12921, 12949, 12977,  /* 352 - 383*/
            13005, 13033, 13061, 13089, 13117, 13145, 13173, 13201, 13229, 13257, 13285, 13313, 13341, 13369, 13397, 13425, 13453, 13481, 13509, 13537, 13565, 13593, 13621, 13649, 13677, 13705, 13733, 13761, 13789, 13817, 13845, 13873,  /* 384 - 415*/
            13901, 13929, 13957, 13985, 14013, 14041, 14069, 14097, 14125, 14153, 14181, 14209, 14237, 14265, 14293, 14321, 14349, 14377, 14405, 14433, 14461, 14489, 14517, 14545, 14573, 14601, 14629, 14657, 14685, 14713, 14741, 14769,  /* 416 - 447*/
            14797, 14825, 14853, 14881, 14909, 14937, 14965, 14993, 15021, 15049, 15077, 15105, 15133, 15161, 15189, 15217, 15245, 15273, 15301, 15329, 15357, 15385, 15413, 15441, 15469, 15497, 15525, 15553, 15581, 15609, 15637, 15665,  /* 448 - 479*/
            15693, 15721, 15749, 15777, 15805, 15833, 15861, 15889, 15917, 15945, 15973, 16001, 16029, 16057, 16085, 16113, 16141, 16169, 16197, 16225, 16253, 16281, 16309, 16337, 16365, 16393, 16421, 16449, 16477, 16505, 16533, 16561,  /* 480 - 511*/
            16589, 16617, 16645, 16673, 16701, 16729, 16757, 16785, 16813, 16841, 16869, 16897, 16925, 16953, 16981, 17009, 17037, 17065, 17093, 17121, 17149, 17177, 17205, 17233, 17261, 17289, 17317, 17345, 17373, 17401, 17429, 17457,  /* 512 - 543*/
            17485, 17513, 17541, 17569, 17597, 17625, 17653, 17681, 17709, 17737, 17765, 17793, 17821, 17849, 17877, 17905, 17933, 17961, 17989, 18017, 18045, 18073, 18101, 18129, 18157, 18185, 18213, 18241, 18269, 18297, 18325, 18353,  /* 544 - 575*/
            18381, 18409, 18437, 18465, 18493, 18521, 18549, 18577, 18605, 18633, 18661, 18689, 18717, 18745, 18773, 18801, 18829, 18857, 18885, 18913, 18941, 18969, 18997, 19025, 19053, 19081, 19109, 19137, 19165, 19193, 19221, 19249,  /* 576 - 607*/
            19277, 19305, 19333, 19361, 19389, 19417, 19445, 19473, 19501, 19529, 19557, 19585, 19613, 19641, 19669, 19697, 19725, 19753, 19781, 19809, 19837, 19865, 19893, 19921, 19949, 19977, 20005, 20033, 20061, 20089, 20117, 20145,  /* 608 - 639*/
            20173, 20201, 20229, 20257, 20285, 20313, 20341, 20369, 20397, 20425, 20453, 20481, 20509, 20537, 20565, 20593, 20621, 20649, 20677, 20705, 20733, 20761, 20789, 20817, 20845, 20873, 20901, 20929, 20957, 20985, 21013, 21041,  /* 640 - 671*/
            21069, 21097, 21125, 21153, 21181, 21209, 21237, 21265, 21293, 21321, 21349, 21377, 21405, 21433, 21461, 21489, 21517, 21545, 21573, 21601, 21629, 21657, 21685, 21713, 21741, 21769, 21797, 21825, 21853, 21881, 21909, 21937,  /* 672 - 703*/
            21965, 21993, 22021, 22049, 22077, 22105, 22133, 22161, 22189, 22217, 22245, 22273, 22301, 22329, 22357, 22385, 22413, 22441, 22469, 22497, 22525, 22553, 22581, 22609, 22637, 22665, 22693, 22721, 22749, 22777, 22805, 22833,  /* 704 - 735*/
            22861, 22889, 22917, 22945, 22973, 23001, 23029, 23057, 23085, 23113, 23141, 23169, 23197, 23225, 23253, 23281, 23309, 23337, 23365, 23393, 23421, 23449, 23477, 23505, 23533, 23561, 23589, 23617, 23645, 23673, 23701, 23729,  /* 736 - 767*/
            23757, 23785, 23813, 23841, 23869, 23897, 23925, 23953, 23982, 24010, 24038, 24066, 24094, 24123, 24151, 24179, 24208, 24236, 24265, 24293, 24321, 24350, 24378, 24407, 24435, 24464, 24493, 24521, 24550, 24579, 24607, 24636,  /* 768 - 799*/
            24665, 24694, 24722, 24751, 24780, 24809, 24838, 24867, 24896, 24925, 24954, 24983, 25012, 25041, 25070, 25100, 25129, 25158, 25187, 25217, 25246, 25275, 25305, 25334, 25363, 25393, 25422, 25452, 25481, 25511, 25541, 25570,  /* 800 - 831*/
            25600, 25630, 25659, 25689, 25719, 25749, 25779, 25809, 25839, 25869, 25899, 25929, 25959, 25989, 26019, 26049, 26079, 26110, 26140, 26170, 26201, 26231, 26261, 26292, 26322, 26353, 26383, 26414, 26445, 26475, 26506, 26537,  /* 832 - 863*/
            26568, 26599, 26629, 26660, 26691, 26722, 26753, 26784, 26816, 26847, 26878, 26909, 26941, 26972, 27003, 27035, 27066, 27098, 27129, 27161, 27192, 27224, 27256, 27288, 27320, 27351, 27383, 27415, 27447, 27480, 27512, 27544,  /* 864 - 895*/
            27576, 27608, 27641, 27673, 27706, 27738, 27771, 27803, 27836, 27869, 27901, 27934, 27967, 28000, 28033, 28066, 28099, 28132, 28166, 28199, 28232, 28266, 28299, 28333, 28367, 28400, 28434, 28468, 28502, 28536, 28570, 28604,  /* 896 - 927*/
            28638, 28672, 28707, 28741, 28776, 28810, 28845, 28879, 28914, 28949, 28984, 29019, 29054, 29089, 29125, 29160, 29196, 29231, 29267, 29303, 29338, 29374, 29410, 29447, 29483, 29519, 29556, 29592, 29629, 29666, 29702, 29740,  /* 928 - 959*/
            29777, 29814, 29851, 29889, 29926, 29964, 30002, 30040, 30078, 30116, 30155, 30193, 30232, 30271, 30310, 30349, 30388, 30428, 30468, 30508, 30548, 30588, 30628, 30669, 30710, 30751, 30792, 30833, 30875, 30917, 30959, 31002,  /* 960 - 991*/
            31044, 31087, 31131, 31174, 31218, 31262, 31307, 31352, 31397, 31443, 31489, 31535, 31582, 31630, 31677, 31726, 31775, 31825, 31875, 31926, 31978, 32031, 32085, 32140, 32196, 32254, 32313, 32374, 32438, 32506, 32578, 32659,  /* 992 - 1023*/
            32768, /*1024 - 1024*/
        },
        /* tHistWt[16] */
        {
            /* 0 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 1 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 2 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 3 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 4 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 5 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 6 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 7 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 8 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 9 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 10 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 11 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 12 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 13 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 14 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
            /* 15 */
            {
                /* nHistogramWeight[63] */
                {
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                },
            },
        },
        /* tHighFreqEnh */
        {
            /* nDetailSigmaDis */
            8000,
            /* nDetailSigmaVal */
            800,
            /* nDetailCoringPos */
            80,
            /* nDetailCoringNeg */
            50,
            /* nDetailGainPos */
            50,
            /* nDetailGainNeg */
            90,
            /* nDetailExtraStrPos */
            15,
            /* nDetailExtraStrNeg */
            30,
            /* nDetailGainLimitPos */
            65535,
            /* nDetailGainLimitNeg */
            65535,
            /* nSlopeStrengthLut[33] */
            {
                8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                8192, /*32 - 32*/
            },
            /* nSlopeCoeff */
            16384,
        },
        /* tLowFreqEnh */
        {
            /* nRltmDetailLowEn */
            0,
            /* nSigmaDisBlur */
            10000,
            /* nDetailGainPosLow */
            64,
            /* nDetailGainNegLow */
            64,
            /* nDetailLimitPosLow */
            65535,
            /* nDetailLimitNegLow */
            65535,
            /* nSigmaDisPst */
            10000,
            /* nSigmaValPst */
            1000,
        },
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nLocalFactor[12] */
        {110, 110, 110, 110, 110, 110, 110, 100, 100, 90, 90, 90, /*0 - 11*/},
        /* nHighlightSup[12] */
        {10, 10, 10, 10, 10, 10, 10, 10, 12, 14, 15, 15, /*0 - 11*/},
        /* nKMax[12] */
        {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, /*0 - 11*/},
        /* nPreGamma[12] */
        {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, /*0 - 11*/},
        /* nPostGamma[12] */
        {42, 42, 42, 42, 42, 44, 45, 45, 45, 45, 45, 45, /*0 - 11*/},
        /* nExtraDgain[12] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 11*/},
        /* nRltmStrength[12] */
        {64, 64, 72, 80, 80, 80, 80, 80, 72, 64, 64, 64, /*0 - 11*/},
        /* nLog10Offset[12] */
        {96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, /*0 - 11*/},
        /* nContrastStrength[12] */
        {42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, /*0 - 11*/},
        /* nBaseGain[12] */
        {64, 64, 64, 64, 64, 64, 64, 56, 48, 40, 32, 32, /*0 - 11*/},
        /* nDitherMode[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nDitherScale[12] */
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, /*0 - 11*/},
        /* nHistWtBrightLow[12][4] */
        {
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
        },
        /* nHistWtBrightHigh[12][4] */
        {
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
            {0, 0, 0, 0, /*0 - 3*/},
        },
        /* nHistWtThreshold[12][4] */
        {
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
            {129, 129, 129, 129, /*0 - 3*/},
        },
        /* nSCurveList[12][1025] */
        {
            {
                0, 139, 235, 320, 398, 472, 542, 609, 674, 738, 799, 859, 918, 976, 1032, 1088, 1143, 1197, 1250, 1302, 1354, 1405, 1456, 1506, 1556, 1605, 1653, 1701, 1749, 1796, 1843, 1890,  /* 0 - 31*/
                1936, 1982, 2028, 2073, 2118, 2162, 2207, 2251, 2295, 2338, 2381, 2424, 2467, 2510, 2552, 2594, 2636, 2678, 2719, 2760, 2801, 2842, 2883, 2924, 2964, 3004, 3044, 3084, 3124, 3163, 3203, 3242,  /* 32 - 63*/
                3281, 3320, 3359, 3397, 3436, 3474, 3512, 3551, 3589, 3626, 3664, 3702, 3739, 3777, 3814, 3851, 3888, 3925, 3962, 3999, 4035, 4072, 4108, 4144, 4181, 4217, 4253, 4289, 4324, 4360, 4396, 4431,  /* 64 - 95*/
                4467, 4502, 4537, 4572, 4608, 4643, 4678, 4712, 4747, 4782, 4816, 4851, 4885, 4920, 4954, 4988, 5022, 5057, 5091, 5125, 5158, 5192, 5226, 5260, 5293, 5327, 5360, 5394, 5427, 5460, 5493, 5527,  /* 96 - 127*/
                5560, 5593, 5626, 5658, 5691, 5724, 5757, 5789, 5822, 5855, 5887, 5920, 5952, 5984, 6016, 6049, 6081, 6113, 6145, 6177, 6209, 6241, 6273, 6304, 6336, 6368, 6400, 6431, 6463, 6494, 6526, 6557,  /* 128 - 159*/
                6588, 6620, 6651, 6682, 6713, 6744, 6776, 6807, 6838, 6869, 6899, 6930, 6961, 6992, 7023, 7053, 7084, 7115, 7145, 7176, 7206, 7237, 7267, 7297, 7328, 7358, 7388, 7418, 7448, 7479, 7509, 7539,  /* 160 - 191*/
                7569, 7599, 7629, 7659, 7688, 7718, 7748, 7778, 7808, 7837, 7867, 7897, 7926, 7956, 7985, 8015, 8044, 8073, 8103, 8132, 8161, 8191, 8220, 8249, 8278, 8308, 8337, 8366, 8395, 8424, 8453, 8482,  /* 192 - 223*/
                8511, 8540, 8568, 8597, 8626, 8655, 8684, 8712, 8741, 8770, 8798, 8827, 8855, 8884, 8912, 8941, 8969, 8998, 9026, 9055, 9083, 9111, 9139, 9168, 9196, 9224, 9252, 9280, 9309, 9337, 9365, 9393,  /* 224 - 255*/
                9421, 9449, 9477, 9505, 9533, 9561, 9589, 9617, 9645, 9673, 9701, 9729, 9757, 9785, 9813, 9841, 9869, 9897, 9925, 9953, 9981, 10009, 10037, 10065, 10093, 10121, 10149, 10177, 10205, 10233, 10261, 10289,  /* 256 - 287*/
                10317, 10345, 10373, 10401, 10429, 10457, 10485, 10513, 10541, 10569, 10597, 10625, 10653, 10681, 10709, 10737, 10765, 10793, 10821, 10849, 10877, 10905, 10933, 10961, 10989, 11017, 11045, 11073, 11101, 11129, 11157, 11185,  /* 288 - 319*/
                11213, 11241, 11269, 11297, 11325, 11353, 11381, 11409, 11437, 11465, 11493, 11521, 11549, 11577, 11605, 11633, 11661, 11689, 11717, 11745, 11773, 11801, 11829, 11857, 11885, 11913, 11941, 11969, 11997, 12025, 12053, 12081,  /* 320 - 351*/
                12109, 12137, 12165, 12193, 12221, 12249, 12277, 12305, 12333, 12361, 12389, 12417, 12445, 12473, 12501, 12529, 12557, 12585, 12613, 12641, 12669, 12697, 12725, 12753, 12781, 12809, 12837, 12865, 12893, 12921, 12949, 12977,  /* 352 - 383*/
                13005, 13033, 13061, 13089, 13117, 13145, 13173, 13201, 13229, 13257, 13285, 13313, 13341, 13369, 13397, 13425, 13453, 13481, 13509, 13537, 13565, 13593, 13621, 13649, 13677, 13705, 13733, 13761, 13789, 13817, 13845, 13873,  /* 384 - 415*/
                13901, 13929, 13957, 13985, 14013, 14041, 14069, 14097, 14125, 14153, 14181, 14209, 14237, 14265, 14293, 14321, 14349, 14377, 14405, 14433, 14461, 14489, 14517, 14545, 14573, 14601, 14629, 14657, 14685, 14713, 14741, 14769,  /* 416 - 447*/
                14797, 14825, 14853, 14881, 14909, 14937, 14965, 14993, 15021, 15049, 15077, 15105, 15133, 15161, 15189, 15217, 15245, 15273, 15301, 15329, 15357, 15385, 15413, 15441, 15469, 15497, 15525, 15553, 15581, 15609, 15637, 15665,  /* 448 - 479*/
                15693, 15721, 15749, 15777, 15805, 15833, 15861, 15889, 15917, 15945, 15973, 16001, 16029, 16057, 16085, 16113, 16141, 16169, 16197, 16225, 16253, 16281, 16309, 16337, 16365, 16393, 16421, 16449, 16477, 16505, 16533, 16561,  /* 480 - 511*/
                16589, 16617, 16645, 16673, 16701, 16729, 16757, 16785, 16813, 16841, 16869, 16897, 16925, 16953, 16981, 17009, 17037, 17065, 17093, 17121, 17149, 17177, 17205, 17233, 17261, 17289, 17317, 17345, 17373, 17401, 17429, 17457,  /* 512 - 543*/
                17485, 17513, 17541, 17569, 17597, 17625, 17653, 17681, 17709, 17737, 17765, 17793, 17821, 17849, 17877, 17905, 17933, 17961, 17989, 18017, 18045, 18073, 18101, 18129, 18157, 18185, 18213, 18241, 18269, 18297, 18325, 18353,  /* 544 - 575*/
                18381, 18409, 18437, 18465, 18493, 18521, 18549, 18577, 18605, 18633, 18661, 18689, 18717, 18745, 18773, 18801, 18829, 18857, 18885, 18913, 18941, 18969, 18997, 19025, 19053, 19081, 19109, 19137, 19165, 19193, 19221, 19249,  /* 576 - 607*/
                19277, 19305, 19333, 19361, 19389, 19417, 19445, 19473, 19501, 19529, 19557, 19585, 19613, 19641, 19669, 19697, 19725, 19753, 19781, 19809, 19837, 19865, 19893, 19921, 19949, 19977, 20005, 20033, 20061, 20089, 20117, 20145,  /* 608 - 639*/
                20173, 20201, 20229, 20257, 20285, 20313, 20341, 20369, 20397, 20425, 20453, 20481, 20509, 20537, 20565, 20593, 20621, 20649, 20677, 20705, 20733, 20761, 20789, 20817, 20845, 20873, 20901, 20929, 20957, 20985, 21013, 21041,  /* 640 - 671*/
                21069, 21097, 21125, 21153, 21181, 21209, 21237, 21265, 21293, 21321, 21349, 21377, 21405, 21433, 21461, 21489, 21517, 21545, 21573, 21601, 21629, 21657, 21685, 21713, 21741, 21769, 21797, 21825, 21853, 21881, 21909, 21937,  /* 672 - 703*/
                21965, 21993, 22021, 22049, 22077, 22105, 22133, 22161, 22189, 22217, 22245, 22273, 22301, 22329, 22357, 22385, 22413, 22441, 22469, 22497, 22525, 22553, 22581, 22609, 22637, 22665, 22693, 22721, 22749, 22777, 22805, 22833,  /* 704 - 735*/
                22861, 22889, 22917, 22945, 22973, 23001, 23029, 23057, 23085, 23113, 23141, 23169, 23197, 23225, 23253, 23281, 23309, 23337, 23365, 23393, 23421, 23449, 23477, 23505, 23533, 23561, 23589, 23617, 23645, 23673, 23701, 23729,  /* 736 - 767*/
                23757, 23785, 23813, 23841, 23869, 23897, 23925, 23953, 23982, 24010, 24038, 24066, 24094, 24123, 24151, 24179, 24208, 24236, 24265, 24293, 24321, 24350, 24378, 24407, 24435, 24464, 24493, 24521, 24550, 24579, 24607, 24636,  /* 768 - 799*/
                24665, 24694, 24722, 24751, 24780, 24809, 24838, 24867, 24896, 24925, 24954, 24983, 25012, 25041, 25070, 25100, 25129, 25158, 25187, 25217, 25246, 25275, 25305, 25334, 25363, 25393, 25422, 25452, 25481, 25511, 25541, 25570,  /* 800 - 831*/
                25600, 25630, 25659, 25689, 25719, 25749, 25779, 25809, 25839, 25869, 25899, 25929, 25959, 25989, 26019, 26049, 26079, 26110, 26140, 26170, 26201, 26231, 26261, 26292, 26322, 26353, 26383, 26414, 26445, 26475, 26506, 26537,  /* 832 - 863*/
                26568, 26599, 26629, 26660, 26691, 26722, 26753, 26784, 26816, 26847, 26878, 26909, 26941, 26972, 27003, 27035, 27066, 27098, 27129, 27161, 27192, 27224, 27256, 27288, 27320, 27351, 27383, 27415, 27447, 27480, 27512, 27544,  /* 864 - 895*/
                27576, 27608, 27641, 27673, 27706, 27738, 27771, 27803, 27836, 27869, 27901, 27934, 27967, 28000, 28033, 28066, 28099, 28132, 28166, 28199, 28232, 28266, 28299, 28333, 28367, 28400, 28434, 28468, 28502, 28536, 28570, 28604,  /* 896 - 927*/
                28638, 28672, 28707, 28741, 28776, 28810, 28845, 28879, 28914, 28949, 28984, 29019, 29054, 29089, 29125, 29160, 29196, 29231, 29267, 29303, 29338, 29374, 29410, 29447, 29483, 29519, 29556, 29592, 29629, 29666, 29702, 29740,  /* 928 - 959*/
                29777, 29814, 29851, 29889, 29926, 29964, 30002, 30040, 30078, 30116, 30155, 30193, 30232, 30271, 30310, 30349, 30388, 30428, 30468, 30508, 30548, 30588, 30628, 30669, 30710, 30751, 30792, 30833, 30875, 30917, 30959, 31002,  /* 960 - 991*/
                31044, 31087, 31131, 31174, 31218, 31262, 31307, 31352, 31397, 31443, 31489, 31535, 31582, 31630, 31677, 31726, 31775, 31825, 31875, 31926, 31978, 32031, 32085, 32140, 32196, 32254, 32313, 32374, 32438, 32506, 32578, 32659,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 139, 235, 320, 398, 472, 542, 609, 674, 738, 799, 859, 918, 976, 1032, 1088, 1143, 1197, 1250, 1302, 1354, 1405, 1456, 1506, 1556, 1605, 1653, 1701, 1749, 1796, 1843, 1890,  /* 0 - 31*/
                1936, 1982, 2028, 2073, 2118, 2162, 2207, 2251, 2295, 2338, 2381, 2424, 2467, 2510, 2552, 2594, 2636, 2678, 2719, 2760, 2801, 2842, 2883, 2924, 2964, 3004, 3044, 3084, 3124, 3163, 3203, 3242,  /* 32 - 63*/
                3281, 3320, 3359, 3397, 3436, 3474, 3512, 3551, 3589, 3626, 3664, 3702, 3739, 3777, 3814, 3851, 3888, 3925, 3962, 3999, 4035, 4072, 4108, 4144, 4181, 4217, 4253, 4289, 4324, 4360, 4396, 4431,  /* 64 - 95*/
                4467, 4502, 4537, 4572, 4608, 4643, 4678, 4712, 4747, 4782, 4816, 4851, 4885, 4920, 4954, 4988, 5022, 5057, 5091, 5125, 5158, 5192, 5226, 5260, 5293, 5327, 5360, 5394, 5427, 5460, 5493, 5527,  /* 96 - 127*/
                5560, 5593, 5626, 5658, 5691, 5724, 5757, 5789, 5822, 5855, 5887, 5920, 5952, 5984, 6016, 6049, 6081, 6113, 6145, 6177, 6209, 6241, 6273, 6304, 6336, 6368, 6400, 6431, 6463, 6494, 6526, 6557,  /* 128 - 159*/
                6588, 6620, 6651, 6682, 6713, 6744, 6776, 6807, 6838, 6869, 6899, 6930, 6961, 6992, 7023, 7053, 7084, 7115, 7145, 7176, 7206, 7237, 7267, 7297, 7328, 7358, 7388, 7418, 7448, 7479, 7509, 7539,  /* 160 - 191*/
                7569, 7599, 7629, 7659, 7688, 7718, 7748, 7778, 7808, 7837, 7867, 7897, 7926, 7956, 7985, 8015, 8044, 8073, 8103, 8132, 8161, 8191, 8220, 8249, 8278, 8308, 8337, 8366, 8395, 8424, 8453, 8482,  /* 192 - 223*/
                8511, 8540, 8568, 8597, 8626, 8655, 8684, 8712, 8741, 8770, 8798, 8827, 8855, 8884, 8912, 8941, 8969, 8998, 9026, 9055, 9083, 9111, 9139, 9168, 9196, 9224, 9252, 9280, 9309, 9337, 9365, 9393,  /* 224 - 255*/
                9421, 9449, 9477, 9505, 9533, 9561, 9589, 9617, 9645, 9673, 9701, 9729, 9757, 9785, 9813, 9841, 9869, 9897, 9925, 9953, 9981, 10009, 10037, 10065, 10093, 10121, 10149, 10177, 10205, 10233, 10261, 10289,  /* 256 - 287*/
                10317, 10345, 10373, 10401, 10429, 10457, 10485, 10513, 10541, 10569, 10597, 10625, 10653, 10681, 10709, 10737, 10765, 10793, 10821, 10849, 10877, 10905, 10933, 10961, 10989, 11017, 11045, 11073, 11101, 11129, 11157, 11185,  /* 288 - 319*/
                11213, 11241, 11269, 11297, 11325, 11353, 11381, 11409, 11437, 11465, 11493, 11521, 11549, 11577, 11605, 11633, 11661, 11689, 11717, 11745, 11773, 11801, 11829, 11857, 11885, 11913, 11941, 11969, 11997, 12025, 12053, 12081,  /* 320 - 351*/
                12109, 12137, 12165, 12193, 12221, 12249, 12277, 12305, 12333, 12361, 12389, 12417, 12445, 12473, 12501, 12529, 12557, 12585, 12613, 12641, 12669, 12697, 12725, 12753, 12781, 12809, 12837, 12865, 12893, 12921, 12949, 12977,  /* 352 - 383*/
                13005, 13033, 13061, 13089, 13117, 13145, 13173, 13201, 13229, 13257, 13285, 13313, 13341, 13369, 13397, 13425, 13453, 13481, 13509, 13537, 13565, 13593, 13621, 13649, 13677, 13705, 13733, 13761, 13789, 13817, 13845, 13873,  /* 384 - 415*/
                13901, 13929, 13957, 13985, 14013, 14041, 14069, 14097, 14125, 14153, 14181, 14209, 14237, 14265, 14293, 14321, 14349, 14377, 14405, 14433, 14461, 14489, 14517, 14545, 14573, 14601, 14629, 14657, 14685, 14713, 14741, 14769,  /* 416 - 447*/
                14797, 14825, 14853, 14881, 14909, 14937, 14965, 14993, 15021, 15049, 15077, 15105, 15133, 15161, 15189, 15217, 15245, 15273, 15301, 15329, 15357, 15385, 15413, 15441, 15469, 15497, 15525, 15553, 15581, 15609, 15637, 15665,  /* 448 - 479*/
                15693, 15721, 15749, 15777, 15805, 15833, 15861, 15889, 15917, 15945, 15973, 16001, 16029, 16057, 16085, 16113, 16141, 16169, 16197, 16225, 16253, 16281, 16309, 16337, 16365, 16393, 16421, 16449, 16477, 16505, 16533, 16561,  /* 480 - 511*/
                16589, 16617, 16645, 16673, 16701, 16729, 16757, 16785, 16813, 16841, 16869, 16897, 16925, 16953, 16981, 17009, 17037, 17065, 17093, 17121, 17149, 17177, 17205, 17233, 17261, 17289, 17317, 17345, 17373, 17401, 17429, 17457,  /* 512 - 543*/
                17485, 17513, 17541, 17569, 17597, 17625, 17653, 17681, 17709, 17737, 17765, 17793, 17821, 17849, 17877, 17905, 17933, 17961, 17989, 18017, 18045, 18073, 18101, 18129, 18157, 18185, 18213, 18241, 18269, 18297, 18325, 18353,  /* 544 - 575*/
                18381, 18409, 18437, 18465, 18493, 18521, 18549, 18577, 18605, 18633, 18661, 18689, 18717, 18745, 18773, 18801, 18829, 18857, 18885, 18913, 18941, 18969, 18997, 19025, 19053, 19081, 19109, 19137, 19165, 19193, 19221, 19249,  /* 576 - 607*/
                19277, 19305, 19333, 19361, 19389, 19417, 19445, 19473, 19501, 19529, 19557, 19585, 19613, 19641, 19669, 19697, 19725, 19753, 19781, 19809, 19837, 19865, 19893, 19921, 19949, 19977, 20005, 20033, 20061, 20089, 20117, 20145,  /* 608 - 639*/
                20173, 20201, 20229, 20257, 20285, 20313, 20341, 20369, 20397, 20425, 20453, 20481, 20509, 20537, 20565, 20593, 20621, 20649, 20677, 20705, 20733, 20761, 20789, 20817, 20845, 20873, 20901, 20929, 20957, 20985, 21013, 21041,  /* 640 - 671*/
                21069, 21097, 21125, 21153, 21181, 21209, 21237, 21265, 21293, 21321, 21349, 21377, 21405, 21433, 21461, 21489, 21517, 21545, 21573, 21601, 21629, 21657, 21685, 21713, 21741, 21769, 21797, 21825, 21853, 21881, 21909, 21937,  /* 672 - 703*/
                21965, 21993, 22021, 22049, 22077, 22105, 22133, 22161, 22189, 22217, 22245, 22273, 22301, 22329, 22357, 22385, 22413, 22441, 22469, 22497, 22525, 22553, 22581, 22609, 22637, 22665, 22693, 22721, 22749, 22777, 22805, 22833,  /* 704 - 735*/
                22861, 22889, 22917, 22945, 22973, 23001, 23029, 23057, 23085, 23113, 23141, 23169, 23197, 23225, 23253, 23281, 23309, 23337, 23365, 23393, 23421, 23449, 23477, 23505, 23533, 23561, 23589, 23617, 23645, 23673, 23701, 23729,  /* 736 - 767*/
                23757, 23785, 23813, 23841, 23869, 23897, 23925, 23953, 23982, 24010, 24038, 24066, 24094, 24123, 24151, 24179, 24208, 24236, 24265, 24293, 24321, 24350, 24378, 24407, 24435, 24464, 24493, 24521, 24550, 24579, 24607, 24636,  /* 768 - 799*/
                24665, 24694, 24722, 24751, 24780, 24809, 24838, 24867, 24896, 24925, 24954, 24983, 25012, 25041, 25070, 25100, 25129, 25158, 25187, 25217, 25246, 25275, 25305, 25334, 25363, 25393, 25422, 25452, 25481, 25511, 25541, 25570,  /* 800 - 831*/
                25600, 25630, 25659, 25689, 25719, 25749, 25779, 25809, 25839, 25869, 25899, 25929, 25959, 25989, 26019, 26049, 26079, 26110, 26140, 26170, 26201, 26231, 26261, 26292, 26322, 26353, 26383, 26414, 26445, 26475, 26506, 26537,  /* 832 - 863*/
                26568, 26599, 26629, 26660, 26691, 26722, 26753, 26784, 26816, 26847, 26878, 26909, 26941, 26972, 27003, 27035, 27066, 27098, 27129, 27161, 27192, 27224, 27256, 27288, 27320, 27351, 27383, 27415, 27447, 27480, 27512, 27544,  /* 864 - 895*/
                27576, 27608, 27641, 27673, 27706, 27738, 27771, 27803, 27836, 27869, 27901, 27934, 27967, 28000, 28033, 28066, 28099, 28132, 28166, 28199, 28232, 28266, 28299, 28333, 28367, 28400, 28434, 28468, 28502, 28536, 28570, 28604,  /* 896 - 927*/
                28638, 28672, 28707, 28741, 28776, 28810, 28845, 28879, 28914, 28949, 28984, 29019, 29054, 29089, 29125, 29160, 29196, 29231, 29267, 29303, 29338, 29374, 29410, 29447, 29483, 29519, 29556, 29592, 29629, 29666, 29702, 29740,  /* 928 - 959*/
                29777, 29814, 29851, 29889, 29926, 29964, 30002, 30040, 30078, 30116, 30155, 30193, 30232, 30271, 30310, 30349, 30388, 30428, 30468, 30508, 30548, 30588, 30628, 30669, 30710, 30751, 30792, 30833, 30875, 30917, 30959, 31002,  /* 960 - 991*/
                31044, 31087, 31131, 31174, 31218, 31262, 31307, 31352, 31397, 31443, 31489, 31535, 31582, 31630, 31677, 31726, 31775, 31825, 31875, 31926, 31978, 32031, 32085, 32140, 32196, 32254, 32313, 32374, 32438, 32506, 32578, 32659,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 139, 235, 320, 398, 472, 542, 609, 674, 738, 799, 859, 918, 976, 1032, 1088, 1143, 1197, 1250, 1302, 1354, 1405, 1456, 1506, 1556, 1605, 1653, 1701, 1749, 1796, 1843, 1890,  /* 0 - 31*/
                1936, 1982, 2028, 2073, 2118, 2162, 2207, 2251, 2295, 2338, 2381, 2424, 2467, 2510, 2552, 2594, 2636, 2678, 2719, 2760, 2801, 2842, 2883, 2924, 2964, 3004, 3044, 3084, 3124, 3163, 3203, 3242,  /* 32 - 63*/
                3281, 3320, 3359, 3397, 3436, 3474, 3512, 3551, 3589, 3626, 3664, 3702, 3739, 3777, 3814, 3851, 3888, 3925, 3962, 3999, 4035, 4072, 4108, 4144, 4181, 4217, 4253, 4289, 4324, 4360, 4396, 4431,  /* 64 - 95*/
                4467, 4502, 4537, 4572, 4608, 4643, 4678, 4712, 4747, 4782, 4816, 4851, 4885, 4920, 4954, 4988, 5022, 5057, 5091, 5125, 5158, 5192, 5226, 5260, 5293, 5327, 5360, 5394, 5427, 5460, 5493, 5527,  /* 96 - 127*/
                5560, 5593, 5626, 5658, 5691, 5724, 5757, 5789, 5822, 5855, 5887, 5920, 5952, 5984, 6016, 6049, 6081, 6113, 6145, 6177, 6209, 6241, 6273, 6304, 6336, 6368, 6400, 6431, 6463, 6494, 6526, 6557,  /* 128 - 159*/
                6588, 6620, 6651, 6682, 6713, 6744, 6776, 6807, 6838, 6869, 6899, 6930, 6961, 6992, 7023, 7053, 7084, 7115, 7145, 7176, 7206, 7237, 7267, 7297, 7328, 7358, 7388, 7418, 7448, 7479, 7509, 7539,  /* 160 - 191*/
                7569, 7599, 7629, 7659, 7688, 7718, 7748, 7778, 7808, 7837, 7867, 7897, 7926, 7956, 7985, 8015, 8044, 8073, 8103, 8132, 8161, 8191, 8220, 8249, 8278, 8308, 8337, 8366, 8395, 8424, 8453, 8482,  /* 192 - 223*/
                8511, 8540, 8568, 8597, 8626, 8655, 8684, 8712, 8741, 8770, 8798, 8827, 8855, 8884, 8912, 8941, 8969, 8998, 9026, 9055, 9083, 9111, 9139, 9168, 9196, 9224, 9252, 9280, 9309, 9337, 9365, 9393,  /* 224 - 255*/
                9421, 9449, 9477, 9505, 9533, 9561, 9589, 9617, 9645, 9673, 9701, 9729, 9757, 9785, 9813, 9841, 9869, 9897, 9925, 9953, 9981, 10009, 10037, 10065, 10093, 10121, 10149, 10177, 10205, 10233, 10261, 10289,  /* 256 - 287*/
                10317, 10345, 10373, 10401, 10429, 10457, 10485, 10513, 10541, 10569, 10597, 10625, 10653, 10681, 10709, 10737, 10765, 10793, 10821, 10849, 10877, 10905, 10933, 10961, 10989, 11017, 11045, 11073, 11101, 11129, 11157, 11185,  /* 288 - 319*/
                11213, 11241, 11269, 11297, 11325, 11353, 11381, 11409, 11437, 11465, 11493, 11521, 11549, 11577, 11605, 11633, 11661, 11689, 11717, 11745, 11773, 11801, 11829, 11857, 11885, 11913, 11941, 11969, 11997, 12025, 12053, 12081,  /* 320 - 351*/
                12109, 12137, 12165, 12193, 12221, 12249, 12277, 12305, 12333, 12361, 12389, 12417, 12445, 12473, 12501, 12529, 12557, 12585, 12613, 12641, 12669, 12697, 12725, 12753, 12781, 12809, 12837, 12865, 12893, 12921, 12949, 12977,  /* 352 - 383*/
                13005, 13033, 13061, 13089, 13117, 13145, 13173, 13201, 13229, 13257, 13285, 13313, 13341, 13369, 13397, 13425, 13453, 13481, 13509, 13537, 13565, 13593, 13621, 13649, 13677, 13705, 13733, 13761, 13789, 13817, 13845, 13873,  /* 384 - 415*/
                13901, 13929, 13957, 13985, 14013, 14041, 14069, 14097, 14125, 14153, 14181, 14209, 14237, 14265, 14293, 14321, 14349, 14377, 14405, 14433, 14461, 14489, 14517, 14545, 14573, 14601, 14629, 14657, 14685, 14713, 14741, 14769,  /* 416 - 447*/
                14797, 14825, 14853, 14881, 14909, 14937, 14965, 14993, 15021, 15049, 15077, 15105, 15133, 15161, 15189, 15217, 15245, 15273, 15301, 15329, 15357, 15385, 15413, 15441, 15469, 15497, 15525, 15553, 15581, 15609, 15637, 15665,  /* 448 - 479*/
                15693, 15721, 15749, 15777, 15805, 15833, 15861, 15889, 15917, 15945, 15973, 16001, 16029, 16057, 16085, 16113, 16141, 16169, 16197, 16225, 16253, 16281, 16309, 16337, 16365, 16393, 16421, 16449, 16477, 16505, 16533, 16561,  /* 480 - 511*/
                16589, 16617, 16645, 16673, 16701, 16729, 16757, 16785, 16813, 16841, 16869, 16897, 16925, 16953, 16981, 17009, 17037, 17065, 17093, 17121, 17149, 17177, 17205, 17233, 17261, 17289, 17317, 17345, 17373, 17401, 17429, 17457,  /* 512 - 543*/
                17485, 17513, 17541, 17569, 17597, 17625, 17653, 17681, 17709, 17737, 17765, 17793, 17821, 17849, 17877, 17905, 17933, 17961, 17989, 18017, 18045, 18073, 18101, 18129, 18157, 18185, 18213, 18241, 18269, 18297, 18325, 18353,  /* 544 - 575*/
                18381, 18409, 18437, 18465, 18493, 18521, 18549, 18577, 18605, 18633, 18661, 18689, 18717, 18745, 18773, 18801, 18829, 18857, 18885, 18913, 18941, 18969, 18997, 19025, 19053, 19081, 19109, 19137, 19165, 19193, 19221, 19249,  /* 576 - 607*/
                19277, 19305, 19333, 19361, 19389, 19417, 19445, 19473, 19501, 19529, 19557, 19585, 19613, 19641, 19669, 19697, 19725, 19753, 19781, 19809, 19837, 19865, 19893, 19921, 19949, 19977, 20005, 20033, 20061, 20089, 20117, 20145,  /* 608 - 639*/
                20173, 20201, 20229, 20257, 20285, 20313, 20341, 20369, 20397, 20425, 20453, 20481, 20509, 20537, 20565, 20593, 20621, 20649, 20677, 20705, 20733, 20761, 20789, 20817, 20845, 20873, 20901, 20929, 20957, 20985, 21013, 21041,  /* 640 - 671*/
                21069, 21097, 21125, 21153, 21181, 21209, 21237, 21265, 21293, 21321, 21349, 21377, 21405, 21433, 21461, 21489, 21517, 21545, 21573, 21601, 21629, 21657, 21685, 21713, 21741, 21769, 21797, 21825, 21853, 21881, 21909, 21937,  /* 672 - 703*/
                21965, 21993, 22021, 22049, 22077, 22105, 22133, 22161, 22189, 22217, 22245, 22273, 22301, 22329, 22357, 22385, 22413, 22441, 22469, 22497, 22525, 22553, 22581, 22609, 22637, 22665, 22693, 22721, 22749, 22777, 22805, 22833,  /* 704 - 735*/
                22861, 22889, 22917, 22945, 22973, 23001, 23029, 23057, 23085, 23113, 23141, 23169, 23197, 23225, 23253, 23281, 23309, 23337, 23365, 23393, 23421, 23449, 23477, 23505, 23533, 23561, 23589, 23617, 23645, 23673, 23701, 23729,  /* 736 - 767*/
                23757, 23785, 23813, 23841, 23869, 23897, 23925, 23953, 23982, 24010, 24038, 24066, 24094, 24123, 24151, 24179, 24208, 24236, 24265, 24293, 24321, 24350, 24378, 24407, 24435, 24464, 24493, 24521, 24550, 24579, 24607, 24636,  /* 768 - 799*/
                24665, 24694, 24722, 24751, 24780, 24809, 24838, 24867, 24896, 24925, 24954, 24983, 25012, 25041, 25070, 25100, 25129, 25158, 25187, 25217, 25246, 25275, 25305, 25334, 25363, 25393, 25422, 25452, 25481, 25511, 25541, 25570,  /* 800 - 831*/
                25600, 25630, 25659, 25689, 25719, 25749, 25779, 25809, 25839, 25869, 25899, 25929, 25959, 25989, 26019, 26049, 26079, 26110, 26140, 26170, 26201, 26231, 26261, 26292, 26322, 26353, 26383, 26414, 26445, 26475, 26506, 26537,  /* 832 - 863*/
                26568, 26599, 26629, 26660, 26691, 26722, 26753, 26784, 26816, 26847, 26878, 26909, 26941, 26972, 27003, 27035, 27066, 27098, 27129, 27161, 27192, 27224, 27256, 27288, 27320, 27351, 27383, 27415, 27447, 27480, 27512, 27544,  /* 864 - 895*/
                27576, 27608, 27641, 27673, 27706, 27738, 27771, 27803, 27836, 27869, 27901, 27934, 27967, 28000, 28033, 28066, 28099, 28132, 28166, 28199, 28232, 28266, 28299, 28333, 28367, 28400, 28434, 28468, 28502, 28536, 28570, 28604,  /* 896 - 927*/
                28638, 28672, 28707, 28741, 28776, 28810, 28845, 28879, 28914, 28949, 28984, 29019, 29054, 29089, 29125, 29160, 29196, 29231, 29267, 29303, 29338, 29374, 29410, 29447, 29483, 29519, 29556, 29592, 29629, 29666, 29702, 29740,  /* 928 - 959*/
                29777, 29814, 29851, 29889, 29926, 29964, 30002, 30040, 30078, 30116, 30155, 30193, 30232, 30271, 30310, 30349, 30388, 30428, 30468, 30508, 30548, 30588, 30628, 30669, 30710, 30751, 30792, 30833, 30875, 30917, 30959, 31002,  /* 960 - 991*/
                31044, 31087, 31131, 31174, 31218, 31262, 31307, 31352, 31397, 31443, 31489, 31535, 31582, 31630, 31677, 31726, 31775, 31825, 31875, 31926, 31978, 32031, 32085, 32140, 32196, 32254, 32313, 32374, 32438, 32506, 32578, 32659,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 139, 235, 320, 398, 472, 542, 609, 674, 738, 799, 859, 918, 976, 1032, 1088, 1143, 1197, 1250, 1302, 1354, 1405, 1456, 1506, 1556, 1605, 1653, 1701, 1749, 1796, 1843, 1890,  /* 0 - 31*/
                1936, 1982, 2028, 2073, 2118, 2162, 2207, 2251, 2295, 2338, 2381, 2424, 2467, 2510, 2552, 2594, 2636, 2678, 2719, 2760, 2801, 2842, 2883, 2924, 2964, 3004, 3044, 3084, 3124, 3163, 3203, 3242,  /* 32 - 63*/
                3281, 3320, 3359, 3397, 3436, 3474, 3512, 3551, 3589, 3626, 3664, 3702, 3739, 3777, 3814, 3851, 3888, 3925, 3962, 3999, 4035, 4072, 4108, 4144, 4181, 4217, 4253, 4289, 4324, 4360, 4396, 4431,  /* 64 - 95*/
                4467, 4502, 4537, 4572, 4608, 4643, 4678, 4712, 4747, 4782, 4816, 4851, 4885, 4920, 4954, 4988, 5022, 5057, 5091, 5125, 5158, 5192, 5226, 5260, 5293, 5327, 5360, 5394, 5427, 5460, 5493, 5527,  /* 96 - 127*/
                5560, 5593, 5626, 5658, 5691, 5724, 5757, 5789, 5822, 5855, 5887, 5920, 5952, 5984, 6016, 6049, 6081, 6113, 6145, 6177, 6209, 6241, 6273, 6304, 6336, 6368, 6400, 6431, 6463, 6494, 6526, 6557,  /* 128 - 159*/
                6588, 6620, 6651, 6682, 6713, 6744, 6776, 6807, 6838, 6869, 6899, 6930, 6961, 6992, 7023, 7053, 7084, 7115, 7145, 7176, 7206, 7237, 7267, 7297, 7328, 7358, 7388, 7418, 7448, 7479, 7509, 7539,  /* 160 - 191*/
                7569, 7599, 7629, 7659, 7688, 7718, 7748, 7778, 7808, 7837, 7867, 7897, 7926, 7956, 7985, 8015, 8044, 8073, 8103, 8132, 8161, 8191, 8220, 8249, 8278, 8308, 8337, 8366, 8395, 8424, 8453, 8482,  /* 192 - 223*/
                8511, 8540, 8568, 8597, 8626, 8655, 8684, 8712, 8741, 8770, 8798, 8827, 8855, 8884, 8912, 8941, 8969, 8998, 9026, 9055, 9083, 9111, 9139, 9168, 9196, 9224, 9252, 9280, 9309, 9337, 9365, 9393,  /* 224 - 255*/
                9421, 9449, 9477, 9505, 9533, 9561, 9589, 9617, 9645, 9673, 9701, 9729, 9757, 9785, 9813, 9841, 9869, 9897, 9925, 9953, 9981, 10009, 10037, 10065, 10093, 10121, 10149, 10177, 10205, 10233, 10261, 10289,  /* 256 - 287*/
                10317, 10345, 10373, 10401, 10429, 10457, 10485, 10513, 10541, 10569, 10597, 10625, 10653, 10681, 10709, 10737, 10765, 10793, 10821, 10849, 10877, 10905, 10933, 10961, 10989, 11017, 11045, 11073, 11101, 11129, 11157, 11185,  /* 288 - 319*/
                11213, 11241, 11269, 11297, 11325, 11353, 11381, 11409, 11437, 11465, 11493, 11521, 11549, 11577, 11605, 11633, 11661, 11689, 11717, 11745, 11773, 11801, 11829, 11857, 11885, 11913, 11941, 11969, 11997, 12025, 12053, 12081,  /* 320 - 351*/
                12109, 12137, 12165, 12193, 12221, 12249, 12277, 12305, 12333, 12361, 12389, 12417, 12445, 12473, 12501, 12529, 12557, 12585, 12613, 12641, 12669, 12697, 12725, 12753, 12781, 12809, 12837, 12865, 12893, 12921, 12949, 12977,  /* 352 - 383*/
                13005, 13033, 13061, 13089, 13117, 13145, 13173, 13201, 13229, 13257, 13285, 13313, 13341, 13369, 13397, 13425, 13453, 13481, 13509, 13537, 13565, 13593, 13621, 13649, 13677, 13705, 13733, 13761, 13789, 13817, 13845, 13873,  /* 384 - 415*/
                13901, 13929, 13957, 13985, 14013, 14041, 14069, 14097, 14125, 14153, 14181, 14209, 14237, 14265, 14293, 14321, 14349, 14377, 14405, 14433, 14461, 14489, 14517, 14545, 14573, 14601, 14629, 14657, 14685, 14713, 14741, 14769,  /* 416 - 447*/
                14797, 14825, 14853, 14881, 14909, 14937, 14965, 14993, 15021, 15049, 15077, 15105, 15133, 15161, 15189, 15217, 15245, 15273, 15301, 15329, 15357, 15385, 15413, 15441, 15469, 15497, 15525, 15553, 15581, 15609, 15637, 15665,  /* 448 - 479*/
                15693, 15721, 15749, 15777, 15805, 15833, 15861, 15889, 15917, 15945, 15973, 16001, 16029, 16057, 16085, 16113, 16141, 16169, 16197, 16225, 16253, 16281, 16309, 16337, 16365, 16393, 16421, 16449, 16477, 16505, 16533, 16561,  /* 480 - 511*/
                16589, 16617, 16645, 16673, 16701, 16729, 16757, 16785, 16813, 16841, 16869, 16897, 16925, 16953, 16981, 17009, 17037, 17065, 17093, 17121, 17149, 17177, 17205, 17233, 17261, 17289, 17317, 17345, 17373, 17401, 17429, 17457,  /* 512 - 543*/
                17485, 17513, 17541, 17569, 17597, 17625, 17653, 17681, 17709, 17737, 17765, 17793, 17821, 17849, 17877, 17905, 17933, 17961, 17989, 18017, 18045, 18073, 18101, 18129, 18157, 18185, 18213, 18241, 18269, 18297, 18325, 18353,  /* 544 - 575*/
                18381, 18409, 18437, 18465, 18493, 18521, 18549, 18577, 18605, 18633, 18661, 18689, 18717, 18745, 18773, 18801, 18829, 18857, 18885, 18913, 18941, 18969, 18997, 19025, 19053, 19081, 19109, 19137, 19165, 19193, 19221, 19249,  /* 576 - 607*/
                19277, 19305, 19333, 19361, 19389, 19417, 19445, 19473, 19501, 19529, 19557, 19585, 19613, 19641, 19669, 19697, 19725, 19753, 19781, 19809, 19837, 19865, 19893, 19921, 19949, 19977, 20005, 20033, 20061, 20089, 20117, 20145,  /* 608 - 639*/
                20173, 20201, 20229, 20257, 20285, 20313, 20341, 20369, 20397, 20425, 20453, 20481, 20509, 20537, 20565, 20593, 20621, 20649, 20677, 20705, 20733, 20761, 20789, 20817, 20845, 20873, 20901, 20929, 20957, 20985, 21013, 21041,  /* 640 - 671*/
                21069, 21097, 21125, 21153, 21181, 21209, 21237, 21265, 21293, 21321, 21349, 21377, 21405, 21433, 21461, 21489, 21517, 21545, 21573, 21601, 21629, 21657, 21685, 21713, 21741, 21769, 21797, 21825, 21853, 21881, 21909, 21937,  /* 672 - 703*/
                21965, 21993, 22021, 22049, 22077, 22105, 22133, 22161, 22189, 22217, 22245, 22273, 22301, 22329, 22357, 22385, 22413, 22441, 22469, 22497, 22525, 22553, 22581, 22609, 22637, 22665, 22693, 22721, 22749, 22777, 22805, 22833,  /* 704 - 735*/
                22861, 22889, 22917, 22945, 22973, 23001, 23029, 23057, 23085, 23113, 23141, 23169, 23197, 23225, 23253, 23281, 23309, 23337, 23365, 23393, 23421, 23449, 23477, 23505, 23533, 23561, 23589, 23617, 23645, 23673, 23701, 23729,  /* 736 - 767*/
                23757, 23785, 23813, 23841, 23869, 23897, 23925, 23953, 23982, 24010, 24038, 24066, 24094, 24123, 24151, 24179, 24208, 24236, 24265, 24293, 24321, 24350, 24378, 24407, 24435, 24464, 24493, 24521, 24550, 24579, 24607, 24636,  /* 768 - 799*/
                24665, 24694, 24722, 24751, 24780, 24809, 24838, 24867, 24896, 24925, 24954, 24983, 25012, 25041, 25070, 25100, 25129, 25158, 25187, 25217, 25246, 25275, 25305, 25334, 25363, 25393, 25422, 25452, 25481, 25511, 25541, 25570,  /* 800 - 831*/
                25600, 25630, 25659, 25689, 25719, 25749, 25779, 25809, 25839, 25869, 25899, 25929, 25959, 25989, 26019, 26049, 26079, 26110, 26140, 26170, 26201, 26231, 26261, 26292, 26322, 26353, 26383, 26414, 26445, 26475, 26506, 26537,  /* 832 - 863*/
                26568, 26599, 26629, 26660, 26691, 26722, 26753, 26784, 26816, 26847, 26878, 26909, 26941, 26972, 27003, 27035, 27066, 27098, 27129, 27161, 27192, 27224, 27256, 27288, 27320, 27351, 27383, 27415, 27447, 27480, 27512, 27544,  /* 864 - 895*/
                27576, 27608, 27641, 27673, 27706, 27738, 27771, 27803, 27836, 27869, 27901, 27934, 27967, 28000, 28033, 28066, 28099, 28132, 28166, 28199, 28232, 28266, 28299, 28333, 28367, 28400, 28434, 28468, 28502, 28536, 28570, 28604,  /* 896 - 927*/
                28638, 28672, 28707, 28741, 28776, 28810, 28845, 28879, 28914, 28949, 28984, 29019, 29054, 29089, 29125, 29160, 29196, 29231, 29267, 29303, 29338, 29374, 29410, 29447, 29483, 29519, 29556, 29592, 29629, 29666, 29702, 29740,  /* 928 - 959*/
                29777, 29814, 29851, 29889, 29926, 29964, 30002, 30040, 30078, 30116, 30155, 30193, 30232, 30271, 30310, 30349, 30388, 30428, 30468, 30508, 30548, 30588, 30628, 30669, 30710, 30751, 30792, 30833, 30875, 30917, 30959, 31002,  /* 960 - 991*/
                31044, 31087, 31131, 31174, 31218, 31262, 31307, 31352, 31397, 31443, 31489, 31535, 31582, 31630, 31677, 31726, 31775, 31825, 31875, 31926, 31978, 32031, 32085, 32140, 32196, 32254, 32313, 32374, 32438, 32506, 32578, 32659,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 156, 261, 352, 436, 514, 588, 659, 727, 793, 857, 920, 981, 1041, 1100, 1157, 1214, 1269, 1324, 1378, 1431, 1484, 1536, 1587, 1638, 1688, 1738, 1787, 1835, 1884, 1931, 1979,  /* 0 - 31*/
                2026, 2072, 2119, 2164, 2210, 2255, 2300, 2345, 2389, 2433, 2477, 2520, 2563, 2606, 2649, 2691, 2734, 2776, 2817, 2859, 2900, 2941, 2982, 3023, 3064, 3104, 3144, 3184, 3224, 3263, 3303, 3342,  /* 32 - 63*/
                3381, 3420, 3459, 3498, 3536, 3575, 3613, 3651, 3689, 3727, 3764, 3802, 3839, 3877, 3914, 3951, 3988, 4024, 4061, 4098, 4134, 4170, 4207, 4243, 4279, 4315, 4350, 4386, 4422, 4457, 4492, 4528,  /* 64 - 95*/
                4563, 4598, 4633, 4668, 4703, 4737, 4772, 4807, 4841, 4875, 4910, 4944, 4978, 5012, 5046, 5080, 5114, 5147, 5181, 5214, 5248, 5281, 5315, 5348, 5381, 5414, 5447, 5480, 5513, 5546, 5579, 5611,  /* 96 - 127*/
                5644, 5677, 5709, 5741, 5774, 5806, 5838, 5871, 5903, 5935, 5967, 5999, 6030, 6062, 6094, 6126, 6157, 6189, 6220, 6252, 6283, 6315, 6346, 6377, 6408, 6440, 6471, 6502, 6533, 6564, 6594, 6625,  /* 128 - 159*/
                6656, 6687, 6717, 6748, 6779, 6809, 6840, 6870, 6900, 6931, 6961, 6991, 7022, 7052, 7082, 7112, 7142, 7172, 7202, 7232, 7261, 7291, 7321, 7351, 7380, 7410, 7440, 7469, 7499, 7528, 7558, 7587,  /* 160 - 191*/
                7616, 7646, 7675, 7704, 7733, 7762, 7791, 7821, 7850, 7879, 7908, 7936, 7965, 7994, 8023, 8052, 8080, 8109, 8138, 8166, 8195, 8224, 8252, 8281, 8309, 8337, 8366, 8394, 8422, 8451, 8479, 8507,  /* 192 - 223*/
                8535, 8564, 8592, 8620, 8648, 8676, 8704, 8732, 8760, 8788, 8815, 8843, 8871, 8899, 8927, 8954, 8982, 9010, 9037, 9065, 9092, 9120, 9147, 9175, 9202, 9230, 9257, 9284, 9312, 9339, 9366, 9394,  /* 224 - 255*/
                9421, 9448, 9475, 9502, 9530, 9557, 9584, 9611, 9638, 9666, 9693, 9720, 9747, 9774, 9802, 9829, 9856, 9883, 9910, 9938, 9965, 9992, 10019, 10046, 10074, 10101, 10128, 10155, 10182, 10210, 10237, 10264,  /* 256 - 287*/
                10291, 10318, 10346, 10373, 10400, 10427, 10454, 10482, 10509, 10536, 10563, 10590, 10618, 10645, 10672, 10699, 10726, 10754, 10781, 10808, 10835, 10862, 10890, 10917, 10944, 10971, 10998, 11026, 11053, 11080, 11107, 11134,  /* 288 - 319*/
                11162, 11189, 11216, 11243, 11270, 11298, 11325, 11352, 11379, 11406, 11434, 11461, 11488, 11515, 11542, 11570, 11597, 11624, 11651, 11678, 11706, 11733, 11760, 11787, 11814, 11842, 11869, 11896, 11923, 11950, 11978, 12005,  /* 320 - 351*/
                12032, 12059, 12086, 12114, 12141, 12168, 12195, 12222, 12250, 12277, 12304, 12331, 12358, 12386, 12413, 12440, 12467, 12494, 12522, 12549, 12576, 12603, 12630, 12658, 12685, 12712, 12739, 12766, 12794, 12821, 12848, 12875,  /* 352 - 383*/
                12902, 12930, 12957, 12984, 13011, 13038, 13066, 13093, 13120, 13147, 13174, 13202, 13229, 13256, 13283, 13310, 13338, 13365, 13392, 13419, 13446, 13474, 13501, 13528, 13555, 13582, 13610, 13637, 13664, 13691, 13718, 13746,  /* 384 - 415*/
                13773, 13800, 13827, 13854, 13882, 13909, 13936, 13963, 13990, 14018, 14045, 14072, 14099, 14126, 14154, 14181, 14208, 14235, 14262, 14290, 14317, 14344, 14371, 14398, 14426, 14453, 14480, 14507, 14534, 14562, 14589, 14616,  /* 416 - 447*/
                14643, 14670, 14698, 14725, 14752, 14779, 14806, 14834, 14861, 14888, 14915, 14942, 14970, 14997, 15024, 15051, 15078, 15106, 15133, 15160, 15187, 15214, 15242, 15269, 15296, 15323, 15350, 15378, 15405, 15432, 15459, 15486,  /* 448 - 479*/
                15514, 15541, 15568, 15595, 15622, 15650, 15677, 15704, 15731, 15758, 15786, 15813, 15840, 15867, 15894, 15922, 15949, 15976, 16003, 16030, 16058, 16085, 16112, 16139, 16166, 16194, 16221, 16248, 16275, 16302, 16330, 16357,  /* 480 - 511*/
                16384, 16411, 16438, 16466, 16493, 16520, 16547, 16574, 16602, 16629, 16656, 16683, 16710, 16738, 16765, 16792, 16819, 16846, 16874, 16901, 16928, 16955, 16982, 17010, 17037, 17064, 17091, 17118, 17146, 17173, 17200, 17227,  /* 512 - 543*/
                17254, 17282, 17309, 17336, 17363, 17390, 17418, 17445, 17472, 17499, 17526, 17554, 17581, 17608, 17635, 17662, 17690, 17717, 17744, 17771, 17798, 17826, 17853, 17880, 17907, 17934, 17962, 17989, 18016, 18043, 18070, 18098,  /* 544 - 575*/
                18125, 18152, 18179, 18206, 18234, 18261, 18288, 18315, 18342, 18370, 18397, 18424, 18451, 18478, 18506, 18533, 18560, 18587, 18614, 18642, 18669, 18696, 18723, 18750, 18778, 18805, 18832, 18859, 18886, 18914, 18941, 18968,  /* 576 - 607*/
                18995, 19022, 19050, 19077, 19104, 19131, 19158, 19186, 19213, 19240, 19267, 19294, 19322, 19349, 19376, 19403, 19430, 19458, 19485, 19512, 19539, 19566, 19594, 19621, 19648, 19675, 19702, 19730, 19757, 19784, 19811, 19838,  /* 608 - 639*/
                19866, 19893, 19920, 19947, 19974, 20002, 20029, 20056, 20083, 20110, 20138, 20165, 20192, 20219, 20246, 20274, 20301, 20328, 20355, 20382, 20410, 20437, 20464, 20491, 20518, 20546, 20573, 20600, 20627, 20654, 20682, 20709,  /* 640 - 671*/
                20736, 20763, 20790, 20818, 20845, 20872, 20899, 20926, 20954, 20981, 21008, 21035, 21062, 21090, 21117, 21144, 21171, 21198, 21226, 21253, 21280, 21307, 21334, 21362, 21389, 21416, 21443, 21470, 21498, 21525, 21552, 21579,  /* 672 - 703*/
                21606, 21634, 21661, 21688, 21715, 21742, 21770, 21797, 21824, 21851, 21878, 21906, 21933, 21960, 21987, 22014, 22042, 22069, 22096, 22123, 22150, 22178, 22205, 22232, 22259, 22286, 22314, 22341, 22368, 22395, 22422, 22450,  /* 704 - 735*/
                22477, 22504, 22531, 22558, 22586, 22613, 22640, 22667, 22694, 22722, 22749, 22776, 22803, 22830, 22858, 22885, 22912, 22939, 22966, 22994, 23021, 23048, 23075, 23102, 23130, 23157, 23184, 23211, 23238, 23266, 23293, 23320,  /* 736 - 767*/
                23347, 23374, 23402, 23429, 23456, 23484, 23511, 23538, 23566, 23593, 23621, 23648, 23676, 23703, 23731, 23758, 23786, 23814, 23841, 23869, 23897, 23925, 23953, 23980, 24008, 24036, 24064, 24092, 24120, 24148, 24176, 24204,  /* 768 - 799*/
                24233, 24261, 24289, 24317, 24346, 24374, 24402, 24431, 24459, 24487, 24516, 24544, 24573, 24602, 24630, 24659, 24688, 24716, 24745, 24774, 24803, 24832, 24860, 24889, 24918, 24947, 24977, 25006, 25035, 25064, 25093, 25122,  /* 800 - 831*/
                25152, 25181, 25210, 25240, 25269, 25299, 25328, 25358, 25388, 25417, 25447, 25477, 25507, 25536, 25566, 25596, 25626, 25656, 25686, 25716, 25746, 25777, 25807, 25837, 25868, 25898, 25928, 25959, 25989, 26020, 26051, 26081,  /* 832 - 863*/
                26112, 26143, 26174, 26204, 26235, 26266, 26297, 26328, 26360, 26391, 26422, 26453, 26485, 26516, 26548, 26579, 26611, 26642, 26674, 26706, 26738, 26769, 26801, 26833, 26865, 26897, 26930, 26962, 26994, 27027, 27059, 27091,  /* 864 - 895*/
                27124, 27157, 27189, 27222, 27255, 27288, 27321, 27354, 27387, 27420, 27453, 27487, 27520, 27554, 27587, 27621, 27654, 27688, 27722, 27756, 27790, 27824, 27858, 27893, 27927, 27961, 27996, 28031, 28065, 28100, 28135, 28170,  /* 896 - 927*/
                28205, 28240, 28276, 28311, 28346, 28382, 28418, 28453, 28489, 28525, 28561, 28598, 28634, 28670, 28707, 28744, 28780, 28817, 28854, 28891, 28929, 28966, 29004, 29041, 29079, 29117, 29155, 29193, 29232, 29270, 29309, 29348,  /* 928 - 959*/
                29387, 29426, 29465, 29505, 29544, 29584, 29624, 29664, 29704, 29745, 29786, 29827, 29868, 29909, 29951, 29992, 30034, 30077, 30119, 30162, 30205, 30248, 30291, 30335, 30379, 30423, 30468, 30513, 30558, 30604, 30649, 30696,  /* 960 - 991*/
                30742, 30789, 30837, 30884, 30933, 30981, 31030, 31080, 31130, 31181, 31232, 31284, 31337, 31390, 31444, 31499, 31554, 31611, 31668, 31727, 31787, 31848, 31911, 31975, 32041, 32109, 32180, 32254, 32332, 32416, 32507, 32612,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 156, 261, 352, 436, 514, 588, 659, 727, 793, 857, 920, 981, 1041, 1100, 1157, 1214, 1269, 1324, 1378, 1431, 1484, 1536, 1587, 1638, 1688, 1738, 1787, 1835, 1884, 1931, 1979,  /* 0 - 31*/
                2026, 2072, 2119, 2164, 2210, 2255, 2300, 2345, 2389, 2433, 2477, 2520, 2563, 2606, 2649, 2691, 2734, 2776, 2817, 2859, 2900, 2941, 2982, 3023, 3064, 3104, 3144, 3184, 3224, 3263, 3303, 3342,  /* 32 - 63*/
                3381, 3420, 3459, 3498, 3536, 3575, 3613, 3651, 3689, 3727, 3764, 3802, 3839, 3877, 3914, 3951, 3988, 4024, 4061, 4098, 4134, 4170, 4207, 4243, 4279, 4315, 4350, 4386, 4422, 4457, 4492, 4528,  /* 64 - 95*/
                4563, 4598, 4633, 4668, 4703, 4737, 4772, 4807, 4841, 4875, 4910, 4944, 4978, 5012, 5046, 5080, 5114, 5147, 5181, 5214, 5248, 5281, 5315, 5348, 5381, 5414, 5447, 5480, 5513, 5546, 5579, 5611,  /* 96 - 127*/
                5644, 5677, 5709, 5741, 5774, 5806, 5838, 5871, 5903, 5935, 5967, 5999, 6030, 6062, 6094, 6126, 6157, 6189, 6220, 6252, 6283, 6315, 6346, 6377, 6408, 6440, 6471, 6502, 6533, 6564, 6594, 6625,  /* 128 - 159*/
                6656, 6687, 6717, 6748, 6779, 6809, 6840, 6870, 6900, 6931, 6961, 6991, 7022, 7052, 7082, 7112, 7142, 7172, 7202, 7232, 7261, 7291, 7321, 7351, 7380, 7410, 7440, 7469, 7499, 7528, 7558, 7587,  /* 160 - 191*/
                7616, 7646, 7675, 7704, 7733, 7762, 7791, 7821, 7850, 7879, 7908, 7936, 7965, 7994, 8023, 8052, 8080, 8109, 8138, 8166, 8195, 8224, 8252, 8281, 8309, 8337, 8366, 8394, 8422, 8451, 8479, 8507,  /* 192 - 223*/
                8535, 8564, 8592, 8620, 8648, 8676, 8704, 8732, 8760, 8788, 8815, 8843, 8871, 8899, 8927, 8954, 8982, 9010, 9037, 9065, 9092, 9120, 9147, 9175, 9202, 9230, 9257, 9284, 9312, 9339, 9366, 9394,  /* 224 - 255*/
                9421, 9448, 9475, 9502, 9530, 9557, 9584, 9611, 9638, 9666, 9693, 9720, 9747, 9774, 9802, 9829, 9856, 9883, 9910, 9938, 9965, 9992, 10019, 10046, 10074, 10101, 10128, 10155, 10182, 10210, 10237, 10264,  /* 256 - 287*/
                10291, 10318, 10346, 10373, 10400, 10427, 10454, 10482, 10509, 10536, 10563, 10590, 10618, 10645, 10672, 10699, 10726, 10754, 10781, 10808, 10835, 10862, 10890, 10917, 10944, 10971, 10998, 11026, 11053, 11080, 11107, 11134,  /* 288 - 319*/
                11162, 11189, 11216, 11243, 11270, 11298, 11325, 11352, 11379, 11406, 11434, 11461, 11488, 11515, 11542, 11570, 11597, 11624, 11651, 11678, 11706, 11733, 11760, 11787, 11814, 11842, 11869, 11896, 11923, 11950, 11978, 12005,  /* 320 - 351*/
                12032, 12059, 12086, 12114, 12141, 12168, 12195, 12222, 12250, 12277, 12304, 12331, 12358, 12386, 12413, 12440, 12467, 12494, 12522, 12549, 12576, 12603, 12630, 12658, 12685, 12712, 12739, 12766, 12794, 12821, 12848, 12875,  /* 352 - 383*/
                12902, 12930, 12957, 12984, 13011, 13038, 13066, 13093, 13120, 13147, 13174, 13202, 13229, 13256, 13283, 13310, 13338, 13365, 13392, 13419, 13446, 13474, 13501, 13528, 13555, 13582, 13610, 13637, 13664, 13691, 13718, 13746,  /* 384 - 415*/
                13773, 13800, 13827, 13854, 13882, 13909, 13936, 13963, 13990, 14018, 14045, 14072, 14099, 14126, 14154, 14181, 14208, 14235, 14262, 14290, 14317, 14344, 14371, 14398, 14426, 14453, 14480, 14507, 14534, 14562, 14589, 14616,  /* 416 - 447*/
                14643, 14670, 14698, 14725, 14752, 14779, 14806, 14834, 14861, 14888, 14915, 14942, 14970, 14997, 15024, 15051, 15078, 15106, 15133, 15160, 15187, 15214, 15242, 15269, 15296, 15323, 15350, 15378, 15405, 15432, 15459, 15486,  /* 448 - 479*/
                15514, 15541, 15568, 15595, 15622, 15650, 15677, 15704, 15731, 15758, 15786, 15813, 15840, 15867, 15894, 15922, 15949, 15976, 16003, 16030, 16058, 16085, 16112, 16139, 16166, 16194, 16221, 16248, 16275, 16302, 16330, 16357,  /* 480 - 511*/
                16384, 16411, 16438, 16466, 16493, 16520, 16547, 16574, 16602, 16629, 16656, 16683, 16710, 16738, 16765, 16792, 16819, 16846, 16874, 16901, 16928, 16955, 16982, 17010, 17037, 17064, 17091, 17118, 17146, 17173, 17200, 17227,  /* 512 - 543*/
                17254, 17282, 17309, 17336, 17363, 17390, 17418, 17445, 17472, 17499, 17526, 17554, 17581, 17608, 17635, 17662, 17690, 17717, 17744, 17771, 17798, 17826, 17853, 17880, 17907, 17934, 17962, 17989, 18016, 18043, 18070, 18098,  /* 544 - 575*/
                18125, 18152, 18179, 18206, 18234, 18261, 18288, 18315, 18342, 18370, 18397, 18424, 18451, 18478, 18506, 18533, 18560, 18587, 18614, 18642, 18669, 18696, 18723, 18750, 18778, 18805, 18832, 18859, 18886, 18914, 18941, 18968,  /* 576 - 607*/
                18995, 19022, 19050, 19077, 19104, 19131, 19158, 19186, 19213, 19240, 19267, 19294, 19322, 19349, 19376, 19403, 19430, 19458, 19485, 19512, 19539, 19566, 19594, 19621, 19648, 19675, 19702, 19730, 19757, 19784, 19811, 19838,  /* 608 - 639*/
                19866, 19893, 19920, 19947, 19974, 20002, 20029, 20056, 20083, 20110, 20138, 20165, 20192, 20219, 20246, 20274, 20301, 20328, 20355, 20382, 20410, 20437, 20464, 20491, 20518, 20546, 20573, 20600, 20627, 20654, 20682, 20709,  /* 640 - 671*/
                20736, 20763, 20790, 20818, 20845, 20872, 20899, 20926, 20954, 20981, 21008, 21035, 21062, 21090, 21117, 21144, 21171, 21198, 21226, 21253, 21280, 21307, 21334, 21362, 21389, 21416, 21443, 21470, 21498, 21525, 21552, 21579,  /* 672 - 703*/
                21606, 21634, 21661, 21688, 21715, 21742, 21770, 21797, 21824, 21851, 21878, 21906, 21933, 21960, 21987, 22014, 22042, 22069, 22096, 22123, 22150, 22178, 22205, 22232, 22259, 22286, 22314, 22341, 22368, 22395, 22422, 22450,  /* 704 - 735*/
                22477, 22504, 22531, 22558, 22586, 22613, 22640, 22667, 22694, 22722, 22749, 22776, 22803, 22830, 22858, 22885, 22912, 22939, 22966, 22994, 23021, 23048, 23075, 23102, 23130, 23157, 23184, 23211, 23238, 23266, 23293, 23320,  /* 736 - 767*/
                23347, 23374, 23402, 23429, 23456, 23484, 23511, 23538, 23566, 23593, 23621, 23648, 23676, 23703, 23731, 23758, 23786, 23814, 23841, 23869, 23897, 23925, 23953, 23980, 24008, 24036, 24064, 24092, 24120, 24148, 24176, 24204,  /* 768 - 799*/
                24233, 24261, 24289, 24317, 24346, 24374, 24402, 24431, 24459, 24487, 24516, 24544, 24573, 24602, 24630, 24659, 24688, 24716, 24745, 24774, 24803, 24832, 24860, 24889, 24918, 24947, 24977, 25006, 25035, 25064, 25093, 25122,  /* 800 - 831*/
                25152, 25181, 25210, 25240, 25269, 25299, 25328, 25358, 25388, 25417, 25447, 25477, 25507, 25536, 25566, 25596, 25626, 25656, 25686, 25716, 25746, 25777, 25807, 25837, 25868, 25898, 25928, 25959, 25989, 26020, 26051, 26081,  /* 832 - 863*/
                26112, 26143, 26174, 26204, 26235, 26266, 26297, 26328, 26360, 26391, 26422, 26453, 26485, 26516, 26548, 26579, 26611, 26642, 26674, 26706, 26738, 26769, 26801, 26833, 26865, 26897, 26930, 26962, 26994, 27027, 27059, 27091,  /* 864 - 895*/
                27124, 27157, 27189, 27222, 27255, 27288, 27321, 27354, 27387, 27420, 27453, 27487, 27520, 27554, 27587, 27621, 27654, 27688, 27722, 27756, 27790, 27824, 27858, 27893, 27927, 27961, 27996, 28031, 28065, 28100, 28135, 28170,  /* 896 - 927*/
                28205, 28240, 28276, 28311, 28346, 28382, 28418, 28453, 28489, 28525, 28561, 28598, 28634, 28670, 28707, 28744, 28780, 28817, 28854, 28891, 28929, 28966, 29004, 29041, 29079, 29117, 29155, 29193, 29232, 29270, 29309, 29348,  /* 928 - 959*/
                29387, 29426, 29465, 29505, 29544, 29584, 29624, 29664, 29704, 29745, 29786, 29827, 29868, 29909, 29951, 29992, 30034, 30077, 30119, 30162, 30205, 30248, 30291, 30335, 30379, 30423, 30468, 30513, 30558, 30604, 30649, 30696,  /* 960 - 991*/
                30742, 30789, 30837, 30884, 30933, 30981, 31030, 31080, 31130, 31181, 31232, 31284, 31337, 31390, 31444, 31499, 31554, 31611, 31668, 31727, 31787, 31848, 31911, 31975, 32041, 32109, 32180, 32254, 32332, 32416, 32507, 32612,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 217, 350, 462, 563, 657, 745, 828, 907, 984, 1058, 1129, 1199, 1267, 1333, 1398, 1461, 1523, 1585, 1645, 1704, 1762, 1819, 1875, 1931, 1986, 2040, 2094, 2147, 2199, 2251, 2303,  /* 0 - 31*/
                2353, 2404, 2454, 2503, 2552, 2600, 2649, 2696, 2744, 2791, 2837, 2883, 2929, 2975, 3020, 3065, 3110, 3154, 3199, 3242, 3286, 3329, 3372, 3415, 3458, 3500, 3542, 3584, 3626, 3667, 3708, 3749,  /* 32 - 63*/
                3790, 3831, 3871, 3911, 3951, 3991, 4031, 4070, 4110, 4149, 4188, 4227, 4265, 4304, 4342, 4381, 4419, 4456, 4494, 4532, 4569, 4607, 4644, 4681, 4718, 4755, 4791, 4828, 4864, 4900, 4937, 4973,  /* 64 - 95*/
                5009, 5044, 5080, 5116, 5151, 5187, 5222, 5257, 5292, 5327, 5362, 5396, 5431, 5466, 5500, 5534, 5569, 5603, 5637, 5671, 5705, 5738, 5772, 5806, 5839, 5872, 5906, 5939, 5972, 6005, 6038, 6071,  /* 96 - 127*/
                6104, 6137, 6169, 6202, 6234, 6267, 6299, 6332, 6364, 6396, 6428, 6460, 6492, 6524, 6555, 6587, 6619, 6650, 6682, 6713, 6745, 6776, 6807, 6838, 6869, 6901, 6931, 6962, 6993, 7024, 7055, 7085,  /* 128 - 159*/
                7116, 7147, 7177, 7208, 7238, 7268, 7298, 7329, 7359, 7389, 7419, 7449, 7479, 7509, 7538, 7568, 7598, 7628, 7657, 7687, 7716, 7746, 7775, 7804, 7834, 7863, 7892, 7921, 7950, 7979, 8008, 8037,  /* 160 - 191*/
                8066, 8095, 8124, 8153, 8181, 8210, 8239, 8267, 8296, 8324, 8353, 8381, 8410, 8438, 8466, 8494, 8523, 8551, 8579, 8607, 8635, 8663, 8691, 8719, 8747, 8774, 8802, 8830, 8858, 8885, 8913, 8941,  /* 192 - 223*/
                8968, 8996, 9023, 9051, 9078, 9105, 9133, 9160, 9187, 9214, 9241, 9269, 9296, 9323, 9350, 9377, 9404, 9431, 9458, 9484, 9511, 9538, 9565, 9591, 9618, 9645, 9671, 9698, 9725, 9751, 9778, 9804,  /* 224 - 255*/
                9830, 9857, 9883, 9910, 9936, 9962, 9989, 10015, 10042, 10068, 10094, 10121, 10147, 10174, 10200, 10226, 10253, 10279, 10306, 10332, 10358, 10385, 10411, 10438, 10464, 10490, 10517, 10543, 10570, 10596, 10622, 10649,  /* 256 - 287*/
                10675, 10702, 10728, 10754, 10781, 10807, 10834, 10860, 10886, 10913, 10939, 10966, 10992, 11018, 11045, 11071, 11098, 11124, 11150, 11177, 11203, 11230, 11256, 11282, 11309, 11335, 11362, 11388, 11414, 11441, 11467, 11494,  /* 288 - 319*/
                11520, 11546, 11573, 11599, 11626, 11652, 11678, 11705, 11731, 11758, 11784, 11810, 11837, 11863, 11890, 11916, 11942, 11969, 11995, 12022, 12048, 12074, 12101, 12127, 12154, 12180, 12206, 12233, 12259, 12286, 12312, 12338,  /* 320 - 351*/
                12365, 12391, 12418, 12444, 12470, 12497, 12523, 12550, 12576, 12602, 12629, 12655, 12682, 12708, 12734, 12761, 12787, 12814, 12840, 12866, 12893, 12919, 12946, 12972, 12998, 13025, 13051, 13078, 13104, 13130, 13157, 13183,  /* 352 - 383*/
                13210, 13236, 13262, 13289, 13315, 13342, 13368, 13394, 13421, 13447, 13474, 13500, 13526, 13553, 13579, 13606, 13632, 13658, 13685, 13711, 13738, 13764, 13790, 13817, 13843, 13870, 13896, 13922, 13949, 13975, 14002, 14028,  /* 384 - 415*/
                14054, 14081, 14107, 14134, 14160, 14186, 14213, 14239, 14266, 14292, 14318, 14345, 14371, 14398, 14424, 14450, 14477, 14503, 14530, 14556, 14582, 14609, 14635, 14662, 14688, 14714, 14741, 14767, 14794, 14820, 14846, 14873,  /* 416 - 447*/
                14899, 14926, 14952, 14978, 15005, 15031, 15058, 15084, 15110, 15137, 15163, 15190, 15216, 15242, 15269, 15295, 15322, 15348, 15374, 15401, 15427, 15454, 15480, 15506, 15533, 15559, 15586, 15612, 15638, 15665, 15691, 15718,  /* 448 - 479*/
                15744, 15770, 15797, 15823, 15850, 15876, 15902, 15929, 15955, 15982, 16008, 16034, 16061, 16087, 16114, 16140, 16166, 16193, 16219, 16246, 16272, 16298, 16325, 16351, 16378, 16404, 16430, 16457, 16483, 16510, 16536, 16562,  /* 480 - 511*/
                16589, 16615, 16642, 16668, 16694, 16721, 16747, 16774, 16800, 16826, 16853, 16879, 16906, 16932, 16958, 16985, 17011, 17038, 17064, 17090, 17117, 17143, 17170, 17196, 17222, 17249, 17275, 17302, 17328, 17354, 17381, 17407,  /* 512 - 543*/
                17434, 17460, 17486, 17513, 17539, 17566, 17592, 17618, 17645, 17671, 17698, 17724, 17750, 17777, 17803, 17830, 17856, 17882, 17909, 17935, 17962, 17988, 18014, 18041, 18067, 18094, 18120, 18146, 18173, 18199, 18226, 18252,  /* 544 - 575*/
                18278, 18305, 18331, 18358, 18384, 18410, 18437, 18463, 18490, 18516, 18542, 18569, 18595, 18622, 18648, 18674, 18701, 18727, 18754, 18780, 18806, 18833, 18859, 18886, 18912, 18938, 18965, 18991, 19018, 19044, 19070, 19097,  /* 576 - 607*/
                19123, 19150, 19176, 19202, 19229, 19255, 19282, 19308, 19334, 19361, 19387, 19414, 19440, 19466, 19493, 19519, 19546, 19572, 19598, 19625, 19651, 19678, 19704, 19730, 19757, 19783, 19810, 19836, 19862, 19889, 19915, 19942,  /* 608 - 639*/
                19968, 19994, 20021, 20047, 20074, 20100, 20126, 20153, 20179, 20206, 20232, 20258, 20285, 20311, 20338, 20364, 20390, 20417, 20443, 20470, 20496, 20522, 20549, 20575, 20602, 20628, 20654, 20681, 20707, 20734, 20760, 20786,  /* 640 - 671*/
                20813, 20839, 20866, 20892, 20918, 20945, 20971, 20998, 21024, 21050, 21077, 21103, 21130, 21156, 21182, 21209, 21235, 21262, 21288, 21314, 21341, 21367, 21394, 21420, 21446, 21473, 21499, 21526, 21552, 21578, 21605, 21631,  /* 672 - 703*/
                21658, 21684, 21710, 21737, 21763, 21790, 21816, 21842, 21869, 21895, 21922, 21948, 21974, 22001, 22027, 22054, 22080, 22106, 22133, 22159, 22186, 22212, 22238, 22265, 22291, 22318, 22344, 22370, 22397, 22423, 22450, 22476,  /* 704 - 735*/
                22502, 22529, 22555, 22582, 22608, 22634, 22661, 22687, 22714, 22740, 22766, 22793, 22819, 22846, 22872, 22898, 22925, 22951, 22978, 23004, 23030, 23057, 23083, 23110, 23136, 23162, 23189, 23215, 23242, 23268, 23294, 23321,  /* 736 - 767*/
                23347, 23374, 23400, 23427, 23453, 23480, 23506, 23533, 23559, 23586, 23613, 23639, 23666, 23693, 23720, 23747, 23773, 23800, 23827, 23854, 23881, 23908, 23935, 23962, 23990, 24017, 24044, 24071, 24098, 24126, 24153, 24180,  /* 768 - 799*/
                24208, 24235, 24263, 24290, 24318, 24345, 24373, 24401, 24428, 24456, 24484, 24511, 24539, 24567, 24595, 24623, 24651, 24679, 24707, 24735, 24763, 24791, 24820, 24848, 24876, 24905, 24933, 24961, 24990, 25018, 25047, 25075,  /* 800 - 831*/
                25104, 25133, 25161, 25190, 25219, 25248, 25277, 25305, 25334, 25363, 25392, 25422, 25451, 25480, 25509, 25538, 25568, 25597, 25627, 25656, 25686, 25715, 25745, 25774, 25804, 25834, 25864, 25894, 25923, 25953, 25983, 26013,  /* 832 - 863*/
                26044, 26074, 26104, 26134, 26165, 26195, 26225, 26256, 26287, 26317, 26348, 26379, 26409, 26440, 26471, 26502, 26533, 26564, 26595, 26627, 26658, 26689, 26721, 26752, 26784, 26815, 26847, 26879, 26910, 26942, 26974, 27006,  /* 864 - 895*/
                27038, 27070, 27103, 27135, 27167, 27200, 27232, 27265, 27298, 27330, 27363, 27396, 27429, 27462, 27495, 27528, 27562, 27595, 27629, 27662, 27696, 27730, 27763, 27797, 27831, 27865, 27900, 27934, 27968, 28003, 28037, 28072,  /* 896 - 927*/
                28107, 28142, 28177, 28212, 28247, 28282, 28318, 28353, 28389, 28425, 28460, 28496, 28533, 28569, 28605, 28642, 28678, 28715, 28752, 28789, 28826, 28863, 28901, 28938, 28976, 29014, 29052, 29090, 29128, 29167, 29205, 29244,  /* 928 - 959*/
                29283, 29322, 29362, 29401, 29441, 29481, 29521, 29561, 29602, 29642, 29683, 29724, 29765, 29807, 29849, 29891, 29933, 29976, 30018, 30061, 30105, 30148, 30192, 30236, 30281, 30325, 30370, 30416, 30462, 30508, 30554, 30601,  /* 960 - 991*/
                30649, 30696, 30744, 30793, 30842, 30892, 30942, 30993, 31044, 31096, 31148, 31201, 31255, 31310, 31365, 31422, 31479, 31537, 31597, 31657, 31719, 31783, 31848, 31915, 31984, 32056, 32130, 32208, 32291, 32380, 32478, 32592,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 217, 350, 462, 563, 657, 745, 828, 907, 984, 1058, 1129, 1199, 1267, 1333, 1398, 1461, 1523, 1585, 1645, 1704, 1762, 1819, 1875, 1931, 1986, 2040, 2094, 2147, 2199, 2251, 2303,  /* 0 - 31*/
                2353, 2404, 2454, 2503, 2552, 2600, 2649, 2696, 2744, 2791, 2837, 2883, 2929, 2975, 3020, 3065, 3110, 3154, 3199, 3242, 3286, 3329, 3372, 3415, 3458, 3500, 3542, 3584, 3626, 3667, 3708, 3749,  /* 32 - 63*/
                3790, 3831, 3871, 3911, 3951, 3991, 4031, 4070, 4110, 4149, 4188, 4227, 4265, 4304, 4342, 4381, 4419, 4456, 4494, 4532, 4569, 4607, 4644, 4681, 4718, 4755, 4791, 4828, 4864, 4900, 4937, 4973,  /* 64 - 95*/
                5009, 5044, 5080, 5116, 5151, 5187, 5222, 5257, 5292, 5327, 5362, 5396, 5431, 5466, 5500, 5534, 5569, 5603, 5637, 5671, 5705, 5738, 5772, 5806, 5839, 5872, 5906, 5939, 5972, 6005, 6038, 6071,  /* 96 - 127*/
                6104, 6137, 6169, 6202, 6234, 6267, 6299, 6332, 6364, 6396, 6428, 6460, 6492, 6524, 6555, 6587, 6619, 6650, 6682, 6713, 6745, 6776, 6807, 6838, 6869, 6901, 6931, 6962, 6993, 7024, 7055, 7085,  /* 128 - 159*/
                7116, 7147, 7177, 7208, 7238, 7268, 7298, 7329, 7359, 7389, 7419, 7449, 7479, 7509, 7538, 7568, 7598, 7628, 7657, 7687, 7716, 7746, 7775, 7804, 7834, 7863, 7892, 7921, 7950, 7979, 8008, 8037,  /* 160 - 191*/
                8066, 8095, 8124, 8153, 8181, 8210, 8239, 8267, 8296, 8324, 8353, 8381, 8410, 8438, 8466, 8494, 8523, 8551, 8579, 8607, 8635, 8663, 8691, 8719, 8747, 8774, 8802, 8830, 8858, 8885, 8913, 8941,  /* 192 - 223*/
                8968, 8996, 9023, 9051, 9078, 9105, 9133, 9160, 9187, 9214, 9241, 9269, 9296, 9323, 9350, 9377, 9404, 9431, 9458, 9484, 9511, 9538, 9565, 9591, 9618, 9645, 9671, 9698, 9725, 9751, 9778, 9804,  /* 224 - 255*/
                9830, 9857, 9883, 9910, 9936, 9962, 9989, 10015, 10042, 10068, 10094, 10121, 10147, 10174, 10200, 10226, 10253, 10279, 10306, 10332, 10358, 10385, 10411, 10438, 10464, 10490, 10517, 10543, 10570, 10596, 10622, 10649,  /* 256 - 287*/
                10675, 10702, 10728, 10754, 10781, 10807, 10834, 10860, 10886, 10913, 10939, 10966, 10992, 11018, 11045, 11071, 11098, 11124, 11150, 11177, 11203, 11230, 11256, 11282, 11309, 11335, 11362, 11388, 11414, 11441, 11467, 11494,  /* 288 - 319*/
                11520, 11546, 11573, 11599, 11626, 11652, 11678, 11705, 11731, 11758, 11784, 11810, 11837, 11863, 11890, 11916, 11942, 11969, 11995, 12022, 12048, 12074, 12101, 12127, 12154, 12180, 12206, 12233, 12259, 12286, 12312, 12338,  /* 320 - 351*/
                12365, 12391, 12418, 12444, 12470, 12497, 12523, 12550, 12576, 12602, 12629, 12655, 12682, 12708, 12734, 12761, 12787, 12814, 12840, 12866, 12893, 12919, 12946, 12972, 12998, 13025, 13051, 13078, 13104, 13130, 13157, 13183,  /* 352 - 383*/
                13210, 13236, 13262, 13289, 13315, 13342, 13368, 13394, 13421, 13447, 13474, 13500, 13526, 13553, 13579, 13606, 13632, 13658, 13685, 13711, 13738, 13764, 13790, 13817, 13843, 13870, 13896, 13922, 13949, 13975, 14002, 14028,  /* 384 - 415*/
                14054, 14081, 14107, 14134, 14160, 14186, 14213, 14239, 14266, 14292, 14318, 14345, 14371, 14398, 14424, 14450, 14477, 14503, 14530, 14556, 14582, 14609, 14635, 14662, 14688, 14714, 14741, 14767, 14794, 14820, 14846, 14873,  /* 416 - 447*/
                14899, 14926, 14952, 14978, 15005, 15031, 15058, 15084, 15110, 15137, 15163, 15190, 15216, 15242, 15269, 15295, 15322, 15348, 15374, 15401, 15427, 15454, 15480, 15506, 15533, 15559, 15586, 15612, 15638, 15665, 15691, 15718,  /* 448 - 479*/
                15744, 15770, 15797, 15823, 15850, 15876, 15902, 15929, 15955, 15982, 16008, 16034, 16061, 16087, 16114, 16140, 16166, 16193, 16219, 16246, 16272, 16298, 16325, 16351, 16378, 16404, 16430, 16457, 16483, 16510, 16536, 16562,  /* 480 - 511*/
                16589, 16615, 16642, 16668, 16694, 16721, 16747, 16774, 16800, 16826, 16853, 16879, 16906, 16932, 16958, 16985, 17011, 17038, 17064, 17090, 17117, 17143, 17170, 17196, 17222, 17249, 17275, 17302, 17328, 17354, 17381, 17407,  /* 512 - 543*/
                17434, 17460, 17486, 17513, 17539, 17566, 17592, 17618, 17645, 17671, 17698, 17724, 17750, 17777, 17803, 17830, 17856, 17882, 17909, 17935, 17962, 17988, 18014, 18041, 18067, 18094, 18120, 18146, 18173, 18199, 18226, 18252,  /* 544 - 575*/
                18278, 18305, 18331, 18358, 18384, 18410, 18437, 18463, 18490, 18516, 18542, 18569, 18595, 18622, 18648, 18674, 18701, 18727, 18754, 18780, 18806, 18833, 18859, 18886, 18912, 18938, 18965, 18991, 19018, 19044, 19070, 19097,  /* 576 - 607*/
                19123, 19150, 19176, 19202, 19229, 19255, 19282, 19308, 19334, 19361, 19387, 19414, 19440, 19466, 19493, 19519, 19546, 19572, 19598, 19625, 19651, 19678, 19704, 19730, 19757, 19783, 19810, 19836, 19862, 19889, 19915, 19942,  /* 608 - 639*/
                19968, 19994, 20021, 20047, 20074, 20100, 20126, 20153, 20179, 20206, 20232, 20258, 20285, 20311, 20338, 20364, 20390, 20417, 20443, 20470, 20496, 20522, 20549, 20575, 20602, 20628, 20654, 20681, 20707, 20734, 20760, 20786,  /* 640 - 671*/
                20813, 20839, 20866, 20892, 20918, 20945, 20971, 20998, 21024, 21050, 21077, 21103, 21130, 21156, 21182, 21209, 21235, 21262, 21288, 21314, 21341, 21367, 21394, 21420, 21446, 21473, 21499, 21526, 21552, 21578, 21605, 21631,  /* 672 - 703*/
                21658, 21684, 21710, 21737, 21763, 21790, 21816, 21842, 21869, 21895, 21922, 21948, 21974, 22001, 22027, 22054, 22080, 22106, 22133, 22159, 22186, 22212, 22238, 22265, 22291, 22318, 22344, 22370, 22397, 22423, 22450, 22476,  /* 704 - 735*/
                22502, 22529, 22555, 22582, 22608, 22634, 22661, 22687, 22714, 22740, 22766, 22793, 22819, 22846, 22872, 22898, 22925, 22951, 22978, 23004, 23030, 23057, 23083, 23110, 23136, 23162, 23189, 23215, 23242, 23268, 23294, 23321,  /* 736 - 767*/
                23347, 23374, 23400, 23427, 23453, 23480, 23506, 23533, 23559, 23586, 23613, 23639, 23666, 23693, 23720, 23747, 23773, 23800, 23827, 23854, 23881, 23908, 23935, 23962, 23990, 24017, 24044, 24071, 24098, 24126, 24153, 24180,  /* 768 - 799*/
                24208, 24235, 24263, 24290, 24318, 24345, 24373, 24401, 24428, 24456, 24484, 24511, 24539, 24567, 24595, 24623, 24651, 24679, 24707, 24735, 24763, 24791, 24820, 24848, 24876, 24905, 24933, 24961, 24990, 25018, 25047, 25075,  /* 800 - 831*/
                25104, 25133, 25161, 25190, 25219, 25248, 25277, 25305, 25334, 25363, 25392, 25422, 25451, 25480, 25509, 25538, 25568, 25597, 25627, 25656, 25686, 25715, 25745, 25774, 25804, 25834, 25864, 25894, 25923, 25953, 25983, 26013,  /* 832 - 863*/
                26044, 26074, 26104, 26134, 26165, 26195, 26225, 26256, 26287, 26317, 26348, 26379, 26409, 26440, 26471, 26502, 26533, 26564, 26595, 26627, 26658, 26689, 26721, 26752, 26784, 26815, 26847, 26879, 26910, 26942, 26974, 27006,  /* 864 - 895*/
                27038, 27070, 27103, 27135, 27167, 27200, 27232, 27265, 27298, 27330, 27363, 27396, 27429, 27462, 27495, 27528, 27562, 27595, 27629, 27662, 27696, 27730, 27763, 27797, 27831, 27865, 27900, 27934, 27968, 28003, 28037, 28072,  /* 896 - 927*/
                28107, 28142, 28177, 28212, 28247, 28282, 28318, 28353, 28389, 28425, 28460, 28496, 28533, 28569, 28605, 28642, 28678, 28715, 28752, 28789, 28826, 28863, 28901, 28938, 28976, 29014, 29052, 29090, 29128, 29167, 29205, 29244,  /* 928 - 959*/
                29283, 29322, 29362, 29401, 29441, 29481, 29521, 29561, 29602, 29642, 29683, 29724, 29765, 29807, 29849, 29891, 29933, 29976, 30018, 30061, 30105, 30148, 30192, 30236, 30281, 30325, 30370, 30416, 30462, 30508, 30554, 30601,  /* 960 - 991*/
                30649, 30696, 30744, 30793, 30842, 30892, 30942, 30993, 31044, 31096, 31148, 31201, 31255, 31310, 31365, 31422, 31479, 31537, 31597, 31657, 31719, 31783, 31848, 31915, 31984, 32056, 32130, 32208, 32291, 32380, 32478, 32592,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 217, 350, 462, 563, 657, 745, 828, 907, 984, 1058, 1129, 1199, 1267, 1333, 1398, 1461, 1523, 1585, 1645, 1704, 1762, 1819, 1875, 1931, 1986, 2040, 2094, 2147, 2199, 2251, 2303,  /* 0 - 31*/
                2353, 2404, 2454, 2503, 2552, 2600, 2649, 2696, 2744, 2791, 2837, 2883, 2929, 2975, 3020, 3065, 3110, 3154, 3199, 3242, 3286, 3329, 3372, 3415, 3458, 3500, 3542, 3584, 3626, 3667, 3708, 3749,  /* 32 - 63*/
                3790, 3831, 3871, 3911, 3951, 3991, 4031, 4070, 4110, 4149, 4188, 4227, 4265, 4304, 4342, 4381, 4419, 4456, 4494, 4532, 4569, 4607, 4644, 4681, 4718, 4755, 4791, 4828, 4864, 4900, 4937, 4973,  /* 64 - 95*/
                5009, 5044, 5080, 5116, 5151, 5187, 5222, 5257, 5292, 5327, 5362, 5396, 5431, 5466, 5500, 5534, 5569, 5603, 5637, 5671, 5705, 5738, 5772, 5806, 5839, 5872, 5906, 5939, 5972, 6005, 6038, 6071,  /* 96 - 127*/
                6104, 6137, 6169, 6202, 6234, 6267, 6299, 6332, 6364, 6396, 6428, 6460, 6492, 6524, 6555, 6587, 6619, 6650, 6682, 6713, 6745, 6776, 6807, 6838, 6869, 6901, 6931, 6962, 6993, 7024, 7055, 7085,  /* 128 - 159*/
                7116, 7147, 7177, 7208, 7238, 7268, 7298, 7329, 7359, 7389, 7419, 7449, 7479, 7509, 7538, 7568, 7598, 7628, 7657, 7687, 7716, 7746, 7775, 7804, 7834, 7863, 7892, 7921, 7950, 7979, 8008, 8037,  /* 160 - 191*/
                8066, 8095, 8124, 8153, 8181, 8210, 8239, 8267, 8296, 8324, 8353, 8381, 8410, 8438, 8466, 8494, 8523, 8551, 8579, 8607, 8635, 8663, 8691, 8719, 8747, 8774, 8802, 8830, 8858, 8885, 8913, 8941,  /* 192 - 223*/
                8968, 8996, 9023, 9051, 9078, 9105, 9133, 9160, 9187, 9214, 9241, 9269, 9296, 9323, 9350, 9377, 9404, 9431, 9458, 9484, 9511, 9538, 9565, 9591, 9618, 9645, 9671, 9698, 9725, 9751, 9778, 9804,  /* 224 - 255*/
                9830, 9857, 9883, 9910, 9936, 9962, 9989, 10015, 10042, 10068, 10094, 10121, 10147, 10174, 10200, 10226, 10253, 10279, 10306, 10332, 10358, 10385, 10411, 10438, 10464, 10490, 10517, 10543, 10570, 10596, 10622, 10649,  /* 256 - 287*/
                10675, 10702, 10728, 10754, 10781, 10807, 10834, 10860, 10886, 10913, 10939, 10966, 10992, 11018, 11045, 11071, 11098, 11124, 11150, 11177, 11203, 11230, 11256, 11282, 11309, 11335, 11362, 11388, 11414, 11441, 11467, 11494,  /* 288 - 319*/
                11520, 11546, 11573, 11599, 11626, 11652, 11678, 11705, 11731, 11758, 11784, 11810, 11837, 11863, 11890, 11916, 11942, 11969, 11995, 12022, 12048, 12074, 12101, 12127, 12154, 12180, 12206, 12233, 12259, 12286, 12312, 12338,  /* 320 - 351*/
                12365, 12391, 12418, 12444, 12470, 12497, 12523, 12550, 12576, 12602, 12629, 12655, 12682, 12708, 12734, 12761, 12787, 12814, 12840, 12866, 12893, 12919, 12946, 12972, 12998, 13025, 13051, 13078, 13104, 13130, 13157, 13183,  /* 352 - 383*/
                13210, 13236, 13262, 13289, 13315, 13342, 13368, 13394, 13421, 13447, 13474, 13500, 13526, 13553, 13579, 13606, 13632, 13658, 13685, 13711, 13738, 13764, 13790, 13817, 13843, 13870, 13896, 13922, 13949, 13975, 14002, 14028,  /* 384 - 415*/
                14054, 14081, 14107, 14134, 14160, 14186, 14213, 14239, 14266, 14292, 14318, 14345, 14371, 14398, 14424, 14450, 14477, 14503, 14530, 14556, 14582, 14609, 14635, 14662, 14688, 14714, 14741, 14767, 14794, 14820, 14846, 14873,  /* 416 - 447*/
                14899, 14926, 14952, 14978, 15005, 15031, 15058, 15084, 15110, 15137, 15163, 15190, 15216, 15242, 15269, 15295, 15322, 15348, 15374, 15401, 15427, 15454, 15480, 15506, 15533, 15559, 15586, 15612, 15638, 15665, 15691, 15718,  /* 448 - 479*/
                15744, 15770, 15797, 15823, 15850, 15876, 15902, 15929, 15955, 15982, 16008, 16034, 16061, 16087, 16114, 16140, 16166, 16193, 16219, 16246, 16272, 16298, 16325, 16351, 16378, 16404, 16430, 16457, 16483, 16510, 16536, 16562,  /* 480 - 511*/
                16589, 16615, 16642, 16668, 16694, 16721, 16747, 16774, 16800, 16826, 16853, 16879, 16906, 16932, 16958, 16985, 17011, 17038, 17064, 17090, 17117, 17143, 17170, 17196, 17222, 17249, 17275, 17302, 17328, 17354, 17381, 17407,  /* 512 - 543*/
                17434, 17460, 17486, 17513, 17539, 17566, 17592, 17618, 17645, 17671, 17698, 17724, 17750, 17777, 17803, 17830, 17856, 17882, 17909, 17935, 17962, 17988, 18014, 18041, 18067, 18094, 18120, 18146, 18173, 18199, 18226, 18252,  /* 544 - 575*/
                18278, 18305, 18331, 18358, 18384, 18410, 18437, 18463, 18490, 18516, 18542, 18569, 18595, 18622, 18648, 18674, 18701, 18727, 18754, 18780, 18806, 18833, 18859, 18886, 18912, 18938, 18965, 18991, 19018, 19044, 19070, 19097,  /* 576 - 607*/
                19123, 19150, 19176, 19202, 19229, 19255, 19282, 19308, 19334, 19361, 19387, 19414, 19440, 19466, 19493, 19519, 19546, 19572, 19598, 19625, 19651, 19678, 19704, 19730, 19757, 19783, 19810, 19836, 19862, 19889, 19915, 19942,  /* 608 - 639*/
                19968, 19994, 20021, 20047, 20074, 20100, 20126, 20153, 20179, 20206, 20232, 20258, 20285, 20311, 20338, 20364, 20390, 20417, 20443, 20470, 20496, 20522, 20549, 20575, 20602, 20628, 20654, 20681, 20707, 20734, 20760, 20786,  /* 640 - 671*/
                20813, 20839, 20866, 20892, 20918, 20945, 20971, 20998, 21024, 21050, 21077, 21103, 21130, 21156, 21182, 21209, 21235, 21262, 21288, 21314, 21341, 21367, 21394, 21420, 21446, 21473, 21499, 21526, 21552, 21578, 21605, 21631,  /* 672 - 703*/
                21658, 21684, 21710, 21737, 21763, 21790, 21816, 21842, 21869, 21895, 21922, 21948, 21974, 22001, 22027, 22054, 22080, 22106, 22133, 22159, 22186, 22212, 22238, 22265, 22291, 22318, 22344, 22370, 22397, 22423, 22450, 22476,  /* 704 - 735*/
                22502, 22529, 22555, 22582, 22608, 22634, 22661, 22687, 22714, 22740, 22766, 22793, 22819, 22846, 22872, 22898, 22925, 22951, 22978, 23004, 23030, 23057, 23083, 23110, 23136, 23162, 23189, 23215, 23242, 23268, 23294, 23321,  /* 736 - 767*/
                23347, 23374, 23400, 23427, 23453, 23480, 23506, 23533, 23559, 23586, 23613, 23639, 23666, 23693, 23720, 23747, 23773, 23800, 23827, 23854, 23881, 23908, 23935, 23962, 23990, 24017, 24044, 24071, 24098, 24126, 24153, 24180,  /* 768 - 799*/
                24208, 24235, 24263, 24290, 24318, 24345, 24373, 24401, 24428, 24456, 24484, 24511, 24539, 24567, 24595, 24623, 24651, 24679, 24707, 24735, 24763, 24791, 24820, 24848, 24876, 24905, 24933, 24961, 24990, 25018, 25047, 25075,  /* 800 - 831*/
                25104, 25133, 25161, 25190, 25219, 25248, 25277, 25305, 25334, 25363, 25392, 25422, 25451, 25480, 25509, 25538, 25568, 25597, 25627, 25656, 25686, 25715, 25745, 25774, 25804, 25834, 25864, 25894, 25923, 25953, 25983, 26013,  /* 832 - 863*/
                26044, 26074, 26104, 26134, 26165, 26195, 26225, 26256, 26287, 26317, 26348, 26379, 26409, 26440, 26471, 26502, 26533, 26564, 26595, 26627, 26658, 26689, 26721, 26752, 26784, 26815, 26847, 26879, 26910, 26942, 26974, 27006,  /* 864 - 895*/
                27038, 27070, 27103, 27135, 27167, 27200, 27232, 27265, 27298, 27330, 27363, 27396, 27429, 27462, 27495, 27528, 27562, 27595, 27629, 27662, 27696, 27730, 27763, 27797, 27831, 27865, 27900, 27934, 27968, 28003, 28037, 28072,  /* 896 - 927*/
                28107, 28142, 28177, 28212, 28247, 28282, 28318, 28353, 28389, 28425, 28460, 28496, 28533, 28569, 28605, 28642, 28678, 28715, 28752, 28789, 28826, 28863, 28901, 28938, 28976, 29014, 29052, 29090, 29128, 29167, 29205, 29244,  /* 928 - 959*/
                29283, 29322, 29362, 29401, 29441, 29481, 29521, 29561, 29602, 29642, 29683, 29724, 29765, 29807, 29849, 29891, 29933, 29976, 30018, 30061, 30105, 30148, 30192, 30236, 30281, 30325, 30370, 30416, 30462, 30508, 30554, 30601,  /* 960 - 991*/
                30649, 30696, 30744, 30793, 30842, 30892, 30942, 30993, 31044, 31096, 31148, 31201, 31255, 31310, 31365, 31422, 31479, 31537, 31597, 31657, 31719, 31783, 31848, 31915, 31984, 32056, 32130, 32208, 32291, 32380, 32478, 32592,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 217, 350, 462, 563, 657, 745, 828, 907, 984, 1058, 1129, 1199, 1267, 1333, 1398, 1461, 1523, 1585, 1645, 1704, 1762, 1819, 1875, 1931, 1986, 2040, 2094, 2147, 2199, 2251, 2303,  /* 0 - 31*/
                2353, 2404, 2454, 2503, 2552, 2600, 2649, 2696, 2744, 2791, 2837, 2883, 2929, 2975, 3020, 3065, 3110, 3154, 3199, 3242, 3286, 3329, 3372, 3415, 3458, 3500, 3542, 3584, 3626, 3667, 3708, 3749,  /* 32 - 63*/
                3790, 3831, 3871, 3911, 3951, 3991, 4031, 4070, 4110, 4149, 4188, 4227, 4265, 4304, 4342, 4381, 4419, 4456, 4494, 4532, 4569, 4607, 4644, 4681, 4718, 4755, 4791, 4828, 4864, 4900, 4937, 4973,  /* 64 - 95*/
                5009, 5044, 5080, 5116, 5151, 5187, 5222, 5257, 5292, 5327, 5362, 5396, 5431, 5466, 5500, 5534, 5569, 5603, 5637, 5671, 5705, 5738, 5772, 5806, 5839, 5872, 5906, 5939, 5972, 6005, 6038, 6071,  /* 96 - 127*/
                6104, 6137, 6169, 6202, 6234, 6267, 6299, 6332, 6364, 6396, 6428, 6460, 6492, 6524, 6555, 6587, 6619, 6650, 6682, 6713, 6745, 6776, 6807, 6838, 6869, 6901, 6931, 6962, 6993, 7024, 7055, 7085,  /* 128 - 159*/
                7116, 7147, 7177, 7208, 7238, 7268, 7298, 7329, 7359, 7389, 7419, 7449, 7479, 7509, 7538, 7568, 7598, 7628, 7657, 7687, 7716, 7746, 7775, 7804, 7834, 7863, 7892, 7921, 7950, 7979, 8008, 8037,  /* 160 - 191*/
                8066, 8095, 8124, 8153, 8181, 8210, 8239, 8267, 8296, 8324, 8353, 8381, 8410, 8438, 8466, 8494, 8523, 8551, 8579, 8607, 8635, 8663, 8691, 8719, 8747, 8774, 8802, 8830, 8858, 8885, 8913, 8941,  /* 192 - 223*/
                8968, 8996, 9023, 9051, 9078, 9105, 9133, 9160, 9187, 9214, 9241, 9269, 9296, 9323, 9350, 9377, 9404, 9431, 9458, 9484, 9511, 9538, 9565, 9591, 9618, 9645, 9671, 9698, 9725, 9751, 9778, 9804,  /* 224 - 255*/
                9830, 9857, 9883, 9910, 9936, 9962, 9989, 10015, 10042, 10068, 10094, 10121, 10147, 10174, 10200, 10226, 10253, 10279, 10306, 10332, 10358, 10385, 10411, 10438, 10464, 10490, 10517, 10543, 10570, 10596, 10622, 10649,  /* 256 - 287*/
                10675, 10702, 10728, 10754, 10781, 10807, 10834, 10860, 10886, 10913, 10939, 10966, 10992, 11018, 11045, 11071, 11098, 11124, 11150, 11177, 11203, 11230, 11256, 11282, 11309, 11335, 11362, 11388, 11414, 11441, 11467, 11494,  /* 288 - 319*/
                11520, 11546, 11573, 11599, 11626, 11652, 11678, 11705, 11731, 11758, 11784, 11810, 11837, 11863, 11890, 11916, 11942, 11969, 11995, 12022, 12048, 12074, 12101, 12127, 12154, 12180, 12206, 12233, 12259, 12286, 12312, 12338,  /* 320 - 351*/
                12365, 12391, 12418, 12444, 12470, 12497, 12523, 12550, 12576, 12602, 12629, 12655, 12682, 12708, 12734, 12761, 12787, 12814, 12840, 12866, 12893, 12919, 12946, 12972, 12998, 13025, 13051, 13078, 13104, 13130, 13157, 13183,  /* 352 - 383*/
                13210, 13236, 13262, 13289, 13315, 13342, 13368, 13394, 13421, 13447, 13474, 13500, 13526, 13553, 13579, 13606, 13632, 13658, 13685, 13711, 13738, 13764, 13790, 13817, 13843, 13870, 13896, 13922, 13949, 13975, 14002, 14028,  /* 384 - 415*/
                14054, 14081, 14107, 14134, 14160, 14186, 14213, 14239, 14266, 14292, 14318, 14345, 14371, 14398, 14424, 14450, 14477, 14503, 14530, 14556, 14582, 14609, 14635, 14662, 14688, 14714, 14741, 14767, 14794, 14820, 14846, 14873,  /* 416 - 447*/
                14899, 14926, 14952, 14978, 15005, 15031, 15058, 15084, 15110, 15137, 15163, 15190, 15216, 15242, 15269, 15295, 15322, 15348, 15374, 15401, 15427, 15454, 15480, 15506, 15533, 15559, 15586, 15612, 15638, 15665, 15691, 15718,  /* 448 - 479*/
                15744, 15770, 15797, 15823, 15850, 15876, 15902, 15929, 15955, 15982, 16008, 16034, 16061, 16087, 16114, 16140, 16166, 16193, 16219, 16246, 16272, 16298, 16325, 16351, 16378, 16404, 16430, 16457, 16483, 16510, 16536, 16562,  /* 480 - 511*/
                16589, 16615, 16642, 16668, 16694, 16721, 16747, 16774, 16800, 16826, 16853, 16879, 16906, 16932, 16958, 16985, 17011, 17038, 17064, 17090, 17117, 17143, 17170, 17196, 17222, 17249, 17275, 17302, 17328, 17354, 17381, 17407,  /* 512 - 543*/
                17434, 17460, 17486, 17513, 17539, 17566, 17592, 17618, 17645, 17671, 17698, 17724, 17750, 17777, 17803, 17830, 17856, 17882, 17909, 17935, 17962, 17988, 18014, 18041, 18067, 18094, 18120, 18146, 18173, 18199, 18226, 18252,  /* 544 - 575*/
                18278, 18305, 18331, 18358, 18384, 18410, 18437, 18463, 18490, 18516, 18542, 18569, 18595, 18622, 18648, 18674, 18701, 18727, 18754, 18780, 18806, 18833, 18859, 18886, 18912, 18938, 18965, 18991, 19018, 19044, 19070, 19097,  /* 576 - 607*/
                19123, 19150, 19176, 19202, 19229, 19255, 19282, 19308, 19334, 19361, 19387, 19414, 19440, 19466, 19493, 19519, 19546, 19572, 19598, 19625, 19651, 19678, 19704, 19730, 19757, 19783, 19810, 19836, 19862, 19889, 19915, 19942,  /* 608 - 639*/
                19968, 19994, 20021, 20047, 20074, 20100, 20126, 20153, 20179, 20206, 20232, 20258, 20285, 20311, 20338, 20364, 20390, 20417, 20443, 20470, 20496, 20522, 20549, 20575, 20602, 20628, 20654, 20681, 20707, 20734, 20760, 20786,  /* 640 - 671*/
                20813, 20839, 20866, 20892, 20918, 20945, 20971, 20998, 21024, 21050, 21077, 21103, 21130, 21156, 21182, 21209, 21235, 21262, 21288, 21314, 21341, 21367, 21394, 21420, 21446, 21473, 21499, 21526, 21552, 21578, 21605, 21631,  /* 672 - 703*/
                21658, 21684, 21710, 21737, 21763, 21790, 21816, 21842, 21869, 21895, 21922, 21948, 21974, 22001, 22027, 22054, 22080, 22106, 22133, 22159, 22186, 22212, 22238, 22265, 22291, 22318, 22344, 22370, 22397, 22423, 22450, 22476,  /* 704 - 735*/
                22502, 22529, 22555, 22582, 22608, 22634, 22661, 22687, 22714, 22740, 22766, 22793, 22819, 22846, 22872, 22898, 22925, 22951, 22978, 23004, 23030, 23057, 23083, 23110, 23136, 23162, 23189, 23215, 23242, 23268, 23294, 23321,  /* 736 - 767*/
                23347, 23374, 23400, 23427, 23453, 23480, 23506, 23533, 23559, 23586, 23613, 23639, 23666, 23693, 23720, 23747, 23773, 23800, 23827, 23854, 23881, 23908, 23935, 23962, 23990, 24017, 24044, 24071, 24098, 24126, 24153, 24180,  /* 768 - 799*/
                24208, 24235, 24263, 24290, 24318, 24345, 24373, 24401, 24428, 24456, 24484, 24511, 24539, 24567, 24595, 24623, 24651, 24679, 24707, 24735, 24763, 24791, 24820, 24848, 24876, 24905, 24933, 24961, 24990, 25018, 25047, 25075,  /* 800 - 831*/
                25104, 25133, 25161, 25190, 25219, 25248, 25277, 25305, 25334, 25363, 25392, 25422, 25451, 25480, 25509, 25538, 25568, 25597, 25627, 25656, 25686, 25715, 25745, 25774, 25804, 25834, 25864, 25894, 25923, 25953, 25983, 26013,  /* 832 - 863*/
                26044, 26074, 26104, 26134, 26165, 26195, 26225, 26256, 26287, 26317, 26348, 26379, 26409, 26440, 26471, 26502, 26533, 26564, 26595, 26627, 26658, 26689, 26721, 26752, 26784, 26815, 26847, 26879, 26910, 26942, 26974, 27006,  /* 864 - 895*/
                27038, 27070, 27103, 27135, 27167, 27200, 27232, 27265, 27298, 27330, 27363, 27396, 27429, 27462, 27495, 27528, 27562, 27595, 27629, 27662, 27696, 27730, 27763, 27797, 27831, 27865, 27900, 27934, 27968, 28003, 28037, 28072,  /* 896 - 927*/
                28107, 28142, 28177, 28212, 28247, 28282, 28318, 28353, 28389, 28425, 28460, 28496, 28533, 28569, 28605, 28642, 28678, 28715, 28752, 28789, 28826, 28863, 28901, 28938, 28976, 29014, 29052, 29090, 29128, 29167, 29205, 29244,  /* 928 - 959*/
                29283, 29322, 29362, 29401, 29441, 29481, 29521, 29561, 29602, 29642, 29683, 29724, 29765, 29807, 29849, 29891, 29933, 29976, 30018, 30061, 30105, 30148, 30192, 30236, 30281, 30325, 30370, 30416, 30462, 30508, 30554, 30601,  /* 960 - 991*/
                30649, 30696, 30744, 30793, 30842, 30892, 30942, 30993, 31044, 31096, 31148, 31201, 31255, 31310, 31365, 31422, 31479, 31537, 31597, 31657, 31719, 31783, 31848, 31915, 31984, 32056, 32130, 32208, 32291, 32380, 32478, 32592,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 217, 350, 462, 563, 657, 745, 828, 907, 984, 1058, 1129, 1199, 1267, 1333, 1398, 1461, 1523, 1585, 1645, 1704, 1762, 1819, 1875, 1931, 1986, 2040, 2094, 2147, 2199, 2251, 2303,  /* 0 - 31*/
                2353, 2404, 2454, 2503, 2552, 2600, 2649, 2696, 2744, 2791, 2837, 2883, 2929, 2975, 3020, 3065, 3110, 3154, 3199, 3242, 3286, 3329, 3372, 3415, 3458, 3500, 3542, 3584, 3626, 3667, 3708, 3749,  /* 32 - 63*/
                3790, 3831, 3871, 3911, 3951, 3991, 4031, 4070, 4110, 4149, 4188, 4227, 4265, 4304, 4342, 4381, 4419, 4456, 4494, 4532, 4569, 4607, 4644, 4681, 4718, 4755, 4791, 4828, 4864, 4900, 4937, 4973,  /* 64 - 95*/
                5009, 5044, 5080, 5116, 5151, 5187, 5222, 5257, 5292, 5327, 5362, 5396, 5431, 5466, 5500, 5534, 5569, 5603, 5637, 5671, 5705, 5738, 5772, 5806, 5839, 5872, 5906, 5939, 5972, 6005, 6038, 6071,  /* 96 - 127*/
                6104, 6137, 6169, 6202, 6234, 6267, 6299, 6332, 6364, 6396, 6428, 6460, 6492, 6524, 6555, 6587, 6619, 6650, 6682, 6713, 6745, 6776, 6807, 6838, 6869, 6901, 6931, 6962, 6993, 7024, 7055, 7085,  /* 128 - 159*/
                7116, 7147, 7177, 7208, 7238, 7268, 7298, 7329, 7359, 7389, 7419, 7449, 7479, 7509, 7538, 7568, 7598, 7628, 7657, 7687, 7716, 7746, 7775, 7804, 7834, 7863, 7892, 7921, 7950, 7979, 8008, 8037,  /* 160 - 191*/
                8066, 8095, 8124, 8153, 8181, 8210, 8239, 8267, 8296, 8324, 8353, 8381, 8410, 8438, 8466, 8494, 8523, 8551, 8579, 8607, 8635, 8663, 8691, 8719, 8747, 8774, 8802, 8830, 8858, 8885, 8913, 8941,  /* 192 - 223*/
                8968, 8996, 9023, 9051, 9078, 9105, 9133, 9160, 9187, 9214, 9241, 9269, 9296, 9323, 9350, 9377, 9404, 9431, 9458, 9484, 9511, 9538, 9565, 9591, 9618, 9645, 9671, 9698, 9725, 9751, 9778, 9804,  /* 224 - 255*/
                9830, 9857, 9883, 9910, 9936, 9962, 9989, 10015, 10042, 10068, 10094, 10121, 10147, 10174, 10200, 10226, 10253, 10279, 10306, 10332, 10358, 10385, 10411, 10438, 10464, 10490, 10517, 10543, 10570, 10596, 10622, 10649,  /* 256 - 287*/
                10675, 10702, 10728, 10754, 10781, 10807, 10834, 10860, 10886, 10913, 10939, 10966, 10992, 11018, 11045, 11071, 11098, 11124, 11150, 11177, 11203, 11230, 11256, 11282, 11309, 11335, 11362, 11388, 11414, 11441, 11467, 11494,  /* 288 - 319*/
                11520, 11546, 11573, 11599, 11626, 11652, 11678, 11705, 11731, 11758, 11784, 11810, 11837, 11863, 11890, 11916, 11942, 11969, 11995, 12022, 12048, 12074, 12101, 12127, 12154, 12180, 12206, 12233, 12259, 12286, 12312, 12338,  /* 320 - 351*/
                12365, 12391, 12418, 12444, 12470, 12497, 12523, 12550, 12576, 12602, 12629, 12655, 12682, 12708, 12734, 12761, 12787, 12814, 12840, 12866, 12893, 12919, 12946, 12972, 12998, 13025, 13051, 13078, 13104, 13130, 13157, 13183,  /* 352 - 383*/
                13210, 13236, 13262, 13289, 13315, 13342, 13368, 13394, 13421, 13447, 13474, 13500, 13526, 13553, 13579, 13606, 13632, 13658, 13685, 13711, 13738, 13764, 13790, 13817, 13843, 13870, 13896, 13922, 13949, 13975, 14002, 14028,  /* 384 - 415*/
                14054, 14081, 14107, 14134, 14160, 14186, 14213, 14239, 14266, 14292, 14318, 14345, 14371, 14398, 14424, 14450, 14477, 14503, 14530, 14556, 14582, 14609, 14635, 14662, 14688, 14714, 14741, 14767, 14794, 14820, 14846, 14873,  /* 416 - 447*/
                14899, 14926, 14952, 14978, 15005, 15031, 15058, 15084, 15110, 15137, 15163, 15190, 15216, 15242, 15269, 15295, 15322, 15348, 15374, 15401, 15427, 15454, 15480, 15506, 15533, 15559, 15586, 15612, 15638, 15665, 15691, 15718,  /* 448 - 479*/
                15744, 15770, 15797, 15823, 15850, 15876, 15902, 15929, 15955, 15982, 16008, 16034, 16061, 16087, 16114, 16140, 16166, 16193, 16219, 16246, 16272, 16298, 16325, 16351, 16378, 16404, 16430, 16457, 16483, 16510, 16536, 16562,  /* 480 - 511*/
                16589, 16615, 16642, 16668, 16694, 16721, 16747, 16774, 16800, 16826, 16853, 16879, 16906, 16932, 16958, 16985, 17011, 17038, 17064, 17090, 17117, 17143, 17170, 17196, 17222, 17249, 17275, 17302, 17328, 17354, 17381, 17407,  /* 512 - 543*/
                17434, 17460, 17486, 17513, 17539, 17566, 17592, 17618, 17645, 17671, 17698, 17724, 17750, 17777, 17803, 17830, 17856, 17882, 17909, 17935, 17962, 17988, 18014, 18041, 18067, 18094, 18120, 18146, 18173, 18199, 18226, 18252,  /* 544 - 575*/
                18278, 18305, 18331, 18358, 18384, 18410, 18437, 18463, 18490, 18516, 18542, 18569, 18595, 18622, 18648, 18674, 18701, 18727, 18754, 18780, 18806, 18833, 18859, 18886, 18912, 18938, 18965, 18991, 19018, 19044, 19070, 19097,  /* 576 - 607*/
                19123, 19150, 19176, 19202, 19229, 19255, 19282, 19308, 19334, 19361, 19387, 19414, 19440, 19466, 19493, 19519, 19546, 19572, 19598, 19625, 19651, 19678, 19704, 19730, 19757, 19783, 19810, 19836, 19862, 19889, 19915, 19942,  /* 608 - 639*/
                19968, 19994, 20021, 20047, 20074, 20100, 20126, 20153, 20179, 20206, 20232, 20258, 20285, 20311, 20338, 20364, 20390, 20417, 20443, 20470, 20496, 20522, 20549, 20575, 20602, 20628, 20654, 20681, 20707, 20734, 20760, 20786,  /* 640 - 671*/
                20813, 20839, 20866, 20892, 20918, 20945, 20971, 20998, 21024, 21050, 21077, 21103, 21130, 21156, 21182, 21209, 21235, 21262, 21288, 21314, 21341, 21367, 21394, 21420, 21446, 21473, 21499, 21526, 21552, 21578, 21605, 21631,  /* 672 - 703*/
                21658, 21684, 21710, 21737, 21763, 21790, 21816, 21842, 21869, 21895, 21922, 21948, 21974, 22001, 22027, 22054, 22080, 22106, 22133, 22159, 22186, 22212, 22238, 22265, 22291, 22318, 22344, 22370, 22397, 22423, 22450, 22476,  /* 704 - 735*/
                22502, 22529, 22555, 22582, 22608, 22634, 22661, 22687, 22714, 22740, 22766, 22793, 22819, 22846, 22872, 22898, 22925, 22951, 22978, 23004, 23030, 23057, 23083, 23110, 23136, 23162, 23189, 23215, 23242, 23268, 23294, 23321,  /* 736 - 767*/
                23347, 23374, 23400, 23427, 23453, 23480, 23506, 23533, 23559, 23586, 23613, 23639, 23666, 23693, 23720, 23747, 23773, 23800, 23827, 23854, 23881, 23908, 23935, 23962, 23990, 24017, 24044, 24071, 24098, 24126, 24153, 24180,  /* 768 - 799*/
                24208, 24235, 24263, 24290, 24318, 24345, 24373, 24401, 24428, 24456, 24484, 24511, 24539, 24567, 24595, 24623, 24651, 24679, 24707, 24735, 24763, 24791, 24820, 24848, 24876, 24905, 24933, 24961, 24990, 25018, 25047, 25075,  /* 800 - 831*/
                25104, 25133, 25161, 25190, 25219, 25248, 25277, 25305, 25334, 25363, 25392, 25422, 25451, 25480, 25509, 25538, 25568, 25597, 25627, 25656, 25686, 25715, 25745, 25774, 25804, 25834, 25864, 25894, 25923, 25953, 25983, 26013,  /* 832 - 863*/
                26044, 26074, 26104, 26134, 26165, 26195, 26225, 26256, 26287, 26317, 26348, 26379, 26409, 26440, 26471, 26502, 26533, 26564, 26595, 26627, 26658, 26689, 26721, 26752, 26784, 26815, 26847, 26879, 26910, 26942, 26974, 27006,  /* 864 - 895*/
                27038, 27070, 27103, 27135, 27167, 27200, 27232, 27265, 27298, 27330, 27363, 27396, 27429, 27462, 27495, 27528, 27562, 27595, 27629, 27662, 27696, 27730, 27763, 27797, 27831, 27865, 27900, 27934, 27968, 28003, 28037, 28072,  /* 896 - 927*/
                28107, 28142, 28177, 28212, 28247, 28282, 28318, 28353, 28389, 28425, 28460, 28496, 28533, 28569, 28605, 28642, 28678, 28715, 28752, 28789, 28826, 28863, 28901, 28938, 28976, 29014, 29052, 29090, 29128, 29167, 29205, 29244,  /* 928 - 959*/
                29283, 29322, 29362, 29401, 29441, 29481, 29521, 29561, 29602, 29642, 29683, 29724, 29765, 29807, 29849, 29891, 29933, 29976, 30018, 30061, 30105, 30148, 30192, 30236, 30281, 30325, 30370, 30416, 30462, 30508, 30554, 30601,  /* 960 - 991*/
                30649, 30696, 30744, 30793, 30842, 30892, 30942, 30993, 31044, 31096, 31148, 31201, 31255, 31310, 31365, 31422, 31479, 31537, 31597, 31657, 31719, 31783, 31848, 31915, 31984, 32056, 32130, 32208, 32291, 32380, 32478, 32592,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 139, 235, 320, 398, 472, 542, 609, 674, 738, 799, 859, 918, 976, 1032, 1088, 1143, 1197, 1250, 1302, 1354, 1405, 1456, 1506, 1556, 1605, 1653, 1701, 1749, 1796, 1843, 1890,  /* 0 - 31*/
                1936, 1982, 2028, 2073, 2118, 2162, 2207, 2251, 2295, 2338, 2381, 2424, 2467, 2510, 2552, 2594, 2636, 2678, 2719, 2760, 2801, 2842, 2883, 2924, 2964, 3004, 3044, 3084, 3124, 3163, 3203, 3242,  /* 32 - 63*/
                3281, 3320, 3359, 3397, 3436, 3474, 3512, 3551, 3589, 3626, 3664, 3702, 3739, 3777, 3814, 3851, 3888, 3925, 3962, 3999, 4035, 4072, 4108, 4144, 4181, 4217, 4253, 4289, 4324, 4360, 4396, 4431,  /* 64 - 95*/
                4467, 4502, 4537, 4572, 4608, 4643, 4678, 4712, 4747, 4782, 4816, 4851, 4885, 4920, 4954, 4988, 5022, 5057, 5091, 5125, 5158, 5192, 5226, 5260, 5293, 5327, 5360, 5394, 5427, 5460, 5493, 5527,  /* 96 - 127*/
                5560, 5593, 5626, 5658, 5691, 5724, 5757, 5789, 5822, 5855, 5887, 5920, 5952, 5984, 6016, 6049, 6081, 6113, 6145, 6177, 6209, 6241, 6273, 6304, 6336, 6368, 6400, 6431, 6463, 6494, 6526, 6557,  /* 128 - 159*/
                6588, 6620, 6651, 6682, 6713, 6744, 6776, 6807, 6838, 6869, 6899, 6930, 6961, 6992, 7023, 7053, 7084, 7115, 7145, 7176, 7206, 7237, 7267, 7297, 7328, 7358, 7388, 7418, 7448, 7479, 7509, 7539,  /* 160 - 191*/
                7569, 7599, 7629, 7659, 7688, 7718, 7748, 7778, 7808, 7837, 7867, 7897, 7926, 7956, 7985, 8015, 8044, 8073, 8103, 8132, 8161, 8191, 8220, 8249, 8278, 8308, 8337, 8366, 8395, 8424, 8453, 8482,  /* 192 - 223*/
                8511, 8540, 8568, 8597, 8626, 8655, 8684, 8712, 8741, 8770, 8798, 8827, 8855, 8884, 8912, 8941, 8969, 8998, 9026, 9055, 9083, 9111, 9139, 9168, 9196, 9224, 9252, 9280, 9309, 9337, 9365, 9393,  /* 224 - 255*/
                9421, 9449, 9477, 9505, 9533, 9561, 9589, 9617, 9645, 9673, 9701, 9729, 9757, 9785, 9813, 9841, 9869, 9897, 9925, 9953, 9981, 10009, 10037, 10065, 10093, 10121, 10149, 10177, 10205, 10233, 10261, 10289,  /* 256 - 287*/
                10317, 10345, 10373, 10401, 10429, 10457, 10485, 10513, 10541, 10569, 10597, 10625, 10653, 10681, 10709, 10737, 10765, 10793, 10821, 10849, 10877, 10905, 10933, 10961, 10989, 11017, 11045, 11073, 11101, 11129, 11157, 11185,  /* 288 - 319*/
                11213, 11241, 11269, 11297, 11325, 11353, 11381, 11409, 11437, 11465, 11493, 11521, 11549, 11577, 11605, 11633, 11661, 11689, 11717, 11745, 11773, 11801, 11829, 11857, 11885, 11913, 11941, 11969, 11997, 12025, 12053, 12081,  /* 320 - 351*/
                12109, 12137, 12165, 12193, 12221, 12249, 12277, 12305, 12333, 12361, 12389, 12417, 12445, 12473, 12501, 12529, 12557, 12585, 12613, 12641, 12669, 12697, 12725, 12753, 12781, 12809, 12837, 12865, 12893, 12921, 12949, 12977,  /* 352 - 383*/
                13005, 13033, 13061, 13089, 13117, 13145, 13173, 13201, 13229, 13257, 13285, 13313, 13341, 13369, 13397, 13425, 13453, 13481, 13509, 13537, 13565, 13593, 13621, 13649, 13677, 13705, 13733, 13761, 13789, 13817, 13845, 13873,  /* 384 - 415*/
                13901, 13929, 13957, 13985, 14013, 14041, 14069, 14097, 14125, 14153, 14181, 14209, 14237, 14265, 14293, 14321, 14349, 14377, 14405, 14433, 14461, 14489, 14517, 14545, 14573, 14601, 14629, 14657, 14685, 14713, 14741, 14769,  /* 416 - 447*/
                14797, 14825, 14853, 14881, 14909, 14937, 14965, 14993, 15021, 15049, 15077, 15105, 15133, 15161, 15189, 15217, 15245, 15273, 15301, 15329, 15357, 15385, 15413, 15441, 15469, 15497, 15525, 15553, 15581, 15609, 15637, 15665,  /* 448 - 479*/
                15693, 15721, 15749, 15777, 15805, 15833, 15861, 15889, 15917, 15945, 15973, 16001, 16029, 16057, 16085, 16113, 16141, 16169, 16197, 16225, 16253, 16281, 16309, 16337, 16365, 16393, 16421, 16449, 16477, 16505, 16533, 16561,  /* 480 - 511*/
                16589, 16617, 16645, 16673, 16701, 16729, 16757, 16785, 16813, 16841, 16869, 16897, 16925, 16953, 16981, 17009, 17037, 17065, 17093, 17121, 17149, 17177, 17205, 17233, 17261, 17289, 17317, 17345, 17373, 17401, 17429, 17457,  /* 512 - 543*/
                17485, 17513, 17541, 17569, 17597, 17625, 17653, 17681, 17709, 17737, 17765, 17793, 17821, 17849, 17877, 17905, 17933, 17961, 17989, 18017, 18045, 18073, 18101, 18129, 18157, 18185, 18213, 18241, 18269, 18297, 18325, 18353,  /* 544 - 575*/
                18381, 18409, 18437, 18465, 18493, 18521, 18549, 18577, 18605, 18633, 18661, 18689, 18717, 18745, 18773, 18801, 18829, 18857, 18885, 18913, 18941, 18969, 18997, 19025, 19053, 19081, 19109, 19137, 19165, 19193, 19221, 19249,  /* 576 - 607*/
                19277, 19305, 19333, 19361, 19389, 19417, 19445, 19473, 19501, 19529, 19557, 19585, 19613, 19641, 19669, 19697, 19725, 19753, 19781, 19809, 19837, 19865, 19893, 19921, 19949, 19977, 20005, 20033, 20061, 20089, 20117, 20145,  /* 608 - 639*/
                20173, 20201, 20229, 20257, 20285, 20313, 20341, 20369, 20397, 20425, 20453, 20481, 20509, 20537, 20565, 20593, 20621, 20649, 20677, 20705, 20733, 20761, 20789, 20817, 20845, 20873, 20901, 20929, 20957, 20985, 21013, 21041,  /* 640 - 671*/
                21069, 21097, 21125, 21153, 21181, 21209, 21237, 21265, 21293, 21321, 21349, 21377, 21405, 21433, 21461, 21489, 21517, 21545, 21573, 21601, 21629, 21657, 21685, 21713, 21741, 21769, 21797, 21825, 21853, 21881, 21909, 21937,  /* 672 - 703*/
                21965, 21993, 22021, 22049, 22077, 22105, 22133, 22161, 22189, 22217, 22245, 22273, 22301, 22329, 22357, 22385, 22413, 22441, 22469, 22497, 22525, 22553, 22581, 22609, 22637, 22665, 22693, 22721, 22749, 22777, 22805, 22833,  /* 704 - 735*/
                22861, 22889, 22917, 22945, 22973, 23001, 23029, 23057, 23085, 23113, 23141, 23169, 23197, 23225, 23253, 23281, 23309, 23337, 23365, 23393, 23421, 23449, 23477, 23505, 23533, 23561, 23589, 23617, 23645, 23673, 23701, 23729,  /* 736 - 767*/
                23757, 23785, 23813, 23841, 23869, 23897, 23925, 23953, 23982, 24010, 24038, 24066, 24094, 24123, 24151, 24179, 24208, 24236, 24265, 24293, 24321, 24350, 24378, 24407, 24435, 24464, 24493, 24521, 24550, 24579, 24607, 24636,  /* 768 - 799*/
                24665, 24694, 24722, 24751, 24780, 24809, 24838, 24867, 24896, 24925, 24954, 24983, 25012, 25041, 25070, 25100, 25129, 25158, 25187, 25217, 25246, 25275, 25305, 25334, 25363, 25393, 25422, 25452, 25481, 25511, 25541, 25570,  /* 800 - 831*/
                25600, 25630, 25659, 25689, 25719, 25749, 25779, 25809, 25839, 25869, 25899, 25929, 25959, 25989, 26019, 26049, 26079, 26110, 26140, 26170, 26201, 26231, 26261, 26292, 26322, 26353, 26383, 26414, 26445, 26475, 26506, 26537,  /* 832 - 863*/
                26568, 26599, 26629, 26660, 26691, 26722, 26753, 26784, 26816, 26847, 26878, 26909, 26941, 26972, 27003, 27035, 27066, 27098, 27129, 27161, 27192, 27224, 27256, 27288, 27320, 27351, 27383, 27415, 27447, 27480, 27512, 27544,  /* 864 - 895*/
                27576, 27608, 27641, 27673, 27706, 27738, 27771, 27803, 27836, 27869, 27901, 27934, 27967, 28000, 28033, 28066, 28099, 28132, 28166, 28199, 28232, 28266, 28299, 28333, 28367, 28400, 28434, 28468, 28502, 28536, 28570, 28604,  /* 896 - 927*/
                28638, 28672, 28707, 28741, 28776, 28810, 28845, 28879, 28914, 28949, 28984, 29019, 29054, 29089, 29125, 29160, 29196, 29231, 29267, 29303, 29338, 29374, 29410, 29447, 29483, 29519, 29556, 29592, 29629, 29666, 29702, 29740,  /* 928 - 959*/
                29777, 29814, 29851, 29889, 29926, 29964, 30002, 30040, 30078, 30116, 30155, 30193, 30232, 30271, 30310, 30349, 30388, 30428, 30468, 30508, 30548, 30588, 30628, 30669, 30710, 30751, 30792, 30833, 30875, 30917, 30959, 31002,  /* 960 - 991*/
                31044, 31087, 31131, 31174, 31218, 31262, 31307, 31352, 31397, 31443, 31489, 31535, 31582, 31630, 31677, 31726, 31775, 31825, 31875, 31926, 31978, 32031, 32085, 32140, 32196, 32254, 32313, 32374, 32438, 32506, 32578, 32659,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
        },
        /* tHistWt */
        {
            /* 0 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 1 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 2 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 3 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 4 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 5 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 6 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 7 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 8 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 9 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 10 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
            /* 11 */
            {
                /* 0 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 1 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 2 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 3 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 4 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 5 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 6 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 7 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 8 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 9 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 10 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 11 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 12 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 13 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 14 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
                /* 15 */
                {
                    /* nHistogramWeight[63] */
                    {
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  /* 0 - 31*/
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*32 - 62*/
                    },
                },
            },
        },
        /* tHighFreqEnh[12] */
        {
            /* 0 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                80,
                /* nDetailCoringNeg */
                50,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 1 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                80,
                /* nDetailCoringNeg */
                50,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 2 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                80,
                /* nDetailCoringNeg */
                50,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 3 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                90,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 4 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 5 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 6 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 7 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 8 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                15,
                /* nDetailExtraStrNeg */
                30,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 9 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                10,
                /* nDetailExtraStrNeg */
                20,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 10 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                120,
                /* nDetailCoringNeg */
                70,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                5,
                /* nDetailExtraStrNeg */
                15,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
            /* 11 */
            {
                /* nDetailSigmaDis */
                8000,
                /* nDetailSigmaVal */
                800,
                /* nDetailCoringPos */
                140,
                /* nDetailCoringNeg */
                80,
                /* nDetailGainPos */
                50,
                /* nDetailGainNeg */
                90,
                /* nDetailExtraStrPos */
                0,
                /* nDetailExtraStrNeg */
                10,
                /* nDetailGainLimitPos */
                65535,
                /* nDetailGainLimitNeg */
                65535,
                /* nSlopeStrengthLut[33] */
                {
                    8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192, 8192,  /* 0 - 31*/
                    8192, /*32 - 32*/
                },
                /* nSlopeCoeff */
                16384,
            },
        },
        /* tLowFreqEnh[12] */
        {
            /* 0 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 1 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 2 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 3 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 4 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 5 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 6 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 7 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 8 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 9 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 10 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
            /* 11 */
            {
                /* nRltmDetailLowEn */
                0,
                /* nSigmaDisBlur */
                9000,
                /* nDetailGainPosLow */
                64,
                /* nDetailGainNegLow */
                64,
                /* nDetailLimitPosLow */
                65535,
                /* nDetailLimitNegLow */
                65535,
                /* nSigmaDisPst */
                9000,
                /* nSigmaValPst */
                1000,
            },
        },
    },
};

const static AX_ISP_IQ_DEMOSAIC_PARAM_T demosaic_param_sdr = {
    /* nDemosaicEn */
    1,
    /* nMode */
    0,
    /* nFreqSensitivity */
    12,
    /* nEdgeDirectEstStrengthLut[9] */
    {128, 256, 384, 448, 512, 576, 640, 704, 768, /*0 - 8*/},
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tManualParam */
    {
        /* nEdgeDirectEstStrength */
        64,
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        16,
        /* nRefVal[16] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, 2097152, 2097152, 2097152, 2097152, /*0 - 15*/},
        /* nEdgeDirectEstStrength[16] */
        {64, 64, 64, 64, 96, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 15*/},
    },
};

const static AX_ISP_IQ_GIC_PARAM_T gic_param_sdr = {
    /* nGicEnable */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    0,
    /* tManualParam */
    {
        /* nGicStrengthLut[9] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        16,
        /* nRefVal[16] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, 2097152, 2097152, 2097152, 2097152, /*0 - 15*/},
        /* nGicStrengthLut[16][9] */
        {
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
            {128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
        },
    },
};

const static AX_ISP_IQ_FCC_PARAM_T fcc_param_sdr = {
    /* nFcCorEnable */
    0,
    /* nFcCorLimit */
    512,
    /* nAutoMode */
    0,
    /* nRefMode */
    0,
    /* tManualParam */
    {
        /* nFcCorStrength */
        16,
        /* nFcCorSatLut[9] */
        {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
        /* nFcCorSatLevel0 */
        11,
        /* nFcCorSatLevel1 */
        16,
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        16,
        /* nRefVal[16] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, 2097152, 2097152, 2097152, 2097152, /*0 - 15*/},
        /* nFcCorStrength[16] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 15*/},
        /* nFcCorSatLut[16][9] */
        {
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
            {8, 16, 32, 64, 128, 256, 256, 256, 256, /*0 - 8*/},
        },
        /* nFcCorSatLevel0[16] */
        {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,  /*0 - 15*/},
        /* nFcCorSatLevel1[16] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,  /*0 - 15*/},
    },
};

const static AX_ISP_IQ_DEPURPLE_PARAM_T depurple_param_sdr = {
    /* nEnable */
    1,
    /* nAutoMode */
    0,
    /* nRefMode */
    1,
    /* nDepurpleMode */
    1,
    /* tDetParam */
    {
        /* nDetMode */
        0,
        /* nDetEdgeSlopeY */
        4,
        /* nDetEdgeOffsetY */
        -32,
        /* nDetEdgeEnableC */
        1,
        /* nDetEdgeSlopeC */
        2,
        /* nDetEdgeOffsetC */
        -16,
        /* nDetSeledgeThrY */
        14080,
        /* nDetSeledgeSlopeY */
        1,
        /* nDetSeledgeWeight[7] */
        {64, 64, 48, 40, 32, 24, 16, /*0 - 6*/},
        /* nDetMaskStrength */
        64,
        /* nDetMaskStrengthPre */
        64,
        /* nDetMaskWeightPre[11] */
        {64, 64, 64, 48, 48, 48, 32, 32, 32, 32, 16, /*0 - 10*/},
    },
    /* tCmpParam */
    {
        /* nDebugMaskHighlightEnable */
        0,
        /* nDebugMaskHighlightThr */
        0,
    },
    /* tManualParam */
    {
        /* nCompStrength */
        128,
        /* nCompTargetLuma[8] */
        {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
        /* nCompTargetHue[16] */
        {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
        /* nCompTargetSat[6] */
        {128, 128, 128, 128, 128, 128, /*0 - 5*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[16] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nCompStrength[16] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nCompTargetLuma[16][8] */
        {
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
            {0, 0, 0, 16, 32, 96, 80, 32, /*0 - 7*/},
        },
        /* nCompTargetHue[16][16] */
        {
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
            {120, 75, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 90, /*0 - 15*/},
        },
        /* nCompTargetSat[16][6] */
        {
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
            {128, 128, 128, 128, 128, 128, /*0 - 5*/},
        },
    },
};

const static AX_ISP_IQ_CC_PARAM_T cc_param_sdr = {
    /* nCcEn */
    1,
    /* nCcMode */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* nLumaRatio[2] */
    {38, 15, /*0 - 1*/},
    /* tManualParam */
    {
        /* nCcmCtrlLevel */
        256,
        /* nCcmSat */
        5,
        /* nCcmHue */
        0,
        /* nCcmMatrix[6] */
        {-257, -5, -53, -30, 0, -155, /*0 - 5*/},
        /* nXcmCtrlLevel[16] */
        {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
        /* nXcmSat[16] */
        {-8, -5, 0, -5, -10, -5, 0, 0, 5, 12, 15, 12, 0, 0, 0, -5, /*0 - 15*/},
        /* nXcmHue[16] */
        {0, 0, 0, 0, 0, 0, 0, 0, 640, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
    },
    /* tAutoParam */
    {
        /* nLightSourceRatio */
        0,
        /* tColorTempAuto */
        {
            /* nCtNum */
            7,
            /* nRefValCt[12] */
            {2300, 2854, 3800, 4100, 5000, 6500, 7500, /*0 - 6*/},
            /* nLuxGainNum */
            4,
            /* nRefValLuxGain[12][5] */
            {
                {1024, 16384, 110592, 524288, /*0 - 3*/},
                {1024, 16384, 110592, 524288, /*0 - 3*/},
                {1024, 16384, 110592, 524288, /*0 - 3*/},
                {1024, 16384, 110592, 524288, /*0 - 3*/},
                {1024, 16384, 110592, 524288, /*0 - 3*/},
                {1024, 16384, 110592, 524288, /*0 - 3*/},
                {1024, 16384, 110592, 524288, /*0 - 3*/},
            },
            /* nCcmCtrlLevel[12][5] */
            {
                {256, 256, 256, 256, /*0 - 3*/},
                {256, 256, 256, 256, /*0 - 3*/},
                {256, 256, 256, 256, /*0 - 3*/},
                {256, 256, 256, 256, /*0 - 3*/},
                {256, 256, 256, 256, /*0 - 3*/},
                {256, 256, 256, 256, /*0 - 3*/},
                {256, 256, 256, 256, /*0 - 3*/},
            },
            /* nCcmSat[12][5] */
            {
                {-10, -10, -10, -10, /*0 - 3*/},
                {-5, -5, -5, -10, /*0 - 3*/},
                {5, 5, 5, -5, /*0 - 3*/},
                {7, 5, 5, -5, /*0 - 3*/},
                {10, 7, 5, -5, /*0 - 3*/},
                {10, 7, 5, -5, /*0 - 3*/},
                {7, 5, 5, -5, /*0 - 3*/},
            },
            /* nCcmHue[12][5] */
            {
                {0, 0, 0, 0, /*0 - 3*/},
                {0, 0, 0, 0, /*0 - 3*/},
                {0, 0, 0, 0, /*0 - 3*/},
                {0, 0, 0, 0, /*0 - 3*/},
                {0, 0, 0, 0, /*0 - 3*/},
                {0, 0, 0, 0, /*0 - 3*/},
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCcmMatrix[12][5][6] */
            {
                /* nCcmMatrix 0 */
                {
                    {37, -92, -113, 9, -15, -312, /*0 - 5*/},
                    {37, -92, -113, 9, -15, -312, /*0 - 5*/},
                    {37, -92, -113, 9, -15, -312, /*0 - 5*/},
                    {37, -92, -113, 9, -15, -312, /*0 - 5*/},
                },
                /* nCcmMatrix 1 */
                {
                    {-3, -71, -102, -18, -1, -224, /*0 - 5*/},
                    {-3, -71, -102, -18, -1, -224, /*0 - 5*/},
                    {-3, -71, -102, -18, -1, -224, /*0 - 5*/},
                    {-3, -71, -102, -18, -1, -224, /*0 - 5*/},
                },
                /* nCcmMatrix 2 */
                {
                    {-47, -57, -84, -47, -1, -182, /*0 - 5*/},
                    {-47, -57, -84, -47, -1, -182, /*0 - 5*/},
                    {-47, -57, -84, -47, -1, -182, /*0 - 5*/},
                    {-47, -57, -84, -47, -1, -182, /*0 - 5*/},
                },
                /* nCcmMatrix 3 */
                {
                    {-52, -54, -80, -52, -2, -175, /*0 - 5*/},
                    {-52, -54, -80, -52, -2, -175, /*0 - 5*/},
                    {-52, -54, -80, -52, -2, -175, /*0 - 5*/},
                    {-52, -54, -80, -52, -2, -175, /*0 - 5*/},
                },
                /* nCcmMatrix 4 */
                {
                    {-73, -46, -69, -61, -2, -162, /*0 - 5*/},
                    {-73, -46, -69, -61, -2, -162, /*0 - 5*/},
                    {-73, -46, -69, -61, -2, -162, /*0 - 5*/},
                    {-73, -46, -69, -61, -2, -162, /*0 - 5*/},
                },
                /* nCcmMatrix 5 */
                {
                    {-95, -37, -60, -70, -3, -154, /*0 - 5*/},
                    {-95, -37, -60, -70, -3, -154, /*0 - 5*/},
                    {-95, -37, -60, -70, -3, -154,/*0 - 5*/},
                    {-95, -37, -60, -70, -3, -154, /*0 - 5*/},
                },
                /* nCcmMatrix 6 */
                {
                    {-110, -33, -55, -74, -4, -150, /*0 - 5*/},
                    {-110, -33, -55, -74, -4, -150, /*0 - 5*/},
                    {-110, -33, -55, -74, -4, -150, /*0 - 5*/},
                    {-110, -33, -55, -74, -4, -150, /*0 - 5*/},
                },
            },
            /* nXcmCtrlLevel[12][5][16] */
            {
                /* nXcmCtrlLevel 0 */
                {
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                },
                /* nXcmCtrlLevel 1 */
                {
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                },
                /* nXcmCtrlLevel 2 */
                {
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                },
                /* nXcmCtrlLevel 3 */
                {
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                },
                /* nXcmCtrlLevel 4 */
                {
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                },
                /* nXcmCtrlLevel 5 */
                {
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                },
                /* nXcmCtrlLevel 6 */
                {
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                    {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
                },
            },
            /* nXcmSat[12][5][16] */
            {
                /* nXcmSat 0 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmSat 1 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmSat 2 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmSat 3 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmSat 4 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmSat 5 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmSat 6 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
            },
            /* nXcmHue[12][5][16] */
            {
                /* nXcmHue 0 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 1 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 2 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 3 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 4 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 5 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 6 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                },
            },
        },
        /* tLightSourceAuto */
        {
            /* nLightSource */
            0,
            /* nLightSourceNum */
            0,
            /* nCcmCtrlLevel[12] */
            {0, /*0 - 0*/},
            /* nCcmSat[12] */
            {0, /*0 - 0*/},
            /* nCcmHue[12] */
            {0, /*0 - 0*/},
            /* nCcmMatrix[12][6] */
            {
                {0, 0, 0, 0, 0, 0, /*0 - 5*/},
            },
            /* nXcmCtrlLevel[12][16] */
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            },
            /* nXcmSat[12][16] */
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            },
            /* nXcmHue[12][16] */
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
            },
        },
    },
};

const static AX_ISP_IQ_HS2DLUT_PARAM_T hs2dlut_param_sdr = {
    /* nHs2dLutEn */
    0,
    /* nAutoMode */
    0,
    /* nRefMode */
    1,
    /* tManualParam */
    {
        /* tHs2dLut */
        {
            /* nHueLut[25][17] */
            {
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
            },
            /* nSatLut[25][17] */
            {
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
            },
        },
    },
    /* tAutoParam */
    {
        /* nRefListNum */
        1,
        /* tRefTbl[12] */
        {
            /* 0 */
            {
                /* nRefStartVal */
                1024,
                /* nRefEndVal */
                2048,
                /* nCctListNum */
                1,
                /* tCctTbl[16] */
                {
                    /* 0 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 1 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 2 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 3 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 4 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 5 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 6 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 7 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 8 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 9 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 10 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 11 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 12 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 13 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 14 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                    /* 15 */
                    {
                        /* nCctStart */
                        5000,
                        /* nCctEnd */
                        6000,
                        /* tHs2dLut */
                        {
                            /* nHueLut[25][17] */
                            {
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 16*/},
                            },
                            /* nSatLut[25][17] */
                            {
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                                {0, 2048, 4096, 6144, 8192, 10240, 12288, 14336, 16384, 18432, 20480, 22528, 24576, 26624, 28672, 30720, 32768, /*0 - 16*/},
                            },
                        },
                    },
                },
            },
        },
        /* tConvergeParam */
        {
            /* nConvergeSpeed */
            5,
            /* nGainTrigger */
            10240,
            /* nLuxTrigger */
            10240,
            /* nCctTrigger */
            50,
        },
    },
};

const static AX_ISP_IQ_GAMMA_PARAM_T gamma_param_sdr = {
    /* nGammaEn */
    1,
    /* nAutoMode */
    0,
    /* nRefMode */
    0,
    /* eGammaMode */
    /* 0:AX_ISP_GAM_USER_GAMMA, 1:AX_ISP_GAM_PRESET_GAMMA */
    AX_ISP_GAM_PRESET_GAMMA,
    /* ePresetGammaType */
    /* 0:AX_ISP_GAM_LINEAR, 1:AX_ISP_GAM_BT709, 2:AX_ISP_GAM_SRGB, 10:AX_ISP_GAM_AX_GAM0, 11:AX_ISP_GAM_AX_GAM1, 12:AX_ISP_GAM_AX_GAM2, 255:AX_ISP_GAM_MODE_CUSTOMER */
    AX_ISP_GAM_AX_GAM2,
    /* eLutMode */
    /* 0:AX_ISP_GAM_LUT_LINEAR, 1:AX_ISP_GAM_EXPONENTIAL */
    AX_ISP_GAM_EXPONENTIAL,
    /* tManualParam */
    {
        /* tGammaLut */
        {
            /* nLut[129] */
            {
                0, 3, 6, 10, 13, 16, 20, 23, 27, 30, 34, 38, 41, 45, 48, 52, 56, 60, 63, 67, 71, 75, 79, 83, 87, 91, 94, 98, 103, 107, 111, 115,  /* 0 - 31*/
                119, 127, 136, 144, 153, 162, 171, 180, 189, 198, 207, 217, 226, 236, 245, 255, 265, 285, 306, 326, 348, 369, 391, 414, 437, 460, 483, 507, 531, 556, 581, 606,  /* 32 - 63*/
                632, 683, 733, 782, 830, 877, 922, 967, 1011, 1055, 1097, 1138, 1179, 1219, 1258, 1297, 1335, 1408, 1479, 1548, 1614, 1679, 1741, 1802, 1860, 1917, 1972, 2026, 2078, 2129, 2178, 2226,  /* 64 - 95*/
                2273, 2362, 2448, 2529, 2606, 2679, 2749, 2816, 2880, 2941, 2999, 3055, 3108, 3159, 3208, 3255, 3300, 3385, 3463, 3534, 3601, 3662, 3719, 3771, 3820, 3864, 3906, 3944, 3979, 4012, 4042, 4070,  /* 96 - 127*/
                4095, /*128 - 128*/
            },
        },
    },
    /* tAutoParam */
    {
        /* nRefValStart[3] */
        {0, 100, 500, /*0 - 2*/},
        /* nRefValEnd[3] */
        {50, 200, 1000, /*0 - 2*/},
        /* tGammaLut[3] */
        {
            /* 0 */
            {
                /* nLut[129] */
                {
                    0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61,  /* 0 - 31*/
                    63, 67, 71, 75, 79, 83, 87, 91, 95, 99, 103, 107, 111, 115, 119, 123, 127, 135, 143, 151, 159, 167, 175, 183, 191, 199, 207, 215, 223, 231, 239, 247,  /* 32 - 63*/
                    255, 271, 287, 303, 319, 335, 351, 367, 383, 399, 415, 431, 447, 463, 479, 495, 511, 543, 575, 607, 639, 671, 703, 735, 767, 799, 831, 863, 895, 927, 959, 991,  /* 64 - 95*/
                    1023, 1087, 1151, 1215, 1279, 1343, 1407, 1471, 1535, 1599, 1663, 1727, 1791, 1855, 1919, 1983, 2047, 2175, 2303, 2431, 2559, 2687, 2815, 2943, 3071, 3199, 3327, 3455, 3583, 3711, 3839, 3967,  /* 96 - 127*/
                    4095, /*128 - 128*/
                },
            },
            /* 1 */
            {
                /* nLut[129] */
                {
                    0, 8, 17, 26, 35, 44, 53, 62, 71, 80, 89, 98, 107, 116, 125, 134, 143, 152, 161, 170, 179, 188, 197, 206, 215, 224, 233, 242, 251, 260, 269, 278,  /* 0 - 31*/
                    287, 305, 323, 342, 360, 377, 393, 410, 425, 441, 456, 471, 485, 499, 513, 527, 540, 566, 592, 616, 640, 663, 686, 708, 730, 751, 771, 792, 811, 831, 850, 868,  /* 32 - 63*/
                    887, 922, 957, 991, 1023, 1055, 1086, 1116, 1145, 1174, 1202, 1230, 1257, 1283, 1309, 1335, 1360, 1409, 1456, 1502, 1546, 1590, 1632, 1673, 1713, 1753, 1791, 1829, 1865, 1902, 1937, 1972,  /* 64 - 95*/
                    2006, 2073, 2137, 2200, 2261, 2320, 2378, 2434, 2489, 2543, 2595, 2647, 2697, 2746, 2795, 2842, 2889, 2980, 3068, 3154, 3237, 3318, 3397, 3474, 3549, 3622, 3694, 3764, 3833, 3900, 3966, 4031,  /* 96 - 127*/
                    4095, /*128 - 128*/
                },
            },
            /* 2 */
            {
                /* nLut[129] */
                {
                    0, 25, 51, 77, 103, 129, 155, 180, 203, 224, 245, 264, 282, 299, 316, 331, 346, 361, 375, 389, 402, 415, 428, 440, 452, 463, 475, 486, 497, 507, 518, 528,  /* 0 - 31*/
                    538, 558, 577, 595, 613, 630, 646, 663, 679, 694, 709, 724, 739, 753, 767, 780, 794, 820, 845, 870, 893, 916, 939, 960, 982, 1002, 1022, 1042, 1062, 1081, 1099, 1117,  /* 32 - 63*/
                    1135, 1170, 1204, 1236, 1268, 1299, 1328, 1357, 1386, 1413, 1440, 1467, 1493, 1518, 1543, 1567, 1591, 1637, 1682, 1726, 1768, 1809, 1849, 1888, 1925, 1962, 1998, 2034, 2068, 2102, 2135, 2167,  /* 64 - 95*/
                    2199, 2261, 2321, 2379, 2436, 2490, 2543, 2595, 2646, 2695, 2743, 2790, 2836, 2881, 2925, 2969, 3011, 3094, 3174, 3252, 3327, 3400, 3471, 3540, 3607, 3673, 3737, 3800, 3861, 3922, 3981, 4038,  /* 96 - 127*/
                    4095, /*128 - 128*/
                },
            },
        },
    },
};

const static AX_ISP_IQ_DEHAZE_PARAM_T dehaze_param_sdr = {
    /* nDehazeEn */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tGlbParam */
    {
        /* nCalcMode */
        1,
        /* nAirReflect */
        52224,
        /* nSpatialSmoothness */
        2,
        /* nStrengthLimit */
        37,
        /* nMeshSize */
        32,
        /* nEps */
        8192,
        /* nBlurEnable */
        1,
        /* nSigmaBlur */
        4096,
    },
    /* tManualParam */
    {
        /* nEffectStrength */
        48,
        /* nGrayDcRatio */
        64,
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nEffectStrength[12] */
        {48, 48, 48, 48, 48, 48, 48, 48, 48, 56, 64, 64, /*0 - 11*/},
        /* nGrayDcRatio[12] */
        {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, /*0 - 11*/},
    },
};

const static AX_ISP_IQ_CSC_PARAM_T csc_param_sdr = {
    /* nMatrix[3][3] */
    {
        {77, 150, 29, /*0 - 2*/},
        {-43, -85, 128, /*0 - 2*/},
        {128, -107, -21, /*0 - 2*/},
    },
    /* eColorSpaceMode */
    /* 0:AX_ISP_CSC_USER, 1:AX_ISP_CSC_BT601, 2:AX_ISP_CSC_BT709, 3:AX_ISP_CSC_BT2020, 4:AX_ISP_CSC_BUTT */
    AX_ISP_CSC_BT601,
    /* eUvSeqSel */
    /* 0:AX_ISP_NV12_SEL, 1:AX_ISP_NV21_SEL */
    AX_ISP_NV12_SEL,
};

const static AX_ISP_IQ_CA_PARAM_T ca_param_sdr = {
    /* nCppEn */
    0,
    /* nAutoMode */
    0,
    /* nRefMode */
    0,
    /* tManualParam */
    {
        /* nCtrlLevel */
        0,
        /* nSat */
        0,
        /* nHue */
        0,
        /* nCmtx[2][2] */
        {
            {256, 0, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
        },
    },
    /* tAutoParam */
    {
        /* nParamGrpNumCt */
        12,
        /* nParamGrpNumLG */
        1,
        /* nRefValCt[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nRefValLG[12][5] */
        {
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
            {1024, /*0 - 0*/},
        },
        /* nCmtx[12][5][4] */
        {
            /* nCmtx 0 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 1 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 2 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 3 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 4 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 5 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 6 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 7 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 8 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 9 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 10 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
            /* nCmtx 11 */
            {
                {0, 0, 0, 0, /*0 - 3*/},
            },
        },
    },
};

const static AX_ISP_IQ_YNR_PARAM_T ynr_param_sdr = {
    /* nYnrEn */
    1,
    /* nColorTargetEn */
    0,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* nIoFlag */
    0,
    /* tManualParam */
    {
        /* nYnrCenter[3] */
        {0, 0, 0, /*0 - 2*/},
        /* nYnrRadius[3] */
        {0, 0, 0, /*0 - 2*/},
        /* nYnrSmooth[3] */
        {0, 0, 0, /*0 - 2*/},
        /* nYnrLevel[2] */
        {255, 0, /*0 - 1*/},
        /* nYnrInvNrLut[4] */
        {192, 240, 256, 256, /*0 - 3*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nYnrCenter[12][3] */
        {
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nYnrRadius[12][3] */
        {
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nYnrSmooth[12][3] */
        {
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nYnrLevel[12][2] */
        {
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
            {255, 0, /*0 - 1*/},
        },
        /* nYnrInvNrLut[12][4] */
        {
            {256, 360, 384, 384, /*0 - 3*/},
            {224, 300, 320, 320, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {144, 180, 192, 192, /*0 - 3*/},
            {120, 150, 160, 160, /*0 - 3*/},
        },
    },
};

const static AX_ISP_IQ_CNR_PARAM_T cnr_param_sdr = {
    /* nCnrEn */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tManualParam */
    {
        /* nCnrLevel */
        16,
        /* nCnrInvNrLut[4] */
        {128, 128, 128, 128, /*0 - 3*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nCnrLevel[12] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 11*/},
        /* nCnrInvNrLut[12][4] */
        {
            {256, 360, 384, 384, /*0 - 3*/},
            {224, 300, 320, 320, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {144, 180, 192, 192, /*0 - 3*/},
            {120, 150, 160, 160, /*0 - 3*/},
            {96, 120, 128, 128, /*0 - 3*/},
            {96, 120, 128, 128, /*0 - 3*/},
            {96, 120, 128, 128, /*0 - 3*/},
            {80, 120, 128, 128, /*0 - 3*/},
            {64, 120, 128, 128, /*0 - 3*/},
            {64, 120, 128, 128, /*0 - 3*/},
            {64, 120, 128, 128, /*0 - 3*/},
        },
    },
};

const static AX_ISP_IQ_YUV3DNR_PARAM_T yuv3dnr_param_sdr = {
    /* nYuv3dnrEnable */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* nConvergeSpeed */
    160,
    /* tExtMaskParam */
    {
        /* nExtMaskEnable */
        1,
        /* nExtMaskMode */
        0,
    },
    /* tSubModuleEnParam */
    {
        /* nMotionDetEnable */
        1,
        /* nTfEnable */
        1,
        /* nSf0YnrEnable */
        1,
        /* nSf1YnrEnable */
        1,
        /* nSf2YnrEnable */
        1,
        /* nSf0CnrEnable */
        1,
        /* nSf1CnrEnable */
        1,
    },
    /* tManualParam */
    {
        /* nMotDetNoiseLut[2][17] */
        {
            {8, 12, 16, 20, 20, 20, 20, 20, 16, 16, 16, 12, 8, 8, 8, 8, 4, /*0 - 16*/},
            {8, 12, 16, 20, 20, 20, 20, 20, 16, 16, 16, 12, 8, 8, 8, 8, 4, /*0 - 16*/},
        },
        /* nMotDetStrenLuma[2] */
        {128, 0, /*0 - 1*/},
        /* nMotDetStrenChrom[2] */
        {128, 0, /*0 - 1*/},
        /* nMotDetSmoothLuma[2] */
        {2, 1, /*0 - 1*/},
        /* nMotDetSmoothChroma[2] */
        {2, 1, /*0 - 1*/},
        /* nMotDetLimitLuma[2] */
        {0, 256, /*0 - 1*/},
        /* nMotDetLimitChrom[2] */
        {0, 256, /*0 - 1*/},
        /* nMotDetBlendRatio[2] */
        {256, 256, /*0 - 1*/},
        /* nStasUpdateLut[2][16] */
        {
            {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, /*0 - 15*/},
            {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
        },
        /* nTfRatioLut[16] */
        {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
        /* nTfRatLimitLuma[2][2] */
        {
            {64, 255, /*0 - 1*/},
            {16, 255, /*0 - 1*/},
        },
        /* nTfRatLimitChroma[2][2] */
        {
            {64, 255, /*0 - 1*/},
            {16, 255, /*0 - 1*/},
        },
        /* nSf0EdgeStre */
        192,
        /* nSf0DirStre */
        128,
        /* nSf0DetailStre */
        128,
        /* nSf0LumaNoiseLut[4][9] */
        {
            {48, 32, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
            {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            {24, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 8*/},
        },
        /* nSf0LumaKernelSize[2] */
        {1, 0, /*0 - 1*/},
        /* nSf0LumaGauStre[2] */
        {32, 128, /*0 - 1*/},
        /* nSf0lumaBlendRatio[2][3] */
        {
            {80, 48, 128, /*0 - 2*/},
            {64, 0, 192, /*0 - 2*/},
        },
        /* nSf0ChromaAttenStre[2] */
        {1000, 1023, /*0 - 1*/},
        /* nSf0ChromaAttenLimit[2] */
        {240, 250, /*0 - 1*/},
        /* nSf0ChromaProtLut[2][9] */
        {
            {180, 160, 140, 120, 100, 70, 50, 30, 20, /*0 - 8*/},
            {32, 16, 8, 8, 8, 8, 8, 8, 8, /*0 - 8*/},
        },
        /* nSf1LumaMedEn */
        0,
        /* nSf1LumaGauStre[2] */
        {32, 0, /*0 - 1*/},
        /* nSf1LumaGauRatio[2] */
        {32, 32, /*0 - 1*/},
        /* nSf1LumaKernelSize */
        1,
        /* nSf1LumaNoiseLut[2][9] */
        {
            {48, 40, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
            {32, 28, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
        },
        /* nSf1LumaIdrThre[2] */
        {128, 128, /*0 - 1*/},
        /* nSf1LumaIdrGain[2] */
        {128, 128, /*0 - 1*/},
        /* nSf1LumaClipLevel[2] */
        {0, 1023, /*0 - 1*/},
        /* nSf1LumaCoring[2] */
        {0, 0, /*0 - 1*/},
        /* nSf1LumaBlendRatio[2] */
        {24, 256, /*0 - 1*/},
        /* nSf1ChromaCoring */
        256,
        /* nSf1ChromaBlendRatio */
        128,
        /* nSf2LumaGauStre[2] */
        {32, 64, /*0 - 1*/},
        /* nSf2LumaMedEn */
        0,
        /* nSf2KernelSize */
        0,
        /* nSf2NoiseLut[2][9] */
        {
            {48, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            {24, 12, 12, 12, 12, 12, 12, 12, 12, /*0 - 8*/},
        },
        /* nSf2BlendRatio[2][3] */
        {
            {128, 64, 64, /*0 - 2*/},
            {64, 0, 192, /*0 - 2*/},
        },
        /* nExtMaskStrenLuma */
        0,
        /* nExtMaskStrenChrom */
        0,
        /* nExtMaskStrenStatus */
        0,
        /* nExtMaskRatioLuma[2] */
        {0, 0, /*0 - 1*/},
        /* nExtMaskRatioChrom[2] */
        {0, 0, /*0 - 1*/},
        /* nExtMaskRatioStatus[2] */
        {0, 0, /*0 - 1*/},
        /* nY3dnrPos */
        0,
        /* nStaRefineErode */
        0,
        /* nSfGuideMapLuma[2] */
        {0, 0, /*0 - 1*/},
        /* nSfGuideMapChroma[2] */
        {0, 0, /*0 - 1*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nMotDetNoiseLut[12][2][17] */
        {
            /* nMotDetNoiseLut 0 */
            {
                {16, 20, 24, 24, 24, 24, 24, 24, 24, 20, 16, 16, 12, 12, 8, 8, 4, /*0 - 16*/},
                {16, 20, 24, 24, 24, 24, 24, 24, 24, 20, 16, 16, 12, 12, 8, 8, 4, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 1 */
            {
                {16, 24, 28, 28, 28, 28, 28, 28, 28, 24, 20, 16, 16, 16, 16, 16, 8, /*0 - 16*/},
                {16, 24, 28, 28, 28, 28, 28, 28, 28, 24, 20, 16, 16, 16, 16, 16, 8, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 2 */
            {
                {20, 24, 32, 32, 32, 32, 32, 32, 32, 32, 28, 24, 24, 20, 16, 16, 16, /*0 - 16*/},
                {20, 24, 32, 32, 32, 32, 32, 32, 32, 32, 28, 24, 24, 20, 16, 16, 16, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 3 */
            {
                {24, 32, 40, 48, 48, 48, 48, 48, 48, 48, 48, 40, 40, 32, 32, 24, 16, /*0 - 16*/},
                {24, 32, 40, 48, 48, 48, 48, 48, 48, 48, 48, 40, 40, 32, 32, 24, 16, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 4 */
            {
                {40, 54, 60, 72, 72, 72, 72, 72, 72, 72, 72, 72, 64, 56, 48, 32, 24, /*0 - 16*/},
                {40, 54, 60, 72, 72, 72, 72, 72, 72, 72, 72, 72, 64, 56, 48, 32, 24, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 5 */
            {
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 6 */
            {
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 7 */
            {
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 8 */
            {
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 9 */
            {
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 10 */
            {
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 11 */
            {
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
                {48, 64, 80, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 72, 64, 64, 48, /*0 - 16*/},
            },
        },
        /* nMotDetStrenLuma[12][2] */
        {
            {128, 0, /*0 - 1*/},
            {128, 0, /*0 - 1*/},
            {128, 0, /*0 - 1*/},
            {128, -4, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
        },
        /* nMotDetStrenChrom[12][2] */
        {
            {96, 0, /*0 - 1*/},
            {96, 0, /*0 - 1*/},
            {96, 0, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
        },
        /* nMotDetSmoothLuma[12][2] */
        {
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
        },
        /* nMotDetSmoothChroma[12][2] */
        {
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
        },
        /* nMotDetLimitLuma[12][2] */
        {
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
        },
        /* nMotDetLimitChrom[12][2] */
        {
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
            {0, 256, /*0 - 1*/},
        },
        /* nMotDetBlendRatio[12][2] */
        {
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
        },
        /* nStasUpdateLut[12][2][16] */
        {
            /* nStasUpdateLut 0 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 1 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 2 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 3 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 4 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 5 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 6 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 7 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 8 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 9 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 10 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
            /* nStasUpdateLut 11 */
            {
                {4, 4, 4, 4, 3, 3, 3, 2, 2, 2, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
                {15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, /*0 - 15*/},
            },
        },
        /* nTfRatioLut[12][16] */
        {
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 16, /*0 - 15*/},
        },
        /* nTfRatLimitLuma[12][2][2] */
        {
            /* nTfRatLimitLuma 0 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 1 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 2 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 3 */
            {
                {48, 255, /*0 - 1*/},
                {8, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 4 */
            {
                {32, 255, /*0 - 1*/},
                {0, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 5 */
            {
                {32, 255, /*0 - 1*/},
                {0, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 6 */
            {
                {32, 255, /*0 - 1*/},
                {0, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 7 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 8 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 9 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 10 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 11 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
        },
        /* nTfRatLimitChroma[12][2][2] */
        {
            /* nTfRatLimitChroma 0 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 1 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 2 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 3 */
            {
                {64, 255, /*0 - 1*/},
                {8, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 4 */
            {
                {64, 255, /*0 - 1*/},
                {0, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 5 */
            {
                {64, 255, /*0 - 1*/},
                {0, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 6 */
            {
                {64, 255, /*0 - 1*/},
                {0, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 7 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 8 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 9 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 10 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 11 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
        },
        /* nSf0EdgeStre[12] */
        {192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, /*0 - 11*/},
        /* nSf0DirStre[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nSf0DetailStre[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nSf0LumaNoiseLut[12][4][9] */
        {
            /* nSf0LumaNoiseLut 0 */
            {
                {48, 32, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {24, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 1 */
            {
                {48, 32, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {24, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 2 */
            {
                {48, 32, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {32, 24, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {24, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 3 */
            {
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {48, 40, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 4 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 5 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 6 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 7 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 8 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 9 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 10 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 11 */
            {
                {160, 128, 96, 80, 80, 80, 80, 80, 80, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
            },
        },
        /* nSf0LumaKernelSize[12][2] */
        {
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 1, /*0 - 1*/},
            {2, 2, /*0 - 1*/},
            {2, 2, /*0 - 1*/},
            {2, 2, /*0 - 1*/},
            {2, 2, /*0 - 1*/},
            {2, 2, /*0 - 1*/},
        },
        /* nSf0LumaGauStre[12][2] */
        {
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
            {32, 128, /*0 - 1*/},
        },
        /* nSf0lumaBlendRatio[12][2][3] */
        {
            /* nSf0lumaBlendRatio 0 */
            {
                {112, 16, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 1 */
            {
                {112, 16, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 2 */
            {
                {96, 32, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 3 */
            {
                {112, 32, 112, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 4 */
            {
                {160, 32, 64, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 5 */
            {
                {160, 32, 64, /*0 - 2*/},
                {96, 32, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 6 */
            {
                {128, 32, 96, /*0 - 2*/},
                {80, 16, 160, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 7 */
            {
                {96, 32, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 8 */
            {
                {96, 32, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 9 */
            {
                {96, 32, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 10 */
            {
                {96, 32, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 11 */
            {
                {96, 32, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
        },
        /* nSf0ChromaAttenStre[12][2] */
        {
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
        },
        /* nSf0ChromaAttenLimit[12][2] */
        {
            {230, 255, /*0 - 1*/},
            {230, 255, /*0 - 1*/},
            {230, 255, /*0 - 1*/},
            {220, 250, /*0 - 1*/},
            {210, 240, /*0 - 1*/},
            {210, 230, /*0 - 1*/},
            {210, 230, /*0 - 1*/},
            {210, 240, /*0 - 1*/},
            {210, 240, /*0 - 1*/},
            {200, 240, /*0 - 1*/},
            {180, 230, /*0 - 1*/},
            {180, 230, /*0 - 1*/},
        },
        /* nSf0ChromaProtLut[12][2][9] */
        {
            /* nSf0ChromaProtLut 0 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {48, 40, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 1 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {48, 40, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 2 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {64, 56, 48, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 3 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {72, 64, 56, 48, 48, 48, 48, 48, 48, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 4 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 5 */
            {
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 6 */
            {
                {160, 120, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 7 */
            {
                {192, 160, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 8 */
            {
                {192, 160, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 9 */
            {
                {192, 160, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 10 */
            {
                {192, 160, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 11 */
            {
                {192, 160, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {128, 96, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
        },
        /* nSf1LumaMedEn[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nSf1LumaGauStre[12][2] */
        {
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
            {32, 0, /*0 - 1*/},
        },
        /* nSf1LumaGauRatio[12][2] */
        {
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
        },
        /* nSf1LumaKernelSize[12] */
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, /*0 - 11*/},
        /* nSf1LumaNoiseLut[12][2][9] */
        {
            /* nSf1LumaNoiseLut 0 */
            {
                {48, 40, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {32, 28, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 1 */
            {
                {48, 40, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {32, 28, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 2 */
            {
                {64, 56, 48, 48, 48, 48, 48, 44, 40, /*0 - 8*/},
                {48, 40, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 3 */
            {
                {64, 56, 48, 48, 48, 48, 48, 44, 40, /*0 - 8*/},
                {48, 40, 32, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 4 */
            {
                {96, 80, 72, 64, 56, 56, 56, 48, 48, /*0 - 8*/},
                {64, 56, 48, 48, 48, 48, 48, 44, 40, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 5 */
            {
                {128, 112, 96, 80, 80, 80, 72, 64, 64, /*0 - 8*/},
                {96, 80, 72, 64, 56, 56, 56, 48, 48, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 6 */
            {
                {128, 112, 96, 80, 80, 80, 72, 64, 64, /*0 - 8*/},
                {96, 80, 72, 64, 56, 56, 56, 48, 48, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 7 */
            {
                {128, 112, 96, 80, 80, 80, 72, 64, 64, /*0 - 8*/},
                {96, 80, 72, 64, 56, 56, 56, 48, 48, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 8 */
            {
                {128, 112, 96, 80, 80, 80, 72, 64, 64, /*0 - 8*/},
                {96, 80, 72, 64, 56, 56, 56, 48, 48, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 9 */
            {
                {192, 144, 128, 96, 96, 88, 80, 72, 64, /*0 - 8*/},
                {128, 112, 96, 80, 80, 80, 72, 64, 64, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 10 */
            {
                {192, 144, 128, 96, 96, 88, 80, 72, 64, /*0 - 8*/},
                {128, 112, 96, 80, 80, 80, 72, 64, 64, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 11 */
            {
                {192, 144, 128, 96, 96, 88, 80, 72, 64, /*0 - 8*/},
                {128, 112, 96, 80, 80, 80, 72, 64, 64, /*0 - 8*/},
            },
        },
        /* nSf1LumaIdrThre[12][2] */
        {
            {32, 64, /*0 - 1*/},
            {32, 64, /*0 - 1*/},
            {32, 64, /*0 - 1*/},
            {48, 96, /*0 - 1*/},
            {64, 128, /*0 - 1*/},
            {96, 192, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
        },
        /* nSf1LumaIdrGain[12][2] */
        {
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
        },
        /* nSf1LumaClipLevel[12][2] */
        {
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
        },
        /* nSf1LumaCoring[12][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {64, 32, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
        },
        /* nSf1LumaBlendRatio[12][2] */
        {
            {24, 256, /*0 - 1*/},
            {24, 256, /*0 - 1*/},
            {24, 224, /*0 - 1*/},
            {24, 192, /*0 - 1*/},
            {20, 160, /*0 - 1*/},
            {16, 128, /*0 - 1*/},
            {16, 128, /*0 - 1*/},
            {28, 224, /*0 - 1*/},
            {32, 224, /*0 - 1*/},
            {32, 224, /*0 - 1*/},
            {32, 224, /*0 - 1*/},
            {32, 224, /*0 - 1*/},
        },
        /* nSf1ChromaCoring[12] */
        {128, 160, 192, 256, 384, 512, 512, 256, 256, 256, 256, 256, /*0 - 11*/},
        /* nSf1ChromaBlendRatio[12] */
        {128, 128, 128, 64, 32, 24, 24, 96, 128, 128, 128, 128, /*0 - 11*/},
        /* nSf2LumaGauStre[12][2] */
        {
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
        },
        /* nSf2LumaMedEn[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nSf2KernelSize[12] */
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*0 - 11*/},
        /* nSf2NoiseLut[12][2][9] */
        {
            /* nSf2NoiseLut 0 */
            {
                {32, 24, 20, 20, 20, 20, 20, 20, 20, /*0 - 8*/},
                {24, 18, 12, 12, 12, 12, 12, 12, 12, /*0 - 8*/},
            },
            /* nSf2NoiseLut 1 */
            {
                {32, 24, 20, 20, 20, 20, 20, 20, 20, /*0 - 8*/},
                {24, 18, 12, 12, 12, 12, 12, 12, 12, /*0 - 8*/},
            },
            /* nSf2NoiseLut 2 */
            {
                {32, 24, 20, 20, 20, 20, 20, 20, 20, /*0 - 8*/},
                {24, 18, 12, 12, 12, 12, 12, 12, 12, /*0 - 8*/},
            },
            /* nSf2NoiseLut 3 */
            {
                {48, 32, 24, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {32, 24, 16, 16, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf2NoiseLut 4 */
            {
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {96, 64, 48, 48, 48, 48, 48, 48, 48, /*0 - 8*/},
            },
            /* nSf2NoiseLut 5 */
            {
                {192, 144, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 6 */
            {
                {192, 144, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 7 */
            {
                {192, 144, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 8 */
            {
                {192, 144, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 9 */
            {
                {192, 144, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 10 */
            {
                {192, 144, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 11 */
            {
                {192, 144, 96, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
        },
        /* nSf2BlendRatio[12][2][3] */
        {
            /* nSf2BlendRatio 0 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 1 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 2 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 3 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 4 */
            {
                {128, 32, 96, /*0 - 2*/},
                {96, 16, 144, /*0 - 2*/},
            },
            /* nSf2BlendRatio 5 */
            {
                {144, 32, 80, /*0 - 2*/},
                {96, 32, 128, /*0 - 2*/},
            },
            /* nSf2BlendRatio 6 */
            {
                {144, 32, 80, /*0 - 2*/},
                {96, 32, 128, /*0 - 2*/},
            },
            /* nSf2BlendRatio 7 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 8 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 9 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 10 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf2BlendRatio 11 */
            {
                {96, 32, 128, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
        },
        /* nExtMaskStrenLuma[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nExtMaskStrenChrom[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nExtMaskStrenStatus[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nExtMaskRatioLuma[12][2] */
        {
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
        },
        /* nExtMaskRatioChrom[12][2] */
        {
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
        },
        /* nExtMaskRatioStatus[12][2] */
        {
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
        },
        /* nY3dnrPos[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nStaRefineErode[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nSfGuideMapLuma[12][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
        },
        /* nSfGuideMapChroma[12][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
        },
    },
};

const static AX_ISP_IQ_SHARPEN_PARAM_T sharpen_param_sdr = {
    /* nShpEn */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tMaskControl */
    {
        /* nMotionMaskEn */
        1,
        /* nShpClnpNpuMaskEn */
        1,
        /* nShpLumaMaskLut[17] */
        {0, 0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 255, 255, 255, /*0 - 16*/},
    },
    /* tFineGrainNoise */
    {
        /* nGrainNoiseEn */
        0,
        /* nGnMotionMskEn */
        0,
        /* nGnMotionLut[5] */
        {0, 0, 0, 0, 0, /*0 - 4*/},
        /* nGnLumaMskEn */
        0,
        /* nGnLumaLut[5] */
        {0, 0, 0, 0, 0, /*0 - 4*/},
        /* nGnTextureMskEn */
        0,
        /* nGnTextureLut[9] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
        /* nGnClnpMskEn[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nGnClnpLut[4][5] */
        {
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
    },
    /* tOsStaticMotion */
    {
        /* nOsStaticLimit[2] */
        {127, 96, /*0 - 1*/},
        /* nOsStaticGain[2] */
        {8, 6, /*0 - 1*/},
        /* nOsMotionLimit[2] */
        {64, 48, /*0 - 1*/},
        /* nOsMotionGain[2] */
        {4, 3, /*0 - 1*/},
    },
    /* tCommonLutCore */
    {
        /* nCommonLutEnable */
        0,
        /* nCommonMotionLut[5] */
        {0, 0, 0, 0, 0, /*0 - 4*/},
        /* nCommonLumaLut[5] */
        {0, 0, 0, 0, 0, /*0 - 4*/},
        /* nCommonTextureStaticLut[9] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
        /* nCommonTexturemotionLut[9] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
        /* nCommonClnpLut[4][5] */
        {
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
    },
    /* tColorTarget */
    {
        /* nColorEnable[8] */
        {1, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
        /* nColorCenter[8][3] */
        {
            {440, -95, -75, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nColorRange[8][3] */
        {
            {128, 72, 64, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nColorSmooth[8][3] */
        {
            {7, 2, 2, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nColorIoFlag[8] */
        {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
        /* nColorMaskIndex[8] */
        {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
        /* nColorMaskLimit[8] */
        {128, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
    },
    /* tHighFreqControl */
    {
        /* nHighFreqEnable */
        1,
        /* nHighFreqMotionMskEn */
        1,
        /* nHighFreqMotionLutLevel */
        0,
        /* nHighFreqLumaMskEn */
        1,
        /* nHighFreqLumaLutLevel */
        0,
        /* nHighFreqTextureMskEn */
        1,
        /* nHighFreqTextureLutLevel */
        0,
        /* nHighFreqTextureLutMotionLevel */
        0,
        /* nHighFreqClnpMskEn[4] */
        {1, 0, 0, 0, /*0 - 3*/},
        /* nHighFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nHighFreqMotionLut[5] */
        {64, 32, 16, 0, -8, /*0 - 4*/},
        /* nHighFreqLumaLut[5] */
        {-48, 64, 64, 16, -32, /*0 - 4*/},
        /* nHighFreqTextureLut[9] */
        {0, 32, 64, 96, 127, 127, 127, 127, 127, /*0 - 8*/},
        /* nHighFreqTextureLutMotion[9] */
        {0, 32, 64, 96, 96, 96, 96, 96, 80, /*0 - 8*/},
        /* nHighFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
        /* nHighFreqOsLimit[2] */
        {64, 48, /*0 - 1*/},
        /* nHighFreqOsGain[2] */
        {4, 4, /*0 - 1*/},
    },
    /* tMedFreqControl */
    {
        /* nMedFreqEnable */
        1,
        /* nMedFreqMotionMskEn */
        1,
        /* nMedFreqMotionLutLevel */
        0,
        /* nMedFreqLumaMskEn */
        1,
        /* nMedFreqLumaLutLevel */
        0,
        /* nMedFreqTextureMskEn */
        1,
        /* nMedFreqTextureLutLevel */
        0,
        /* nMedFreqTextureLutMotionLevel */
        0,
        /* nMedFreqClnpMskEn[4] */
        {1, 0, 0, 0, /*0 - 3*/},
        /* nMedFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nMedFreqMotionLut[5] */
        {64, 32, 8, -8, -16, /*0 - 4*/},
        /* nMedFreqLumaLut[5] */
        {-64, 64, 64, 0, -64, /*0 - 4*/},
        /* nMedFreqTextureLut[9] */
        {0, 32, 64, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
        /* nMedFreqTextureLutMotion[9] */
        {-32, -16, -8, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
        /* nMedFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
        /* nMedFreqOsLimit[2] */
        {48, 32, /*0 - 1*/},
        /* nMedFreqOsGain[2] */
        {4, 4, /*0 - 1*/},
    },
    /* tDirFreqControl */
    {
        /* nDirFreqEnable */
        1,
        /* nDirFreqMotionMskEn */
        1,
        /* nDirFreqMotionLutLevel */
        0,
        /* nDirFreqLumaMskEn */
        1,
        /* nDirFreqLumaLutLevel */
        0,
        /* nDirFreqTextureMskEn */
        1,
        /* nDirFreqTextureLutLevel */
        0,
        /* nDirFreqTextureLutMotionLevel */
        0,
        /* nDirFreqClnpMskEn[4] */
        {1, 0, 0, 0, /*0 - 3*/},
        /* nDirFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nDirFreqMotionLut[5] */
        {96, 64, 32, 16, 0, /*0 - 4*/},
        /* nDirFreqLumaLut[5] */
        {-48, 96, 96, 32, -32, /*0 - 4*/},
        /* nDirFreqTextureLut[9] */
        {32, 64, 96, 127, 127, 127, 127, 127, 127, /*0 - 8*/},
        /* nDirFreqTextureLutMotion[9] */
        {0, 32, 64, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
        /* nDirFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
        /* nDirFreqOsLimit[2] */
        {127, 96, /*0 - 1*/},
        /* nDirFreqOsGain[2] */
        {6, 4, /*0 - 1*/},
        /* nDirFreqDirEdgeLevelLut[9] */
        {64, 64, 108, 152, 192, 192, 192, 224, 255, /*0 - 8*/},
    },
    /* tLowFreqControl */
    {
        /* nLowFreqEnable */
        1,
        /* nLowFreqMotionMskEn */
        1,
        /* nLowFreqMotionLutLevel */
        0,
        /* nLowFreqLumaMskEn */
        1,
        /* nLowFreqLumaLutLevel */
        0,
        /* nLowFreqTextureMskEn */
        1,
        /* nLowFreqTextureLutLevel */
        0,
        /* nLowFreqTextureLutMotionLevel */
        0,
        /* nLowFreqClnpMskEn[4] */
        {1, 0, 0, 0, /*0 - 3*/},
        /* nLowFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nLowFreqMotionLut[5] */
        {64, 32, 8, -16, -32, /*0 - 4*/},
        /* nLowFreqLumaLut[5] */
        {-64, 64, 64, 0, -64, /*0 - 4*/},
        /* nLowFreqTextureLut[9] */
        {-32, -16, 0, 16, 32, 48, 64, 64, 64, /*0 - 8*/},
        /* nLowFreqTextureLutMotion[9] */
        {-32, -16, -8, 0, 0, 0, 0, 0, 0, /*0 - 8*/},
        /* nLowFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
        /* nLowFreqOsLimit[2] */
        {16, 16, /*0 - 1*/},
        /* nLowFreqOsGain[2] */
        {4, 3, /*0 - 1*/},
    },
    /* tManualParam */
    {
        /* nHighFreqLogGain[2] */
        {64, 48, /*0 - 1*/},
        /* nHighFreqGainLimit[2] */
        {0, 64, /*0 - 1*/},
        /* nHighFreqCorBaseGain */
        2,
        /* nHighFreqCorSlope */
        8,
        /* nHighFreqCorOffset */
        4,
        /* nHighFreqLimit[2] */
        {512, 512, /*0 - 1*/},
        /* nMedFreqLogGain[2] */
        {48, 32, /*0 - 1*/},
        /* nMedFreqGainLimit[2] */
        {0, 64, /*0 - 1*/},
        /* nMedFreqCorBaseGain */
        1,
        /* nMedFreqCorSlope */
        12,
        /* nMedFreqCorOffset */
        12,
        /* nMedFreqLimit[2] */
        {256, 256, /*0 - 1*/},
        /* nDirFreqLogGain[2] */
        {96, 64, /*0 - 1*/},
        /* nDirFreqGainLimit[2] */
        {0, 96, /*0 - 1*/},
        /* nDirFreqCorBaseGain */
        8,
        /* nDirFreqCorSlope */
        8,
        /* nDirFreqCorOffset */
        0,
        /* nDirFreqLimit[2] */
        {1023, 1023, /*0 - 1*/},
        /* nLowFreqLogGain[2] */
        {32, 32, /*0 - 1*/},
        /* nLowFreqGainLimit[2] */
        {0, 48, /*0 - 1*/},
        /* nLowFreqCorBaseGain */
        0,
        /* nLowFreqCorSlope */
        12,
        /* nLowFreqCorOffset */
        16,
        /* nLowFreqLimit[2] */
        {128, 128, /*0 - 1*/},
        /* nShpHpfBsigma[3] */
        {12, 14, 16, /*0 - 2*/},
        /* nShpHpfDsigma[3] */
        {24, 32, 40, /*0 - 2*/},
        /* nShpHpfScale[3] */
        {128, 128, 128, /*0 - 2*/},
        /* nShpGain[2] */
        {20, 16, /*0 - 1*/},
        /* nShpLimit[2] */
        {-4096, 4095, /*0 - 1*/},
        /* nGrainLogGain */
        0,
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nHighFreqLogGain[12][2] */
        {
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
            {64, 48, /*0 - 1*/},
        },
        /* nHighFreqGainLimit[12][2] */
        {
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
        },
        /* nHighFreqCorBaseGain[12] */
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /*0 - 11*/},
        /* nHighFreqCorSlope[12] */
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nHighFreqCorOffset[12] */
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, /*0 - 11*/},
        /* nHighFreqLimit[12][2] */
        {
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
            {512, 512, /*0 - 1*/},
        },
        /* nMedFreqLogGain[12][2] */
        {
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
            {48, 32, /*0 - 1*/},
        },
        /* nMedFreqGainLimit[12][2] */
        {
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
            {0, 64, /*0 - 1*/},
        },
        /* nMedFreqCorBaseGain[12] */
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*0 - 11*/},
        /* nMedFreqCorSlope[12] */
        {12, 12, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nMedFreqCorOffset[12] */
        {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, /*0 - 11*/},
        /* nMedFreqLimit[12][2] */
        {
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
            {256, 256, /*0 - 1*/},
        },
        /* nDirFreqLogGain[12][2] */
        {
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
            {96, 64, /*0 - 1*/},
        },
        /* nDirFreqGainLimit[12][2] */
        {
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
            {0, 96, /*0 - 1*/},
        },
        /* nDirFreqCorBaseGain[12] */
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nDirFreqCorSlope[12] */
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nDirFreqCorOffset[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nDirFreqLimit[12][2] */
        {
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
            {1023, 1023, /*0 - 1*/},
        },
        /* nLowFreqLogGain[12][2] */
        {
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
            {32, 32, /*0 - 1*/},
        },
        /* nLowFreqGainLimit[12][2] */
        {
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
            {0, 48, /*0 - 1*/},
        },
        /* nLowFreqCorBaseGain[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nLowFreqCorSlope[12] */
        {12, 12, 12, 12, 12, 12, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nLowFreqCorOffset[12] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 11*/},
        /* nLowFreqLimit[12][2] */
        {
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
            {128, 128, /*0 - 1*/},
        },
        /* nShpHpfBsigma[12][3] */
        {
            {12, 14, 16, /*0 - 2*/},
            {12, 14, 16, /*0 - 2*/},
            {12, 14, 18, /*0 - 2*/},
            {12, 16, 20, /*0 - 2*/},
            {12, 16, 20, /*0 - 2*/},
            {12, 16, 20, /*0 - 2*/},
            {12, 16, 20, /*0 - 2*/},
            {12, 16, 20, /*0 - 2*/},
            {12, 16, 22, /*0 - 2*/},
            {12, 16, 24, /*0 - 2*/},
            {12, 16, 24, /*0 - 2*/},
            {12, 16, 24, /*0 - 2*/},
        },
        /* nShpHpfDsigma[12][3] */
        {
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
            {24, 32, 40, /*0 - 2*/},
        },
        /* nShpHpfScale[12][3] */
        {
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
            {128, 128, 128, /*0 - 2*/},
        },
        /* nShpGain[12][2] */
        {
            {20, 16, /*0 - 1*/},
            {22, 16, /*0 - 1*/},
            {24, 16, /*0 - 1*/},
            {24, 16, /*0 - 1*/},
            {32, 20, /*0 - 1*/},
            {40, 24, /*0 - 1*/},
            {40, 24, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {32, 16, /*0 - 1*/},
            {30, 16, /*0 - 1*/},
            {28, 16, /*0 - 1*/},
        },
        /* nShpLimit[12][2] */
        {
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
            {-4096, 4095, /*0 - 1*/},
        },
        /* nGrainLogGain[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
    },
};

const static AX_ISP_IQ_CCMP_PARAM_T ccmp_param_sdr = {
    /* nChromaCompEn */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tManualParam */
    {
        /* nChromaCompY[29] */
        {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
        /* nChromaCompSat[23] */
        {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 24576, 32768, 55296, 131072, 262144, 524288, 1048576, /*0 - 11*/},
        /* nChromaCompY[12][29] */
        {
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {450, 450, 450, 450, 450, 450, 450, 450, 450, 480, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, /*0 - 28*/},
            {450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, /*0 - 28*/},
            {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, /*0 - 28*/},
            {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, /*0 - 28*/},
        },
        /* nChromaCompSat[12][23] */
        {
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 22*/},
            {300, 350, 400, 440, 480, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {200, 250, 320, 380, 440, 480, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {200, 240, 280, 320, 360, 400, 440, 450, 480, 480, 480, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {200, 240, 280, 320, 360, 400, 440, 450, 480, 480, 480, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
        },
    },
};

const static AX_ISP_IQ_SCM_PARAM_T scm_param_sdr = {
    /* nScmEn */
    0,
    /* nAutoMode */
    0,
    /* nRefMode */
    0,
    /* nScmIoFlag */
    0,
    /* tManualParam */
    {
        /* nScmColor[2] */
        {0, 0, /*0 - 1*/},
        /* nScmCenterY */
        0,
        /* nScmCenterUv[2] */
        {0, 0, /*0 - 1*/},
        /* nScmRadius[3] */
        {0, 0, 0, /*0 - 2*/},
        /* nScmSmooth[3] */
        {0, 0, 0, /*0 - 2*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        16,
        /* nRefVal[16] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
        /* nScmColor[16][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
        },
        /* nScmCenterY[16] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
        /* nScmCenterUv[16][2] */
        {
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
        },
        /* nScmRadius[16][3] */
        {
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nScmSmooth[16][3] */
        {
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
    },
};

const static AX_ISP_IQ_YCPROC_PARAM_T ycproc_param_sdr = {
    /* nYCprocEn */
    0,
    /* nBrightness */
    256,
    /* nContrast */
    256,
    /* nSaturation */
    4096,
    /* nHue */
    0,
};

const static AX_ISP_IQ_YCRT_PARAM_T ycrt_param_sdr = {
    /* nYcrtEn */
    1,
    /* nSignalRangeMode */
    0,
    /* nYrtInputRange[2] */
    {64, 1023, /*0 - 1*/},
    /* nYrtOutputRange[2] */
    {64, 1023, /*0 - 1*/},
    /* nCrtInputRange[2] */
    {64, 960, /*0 - 1*/},
    /* nCrtOutputRange[2] */
    {64, 960, /*0 - 1*/},
    /* nClipLevelY[2] */
    {0, 1023, /*0 - 1*/},
    /* nClipLevelUV[2] */
    {-512, 511, /*0 - 1*/},
};

const static AX_ISP_IQ_CLP_PARAM_T clp_param_sdr = {
    /* nClpEn */
    0,
    /* nColorPaletteId */
    0,
    /* nColorPaletteYuvLut[3][256] */
    {
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 0 - 31*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 32 - 63*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 64 - 95*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 96 - 127*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 128 - 159*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 160 - 191*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 192 - 223*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 224 - 255*/
        },
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 0 - 31*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 32 - 63*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 64 - 95*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 96 - 127*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 128 - 159*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 160 - 191*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 192 - 223*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 224 - 255*/
        },
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 0 - 31*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 32 - 63*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 64 - 95*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 96 - 127*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 128 - 159*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 160 - 191*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 192 - 223*/
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /* 224 - 255*/
        },
    },
};

const static AX_ISP_IQ_NUC_PARAM_T nuc_param_sdr = {
    /* nNucEnable */
    0,
    /* nModuleMode */
    0,
    /* tManualParam */
    {
        /* tSensorNucCalib */
        {
            /* nNuc1stFrame */
            1,
            /* nStepEnhEn */
            0,
            /* nEffectiveBits */
            7,
            /* nNucAdjustTrend */
            0,
            /* nNucFineBitMask */
            15,
            /* nNucCoarseBitMask */
            240,
            /* nNucInitFine */
            0,
            /* nNucInitCoarse */
            0,
            /* nNucFineStep */
            17,
            /* nNucCoarseStep */
            17,
            /* nNucMaxFVal */
            17,
            /* nNucMaxCVal */
            17,
            /* nNucMinFVal */
            0,
            /* nNucMinCVal */
            0,
            /* nNucAdFineHigh */
            65535,
            /* nNucAdCoarseHigh */
            65535,
            /* nNucAdFineLow */
            65535,
            /* nNucAdCoarseLow */
            65535,
            /* nNucFineCnt */
            1,
            /* nNucCoarseCnt */
            1,
        },
        /* tTwoPointsCalib */
        {
            /* nNucFpnEn */
            0,
            /* nNucBaseGain */
            256,
            /* nNucFpnGain */
            256,
        },
    },
};

const static AX_ISP_IQ_LDC_PARAM_T ldc_param_sdr = {
    /* nLdcEnable */
    0,
    /* nType */
    0,
    /* tLdcV1Param */
    {
        /* bAspect */
        /* 0:AX_FALSE, 1:AX_TRUE */
        AX_FALSE,
        /* nXRatio */
        0,
        /* nYRatio */
        0,
        /* nXYRatio */
        0,
        /* nCenterXOffset */
        0,
        /* nCenterYOffset */
        0,
        /* nDistortionRatio */
        0,
        /* nSpreadCoef */
        0,
    },
    /* tLdcV2Param */
    {
        /* nMatrix[3][3] */
        {
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 1, /*0 - 2*/},
        },
        /* nDistortionCoeff[8] */
        {0, 0, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
    },
};

const static AX_ISP_IQ_DIS_PARAM_T dis_param_sdr = {
    /* bDisEnable */
    0,
    /* nDisType */
    0,
    /* tDisV1Param */
    {
        /* bSWCalcEnable */
        0,
        /* nDelayFrameNum */
        0,
        /* nHistoryFrameNum */
        0,
        /* nCropRatio */
        0,
        /* nFramePosWeights[16] */
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*0 - 15*/},
        /* nSadThreshold */
        0,
    },
};

const static AX_ISP_IQ_ME_PARAM_T me_param_sdr = {
    /* nEnable */
    1,
    /* nLutEnable */
    1,
    /* nLut[33] */
    {
        0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248,  /* 0 - 31*/
        256, /*32 - 32*/
    },
    /* nProjShiftBit[2] */
    {2, 2, /*0 - 1*/},
    /* nScaleRatio */
    0,
    /* tGridRoiH */
    {
        /* nRoiOffsetH */
        16,
        /* nRoiOffsetV */
        0,
        /* nRoiRegionNumH */
        4,
        /* nRoiRegionNumV */
        2,
        /* nRoiRegionSizeH */
        472,
        /* nRoiRegionSizeV */
        540,
        /* nSearchRange */
        32,
    },
    /* tGridRoiV */
    {
        /* nRoiOffsetH */
        0,
        /* nRoiOffsetV */
        16,
        /* nRoiRegionNumH */
        3,
        /* nRoiRegionNumV */
        2,
        /* nRoiRegionSizeH */
        640,
        /* nRoiRegionSizeV */
        524,
        /* nSearchRange */
        32,
    },
};

#endif