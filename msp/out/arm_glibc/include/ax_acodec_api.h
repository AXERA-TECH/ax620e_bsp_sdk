/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _AX_ACODEC_API_H_
#define _AX_ACODEC_API_H_

#include "ax_global_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define AX_ACODEC_BAND_NUM 5
#define AX_ACODEC_PARAM_NUM (AX_ACODEC_BAND_NUM*2)
#define AX_ACODEC_STRING_LEN 32
typedef AX_U32 ACODEC_CARD;

typedef enum {
    AX_ID_ACODEC_NULL    = 0x02,

    AX_ID_ACODEC_BUTT,
} AX_ACODEC_SUB_ID_E;

#define AX_ERR_ACODEC_INVALID_CHNID               AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_INVALID_CHNID)
#define AX_ERR_ACODEC_NULL_PTR                    AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_NULL_PTR)
#define AX_ERR_ACODEC_EXIST                       AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_EXIST)
#define AX_ERR_ACODEC_NOMEM                       AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_NOMEM)
#define AX_ERR_ACODEC_NOT_SUPPORT                 AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_NOT_SUPPORT)
#define AX_ERR_ACODEC_UNEXIST                     AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_UNEXIST)
#define AX_ERR_ACODEC_NOBUF                       AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_NOBUF)
#define AX_ERR_ACODEC_NOT_PERM                    AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_NOT_PERM)
#define AX_ERR_ACODEC_BUF_FULL                    AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_BUF_FULL)
#define AX_ERR_ACODEC_BUF_EMPTY                   AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_BUF_EMPTY)
#define AX_ERR_ACODEC_SYS_NOTREADY                AX_DEF_ERR(AX_ID_ACODEC, AX_ID_ACODEC_NULL, AX_ERR_SYS_NOTREADY)

typedef struct axACODEC_EQ_ATTR_T {
    AX_S32  s32GainDb[AX_ACODEC_BAND_NUM];
    AX_S32  s32Samplerate;
    AX_BOOL bEnable;
    AX_U32  u32Reserved;
} AX_ACODEC_EQ_ATTR_T;

typedef struct axACODEC_FREQ_ATTR_T {
    AX_S32  s32GainDb;
    AX_S32  s32Samplerate;
    AX_S32  s32Freq;
    AX_BOOL bEnable;
    AX_U32  u32Reserved;
} AX_ACODEC_FREQ_ATTR_T;

AX_S32 AX_ACODEC_RxEqSetAttr(ACODEC_CARD acCardId, const AX_ACODEC_EQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_RxEqGetAttr(ACODEC_CARD acCardId, AX_ACODEC_EQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_RxEqEnable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_RxEqDisable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_RxHpfSetAttr(ACODEC_CARD acCardId, const AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_RxHpfGetAttr(ACODEC_CARD acCardId, AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_RxHpfEnable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_RxHpfDisable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_RxLpfSetAttr(ACODEC_CARD acCardId, const AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_RxLpfGetAttr(ACODEC_CARD acCardId, AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_RxLpfEnable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_RxLpfDisable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_TxEqSetAttr(ACODEC_CARD acCardId, const AX_ACODEC_EQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_TxEqGetAttr(ACODEC_CARD acCardId, AX_ACODEC_EQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_TxEqEnable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_TxEqDisable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_TxHpfSetAttr(ACODEC_CARD acCardId, const AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_TxHpfGetAttr(ACODEC_CARD acCardId, AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_TxHpfEnable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_TxHpfDisable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_TxLpfSetAttr(ACODEC_CARD acCardId, const AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_TxLpfGetAttr(ACODEC_CARD acCardId, AX_ACODEC_FREQ_ATTR_T *pstAttr);
AX_S32 AX_ACODEC_TxLpfEnable(ACODEC_CARD acCardId);
AX_S32 AX_ACODEC_TxLpfDisable(ACODEC_CARD acCardId);

#ifdef __cplusplus
}
#endif

#endif
