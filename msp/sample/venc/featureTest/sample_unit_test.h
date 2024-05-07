/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __SAMPLE_UNIT_TEST_H__
#define __SAMPLE_UNIT_TEST_H__

#include "sample_global.h"

/* #define SUPPORT_DYN_RC_MODE */

typedef AX_S32 (*UTestCase)(SAMPLE_VENC_CMD_PARA_T *pst);

typedef struct axSample_Test_Case_T
{
    SAMPLE_TESTCASE_ID_E enTestId;
    UTestCase testCase;
    TestFunction testAttrFunc;
    SAMPLE_VENC_CMD_PARA_T *pCml;
    AX_CHAR testCaseName[MAX_TEST_CASE_NAME_SIZE];
} Sample_Test_Case_T;


AX_VOID SampleTestCaseStart(SAMPLE_VENC_CMD_PARA_T *pCml);
AX_BOOL SampleInvalidEnType(AX_S32 ut, AX_PAYLOAD_TYPE_E enType, SAMPLE_VENC_RC_E rcMode);
/* Unit Test case function */
AX_S32 UTestNormal(SAMPLE_VENC_CMD_PARA_T *pHandle);
AX_S32 UTestDynamicAttr(SAMPLE_VENC_CMD_PARA_T *pHandle);

/* Test reset channel */
AX_S32 UTestResetChn(SAMPLE_VENC_CMD_PARA_T *pHandle);
AX_S32 UTestVencRoi(SAMPLE_VENC_CMD_PARA_T *pCml);
AX_S32 UTestJpegStartEncOnce(SAMPLE_VENC_CMD_PARA_T *pCml);
AX_S32 UTestSetChnAttr(SAMPLE_VENC_CMD_PARA_T *pCml);
AX_S32 UTestDynamicJpeg(SAMPLE_VENC_CMD_PARA_T *pCml);
/* select channel to get stream */
AX_S32 UTestSelectChn(SAMPLE_VENC_CMD_PARA_T *pCml);
/* OSD test */
AX_S32 UTestOSD(SAMPLE_VENC_CMD_PARA_T *pCml);
AX_S32 UTestSelect(SAMPLE_VENC_CMD_PARA_T *pCml);
AX_S32 UTestEpoll(SAMPLE_VENC_CMD_PARA_T *pCml);

#endif
