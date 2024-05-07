/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

#include "ax_isp_api.h"
#include "sample_vin.h"
#include "common_sys.h"
#include "common_hw.h"
#include "common_vin.h"
#include "common_cam.h"
#include "common_isp.h"
#include "ax_vin_error_code.h"
#include "common_nt.h"
#include "sample_case_dcg_vs.h"

COMMON_SYS_POOL_CFG_T gtSysCommPoolOs04a10DcgHdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 3, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolOs04a10DcgHdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 8, AX_COMPRESS_MODE_LOSSY, 4},      /* vin raw10 use */
};

COMMON_SYS_POOL_CFG_T gtSysCommPoolOs04a10DcgVsHdr[] = {
    {2688, 1520, 2688, AX_FORMAT_YUV420_SEMIPLANAR, 6, AX_COMPRESS_MODE_LOSSY, 4},    /* vin nv21/nv21 use */
};

COMMON_SYS_POOL_CFG_T gtPrivatePoolOs04a10DcgVsHdr[] = {
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_LOSSY, 4},
    {2688, 1520, 2688, AX_FORMAT_BAYER_RAW_10BPP_PACKED, 7, AX_COMPRESS_MODE_NONE, 0},      /* vin raw10 use */
};

static AX_CAMERA_T gCams[MAX_CAMERAS] = {0};
static volatile AX_S32 gLoopExit = 0;
extern AX_CHIP_TYPE_E AX_SYS_GetChipType(AX_VOID);

static AX_VOID __sigint(int iSigNo)
{
    COMM_ISP_PRT("Catch signal %d\n", iSigNo);
    gLoopExit = 1;

    return ;
}

static AX_VOID __cal_dump_pool(COMMON_SYS_POOL_CFG_T pool[], AX_SNS_HDR_MODE_E eHdrMode, AX_S32 nFrameNum)
{
    if (NULL == pool) {
        return;
    }
    if (nFrameNum > 0) {
        switch (eHdrMode) {
        case AX_SNS_LINEAR_MODE:
            pool[0].nBlkCnt += nFrameNum;
            break;

        case AX_SNS_HDR_2X_MODE:
            pool[0].nBlkCnt += nFrameNum * 2;
            break;

        case AX_SNS_HDR_3X_MODE:
            pool[0].nBlkCnt += nFrameNum * 3;
            break;

        case AX_SNS_HDR_4X_MODE:
            pool[0].nBlkCnt += nFrameNum * 4;
            break;

        default:
            pool[0].nBlkCnt += nFrameNum;
            break;
        }
    }
}

static AX_VOID __set_pipe_hdr_mode(AX_U32 *pHdrSel, AX_SNS_HDR_MODE_E eHdrMode)
{
    if (NULL == pHdrSel) {
        return;
    }

    switch (eHdrMode) {
    case AX_SNS_LINEAR_MODE:
        *pHdrSel = 0x1;
        break;

    case AX_SNS_HDR_2X_MODE:
        *pHdrSel = 0x1 | 0x2;
        break;

    case AX_SNS_HDR_3X_MODE:
        *pHdrSel = 0x1 | 0x2 | 0x4;
        break;

    case AX_SNS_HDR_4X_MODE:
        *pHdrSel = 0x1 | 0x2 | 0x4 | 0x8;
        break;

    default:
        *pHdrSel = 0x1;
        break;
    }
}

static AX_VOID __set_vin_attr(AX_CAMERA_T *pCam, SAMPLE_SNS_TYPE_E eSnsType, AX_SNS_HDR_MODE_E eHdrMode,
                              COMMON_VIN_MODE_E eSysMode, AX_BOOL bAiispEnable)
{
    pCam->eSnsType = eSnsType;
    pCam->tSnsAttr.eSnsMode = eHdrMode;
    pCam->tDevAttr.eSnsMode = eHdrMode;
    pCam->eSysMode = eSysMode;
    pCam->tPipeAttr[pCam->nPipeId].eSnsMode = eHdrMode;
    pCam->tPipeAttr[pCam->nPipeId].bAiIspEnable = bAiispEnable;

    if (COMMON_VIN_TPG == eSysMode) {
        pCam->tDevAttr.eSnsIntfType = AX_SNS_INTF_TYPE_TPG;
    }

    if (COMMON_VIN_LOADRAW == eSysMode) {
        pCam->bEnableDev = AX_FALSE;
    } else {
        pCam->bEnableDev = AX_TRUE;
    }
    pCam->bChnEn[0] = AX_TRUE;
    pCam->bRegisterSns = AX_TRUE;

    return;
}

static AX_U32 __sample_case_single_os04a10_dcg_hdr(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    pCommonArgs->nCamCnt = 1;
    pCam = &pCamList[0];
    pCam->nNumber = 0;
    pCam->nPipeId = 0;
    COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);

    //DCG
    pCam->nDevId = 0;
    pCam->nRxDev = 0;
    pCam->tSnsClkAttr.nSnsClkIdx = 0;
    pCam->tDevBindPipe.nNum =  1;
    pCam->tDevBindPipe.nPipeId[0] = 0;
    pCam->tSnsAttr.eSnsOutputMode = AX_SNS_DCG_HDR;
    pCam->tDevAttr.eSnsOutputMode = AX_SNS_DCG_HDR;
    pCam->tSnsAttr.eSnsMode = AX_SNS_HDR_2X_MODE;

    pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(eSnsType);
    pCam->eBusType = COMMON_ISP_GetSnsBusType(eSnsType);
    __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], AX_SNS_HDR_2X_MODE);

    for (int j = 0; j < pCam->tDevBindPipe.nNum; j++) {
        pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
        pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
    }
    __set_vin_attr(pCam, eSnsType, AX_SNS_HDR_2X_MODE, eSysMode, pVinParam->bAiispEnable);

    return 0;
}

static AX_U32 __sample_case_single_os04a10_dcg_vs_hdr(AX_CAMERA_T *pCamList, SAMPLE_SNS_TYPE_E eSnsType,
        SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs)
{
    AX_S32 i = 0, j = 0;
    AX_CAMERA_T *pCam = NULL;
    COMMON_VIN_MODE_E eSysMode = pVinParam->eSysMode;
    AX_SNS_HDR_MODE_E eHdrMode = pVinParam->eHdrMode;

    pCommonArgs->nCamCnt = 2;

    for (i = 0; i < pCommonArgs->nCamCnt; i++) {
        pCam = &pCamList[i];
        pCam->nNumber = i;

        //DCG + VS
        pCam->nDevId = i;
        pCam->nPipeId = i;
        pCam->nRxDev = 0;
        pCam->tSnsClkAttr.nSnsClkIdx = 0;

        pCam->tDevBindPipe.nNum =  1;
        pCam->tDevBindPipe.nPipeId[0] = i;

        for (j = 0; j < pCam->tDevBindPipe.nNum; j++) {
            COMMON_VIN_GetSnsConfig(eSnsType, &pCam->tMipiAttr, &pCam->tSnsAttr,
                            &pCam->tSnsClkAttr, &pCam->tDevAttr,
                            &pCam->tPipeAttr[pCam->nPipeId], pCam->tChnAttr);

            pCam->tPipeInfo[j].ePipeMode = SAMPLE_PIPE_MODE_VIDEO;
            pCam->tPipeInfo[j].bAiispEnable = pVinParam->bAiispEnable;
        }

        pCam->tSnsAttr.eSnsOutputMode = AX_SNS_DCG_VS_HDR;
        pCam->tDevAttr.eSnsOutputMode = AX_SNS_DCG_VS_HDR;

        if (0 == i) {
            pCam->eBusType = COMMON_ISP_GetSnsBusType(OMNIVISION_OS04A10_DCG);
            pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(OMNIVISION_OS04A10_DCG);
            pCam->tSnsAttr.eSnsMode = eHdrMode;
            __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], AX_SNS_HDR_2X_MODE);
            __set_vin_attr(pCam, eSnsType, AX_SNS_HDR_2X_MODE, eSysMode, pVinParam->bAiispEnable);
            pCam->tPipeAttr[pCam->nPipeId].eSnsMode = eHdrMode;
            pCam->tSnsAttr.eSnsMode = eHdrMode;
        } else {
            pCam->tSnsAttr.eSnsMode = AX_SNS_LINEAR_MODE;
            pCam->tDevAttr.tMipiIntfAttr.szImgVc[0] = 0x02;
            pCam->tDevAttr.tMipiIntfAttr.szImgDt[0] = 0x2b;
            pCam->tPipeAttr[pCam->nPipeId].tCompressInfo.enCompressMode = AX_COMPRESS_MODE_NONE;
            pCam->eBusType = COMMON_ISP_GetSnsBusType(OMNIVISION_OS04A10_DCG_VS);
            pCam->ptSnsHdl[pCam->nPipeId] = COMMON_ISP_GetSnsObj(OMNIVISION_OS04A10_DCG_VS);
            __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], AX_SNS_LINEAR_MODE);
            __set_vin_attr(pCam, eSnsType, AX_SNS_LINEAR_MODE, eSysMode, pVinParam->bAiispEnable);
        }
    }

    return 0;
}

static AX_U32 __sample_case_config(SAMPLE_VIN_PARAM_T *pVinParam, COMMON_SYS_ARGS_T *pCommonArgs,
                                   COMMON_SYS_ARGS_T *pPrivArgs)
{
    AX_CAMERA_T         *pCamList = &gCams[0];
    SAMPLE_SNS_TYPE_E   eSnsType = OMNIVISION_OS04A10;

    COMM_ISP_PRT("eSysCase %d, eSysMode %d, eHdrMode %d, bAiispEnable %d\n", pVinParam->eSysCase,
                 pVinParam->eSysMode, pVinParam->eHdrMode, pVinParam->bAiispEnable);

    switch (pVinParam->eSysCase) {
    case SAMPLE_VIN_SINGLE_OS04A10_DCG_HDR:
        eSnsType = OMNIVISION_OS04A10_DCG;
        /* pool config */
        __cal_dump_pool(gtSysCommPoolOs04a10DcgHdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolOs04a10DcgHdr) / sizeof(gtSysCommPoolOs04a10DcgHdr[0]);
        pCommonArgs->pPoolCfg  = gtSysCommPoolOs04a10DcgHdr;

        /* private pool config */
        __cal_dump_pool(gtPrivatePoolOs04a10DcgHdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolOs04a10DcgHdr) / sizeof(gtPrivatePoolOs04a10DcgHdr[0]);
        pPrivArgs->pPoolCfg  = gtPrivatePoolOs04a10DcgHdr;

        /* cams config */
        __sample_case_single_os04a10_dcg_hdr(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;
    case SAMPLE_VIN_SINGLE_OS04A10_DCG_VS_HDR:
        eSnsType = OMNIVISION_OS04A10_DCG_VS;
        /* pool config */
        __cal_dump_pool(gtSysCommPoolOs04a10DcgVsHdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pCommonArgs->nPoolCfgCnt = sizeof(gtSysCommPoolOs04a10DcgVsHdr) / sizeof(gtSysCommPoolOs04a10DcgVsHdr[0]);
        pCommonArgs->pPoolCfg  = gtSysCommPoolOs04a10DcgVsHdr;

        /* private pool config */
        __cal_dump_pool(gtPrivatePoolOs04a10DcgVsHdr, pVinParam->eHdrMode, pVinParam->nDumpFrameNum);
        pPrivArgs->nPoolCfgCnt = sizeof(gtPrivatePoolOs04a10DcgVsHdr) / sizeof(gtPrivatePoolOs04a10DcgVsHdr[0]);
        pPrivArgs->pPoolCfg  = gtPrivatePoolOs04a10DcgVsHdr;

        /* cams config */
        __sample_case_single_os04a10_dcg_vs_hdr(pCamList, eSnsType, pVinParam, pCommonArgs);
        break;

    default:
        COMM_ISP_PRT("eSysCase %d not match, DCG_HDR need %d, DCG_VS_HDR need %d \n", pVinParam->eSysCase,
                                SAMPLE_VIN_SINGLE_OS04A10_DCG_HDR, SAMPLE_VIN_SINGLE_OS04A10_DCG_VS_HDR);
        return -1;
    }

    return 0;
}

static AX_U32 __dcg_vs_sensor_init(AX_U8 nPipeId, AX_SENSOR_REGISTER_FUNC_T *ptSnsHdl, AX_SNS_ATTR_T *ptSnsAttr, AX_SNS_CLK_ATTR_T *ptSnsClkAttr)
{
    AX_S32 axRet = 0;
    AX_SNS_COMMBUS_T tSnsBusInfo = {0};
    tSnsBusInfo.I2cDev  = 0;

    if (AX_NULL == ptSnsHdl) {
        COMM_ISP_PRT("AX_ISP Sensor Object NULL!\n");
        return -1;
    }

    /* confige i2c/spi dev id */
    if (NULL != ptSnsHdl->pfn_sensor_set_bus_info) {
        axRet = ptSnsHdl->pfn_sensor_set_bus_info(nPipeId, tSnsBusInfo);
        if (0 != axRet) {
            COMM_ISP_PRT("set sensor bus info failed with %#x!\n", axRet);
            return axRet;
        }
        COMM_ISP_PRT("set sensor bus idx %d\n", tSnsBusInfo.I2cDev);
    } else {
        COMM_ISP_PRT("not support set sensor bus info!\n");
        return -1;
    }

    if (NULL != ptSnsHdl->pfn_sensor_set_mode) {
        axRet = ptSnsHdl->pfn_sensor_set_mode(nPipeId, ptSnsAttr);
        if (0 != axRet) {
            COMM_ISP_PRT("set sensor mode failed with %#x!\n", axRet);
            return axRet;
        }
    } else {
        COMM_ISP_PRT("not support set set sensor mode info!\n");
        return -1;
    }

    if (NULL != ptSnsHdl->pfn_sensor_init) {
        ptSnsHdl->pfn_sensor_init(nPipeId);
    } else {
        COMM_ISP_PRT("not support sensor init!\n");
        return -1;
    }

    return 0;
}

static AX_U32 __dcg_vs_sensor_register(AX_U8 nPipeId, AX_SENSOR_REGISTER_FUNC_T *ptSnsHdl, AX_SNS_ATTR_T *ptSnsAttr)
{
    AX_S32 axRet = 0;
    AX_SNS_FUNC_MASK_T tSnsFuncMask = {0};

    if (AX_NULL == ptSnsHdl) {
        COMM_ISP_PRT("AX_ISP Sensor Object NULL!\n");
        return -1;
    }

    /* ISP Register Sensor */
    axRet = AX_ISP_RegisterSensor(nPipeId, ptSnsHdl);
    if (axRet) {
        COMM_ISP_PRT("AX_ISP Register Sensor Failed, ret=0x%x.\n", axRet);
        return axRet;
    }

    axRet = AX_ISP_GetSnsFuncMask(nPipeId, &tSnsFuncMask);
    if (0 != axRet) {
        COMM_CAM_PRT("AX_ISP_GetSnsFuncMask failed, ret=0x%x.\n", axRet);
        return -1;
    }

    tSnsFuncMask.bitSnsInitMaskEn = 0;
    tSnsFuncMask.bitSnsExitMaskEn = 0;
    tSnsFuncMask.bitSnsStreamCtrlMaskEn = 0;
    axRet = AX_ISP_SetSnsFuncMask(nPipeId, &tSnsFuncMask);
    if (0 != axRet) {
        COMM_CAM_PRT("AX_ISP_SetSnsFuncMask failed, ret=0x%x.\n", axRet);
        return -1;
    }

    axRet = AX_ISP_SetSnsAttr(nPipeId, ptSnsAttr);
    if (0 != axRet) {
        COMM_ISP_PRT("AX_ISP_SetSnsAttr failed with %#x!\n", axRet);
        return axRet;
    }

    return 0;
}

static AX_U32 __dcg_vs_sensor_unregister(AX_U8 nPipeId, AX_SENSOR_REGISTER_FUNC_T *ptSnsHdl)
{

    AX_ISP_UnRegisterSensor(nPipeId);

    if (1 == nPipeId) {
        if (NULL != ptSnsHdl->pfn_sensor_exit) {
            ptSnsHdl->pfn_sensor_exit(nPipeId);
        } else {
            COMM_ISP_PRT("not support sensor init!\n");
            return -1;
        }
    }

    return 0;
}

static AX_S32 __dcg_vs_cam_open(AX_CAMERA_T *pCam)
{
    AX_S32 i = 0;
    AX_S32 axRet = 0;
    AX_U8 nPipeId = 0;
    AX_U8 nDevId = pCam->nDevId;
    AX_U32 nRxDev = pCam->nRxDev;

    axRet = __dcg_vs_sensor_init(pCam->nPipeId, pCam->ptSnsHdl[pCam->nPipeId], &pCam->tSnsAttr, &pCam->tSnsClkAttr);

    axRet = COMMON_VIN_CreateDev(nDevId, nRxDev, &pCam->tDevAttr, &pCam->tDevBindPipe);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_VIN_CreateDev failed, ret=0x%x.\n", axRet);
        return -1;
    }

    for (i = 0; i < pCam->tDevBindPipe.nNum; i++) {
        nPipeId = pCam->tDevBindPipe.nPipeId[i];
        pCam->tPipeAttr[pCam->nPipeId].bAiIspEnable = pCam->tPipeInfo[i].bAiispEnable;

        axRet = COMMON_VIN_SetPipeAttr(pCam->eSysMode, pCam->eLoadRawNode, nPipeId, &pCam->tPipeAttr[pCam->nPipeId]);
        if (0 != axRet) {
            COMM_CAM_PRT("COMMON_ISP_SetPipeAttr failed, ret=0x%x.\n", axRet);
            return -1;
        }

        __dcg_vs_sensor_register(nPipeId, pCam->ptSnsHdl[pCam->nPipeId], &pCam->tSnsAttr);

        axRet = COMMON_ISP_Init(nPipeId, pCam->ptSnsHdl[pCam->nPipeId], pCam->bRegisterSns, pCam->bUser3a,
                                &pCam->tAeFuncs, &pCam->tAwbFuncs, &pCam->tAfFuncs, &pCam->tLscFuncs,
                                pCam->tPipeInfo[i].szBinPath);
        if (0 != axRet) {
            COMM_CAM_PRT("COMMON_ISP_StartIsp failed, axRet = 0x%x.\n", axRet);
            return -1;
        }

        axRet = COMMON_VIN_StartChn(nPipeId, pCam->tChnAttr, pCam->bChnEn);
        if (0 != axRet) {
            COMM_CAM_PRT("COMMON_ISP_StartChn failed, nRet = 0x%x.\n", axRet);
            return -1;
        }

        axRet = AX_VIN_StartPipe(nPipeId);
        if (0 != axRet) {
            COMM_CAM_PRT("AX_VIN_StartPipe failed, ret=0x%x\n", axRet);
            return -1;
        }

        axRet = AX_ISP_Start(nPipeId);
        if (0 != axRet) {
            COMM_CAM_PRT("AX_ISP_Open failed, ret=0x%x\n", axRet);
            return -1;
        }
    }

    axRet = COMMON_VIN_StartDev(nDevId, pCam->bEnableDev, &pCam->tDevAttr);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_VIN_StartDev failed, ret=0x%x.\n", axRet);
        return -1;
    }

    return 0;
}

static AX_S32 __dcg_vs_cam_close(AX_CAMERA_T *pCam)
{
    AX_U8 i = 0;
    AX_S32 axRet = 0;
    AX_U8 nPipeId = pCam->nPipeId;
    AX_U8 nDevId = pCam->nDevId;
    AX_U32 nRxDev = pCam->nRxDev;

    for (i = 0; i < pCam->tDevBindPipe.nNum; i++) {
        nPipeId = pCam->tDevBindPipe.nPipeId[i];
        axRet |= AX_ISP_Stop(nPipeId);
        if (0 != axRet) {
            COMM_ISP_PRT("AX_ISP_Stop failed, ret=0x%x.\n", axRet);
        }
    }

    axRet = COMMON_VIN_StopDev(nDevId, pCam->bEnableDev);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_VIN_StopDev failed, ret=0x%x.\n", axRet);
    }

    if (pCam->bRegisterSns && pCam->bEnableDev) {

        if (pCam->tDevAttr.eSnsOutputMode == AX_SNS_DCG_HDR && nPipeId == 0) {
            AX_ISP_StreamOff(nPipeId);
        } else if (pCam->tDevAttr.eSnsOutputMode == AX_SNS_DCG_VS_HDR && nPipeId == 1) {
            AX_ISP_StreamOff(nPipeId);
        }
    }

    axRet = AX_ISP_CloseSnsClk(pCam->tSnsClkAttr.nSnsClkIdx);
    if (0 != axRet) {
        COMM_CAM_PRT("AX_VIN_CloseSnsClk failed, ret=0x%x.\n", axRet);
    }

    for (i = 0; i < pCam->tDevBindPipe.nNum; i++) {
        nPipeId = pCam->tDevBindPipe.nPipeId[i];
        axRet = AX_VIN_StopPipe(nPipeId);
        if (0 != axRet) {
            COMM_CAM_PRT("AX_VIN_StopPipe failed, ret=0x%x.\n", axRet);
        }

        COMMON_VIN_StopChn(nPipeId);

        COMMON_ISP_DeInit(nPipeId, pCam->bRegisterSns);

        __dcg_vs_sensor_unregister(nPipeId, pCam->ptSnsHdl[pCam->nPipeId]);

        AX_VIN_DestroyPipe(nPipeId);
    }

    axRet = COMMON_VIN_StopMipi(nRxDev);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_VIN_StopMipi failed, ret=0x%x.\n", axRet);
    }

    axRet = COMMON_VIN_DestroyDev(nDevId);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_VIN_DestroyDev failed, ret=0x%x.\n", axRet);
    }

    COMM_CAM_PRT("%s: nDevId %d: exit.\n", __func__, nDevId);

    return AX_SUCCESS;
}

static AX_S32 __dcg_vs_mipi_init(AX_CAMERA_T *pCam, AX_S32 nPipeId, AX_U8 Num)
{
    AX_INPUT_MODE_E eInputMode = pCam->eInputMode;
    AX_S32 axRet = 0;
    AX_U16 i = 0;
    AX_U8 nDevId = pCam->nDevId;
    AX_U32 nRxDev = pCam->nRxDev;

    for (i = 0; i < Num; i++) {
        axRet = AX_ISP_OpenSnsClk(pCam->tSnsClkAttr.nSnsClkIdx, pCam->tSnsClkAttr.eSnsClkRate);
        if (0 != axRet) {
            COMM_ISP_PRT("AX_ISP_OpenSnsClk failed, nRet=0x%x.\n", axRet);
            return -1;
        }
    }

    axRet = COMMON_ISP_ResetSnsObj(nPipeId, nDevId, pCam->ptSnsHdl[pCam->nPipeId]);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_ISP_ResetSnsObj failed, ret=0x%x.\n", axRet);
        return -1;
    }

    axRet = COMMON_VIN_StartMipi(nRxDev, eInputMode, &pCam->tMipiAttr);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_VIN_StartMipi failed, r-et=0x%x.\n", axRet);
        return -1;
    }
    return 0;
}

static AX_S32 __dcg_vs_cam_switch_test(AX_CAMERA_T *pCam)
{
    AX_S32 axRet = 0;
    AX_U8 nPipeId = 0;
    /* destory DCG pipe*/
    axRet = AX_ISP_Stop(nPipeId);
    if (0 != axRet) {
        COMM_ISP_PRT("AX_ISP_Stop failed, ret=0x%x.\n", axRet);
    }

    axRet = AX_VIN_StopPipe(nPipeId);
    if (0 != axRet) {
        COMM_CAM_PRT("AX_VIN_StopPipe failed, ret=0x%x.\n", axRet);
    }

    COMMON_VIN_StopChn(nPipeId);

    COMMON_ISP_DeInit(nPipeId, pCam->bRegisterSns);

    __dcg_vs_sensor_unregister(nPipeId, pCam->ptSnsHdl[pCam->nPipeId]);

    AX_VIN_DestroyPipe(nPipeId);

    if (pCam->tPipeAttr[pCam->nPipeId].eSnsMode == AX_SNS_LINEAR_MODE) {
        pCam->tPipeAttr[pCam->nPipeId].eSnsMode  = AX_SNS_HDR_2X_MODE;
        pCam->tSnsAttr.eSnsMode = AX_SNS_HDR_2X_MODE;
        __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], AX_SNS_HDR_2X_MODE);
    } else {
        pCam->tPipeAttr[pCam->nPipeId].eSnsMode  = AX_SNS_LINEAR_MODE;
        pCam->tSnsAttr.eSnsMode = AX_SNS_LINEAR_MODE;
        __set_pipe_hdr_mode(&pCam->tDevBindPipe.nHDRSel[0], AX_SNS_LINEAR_MODE);
    }

    /* rebuild DCG pipe*/
    axRet = COMMON_VIN_SetPipeAttr(pCam->eSysMode, pCam->eLoadRawNode, nPipeId, &pCam->tPipeAttr[pCam->nPipeId]);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_ISP_SetPipeAttr failed, ret=0x%x.\n", axRet);
        return -1;
    }

    __dcg_vs_sensor_register(nPipeId, pCam->ptSnsHdl[pCam->nPipeId], &pCam->tSnsAttr);

    axRet = COMMON_ISP_Init(nPipeId, pCam->ptSnsHdl[pCam->nPipeId], pCam->bRegisterSns, pCam->bUser3a,
                            &pCam->tAeFuncs, &pCam->tAwbFuncs, &pCam->tAfFuncs, &pCam->tLscFuncs,
                            pCam->tPipeInfo[nPipeId].szBinPath);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_ISP_StartIsp failed, axRet = 0x%x.\n", axRet);
        return -1;
    }
    axRet = COMMON_VIN_StartChn(nPipeId, pCam->tChnAttr, pCam->bChnEn);
    if (0 != axRet) {
        COMM_CAM_PRT("COMMON_ISP_StartChn failed, nRet = 0x%x.\n", axRet);
        return -1;
    }

    axRet = AX_VIN_StartPipe(nPipeId);
    if (0 != axRet) {
        COMM_CAM_PRT("AX_VIN_StartPipe failed, ret=0x%x\n", axRet);
        return -1;
    }

    axRet = AX_ISP_Start(nPipeId);
    if (0 != axRet) {
        COMM_CAM_PRT("AX_ISP_Open failed, ret=0x%x\n", axRet);
        return -1;
    }

    return 0;
}

static AX_S32 __cam_open(AX_CAMERA_T *pCamList, AX_U8 Num)
{
    AX_U16 i = 0;
    AX_U8 nPipeId = 0;
    if (pCamList == NULL) {
        return -1;
    }

    if (AX_SUCCESS != __dcg_vs_mipi_init(&pCamList[nPipeId], nPipeId, Num)) {
        goto EXIT;
    }

    for (i = 0; i < Num; i++) {
        if (AX_SUCCESS == __dcg_vs_cam_open(&pCamList[i])) {
            pCamList[i].bOpen = AX_TRUE;
            COMM_CAM_PRT("camera %d is open\n", i);
        } else {
            goto EXIT;
        }
    }
    if (pCamList[0].bRegisterSns && pCamList[0].bEnableDev) {
        if (AX_SUCCESS != AX_ISP_StreamOn(nPipeId)) {
            goto EXIT;
        }
    }

    return 0;
EXIT:
    for (i = 0; i < Num; i++) {
        if (!pCamList[i].bOpen) {
            continue;
        }
        __dcg_vs_cam_close(&pCamList[i]);
    }
    return -1;
}

AX_S32 SAMPLE_CASE_VIN_DCG_VS(SAMPLE_VIN_PARAM_T *pVinParam)
{
    AX_S32 axRet = 0;
    AX_S32 i = 0, j = 0;
    COMMON_SYS_ARGS_T tCommonArgs = {0};
    COMMON_SYS_ARGS_T tPrivArgs = {0};

    signal(SIGINT, __sigint);
    /* Step1: cam config & pool Config */
    axRet = __sample_case_config(pVinParam, &tCommonArgs, &tPrivArgs);
    if (axRet) {
        COMM_ISP_PRT("__sample_case_config fail, ret:0x%x", axRet);
        goto EXIT_FAIL;
    }
    /* Step2: SYS Init */
    axRet = COMMON_SYS_Init(&tCommonArgs);
    if (axRet) {
        COMM_ISP_PRT("COMMON_SYS_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL;
    }
    /* Step3: NPU Init */
    axRet = COMMON_NPU_Init();
    if (axRet) {
        COMM_ISP_PRT("COMMON_NPU_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL1;
    }
    /* Step4: Cam Init */
    axRet = COMMON_CAM_Init();
    if (axRet) {
        COMM_ISP_PRT("COMMON_CAM_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL1;
    }

    axRet = COMMON_CAM_PrivPoolInit(&tPrivArgs);
    if (axRet) {
        COMM_ISP_PRT("COMMON_CAM_PrivPoolInit fail, ret:0x%x", axRet);
        goto EXIT_FAIL1;
    }
    /* Step5: Cam Open */
    axRet = __cam_open(&gCams[0], tCommonArgs.nCamCnt);
    if (axRet) {
        COMM_ISP_PRT("COMMON_CAM_Open fail, ret:0x%x", axRet);
        goto EXIT_FAIL2;
    }
    /* Step6. NT Init (tuning socket server. optional)
    Stream default port 6000, Ctrl default port 8082 */
    axRet = COMMON_NT_Init(6000, 8082);
    if (axRet) {
        COMM_ISP_PRT("COMMON_NT_Init fail, ret:0x%x", axRet);
        goto EXIT_FAIL3;
    }
    /* update pipe attribute */
    for (i = 0; i < tCommonArgs.nCamCnt; i++) {
        for (j = 0; j < gCams[i].tDevBindPipe.nNum; j++) {
            COMMON_NT_UpdateSource(gCams[i].tDevBindPipe.nPipeId[j]);
        }
    }

    /* DCG VS switch twice */
    if (pVinParam->eSysCase == SAMPLE_VIN_SINGLE_OS04A10_DCG_VS_HDR) {
        for(i = 0; i < 2;) {
            sleep(5);
            COMM_CAM_PRT("switch times: %d.\n", ++i);
            __dcg_vs_cam_switch_test(&gCams[0]);
        }
    }

    while (!gLoopExit) {
        sleep(1);
    }

    COMMON_NT_DeInit();
EXIT_FAIL3:
    for (i = 0; i < tCommonArgs.nCamCnt; i++) {
        for (j = 0; j < gCams[i].tDevBindPipe.nNum; j++) {
        if (!gCams[i].bOpen) {
            continue;
        }
        __dcg_vs_cam_close(&gCams[i]);
        }
    }
EXIT_FAIL2:
    COMMON_CAM_Deinit();
EXIT_FAIL1:
    COMMON_SYS_DeInit();
EXIT_FAIL:
    return axRet;
}
