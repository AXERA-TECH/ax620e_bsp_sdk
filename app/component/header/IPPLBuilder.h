/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#pragma once

#include <string>
#include "AXFrame.hpp"
#include "BaseLinkage.h"
#include "IModule.h"
#include "IObserver.h"
#include "ax_base_type.h"

#if !defined(SLT) && !defined(SLT_EX)
#include "WebServer.h"
#endif

typedef enum { E_PPL_TYPE_IPC = 0, E_PPL_TYPE_PANO, E_PPL_TYPE_MAX } PPL_TYPE_E;

typedef enum {
    E_APP_SCENARIO_DUAL_SENSOR = 0,                      /* Dual sensor */
    E_APP_SCENARIO_DEFAULT = E_APP_SCENARIO_DUAL_SENSOR, /* Default */
    E_APP_SCENARIO_SINGLE = 1,                           /* Single sensor */
    E_APP_SCENARIO_DUAL_WITH_VO = 2,                     /* Dual sensor with vo*/
    E_APP_SCENARIO_SINGLE_WITH_VO = 3,                   /* Single sensor with vo*/
    E_APP_SCENARIO_SLT = 99,                             /* Similar to default scenario while without Web/RTSP */
    E_APP_SCENARIO_MAX
} AX_APP_SCENARIO_E;

typedef enum {
    E_WEB_REQ_INFO_TYPE_CAMERA = 0,
    E_WEB_REQ_INFO_TYPE_FPS_OPTION,
    E_WEB_REQ_INFO_TYPE_VIDEO,
    E_WEB_REQ_INFO_TYPE_MAX
} WEB_REQ_INFO_TYPE_E;

typedef struct _IPC_MOD_RELATIONSHIP_T {
    AX_U32 nIndex;
    IPC_MOD_INFO_T tSrcModChn;
    IPC_MOD_INFO_T tDstModChn;
    AX_BOOL bLink;

    _IPC_MOD_RELATIONSHIP_T() {
        memset(this, 0, sizeof(_IPC_MOD_RELATIONSHIP_T));
        tSrcModChn.eModType = E_PPL_MOD_TYPE_MAX;
        tDstModChn.eModType = E_PPL_MOD_TYPE_MAX;
    }

    AX_BOOL Valid() const {
        return (tSrcModChn.eModType != E_PPL_MOD_TYPE_MAX && tDstModChn.eModType != E_PPL_MOD_TYPE_MAX) ? AX_TRUE : AX_FALSE;
    }
} IPC_MOD_RELATIONSHIP_T, PPL_MOD_RELATIONSHIP_T;

class IPPLBuilder {
public:
    virtual ~IPPLBuilder(AX_VOID) = default;

    virtual AX_BOOL Init(AX_VOID) = 0;
    virtual AX_BOOL Deinit(AX_VOID) = 0;

    virtual AX_BOOL Construct(AX_VOID) = 0;
    virtual AX_BOOL Destroy(AX_VOID) = 0;
    virtual AX_BOOL Start(AX_VOID) = 0;
    virtual AX_BOOL Stop(AX_VOID) = 0;

#if !defined(SLT) && !defined(SLT_EX)
    /* Web relative interfaces */
    virtual AX_BOOL ProcessWebOprs(WEB_REQUEST_TYPE_E eReqType, const AX_VOID* pJsonReq, AX_VOID** pResult = nullptr) = 0;
    virtual AX_BOOL ProcessTestSuiteOpers(WEB_REQ_OPERATION_T& tOperation) = 0;

#endif
};
