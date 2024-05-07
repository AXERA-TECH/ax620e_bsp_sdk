#ifndef __SC450AI_HDR_2X_H__
#define __SC450AI_HDR_2X_H__

/********************************************************************
* Store the default parameters of the hdr 2x mode
* warn: user need to add 'static' when defining global variables.
        Limit the scope of the variable to this sensor
*********************************************************************/

#include "ax_isp_iq_api.h"
#include "ax_isp_api.h"


const static AX_ISP_VERSION_T ax_isp_version_param_hdr_2x = {

    /* nIspMajor */
    4,
    /* nIspMinor1 */
    0,
    /* nIspMinor2 */
    31,
    /* szBuildTime */
    "",
    /* szIspVersion */
    "AX620E_ISP_V4.0.31",
};

const static AX_ISP_IQ_AE_PARAM_T ae_param_hdr_2x = {
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
        0,
        /* nSnsTotalAGain */
        1024,
        /* nSysTotalGain */
        1024,
        /* nShutter */
        2000,
        /* nIrisPwmDuty */
        0,
        /* nPos */
        512,
        /* nHdrRealRatioLtoS */
        31231,
        /* nHdrRealRatioStoVS */
        31231,
        /* nLumaHdrRealRatioLtoS */
        1024,
        /* nSetPoint */
        32768,
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
        16384,
        /* nHdrMaxShutterHwLimit */
        37864,
        /* nRealMaxShutter */
        37864,
    },
    /* tAeAlgAuto */
    {
        /* nSetPoint */
        102400,
        /* nFaceTarget */
        35840,
        /* nTolerance */
        6291456,
        /* nAgainLcg2HcgTh */
        15872,
        /* nAgainHcg2LcgTh */
        1228,
        /* nAgainLcg2HcgRatio */
        1024,
        /* nAgainHcg2LcgRatio */
        1024,
        /* nLuxk */
        101157,
        /* nCompensationMode */
        1,
        /* nMaxIspGain */
        8192,
        /* nMinIspGain */
        1024,
        /* nMaxUserDgain */
        16373,
        /* nMinUserDgain */
        1024,
        /* nMaxUserTotalAgain */
        61976,
        /* nMinUserTotalAgain */
        1024,
        /* nMaxUserSysGain */
        513024,
        /* nMinUserSysGain */
        1024,
        /* nMaxShutter */
        37864,
        /* nMinShutter */
        14,
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
            0,
            /* nFlickerPeriod */
            0,
            /* nAntiFlickerTolerance */
            200,
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
            1,
            /* nUsedTableId */
            0,
            /* tRouteTable[8] */
            {
                /* 0 */
                {
                    /* sTableName[32] */
                    "DefaultAeRoute",
                    /* nRouteCurveNum */
                    6,
                    /* tRouteCurveList[16] */
                    {
                        /* 0 */
                        {
                            /* nIntergrationTime */
                            40,
                            /* nGain */
                            1024,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 1 */
                        {
                            /* nIntergrationTime */
                            4000,
                            /* nGain */
                            1024,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 2 */
                        {
                            /* nIntergrationTime */
                            10000,
                            /* nGain */
                            1024,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 3 */
                        {
                            /* nIntergrationTime */
                            20000,
                            /* nGain */
                            1024,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 4 */
                        {
                            /* nIntergrationTime */
                            30000,
                            /* nGain */
                            1024,
                            /* nIncrementPriority */
                            0,
                        },
                        /* 5 */
                        {
                            /* nIntergrationTime */
                            37864,
                            /* nGain */
                            182272,
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
            9,
            /* nRefList[10] */
            {205, 1024, 5120, 10240, 51200, 102400, 204800, 1024000, 2048000, /*0 - 8*/},
            /* nSetPointList[10] */
            {20480, 45056, 57344, 61440, 73728, 73728, 73728, 73728, 73728, /*0 - 8*/},
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
            0,
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
                3,
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
                0,
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

const static AX_ISP_IQ_AWB_PARAM_T awb_param_hdr_2x = {
    /* nEnable */
    0,
    /* tManualParam */
    {
        /* nManualMode */
        0,
        /* tGain */
        {
            /* nGainR */
            256,
            /* nGainGr */
            256,
            /* nGainGb */
            256,
            /* nGainB */
            256,
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
            1523187,
            /* nBg */
            1396608,
        },
        /* nCenterPntRadius */
        1241394,
        /* nLowCut */
        0,
        /* nHighCut */
        56,
        /* nCctMax */
        10500,
        /* nCctMin */
        1800,
        /* nPartCtrlPntNum */
        8,
        /* nCtrlPntNum */
        57,
        /* nCtrlSegKbNum */
        56,
        /* nCctList[512] */
        {
            1800, 1862, 1925, 1987, 2050, 2112, 2175, 2237, 2300, 2369, 2439, 2508, 2578, 2647, 2717, 2786, 2856, 2974, 3092, 3210, 3328, 3446, 3564, 3682, 3800, 3950, 4100, 4250, 4400, 4550, 4700, 4850,  /* 0 - 31*/
            5000, 5187, 5375, 5562, 5750, 5937, 6125, 6312, 6500, 6625, 6750, 6875, 7000, 7125, 7250, 7375, 7500, 7875, 8250, 8625, 9000, 9375, 9750, 10125, 10500, /*32 - 56*/
        },
        /* tChordKB */
        {
            /* nK */
            -1029,
            /* nB */
            1357,
        },
        /* tChordPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1180697,
                /* nBg */
                203392,
            },
            /* 1 */
            {
                /* nRg */
                1164412,
                /* nBg */
                219761,
            },
            /* 2 */
            {
                /* nRg */
                1148411,
                /* nBg */
                235846,
            },
            /* 3 */
            {
                /* nRg */
                1132682,
                /* nBg */
                251648,
            },
            /* 4 */
            {
                /* nRg */
                1117205,
                /* nBg */
                267209,
            },
            /* 5 */
            {
                /* nRg */
                1101959,
                /* nBg */
                282528,
            },
            /* 6 */
            {
                /* nRg */
                1086943,
                /* nBg */
                297617,
            },
            /* 7 */
            {
                /* nRg */
                1072148,
                /* nBg */
                312497,
            },
            /* 8 */
            {
                /* nRg */
                1057541,
                /* nBg */
                327166,
            },
            /* 9 */
            {
                /* nRg */
                1041530,
                /* nBg */
                343272,
            },
            /* 10 */
            {
                /* nRg */
                1025728,
                /* nBg */
                359148,
            },
            /* 11 */
            {
                /* nRg */
                1010135,
                /* nBg */
                374824,
            },
            /* 12 */
            {
                /* nRg */
                994721,
                /* nBg */
                390311,
            },
            /* 13 */
            {
                /* nRg */
                979496,
                /* nBg */
                405621,
            },
            /* 14 */
            {
                /* nRg */
                964428,
                /* nBg */
                420762,
            },
            /* 15 */
            {
                /* nRg */
                949507,
                /* nBg */
                435757,
            },
            /* 16 */
            {
                /* nRg */
                934722,
                /* nBg */
                450615,
            },
            /* 17 */
            {
                /* nRg */
                923953,
                /* nBg */
                461436,
            },
            /* 18 */
            {
                /* nRg */
                913247,
                /* nBg */
                472195,
            },
            /* 19 */
            {
                /* nRg */
                902604,
                /* nBg */
                482901,
            },
            /* 20 */
            {
                /* nRg */
                892013,
                /* nBg */
                493544,
            },
            /* 21 */
            {
                /* nRg */
                881475,
                /* nBg */
                504134,
            },
            /* 22 */
            {
                /* nRg */
                870979,
                /* nBg */
                514683,
            },
            /* 23 */
            {
                /* nRg */
                860524,
                /* nBg */
                525179,
            },
            /* 24 */
            {
                /* nRg */
                850112,
                /* nBg */
                535644,
            },
            /* 25 */
            {
                /* nRg */
                830283,
                /* nBg */
                555578,
            },
            /* 26 */
            {
                /* nRg */
                810549,
                /* nBg */
                575417,
            },
            /* 27 */
            {
                /* nRg */
                790888,
                /* nBg */
                595172,
            },
            /* 28 */
            {
                /* nRg */
                771280,
                /* nBg */
                614885,
            },
            /* 29 */
            {
                /* nRg */
                751693,
                /* nBg */
                634567,
            },
            /* 30 */
            {
                /* nRg */
                732095,
                /* nBg */
                654259,
            },
            /* 31 */
            {
                /* nRg */
                712476,
                /* nBg */
                673983,
            },
            /* 32 */
            {
                /* nRg */
                692805,
                /* nBg */
                693759,
            },
            /* 33 */
            {
                /* nRg */
                686555,
                /* nBg */
                700040,
            },
            /* 34 */
            {
                /* nRg */
                680295,
                /* nBg */
                706331,
            },
            /* 35 */
            {
                /* nRg */
                674025,
                /* nBg */
                712623,
            },
            /* 36 */
            {
                /* nRg */
                667754,
                /* nBg */
                718935,
            },
            /* 37 */
            {
                /* nRg */
                661463,
                /* nBg */
                725258,
            },
            /* 38 */
            {
                /* nRg */
                655161,
                /* nBg */
                731591,
            },
            /* 39 */
            {
                /* nRg */
                648848,
                /* nBg */
                737935,
            },
            /* 40 */
            {
                /* nRg */
                642515,
                /* nBg */
                744290,
            },
            /* 41 */
            {
                /* nRg */
                633644,
                /* nBg */
                753213,
            },
            /* 42 */
            {
                /* nRg */
                624731,
                /* nBg */
                762168,
            },
            /* 43 */
            {
                /* nRg */
                615787,
                /* nBg */
                771165,
            },
            /* 44 */
            {
                /* nRg */
                606800,
                /* nBg */
                780193,
            },
            /* 45 */
            {
                /* nRg */
                597783,
                /* nBg */
                789253,
            },
            /* 46 */
            {
                /* nRg */
                588723,
                /* nBg */
                798365,
            },
            /* 47 */
            {
                /* nRg */
                579611,
                /* nBg */
                807519,
            },
            /* 48 */
            {
                /* nRg */
                570457,
                /* nBg */
                816725,
            },
            /* 49 */
            {
                /* nRg */
                542680,
                /* nBg */
                844638,
            },
            /* 50 */
            {
                /* nRg */
                514368,
                /* nBg */
                873086,
            },
            /* 51 */
            {
                /* nRg */
                485459,
                /* nBg */
                902153,
            },
            /* 52 */
            {
                /* nRg */
                455837,
                /* nBg */
                931922,
            },
            /* 53 */
            {
                /* nRg */
                425418,
                /* nBg */
                962488,
            },
            /* 54 */
            {
                /* nRg */
                394097,
                /* nBg */
                993977,
            },
            /* 55 */
            {
                /* nRg */
                361759,
                /* nBg */
                1026483,
            },
            /* 56 */
            {
                /* nRg */
                328257,
                /* nBg */
                1060142,
            },
        },
        /* tArcPointList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1180697,
                /* nBg */
                203392,
            },
            /* 1 */
            {
                /* nRg */
                1161183,
                /* nBg */
                209170,
            },
            /* 2 */
            {
                /* nRg */
                1141773,
                /* nBg */
                215262,
            },
            /* 3 */
            {
                /* nRg */
                1122459,
                /* nBg */
                221669,
            },
            /* 4 */
            {
                /* nRg */
                1103249,
                /* nBg */
                228401,
            },
            /* 5 */
            {
                /* nRg */
                1084154,
                /* nBg */
                235437,
            },
            /* 6 */
            {
                /* nRg */
                1065185,
                /* nBg */
                242787,
            },
            /* 7 */
            {
                /* nRg */
                1046332,
                /* nBg */
                250452,
            },
            /* 8 */
            {
                /* nRg */
                1027615,
                /* nBg */
                258422,
            },
            /* 9 */
            {
                /* nRg */
                1006948,
                /* nBg */
                267649,
            },
            /* 10 */
            {
                /* nRg */
                986458,
                /* nBg */
                277243,
            },
            /* 11 */
            {
                /* nRg */
                966137,
                /* nBg */
                287215,
            },
            /* 12 */
            {
                /* nRg */
                946015,
                /* nBg */
                297554,
            },
            /* 13 */
            {
                /* nRg */
                926071,
                /* nBg */
                308250,
            },
            /* 14 */
            {
                /* nRg */
                906337,
                /* nBg */
                319323,
            },
            /* 15 */
            {
                /* nRg */
                886802,
                /* nBg */
                330742,
            },
            /* 16 */
            {
                /* nRg */
                867476,
                /* nBg */
                342517,
            },
            /* 17 */
            {
                /* nRg */
                853436,
                /* nBg */
                351388,
            },
            /* 18 */
            {
                /* nRg */
                839511,
                /* nBg */
                360438,
            },
            /* 19 */
            {
                /* nRg */
                825712,
                /* nBg */
                369675,
            },
            /* 20 */
            {
                /* nRg */
                812028,
                /* nBg */
                379102,
            },
            /* 21 */
            {
                /* nRg */
                798480,
                /* nBg */
                388707,
            },
            /* 22 */
            {
                /* nRg */
                785058,
                /* nBg */
                398501,
            },
            /* 23 */
            {
                /* nRg */
                771773,
                /* nBg */
                408462,
            },
            /* 24 */
            {
                /* nRg */
                758613,
                /* nBg */
                418602,
            },
            /* 25 */
            {
                /* nRg */
                733825,
                /* nBg */
                438504,
            },
            /* 26 */
            {
                /* nRg */
                709550,
                /* nBg */
                459025,
            },
            /* 27 */
            {
                /* nRg */
                685811,
                /* nBg */
                480174,
            },
            /* 28 */
            {
                /* nRg */
                662616,
                /* nBg */
                501911,
            },
            /* 29 */
            {
                /* nRg */
                639988,
                /* nBg */
                524236,
            },
            /* 30 */
            {
                /* nRg */
                617947,
                /* nBg */
                547136,
            },
            /* 31 */
            {
                /* nRg */
                596493,
                /* nBg */
                570593,
            },
            /* 32 */
            {
                /* nRg */
                575647,
                /* nBg */
                594595,
            },
            /* 33 */
            {
                /* nRg */
                569167,
                /* nBg */
                602313,
            },
            /* 34 */
            {
                /* nRg */
                562760,
                /* nBg */
                610072,
            },
            /* 35 */
            {
                /* nRg */
                556416,
                /* nBg */
                617884,
            },
            /* 36 */
            {
                /* nRg */
                550125,
                /* nBg */
                625748,
            },
            /* 37 */
            {
                /* nRg */
                543907,
                /* nBg */
                633665,
            },
            /* 38 */
            {
                /* nRg */
                537752,
                /* nBg */
                641634,
            },
            /* 39 */
            {
                /* nRg */
                531659,
                /* nBg */
                649656,
            },
            /* 40 */
            {
                /* nRg */
                525641,
                /* nBg */
                657719,
            },
            /* 41 */
            {
                /* nRg */
                517325,
                /* nBg */
                669086,
            },
            /* 42 */
            {
                /* nRg */
                509136,
                /* nBg */
                680547,
            },
            /* 43 */
            {
                /* nRg */
                501073,
                /* nBg */
                692092,
            },
            /* 44 */
            {
                /* nRg */
                493145,
                /* nBg */
                703731,
            },
            /* 45 */
            {
                /* nRg */
                485354,
                /* nBg */
                715464,
            },
            /* 46 */
            {
                /* nRg */
                477689,
                /* nBg */
                727282,
            },
            /* 47 */
            {
                /* nRg */
                470161,
                /* nBg */
                739183,
            },
            /* 48 */
            {
                /* nRg */
                462768,
                /* nBg */
                751179,
            },
            /* 49 */
            {
                /* nRg */
                441419,
                /* nBg */
                787638,
            },
            /* 50 */
            {
                /* nRg */
                421328,
                /* nBg */
                824799,
            },
            /* 51 */
            {
                /* nRg */
                402506,
                /* nBg */
                862632,
            },
            /* 52 */
            {
                /* nRg */
                384985,
                /* nBg */
                901073,
            },
            /* 53 */
            {
                /* nRg */
                368784,
                /* nBg */
                940090,
            },
            /* 54 */
            {
                /* nRg */
                353915,
                /* nBg */
                979643,
            },
            /* 55 */
            {
                /* nRg */
                340399,
                /* nBg */
                1019677,
            },
            /* 56 */
            {
                /* nRg */
                328257,
                /* nBg */
                1060142,
            },
        },
        /* tRadiusLineList[512] */
        {
            /* 0 */
            {
                /* nK */
                3567,
                /* nB */
                -3818,
            },
            /* 1 */
            {
                /* nK */
                3358,
                /* nB */
                -3515,
            },
            /* 2 */
            {
                /* nK */
                3171,
                /* nB */
                -3243,
            },
            /* 3 */
            {
                /* nK */
                3002,
                /* nB */
                -2997,
            },
            /* 4 */
            {
                /* nK */
                2848,
                /* nB */
                -2774,
            },
            /* 5 */
            {
                /* nK */
                2708,
                /* nB */
                -2570,
            },
            /* 6 */
            {
                /* nK */
                2579,
                /* nB */
                -2383,
            },
            /* 7 */
            {
                /* nK */
                2461,
                /* nB */
                -2211,
            },
            /* 8 */
            {
                /* nK */
                2351,
                /* nB */
                -2052,
            },
            /* 9 */
            {
                /* nK */
                2239,
                /* nB */
                -1889,
            },
            /* 10 */
            {
                /* nK */
                2135,
                /* nB */
                -1738,
            },
            /* 11 */
            {
                /* nK */
                2039,
                /* nB */
                -1598,
            },
            /* 12 */
            {
                /* nK */
                1949,
                /* nB */
                -1468,
            },
            /* 13 */
            {
                /* nK */
                1866,
                /* nB */
                -1347,
            },
            /* 14 */
            {
                /* nK */
                1788,
                /* nB */
                -1233,
            },
            /* 15 */
            {
                /* nK */
                1715,
                /* nB */
                -1127,
            },
            /* 16 */
            {
                /* nK */
                1646,
                /* nB */
                -1027,
            },
            /* 17 */
            {
                /* nK */
                1598,
                /* nB */
                -957,
            },
            /* 18 */
            {
                /* nK */
                1551,
                /* nB */
                -890,
            },
            /* 19 */
            {
                /* nK */
                1507,
                /* nB */
                -826,
            },
            /* 20 */
            {
                /* nK */
                1465,
                /* nB */
                -764,
            },
            /* 21 */
            {
                /* nK */
                1424,
                /* nB */
                -704,
            },
            /* 22 */
            {
                /* nK */
                1384,
                /* nB */
                -647,
            },
            /* 23 */
            {
                /* nK */
                1346,
                /* nB */
                -592,
            },
            /* 24 */
            {
                /* nK */
                1309,
                /* nB */
                -538,
            },
            /* 25 */
            {
                /* nK */
                1242,
                /* nB */
                -441,
            },
            /* 26 */
            {
                /* nK */
                1179,
                /* nB */
                -350,
            },
            /* 27 */
            {
                /* nK */
                1120,
                /* nB */
                -264,
            },
            /* 28 */
            {
                /* nK */
                1064,
                /* nB */
                -182,
            },
            /* 29 */
            {
                /* nK */
                1011,
                /* nB */
                -105,
            },
            /* 30 */
            {
                /* nK */
                960,
                /* nB */
                -31,
            },
            /* 31 */
            {
                /* nK */
                912,
                /* nB */
                38,
            },
            /* 32 */
            {
                /* nK */
                866,
                /* nB */
                104,
            },
            /* 33 */
            {
                /* nK */
                852,
                /* nB */
                125,
            },
            /* 34 */
            {
                /* nK */
                838,
                /* nB */
                145,
            },
            /* 35 */
            {
                /* nK */
                824,
                /* nB */
                165,
            },
            /* 36 */
            {
                /* nK */
                811,
                /* nB */
                185,
            },
            /* 37 */
            {
                /* nK */
                797,
                /* nB */
                204,
            },
            /* 38 */
            {
                /* nK */
                784,
                /* nB */
                224,
            },
            /* 39 */
            {
                /* nK */
                771,
                /* nB */
                243,
            },
            /* 40 */
            {
                /* nK */
                758,
                /* nB */
                262,
            },
            /* 41 */
            {
                /* nK */
                740,
                /* nB */
                288,
            },
            /* 42 */
            {
                /* nK */
                723,
                /* nB */
                313,
            },
            /* 43 */
            {
                /* nK */
                705,
                /* nB */
                338,
            },
            /* 44 */
            {
                /* nK */
                688,
                /* nB */
                363,
            },
            /* 45 */
            {
                /* nK */
                672,
                /* nB */
                387,
            },
            /* 46 */
            {
                /* nK */
                655,
                /* nB */
                411,
            },
            /* 47 */
            {
                /* nK */
                639,
                /* nB */
                435,
            },
            /* 48 */
            {
                /* nK */
                623,
                /* nB */
                458,
            },
            /* 49 */
            {
                /* nK */
                576,
                /* nB */
                526,
            },
            /* 50 */
            {
                /* nK */
                531,
                /* nB */
                591,
            },
            /* 51 */
            {
                /* nK */
                487,
                /* nB */
                655,
            },
            /* 52 */
            {
                /* nK */
                445,
                /* nB */
                716,
            },
            /* 53 */
            {
                /* nK */
                404,
                /* nB */
                775,
            },
            /* 54 */
            {
                /* nK */
                365,
                /* nB */
                833,
            },
            /* 55 */
            {
                /* nK */
                326,
                /* nB */
                889,
            },
            /* 56 */
            {
                /* nK */
                288,
                /* nB */
                945,
            },
        },
        /* tInLeftBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1145978,
                /* nBg */
                82450,
            },
            /* 1 */
            {
                /* nRg */
                1124493,
                /* nBg */
                88804,
            },
            /* 2 */
            {
                /* nRg */
                1103112,
                /* nBg */
                95515,
            },
            /* 3 */
            {
                /* nRg */
                1081837,
                /* nBg */
                102582,
            },
            /* 4 */
            {
                /* nRg */
                1060687,
                /* nBg */
                109985,
            },
            /* 5 */
            {
                /* nRg */
                1039663,
                /* nBg */
                117745,
            },
            /* 6 */
            {
                /* nRg */
                1018765,
                /* nBg */
                125840,
            },
            /* 7 */
            {
                /* nRg */
                998003,
                /* nBg */
                134281,
            },
            /* 8 */
            {
                /* nRg */
                977378,
                /* nBg */
                143057,
            },
            /* 9 */
            {
                /* nRg */
                954624,
                /* nBg */
                153218,
            },
            /* 10 */
            {
                /* nRg */
                932048,
                /* nBg */
                163788,
            },
            /* 11 */
            {
                /* nRg */
                909682,
                /* nBg */
                174766,
            },
            /* 12 */
            {
                /* nRg */
                887504,
                /* nBg */
                186154,
            },
            /* 13 */
            {
                /* nRg */
                865547,
                /* nBg */
                197940,
            },
            /* 14 */
            {
                /* nRg */
                843810,
                /* nBg */
                210124,
            },
            /* 15 */
            {
                /* nRg */
                822293,
                /* nBg */
                222707,
            },
            /* 16 */
            {
                /* nRg */
                801018,
                /* nBg */
                235678,
            },
            /* 17 */
            {
                /* nRg */
                785551,
                /* nBg */
                245440,
            },
            /* 18 */
            {
                /* nRg */
                770211,
                /* nBg */
                255412,
            },
            /* 19 */
            {
                /* nRg */
                755006,
                /* nBg */
                265594,
            },
            /* 20 */
            {
                /* nRg */
                739949,
                /* nBg */
                275964,
            },
            /* 21 */
            {
                /* nRg */
                725027,
                /* nBg */
                286544,
            },
            /* 22 */
            {
                /* nRg */
                710242,
                /* nBg */
                297324,
            },
            /* 23 */
            {
                /* nRg */
                695604,
                /* nBg */
                308302,
            },
            /* 24 */
            {
                /* nRg */
                681124,
                /* nBg */
                319470,
            },
            /* 25 */
            {
                /* nRg */
                653819,
                /* nBg */
                341385,
            },
            /* 26 */
            {
                /* nRg */
                627080,
                /* nBg */
                363992,
            },
            /* 27 */
            {
                /* nRg */
                600928,
                /* nBg */
                387281,
            },
            /* 28 */
            {
                /* nRg */
                575396,
                /* nBg */
                411220,
            },
            /* 29 */
            {
                /* nRg */
                550471,
                /* nBg */
                435820,
            },
            /* 30 */
            {
                /* nRg */
                526186,
                /* nBg */
                461038,
            },
            /* 31 */
            {
                /* nRg */
                502562,
                /* nBg */
                486875,
            },
            /* 32 */
            {
                /* nRg */
                479598,
                /* nBg */
                513309,
            },
            /* 33 */
            {
                /* nRg */
                472467,
                /* nBg */
                521792,
            },
            /* 34 */
            {
                /* nRg */
                465410,
                /* nBg */
                530349,
            },
            /* 35 */
            {
                /* nRg */
                458416,
                /* nBg */
                538958,
            },
            /* 36 */
            {
                /* nRg */
                451496,
                /* nBg */
                547619,
            },
            /* 37 */
            {
                /* nRg */
                444649,
                /* nBg */
                556332,
            },
            /* 38 */
            {
                /* nRg */
                437875,
                /* nBg */
                565109,
            },
            /* 39 */
            {
                /* nRg */
                431164,
                /* nBg */
                573938,
            },
            /* 40 */
            {
                /* nRg */
                424526,
                /* nBg */
                582820,
            },
            /* 41 */
            {
                /* nRg */
                415362,
                /* nBg */
                595340,
            },
            /* 42 */
            {
                /* nRg */
                406344,
                /* nBg */
                607964,
            },
            /* 43 */
            {
                /* nRg */
                397473,
                /* nBg */
                620684,
            },
            /* 44 */
            {
                /* nRg */
                388739,
                /* nBg */
                633508,
            },
            /* 45 */
            {
                /* nRg */
                380151,
                /* nBg */
                646426,
            },
            /* 46 */
            {
                /* nRg */
                371720,
                /* nBg */
                659439,
            },
            /* 47 */
            {
                /* nRg */
                363426,
                /* nBg */
                672557,
            },
            /* 48 */
            {
                /* nRg */
                355289,
                /* nBg */
                685758,
            },
            /* 49 */
            {
                /* nRg */
                331769,
                /* nBg */
                725908,
            },
            /* 50 */
            {
                /* nRg */
                309644,
                /* nBg */
                766845,
            },
            /* 51 */
            {
                /* nRg */
                288914,
                /* nBg */
                808505,
            },
            /* 52 */
            {
                /* nRg */
                269610,
                /* nBg */
                850846,
            },
            /* 53 */
            {
                /* nRg */
                251774,
                /* nBg */
                893817,
            },
            /* 54 */
            {
                /* nRg */
                235395,
                /* nBg */
                937375,
            },
            /* 55 */
            {
                /* nRg */
                220516,
                /* nBg */
                981467,
            },
            /* 56 */
            {
                /* nRg */
                207146,
                /* nBg */
                1026042,
            },
        },
        /* tInRightBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1209627,
                /* nBg */
                304181,
            },
            /* 1 */
            {
                /* nRg */
                1191759,
                /* nBg */
                309466,
            },
            /* 2 */
            {
                /* nRg */
                1173986,
                /* nBg */
                315045,
            },
            /* 3 */
            {
                /* nRg */
                1156307,
                /* nBg */
                320917,
            },
            /* 4 */
            {
                /* nRg */
                1138722,
                /* nBg */
                327072,
            },
            /* 5 */
            {
                /* nRg */
                1121242,
                /* nBg */
                333521,
            },
            /* 6 */
            {
                /* nRg */
                1103867,
                /* nBg */
                340252,
            },
            /* 7 */
            {
                /* nRg */
                1086608,
                /* nBg */
                347267,
            },
            /* 8 */
            {
                /* nRg */
                1069474,
                /* nBg */
                354565,
            },
            /* 9 */
            {
                /* nRg */
                1050547,
                /* nBg */
                363007,
            },
            /* 10 */
            {
                /* nRg */
                1031788,
                /* nBg */
                371794,
            },
            /* 11 */
            {
                /* nRg */
                1013197,
                /* nBg */
                380916,
            },
            /* 12 */
            {
                /* nRg */
                994763,
                /* nBg */
                390385,
            },
            /* 13 */
            {
                /* nRg */
                976507,
                /* nBg */
                400189,
            },
            /* 14 */
            {
                /* nRg */
                958440,
                /* nBg */
                410318,
            },
            /* 15 */
            {
                /* nRg */
                940552,
                /* nBg */
                420773,
            },
            /* 16 */
            {
                /* nRg */
                922862,
                /* nBg */
                431552,
            },
            /* 17 */
            {
                /* nRg */
                910007,
                /* nBg */
                439668,
            },
            /* 18 */
            {
                /* nRg */
                897256,
                /* nBg */
                447962,
            },
            /* 19 */
            {
                /* nRg */
                884621,
                /* nBg */
                456424,
            },
            /* 20 */
            {
                /* nRg */
                872101,
                /* nBg */
                465054,
            },
            /* 21 */
            {
                /* nRg */
                859696,
                /* nBg */
                473841,
            },
            /* 22 */
            {
                /* nRg */
                847407,
                /* nBg */
                482806,
            },
            /* 23 */
            {
                /* nRg */
                835243,
                /* nBg */
                491929,
            },
            /* 24 */
            {
                /* nRg */
                823195,
                /* nBg */
                501219,
            },
            /* 25 */
            {
                /* nRg */
                800504,
                /* nBg */
                519433,
            },
            /* 26 */
            {
                /* nRg */
                778274,
                /* nBg */
                538224,
            },
            /* 27 */
            {
                /* nRg */
                756537,
                /* nBg */
                557580,
            },
            /* 28 */
            {
                /* nRg */
                735314,
                /* nBg */
                577482,
            },
            /* 29 */
            {
                /* nRg */
                714594,
                /* nBg */
                597929,
            },
            /* 30 */
            {
                /* nRg */
                694409,
                /* nBg */
                618891,
            },
            /* 31 */
            {
                /* nRg */
                674769,
                /* nBg */
                640365,
            },
            /* 32 */
            {
                /* nRg */
                655685,
                /* nBg */
                662344,
            },
            /* 33 */
            {
                /* nRg */
                649750,
                /* nBg */
                669400,
            },
            /* 34 */
            {
                /* nRg */
                643889,
                /* nBg */
                676510,
            },
            /* 35 */
            {
                /* nRg */
                638079,
                /* nBg */
                683661,
            },
            /* 36 */
            {
                /* nRg */
                632323,
                /* nBg */
                690865,
            },
            /* 37 */
            {
                /* nRg */
                626629,
                /* nBg */
                698110,
            },
            /* 38 */
            {
                /* nRg */
                620988,
                /* nBg */
                705409,
            },
            /* 39 */
            {
                /* nRg */
                615420,
                /* nBg */
                712749,
            },
            /* 40 */
            {
                /* nRg */
                609904,
                /* nBg */
                720131,
            },
            /* 41 */
            {
                /* nRg */
                602281,
                /* nBg */
                730532,
            },
            /* 42 */
            {
                /* nRg */
                594784,
                /* nBg */
                741029,
            },
            /* 43 */
            {
                /* nRg */
                587412,
                /* nBg */
                751598,
            },
            /* 44 */
            {
                /* nRg */
                580146,
                /* nBg */
                762262,
            },
            /* 45 */
            {
                /* nRg */
                573015,
                /* nBg */
                773000,
            },
            /* 46 */
            {
                /* nRg */
                566000,
                /* nBg */
                783821,
            },
            /* 47 */
            {
                /* nRg */
                559111,
                /* nBg */
                794716,
            },
            /* 48 */
            {
                /* nRg */
                552348,
                /* nBg */
                805694,
            },
            /* 49 */
            {
                /* nRg */
                532792,
                /* nBg */
                839071,
            },
            /* 50 */
            {
                /* nRg */
                514400,
                /* nBg */
                873097,
            },
            /* 51 */
            {
                /* nRg */
                497172,
                /* nBg */
                907731,
            },
            /* 52 */
            {
                /* nRg */
                481129,
                /* nBg */
                942932,
            },
            /* 53 */
            {
                /* nRg */
                466291,
                /* nBg */
                978657,
            },
            /* 54 */
            {
                /* nRg */
                452681,
                /* nBg */
                1014864,
            },
            /* 55 */
            {
                /* nRg */
                440308,
                /* nBg */
                1051512,
            },
            /* 56 */
            {
                /* nRg */
                429193,
                /* nBg */
                1088558,
            },
        },
        /* tOutLeftBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1128624,
                /* nBg */
                21978,
            },
            /* 1 */
            {
                /* nRg */
                1106143,
                /* nBg */
                28626,
            },
            /* 2 */
            {
                /* nRg */
                1083777,
                /* nBg */
                35652,
            },
            /* 3 */
            {
                /* nRg */
                1061526,
                /* nBg */
                43034,
            },
            /* 4 */
            {
                /* nRg */
                1039401,
                /* nBg */
                50783,
            },
            /* 5 */
            {
                /* nRg */
                1017412,
                /* nBg */
                58888,
            },
            /* 6 */
            {
                /* nRg */
                995550,
                /* nBg */
                67361,
            },
            /* 7 */
            {
                /* nRg */
                973834,
                /* nBg */
                76190,
            },
            /* 8 */
            {
                /* nRg */
                952264,
                /* nBg */
                85375,
            },
            /* 9 */
            {
                /* nRg */
                928451,
                /* nBg */
                95997,
            },
            /* 10 */
            {
                /* nRg */
                904848,
                /* nBg */
                107049,
            },
            /* 11 */
            {
                /* nRg */
                881443,
                /* nBg */
                118542,
            },
            /* 12 */
            {
                /* nRg */
                858259,
                /* nBg */
                130443,
            },
            /* 13 */
            {
                /* nRg */
                835285,
                /* nBg */
                142774,
            },
            /* 14 */
            {
                /* nRg */
                812552,
                /* nBg */
                155525,
            },
            /* 15 */
            {
                /* nRg */
                790050,
                /* nBg */
                168684,
            },
            /* 16 */
            {
                /* nRg */
                767788,
                /* nBg */
                182253,
            },
            /* 17 */
            {
                /* nRg */
                751609,
                /* nBg */
                192466,
            },
            /* 18 */
            {
                /* nRg */
                735566,
                /* nBg */
                202899,
            },
            /* 19 */
            {
                /* nRg */
                719659,
                /* nBg */
                213543,
            },
            /* 20 */
            {
                /* nRg */
                703909,
                /* nBg */
                224406,
            },
            /* 21 */
            {
                /* nRg */
                688296,
                /* nBg */
                235468,
            },
            /* 22 */
            {
                /* nRg */
                672829,
                /* nBg */
                246740,
            },
            /* 23 */
            {
                /* nRg */
                657520,
                /* nBg */
                258222,
            },
            /* 24 */
            {
                /* nRg */
                642368,
                /* nBg */
                269903,
            },
            /* 25 */
            {
                /* nRg */
                613805,
                /* nBg */
                292825,
            },
            /* 26 */
            {
                /* nRg */
                585839,
                /* nBg */
                316481,
            },
            /* 27 */
            {
                /* nRg */
                558493,
                /* nBg */
                340829,
            },
            /* 28 */
            {
                /* nRg */
                531775,
                /* nBg */
                365880,
            },
            /* 29 */
            {
                /* nRg */
                505707,
                /* nBg */
                391601,
            },
            /* 30 */
            {
                /* nRg */
                480311,
                /* nBg */
                417983,
            },
            /* 31 */
            {
                /* nRg */
                455596,
                /* nBg */
                445005,
            },
            /* 32 */
            {
                /* nRg */
                431573,
                /* nBg */
                472656,
            },
            /* 33 */
            {
                /* nRg */
                424118,
                /* nBg */
                481538,
            },
            /* 34 */
            {
                /* nRg */
                416736,
                /* nBg */
                490482,
            },
            /* 35 */
            {
                /* nRg */
                409427,
                /* nBg */
                499489,
            },
            /* 36 */
            {
                /* nRg */
                402181,
                /* nBg */
                508549,
            },
            /* 37 */
            {
                /* nRg */
                395020,
                /* nBg */
                517671,
            },
            /* 38 */
            {
                /* nRg */
                387931,
                /* nBg */
                526847,
            },
            /* 39 */
            {
                /* nRg */
                380916,
                /* nBg */
                536084,
            },
            /* 40 */
            {
                /* nRg */
                373975,
                /* nBg */
                545375,
            },
            /* 41 */
            {
                /* nRg */
                364391,
                /* nBg */
                558472,
            },
            /* 42 */
            {
                /* nRg */
                354953,
                /* nBg */
                571673,
            },
            /* 43 */
            {
                /* nRg */
                345674,
                /* nBg */
                584980,
            },
            /* 44 */
            {
                /* nRg */
                336540,
                /* nBg */
                598391,
            },
            /* 45 */
            {
                /* nRg */
                327554,
                /* nBg */
                611907,
            },
            /* 46 */
            {
                /* nRg */
                318736,
                /* nBg */
                625518,
            },
            /* 47 */
            {
                /* nRg */
                310064,
                /* nBg */
                639233,
            },
            /* 48 */
            {
                /* nRg */
                301549,
                /* nBg */
                653043,
            },
            /* 49 */
            {
                /* nRg */
                276950,
                /* nBg */
                695049,
            },
            /* 50 */
            {
                /* nRg */
                253797,
                /* nBg */
                737862,
            },
            /* 51 */
            {
                /* nRg */
                232113,
                /* nBg */
                781441,
            },
            /* 52 */
            {
                /* nRg */
                211928,
                /* nBg */
                825733,
            },
            /* 53 */
            {
                /* nRg */
                193263,
                /* nBg */
                870685,
            },
            /* 54 */
            {
                /* nRg */
                176140,
                /* nBg */
                916246,
            },
            /* 55 */
            {
                /* nRg */
                160568,
                /* nBg */
                962362,
            },
            /* 56 */
            {
                /* nRg */
                146580,
                /* nBg */
                1008982,
            },
        },
        /* tOutRightBorderPntList[512] */
        {
            /* 0 */
            {
                /* nRg */
                1224097,
                /* nBg */
                354576,
            },
            /* 1 */
            {
                /* nRg */
                1207047,
                /* nBg */
                359620,
            },
            /* 2 */
            {
                /* nRg */
                1190092,
                /* nBg */
                364936,
            },
            /* 3 */
            {
                /* nRg */
                1173231,
                /* nBg */
                370535,
            },
            /* 4 */
            {
                /* nRg */
                1156453,
                /* nBg */
                376407,
            },
            /* 5 */
            {
                /* nRg */
                1139781,
                /* nBg */
                382562,
            },
            /* 6 */
            {
                /* nRg */
                1123214,
                /* nBg */
                388980,
            },
            /* 7 */
            {
                /* nRg */
                1106751,
                /* nBg */
                395670,
            },
            /* 8 */
            {
                /* nRg */
                1090404,
                /* nBg */
                402632,
            },
            /* 9 */
            {
                /* nRg */
                1072358,
                /* nBg */
                410685,
            },
            /* 10 */
            {
                /* nRg */
                1054459,
                /* nBg */
                419063,
            },
            /* 11 */
            {
                /* nRg */
                1036717,
                /* nBg */
                427777,
            },
            /* 12 */
            {
                /* nRg */
                1019142,
                /* nBg */
                436805,
            },
            /* 13 */
            {
                /* nRg */
                1001726,
                /* nBg */
                446148,
            },
            /* 14 */
            {
                /* nRg */
                984487,
                /* nBg */
                455816,
            },
            /* 15 */
            {
                /* nRg */
                967437,
                /* nBg */
                465788,
            },
            /* 16 */
            {
                /* nRg */
                950555,
                /* nBg */
                476074,
            },
            /* 17 */
            {
                /* nRg */
                938297,
                /* nBg */
                483813,
            },
            /* 18 */
            {
                /* nRg */
                926134,
                /* nBg */
                491719,
            },
            /* 19 */
            {
                /* nRg */
                914075,
                /* nBg */
                499793,
            },
            /* 20 */
            {
                /* nRg */
                902132,
                /* nBg */
                508025,
            },
            /* 21 */
            {
                /* nRg */
                890304,
                /* nBg */
                516413,
            },
            /* 22 */
            {
                /* nRg */
                878581,
                /* nBg */
                524959,
            },
            /* 23 */
            {
                /* nRg */
                866973,
                /* nBg */
                533662,
            },
            /* 24 */
            {
                /* nRg */
                855491,
                /* nBg */
                542523,
            },
            /* 25 */
            {
                /* nRg */
                833838,
                /* nBg */
                559898,
            },
            /* 26 */
            {
                /* nRg */
                812636,
                /* nBg */
                577818,
            },
            /* 27 */
            {
                /* nRg */
                791906,
                /* nBg */
                596283,
            },
            /* 28 */
            {
                /* nRg */
                771658,
                /* nBg */
                615273,
            },
            /* 29 */
            {
                /* nRg */
                751892,
                /* nBg */
                634766,
            },
            /* 30 */
            {
                /* nRg */
                732640,
                /* nBg */
                654773,
            },
            /* 31 */
            {
                /* nRg */
                713902,
                /* nBg */
                675251,
            },
            /* 32 */
            {
                /* nRg */
                695699,
                /* nBg */
                696213,
            },
            /* 33 */
            {
                /* nRg */
                690047,
                /* nBg */
                702944,
            },
            /* 34 */
            {
                /* nRg */
                684447,
                /* nBg */
                709729,
            },
            /* 35 */
            {
                /* nRg */
                678901,
                /* nBg */
                716555,
            },
            /* 36 */
            {
                /* nRg */
                673416,
                /* nBg */
                723423,
            },
            /* 37 */
            {
                /* nRg */
                667985,
                /* nBg */
                730333,
            },
            /* 38 */
            {
                /* nRg */
                662606,
                /* nBg */
                737296,
            },
            /* 39 */
            {
                /* nRg */
                657289,
                /* nBg */
                744290,
            },
            /* 40 */
            {
                /* nRg */
                652026,
                /* nBg */
                751336,
            },
            /* 41 */
            {
                /* nRg */
                644769,
                /* nBg */
                761266,
            },
            /* 42 */
            {
                /* nRg */
                637618,
                /* nBg */
                771270,
            },
            /* 43 */
            {
                /* nRg */
                630572,
                /* nBg */
                781357,
            },
            /* 44 */
            {
                /* nRg */
                623651,
                /* nBg */
                791528,
            },
            /* 45 */
            {
                /* nRg */
                616846,
                /* nBg */
                801762,
            },
            /* 46 */
            {
                /* nRg */
                610156,
                /* nBg */
                812091,
            },
            /* 47 */
            {
                /* nRg */
                603581,
                /* nBg */
                822482,
            },
            /* 48 */
            {
                /* nRg */
                597133,
                /* nBg */
                832957,
            },
            /* 49 */
            {
                /* nRg */
                578489,
                /* nBg */
                864792,
            },
            /* 50 */
            {
                /* nRg */
                560936,
                /* nBg */
                897246,
            },
            /* 51 */
            {
                /* nRg */
                544494,
                /* nBg */
                930286,
            },
            /* 52 */
            {
                /* nRg */
                529195,
                /* nBg */
                963862,
            },
            /* 53 */
            {
                /* nRg */
                515050,
                /* nBg */
                997940,
            },
            /* 54 */
            {
                /* nRg */
                502058,
                /* nBg */
                1032470,
            },
            /* 55 */
            {
                /* nRg */
                490262,
                /* nBg */
                1067429,
            },
            /* 56 */
            {
                /* nRg */
                479661,
                /* nBg */
                1102777,
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
                    1040187,
                    /* nBg */
                    287310,
                },
            },
            /* 1 */
            {
                /* szName[32] */
                "A",
                /* nCct */
                2856,
                /* nRadius */
                0,
                /* tCoord */
                {
                    /* nRg */
                    870318,
                    /* nBg */
                    347079,
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
                    718275,
                    /* nBg */
                    367002,
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
                    596640,
                    /* nBg */
                    612368,
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
                    639631,
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
                    489685,
                    /* nBg */
                    767558,
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
                    585105,
                    /* nBg */
                    360710,
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
                373,
                /* nGainGr */
                256,
                /* nGainGb */
                256,
                /* nGainB */
                731,
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
        8192,
        /* nLuxDarkStart */
        10240,
        /* nLuxDarkEnd */
        46080,
        /* nLuxIndoorStart */
        51200,
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
        2300,
        /* nCctMaxInner */
        7800,
        /* nCctMinOuter */
        1950,
        /* nCctMaxOuter */
        10000,
        /* nCctSplitHtoA */
        2800,
        /* nCctSplitAtoF */
        3300,
        /* nCctSplitFtoD5 */
        4600,
        /* nCctSplitD5toD6 */
        5600,
        /* nCctSplitD6toS */
        6600,
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
            {1000, 1000, 200, 200, 50, 0, 0, 0, /*0 - 7*/},
            {1000, 1000, 200, 400, 400, 100, 100, 100, /*0 - 7*/},
            {1000, 1000, 200, 400, 400, 100, 100, 100, /*0 - 7*/},
            {1000, 500, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {1000, 1000, 200, 200, 50, 0, 0, 0, /*0 - 7*/},
            {1000, 1000, 200, 400, 400, 100, 100, 100, /*0 - 7*/},
            {1000, 1000, 200, 400, 400, 100, 100, 100, /*0 - 7*/},
            {1000, 500, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {1000, 1000, 200, 200, 50, 0, 0, 0, /*0 - 7*/},
            {1000, 1000, 200, 1000, 1000, 800, 800, 800, /*0 - 7*/},
            {1000, 1000, 200, 1000, 1000, 800, 800, 800, /*0 - 7*/},
            {200, 10, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {1000, 1000, 1000, 800, 200, 100, 100, 100, /*0 - 7*/},
            {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, /*0 - 7*/},
            {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, /*0 - 7*/},
            {200, 10, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {1000, 1000, 1000, 800, 200, 100, 100, 100, /*0 - 7*/},
            {1000, 1000, 1000, 1000, 1000, 1000, 900, 800, /*0 - 7*/},
            {1000, 1000, 1000, 1000, 1000, 1000, 900, 800, /*0 - 7*/},
            {200, 10, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
            {300, 300, 300, 300, 200, 100, 100, 100, /*0 - 7*/},
            {300, 300, 300, 300, 300, 300, 300, 200, /*0 - 7*/},
            {300, 300, 300, 300, 300, 300, 300, 200, /*0 - 7*/},
            {200, 10, 0, 0, 0, 0, 0, 0, /*0 - 7*/},
        },
        /* nExtIlllumLuxWeight[32][8] */
        {
            {1000, 1000, 1000, 200, 50, 0, 0, 0, /*0 - 7*/},
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
            {512, 512, 1024, 1024, 1024, 1024, 1024, 820, /*0 - 7*/},
            {205, 205, 1024, 1024, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 0, 512, 512, 1024, 1024, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
            {0, 0, 0, 512, 1024, 1024, 1024, 820, /*0 - 7*/},
        },
        /* bMixLightEn */
        1,
        /* nMixLightProba_0_CctStd[8] */
        {450, 450, 400, 450, 600, 9998, 9998, 9998, /*0 - 7*/},
        /* nMixLightProba_100_CctStd[8] */
        {750, 750, 600, 800, 1000, 9999, 9999, 9999, /*0 - 7*/},
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
            {205, 205, 307, 410, 1024, 820, 819, 358, /*0 - 7*/},
            {205, 205, 410, 922, 1024, 820, 614, 358, /*0 - 7*/},
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
                1,
                /* nDomMinCctThresh */
                2000,
                /* nDomMaxCctThresh */
                2500,
                /* nDom2AllRatioThresh */
                409,
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
                1,
                /* nDomMinCctThresh */
                2500,
                /* nDomMaxCctThresh */
                3300,
                /* nDom2AllRatioThresh */
                409,
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
                1,
                /* nDomMinCctThresh */
                3300,
                /* nDomMaxCctThresh */
                4600,
                /* nDom2AllRatioThresh */
                409,
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
                1,
                /* nDomMinCctThresh */
                4600,
                /* nDomMaxCctThresh */
                8500,
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
        {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
        /* nPreferDstCct[8][32] */
        {
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
            {1800, 2000, 2200, 2400, 2600, 2800, 8000, 9000, 10000, 12000, /*0 - 9*/},
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
        0,
        /* nGreenCutConfid_0_Lx */
        2560000,
        /* nGreenCutConfid_100_Lx */
        1024000,
        /* nGreenCutWeight */
        102,
        /* nGreenCutBreakAngle */
        52429,
        /* nGreenCutOffsetRg */
        31457,
        /* nGreenCutOffsetBg */
        -20971,
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

const static AX_ISP_IQ_HDR_PARAM_T hdr_param_hdr_2x = {
    /* nEnable */
    1,
    /* nAutoMode */
    1,
    /* nRefMode */
    1,
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
                0, 0, 0, 0, 0, 1779, 3559, 5338, 7118, 8592, 10066, 11540, 13015, 14397, 15779, 17161, 18544, 20387, 22230, 24073, 25916, 27629, 29342, 31055, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 0 - 31*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 32 - 63*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 64 - 95*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 96 - 127*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 128 - 159*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 160 - 191*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 192 - 223*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 224 - 255*/
                32768, /*256 - 256*/
            },
            {
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 0 - 31*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 32 - 63*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 64 - 95*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 96 - 127*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 128 - 159*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 160 - 191*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 192 - 223*/
                32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768, 32768,  /* 224 - 255*/
                32768, /*256 - 256*/
            },
        },
        /* nExpWeightGain[2] */
        {0, 256, /*0 - 1*/},
    },
    /* tDgstParam */
    {
        /* nDeghostEnable */
        0,
        /* nDgstStrenThre[2] */
        {0, 1024, /*0 - 1*/},
        /* nDgstStrenLimit[2] */
        {0, 256, /*0 - 1*/},
        /* nDgstBaseFid */
        1,
    },
    /* tFusionParam */
    {
        /* nFusionProtectThreshold[2][2] */
        {
            {16191, 16192, /*0 - 1*/},
            {16191, 16192, /*0 - 1*/},
        },
    },
    /* tHdrManualParam */
    {
        /* nNoiseLutScale */
        7500,
        /* nCoarseMotMaskNoiseLvl */
        300,
        /* nCoarseMotMaskSen */
        4096,
        /* nCoarseExpMaskSen[2] */
        {28672, 28672, /*0 - 1*/},
    },
    /* tHdrAutoParam */
    {
        /* nParamGrpNum */
        16,
        /* nRefVal[16] */
        {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 182272, 262144, 262144,  262144, 262144, 262144, 262144, 262144, /*0 - 15*/},
        /* nNoiseLutScale[16] */
        {7500, 7500, 7500, 7500, 7500, 1500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, /*0 - 15*/},
        /* nCoarseMotMaskNoiseLvl[16] */
        {300, 300, 300, 300, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, /*0 - 15*/},
        /* nCoarseMotMaskSen[16] */
        {4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, 4096, /*0 - 15*/},
        /* nCoarseExpMaskSen[16][2] */
        {
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
            {28672, 28672, /*0 - 1*/},
        },
    },
};

#endif
