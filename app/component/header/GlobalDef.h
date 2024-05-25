/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#pragma once
#include "ax_global_type.h"
#include "ax_os_mem_api.h"

#ifdef AX_MEM_CHECK
#include <mcheck.h>
#define AX_MTRACE_ENTER(name)                                  \
    do {                                                       \
        if (!getenv("MALLOC_TRACE")) {                         \
            setenv("MALLOC_TRACE", "" #name "_mtrace.log", 1); \
        }                                                      \
        mtrace();                                              \
    } while (0)

#define AX_MTRACE_LEAVE                                      \
    do {                                                     \
        printf("please wait mtrace flush log to file...\n"); \
        sleep(30);                                           \
    } while (0)

#else
#define AX_MTRACE_ENTER(name)
#define AX_MTRACE_LEAVE
#endif

#define SDK_VERSION_PREFIX "Ax_Version"

#ifndef AX_MALLOC
#define AX_MALLOC(s) AX_OS_MEM_Malloc(AX_ID_USER, s)
#endif

#ifndef AX_CALLOC
#define AX_CALLOC(n, s) AX_OS_MEM_Calloc(AX_ID_USER, n, s)
#endif

#ifndef AX_FREE
#define AX_FREE(p)                              \
    do {                                        \
        if (p) {                                \
            AX_OS_MEM_Free(AX_ID_USER, p);      \
            p = nullptr;                        \
        }                                       \
    } while (0)
#endif

#ifndef AX_MAX
#define AX_MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef AX_MIN
#define AX_MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef ALIGN_UP
#define ALIGN_UP(x, align) (((x) + ((align)-1)) & ~((align)-1))
#endif

#ifndef ALIGN_DOWN
#define ALIGN_DOWN(x, align) ((x) & ~((align)-1))
#endif

#ifndef ALIGN_COMM_UP
#define ALIGN_COMM_UP(x, align) ((((x) + ((align)-1)) / (align)) * (align))
#endif

#ifndef ALIGN_COMM_DOWN
#define ALIGN_COMM_DOWN(x, align) (((x) / (align)) * (align))
#endif

#ifndef ADAPTER_RANGE
#define ADAPTER_RANGE(v, min, max) ((v) < (min)) ? (min) : ((v) > (max)) ? (max) : (v)
#endif

#ifndef AX_BIT_CHECK
#define AX_BIT_CHECK(v, b) (((AX_U32)(v) & (1 << (b))))
#endif

#ifndef AX_BIT_SET
#define AX_BIT_SET(v, b) ((v) |= (1 << (b)))
#endif

#ifndef AX_BIT_CLEAR
#define AX_BIT_CLEAR(v, b) ((v) &= ~(1 << (b)))
#endif

#ifndef AX_ABS
#define AX_ABS(a) (((a) < 0) ? -(a) : (a))
#endif

#ifndef AX_MASK
#define AX_MASK(width) ((1 << (width)) - 1) /* 2^w - 1 */
#endif

#define SAFE_DELETE_PTR(p) \
    do {                   \
        if (p) {           \
            delete p;      \
            p = nullptr;   \
        }                  \
    } while (0)

#define SAFE_DELETE_ARRAY_PTR(p) \
    do {                         \
        if (p) {                 \
            delete[] p;          \
            p = nullptr;         \
        }                        \
    } while (0)

#ifndef AX_DLOPEN
#define AX_DLOPEN(_HANDLE_, _SO_NAME_) _HANDLE_ = dlopen(_SO_NAME_, RTLD_LAZY)
#endif

#ifndef AX_DLCLOSE
#define AX_DLCLOSE(_HANDLE_) \
                do { \
                    if (_HANDLE_) { \
                        dlclose(_HANDLE_); \
                        _HANDLE_ = nullptr; \
                    } \
                } while(0)
#endif

#ifndef AX_DLAPI
#define AX_DLAPI(_API_NAME_) m_pApi_##_API_NAME_
#endif

#ifndef AX_DLAPI_DEF
#define AX_DLAPI_DEF(_API_NAME_, _API_RET_, _API_PARAM_) \
                _API_RET_ (* AX_DLAPI(_API_NAME_))_API_PARAM_ = nullptr
#endif

#ifndef AX_DLAPI_LOAD
#define AX_DLAPI_LOAD(_HANDLE_, _API_NAME_, _API_RET_, _API_PARAM_) \
                do { \
                    if (_HANDLE_) { \
                        AX_DLAPI(_API_NAME_) = (_API_RET_ (*)_API_PARAM_)dlsym(_HANDLE_, #_API_NAME_); \
                    } \
                } while (0)
#endif

#ifndef AX_DLVAR_LOAD
#define AX_DLVAR_LOAD(_VAR_OBJ_, _HANDLE_, _VAR_NAME_, _VAR_TYPE_) \
                do { \
                    if (_HANDLE_) { \
                        _VAR_OBJ_ = (_VAR_TYPE_ (*))dlsym(_HANDLE_, _VAR_NAME_); \
                    } \
                } while (0)
#endif

#define AX_VIN_FBC_STRIDE_ALIGN_VAL (128)
#define AX_VIN_NONE_FBC_STRIDE_ALIGN_VAL (2)
#define AX_IVPS_FBC_STRIDE_ALIGN_VAL (128)
#define AX_IVPS_NONE_FBC_STRIDE_ALIGN_VAL (16)
#define AX_ENCODER_FBC_STRIDE_ALIGN_VAL (128)
#define AX_ENCODER_NONE_FBC_STRIDE_ALIGN_VAL (16)

// MAX VIN/IVPS/VENC FBC STRIDE
#define AX_YUV_FBC_STRIDE_ALIGN_VAL (128)

// MAX VIN/IVPS/VENC NONE FBC STRIDE
#define AX_YUV_NONE_FBC_STRIDE_ALIGN_VAL (16)

#define AX_SHIFT_LEFT_ALIGN(a) (1 << (a))

/* VDEC stride align 256 */
#define VDEC_STRIDE_ALIGN AX_SHIFT_LEFT_ALIGN(8)

#define ADAPTER_INT2BOOLSTR(val) (val == 1 ? "true" : "false")
#define ADAPTER_INT2BOOL(val) (val == 1 ? AX_TRUE : AX_FALSE)
#define ADAPTER_BOOL2BOOLSTR(val) (val == AX_TRUE ? "true" : "false")
#define ADAPTER_BOOLSTR2INT(val) (strcmp(val, "true") == 0 ? 1 : 0)

#define AX_APP_LOCKQ_CAPACITY (2)

#define AX_EZOOM_MAX  32

#define WEB_SET_BOOL(var, obj, key)  do{\
    if(!obj) return AX_FALSE;\
    cchar *pStr = mprReadJson(obj, key);\
    if (pStr) {\
        var = strcmp(pStr, "true") == 0 ? AX_TRUE : AX_FALSE;\
    } else {\
        return AX_FALSE;\
    }\
}while(0)

#define WEB_SET_INT(var, obj, key)  do{\
    if(!obj) return AX_FALSE;\
    cchar *pStr = mprReadJson(obj, key);\
    if (pStr) {\
        var = atoi(pStr);\
    } else {\
        return AX_FALSE;\
    }\
}while(0)

#define WEB_SET_INT_OBJ(var, obj)  do{\
    if(!obj) return AX_FALSE;\
    cchar *pStr = obj->value;\
    if (pStr) {\
        var = atoi(pStr);\
    } else {\
        return AX_FALSE;\
    }\
}while(0)

#define WEB_SET_HEX(var, obj, key)  do{\
    if(!obj) return AX_FALSE;\
    cchar *pStr = mprReadJson(obj, key);\
    char *pEnd = NULL;\
    if (pStr) {\
        var = strtol(pStr, &pEnd, 16);\
    } else {\
        return AX_FALSE;\
    }\
}while(0)

#define WRITE_JSON_STR(obj, key, value)  \
    mprWriteJson(obj, key, value.c_str(), MPR_JSON_STRING)

#define WRITE_JSON_PSTR(obj, key, value)  \
    mprWriteJson(obj, key, value, MPR_JSON_STRING)

#define WRITE_JSON_INT(obj, key, value)  \
    mprWriteJson(obj, key, std::to_string(value).c_str(), MPR_JSON_NUMBER)

#define WRITE_JSON_BOOL(obj, key, value)  { \
    const char* str = value ? "true" : "false";\
    AX_S32 type = value ? MPR_JSON_TRUE : MPR_JSON_FALSE;\
    mprWriteJson(obj, key, str, type);\
}

#define WRITE_JSON_OBJ(obj, key, value)  \
    mprWriteJsonObj(obj, key, value)\

#define WRITE_JSON_HEX(obj, key, format, value)  { \
    AX_CHAR buffer[32] = {0};\
    sprintf(buffer, format, value);\
    mprWriteJson(obj, key, buffer, MPR_JSON_STRING);\
}

#define APPEND_JSON_OBJ(obj, value)  \
    AppenJsonChild(obj, value)

#define APPEND_JSON_STR(obj, value)  \
    AppenJsonChild(obj, mprCreateJsonValue(value.c_str(), MPR_JSON_STRING))

#define APPEND_JSON_INT(obj, value)  {\
    AppenJsonChild(obj, mprCreateJsonValue(std::to_string(value).c_str(), MPR_JSON_NUMBER));\
}

#define APPEND_JSON_2_INT(obj, value1, value2)  \
    AppenJsonChild(obj, mprCreateJsonValue(std::to_string(value1).c_str(), MPR_JSON_NUMBER));\
    AppenJsonChild(obj, mprCreateJsonValue(std::to_string(value2).c_str(), MPR_JSON_NUMBER))
