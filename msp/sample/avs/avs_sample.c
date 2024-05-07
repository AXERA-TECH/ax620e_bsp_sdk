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
#include <signal.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <sys/time.h>
#include <time.h>

#include "ax_base_type.h"
#include "ax_sys_api.h"
#include "common/avs_common_api.h"

extern AX_BOOL gLoopExit;

static void SigInt(int sigNo)
{
    SAMPLE_LOG("Catch signal %d\n", sigNo);
    gLoopExit = AX_TRUE;
}

AX_S32 main(AX_S32 argc, AX_CHAR *argv[]) {
    AX_S32 s32Ret = -1;
    SAMPLE_AVS_BASE_PARA_T* pAVSBaseParam = NULL;

    pAVSBaseParam = malloc(sizeof(SAMPLE_AVS_BASE_PARA_T));
    if (pAVSBaseParam == NULL) {
        SAMPLE_ERR_LOG("SAMPLE_AVS_BASE_PARA_T malloc fail");
        return 0;
    }
    memset(pAVSBaseParam, 0 , sizeof(SAMPLE_AVS_BASE_PARA_T));

    signal(SIGINT, SigInt);

    AVSParameterDefault(pAVSBaseParam);

    s32Ret = AVSParameterGet(argc, argv, pAVSBaseParam);
    if (s32Ret) {
        // SAMPLE_ERR_LOG("Input param error\n");
        goto err0;
    }

    s32Ret = AX_SYS_Init();
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("AX_SYS_Init failed! Error Code:0x%X\n", s32Ret);
        goto err0;
    }

    s32Ret = AX_POOL_Exit();
    if(s32Ret) {
        SAMPLE_ERR_LOG("AX_POOL_Exit failed! Error Code:0x%X\n", s32Ret);
        goto err1;
    }

    s32Ret = SampleAVSUsage(pAVSBaseParam);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("SampleAVSUsage error. s32Ret:0x%x\n", s32Ret);
        goto err2;
    }

    AVSParameterFree(pAVSBaseParam);

    s32Ret = AX_POOL_Exit();
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("AX_POOL_Exit failed! Error Code:0x%X\n", s32Ret);
    }

    s32Ret = AX_SYS_Deinit();
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("AX_SYS_Deinit failed! Error Code:0x%X\n", s32Ret);
    }

    free(pAVSBaseParam);

    return 0;

err2:
    AVSParameterFree(pAVSBaseParam);
    AX_POOL_Exit();
err1:
    AX_SYS_Deinit();
err0:
    free(pAVSBaseParam);

    return -1;
}
