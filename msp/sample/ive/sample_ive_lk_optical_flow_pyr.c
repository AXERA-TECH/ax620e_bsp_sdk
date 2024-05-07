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

#define MAX_LEVEL   3

typedef struct axTEST_LK_OPTICAL_FLOW_PYR_T {

    AX_IVE_SRC_IMAGE_T stSrcPrevPyr[MAX_LEVEL];
    AX_IVE_SRC_IMAGE_T stSrcNextPyr[MAX_LEVEL];
    AX_IVE_SRC_MEM_INFO_T stPrevPts;
    AX_IVE_MEM_INFO_T stNextPts;
    AX_IVE_DST_MEM_INFO_T stStatus;
    AX_IVE_LK_OPTICAL_FLOW_PYR_CTRL_T stLkOptiFlowPyrCtrl;
    FILE* pFpSrcPrevPyr[MAX_LEVEL];
    FILE* pFpSrcNextPyr[MAX_LEVEL];
    FILE* pFpstPrevPts;
    FILE* pFpSrcNextPts;
    FILE* pFpDstNextPts;
    FILE* pFpstStatus;
} TEST_LK_OPTICAL_FLOW_PYR_T;
static TEST_LK_OPTICAL_FLOW_PYR_T s_stTestLkOpticalFlowPyr;

/******************************************************************************
* function : parse LkOpticalFlow parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestLkOpticalFlowPyr_ParseParams(TEST_LK_OPTICAL_FLOW_PYR_T* pstTestLkOpticalFlowPyr, AX_CHAR *pchParamsList)
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
    cJSON *item_array = NULL;
    item = cJSON_GetObjectItem(root, "out_mode");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param corner_num failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.enOutMode = item->valueint;
    item = cJSON_GetObjectItem(root, "init_flow");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param corner_num failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.bUseInitFlow = item->valueint;
    item = cJSON_GetObjectItem(root, "max_level");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param corner_num failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u8MaxLevel = item->valueint;
    item = cJSON_GetObjectItem(root, "corner_num");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param corner_num failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u16CornerNum = item->valueint;
    item = cJSON_GetObjectItem(root, "pyra_scale");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param pyra_scale failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u3q5PyraScale = item->valueint;
    item = cJSON_GetObjectItem(root, "mat_scale");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mat_scale failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u8MatScale = item->valueint;
    item = cJSON_GetObjectItem(root, "grad_compensation");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param grad_compensation failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u8q6GradCompensation = item->valueint;
    item = cJSON_GetObjectItem(root, "filter_weight");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param filter_weight failed!\n");
    AX_U32 u32ArraySize = cJSON_GetArraySize(item);
    SAMPLE_IVE_CHECK_EXPR_GOTO(u32ArraySize != 25, PARSE_FAIL, "Error:u32ArraySize[%d] is not equal to 25!\n", u32ArraySize);
    for (AX_S32 i = 0; i < u32ArraySize; i++) {
        item_array = cJSON_GetArrayItem(item, i);
        pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.s8q10FilterWeight[i] = item_array->valueint;
    }
    item = cJSON_GetObjectItem(root, "flt_g_epsilon");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param flt_g_epsilon failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u7q12FltGEpsilon = item->valueint;
    item = cJSON_GetObjectItem(root, "iter_epsilon");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param iter_epsilon failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u0q16IterEpsilon = item->valueint;
    item = cJSON_GetObjectItem(root, "max_iter");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param max_iter failed!\n");
    pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u8MaxIter = item->valueint;

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
* function : test LkOpticalFlowPyr uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(TEST_LK_OPTICAL_FLOW_PYR_T* pstTestLkOpticalFlowPyr)
{
    for (int i = 0; i <= pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u8MaxLevel; i++) {
        IVE_CMM_FREE(pstTestLkOpticalFlowPyr->stSrcPrevPyr[i].au64PhyAddr[0], pstTestLkOpticalFlowPyr->stSrcPrevPyr[i].au64VirAddr[0]);
        IVE_CMM_FREE(pstTestLkOpticalFlowPyr->stSrcNextPyr[i].au64PhyAddr[0], pstTestLkOpticalFlowPyr->stSrcNextPyr[i].au64VirAddr[0]);

        if (NULL != pstTestLkOpticalFlowPyr->pFpSrcPrevPyr[i]) {
            fclose(pstTestLkOpticalFlowPyr->pFpSrcPrevPyr[i]);
            pstTestLkOpticalFlowPyr->pFpSrcPrevPyr[i] = NULL;
        }
        if (NULL != pstTestLkOpticalFlowPyr->pFpSrcNextPyr[i]) {
            fclose(pstTestLkOpticalFlowPyr->pFpSrcNextPyr[i]);
            pstTestLkOpticalFlowPyr->pFpSrcNextPyr[i] = NULL;
        }
    }
    IVE_CMM_FREE(pstTestLkOpticalFlowPyr->stPrevPts.u64PhyAddr, pstTestLkOpticalFlowPyr->stPrevPts.u64VirAddr);
    IVE_CMM_FREE(pstTestLkOpticalFlowPyr->stNextPts.u64PhyAddr, pstTestLkOpticalFlowPyr->stNextPts.u64VirAddr);
    IVE_CMM_FREE(pstTestLkOpticalFlowPyr->stStatus.u64PhyAddr, pstTestLkOpticalFlowPyr->stStatus.u64VirAddr);

    if (NULL != pstTestLkOpticalFlowPyr->pFpstPrevPts) {
        fclose(pstTestLkOpticalFlowPyr->pFpstPrevPts);
        pstTestLkOpticalFlowPyr->pFpstPrevPts = NULL;
    }
    if (NULL != pstTestLkOpticalFlowPyr->pFpSrcNextPts) {
        fclose(pstTestLkOpticalFlowPyr->pFpSrcNextPts);
        pstTestLkOpticalFlowPyr->pFpSrcNextPts = NULL;
    }
    if (NULL != pstTestLkOpticalFlowPyr->pFpDstNextPts) {
        fclose(pstTestLkOpticalFlowPyr->pFpDstNextPts);
        pstTestLkOpticalFlowPyr->pFpDstNextPts = NULL;
    }
    if (NULL != pstTestLkOpticalFlowPyr->pFpstStatus) {
        fclose(pstTestLkOpticalFlowPyr->pFpstStatus);
        pstTestLkOpticalFlowPyr->pFpstStatus = NULL;
    }
}
/******************************************************************************
* function : test LkOpticalFlow init
******************************************************************************/
static AX_S32 SAMPLE_IVE_LkOpticalFlowPyr_Init(TEST_LK_OPTICAL_FLOW_PYR_T* pstTestLkOpticalFlowPyr, AX_CHAR* pchSrcPrevPyrFile[],
        AX_CHAR* pchSrcNextPyrFile[], AX_CHAR* pchSrcPrevPtsFile, AX_CHAR* pchSrcNextPtsFile, AX_CHAR* pchDstNextPtsFile, AX_CHAR* pchDstStatusFile,
        AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;

    for (int i = 0; i <= pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u8MaxLevel; i++) {
        s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestLkOpticalFlowPyr->stSrcPrevPyr[i]), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_U8C1), u32Width >> i, u32Height >> i);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_IVE_PRT("Error(%#x),Create SrcPrevPyr image failed!\n", s32Ret);
            SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
            return s32Ret;
        }
        s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestLkOpticalFlowPyr->stSrcNextPyr[i]), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_U8C1), u32Width >> i, u32Height >> i);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_IVE_PRT("Error(%#x),Create SrcNextPyr image failed!\n", s32Ret);
            SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
            return s32Ret;
        }
        s32Ret = AX_FAILURE;
        pstTestLkOpticalFlowPyr->pFpSrcPrevPyr[i] = fopen(pchSrcPrevPyrFile[i], "rb");
        if (AX_NULL == pstTestLkOpticalFlowPyr->pFpSrcPrevPyr[i]) {
            SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcPrevPyrFile[i]);
            SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
            return s32Ret;
        }
        pstTestLkOpticalFlowPyr->pFpSrcNextPyr[i] = fopen(pchSrcNextPyrFile[i], "rb");
        if (AX_NULL == pstTestLkOpticalFlowPyr->pFpSrcNextPyr[i]) {
            SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcNextPyrFile[i]);
            SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
            return s32Ret;
        }
    }

    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestLkOpticalFlowPyr->stPrevPts),
        pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u16CornerNum * sizeof(AX_IVE_LK_OPTICAL_FLOW_POINT_MEM_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create PrevPts mem failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestLkOpticalFlowPyr->stNextPts),
        pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u16CornerNum * sizeof(AX_IVE_LK_OPTICAL_FLOW_POINT_MEM_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create NextPts mem failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestLkOpticalFlowPyr->stStatus),
        pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u16CornerNum * sizeof(IVE_LK_OPTICAL_FLOW_STATUS_MEM_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create Status mem failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestLkOpticalFlowPyr->pFpstPrevPts = fopen(pchSrcPrevPtsFile, "rb");
    if (AX_NULL == pstTestLkOpticalFlowPyr->pFpstPrevPts) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcPrevPtsFile);
        SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
        return s32Ret;
    }
    pstTestLkOpticalFlowPyr->pFpSrcNextPts = fopen(pchSrcNextPtsFile, "rb");
    if (AX_NULL == pstTestLkOpticalFlowPyr->pFpSrcNextPts) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcNextPtsFile);
        SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
        return s32Ret;
    }
    pstTestLkOpticalFlowPyr->pFpDstNextPts = fopen(pchDstNextPtsFile, "wb");
    if (AX_NULL == pstTestLkOpticalFlowPyr->pFpDstNextPts) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstNextPtsFile);
        SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
        return s32Ret;
    }
    pstTestLkOpticalFlowPyr->pFpstStatus = fopen(pchDstStatusFile, "wb");
    if (AX_NULL == pstTestLkOpticalFlowPyr->pFpstStatus) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstStatusFile);
        SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(pstTestLkOpticalFlowPyr);
        return s32Ret;
    }

    return AX_SUCCESS;
}

/******************************************************************************
* function : test LkOpticalFlowPyr
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestLkOpticalFlowPyrProc(TEST_LK_OPTICAL_FLOW_PYR_T* pstTestLkOpticalFlowPyr, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    for (int i = 0; i <= pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl.u8MaxLevel; i++) {
        s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestLkOpticalFlowPyr->stSrcPrevPyr[i]), pstTestLkOpticalFlowPyr->pFpSrcPrevPyr[i]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_IVE_PRT("Error(%#x),Read stSrcPrevPyr file failed!\n",s32Ret);
            return s32Ret;
        }

        s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestLkOpticalFlowPyr->stSrcNextPyr[i]), pstTestLkOpticalFlowPyr->pFpSrcNextPyr[i]);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_IVE_PRT("Error(%#x),Read stSrcNextPyr file failed!\n",s32Ret);
            return s32Ret;
        }
    }

    s32Ret = SAMPLE_COMM_IVE_ReadMemInfoFile(&(pstTestLkOpticalFlowPyr->stPrevPts), pstTestLkOpticalFlowPyr->pFpstPrevPts);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read stPrevPts file failed!\n",s32Ret);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_ReadMemInfoFile(&(pstTestLkOpticalFlowPyr->stNextPts), pstTestLkOpticalFlowPyr->pFpSrcNextPts);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read stNextPts file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_LKOpticalFlowPyr(&IveHandle, pstTestLkOpticalFlowPyr->stSrcPrevPyr, pstTestLkOpticalFlowPyr->stSrcNextPyr,
        &pstTestLkOpticalFlowPyr->stPrevPts, &pstTestLkOpticalFlowPyr->stNextPts, &pstTestLkOpticalFlowPyr->stStatus,
        &pstTestLkOpticalFlowPyr->stLkOptiFlowPyrCtrl, bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_LKOpticalFlowPyr failed!\n",s32Ret);
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
    printf("Run LKOpticalFlowPyr task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_COMM_IVE_WriteMemInfoFile(&pstTestLkOpticalFlowPyr->stNextPts, pstTestLkOpticalFlowPyr->pFpDstNextPts);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write stNextPts file failed!\n");
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_WriteMemInfoFile(&pstTestLkOpticalFlowPyr->stStatus, pstTestLkOpticalFlowPyr->pFpstStatus);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write stStatus file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test LkOpticalFlowPyr calculate sample
******************************************************************************/
AX_VOID SAMPLE_IVE_LkOpticalFlowPyr_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_S32 i = 0;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcPrevPyrFile[MAX_LEVEL] = {0};
    AX_CHAR* pchSrcNextPyrFile[MAX_LEVEL] = {0};
    AX_CHAR* pchSrcPrevPtsFile = {0};
    AX_CHAR* pchSrcNextPtsFile = {0};
    AX_CHAR* pchDstNextPtsFile = {0};
    AX_CHAR* pchDstStatusFile = {0};

    memset(&s_stTestLkOpticalFlowPyr, 0, sizeof(TEST_LK_OPTICAL_FLOW_PYR_T));
    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestLkOpticalFlowPyr_ParseParams(&s_stTestLkOpticalFlowPyr, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return;
    } else {
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.enOutMode = AX_IVE_LK_OPTICAL_FLOW_PYR_OUT_MODE_NONE;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.bUseInitFlow = AX_TRUE;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8MaxLevel = 3;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u16CornerNum = 0;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u3q5PyraScale = 0;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8MatScale = 0;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8q6GradCompensation = 0;
        for(AX_U32 i = 0; i < 25; i++){
            s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.s8q10FilterWeight[i] = 0;
        }
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u7q12FltGEpsilon = 0;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u0q16IterEpsilon = 0;
        s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8MaxIter = 0;
    }
    if (s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8MaxLevel > MAX_LEVEL) {
        SAMPLE_IVE_PRT("Error(%#x),The range of u8MaxLevel values is [0,3]!\n", s32Ret);
        return;
    }
    for (i = 0; i <= s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8MaxLevel; i++) {
        if(pchSrcPath[i] != NULL) {
            pchSrcPrevPyrFile[i] = pchSrcPath[i];
            pchSrcNextPyrFile[i] = pchSrcPath[i+s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8MaxLevel+1];
        } else {
            SAMPLE_IVE_PRT("Error: null pointer(src path not specified)!\n");
            return;
        }
    }
    i = (s_stTestLkOpticalFlowPyr.stLkOptiFlowPyrCtrl.u8MaxLevel+1)*2;
    if(pchSrcPath[i] != NULL) {
        pchSrcPrevPtsFile = pchSrcPath[i];
    } else {
        SAMPLE_IVE_PRT("Error: null pointer(srcprevpts path not specified)!\n");
        return;
    }
    i+=1;
    if(pchSrcPath[i] != NULL) {
        pchSrcNextPtsFile = pchSrcPath[i];
    } else {
        SAMPLE_IVE_PRT("Error: null pointer(srcdstnextpts path not specified)!\n");
        return;
    }

    if(pchDstPath[0] != NULL) {
        pchDstNextPtsFile = pchDstPath[0];
    } else {
        SAMPLE_IVE_PRT("Error: null pointer(dstnextpts path not specified)!\n");
        return;
    }
    if(pchDstPath[1] != NULL) {
        pchDstStatusFile = pchDstPath[1];
    } else {
        SAMPLE_IVE_PRT("Error: null pointer(dststatus path not specified)!\n");
        return;
    }

    s32Ret = SAMPLE_IVE_LkOpticalFlowPyr_Init(&s_stTestLkOpticalFlowPyr, pchSrcPrevPyrFile, pchSrcNextPyrFile,
            pchSrcPrevPtsFile, pchSrcNextPtsFile, pchDstNextPtsFile, pchDstStatusFile, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_LkOpticalFlowPyr_Init failed!\n", s32Ret);
        return;
    }
    s32Ret =  SAMPLE_IVE_TestLkOpticalFlowPyrProc(&s_stTestLkOpticalFlowPyr, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");
    SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(&s_stTestLkOpticalFlowPyr);
    memset(&s_stTestLkOpticalFlowPyr, 0, sizeof(TEST_LK_OPTICAL_FLOW_PYR_T));
}

/******************************************************************************
* function : LkOpticalFlowPyr Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_LkOpticalFlowPyr_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestLkOpticalFlowPyr_Uninit(&s_stTestLkOpticalFlowPyr);
    memset(&s_stTestLkOpticalFlowPyr, 0, sizeof(TEST_LK_OPTICAL_FLOW_PYR_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
