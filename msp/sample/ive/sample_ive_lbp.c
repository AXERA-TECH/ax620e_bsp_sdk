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

typedef struct axTEST_Lbp_T {
    AX_IVE_SRC_IMAGE_T stSrc;
    AX_IVE_DST_IMAGE_T stDst;
    AX_IVE_LBP_CTRL_T stLbpCtrl;
    FILE* pFpSrc;
    FILE* pFpDst;
} TEST_LBP_T;
static TEST_LBP_T s_stTestLbp;

/******************************************************************************
* function : parse lbp parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestLbp_ParseParams(TEST_LBP_T* pstTestLbp, AX_CHAR *pchParamsList)
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
    pstTestLbp->stLbpCtrl.enMode = (AX_IVE_LBP_CMP_MODE_E)item->valueint;

    if(pstTestLbp->stLbpCtrl.enMode == AX_IVE_LBP_CMP_MODE_NORMAL) {
        item = cJSON_GetObjectItem(root, "s16Val");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param s16Val failed!\n");
        pstTestLbp->stLbpCtrl.un8BitThr.s16Val = item->valueint;
    } else if(pstTestLbp->stLbpCtrl.enMode == AX_IVE_LBP_CMP_MODE_ABS) {
        item = cJSON_GetObjectItem(root, "u8Val");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param u8Val failed!\n");
        pstTestLbp->stLbpCtrl.un8BitThr.u8Val = item->valueint;
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
* function : test lbp uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestLbp_Uninit(TEST_LBP_T* pstTestLbp)
{
    IVE_CMM_FREE(pstTestLbp->stSrc.au64PhyAddr[0], pstTestLbp->stSrc.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestLbp->stDst.au64PhyAddr[0], pstTestLbp->stDst.au64VirAddr[0]);

    if (NULL != pstTestLbp->pFpSrc) {
        fclose(pstTestLbp->pFpSrc);
        pstTestLbp->pFpSrc = NULL;
    }
    if (NULL != pstTestLbp->pFpDst) {
        fclose(pstTestLbp->pFpDst);
        pstTestLbp->pFpDst = NULL;
    }
}
/******************************************************************************
* function : test lbp init
******************************************************************************/
static AX_S32 SAMPLE_IVE_Lbp_Init(TEST_LBP_T* pstTestLbp, AX_CHAR* pchSrcFileName,
    AX_CHAR* pchDstFileName, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    memset(pstTestLbp, 0, sizeof(TEST_LBP_T));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestLbp->stSrc), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src image failed!\n", s32Ret);
        SAMPLE_IVE_TestLbp_Uninit(pstTestLbp);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestLbp->stDst), IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if(AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create dst image failed!\n", s32Ret);
        SAMPLE_IVE_TestLbp_Uninit(pstTestLbp);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestLbp->pFpSrc = fopen(pchSrcFileName, "rb");
    if (AX_NULL == pstTestLbp->pFpSrc) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFileName);
        SAMPLE_IVE_TestLbp_Uninit(pstTestLbp);
        return s32Ret;
    }
    pstTestLbp->pFpDst = fopen(pchDstFileName, "wb");
    if (AX_NULL == pstTestLbp->pFpDst) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName);
        SAMPLE_IVE_TestLbp_Uninit(pstTestLbp);
        return s32Ret;
    }

    return AX_SUCCESS;
}
/******************************************************************************
* function : test lbp
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestLbpProc(TEST_LBP_T* pstTestLbp, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestLbp_ParseParams(pstTestLbp, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return s32Ret;
    } else {
        pstTestLbp->stLbpCtrl.enMode = AX_IVE_LBP_CMP_MODE_NORMAL;
        pstTestLbp->stLbpCtrl.un8BitThr.s16Val = 0;
        pstTestLbp->stLbpCtrl.un8BitThr.u8Val = 0;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestLbp->stSrc), pstTestLbp->pFpSrc);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src1 file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_LBP(&IveHandle, &pstTestLbp->stSrc, &pstTestLbp->stDst, &pstTestLbp->stLbpCtrl,bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_LBP failed!\n",s32Ret);
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
    printf("Run Lbp task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestLbp->stDst, pstTestLbp->pFpDst);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write dst file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test lbp calculate sample
******************************************************************************/
AX_VOID SAMPLE_IVE_Lbp_TEST(AX_S32 as32Type[], AX_CHAR *pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
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

    memset(&s_stTestLbp, 0, sizeof(TEST_LBP_T));
    s32Ret = SAMPLE_IVE_Lbp_Init(&s_stTestLbp, pchSrcFile, pchDstFile, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_Lbp_Init failed!\n", s32Ret);
        return;
    }

    s32Ret =  SAMPLE_IVE_TestLbpProc(&s_stTestLbp, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");

    SAMPLE_IVE_TestLbp_Uninit(&s_stTestLbp);
    memset(&s_stTestLbp, 0, sizeof(TEST_LBP_T));
}

/******************************************************************************
* function : Lbp Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_Lbp_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestLbp_Uninit(&s_stTestLbp);
    memset(&s_stTestLbp, 0, sizeof(TEST_LBP_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
