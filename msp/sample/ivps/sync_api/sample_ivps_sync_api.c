/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include "sample_ivps_main.h"

SAMPLE_IVPS_SYNC_API_T gSampleIvpsSyncApi = {

};

SAMPLE_IVPS_REGION_T gSampleIvpsRegion = {

};

AX_S32 SAMPLE_IVPS_SyncApi(const IVPS_ARG_T *ptArg, const SAMPLE_IVPS_GRP_T *pGrp, SAMPLE_IVPS_SYNC_API_T *ptSyncIntf)
{
    AX_S32 ret;
    AX_VIDEO_FRAME_T tOverlay = {0};

    if (ptArg->bCsc)
    {
        ret = SAMPLE_IVPS_Csc(ptArg->nEngineId, &pGrp->tFrameInput, pGrp->pFilePath);
        if (ret)
        {
            ALOGE("SAMPLE_IVPS_Csc failed, ret=0x%x.", ret);
            goto error1;
        }
    }

    if (ptArg->bFlipRotation)
    {
        ret = SAMPLE_IVPS_FlipAndRotation(&pGrp->tFrameInput, 1, AX_IVPS_ROTATION_90, pGrp->pFilePath);
        if (ret)
        {
            ALOGE("SAMPLE_IVPS_FlipAndRotation failed, ret=0x%x.", ret);
            goto error1;
        }
    }

    if (ptArg->bAlphaBlend && ptArg->pOverlayInfo)
    {
        char *pOverlayFile = FrameInfoGet(ptArg->pOverlayInfo, &tOverlay);
        ptSyncIntf->nOsdBlkId = tOverlay.u32BlkId[0];
        FrameBufGet(0, &tOverlay, pOverlayFile);
        ret = SAMPLE_IVPS_AlphaBlending(ptArg->nEngineId, &pGrp->tFrameInput, &tOverlay, 128, pGrp->pFilePath);
        if (ret)
        {
            ALOGE("SAMPLE_IVPS_AlphaBlending failed, ret=0x%x.", ret);
            goto error1;
        }
    }
    if (ptArg->bCropResize)
    {
        ret = SAMPLE_IVPS_CropResize(ptArg->nEngineId, &pGrp->tFrameInput, pGrp->pFilePath);
        if (ret)
        {
            ALOGE("SAMPLE_IVPS_CropResize failed, ret=0x%x", ret);
            goto error1;
        }
    }
    if (ptArg->bCropResizeV2)
    {
        ret = SAMPLE_IVPS_CropResizeV2(ptArg->nEngineId, &pGrp->tFrameInput, pGrp->pFilePath);
        if (ret)
        {
            ALOGE("SAMPLE_IVPS_CropResizeV2 failed, ret=0x%x", ret);
            goto error1;
        }
    }
    if (ptArg->bMosaic)
    {
        AX_IVPS_RGN_MOSAIC_T tMosaic[32] = {
            {
                .tRect = {
                    .nX = 0,
                    .nY = 0,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 30,
                    .nY = 30,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 60,
                    .nY = 60,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 90,
                    .nY = 90,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 120,
                    .nY = 120,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 150,
                    .nY = 150,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 180,
                    .nY = 180,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 210,
                    .nY = 210,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },

            {
                .tRect = {
                    .nX = 240,
                    .nY = 240,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 270,
                    .nY = 270,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 300,
                    .nY = 300,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 330,
                    .nY = 330,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 360,
                    .nY = 360,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 390,
                    .nY = 390,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 420,
                    .nY = 420,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 450,
                    .nY = 450,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },

            {
                .tRect = {
                    .nX = 480,
                    .nY = 480,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 510,
                    .nY = 510,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 540,
                    .nY = 540,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 570,
                    .nY = 570,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 600,
                    .nY = 600,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 630,
                    .nY = 630,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 660,
                    .nY = 660,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 690,
                    .nY = 690,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },

            {
                .tRect = {
                    .nX = 720,
                    .nY = 720,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 750,
                    .nY = 750,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 780,
                    .nY = 780,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 810,
                    .nY = 810,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 840,
                    .nY = 840,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 870,
                    .nY = 870,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 900,
                    .nY = 900,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
            {
                .tRect = {
                    .nX = 930,
                    .nY = 930,
                    .nW = 30,
                    .nH = 30,
                },
                .eBklSize = AX_IVPS_MOSAIC_BLK_SIZE_64,
            },
        };
        ret = SAMPLE_IVPS_DrawMosaic(ptArg->nEngineId, &pGrp->tFrameInput, tMosaic, 32, pGrp->pFilePath);
        if (ret)
        {
            ALOGE("SAMPLE_IVPS_DrawMosaic failed, ret=0x%x.", ret);
            goto error1;
        }
    }

    if (ptArg->bOsd && ptArg->pOverlayInfo)
    {
        /* get overlay info */
        char *pOverlayFile = FrameInfoGet(ptArg->pOverlayInfo, &tOverlay);
        FrameBufGet(0, &tOverlay, pOverlayFile);
        ret = SAMPLE_IVPS_DrawOsd(ptArg->nEngineId, &pGrp->tFrameInput, &tOverlay, pGrp->pFilePath);
        if (ret)
        {
            ALOGE("SAMPLE_IVPS_DrawOsd failed, ret=0x%x", ret);
            goto error1;
        }
    }
    return 0;
error1:
    if (tOverlay.u32BlkId[0])
    {
        ret = AX_POOL_ReleaseBlock(tOverlay.u32BlkId[0]);
        if (ret)
        {
            ALOGE("IVPS Release Overlay BlkId fail, ret=0x%x", ret);
        }
    }
    return ret;
}

AX_S32 SAMPLE_IVPS_SyncApiRegion(const IVPS_ARG_T *ptArg, const SAMPLE_IVPS_GRP_T *pGrp,
                                 const SAMPLE_IVPS_REGION_T *ptRegion)
{
    SAMPLE_FillFrameWithCover(&pGrp->tFrameInput, &ptRegion->tCover, pGrp->pFilePath);
    return 0;
}