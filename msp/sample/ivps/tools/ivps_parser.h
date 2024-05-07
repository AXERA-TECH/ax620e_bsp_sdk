/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _IVPS_PARSER_H_
#define _IVPS_PARSER_H_
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "ini_dict.h"
#include "ini_parser.h"
#include "ivps_util.h"
#include "ivps_help.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define iniparser_getval(val, func, ini, default, tmpstr, fmt, ...) \
    {                                                               \
        sprintf(tmpstr, fmt, __VA_ARGS__);                          \
        val = func(ini, tmpstr, default);                           \
    }                                                               \
    while (0)

    void print_arr_f32(AX_F32 *arr, int ele_num, const char *arr_name);
    void print_arr_s32(AX_S32 *arr, int ele_num, const char *arr_name);
    void print_arr_u8(AX_U8 *arr, int ele_num, const char *arr_name);

    typedef struct
    {
        char *pPipelineIni;        /* --pipeline */
        char *pRegionIni;          /* --region */
        char *pChangeIni;          /* --change */
        char *pPipelineExtIni;     /* --pipeline_ext */
        char *pDewarpIni;          /* --dewarp */

        AX_S32 nRepeatCount;       /* -n */
        AX_S32 nRegionNum;         /* -r */
        AX_BOOL bRegionStop;       /* --region_stop */
        AX_S32 nStreamNum;

        AX_U8 nLinkMode;           /* -l */

        char *pFrameInfo;          /* -v */
        char *pOverlayInfo;        /* -g */
        char *pSpAlphaFileInfo;    /* -s */
        char *pSavePath;           /* --save */

        AX_U8 nEngineId;
        AX_BOOL bCmmCopy;          /* --cmmcopy */
        AX_BOOL bCsc;              /* --csc */
        AX_BOOL bFlipRotation;     /* --fliprotation */
        AX_BOOL bCropResize;       /* --cropresize */
        AX_BOOL bAlphaBlend;       /* --alphablend */
        AX_BOOL bOsd;              /* --osd */
        AX_BOOL bMosaic;           /* --mosaic */
        AX_BOOL bMask;             /* --mask */
        AX_BOOL bCropResizeV2;     /* --cropresize2 */
        AX_BOOL bCropResizeV3;     /* --cropresize3 */
        AX_BOOL bAlphaBlendV2;     /* --alphablend2 */
        AX_BOOL bAlphaBlendV3;     /* --alphablend3 */
        AX_POOL_SOURCE_E ePoolSrc; /* --pool_type */
        AX_U8 nOutChnNum;
        IVPS_GRP nIvpsGrp;
        IVPS_CHN_INFO_T tChnInfo[5];
        AX_BOOL bCropInfo;         /* --crop */
        AX_BOOL bFewPool;          /* --FewPool test */
        AX_IVPS_CROP_INFO_T tCropInfo;
        AX_BOOL bLdcAttr;          /* --ldc */
        AX_IVPS_LDC_ATTR_T tLdcAttr;
        AX_U8 nAngle; /* --angle; 0: 0 degree; 1: 90 degree; 2: 180 degree; 3: 270 degree */
        AX_U8 nFlip; /* --flip; 0: 0 no flip; 1: flip up and down; 2: mirror right and left; 3: flip&mirror */
        AX_U8 nFormat; /* --format */
    } IVPS_ARG_T;

    AX_BOOL ThreadLoopStateGet(AX_VOID);
    AX_VOID ThreadLoopStateSet(AX_BOOL bValue);

#ifdef __cplusplus
}
#endif

#endif /* _IVPS_PARSER_H_ */