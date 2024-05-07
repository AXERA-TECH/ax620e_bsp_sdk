/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_unit_test.h"

#include "sample_dynamic_attr.h"
#include "sample_dynamic_jpeg.h"

#define VENC_TEST_CASE_INIT(ID, TEST_CASE, TEST_ATTR_FUNC)                                                        \
    {                                                                                                             \
        .enTestId = ID, .testCaseName = #ID, .testCase = TEST_CASE, .testAttrFunc = TEST_ATTR_FUNC, .pCml = NULL, \
    }

Sample_Test_Case_T gTestCaseSet[SAMPLE_MAX_TESTCASE_NUM] = {
    VENC_TEST_CASE_INIT(UT_CASE_NORMAL, UTestNormal, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_BIT_RATE, UTestDynamicAttr, SampleTestBitRate),
    VENC_TEST_CASE_INIT(UT_CASE_RESET_CHN, UTestResetChn, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_VENC_ROI, UTestDynamicAttr, SampleVencRoi),
    VENC_TEST_CASE_INIT(UT_CASE_FRAME_RATE, UTestDynamicAttr, SampleTestFrameRate),
    VENC_TEST_CASE_INIT(UT_CASE_CHN_ATTR, UTestSetChnAttr, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_RC_MODE, UTestDynamicAttr, SampleDynRcMode),
    VENC_TEST_CASE_INIT(UT_CASE_VUI, UTestDynamicAttr, SampleDynVui),
    VENC_TEST_CASE_INIT(UT_CASE_JPEG_ENCODE_ONCE, UTestJpegStartEncOnce, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_JPEG_PARAM, UTestDynamicJpeg, SampleJpegParam),
    VENC_TEST_CASE_INIT(UT_CASE_VIR_INTRA_INTERVAL, UTestDynamicAttr, SampleVirIntraInterval),
    VENC_TEST_CASE_INIT(UT_CASE_INTRA_REFRESH, UTestDynamicAttr, SampleIntraRefresh),
    VENC_TEST_CASE_INIT(UT_CASE_RESOLUTION, UTestDynamicAttr, SampleDynResolution),
    VENC_TEST_CASE_INIT(UT_CASE_REQUEST_IDR, UTestDynamicAttr, SampleRequestIDR),
    VENC_TEST_CASE_INIT(UT_CASE_SELECT_CHN, UTestSelectChn, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_SET_USR_DATA, UTestDynamicAttr, SampleSetUserData),
    VENC_TEST_CASE_INIT(UT_CASE_RATE_JAM, UTestDynamicAttr, SampleTestBitrateJamStrategy),
    VENC_TEST_CASE_INIT(UT_CASE_SUPER_FRAME, UTestDynamicAttr, SampleTestSuperFrameStrategy),
    VENC_TEST_CASE_INIT(UT_CASE_SLICE_SPLIT, UTestDynamicAttr, SampleTestSliceSplit),
    VENC_TEST_CASE_INIT(UT_CASE_JPEG_RESOLUTION, UTestDynamicJpeg, SampleJpegDynResolution),
    VENC_TEST_CASE_INIT(UT_CASE_QP_AND_GOP, UTestDynamicAttr, SampleTestGopAndQp),
    VENC_TEST_CASE_INIT(UT_CASE_OSD, UTestOSD, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_BPS_ADAPT, UTestDynamicAttr, SampleTestBpsAdapt),
    VENC_TEST_CASE_INIT(UT_CASE_GOP_LEN, UTestDynamicAttr, SampleTestGop),
    VENC_TEST_CASE_INIT(UT_CASE_BLOCK_NOBLOCK_TIMEOUT, UTestNormal, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_STD_SELECT, UTestSelect, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_STD_EPOLL, UTestEpoll, NULL),
    VENC_TEST_CASE_INIT(UT_CASE_SVC, UTestDynamicAttr, SampleVencSvc),
};

AX_VOID SampleTestCaseStart(SAMPLE_VENC_CMD_PARA_T *pCml)
{
    AX_S32 s32Ret = -1;
    AX_S32 i = 0;
    AX_S32 caseId = 0;
    AX_S32 utPass = 0, utFail = 0;
    AX_U32 ut = pCml->ut;

    for (i = 0; i < SAMPLE_MAX_TESTCASE_NUM; i++) {
        if (VENC_TEST_ALL_CASE == ut) {
            caseId = gTestCaseSet[i].enTestId;
            gTestCaseSet[i].pCml = pCml;
            gTestCaseSet[i].pCml->function = gTestCaseSet[i].testAttrFunc;
            gTestCaseSet[i].pCml->ut = caseId;
            gTestCaseSet[i].pCml->defaultUt = ut;

            if (gTestCaseSet[i].testCase) {
                SAMPLE_LOG_WARN("========== %s start. ==========\n", gTestCaseSet[i].testCaseName);
                s32Ret = gTestCaseSet[i].testCase(pCml);
                if (s32Ret) {
                    SAMPLE_LOG_ERR("====== UT Test Case: %d failed! ======\n", i);
                    utFail++;
                    continue;
                }

                SAMPLE_LOG_WARN("========== %s end. ==========\n", gTestCaseSet[i].testCaseName);
                utPass++;
            }
        } else {
            caseId = gTestCaseSet[i].enTestId;
            if (ut == caseId) {
                gTestCaseSet[i].pCml = pCml;
                gTestCaseSet[i].pCml->function = gTestCaseSet[i].testAttrFunc;
                gTestCaseSet[i].pCml->ut = caseId;
                gTestCaseSet[i].pCml->defaultUt = ut;
                if (gTestCaseSet[i].testCase) {
                    SAMPLE_LOG_WARN("========== %s start. ==========\n", gTestCaseSet[i].testCaseName);
                    s32Ret = gTestCaseSet[i].testCase(pCml);
                    if (s32Ret) {
                        SAMPLE_LOG_ERR("====== UT Test Case: %d failed! ======\n", i);
                        utFail++;
                        break;
                    }

                    SAMPLE_LOG_WARN("========== %s end. ==========\n", gTestCaseSet[i].testCaseName);
                    utPass++;

                    break;
                }
            }
        }
    }

    SAMPLE_LOG_WARN("====== All Test Case Finished! Pass: %d, Fail: %d. ======\n", utPass, utFail);
}
