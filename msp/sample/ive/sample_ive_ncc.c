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

typedef struct axTEST_NCC_T {
    AX_IVE_SRC_IMAGE_T stSrc1;
    AX_IVE_SRC_IMAGE_T stSrc2;
    AX_IVE_DST_MEM_INFO_T stDst;
    FILE* pFpSrc1;
    FILE* pFpSrc2;
    FILE* pFpDst1;
    FILE* pFpDst2;
    FILE* pFpDst3;
} TEST_NCC_T;
static TEST_NCC_T s_stTestNcc;

/******************************************************************************
* function : test ncc uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestNcc_Uninit(TEST_NCC_T* pstTestNcc)
{
    IVE_CMM_FREE(pstTestNcc->stSrc1.au64PhyAddr[0], pstTestNcc->stSrc1.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestNcc->stSrc2.au64PhyAddr[0], pstTestNcc->stSrc2.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestNcc->stDst.u64PhyAddr, pstTestNcc->stDst.u64VirAddr);

    if (NULL != pstTestNcc->pFpSrc1) {
        fclose(pstTestNcc->pFpSrc1);
        pstTestNcc->pFpSrc1 = NULL;
    }
    if (NULL != pstTestNcc->pFpSrc2) {
        fclose(pstTestNcc->pFpSrc2);
        pstTestNcc->pFpSrc2 = NULL;
    }
    if (NULL != pstTestNcc->pFpDst1) {
        fclose(pstTestNcc->pFpDst1);
        pstTestNcc->pFpDst1 = NULL;
    }
    if (NULL != pstTestNcc->pFpDst2) {
        fclose(pstTestNcc->pFpDst2);
        pstTestNcc->pFpDst2 = NULL;
    }
    if (NULL != pstTestNcc->pFpDst3) {
        fclose(pstTestNcc->pFpDst3);
        pstTestNcc->pFpDst3 = NULL;
    }

}
/******************************************************************************
* function : test Ncc init
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestNcc_Init(TEST_NCC_T* pstTestNcc, AX_CHAR* pchSrcFile1Name, AX_CHAR* pchSrcFile2Name,
    AX_CHAR* pchDstFileName1, AX_CHAR* pchDstFileName2, AX_CHAR* pchDstFileName3, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    memset(pstTestNcc, 0, sizeof(TEST_NCC_T));
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestNcc->stSrc1), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_S16C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src1 image failed!\n", s32Ret);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestNcc->stSrc2), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_S16C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src2 image failed!\n", s32Ret);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestNcc->stDst), sizeof(AX_IVE_NCC_DST_MEM_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create stDst mem failed!\n", s32Ret);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }
    pstTestNcc->pFpSrc1 = fopen(pchSrcFile1Name, "rb");
    if (AX_NULL == pstTestNcc->pFpSrc1) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile1Name);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }
    pstTestNcc->pFpSrc2 = fopen(pchSrcFile2Name, "rb");
    if (AX_NULL == pstTestNcc->pFpSrc2) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile2Name);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }
    pstTestNcc->pFpDst1 = fopen(pchDstFileName1, "wb");
    if (AX_NULL == pstTestNcc->pFpDst1) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName1);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }
    pstTestNcc->pFpDst2 = fopen(pchDstFileName2, "wb");
    if (AX_NULL == pstTestNcc->pFpDst2) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName2);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }
    pstTestNcc->pFpDst3 = fopen(pchDstFileName3, "wb");
    if (AX_NULL == pstTestNcc->pFpDst3) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName3);
        SAMPLE_IVE_TestNcc_Uninit(pstTestNcc);
        return s32Ret;
    }


    return AX_SUCCESS;
}

AX_S32 SAMPLE_IVE_Ncc_Out(AX_IVE_MEM_INFO_T *pstDst, FILE* pFpDst1, FILE* pFpDst2, FILE* pFpDst3)
{
    AX_IVE_NCC_DST_MEM_T *pNccDstMemInfo = (AX_IVE_NCC_DST_MEM_T *)(AX_UL)((AX_ADDR)pstDst->u64VirAddr);
    if (sizeof(AX_U64) != fwrite((AX_U8 *)(&pNccDstMemInfo->u64QuadSum1), 1, sizeof(AX_U64), pFpDst1)) {
        SAMPLE_IVE_PRT("Write file fail\n");
        return AX_FAILURE;
    }
    if (sizeof(AX_U64) != fwrite((AX_U8 *)(&pNccDstMemInfo->u64QuadSum2), 1, sizeof(AX_U64), pFpDst2)) {
        SAMPLE_IVE_PRT("Write file fail\n");
        return AX_FAILURE;
    }
    if (sizeof(AX_U64) != fwrite((AX_U8 *)(&pNccDstMemInfo->u64Numerator), 1, sizeof(AX_U64), pFpDst3)) {
        SAMPLE_IVE_PRT("Write file fail\n");
        return AX_FAILURE;
    }
    return AX_SUCCESS;
}

/******************************************************************************
* function : test ncc
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestNccProc(TEST_NCC_T* pstTestNcc)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestNcc->stSrc1), pstTestNcc->pFpSrc1);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src1 file failed!\n",s32Ret);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestNcc->stSrc2), pstTestNcc->pFpSrc2);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src2 file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_NCC(&IveHandle, &pstTestNcc->stSrc1, &pstTestNcc->stSrc2, &pstTestNcc->stDst, bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_NCC failed!\n",s32Ret);
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
    printf("Run Ncc task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_IVE_Ncc_Out(&pstTestNcc->stDst,pstTestNcc->pFpDst1, pstTestNcc->pFpDst2, pstTestNcc->pFpDst3);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write dxdy status file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test ncc sample
******************************************************************************/
AX_VOID SAMPLE_IVE_Ncc_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc)
{
    AX_S32 s32Ret;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcFile1 = pchSrcPath[0];
    AX_CHAR* pchSrcFile2 = pchSrcPath[1];
    AX_CHAR* pchDstFile1 = pchDstPath[0];
    AX_CHAR* pchDstFile2 = pchDstPath[1];
    AX_CHAR* pchDstFile3 = pchDstPath[2];
    if (!pchSrcFile1 || !pchSrcFile2 || !pchDstFile1 || !pchDstFile2 || !pchDstFile3) {
        SAMPLE_IVE_PRT("Error: null pointer(src or dst path not specified)!\n");
        return;
    }

    memset(&s_stTestNcc, 0, sizeof(TEST_NCC_T));
    s32Ret = SAMPLE_IVE_TestNcc_Init(&s_stTestNcc, pchSrcFile1, pchSrcFile2, pchDstFile1, pchDstFile2, pchDstFile3, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_TestNcc_Init failed!\n", s32Ret);
        return;
    }

    s32Ret =  SAMPLE_IVE_TestNccProc(&s_stTestNcc);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");

    SAMPLE_IVE_TestNcc_Uninit(&s_stTestNcc);
    memset(&s_stTestNcc, 0, sizeof(TEST_NCC_T));
}

/******************************************************************************
* function : Ncc Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_Ncc_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestNcc_Uninit(&s_stTestNcc);
    memset(&s_stTestNcc, 0, sizeof(TEST_NCC_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
