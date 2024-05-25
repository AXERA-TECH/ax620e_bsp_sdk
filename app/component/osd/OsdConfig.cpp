/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "OsdConfig.h"

/* must be ordered as nMagic */
const static OSD_FONT_STYLE g_arrOsdStyle[] = {
    {3840 * 2160, 128, 4, 56}, {3072 * 2048, 128, 4, 56}, {3072 * 1728, 128, 4, 48}, {2624 * 1944, 96, 4, 48}, {2688 * 1520, 96, 4, 48},
    {2048 * 1536, 96, 4, 48},  {2304 * 1296, 96, 4, 48},  {1920 * 1080, 48, 2, 24},  {1280 * 720, 48, 2, 20},  {1024 * 768, 32, 2, 16},
    {720 * 576, 32, 2, 12},    {704 * 576, 32, 2, 12},    {640 * 480, 16, 2, 8},     {384 * 288, 16, 2, 2}};

AX_BOOL COSDStyle::InitOnce() {
    return AX_TRUE;
}

AX_U32 COSDStyle::GetTimeFontSize(AX_U32 nWidth, AX_U32 nHeight) {
    AX_U32 nIndex = GetOsdStyleIndex(nWidth, nHeight);
    return g_arrOsdStyle[nIndex].nTimeFontSize;
}

AX_U32 COSDStyle::GetRectLineWidth(AX_U32 nWidth, AX_U32 nHeight) {
    AX_U32 nIndex = GetOsdStyleIndex(nWidth, nHeight);
    return g_arrOsdStyle[nIndex].nRectLineWidth;
}

AX_U32 COSDStyle::GetBoundaryX(AX_U32 nWidth, AX_U32 nHeight) {
    AX_U32 nIndex = GetOsdStyleIndex(nWidth, nHeight);
    return g_arrOsdStyle[nIndex].nBoundaryX;
}

AX_U32 COSDStyle::GetOsdStyleIndex(AX_U32 nWidth, AX_U32 nHeight) {
    AX_U32 nMagic = nWidth * nHeight;
    AX_U32 nCount = sizeof(g_arrOsdStyle) / sizeof(g_arrOsdStyle[0]);
    for (AX_U32 i = 0; i < nCount; i++) {
        if (nMagic >= g_arrOsdStyle[i].nMagic) {
            return i;
        }
    }
    return nCount - 1;
}
