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

typedef struct axTEST_CORNER_T {
    AX_IVE_SRC_IMAGE_T stSrc1;
    AX_IVE_SRC_IMAGE_T stSrc2;
    AX_IVE_DST_MEM_INFO_T stCorner;
    AX_IVE_DST_IMAGE_T stDst;
    AX_IVE_CORNER_DET_CTRL_T stCornerCtrl;
    FILE* pFpSrc1;
    FILE* pFpSrc2;
    FILE* pFpCorner;
    FILE* pFpDst;
} TEST_CORNER_T;
static TEST_CORNER_T s_stTestCorner;

static AX_S32 SAMPLE_IVE_Corner_GetOutCoord(AX_IVE_DST_MEM_INFO_T *pstCorner, FILE* pFpCorner)
{
    AX_IVE_CORNER_DET_MEM_T *pstCornerInfo = (AX_IVE_CORNER_DET_MEM_T *)((AX_ADDR)pstCorner->u64VirAddr);

    if(pstCorner->u32Size < sizeof(AX_IVE_CORNER_DET_MEM_T)) {
        SAMPLE_IVE_PRT("Error:fpt num info size is %d, Should be greater than or equal to %d!\n",pstCorner->u32Size, (AX_U32)sizeof(AX_IVE_CORNER_DET_MEM_T));
        return AX_FAILURE;
    }
    if(pstCornerInfo->u16CornerNum != 0) {
        if ( 1 != fwrite(pstCornerInfo->astCorner, pstCornerInfo->u16CornerNum * sizeof(AX_IVE_POINT_U16_T), 1, pFpCorner)) {
            SAMPLE_IVE_PRT("Write file fail\n");
            return AX_FAILURE;
        }
    }

    return AX_SUCCESS;
}

/******************************************************************************
* function : parse corner parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestCorner_ParseParams(TEST_CORNER_T* pstTestCorner, AX_CHAR *pchParamsList)
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
    pstTestCorner->stCornerCtrl.enMode = (AX_IVE_CORNER_DET_MODE_E)item->valueint;

    if(pstTestCorner->stCornerCtrl.enMode == AX_IVE_CORNER_DET_MODE_HARRIS) {
        item = cJSON_GetObjectItem(root, "max_num");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param max_num failed!\n");
        pstTestCorner->stCornerCtrl.u16MaxCornerNum = item->valueint;
        item = cJSON_GetObjectItem(root, "thr");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param thr failed!\n");
        pstTestCorner->stCornerCtrl.s16CornerThr = item->valueint;
        item = cJSON_GetObjectItem(root, "shift");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param shift failed!\n");
        pstTestCorner->stCornerCtrl.u8Shift = item->valueint;
        item = cJSON_GetObjectItem(root, "harris");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param harris failed!\n");
        pstTestCorner->stCornerCtrl.u1q15Harris = item->valueint;
        item = cJSON_GetObjectItem(root, "mat_scale");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mat_scale failed!\n");
        pstTestCorner->stCornerCtrl.u8MatScale = item->valueint;
    } else if(pstTestCorner->stCornerCtrl.enMode == AX_IVE_CORNER_DET_MODE_ST) {
        item = cJSON_GetObjectItem(root, "max_num");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param max_num failed!\n");
        pstTestCorner->stCornerCtrl.u16MaxCornerNum = item->valueint;
        item = cJSON_GetObjectItem(root, "thr");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param thr failed!\n");
        pstTestCorner->stCornerCtrl.s16CornerThr = item->valueint;
        item = cJSON_GetObjectItem(root, "shift");
        SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param shift failed!\n");
        pstTestCorner->stCornerCtrl.u8Shift = item->valueint;
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
* function : test corner uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestCorner_Uninit(TEST_CORNER_T* pstTestCorner)
{
    IVE_CMM_FREE(pstTestCorner->stSrc1.au64PhyAddr[0], pstTestCorner->stSrc1.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestCorner->stSrc2.au64PhyAddr[0], pstTestCorner->stSrc2.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestCorner->stCorner.u64PhyAddr, pstTestCorner->stCorner.u64VirAddr);
    IVE_CMM_FREE(pstTestCorner->stDst.au64PhyAddr[0], pstTestCorner->stDst.au64VirAddr[0]);

    if (NULL != pstTestCorner->pFpSrc1) {
        fclose(pstTestCorner->pFpSrc1);
        pstTestCorner->pFpSrc1 = NULL;
    }
    if (NULL != pstTestCorner->pFpSrc2) {
        fclose(pstTestCorner->pFpSrc2);
        pstTestCorner->pFpSrc2 = NULL;
    }
    if (NULL != pstTestCorner->pFpCorner) {
        fclose(pstTestCorner->pFpCorner);
        pstTestCorner->pFpCorner = NULL;
    }
    if (NULL != pstTestCorner->pFpDst) {
        fclose(pstTestCorner->pFpDst);
        pstTestCorner->pFpDst = NULL;
    }
}
/******************************************************************************
* function : test corner init
******************************************************************************/
static AX_S32 SAMPLE_IVE_Corner_Init(TEST_CORNER_T* pstTestCorner, AX_CHAR* pchSrcFile1Name, AX_CHAR* pchSrcFile2Name,
    AX_CHAR* pchDstFile1Name, AX_CHAR* pchDstFile2Name, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    memset(pstTestCorner, 0, sizeof(TEST_CORNER_T));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestCorner->stSrc1), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_S16C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src1 image failed!\n", s32Ret);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestCorner->stSrc2), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_S16C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src2 image failed!\n", s32Ret);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestCorner->stDst), IMAGE_TYPE_SPECIFY(as32Type[2], AX_IVE_IMAGE_TYPE_S16C1), u32Width, u32Height);
    if(AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create dst image failed!\n", s32Ret);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestCorner->stCorner), sizeof(AX_IVE_CORNER_DET_MEM_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create corner mem failed!\n", s32Ret);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestCorner->pFpSrc1 = fopen(pchSrcFile1Name, "rb");
    if (AX_NULL == pstTestCorner->pFpSrc1) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile1Name);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }
    pstTestCorner->pFpSrc2 = fopen(pchSrcFile2Name, "rb");
    if (AX_NULL == pstTestCorner->pFpSrc2) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile2Name);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }
    pstTestCorner->pFpDst = fopen(pchDstFile1Name, "wb");
    if (AX_NULL == pstTestCorner->pFpDst) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFile1Name);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }
    pstTestCorner->pFpCorner = fopen(pchDstFile2Name, "wb");
    if (AX_NULL == pstTestCorner->pFpCorner) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFile2Name);
        SAMPLE_IVE_TestCorner_Uninit(pstTestCorner);
        return s32Ret;
    }

    return AX_SUCCESS;
}
/******************************************************************************
* function : test corner
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestCornerProc(TEST_CORNER_T* pstTestCorner, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestCorner_ParseParams(pstTestCorner, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return s32Ret;
    } else {
        pstTestCorner->stCornerCtrl.enMode = AX_IVE_CORNER_DET_MODE_HARRIS;
        pstTestCorner->stCornerCtrl.u16MaxCornerNum = 0;
        pstTestCorner->stCornerCtrl.s16CornerThr = 0;
        pstTestCorner->stCornerCtrl.u8Shift = 0;
        pstTestCorner->stCornerCtrl.u1q15Harris = 0;
        pstTestCorner->stCornerCtrl.u8MatScale = 0;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestCorner->stSrc1), pstTestCorner->pFpSrc1);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src1 file failed!\n",s32Ret);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestCorner->stSrc2), pstTestCorner->pFpSrc2);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src2 file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_CornerDet(&IveHandle, &pstTestCorner->stSrc1, &pstTestCorner->stSrc2, &pstTestCorner->stCorner, &pstTestCorner->stDst, &pstTestCorner->stCornerCtrl,bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_CornerDet failed!\n",s32Ret);
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
    printf("Run corner task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestCorner->stDst, pstTestCorner->pFpDst);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write dst file failed!\n");
        return s32Ret;
    }

    s32Ret = SAMPLE_IVE_Corner_GetOutCoord(&pstTestCorner->stCorner, pstTestCorner->pFpCorner);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write fpt file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test corner calculate sample
******************************************************************************/
AX_VOID SAMPLE_IVE_Corner_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcFile1 = pchSrcPath[0];
    AX_CHAR* pchSrcFile2 = pchSrcPath[1];
    AX_CHAR* pchDstFile1 = pchDstPath[0];
    AX_CHAR* pchDstFile2 = pchDstPath[1];

    if (!pchSrcFile1 || !pchSrcFile2 || !pchDstFile1 || !pchDstFile2 ) {
        SAMPLE_IVE_PRT("Error: null pointer(src or dst path not specified)!\n");
        return;
    }

    memset(&s_stTestCorner, 0, sizeof(TEST_CORNER_T));
    s32Ret = SAMPLE_IVE_Corner_Init(&s_stTestCorner, pchSrcFile1, pchSrcFile2, pchDstFile1, pchDstFile2, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_Corner_Init failed!\n", s32Ret);
        return;
    }

    s32Ret =  SAMPLE_IVE_TestCornerProc(&s_stTestCorner, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");

    SAMPLE_IVE_TestCorner_Uninit(&s_stTestCorner);
    memset(&s_stTestCorner, 0, sizeof(TEST_CORNER_T));
}

/******************************************************************************
* function : Corner Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_Corner_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestCorner_Uninit(&s_stTestCorner);
    memset(&s_stTestCorner, 0, sizeof(TEST_CORNER_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
