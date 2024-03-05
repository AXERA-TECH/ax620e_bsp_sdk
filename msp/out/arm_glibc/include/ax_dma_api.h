/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _AX_DMA_API_H_
#define _AX_DMA_API_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
    AX_DMA_ENDIAN_DEF = 0,
    AX_DMA_ENDIAN_32,
    AX_DMA_ENDIAN_16,
    AX_DMA_ENDIAN_MAX = AX_DMA_ENDIAN_16
} AX_DMA_ENDIAN_E;

typedef enum {
    AX_DMA_1D = 0,
    AX_DMA_2D,
    AX_DMA_3D,
    AX_DMA_4D,
    AX_DMA_MEMORY_INIT,
    AX_DMA_CHECKSUM,
} AX_DMA_XFER_MODE_E;

typedef struct {
    AX_S32 s32Id;
    AX_U32 u32CheckSum;
    AX_U32 u32Stat;
} AX_DMA_XFER_STAT_T;

enum {
    e2DCpy = 0,
    e3DCpy,
    e4DCpy,
    eMaxSize,
};

typedef struct {
    AX_U64 u64PhyAddr;
    AX_U32 u32Imgw;
    AX_U32 u32Stride[eMaxSize];
} AX_DMA_INFO_T;

/** @brief transmit information for AX_DMA_2D/AX_DMA_3D/AX_DMA_4D */
typedef struct {
    AX_U16 u16Ntiles[eMaxSize];
    AX_DMA_INFO_T tSrcInfo;
    AX_DMA_INFO_T tDstInfo;
} AX_DMA_DESC_XD_T;

/** @brief transmit information for AX_DMA_MEMORY_INIT */
typedef struct {
    AX_U64 u64InitVal;
    AX_U64 u64PhyDst;
    AX_U32 u32Size;
} AX_DMA_DESC_MEMSET_T;

/** @brief transmit information for AX_DMA_CHECKSUM/AX_DMA_1D */
typedef struct {
    AX_U64 u64PhySrc;
    AX_U64 u64PhyDst;
    AX_U32 u32Size;
} AX_DMA_DESC_T;

/**
 * @brief DIM transfer msg struct
 *
 * u32DescNum: The number of dma transmission nodes
 * eEndian: The endian for AX_DMA_1D/AX_DMA_2D/AX_DMA_3D/AX_DMA_4D
 * pDescBuf: dma transmission nodes, type is related to eDmaMode, and assigned
 *           (AX_DMA_DESC_T *) or (AX_DMA_DESC_XD_T *)
 * pfnCallBack: a call back func for dma transfer done,
 *             The first parameter save the dma transfer result
 *             The second parameter id pCbArg, customized by user
 * pCbArg: The second parameter of pfnCallBack
 * eDmaMode: dma transfer mode(AX_DMA_XFER_MODE_E)
 */
typedef struct {
    AX_U32 u32DescNum;
    AX_DMA_ENDIAN_E eEndian;
    AX_VOID *pDescBuf;
    AX_VOID(*pfnCallBack)(AX_DMA_XFER_STAT_T *, AX_VOID *);
    AX_VOID *pCbArg;
    AX_DMA_XFER_MODE_E eDmaMode;
} AX_DMA_MSG_T;

AX_S32 AX_DMA_Open(AX_BOOL bSync);
AX_S32 AX_DMA_Cfg(AX_S32 s32DmaChn, AX_DMA_MSG_T *pDmaMsg);
AX_S32 AX_DMA_Start(AX_S32 s32DmaChn, AX_S32 s32Id);
AX_S32 AX_DMA_Waitdone(AX_S32 s32DmaChn, AX_DMA_XFER_STAT_T *pXferStat, AX_S32 s32Timeout);
AX_S32 AX_DMA_Close(AX_S32 s32DmaChn);

AX_S32 AX_DMA_MemCopy(AX_U64 u64PhyDst, AX_U64 u64PhySrc, AX_U64 U64Size);
AX_S32 AX_DMA_MemSet(AX_U64 u64PhyDst, AX_U8 u8InitVal, AX_U64 U64Size);
AX_S32 AX_DMA_MemCopyXD(AX_DMA_DESC_XD_T tDimDesc, AX_DMA_XFER_MODE_E eMode);
AX_S32 AX_DMA_CheckSum(AX_U32 *u32Result, AX_U64 u64PhySrc, AX_U64 U64Size);

enum {
    AX_DMA_ERRNO_DEFAULT = 0x80,
    AX_DMA_ERRNO_ENOENT = 0x82,
    AX_DMA_ERRNO_EIO = 0x85,
    AX_DMA_ERRNO_EFAULT = 0x8E,
    AX_DMA_ERRNO_EINVAL = 0x96,
};

#define AX_ID_DMA_SUB                   0x1
#define AX_ERR_DMA_NOMEM                AX_DEF_ERR(AX_ID_DMA, AX_ID_DMA_SUB, AX_ERR_NOMEM)
#define AX_ERR_DMA_TIMEOUT              AX_DEF_ERR(AX_ID_DMA, AX_ID_DMA_SUB, AX_ERR_TIMED_OUT)

#define AX_ERR_DMA_EIO                  AX_DEF_ERR(AX_ID_DMA, AX_ID_DMA_SUB, AX_DMA_ERRNO_EIO)
#define AX_ERR_DMA_ENOENT               AX_DEF_ERR(AX_ID_DMA, AX_ID_DMA_SUB, AX_DMA_ERRNO_ENOENT)
#define AX_ERR_DMA_EFAULT               AX_DEF_ERR(AX_ID_DMA, AX_ID_DMA_SUB, AX_DMA_ERRNO_EFAULT)
#define AX_ERR_DMA_EINVAL               AX_DEF_ERR(AX_ID_DMA, AX_ID_DMA_SUB, AX_DMA_ERRNO_EINVAL)

#define DMA_XFER_SUCCESS     1

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
