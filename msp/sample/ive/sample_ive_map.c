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

typedef struct axTEST_MAP_T {
    AX_IVE_SRC_IMAGE_T stSrc;
    AX_IVE_SRC_MEM_INFO_T stMap;
    AX_IVE_DST_IMAGE_T stDst;
    AX_IVE_MAP_CTRL_T stMapCtrl;
    FILE* pFpSrc;
    FILE* pFpMap;
    FILE* pFpDst;
} TEST_MAP_T;
static TEST_MAP_T s_stTestMap;

/******************************************************************************
* function : parse map parameters
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestMap_ParseParams(TEST_MAP_T* pstTestMap, AX_CHAR *pchParamsList)
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
    pstTestMap->stMapCtrl.enMode = (AX_IVE_MAP_MODE_E)item->valueint;
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
* function : test map uninit
******************************************************************************/
static AX_VOID SAMPLE_IVE_TestMap_Uninit(TEST_MAP_T* pstTestMap)
{
    IVE_CMM_FREE(pstTestMap->stSrc.au64PhyAddr[0], pstTestMap->stSrc.au64VirAddr[0]);
    IVE_CMM_FREE(pstTestMap->stMap.u64PhyAddr, pstTestMap->stMap.u64VirAddr);
    IVE_CMM_FREE(pstTestMap->stDst.au64PhyAddr[0], pstTestMap->stDst.au64VirAddr[0]);

    if (NULL != pstTestMap->pFpSrc) {
        fclose(pstTestMap->pFpSrc);
        pstTestMap->pFpSrc = NULL;
    }
    if (NULL != pstTestMap->pFpMap) {
        fclose(pstTestMap->pFpMap);
        pstTestMap->pFpMap = NULL;
    }
    if (NULL != pstTestMap->pFpDst) {
        fclose(pstTestMap->pFpDst);
        pstTestMap->pFpDst = NULL;
    }
}
/******************************************************************************
* function : test map init
******************************************************************************/
static AX_S32 SAMPLE_IVE_Map_Init(TEST_MAP_T* pstTestMap, AX_CHAR* pchSrcFile1Name, AX_CHAR* pchSrcFile2Name,
    AX_CHAR* pchDstFileName, AX_U32 u32Width, AX_U32 u32Height, AX_S32 as32Type[])
{
    AX_S32 s32Ret = AX_FAILURE;
    memset(pstTestMap, 0, sizeof(TEST_MAP_T));

    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestMap->stSrc), (AX_IVE_IMAGE_TYPE_E)IMAGE_TYPE_SPECIFY(as32Type[0], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create src1 image failed!\n", s32Ret);
        SAMPLE_IVE_TestMap_Uninit(pstTestMap);
        return s32Ret;
    }

    /*Note: U8_TO_U8:AX_IVE_IMAGE_TYPE_U8C1; U8_TO_S15:AX_IVE_IMAGE_TYPE_S16C1; U8_TO_U16:AX_IVE_IMAGE_TYPE_U16C1*/
    s32Ret = SAMPLE_COMM_IVE_CreateImage(&(pstTestMap->stDst), IMAGE_TYPE_SPECIFY(as32Type[1], AX_IVE_IMAGE_TYPE_U8C1), u32Width, u32Height);
    if(AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create dst image failed!\n", s32Ret);
        SAMPLE_IVE_TestMap_Uninit(pstTestMap);
        return s32Ret;
    }

    s32Ret = AX_FAILURE;
    pstTestMap->pFpSrc = fopen(pchSrcFile1Name, "rb");
    if (AX_NULL == pstTestMap->pFpSrc) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile1Name);
        SAMPLE_IVE_TestMap_Uninit(pstTestMap);
        return s32Ret;
    }
    pstTestMap->pFpMap = fopen(pchSrcFile2Name, "rb");
    if (AX_NULL == pstTestMap->pFpMap) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchSrcFile2Name);
        SAMPLE_IVE_TestMap_Uninit(pstTestMap);
        return s32Ret;
    }
    pstTestMap->pFpDst = fopen(pchDstFileName, "wb");
    if (AX_NULL == pstTestMap->pFpDst) {
        SAMPLE_IVE_PRT("Error,Open file %s failed!\n", pchDstFileName);
        SAMPLE_IVE_TestMap_Uninit(pstTestMap);
        return s32Ret;
    }

    return AX_SUCCESS;
}
/******************************************************************************
* function : test map
******************************************************************************/
static AX_S32 SAMPLE_IVE_TestMspProc(TEST_MAP_T* pstTestMap, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_U32 u32Size;
    AX_IVE_HANDLE IveHandle;
    AX_BOOL bInstant = AX_FALSE;
    AX_BOOL bBlock = AX_TRUE;
    AX_BOOL bFinish = AX_FALSE;

    if (pchParamsList) {
        s32Ret = SAMPLE_IVE_TestMap_ParseParams(pstTestMap, pchParamsList);
        if (AX_SUCCESS != s32Ret)
            return s32Ret;
    } else {
        pstTestMap->stMapCtrl.enMode = AX_IVE_MAP_MODE_U8;
    }

    if(pstTestMap->stMapCtrl.enMode == AX_IVE_MAP_MODE_U8) {
        u32Size = sizeof(AX_IVE_MAP_U8BIT_LUT_MEM_T);
    } else if(pstTestMap->stMapCtrl.enMode == AX_IVE_MAP_MODE_S16) {
        u32Size = sizeof(AX_IVE_MAP_S16BIT_LUT_MEM_T);
    } else if(pstTestMap->stMapCtrl.enMode == AX_IVE_MAP_MODE_U16) {
        u32Size = sizeof(AX_IVE_MAP_U16BIT_LUT_MEM_T);
    } else {
        u32Size = 0;
    }

    s32Ret = SAMPLE_COMM_IVE_CreateMemInfo(&(pstTestMap->stMap), u32Size);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Create map mem failed!\n", s32Ret);
        SAMPLE_IVE_TestMap_Uninit(pstTestMap);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadFile(&(pstTestMap->stSrc), pstTestMap->pFpSrc);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read src1 file failed!\n",s32Ret);
        return s32Ret;
    }

    s32Ret = SAMPLE_COMM_IVE_ReadMemInfoFile(&(pstTestMap->stMap), pstTestMap->pFpMap);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),Read map file failed!\n",s32Ret);
        return s32Ret;
    }

    bInstant = AX_TRUE;
    AX_U64 u64StartTime = SAMPLE_COMM_IVE_GetTime_US();
    s32Ret = AX_IVE_Map(&IveHandle, &pstTestMap->stSrc, &pstTestMap->stMap, &pstTestMap->stDst, &pstTestMap->stMapCtrl,bInstant);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),AX_IVE_Map failed!\n",s32Ret);
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
    printf("Run Map task cost %lld us\n", u64EndTime - u64StartTime);

    s32Ret = SAMPLE_COMM_IVE_WriteFile(&pstTestMap->stDst, pstTestMap->pFpDst);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error,Write dst file failed!\n");
        return s32Ret;
    }

    return s32Ret;
}
/******************************************************************************
* function : Show test map calculate sample
******************************************************************************/
AX_VOID SAMPLE_IVE_Map_TEST(AX_S32 as32Type[], AX_CHAR **pchSrcPath, AX_CHAR *pchDstPath, AX_U32 u32WidthSrc, AX_U32 u32HeightSrc, AX_CHAR *pchParamsList)
{
    AX_S32 s32Ret;
    AX_U32 u32Width = u32WidthSrc;
    AX_U32 u32Height = u32HeightSrc;
    AX_CHAR* pchSrcFile1 = pchSrcPath[0];
    AX_CHAR* pchSrcFile2 = pchSrcPath[1];
    AX_CHAR* pchDstFile = pchDstPath;

    if (!pchSrcFile1 || !pchSrcFile2 || !pchDstFile ) {
        SAMPLE_IVE_PRT("Error: null pointer(src or dst path not specified)!\n");
        return;
    }

    memset(&s_stTestMap, 0, sizeof(TEST_MAP_T));
    s32Ret = SAMPLE_IVE_Map_Init(&s_stTestMap, pchSrcFile1, pchSrcFile2, pchDstFile, u32Width, u32Height, as32Type);
    if (AX_SUCCESS != s32Ret) {
        SAMPLE_IVE_PRT("Error(%#x),SAMPLE_IVE_Map_Init failed!\n", s32Ret);
        return;
    }

    s32Ret =  SAMPLE_IVE_TestMspProc(&s_stTestMap, pchParamsList);
    if (AX_SUCCESS == s32Ret)
        SAMPLE_IVE_PRT("Process success!\n");
    else
        SAMPLE_IVE_PRT("Error:process failed!\n");

    SAMPLE_IVE_TestMap_Uninit(&s_stTestMap);
    memset(&s_stTestMap, 0, sizeof(TEST_MAP_T));
}

/******************************************************************************
* function : Map Test sample signal handle
******************************************************************************/
AX_VOID SAMPLE_IVE_Map_TEST_HandleSig(AX_VOID)
{
    SAMPLE_IVE_TestMap_Uninit(&s_stTestMap);
    memset(&s_stTestMap, 0, sizeof(TEST_MAP_T));

    AX_IVE_Exit();
    AX_SYS_Deinit();
}
