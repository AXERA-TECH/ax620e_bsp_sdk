/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#pragma once

#include "AXSingleton.h"
#include "AXThread.hpp"
#include "AppLogApi.h"
#include "ElapsedTimer.hpp"
#include "GlobalDef.h"
#include "OptionHelper.h"

#define PRINT_INTERVAL (10)
#define MAX_CHANNEL_NUM (16)

typedef enum _PRINT_HELPER_MOD_E {
    E_PH_MOD_VENC = 0,
    E_PH_MOD_JENC,
    E_PH_MOD_MJENC,
    E_PH_MOD_DUMMY_ENCODER,
    /* pending */
    E_PH_MOD_MAX
} PRINT_HELPER_MOD_E;

typedef struct _VENC_PRINT_INFO_T {
    AX_U32 nVencTargetFPS[MAX_CHANNEL_NUM];
    AX_U32 nVencReceivedFrames[MAX_CHANNEL_NUM];
    AX_U32 nVencPeriodFrames[MAX_CHANNEL_NUM];
    AX_F32 fVencFinalFps[MAX_CHANNEL_NUM];

    _VENC_PRINT_INFO_T() {
        memset(this, 0, sizeof(_VENC_PRINT_INFO_T));
    }

    AX_VOID SetTargetFPS(AX_U32 nChn, AX_U32 nTargetFPS) {
        nVencTargetFPS[nChn] = nTargetFPS;
    }

    AX_VOID Add(AX_U32 nChn) {
        if (nChn < 0 || nChn >= MAX_CHANNEL_NUM) {
            return;
        }

        if (nVencReceivedFrames[nChn] > 0) {
            /* Ignore the header frame */
            nVencPeriodFrames[nChn]++;
        }
        nVencReceivedFrames[nChn]++;
    }

    AX_VOID Reset(AX_U32 nChn) {
        nVencPeriodFrames[nChn] = 0;
        nVencReceivedFrames[nChn] = 0;
    }

    AX_VOID ClearAll() {
        memset(this, 0, sizeof(_VENC_PRINT_INFO_T));
    }

    AX_VOID Print() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nVencReceivedFrames[i] > 0) {
                AX_F32 fps = nVencPeriodFrames[i] * 1.0 / PRINT_INTERVAL;
                if (!fVencFinalFps[i]) {
                    fVencFinalFps[i] = fps;
                }
                fVencFinalFps[i] = (fVencFinalFps[i] + fps) / 2;
                nVencPeriodFrames[i] = 0;
                LOG_M_C("VENC", "[%d] fps %5.2f, recv %d", i, fps,
                        nVencReceivedFrames[i] > 0 ? nVencReceivedFrames[i] - 1 : 0); /* Ignore the header frame */
            }
        }
    }

    AX_BOOL SLT_CheckResult() {
        /* Check framerate of main path */
        AX_F64 fFPS = nVencPeriodFrames[0] * 1.0 / COptionHelper::GetInstance()->GetSLTFpsCheckFreq();
        if ((AX_U64)abs(fFPS - nVencTargetFPS[0]) > COptionHelper::GetInstance()->GetSLTFpsDiff()) {
            printf("[ERROR] FRTDemo-IPC: fps = %.2f\n", fFPS);
            return AX_FALSE;
        } else {
            AX_CHAR szHMS[16] = {0};
            LOG_M_C("VENC", "[%d] [%s] fps %5.2f, recv %d", 0, CElapsedTimer::GetInstance()->GetLocalTime(&szHMS[0], 16),
                    nVencPeriodFrames[0] * 1.0 / COptionHelper::GetInstance()->GetSLTFpsCheckFreq(),
                    nVencReceivedFrames[0] > 0 ? nVencReceivedFrames[0] - 1 : 0); /* Ignore the header frame */

            nVencPeriodFrames[0] = 0;
        }

        return AX_TRUE;
    }

    AX_VOID FinalPrint() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nVencReceivedFrames[i] > 0) {
                LOG_M_C("Final VENC", "[%d] fps %5.2f", i, fVencFinalFps[i]); /* Ignore the header frame */
            }
        }
    }
} VENC_PRINT_INFO_T;

typedef struct _JENC_PRINT_INFO_T {
    AX_U32 nJencReceivedFrames[MAX_CHANNEL_NUM];
    AX_U32 nJencPeriodFrames[MAX_CHANNEL_NUM];
    AX_F32 fJencFinalFps[MAX_CHANNEL_NUM];

    _JENC_PRINT_INFO_T() {
        memset(this, 0, sizeof(_JENC_PRINT_INFO_T));
    }

    AX_VOID Add(AX_U32 nChn) {
        if (nChn < 0 || nChn >= MAX_CHANNEL_NUM) {
            return;
        }

        if (nJencReceivedFrames[nChn] > 0) {
            /* Ignore the header frame */
            nJencPeriodFrames[nChn]++;
        }
        nJencReceivedFrames[nChn]++;
    }

    AX_VOID Reset(AX_U32 nChn) {
        nJencPeriodFrames[nChn] = 0;
        nJencReceivedFrames[nChn] = 0;
    }

    AX_VOID ClearAll() {
        memset(this, 0, sizeof(_JENC_PRINT_INFO_T));
    }

    AX_VOID Print() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nJencReceivedFrames[i] > 0) {
                AX_F32 fps = nJencPeriodFrames[i] * 1.0 / PRINT_INTERVAL;
                if (!fJencFinalFps[i]) {
                    fJencFinalFps[i] = fps;
                }
                fJencFinalFps[i] = (fJencFinalFps[i] + fps) / 2;
                nJencPeriodFrames[i] = 0;
                LOG_M_C("JENC", "[%d] fps %5.2f, recv %d", i, fps,
                        nJencReceivedFrames[i] > 0 ? nJencReceivedFrames[i] - 1 : 0); /* Ignore the header frame */
            }
        }
    }

    AX_VOID FinalPrint() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nJencReceivedFrames[i] > 0) {
                LOG_M_C("Final JENC", "[%d] fps %5.2f", i, fJencFinalFps[i]); /* Ignore the header frame */
            }
        }
    }

} JENC_PRINT_INFO_T;

typedef struct _MJENC_PRINT_INFO_T {
    AX_U32 nMJencReceivedFrames[MAX_CHANNEL_NUM];
    AX_U32 nMJencPeriodFrames[MAX_CHANNEL_NUM];
    AX_F32 fMJencFinalFps[MAX_CHANNEL_NUM];

    _MJENC_PRINT_INFO_T() {
        memset(this, 0, sizeof(_MJENC_PRINT_INFO_T));
    }

    AX_VOID Add(AX_U32 nChn) {
        if (nChn < 0 || nChn >= MAX_CHANNEL_NUM) {
            return;
        }

        if (nMJencReceivedFrames[nChn] > 0) {
            /* Ignore the header frame */
            nMJencPeriodFrames[nChn]++;
        }
        nMJencReceivedFrames[nChn]++;
    }

    AX_VOID Reset(AX_U32 nChn) {
        nMJencPeriodFrames[nChn] = 0;
        nMJencReceivedFrames[nChn] = 0;
    }

    AX_VOID ClearAll() {
        memset(this, 0, sizeof(_MJENC_PRINT_INFO_T));
    }

    AX_VOID Print() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nMJencReceivedFrames[i] > 0) {
                AX_F32 fps = nMJencPeriodFrames[i] * 1.0 / PRINT_INTERVAL;
                if (!fMJencFinalFps[i]) {
                    fMJencFinalFps[i] = fps;
                }
                fMJencFinalFps[i] = (fMJencFinalFps[i] + fps) / 2;
                nMJencPeriodFrames[i] = 0;
                LOG_M_C("MJPG", "[%d] fps %5.2f, recv %d", i, fps,
                        nMJencReceivedFrames[i] > 0 ? nMJencReceivedFrames[i] - 1 : 0); /* Ignore the header frame */
            }
        }
    }

    AX_VOID FinalPrint() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nMJencReceivedFrames[i] > 0) {
                LOG_M_C("Final MJPG", "[%d] fps %5.2f", i, fMJencFinalFps[i]); /* Ignore the header frame */
            }
        }
    }
} MJENC_PRINT_INFO_T;

typedef struct _DUMMY_ENCODER_PRINT_INFO_T {
    AX_U32 nDummyEncReceivedFrames[MAX_CHANNEL_NUM];
    AX_U32 nDummyEncPeriodFrames[MAX_CHANNEL_NUM];
    AX_F32 fDummyEncFinalFps[MAX_CHANNEL_NUM];

    _DUMMY_ENCODER_PRINT_INFO_T() {
        memset(this, 0, sizeof(_DUMMY_ENCODER_PRINT_INFO_T));
    }

    AX_VOID Add(AX_U32 nChn) {
        if (nChn < 0 || nChn >= MAX_CHANNEL_NUM) {
            return;
        }

        if (nDummyEncReceivedFrames[nChn] > 0) {
            /* Ignore the header frame */
            nDummyEncPeriodFrames[nChn]++;
        }
        nDummyEncReceivedFrames[nChn]++;
    }

    AX_VOID Reset(AX_U32 nChn) {
        nDummyEncPeriodFrames[nChn] = 0;
        nDummyEncReceivedFrames[nChn] = 0;
    }

    AX_VOID ClearAll() {
        memset(this, 0, sizeof(_DUMMY_ENCODER_PRINT_INFO_T));
    }

    AX_VOID Print() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nDummyEncReceivedFrames[i] > 0) {
                AX_F32 fps = nDummyEncPeriodFrames[i] * 1.0 / PRINT_INTERVAL;
                if (!fDummyEncFinalFps[i]) {
                    fDummyEncFinalFps[i] = fps;
                }
                fDummyEncFinalFps[i] = (fDummyEncFinalFps[i] + fps) / 2;
                nDummyEncPeriodFrames[i] = 0;
                LOG_M_C("DUMMY_ENC", "[%d] fps %5.2f, recv %d", i, fps,
                        nDummyEncReceivedFrames[i] > 0 ? nDummyEncReceivedFrames[i] - 1 : 0); /* Ignore the header frame */
            }
        }
    }

    AX_VOID FinalPrint() {
        for (AX_U32 i = 0; i < MAX_CHANNEL_NUM; i++) {
            if (nDummyEncReceivedFrames[i] > 0) {
                LOG_M_C("Final DUMMY_ENC", "[%d] fps %5.2f", i, fDummyEncFinalFps[i]); /* Ignore the header frame */
            }
        }
    }

} DUMMY_ENCODER_PRINT_INFO_T;

/**
 * (frame)statistics info printer
 */
class CPrintHelper final : public CAXSingleton<CPrintHelper> {
    friend class CAXSingleton<CPrintHelper>;

public:
    AX_VOID Start();
    AX_VOID Stop();
    AX_VOID Add(PRINT_HELPER_MOD_E eModType, AX_U32 nChn);
    AX_VOID Reset(PRINT_HELPER_MOD_E eModType, AX_U32 nChn);
#ifdef SLT
    AX_VOID SetSLTTargetFPS(PRINT_HELPER_MOD_E eModType, AX_U32 nChn, AX_U32 nTargetFPS);
    AX_S32 GetSLTResult() const;
    AX_VOID SetSLTResult(AX_S32 nRet);
#endif
    AX_S32 GetVencFramerate(AX_U32 nChn);
    AX_VOID FinalPrint();

private:
    CPrintHelper(AX_VOID) = default;
    ~CPrintHelper(AX_VOID) = default;

protected:
    AX_VOID PrintThreadFunc(CPrintHelper* pCaller);
#ifdef SLT
    AX_VOID SLTThreadFunc(CPrintHelper* pCaller);
#endif

private:
    AX_BOOL m_bEnableStart{AX_FALSE};
    AX_U64 m_nTickStart{0};
    AX_U64 m_nTickEnd{0};

    std::thread m_hPrintThread;
    AX_BOOL m_bPrintThreadWorking{AX_FALSE};
    AX_BOOL m_bSLTThreadWorking{AX_FALSE};
    AX_S32 m_nSLTResult{-1}; /* -1: Init; 0: OK; 1: Fail; 2: Reach Timeout */

    /* statistics info (pending) */
    VENC_PRINT_INFO_T m_stVencStatisticsInfo;
    JENC_PRINT_INFO_T m_stJencStatisticsInfo;
    MJENC_PRINT_INFO_T m_stMJencStatisticsInfo;
    DUMMY_ENCODER_PRINT_INFO_T m_stDummyEncoderStatisticsInfo;
};
