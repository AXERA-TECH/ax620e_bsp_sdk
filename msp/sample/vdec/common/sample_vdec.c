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
#include <signal.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <sys/prctl.h>

#include "common_vdec_api.h"
extern AX_U64 g_u64GetFrmTag;

static volatile AX_S32 s_ThreadExit = 0;
static AX_BOOL s_groupSuccess = AX_FALSE;

const char *__VdecDecModeStr(AX_S32 value)
{
    switch (value) {
    case VIDEO_DEC_MODE_IPB:
        return ("IPB");
    case VIDEO_DEC_MODE_IP:
        return ("IP");
    case VIDEO_DEC_MODE_I:
        return ("I");
    default:
        SAMPLE_LOG_TMP("Unknown return code. %#x\n", value);
        return "unknow";
    }
}

static AX_VOID __VdecFeatureTest(AX_VDEC_GRP VdGrp, SAMPLE_VDEC_CMD_PARAM_T *pstCmd)
{
    AX_S32 ret = 0;
    AX_S32 i = 0;
    AX_U8* pu8Addr = NULL;

    if (!pstCmd)
        return;

    if (pstCmd->bGetUserData) {
        AX_VDEC_USERDATA_T stUserData;
        AX_U32 outInfoLen = 32;
        AX_U32 tmpLen = 0;
        memset(&stUserData, 0x0, sizeof(AX_VDEC_USERDATA_T));
        /* AX_VDEC_GetUserData can be called anywhere, and is used here
         * only for demonstration and testing purposes.
         */
        ret = AX_VDEC_GetUserData(VdGrp, &stUserData);
        if (AX_SUCCESS == ret) {
            SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_GetUserData u32UserDataCnt:%d, u32Len:%d",
                         VdGrp, stUserData.u32UserDataCnt, stUserData.u32Len);
            if (stUserData.bValid && stUserData.pu8Addr) {

                pu8Addr = stUserData.pu8Addr;
                for (i = 0; i < stUserData.u32UserDataCnt; i++) {
                    tmpLen = stUserData.u32DataLen[i] > outInfoLen ? outInfoLen : stUserData.u32DataLen[i];
                    pu8Addr[tmpLen] = '\0';
                    SAMPLE_LOG_TMP("SEI%d pu8Addr:%p, u32DataLen:%d, data: %s",
                                i, pu8Addr, stUserData.u32DataLen[i], pu8Addr);
                    pu8Addr += stUserData.u32DataLen[i];
                }
            }

            ret = AX_VDEC_ReleaseUserData(VdGrp, &stUserData);
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("VdGrp=%d,  AX_VDEC_ReleaseUserData succ!", VdGrp);
            else
                SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_ReleaseUserData FAILED! ret:0x%x", VdGrp, ret);
        } else {
            SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_GetUserData FAILED! ret:0x%x", VdGrp, ret);
        }
    }

    if (pstCmd->bGetRbInfo) {
        AX_VDEC_STREAM_BUF_INFO_T stStreamBufInfo;
        memset(&stStreamBufInfo, 0x0, sizeof(AX_VDEC_STREAM_BUF_INFO_T));
        ret = AX_VDEC_GetStreamBufInfo(VdGrp, &stStreamBufInfo);
        if (AX_SUCCESS == ret)
            SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_GetStreamBufInfo: "
                         "phyStart: 0x%llx, virStart: %p, totalSize: 0x%x, readAbleSize: 0x%x, "
                         "writeAbleSize: 0x%x, readOffset: 0x%x, writeOffset: 0x%x",
                         VdGrp, stStreamBufInfo.phyStart,
                         stStreamBufInfo.virStart,
                         stStreamBufInfo.totalSize,
                         stStreamBufInfo.readAbleSize,
                         stStreamBufInfo.writeAbleSize,
                         stStreamBufInfo.readOffset,
                         stStreamBufInfo.writeOffset);
        else
            SAMPLE_CRIT_LOG("VdGrp=%d,  stStreamBufInfo FAILED! ret:0x%x", VdGrp, ret);
    }

    if (pstCmd->bGetGrpAtrr) {
        AX_VDEC_GRP_ATTR_T stGrpAttrInfo;
        memset(&stGrpAttrInfo, 0x0, sizeof(AX_VDEC_GRP_ATTR_T));
        ret = AX_VDEC_GetGrpAttr(VdGrp, &stGrpAttrInfo);
        if (AX_SUCCESS == ret)
            SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_GetGrpAttr: "
                         "codecType: %d, inputmode: %d, res: %d x %d, frmheight: 0x%d, "
                         "bufsize: %#x, bufCnt: 0x%x, outOrder: %d islink: %d\n",
                         VdGrp, stGrpAttrInfo.enCodecType,
                         stGrpAttrInfo.enInputMode,
                         stGrpAttrInfo.u32PicWidth,
                         stGrpAttrInfo.u32PicHeight,
                         stGrpAttrInfo.u32FrameHeight,
                         stGrpAttrInfo.u32StreamBufSize,
                         stGrpAttrInfo.u32FrameBufCnt,
                         stGrpAttrInfo.enOutOrder,
                         stGrpAttrInfo.enLinkMode);
        else
            SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_GetGrpAttr FAILED! ret:0x%x", VdGrp, ret);
    }

    if (pstCmd->bQueryStatus) {
        AX_VDEC_GRP_STATUS_T stGrpStatus;
        memset(&stGrpStatus, 0x0, sizeof(AX_VDEC_GRP_STATUS_T));
        ret = AX_VDEC_QueryStatus(VdGrp, &stGrpStatus);
        if (AX_SUCCESS == ret)
            SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_QueryStatus: \n"
                         "enCodecType: %d, u32LeftStreamBytes: %d, u32LeftStreamFrames: %d, "
                         "u32LeftPics: %d, bStartRecvStream: %d, u32RecvStreamFrames: %d, "
                         "u32DecodeStreamFrames: %d, u32PicWidth: %d, u32PicHeight: %d, "
                         "s32PicSizeErrSet: %d, s32StreamUnsprt: %d, s32PackErr: %d, "
                         "s32PicBufSizeErrSet: %d",
                         VdGrp, stGrpStatus.enCodecType, stGrpStatus.u32LeftStreamBytes,
                         stGrpStatus.u32LeftStreamFrames, stGrpStatus.u32LeftPics,
                         stGrpStatus.bStartRecvStream, stGrpStatus.u32RecvStreamFrames,
                         stGrpStatus.u32DecodeStreamFrames, stGrpStatus.u32PicWidth,
                         stGrpStatus.u32PicHeight, stGrpStatus.stVdecDecErr.s32PicSizeErrSet,
                         stGrpStatus.stVdecDecErr.s32StreamUnsprt, stGrpStatus.stVdecDecErr.s32PackErr,
                         stGrpStatus.stVdecDecErr.s32PicBufSizeErrSet);
        else
            SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_QueryStatus FAILED! ret:0x%x", VdGrp, ret);
    }

    if (pstCmd->bGetVuiParam) {
        AX_VDEC_VUI_PARAM_T stVuiParam;
        memset(&stVuiParam, 0x0, sizeof(AX_VDEC_VUI_PARAM_T));
        ret = AX_VDEC_GetVuiParam(VdGrp, &stVuiParam);
        if (AX_SUCCESS == ret)
            SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_GetVuiParam: "
                         "time_scale: %u, num_units_in_tick: %d",
                         VdGrp,
                         stVuiParam.stVuiTimeInfo.time_scale,
                         stVuiParam.stVuiTimeInfo.num_units_in_tick);
        else
            SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_GetVuiParam FAILED! ret:0x%x", VdGrp, ret);
    }

    if (pstCmd->bGetDispMode) {
        AX_VDEC_DISPLAY_MODE_E enDispMode;
        ret = AX_VDEC_GetDisplayMode(VdGrp, &enDispMode);
        if (AX_SUCCESS == ret)
            SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_GetDisplayMode: %s\n",
                         VdGrp, (enDispMode == AX_VDEC_DISPLAY_MODE_PREVIEW) ? "preview" : "playback");
        else
            SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_GetDisplayMode FAILED! ret:0x%x", VdGrp, ret);
    }

    if (pstCmd->bGetGrpPrm) {
        AX_VDEC_GRP_PARAM_T stGrpPrm;
        ret = AX_VDEC_GetGrpParam(VdGrp, &stGrpPrm);
        if (AX_SUCCESS == ret)
            SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_GetGrpParam: %s mode\n",
                         VdGrp, __VdecDecModeStr(stGrpPrm.enVdecMode));
        else
            SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_GetGrpParam FAILED! ret:0x%x", VdGrp, ret);
    }
}

static AX_S32 __VdecRecvFrame(AX_VDEC_GRP VdGrp, SAMPLE_VDEC_CONTEXT_T *pstVdecCtx)
{
    int res;
    AX_S32 ret;
    AX_S32 sRet = AX_SUCCESS;
    AX_VIDEO_FRAME_INFO_T stFrameInfo[SAMPLE_VDEC_FRAME_CNT];
    AX_VIDEO_FRAME_INFO_T *pstFrameInfo;
    AX_S32 sGetMilliSec = -1;
    FILE *fp_out = NULL;
    int ii = 0;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    AX_U32 uStartGrpId = 0;
    SAMPLE_VDEC_USERPIC_T *pstVdecUserPic = NULL;
    AX_U32 u32UsrPicBlkId = 0;
    SAMPLE_VDEC_OUTPUT_INFO_T *pOutInfo = NULL;
    AX_CHAR *pOutputFilePath = NULL;

    if (pstVdecCtx == NULL) {
        SAMPLE_LOG("VdGrp=%d, pstVdecCtx == NULL", VdGrp);
        return -1;
    }

    pstCmd = &pstVdecCtx->tCmdParam;
    pstVdecUserPic = &pstVdecCtx->stVdecUserPic;
    u32UsrPicBlkId = pstVdecUserPic->stUserPic.stFrmInfo.stVFrame.u32BlkId[0];
    sGetMilliSec = pstCmd->sGetMilliSec;
    uStartGrpId = pstCmd->uStartGrpId;

    // sleep(10000); // just for test

    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];

        memset(pstFrameInfo, 0, sizeof(AX_VIDEO_FRAME_INFO_T));
        SAMPLE_LOG_N("VdGrp=%d, ", VdGrp);

        ret = AX_VDEC_GetFrame(VdGrp, pstFrameInfo, sGetMilliSec);
        if (ret != AX_SUCCESS) {
            if (ret == AX_ERR_VDEC_QUEUE_EMPTY) {
                /* no data in unblock mode or timeout mode */
                SAMPLE_LOG("VdGrp=%d, AX_VDEC_GetFrame AX_ERR_VDEC_QUEUE_EMPTY\n",
                            VdGrp);
                usleep(20 * 1000);
                sRet = ret;
                goto ERR_RET;
            } else if (ret == AX_ERR_VDEC_UNEXIST) {
                SAMPLE_ERR_LOG("VdGrp=%d, AX_VDEC_GetFrame AX_ERR_VDEC_UNEXIST \n",
                                VdGrp);
                usleep(20 * 1000);
                sRet = ret;
                goto ERR_RET;
            } else if (ret == AX_ERR_VDEC_FLOW_END) {
                SAMPLE_LOG("VdGrp=%d, AX_VDEC_GetFrame AX_ERR_VDEC_FLOW_END\n",
                            VdGrp);
                sRet = ret;
                goto ERR_RET;
            } else if (AX_ERR_VDEC_NOT_PERM == ret) {
                SAMPLE_LOG("VdGrp=%d, AX_VDEC_GetFrame AX_ERR_VDEC_NOT_PERM\n",
                                VdGrp);
                sRet = ret;
                goto ERR_RET;
            }

            SAMPLE_LOG("VdGrp=%d, AX_VDEC_GetFrame FAILED! ret=0x%x %s\n",
                            VdGrp, ret, SampleVdecRetStr(ret));
            continue;
        } else {
            pstVdecCtx->recvFrmCnt[VdGrp]++;
        }

#if 0
        if (pstCmd->bMultiLck) {
            int bi;
            AX_S32 sRefCnt = 0;

            ret = AX_POOL_IncreaseRefCnt(pstFrameInfo->stVFrame.u32BlkId[0]);
            if (ret) {
                sRet = ret;
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_POOL_IncreaseRefCnt FAILED! res:0x%x %s \n"
                                "u64PhyAddr[0]:%lld, BlkId[0]:0x%x, BlkId[1]:0x%x\n",
                                VdGrp, ret, SampleVdecRetStr(ret), pstFrameInfo->stVFrame.u64PhyAddr[0],
                                pstFrameInfo->stVFrame.u32BlkId[0], pstFrameInfo->stVFrame.u32BlkId[1]);
                goto ERR_RET;
            }

            ret = AX_POOL_CheckRefCnt(pstFrameInfo->stVFrame.u32BlkId[0], &sRefCnt);
            if (ret) {
                sRet = ret;
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_POOL_CheckRefCnt FAILED! res:0x%x %s u32BlkId:0x%x\n",
                                VdGrp, ret, SampleVdecRetStr(ret), pstFrameInfo->stVFrame.u32BlkId[0]);
                goto ERR_RET;
            }

            SAMPLE_LOG_TMP("VdGrp=%d, u32BlkId:0x%x sRefCnt:%d\n",
                        VdGrp, pstFrameInfo->stVFrame.u32BlkId[0], sRefCnt);

            while(1) {
                for (bi = 0; bi < SAMPLE_VDEC_REF_BLK_CNT; bi++) {
                    if (pstVdecCtx->blkRef[VdGrp][bi] == AX_INVALID_BLOCKID) {
                        pstVdecCtx->blkRef[VdGrp][bi] = pstFrameInfo->stVFrame.u32BlkId[0];
                        SAMPLE_LOG("save pstVdecCtx->blkRef[VdGrp=%d][bi=%d]:0x%x",
                                   VdGrp, bi, pstVdecCtx->blkRef[VdGrp][bi]);
                        break;
                    }
                }

                if (bi < SAMPLE_VDEC_REF_BLK_CNT) {
                    break;
                }
            }
        }
#endif

        SAMPLE_LOG("VdGrp=%d, after AX_VDEC_GetFrame "
                    ".u32Width:%d, .bEndOfStream:%d, .u64PhyAddr[0]:0x%llx, "
                    ".u64VirAddr[0]:0x%llx, BlkId[0]:0x%x, u64PTS:%lld, .u64PrivateData:0x%llx\n",
                    VdGrp, pstFrameInfo->stVFrame.u32Width, pstFrameInfo->bEndOfStream,
                    pstFrameInfo->stVFrame.u64PhyAddr[0], pstFrameInfo->stVFrame.u64VirAddr[0],
                    pstFrameInfo->stVFrame.u32BlkId[0], pstFrameInfo->stVFrame.u64PTS,
                    pstFrameInfo->stVFrame.u64PrivateData);
    }

    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];
        if (pstFrameInfo->bEndOfStream == AX_FALSE) {
            if (pstFrameInfo->stVFrame.u64PhyAddr[0] == 0) {
                if (!pstCmd->bUserPicEnable) {
                    SAMPLE_LOG("VdGrp=%d, AX_VDEC_GetChnFrame FAILED! "
                                    "pstFrameInfo->stVFrame.u64PhyAddr[0] == 0\n",
                                    VdGrp);
                } else {
                    SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_GetChnFrame FAILED! "
                                    "pstFrameInfo->stVFrame.u64PhyAddr[0] == 0\n",
                                    VdGrp);
                    sRet = AX_ERR_VDEC_BAD_ADDR;
                    goto ERR_RET;
                }
            }
        }
    }

    if (pstVdecCtx->GrpStatus[VdGrp] == AX_VDEC_GRP_START_RECV)
        __VdecFeatureTest(VdGrp, pstCmd);

    fp_out = pstVdecCtx->pOutputFd[VdGrp];

    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];

        if (!pstFrameInfo->stVFrame.u64PhyAddr[0])
            continue;

        if (pstCmd->sWriteFrames) {
            pOutInfo = &pstVdecCtx->outInfo;

            pOutInfo->VdGrp = VdGrp;
            pOutInfo->bOneShot = AX_FALSE;
            pOutputFilePath = pstVdecCtx->pOutputFilePath[VdGrp];
            if (pstCmd->bDynRes && pstFrameInfo->stVFrame.u64SeqNum) {
                if ((pOutInfo->enImgFormat != pstFrameInfo->stVFrame.enImgFormat) ||
                   (pOutInfo->u32Width != pstFrameInfo->stVFrame.u32Width) ||
                   (pOutInfo->u32Height != pstFrameInfo->stVFrame.u32Height) ||
                   (pOutInfo->u32PicStride != pstFrameInfo->stVFrame.u32PicStride[0])) {
                    if (fp_out) {
                        res = fclose(fp_out);
                        if (res) {
                            SAMPLE_CRIT_LOG("VdGrp=%d, fclose FAILED! res:%d fp_out:%p\n",
                                            VdGrp, res, fp_out);
                        }
                        fp_out = NULL;
                        pstVdecCtx->pOutputFd[VdGrp] = NULL;
                        SAMPLE_LOG("VdGrp=%d, fclose! fmt %d %d width %d %d height %d %d stride %d %d\n", VdGrp,
                            pOutInfo->enImgFormat, pstFrameInfo->stVFrame.enImgFormat,
                            pOutInfo->u32Width, pstFrameInfo->stVFrame.u32Width,
                            pOutInfo->u32Height, pstFrameInfo->stVFrame.u32Height,
                            pOutInfo->u32PicStride, pstFrameInfo->stVFrame.u32PicStride[0]);
                    }
                    pOutputFilePath = pstVdecCtx->pOutputFilePath1[VdGrp];
                }
            }

            pOutInfo->enImgFormat = pstFrameInfo->stVFrame.enImgFormat;
            pOutInfo->u32Width = pstFrameInfo->stVFrame.u32Width;
            pOutInfo->u32Height = pstFrameInfo->stVFrame.u32Height;
            pOutInfo->u32PicStride = pstFrameInfo->stVFrame.u32PicStride[0];

            if (fp_out == NULL) {
                SAMPLE_LOG("VdGrp=%d, pOutputFilePath:%s, out_info.VdGrp=%d, out_info.",
                           VdGrp, pOutputFilePath, pOutInfo->VdGrp);

                fp_out = OutputFileOpen(&pOutputFilePath, pOutInfo);
                if (fp_out == NULL) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, OutputFileOpen FAILED!",
                                    VdGrp);
                    if (pstVdecCtx->pOutputFilePath[VdGrp] != NULL) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, fopen pstVdecCtx->pOutputFilePath:%s FAILED!",
                                        VdGrp, pstVdecCtx->pOutputFilePath[VdGrp]);
                        free(pstVdecCtx->pOutputFilePath[VdGrp]);
                        pstVdecCtx->pOutputFilePath[VdGrp] = NULL;
                    }
                    sRet = AX_ERR_VDEC_RUN_ERROR;
                    goto ERR_RET;
                } else {
                    SAMPLE_LOG_TMP("old path %p new %p\n", pstVdecCtx->pOutputFilePath[VdGrp], pOutputFilePath);
                    if (pstVdecCtx->pOutputFilePath[VdGrp] != NULL)
                        free(pstVdecCtx->pOutputFilePath[VdGrp]);
                    pstVdecCtx->pOutputFilePath[VdGrp] = pOutputFilePath;
                }

                pstVdecCtx->pOutputFd[VdGrp] = fp_out;

                SAMPLE_LOG("VdGrp=%d, pstVdecCtx->pOutputFd:%p, fp_out:%p",
                            VdGrp, pstVdecCtx->pOutputFd[VdGrp], fp_out);
            }

            ret = OutputFileSaveYUV(VdGrp, pstFrameInfo, fp_out, pOutputFilePath);
            if (ret) {
                SAMPLE_CRIT_LOG("VdGrp=%d, OutputFileSaveYUV FAILED! ret:0x%x",
                                VdGrp, ret);
                sRet = AX_ERR_VDEC_RUN_ERROR;
            }
        }
    }

    if (VdGrp == uStartGrpId) {
        if (pstFrameInfo->stVFrame.u64PhyAddr[0]) {
            SAMPLE_LOG("u32TimeRef %-8d u64SeqNum %-8lld pts %-8lld\n",
                pstFrameInfo->stVFrame.u32TimeRef, pstFrameInfo->stVFrame.u64SeqNum, pstFrameInfo->stVFrame.u64PTS);
            fflush(stdout);
        }
    }

    if (pstCmd->bCheckFrmParam) {
        if (pstFrameInfo->stVFrame.u64PTS && pstFrameInfo->stVFrame.u64SeqNum && pstFrameInfo->stVFrame.u32TimeRef) {
            SAMPLE_LOG_TMP("VdGrp=%d, check frm param succ\n", VdGrp);
        }
    }

    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];

        SAMPLE_LOG_N("VdGrp=%d, ii:%d", VdGrp, ii);

        if (!pstFrameInfo->stVFrame.u64PhyAddr[0])
            continue;

        if (!pstCmd->bSkipRelease) {
            ret = AX_VDEC_ReleaseFrame(VdGrp, pstFrameInfo);
            if (ret) {
                if ((AX_ERR_VDEC_FLOW_END != ret) && (pstVdecCtx->GrpStatus[VdGrp] == AX_VDEC_GRP_START_RECV)) {
                    sRet = ret;
                    SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_ReleaseFrame FAILED! res:0x%x %s \n"
                                    "u64PhyAddr[0]:0x%llX, BlkId[0]:0x%x, BlkId[1]:0x%x\n",
                                    VdGrp, ret, SampleVdecRetStr(ret), pstFrameInfo->stVFrame.u64PhyAddr[0],
                                    pstFrameInfo->stVFrame.u32BlkId[0], pstFrameInfo->stVFrame.u32BlkId[1]);
                    goto ERR_RET;
                }
            } else {
                pstVdecCtx->releaseFrmCnt[VdGrp]++;
            }
        }
        pstCmd->bSkipRelease = AX_FALSE;
#if 0
        if (pstCmd->bMultiLck) {
            AX_S32 sRefCnt = 0;
            for (int bi = 0; bi < SAMPLE_VDEC_REF_BLK_CNT; bi++) {
                if (pstVdecCtx->blkRef[VdGrp][bi] == pstFrameInfo->stVFrame.u32BlkId[0]) {
                    ret = AX_POOL_DecreaseRefCnt(pstVdecCtx->blkRef[VdGrp][bi]);
                    if (ret) {
                        sRet = ret;
                        SAMPLE_CRIT_LOG("VdGrp=%d, AX_POOL_DecreaseRefCnt FAILED! res:0x%x %s \n"
                                        "blkRef[%d]:0x%x\n",
                                        VdGrp, ret, SampleVdecRetStr(ret), bi, pstVdecCtx->blkRef[VdGrp][bi]);
                        goto ERR_RET;
                    }

                    SAMPLE_LOG_TMP("AX_POOL_DecreaseRefCnt blkRef[bi:%d]:0x%x", bi, pstVdecCtx->blkRef[VdGrp][bi]);

                    ret = AX_POOL_CheckRefCnt(pstVdecCtx->blkRef[VdGrp][bi], &sRefCnt);
                    if (ret) {
                        sRet = ret;
                        SAMPLE_CRIT_LOG("VdGrp=%d, AX_POOL_CheckRefCnt FAILED! res:0x%x %s u32BlkId:0x%x\n",
                                        VdGrp, ret, SampleVdecRetStr(ret), pstVdecCtx->blkRef[VdGrp][bi]);
                        goto ERR_RET;
                    }

                    SAMPLE_LOG("VdGrp=%d, u32BlkId:0x%x sRefCnt:%d\n",
                               VdGrp, pstVdecCtx->blkRef[VdGrp][bi], sRefCnt);

                    pstVdecCtx->blkRef[VdGrp][bi] = AX_INVALID_BLOCKID;
                }
            }
        }
#endif
        /* This is only valid when using the user image Insert feature.
         * AX_VDEC_SetUserPic. */
        if (pstVdecUserPic->stUserPic.bEnable) {
            SAMPLE_LOG("BlkId[0]:0x%x, u32UsrPicBlkId:0x%x", pstFrameInfo->stVFrame.u32BlkId[0], u32UsrPicBlkId);
            if ((pstFrameInfo->stVFrame.u32BlkId[0] == u32UsrPicBlkId)
                && (pstVdecUserPic->PoolId != AX_INVALID_POOLID)) {
                pstVdecUserPic->usrPicGet = AX_TRUE;
            }
        }

        if ((!pstCmd->recvStmAfUsrPic && pstVdecUserPic->usrPicGet)) {
            if (fp_out) {
                res = fclose(fp_out);
                if (res) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, fclose FAILED! res:%d fp_out:%p\n",
                                    VdGrp, res, fp_out);
                }
                fp_out = NULL;
                pstVdecCtx->pOutputFd[VdGrp] = NULL;
            }
        }

        if (pstFrameInfo->bEndOfStream == AX_TRUE) {
            SAMPLE_LOG("VdGrp=%d, bEndOfStream == AX_TRUE, ret AX_ERR_VDEC_FLOW_END", VdGrp);
            sRet = AX_ERR_VDEC_FLOW_END;
            goto ERR_RET;
        }
    }

ERR_RET:
    for (ii = 0; ii < SAMPLE_VDEC_FRAME_CNT; ii++) {
        pstFrameInfo = &stFrameInfo[ii];
        SAMPLE_LOG_N("VdGrp=%d, .u64PTS:%lld, sRet0x%x %s\n",
                    VdGrp, pstFrameInfo->stVFrame.u64PTS, sRet, SampleVdecRetStr(sRet));
    }

    return sRet;
}

static void *_VdecRecvThread(void *arg)
{
    AX_S32 sRet = 0;
    AX_S32 ret = 0;
    SAMPLE_VDEC_ARGS_T *pstVdecGrpArgs = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstVdecCtx = (SAMPLE_VDEC_CONTEXT_T *)arg;
    AX_VDEC_GRP_SET_INFO_T stGrpSet;
    AX_VDEC_GRP_SET_INFO_T *pstGrpSet = &stGrpSet;
    int gi;
    AX_VDEC_GRP VdGrp = 0;
    int flow_end_total_cnt = 0;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    AX_U32 uGrpCount = 0;
    AX_BOOL bRecvFlowEnd[AX_VDEC_MAX_GRP_NUM] = {0};
    AX_VDEC_GRP uStartGrpId;

    if (pstVdecCtx == NULL) {
        SAMPLE_CRIT_LOG("arg == NULL");
        return NULL;
    }

    SampelVdecSetThreadName("smp_dec_select");

    pstCmd = &pstVdecCtx->tCmdParam;
    uGrpCount = pstCmd->uGrpCount;
    uStartGrpId = pstCmd->uStartGrpId;

    memset(pstGrpSet, 0, sizeof(AX_VDEC_GRP_SET_INFO_T));
    SAMPLE_LOG("uGrpCount:%d Enter while(1) SelectGrp \n", uGrpCount);

    while (1) {
        if (pstVdecCtx->GrpStatus[uStartGrpId] == AX_VDEC_GRP_START_RECV || s_ThreadExit) {
            break;
        }

        usleep(1000);
    }

    while (1) {
        if (s_ThreadExit) {
            SAMPLE_LOG("s_ThreadExit:%d, so break\n", s_ThreadExit);
            break;
        }

        SAMPLE_LOG("before SelectGrp \n");
        sRet = AX_VDEC_SelectGrp(pstGrpSet, -1);
        if (sRet != AX_SUCCESS) {
            if (AX_ERR_VDEC_NOT_INIT == sRet) {
                SAMPLE_NOTICE_LOG("AX_ERR_VDEC_NOT_INIT, Need Call AX_VDEC_Init first");
                goto ERR_RET;
            } else if (AX_ERR_VDEC_FLOW_END == sRet) {
                SAMPLE_NOTICE_LOG("recv AX_ERR_VDEC_FLOW_END");
                goto ERR_RET;
            } else if (AX_ERR_VDEC_NOT_PERM == sRet) {
                SAMPLE_NOTICE_LOG("recv AX_ERR_VDEC_NOT_PERM");
                goto ERR_RET;
            }

            SAMPLE_CRIT_LOG("AX_VDEC_SelectGrp FAILED! ret:0x%x %s",
                            sRet, SampleVdecRetStr(sRet));
            goto ERR_RET;
        }

        SAMPLE_LOG("after SelectGrp, u32GrpCount:%d", pstGrpSet->u32GrpCount);
        for (gi = 0; gi < pstGrpSet->u32GrpCount; gi++) {
            VdGrp = pstGrpSet->VdGrp[gi];
            if (VdGrp < uStartGrpId) {
                SAMPLE_CRIT_LOG("VdGrp:%d < uStartGrpId:%d", VdGrp, uStartGrpId);
                goto ERR_RET;
            }

            pstVdecGrpArgs = &pstVdecCtx->stVdecGrpArgs[VdGrp];
            if (pstVdecGrpArgs == NULL) {
                SAMPLE_LOG("VdGrp=%d, pstVdecGrpArgs == NULL", VdGrp);
                continue;
            }

            if (VdGrp == uStartGrpId)
                pstVdecCtx->pOutputFilePath[VdGrp] = pstCmd->pOutputFilePath;
            else
                pstVdecCtx->pOutputFilePath[VdGrp] = NULL;
            SAMPLE_LOG_N("u32GrpCount:%d, u32ChnCount:%d, VdGrp=%d, gi:%d\n",
                        pstGrpSet->u32GrpCount, pstGrpSet->stChnSet[gi].u32ChnCount,
                        VdGrp, gi);
            ret = __VdecRecvFrame(VdGrp, pstVdecCtx);
            if (ret != AX_SUCCESS) {
                if (ret == AX_ERR_VDEC_QUEUE_EMPTY) {
                    SAMPLE_ERR_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s\n",
                                VdGrp, ret, SampleVdecRetStr(ret));
                } else if (ret == AX_ERR_VDEC_UNEXIST) {
                    SAMPLE_ERR_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s \n",
                                       VdGrp, ret, SampleVdecRetStr(ret));
                } else if (AX_ERR_VDEC_NOT_PERM == ret) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s \n",
                                       VdGrp, ret, SampleVdecRetStr(ret));
                } else if (ret == AX_ERR_VDEC_FLOW_END) {
                    SAMPLE_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s\n",
                                VdGrp, ret, SampleVdecRetStr(ret));
                }

                SAMPLE_LOG_TMP("VdGrp=%d, __VdecRecvFrame FAILED! ret=0x%x %s\n",
                                VdGrp, ret, SampleVdecRetStr(ret));
            } else {
                pstVdecCtx->u64SelectFrameCnt++;
            }

            if (ret == AX_ERR_VDEC_FLOW_END) {
                SAMPLE_LOG("VdGrp=%d, gi:%d, flow_end_total_cnt:%d, ->bRecvFlowEnd[VdGrp]:%d\n",
                            VdGrp, gi, flow_end_total_cnt, bRecvFlowEnd[VdGrp]);

                if (bRecvFlowEnd[VdGrp] == AX_FALSE) {
                    flow_end_total_cnt++;
                    bRecvFlowEnd[VdGrp] = AX_TRUE;
                    SAMPLE_LOG("VdGrp=%d, gi:%d, flow_end_total_cnt:%d, ->bRecvFlowEnd[VdGrp]:%d\n",
                               VdGrp, gi, flow_end_total_cnt, bRecvFlowEnd[VdGrp]);
                }
            }
        }

        if (flow_end_total_cnt == uGrpCount) {
            SAMPLE_LOG("flow_end_total_cnt:%d flow end!\n", flow_end_total_cnt);
            break;
        }
    }

ERR_RET:
    for (gi = 0; gi < uGrpCount; gi++) {
        pstVdecCtx->bRecvFlowEnd[gi + uStartGrpId] = AX_TRUE;
    }

    if (pstCmd->bQuitWait == AX_TRUE) {
        SAMPLE_LOG_TMP("VdecRecvFrame /Finished! Now waiting forever until press q");

        while(('q' != getchar())) {
            sleep(1);
        }

        for (gi = 0; gi < uGrpCount; gi++) {
            pstVdecCtx->bGrpQuitWait[gi + uStartGrpId] = AX_FALSE;
            SAMPLE_LOG("VdGrp=%d, bGrpQuitWait:%d", VdGrp, pstVdecCtx->bGrpQuitWait[VdGrp]);
        }
    }

    if (pstVdecCtx->u64SelectFrameCnt) {
        g_u64GetFrmTag += 1;
    } else {
        SAMPLE_CRIT_LOG("thread exit:%d, pstGrpSet->u32GrpCount:%d",
                        s_ThreadExit, pstGrpSet->u32GrpCount);
    }

    if (pstVdecCtx->u64SelectFrameCnt) {
        gettimeofday(&pstVdecCtx->Timeend, NULL);
        AX_U32 total_usec = 1000000 * (pstVdecCtx->Timeend.tv_sec - pstVdecCtx->Timebegin.tv_sec)
                            + pstVdecCtx->Timeend.tv_usec - pstVdecCtx->Timebegin.tv_usec;
        float total_msec = (float)total_usec / 1000.f;
        float msec_per_frame = total_msec / (float)pstVdecCtx->u64SelectFrameCnt;

        SAMPLE_LOG_TMP("uGrpCount=%d, msec per frame: %.1f, AVG FPS: %.1f. total msec:%.1f, total frame count:%lld \n",
                    uGrpCount, msec_per_frame, 1000.f / msec_per_frame, total_msec, pstVdecCtx->u64SelectFrameCnt);
    }

    SAMPLE_LOG_TMP(" RecvThread exit, last VdGrp=%d\n", VdGrp);
    return NULL;
}

static void *__VdecGrpChnRecvThread(void *arg)
{
    SAMPLE_VDEC_ARGS_T *pstFuncArgs = (SAMPLE_VDEC_ARGS_T *)arg;
    AX_VDEC_GRP VdGrp = 0;
    AX_S32 ret = 0;
    SAMPLE_VDEC_CONTEXT_T *pstCtx = NULL;
    AX_U32 recvFrmCnt = 0;
    AX_U32 sleepCnt = 1;

    if (arg == NULL) {
        SAMPLE_CRIT_LOG("arg == NULL");
        return NULL;
    }

    SampelVdecSetThreadName("smp_dec_recv_%d", pstFuncArgs->VdGrp);

    VdGrp = pstFuncArgs->VdGrp;
    pstCtx = pstFuncArgs->pstCtx;

    if (NULL == pstCtx) {
        SAMPLE_CRIT_LOG("pstFuncArgs->pstCtx == NULL");
        return NULL;
    }

    while (1) {
        if (pstCtx->GrpStatus[VdGrp] == AX_VDEC_GRP_START_RECV || s_ThreadExit) {
            break;
        }

        usleep(1000);
    }

    while (1) {
        if (s_ThreadExit) {
            pstCtx->bRecvFlowEnd[VdGrp] = AX_TRUE;
            SAMPLE_LOG_TMP("VdGrp=%d, thread exit:%d\n", VdGrp, s_ThreadExit);
            break;
        }

        SAMPLE_LOG_N("VdGrp=%d", VdGrp);

        ret = __VdecRecvFrame(VdGrp, pstCtx);
        if (ret != AX_SUCCESS) {
            if (ret == AX_ERR_VDEC_QUEUE_EMPTY || ret == AX_ERR_VDEC_STRM_ERROR) {
                SAMPLE_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s\n",
                           VdGrp, ret, SampleVdecRetStr(ret));
                continue;
            } else if (ret == AX_ERR_VDEC_UNEXIST) {
                SAMPLE_ERR_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s \n",
                               VdGrp, ret, SampleVdecRetStr(ret));
                continue;
            } else if (AX_ERR_VDEC_NOT_PERM == ret) {
                SAMPLE_CRIT_LOG("VdGrp=%d, __VdecRecvFrame ret=0x%x %s \n",
                               VdGrp, ret, SampleVdecRetStr(ret));
                continue;
            } else if (ret == AX_ERR_VDEC_FLOW_END) {
                if (pstCtx->bRecvFlowEnd[VdGrp] == AX_FALSE)
                    pstCtx->bRecvFlowEnd[VdGrp] = AX_TRUE;
                SAMPLE_LOG_TMP("VdGrp=%d, __VdecRecvFrame ret=0x%x %s\n",
                               VdGrp, ret, SampleVdecRetStr(ret));
                break;
            } else {
                SAMPLE_LOG_TMP("VdGrp=%d, __VdecRecvFrame FAILED! ret=0x%x %s\n",
                               VdGrp, ret, SampleVdecRetStr(ret));
            }
            break;
        } else {
            recvFrmCnt++;
        }

        if (pstCtx->tCmdParam.bSleep && (recvFrmCnt % (3 + VdGrp * 5) == 0)) {
            SAMPLE_LOG_TMP("VdGrp %d recvFrmCnt %d start sleep test\n", VdGrp, recvFrmCnt);
            ret = AX_SYS_Sleep();
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("================= AX_SYS_Sleep success, sleepCnt %d\n", sleepCnt++);
            else
                SAMPLE_CRIT_LOG("AX_SYS_Sleep FAILED! ret:0x%x", ret);
        }
    }

    if (recvFrmCnt) {
        g_u64GetFrmTag += 1;
    } else {
        SAMPLE_CRIT_LOG("VdGrp=%d, thread exit:%d", VdGrp, s_ThreadExit);
    }

    SAMPLE_LOG_TMP("VdGrp=%d, recvFrmCnt %d RecvThread exit\n", VdGrp, recvFrmCnt);
    return NULL;
}

static AX_S32 __VdecSendEndOfStream(AX_VDEC_GRP VdGrp)
{
    AX_S32 sRet = 0;
    AX_VDEC_STREAM_T tStrInfo = {0};
    tStrInfo.bEndOfStream = AX_TRUE;
    sRet = AX_VDEC_SendStream(VdGrp, &tStrInfo, -1);
    if (sRet != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x %s\n",
                        VdGrp, sRet, SampleVdecRetStr(sRet));
    }

    return sRet;
}

static AX_S32 __VdecInputModeFrame(SAMPLE_VDEC_ARGS_T *pstFuncArgs,
                                   SAMPLE_INPUT_FILE_INFO_T *pstStreamInfo,
                                   SAMPLE_STREAM_BUF_T *pstStreamBuf)
{
    AX_S32 ret = 0;
    AX_S32 sRet = 0;
    AX_VDEC_STREAM_T tStrInfo = {0};
    AX_VDEC_GRP VdGrp = 0;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstCtx = NULL;
    AX_U32 uBufSize = 0;
    size_t sReadLen = 0;
    AX_U64 u64SendPicNum = 0;
    AX_BOOL bContSendStm = AX_TRUE;
    AX_S32 sMilliSec = -1;
    AX_BOOL bPerfTest = AX_FALSE;
    AX_BOOL bReadFrm = AX_TRUE;
    AX_S32 sLoopDecNum = 0;
    AX_BOOL bSkipRelease = AX_FALSE;

    if (NULL == pstFuncArgs) {
        SAMPLE_CRIT_LOG("NULL == pstFuncArgs\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    VdGrp = pstFuncArgs->VdGrp;
    if (NULL == pstStreamInfo) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamInfo\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (NULL == pstStreamBuf) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamBuf\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (pstStreamBuf->tBufAddr.pVirAddr == NULL) {
        SAMPLE_CRIT_LOG("pstStreamBuf->tBufAddr.pVirAddr == NULL\n");
        ret = AX_ERR_VDEC_BAD_ADDR;
        goto ERR_RET;
    }

    pstCtx = pstFuncArgs->pstCtx;
    if (NULL == pstCtx) {
        SAMPLE_CRIT_LOG("pstFuncArgs->pstCtx == NULL\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    pstCmd = &pstCtx->tCmdParam;
    if (pstCmd == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, pstCmd == NULL", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    sMilliSec = pstCmd->sMilliSec;
    bPerfTest = pstCmd->bPerfTest;
    pstStreamInfo->enDecType = pstCmd->enDecType;
    uBufSize = pstStreamBuf->uBufSize;
    sLoopDecNum = pstCmd->sLoopDecNum;
    bSkipRelease = pstCmd->bSkipRelease;
    SAMPLE_LOG("begin to decoder. uBufSize=%d\n", uBufSize);

    while (1) {
        if (s_ThreadExit || (sLoopDecNum <= 0)) {
            sRet = __VdecSendEndOfStream(VdGrp);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, __VdecSendEndOfStream FAILED! ret:0x%x %s",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
                ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET;
            }
            SAMPLE_LOG("VdGrp=%d, thread exit:%d, __VdecSendEndOfStream Done! break sendstream while(1)",
                       VdGrp, s_ThreadExit);
            break;
        }

        if (bReadFrm) {
            if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                if (pstCmd->bFfmpegEnable) {
                    sRet = SampleVdecFfmpegExtractOnePic(&pstCtx->stFfmpeg[VdGrp], &pstCtx->stBitStreamInfo[VdGrp], pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegExtractOnePic FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                } else {
                    sRet = StreamFileParserReadFrame(pstStreamInfo, pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameH264 FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                }
#else
                sRet = StreamFileParserReadFrame(pstStreamInfo, pstStreamBuf, &sReadLen);
                if (sRet) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameH264 FAILED! ret:0x%x\n", VdGrp, sRet);
                    ret = AX_ERR_VDEC_STRM_ERROR;
                    goto ERR_RET;
                }
#endif
            } else if (pstCmd->enDecType == PT_JPEG) {
                if (!(bPerfTest && u64SendPicNum)) {
                    sRet = StreamParserReadFrameJpeg(pstStreamInfo, pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameJpeg FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                }
            }
        }

        if (sReadLen > 0) {
            tStrInfo.pu8Addr = pstStreamBuf->tBufAddr.pVirAddr;
            tStrInfo.u64PhyAddr = 0;
            tStrInfo.u32StreamPackLen = (AX_U32)sReadLen;  /*stream len*/
            tStrInfo.bEndOfFrame = AX_TRUE;
            tStrInfo.bEndOfStream = AX_FALSE;

            if (pstCmd->bSkipFrms && (u64SendPicNum & 1))
                tStrInfo.u64PTS = -1; /* dec not out put */
            else if (pstCmd->u32StreamFps)
                tStrInfo.u64PTS = (u64SendPicNum + 1) * 1000000 / pstCmd->u32StreamFps;
            else
                tStrInfo.u64PTS = u64SendPicNum;

            tStrInfo.u64PrivateData = 0xAFAF5A5A;
        } else {
            if (pstCmd->enDecType == PT_JPEG) {
                if (!pstCmd->bDynRes) {
                    sLoopDecNum--;
                } else if (pstCmd->bDynRes && (pstStreamInfo->fInput == pstCtx->pNewInputFd[VdGrp])) {
                    sLoopDecNum--;
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    pstStreamInfo->fInput = pstCtx->pInputFd[VdGrp];
                    pstStreamInfo->curPos = 0;
                    pstStreamInfo->sFileSize = pstCtx->oInputFileSize[VdGrp];
               } else if (pstCmd->bDynRes && (pstStreamInfo->fInput == pstCtx->pInputFd[VdGrp])) {
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    pstStreamInfo->fInput = pstCtx->pNewInputFd[VdGrp];
                    pstStreamInfo->curPos = 0;
                    pstStreamInfo->sFileSize = pstCtx->oNewInputFileSize[VdGrp];
                }
            } else {
                sLoopDecNum--;
            }

            if (sLoopDecNum > 0) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                if (pstCmd->bFfmpegEnable && pstCmd->enDecType != PT_JPEG) {
                    if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                            && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
                        sRet = SampleVdecFfmpegDeinit(&pstCtx->stFfmpeg[VdGrp], VdGrp);
                        if (sRet != AX_SUCCESS) {
                            SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegDeinit FAILED! ret:0x%x\n",
                                        VdGrp, sRet);
                        }
                        pstCtx->stBitStreamInfo[VdGrp].VdGrp = VdGrp;
                        sRet = SampleVdecFfmpegInit(&pstCtx->stFfmpeg[VdGrp], pstCmd->pInputFilePath, &pstCtx->stBitStreamInfo[VdGrp]);
                        if (sRet != AX_SUCCESS) {
                            SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegInit FAILED! ret:0x%x\n",
                                        VdGrp, sRet);
                        }
                        continue;
                    }
                } else {
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    if (pstCmd->enDecType == PT_JPEG)
                        pstStreamInfo->curPos = 0;
                    continue;
                }
#else
                fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                if (pstCmd->enDecType == PT_JPEG)
                    pstStreamInfo->curPos = 0;
                continue;
#endif
            } else {
                SAMPLE_LOG("VdGrp=%d, Notice! sLoopDecNum: %d\n", VdGrp, sLoopDecNum);
                continue;
            }
        }

        SAMPLE_LOG("VdGrp=%d, before AX_VDEC_SendStream, u64SendPicNum:%d, sReadLen:0x%lx",
                   VdGrp, u64SendPicNum, sReadLen);

        SAMPLE_LOG("VdGrp=%d, tStrInfo.pu8Addr:%p, tStrInfo.u64PhyAddr:0x%llx, sRecvPicNum:%d ",
                   VdGrp, tStrInfo.pu8Addr, tStrInfo.u64PhyAddr, pstCmd->sRecvPicNum);

        SAMPLE_LOG("VdGrp=%d, thread exit:%d, .u64PTS:%lld .bEndOfStream:%d, .bEndOfFrame:%d, .bSkipDisplay:%d",
                   VdGrp, s_ThreadExit, tStrInfo.u64PTS,
                   tStrInfo.bEndOfStream, tStrInfo.bEndOfFrame, tStrInfo.bSkipDisplay);

        if ((pstCtx->Timebegin.tv_sec == 0) && (pstCtx->Timebegin.tv_usec == 0)) {
            gettimeofday(&pstCtx->Timebegin, NULL);
        }

        sRet = AX_VDEC_SendStream(VdGrp, &tStrInfo, sMilliSec);
        if (sRet != AX_SUCCESS) {
            if (sRet == AX_ERR_VDEC_FLOW_END) {
                SAMPLE_LOG("VdGrp=%d, AX_VDEC_SendStream ret AX_ERR_VDEC_FLOW_END, u64SendPicNum:%d\n", VdGrp, u64SendPicNum);
                break;
            } else if (sRet == AX_ERR_VDEC_QUEUE_FULL) {
                bReadFrm = AX_FALSE;
                usleep(1000);
                continue;
            }

            if (sRet != AX_ERR_VDEC_NOT_SUPPORT) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x %s\n",
                            VdGrp, sRet, SampleVdecRetStr(sRet));
                ret = sRet;
            } else {
                ret = AX_ERR_VDEC_NOT_SUPPORT;
            }

            goto ERR_RET;
        }

        bReadFrm = AX_TRUE;
        u64SendPicNum ++;

        if (pstCmd->bResetGrp && (u64SendPicNum == 10)) {
            ret = AX_VDEC_StopRecvStream(VdGrp);
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_StopRecvStream success \n", VdGrp);
            else
                SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_StopRecvStream FAILED! ret:0x%x", VdGrp, ret);

            /* wait release frm */
            while ((pstCtx->recvFrmCnt[VdGrp] != pstCtx->releaseFrmCnt[VdGrp]
                || u64SendPicNum != pstCtx->releaseFrmCnt[VdGrp])
                && !bSkipRelease)
                usleep(5000);

            ret = AX_VDEC_ResetGrp(VdGrp);
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_ResetGrp success \n", VdGrp);
            else
                SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_ResetGrp FAILED! ret:0x%x", VdGrp, ret);

            AX_VDEC_RECV_PIC_PARAM_T tRecvParam = {0};
            ret = AX_VDEC_StartRecvStream(VdGrp, &tRecvParam);
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_StartRecvStream success \n", VdGrp);
            else
                SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_StartRecvStream FAILED! ret:0x%x", VdGrp, ret);
        }

        if (u64SendPicNum == pstCmd->usrPicIdx) {
            sRet = VdecUserPicEnable(VdGrp, pstFuncArgs->tUsrPicArgs.pstVdecUserPic,
                                     &bContSendStm, pstCtx);
            if (sRet != AX_SUCCESS){
                SAMPLE_CRIT_LOG("VdGrp=%d, VdecUserPicEnable FAILED! ret:0x%x %s",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
                goto ERR_RET;
            }

            if (!bContSendStm) {
                sReadLen = 0;
                sLoopDecNum = 0;
                continue;
            }
        }

        if (u64SendPicNum == pstCmd->sRecvPicNum)
            sLoopDecNum = 0;
    }

    return 0;

ERR_RET:
    return ret;
}
static AX_S32 __VdecInputModeCompact(SAMPLE_VDEC_ARGS_T *pstFuncArgs,
                                   SAMPLE_INPUT_FILE_INFO_T *pstStreamInfo,
                                   SAMPLE_STREAM_BUF_T *pstStreamBuf)
{
    AX_S32 ret = 0;
    AX_S32 sRet = 0;
    AX_VDEC_STREAM_T tStrInfo = {0};
    AX_VDEC_STREAM_T tStrInfoTmp = {0};
    AX_VDEC_GRP VdGrp = 0;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstCtx = NULL;
    AX_U32 uBufSize = 0;
    size_t sReadLen = 0;
    AX_U32 u64SendPicNum = 0;
    AX_BOOL bContSendStm = AX_TRUE;
    AX_S32 sMilliSec = -1;
    AX_BOOL bPerfTest = AX_FALSE;
    AX_BOOL bReadFrm = AX_TRUE;
    AX_U32 u32TmpSize = 0;
    AX_S32 sLoopDecNum = 0;

    if (NULL == pstFuncArgs) {
        SAMPLE_CRIT_LOG("NULL == pstFuncArgs\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    VdGrp = pstFuncArgs->VdGrp;
    if (NULL == pstStreamInfo) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamInfo\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (NULL == pstStreamBuf) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamBuf\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (pstStreamBuf->tBufAddr.pVirAddr == NULL) {
        SAMPLE_CRIT_LOG("pstStreamBuf->tBufAddr.pVirAddr == NULL\n");
        ret = AX_ERR_VDEC_BAD_ADDR;
        goto ERR_RET;
    }

    pstCtx = pstFuncArgs->pstCtx;
    if (NULL == pstCtx) {
        SAMPLE_CRIT_LOG("pstFuncArgs->pstCtx == NULL\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    pstCmd = &pstCtx->tCmdParam;
    if (pstCmd == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, pstCmd == NULL", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    sMilliSec = pstCmd->sMilliSec;
    bPerfTest = pstCmd->bPerfTest;
    pstStreamInfo->enDecType = pstCmd->enDecType;
    uBufSize = pstStreamBuf->uBufSize;
    sLoopDecNum = pstCmd->sLoopDecNum;
    SAMPLE_LOG("begin to decoder. uBufSize=%d\n", uBufSize);

    while (1) {
        if (s_ThreadExit || (sLoopDecNum <= 0)) {
            sRet = __VdecSendEndOfStream(VdGrp);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, __VdecSendEndOfStream FAILED! ret:0x%x %s",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
                ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET;
            }
            SAMPLE_LOG_TMP("VdGrp=%d, thread exit:%d, __VdecSendEndOfStream Done! break sendstream while(1)",
                       VdGrp, s_ThreadExit);
            break;
        }

        if (bReadFrm) {
            if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                if (pstCmd->bFfmpegEnable) {
                    sRet = SampleVdecFfmpegExtractOnePic(&pstCtx->stFfmpeg[VdGrp], &pstCtx->stBitStreamInfo[VdGrp], pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegExtractOnePic FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                } else {
                    sRet = StreamFileParserReadFrame(pstStreamInfo, pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameH264 FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                }
#else
                sRet = StreamFileParserReadFrame(pstStreamInfo, pstStreamBuf, &sReadLen);
                if (sRet) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameH264 FAILED! ret:0x%x\n", VdGrp, sRet);
                    ret = AX_ERR_VDEC_STRM_ERROR;
                    goto ERR_RET;
                }
#endif
            } else if (pstCmd->enDecType == PT_JPEG) {
                if (!(bPerfTest && u64SendPicNum)) {
                    sRet = StreamParserReadFrameJpeg(pstStreamInfo, pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameJpeg FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                }
            }
        }

        if (sReadLen > 0) {
            tStrInfo.pu8Addr = pstStreamBuf->tBufAddr.pVirAddr;
            tStrInfo.u64PhyAddr = 0;
            tStrInfo.u32StreamPackLen = (AX_U32)sReadLen;  /*stream len*/
            tStrInfo.bEndOfFrame = AX_TRUE;
            tStrInfo.bEndOfStream = AX_FALSE;

            tStrInfo.u64PTS = 0;
            tStrInfo.u64PrivateData = 0xAFAF5A5A;
        } else {
            if (pstCmd->enDecType == PT_JPEG) {
                if (!pstCmd->bDynRes) {
                    sLoopDecNum--;
                } else if (pstCmd->bDynRes && (pstStreamInfo->fInput == pstCtx->pNewInputFd[VdGrp])) {
                    sLoopDecNum--;
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    pstStreamInfo->fInput = pstCtx->pInputFd[VdGrp];
                    pstStreamInfo->curPos = 0;
                    pstStreamInfo->sFileSize = pstCtx->oInputFileSize[VdGrp];
               } else if (pstCmd->bDynRes && (pstStreamInfo->fInput == pstCtx->pInputFd[VdGrp])) {
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    pstStreamInfo->fInput = pstCtx->pNewInputFd[VdGrp];
                    pstStreamInfo->curPos = 0;
                    pstStreamInfo->sFileSize = pstCtx->oNewInputFileSize[VdGrp];
                }
            } else {
                sLoopDecNum--;
            }
            SAMPLE_LOG_TMP("read data fail\n");
            if (sLoopDecNum > 0) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                if (pstCmd->bFfmpegEnable && pstCmd->enDecType != PT_JPEG) {
                    if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                            && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
                        sRet = SampleVdecFfmpegDeinit(&pstCtx->stFfmpeg[VdGrp], VdGrp);
                        if (sRet != AX_SUCCESS) {
                            SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegDeinit FAILED! ret:0x%x\n",
                                        VdGrp, sRet);
                        }
                        pstCtx->stBitStreamInfo[VdGrp].VdGrp = VdGrp;
                        sRet = SampleVdecFfmpegInit(&pstCtx->stFfmpeg[VdGrp], pstCmd->pInputFilePath, &pstCtx->stBitStreamInfo[VdGrp]);
                        if (sRet != AX_SUCCESS) {
                            SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegInit FAILED! ret:0x%x\n",
                                        VdGrp, sRet);
                        }
                        continue;
                    }
                } else {
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    if (pstCmd->enDecType == PT_JPEG)
                        pstStreamInfo->curPos = 0;
                    continue;
                }
#else
                fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                if (pstCmd->enDecType == PT_JPEG)
                     pstStreamInfo->curPos = 0;
                continue;
#endif
            } else {
                SAMPLE_LOG("VdGrp=%d, Notice! sLoopDecNum: %d\n", VdGrp, sLoopDecNum);
                continue;
            }
        }

        SAMPLE_LOG("VdGrp=%d, before AX_VDEC_SendStream, u64SendPicNum:%d, sReadLen:0x%lx",
                   VdGrp, u64SendPicNum, sReadLen);

        SAMPLE_LOG("VdGrp=%d, tStrInfo.pu8Addr:%p, tStrInfo.u64PhyAddr:0x%llx, sRecvPicNum:%d ",
                   VdGrp, tStrInfo.pu8Addr, tStrInfo.u64PhyAddr, pstCmd->sRecvPicNum);

        SAMPLE_LOG("VdGrp=%d, thread exit:%d, .u64PTS:%lld .bEndOfStream:%d, .bEndOfFrame:%d, .bSkipDisplay:%d",
                   VdGrp, s_ThreadExit, tStrInfo.u64PTS,
                   tStrInfo.bEndOfStream, tStrInfo.bEndOfFrame, tStrInfo.bSkipDisplay);

        if ((pstCtx->Timebegin.tv_sec == 0) && (pstCtx->Timebegin.tv_usec == 0)) {
            gettimeofday(&pstCtx->Timebegin, NULL);
        }

        SAMPLE_LOG_N("new frm %d ptr %p size %d\n", u64SendPicNum, tStrInfo.pu8Addr, tStrInfo.u32StreamPackLen);
        u32TmpSize = tStrInfo.u32StreamPackLen / 4;

        for (int sendCnt = 0; sendCnt < 4; sendCnt++) {
            tStrInfoTmp.bEndOfFrame  = AX_FALSE;
            tStrInfoTmp.bEndOfStream = AX_FALSE;
            tStrInfoTmp.u32StreamPackLen = u32TmpSize;
            tStrInfoTmp.pu8Addr = tStrInfo.pu8Addr + sendCnt * u32TmpSize;
            tStrInfoTmp.u64PhyAddr = tStrInfo.u64PhyAddr + sendCnt * u32TmpSize;

            if (sendCnt == 3) {
                tStrInfoTmp.bEndOfFrame  = AX_TRUE;
                tStrInfoTmp.bEndOfStream = tStrInfo.bEndOfStream;
                tStrInfoTmp.u32StreamPackLen = tStrInfo.u32StreamPackLen - u32TmpSize * 3;
            }
            SAMPLE_LOG("send idx %d ptr %p size %d\n", sendCnt, tStrInfoTmp.pu8Addr, tStrInfoTmp.u32StreamPackLen);

            sRet = AX_VDEC_SendStream(VdGrp, &tStrInfoTmp, sMilliSec);
            if (sRet != AX_SUCCESS) {
                if (sRet == AX_ERR_VDEC_FLOW_END) {
                    SAMPLE_LOG("VdGrp=%d, AX_VDEC_SendStream ret AX_ERR_VDEC_FLOW_END, u64SendPicNum:%d\n", VdGrp, u64SendPicNum);
                    break;
                } else if (sRet == AX_ERR_VDEC_QUEUE_FULL) {
                    bReadFrm = AX_FALSE;
                    usleep(1000);
                    continue;
                }

                if (sRet != AX_ERR_VDEC_NOT_SUPPORT) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x %s\n",
                                    VdGrp, sRet, SampleVdecRetStr(sRet));
                    ret = sRet;
                } else {
                    ret = AX_ERR_VDEC_NOT_SUPPORT;
                }

                goto ERR_RET;
            }
        }

        bReadFrm = AX_TRUE;
        u64SendPicNum ++;

        if (u64SendPicNum == pstCmd->usrPicIdx) {
            sRet = VdecUserPicEnable(VdGrp, pstFuncArgs->tUsrPicArgs.pstVdecUserPic,
                                     &bContSendStm, pstCtx);
            if (sRet != AX_SUCCESS){
                SAMPLE_CRIT_LOG("VdGrp=%d, VdecUserPicEnable FAILED! ret:0x%x %s",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
                goto ERR_RET;
            }

            if (!bContSendStm) {
                sReadLen = 0;
                sLoopDecNum = 0;
                continue;
            }
        }

        if (u64SendPicNum == pstCmd->sRecvPicNum)
            sLoopDecNum = 0;
    }

    return 0;

ERR_RET:
    return ret;
}
static AX_S32 __VdecInputModeSlice(SAMPLE_VDEC_ARGS_T *pstFuncArgs,
                                   SAMPLE_INPUT_FILE_INFO_T *pstStreamInfo,
                                   SAMPLE_STREAM_BUF_T *pstStreamBuf)
{
    AX_S32 ret = 0;
    AX_S32 sRet = 0;
    AX_VDEC_STREAM_T tStrInfo = {0};
    AX_VDEC_STREAM_T tStrInfoTmp = {0};
    AX_U8 *puStrAddr = NULL;
    AX_VDEC_GRP VdGrp = 0;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstCtx = NULL;
    AX_U32 uBufSize = 0;
    size_t sReadLen = 0;
    AX_U32 u64SendPicNum = 0;
    AX_BOOL bContSendStm = AX_TRUE;
    AX_S32 sMilliSec = -1;
    AX_BOOL bPerfTest = AX_FALSE;
    AX_BOOL bReadFrm = AX_TRUE;
    AX_U32 u32TmpSize = 0;
    AX_U32 uZeroCount = 0;
    AX_U32 uPos = 0;
    AX_U32 uSliceCnt = 0;
    AX_BOOL bRet = AX_TRUE;
    AX_S32 sLoopDecNum = 0;

    if (NULL == pstFuncArgs) {
        SAMPLE_CRIT_LOG("NULL == pstFuncArgs\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    VdGrp = pstFuncArgs->VdGrp;
    if (NULL == pstStreamInfo) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamInfo\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (NULL == pstStreamBuf) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamBuf\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (pstStreamBuf->tBufAddr.pVirAddr == NULL) {
        SAMPLE_CRIT_LOG("pstStreamBuf->tBufAddr.pVirAddr == NULL\n");
        ret = AX_ERR_VDEC_BAD_ADDR;
        goto ERR_RET;
    }

    pstCtx = pstFuncArgs->pstCtx;
    if (NULL == pstCtx) {
        SAMPLE_CRIT_LOG("pstFuncArgs->pstCtx == NULL\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    pstCmd = &pstCtx->tCmdParam;
    if (pstCmd == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, pstCmd == NULL", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    sMilliSec = pstCmd->sMilliSec;
    bPerfTest = pstCmd->bPerfTest;
    pstStreamInfo->enDecType = pstCmd->enDecType;
    uBufSize = pstStreamBuf->uBufSize;
    sLoopDecNum = pstCmd->sLoopDecNum;
    SAMPLE_LOG("begin to decoder. uBufSize=%d\n", uBufSize);

    while (1) {
        if (s_ThreadExit || (sLoopDecNum <= 0)) {
            sRet = __VdecSendEndOfStream(VdGrp);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, __VdecSendEndOfStream FAILED! ret:0x%x %s",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
                ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET;
            }
            SAMPLE_LOG_TMP("VdGrp=%d, thread exit:%d, __VdecSendEndOfStream Done! break sendstream while(1)",
                       VdGrp, s_ThreadExit);
            break;
        }

        if (bReadFrm) {
            if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                if (pstCmd->bFfmpegEnable) {
                    sRet = SampleVdecFfmpegExtractOnePic(&pstCtx->stFfmpeg[VdGrp], &pstCtx->stBitStreamInfo[VdGrp], pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegExtractOnePic FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                } else {
                    sRet = StreamFileParserReadFrame(pstStreamInfo, pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameH264 FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                }
#else
                sRet = StreamFileParserReadFrame(pstStreamInfo, pstStreamBuf, &sReadLen);
                if (sRet) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameH264 FAILED! ret:0x%x\n", VdGrp, sRet);
                    ret = AX_ERR_VDEC_STRM_ERROR;
                    goto ERR_RET;
                }
#endif
            } else if (pstCmd->enDecType == PT_JPEG) {
                if (!(bPerfTest && u64SendPicNum)) {
                    sRet = StreamParserReadFrameJpeg(pstStreamInfo, pstStreamBuf, &sReadLen);
                    if (sRet) {
                        SAMPLE_CRIT_LOG("VdGrp=%d, StreamParserReadFrameJpeg FAILED! ret:0x%x\n", VdGrp, sRet);
                        ret = AX_ERR_VDEC_STRM_ERROR;
                        goto ERR_RET;
                    }
                }
            }
        }

        if (sReadLen > 0) {
            tStrInfo.pu8Addr = pstStreamBuf->tBufAddr.pVirAddr;
            tStrInfo.u64PhyAddr = 0;
            tStrInfo.u32StreamPackLen = (AX_U32)sReadLen;  /*stream len*/
            tStrInfo.bEndOfFrame = AX_TRUE;
            tStrInfo.bEndOfStream = AX_FALSE;

            tStrInfo.u64PTS = 0;
            tStrInfo.u64PrivateData = 0xAFAF5A5A;
        } else {
            if (pstCmd->enDecType == PT_JPEG) {
                if (!pstCmd->bDynRes) {
                    sLoopDecNum--;
                } else if (pstCmd->bDynRes && (pstStreamInfo->fInput == pstCtx->pNewInputFd[VdGrp])) {
                    sLoopDecNum--;
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    pstStreamInfo->fInput = pstCtx->pInputFd[VdGrp];
                    pstStreamInfo->curPos = 0;
                    pstStreamInfo->sFileSize = pstCtx->oInputFileSize[VdGrp];
               } else if (pstCmd->bDynRes && (pstStreamInfo->fInput == pstCtx->pInputFd[VdGrp])) {
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    pstStreamInfo->fInput = pstCtx->pNewInputFd[VdGrp];
                    pstStreamInfo->curPos = 0;
                    pstStreamInfo->sFileSize = pstCtx->oNewInputFileSize[VdGrp];
                }
            } else {
                sLoopDecNum--;
            }
            SAMPLE_LOG_TMP("read data fail\n");
            if (sLoopDecNum > 0) {
#ifdef AX_VDEC_FFMPEG_ENABLE
                if (pstCmd->bFfmpegEnable && pstCmd->enDecType != PT_JPEG) {
                    if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                            && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
                        sRet = SampleVdecFfmpegDeinit(&pstCtx->stFfmpeg[VdGrp], VdGrp);
                        if (sRet != AX_SUCCESS) {
                            SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegDeinit FAILED! ret:0x%x\n",
                                        VdGrp, sRet);
                        }
                        pstCtx->stBitStreamInfo[VdGrp].VdGrp = VdGrp;
                        sRet = SampleVdecFfmpegInit(&pstCtx->stFfmpeg[VdGrp], pstCmd->pInputFilePath, &pstCtx->stBitStreamInfo[VdGrp]);
                        if (sRet != AX_SUCCESS) {
                            SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegInit FAILED! ret:0x%x\n",
                                        VdGrp, sRet);
                        }
                        continue;
                    }
                } else {
                    fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                    if (pstCmd->enDecType == PT_JPEG)
                        pstStreamInfo->curPos = 0;
                    continue;
                }
#else
                fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                if (pstCmd->enDecType == PT_JPEG)
                    pstStreamInfo->curPos = 0;
                continue;
#endif
            } else {
                SAMPLE_LOG("VdGrp=%d, Notice! sLoopDecNum: %d\n", VdGrp, sLoopDecNum);
                continue;
            }
        }

        SAMPLE_LOG("VdGrp=%d, before AX_VDEC_SendStream, u64SendPicNum:%d, sReadLen:0x%lx",
                   VdGrp, u64SendPicNum, sReadLen);

        SAMPLE_LOG("VdGrp=%d, tStrInfo.pu8Addr:%p, tStrInfo.u64PhyAddr:0x%llx, sRecvPicNum:%d ",
                   VdGrp, tStrInfo.pu8Addr, tStrInfo.u64PhyAddr, pstCmd->sRecvPicNum);

        SAMPLE_LOG("VdGrp=%d, thread exit:%d, .u64PTS:%lld .bEndOfStream:%d, .bEndOfFrame:%d, .bSkipDisplay:%d",
                   VdGrp, s_ThreadExit, tStrInfo.u64PTS,
                   tStrInfo.bEndOfStream, tStrInfo.bEndOfFrame, tStrInfo.bSkipDisplay);

        if ((pstCtx->Timebegin.tv_sec == 0) && (pstCtx->Timebegin.tv_usec == 0)) {
            gettimeofday(&pstCtx->Timebegin, NULL);
        }

        SAMPLE_LOG_N("new frm ptr %p size %d\n", tStrInfo.pu8Addr, tStrInfo.u32StreamPackLen);
        u32TmpSize = tStrInfo.u32StreamPackLen;
        puStrAddr = tStrInfo.pu8Addr;
        uZeroCount = 2;
        uSliceCnt = 0;

        do {
            if (u32TmpSize > 4) {
                bRet = SampleVdecSearchStartCode(puStrAddr + uZeroCount, u32TmpSize - uZeroCount, &uPos, &uZeroCount);
                if (bRet) {
                    tStrInfoTmp.bEndOfFrame  = AX_FALSE;
                    tStrInfoTmp.bEndOfStream = AX_FALSE;
                    tStrInfoTmp.u32StreamPackLen = uPos + uZeroCount;
                    tStrInfoTmp.pu8Addr = puStrAddr;
                    tStrInfoTmp.u64PhyAddr = tStrInfo.u64PhyAddr + (puStrAddr - tStrInfo.pu8Addr);
                    SAMPLE_LOG("frm %d slice %d data: %#x %#x %#x %#x %#x\n", u64SendPicNum, uSliceCnt,
                                   puStrAddr[0], puStrAddr[1], puStrAddr[2], puStrAddr[3], puStrAddr[4]);
                    puStrAddr += tStrInfoTmp.u32StreamPackLen;
                    u32TmpSize -= tStrInfoTmp.u32StreamPackLen;
                    uSliceCnt++;
                } else {
                    tStrInfoTmp.bEndOfFrame  = AX_TRUE;
                    tStrInfoTmp.bEndOfStream = AX_FALSE;
                    tStrInfoTmp.u32StreamPackLen = u32TmpSize;
                    tStrInfoTmp.pu8Addr = puStrAddr;
                    tStrInfoTmp.u64PhyAddr = tStrInfo.u64PhyAddr + (puStrAddr - tStrInfo.pu8Addr);
                    SAMPLE_LOG("frm %d last slice %d data:  %#x %#x %#x %#x %#x %#x\n", u64SendPicNum, uSliceCnt,
                                   puStrAddr[0], puStrAddr[1], puStrAddr[2], puStrAddr[3], puStrAddr[4], puStrAddr[5]);
                }
            } else {
                tStrInfoTmp.bEndOfFrame  = AX_TRUE;
                tStrInfoTmp.bEndOfStream = AX_FALSE;
                tStrInfoTmp.u32StreamPackLen = u32TmpSize;
                tStrInfoTmp.pu8Addr = puStrAddr;
                tStrInfoTmp.u64PhyAddr = tStrInfo.u64PhyAddr + (puStrAddr - tStrInfo.pu8Addr);
                SAMPLE_LOG_TMP("frm size %d\n", u32TmpSize);
            }

            sRet = AX_VDEC_SendStream(VdGrp, &tStrInfoTmp, sMilliSec);
            if (sRet != AX_SUCCESS) {
                if (sRet == AX_ERR_VDEC_FLOW_END) {
                    SAMPLE_LOG("VdGrp=%d, AX_VDEC_SendStream ret AX_ERR_VDEC_FLOW_END, u64SendPicNum:%d\n", VdGrp, u64SendPicNum);
                    break;
                } else if (sRet == AX_ERR_VDEC_QUEUE_FULL) {
                    bReadFrm = AX_FALSE;
                    usleep(1000);
                    continue;
                }

                if (sRet != AX_ERR_VDEC_NOT_SUPPORT) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x %s\n",
                                    VdGrp, sRet, SampleVdecRetStr(sRet));
                    ret = sRet;
                } else {
                    ret = AX_ERR_VDEC_NOT_SUPPORT;
                }

                goto ERR_RET;
            }
        } while (AX_FALSE == tStrInfoTmp.bEndOfFrame);

        bReadFrm = AX_TRUE;
        u64SendPicNum ++;

        if (u64SendPicNum == pstCmd->usrPicIdx) {
            sRet = VdecUserPicEnable(VdGrp, pstFuncArgs->tUsrPicArgs.pstVdecUserPic,
                                     &bContSendStm, pstCtx);
            if (sRet != AX_SUCCESS){
                SAMPLE_CRIT_LOG("VdGrp=%d, VdecUserPicEnable FAILED! ret:0x%x %s",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
                goto ERR_RET;
            }

            if (!bContSendStm) {
                sReadLen = 0;
                sLoopDecNum = 0;
                continue;
            }
        }

        if (u64SendPicNum == pstCmd->sRecvPicNum)
            sLoopDecNum = 0;
    }

    return 0;

ERR_RET:
    return ret;
}

static AX_S32 __VdecCreateUserPool(SAMPLE_VDEC_ARGS_T *pstFuncArgs)
{
    AX_U32 FrameSize = 0;
    AX_U32 uPixBits = 8;
    AX_U32 u32FrameStride = 0;
    AX_VDEC_GRP VdGrp = AX_INVALID_ID;
    AX_VDEC_GRP_ATTR_T *pstVdGrpAttr = NULL;
    AX_POOL_CONFIG_T *pstPoolConfig = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstVdecCtx = NULL;
    AX_S32 s32Ret = AX_SUCCESS;
    AX_S32 sRet = AX_SUCCESS;

    if (pstFuncArgs == NULL) {
        SAMPLE_CRIT_LOG("pstFuncArgs == NULL\n");
        s32Ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    VdGrp = pstFuncArgs->VdGrp;
    pstVdGrpAttr = &pstFuncArgs->tVdGrpAttr;
    pstPoolConfig = &pstFuncArgs->tPoolConfig;
    pstVdecCtx = (SAMPLE_VDEC_CONTEXT_T *)pstFuncArgs->pstCtx;
    u32FrameStride = AX_COMM_ALIGN(pstVdGrpAttr->u32PicWidth * uPixBits, AX_VDEC_WIDTH_ALIGN * 8) / 8;

    FrameSize = AX_VDEC_GetPicBufferSize(u32FrameStride,
                                        pstVdGrpAttr->u32PicHeight,
                                        pstVdGrpAttr->enCodecType);

    pstPoolConfig->MetaSize = 512;
    pstPoolConfig->BlkCnt = pstVdecCtx->tCmdParam.u32FrameBufCnt;

    SAMPLE_LOG("Get FrameSize is 0x%x %d, BlkCnt:%d\n",
                FrameSize, FrameSize, pstPoolConfig->BlkCnt);

    pstPoolConfig->BlkSize = FrameSize;
    pstPoolConfig->CacheMode = AX_POOL_CACHE_MODE_NONCACHE;
    // memset(pstPoolConfig->PartitionName, 0, sizeof(pstPoolConfig->PartitionName));
    snprintf((AX_CHAR *)pstPoolConfig->PartitionName, AX_MAX_PARTITION_NAME_LEN, "anonymous");

    pstPoolConfig = &pstFuncArgs->tPoolConfig;
    pstFuncArgs->PoolId = AX_POOL_CreatePool(pstPoolConfig);
    if (AX_INVALID_POOLID == pstFuncArgs->PoolId) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_POOL_CreatePool FAILED! BlkCnt:%d, BlkSize:0x%llx\n",
                        VdGrp, pstPoolConfig->BlkCnt,
                        pstPoolConfig->BlkSize);
        goto ERR_RET_DESTROY_POOL;
    }

    s32Ret = AX_VDEC_AttachPool(VdGrp, pstFuncArgs->PoolId);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_AttachPool FAILED! PoolId:%d ret:0x%x %s\n",
                        VdGrp, pstFuncArgs->PoolId,
                        s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_DETACH_POOL;
    }

    return s32Ret;

ERR_RET_DETACH_POOL:
    sRet = AX_VDEC_DetachPool(VdGrp);
    if (sRet) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_DetachPool FAILED! ret:0x%x %s",
                        VdGrp, sRet, SampleVdecRetStr(sRet));
    }

ERR_RET_DESTROY_POOL:
    if (pstFuncArgs->PoolId != AX_INVALID_POOLID) {
        sRet = AX_POOL_DestroyPool(pstFuncArgs->PoolId);
        if (sRet) {
            SAMPLE_CRIT_LOG("VdGrp=%d, PoolId:%d, AX_POOL_DestroyPool FAILED! ret:0x%x %s",
                            VdGrp, pstFuncArgs->PoolId, sRet, SampleVdecRetStr(sRet));
        }
    }

ERR_RET:
    return s32Ret;
}

static AX_S32 __VdecGrpCreate(AX_VDEC_GRP VdGrp, AX_VDEC_GRP_ATTR_T *pstVdGrpAttr,
                              SAMPLE_VDEC_CMD_PARAM_T *pstCmd, AX_U32 uStreamBufSize)
{
    AX_S32 s32Ret = AX_SUCCESS;

    pstVdGrpAttr->enCodecType = pstCmd->enDecType;
    pstVdGrpAttr->u32PicWidth = pstCmd->u32PicWidth;  /* pic width */
    pstVdGrpAttr->u32PicHeight = pstCmd->u32PicHeight;  /* pic height */
    pstVdGrpAttr->u32FrameHeight = pstCmd->u32FrameHeight; /* pic height inc padding lines */
    pstVdGrpAttr->u32StreamBufSize = uStreamBufSize;
    pstVdGrpAttr->u32FrameBufCnt = pstCmd->u32FrameBufCnt;
    pstVdGrpAttr->enInputMode = pstCmd->enInputMode;
    pstVdGrpAttr->enLinkMode = AX_UNLINK_MODE;
    pstVdGrpAttr->enOutOrder = pstCmd->enOutOrder;

    if (pstCmd->enFrameBufSrc == AX_POOL_SOURCE_USER) {
        pstVdGrpAttr->enVdecVbSource = AX_POOL_SOURCE_USER;
    } else if (pstCmd->enFrameBufSrc == AX_POOL_SOURCE_PRIVATE) {
        pstVdGrpAttr->enVdecVbSource = AX_POOL_SOURCE_PRIVATE;
    } else if (pstCmd->enFrameBufSrc == AX_POOL_SOURCE_COMMON) {
        pstVdGrpAttr->enVdecVbSource = AX_POOL_SOURCE_COMMON;
    } else {
        SAMPLE_CRIT_LOG("Unsupport enFrameBufSrc:%d\n",
                        pstCmd->enFrameBufSrc);
        goto ERR_RET;
    }

    s32Ret = AX_VDEC_CreateGrp(VdGrp, pstVdGrpAttr);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_CreateGrp FAILED! ret:0x%x %s\n",
                        VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET;
    }

    if (pstCmd->bRepeatTest) {
        for (int i = 0; i < 30 ; i++) {
            s32Ret = AX_VDEC_DestroyGrp(VdGrp);
            if (s32Ret != AX_SUCCESS) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_CreateGrp FAILED! ret:0x%x %s\n",
                        VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
                goto ERR_RET;
            }

            s32Ret = AX_VDEC_CreateGrp(VdGrp, pstVdGrpAttr);
            if (s32Ret != AX_SUCCESS) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_CreateGrp FAILED! ret:0x%x %s\n",
                        VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
                goto ERR_RET;
            }
        }
        SAMPLE_LOG_TMP("------------ repeat test finished -----------\n");
    }

ERR_RET:
    return s32Ret;
}

static AX_S32 __VdecInputModeStream(SAMPLE_VDEC_ARGS_T *pstFuncArgs,
                                   SAMPLE_INPUT_FILE_INFO_T *pstStreamInfo,
                                   SAMPLE_STREAM_BUF_T *pstStreamBuf)
{
    AX_S32 ret = 0;
    AX_S32 sRet = 0;
    AX_VDEC_STREAM_T tStrInfo = {0};
    AX_VDEC_GRP VdGrp = 0;
    AX_S32 sMilliSec = -1;
    AX_S32 sLoopDecNum = 0;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstCtx = NULL;
    AX_VDEC_GRP_STATUS_T stVdecStatus = {0};
    FILE *fInput = NULL;
    off_t inputFileSize = 0;
    AX_U32 uSendCnt = 0;

    if (NULL == pstFuncArgs) {
        SAMPLE_CRIT_LOG("NULL == pstFuncArgs\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    VdGrp = pstFuncArgs->VdGrp;
    if (NULL == pstStreamInfo) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamInfo\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (NULL == pstStreamBuf) {
        SAMPLE_CRIT_LOG("VdGrp=%d, NULL == pstStreamBuf\n", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (pstStreamBuf->tBufAddr.pVirAddr == NULL) {
        SAMPLE_CRIT_LOG("pstStreamBuf->tBufAddr.pVirAddr == NULL\n");
        ret = AX_ERR_VDEC_BAD_ADDR;
        goto ERR_RET;
    }

    pstCtx = pstFuncArgs->pstCtx;
    if (NULL == pstCtx) {
        SAMPLE_CRIT_LOG("pstFuncArgs->pstCtx == NULL\n");
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    pstCmd = &pstCtx->tCmdParam;
    if (pstCmd == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, pstCmd == NULL", VdGrp);
        ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    fInput = pstStreamInfo->fInput;
    rewind(fInput);

    /* sMilliSec must >= 0 in stream mode */
    sMilliSec = pstCmd->sMilliSec;
    if (sMilliSec == -1)
        sMilliSec = 100;

    inputFileSize = pstStreamInfo->sFileSize;
    AX_U32 uLeftSize = inputFileSize;
    AX_U32 uReadPackSize = pstCmd->sStreamSize;
    sLoopDecNum = pstCmd->sLoopDecNum;

    while (1) {
        uReadPackSize = ((uLeftSize < pstCmd->sStreamSize) ? uLeftSize : pstCmd->sStreamSize);
        size_t fread_sz = fread(pstStreamBuf->tBufAddr.pVirAddr, 1, uReadPackSize, fInput);
        uLeftSize = inputFileSize - uReadPackSize;
        tStrInfo.pu8Addr = pstStreamBuf->tBufAddr.pVirAddr;
        tStrInfo.u64PhyAddr = 0;
        tStrInfo.u32StreamPackLen = uReadPackSize;
        tStrInfo.bEndOfStream = AX_FALSE;

        if (fread_sz != uReadPackSize) {
            SAMPLE_LOG_TMP("VdGrp=%d, fread_sz %d uReadPackSize %d\n", VdGrp, (int)fread_sz, uReadPackSize);
        }

        if ((pstCtx->Timebegin.tv_sec == 0) && (pstCtx->Timebegin.tv_usec == 0)) {
            gettimeofday(&pstCtx->Timebegin, NULL);
        }

        SAMPLE_LOG("VdGrp=%d, pts:%lld inputFileSize:0x%lx fread_sz:0x%lx\n",
                    VdGrp, tStrInfo.u64PTS, inputFileSize, fread_sz);
        sRet = AX_VDEC_SendStream(VdGrp, &tStrInfo, sMilliSec); /* stream mod should not set wait time to -1 */
        if (sRet != AX_SUCCESS) {
            if (sRet == AX_ERR_VDEC_FLOW_END) {
                SAMPLE_LOG("VdGrp=%d, AX_VDEC_SendStream ret AX_ERR_VDEC_FLOW_END\n", VdGrp);
                break;
            } else if (sRet == AX_ERR_VDEC_QUEUE_FULL) {
                usleep(1000);
                continue;
            }

            if (sRet != AX_ERR_VDEC_NOT_SUPPORT) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SendStream FAILED! ret:0x%x %s\n",
                            VdGrp, sRet, SampleVdecRetStr(sRet));
                ret = sRet;
            } else {
                ret = AX_ERR_VDEC_NOT_SUPPORT;
            }

            goto ERR_RET;
        }

        uSendCnt++;

        if (pstCmd->bResetGrp && (uSendCnt == 10)) {
            ret = AX_VDEC_StopRecvStream(VdGrp);
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_StopRecvStream success \n", VdGrp);
            else
                SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_StopRecvStream FAILED! ret:0x%x", VdGrp, ret);

            /* wait release frm */
            sleep(1);

            ret = AX_VDEC_ResetGrp(VdGrp);
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_ResetGrp success \n", VdGrp);
            else
                SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_ResetGrp FAILED! ret:0x%x", VdGrp, ret);

            AX_VDEC_RECV_PIC_PARAM_T tRecvParam = {0};
            ret = AX_VDEC_StartRecvStream(VdGrp, &tRecvParam);
            if (AX_SUCCESS == ret)
                SAMPLE_LOG_TMP("================= VdGrp=%d, AX_VDEC_StartRecvStream success \n", VdGrp);
            else
                SAMPLE_CRIT_LOG("VdGrp=%d,  AX_VDEC_StartRecvStream FAILED! ret:0x%x", VdGrp, ret);
        }

        inputFileSize -= fread_sz;
        if (inputFileSize == 0) {
            sLoopDecNum--;
            SAMPLE_LOG_TMP("VdGrp=%d, file read finish, loop %d\n", VdGrp, sLoopDecNum);
            if (sLoopDecNum <= 0) {
                sRet = __VdecSendEndOfStream(VdGrp);
                if (sRet != AX_SUCCESS) {
                    SAMPLE_CRIT_LOG("VdGrp=%d, __VdecSendEndOfStream FAILED! ret:0x%x %s\n",
                            VdGrp, sRet, SampleVdecRetStr(sRet));
                    ret = AX_ERR_VDEC_RUN_ERROR;
                    goto ERR_RET;
                }
                break;
            } else {
                fseek(pstStreamInfo->fInput, 0, SEEK_SET);
                uLeftSize = inputFileSize = pstStreamInfo->sFileSize;
            }
        }

        if (s_ThreadExit) {
            SAMPLE_LOG_TMP("VdGrp=%d, thread exit:%d, so break while(1) stream mode", VdGrp, s_ThreadExit);
            break;
        }

retry:
        sRet = AX_VDEC_QueryStatus(VdGrp, &stVdecStatus);
        if (sRet == AX_SUCCESS) {
            if (stVdecStatus.bInputFifoIsFull || stVdecStatus.u32LeftStreamFrames > 1) {
                SAMPLE_LOG("fifo is full %d u32LeftStreamFrames %d\n",
                    stVdecStatus.bInputFifoIsFull, stVdecStatus.u32LeftStreamFrames);
                usleep(10000);
                goto retry;
            }

            if (stVdecStatus.u32LeftStreamBytes + uReadPackSize * 3 >= pstFuncArgs->tVdGrpAttr.u32StreamBufSize) {
                SAMPLE_LOG_TMP("buf full:remain data %d data size %d buf size %d\n",
                    stVdecStatus.u32LeftStreamBytes, uReadPackSize, pstFuncArgs->tVdGrpAttr.u32StreamBufSize);
            }
        }
    }

    SAMPLE_LOG_TMP("VdGrp=%d, AX_VDEC_SendStream done! \n", VdGrp);

    return 0;

ERR_RET:
    return ret;
}

static AX_S32 __VdecGrpSendStream(SAMPLE_VDEC_ARGS_T *pstFuncArgs, SAMPLE_STREAM_BUF_T *pstStreamBuf)
{
    AX_S32 sRet = AX_SUCCESS;

    AX_VDEC_RECV_PIC_PARAM_T tRecvParam;
    AX_VDEC_GRP VdGrp = pstFuncArgs->VdGrp;
    SAMPLE_INPUT_FILE_INFO_T tStreamInfo = {0};
    SAMPLE_VDEC_CONTEXT_T *pstVdecCtx;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd;

    pstVdecCtx = pstFuncArgs->pstCtx;
    pstCmd = &pstVdecCtx->tCmdParam;


    sRet = AX_VDEC_SetDisplayMode(VdGrp, pstCmd->enDisplayMode);
    if (sRet != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_SetDisplayMode failed! ret:0x%x %s\n", sRet, SampleVdecRetStr(sRet));
        goto ERR_RET;
    }

    if (!s_ThreadExit) {
        memset(&tRecvParam, 0, sizeof(tRecvParam));
        tRecvParam.s32RecvPicNum = pstCmd->sRecvPicNum;
        sRet = AX_VDEC_StartRecvStream(VdGrp, &tRecvParam);
        if (sRet != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_StartRecvStream FAILED! ret:0x%x %s\n",
                            VdGrp, sRet, SampleVdecRetStr(sRet));
            goto ERR_RET;
        } else {
            pstVdecCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_START_RECV;
        }

        SAMPLE_LOG("VdGrp=%d, pstCmd->enInputMode:%d \n", VdGrp, pstCmd->enInputMode);
        if (s_ThreadExit) {
            SAMPLE_LOG_TMP("VdGrp=%d, thread exit:%d, so goto exit\n", VdGrp, s_ThreadExit);
            sRet = __VdecSendEndOfStream(VdGrp);
            if (sRet != AX_SUCCESS) {
                SAMPLE_CRIT_LOG("VdGrp=%d, __VdecSendEndOfStream FAILED! ret:0x%x %s\n",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
                goto ERR_RET_STOP_RECV;
            }
        } else {
            if ((AX_VDEC_INPUT_MODE_FRAME == pstCmd->enInputMode)) {
                tStreamInfo.fInput = pstVdecCtx->pInputFd[VdGrp];
                tStreamInfo.sFileSize = pstVdecCtx->oInputFileSize[VdGrp];

                sRet = __VdecInputModeFrame(pstFuncArgs, &tStreamInfo, pstStreamBuf);
                if (sRet) {
                    goto ERR_RET_STOP_RECV;
                }
            } else if (AX_VDEC_INPUT_MODE_STREAM == pstCmd->enInputMode) {
                tStreamInfo.fInput = pstVdecCtx->pInputFd[VdGrp];
                tStreamInfo.sFileSize = pstVdecCtx->oInputFileSize[VdGrp];
                fseek(tStreamInfo.fInput, 0, SEEK_SET);

                sRet = __VdecInputModeStream(pstFuncArgs, &tStreamInfo, pstStreamBuf);
                if (sRet) {
                    goto ERR_RET_STOP_RECV;
                }
            } else if ((AX_VDEC_INPUT_MODE_SLICE == pstCmd->enInputMode)
                    || (AX_VDEC_INPUT_MODE_NAL == pstCmd->enInputMode)) {
                tStreamInfo.fInput = pstVdecCtx->pInputFd[VdGrp];
                tStreamInfo.sFileSize = pstVdecCtx->oInputFileSize[VdGrp];
                fseek(tStreamInfo.fInput, 0, SEEK_SET);

                sRet = __VdecInputModeSlice(pstFuncArgs, &tStreamInfo, pstStreamBuf);
                if (sRet) {
                    goto ERR_RET_STOP_RECV;
                }
            } else if (AX_VDEC_INPUT_MODE_COMPAT == pstCmd->enInputMode) {
                tStreamInfo.fInput = pstVdecCtx->pInputFd[VdGrp];
                tStreamInfo.sFileSize = pstVdecCtx->oInputFileSize[VdGrp];
                fseek(tStreamInfo.fInput, 0, SEEK_SET);

                sRet = __VdecInputModeCompact(pstFuncArgs, &tStreamInfo, pstStreamBuf);
                if (sRet) {
                    goto ERR_RET_STOP_RECV;
                }
            }
        }

        SAMPLE_LOG_TMP("VdGrp=%d, send stream finish!\n", VdGrp);

        if (s_ThreadExit) {
            SAMPLE_LOG_TMP("VdGrp=%d, thread exit:%d, so goto exit\n", VdGrp, s_ThreadExit);
        }
    }

    return sRet;

ERR_RET_STOP_RECV:
    if ((sRet != AX_ERR_VDEC_NOT_SUPPORT) && (sRet != AX_ERR_VDEC_FLOW_END)) {
        SAMPLE_CRIT_LOG("VdGrp=%d, VdecInputModeFrame FAILED! ret:0x%x\n", VdGrp, sRet);
    }

    if (pstVdecCtx->GrpStatus[VdGrp] == AX_VDEC_GRP_START_RECV) {
        sRet = __VdecSendEndOfStream(VdGrp);
        if (sRet != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("VdGrp=%d, __VdecSendEndOfStream FAILED! ret:0x%x %s\n",
                                VdGrp, sRet, SampleVdecRetStr(sRet));
        }
    }

ERR_RET:
    return sRet;
}

static AX_S32 __VdecInitUsrPicArgs(SAMPLE_VDEC_ARGS_T *pstFuncArgs, SAMPLE_VDEC_USERPIC_T *pstVdecUserPic)
{
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstVdecCtx = NULL;
    SAMPLE_VDEC_USRPIC_ARGS_T *pstUsrPicArgs = NULL;
    AX_VDEC_GRP VdGrp = 0;
    AX_S32 sRet = AX_SUCCESS;

    if (pstFuncArgs == NULL) {
        sRet = AX_ERR_VDEC_NULL_PTR;
        SAMPLE_CRIT_LOG("pstFuncArgs == NULL\n");
        goto ERR_RET;
    }
    VdGrp = pstFuncArgs->VdGrp;
    if (pstVdecUserPic == NULL) {
        sRet = AX_ERR_VDEC_NULL_PTR;
        SAMPLE_CRIT_LOG("pstVdecUserPic == NULL\n");
        goto ERR_RET;
    }

    pstVdecCtx = pstFuncArgs->pstCtx;
    if (NULL == pstVdecCtx) {
        sRet = AX_ERR_VDEC_NULL_PTR;
        SAMPLE_CRIT_LOG("VdGrp=%d, pstFuncArgs->pstCtx == NULL\n", VdGrp);
        goto ERR_RET;
    }

    pstCmd = &pstVdecCtx->tCmdParam;
    pstVdecUserPic->recvStmAfUsrPic = pstCmd->recvStmAfUsrPic;
    pstVdecUserPic->s32RecvPicNumBak = pstCmd->sRecvPicNum;
    pstUsrPicArgs = &pstFuncArgs->tUsrPicArgs;
    pstUsrPicArgs->VdGrp = VdGrp;
    pstUsrPicArgs->bUsrInstant = pstCmd->bUsrInstant;
    pstUsrPicArgs->enDecType = pstCmd->enDecType;
    pstUsrPicArgs->pstVdecUserPic = pstVdecUserPic;
    pstUsrPicArgs->tPicParam.bUserPicEnable = pstCmd->bUserPicEnable;
    pstUsrPicArgs->tPicParam.enImgFormat = AX_FORMAT_YUV420_SEMIPLANAR;
    pstUsrPicArgs->tPicParam.pUsrPicFilePath = pstCmd->pUsrPicFilePath;
    pstUsrPicArgs->tPicParam.u32PicWidth = pstCmd->u32PicWidth;
    pstUsrPicArgs->tPicParam.u32PicHeight = pstCmd->u32PicHeight;

ERR_RET:
    return sRet;
}

static void *_VdecGroupThreadMain(void *arg)
{
    SAMPLE_VDEC_ARGS_T *pstFuncArgs = (SAMPLE_VDEC_ARGS_T *)arg;
    AX_S32 sRet = 0;
    AX_S32 s32Ret = 0;
    int res = 0;

    AX_VDEC_GRP VdGrp = 0;
    AX_CHAR *sFile = NULL;
    FILE *fInput = NULL;

    off_t inputFileSize = 0;
    size_t read_size = 0;

    AX_U8 *pstStreamMem = NULL;
    AX_VDEC_GRP_ATTR_T *pstVdGrpAttr = NULL;
    SAMPLE_STREAM_BUF_T tStreamBuf = {0};

    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstVdecCtx = NULL;
    AX_S32 ErrorCode = 0;
    AX_BOOL bCreateUserPool = AX_FALSE;
    AX_U32 uBufSize = 0;
    AX_U32 uWaitCnt = 0;

    if (pstFuncArgs == NULL) {
        SAMPLE_CRIT_LOG("pstFuncArgs == NULL\n");
        return NULL;
    }

    SampelVdecSetThreadName("smp_dec_send_%d", pstFuncArgs->VdGrp);

    VdGrp = pstFuncArgs->VdGrp;
    SAMPLE_LOG("VdGrp=%d begin\n", VdGrp);

    pstVdecCtx = pstFuncArgs->pstCtx;
    if (NULL == pstVdecCtx) {
        SAMPLE_CRIT_LOG("VdGrp=%d, pstFuncArgs->pstCtx == NULL\n", VdGrp);
        return NULL;
    }

    pstVdecCtx->GrpPID[VdGrp] = gettid();

    pstCmd = &pstVdecCtx->tCmdParam;

    sFile = pstCmd->pInputFilePath;
    if (sFile == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, Please input pInputFilePath\n", VdGrp);
        return NULL;
    }

    fInput = fopen(sFile, "rb");
    if (fInput == NULL) {
        SAMPLE_CRIT_LOG("VdGrp=%d, Unable to open input file:%s\n", VdGrp, sFile);
        return NULL;
    }

    res = fseek(fInput, 0L, SEEK_END);
    if (res) {
        SAMPLE_CRIT_LOG("VdGrp=%d, fseek FAILED! ret:%d\n", VdGrp, res);
        goto ERR_RET_FCLOSE;
    }

    inputFileSize = ftello(fInput);
    rewind(fInput);
    if (inputFileSize == -1) {
        SAMPLE_LOG_TMP("note:---------------file size err!!!!!!--------------\n");
    }

    pstVdecCtx->pInputFd[VdGrp] = fInput;
    pstVdecCtx->oInputFileSize[VdGrp] = inputFileSize;
    pstVdecCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_UNEXIST;

    if (pstCmd->bDynRes) {
        sFile = pstCmd->pNewInputFilePath;
        if (sFile == NULL) {
            SAMPLE_CRIT_LOG("VdGrp=%d, Please input pInputFilePath\n", VdGrp);
            return NULL;
        }

        fInput = fopen(sFile, "rb");
        if (fInput == NULL) {
            SAMPLE_CRIT_LOG("VdGrp=%d, Unable to open input file:%s\n", VdGrp, sFile);
            return NULL;
        }

        res = fseek(fInput, 0L, SEEK_END);
        if (res) {
            SAMPLE_CRIT_LOG("VdGrp=%d, fseek FAILED! ret:%d\n", VdGrp, res);
            goto ERR_RET_FCLOSE;
        }

        inputFileSize = ftello(fInput);
        rewind(fInput);
        if (inputFileSize == -1) {
            SAMPLE_LOG_TMP("note:---------------file size err!!!!!!--------------\n");
        }

        pstVdecCtx->pNewInputFd[VdGrp] = fInput;
        pstVdecCtx->oNewInputFileSize[VdGrp] = inputFileSize;
    }


    inputFileSize = pstVdecCtx->oInputFileSize[VdGrp] > pstVdecCtx->oNewInputFileSize[VdGrp] ? \
                    pstVdecCtx->oInputFileSize[VdGrp] : pstVdecCtx->oNewInputFileSize[VdGrp];
    SAMPLE_LOG_TMP("bDynRes:%d file:%s - %s, pInputFd:%p - %p, FileSize: %lld :%lld - %lld",
               pstCmd->bDynRes, pstCmd->pInputFilePath, pstCmd->pNewInputFilePath,
               pstVdecCtx->pInputFd[VdGrp], pstVdecCtx->pNewInputFd[VdGrp], (AX_U64)inputFileSize,
               (AX_U64)pstVdecCtx->oInputFileSize[VdGrp], (AX_U64)pstVdecCtx->oNewInputFileSize[VdGrp]);

#ifdef AX_VDEC_FFMPEG_ENABLE
    SAMPLE_BITSTREAM_INFO_T *pstBitStreamInfo = &pstVdecCtx->stBitStreamInfo[VdGrp];

    if (pstCmd->bFfmpegEnable) {
        if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
            pstBitStreamInfo->VdGrp = VdGrp;
            s32Ret = SampleVdecFfmpegInit(&pstVdecCtx->stFfmpeg[VdGrp], pstCmd->pInputFilePath, pstBitStreamInfo);
            if (s32Ret != AX_SUCCESS) {
                SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegInit FAILED! ret:0x%x\n",
                            VdGrp, s32Ret);
                goto ERR_RET_FCLOSE;
            }
        }
    }

    SAMPLE_LOG_TMP("pstCmd->bFfmpegEnable %d\n", pstCmd->bFfmpegEnable);
#endif

    if (pstCmd->highRes) {
        tStreamBuf.uBufSize = STREAM_BUFFER_MAX_SIZE_HIGH_RES;
    } else {
        if (pstCmd->enDecType == PT_JPEG) {
            uBufSize = inputFileSize > STREAM_BUFFER_MIN_SIZE ? inputFileSize : STREAM_BUFFER_MIN_SIZE;
            tStreamBuf.uBufSize = uBufSize > STREAM_BUFFER_MAX_SIZE ? STREAM_BUFFER_MAX_SIZE : uBufSize;
        } else {
            tStreamBuf.uBufSize = inputFileSize > STREAM_BUFFER_MAX_SIZE ? STREAM_BUFFER_MAX_SIZE : inputFileSize;
        }
    }

    SAMPLE_LOG_TMP("pstCmd->enDecType %d tStreamBuf.uBufSize %d\n", pstCmd->enDecType, tStreamBuf.uBufSize );

    s32Ret = AX_SYS_MemAlloc(&tStreamBuf.tBufAddr.u64PhyAddr, (AX_VOID **)&tStreamBuf.tBufAddr.pVirAddr,
                             tStreamBuf.uBufSize, 0x100, (AX_S8 *)"vdec_input_stream");
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemAlloc FAILED! uBufSize:0x%x ret:0x%x\n",
                         VdGrp, tStreamBuf.uBufSize, s32Ret);
        goto ERR_RET_MEMFREE;
    } else {
        if ((tStreamBuf.tBufAddr.pVirAddr == NULL) || (tStreamBuf.tBufAddr.u64PhyAddr == 0)) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemAlloc FAILED! uBufSize:%d",
                            VdGrp, tStreamBuf.uBufSize);
            goto ERR_RET_MEMFREE;
        }
    }

    SAMPLE_LOG_TMP("VdGrp=%d, AX_SYS_MemAlloc uBufSize:0x%x tBufAddr.pVirAddr:%p, .tBufAddr.u64PhyAddr:0x%llx\n",
               VdGrp, tStreamBuf.uBufSize, tStreamBuf.tBufAddr.pVirAddr, tStreamBuf.tBufAddr.u64PhyAddr);

    tStreamBuf.pBufBeforeFill = tStreamBuf.tBufAddr.pVirAddr;
    tStreamBuf.pBufAfterFill = tStreamBuf.tBufAddr.pVirAddr;
    tStreamBuf.bRingbuf = AX_FALSE;

    pstStreamMem = (AX_U8 *)tStreamBuf.tBufAddr.pVirAddr;

    if (pstCmd->enDecType == PT_H264) {
        AX_VDEC_STREAM_T vdecStream = {0};
        AX_VDEC_BITSTREAM_INFO_T sps_data;
        AX_U32 parse_len = ((AX_U32)pstVdecCtx->oInputFileSize[VdGrp]) >= SEEK_NALU_MAX_LEN ? SEEK_NALU_MAX_LEN : pstVdecCtx->oInputFileSize[VdGrp];
        memset(&sps_data, 0, sizeof(SAMPLE_H264_SPS_DATA_T));

        read_size = fread(pstStreamMem, sizeof(AX_U8), (size_t)parse_len, fInput);
        if (read_size != parse_len) {
            SAMPLE_CRIT_LOG("fread FAILED! read_size:0x%x != parse_len:0x%x\n",
                            (AX_U32)read_size, parse_len);
            goto ERR_RET_MEMFREE;
        }
        rewind(fInput);

        vdecStream.pu8Addr = pstStreamMem;
        vdecStream.u32StreamPackLen = parse_len;

        sRet = AX_VDEC_ExtractStreamHeaderInfo(&vdecStream, PT_H264, &sps_data);
        SAMPLE_LOG_TMP("h264_parse_sps sRet:0x%x sps_data.height:%d, sps_data.width:%d u32RefFramesNum:%d u32BitDepthY %d\n",
                   sRet, sps_data.u32Height, sps_data.u32Width, sps_data.u32RefFramesNum, sps_data.u32BitDepthY);
    }

    pstVdGrpAttr = &pstFuncArgs->tVdGrpAttr;

    if (pstCmd->bQuitWait == AX_TRUE) {
        pstVdecCtx->bGrpQuitWait[VdGrp] = AX_TRUE;
    }

    sRet = __VdecGrpCreate(VdGrp, pstVdGrpAttr, pstCmd, tStreamBuf.uBufSize);
    if (sRet != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, __VdecGrpCreate FAILED! ret:0x%x\n",
                        VdGrp, sRet);
        s_ThreadExit++;
        goto ERR_RET_MEMFREE;
    }

    pstVdecCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_CREATED;
    SAMPLE_LOG("VdGrp=%d, AX_VDEC_CreateGrp done!", VdGrp);

    if (pstVdGrpAttr->enVdecVbSource == AX_POOL_SOURCE_USER) {
        sRet = __VdecCreateUserPool(pstFuncArgs);
        if (sRet != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("VdGrp=%d, __VdecCreateUserPool FAILED! ret:0x%x\n",
                            VdGrp, sRet);
            goto ERR_RET_DETACH_POOL;
        }
        bCreateUserPool = AX_TRUE;
    }

    AX_VDEC_GRP_PARAM_T stGrpParam;
    memset(&stGrpParam, 0, sizeof(stGrpParam));
    stGrpParam.enVdecMode = pstCmd->enVideoMode;
    sRet = AX_VDEC_SetGrpParam(VdGrp, &stGrpParam);
    if (0 != sRet) {
        SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_SetGrpParam fail, ret = 0x%x", VdGrp, sRet);
        /* goto ERR_RET_DETACH_POOL; */ /* not support */
    }

    sRet = __VdecInitUsrPicArgs(pstFuncArgs, &pstVdecCtx->stVdecUserPic);
    if (sRet != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, __VdecInitUsrPicArgs failed. ret:0x%x %s\n",
                         VdGrp, sRet, SampleVdecRetStr(sRet));
        goto ERR_RET_DETACH_POOL;
    }

    sRet = __VdecUsrPicCreat(&pstFuncArgs->tUsrPicArgs, &pstVdecCtx->stVdecUserPic);
    if (sRet != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("VdGrp=%d, __VdecUsrPicCreat failed. ret:0x%x %s\n",
                         VdGrp, sRet, SampleVdecRetStr(sRet));
        goto ERR_RET_DETACH_POOL;
    }

    s_groupSuccess = AX_TRUE;

    sRet = __VdecGrpSendStream(pstFuncArgs, &tStreamBuf);
    if (sRet != AX_SUCCESS) {
        goto ERR_RET_DISABLE_USER_PIC;
    }

    SAMPLE_LOG_TMP("VdGrp=%d, bQuitWait:%d, thread exit:%d, bRecvFlowEnd:%d bGrpQuitWait:%d\n",
               VdGrp, pstCmd->bQuitWait, s_ThreadExit,
               pstVdecCtx->bRecvFlowEnd[VdGrp], pstVdecCtx->bGrpQuitWait[VdGrp]);

    if (pstCmd->bQuitWait == AX_TRUE) {
        SAMPLE_LOG_TMP("VdecGrpSendStream Finished! Now waiting RecvFlowEnd");
    }

    while (1) {
        if (s_ThreadExit) {
            SAMPLE_LOG_TMP("VdGrp=%d, thread exit:%d, break while(1)!", VdGrp, s_ThreadExit);
            break;
        }

        sleep(2);

        if ((AX_TRUE == pstVdecCtx->bRecvFlowEnd[VdGrp]) && (AX_FALSE == pstVdecCtx->bGrpQuitWait[VdGrp])) {
            SAMPLE_LOG_TMP("VdGrp=%d, bRecvFlowEnd break while(1)! \n", VdGrp);
            break;
        }
        SAMPLE_LOG_TMP("VdGrp=%d, bRecvFlowEnd:%d bGrpQuitWait:%d, thread exit:%d\n",
                    VdGrp, pstVdecCtx->bRecvFlowEnd[VdGrp], pstVdecCtx->bGrpQuitWait[VdGrp], s_ThreadExit);
    }

    if (pstVdGrpAttr->enVdecVbSource == AX_POOL_SOURCE_USER) {
        sRet = AX_VDEC_DetachPool(VdGrp);
        if (sRet) {
            SAMPLE_CRIT_LOG("VdGrp=%d, PoolId:%d, AX_VDEC_DetachPool FAILED! ret:0x%x %s",
                            VdGrp, pstFuncArgs->PoolId, sRet, SampleVdecRetStr(sRet));
        }
    }

    if (pstVdecCtx->GrpStatus[VdGrp] == AX_VDEC_GRP_START_RECV) {
        while ((pstVdecCtx->bRecvFlowEnd[VdGrp] != AX_TRUE) && (uWaitCnt < 100)) {
            usleep(50000);
            uWaitCnt++;
        }
        SAMPLE_LOG_TMP("wait stop recv strm %d\n", uWaitCnt);

        sRet = AX_VDEC_StopRecvStream(VdGrp);
        if (sRet) {
            SAMPLE_CRIT_LOG("AX_VDEC_StopRecvStream ret:0x%x %s\n", sRet, SampleVdecRetStr(sRet));
            ErrorCode |= sRet;
        }
    }

    SAMPLE_LOG("VdGrp=%d, thread exit:%d AX_VDEC_DestroyGrp enter ++++", VdGrp, s_ThreadExit);

    while (1) {
        sRet = AX_VDEC_DestroyGrp(VdGrp);
        if (sRet == AX_ERR_VDEC_BUSY) {
            SAMPLE_ERR_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                           VdGrp, sRet, SampleVdecRetStr(sRet));
            usleep(100000);
            continue;
        }

        if (sRet == AX_SUCCESS) {
            pstVdecCtx->GrpStatus[VdGrp] = AX_VDEC_GRP_DESTROYED;
            SAMPLE_LOG_TMP("grp %d AX_VDEC_DestroyGrp ok\n", VdGrp);
        } else {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! stat %d ret:0x%x %s",
                            VdGrp, pstVdecCtx->GrpStatus[VdGrp], sRet, SampleVdecRetStr(sRet));
            ErrorCode |= sRet;
        }

        break;
    }

    SAMPLE_LOG("VdGrp=%d, AX_VDEC_DestroyGrp exit ---- ret:0x%x", VdGrp, sRet);

    if (pstVdGrpAttr->enVdecVbSource == AX_POOL_SOURCE_USER) {
        if (pstFuncArgs->PoolId != AX_INVALID_POOLID) {
            sRet = AX_POOL_DestroyPool(pstFuncArgs->PoolId);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, PoolId:%d, AX_POOL_DestroyPool FAILED! ret:0x%x %s",
                                VdGrp, pstFuncArgs->PoolId, sRet, SampleVdecRetStr(sRet));
            }
        }
    }

#ifdef AX_VDEC_FFMPEG_ENABLE
    if (pstCmd->bFfmpegEnable) {
        if ((pstCmd->enInputMode != AX_VDEC_INPUT_MODE_STREAM)
                && (pstCmd->enDecType == PT_H264)) {
            s32Ret = SampleVdecFfmpegDeinit(&pstVdecCtx->stFfmpeg[VdGrp], pstBitStreamInfo->VdGrp);
            if (s32Ret != AX_SUCCESS) {
                SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegDeinit FAILED! ret:0x%x\n",
                            VdGrp, s32Ret);
                goto ERR_RET_FCLOSE;
            }
        }
    }
#endif

    if (pstStreamMem) {
        if (tStreamBuf.tBufAddr.u64PhyAddr != 0) {
            sRet = AX_SYS_MemFree(tStreamBuf.tBufAddr.u64PhyAddr, tStreamBuf.tBufAddr.pVirAddr);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemFree FAILED! ret:0x%x", VdGrp, sRet);
                ErrorCode |= sRet;
            }
        } else {
            free(tStreamBuf.tBufAddr.pVirAddr);
        }
    }

    if (fInput) {
        fclose(fInput);
        fInput = NULL;
    }

    return NULL;


ERR_RET_DISABLE_USER_PIC:
    VdecUserPicDestroy(VdGrp, pstFuncArgs->tUsrPicArgs.pstVdecUserPic);

    if (pstCmd->bFfmpegEnable) {
#ifdef AX_VDEC_FFMPEG_ENABLE
        if ((pstCmd->enInputMode !=AX_VDEC_INPUT_MODE_STREAM)
                && ((pstCmd->enDecType == PT_H264) || (pstCmd->enDecType == PT_H265))) {
            s32Ret = SampleVdecFfmpegDeinit(&pstVdecCtx->stFfmpeg[VdGrp], pstBitStreamInfo->VdGrp);
            if (s32Ret != AX_SUCCESS) {
                SAMPLE_CRIT_LOG("VdGrp=%d, SampleVdecFfmpegDeinit FAILED! ret:0x%x\n",
                            VdGrp, s32Ret);
            }
        }
#endif
    }

ERR_RET_DETACH_POOL:
    if (pstVdGrpAttr->enVdecVbSource == AX_POOL_SOURCE_USER) {
        sRet = AX_VDEC_DetachPool(VdGrp);
        if (sRet) {
            SAMPLE_CRIT_LOG("VdGrp=%d, PoolId:%d, AX_VDEC_DetachPool FAILED! ret:0x%x %s",
                            VdGrp, pstFuncArgs->PoolId, sRet, SampleVdecRetStr(sRet));
        }
    }

    while (1) {
        s32Ret = AX_VDEC_DestroyGrp(VdGrp);
        if (s32Ret == AX_ERR_VDEC_BUSY) {
            SAMPLE_ERR_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                           VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
            usleep(10000);
            continue;
        }

        if (s32Ret != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("VdGrp=%d, AX_VDEC_DestroyGrp FAILED! ret:0x%x %s",
                            VdGrp, s32Ret, SampleVdecRetStr(s32Ret));
            ErrorCode |= sRet;
        }

        break;
    }

    if ((bCreateUserPool) && pstVdGrpAttr->enVdecVbSource == AX_POOL_SOURCE_USER) {
        if (pstFuncArgs->PoolId != AX_INVALID_POOLID) {
            sRet = AX_POOL_DestroyPool(pstFuncArgs->PoolId);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, PoolId:%d, AX_POOL_DestroyPool FAILED! ret:0x%x %s",
                                VdGrp, pstFuncArgs->PoolId, sRet, SampleVdecRetStr(sRet));
            }
        }
    }

ERR_RET_MEMFREE:
    if (pstStreamMem) {
        if (tStreamBuf.tBufAddr.u64PhyAddr != 0) {
            sRet = AX_SYS_MemFree(tStreamBuf.tBufAddr.u64PhyAddr, tStreamBuf.tBufAddr.pVirAddr);
            if (sRet) {
                SAMPLE_CRIT_LOG("VdGrp=%d, AX_SYS_MemFree FAILED! ret:0x%x", VdGrp, sRet);
            }
        } else {
            free(tStreamBuf.tBufAddr.pVirAddr);
            tStreamBuf.tBufAddr.pVirAddr = NULL;
        }
    }

ERR_RET_FCLOSE:
    if (fInput) {
        fclose(fInput);
        fInput = NULL;
    }

    pthread_exit(NULL);

    return NULL;
}

static int _VdecRecvProcess(SAMPLE_VDEC_CONTEXT_T *pstVdecCtx)
{
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    AX_S32 s32Ret = 0;
    int gi;
    AX_VDEC_GRP VdGrp = 0;
    SAMPLE_VDEC_ARGS_T *pstFuncArgs = NULL;

    if (pstVdecCtx == NULL) {
        SAMPLE_CRIT_LOG("pstSampleCtx == NULL\n");
        return -1;
    }

    pstCmd = &pstVdecCtx->tCmdParam;

    if (pstCmd->bSelectMode == AX_FALSE) {
        for (gi = pstCmd->uStartGrpId; gi < pstCmd->uStartGrpId + pstCmd->uGrpCount; gi++) {
            VdGrp = gi;
            pstFuncArgs = &pstVdecCtx->stVdecGrpArgs[VdGrp];
            /* create thread for get chn frame */
            if (pthread_create(&pstVdecCtx->GrpChnRecvTid[VdGrp],
                                NULL, __VdecGrpChnRecvThread, pstFuncArgs) != 0) {
                SAMPLE_CRIT_LOG("VdGrp=%d, pthread_create __VdecGrpChnRecvThread FAILED!\n",
                                VdGrp);
                goto ERR_RET;
            }

            SAMPLE_LOG_N("VdGrp=%d, pthread_create __VdecGrpChnRecvThread done! pthread_id:0x%lx!\n",
                        VdGrp, pstVdecCtx->GrpChnRecvTid[VdGrp]);
        }
    } else {
        if (pthread_create(&pstVdecCtx->RecvTid, NULL, _VdecRecvThread, pstVdecCtx) != 0) {
            SAMPLE_CRIT_LOG("pthread_create _VdecRecvThread FAILED!\n");
            s32Ret = AX_ERR_VDEC_RUN_ERROR;
            goto ERR_RET;
        }
    }

    return s32Ret;

ERR_RET:
    return s32Ret;
}

static int _VdecTestMain(SAMPLE_VDEC_CONTEXT_T *pstVdecCtx)
{
    int i;
    int ret = 0;
    AX_S32 s32Ret = 0;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_ARGS_T *pstFuncArgs = NULL;
    AX_VDEC_GRP VdGrp = 0;

    if (pstVdecCtx == NULL) {
        SAMPLE_CRIT_LOG("pstSampleCtx == NULL\n");
        return -1;
    }

    pstCmd = &pstVdecCtx->tCmdParam;

    s32Ret = _VdecRecvProcess(pstVdecCtx);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_SUCCESS FAILED! ret:0x%x\n", s32Ret);
        goto ERR_RET;
    }

    for (i = pstCmd->uStartGrpId; i < pstCmd->uStartGrpId + pstCmd->uGrpCount; i++) {
        pstFuncArgs = &pstVdecCtx->stVdecGrpArgs[i];
        ret = pthread_create(&pstVdecCtx->GrpTid[i], NULL, _VdecGroupThreadMain,
                             (void *)pstFuncArgs);
        if (ret) {
            SAMPLE_CRIT_LOG("VdGrp=%d, pthread_create _VdecGroupThreadMain FAILED! ret:%d, %s, \n",
                            i, ret, strerror(ret));
            s32Ret = AX_ERR_VDEC_RUN_ERROR;
            goto ERR_RET_CANCEL_PTHREAD_RECV;
        }
        SAMPLE_LOG("VdGrp=%d, pthread_create _VdecGroupThread done! pthread_id:0x%lx \n",
                   i, pstVdecCtx->GrpTid[i]);
    }

    /* wait all thread finish */
    for (i = pstCmd->uStartGrpId; i < pstCmd->uStartGrpId + pstCmd->uGrpCount; i++) {
        SAMPLE_LOG("VdGrp=%d, before pthread_join _VdecGroupThread pthread_id:0x%lx, PID:%d\n",
                   i, pstVdecCtx->GrpTid[i], pstVdecCtx->GrpPID[i]);

        ret = pthread_join(pstVdecCtx->GrpTid[i], NULL);
        if (ret) {
            SAMPLE_CRIT_LOG("VdGrp=%d, pthread_join FAILED! ret:%d, %s, \n",
                            i, ret, strerror(ret));
            s32Ret = AX_ERR_VDEC_RUN_ERROR;
            goto ERR_RET_CANCEL_PTHREAD_RECV;
        }
        SAMPLE_LOG("VdGrp=%d, pthread_join _VdecGroupThread done! pthread_id:0x%lx, PID:%d \n",
                   i, pstVdecCtx->GrpTid[i], pstVdecCtx->GrpPID[i]);
        pstVdecCtx->GrpTid[i] = 0;
    }

    if (pstVdecCtx->tCmdParam.bSelectMode == AX_FALSE) {
        for (int gi = pstCmd->uStartGrpId; gi < pstCmd->uStartGrpId + pstCmd->uGrpCount; gi++) {
            VdGrp = gi;
            SAMPLE_LOG("VdGrp=%d, before pthread_join pthread_id:0x%lx",
                        VdGrp, pstVdecCtx->GrpChnRecvTid[VdGrp]);

            ret = pthread_join(pstVdecCtx->GrpChnRecvTid[VdGrp], NULL);
            if (ret) {
                SAMPLE_CRIT_LOG("VdGrp=%d, pthread_join __VdecGrpChnRecvThread FAILED! ret:%d, %s, \n",
                                VdGrp, ret, strerror(ret));
                s32Ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET_CANCEL_PTHREAD_DEC;
            } else {
                SAMPLE_LOG("VdGrp=%d, pthread_join __VdecGrpChnRecvThread done! pthread_id:0x%lx",
                                VdGrp, pstVdecCtx->GrpChnRecvTid[VdGrp]);
                pstVdecCtx->GrpChnRecvTid[VdGrp] = 0;
            }
        }
    }
    else {
        /* At least one group was successfully created and configured */
        if (s_groupSuccess) {
            ret = pthread_join(pstVdecCtx->RecvTid, NULL);
            if (ret) {
                SAMPLE_CRIT_LOG("pthread_join FAILED! ret:%d, %s, \n",
                                ret, strerror(ret));
                s32Ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET;
            }
        } else {
            /* If no group is successfully created, cancel the thread directly */
            ret = pthread_cancel(pstVdecCtx->RecvTid);
            if (ret) {
                SAMPLE_LOG("pthread has been released! ret:%d, %s, \n",
                           ret, strerror(ret));
                s32Ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET;
            }
        }
    }

    return s32Ret;

ERR_RET_CANCEL_PTHREAD_RECV:
    if (pstVdecCtx->tCmdParam.bSelectMode == AX_FALSE) {
        for (int gi = pstCmd->uStartGrpId; gi < pstCmd->uStartGrpId + pstCmd->uGrpCount; gi++) {
            VdGrp = gi;
            ret = pthread_cancel(pstVdecCtx->GrpChnRecvTid[VdGrp]);
            if (ret) {
                SAMPLE_CRIT_LOG("VdGrp=%d, pthread_cancel __VdecGrpChnRecvThread FAILED! ret:%d, %s, \n",
                                VdGrp, ret, strerror(ret));
                s32Ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET;
            }

            ret = pthread_join(pstVdecCtx->GrpChnRecvTid[VdGrp], NULL);
            if (ret) {
                SAMPLE_CRIT_LOG("VdGrp=%d, pthread_join __VdecGrpChnRecvThread FAILED! ret:%d, %s, \n",
                                VdGrp, ret, strerror(ret));
                s32Ret = AX_ERR_VDEC_RUN_ERROR;
                goto ERR_RET;
            }
            SAMPLE_LOG("VdGrp=%d, pthread_join __VdecGrpChnRecvThread done! pthread_id:0x%lx",
                        VdGrp, pstVdecCtx->GrpChnRecvTid[VdGrp]);
            pstVdecCtx->GrpChnRecvTid[VdGrp] = 0;
        }
    } else {
        ret = pthread_cancel(pstVdecCtx->RecvTid);
        if (ret) {
            SAMPLE_CRIT_LOG("pthread_cancel FAILED! ret:%d, %s, \n",
                            ret, strerror(ret));
            s32Ret = AX_ERR_VDEC_RUN_ERROR;
            goto ERR_RET;
        }

        ret = pthread_join(pstVdecCtx->RecvTid, NULL);
        if (ret) {
            SAMPLE_CRIT_LOG("pthread_join FAILED! ret:%d, %s, \n",
                            ret, strerror(ret));
            s32Ret = AX_ERR_VDEC_RUN_ERROR;
            goto ERR_RET;
        }
    }

ERR_RET_CANCEL_PTHREAD_DEC:
    for (i = pstCmd->uStartGrpId; i < pstCmd->uStartGrpId + pstCmd->uGrpCount; i++) {
        ret = pthread_cancel(pstVdecCtx->GrpTid[i]);
        if (ret) {
            SAMPLE_CRIT_LOG("VdGrp=%d, pthread_cancel FAILED! ret:%d, %s, \n",
                            i, ret, strerror(ret));
            goto ERR_RET;
        }

        ret = pthread_join(pstVdecCtx->GrpTid[i], NULL);
        if (ret) {
            SAMPLE_CRIT_LOG("VdGrp=%d, pthread_join FAILED! ret:%d, %s, \n",
                            i, ret, strerror(ret));
            goto ERR_RET;
        }
    }
ERR_RET:
    return s32Ret;
}

int Sample_VdecTestBenchMain(SAMPLE_VDEC_CONTEXT_T *pstSampleCtx)
{
    int i;
    AX_S32 s32Ret = 0;
    SAMPLE_VDEC_ARGS_T *pstVdecGrpArgs = NULL;
    SAMPLE_VDEC_CMD_PARAM_T *pstCmd = NULL;
    SAMPLE_VDEC_CONTEXT_T *pstVdecCtx = pstSampleCtx;
    AX_VDEC_GRP uStartGrpId = 0;

    if (pstVdecCtx == NULL) {
        SAMPLE_CRIT_LOG("pstSampleCtx == NULL\n");
        return -1;
    }

    pstCmd = &pstVdecCtx->tCmdParam;

    uStartGrpId = pstCmd->uStartGrpId;
    for (i = uStartGrpId; i < uStartGrpId + pstCmd->uGrpCount; i++) {
        pstVdecGrpArgs = &pstVdecCtx->stVdecGrpArgs[i];
        memset(pstVdecGrpArgs, 0x0, sizeof(SAMPLE_VDEC_ARGS_T));

        pstVdecGrpArgs->VdGrp = i;
        pstVdecGrpArgs->pstCtx = pstVdecCtx;
        pstVdecGrpArgs->tVdGrpAttr.enCodecType = pstVdecCtx->tCmdParam.enDecType;
    }

    SAMPLE_LOG_N("pstVdecCtx->tCmdParam.enDecType:%d\n", pstVdecCtx->tCmdParam.enDecType);

    if (s_ThreadExit) {
        SAMPLE_LOG_TMP("thread exit:%d, so goto exit\n", s_ThreadExit);
        goto ERR_RET_ARGS;
    }

    s32Ret = _VdecTestMain(pstVdecCtx);
    if (s32Ret) {
        SAMPLE_CRIT_LOG("VdGrp=%d, _VdecTestMain FAILED! ret:0x%x, %s\n",
                        i, s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_ARGS;
    }

    return s32Ret;
ERR_RET_ARGS:

    return s32Ret;
}

static void _VdecSigInt(int sigNo)
{
    s_ThreadExit++;

    SAMPLE_LOG_TMP("Catch signal %d, s_ThreadExit:%d ==============\n\n\n", sigNo, s_ThreadExit);

    if (s_ThreadExit > 3) {
        exit(0);
    }
}

AX_S32 Sample_VdecTestBenchInit(int argc, char *argv[], SAMPLE_VDEC_CONTEXT_T **ppstVdecCtx)
{
    AX_S32 s32Ret = 0;
    pid_t pid, ppid;
    struct timeval current_tv;
    SAMPLE_VDEC_CONTEXT_T *pstVdecCtx = NULL;
    int gi = 0;
    int bi;

    signal(SIGINT, _VdecSigInt); /* ctrl + c */
    signal(SIGQUIT, _VdecSigInt); /* ctrl + \ */
    signal(SIGTSTP, _VdecSigInt); /* ctrl + z */

    gettimeofday(&current_tv, NULL);
    pid = getpid();
    ppid = getppid();

    SampelVdecSetThreadName("%s", argv[0]);
    SAMPLE_LOG("Start! pid:%d, ppid:%d, thr %s date:%s, time:%s, current_tv.tv_sec:%ld",
               pid, ppid, argv[0], __DATE__, __TIME__, current_tv.tv_sec);

    pstVdecCtx = (SAMPLE_VDEC_CONTEXT_T *)calloc(1, sizeof(SAMPLE_VDEC_CONTEXT_T));
    if (NULL == pstVdecCtx) {
        SAMPLE_CRIT_LOG("calloc FAILED! size:0x%x\n", (AX_U32)sizeof(SAMPLE_VDEC_CONTEXT_T));
        return -1;
    }
    pstVdecCtx->argc = argc;
    pstVdecCtx->argv = argv;

    for (gi = 0; gi < AX_VDEC_MAX_GRP_NUM; gi++) {
        for (bi = 0; bi < SAMPLE_VDEC_REF_BLK_CNT; bi++) {
            pstVdecCtx->blkRef[gi][bi] = AX_INVALID_BLOCKID;
        }
    }

    *ppstVdecCtx = pstVdecCtx;

    return s32Ret;
}

int Sample_VdecJpegDecodeOneFrame(SAMPLE_VDEC_CMD_PARAM_T *pstCmd)
{
    int res = 0;
    AX_S32 s32Ret = 0;
    AX_S32 sRet = 0;
    AX_U64 streamPhyAddr = 0;
    AX_VOID *pStreamVirAddr = NULL;
    AX_U64 outPhyAddrDst = 0;
    AX_VOID *outVirAddrDst = NULL;
    AX_S32 heightAlign = 0;
    AX_S32 frmStride = 0;

    FILE *fInput = NULL;
    FILE *fp_out = NULL;
    AX_U32 uBufSize = 0;
    off_t inputFileSize = 0;
    AX_CHAR *streamFile = NULL;
    AX_VDEC_DEC_ONE_FRM_T decOneFrmParam;
    SAMPLE_INPUT_FILE_INFO_T stStreamInfo;
    SAMPLE_STREAM_BUF_T stStreamBuf;
    size_t sReadLen = 0;
    SAMPLE_VDEC_OUTPUT_INFO_T out_info;
    AX_VIDEO_FRAME_INFO_T stFrameInfo;
    AX_U32 uPixBits = 0;

    if (NULL == pstCmd) {
        SAMPLE_CRIT_LOG("NULL == pstCmd\n");
        s32Ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    if (pstCmd->enDecType != PT_JPEG) {
        SAMPLE_CRIT_LOG("only support for jpeg\n");
        s32Ret = AX_ERR_VDEC_ILLEGAL_PARAM;
        goto ERR_RET;
    }

    streamFile = pstCmd->pInputFilePath;
    if (NULL == streamFile) {
        SAMPLE_CRIT_LOG("NULL == streamFile\n");
        s32Ret = AX_ERR_VDEC_NULL_PTR;
        goto ERR_RET;
    }

    memset(&decOneFrmParam, 0x0, sizeof(AX_VDEC_DEC_ONE_FRM_T));
    memset(&stStreamInfo, 0x0, sizeof(SAMPLE_INPUT_FILE_INFO_T));
    memset(&stStreamBuf, 0x0, sizeof(SAMPLE_STREAM_BUF_T));
    memset(&out_info, 0x0, sizeof(SAMPLE_VDEC_OUTPUT_INFO_T));
    memset(&stFrameInfo, 0x0, sizeof(AX_VIDEO_FRAME_INFO_T));
    /* Reading input file */
    fInput = fopen(streamFile, "rb");
    if (fInput == NULL) {
        SAMPLE_CRIT_LOG("Unable to open input stream file:%s\n", streamFile);
        s32Ret = AX_ERR_VDEC_RUN_ERROR;
        goto ERR_RET;
    }

    /* file i/o pointer to full */
    res = fseek(fInput, 0L, SEEK_END);
    if (res) {
        SAMPLE_CRIT_LOG("fseek FAILED! ret:%d\n", res);
        s32Ret = AX_ERR_VDEC_RUN_ERROR;
        goto ERR_RET_CLOSE_IN;
    }

    inputFileSize = ftello(fInput);
    rewind(fInput);
    if (inputFileSize == -1) {
        SAMPLE_LOG_TMP("note:---------------file size err!!!!!!--------------\n");
    }

    if (pstCmd->highRes)
        stStreamBuf.uBufSize = STREAM_BUFFER_MAX_SIZE_HIGH_RES;
    else
        stStreamBuf.uBufSize = inputFileSize > STREAM_BUFFER_MAX_SIZE ? STREAM_BUFFER_MAX_SIZE : inputFileSize;
    s32Ret = AX_SYS_MemAlloc(&streamPhyAddr, (AX_VOID **)&pStreamVirAddr,
                             stStreamBuf.uBufSize, 0x100, (AX_S8 *)"vdec_input_stream");
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_SYS_MemAlloc FAILED! uBufSize:0x%x ret:0x%x\n",
                        stStreamBuf.uBufSize, s32Ret);
        goto ERR_RET_CLOSE_IN;
    }

    stStreamBuf.tBufAddr.pVirAddr = pStreamVirAddr;
    stStreamBuf.tBufAddr.u64PhyAddr = streamPhyAddr;

    uPixBits = 8;
    frmStride = AX_COMM_ALIGN(pstCmd->u32PicWidth * uPixBits, AX_VDEC_WIDTH_ALIGN * 8) / 8;
    heightAlign = ALIGN_UP(pstCmd->u32PicHeight, 16);
    // uBufSize = widthAlign * heightAlign * 3 / 2;
    uBufSize = AX_VDEC_GetPicBufferSize(frmStride, heightAlign, pstCmd->enDecType);
    s32Ret = AX_SYS_MemAlloc(&outPhyAddrDst, (AX_VOID **)&outVirAddrDst,
                             uBufSize, 0x1000, (AX_S8 *)"vdec_output_YUV");
    if (s32Ret != 0) {
        SAMPLE_CRIT_LOG("AX_SYS_MemAlloc FAILED! uBufSize:0x%x ret:0x%x\n",
                       uBufSize, s32Ret);
        goto ERR_RET_FREE_STREAM;
    }

    stStreamInfo.fInput = fInput;
    stStreamInfo.sFileSize = inputFileSize;

    sRet = StreamParserReadFrameJpeg(&stStreamInfo, &stStreamBuf, &sReadLen);
    if (sRet) {
        SAMPLE_CRIT_LOG("StreamParserReadFrameJpeg FAILED! ret:0x%x\n", sRet);
        s32Ret = AX_ERR_VDEC_STRM_ERROR;
        goto ERR_RET_FREE_OUT;
    }

    if (!sReadLen) {
        SAMPLE_CRIT_LOG("read jpeg frame FAILED!\n");
        s32Ret = AX_ERR_VDEC_STRM_ERROR;
        goto ERR_RET_FREE_OUT;
    }

    decOneFrmParam.stStream.pu8Addr = stStreamBuf.tBufAddr.pVirAddr;
    decOneFrmParam.stStream.u64PhyAddr = stStreamBuf.tBufAddr.u64PhyAddr;
    decOneFrmParam.stStream.u32StreamPackLen = (AX_U32)sReadLen;

    decOneFrmParam.stFrame.u64VirAddr[0] = (AX_ULONG)outVirAddrDst;
    decOneFrmParam.stFrame.u64VirAddr[1] = (AX_ULONG)outVirAddrDst + frmStride * heightAlign;
    decOneFrmParam.stFrame.u64PhyAddr[0] = outPhyAddrDst;
    decOneFrmParam.stFrame.u64PhyAddr[1] = outPhyAddrDst + frmStride * heightAlign;

    s32Ret = AX_VDEC_JpegDecodeOneFrame(&decOneFrmParam);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_VDEC_JpegDecodeOneFrame FAILED! ret:0x%x %s\n",
                        s32Ret, SampleVdecRetStr(s32Ret));
        goto ERR_RET_FREE_OUT;
    }

    if (pstCmd->sWriteFrames) {
        out_info.enImgFormat = decOneFrmParam.stFrame.enImgFormat;
        out_info.u32Width = decOneFrmParam.stFrame.u32Width;
        out_info.u32Height = decOneFrmParam.stFrame.u32Height;
        out_info.u32PicStride = decOneFrmParam.stFrame.u32PicStride[0];
        out_info.bOneShot = AX_TRUE;
        fp_out = OutputFileOpen(&pstCmd->pOutputFilePath, &out_info);
        if (fp_out == NULL) {
            if (pstCmd->pOutputFilePath != NULL) {
                SAMPLE_CRIT_LOG("fopen pstCmd->pOutputFilePath:%s FAILED!", pstCmd->pOutputFilePath);
                free(pstCmd->pOutputFilePath);
                pstCmd->pOutputFilePath = NULL;
            }
            s32Ret = AX_ERR_VDEC_RUN_ERROR;
            goto ERR_RET_FREE_OUT;
        }

        stFrameInfo.stVFrame = decOneFrmParam.stFrame;
        s32Ret = OutputFileSaveYUV(0, &stFrameInfo, fp_out, pstCmd->pOutputFilePath);
        if (s32Ret) {
            SAMPLE_CRIT_LOG("OutputFileSaveYUV FAILED! ret:0x%x", s32Ret);
            s32Ret = AX_ERR_VDEC_RUN_ERROR;
            goto ERR_RET_FREE_OUT;
        }
    }

    if (fInput != NULL) {
        res = fclose(fInput);
        if (res) {
            SAMPLE_CRIT_LOG("fclose FAILED! ret:%d\n", res);
            sRet = AX_ERR_VDEC_RUN_ERROR;
        }
        fInput = NULL;
    }

    if (fp_out != NULL) {
        res = fclose(fp_out);
        if (res) {
            SAMPLE_CRIT_LOG("fclose FAILED! ret:%d\n", res);
            sRet = AX_ERR_VDEC_RUN_ERROR;
        }
        fp_out = NULL;
    }

    s32Ret = AX_SYS_MemFree(streamPhyAddr, pStreamVirAddr);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_SYS_MemFree streamPhyAddr FAILED! s32Ret:0x%x\n", s32Ret);
    }

    s32Ret = AX_SYS_MemFree(outPhyAddrDst, (AX_VOID *)outVirAddrDst);
    if (s32Ret != AX_SUCCESS) {
        SAMPLE_CRIT_LOG("AX_SYS_MemFree outPhyAddrDst FAILED! s32Ret:0x%x\n", s32Ret);
    }

    if (s32Ret || sRet) {
        goto ERR_RET;
    }

    g_u64GetFrmTag += 1;

    return 0;


ERR_RET_FREE_OUT:
    if (outVirAddrDst != NULL) {
        sRet = AX_SYS_MemFree(outPhyAddrDst, (AX_VOID *)outVirAddrDst);
        if(sRet != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("AX_SYS_MemFree outPhyAddrDst FAILED! sRet:0x%x\n", sRet);
        }
    }
ERR_RET_FREE_STREAM:
    if (pStreamVirAddr != NULL) {
        sRet = AX_SYS_MemFree(streamPhyAddr, pStreamVirAddr);
        if(sRet != AX_SUCCESS) {
            SAMPLE_CRIT_LOG("AX_SYS_MemFree streamPhyAddr FAILED! sRet:0x%x\n", sRet);
        }
    }
ERR_RET_CLOSE_IN:
    if (fInput) {
        res = fclose(fInput);
        if (res) {
            SAMPLE_CRIT_LOG("fclose FAILED! ret:%d\n", res);
        }
        fInput = NULL;
    }
ERR_RET:
    SAMPLE_CRIT_LOG("s32Ret:0x%x, sRet:0x%x", s32Ret, sRet);
    return s32Ret || sRet;
}
