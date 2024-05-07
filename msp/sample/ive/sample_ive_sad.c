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

typedef struct axTEST_SAD_T {
    AX_IVE_SRC_IMAGE_T stSrc1;
    AX_IVE_SRC_IMAGE_T stSrc2;
    AX_IVE_DST_IMAGE_T stSad;
    AX_IVE_DST_IMAGE_T stThr;
    AX_IVE_SAD_CTRL_T stSadCtrl;
    FILE* pFpSrc1;
    FILE* pFpSrc2;
    FILE* pFpSad;
    FILE* pFpThr;
} TEST_SAD_T;
static TEST_SAD_T s_stTestSad;

/******************************************************************************
* function : parse sad parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestSad_ParseParams(TEST_SAD_T* pstTestSad, AX_CHAR *pchParamsList)
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
    item = cJSON_GetObjectItem(root, "mask");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param fiter mask failed!\n");
    AX_U32 u32ArraySize = cJSON_GetArraySize(item);
    SAMPLE_IVE_CHECK_EXPR_GOTO(u32ArraySize != 25, PARSE_FAIL, "Error:u32ArraySize[%d] is not equal to 25!\n", u32ArraySize);
    for (AX_S32 i = 0; i < u32ArraySize; i++) {
        item_array = cJSON_GetArrayItem(item, i);
        pstTestSad->stSadCtrl.as8q10Mask[i] = item_array->valueint;
    }
    item = cJSON_GetObjectItem(root, "mode");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestSad->stSadCtrl.enMode = (AX_IVE_SAD_MODE_E)item->valueint;
    item = cJSON_GetObjectItem(root, "out_ctrl");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestSad->stSadCtrl.enOutCtrl = (AX_IVE_SAD_OUT_CTRL_E)item->valueint;
    item = cJSON_GetObjectItem(root, "thr_l");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestSad->stSadCtrl.u8LowThr = item->valueint;
    item = cJSON_GetObjectItem(root, "thr_h");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestSad->stSadCtrl.u8HighThr = item->valueint;
    item = cJSON_GetObjectItem(root, "min_val");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestSad->stSadCtrl.u8MinVal = item->valueint;
    item = cJSON_GetObjectItem(root, "mid_val");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestSad->stSadCtrl.u8MidVal = item->valueint;
    item = cJSON_GetObjectItem(root, "max_val");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mode failed!\n");
    pstTestSad->stSadCtrl.u8MaxVal = item->valueint;
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
* function : test sad uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestSad_Uninit(TEST_SAD_T* pstTestSad)
{
    IVE_CMM_FREE(pstTestSad->stSrc1.au64PhyAddr[0], pstTestSad->stSrc1.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestSad->stSrc2.au64PhyAddr[0], pstTestSad->stSrc2.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestSad->stSad.au64PhyAddr[0], pstTestSad->stSad.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestSad->stThr.au64PhyAddr[0], pstTestSad->stThr.au64VirAddr[0]);

    if (NULL != pstTestSad->pFpSrc1) {
        fclose(pstTestSad->pFpSrc1);
        pstTestSad->pFpSrc1 = NULL;
    }
    if (NULL != pstTestSad->pFpSrc2) {
        fclose(pstTestSad->pFpSrc2);
        pstTestSad->pFpSrc2 = NULL;
    }
    if (NULL != pstTestSad->pFpSad) {
        fclose(pstTestSad->pFpSad);
        pstTestSad->pFpSad = NULL;
    }
    if (NULL != pstTestSad->pFpThr) {
        fclose(pstTestSad->pFpThr);
        pstTestSad->pFpThr = NULL;
    }

}
/******************************************************************************
* function : test sad init
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestSad_Init(TEST_SAD_T* pstTestSad, AX_CHAR* pchSrcFileName1, AX_CHAR* pchSrcFileName2,
    AX_CHAR* pchDstFileName1, AX_CHAR* pchDstFileName2, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    memset(pstTestSad, 0, sizeof(TEST_SAD_T));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestSad->stSrc1), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src image failed!\n", s32Ret);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestSad->stSrc2), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src image failed!\n", s32Ret);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestSad->stSad), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[2], AX_IVE_IMAGE_TYPE_U8C1), ((u32Width - 1 - 1) / 4 + 1),((u32Height - 1 - 1) / 4 + 1));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create sad image failed!\n", s32Ret);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestSad->stThr), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[3], AX_IVE_IMAGE_TYPE_U8C1), ((u32Width - 1 - 1) / 4 + 1),((u32Height - 1 - 1) / 4 + 1));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create thr image failed!\n", s32Ret);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestSad->pFpSrc1 = fopen(pchSrcFileName1, "rb");
    if (AX_NULL == pstTestSad->pFpSrc1) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFileName1);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }
    pstTestSad->pFpSrc2 = fopen(pchSrcFileName2, "rb");
    if (AX_NULL == pstTestSad->pFpSrc2) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFileName2);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }
    pstTestSad->pFpSad = fopen(pchDstFileName1, "wb");
    if (AX_NULL == pstTestSad->pFpSad) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName1);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }
    pstTestSad->pFpThr = fopen(pchDstFileName2, "wb");
    if (AX_NULL == pstTestSad->pFpThr) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName2);
        SAMPLE_IVE_TestSad_Uninit(pstTestSad);
        return s32Ret;
    }

    return AX_SUCCESS;
}

/******************************************************************************
* function : test sad
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestSadProc(TEST_SAD_T* pstTestSad, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestSad_ParseParams(pstTestSad, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return s32Ret;
    } else {
        AX_S6Q10 as8q10Mask[25] = {
            0, 0, 0, 0, 40,
            0, -64488, 37430, -27681, -48659,
            0, -16709, 26667, 2023, 51858,
            0, 19455, 19648, 55833, -2102,
            0, -11678, 13204, 20532, -2051
        };
        memcpy(pstTestSad->stSadCtrl.as8q10Mask, as8q10Mask, sizeof(as8q10Mask));
        pstTestSad->stSadCtrl.enMode = AX_IVE_SAD_MODE_MB_4X4;
        pstTestSad->stSadCtrl.enOutCtrl = AX_IVE_SAD_OUT_CTRL_8BIT_BOTH;
        pstTestSad->stSadCtrl.u8LowThr = 0;
        pstTestSad->stSadCtrl.u8HighThr = 10;
        pstTestSad->stSadCtrl.u8MinVal = 1;
        pstTestSad->stSadCtrl.u8MidVal = 2;
        pstTestSad->stSadCtrl.u8MaxVal = 3;
    }
    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestSad->stSrc1), pstTestSad->pFpSrc1);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src1 file failed!\n",s32Ret);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestSad->stSrc2), pstTestSad->pFpSrc2);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src2 file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_SAD(&IveHandle, &pstTestSad->stSrc1, &pstTestSad->stSrc2,
        &pstTestSad->stSad, &pstTestSad->stThr, &pstTestSad->stSadCtrl, bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_Sad failed!\n",s32Ret);
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
    printf("Run sad task cost %lld us\n", u64EndTime - u64StartTime);

    if(pstTestSad->stSadCtrl.enOutCtrl == AX_IVE_SAD_OUT_CTRL_8BIT_BOTH ||
            pstTestSad->stSadCtrl.enOutCtrl == AX_IVE_SAD_OUT_CTRL_8BIT_SAD) {
        s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestSad->stSad, pstTestSad->pFpSad);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_IVE_PRT("Error,Write sad file failed!\n");
            return s32Ret;
        }
    }
    if(pstTestSad->stSadCtrl.enOutCtrl == AX_IVE_SAD_OUT_CTRL_8BIT_BOTH ||
        pstTestSad->stSadCtrl.enOutCtrl == AX_IVE_SAD_OUT_CTRL_THRESH) {
        s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestSad->stThr, pstTestSad->pFpThr);
        if (AX_SUCCESS != s32Ret) {
            SAMPLE_IVE_PRT("Error,Write thr file failed!\n");
            return s32Ret;
        }
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test sad sample
******************************************************************************/
AX_VOID SAMPLE_IVE_Sad_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcFile1 = pchSrcPath[0];
    AX_CHAR* pchSrcFile2 = pchSrcPath[1];
    AX_CHAR* pchDstFile1 = pchDstPath[0];
    AX_CHAR* pchDstFile2 = pchDstPath[1];
    if (!pchSrcFile1 || !pchSrcFile2 || !pchDstFile1 || !pchDstFile2) {
        SAMPLE_IVE_PRT("Error: null pointer(src or dst path not specified)!\n");
        return;
    }

    memset(&s_stTestSad, 0, sizeof(TEST_SAD_T));
    s32Ret = SAMPLE_IVE_TestSad_Init(&s_stTestSad, pchSrcFile1, pchSrcFile2, pchDstFile1, pchDstFile2, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_TestSad_Init failed!\n", s32Ret);
        return;
    }

    s32Ret =  SAMPLE_IVE_TestSadProc(&s_stTestSad, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");

    SAMPLE_IVE_TestSad_Uninit(&s_stTestSad);
    memset(&s_stTestSad, 0, sizeof(TEST_SAD_T));
}

/******************************************************************************
* function : Sad Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_Sad_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestSad_Uninit(&s_stTestSad);
    memset(&s_stTestSad, 0, sizeof(TEST_SAD_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
