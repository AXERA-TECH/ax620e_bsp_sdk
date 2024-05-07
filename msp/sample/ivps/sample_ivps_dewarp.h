/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _SAMPLE_IVPS_DEWARP_H_
#define _SAMPLE_IVPS_DEWARP_H_
#include "ivps_parser.h"

typedef enum
{
	SAMPLE_IVPS_DEWARP_NONE,
	SAMPLE_IVPS_DEWARP_GDC,
	SAMPLE_IVPS_DEWARP_SYNC,
} SAMPLE_IVPS_DEWARP_TYPE;

typedef struct
{
	SAMPLE_IVPS_DEWARP_TYPE eSampleType;

	AX_U16 nSrcWidth;
	AX_U16 nSrcHeight;
	AX_U16 nDstWidth;
	AX_U16 nDstHeight;
	int nRepeatNum;
	int nHandle;
	char *pMeshFile;
	char *pFilePath;
	AX_VIDEO_FRAME_T tFrame;

	AX_IVPS_DEWARP_ATTR_T tDewarpAttr; /* common, perspective */
	AX_IVPS_GDC_ATTR_T tGdcAttr; /* fisheye, usermap */
} SAMPLE_IVPS_DEWARP_T;

#endif /* _SAMPLE_IVPS_DEWARP_H_ */
