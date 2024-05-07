#ifndef __SC200AI_SDR_QS_H__
#define __SC200AI_SDR_QS_H__

/********************************************************************
* Store the default parameters of the sdr mode
* warn: user need to add 'static' when defining global variables.
        Limit the scope of the variable to this sensor
*********************************************************************/

#include "ax_isp_iq_api.h"
#include "ax_isp_api.h"


const static AX_ISP_VERSION_T ax_isp_version_param_sdr_qs = {
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

const static AX_ISP_IQ_SCENE_PARAM_T scene_param_sdr_qs = {
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
        2048,
        /* nRefValStart[4] */
        {1024, 16384, /*0 - 1*/},
        /* nRefValEnd[4] */
        {16384, 884736, /*0 - 1*/},
        /* nAiWorkMode[4] */
        {0, 1, /*0 - 1*/},
    },
};

const static AX_ISP_IQ_AE_PARAM_T ae_param_sdr_qs = {
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
        15360,
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
        104266,
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
        55271,
        /* nMinUserTotalAgain */
        1024,
        /* nMaxUserSysGain */
        884336,
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
                        /* 4 */
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
                        /* 5 */
                        {
                            /* nIntergrationTime */
                            110000,
                            /* nGain */
                            184320,
                            /* nAperture */
                            0,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 6 */
                        {
                            /* nIntergrationTime */
                            166000,
                            /* nGain */
                            884336,
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
                            884336,
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
            {256, 1536, 10240, 81920, 409600, 2048000, /*0 - 5*/},
            /* nSetPointList[10] */
            {18432, 20480, 22528, 26624, 28672, 30720, /*0 - 5*/},
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
                {61, 82, 102, 123, 154, 154, 205, 205, 256, 307, 358, 410, 512, 614, /*0 - 13*/},
                /* nFastOverSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31, 102, 154, 307, /*0 - 13*/},
                /* nFastOverSkipList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 13*/},
                /* nFastUnderKneeCnt */
                11,
                /* nFastUnderLumaDiffList[16] */
                {5120, 10240, 15360, 20480, 25600, 30720, 35840, 40960, 51200, 153600, 262144, /*0 - 10*/},
                /* nFastUnderStepFactorList[16] */
                {51, 72, 92, 102, 123, 154, 154, 154, 184, 205, 256, /*0 - 10*/},
                /* nFastUnderSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 20, 51, 102, /*0 - 10*/},
                /* nFastUnderSkipList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 10*/},
                /* nSlowOverKneeCnt */
                14,
                /* nSlowOverLumaDiffList[16] */
                {5120, 10240, 15360, 20480, 25600, 30720, 40960, 51200, 81920, 92160, 112640, 153600, 209920, 262144, /*0 - 13*/},
                /* nSlowOverStepFactorList[16] */
                {41, 61, 82, 102, 102, 123, 123, 154, 184, 184, 184, 184, 205, 256, /*0 - 13*/},
                /* nSlowOverSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 41, 82, /*0 - 13*/},
                /* nSlowOverSkipList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 13*/},
                /* nSlowUnderKneeCnt */
                11,
                /* nSlowUnderLumaDiffList[16] */
                {5120, 10240, 15360, 20480, 25600, 30720, 35840, 40960, 51200, 153600, 262144, /*0 - 10*/},
                /* nSlowUnderStepFactorList[16] */
                {31, 51, 72, 92, 102, 123, 154, 154, 184, 205, 256, /*0 - 10*/},
                /* nSlowUnderSpeedDownFactorList[16] */
                {0, 0, 0, 0, 0, 0, 0, 0, 10, 31, 51, /*0 - 10*/},
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

const static AX_ISP_IQ_AWB_PARAM_T awb_param_sdr_qs = {
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
            1441807,
            /* nBg */
            1441800,
        },
        /* nCenterPntRadius */
        1255329,
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
            1100, 1250, 1400, 1550, 1700, 1850, 2000, 2150, 2300, 2369, 2438, 2507, 2577, 2646, 2715, 2784, 2854, 2984, 3115, 3246, 3377, 3507, 3638, 3769, 3900, 4037, 4175, 4312, 4450, 4587, 4725, 4862,  /* 0 - 31*/
            5000, 5187, 5375, 5562, 5750, 5937, 6125, 6312, 6500, 6687, 6875, 7062, 7250, 7437, 7625, 7812, 8000, 8500, 9000, 9500, 10000, 10500, 11000, 11500, 12000, /*32 - 56*/
        },
        /* tChordKB */
        {
            /* nK */
            -534,
            /* nB */
            1083,
        },
        /* tChordPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1709483,
                /* nBg */
                215346,
            },
            /* 1 */
            {
                /* nRg */
                1632381,
                /* nBg */
                255664,
            },
            /* 2 */
            {
                /* nRg */
                1561424,
                /* nBg */
                292762,
            },
            /* 3 */
            {
                /* nRg */
                1495511,
                /* nBg */
                327229,
            },
            /* 4 */
            {
                /* nRg */
                1433770,
                /* nBg */
                359515,
            },
            /* 5 */
            {
                /* nRg */
                1375449,
                /* nBg */
                390007,
            },
            /* 6 */
            {
                /* nRg */
                1319947,
                /* nBg */
                419032,
            },
            /* 7 */
            {
                /* nRg */
                1266753,
                /* nBg */
                446851,
            },
            /* 8 */
            {
                /* nRg */
                1215404,
                /* nBg */
                473705,
            },
            /* 9 */
            {
                /* nRg */
                1192199,
                /* nBg */
                485826,
            },
            /* 10 */
            {
                /* nRg */
                1169278,
                /* nBg */
                497822,
            },
            /* 11 */
            {
                /* nRg */
                1146597,
                /* nBg */
                509681,
            },
            /* 12 */
            {
                /* nRg */
                1124115,
                /* nBg */
                521436,
            },
            /* 13 */
            {
                /* nRg */
                1101812,
                /* nBg */
                533096,
            },
            /* 14 */
            {
                /* nRg */
                1079645,
                /* nBg */
                544683,
            },
            /* 15 */
            {
                /* nRg */
                1057594,
                /* nBg */
                556217,
            },
            /* 16 */
            {
                /* nRg */
                1035626,
                /* nBg */
                567710,
            },
            /* 17 */
            {
                /* nRg */
                1011572,
                /* nBg */
                580282,
            },
            /* 18 */
            {
                /* nRg */
                987538,
                /* nBg */
                592854,
            },
            /* 19 */
            {
                /* nRg */
                963495,
                /* nBg */
                605416,
            },
            /* 20 */
            {
                /* nRg */
                939409,
                /* nBg */
                618020,
            },
            /* 21 */
            {
                /* nRg */
                915229,
                /* nBg */
                630666,
            },
            /* 22 */
            {
                /* nRg */
                890912,
                /* nBg */
                643375,
            },
            /* 23 */
            {
                /* nRg */
                866438,
                /* nBg */
                656178,
            },
            /* 24 */
            {
                /* nRg */
                841744,
                /* nBg */
                669086,
            },
            /* 25 */
            {
                /* nRg */
                828711,
                /* nBg */
                675902,
            },
            /* 26 */
            {
                /* nRg */
                815593,
                /* nBg */
                682759,
            },
            /* 27 */
            {
                /* nRg */
                802391,
                /* nBg */
                689669,
            },
            /* 28 */
            {
                /* nRg */
                789106,
                /* nBg */
                696611,
            },
            /* 29 */
            {
                /* nRg */
                775726,
                /* nBg */
                703615,
            },
            /* 30 */
            {
                /* nRg */
                762241,
                /* nBg */
                710662,
            },
            /* 31 */
            {
                /* nRg */
                748641,
                /* nBg */
                717771,
            },
            /* 32 */
            {
                /* nRg */
                734936,
                /* nBg */
                724944,
            },
            /* 33 */
            {
                /* nRg */
                723769,
                /* nBg */
                730774,
            },
            /* 34 */
            {
                /* nRg */
                712518,
                /* nBg */
                736656,
            },
            /* 35 */
            {
                /* nRg */
                701183,
                /* nBg */
                742591,
            },
            /* 36 */
            {
                /* nRg */
                689753,
                /* nBg */
                748568,
            },
            /* 37 */
            {
                /* nRg */
                678219,
                /* nBg */
                754597,
            },
            /* 38 */
            {
                /* nRg */
                666590,
                /* nBg */
                760679,
            },
            /* 39 */
            {
                /* nRg */
                654846,
                /* nBg */
                766813,
            },
            /* 40 */
            {
                /* nRg */
                642997,
                /* nBg */
                773010,
            },
            /* 41 */
            {
                /* nRg */
                632574,
                /* nBg */
                778463,
            },
            /* 42 */
            {
                /* nRg */
                622057,
                /* nBg */
                783957,
            },
            /* 43 */
            {
                /* nRg */
                611446,
                /* nBg */
                789515,
            },
            /* 44 */
            {
                /* nRg */
                600740,
                /* nBg */
                795114,
            },
            /* 45 */
            {
                /* nRg */
                589918,
                /* nBg */
                800766,
            },
            /* 46 */
            {
                /* nRg */
                579003,
                /* nBg */
                806481,
            },
            /* 47 */
            {
                /* nRg */
                567961,
                /* nBg */
                812248,
            },
            /* 48 */
            {
                /* nRg */
                556815,
                /* nBg */
                818078,
            },
            /* 49 */
            {
                /* nRg */
                526490,
                /* nBg */
                833932,
            },
            /* 50 */
            {
                /* nRg */
                495221,
                /* nBg */
                850290,
            },
            /* 51 */
            {
                /* nRg */
                462925,
                /* nBg */
                867172,
            },
            /* 52 */
            {
                /* nRg */
                429486,
                /* nBg */
                884663,
            },
            /* 53 */
            {
                /* nRg */
                394789,
                /* nBg */
                902803,
            },
            /* 54 */
            {
                /* nRg */
                358718,
                /* nBg */
                921667,
            },
            /* 55 */
            {
                /* nRg */
                321126,
                /* nBg */
                941317,
            },
            /* 56 */
            {
                /* nRg */
                281847,
                /* nBg */
                961859,
            },
        },
        /* tArcPointList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1691594,
                /* nBg */
                297303,
            },
            /* 1 */
            {
                /* nRg */
                1628470,
                /* nBg */
                280012,
            },
            /* 2 */
            {
                /* nRg */
                1564182,
                /* nBg */
                266223,
            },
            /* 3 */
            {
                /* nRg */
                1498950,
                /* nBg */
                255999,
            },
            /* 4 */
            {
                /* nRg */
                1432953,
                /* nBg */
                249414,
            },
            /* 5 */
            {
                /* nRg */
                1366399,
                /* nBg */
                246520,
            },
            /* 6 */
            {
                /* nRg */
                1299500,
                /* nBg */
                247349,
            },
            /* 7 */
            {
                /* nRg */
                1232454,
                /* nBg */
                251931,
            },
            /* 8 */
            {
                /* nRg */
                1165492,
                /* nBg */
                260299,
            },
            /* 9 */
            {
                /* nRg */
                1133941,
                /* nBg */
                262700,
            },
            /* 10 */
            {
                /* nRg */
                1102336,
                /* nBg */
                265950,
            },
            /* 11 */
            {
                /* nRg */
                1070701,
                /* nBg */
                270050,
            },
            /* 12 */
            {
                /* nRg */
                1039055,
                /* nBg */
                275000,
            },
            /* 13 */
            {
                /* nRg */
                1007409,
                /* nBg */
                280809,
            },
            /* 14 */
            {
                /* nRg */
                975805,
                /* nBg */
                287467,
            },
            /* 15 */
            {
                /* nRg */
                944264,
                /* nBg */
                294996,
            },
            /* 16 */
            {
                /* nRg */
                912796,
                /* nBg */
                303384,
            },
            /* 17 */
            {
                /* nRg */
                880951,
                /* nBg */
                318725,
            },
            /* 18 */
            {
                /* nRg */
                849546,
                /* nBg */
                334968,
            },
            /* 19 */
            {
                /* nRg */
                818623,
                /* nBg */
                352080,
            },
            /* 20 */
            {
                /* nRg */
                788183,
                /* nBg */
                370063,
            },
            /* 21 */
            {
                /* nRg */
                758267,
                /* nBg */
                388885,
            },
            /* 22 */
            {
                /* nRg */
                728897,
                /* nBg */
                408546,
            },
            /* 23 */
            {
                /* nRg */
                700082,
                /* nBg */
                429035,
            },
            /* 24 */
            {
                /* nRg */
                671865,
                /* nBg */
                450321,
            },
            /* 25 */
            {
                /* nRg */
                657310,
                /* nBg */
                461793,
            },
            /* 26 */
            {
                /* nRg */
                642924,
                /* nBg */
                473484,
            },
            /* 27 */
            {
                /* nRg */
                628716,
                /* nBg */
                485375,
            },
            /* 28 */
            {
                /* nRg */
                614686,
                /* nBg */
                497486,
            },
            /* 29 */
            {
                /* nRg */
                600845,
                /* nBg */
                509797,
            },
            /* 30 */
            {
                /* nRg */
                587171,
                /* nBg */
                522317,
            },
            /* 31 */
            {
                /* nRg */
                573697,
                /* nBg */
                535025,
            },
            /* 32 */
            {
                /* nRg */
                560401,
                /* nBg */
                547944,
            },
            /* 33 */
            {
                /* nRg */
                549810,
                /* nBg */
                558514,
            },
            /* 34 */
            {
                /* nRg */
                539346,
                /* nBg */
                569209,
            },
            /* 35 */
            {
                /* nRg */
                529007,
                /* nBg */
                580030,
            },
            /* 36 */
            {
                /* nRg */
                518793,
                /* nBg */
                590977,
            },
            /* 37 */
            {
                /* nRg */
                508717,
                /* nBg */
                602040,
            },
            /* 38 */
            {
                /* nRg */
                498766,
                /* nBg */
                613228,
            },
            /* 39 */
            {
                /* nRg */
                488961,
                /* nBg */
                624532,
            },
            /* 40 */
            {
                /* nRg */
                479283,
                /* nBg */
                635951,
            },
            /* 41 */
            {
                /* nRg */
                470968,
                /* nBg */
                645986,
            },
            /* 42 */
            {
                /* nRg */
                462747,
                /* nBg */
                656115,
            },
            /* 43 */
            {
                /* nRg */
                454642,
                /* nBg */
                666328,
            },
            /* 44 */
            {
                /* nRg */
                446641,
                /* nBg */
                676625,
            },
            /* 45 */
            {
                /* nRg */
                438745,
                /* nBg */
                687006,
            },
            /* 46 */
            {
                /* nRg */
                430954,
                /* nBg */
                697471,
            },
            /* 47 */
            {
                /* nRg */
                423279,
                /* nBg */
                708009,
            },
            /* 48 */
            {
                /* nRg */
                415708,
                /* nBg */
                718631,
            },
            /* 49 */
            {
                /* nRg */
                396068,
                /* nBg */
                747331,
            },
            /* 50 */
            {
                /* nRg */
                377236,
                /* nBg */
                776554,
            },
            /* 51 */
            {
                /* nRg */
                359221,
                /* nBg */
                806303,
            },
            /* 52 */
            {
                /* nRg */
                342035,
                /* nBg */
                836533,
            },
            /* 53 */
            {
                /* nRg */
                325688,
                /* nBg */
                867225,
            },
            /* 54 */
            {
                /* nRg */
                310200,
                /* nBg */
                898367,
            },
            /* 55 */
            {
                /* nRg */
                295583,
                /* nBg */
                929919,
            },
            /* 56 */
            {
                /* nRg */
                281847,
                /* nBg */
                961859,
            },
        },
        /* tRadiusLineList[512] */
        {
            /* 0 */
            {
                /* nK */
                -4691,
                /* nB */
                7859,
            },
            /* 1 */
            {
                /* nK */
                -6372,
                /* nB */
                10172,
            },
            /* 2 */
            {
                /* nK */
                -9836,
                /* nB */
                14933,
            },
            /* 3 */
            {
                /* nK */
                -21249,
                /* nB */
                30627,
            },
            /* 4 */
            {
                /* nK */
                137869,
                /* nB */
                -188163,
            },
            /* 5 */
            {
                /* nK */
                16231,
                /* nB */
                -20909,
            },
            /* 6 */
            {
                /* nK */
                8595,
                /* nB */
                -10409,
            },
            /* 7 */
            {
                /* nK */
                5820,
                /* nB */
                -6594,
            },
            /* 8 */
            {
                /* nK */
                4379,
                /* nB */
                -4612,
            },
            /* 9 */
            {
                /* nK */
                3922,
                /* nB */
                -3984,
            },
            /* 10 */
            {
                /* nK */
                3547,
                /* nB */
                -3468,
            },
            /* 11 */
            {
                /* nK */
                3233,
                /* nB */
                -3037,
            },
            /* 12 */
            {
                /* nK */
                2967,
                /* nB */
                -2670,
            },
            /* 13 */
            {
                /* nK */
                2737,
                /* nB */
                -2354,
            },
            /* 14 */
            {
                /* nK */
                2537,
                /* nB */
                -2079,
            },
            /* 15 */
            {
                /* nK */
                2360,
                /* nB */
                -1836,
            },
            /* 16 */
            {
                /* nK */
                2204,
                /* nB */
                -1621,
            },
            /* 17 */
            {
                /* nK */
                2050,
                /* nB */
                -1410,
            },
            /* 18 */
            {
                /* nK */
                1914,
                /* nB */
                -1222,
            },
            /* 19 */
            {
                /* nK */
                1791,
                /* nB */
                -1053,
            },
            /* 20 */
            {
                /* nK */
                1679,
                /* nB */
                -900,
            },
            /* 21 */
            {
                /* nK */
                1577,
                /* nB */
                -760,
            },
            /* 22 */
            {
                /* nK */
                1484,
                /* nB */
                -632,
            },
            /* 23 */
            {
                /* nK */
                1398,
                /* nB */
                -514,
            },
            /* 24 */
            {
                /* nK */
                1319,
                /* nB */
                -404,
            },
            /* 25 */
            {
                /* nK */
                1279,
                /* nB */
                -350,
            },
            /* 26 */
            {
                /* nK */
                1241,
                /* nB */
                -298,
            },
            /* 27 */
            {
                /* nK */
                1205,
                /* nB */
                -247,
            },
            /* 28 */
            {
                /* nK */
                1169,
                /* nB */
                -199,
            },
            /* 29 */
            {
                /* nK */
                1135,
                /* nB */
                -151,
            },
            /* 30 */
            {
                /* nK */
                1102,
                /* nB */
                -106,
            },
            /* 31 */
            {
                /* nK */
                1070,
                /* nB */
                -62,
            },
            /* 32 */
            {
                /* nK */
                1038,
                /* nB */
                -19,
            },
            /* 33 */
            {
                /* nK */
                1014,
                /* nB */
                14,
            },
            /* 34 */
            {
                /* nK */
                990,
                /* nB */
                47,
            },
            /* 35 */
            {
                /* nK */
                967,
                /* nB */
                79,
            },
            /* 36 */
            {
                /* nK */
                944,
                /* nB */
                110,
            },
            /* 37 */
            {
                /* nK */
                922,
                /* nB */
                141,
            },
            /* 38 */
            {
                /* nK */
                900,
                /* nB */
                171,
            },
            /* 39 */
            {
                /* nK */
                878,
                /* nB */
                200,
            },
            /* 40 */
            {
                /* nK */
                857,
                /* nB */
                229,
            },
            /* 41 */
            {
                /* nK */
                839,
                /* nB */
                254,
            },
            /* 42 */
            {
                /* nK */
                822,
                /* nB */
                278,
            },
            /* 43 */
            {
                /* nK */
                804,
                /* nB */
                302,
            },
            /* 44 */
            {
                /* nK */
                787,
                /* nB */
                325,
            },
            /* 45 */
            {
                /* nK */
                771,
                /* nB */
                348,
            },
            /* 46 */
            {
                /* nK */
                754,
                /* nB */
                371,
            },
            /* 47 */
            {
                /* nK */
                738,
                /* nB */
                394,
            },
            /* 48 */
            {
                /* nK */
                722,
                /* nB */
                416,
            },
            /* 49 */
            {
                /* nK */
                680,
                /* nB */
                473,
            },
            /* 50 */
            {
                /* nK */
                640,
                /* nB */
                528,
            },
            /* 51 */
            {
                /* nK */
                601,
                /* nB */
                581,
            },
            /* 52 */
            {
                /* nK */
                564,
                /* nB */
                633,
            },
            /* 53 */
            {
                /* nK */
                527,
                /* nB */
                683,
            },
            /* 54 */
            {
                /* nK */
                492,
                /* nB */
                732,
            },
            /* 55 */
            {
                /* nK */
                457,
                /* nB */
                779,
            },
            /* 56 */
            {
                /* nK */
                424,
                /* nB */
                825,
            },
        },
        /* tInLeftBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1711716,
                /* nBg */
                205101,
            },
            /* 1 */
            {
                /* nRg */
                1643444,
                /* nBg */
                186835,
            },
            /* 2 */
            {
                /* nRg */
                1573955,
                /* nBg */
                172354,
            },
            /* 3 */
            {
                /* nRg */
                1503490,
                /* nBg */
                161743,
            },
            /* 4 */
            {
                /* nRg */
                1432250,
                /* nBg */
                155053,
            },
            /* 5 */
            {
                /* nRg */
                1360454,
                /* nBg */
                152337,
            },
            /* 6 */
            {
                /* nRg */
                1288333,
                /* nBg */
                153637,
            },
            /* 7 */
            {
                /* nRg */
                1216107,
                /* nBg */
                158985,
            },
            /* 8 */
            {
                /* nRg */
                1143996,
                /* nBg */
                168401,
            },
            /* 9 */
            {
                /* nRg */
                1110106,
                /* nBg */
                171390,
            },
            /* 10 */
            {
                /* nRg */
                1076164,
                /* nBg */
                175280,
            },
            /* 11 */
            {
                /* nRg */
                1042211,
                /* nBg */
                180082,
            },
            /* 12 */
            {
                /* nRg */
                1008258,
                /* nBg */
                185787,
            },
            /* 13 */
            {
                /* nRg */
                974347,
                /* nBg */
                192414,
            },
            /* 14 */
            {
                /* nRg */
                940478,
                /* nBg */
                199963,
            },
            /* 15 */
            {
                /* nRg */
                906693,
                /* nBg */
                208415,
            },
            /* 16 */
            {
                /* nRg */
                873023,
                /* nBg */
                217800,
            },
            /* 17 */
            {
                /* nRg */
                838787,
                /* nBg */
                234304,
            },
            /* 18 */
            {
                /* nRg */
                805023,
                /* nBg */
                251753,
            },
            /* 19 */
            {
                /* nRg */
                771773,
                /* nBg */
                270155,
            },
            /* 20 */
            {
                /* nRg */
                739047,
                /* nBg */
                289491,
            },
            /* 21 */
            {
                /* nRg */
                706877,
                /* nBg */
                309728,
            },
            /* 22 */
            {
                /* nRg */
                675293,
                /* nBg */
                330878,
            },
            /* 23 */
            {
                /* nRg */
                644318,
                /* nBg */
                352898,
            },
            /* 24 */
            {
                /* nRg */
                613983,
                /* nBg */
                375778,
            },
            /* 25 */
            {
                /* nRg */
                598328,
                /* nBg */
                388120,
            },
            /* 26 */
            {
                /* nRg */
                582872,
                /* nBg */
                400682,
            },
            /* 27 */
            {
                /* nRg */
                567594,
                /* nBg */
                413474,
            },
            /* 28 */
            {
                /* nRg */
                552505,
                /* nBg */
                426498,
            },
            /* 29 */
            {
                /* nRg */
                537615,
                /* nBg */
                439731,
            },
            /* 30 */
            {
                /* nRg */
                522925,
                /* nBg */
                453195,
            },
            /* 31 */
            {
                /* nRg */
                508434,
                /* nBg */
                466857,
            },
            /* 32 */
            {
                /* nRg */
                494141,
                /* nBg */
                480751,
            },
            /* 33 */
            {
                /* nRg */
                482754,
                /* nBg */
                492118,
            },
            /* 34 */
            {
                /* nRg */
                471492,
                /* nBg */
                503610,
            },
            /* 35 */
            {
                /* nRg */
                460377,
                /* nBg */
                515249,
            },
            /* 36 */
            {
                /* nRg */
                449409,
                /* nBg */
                527014,
            },
            /* 37 */
            {
                /* nRg */
                438567,
                /* nBg */
                538916,
            },
            /* 38 */
            {
                /* nRg */
                427871,
                /* nBg */
                550932,
            },
            /* 39 */
            {
                /* nRg */
                417323,
                /* nBg */
                563085,
            },
            /* 40 */
            {
                /* nRg */
                406921,
                /* nBg */
                575364,
            },
            /* 41 */
            {
                /* nRg */
                397977,
                /* nBg */
                586164,
            },
            /* 42 */
            {
                /* nRg */
                389148,
                /* nBg */
                597049,
            },
            /* 43 */
            {
                /* nRg */
                380423,
                /* nBg */
                608027,
            },
            /* 44 */
            {
                /* nRg */
                371825,
                /* nBg */
                619100,
            },
            /* 45 */
            {
                /* nRg */
                363332,
                /* nBg */
                630268,
            },
            /* 46 */
            {
                /* nRg */
                354964,
                /* nBg */
                641508,
            },
            /* 47 */
            {
                /* nRg */
                346712,
                /* nBg */
                652843,
            },
            /* 48 */
            {
                /* nRg */
                338575,
                /* nBg */
                664262,
            },
            /* 49 */
            {
                /* nRg */
                317456,
                /* nBg */
                695122,
            },
            /* 50 */
            {
                /* nRg */
                297208,
                /* nBg */
                726548,
            },
            /* 51 */
            {
                /* nRg */
                277831,
                /* nBg */
                758529,
            },
            /* 52 */
            {
                /* nRg */
                259355,
                /* nBg */
                791035,
            },
            /* 53 */
            {
                /* nRg */
                241781,
                /* nBg */
                824034,
            },
            /* 54 */
            {
                /* nRg */
                225129,
                /* nBg */
                857504,
            },
            /* 55 */
            {
                /* nRg */
                209411,
                /* nBg */
                891436,
            },
            /* 56 */
            {
                /* nRg */
                194647,
                /* nBg */
                925777,
            },
        },
        /* tInRightBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1673706,
                /* nBg */
                379259,
            },
            /* 1 */
            {
                /* nRg */
                1615164,
                /* nBg */
                362839,
            },
            /* 2 */
            {
                /* nRg */
                1555500,
                /* nBg */
                349658,
            },
            /* 3 */
            {
                /* nRg */
                1494913,
                /* nBg */
                339791,
            },
            /* 4 */
            {
                /* nRg */
                1433571,
                /* nBg */
                333300,
            },
            /* 5 */
            {
                /* nRg */
                1371684,
                /* nBg */
                330239,
            },
            /* 6 */
            {
                /* nRg */
                1309420,
                /* nBg */
                330647,
            },
            /* 7 */
            {
                /* nRg */
                1246998,
                /* nBg */
                334548,
            },
            /* 8 */
            {
                /* nRg */
                1184597,
                /* nBg */
                341972,
            },
            /* 9 */
            {
                /* nRg */
                1155132,
                /* nBg */
                343860,
            },
            /* 10 */
            {
                /* nRg */
                1125604,
                /* nBg */
                346544,
            },
            /* 11 */
            {
                /* nRg */
                1096035,
                /* nBg */
                350015,
            },
            /* 12 */
            {
                /* nRg */
                1066423,
                /* nBg */
                354293,
            },
            /* 13 */
            {
                /* nRg */
                1036811,
                /* nBg */
                359368,
            },
            /* 14 */
            {
                /* nRg */
                1007210,
                /* nBg */
                365250,
            },
            /* 15 */
            {
                /* nRg */
                977650,
                /* nBg */
                371951,
            },
            /* 16 */
            {
                /* nRg */
                948143,
                /* nBg */
                379459,
            },
            /* 17 */
            {
                /* nRg */
                918427,
                /* nBg */
                393772,
            },
            /* 18 */
            {
                /* nRg */
                889130,
                /* nBg */
                408924,
            },
            /* 19 */
            {
                /* nRg */
                860262,
                /* nBg */
                424904,
            },
            /* 20 */
            {
                /* nRg */
                831856,
                /* nBg */
                441681,
            },
            /* 21 */
            {
                /* nRg */
                803943,
                /* nBg */
                459245,
            },
            /* 22 */
            {
                /* nRg */
                776533,
                /* nBg */
                477595,
            },
            /* 23 */
            {
                /* nRg */
                749648,
                /* nBg */
                496710,
            },
            /* 24 */
            {
                /* nRg */
                723308,
                /* nBg */
                516570,
            },
            /* 25 */
            {
                /* nRg */
                709729,
                /* nBg */
                527276,
            },
            /* 26 */
            {
                /* nRg */
                696307,
                /* nBg */
                538192,
            },
            /* 27 */
            {
                /* nRg */
                683053,
                /* nBg */
                549286,
            },
            /* 28 */
            {
                /* nRg */
                669956,
                /* nBg */
                560590,
            },
            /* 29 */
            {
                /* nRg */
                657038,
                /* nBg */
                572082,
            },
            /* 30 */
            {
                /* nRg */
                644287,
                /* nBg */
                583753,
            },
            /* 31 */
            {
                /* nRg */
                631704,
                /* nBg */
                595623,
            },
            /* 32 */
            {
                /* nRg */
                619299,
                /* nBg */
                607671,
            },
            /* 33 */
            {
                /* nRg */
                609411,
                /* nBg */
                617538,
            },
            /* 34 */
            {
                /* nRg */
                599649,
                /* nBg */
                627520,
            },
            /* 35 */
            {
                /* nRg */
                590002,
                /* nBg */
                637618,
            },
            /* 36 */
            {
                /* nRg */
                580471,
                /* nBg */
                647831,
            },
            /* 37 */
            {
                /* nRg */
                571065,
                /* nBg */
                658160,
            },
            /* 38 */
            {
                /* nRg */
                561785,
                /* nBg */
                668593,
            },
            /* 39 */
            {
                /* nRg */
                552631,
                /* nBg */
                679142,
            },
            /* 40 */
            {
                /* nRg */
                543603,
                /* nBg */
                689795,
            },
            /* 41 */
            {
                /* nRg */
                535843,
                /* nBg */
                699170,
            },
            /* 42 */
            {
                /* nRg */
                528178,
                /* nBg */
                708617,
            },
            /* 43 */
            {
                /* nRg */
                520607,
                /* nBg */
                718149,
            },
            /* 44 */
            {
                /* nRg */
                513142,
                /* nBg */
                727754,
            },
            /* 45 */
            {
                /* nRg */
                505770,
                /* nBg */
                737443,
            },
            /* 46 */
            {
                /* nRg */
                498504,
                /* nBg */
                747205,
            },
            /* 47 */
            {
                /* nRg */
                491342,
                /* nBg */
                757040,
            },
            /* 48 */
            {
                /* nRg */
                484274,
                /* nBg */
                766949,
            },
            /* 49 */
            {
                /* nRg */
                465956,
                /* nBg */
                793730,
            },
            /* 50 */
            {
                /* nRg */
                448371,
                /* nBg */
                821014,
            },
            /* 51 */
            {
                /* nRg */
                431562,
                /* nBg */
                848770,
            },
            /* 52 */
            {
                /* nRg */
                415519,
                /* nBg */
                876977,
            },
            /* 53 */
            {
                /* nRg */
                400273,
                /* nBg */
                905624,
            },
            /* 54 */
            {
                /* nRg */
                385824,
                /* nBg */
                934680,
            },
            /* 55 */
            {
                /* nRg */
                372182,
                /* nBg */
                964124,
            },
            /* 56 */
            {
                /* nRg */
                359357,
                /* nBg */
                993935,
            },
        },
        /* tOutLeftBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1725138,
                /* nBg */
                143634,
            },
            /* 1 */
            {
                /* nRg */
                1653416,
                /* nBg */
                124718,
            },
            /* 2 */
            {
                /* nRg */
                1580477,
                /* nBg */
                109786,
            },
            /* 3 */
            {
                /* nRg */
                1506521,
                /* nBg */
                98902,
            },
            /* 4 */
            {
                /* nRg */
                1431778,
                /* nBg */
                92138,
            },
            /* 5 */
            {
                /* nRg */
                1356490,
                /* nBg */
                89548,
            },
            /* 6 */
            {
                /* nRg */
                1280888,
                /* nBg */
                91163,
            },
            /* 7 */
            {
                /* nRg */
                1205202,
                /* nBg */
                97025,
            },
            /* 8 */
            {
                /* nRg */
                1129673,
                /* nBg */
                107143,
            },
            /* 9 */
            {
                /* nRg */
                1094210,
                /* nBg */
                110520,
            },
            /* 10 */
            {
                /* nRg */
                1058716,
                /* nBg */
                114830,
            },
            /* 11 */
            {
                /* nRg */
                1023211,
                /* nBg */
                120104,
            },
            /* 12 */
            {
                /* nRg */
                987727,
                /* nBg */
                126322,
            },
            /* 13 */
            {
                /* nRg */
                952296,
                /* nBg */
                133494,
            },
            /* 14 */
            {
                /* nRg */
                916927,
                /* nBg */
                141621,
            },
            /* 15 */
            {
                /* nRg */
                881653,
                /* nBg */
                150701,
            },
            /* 16 */
            {
                /* nRg */
                846505,
                /* nBg */
                160747,
            },
            /* 17 */
            {
                /* nRg */
                810675,
                /* nBg */
                178017,
            },
            /* 18 */
            {
                /* nRg */
                775338,
                /* nBg */
                196283,
            },
            /* 19 */
            {
                /* nRg */
                740536,
                /* nBg */
                215545,
            },
            /* 20 */
            {
                /* nRg */
                706289,
                /* nBg */
                235772,
            },
            /* 21 */
            {
                /* nRg */
                672620,
                /* nBg */
                256964,
            },
            /* 22 */
            {
                /* nRg */
                639568,
                /* nBg */
                279089,
            },
            /* 23 */
            {
                /* nRg */
                607146,
                /* nBg */
                302137,
            },
            /* 24 */
            {
                /* nRg */
                575396,
                /* nBg */
                326086,
            },
            /* 25 */
            {
                /* nRg */
                559017,
                /* nBg */
                339005,
            },
            /* 26 */
            {
                /* nRg */
                542827,
                /* nBg */
                352154,
            },
            /* 27 */
            {
                /* nRg */
                526847,
                /* nBg */
                365544,
            },
            /* 28 */
            {
                /* nRg */
                511055,
                /* nBg */
                379165,
            },
            /* 29 */
            {
                /* nRg */
                495473,
                /* nBg */
                393027,
            },
            /* 30 */
            {
                /* nRg */
                480091,
                /* nBg */
                407110,
            },
            /* 31 */
            {
                /* nRg */
                464928,
                /* nBg */
                421412,
            },
            /* 32 */
            {
                /* nRg */
                449965,
                /* nBg */
                435945,
            },
            /* 33 */
            {
                /* nRg */
                438043,
                /* nBg */
                447847,
            },
            /* 34 */
            {
                /* nRg */
                426267,
                /* nBg */
                459884,
            },
            /* 35 */
            {
                /* nRg */
                414628,
                /* nBg */
                472058,
            },
            /* 36 */
            {
                /* nRg */
                403146,
                /* nBg */
                484379,
            },
            /* 37 */
            {
                /* nRg */
                391800,
                /* nBg */
                496826,
            },
            /* 38 */
            {
                /* nRg */
                380612,
                /* nBg */
                509409,
            },
            /* 39 */
            {
                /* nRg */
                369571,
                /* nBg */
                522128,
            },
            /* 40 */
            {
                /* nRg */
                358686,
                /* nBg */
                534973,
            },
            /* 41 */
            {
                /* nRg */
                349323,
                /* nBg */
                546277,
            },
            /* 42 */
            {
                /* nRg */
                340074,
                /* nBg */
                557675,
            },
            /* 43 */
            {
                /* nRg */
                330952,
                /* nBg */
                569167,
            },
            /* 44 */
            {
                /* nRg */
                321944,
                /* nBg */
                580754,
            },
            /* 45 */
            {
                /* nRg */
                313063,
                /* nBg */
                592435,
            },
            /* 46 */
            {
                /* nRg */
                304297,
                /* nBg */
                604210,
            },
            /* 47 */
            {
                /* nRg */
                295656,
                /* nBg */
                616070,
            },
            /* 48 */
            {
                /* nRg */
                287142,
                /* nBg */
                628013,
            },
            /* 49 */
            {
                /* nRg */
                265049,
                /* nBg */
                660309,
            },
            /* 50 */
            {
                /* nRg */
                243857,
                /* nBg */
                693214,
            },
            /* 51 */
            {
                /* nRg */
                223577,
                /* nBg */
                726674,
            },
            /* 52 */
            {
                /* nRg */
                204231,
                /* nBg */
                760700,
            },
            /* 53 */
            {
                /* nRg */
                185850,
                /* nBg */
                795240,
            },
            /* 54 */
            {
                /* nRg */
                168422,
                /* nBg */
                830273,
            },
            /* 55 */
            {
                /* nRg */
                151970,
                /* nBg */
                865778,
            },
            /* 56 */
            {
                /* nRg */
                136504,
                /* nBg */
                901723,
            },
        },
        /* tOutRightBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1660294,
                /* nBg */
                440727,
            },
            /* 1 */
            {
                /* nRg */
                1605181,
                /* nBg */
                424956,
            },
            /* 2 */
            {
                /* nRg */
                1548988,
                /* nBg */
                412237,
            },
            /* 3 */
            {
                /* nRg */
                1491882,
                /* nBg */
                402632,
            },
            /* 4 */
            {
                /* nRg */
                1434043,
                /* nBg */
                396215,
            },
            /* 5 */
            {
                /* nRg */
                1375637,
                /* nBg */
                393027,
            },
            /* 6 */
            {
                /* nRg */
                1316865,
                /* nBg */
                393122,
            },
            /* 7 */
            {
                /* nRg */
                1257893,
                /* nBg */
                396509,
            },
            /* 8 */
            {
                /* nRg */
                1198921,
                /* nBg */
                403240,
            },
            /* 9 */
            {
                /* nRg */
                1171029,
                /* nBg */
                404740,
            },
            /* 10 */
            {
                /* nRg */
                1143063,
                /* nBg */
                406994,
            },
            /* 11 */
            {
                /* nRg */
                1115024,
                /* nBg */
                409993,
            },
            /* 12 */
            {
                /* nRg */
                1086954,
                /* nBg */
                413768,
            },
            /* 13 */
            {
                /* nRg */
                1058852,
                /* nBg */
                418298,
            },
            /* 14 */
            {
                /* nRg */
                1030761,
                /* nBg */
                423593,
            },
            /* 15 */
            {
                /* nRg */
                1002690,
                /* nBg */
                429665,
            },
            /* 16 */
            {
                /* nRg */
                974651,
                /* nBg */
                436512,
            },
            /* 17 */
            {
                /* nRg */
                946539,
                /* nBg */
                450059,
            },
            /* 18 */
            {
                /* nRg */
                918804,
                /* nBg */
                464404,
            },
            /* 19 */
            {
                /* nRg */
                891499,
                /* nBg */
                479514,
            },
            /* 20 */
            {
                /* nRg */
                864624,
                /* nBg */
                495389,
            },
            /* 21 */
            {
                /* nRg */
                838200,
                /* nBg */
                512020,
            },
            /* 22 */
            {
                /* nRg */
                812258,
                /* nBg */
                529384,
            },
            /* 23 */
            {
                /* nRg */
                786820,
                /* nBg */
                547472,
            },
            /* 24 */
            {
                /* nRg */
                761895,
                /* nBg */
                566262,
            },
            /* 25 */
            {
                /* nRg */
                749050,
                /* nBg */
                576392,
            },
            /* 26 */
            {
                /* nRg */
                736352,
                /* nBg */
                586720,
            },
            /* 27 */
            {
                /* nRg */
                723801,
                /* nBg */
                597227,
            },
            /* 28 */
            {
                /* nRg */
                711417,
                /* nBg */
                607912,
            },
            /* 29 */
            {
                /* nRg */
                699180,
                /* nBg */
                618786,
            },
            /* 30 */
            {
                /* nRg */
                687111,
                /* nBg */
                629838,
            },
            /* 31 */
            {
                /* nRg */
                675210,
                /* nBg */
                641068,
            },
            /* 32 */
            {
                /* nRg */
                663476,
                /* nBg */
                652476,
            },
            /* 33 */
            {
                /* nRg */
                654123,
                /* nBg */
                661809,
            },
            /* 34 */
            {
                /* nRg */
                644874,
                /* nBg */
                671256,
            },
            /* 35 */
            {
                /* nRg */
                635752,
                /* nBg */
                680809,
            },
            /* 36 */
            {
                /* nRg */
                626734,
                /* nBg */
                690477,
            },
            /* 37 */
            {
                /* nRg */
                617831,
                /* nBg */
                700250,
            },
            /* 38 */
            {
                /* nRg */
                609055,
                /* nBg */
                710117,
            },
            /* 39 */
            {
                /* nRg */
                600383,
                /* nBg */
                720099,
            },
            /* 40 */
            {
                /* nRg */
                591848,
                /* nBg */
                730186,
            },
            /* 41 */
            {
                /* nRg */
                584497,
                /* nBg */
                739047,
            },
            /* 42 */
            {
                /* nRg */
                577241,
                /* nBg */
                747991,
            },
            /* 43 */
            {
                /* nRg */
                570079,
                /* nBg */
                757019,
            },
            /* 44 */
            {
                /* nRg */
                563012,
                /* nBg */
                766111,
            },
            /* 45 */
            {
                /* nRg */
                556039,
                /* nBg */
                775275,
            },
            /* 46 */
            {
                /* nRg */
                549171,
                /* nBg */
                784513,
            },
            /* 47 */
            {
                /* nRg */
                542386,
                /* nBg */
                793814,
            },
            /* 48 */
            {
                /* nRg */
                535707,
                /* nBg */
                803199,
            },
            /* 49 */
            {
                /* nRg */
                518364,
                /* nBg */
                828543,
            },
            /* 50 */
            {
                /* nRg */
                501733,
                /* nBg */
                854359,
            },
            /* 51 */
            {
                /* nRg */
                485816,
                /* nBg */
                880615,
            },
            /* 52 */
            {
                /* nRg */
                470643,
                /* nBg */
                907312,
            },
            /* 53 */
            {
                /* nRg */
                456214,
                /* nBg */
                934418,
            },
            /* 54 */
            {
                /* nRg */
                442531,
                /* nBg */
                961911,
            },
            /* 55 */
            {
                /* nRg */
                429623,
                /* nBg */
                989772,
            },
            /* 56 */
            {
                /* nRg */
                417491,
                /* nBg */
                1017989,
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
                    1160774,
                    /* nBg */
                    240124,
                },
            },
            /* 1 */
            {
                /* szName[32] */
                "A",
                /* nCct */
                2854,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    917504,
                    /* nBg */
                    313524,
                },
            },
            /* 2 */
            {
                /* szName[32] */
                "TL84",
                /* nCct */
                3900,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    629146,
                    /* nBg */
                    395313,
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
                    551551,
                    /* nBg */
                    538968,
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
                    501219,
                    /* nBg */
                    654311,
                },
            },
            /* 5 */
            {
                /* szName[32] */
                "D75",
                /* nCct */
                8000,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    433062,
                    /* nBg */
                    730857,
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
                4000,
                /* nRadius */
                31457,
                /* tCoord */
                {
                    /* nRg */
                    586154,
                    /* nBg */
                    413139,
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
        10240,
        /* nLuxIndoorStart */
        25600,
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
            {300, 200, 100, 50, 20, 10, 10, 10, /*0 - 7*/},
            {500, 300, 150, 150, 80, 30, 30, 30, /*0 - 7*/},
            {700, 700, 500, 400, 200, 100, 100, 100, /*0 - 7*/},
            {700, 700, 500, 400, 200, 100, 100, 100, /*0 - 7*/},
            {400, 200, 150, 150, 80, 30, 30, 30, /*0 - 7*/},
            {200, 200, 200, 100, 100, 50, 50, 50, /*0 - 7*/},
            {700, 700, 700, 700, 600, 500, 500, 500, /*0 - 7*/},
            {800, 800, 800, 800, 700, 600, 600, 600, /*0 - 7*/},
            {300, 250, 200, 100, 50, 50, 50, 50, /*0 - 7*/},
            {400, 400, 200, 200, 100, 100, 100, 100, /*0 - 7*/},
            {800, 800, 800, 800, 800, 800, 800, 800, /*0 - 7*/},
            {900, 1000, 1000, 1000, 900, 900, 900, 900, /*0 - 7*/},
            {500, 400, 300, 100, 50, 50, 50, 50, /*0 - 7*/},
            {500, 500, 400, 400, 300, 200, 200, 200, /*0 - 7*/},
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
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
            {1800, 2300, 2800, 3800, 4100, 5000, 6500, 7500, 10000, 12000, /*0 - 9*/},
        },
        /* nPreferGrShift[8][32] */
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 9*/},
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
        512,
        /* nGreenCutBreakAngle */
        104858,
        /* nGreenCutOffsetRg */
        -31456,
        /* nGreenCutOffsetBg */
        -52428,
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

const static AX_ISP_IQ_CAF_PARAM_T caf_param_sdr_qs = {
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

const static AX_ISP_IQ_DPC_PARAM_T dpc_param_sdr_qs = {
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

const static AX_ISP_IQ_BLC_PARAM_T blc_param_sdr_qs = {
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
            4128,
            /* nSblGrValue */
            4128,
            /* nSblGbValue */
            4128,
            /* nSblBValue */
            4128,
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
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4112, 4112, /*0 - 1*/},
                {4105, 4105, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4115, 4115, /*0 - 1*/},
            },
            /* nAutoSblGrValue[16][10] */
            {
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4112, 4112, /*0 - 1*/},
                {4105, 4105, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4115, 4115, /*0 - 1*/},
            },
            /* nAutoSblGbValue[16][10] */
            {
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4112, 4112, /*0 - 1*/},
                {4105, 4105, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4115, 4115, /*0 - 1*/},
            },
            /* nAutoSblBValue[16][10] */
            {
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4112, 4112, /*0 - 1*/},
                {4105, 4105, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4128, 4128, /*0 - 1*/},
                {4115, 4115, /*0 - 1*/},
            },
        },
    },
};

const static AX_ISP_IQ_HDR_PARAM_T hdr_param_sdr_qs = {
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

const static AX_ISP_IQ_AINR_PARAM_T ainr_param_sdr_qs = {
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
            "3d_0108_again54x_lv0",
            /* szSpatialBaseNrName[256] */
            "2d_0108_again54x_lv0",
            /* nHcgMode */
            0,
            /* nIsoThresholdMin */
            0,
            /* nIsoThresholdMax */
            0,
            /* nBiasIn2D */
            {4096, 4096, 4096, 4096, /*0 - 3*/},
            /* nBiasIn3D */
            {4096, 4096, 4096, 4096, /*0 - 3*/},
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
                    {64, 4096, /*0 - 1*/},
                    {80, 4096, /*0 - 1*/},
                    {96, 4096, /*0 - 1*/},
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
        3,
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
                    "3d_0108_again54x_lv0",
                    /* szSpatialBaseNrName[256] */
                    "2d_0108_again54x_lv0",
                    /* nHcgMode */
                    0,
                    /* nIsoThresholdMin */
                    1600,
                    /* nIsoThresholdMax */
                    5400,
                    /* nBiasIn2D */
                    {4096, 4096, 4096, 4096, /*0 - 3*/},
                    /* nBiasIn3D */
                    {4096, 4096, 4096, 4096, /*0 - 3*/},
                },
                /* tParams */
                {
                    /* tBias */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {16384, 32768, 40960, 49152, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {20480, 40960, 49152, 55296, /*0 - 3*/},
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
                        {16384, 32768, 40960, 49152, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {20480, 40960, 49152, 55296, /*0 - 3*/},
                        /* nTemporalFilterStrLut[4][17][2] */
                        {
                            /* nTemporalFilterStrLut 0 */
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
                            /* nTemporalFilterStrLut 1 */
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
                            /* nTemporalFilterStrLut 2 */
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
                            /* nTemporalFilterStrLut 3 */
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
                        /* nVstTemporalFilterStrLut[4][17][2] */
                        {
                            /* nVstTemporalFilterStrLut 0 */
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
                            /* nVstTemporalFilterStrLut 1 */
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
                            /* nVstTemporalFilterStrLut 2 */
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
                            /* nVstTemporalFilterStrLut 3 */
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
                    },
                    /* tSens */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {16384, 32768, 40960, 49152, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {20480, 40960, 49152, 55296, /*0 - 3*/},
                        /* nSpatialNrStrLut[4][17][2] */
                        {
                            /* nSpatialNrStrLut 0 */
                            {
                                {0, 300, /*0 - 1*/},
                                {16, 400, /*0 - 1*/},
                                {32, 500, /*0 - 1*/},
                                {48, 600, /*0 - 1*/},
                                {64, 700, /*0 - 1*/},
                                {80, 800, /*0 - 1*/},
                                {96, 900, /*0 - 1*/},
                                {112, 1000, /*0 - 1*/},
                                {128, 1200, /*0 - 1*/},
                                {144, 1400, /*0 - 1*/},
                                {160, 1600, /*0 - 1*/},
                                {176, 1800, /*0 - 1*/},
                                {192, 2000, /*0 - 1*/},
                                {208, 2000, /*0 - 1*/},
                                {224, 2000, /*0 - 1*/},
                                {240, 2000, /*0 - 1*/},
                                {255, 2000, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 1 */
                            {
                                {0, 900, /*0 - 1*/},
                                {16, 1000, /*0 - 1*/},
                                {32, 1100, /*0 - 1*/},
                                {48, 1200, /*0 - 1*/},
                                {64, 1300, /*0 - 1*/},
                                {80, 1400, /*0 - 1*/},
                                {96, 1400, /*0 - 1*/},
                                {112, 1400, /*0 - 1*/},
                                {128, 1500, /*0 - 1*/},
                                {144, 1600, /*0 - 1*/},
                                {160, 1700, /*0 - 1*/},
                                {176, 1800, /*0 - 1*/},
                                {192, 1900, /*0 - 1*/},
                                {208, 2000, /*0 - 1*/},
                                {224, 2000, /*0 - 1*/},
                                {240, 2000, /*0 - 1*/},
                                {255, 2000, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 2 */
                            {
                                {0, 1200, /*0 - 1*/},
                                {16, 1300, /*0 - 1*/},
                                {32, 1400, /*0 - 1*/},
                                {48, 1500, /*0 - 1*/},
                                {64, 1600, /*0 - 1*/},
                                {80, 1600, /*0 - 1*/},
                                {96, 1600, /*0 - 1*/},
                                {112, 1600, /*0 - 1*/},
                                {128, 1700, /*0 - 1*/},
                                {144, 1800, /*0 - 1*/},
                                {160, 1900, /*0 - 1*/},
                                {176, 2000, /*0 - 1*/},
                                {192, 2100, /*0 - 1*/},
                                {208, 2200, /*0 - 1*/},
                                {224, 2200, /*0 - 1*/},
                                {240, 2200, /*0 - 1*/},
                                {255, 2200, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 3 */
                            {
                                {0, 1500, /*0 - 1*/},
                                {16, 1600, /*0 - 1*/},
                                {32, 1700, /*0 - 1*/},
                                {48, 1800, /*0 - 1*/},
                                {64, 1800, /*0 - 1*/},
                                {80, 1800, /*0 - 1*/},
                                {96, 1800, /*0 - 1*/},
                                {112, 1900, /*0 - 1*/},
                                {128, 2000, /*0 - 1*/},
                                {144, 2100, /*0 - 1*/},
                                {160, 2200, /*0 - 1*/},
                                {176, 2300, /*0 - 1*/},
                                {192, 2400, /*0 - 1*/},
                                {208, 2400, /*0 - 1*/},
                                {224, 2400, /*0 - 1*/},
                                {240, 2400, /*0 - 1*/},
                                {255, 2400, /*0 - 1*/},
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
                    "3d_0108_isp1-16x_lv0",
                    /* szSpatialBaseNrName[256] */
                    "2d_0108_isp1-16x_lv0",
                    /* nHcgMode */
                    0,
                    /* nIsoThresholdMin */
                    5400,
                    /* nIsoThresholdMax */
                    54000,
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
                        {55296, 110592, 221184, 368640, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {82944, 165888, 307200, 442368, /*0 - 3*/},
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
                        {55296, 110592, 221184, 409600, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {82944, 165888, 307200, 552960, /*0 - 3*/},
                        /* nTemporalFilterStrLut[4][17][2] */
                        {
                            /* nTemporalFilterStrLut 0 */
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
                            /* nTemporalFilterStrLut 1 */
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
                            /* nTemporalFilterStrLut 2 */
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
                            /* nTemporalFilterStrLut 3 */
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
                        /* nVstTemporalFilterStrLut[4][17][2] */
                        {
                            /* nVstTemporalFilterStrLut 0 */
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
                            /* nVstTemporalFilterStrLut 1 */
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
                            /* nVstTemporalFilterStrLut 2 */
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
                            /* nVstTemporalFilterStrLut 3 */
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
                    },
                    /* tSens */
                    {
                        /* nRefGrpNum */
                        4,
                        /* nRefValStart[4] */
                        {55296, 110592, 221184, 409600, /*0 - 3*/},
                        /* nRefValEnd[4] */
                        {82944, 165888, 307200, 552960, /*0 - 3*/},
                        /* nSpatialNrStrLut[4][17][2] */
                        {
                            /* nSpatialNrStrLut 0 */
                            {
                                {0, 2000, /*0 - 1*/},
                                {16, 2200, /*0 - 1*/},
                                {32, 2400, /*0 - 1*/},
                                {48, 2600, /*0 - 1*/},
                                {64, 2800, /*0 - 1*/},
                                {80, 3000, /*0 - 1*/},
                                {96, 3000, /*0 - 1*/},
                                {112, 3000, /*0 - 1*/},
                                {128, 3000, /*0 - 1*/},
                                {144, 3000, /*0 - 1*/},
                                {160, 3000, /*0 - 1*/},
                                {176, 3000, /*0 - 1*/},
                                {192, 3000, /*0 - 1*/},
                                {208, 3000, /*0 - 1*/},
                                {224, 3000, /*0 - 1*/},
                                {240, 3000, /*0 - 1*/},
                                {255, 3000, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 1 */
                            {
                                {0, 2400, /*0 - 1*/},
                                {16, 2600, /*0 - 1*/},
                                {32, 2800, /*0 - 1*/},
                                {48, 3000, /*0 - 1*/},
                                {64, 3200, /*0 - 1*/},
                                {80, 3400, /*0 - 1*/},
                                {96, 3600, /*0 - 1*/},
                                {112, 3600, /*0 - 1*/},
                                {128, 3600, /*0 - 1*/},
                                {144, 3600, /*0 - 1*/},
                                {160, 3600, /*0 - 1*/},
                                {176, 3600, /*0 - 1*/},
                                {192, 3500, /*0 - 1*/},
                                {208, 3400, /*0 - 1*/},
                                {224, 3300, /*0 - 1*/},
                                {240, 3200, /*0 - 1*/},
                                {255, 3100, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 2 */
                            {
                                {0, 2600, /*0 - 1*/},
                                {16, 2800, /*0 - 1*/},
                                {32, 3000, /*0 - 1*/},
                                {48, 3200, /*0 - 1*/},
                                {64, 3400, /*0 - 1*/},
                                {80, 3600, /*0 - 1*/},
                                {96, 3800, /*0 - 1*/},
                                {112, 3800, /*0 - 1*/},
                                {128, 3800, /*0 - 1*/},
                                {144, 3800, /*0 - 1*/},
                                {160, 3800, /*0 - 1*/},
                                {176, 3800, /*0 - 1*/},
                                {192, 3700, /*0 - 1*/},
                                {208, 3600, /*0 - 1*/},
                                {224, 3500, /*0 - 1*/},
                                {240, 3400, /*0 - 1*/},
                                {255, 3300, /*0 - 1*/},
                            },
                            /* nSpatialNrStrLut 3 */
                            {
                                {0, 2700, /*0 - 1*/},
                                {16, 2900, /*0 - 1*/},
                                {32, 3100, /*0 - 1*/},
                                {48, 3300, /*0 - 1*/},
                                {64, 3500, /*0 - 1*/},
                                {80, 3700, /*0 - 1*/},
                                {96, 3800, /*0 - 1*/},
                                {112, 3800, /*0 - 1*/},
                                {128, 3800, /*0 - 1*/},
                                {144, 3800, /*0 - 1*/},
                                {160, 3800, /*0 - 1*/},
                                {176, 3800, /*0 - 1*/},
                                {192, 3700, /*0 - 1*/},
                                {208, 3600, /*0 - 1*/},
                                {224, 3500, /*0 - 1*/},
                                {240, 3400, /*0 - 1*/},
                                {255, 3300, /*0 - 1*/},
                            },
                        },
                    },
                },
            },
            /* 2 */
            {
                /* tMata */
                {
                    /* szModelPath[256] */
                    "/opt/etc/models/aiisp/SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
                    /* szModelName[256] */
                    "SC200AI_SDR_1920x1080_10b_LCG_ISP1_A54X_I1-16X_0000_MULTI2_00000695723_240308_AX620E.axmodel",
                    /* szTemporalBaseNrName[256] */
                    "3d_0108_isp1-16x_lv0",
                    /* szSpatialBaseNrName[256] */
                    "2d_0108_isp1-16x_lv0",
                    /* nHcgMode */
                    0,
                    /* nIsoThresholdMin */
                    54000,
                    /* nIsoThresholdMax */
                    86400,
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
                        2,
                        /* nRefValStart[4] */
                        {552960, 663552, /*0 - 1*/},
                        /* nRefValEnd[4] */
                        {663552, 884336, /*0 - 1*/},
                        /* nBiasIn[4][4] */
                        {
                            /*  nBiasIn 0 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 1 */
                            {0, 0, 0, 0, /*0 - 3*/},
                        },
                        /* nBiasOut[4][4] */
                        {
                            /*  nBiasOut 0 */
                            {0, 0, 0, 0, /*0 - 3*/},
                            /*  nBiasOut 1 */
                            {0, 0, 0, 0, /*0 - 3*/},

                        },
                    },
                    /* tNonSens */
                    {
                        /* nRefGrpNum */
                        2,
                        /* nRefValStart[4] */
                        {552960, 663552, /*0 - 1*/},
                        /* nRefValEnd[4] */
                        {663552, 884336, /*0 - 1*/},
                        /* nTemporalFilterStrLut[4][17][2] */
                        {
                            /* nTemporalFilterStrLut 0 */
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
                            /* nTemporalFilterStrLut 1 */
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
                        /* nVstTemporalFilterStrLut[4][17][2] */
                        {
                            /* nVstTemporalFilterStrLut 0 */
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
                            /* nVstTemporalFilterStrLut 1 */
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
                            /* nVstTemporalFilterStrLut 2 */
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
                            /* nVstTemporalFilterStrLut 3 */
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
                    },
                    /* tSens */
                    {
                        /* nRefGrpNum */
                        2,
                        /* nRefValStart[4] */
                        {552960, 663552, /*0 - 1*/},
                        /* nRefValEnd[4] */
                        {663552, 884336, /*0 - 1*/},
                        /* nSpatialNrStrLut[4][17][2] */
                        {
                            /* nSpatialNrStrLut 0 */
                            {
                                {0, 2900, /*0 - 1*/},
                                {16, 3100, /*0 - 1*/},
                                {32, 3300, /*0 - 1*/},
                                {48, 3500, /*0 - 1*/},
                                {64, 3700, /*0 - 1*/},
                                {80, 3800, /*0 - 1*/},
                                {96, 3800, /*0 - 1*/},
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
                            /* nSpatialNrStrLut 1 */
                            {
                                {0, 3000, /*0 - 1*/},
                                {16, 3200, /*0 - 1*/},
                                {32, 3400, /*0 - 1*/},
                                {48, 3600, /*0 - 1*/},
                                {64, 3800, /*0 - 1*/},
                                {80, 3800, /*0 - 1*/},
                                {96, 3800, /*0 - 1*/},
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

const static AX_ISP_IQ_RAW2DNR_PARAM_T raw2dnr_param_sdr_qs = {
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
            {1024, 768, 512, 384, 256, 192, 160, 128, 96, 64, 64, 64, 64, 64, 64, 64, 64, /*0 - 16*/},
            {1024, 768, 512, 384, 256, 192, 160, 128, 96, 64, 64, 64, 64, 64, 64, 64, 64 /*0 - 16*/},
        },
        /* nLowFreqNrFactor[2][17] */
        {
            {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
            {64, 56, 48, 40, 36, 32, 28, 24, 20, 16, 16, 12, 12, 8, 8, 8, 8, /*0 - 16*/},
        },
        /* nInterChannelStrength */
        128,
        /* nHfNrStrength[2] */
        {16, 16, /*0 - 1*/},
        /* nMfNrStrength[2] */
        {24, 24, /*0 - 1*/},
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
                {1024, 768, 512, 384, 256, 192, 160, 128, 96, 64, 64, 64, 64, 64, 64, 64, 64 /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 96, 64, 64, 64, 64, 64, 64, 64, 64 /*0 - 16*/},
            },
            /* nHighFreqNrFactor 1 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 96, 64, 64, 64, 64, 64, 64, 64, 64 /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 96, 64, 64, 64, 64, 64, 64, 64, 64 /*0 - 16*/},
            },
            /* nHighFreqNrFactor 2 */
            {
                {1024, 768, 512, 384, 256, 192, 160, 128, 96, 96, 96, 96, 96, 96, 96, 96, 96, /*0 - 16*/},
                {1024, 768, 512, 384, 256, 192, 160, 128, 96, 96, 96, 96, 96, 96, 96, 96, 96, /*0 - 16*/},
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
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nHfNrStrength[12][2] */
        {
            {32, 32, /*0 - 1*/},
            {40, 40, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {56, 56, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
            {48, 48, /*0 - 1*/},
        },
        /* nMfNrStrength[12][2] */
        {
            {48, 48, /*0 - 1*/},
            {56, 56, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {72, 72, /*0 - 1*/},
            {80, 80, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
            {64, 64, /*0 - 1*/},
        },
    },
};

const static AX_ISP_IQ_LSC_PARAM_T lsc_param_sdr_qs = {
    /* nLscEn */
    0,
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

const static AX_ISP_IQ_RLTM_PARAM_T rltm_param_sdr_qs = {
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
        {16, 16, 16, 16, 64, /*0 - 4*/},
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
        45,
        /* nExtraDgain */
        16,
        /* nRltmStrength */
        48,
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
            0, 96, 170, 237, 300, 360, 418, 474, 529, 582, 635, 686, 737, 787, 836, 884, 932, 980, 1027, 1073, 1119, 1165, 1210, 1255, 1299, 1343, 1387, 1431, 1474, 1517, 1559, 1602,  /* 0 - 31*/
            1644, 1686, 1728, 1769, 1810, 1851, 1892, 1933, 1973, 2014, 2054, 2094, 2133, 2173, 2212, 2252, 2291, 2330, 2368, 2407, 2446, 2484, 2522, 2561, 2599, 2637, 2674, 2712, 2750, 2787, 2824, 2861,  /* 32 - 63*/
            2899, 2936, 2973, 3009, 3046, 3083, 3119, 3156, 3192, 3228, 3264, 3300, 3336, 3372, 3408, 3444, 3479, 3515, 3550, 3586, 3621, 3656, 3691, 3726, 3761, 3796, 3831, 3866, 3901, 3935, 3970, 4004,  /* 64 - 95*/
            4039, 4073, 4108, 4142, 4176, 4210, 4244, 4278, 4312, 4346, 4380, 4414, 4447, 4481, 4515, 4548, 4582, 4615, 4649, 4682, 4715, 4749, 4782, 4815, 4848, 4881, 4914, 4947, 4980, 5013, 5045, 5078,  /* 96 - 127*/
            5111, 5143, 5176, 5209, 5241, 5274, 5306, 5338, 5371, 5403, 5435, 5467, 5500, 5532, 5564, 5596, 5628, 5660, 5692, 5724, 5755, 5787, 5819, 5851, 5882, 5914, 5946, 5977, 6009, 6040, 6072, 6103,  /* 128 - 159*/
            6134, 6166, 6197, 6228, 6260, 6291, 6322, 6353, 6384, 6415, 6446, 6477, 6508, 6539, 6570, 6601, 6632, 6663, 6694, 6724, 6755, 6786, 6816, 6847, 6878, 6908, 6939, 6969, 7000, 7030, 7061, 7091,  /* 160 - 191*/
            7121, 7152, 7182, 7212, 7242, 7273, 7303, 7333, 7363, 7393, 7423, 7453, 7483, 7513, 7543, 7573, 7603, 7633, 7663, 7693, 7723, 7753, 7782, 7812, 7842, 7871, 7901, 7931, 7960, 7990, 8020, 8049,  /* 192 - 223*/
            8079, 8108, 8138, 8167, 8196, 8226, 8255, 8285, 8314, 8343, 8372, 8402, 8431, 8460, 8489, 8519, 8548, 8577, 8606, 8635, 8664, 8693, 8722, 8751, 8780, 8809, 8838, 8867, 8896, 8925, 8954, 8982,  /* 224 - 255*/
            9011, 9040, 9069, 9098, 9126, 9155, 9184, 9213, 9242, 9270, 9299, 9328, 9357, 9386, 9414, 9443, 9472, 9501, 9530, 9558, 9587, 9616, 9645, 9674, 9702, 9731, 9760, 9789, 9818, 9846, 9875, 9904,  /* 256 - 287*/
            9933, 9962, 9990, 10019, 10048, 10077, 10106, 10134, 10163, 10192, 10221, 10250, 10278, 10307, 10336, 10365, 10394, 10422, 10451, 10480, 10509, 10538, 10566, 10595, 10624, 10653, 10682, 10710, 10739, 10768, 10797, 10826,  /* 288 - 319*/
            10854, 10883, 10912, 10941, 10970, 10998, 11027, 11056, 11085, 11114, 11142, 11171, 11200, 11229, 11258, 11286, 11315, 11344, 11373, 11402, 11430, 11459, 11488, 11517, 11546, 11574, 11603, 11632, 11661, 11690, 11718, 11747,  /* 320 - 351*/
            11776, 11805, 11834, 11862, 11891, 11920, 11949, 11978, 12006, 12035, 12064, 12093, 12122, 12150, 12179, 12208, 12237, 12266, 12294, 12323, 12352, 12381, 12410, 12438, 12467, 12496, 12525, 12554, 12582, 12611, 12640, 12669,  /* 352 - 383*/
            12698, 12726, 12755, 12784, 12813, 12842, 12870, 12899, 12928, 12957, 12986, 13014, 13043, 13072, 13101, 13130, 13158, 13187, 13216, 13245, 13274, 13302, 13331, 13360, 13389, 13418, 13446, 13475, 13504, 13533, 13562, 13590,  /* 384 - 415*/
            13619, 13648, 13677, 13706, 13734, 13763, 13792, 13821, 13850, 13878, 13907, 13936, 13965, 13994, 14022, 14051, 14080, 14109, 14138, 14166, 14195, 14224, 14253, 14282, 14310, 14339, 14368, 14397, 14426, 14454, 14483, 14512,  /* 416 - 447*/
            14541, 14570, 14598, 14627, 14656, 14685, 14714, 14742, 14771, 14800, 14829, 14858, 14886, 14915, 14944, 14973, 15002, 15030, 15059, 15088, 15117, 15146, 15174, 15203, 15232, 15261, 15290, 15318, 15347, 15376, 15405, 15434,  /* 448 - 479*/
            15462, 15491, 15520, 15549, 15578, 15606, 15635, 15664, 15693, 15722, 15750, 15779, 15808, 15837, 15866, 15894, 15923, 15952, 15981, 16010, 16038, 16067, 16096, 16125, 16154, 16182, 16211, 16240, 16269, 16298, 16326, 16355,  /* 480 - 511*/
            16384, 16413, 16442, 16470, 16499, 16528, 16557, 16586, 16614, 16643, 16672, 16701, 16730, 16758, 16787, 16816, 16845, 16874, 16902, 16931, 16960, 16989, 17018, 17046, 17075, 17104, 17133, 17162, 17190, 17219, 17248, 17277,  /* 512 - 543*/
            17306, 17334, 17363, 17392, 17421, 17450, 17478, 17507, 17536, 17565, 17594, 17622, 17651, 17680, 17709, 17738, 17766, 17795, 17824, 17853, 17882, 17910, 17939, 17968, 17997, 18026, 18054, 18083, 18112, 18141, 18170, 18198,  /* 544 - 575*/
            18227, 18256, 18285, 18314, 18342, 18371, 18400, 18429, 18458, 18486, 18515, 18544, 18573, 18602, 18630, 18659, 18688, 18717, 18746, 18774, 18803, 18832, 18861, 18890, 18918, 18947, 18976, 19005, 19034, 19062, 19091, 19120,  /* 576 - 607*/
            19149, 19178, 19206, 19235, 19264, 19293, 19322, 19350, 19379, 19408, 19437, 19466, 19494, 19523, 19552, 19581, 19610, 19638, 19667, 19696, 19725, 19754, 19782, 19811, 19840, 19869, 19898, 19926, 19955, 19984, 20013, 20042,  /* 608 - 639*/
            20070, 20099, 20128, 20157, 20186, 20214, 20243, 20272, 20301, 20330, 20358, 20387, 20416, 20445, 20474, 20502, 20531, 20560, 20589, 20618, 20646, 20675, 20704, 20733, 20762, 20790, 20819, 20848, 20877, 20906, 20934, 20963,  /* 640 - 671*/
            20992, 21021, 21050, 21078, 21107, 21136, 21165, 21194, 21222, 21251, 21280, 21309, 21338, 21366, 21395, 21424, 21453, 21482, 21510, 21539, 21568, 21597, 21626, 21654, 21683, 21712, 21741, 21770, 21798, 21827, 21856, 21885,  /* 672 - 703*/
            21914, 21942, 21971, 22000, 22029, 22058, 22086, 22115, 22144, 22173, 22202, 22230, 22259, 22288, 22317, 22346, 22374, 22403, 22432, 22461, 22490, 22518, 22547, 22576, 22605, 22634, 22662, 22691, 22720, 22749, 22778, 22806,  /* 704 - 735*/
            22835, 22864, 22893, 22922, 22950, 22979, 23008, 23037, 23066, 23094, 23123, 23152, 23181, 23210, 23238, 23267, 23296, 23325, 23354, 23382, 23411, 23440, 23469, 23498, 23526, 23555, 23584, 23613, 23642, 23670, 23699, 23728,  /* 736 - 767*/
            23757, 23786, 23814, 23843, 23872, 23901, 23930, 23959, 23988, 24017, 24046, 24075, 24104, 24133, 24162, 24191, 24220, 24249, 24279, 24308, 24337, 24366, 24396, 24425, 24454, 24483, 24513, 24542, 24572, 24601, 24630, 24660,  /* 768 - 799*/
            24689, 24719, 24748, 24778, 24808, 24837, 24867, 24897, 24926, 24956, 24986, 25015, 25045, 25075, 25105, 25135, 25165, 25195, 25225, 25255, 25285, 25315, 25345, 25375, 25405, 25435, 25465, 25495, 25526, 25556, 25586, 25616,  /* 800 - 831*/
            25647, 25677, 25707, 25738, 25768, 25799, 25829, 25860, 25890, 25921, 25952, 25982, 26013, 26044, 26074, 26105, 26136, 26167, 26198, 26229, 26260, 26291, 26322, 26353, 26384, 26415, 26446, 26477, 26508, 26540, 26571, 26602,  /* 832 - 863*/
            26634, 26665, 26696, 26728, 26759, 26791, 26822, 26854, 26886, 26917, 26949, 26981, 27013, 27044, 27076, 27108, 27140, 27172, 27204, 27236, 27268, 27301, 27333, 27365, 27397, 27430, 27462, 27494, 27527, 27559, 27592, 27625,  /* 864 - 895*/
            27657, 27690, 27723, 27755, 27788, 27821, 27854, 27887, 27920, 27953, 27986, 28019, 28053, 28086, 28119, 28153, 28186, 28220, 28253, 28287, 28321, 28354, 28388, 28422, 28456, 28490, 28524, 28558, 28592, 28626, 28660, 28695,  /* 896 - 927*/
            28729, 28764, 28798, 28833, 28867, 28902, 28937, 28972, 29007, 29042, 29077, 29112, 29147, 29182, 29218, 29253, 29289, 29324, 29360, 29396, 29432, 29468, 29504, 29540, 29576, 29612, 29649, 29685, 29722, 29759, 29795, 29832,  /* 928 - 959*/
            29869, 29907, 29944, 29981, 30018, 30056, 30094, 30131, 30169, 30207, 30246, 30284, 30322, 30361, 30400, 30438, 30477, 30516, 30556, 30595, 30635, 30674, 30714, 30754, 30795, 30835, 30876, 30917, 30958, 30999, 31040, 31082,  /* 960 - 991*/
            31124, 31166, 31209, 31251, 31294, 31337, 31381, 31425, 31469, 31513, 31558, 31603, 31649, 31695, 31741, 31788, 31836, 31884, 31932, 31981, 32031, 32082, 32133, 32186, 32239, 32294, 32350, 32408, 32468, 32531, 32598, 32672,  /* 992 - 1023*/
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
            9000,
            /* nDetailSigmaVal */
            700,
            /* nDetailCoringPos */
            80,
            /* nDetailCoringNeg */
            50,
            /* nDetailGainPos */
            90,
            /* nDetailGainNeg */
            100,
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
        {100, 100, 100, 100, 100, 100, 100, 100, 95, 90, 90, 90, /*0 - 11*/},
        /* nHighlightSup[12] */
        {10, 10, 10, 10, 10, 10, 10, 10, 12, 14, 15, 15, /*0 - 11*/},
        /* nKMax[12] */
        {65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, /*0 - 11*/},
        /* nPreGamma[12] */
        {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, /*0 - 11*/},
        /* nPostGamma[12] */
        {42, 42, 42, 42, 42, 42, 43, 44, 45, 46, 48, 50, /*0 - 11*/},
        /* nExtraDgain[12] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 11*/},
        /* nRltmStrength[12] */
        {48, 45, 40, 36, 32, 32, 32, 32, 32, 32, 28, 24, /*0 - 11*/},
        /* nLog10Offset[12] */
        {96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, /*0 - 11*/},
        /* nContrastStrength[12] */
        {42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 38, 32, /*0 - 11*/},
        /* nBaseGain[12] */
        {64, 64, 72, 80, 96, 96, 96, 96, 112, 128, 128, 128, /*0 - 11*/},
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
                0, 96, 170, 237, 300, 360, 418, 474, 529, 582, 635, 686, 737, 787, 836, 884, 932, 980, 1027, 1073, 1119, 1165, 1210, 1255, 1299, 1343, 1387, 1431, 1474, 1517, 1559, 1602,  /* 0 - 31*/
                1644, 1686, 1728, 1769, 1810, 1851, 1892, 1933, 1973, 2014, 2054, 2094, 2133, 2173, 2212, 2252, 2291, 2330, 2368, 2407, 2446, 2484, 2522, 2561, 2599, 2637, 2674, 2712, 2750, 2787, 2824, 2861,  /* 32 - 63*/
                2899, 2936, 2973, 3009, 3046, 3083, 3119, 3156, 3192, 3228, 3264, 3300, 3336, 3372, 3408, 3444, 3479, 3515, 3550, 3586, 3621, 3656, 3691, 3726, 3761, 3796, 3831, 3866, 3901, 3935, 3970, 4004,  /* 64 - 95*/
                4039, 4073, 4108, 4142, 4176, 4210, 4244, 4278, 4312, 4346, 4380, 4414, 4447, 4481, 4515, 4548, 4582, 4615, 4649, 4682, 4715, 4749, 4782, 4815, 4848, 4881, 4914, 4947, 4980, 5013, 5045, 5078,  /* 96 - 127*/
                5111, 5143, 5176, 5209, 5241, 5274, 5306, 5338, 5371, 5403, 5435, 5467, 5500, 5532, 5564, 5596, 5628, 5660, 5692, 5724, 5755, 5787, 5819, 5851, 5882, 5914, 5946, 5977, 6009, 6040, 6072, 6103,  /* 128 - 159*/
                6134, 6166, 6197, 6228, 6260, 6291, 6322, 6353, 6384, 6415, 6446, 6477, 6508, 6539, 6570, 6601, 6632, 6663, 6694, 6724, 6755, 6786, 6816, 6847, 6878, 6908, 6939, 6969, 7000, 7030, 7061, 7091,  /* 160 - 191*/
                7121, 7152, 7182, 7212, 7242, 7273, 7303, 7333, 7363, 7393, 7423, 7453, 7483, 7513, 7543, 7573, 7603, 7633, 7663, 7693, 7723, 7753, 7782, 7812, 7842, 7871, 7901, 7931, 7960, 7990, 8020, 8049,  /* 192 - 223*/
                8079, 8108, 8138, 8167, 8196, 8226, 8255, 8285, 8314, 8343, 8372, 8402, 8431, 8460, 8489, 8519, 8548, 8577, 8606, 8635, 8664, 8693, 8722, 8751, 8780, 8809, 8838, 8867, 8896, 8925, 8954, 8982,  /* 224 - 255*/
                9011, 9040, 9069, 9098, 9126, 9155, 9184, 9213, 9242, 9270, 9299, 9328, 9357, 9386, 9414, 9443, 9472, 9501, 9530, 9558, 9587, 9616, 9645, 9674, 9702, 9731, 9760, 9789, 9818, 9846, 9875, 9904,  /* 256 - 287*/
                9933, 9962, 9990, 10019, 10048, 10077, 10106, 10134, 10163, 10192, 10221, 10250, 10278, 10307, 10336, 10365, 10394, 10422, 10451, 10480, 10509, 10538, 10566, 10595, 10624, 10653, 10682, 10710, 10739, 10768, 10797, 10826,  /* 288 - 319*/
                10854, 10883, 10912, 10941, 10970, 10998, 11027, 11056, 11085, 11114, 11142, 11171, 11200, 11229, 11258, 11286, 11315, 11344, 11373, 11402, 11430, 11459, 11488, 11517, 11546, 11574, 11603, 11632, 11661, 11690, 11718, 11747,  /* 320 - 351*/
                11776, 11805, 11834, 11862, 11891, 11920, 11949, 11978, 12006, 12035, 12064, 12093, 12122, 12150, 12179, 12208, 12237, 12266, 12294, 12323, 12352, 12381, 12410, 12438, 12467, 12496, 12525, 12554, 12582, 12611, 12640, 12669,  /* 352 - 383*/
                12698, 12726, 12755, 12784, 12813, 12842, 12870, 12899, 12928, 12957, 12986, 13014, 13043, 13072, 13101, 13130, 13158, 13187, 13216, 13245, 13274, 13302, 13331, 13360, 13389, 13418, 13446, 13475, 13504, 13533, 13562, 13590,  /* 384 - 415*/
                13619, 13648, 13677, 13706, 13734, 13763, 13792, 13821, 13850, 13878, 13907, 13936, 13965, 13994, 14022, 14051, 14080, 14109, 14138, 14166, 14195, 14224, 14253, 14282, 14310, 14339, 14368, 14397, 14426, 14454, 14483, 14512,  /* 416 - 447*/
                14541, 14570, 14598, 14627, 14656, 14685, 14714, 14742, 14771, 14800, 14829, 14858, 14886, 14915, 14944, 14973, 15002, 15030, 15059, 15088, 15117, 15146, 15174, 15203, 15232, 15261, 15290, 15318, 15347, 15376, 15405, 15434,  /* 448 - 479*/
                15462, 15491, 15520, 15549, 15578, 15606, 15635, 15664, 15693, 15722, 15750, 15779, 15808, 15837, 15866, 15894, 15923, 15952, 15981, 16010, 16038, 16067, 16096, 16125, 16154, 16182, 16211, 16240, 16269, 16298, 16326, 16355,  /* 480 - 511*/
                16384, 16413, 16442, 16470, 16499, 16528, 16557, 16586, 16614, 16643, 16672, 16701, 16730, 16758, 16787, 16816, 16845, 16874, 16902, 16931, 16960, 16989, 17018, 17046, 17075, 17104, 17133, 17162, 17190, 17219, 17248, 17277,  /* 512 - 543*/
                17306, 17334, 17363, 17392, 17421, 17450, 17478, 17507, 17536, 17565, 17594, 17622, 17651, 17680, 17709, 17738, 17766, 17795, 17824, 17853, 17882, 17910, 17939, 17968, 17997, 18026, 18054, 18083, 18112, 18141, 18170, 18198,  /* 544 - 575*/
                18227, 18256, 18285, 18314, 18342, 18371, 18400, 18429, 18458, 18486, 18515, 18544, 18573, 18602, 18630, 18659, 18688, 18717, 18746, 18774, 18803, 18832, 18861, 18890, 18918, 18947, 18976, 19005, 19034, 19062, 19091, 19120,  /* 576 - 607*/
                19149, 19178, 19206, 19235, 19264, 19293, 19322, 19350, 19379, 19408, 19437, 19466, 19494, 19523, 19552, 19581, 19610, 19638, 19667, 19696, 19725, 19754, 19782, 19811, 19840, 19869, 19898, 19926, 19955, 19984, 20013, 20042,  /* 608 - 639*/
                20070, 20099, 20128, 20157, 20186, 20214, 20243, 20272, 20301, 20330, 20358, 20387, 20416, 20445, 20474, 20502, 20531, 20560, 20589, 20618, 20646, 20675, 20704, 20733, 20762, 20790, 20819, 20848, 20877, 20906, 20934, 20963,  /* 640 - 671*/
                20992, 21021, 21050, 21078, 21107, 21136, 21165, 21194, 21222, 21251, 21280, 21309, 21338, 21366, 21395, 21424, 21453, 21482, 21510, 21539, 21568, 21597, 21626, 21654, 21683, 21712, 21741, 21770, 21798, 21827, 21856, 21885,  /* 672 - 703*/
                21914, 21942, 21971, 22000, 22029, 22058, 22086, 22115, 22144, 22173, 22202, 22230, 22259, 22288, 22317, 22346, 22374, 22403, 22432, 22461, 22490, 22518, 22547, 22576, 22605, 22634, 22662, 22691, 22720, 22749, 22778, 22806,  /* 704 - 735*/
                22835, 22864, 22893, 22922, 22950, 22979, 23008, 23037, 23066, 23094, 23123, 23152, 23181, 23210, 23238, 23267, 23296, 23325, 23354, 23382, 23411, 23440, 23469, 23498, 23526, 23555, 23584, 23613, 23642, 23670, 23699, 23728,  /* 736 - 767*/
                23757, 23786, 23814, 23843, 23872, 23901, 23930, 23959, 23988, 24017, 24046, 24075, 24104, 24133, 24162, 24191, 24220, 24249, 24279, 24308, 24337, 24366, 24396, 24425, 24454, 24483, 24513, 24542, 24572, 24601, 24630, 24660,  /* 768 - 799*/
                24689, 24719, 24748, 24778, 24808, 24837, 24867, 24897, 24926, 24956, 24986, 25015, 25045, 25075, 25105, 25135, 25165, 25195, 25225, 25255, 25285, 25315, 25345, 25375, 25405, 25435, 25465, 25495, 25526, 25556, 25586, 25616,  /* 800 - 831*/
                25647, 25677, 25707, 25738, 25768, 25799, 25829, 25860, 25890, 25921, 25952, 25982, 26013, 26044, 26074, 26105, 26136, 26167, 26198, 26229, 26260, 26291, 26322, 26353, 26384, 26415, 26446, 26477, 26508, 26540, 26571, 26602,  /* 832 - 863*/
                26634, 26665, 26696, 26728, 26759, 26791, 26822, 26854, 26886, 26917, 26949, 26981, 27013, 27044, 27076, 27108, 27140, 27172, 27204, 27236, 27268, 27301, 27333, 27365, 27397, 27430, 27462, 27494, 27527, 27559, 27592, 27625,  /* 864 - 895*/
                27657, 27690, 27723, 27755, 27788, 27821, 27854, 27887, 27920, 27953, 27986, 28019, 28053, 28086, 28119, 28153, 28186, 28220, 28253, 28287, 28321, 28354, 28388, 28422, 28456, 28490, 28524, 28558, 28592, 28626, 28660, 28695,  /* 896 - 927*/
                28729, 28764, 28798, 28833, 28867, 28902, 28937, 28972, 29007, 29042, 29077, 29112, 29147, 29182, 29218, 29253, 29289, 29324, 29360, 29396, 29432, 29468, 29504, 29540, 29576, 29612, 29649, 29685, 29722, 29759, 29795, 29832,  /* 928 - 959*/
                29869, 29907, 29944, 29981, 30018, 30056, 30094, 30131, 30169, 30207, 30246, 30284, 30322, 30361, 30400, 30438, 30477, 30516, 30556, 30595, 30635, 30674, 30714, 30754, 30795, 30835, 30876, 30917, 30958, 30999, 31040, 31082,  /* 960 - 991*/
                31124, 31166, 31209, 31251, 31294, 31337, 31381, 31425, 31469, 31513, 31558, 31603, 31649, 31695, 31741, 31788, 31836, 31884, 31932, 31981, 32031, 32082, 32133, 32186, 32239, 32294, 32350, 32408, 32468, 32531, 32598, 32672,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 96, 170, 237, 300, 360, 418, 474, 529, 582, 635, 686, 737, 787, 836, 884, 932, 980, 1027, 1073, 1119, 1165, 1210, 1255, 1299, 1343, 1387, 1431, 1474, 1517, 1559, 1602,  /* 0 - 31*/
                1644, 1686, 1728, 1769, 1810, 1851, 1892, 1933, 1973, 2014, 2054, 2094, 2133, 2173, 2212, 2252, 2291, 2330, 2368, 2407, 2446, 2484, 2522, 2561, 2599, 2637, 2674, 2712, 2750, 2787, 2824, 2861,  /* 32 - 63*/
                2899, 2936, 2973, 3009, 3046, 3083, 3119, 3156, 3192, 3228, 3264, 3300, 3336, 3372, 3408, 3444, 3479, 3515, 3550, 3586, 3621, 3656, 3691, 3726, 3761, 3796, 3831, 3866, 3901, 3935, 3970, 4004,  /* 64 - 95*/
                4039, 4073, 4108, 4142, 4176, 4210, 4244, 4278, 4312, 4346, 4380, 4414, 4447, 4481, 4515, 4548, 4582, 4615, 4649, 4682, 4715, 4749, 4782, 4815, 4848, 4881, 4914, 4947, 4980, 5013, 5045, 5078,  /* 96 - 127*/
                5111, 5143, 5176, 5209, 5241, 5274, 5306, 5338, 5371, 5403, 5435, 5467, 5500, 5532, 5564, 5596, 5628, 5660, 5692, 5724, 5755, 5787, 5819, 5851, 5882, 5914, 5946, 5977, 6009, 6040, 6072, 6103,  /* 128 - 159*/
                6134, 6166, 6197, 6228, 6260, 6291, 6322, 6353, 6384, 6415, 6446, 6477, 6508, 6539, 6570, 6601, 6632, 6663, 6694, 6724, 6755, 6786, 6816, 6847, 6878, 6908, 6939, 6969, 7000, 7030, 7061, 7091,  /* 160 - 191*/
                7121, 7152, 7182, 7212, 7242, 7273, 7303, 7333, 7363, 7393, 7423, 7453, 7483, 7513, 7543, 7573, 7603, 7633, 7663, 7693, 7723, 7753, 7782, 7812, 7842, 7871, 7901, 7931, 7960, 7990, 8020, 8049,  /* 192 - 223*/
                8079, 8108, 8138, 8167, 8196, 8226, 8255, 8285, 8314, 8343, 8372, 8402, 8431, 8460, 8489, 8519, 8548, 8577, 8606, 8635, 8664, 8693, 8722, 8751, 8780, 8809, 8838, 8867, 8896, 8925, 8954, 8982,  /* 224 - 255*/
                9011, 9040, 9069, 9098, 9126, 9155, 9184, 9213, 9242, 9270, 9299, 9328, 9357, 9386, 9414, 9443, 9472, 9501, 9530, 9558, 9587, 9616, 9645, 9674, 9702, 9731, 9760, 9789, 9818, 9846, 9875, 9904,  /* 256 - 287*/
                9933, 9962, 9990, 10019, 10048, 10077, 10106, 10134, 10163, 10192, 10221, 10250, 10278, 10307, 10336, 10365, 10394, 10422, 10451, 10480, 10509, 10538, 10566, 10595, 10624, 10653, 10682, 10710, 10739, 10768, 10797, 10826,  /* 288 - 319*/
                10854, 10883, 10912, 10941, 10970, 10998, 11027, 11056, 11085, 11114, 11142, 11171, 11200, 11229, 11258, 11286, 11315, 11344, 11373, 11402, 11430, 11459, 11488, 11517, 11546, 11574, 11603, 11632, 11661, 11690, 11718, 11747,  /* 320 - 351*/
                11776, 11805, 11834, 11862, 11891, 11920, 11949, 11978, 12006, 12035, 12064, 12093, 12122, 12150, 12179, 12208, 12237, 12266, 12294, 12323, 12352, 12381, 12410, 12438, 12467, 12496, 12525, 12554, 12582, 12611, 12640, 12669,  /* 352 - 383*/
                12698, 12726, 12755, 12784, 12813, 12842, 12870, 12899, 12928, 12957, 12986, 13014, 13043, 13072, 13101, 13130, 13158, 13187, 13216, 13245, 13274, 13302, 13331, 13360, 13389, 13418, 13446, 13475, 13504, 13533, 13562, 13590,  /* 384 - 415*/
                13619, 13648, 13677, 13706, 13734, 13763, 13792, 13821, 13850, 13878, 13907, 13936, 13965, 13994, 14022, 14051, 14080, 14109, 14138, 14166, 14195, 14224, 14253, 14282, 14310, 14339, 14368, 14397, 14426, 14454, 14483, 14512,  /* 416 - 447*/
                14541, 14570, 14598, 14627, 14656, 14685, 14714, 14742, 14771, 14800, 14829, 14858, 14886, 14915, 14944, 14973, 15002, 15030, 15059, 15088, 15117, 15146, 15174, 15203, 15232, 15261, 15290, 15318, 15347, 15376, 15405, 15434,  /* 448 - 479*/
                15462, 15491, 15520, 15549, 15578, 15606, 15635, 15664, 15693, 15722, 15750, 15779, 15808, 15837, 15866, 15894, 15923, 15952, 15981, 16010, 16038, 16067, 16096, 16125, 16154, 16182, 16211, 16240, 16269, 16298, 16326, 16355,  /* 480 - 511*/
                16384, 16413, 16442, 16470, 16499, 16528, 16557, 16586, 16614, 16643, 16672, 16701, 16730, 16758, 16787, 16816, 16845, 16874, 16902, 16931, 16960, 16989, 17018, 17046, 17075, 17104, 17133, 17162, 17190, 17219, 17248, 17277,  /* 512 - 543*/
                17306, 17334, 17363, 17392, 17421, 17450, 17478, 17507, 17536, 17565, 17594, 17622, 17651, 17680, 17709, 17738, 17766, 17795, 17824, 17853, 17882, 17910, 17939, 17968, 17997, 18026, 18054, 18083, 18112, 18141, 18170, 18198,  /* 544 - 575*/
                18227, 18256, 18285, 18314, 18342, 18371, 18400, 18429, 18458, 18486, 18515, 18544, 18573, 18602, 18630, 18659, 18688, 18717, 18746, 18774, 18803, 18832, 18861, 18890, 18918, 18947, 18976, 19005, 19034, 19062, 19091, 19120,  /* 576 - 607*/
                19149, 19178, 19206, 19235, 19264, 19293, 19322, 19350, 19379, 19408, 19437, 19466, 19494, 19523, 19552, 19581, 19610, 19638, 19667, 19696, 19725, 19754, 19782, 19811, 19840, 19869, 19898, 19926, 19955, 19984, 20013, 20042,  /* 608 - 639*/
                20070, 20099, 20128, 20157, 20186, 20214, 20243, 20272, 20301, 20330, 20358, 20387, 20416, 20445, 20474, 20502, 20531, 20560, 20589, 20618, 20646, 20675, 20704, 20733, 20762, 20790, 20819, 20848, 20877, 20906, 20934, 20963,  /* 640 - 671*/
                20992, 21021, 21050, 21078, 21107, 21136, 21165, 21194, 21222, 21251, 21280, 21309, 21338, 21366, 21395, 21424, 21453, 21482, 21510, 21539, 21568, 21597, 21626, 21654, 21683, 21712, 21741, 21770, 21798, 21827, 21856, 21885,  /* 672 - 703*/
                21914, 21942, 21971, 22000, 22029, 22058, 22086, 22115, 22144, 22173, 22202, 22230, 22259, 22288, 22317, 22346, 22374, 22403, 22432, 22461, 22490, 22518, 22547, 22576, 22605, 22634, 22662, 22691, 22720, 22749, 22778, 22806,  /* 704 - 735*/
                22835, 22864, 22893, 22922, 22950, 22979, 23008, 23037, 23066, 23094, 23123, 23152, 23181, 23210, 23238, 23267, 23296, 23325, 23354, 23382, 23411, 23440, 23469, 23498, 23526, 23555, 23584, 23613, 23642, 23670, 23699, 23728,  /* 736 - 767*/
                23757, 23786, 23814, 23843, 23872, 23901, 23930, 23959, 23988, 24017, 24046, 24075, 24104, 24133, 24162, 24191, 24220, 24249, 24279, 24308, 24337, 24366, 24396, 24425, 24454, 24483, 24513, 24542, 24572, 24601, 24630, 24660,  /* 768 - 799*/
                24689, 24719, 24748, 24778, 24808, 24837, 24867, 24897, 24926, 24956, 24986, 25015, 25045, 25075, 25105, 25135, 25165, 25195, 25225, 25255, 25285, 25315, 25345, 25375, 25405, 25435, 25465, 25495, 25526, 25556, 25586, 25616,  /* 800 - 831*/
                25647, 25677, 25707, 25738, 25768, 25799, 25829, 25860, 25890, 25921, 25952, 25982, 26013, 26044, 26074, 26105, 26136, 26167, 26198, 26229, 26260, 26291, 26322, 26353, 26384, 26415, 26446, 26477, 26508, 26540, 26571, 26602,  /* 832 - 863*/
                26634, 26665, 26696, 26728, 26759, 26791, 26822, 26854, 26886, 26917, 26949, 26981, 27013, 27044, 27076, 27108, 27140, 27172, 27204, 27236, 27268, 27301, 27333, 27365, 27397, 27430, 27462, 27494, 27527, 27559, 27592, 27625,  /* 864 - 895*/
                27657, 27690, 27723, 27755, 27788, 27821, 27854, 27887, 27920, 27953, 27986, 28019, 28053, 28086, 28119, 28153, 28186, 28220, 28253, 28287, 28321, 28354, 28388, 28422, 28456, 28490, 28524, 28558, 28592, 28626, 28660, 28695,  /* 896 - 927*/
                28729, 28764, 28798, 28833, 28867, 28902, 28937, 28972, 29007, 29042, 29077, 29112, 29147, 29182, 29218, 29253, 29289, 29324, 29360, 29396, 29432, 29468, 29504, 29540, 29576, 29612, 29649, 29685, 29722, 29759, 29795, 29832,  /* 928 - 959*/
                29869, 29907, 29944, 29981, 30018, 30056, 30094, 30131, 30169, 30207, 30246, 30284, 30322, 30361, 30400, 30438, 30477, 30516, 30556, 30595, 30635, 30674, 30714, 30754, 30795, 30835, 30876, 30917, 30958, 30999, 31040, 31082,  /* 960 - 991*/
                31124, 31166, 31209, 31251, 31294, 31337, 31381, 31425, 31469, 31513, 31558, 31603, 31649, 31695, 31741, 31788, 31836, 31884, 31932, 31981, 32031, 32082, 32133, 32186, 32239, 32294, 32350, 32408, 32468, 32531, 32598, 32672,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 75, 136, 194, 248, 301, 352, 403, 452, 500, 548, 595, 641, 687, 732, 777, 822, 866, 910, 953, 997, 1040, 1082, 1125, 1167, 1209, 1250, 1292, 1333, 1374, 1415, 1455,  /* 0 - 31*/
                1496, 1536, 1576, 1616, 1656, 1695, 1735, 1774, 1814, 1853, 1892, 1930, 1969, 2008, 2046, 2085, 2123, 2161, 2199, 2237, 2275, 2313, 2350, 2388, 2425, 2463, 2500, 2537, 2574, 2611, 2648, 2685,  /* 32 - 63*/
                2722, 2758, 2795, 2831, 2868, 2904, 2941, 2977, 3013, 3049, 3085, 3121, 3157, 3193, 3229, 3264, 3300, 3336, 3371, 3407, 3442, 3477, 3513, 3548, 3583, 3618, 3653, 3688, 3723, 3758, 3793, 3828,  /* 64 - 95*/
                3863, 3898, 3932, 3967, 4001, 4036, 4070, 4105, 4139, 4174, 4208, 4242, 4276, 4311, 4345, 4379, 4413, 4447, 4481, 4515, 4549, 4582, 4616, 4650, 4684, 4717, 4751, 4785, 4818, 4852, 4885, 4919,  /* 96 - 127*/
                4952, 4986, 5019, 5052, 5086, 5119, 5152, 5185, 5218, 5252, 5285, 5318, 5351, 5384, 5417, 5450, 5483, 5515, 5548, 5581, 5614, 5647, 5679, 5712, 5745, 5777, 5810, 5842, 5875, 5907, 5940, 5972,  /* 128 - 159*/
                6005, 6037, 6070, 6102, 6134, 6167, 6199, 6231, 6263, 6295, 6328, 6360, 6392, 6424, 6456, 6488, 6520, 6552, 6584, 6616, 6648, 6680, 6711, 6743, 6775, 6807, 6839, 6870, 6902, 6934, 6966, 6997,  /* 160 - 191*/
                7029, 7060, 7092, 7124, 7155, 7187, 7218, 7250, 7281, 7312, 7344, 7375, 7407, 7438, 7469, 7501, 7532, 7563, 7594, 7626, 7657, 7688, 7719, 7750, 7781, 7813, 7844, 7875, 7906, 7937, 7968, 7999,  /* 192 - 223*/
                8030, 8061, 8092, 8122, 8153, 8184, 8215, 8246, 8277, 8308, 8338, 8369, 8400, 8431, 8461, 8492, 8523, 8553, 8584, 8615, 8645, 8676, 8706, 8737, 8767, 8798, 8829, 8859, 8889, 8920, 8950, 8981,  /* 224 - 255*/
                9011, 9042, 9072, 9102, 9133, 9163, 9194, 9224, 9254, 9285, 9315, 9346, 9376, 9406, 9437, 9467, 9498, 9528, 9558, 9589, 9619, 9650, 9680, 9710, 9741, 9771, 9802, 9832, 9862, 9893, 9923, 9954,  /* 256 - 287*/
                9984, 10014, 10045, 10075, 10106, 10136, 10166, 10197, 10227, 10258, 10288, 10318, 10349, 10379, 10410, 10440, 10470, 10501, 10531, 10562, 10592, 10622, 10653, 10683, 10714, 10744, 10774, 10805, 10835, 10866, 10896, 10926,  /* 288 - 319*/
                10957, 10987, 11018, 11048, 11078, 11109, 11139, 11170, 11200, 11230, 11261, 11291, 11322, 11352, 11382, 11413, 11443, 11474, 11504, 11534, 11565, 11595, 11626, 11656, 11686, 11717, 11747, 11778, 11808, 11838, 11869, 11899,  /* 320 - 351*/
                11930, 11960, 11990, 12021, 12051, 12082, 12112, 12142, 12173, 12203, 12234, 12264, 12294, 12325, 12355, 12386, 12416, 12446, 12477, 12507, 12538, 12568, 12598, 12629, 12659, 12690, 12720, 12750, 12781, 12811, 12842, 12872,  /* 352 - 383*/
                12902, 12933, 12963, 12994, 13024, 13054, 13085, 13115, 13146, 13176, 13206, 13237, 13267, 13298, 13328, 13358, 13389, 13419, 13450, 13480, 13510, 13541, 13571, 13602, 13632, 13662, 13693, 13723, 13754, 13784, 13814, 13845,  /* 384 - 415*/
                13875, 13906, 13936, 13966, 13997, 14027, 14058, 14088, 14118, 14149, 14179, 14210, 14240, 14270, 14301, 14331, 14362, 14392, 14422, 14453, 14483, 14514, 14544, 14574, 14605, 14635, 14666, 14696, 14726, 14757, 14787, 14818,  /* 416 - 447*/
                14848, 14878, 14909, 14939, 14970, 15000, 15030, 15061, 15091, 15122, 15152, 15182, 15213, 15243, 15274, 15304, 15334, 15365, 15395, 15426, 15456, 15486, 15517, 15547, 15578, 15608, 15638, 15669, 15699, 15730, 15760, 15790,  /* 448 - 479*/
                15821, 15851, 15882, 15912, 15942, 15973, 16003, 16034, 16064, 16094, 16125, 16155, 16186, 16216, 16246, 16277, 16307, 16338, 16368, 16398, 16429, 16459, 16490, 16520, 16550, 16581, 16611, 16642, 16672, 16702, 16733, 16763,  /* 480 - 511*/
                16794, 16824, 16854, 16885, 16915, 16946, 16976, 17006, 17037, 17067, 17098, 17128, 17158, 17189, 17219, 17250, 17280, 17310, 17341, 17371, 17402, 17432, 17462, 17493, 17523, 17554, 17584, 17614, 17645, 17675, 17706, 17736,  /* 512 - 543*/
                17766, 17797, 17827, 17858, 17888, 17918, 17949, 17979, 18010, 18040, 18070, 18101, 18131, 18162, 18192, 18222, 18253, 18283, 18314, 18344, 18374, 18405, 18435, 18466, 18496, 18526, 18557, 18587, 18618, 18648, 18678, 18709,  /* 544 - 575*/
                18739, 18770, 18800, 18830, 18861, 18891, 18922, 18952, 18982, 19013, 19043, 19074, 19104, 19134, 19165, 19195, 19226, 19256, 19286, 19317, 19347, 19378, 19408, 19438, 19469, 19499, 19530, 19560, 19590, 19621, 19651, 19682,  /* 576 - 607*/
                19712, 19742, 19773, 19803, 19834, 19864, 19894, 19925, 19955, 19986, 20016, 20046, 20077, 20107, 20138, 20168, 20198, 20229, 20259, 20290, 20320, 20350, 20381, 20411, 20442, 20472, 20502, 20533, 20563, 20594, 20624, 20654,  /* 608 - 639*/
                20685, 20715, 20746, 20776, 20806, 20837, 20867, 20898, 20928, 20958, 20989, 21019, 21050, 21080, 21110, 21141, 21171, 21202, 21232, 21262, 21293, 21323, 21354, 21384, 21414, 21445, 21475, 21506, 21536, 21566, 21597, 21627,  /* 640 - 671*/
                21658, 21688, 21718, 21749, 21779, 21810, 21840, 21870, 21901, 21931, 21962, 21992, 22022, 22053, 22083, 22114, 22144, 22174, 22205, 22235, 22266, 22296, 22326, 22357, 22387, 22418, 22448, 22478, 22509, 22539, 22570, 22600,  /* 672 - 703*/
                22630, 22661, 22691, 22722, 22752, 22782, 22813, 22843, 22874, 22904, 22934, 22965, 22995, 23026, 23056, 23086, 23117, 23147, 23178, 23208, 23238, 23269, 23299, 23330, 23360, 23390, 23421, 23451, 23482, 23512, 23542, 23573,  /* 704 - 735*/
                23603, 23634, 23664, 23694, 23725, 23755, 23786, 23816, 23846, 23877, 23907, 23938, 23968, 23998, 24029, 24059, 24090, 24120, 24150, 24181, 24211, 24242, 24272, 24302, 24333, 24363, 24394, 24424, 24454, 24485, 24515, 24546,  /* 736 - 767*/
                24576, 24606, 24637, 24667, 24698, 24728, 24759, 24789, 24819, 24850, 24880, 24911, 24941, 24972, 25002, 25033, 25063, 25094, 25124, 25155, 25185, 25216, 25246, 25277, 25307, 25338, 25368, 25399, 25430, 25460, 25491, 25521,  /* 768 - 799*/
                25552, 25583, 25613, 25644, 25674, 25705, 25736, 25766, 25797, 25828, 25858, 25889, 25920, 25950, 25981, 26012, 26043, 26073, 26104, 26135, 26165, 26196, 26227, 26258, 26289, 26319, 26350, 26381, 26412, 26443, 26473, 26504,  /* 800 - 831*/
                26535, 26566, 26597, 26628, 26658, 26689, 26720, 26751, 26782, 26813, 26844, 26875, 26906, 26937, 26968, 26999, 27029, 27060, 27091, 27122, 27153, 27184, 27216, 27247, 27278, 27309, 27340, 27371, 27402, 27433, 27464, 27495,  /* 832 - 863*/
                27526, 27557, 27589, 27620, 27651, 27682, 27713, 27744, 27776, 27807, 27838, 27869, 27900, 27932, 27963, 27994, 28026, 28057, 28088, 28119, 28151, 28182, 28213, 28245, 28276, 28308, 28339, 28370, 28402, 28433, 28465, 28496,  /* 864 - 895*/
                28528, 28559, 28591, 28622, 28654, 28685, 28717, 28748, 28780, 28811, 28843, 28875, 28906, 28938, 28969, 29001, 29033, 29064, 29096, 29128, 29160, 29191, 29223, 29255, 29287, 29318, 29350, 29382, 29414, 29446, 29478, 29510,  /* 896 - 927*/
                29542, 29574, 29605, 29637, 29669, 29701, 29733, 29766, 29798, 29830, 29862, 29894, 29926, 29958, 29990, 30022, 30055, 30087, 30119, 30151, 30184, 30216, 30248, 30281, 30313, 30346, 30378, 30410, 30443, 30475, 30508, 30540,  /* 928 - 959*/
                30573, 30606, 30638, 30671, 30704, 30736, 30769, 30802, 30835, 30867, 30900, 30933, 30966, 30999, 31032, 31065, 31098, 31131, 31164, 31197, 31230, 31264, 31297, 31330, 31364, 31397, 31430, 31464, 31497, 31531, 31564, 31598,  /* 960 - 991*/
                31632, 31666, 31699, 31733, 31767, 31801, 31835, 31869, 31904, 31938, 31972, 32006, 32041, 32076, 32110, 32145, 32180, 32215, 32250, 32285, 32321, 32356, 32392, 32428, 32464, 32500, 32536, 32573, 32610, 32648, 32686, 32726,  /* 992 - 1023*/
                32768, /*1024 - 1024*/
            },
            {
                0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512, 544, 576, 608, 640, 672, 704, 736, 768, 800, 832, 864, 896, 928, 960, 992,  /* 0 - 31*/
                1024, 1056, 1088, 1120, 1152, 1184, 1216, 1248, 1280, 1312, 1344, 1376, 1408, 1440, 1472, 1504, 1536, 1568, 1600, 1632, 1664, 1696, 1728, 1760, 1792, 1824, 1856, 1888, 1920, 1952, 1984, 2016,  /* 32 - 63*/
                2048, 2080, 2112, 2144, 2176, 2208, 2240, 2272, 2304, 2336, 2368, 2400, 2432, 2464, 2496, 2528, 2560, 2592, 2624, 2656, 2688, 2720, 2752, 2784, 2816, 2848, 2880, 2912, 2944, 2976, 3008, 3040,  /* 64 - 95*/
                3072, 3104, 3136, 3168, 3200, 3232, 3264, 3296, 3328, 3360, 3392, 3424, 3456, 3488, 3520, 3552, 3584, 3616, 3648, 3680, 3712, 3744, 3776, 3808, 3840, 3872, 3904, 3936, 3968, 4000, 4032, 4064,  /* 96 - 127*/
                4096, 4128, 4160, 4192, 4224, 4256, 4288, 4320, 4352, 4384, 4416, 4448, 4480, 4512, 4544, 4576, 4608, 4640, 4672, 4704, 4736, 4768, 4800, 4832, 4864, 4896, 4928, 4960, 4992, 5024, 5056, 5088,  /* 128 - 159*/
                5120, 5152, 5184, 5216, 5248, 5280, 5312, 5344, 5376, 5408, 5440, 5472, 5504, 5536, 5568, 5600, 5632, 5664, 5696, 5728, 5760, 5792, 5824, 5856, 5888, 5920, 5952, 5984, 6016, 6048, 6080, 6112,  /* 160 - 191*/
                6144, 6176, 6208, 6240, 6272, 6304, 6336, 6368, 6400, 6432, 6464, 6496, 6528, 6560, 6592, 6624, 6656, 6688, 6720, 6752, 6784, 6816, 6848, 6880, 6912, 6944, 6976, 7008, 7040, 7072, 7104, 7136,  /* 192 - 223*/
                7168, 7200, 7232, 7264, 7296, 7328, 7360, 7392, 7424, 7456, 7488, 7520, 7552, 7584, 7616, 7648, 7680, 7712, 7744, 7776, 7808, 7840, 7872, 7904, 7936, 7968, 8000, 8032, 8064, 8096, 8128, 8160,  /* 224 - 255*/
                8192, 8224, 8256, 8288, 8320, 8352, 8384, 8416, 8448, 8480, 8512, 8544, 8576, 8608, 8640, 8672, 8704, 8736, 8768, 8800, 8832, 8864, 8896, 8928, 8960, 8992, 9024, 9056, 9088, 9120, 9152, 9184,  /* 256 - 287*/
                9216, 9248, 9280, 9312, 9344, 9376, 9408, 9440, 9472, 9504, 9536, 9568, 9600, 9632, 9664, 9696, 9728, 9760, 9792, 9824, 9856, 9888, 9920, 9952, 9984, 10016, 10048, 10080, 10112, 10144, 10176, 10208,  /* 288 - 319*/
                10240, 10272, 10304, 10336, 10368, 10400, 10432, 10464, 10496, 10528, 10560, 10592, 10624, 10656, 10688, 10720, 10752, 10784, 10816, 10848, 10880, 10912, 10944, 10976, 11008, 11040, 11072, 11104, 11136, 11168, 11200, 11232,  /* 320 - 351*/
                11264, 11296, 11328, 11360, 11392, 11424, 11456, 11488, 11520, 11552, 11584, 11616, 11648, 11680, 11712, 11744, 11776, 11808, 11840, 11872, 11904, 11936, 11968, 12000, 12032, 12064, 12096, 12128, 12160, 12192, 12224, 12256,  /* 352 - 383*/
                12288, 12320, 12352, 12384, 12416, 12448, 12480, 12512, 12544, 12576, 12608, 12640, 12672, 12704, 12736, 12768, 12800, 12832, 12864, 12896, 12928, 12960, 12992, 13024, 13056, 13088, 13120, 13152, 13184, 13216, 13248, 13280,  /* 384 - 415*/
                13312, 13344, 13376, 13408, 13440, 13472, 13504, 13536, 13568, 13600, 13632, 13664, 13696, 13728, 13760, 13792, 13824, 13856, 13888, 13920, 13952, 13984, 14016, 14048, 14080, 14112, 14144, 14176, 14208, 14240, 14272, 14304,  /* 416 - 447*/
                14336, 14368, 14400, 14432, 14464, 14496, 14528, 14560, 14592, 14624, 14656, 14688, 14720, 14752, 14784, 14816, 14848, 14880, 14912, 14944, 14976, 15008, 15040, 15072, 15104, 15136, 15168, 15200, 15232, 15264, 15296, 15328,  /* 448 - 479*/
                15360, 15392, 15424, 15456, 15488, 15520, 15552, 15584, 15616, 15648, 15680, 15712, 15744, 15776, 15808, 15840, 15872, 15904, 15936, 15968, 16000, 16032, 16064, 16096, 16128, 16160, 16192, 16224, 16256, 16288, 16320, 16352,  /* 480 - 511*/
                16384, 16416, 16448, 16480, 16512, 16544, 16576, 16608, 16640, 16672, 16704, 16736, 16768, 16800, 16832, 16864, 16896, 16928, 16960, 16992, 17024, 17056, 17088, 17120, 17152, 17184, 17216, 17248, 17280, 17312, 17344, 17376,  /* 512 - 543*/
                17408, 17440, 17472, 17504, 17536, 17568, 17600, 17632, 17664, 17696, 17728, 17760, 17792, 17824, 17856, 17888, 17920, 17952, 17984, 18016, 18048, 18080, 18112, 18144, 18176, 18208, 18240, 18272, 18304, 18336, 18368, 18400,  /* 544 - 575*/
                18432, 18464, 18496, 18528, 18560, 18592, 18624, 18656, 18688, 18720, 18752, 18784, 18816, 18848, 18880, 18912, 18944, 18976, 19008, 19040, 19072, 19104, 19136, 19168, 19200, 19232, 19264, 19296, 19328, 19360, 19392, 19424,  /* 576 - 607*/
                19456, 19488, 19520, 19552, 19584, 19616, 19648, 19680, 19712, 19744, 19776, 19808, 19840, 19872, 19904, 19936, 19968, 20000, 20032, 20064, 20096, 20128, 20160, 20192, 20224, 20256, 20288, 20320, 20352, 20384, 20416, 20448,  /* 608 - 639*/
                20480, 20512, 20544, 20576, 20608, 20640, 20672, 20704, 20736, 20768, 20800, 20832, 20864, 20896, 20928, 20960, 20992, 21024, 21056, 21088, 21120, 21152, 21184, 21216, 21248, 21280, 21312, 21344, 21376, 21408, 21440, 21472,  /* 640 - 671*/
                21504, 21536, 21568, 21600, 21632, 21664, 21696, 21728, 21760, 21792, 21824, 21856, 21888, 21920, 21952, 21984, 22016, 22048, 22080, 22112, 22144, 22176, 22208, 22240, 22272, 22304, 22336, 22368, 22400, 22432, 22464, 22496,  /* 672 - 703*/
                22528, 22560, 22592, 22624, 22656, 22688, 22720, 22752, 22784, 22816, 22848, 22880, 22912, 22944, 22976, 23008, 23040, 23072, 23104, 23136, 23168, 23200, 23232, 23264, 23296, 23328, 23360, 23392, 23424, 23456, 23488, 23520,  /* 704 - 735*/
                23552, 23584, 23616, 23648, 23680, 23712, 23744, 23776, 23808, 23840, 23872, 23904, 23936, 23968, 24000, 24032, 24064, 24096, 24128, 24160, 24192, 24224, 24256, 24288, 24320, 24352, 24384, 24416, 24448, 24480, 24512, 24544,  /* 736 - 767*/
                24576, 24608, 24640, 24672, 24704, 24736, 24768, 24800, 24832, 24864, 24896, 24928, 24960, 24992, 25024, 25056, 25088, 25120, 25152, 25184, 25216, 25248, 25280, 25312, 25344, 25376, 25408, 25440, 25472, 25504, 25536, 25568,  /* 768 - 799*/
                25600, 25632, 25664, 25696, 25728, 25760, 25792, 25824, 25856, 25888, 25920, 25952, 25984, 26016, 26048, 26080, 26112, 26144, 26176, 26208, 26240, 26272, 26304, 26336, 26368, 26400, 26432, 26464, 26496, 26528, 26560, 26592,  /* 800 - 831*/
                26624, 26656, 26688, 26720, 26752, 26784, 26816, 26848, 26880, 26912, 26944, 26976, 27008, 27040, 27072, 27104, 27136, 27168, 27200, 27232, 27264, 27296, 27328, 27360, 27392, 27424, 27456, 27488, 27520, 27552, 27584, 27616,  /* 832 - 863*/
                27648, 27680, 27712, 27744, 27776, 27808, 27840, 27872, 27904, 27936, 27968, 28000, 28032, 28064, 28096, 28128, 28160, 28192, 28224, 28256, 28288, 28320, 28352, 28384, 28416, 28448, 28480, 28512, 28544, 28576, 28608, 28640,  /* 864 - 895*/
                28672, 28704, 28736, 28768, 28800, 28832, 28864, 28896, 28928, 28960, 28992, 29024, 29056, 29088, 29120, 29152, 29184, 29216, 29248, 29280, 29312, 29344, 29376, 29408, 29440, 29472, 29504, 29536, 29568, 29600, 29632, 29664,  /* 896 - 927*/
                29696, 29728, 29760, 29792, 29824, 29856, 29888, 29920, 29952, 29984, 30016, 30048, 30080, 30112, 30144, 30176, 30208, 30240, 30272, 30304, 30336, 30368, 30400, 30432, 30464, 30496, 30528, 30560, 30592, 30624, 30656, 30688,  /* 928 - 959*/
                30720, 30752, 30784, 30816, 30848, 30880, 30912, 30944, 30976, 31008, 31040, 31072, 31104, 31136, 31168, 31200, 31232, 31264, 31296, 31328, 31360, 31392, 31424, 31456, 31488, 31520, 31552, 31584, 31616, 31648, 31680, 31712,  /* 960 - 991*/
                31744, 31776, 31808, 31840, 31872, 31904, 31936, 31968, 32000, 32032, 32064, 32096, 32128, 32160, 32192, 32224, 32256, 32288, 32320, 32352, 32384, 32416, 32448, 32480, 32512, 32544, 32576, 32608, 32640, 32672, 32704, 32736,  /* 992 - 1023*/
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                80,
                /* nDetailCoringNeg */
                50,
                /* nDetailGainPos */
                90,
                /* nDetailGainNeg */
                120,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                80,
                /* nDetailCoringNeg */
                50,
                /* nDetailGainPos */
                90,
                /* nDetailGainNeg */
                120,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                80,
                /* nDetailCoringNeg */
                50,
                /* nDetailGainPos */
                85,
                /* nDetailGainNeg */
                115,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                90,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                85,
                /* nDetailGainNeg */
                115,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                80,
                /* nDetailGainNeg */
                110,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                80,
                /* nDetailGainNeg */
                110,
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
                9000,
                /* nDetailSigmaVal */
                500,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                100,
                /* nDetailCoringNeg */
                60,
                /* nDetailGainPos */
                80,
                /* nDetailGainNeg */
                110,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                120,
                /* nDetailCoringNeg */
                70,
                /* nDetailGainPos */
                80,
                /* nDetailGainNeg */
                110,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                150,
                /* nDetailCoringNeg */
                75,
                /* nDetailGainPos */
                80,
                /* nDetailGainNeg */
                110,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                180,
                /* nDetailCoringNeg */
                110,
                /* nDetailGainPos */
                80,
                /* nDetailGainNeg */
                110,
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
                9000,
                /* nDetailSigmaVal */
                500,
                /* nDetailCoringPos */
                200,
                /* nDetailCoringNeg */
                120,
                /* nDetailGainPos */
                80,
                /* nDetailGainNeg */
                110,
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

const static AX_ISP_IQ_DEMOSAIC_PARAM_T demosaic_param_sdr_qs = {
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

const static AX_ISP_IQ_GIC_PARAM_T gic_param_sdr_qs = {
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

const static AX_ISP_IQ_FCC_PARAM_T fcc_param_sdr_qs = {
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

const static AX_ISP_IQ_DEPURPLE_PARAM_T depurple_param_sdr_qs = {
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

const static AX_ISP_IQ_CC_PARAM_T cc_param_sdr_qs = {
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
        0,
        /* nCcmHue */
        0,
        /* nCcmMatrix[6] */
        {-248, -19, -57, -29, -6, -156, /*0 - 5*/},
        /* nXcmCtrlLevel[16] */
        {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
        /* nXcmSat[16] */
        {-15, -10, -5, -5, -15, -15, -12, -5, -5, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
        /* nXcmHue[16] */
        {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
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
                {1024, 16384, 165888, 524288, /*0 - 3*/},
                {1024, 16384, 165888, 524288, /*0 - 3*/},
                {1024, 16384, 165888, 524288, /*0 - 3*/},
                {1024, 16384, 165888, 524288, /*0 - 3*/},
                {1024, 16384, 165888, 524288, /*0 - 3*/},
                {1024, 16384, 165888, 524288, /*0 - 3*/},
                {1024, 16384, 165888, 524288, /*0 - 3*/},
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
                {-10, -15, -20, -20, /*0 - 3*/},
                {-10, -15, -15, -15, /*0 - 3*/},
                {0, -2, -4, -5, /*0 - 3*/},
                {0, 0, 0, 0, /*0 - 3*/},
                {5, 2, 0, 0, /*0 - 3*/},
                {5, 2, 0, 0, /*0 - 3*/},
                {3, 1, 0, 0, /*0 - 3*/},
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
                    {-257, -39, -94, -16, 20, -406, /*0 - 5*/},
                    {-257, -39, -94, -16, 20, -406, /*0 - 5*/},
                    {-257, -39, -94, -16, 20, -406, /*0 - 5*/},
                    {-257, -39, -94, -16, 20, -406, /*0 - 5*/},
                },
                /* nCcmMatrix 1 */
                {
                    {-271, -17, -73, -13, 2, -262, /*0 - 5*/},
                    {-271, -17, -73, -13, 2, -262, /*0 - 5*/},
                    {-271, -17, -73, -13, 2, -262, /*0 - 5*/},
                    {-271, -17, -73, -13, 2, -262, /*0 - 5*/},
                },
                /* nCcmMatrix 2 */
                {
                    {-227, -26, -100, -50, 10, -194, /*0 - 5*/},
                    {-227, -26, -100, -50, 10, -194, /*0 - 5*/},
                    {-227, -26, -100, -50, 10, -194, /*0 - 5*/},
                    {-227, -26, -100, -50, 10, -194, /*0 - 5*/},
                },
                /* nCcmMatrix 3 */
                {
                    {-217, -19, -80, -44, -2, -156, /*0 - 5*/},
                    {-217, -19, -80, -44, -2, -156, /*0 - 5*/},
                    {-217, -19, -80, -44, -2, -156, /*0 - 5*/},
                    {-217, -19, -80, -44, -2, -156, /*0 - 5*/},
                },
                /* nCcmMatrix 4 */
                {
                    {-248, -19, -57, -29, -6, -156, /*0 - 5*/},
                    {-248, -19, -57, -29, -6, -156, /*0 - 5*/},
                    {-248, -19, -57, -29, -6, -156, /*0 - 5*/},
                    {-248, -19, -57, -29, -6, -156, /*0 - 5*/},
                },
                /* nCcmMatrix 5 */
                {
                    {-280, 20, -49, -38, 8, -159, /*0 - 5*/},
                    {-280, 20, -49, -38, 8, -159, /*0 - 5*/},
                    {-280, 20, -49, -38, 8, -159, /*0 - 5*/},
                    {-280, 20, -49, -38, 8, -159, /*0 - 5*/},
                },
                /* nCcmMatrix 6 */
                {
                    {-310, 25, -35, -40, 8, -154, /*0 - 5*/},
                    {-310, 25, -35, -40, 8, -154, /*0 - 5*/},
                    {-310, 25, -35, -40, 8, -154, /*0 - 5*/},
                    {-310, 25, -35, -40, 8, -154, /*0 - 5*/},
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
                    {-20, -20, -20, -20, -10, -10, -5, 0, 0, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -15, -15, -15, -10, -10, -5, 0, 0, 0, 0, 0, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -10, -10, -10, -10, -5, 0, 0, 0, 0, 0, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -5, -10, -10, -5, 0, 0, 0, 0, 0, 0, 0, -10, -15, /*0 - 15*/},
                },
                /* nXcmSat 1 */
                {
                    {-15, -15, -15, -15, -10, -10, -5, 0, 0, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -10, -10, -10, -10, -5, 0, 0, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -5, -10, -10, -5, 0, 0, 0, 0, 0, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -5, -10, -10, -5, 0, 0, 0, 0, 0, 0, 0, -10, -15, /*0 - 15*/},
                },
                /* nXcmSat 2 */
                {
                    {-5, 0, 0, 0, -15, -10, -5, 0, 0, 10, 10, 10, 0, 0, 0, -5, /*0 - 15*/},
                    {-10, -5, -5, -5, -15, -15, -12, -10, -10, 5, 5, 5, 0, 0, -5, -10, /*0 - 15*/},
                    {-15, -10, -5, -10, -18, -15, -15, -15, -10, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -15, -12, -10, -18, -15, -15, -15, -5, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                },
                /* nXcmSat 3 */
                {
                    {-15, -10, 0, 0, -15, -10, -5, 0, 0, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -5, -15, -15, -12, -10, -10, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -10, -18, -15, -15, -15, -5, 15, 15, 15, 0, 0, -10, -15, /*0 - 15*/},
                    {-20, -20, -15, -10, -18, -15, -15, -15, 0, 20, 20, 20, 0, 0, -10, -15, /*0 - 15*/},
                },
                /* nXcmSat 4 */
                {
                    {-15, -10, -5, -5, -15, -10, -10, -10, 0, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -5, -15, -15, -12, -5, -5, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -10, -18, -15, -12, -10, -5, 20, 20, 20, 0, 0, -10, -15, /*0 - 15*/},
                    {-20, -20, -15, -10, -18, -15, -12, -10, 0, 20, 20, 20, 0, 0, -10, -15, /*0 - 15*/},
                },
                /* nXcmSat 5 */
                {
                    {-10, -10, -5, -5, -15, -10, -5, 0, 5, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -5, -15, -15, -12, -5, 0, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -10, -15, -15, -12, -10, -5, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
                    {-20, -20, -15, -10, -15, -15, -12, -10, 0, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                },
                /* nXcmSat 6 */
                {
                    {-15, -10, -5, -5, -15, -10, -5, 0, 0, 10, 10, 10, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -5, -5, -15, -15, -12, -5, 0, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -10, -10, -10, -15, -15, -12, -5, 0, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
                    {-15, -15, -10, -10, -15, -15, -12, -5, 0, 5, 5, 5, 0, 0, -10, -15, /*0 - 15*/},
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
                    {0, 0, 0, 0, 0, 0, 0, 0, -160, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, -160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, -160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 3 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, -160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, -160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, -160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 4 */
                {
                    {0, 0, 0, 0, 0, -100, -200, -100, 320, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 5 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 320, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                },
                /* nXcmHue 6 */
                {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
                    {0, 0, 0, 0, 0, 0, 0, 0, 160, 320, 320, 320, 0, 0, 0, 0, /*0 - 15*/},
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

const static AX_ISP_IQ_HS2DLUT_PARAM_T hs2dlut_param_sdr_qs = {
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

const static AX_ISP_IQ_GAMMA_PARAM_T gamma_param_sdr_qs = {
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

const static AX_ISP_IQ_DEHAZE_PARAM_T dehaze_param_sdr_qs = {
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
        128,
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
        32,
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
        {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, /*0 - 11*/},
        /* nGrayDcRatio[12] */
        {64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, /*0 - 11*/},
    },
};

const static AX_ISP_IQ_CSC_PARAM_T csc_param_sdr_qs = {
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

const static AX_ISP_IQ_CA_PARAM_T ca_param_sdr_qs = {
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

const static AX_ISP_IQ_YNR_PARAM_T ynr_param_sdr_qs = {
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
        {192, 256, 320, 320, /*0 - 3*/},
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
            {256, 360, 384, 384, /*0 - 3*/},
            {224, 300, 320, 320, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {192, 240, 256, 256, /*0 - 3*/},
            {160, 192, 256, 256, /*0 - 3*/},
            {128, 160, 192, 192, /*0 - 3*/},
            {96, 128, 160, 160, /*0 - 3*/},
        },
    },
};

const static AX_ISP_IQ_CNR_PARAM_T cnr_param_sdr_qs = {
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

const static AX_ISP_IQ_YUV3DNR_PARAM_T yuv3dnr_param_sdr_qs = {
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
            {64, 72, 80, 80, 80, 80, 72, 72, 64, 56, 48, 40, 40, 36, 32, 24, 20, /*0 - 16*/},
            {64, 72, 80, 80, 80, 80, 72, 72, 64, 56, 48, 40, 40, 36, 32, 24, 20, /*0 - 16*/},
        },
        /* nMotDetStrenLuma[2] */
        {128, -8, /*0 - 1*/},
        /* nMotDetStrenChrom[2] */
        {160, -16, /*0 - 1*/},
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
        {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
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
        0,
        /* nSf0DirStre */
        256,
        /* nSf0DetailStre */
        128,
        /* nSf0LumaNoiseLut[4][9] */
        {
            {56, 48, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
            {48, 40, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            {48, 40, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            {32, 28, 24, 20, 16, 12, 12, 12, 12, /*0 - 8*/},
        },
        /* nSf0LumaKernelSize[2] */
        {1, 0, /*0 - 1*/},
        /* nSf0LumaGauStre[2] */
        {32, 128, /*0 - 1*/},
        /* nSf0lumaBlendRatio[2][3] */
        {
            {128, 0, 128, /*0 - 2*/},
            {96, 0, 160, /*0 - 2*/},
        },
        /* nSf0ChromaAttenStre[2] */
        {1023, 1023, /*0 - 1*/},
        /* nSf0ChromaAttenLimit[2] */
        {200, 230, /*0 - 1*/},
        /* nSf0ChromaProtLut[2][9] */
        {
            {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            {80, 72, 64, 48, 48, 48, 48, 48, 48, /*0 - 8*/},
        },
        /* nSf1LumaMedEn */
        0,
        /* nSf1LumaGauStre[2] */
        {32, 0, /*0 - 1*/},
        /* nSf1LumaGauRatio[2] */
        {0, 0, /*0 - 1*/},
        /* nSf1LumaKernelSize */
        0,
        /* nSf1LumaNoiseLut[2][9] */
        {
            {48, 40, 32, 28, 24, 24, 24, 24, 24, /*0 - 8*/},
            {48, 40, 32, 24, 20, 16, 16, 16, 16, /*0 - 8*/},
        },
        /* nSf1LumaIdrThre[2] */
        {32, 64, /*0 - 1*/},
        /* nSf1LumaIdrGain[2] */
        {128, 128, /*0 - 1*/},
        /* nSf1LumaClipLevel[2] */
        {1023, 1023, /*0 - 1*/},
        /* nSf1LumaCoring[2] */
        {32, 16, /*0 - 1*/},
        /* nSf1LumaBlendRatio[2] */
        {24, 160, /*0 - 1*/},
        /* nSf1ChromaCoring */
        1023,
        /* nSf1ChromaBlendRatio */
        32,
        /* nSf2LumaGauStre[2] */
        {64, 64, /*0 - 1*/},
        /* nSf2LumaMedEn */
        0,
        /* nSf2KernelSize */
        0,
        /* nSf2NoiseLut[2][9] */
        {
            {64, 56, 48, 40, 40, 40, 36, 30, 20, /*0 - 8*/},
            {48, 40, 32, 24, 24, 24, 20, 16, 12, /*0 - 8*/},
        },
        /* nSf2BlendRatio[2][3] */
        {
            {192, 0, 64, /*0 - 2*/},
            {192, 0, 64, /*0 - 2*/},
        },
        /* nExtMaskStrenLuma */
        128,
        /* nExtMaskStrenChrom */
        128,
        /* nExtMaskStrenStatus */
        128,
        /* nExtMaskRatioLuma[2] */
        {256, 256, /*0 - 1*/},
        /* nExtMaskRatioChrom[2] */
        {256, 256, /*0 - 1*/},
        /* nExtMaskRatioStatus[2] */
        {256, 256, /*0 - 1*/},
        /* nY3dnrPos */
        0,
        /* nStaRefineErode */
        0,
        /* nSfGuideMapLuma[2] */
        {128, 256, /*0 - 1*/},
        /* nSfGuideMapChroma[2] */
        {256, 0, /*0 - 1*/},
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
                {32, 44, 56, 64, 64, 56, 48, 38, 28, 24, 20, 16, 16, 12, 8, 8, 4, /*0 - 16*/},
                {32, 44, 56, 64, 64, 56, 48, 38, 28, 24, 20, 16, 16, 12, 8, 8, 4, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 1 */
            {
                {40, 50, 60, 64, 64, 64, 56, 48, 36, 32, 28, 24, 24, 20, 16, 16, 8, /*0 - 16*/},
                {40, 50, 60, 64, 64, 64, 56, 48, 36, 32, 28, 24, 24, 20, 16, 16, 8, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 2 */
            {
                {48, 56, 64, 64, 64, 64, 64, 56, 48, 40, 32, 28, 24, 24, 20, 16, 16, /*0 - 16*/},
                {48, 56, 64, 64, 64, 64, 64, 56, 48, 40, 32, 28, 24, 24, 20, 16, 16, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 3 */
            {
                {64, 72, 80, 80, 80, 80, 72, 72, 64, 56, 48, 40, 40, 36, 32, 24, 20, /*0 - 16*/},
                {64, 72, 80, 80, 80, 80, 72, 72, 64, 56, 48, 40, 40, 36, 32, 24, 20, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 4 */
            {
                {72, 80, 80, 88, 96, 96, 88, 80, 72, 72, 72, 64, 56, 48, 40, 32, 24, /*0 - 16*/},
                {72, 80, 80, 88, 96, 96, 88, 80, 72, 72, 72, 64, 56, 48, 40, 32, 24, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 5 */
            {
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 6 */
            {
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 7 */
            {
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 8 */
            {
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 9 */
            {
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 10 */
            {
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
            },
            /* nMotDetNoiseLut 11 */
            {
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
                {80, 96, 100, 110, 110, 110, 100, 96, 80, 80, 80, 72, 64, 56, 48, 40, 32, /*0 - 16*/},
            },
        },
        /* nMotDetStrenLuma[12][2] */
        {
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
            {128, -8, /*0 - 1*/},
            {128, -8, /*0 - 1*/},
        },
        /* nMotDetStrenChrom[12][2] */
        {
            {96, 0, /*0 - 1*/},
            {96, -8, /*0 - 1*/},
            {128, -16, /*0 - 1*/},
            {160, -16, /*0 - 1*/},
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
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
            {128, 128, 128, 128, 128, 126, 120, 96, 64, 42, 32, 28, 24, 20, 16, 12, /*0 - 15*/},
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
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 4 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 5 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitLuma 6 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
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
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 4 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 5 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
            },
            /* nTfRatLimitChroma 6 */
            {
                {64, 255, /*0 - 1*/},
                {16, 255, /*0 - 1*/},
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
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nSf0DirStre[12] */
        {256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 11*/},
        /* nSf0DetailStre[12] */
        {128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, /*0 - 11*/},
        /* nSf0LumaNoiseLut[12][4][9] */
        {
            /* nSf0LumaNoiseLut 0 */
            {
                {56, 48, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {48, 40, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
                {48, 40, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
                {32, 28, 24, 20, 16, 12, 12, 12, 12, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 1 */
            {
                {56, 48, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {48, 40, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
                {48, 40, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
                {32, 28, 24, 20, 16, 12, 12, 12, 12, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 2 */
            {
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {56, 48, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 3 */
            {
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {56, 48, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 4 */
            {
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {56, 48, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 5 */
            {
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {56, 48, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 6 */
            {
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {56, 48, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 7 */
            {
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {56, 48, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 8 */
            {
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {64, 52, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
                {56, 48, 32, 24, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 9 */
            {
                {64, 56, 40, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 56, 40, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {48, 40, 28, 20, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 10 */
            {
                {64, 56, 40, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {64, 56, 40, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {48, 40, 28, 20, 16, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf0LumaNoiseLut 11 */
            {
                {96, 80, 64, 56, 48, 48, 48, 48, 48, /*0 - 8*/},
                {80, 64, 40, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
                {80, 64, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 48, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
        },
        /* nSf0LumaKernelSize[12][2] */
        {
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
            {1, 0, /*0 - 1*/},
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
                {128, 0, 128, /*0 - 2*/},
                {64, 0, 192, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 1 */
            {
                {144, 0, 112, /*0 - 2*/},
                {96, 0, 160, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 2 */
            {
                {160, 0, 96, /*0 - 2*/},
                {112, 0, 144, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 3 */
            {
                {176, 0, 80, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 4 */
            {
                {200, 0, 56, /*0 - 2*/},
                {144, 0, 112, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 5 */
            {
                {192, 0, 64, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 6 */
            {
                {192, 0, 64, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 7 */
            {
                {192, 0, 64, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 8 */
            {
                {192, 0, 64, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 9 */
            {
                {192, 0, 64, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 10 */
            {
                {192, 0, 64, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
            },
            /* nSf0lumaBlendRatio 11 */
            {
                {192, 0, 64, /*0 - 2*/},
                {128, 0, 128, /*0 - 2*/},
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
            {235, 255, /*0 - 1*/},
            {230, 250, /*0 - 1*/},
            {220, 240, /*0 - 1*/},
            {210, 230, /*0 - 1*/},
            {200, 230, /*0 - 1*/},
            {200, 230, /*0 - 1*/},
            {200, 230, /*0 - 1*/},
            {200, 230, /*0 - 1*/},
            {190, 220, /*0 - 1*/},
            {180, 210, /*0 - 1*/},
            {170, 200, /*0 - 1*/},
            {160, 200, /*0 - 1*/},
        },
        /* nSf0ChromaProtLut[12][2][9] */
        {
            /* nSf0ChromaProtLut 0 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {64, 48, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 1 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {64, 48, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 2 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {72, 64, 48, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 3 */
            {
                {96, 80, 64, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
                {80, 72, 64, 48, 48, 48, 48, 48, 48, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 4 */
            {
                {128, 128, 96, 80, 72, 64, 64, 64, 64, /*0 - 8*/},
                {128, 128, 96, 80, 72, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 5 */
            {
                {128, 128, 128, 128, 96, 64, 64, 64, 64, /*0 - 8*/},
                {128, 128, 128, 128, 96, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 6 */
            {
                {160, 128, 128, 128, 96, 96, 96, 96, 96, /*0 - 8*/},
                {128, 128, 128, 128, 96, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 7 */
            {
                {192, 160, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {128, 128, 96, 80, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 8 */
            {
                {192, 160, 128, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {128, 128, 96, 80, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 9 */
            {
                {256, 192, 160, 128, 128, 128, 128, 128, 128, /*0 - 8*/},
                {160, 144, 112, 96, 80, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 10 */
            {
                {384, 288, 192, 160, 128, 128, 128, 128, 128, /*0 - 8*/},
                {256, 192, 144, 96, 80, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf0ChromaProtLut 11 */
            {
                {384, 288, 192, 160, 128, 128, 128, 128, 128, /*0 - 8*/},
                {256, 192, 144, 96, 80, 64, 64, 64, 64, /*0 - 8*/},
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
        /* nSf1LumaKernelSize[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, /*0 - 11*/},
        /* nSf1LumaNoiseLut[12][2][9] */
        {
            /* nSf1LumaNoiseLut 0 */
            {
                {48, 40, 32, 28, 24, 24, 24, 24, 24, /*0 - 8*/},
                {48, 40, 32, 24, 20, 16, 16, 16, 16, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 1 */
            {
                {56, 48, 40, 32, 28, 28, 28, 28, 28, /*0 - 8*/},
                {56, 48, 40, 32, 24, 20, 20, 20, 20, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 2 */
            {
                {64, 56, 40, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 3 */
            {
                {64, 56, 40, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 32, 24, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 4 */
            {
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 30, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 5 */
            {
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 30, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 6 */
            {
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 30, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 7 */
            {
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 30, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 8 */
            {
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 30, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 9 */
            {
                {64, 56, 48, 40, 32, 32, 32, 32, 32, /*0 - 8*/},
                {64, 56, 40, 30, 24, 24, 24, 24, 24, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 10 */
            {
                {64, 56, 48, 48, 48, 48, 48, 44, 40, /*0 - 8*/},
                {64, 56, 40, 32, 32, 32, 32, 32, 32, /*0 - 8*/},
            },
            /* nSf1LumaNoiseLut 11 */
            {
                {96, 80, 72, 64, 56, 56, 56, 48, 48, /*0 - 8*/},
                {64, 56, 48, 48, 48, 48, 48, 44, 40, /*0 - 8*/}
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
            {24, 8, /*0 - 1*/},
            {0, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
            {16, 0, /*0 - 1*/},
        },
        /* nSf1LumaBlendRatio[12][2] */
        {
            {24, 192, /*0 - 1*/},
            {22, 160, /*0 - 1*/},
            {20, 128, /*0 - 1*/},
            {18, 128, /*0 - 1*/},
            {16, 128, /*0 - 1*/},
            {20, 128, /*0 - 1*/},
            {24, 128, /*0 - 1*/},
            {24, 128, /*0 - 1*/},
            {24, 128, /*0 - 1*/},
            {24, 128, /*0 - 1*/},
            {24, 128, /*0 - 1*/},
            {24, 128, /*0 - 1*/},
        },
        /* nSf1ChromaCoring[12] */
        {128, 192, 256, 384, 512, 1023, 1023, 1023, 1023, 1023, 1023, 1023, /*0 - 11*/},
        /* nSf1ChromaBlendRatio[12] */
        {128, 128, 96, 64, 32, 24, 24, 24, 24, 24, 24, 24, /*0 - 11*/},
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
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*0 - 11*/},
        /* nSf2NoiseLut[12][2][9] */
        {
            /* nSf2NoiseLut 0 */
            {
                {64, 56, 48, 40, 40, 40, 36, 30, 20, /*0 - 8*/},
                {48, 40, 32, 24, 24, 24, 20, 16, 12, /*0 - 8*/},
            },
            /* nSf2NoiseLut 1 */
            {
                {96, 80, 64, 48, 40, 40, 36, 30, 20, /*0 - 8*/},
                {80, 64, 48, 32, 24, 24, 20, 16, 12, /*0 - 8*/},
            },
            /* nSf2NoiseLut 2 */
            {
                {128, 96, 64, 48, 48, 48, 40, 32, 24, /*0 - 8*/},
                {96, 64, 48, 32, 32, 32, 28, 24, 16, /*0 - 8*/},
            },
            /* nSf2NoiseLut 3 */
            {
                {160, 128, 96, 64, 64, 64, 56, 48, 40, /*0 - 8*/},
                {128, 96, 64, 48, 48, 48, 44, 40, 32, /*0 - 8*/},
            },
            /* nSf2NoiseLut 4 */
            {
                {192, 144, 96, 96, 96, 96, 96, 80, 64, /*0 - 8*/},
                {128, 96, 64, 64, 64, 64, 64, 56, 48, /*0 - 8*/},
            },
            /* nSf2NoiseLut 5 */
            {
                {192, 160, 128, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {144, 112, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 6 */
            {
                {192, 160, 128, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {144, 112, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 7 */
            {
                {192, 160, 128, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {144, 112, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 8 */
            {
                {192, 160, 128, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {144, 112, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 9 */
            {
                {192, 160, 128, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {144, 112, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 10 */
            {
                {192, 160, 128, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {144, 112, 80, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
            /* nSf2NoiseLut 11 */
            {
                {256, 192, 144, 96, 96, 96, 96, 96, 96, /*0 - 8*/},
                {160, 128, 96, 64, 64, 64, 64, 64, 64, /*0 - 8*/},
            },
        },
        /* nSf2BlendRatio[12][2][3] */
        {
            /* nSf2BlendRatio 0 */
            {
                {192, 0, 64, /*0 - 2*/},
                {192, 0, 64, /*0 - 2*/},
            },
            /* nSf2BlendRatio 1 */
            {
                {192, 0, 64, /*0 - 2*/},
                {192, 0, 64, /*0 - 2*/},
            },
            /* nSf2BlendRatio 2 */
            {
                {224, 0, 32, /*0 - 2*/},
                {224, 0, 32, /*0 - 2*/},
            },
            /* nSf2BlendRatio 3 */
            {
                {240, 0, 16, /*0 - 2*/},
                {240, 0, 16, /*0 - 2*/},
            },
            /* nSf2BlendRatio 4 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
            },
            /* nSf2BlendRatio 5 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
            },
            /* nSf2BlendRatio 6 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
            },
            /* nSf2BlendRatio 7 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
            },
            /* nSf2BlendRatio 8 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
            },
            /* nSf2BlendRatio 9 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
            },
            /* nSf2BlendRatio 10 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
            },
            /* nSf2BlendRatio 11 */
            {
                {256, 0, 0, /*0 - 2*/},
                {256, 0, 0, /*0 - 2*/},
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
            {64, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
            {128, 256, /*0 - 1*/},
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
            {32, 0, /*0 - 1*/},
            {64, 0, /*0 - 1*/},
            {128, 0, /*0 - 1*/},
            {256, 0, /*0 - 1*/},
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

const static AX_ISP_IQ_SHARPEN_PARAM_T sharpen_param_sdr_qs = {
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
        {0, 5, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220, 240, 250, 255, 255, /*0 - 16*/},
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
        {6, 6, /*0 - 1*/},
        /* nOsMotionLimit[2] */
        {127, 96, /*0 - 1*/},
        /* nOsMotionGain[2] */
        {6, 5, /*0 - 1*/},
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
        {1, 1, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
        /* nColorCenter[8][3] */
        {
            {440, -171, -175, /*0 - 2*/},
            {748, -132, 96, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
            {0, 0, 0, /*0 - 2*/},
        },
        /* nColorRange[8][3] */
        {
            {384, 148, 172, /*0 - 2*/},
            {128, 48, 32, /*0 - 2*/},
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
            {6, 3, 3, /*0 - 2*/},
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
        {0, 1, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
        /* nColorMaskLimit[8] */
        {128, 128, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
    },
    /* tHighFreqControl */
    {
        /* nHighFreqEnable */
        0,
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
        {1, 1, 0, 0, /*0 - 3*/},
        /* nHighFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nHighFreqMotionLut[5] */
        {0, 0, 0, 0, -8, /*0 - 4*/},
        /* nHighFreqLumaLut[5] */
        {-64, -32, 0, 0, -32, /*0 - 4*/},
        /* nHighFreqTextureLut[9] */
        {-32, -16, 0, 16, 32, 48, 64, 64, 64, /*0 - 8*/},
        /* nHighFreqTextureLutMotion[9] */
        {-32, -16, 0, 16, 32, 48, 64, 64, 64, /*0 - 8*/},
        /* nHighFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, -8, -24, -48, -64, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
        /* nHighFreqOsLimit[2] */
        {32, 32, /*0 - 1*/},
        /* nHighFreqOsGain[2] */
        {4, 3, /*0 - 1*/},
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
        {1, 1, 0, 0, /*0 - 3*/},
        /* nMedFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nMedFreqMotionLut[5] */
        {0, 0, 0, -8, -16, /*0 - 4*/},
        /* nMedFreqLumaLut[5] */
        {-96, -48, 0, 0, -48, /*0 - 4*/},
        /* nMedFreqTextureLut[9] */
        {32, 96, 96, 80, 64, 48, 32, 16, 0, /*0 - 8*/},
        /* nMedFreqTextureLutMotion[9] */
        {-32, -16, -2, 12, 24, 36, 48, 48, 48, /*0 - 8*/},
        /* nMedFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, -8, -24, -32, -48, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
        /* nMedFreqOsLimit[2] */
        {32, 32, /*0 - 1*/},
        /* nMedFreqOsGain[2] */
        {4, 3, /*0 - 1*/},
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
        {1, 1, 0, 0, /*0 - 3*/},
        /* nDirFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nDirFreqMotionLut[5] */
        {0, 0, 0, 0, 0, /*0 - 4*/},
        /* nDirFreqLumaLut[5] */
        {-48, -24, 8, 8, -24, /*0 - 4*/},
        /* nDirFreqTextureLut[9] */
        {0, 0, 0, 8, 32, 72, 112, 127, 127, /*0 - 8*/},
        /* nDirFreqTextureLutMotion[9] */
        {0, 8, 32, 64, 96, 120, 127, 127, 127, /*0 - 8*/},
        /* nDirFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, -8, -24, -48, -64, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
            {0, 0, 0, 0, 0, /*0 - 4*/},
        },
        /* nDirFreqOsLimit[2] */
        {64, 64, /*0 - 1*/},
        /* nDirFreqOsGain[2] */
        {5, 3, /*0 - 1*/},
        /* nDirFreqDirEdgeLevelLut[9] */
        {32, 64, 192, 255, 255, 255, 255, 255, 255, /*0 - 8*/},
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
        {1, 1, 0, 0, /*0 - 3*/},
        /* nLowFreqClnpLutLevel[4] */
        {0, 0, 0, 0, /*0 - 3*/},
        /* nLowFreqMotionLut[5] */
        {0, 0, 0, -12, -24, /*0 - 4*/},
        /* nLowFreqLumaLut[5] */
        {-96, -48, 0, 0, -48, /*0 - 4*/},
        /* nLowFreqTextureLut[9] */
        {16, 64, 64, 56, 48, 40, 32, 24, 16, /*0 - 8*/},
        /* nLowFreqTextureLutMotion[9] */
        {-32, -16, -8, 0, 8, 16, 16, 16, 16, /*0 - 8*/},
        /* nLowFreqClnpLut[4][5] */
        {
            {0, 8, 24, 48, 64, /*0 - 4*/},
            {0, -8, -24, -48, -64, /*0 - 4*/},
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
        {48, 32, /*0 - 1*/},
        /* nHighFreqGainLimit[2] */
        {0, 128, /*0 - 1*/},
        /* nHighFreqCorBaseGain */
        1,
        /* nHighFreqCorSlope */
        8,
        /* nHighFreqCorOffset */
        4,
        /* nHighFreqLimit[2] */
        {128, 128, /*0 - 1*/},
        /* nMedFreqLogGain[2] */
        {48, 32, /*0 - 1*/},
        /* nMedFreqGainLimit[2] */
        {0, 128, /*0 - 1*/},
        /* nMedFreqCorBaseGain */
        2,
        /* nMedFreqCorSlope */
        12,
        /* nMedFreqCorOffset */
        12,
        /* nMedFreqLimit[2] */
        {128, 128, /*0 - 1*/},
        /* nDirFreqLogGain[2] */
        {48, 32, /*0 - 1*/},
        /* nDirFreqGainLimit[2] */
        {0, 128, /*0 - 1*/},
        /* nDirFreqCorBaseGain */
        4,
        /* nDirFreqCorSlope */
        8,
        /* nDirFreqCorOffset */
        8,
        /* nDirFreqLimit[2] */
        {256, 256, /*0 - 1*/},
        /* nLowFreqLogGain[2] */
        {48, 32, /*0 - 1*/},
        /* nLowFreqGainLimit[2] */
        {0, 128, /*0 - 1*/},
        /* nLowFreqCorBaseGain */
        1,
        /* nLowFreqCorSlope */
        12,
        /* nLowFreqCorOffset */
        16,
        /* nLowFreqLimit[2] */
        {96, 96, /*0 - 1*/},
        /* nShpHpfBsigma[3] */
        {16, 16, 16, /*0 - 2*/},
        /* nShpHpfDsigma[3] */
        {32, 32, 32, /*0 - 2*/},
        /* nShpHpfScale[3] */
        {128, 128, 128, /*0 - 2*/},
        /* nShpGain[2] */
        {30, 25, /*0 - 1*/},
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
        /* nHighFreqGainLimit[12][2] */
        {
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
        },
        /* nHighFreqCorBaseGain[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nHighFreqCorSlope[12] */
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nHighFreqCorOffset[12] */
        {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, /*0 - 11*/},
        /* nHighFreqLimit[12][2] */
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
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
        },
        /* nMedFreqCorBaseGain[12] */
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, /*0 - 11*/},
        /* nMedFreqCorSlope[12] */
        {12, 12, 10, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nMedFreqCorOffset[12] */
        {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, /*0 - 11*/},
        /* nMedFreqLimit[12][2] */
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
        /* nDirFreqLogGain[12][2] */
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
        /* nDirFreqGainLimit[12][2] */
        {
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
        },
        /* nDirFreqCorBaseGain[12] */
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, /*0 - 11*/},
        /* nDirFreqCorSlope[12] */
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nDirFreqCorOffset[12] */
        {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nDirFreqLimit[12][2] */
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
        /* nLowFreqLogGain[12][2] */
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
        /* nLowFreqGainLimit[12][2] */
        {
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
            {0, 128, /*0 - 1*/},
        },
        /* nLowFreqCorBaseGain[12] */
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*0 - 11*/},
        /* nLowFreqCorSlope[12] */
        {12, 12, 12, 12, 12, 12, 8, 8, 8, 8, 8, 8, /*0 - 11*/},
        /* nLowFreqCorOffset[12] */
        {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, /*0 - 11*/},
        /* nLowFreqLimit[12][2] */
        {
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
            {96, 96, /*0 - 1*/},
        },
        /* nShpHpfBsigma[12][3] */
        {
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
            {16, 16, 16, /*0 - 2*/},
        },
        /* nShpHpfDsigma[12][3] */
        {
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
            {32, 32, 32, /*0 - 2*/},
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
            {24, 20, /*0 - 1*/},
            {24, 20, /*0 - 1*/},
            {26, 20, /*0 - 1*/},
            {28, 22, /*0 - 1*/},
            {34, 24, /*0 - 1*/},
            {34, 24, /*0 - 1*/},
            {32, 24, /*0 - 1*/},
            {32, 22, /*0 - 1*/},
            {30, 22, /*0 - 1*/},
            {30, 18, /*0 - 1*/},
            {30, 16, /*0 - 1*/},
            {30, 16, /*0 - 1*/},
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

const static AX_ISP_IQ_CCMP_PARAM_T ccmp_param_sdr_qs = {
    /* nChromaCompEn */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
    /* tManualParam */
    {
        /* nChromaCompY[29] */
        {250, 250, 250, 250, 250, 280, 300, 300, 300, 350, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, /*0 - 28*/},
        /* nChromaCompSat[23] */
        {200, 250, 320, 380, 430, 450, 460, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
    },
    /* tAutoParam */
    {
        /* nParamGrpNum */
        12,
        /* nRefVal[12] */
        {1024, 2048, 4096, 8192, 16384, 32768, 55296, 131072, 262144, 393216, 524288, 1048576, /*0 - 11*/},
        /* nChromaCompY[12][29] */
        {
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {500, 500, 500, 500, 500, 500, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {480, 480, 480, 480, 480, 480, 480, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {450, 450, 450, 450, 450, 480, 480, 480, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {420, 420, 420, 420, 420, 420, 450, 480, 480, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, /*0 - 28*/},
            {360, 360, 360, 360, 360, 400, 420, 420, 450, 480, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, /*0 - 28*/},
            {320, 320, 320, 320, 320, 360, 400, 420, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, 450, /*0 - 28*/},
            {300, 300, 300, 300, 300, 320, 350, 380, 400, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, 420, /*0 - 28*/},
            {250, 250, 250, 250, 250, 280, 300, 300, 300, 350, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, /*0 - 28*/},
        },
        /* nChromaCompSat[12][23] */
        {
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {400, 405, 415, 430, 450, 470, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {350, 360, 380, 410, 440, 460, 480, 490, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
			{300, 310, 330, 360, 400, 430, 450, 465, 480, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {250, 260, 280, 310, 350, 390, 420, 440, 460, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
            {200, 200, 210, 230, 260, 300, 350, 390, 420, 480, 500, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 500, /*0 - 22*/},
        },
    },
};

const static AX_ISP_IQ_SCM_PARAM_T scm_param_sdr_qs = {
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

const static AX_ISP_IQ_YCPROC_PARAM_T ycproc_param_sdr_qs = {
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

const static AX_ISP_IQ_YCRT_PARAM_T ycrt_param_sdr_qs = {
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

const static AX_ISP_IQ_CLP_PARAM_T clp_param_sdr_qs = {
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

const static AX_ISP_IQ_NUC_PARAM_T nuc_param_sdr_qs = {
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

const static AX_ISP_IQ_LDC_PARAM_T ldc_param_sdr_qs = {
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

const static AX_ISP_IQ_DIS_PARAM_T dis_param_sdr_qs = {
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

const static AX_ISP_IQ_ME_PARAM_T me_param_sdr_qs = {
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
    1,
    /* tGridRoiH */
    {
        /* nRoiOffsetH */
        16,
        /* nRoiOffsetV */
        0,
        /* nRoiRegionNumH */
        5,
        /* nRoiRegionNumV */
        2,
        /* nRoiRegionSizeH */
        528,
        /* nRoiRegionSizeV */
        760,
        /* nSearchRange */
        16,
    },
    /* tGridRoiV */
    {
        /* nRoiOffsetH */
        0,
        /* nRoiOffsetV */
        32,
        /* nRoiRegionNumH */
        5,
        /* nRoiRegionNumV */
        5,
        /* nRoiRegionSizeH */
        536,
        /* nRoiRegionSizeV */
        288,
        /* nSearchRange */
        32,
    },
};

#endif
