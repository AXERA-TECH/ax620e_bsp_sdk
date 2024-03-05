/**********************************************************************************
 *
 * Copyright (c) 2019-2020 Beijing AXera Technology Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Beijing AXera Technology Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Beijing AXera Technology Co., Ltd.
 *
 **********************************************************************************/
#ifndef _FRAME_MGR_H_
#define _FRAME_MGR_H_
#include "ax_global_type.h"
#include "ax_sys_api.h"
#include "ax_skel_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SKEL_FRAME_BUF_DEFAULT_DEPTH 2

AX_VOID FrameMgrCreate(AX_U32 nDepth);
AX_VOID FrameMgr(const AX_SKEL_RESULT_T *pstResult);
AX_BOOL FrameMgrGet(AX_U64 *YUVDataPhy, AX_VOID **YUVDataVir, AX_U32 nFrameSize, AX_U64 nFrameId,AX_BLK blkId);
AX_VOID FrameMgrDestroy(AX_VOID);

#ifdef __cplusplus
}
#endif

#endif
