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

typedef struct axTEST_LK_OPTICAL_FLOW_T {
    AX_IVE_SRC_IMAGE_T stSrcPre;
    AX_IVE_SRC_IMAGE_T stSrcCur;
    AX_IVE_SRC_MEM_INFO_T stSrcPoint;
    AX_IVE_SRC_MEM_INFO_T stSrcDxDy;
    AX_IVE_DST_MEM_INFO_T stDstDxDy;
    AX_IVE_DST_MEM_INFO_T stDstStatus;
    AX_IVE_MEM_INFO_T stMv;
    AX_IVE_LK_OPTICAL_FLOW_CTRL_T stLkOptiFlowCtrl;
    FILE* pFpSrcPre;
    FILE* pFpSrcCur;
    FILE* pFpSrcPoint;
    FILE* pFpSrcDxDy;
    FILE* pFpDstDxDy;
    FILE* pFpDstStatus;
} TEST_LK_OPTICAL_FLOW_T;
static TEST_LK_OPTICAL_FLOW_T s_stTestLkOpticalFlow;

/******************************************************************************
* function : parse LkOpticalFlow parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestLkOpticalFlow_ParseParams(TEST_LK_OPTICAL_FLOW_T* pstTestLkOpticalFlow, AX_CHAR *pchParamsList)
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
    item = cJSON_GetObjectItem(root, "corner_num");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param corner_num failed!\n");
    pstTestLkOpticalFlow->stLkOptiFlowCtrl.u16CornerNum = item->valueint;
    item = cJSON_GetObjectItem(root, "pyra_scale");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param pyra_scale failed!\n");
    pstTestLkOpticalFlow->stLkOptiFlowCtrl.u3q5PyraScale = item->valueint;
    item = cJSON_GetObjectItem(root, "mat_scale");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param mat_scale failed!\n");
    pstTestLkOpticalFlow->stLkOptiFlowCtrl.u8MatScale = item->valueint;
    item = cJSON_GetObjectItem(root, "grad_compensation");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param grad_compensation failed!\n");
    pstTestLkOpticalFlow->stLkOptiFlowCtrl.u8q6GradCompensation = item->valueint;
    item = cJSON_GetObjectItem(root, "filter_weight");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param filter_weight failed!\n");
    AX_U32 u32ArraySize = cJSON_GetArraySize(item);
    SAMPLE_IVE_CHECK_EXPR_GOTO(u32ArraySize != 25, PARSE_FAIL, "Error:u32ArraySize[%d] is not equal to 25!\n", u32ArraySize);
    for (AX_S32 i = 0; i < u32ArraySize; i++) {
        item_array = cJSON_GetArrayItem(item, i);
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.s8q10FilterWeight[i] = item_array->valueint;
    }
    item = cJSON_GetObjectItem(root, "flt_g_epsilon");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param flt_g_epsilon failed!\n");
    pstTestLkOpticalFlow->stLkOptiFlowCtrl.u7q12FltGEpsilon = item->valueint;
    item = cJSON_GetObjectItem(root, "iter_epsilon");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param iter_epsilon failed!\n");
    pstTestLkOpticalFlow->stLkOptiFlowCtrl.u0q16IterEpsilon = item->valueint;
    item = cJSON_GetObjectItem(root, "max_iter");
    SAMPLE_IVE_CHECK_EXPR_GOTO(!item, PARSE_FAIL, "Error:parse param max_iter failed!\n");
    pstTestLkOpticalFlow->stLkOptiFlowCtrl.u8MaxIter = item->valueint;

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
* function : test LkOpticalFlow uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestLkOpticalFlow_Uninit(TEST_LK_OPTICAL_FLOW_T* pstTestLkOpticalFlow)
{
    IVE_CMM_FREE(pstTestLkOpticalFlow->stSrcPre.au64PhyAddr[0], pstTestLkOpticalFlow->stSrcPre.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestLkOpticalFlow->stSrcCur.au64PhyAddr[0], pstTestLkOpticalFlow->stSrcCur.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestLkOpticalFlow->stSrcPoint.u64PhyAddr, pstTestLkOpticalFlow->stSrcPoint.u64VirAddr);
    IVE_CMM_FREE(pstTestLkOpticalFlow->stSrcDxDy.u64PhyAddr, pstTestLkOpticalFlow->stSrcDxDy.u64VirAddr);
    IVE_CMM_FREE(pstTestLkOpticalFlow->stDstDxDy.u64PhyAddr, pstTestLkOpticalFlow->stDstDxDy.u64VirAddr);
    IVE_CMM_FREE(pstTestLkOpticalFlow->stDstStatus.u64PhyAddr, pstTestLkOpticalFlow->stDstStatus.u64VirAddr);
    IVE_CMM_FREE(pstTestLkOpticalFlow->stMv.u64PhyAddr, pstTestLkOpticalFlow->stMv.u64VirAddr);

    if (NULL != pstTestLkOpticalFlow->pFpSrcPre) {
        fclose(pstTestLkOpticalFlow->pFpSrcPre);
        pstTestLkOpticalFlow->pFpSrcPre = NULL;
    }
    if (NULL != pstTestLkOpticalFlow->pFpSrcCur) {
        fclose(pstTestLkOpticalFlow->pFpSrcCur);
        pstTestLkOpticalFlow->pFpSrcCur = NULL;
    }
    if (NULL != pstTestLkOpticalFlow->pFpSrcPoint) {
        fclose(pstTestLkOpticalFlow->pFpSrcPoint);
        pstTestLkOpticalFlow->pFpSrcPoint = NULL;
    }
    if (NULL != pstTestLkOpticalFlow->pFpSrcDxDy) {
        fclose(pstTestLkOpticalFlow->pFpSrcDxDy);
        pstTestLkOpticalFlow->pFpSrcDxDy = NULL;
    }
    if (NULL != pstTestLkOpticalFlow->pFpDstDxDy) {
        fclose(pstTestLkOpticalFlow->pFpDstDxDy);
        pstTestLkOpticalFlow->pFpDstDxDy = NULL;
    }
    if (NULL != pstTestLkOpticalFlow->pFpDstStatus) {
        fclose(pstTestLkOpticalFlow->pFpDstStatus);
        pstTestLkOpticalFlow->pFpDstStatus = NULL;
    }
}
/******************************************************************************
* function : test LkOpticalFlow init
******************************************************************************/
static AX_S32 SAMPLE_IVE_LkOpticalFlow_Init(TEST_LK_OPTICAL_FLOW_T* pstTestLkOpticalFlow, AX_CHAR* pchSrcFile1Name, AX_CHAR* pchSrcFile2Name,
    AX_CHAR* pchSrcFile3Name, AX_CHAR* pchSrcFile4Name, AX_CHAR* pchDstFile1Name, AX_CHAR* pchDstFile2Name, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    memset(pstTestLkOpticalFlow, 0, sizeof(TEST_LK_OPTICAL_FLOW_T));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestLkOpticalFlow->stSrcPre), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create stSrcPre image failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestLkOpticalFlow->stSrcCur), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create stSrcCur image failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestLkOpticalFlow->pFpSrcPre = fopen(pchSrcFile1Name, "rb");
    if (AX_NULL == pstTestLkOpticalFlow->pFpSrcPre) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile1Name);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }
    pstTestLkOpticalFlow->pFpSrcCur = fopen(pchSrcFile2Name, "rb");
    if (AX_NULL == pstTestLkOpticalFlow->pFpSrcCur) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile2Name);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }
    pstTestLkOpticalFlow->pFpSrcPoint = fopen(pchSrcFile3Name, "rb");
    if (AX_NULL == pstTestLkOpticalFlow->pFpSrcPoint) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile3Name);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }
    pstTestLkOpticalFlow->pFpSrcDxDy = fopen(pchSrcFile4Name, "rb");
    if (AX_NULL == pstTestLkOpticalFlow->pFpSrcDxDy) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile4Name);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }
    pstTestLkOpticalFlow->pFpDstDxDy = fopen(pchDstFile1Name, "wb");
    if (AX_NULL == pstTestLkOpticalFlow->pFpDstDxDy) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFile1Name);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }
    pstTestLkOpticalFlow->pFpDstStatus = fopen(pchDstFile2Name, "wb");
    if (AX_NULL == pstTestLkOpticalFlow->pFpDstStatus) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFile2Name);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }

    return AX_SUCCESS;
}

AX_S32 SAMPLE_IVE_TestLkOpticalFlowReadDxDy(AX_IVE_SRC_MEM_INFO_T* pstMemDxDyInfo, FILE* pFpDxDy)
{

    AX_S32 s32Ret;
    (AX_VOID)fgetc(pFpDxDy);
    if (feof(pFpDxDy)) {
        SAMPLE_IVE_PRT("end of file!\n");
        s32Ret = fseek(pFpDxDy, 0 , SEEK_SET );
        if (0 != s32Ret) {
            SAMPLE_IVE_PRT("fseek failed!\n");
            return s32Ret;
        }
    } else {
        s32Ret = fseek(pFpDxDy, -1 , SEEK_CUR );
        if (0 != s32Ret) {
            SAMPLE_IVE_PRT("fseek failed!\n");
            return s32Ret;
        }
    }
    AX_U8 *pU8 = (AX_U8 *)((AX_ADDR)pstMemDxDyInfo->u64VirAddr);
    for(AX_U32 i = 0; i < pstMemDxDyInfo->u32Size; i+=8) {
        fread(pU8 + i, 3, 1, pFpDxDy);
        *(pU8 + i + 3) = 0x00;
        fread(pU8 + i + 4, 3, 1, pFpDxDy);
        *(pU8 + i + 7) = 0x00;
    }
    return AX_SUCCESS;
}

AX_S32 SAMPLE_IVE_LKOpticalFlow_GetOutDxDyStatus(AX_U16 u16CornerNum, AX_IVE_MEM_INFO_T *pstMv, FILE* pFpDstDxDy, FILE* pFpDstStatus)
{
    AX_IVE_DxDy_S3Q20_T s3q20DxDy;
    AX_U8 *pU8MvInfo = (AX_U8 *)(AX_UL)((AX_ADDR)pstMv->u64VirAddr);
    AX_U8 *pU8DxDy = (AX_U8 *)(&s3q20DxDy);
    for(AX_U32 i = 0; i < u16CornerNum; i++) {
        if (sizeof(AX_U8) != fwrite((pU8MvInfo + i * sizeof(AX_IVE_MV_S3Q20_T)), sizeof(AX_U8), 1, pFpDstStatus)) {
            SAMPLE_IVE_PRT("Write file fail\n");
            return AX_FAILURE;
        }
        memcpy(pU8DxDy, (pU8MvInfo + i * sizeof(AX_IVE_MV_S3Q20_T) + sizeof(AX_U8)),sizeof(AX_IVE_DxDy_S3Q20_T));
        if (3 != fwrite(pU8DxDy, 1, 3, pFpDstDxDy)) {
            SAMPLE_IVE_PRT("Write file fail\n");
            return AX_FAILURE;
        }
        if (3 != fwrite(pU8DxDy + 4, 1, 3, pFpDstDxDy)) {
            SAMPLE_IVE_PRT("Write file fail\n");
            return AX_FAILURE;
        }
    }
    return AX_SUCCESS;
}

AX_S32 SAMPLE_IVE_TestLkOpticalFlowCreateMvInfo(AX_U16 u16CornerNum, AX_IVE_MEM_INFO_T *pstMv, AX_IVE_SRC_MEM_INFO_T* pstMemDxDyInfo)
{
    AX_U8 *pU8Mv = (AX_U8 *)((AX_ADDR)pstMv->u64VirAddr);
    AX_U8 *pU8DxDyInfo = (AX_U8 *)((AX_ADDR)pstMemDxDyInfo->u64VirAddr);
    for(AX_U32 i = 0; i < u16CornerNum; i++) {
        memset((AX_VOID *)(pU8Mv + (i * sizeof(AX_IVE_MV_S3Q20_T))), 0, sizeof(AX_U8));
        memcpy((AX_VOID *)(pU8Mv + (i * sizeof(AX_IVE_MV_S3Q20_T)) + sizeof(AX_U8)),
            (AX_VOID *)(pU8DxDyInfo + i * sizeof(AX_IVE_DxDy_S3Q20_T)), sizeof(AX_IVE_DxDy_S3Q20_T));
    }
    return AX_SUCCESS;
}

/******************************************************************************
* function : test LkOpticalFlow
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestLkOpticalFlowProc(TEST_LK_OPTICAL_FLOW_T* pstTestLkOpticalFlow, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestLkOpticalFlow_ParseParams(pstTestLkOpticalFlow, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return s32Ret;
    } else {
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u16CornerNum = 0;
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u3q5PyraScale = 0;
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u8MatScale = 0;
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u8q6GradCompensation = 0;
        for(AX_U32 i = 0; i < 25; i++){
            pstTestLkOpticalFlow->stLkOptiFlowCtrl.s8q10FilterWeight[i] = 0;
        }
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u7q12FltGEpsilon = 0;
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u0q16IterEpsilon = 0;
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u8MaxIter = 0;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestLkOpticalFlow->stSrcPoint),
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u16CornerNum * sizeof(AX_IVE_LK_OPTICAL_FLOW_POINT_MEM_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create SrcPoint mem failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestLkOpticalFlow->stSrcDxDy),
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u16CornerNum * sizeof(AX_IVE_LK_OPTICAL_FLOW_DXDY_MEM_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create SrcDxDy mem failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestLkOpticalFlow->stSrcPre), pstTestLkOpticalFlow->pFpSrcPre);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read srcPre file failed!\n",s32Ret);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestLkOpticalFlow->stSrcCur), pstTestLkOpticalFlow->pFpSrcCur);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read srcCur file failed!\n",s32Ret);
        return s32Ret;
    }
    s32Ret = SAMPLE_COMM_IVE_ReadMemInfoFile(&(pstTestLkOpticalFlow->stSrcPoint), pstTestLkOpticalFlow->pFpSrcPoint);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read srcPoint file failed!\n",s32Ret);
        return s32Ret;
    }
    s32Ret = SAMPLE_IVE_TestLkOpticalFlowReadDxDy(&(pstTestLkOpticalFlow->stSrcDxDy), pstTestLkOpticalFlow->pFpSrcDxDy);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read srcDxDy file failed!\n",s32Ret);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestLkOpticalFlow->stMv),
        pstTestLkOpticalFlow->stLkOptiFlowCtrl.u16CornerNum * sizeof(AX_IVE_MV_S3Q20_T));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create stMv mem failed!\n", s32Ret);
        SAMPLE_IVE_TestLkOpticalFlow_Uninit(pstTestLkOpticalFlow);
        return s32Ret;
    }

    s32Ret = SAMPLE_IVE_TestLkOpticalFlowCreateMvInfo(pstTestLkOpticalFlow->stLkOptiFlowCtrl.u16CornerNum, &(pstTestLkOpticalFlow->stMv), &(pstTestLkOpticalFlow->stSrcDxDy));
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create mv info file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_LKOpticalFlow(&IveHandle, &pstTestLkOpticalFlow->stSrcPre, &pstTestLkOpticalFlow->stSrcCur,
        &pstTestLkOpticalFlow->stSrcPoint, &pstTestLkOpticalFlow->stMv, &pstTestLkOpticalFlow->stLkOptiFlowCtrl,bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_LKOpticalFlow failed!\n",s32Ret);
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
    printf("Run LKOpticalFlow task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_IVE_LKOpticalFlow_GetOutDxDyStatus(pstTestLkOpticalFlow->stLkOptiFlowCtrl.u16CornerNum,
        &(pstTestLkOpticalFlow->stMv), pstTestLkOpticalFlow->pFpDstDxDy, pstTestLkOpticalFlow->pFpDstStatus);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write dxdy status file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test LkOpticalFlow calculate sample
******************************************************************************/
AX_VOID SAMPLE_IVE_LkOpticalFlow_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR **pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcFile1 = pchSrcPath[0];
    AX_CHAR* pchSrcFile2 = pchSrcPath[1];
    AX_CHAR* pchSrcFile3 = pchSrcPath[2];
    AX_CHAR* pchSrcFile4 = pchSrcPath[3];
    AX_CHAR* pchDstFile1 = pchDstPath[0];
    AX_CHAR* pchDstFile2 = pchDstPath[1];

    if (!pchSrcFile1 || !pchSrcFile2 || !pchSrcFile3 || !pchSrcFile4 || !pchDstFile1 || !pchDstFile2 ) {
        SAMPLE_IVE_PRT("Error: null pointer(src or dst path not specified)!\n");
        return;
    }

    memset(&s_stTestLkOpticalFlow, 0, sizeof(TEST_LK_OPTICAL_FLOW_T));
    s32Ret = SAMPLE_IVE_LkOpticalFlow_Init(&s_stTestLkOpticalFlow, pchSrcFile1, pchSrcFile2, pchSrcFile3, pchSrcFile4, pchDstFile1, pchDstFile2, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_LkOpticalFlow_Init failed!\n", s32Ret);
        return;
    }
    s32Ret =  SAMPLE_IVE_TestLkOpticalFlowProc(&s_stTestLkOpticalFlow, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");
    SAMPLE_IVE_TestLkOpticalFlow_Uninit(&s_stTestLkOpticalFlow);
    memset(&s_stTestLkOpticalFlow, 0, sizeof(TEST_LK_OPTICAL_FLOW_T));
}

/******************************************************************************
* function : LkOpticalFlow Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_LkOpticalFlow_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestLkOpticalFlow_Uninit(&s_stTestLkOpticalFlow);
    memset(&s_stTestLkOpticalFlow, 0, sizeof(TEST_LK_OPTICAL_FLOW_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
