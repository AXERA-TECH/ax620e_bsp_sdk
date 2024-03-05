/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#include "ax_base_type.h"
#include "ax_sys_api.h"
#include "ax_dma_api.h"
#include "ax_thread_signal.h"

#define DMA_BLOCK 1
#define DMA_NOBLOCK 0

// #define DEBUG
#ifdef DEBUG
    #define PK_DBG(fmt,arg...) printf("DMA Sample: %s,%d "fmt,__func__,__LINE__,##arg)
#else
    #define PK_DBG(fmt,arg...)
#endif

#define PK_INFO(fmt,arg...) printf("DMA Sample: %s,%d "fmt,__func__,__LINE__,##arg)
#define PK_ERR(fmt,arg...) printf("DMA Sample Err: %s,%d "fmt,__func__,__LINE__,##arg)

static ThreadSignal g_signal;

typedef struct {
    AX_U64 *aVir;
    AX_U64 aPhy;
    AX_U64 u32Size;
} ADDR_BUF_T;

typedef struct {
    AX_U32 u32DescNum;
    AX_S32 u32Size;
    AX_U32 eEndian;
    ADDR_BUF_T srcBuf[16];
    ADDR_BUF_T dstBuf[16];
} dma_cfg_t;

static int getAddr(ADDR_BUF_T *addrBuf, ADDR_BUF_T *addrBuf2, AX_U32 u32Size)
{
    int i, ret;
    AX_U64 phyAddr;
    void *src_test_virt = NULL;

    for (i = 0; i < 16; i++) {
        ret = AX_SYS_MemAlloc(&phyAddr, &src_test_virt, u32Size, 0x1, (AX_S8 *)"dma_test");
        if (ret < 0) {
            PK_ERR("getAddr alloc failed %d\n", ret);
            return -1;
        }
        addrBuf[i].aPhy = phyAddr;
        addrBuf[i].aVir = src_test_virt;

        ret = AX_SYS_MemAlloc(&phyAddr, &src_test_virt, u32Size, 0x1, (AX_S8 *)"dma_test");
        if (ret < 0) {
            PK_ERR("getAddr alloc failed %d\n", ret);
            return -1;
        }
        addrBuf2[i].aPhy = phyAddr;
        addrBuf2[i].aVir = src_test_virt;
    }
    return 0;
}

static void freeAddr(ADDR_BUF_T *addrBuf, ADDR_BUF_T *addrBuf2)
{
    int i;
    for (i = 0; i < 16; i++) {
        AX_SYS_MemFree(addrBuf[i].aPhy, addrBuf[i].aVir);
        AX_SYS_MemFree(addrBuf2[i].aPhy, addrBuf2[i].aVir);
    }
}

static int AX_DMA_FUNC_MEMORY_INIT_SYNC(ADDR_BUF_T *srcBuf, ADDR_BUF_T *dstBuf, AX_U32 u32DescNum)
{
    int i, ret = 0, s32DmaChn = 0;
    AX_DMA_MSG_T tDmaMsg;
    AX_DMA_DESC_T *pDescBuf;
    AX_DMA_XFER_STAT_T tXferStat;
    memset(&tXferStat, 0, sizeof(AX_DMA_XFER_STAT_T));

    if ((s32DmaChn = AX_DMA_Open(DMA_BLOCK)) < 0) {
        PK_DBG("open error\n");
        return -1;
    }

    pDescBuf = malloc(sizeof(AX_DMA_DESC_T) * u32DescNum);
    if (!pDescBuf) {
        AX_DMA_Close(s32DmaChn);
        return -1;
    }
    tDmaMsg.u32DescNum = u32DescNum;
    tDmaMsg.eDmaMode = AX_DMA_MEMORY_INIT;
    tDmaMsg.pDescBuf = pDescBuf;
    tDmaMsg.pCbArg = NULL;
    tDmaMsg.pfnCallBack = NULL;
    for (i = 0; i < u32DescNum; i++) {
        pDescBuf->u64PhySrc = 0x1234567890abcdef;
        pDescBuf->u64PhyDst = dstBuf[i].aPhy;
        pDescBuf->u32Size = 0x1000;
        pDescBuf++;
    }
    tXferStat.s32Id = AX_DMA_Cfg(s32DmaChn, &tDmaMsg);
    if (tXferStat.s32Id < 1) {
        PK_ERR("tXferStat.s32Id %d\n", tXferStat.s32Id);
        ret = -1;
        goto err;
    }
    ret = AX_DMA_Start(s32DmaChn, tXferStat.s32Id);
    if (ret) {
        PK_ERR("AX_DMA_Start failed!\n");
        goto err;
    }
    ret = AX_DMA_Waitdone(s32DmaChn, &tXferStat, 5000);
    if (ret) {
        PK_ERR("timeout\n");
        goto err;
    }
err:
    free((AX_DMA_DESC_T *)tDmaMsg.pDescBuf);
    AX_DMA_Close(s32DmaChn);
    return ret;
}

static void AX_DMA_MEMINIT_Signal(AX_DMA_XFER_STAT_T *pXferStat, void *pCbArg)
{
    AX_DMA_XFER_STAT_T *tXferStat = (AX_DMA_XFER_STAT_T *)pCbArg;

    memcpy(tXferStat, pXferStat, sizeof(AX_DMA_XFER_STAT_T));
    AX_ThreadSignal_Signal(&g_signal);
}

static int AX_DMA_FUNC_MEMORY_INIT_ASYNC(ADDR_BUF_T *srcBuf, ADDR_BUF_T *dstBuf, AX_U32 u32DescNum)
{
    int i, ret = 0, s32DmaChn = 0;
    AX_DMA_MSG_T tDmaMsg;
    AX_DMA_DESC_T *pDescBuf;
    AX_DMA_XFER_STAT_T tXferStat;
    memset(&tXferStat, 0, sizeof(AX_DMA_XFER_STAT_T));

    if ((s32DmaChn = AX_DMA_Open(DMA_NOBLOCK)) < 0) {
        PK_DBG("open error\n");
        return -1;
    }

    pDescBuf = malloc(sizeof(AX_DMA_DESC_T) * u32DescNum);
    if (!pDescBuf) {
        AX_DMA_Close(s32DmaChn);
        return -1;
    }
    tDmaMsg.u32DescNum = u32DescNum;
    tDmaMsg.eDmaMode = AX_DMA_MEMORY_INIT;
    tDmaMsg.pDescBuf = pDescBuf;
    tDmaMsg.pCbArg = &tXferStat;
    tDmaMsg.pfnCallBack = AX_DMA_MEMINIT_Signal;
    for (i = 0; i < u32DescNum; i++) {
        pDescBuf->u64PhySrc = 0x1234567890abcdef;
        pDescBuf->u64PhyDst = dstBuf[i].aPhy;
        pDescBuf->u32Size = 0x1000;
        pDescBuf++;
    }
    tXferStat.s32Id = AX_DMA_Cfg(s32DmaChn, &tDmaMsg);
    if (tXferStat.s32Id < 1) {
        PK_ERR("tXferStat.s32Id %d\n", tXferStat.s32Id);
        ret = -1;
        goto err;
    }
    ret = AX_DMA_Start(s32DmaChn, tXferStat.s32Id);
    if (ret) {
        PK_ERR("AX_DMA_Start failed!\n");
        goto err;
    }
    ret = AX_ThreadSignal_Wait(&g_signal, 5000);
    if (ret) {
        PK_ERR("AX_ThreadSignal_Wait failed!\n");
        goto err;
    }
err:
    free((AX_DMA_DESC_T *)tDmaMsg.pDescBuf);
    AX_DMA_Close(s32DmaChn);
    return ret;
}

static void AX_DMA_Test_Signal(AX_DMA_XFER_STAT_T *pXferStat, void *pCbArg)
{
    AX_DMA_XFER_STAT_T *tXferStat = (AX_DMA_XFER_STAT_T *)pCbArg;

    memcpy(tXferStat, pXferStat, sizeof(AX_DMA_XFER_STAT_T));
    AX_ThreadSignal_Signal(&g_signal);
}

static int AX_DMA_FUNC_CHECKSUM(ADDR_BUF_T *srcBuf, ADDR_BUF_T *dstBuf, AX_U32 u32DescNum, bool bIsSync)
{
    int i, ret = 0, s32DmaChn = 0;
    AX_DMA_MSG_T tDmaMsg;
    AX_DMA_DESC_T *pDescBuf;
    AX_DMA_XFER_STAT_T tXferStat;
    memset(&tXferStat, 0, sizeof(AX_DMA_XFER_STAT_T));

    if ((s32DmaChn = AX_DMA_Open(bIsSync)) < 0) {
        PK_DBG("open error\n");
        return -1;
    }

    pDescBuf = malloc(sizeof(AX_DMA_DESC_T) * u32DescNum);
    if (!pDescBuf) {
        AX_DMA_Close(s32DmaChn);
        PK_ERR("AX_DMA_Close...\n");
        return -1;
    }
    tDmaMsg.u32DescNum = u32DescNum;
    tDmaMsg.eDmaMode = AX_DMA_CHECKSUM;
    tDmaMsg.pDescBuf = pDescBuf;
    tDmaMsg.pCbArg = &tXferStat;
    tDmaMsg.pfnCallBack = AX_DMA_Test_Signal;
    for (i = 0; i < u32DescNum; i++) {
        pDescBuf->u64PhySrc = srcBuf[i].aPhy;
        pDescBuf->u64PhyDst = 0;
        pDescBuf->u32Size = 0x1000; //aligned 8
        pDescBuf++;
    }
    tXferStat.s32Id = AX_DMA_Cfg(s32DmaChn, &tDmaMsg);
    if (tXferStat.s32Id < 1) {
        PK_ERR("tXferStat.s32Id %d\n", tXferStat.s32Id);
        ret = -1;
        goto err;
    }
    ret = AX_DMA_Start(s32DmaChn, tXferStat.s32Id);
    if (ret) {
        PK_ERR("AX_DMA_Start failed!\n");
        goto err;
    }
    if (bIsSync) {
        ret = AX_DMA_Waitdone(s32DmaChn, &tXferStat, 5000);
        if (ret) {
            PK_ERR("timeout\n");
            goto err;
        }
    } else {
        ret = AX_ThreadSignal_Wait(&g_signal, 5000);
        if (ret) {
            PK_ERR("AX_ThreadSignal_Wait failed!\n");
            goto err;
        }
    }
    PK_DBG("checksum 0x%x\n", tXferStat.u32CheckSum);
err:
    free((AX_DMA_DESC_T *)tDmaMsg.pDescBuf);
    AX_DMA_Close(s32DmaChn);
    return ret;
}

static int AX_DMA_FUNC_1D(ADDR_BUF_T *srcBuf, ADDR_BUF_T *dstBuf, AX_U32 u32DescNum, bool bIsSync)
{
    int i, s32DmaChn = 0, ret = 0;
    AX_DMA_MSG_T tDmaMsg;
    AX_DMA_DESC_T *pDescBuf;
    AX_DMA_XFER_STAT_T tXferStat;
    memset(&tXferStat, 0, sizeof(AX_DMA_XFER_STAT_T));

    if ((s32DmaChn = AX_DMA_Open(bIsSync)) < 0) {
        PK_DBG("open error\n");
        return -1;
    }

    pDescBuf = malloc(sizeof(AX_DMA_DESC_T) * u32DescNum);
    if (!pDescBuf) {
        AX_DMA_Close(s32DmaChn);
        return -1;
    }
    tDmaMsg.u32DescNum = u32DescNum;
    tDmaMsg.eEndian = 1;
    tDmaMsg.eDmaMode = AX_DMA_1D;
    tDmaMsg.pDescBuf = pDescBuf;
    tDmaMsg.pCbArg = &tXferStat;
    tDmaMsg.pfnCallBack = AX_DMA_Test_Signal;

    for (i = 0; i < u32DescNum; i++) {
        pDescBuf->u64PhySrc = srcBuf[i].aPhy;
        pDescBuf->u64PhyDst = dstBuf[i].aPhy;
        pDescBuf->u32Size = 0x1000;
        pDescBuf++;
    }
    tXferStat.s32Id = AX_DMA_Cfg(s32DmaChn, &tDmaMsg);
    if (tXferStat.s32Id < 1) {
        PK_ERR("tXferStat.s32Id %d\n", tXferStat.s32Id);
        ret = -1;
        goto err;
    }
    ret = AX_DMA_Start(s32DmaChn, tXferStat.s32Id);
    if (ret) {
        PK_ERR("AX_DMA_Start failed!\n");
        goto err;
    }
    if (bIsSync) {
        ret = AX_DMA_Waitdone(s32DmaChn, &tXferStat, 5000);
        if (ret) {
            PK_ERR("timeout\n");
            goto err;
        }
    } else {
        ret = AX_ThreadSignal_Wait(&g_signal, 5000);
        if (ret) {
            PK_ERR("AX_ThreadSignal_Wait failed!\n");
            goto err;
        }
    }
err:
    free((AX_DMA_DESC_T *)tDmaMsg.pDescBuf);
    AX_DMA_Close(s32DmaChn);
    return ret;
}

static int AX_DMA_FUNC_MEMORY_XD(ADDR_BUF_T *srcBuf, ADDR_BUF_T *dstBuf, AX_U8 eDmaMode, AX_U32 u32DescNum,
                                    bool bIsSync)
{
    int i, ret = 0, s32DmaChn = 0;
    AX_DMA_MSG_T tDmaMsg;
    AX_DMA_DESC_XD_T *pDescBuf;
    AX_DMA_XFER_STAT_T tXferStat;
    memset(&tXferStat, 0, sizeof(AX_DMA_XFER_STAT_T));

    AX_DMA_DESC_XD_T dimDesc = {
        .u16Ntiles = {4, 2, 3},
        .tSrcInfo = {
            .u32Imgw = 8,
            .u32Stride = {11, 44, 88},
        },
        .tDstInfo = {
            .u32Imgw = 4,
            .u32Stride = {5, 40, 80},
        },
    };

    PK_DBG("eDmaMode %d\n", eDmaMode);

    if ((s32DmaChn = AX_DMA_Open(bIsSync)) < 0) {
        PK_DBG("open error\n");
        return -1;
    }

    pDescBuf = malloc(sizeof(AX_DMA_DESC_XD_T) * u32DescNum);
    if (!pDescBuf) {
        AX_DMA_Close(s32DmaChn);
        return -1;
    }
    tDmaMsg.u32DescNum = u32DescNum;
    tDmaMsg.eEndian = 1;
    tDmaMsg.eDmaMode = eDmaMode;
    tDmaMsg.pDescBuf = pDescBuf;
    tDmaMsg.pCbArg = &tXferStat;
    tDmaMsg.pfnCallBack = AX_DMA_Test_Signal;
    for (i = 0; i < u32DescNum; i++) {
        memcpy(pDescBuf, &dimDesc, sizeof(AX_DMA_DESC_XD_T));
        pDescBuf->tSrcInfo.u64PhyAddr = srcBuf[i].aPhy;
        pDescBuf->tDstInfo.u64PhyAddr = dstBuf[i].aPhy;
        pDescBuf++;
    }
    tXferStat.s32Id = AX_DMA_Cfg(s32DmaChn, &tDmaMsg);
    if (tXferStat.s32Id < 1) {
        PK_ERR("tXferStat.s32Id %d\n", tXferStat.s32Id);
        ret = -1;
        goto err;
    }
    ret = AX_DMA_Start(s32DmaChn, tXferStat.s32Id);
    if (ret) {
        PK_ERR("AX_DMA_Start failed!\n");
        goto err;
    }
    if (bIsSync) {
        ret = AX_DMA_Waitdone(s32DmaChn, &tXferStat, 5000);
        if (ret) {
            PK_ERR("timeout\n");
            goto err;
        }
    } else {
        ret = AX_ThreadSignal_Wait(&g_signal, 5000);
        if (ret) {
            PK_ERR("AX_ThreadSignal_Wait failed!\n");
            goto err;
        }
    }
err:
    free((AX_DMA_DESC_XD_T *)tDmaMsg.pDescBuf);
    AX_DMA_Close(s32DmaChn);
    return 0;
}

static int AX_DMA_FUNC_SIMPLIFY(ADDR_BUF_T *srcBuf, ADDR_BUF_T *dstBuf)
{
    int ret = 0;
    AX_DMA_DESC_XD_T tDimDesc = {
        .u16Ntiles = {4, 2, 3},
        .tSrcInfo = {
            .u32Imgw = 8,
            .u32Stride = {11, 44, 88},
        },
        .tDstInfo = {
            .u32Imgw = 4,
            .u32Stride = {5, 40, 80},
        },
    };
    tDimDesc.tSrcInfo.u64PhyAddr = srcBuf[2].aPhy;
    tDimDesc.tDstInfo.u64PhyAddr = dstBuf[2].aPhy;

    ret |= AX_DMA_MemCopy(dstBuf[0].aPhy, srcBuf[0].aPhy, 0x1000);
    ret |= AX_DMA_MemSet(dstBuf[1].aPhy, 0xAA, 0x1000);
    ret |= AX_DMA_MemCopyXD(tDimDesc, AX_DMA_2D);
    ret |= AX_DMA_MemCopyXD(tDimDesc, AX_DMA_3D);
    ret |= AX_DMA_MemCopyXD(tDimDesc, AX_DMA_4D);
    return ret;
}

int main()
{
    int ret;
    ADDR_BUF_T srcBuf[16];
    ADDR_BUF_T dstBuf[16];

    AX_SYS_Init();
    ret = getAddr(srcBuf, dstBuf, 0x2000);
    if (ret) {
        PK_ERR("Error!");
        return -1;
    }
    AX_ThreadSignal_Init(&g_signal, 1);
    ret |= AX_DMA_FUNC_MEMORY_INIT_SYNC(srcBuf, dstBuf, 1);
    ret |= AX_DMA_FUNC_MEMORY_INIT_ASYNC(srcBuf, dstBuf, 1);
    ret |= AX_DMA_FUNC_CHECKSUM(srcBuf, dstBuf, 1, DMA_BLOCK);
    ret |= AX_DMA_FUNC_CHECKSUM(srcBuf, dstBuf, 1, DMA_NOBLOCK);
    ret |= AX_DMA_FUNC_1D(srcBuf, dstBuf, 1, DMA_BLOCK);
    ret |= AX_DMA_FUNC_1D(srcBuf, dstBuf, 1, DMA_NOBLOCK);
    ret |= AX_DMA_FUNC_MEMORY_XD(srcBuf, dstBuf, AX_DMA_2D, 1, DMA_BLOCK);
    ret |= AX_DMA_FUNC_MEMORY_XD(srcBuf, dstBuf, AX_DMA_2D, 1, DMA_NOBLOCK);
    ret |= AX_DMA_FUNC_MEMORY_XD(srcBuf, dstBuf, AX_DMA_3D, 1, DMA_BLOCK);
    ret |= AX_DMA_FUNC_MEMORY_XD(srcBuf, dstBuf, AX_DMA_3D, 1, DMA_NOBLOCK);
    ret |= AX_DMA_FUNC_MEMORY_XD(srcBuf, dstBuf, AX_DMA_4D, 1, DMA_BLOCK);
    ret |= AX_DMA_FUNC_MEMORY_XD(srcBuf, dstBuf, AX_DMA_4D, 1, DMA_NOBLOCK);
    ret |= AX_DMA_FUNC_SIMPLIFY(srcBuf, dstBuf);
    AX_ThreadSignal_Destroy(&g_signal);
    freeAddr(srcBuf, dstBuf);
    AX_SYS_Deinit();
    if (ret)
        PK_ERR("test failed!\n");
    else
        PK_INFO("test successful.\n");
    return 0;
}
