/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_ive.h"

typedef struct axTEST_OrdStatFltBern_T {
    AX_IVE_SRC_IMAGE_T stSrc;
    AX_IVE_DST_IMAGE_T stDst;
    AX_IVE_ORD_STAT_FILTER_BERNSEN_CTRL_T stOrdStatFltBernCtrl;
    FILE* pFpSrc;
    FILE* pFpDst;
} TEST_ORD_STAT_FILTER_BERNSEN_T;
static TEST_ORD_STAT_FILTER_BERNSEN_T s_stTestOrdStatFltBern;

/******************************************************************************
* function : parse OrdStatFltBern parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestOrdStatFltBern_ParseParams(TEST_ORD_STAT_FILTER_BERNSEN_T* pstTestOrdStatFltBern, AX_CHAR *pchParamsList)
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
    item = cJSON_GetObjectItem(root, "mode");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestOrdStatFltBern->stOrdStatFltBernCtrl.enMode = (AX_IVE_ORD_STAT_FILTER_BERNSEN_MODE_E)item->valueint;

    if(pstTestOrdStatFltBern->stOrdStatFltBernCtrl.enMode == AX_IVE_ORD_STAT_FILTER_BERNSEN_MODE_BERNSEN) {
        item = cJSON_GetObjectItem(root, "cmin");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param cmin failed!\n");
        pstTestOrdStatFltBern->stOrdStatFltBernCtrl.u8Cmin = item->valueint;
        item = cJSON_GetObjectItem(root, "max_thr");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param max_thr failed!\n");
        pstTestOrdStatFltBern->stOrdStatFltBernCtrl.u8MaxThr = item->valueint;
        item = cJSON_GetObjectItem(root, "thr");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param thr failed!\n");
        pstTestOrdStatFltBern->stOrdStatFltBernCtrl.u8Thr = item->valueint;
    }
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
* function : test OrdStatFltBern uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestOrdStatFltBern_Uninit(TEST_ORD_STAT_FILTER_BERNSEN_T* pstTestOrdStatFltBern)
{
    IVE_CMM_FREE(pstTestOrdStatFltBern->stSrc.au64PhyAddr[0], pstTestOrdStatFltBern->stSrc.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestOrdStatFltBern->stDst.au64PhyAddr[0], pstTestOrdStatFltBern->stDst.au64VirAddr[0]);

    if (NULL != pstTestOrdStatFltBern->pFpSrc) {
        fclose(pstTestOrdStatFltBern->pFpSrc);
        pstTestOrdStatFltBern->pFpSrc = NULL;
    }
    if (NULL != pstTestOrdStatFltBern->pFpDst) {
        fclose(pstTestOrdStatFltBern->pFpDst);
        pstTestOrdStatFltBern->pFpDst = NULL;
    }
}
/******************************************************************************
* function : test OrdStatFltBern init
******************************************************************************/
static AX_S32 SAMPLE_IVE_OrdStatFltBern_Init(TEST_ORD_STAT_FILTER_BERNSEN_T* pstTestOrdStatFltBern, AX_CHAR* pchSrcFileName,
    AX_CHAR* pchDstFileName, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    memset(pstTestOrdStatFltBern, 0, sizeof(TEST_ORD_STAT_FILTER_BERNSEN_T));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestOrdStatFltBern->stSrc), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src image failed!\n", s32Ret);
        SAMPLE_IVE_TestOrdStatFltBern_Uninit(pstTestOrdStatFltBern);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestOrdStatFltBern->stDst), IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if(AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create dst image failed!\n", s32Ret);
        SAMPLE_IVE_TestOrdStatFltBern_Uninit(pstTestOrdStatFltBern);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestOrdStatFltBern->pFpSrc = fopen(pchSrcFileName, "rb");
    if (AX_NULL == pstTestOrdStatFltBern->pFpSrc) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFileName);
        SAMPLE_IVE_TestOrdStatFltBern_Uninit(pstTestOrdStatFltBern);
        return s32Ret;
    }
    pstTestOrdStatFltBern->pFpDst = fopen(pchDstFileName, "wb");
    if (AX_NULL == pstTestOrdStatFltBern->pFpDst) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName);
        SAMPLE_IVE_TestOrdStatFltBern_Uninit(pstTestOrdStatFltBern);
        return s32Ret;
    }

    return AX_SUCCESS;
}
/******************************************************************************
* function : test OrdStatFltBern
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestOrdStatFltBernProc(TEST_ORD_STAT_FILTER_BERNSEN_T* pstTestOrdStatFltBern, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestOrdStatFltBern_ParseParams(pstTestOrdStatFltBern, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return s32Ret;
    } else {
        pstTestOrdStatFltBern->stOrdStatFltBernCtrl.enMode = AX_IVE_ORD_STAT_FILTER_BERNSEN_MODE_MIN;
        pstTestOrdStatFltBern->stOrdStatFltBernCtrl.u8Cmin = 0;
        pstTestOrdStatFltBern->stOrdStatFltBernCtrl.u8MaxThr = 0;
        pstTestOrdStatFltBern->stOrdStatFltBernCtrl.u8Thr = 0;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestOrdStatFltBern->stSrc), pstTestOrdStatFltBern->pFpSrc);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src1 file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_OrdStatFilter_Bernsen(&IveHandle, &pstTestOrdStatFltBern->stSrc, &pstTestOrdStatFltBern->stDst, &pstTestOrdStatFltBern->stOrdStatFltBernCtrl,bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_OrdStatFilter_Bernsen failed!\n",s32Ret);
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
    printf("Run OrdStatFilter_Bernsen task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestOrdStatFltBern->stDst, pstTestOrdStatFltBern->pFpDst);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write dst file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test OrdStatFltBern calculate sample
******************************************************************************/
AX_VOID SAMPLE_IVE_OrdStatFltBern_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcFile = pchSrcPath;
    AX_CHAR* pchDstFile = pchDstPath;

    if (!pchSrcFile || !pchDstFile ) {
        SAMPLE_IVE_PRT("Error: null pointer(src or dst path not specified)!\n");
        return;
    }

    memset(&s_stTestOrdStatFltBern, 0, sizeof(TEST_ORD_STAT_FILTER_BERNSEN_T));
    s32Ret = SAMPLE_IVE_OrdStatFltBern_Init(&s_stTestOrdStatFltBern, pchSrcFile, pchDstFile, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_OrdStatFltBern_Init failed!\n", s32Ret);
        return;
    }

    s32Ret =  SAMPLE_IVE_TestOrdStatFltBernProc(&s_stTestOrdStatFltBern, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");

    SAMPLE_IVE_TestOrdStatFltBern_Uninit(&s_stTestOrdStatFltBern);
    memset(&s_stTestOrdStatFltBern, 0, sizeof(TEST_ORD_STAT_FILTER_BERNSEN_T));
}

/******************************************************************************
* function : OrdStatFltBern Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_OrdStatFltBern_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestOrdStatFltBern_Uninit(&s_stTestOrdStatFltBern);
    memset(&s_stTestOrdStatFltBern, 0, sizeof(TEST_ORD_STAT_FILTER_BERNSEN_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
