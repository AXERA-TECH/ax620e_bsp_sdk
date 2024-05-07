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
#include <sys/time.h>
#include <time.h>

//#include "openssl/md5.h"
#include "ax_vdec_api.h"
#include "ax_base_type.h"
#include "ax_sys_api.h"
#include "ax_buffer_tool.h"
#include "sample_ivps_hal.h"
#include "sample_vdec_hal.h"
#include "sample_vo_hal.h"
#include "common_vdec_api.h"

#undef AX_SAMPLE_LOG_TAG
#define AX_SAMPLE_LOG_TAG "sample_vdec_ivps_vo"

#undef SAMPLE_LOG
#undef SAMPLE_ERR_LOG

#define SAMPLE_LOG(str, arg...)  do { \
        printf("[DEBUG][%s][line:%d]: "str"\n", __func__, __LINE__, ##arg); \
    } while (0)

#define SAMPLE_ERR_LOG(str, arg...)  do { \
        printf("[ERROR][%s][line:%d]: "str"\n", __func__, __LINE__, ##arg); \
    } while (0)


typedef struct axSAMPLE_VDEC_LINK_CMD_PARAM_T {
    SAMPLE_VDEC_CMD_PARAM_T stVdecCmdParam;
} SAMPLE_VDEC_LINK_CMD_PARAM_T;


AX_S32 gGrpNum = 1;
AX_S32 gLoopDecodeNumber = 1;
AX_S32 gLoopExit = 0;
AX_S32 gWriteFrames = 0;
AX_S32 userPicTest = 0;

extern AX_POOL GrpPoolId[AX_VDEC_MAX_GRP_NUM];
SAMPLE_VDEC_LINK_CMD_PARAM_T stCmd = {0};
static SAMPLE_VDEC_FUNC_ARGS_T GrpArgs[AX_VDEC_MAX_GRP_NUM];

static AX_S32 _LinkInit(SAMPLE_VDEC_CMD_PARAM_T *pstCmd, AX_S32 GrpNum)
{
    AX_S32 s32Ret = 0;
    int i = 0;
    AX_MOD_INFO_T DstMod = {0};
    AX_MOD_INFO_T SrcMod = {0};

    for (i = 0; i < GrpNum; i++) {
        if (AX_FALSE == pstCmd->bOpenIvps) {
            SrcMod.enModId = AX_ID_VDEC;
            SrcMod.s32GrpId = i + pstCmd->uStartGrpId;
            SrcMod.s32ChnId = 0;
            DstMod.enModId = AX_ID_VO;
            DstMod.s32GrpId = 0;
            DstMod.s32ChnId = i;
            s32Ret = AX_SYS_Link(&SrcMod, &DstMod);
            if (s32Ret) {
                SAMPLE_ERR_LOG("AX_SYS_Link SRC:%d, DST:%d failed, s32Ret = 0x%x\n",
                                SrcMod.enModId, DstMod.enModId, s32Ret);
                goto ERR_RET;
            }
        } else {
            SrcMod.enModId = AX_ID_VDEC;
            SrcMod.s32GrpId = i + pstCmd->uStartGrpId;
            SrcMod.s32ChnId = 0;
            DstMod.enModId = AX_ID_IVPS;
            DstMod.s32GrpId = i + pstCmd->uStartGrpId;
            DstMod.s32ChnId = 0;
            s32Ret = AX_SYS_Link(&SrcMod, &DstMod);
            if (s32Ret) {
                SAMPLE_ERR_LOG("AX_SYS_Link SRC:%d, DST:%d failed, s32Ret = 0x%x\n",
                                SrcMod.enModId, DstMod.enModId, s32Ret);
                goto ERR_RET;
            }

            SrcMod.enModId = AX_ID_IVPS;
            SrcMod.s32GrpId = i + pstCmd->uStartGrpId;
            SrcMod.s32ChnId = 0;
            DstMod.enModId = AX_ID_VO;
            DstMod.s32GrpId = 0;
            DstMod.s32ChnId = i;
            s32Ret = AX_SYS_Link(&SrcMod, &DstMod);
            if (s32Ret) {
                SAMPLE_ERR_LOG("AX_SYS_Link SRC:%d, DST:%d failed, s32Ret = 0x%x\n",
                                SrcMod.enModId, DstMod.enModId, s32Ret);
                goto ERR_RET;
            }
        }
    }

ERR_RET:
    return s32Ret;
}

static AX_S32 _LinkExit(SAMPLE_VDEC_CMD_PARAM_T *pstCmd, AX_S32 GrpNum)
{
    AX_S32 s32Ret = 0;
    int i = 0;
    AX_MOD_INFO_T DstMod = {0};
    AX_MOD_INFO_T SrcMod = {0};

    for (i = 0; i < GrpNum; i++) {
        if (AX_FALSE == pstCmd->bOpenIvps) {
            SrcMod.enModId = AX_ID_VDEC;
            SrcMod.s32GrpId = i + pstCmd->uStartGrpId;
            SrcMod.s32ChnId = 0;
            DstMod.enModId = AX_ID_VO;
            DstMod.s32GrpId = 0;
            DstMod.s32ChnId = i;
            s32Ret = AX_SYS_UnLink(&SrcMod, &DstMod);
            if (s32Ret) {
                SAMPLE_ERR_LOG("AX_SYS_UnLink SRC:%d, DST:%d failed, s32Ret=0x%x\n",
                                SrcMod.enModId, DstMod.enModId, s32Ret);
                goto ERR_RET;
            }

            SAMPLE_LOG("vdec unlink vo ret:%x\n", s32Ret);
        } else {
            SrcMod.enModId = AX_ID_IVPS;
            SrcMod.s32GrpId = i + pstCmd->uStartGrpId;
            SrcMod.s32ChnId = 0;
            DstMod.enModId = AX_ID_VO;
            DstMod.s32GrpId = 0;
            DstMod.s32ChnId = i;
            s32Ret = AX_SYS_UnLink(&SrcMod, &DstMod);
            if (s32Ret) {
                SAMPLE_ERR_LOG("AX_SYS_UnLink SRC:%d, DST:%d failed, s32Ret=0x%x\n",
                                SrcMod.enModId, DstMod.enModId, s32Ret);
                goto ERR_RET;
            }

            SAMPLE_LOG("ivps unlink vo ret:%x\n", s32Ret);

            SrcMod.enModId = AX_ID_VDEC;
            SrcMod.s32GrpId = i + pstCmd->uStartGrpId;
            SrcMod.s32ChnId = 0;
            DstMod.enModId = AX_ID_IVPS;
            DstMod.s32GrpId = i + pstCmd->uStartGrpId;
            DstMod.s32ChnId = 0;
            s32Ret = AX_SYS_UnLink(&SrcMod, &DstMod);
            if (s32Ret) {
                SAMPLE_ERR_LOG("AX_SYS_UnLink SRC:%d, DST:%d failed, s32Ret=0x%x\n",
                                SrcMod.enModId, DstMod.enModId, s32Ret);
                goto ERR_RET;
            }
            SAMPLE_LOG("vdec unlink ivps ret:%x\n", s32Ret);
        }
    }

ERR_RET:
    return s32Ret;
}


AX_S32 SAMPLE_EXIT(AX_VOID)
{
    AX_S32 s32Ret = AX_SUCCESS;
    AX_S32 sRet = -1;
    int i = 0;
    SAMPLE_VDEC_LINK_CMD_PARAM_T *pstCmd = &stCmd;
    static AX_BOOL bSampleExit = AX_FALSE;

    if (bSampleExit) goto FUNC_RET;

    s32Ret = _LinkExit(&pstCmd->stVdecCmdParam, gGrpNum);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("LinkExit error: %x\n", s32Ret);
    }

    SAMPLE_VoDeInit();

    if (pstCmd->stVdecCmdParam.bOpenIvps) {
        sRet = SampleIvpsExit();
        if (AX_SUCCESS != sRet) {
            SAMPLE_ERR_LOG("SampleIvpsExit error.\n");
            s32Ret = sRet;
        }
    }

    for (i = 0; i < gGrpNum; i++) {
        if (pstCmd->stVdecCmdParam.enFrameBufSrc == AX_POOL_SOURCE_PRIVATE) {
            sRet = VdecExitFunc(GrpArgs[i].VdecGrp);
            if (AX_SUCCESS != sRet) {
                SAMPLE_ERR_LOG("VdecExitFunc %d FAILED! VdGrp:%d ret:0x%x\n",
                                i, GrpArgs[i].VdecGrp, sRet);
                s32Ret = sRet;
            }
        } else if (pstCmd->stVdecCmdParam.enFrameBufSrc == AX_POOL_SOURCE_USER) {
            sRet = VdecUserPoolExitFunc(GrpArgs[i].VdecGrp);
            if (AX_SUCCESS != sRet) {
                SAMPLE_ERR_LOG("VdecUserPoolExitFunc %d FAILED! VdGrp:%d ret:0x%x\n",
                                i, GrpArgs[i].VdecGrp, sRet);
                s32Ret = sRet;
            }
        }
    }

    sRet = AX_VDEC_Deinit();
    if (AX_SUCCESS != sRet) {
        SAMPLE_ERR_LOG("AX_VDEC_Deinit FAILED! ret:0x%x\n", sRet);
    }

    sRet = AX_SYS_Deinit();
    if (AX_SUCCESS != sRet) {
        SAMPLE_ERR_LOG("AX_SYS_Deinit FAILED! ret:0x%x\n", sRet);
    }

    bSampleExit = AX_TRUE;

FUNC_RET:
    return s32Ret;
}

static void _SigInt(int sigNo)
{
    SAMPLE_LOG_TMP("Catch signal %d\n", sigNo);
    gLoopExit++;
    if (gLoopExit == 1) {
        SAMPLE_EXIT();
    } else if (gLoopExit > 3) {
        exit(0);
    }

    return ;
}

static AX_S32 _CaluWinRes(AX_U32 uChnNum, AX_U32 u32LayerWidth, AX_U32 u32LayerHeight, AX_U32 *u32Width, AX_U32 *u32Height)
{
    AX_U32 u32Row = 1;
    AX_U32 u32Col = 1;

    switch (uChnNum) {
    case 1:
        u32Row = 1;
        u32Col = 1;
        break;
    case 2:
        u32Row = 1;
        u32Col = 2;
        break;
    case 3:
    case 4:
        u32Row = 2;
        u32Col = 2;
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        u32Row = 2;
        u32Col = 4;
        break;
    case 9:
        u32Row = 3;
        u32Col = 3;
        break;
    default:
        u32Row = 4;
        u32Col = 4;
        break;
    }

    *u32Width   = ALIGN_DOWN(u32LayerWidth / u32Col, 2);
    *u32Height  = ALIGN_DOWN(u32LayerHeight / u32Row, 2);

    return AX_SUCCESS;
}

int main(int argc, char *argv[])
{
    extern int optind;
    AX_S32 s32Ret = -1;
    AX_S32 sRet = 0;
    AX_PAYLOAD_TYPE_E enType;
    AX_CHAR *psStreamFile = NULL;
    AX_U32 waitCnt = 0;
    int GrpNum = 1;
    AX_U32 voWidth = 0;
    AX_U32 voHeight = 0;
    AX_U32 winWidth = 0;
    AX_U32 winHeight = 0;
    SAMPLE_VO_INIT_PARAM_S stVoInitParam;

    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, _SigInt); /* ctrl + c */
    signal(SIGQUIT, _SigInt); /* ctrl + \ */
    signal(SIGTERM, _SigInt);

    SAMPLE_VDEC_LINK_CMD_PARAM_T *pstCmd = &stCmd;

    sRet = VdecDefaultParamsSet(&pstCmd->stVdecCmdParam);
    if (sRet) {
        SAMPLE_ERR_LOG("VdecDefaultParamsSet FAILED! ret:0x%x\n", sRet);
        goto ERR_RET;
    }

    sRet = VdecCmdLineParseAndCheck(argc, argv, &pstCmd->stVdecCmdParam, 0, 0);
    if (sRet) {
        SAMPLE_VoPrintReso();

        SAMPLE_ERR_LOG("VdecCmdLineParseAndCheck FAILED! ret:0x%x\n", sRet);
        goto ERR_RET;
    }

    if (argc < 2)
       SAMPLE_VoPrintReso();

    s32Ret = SAMPLE_VoGetRes(pstCmd->stVdecCmdParam.voRes, &voWidth, &voHeight);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("SAMPLE_VoGetRes FAILED! ret:0x%x\n", s32Ret);
        goto ERR_RET;
    }

    SAMPLE_LOG_TMP("============ dec res %d x %d vo res %d x %d, voType=%d, voRes=%d =========\n",
                   pstCmd->stVdecCmdParam.u32PicWidth, pstCmd->stVdecCmdParam.u32PicHeight,
                   voWidth, voHeight,
                   pstCmd->stVdecCmdParam.voType, pstCmd->stVdecCmdParam.voRes);

    pstCmd->stVdecCmdParam.bOpenIvps = 1; /* force ivps open */

    enType = pstCmd->stVdecCmdParam.enDecType;
    gGrpNum = GrpNum = pstCmd->stVdecCmdParam.uGrpCount;
    SAMPLE_LOG_TMP("main get type %d gGrpNum %d\n", enType, gGrpNum);
    if (enType != PT_H264 && enType != PT_JPEG) {
        SAMPLE_ERR_LOG("unsupport enType:%d!\n", enType);
        goto ERR_RET;
    }

    if (pstCmd->stVdecCmdParam.enInputMode != AX_VDEC_INPUT_MODE_FRAME) {
        SAMPLE_ERR_LOG("unsupport enInputMode:%d!\n", pstCmd->stVdecCmdParam.enInputMode);
        goto ERR_RET;
    }

    s32Ret = AX_SYS_Init();
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("AX_SYS_Init FAILED! ret:0x%x\n", s32Ret);
        goto ERR_RET;
    }

    s32Ret = AX_VDEC_Init(NULL);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("AX_VDEC_Init FAILED! ret:0x%x %s\n",
                        s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_SYS_DEINIT;
    }

    psStreamFile = pstCmd->stVdecCmdParam.pInputFilePath;

    /*vdec link ivps*/
    s32Ret = _LinkInit(&pstCmd->stVdecCmdParam, GrpNum);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("LinkInit error.\n");
        goto ERR_RET_SYS_DEINIT;
    }

    s32Ret = _CaluWinRes(GrpNum, voWidth, voHeight, &winWidth, &winHeight);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_ERR_LOG("LinkInit error.\n");
        goto ERR_RET_SYS_DEINIT;
    }

    if (pstCmd->stVdecCmdParam.bOpenIvps) {
        s32Ret = SampleIVPS_Init(GrpNum, pstCmd->stVdecCmdParam.uStartGrpId, winWidth, winHeight);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_ERR_LOG("SampleIVPS_Init error. s32Ret:0x%x \n", s32Ret);
            goto ERR_RET_SYS_DEINIT;
        }
    }

    memset(&stVoInitParam, 0x0, sizeof(SAMPLE_VO_INIT_PARAM_S));
    stVoInitParam.nWidth = voWidth;
    stVoInitParam.nHeight = voHeight;
    stVoInitParam.enVoIntfType = pstCmd->stVdecCmdParam.voType;
    stVoInitParam.voDev = pstCmd->stVdecCmdParam.voDev;
    stVoInitParam.enIntfSync = pstCmd->stVdecCmdParam.voRes;
    s32Ret = SAMPLE_VoInit(&stVoInitParam, GrpNum);
    if (s32Ret) {
        SAMPLE_ERR_LOG("SampleVoInit failed, ret:0x%x", s32Ret);
        goto ERR_RET_SYS_DEINIT;
    }

    pthread_t chnTids[AX_VDEC_MAX_GRP_NUM];
    AX_S32 i;

    SAMPLE_LOG_TMP("groupCnt %d \n", pstCmd->stVdecCmdParam.uGrpCount);

    memset(&GrpArgs, 0x0, sizeof(SAMPLE_VDEC_FUNC_ARGS_T) * AX_VDEC_MAX_GRP_NUM);

    for (i = 0; i < GrpNum; i++) {
        GrpArgs[i].VdecGrp = i + pstCmd->stVdecCmdParam.uStartGrpId;
        GrpArgs[i].sFile = psStreamFile;
        GrpArgs[i].pstCmd = &pstCmd->stVdecCmdParam;
        pthread_create(&chnTids[i], NULL, VdecFrameFunc, (void *)&GrpArgs[i]);
    }

    for (i = 0; i < gGrpNum; i++) {
        pthread_join(chnTids[i], NULL);
    }

    while(!gLoopExit && waitCnt <= pstCmd->stVdecCmdParam.waitTime) {
        sleep(1);
        if (pstCmd->stVdecCmdParam.waitTime)
            waitCnt++;
    }

    SAMPLE_EXIT();
    if (pstCmd->stVdecCmdParam.pInputFilePath)
        free(pstCmd->stVdecCmdParam.pInputFilePath);

    if (pstCmd->stVdecCmdParam.pOutputFilePath)
        free(pstCmd->stVdecCmdParam.pOutputFilePath);

    SAMPLE_LOG_TMP("Decode Finished! \n\n"); // Log for verify, please do not modify

    return sRet;

ERR_RET_SYS_DEINIT:
    sRet = AX_SYS_Deinit();
    if (AX_SUCCESS != sRet) {
        SAMPLE_ERR_LOG("AX_SYS_Deinit FAILED! ret:0x%x\n", sRet);
    }

ERR_RET:
    if (pstCmd->stVdecCmdParam.pInputFilePath)
        free(pstCmd->stVdecCmdParam.pInputFilePath);

    if (pstCmd->stVdecCmdParam.pOutputFilePath)
        free(pstCmd->stVdecCmdParam.pOutputFilePath);

    return s32Ret || sRet;
}
