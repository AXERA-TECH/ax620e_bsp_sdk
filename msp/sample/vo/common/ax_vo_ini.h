/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _AX_VO_INI_H_
#define _AX_VO_INI_H_

typedef enum {
    AX_VO_INI_S_LAYER = 0,
    AX_VO_INI_S_LAYER_DISPLAY,
    AX_VO_INI_S_BUTT
} AX_VO_INI_SECTION_E;

typedef enum {
    AX_VO_INI_K_SECTION_TYPE = 0,
    AX_VO_INI_K_VO_DEVICE,

    /* channel keys */
    AX_VO_INI_K_C_VO_MODE,
    AX_VO_INI_K_C_FBDC_MODE,
    AX_VO_INI_K_C_FBDC_LEVEL,
    AX_VO_INI_K_C_FILE_NAME,
    AX_VO_INI_K_C_FRAME_FMT,
    AX_VO_INI_K_C_FRAME_RATE,
    AX_VO_INI_K_C_FRAME_NR,

    /* layer keys */
    AX_VO_INI_K_L_IMG_WIDTH,
    AX_VO_INI_K_L_IMG_HEIGHT,
    AX_VO_INI_K_L_IMG_FMT,
    AX_VO_INI_K_L_SYNC_MODE,
    AX_VO_INI_K_L_PRIMERY_CHNID,
    AX_VO_INI_K_L_FRAME_RATE,
    AX_VO_INI_K_L_FIFO_DEPTH,
    AX_VO_INI_K_L_CHNS,
    AX_VO_INI_K_L_BKCLR,
    AX_VO_INI_K_L_WB_MODE,
    AX_VO_INI_K_L_INPLACE_CHNID,
    AX_VO_INI_K_L_DISPATCH_MODE,
    AX_VO_INI_K_L_KEEP_PREV_CHNS_BITMAP0,
    AX_VO_INI_K_L_KEEP_PREV_CHNS_BITMAP1,
    AX_VO_INI_K_L_PART_MODE,
    AX_VO_INI_K_L_ENGINE_ID,
    AX_VO_INI_K_L_BIND_MODE,
    AX_VO_INI_K_L_FBC_MODE,
    AX_VO_INI_K_L_FBC_LEVEL,
    AX_VO_INI_K_L_CHN_FRAME_OUT,
    AX_VO_INI_K_L_BATCH_PROCESS,
    AX_VO_INI_K_L_BLEND_MODE,
    AX_VO_INI_K_L_MAX = AX_VO_INI_K_L_BLEND_MODE,

    /* display keys */
    AX_VO_INI_K_D_BASE,
    AX_VO_INI_K_D_WORK_MODE = AX_VO_INI_K_D_BASE,
    AX_VO_INI_K_D_INTERFACE,
    AX_VO_INI_K_D_SYNC_TYPE,
    AX_VO_INI_K_D_SYNC_USER_INDEX,
    AX_VO_INI_K_D_WBC_ENABLE,
    AX_VO_INI_K_D_WBC_TYPE,
    AX_VO_INI_K_D_WBC_MODE,
    AX_VO_INI_K_D_WBC_FRAME_RATE,
    AX_VO_INI_K_D_WBC_FRAME_NR,
    AX_VO_INI_K_D_GRAPHIC_FB_CONF,
    AX_VO_INI_K_D_CSC_MATRIX,
    AX_VO_INI_K_D_LUMA,
    AX_VO_INI_K_D_CONTRAST,
    AX_VO_INI_K_D_HUE,
    AX_VO_INI_K_D_SATUATURE,
    AX_VO_INI_K_D_CURSOR_ENABLE,
    AX_VO_INI_K_D_CURSOR_X,
    AX_VO_INI_K_D_CURSOR_Y,
    AX_VO_INI_K_D_CURSOR_WIDTH,
    AX_VO_INI_K_D_CURSOR_HEIGHT,
    AX_VO_INI_K_D_CURSOR_FBID,
    AX_VO_INI_K_D_OUT_FMT,

    AX_VO_INI_K_BUTT
} AX_VO_INI_KEY_E;

AX_S32 SAMPLE_VO_PARSE_INI(const AX_CHAR *section, AX_VO_INI_SECTION_E type, AX_VOID *pConfig, const AX_CHAR* configFile);
#endif