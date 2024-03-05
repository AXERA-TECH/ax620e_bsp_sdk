/**********************************************************************************
 *
 * Copyright (c) 2019-2020 Beijing AXera Technology Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Beijing AXera Technology Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Beijing AXera Technology Co., Ltd.
 *
 **********************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "frameMgr.h"
#include <iostream>

typedef struct _SKEL_FRAME_BUF_T {
    AX_VOID *YUVDataVir;
    AX_U64 YUVDataPhy;
    AX_BOOL bUsed;
    AX_U64 nFrameId;

    _SKEL_FRAME_BUF_T(){
        memset(this, 0x00, sizeof(struct _SKEL_FRAME_BUF_T));
    }
} SKEL_FRAME_BUF_T;

AX_BOOL g_bSkel_frame_mgr_inited = AX_FALSE;
std::vector<SKEL_FRAME_BUF_T> g_skel_frame_buf;

AX_VOID FrameMgrCreate(AX_U32 nDepth) {
    g_skel_frame_buf.resize(nDepth);
    g_bSkel_frame_mgr_inited = AX_TRUE;
}

AX_VOID FrameMgr(const AX_SKEL_RESULT_T *pstResult) {
    if (!pstResult || !g_bSkel_frame_mgr_inited) {
        return;
    }

    for (AX_U32 i = 0; i < g_skel_frame_buf.size(); i ++) {
        if (g_skel_frame_buf[i].bUsed) {
            // still in frame queue
            if (g_skel_frame_buf[i].nFrameId > pstResult->nFrameId) {
                continue;
            }

            AX_BOOL bInCacheList = AX_FALSE;
            for (AX_U32 j = 0; j < pstResult->nCacheListSize; j ++) {
                if (g_skel_frame_buf[i].nFrameId == pstResult->pstCacheList[j].nFrameId) {
                    bInCacheList = AX_TRUE;
                    break;
                }
            }

            if (!bInCacheList) {
                if (g_skel_frame_buf[i].YUVDataPhy != 0
                    && g_skel_frame_buf[i].YUVDataVir) {
                    AX_SYS_MemFree(g_skel_frame_buf[i].YUVDataPhy, g_skel_frame_buf[i].YUVDataVir);
                    g_skel_frame_buf[i].YUVDataPhy = 0;
                    g_skel_frame_buf[i].YUVDataVir = NULL;
                }
                g_skel_frame_buf[i].bUsed = AX_FALSE;
                g_skel_frame_buf[i].nFrameId = 0;
            }
        }
    }
}

AX_BOOL FrameMgrGet(AX_U64 *YUVDataPhy, AX_VOID **YUVDataVir, AX_U32 nFrameSize, AX_U64 nFrameId ,AX_BLK blkId) {
    if (!g_bSkel_frame_mgr_inited) {
        return AX_FALSE;
    }

    for (AX_U32 i = 0; i < g_skel_frame_buf.size(); i ++) {
        if (!g_skel_frame_buf[i].bUsed) {
            if (g_skel_frame_buf[i].YUVDataPhy == 0
                || !g_skel_frame_buf[i].YUVDataVir) {
                //AX_S32 nRet = AX_SYS_MemAlloc(&g_skel_frame_buf[i].YUVDataPhy, (AX_VOID **)&g_skel_frame_buf[i].YUVDataVir, nFrameSize, 256, (AX_S8 *)"SKEL_TEST");
                g_skel_frame_buf[i].YUVDataPhy = AX_POOL_Handle2PhysAddr(blkId);
                g_skel_frame_buf[i].YUVDataVir = AX_POOL_GetBlockVirAddr(blkId);

                if (g_skel_frame_buf[i].YUVDataPhy == 0
                    || !g_skel_frame_buf[i].YUVDataVir) {
                    return AX_FALSE;
                }
            }

            *YUVDataPhy = g_skel_frame_buf[i].YUVDataPhy;
            *YUVDataVir = g_skel_frame_buf[i].YUVDataVir;

            g_skel_frame_buf[i].bUsed = AX_TRUE;
            g_skel_frame_buf[i].nFrameId = nFrameId;

            return AX_TRUE;
        }
    }

    return AX_FALSE;
}

AX_VOID FrameMgrDestroy(AX_VOID) {
    if (!g_bSkel_frame_mgr_inited) {
        return;
    }

    for (AX_U32 i = 0; i < g_skel_frame_buf.size(); i ++) {
        if (g_skel_frame_buf[i].YUVDataPhy != 0
            && g_skel_frame_buf[i].YUVDataVir) {
            AX_SYS_MemFree(g_skel_frame_buf[i].YUVDataPhy, g_skel_frame_buf[i].YUVDataVir);
            g_skel_frame_buf[i].YUVDataPhy = 0;
            g_skel_frame_buf[i].YUVDataVir = NULL;
        }
        g_skel_frame_buf[i].bUsed = AX_FALSE;
        g_skel_frame_buf[i].nFrameId = 0;
    }

    g_bSkel_frame_mgr_inited = AX_FALSE;
}
