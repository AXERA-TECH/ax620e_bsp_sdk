/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef FONT_USE_FREETYPE
#include "FontEn16.h"
#include "FontZh16.h"
#endif

#include "FontIndex.h"
#include <stdio.h>
#include <wchar.h>

#ifndef FONT_USE_FREETYPE
AX_U16 GetZhGlyphIndex(AX_U16 nUnicode) {
    AX_U32 nCount = sizeof(g_fontZh16Index) / sizeof(g_fontZh16Index[0]);
    for (AX_U32 i = 0; i < nCount; i++) {
        if (g_fontZh16Index[i].nUnicode == nUnicode) {
            return g_fontZh16Index[i].nIndex;
        }
    }
    return 0;
}

AX_U16 GetEnGlyphIndex(AX_U16 nUnicode) {
    AX_U32 nCount = sizeof(g_fontEn16Index) / sizeof(g_fontEn16Index[0]);
    for (AX_U32 i = 0; i < nCount; i++) {
        if (g_fontEn16Index[i].nUnicode == nUnicode) {
            return g_fontEn16Index[i].nIndex;
        } else if (g_fontEn16Index[i].nUnicode > nUnicode) {
            break;
        }
    }

    return 0;
}

AX_S32 GetFontBitmap(AX_U16 nUnicode, FONT_BITMAP_T &bmp) {
    if (nUnicode <= 0x7F) {
        AX_U16 nInd = GetEnGlyphIndex(nUnicode);
        bmp.nWidth = 8;
        bmp.nHeight = 16;
        bmp.pBuffer = (AX_U8 *)(g_fontEn16Glyphs + (bmp.nWidth / 8 * bmp.nHeight) * nInd);
    } else {
        AX_U16 nInd = GetZhGlyphIndex(nUnicode);
        bmp.nWidth = 16;
        bmp.nHeight = 16;
        bmp.pBuffer = (AX_U8 *)(g_fontZh16Glyphs + (bmp.nWidth / 8 * bmp.nHeight) * nInd);
    }

    return 0;
}
#endif

AX_S32 OsdCalcStrSize(wchar_t *pStr, AX_U32 nFontSize, AX_U32 &nWidth, AX_U32 &nHeight) {
    AX_S32 nScale = nFontSize / 16;
    if(pStr == NULL || nScale < 1) {
        return 0;
    }

    AX_S32 nCount = wcslen(pStr);
    if (nCount <= 0) {
        return 0;
    }

    AX_S32 nEnCount = 0;
    AX_S32 nGBCount = 0;
    for (AX_S32 i = 0; i < nCount; i++) {
        if (pStr[i] <= 0x7F) {
            nEnCount ++;
        } else {
            nGBCount ++;
        }
    }
    nWidth = (nEnCount * 8 + nGBCount*16) * nScale;
    nHeight = 16 * nScale;
    return nWidth*nHeight;
}

/*
#define FONT_IS_GB2312(a, b)        ((a) >= 0xA1 && (a) <= 0xF7 && (b) >= 0xA1 && (b) <= 0xFE)
#define HZ16_INDEX(C1, C2)         ((((C1)&0xFF)-0xA1)*94 + (((C2)&0xFF)-0xA1))

AX_S32 GenGB2312UnicodeGlyfIndex() {

    AX_S32 nCount = sizeof(g_fontZh16Index) / sizeof(g_fontZh16Index[0]);
    AX_S32 nGBCount = 0;
    UICODE_INDEX_T * gbGlyph = new UICODE_INDEX_T[nCount];
    for (int i = 0; i < nCount; i++) {
        AX_U16 nGB = g_fontZh16Index[i].nIndex;
        AX_U8* szGB = (AX_U8 *)&nGB;
        if ( FONT_IS_GB2312(szGB[1], szGB[0]) ) {
            AX_U16 nIndex = HZ16_INDEX(szGB[1], szGB[0]);
            gbGlyph[nGBCount].nUnicode = g_fontZh16Index[i].nUnicode;
            gbGlyph[nGBCount].nIndex = nIndex;
            nGBCount ++;
        }
    }

    printf("total gb glyph = %d\n",nGBCount);

    for (int i = 0; i < nGBCount/8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("{0x%04x,0x%04x},",gbGlyph[i*8+j].nUnicode, gbGlyph[i*8+j].nIndex);
        }
        printf("\n");
    }

    for (int j = 0; j < nGBCount%8; j++) {
        printf("{0x%04x,0x%04x},",gbGlyph[(nGBCount%8)*8 + j].nUnicode, gbGlyph[(nGBCount%8)*8 + j].nIndex);
    }
    printf("\n");
    return 0;
}
*/