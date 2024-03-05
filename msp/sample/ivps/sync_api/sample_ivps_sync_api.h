/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_IVPS_SYNC_API_H_
#define _SAMPLE_IVPS_SYNC_API_H_

typedef enum
{
        IVPS_ENGINE_ID_TDP = 0,
        IVPS_ENGINE_ID_VPP,
        IVPS_ENGINE_ID_VGP,
        IVPS_ENGINE_ID_GDC,
        IVPS_ENGINE_ID_BUTT
} IVPS_ENGINE_ID_E;

typedef struct
{
        /* cmmcopy */
        IVPS_ENGINE_ID_E eEngineId;
	AX_U32 nMemSize;
        /* csc */
        /* flip and rotation */
        /* alphablending */
        /* crop resize */
        /* crop resize2 */
        /* crop resize3 */
        AX_U32 nOsdBlkId;
} SAMPLE_IVPS_SYNC_API_T;

typedef struct
{
	AX_U32 nOsdNum;
} SAMPLE_IVPS_OSD_T;

typedef struct
{
	AX_U32 nCoverNum;
} SAMPLE_IVPS_COVER_T;

typedef struct
{
        SAMPLE_IVPS_OSD_T tOsd;
	SAMPLE_IVPS_COVER_T tCover;
} SAMPLE_IVPS_REGION_T;

extern SAMPLE_IVPS_SYNC_API_T gSampleIvpsSyncApi;
extern SAMPLE_IVPS_REGION_T gSampleIvpsRegion;

/* Sample for drawing Line, Rect and Polygon by CPU */
AX_S32 SAMPLE_FillCanvasWithCover(const AX_IVPS_RGN_CANVAS_INFO_T *ptCanvas);
AX_S32 SAMPLE_FillFrameWithCover(const AX_VIDEO_FRAME_T *pstVFrame, const SAMPLE_IVPS_COVER_T *ptIvpsCover, char *strFilePath);

/* Csc API, it has copy function */
AX_S32 SAMPLE_IVPS_Csc(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, char *strFilePath);

/* Flip and Rotation API */
AX_S32 SAMPLE_IVPS_FlipAndRotation(const AX_VIDEO_FRAME_T *ptSrcFrame,
                                   AX_S32 nFlipCode, AX_S32 nRotation, char *strFilePath);

/* AlphaBlending API */
AX_S32 SAMPLE_IVPS_AlphaBlending(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame,
                                 AX_VIDEO_FRAME_T *ptOverlay, AX_U8 nAlpha, char *strFilePath);

/* CropResize API, 1 in 1 out */
AX_S32 SAMPLE_IVPS_CropResize(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, char *strFilePath);

/* CropResize V2 API, 1 in N(1~32) out */
AX_S32 SAMPLE_IVPS_CropResizeV2(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, char *strFilePath);

/* Mosaic API */
AX_S32 SAMPLE_IVPS_DrawMosaic(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, AX_IVPS_RGN_MOSAIC_T tMosaic[], AX_U32 nNum, char *strFilePath);

/* OSD */
AX_S32 SAMPLE_IVPS_DrawOsd(IVPS_ENGINE_ID_E eEngineId, const AX_VIDEO_FRAME_T *ptSrcFrame, AX_VIDEO_FRAME_T *ptOverlay, char *strFilePath);
#endif /* _SAMPLE_IVPS_SYNC_API_H_ */
