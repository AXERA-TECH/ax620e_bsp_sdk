#ifndef __FONTINDEX_H__
#define __FONTINDEX_H__
#include "FontDefine.h"

#ifndef FONT_USE_FREETYPE
AX_S32 GetFontBitmap(AX_U16 nUnicode, FONT_BITMAP_T &bmp);
#endif
AX_S32 OsdCalcStrSize(wchar_t *pStr, AX_U32 nFontSize, AX_U32 &nWidth, AX_U32 &nHeight);

#endif  // __FONTINDEX_H__
