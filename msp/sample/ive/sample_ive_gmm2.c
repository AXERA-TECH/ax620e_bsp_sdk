/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_ive.h"

typedef struct axTEST_GMM2_T {
    AX_IVE_SRC_IMAGE_T stSrc;
    AX_IVE_DST_IMAGE_T stFg;
    AX_IVE_DST_IMAGE_T stBg;
    AX_IVE_MEM_INFO_T stModel;
    AX_IVE_GMM2_CTRL_T stGmm2Ctrl;
    FILE* pFpSrc;
    FILE* pFpSrcModel;
    FILE* pFpDstFg;
    FILE* pFpDstBg;
    FILE* pFpDstModel;
} TEST_GMM2_T;
static TEST_GMM2_T s_stTestGmm2;

/******************************************************************************
* function : parse gmm2 parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestGmm2_ParseParams(TEST_GMM2_T* pstTestGmm2, AX_CHAR *pchParamsList)
{
    cJSON *root = NULL;
    FILE *fp = fopen(pchParamsList, "r");
    if (!fp) {
        root = cJSON_Parse(pchParamsList);
        if (!root) {
            SAMPLE_IVE_PRT("Error:parse parameters from string %s failed!\n", pchParamsList);
            return AX_FAILURE;
        }
    } else {
        AX_CHAR buf[512] = {0};
        fread(buf, 1, sizeof(buf), fp);
        root = cJSON_Parse(buf);
        if (!root) {
            SAMPLE_IVE_PRT("Error:parse parameters from file %s failed!\n", pchParamsList);
            return AX_FAILURE;
        }
    }
    cJSON *item = NULL;
    item = cJSON_GetObjectItem(root, "init_var");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param init_var failed!\n");
    pstTestGmm2->stGmm2Ctrl.u14q4InitVar = item->valueint;
    item = cJSON_GetObjectItem(root, "min_var");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param min_var failed!\n");
    pstTestGmm2->stGmm2Ctrl.u14q4MinVar = item->valueint;
    item = cJSON_GetObjectItem(root, "max_var");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param max_var failed!\n");
    pstTestGmm2->stGmm2Ctrl.u14q4MaxVar = item->valueint;
    item = cJSON_GetObjectItem(root, "lr");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param learn_rate failed!\n");
    pstTestGmm2->stGmm2Ctrl.u1q7LearnRate = item->valueint;
    item = cJSON_GetObjectItem(root, "bg_r");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param bg_ratio failed!\n");
    pstTestGmm2->stGmm2Ctrl.u1q7BgRatio = item->valueint;
    item = cJSON_GetObjectItem(root, "var_thr");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param var_thr failed!\n");
    pstTestGmm2->stGmm2Ctrl.u4q4VarThr = item->valueint;
    item = cJSON_GetObjectItem(root, "var_thr_chk");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param var_thr_check failed!\n");
    pstTestGmm2->stGmm2Ctrl.u4q4VarThrCheck = item->valueint;
    item = cJSON_GetObjectItem(root, "ct");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param ct failed!\n");
    pstTestGmm2->stGmm2Ctrl.s1q7CT = item->valueint;
    item = cJSON_GetObjectItem(root, "thr");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param thr failed!\n");
    pstTestGmm2->stGmm2Ctrl.u8Thr = item->valueint;
    cJSON_Delete(root);
    if(fp)
        fclose(fp);
    SAMPLE_IVE_PRT("Parse params success!\n");
    return AX_SUCCESS;

PARSE_FAIL:
    cJSON_Delete(root);
    if(fp)
        fclose(fp);
    return AX_FAILURE;
}
/******************************************************************************
* function : test gmm2 uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestGmm2_Uninit(TEST_GMM2_T* pstTestGmm2)
{
    IVE_CMM_FREE(pstTestGmm2->stSrc.au64PhyAddr[0], pstTestGmm2->stSrc.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestGmm2->stFg.au64PhyAddr[0], pstTestGmm2->stFg.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestGmm2->stBg.au64PhyAddr[0], pstTestGmm2->stBg.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestGmm2->stModel.u64PhyAddr, pstTestGmm2->stModel.u64VirAddr);

    if (NULL != pstTestGmm2->pFpSrc) {
        fclose(pstTestGmm2->pFpSrc);
        pstTestGmm2->pFpSrc = NULL;
    }
    if (NULL != pstTestGmm2->pFpSrcModel) {
        fclose(pstTestGmm2->pFpSrcModel);
        pstTestGmm2->pFpSrcModel = NULL;
    }
    if (NULL != pstTestGmm2->pFpDstFg) {
        fclose(pstTestGmm2->pFpDstFg);
        pstTestGmm2->pFpDstFg = NULL;
    }
    if (NULL != pstTestGmm2->pFpDstBg) {
        fclose(pstTestGmm2->pFpDstBg);
        pstTestGmm2->pFpDstBg = NULL;
    }
    if (NULL != pstTestGmm2->pFpDstModel) {
        fclose(pstTestGmm2->pFpDstModel);
        pstTestGmm2->pFpDstModel = NULL;
    }

}
/******************************************************************************
* function : test gmm2 init
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestGmm2_Init(TEST_GMM2_T* pstTestGmm2, AX_CHAR* pchSrcFileName, AX_CHAR* pchSrcModelFileName,
    AX_CHAR* pchDstFgFileName,  AX_CHAR* pchDstBgFileName,  AX_CHAR* pchDstModelFileName, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    AX_IVE_IMAGE_TYPE_E enSrcImageType = (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_U8C1);
    AX_U32 u32Size = (enSrcImageType == AX_IVE_IMAGE_TYPE_U8C1) ? 48 : 64;
    memset(pstTestGmm2, 0, sizeof(TEST_GMM2_T));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestGmm2->stSrc), enSrcImageType, u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create stSrc image failed!\n", s32Ret);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestGmm2->stFg), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create stFg image failed!\n", s32Ret);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestGmm2->stBg), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[2], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create stBg image failed!\n", s32Ret);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }
    u32Size = u32Width * u32Height * u32Size;
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestGmm2->stModel), u32Size);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create gmm2 stModel failed!\n", s32Ret);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestGmm2->pFpSrc = fopen(pchSrcFileName, "rb");
    if (AX_NULL == pstTestGmm2->pFpSrc) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFileName);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }
    pstTestGmm2->pFpSrcModel = fopen(pchSrcModelFileName, "rb");
    if (AX_NULL == pstTestGmm2->pFpSrcModel) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcModelFileName);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }
    pstTestGmm2->pFpDstFg = fopen(pchDstFgFileName, "wb");
    if (AX_NULL == pstTestGmm2->pFpDstFg) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFgFileName);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }
    pstTestGmm2->pFpDstBg = fopen(pchDstBgFileName, "wb");
    if (AX_NULL == pstTestGmm2->pFpDstBg) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstBgFileName);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }
     pstTestGmm2->pFpDstModel = fopen(pchDstModelFileName, "wb");
    if (AX_NULL == pstTestGmm2->pFpDstModel) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstModelFileName);
        SAMPLE_IVE_TestGmm2_Uninit(pstTestGmm2);
        return s32Ret;
    }

    return AX_SUCCESS;
}
/******************************************************************************
* function : test gmm2
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestGmm2Proc(TEST_GMM2_T* pstTestGmm2, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestGmm2_ParseParams(pstTestGmm2, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return s32Ret;
    } else {
        pstTestGmm2->stGmm2Ctrl.u14q4InitVar = 202820;
        pstTestGmm2->stGmm2Ctrl.u14q4MinVar = 110515;
        pstTestGmm2->stGmm2Ctrl.u14q4MaxVar = 197086;
        pstTestGmm2->stGmm2Ctrl.u1q7LearnRate = 114;
        pstTestGmm2->stGmm2Ctrl.u1q7BgRatio = 124;
        pstTestGmm2->stGmm2Ctrl.u4q4VarThr = 84;
        pstTestGmm2->stGmm2Ctrl.u4q4VarThrCheck = 243;
        pstTestGmm2->stGmm2Ctrl.s1q7CT = 31;
        pstTestGmm2->stGmm2Ctrl.u8Thr = 199;
    }
    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestGmm2->stSrc), pstTestGmm2->pFpSrc);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src file failed!\n",s32Ret);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_ReadMemInfoFile(&(pstTestGmm2->stModel), pstTestGmm2->pFpSrcModel);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src model file failed!\n",s32Ret);
        return s32Ret;
    }

    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    bInstant = AX_TRUE;
    s32Ret = AX_IVE_GMM2(&IveHandle, &pstTestGmm2->stSrc, &pstTestGmm2->stFg,
        &pstTestGmm2->stBg, &pstTestGmm2->stModel, &pstTestGmm2->stGmm2Ctrl, bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_GMM2 failed!\n",s32Ret);
        return s32Ret;
    }
    s32Ret = AX_IVE_Query(IveHandle, &bFinish, bBlock);
    while (AX_ERR_IVE_QUERY_TIMEOUT == s32Ret) {
        usleep(1000*100);
        SAMPLE_IVE_PRT("AX_IVE_Query timeout, retry...\n");
        s32Ret = AX_IVE_Query(IveHandle, &bFinish, bBlock);
    }
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_Query failed!\n",s32Ret);
        return s32Ret;
    }
    AX_U64 u64EndTime = SAMPLE_COMM_IVE_GetTime_US();
    printf("Run GMM2 task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestGmm2->stFg, pstTestGmm2->pFpDstFg);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write DstFg file failed!\n");
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestGmm2->stBg, pstTestGmm2->pFpDstBg);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write DstBg file failed!\n");
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_WriteMemInfoFile(&pstTestGmm2->stModel, pstTestGmm2->pFpDstModel);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write model file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test gmm2 sample
******************************************************************************/
AX_VOID SAMPLE_IVE_GMM2_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcFile = pchSrcPath[0];
    AX_CHAR* pchSrcModelFile = pchSrcPath[1];
    AX_CHAR* pchDstFgFile = pchDstPath[0];
    AX_CHAR* pchDstBgFile = pchDstPath[1];
    AX_CHAR* pchDstModelFile = pchDstPath[2];
    if (!pchSrcFile || !pchSrcModelFile
        || !pchDstBgFile || !pchDstFgFile || !pchDstModelFile) {
        SAMPLE_IVE_PRT("Error: null pointer(src or dst path not specified)!\n");
        return;
    }

    memset(&s_stTestGmm2, 0, sizeof(TEST_GMM2_T));
    s32Ret = SAMPLE_IVE_TestGmm2_Init(&s_stTestGmm2, pchSrcFile, pchSrcModelFile, pchDstFgFile,
        pchDstBgFile, pchDstModelFile, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_TestGmm2_Init failed!\n", s32Ret);
        return;
    }

    s32Ret =  SAMPLE_IVE_TestGmm2Proc(&s_stTestGmm2, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");

    SAMPLE_IVE_TestGmm2_Uninit(&s_stTestGmm2);
    memset(&s_stTestGmm2, 0, sizeof(TEST_GMM2_T));
}

/******************************************************************************
* function : Gmm2 Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_GMM2_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestGmm2_Uninit(&s_stTestGmm2);
    memset(&s_stTestGmm2, 0, sizeof(TEST_GMM2_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
