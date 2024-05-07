/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "OptionHelper.h"
#include "CommonUtils.hpp"

#define AX_WEB_VENC_FRM_SIZE_RATIO (0.5)
#define AX_WEB_JENC_FRM_SIZE_RATIO (0.05)
#define AX_WEB_AENC_FRM_SIZE (8192)
#define AX_WEB_VENC_RING_BUFF_COUNT (5)
#define AX_WEB_JENC_RING_BUFF_COUNT (10)
#define AX_WEB_MJENC_RING_BUFF_COUNT (10)
#define AX_WEB_EVENTS_RING_BUFF_COUNT (5)
#define AX_WEB_AENC_RING_BUFF_COUNT (5)
#define AX_WEB_SNAPSHOT_QP_LEVEL (63)

#define AX_RTSP_FRM_SIZE (700000)
#define AX_RTSP_RING_BUFF_COUNT (2)

#define AX_VENC_THREAD_NUM (2)

AX_BOOL COptionHelper::InitOnce() {
#ifndef _OPAL_LIB_
    string strConfigDir = CCommonUtils::GetPPLConfigDir();
    if (strConfigDir.empty()) {
        return AX_FALSE;
    }

    string strConfigFile = strConfigDir + "/options.ini";

    return m_iniWrapper.Load(strConfigFile);
#else
    return AX_TRUE;
#endif
}

AX_F32 COptionHelper::GetJencOutBuffRatio() {
#ifndef _OPAL_LIB_
    AX_F32 value = (AX_F32)m_iniWrapper.GetDoubleValue("options", "WebJencFrmSizeRatio", AX_WEB_JENC_FRM_SIZE_RATIO);
    return value;
#else
    return AX_WEB_JENC_FRM_SIZE_RATIO;
#endif
}

AX_U32 COptionHelper::GetAencOutFrmSize() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "WebAencFrmSize", AX_WEB_AENC_FRM_SIZE);
    return value;
#else
    return AX_WEB_AENC_FRM_SIZE;
#endif
}

AX_U32 COptionHelper::GetWebJencRingBufCount() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "WebJencRingBufCount", AX_WEB_JENC_RING_BUFF_COUNT);
    return value;
#else
    return AX_WEB_JENC_RING_BUFF_COUNT;
#endif
}

AX_U32 COptionHelper::GetWebMjencRingBufCount() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "WebMjencRingBufCount", AX_WEB_MJENC_RING_BUFF_COUNT);
    return value;
#else
    return AX_WEB_MJENC_RING_BUFF_COUNT;
#endif
}

AX_U32 COptionHelper::GetWebEventsRingBufCount() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "WebEventsRingBufCount", AX_WEB_EVENTS_RING_BUFF_COUNT);
    return value;
#else
    return AX_WEB_EVENTS_RING_BUFF_COUNT;
#endif
}

AX_U32 COptionHelper::GetWebAencRingBufCount() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "WebAencRingBufCount", AX_WEB_AENC_RING_BUFF_COUNT);
    return value;
#else
    return AX_WEB_AENC_RING_BUFF_COUNT;
#endif
}

AX_U32 COptionHelper::GetRTSPMaxFrmSize() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "RTSPMaxFrmSize", AX_RTSP_FRM_SIZE);
    return value;
#else
    return AX_RTSP_FRM_SIZE;
#endif
}

AX_U32 COptionHelper::GetRTSPRingBufCount() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "RTSPRingBufCount", AX_RTSP_RING_BUFF_COUNT);
    return value;
#else
    return AX_RTSP_RING_BUFF_COUNT;
#endif
}

AX_U32 COptionHelper::GetSnapShotQpLevel() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "WebSnapShotQpLevel", AX_WEB_SNAPSHOT_QP_LEVEL);
    return value;
#else
    return AX_WEB_SNAPSHOT_QP_LEVEL;
#endif
}

AX_BOOL COptionHelper::IsEnableOSD() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "EnableOSD", 0);
    return value ? AX_TRUE : AX_FALSE;
#else
    return AX_TRUE;
#endif
}

AX_BOOL COptionHelper::IsEnableMp4Record() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "EnableMp4Record", 0);
    return value ? AX_TRUE : AX_FALSE;
#else
    return AX_FALSE;
#endif
}

string COptionHelper::GetMp4SavedPath() {
#ifndef _OPAL_LIB_
    string strVal = m_iniWrapper.GetStringValue("options", "MP4RecordSavedPath", "./");
    return strVal;

#else
    return "./";
#endif
}

AX_U32 COptionHelper::GetVencThreadNum() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("venc", "VencThreadNum", AX_VENC_THREAD_NUM);
    return value;
#else
    return AX_VENC_THREAD_NUM;
#endif
}

AX_BOOL COptionHelper::IsEnableVencDebreath() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("venc", "EnableDebreathEffect", 0);
    return value ? AX_TRUE : AX_FALSE;
#else
    return AX_FALSE;
#endif
}

AX_BOOL COptionHelper::IsEnableVencRefRingbuf() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("venc", "EnableRefRingbuf", 0);
    return value ? AX_TRUE : AX_FALSE;
#else
    return AX_FALSE;
#endif
}

AX_U32 COptionHelper::GetSLTRunTime() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("slt", "RunTime", 0);
    return value;
#else
    return 0;
#endif
}

AX_U32 COptionHelper::GetSLTFpsCheckFreq() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("slt", "FPSCheckFreq", 0);
    return value;
#else
    return 0;
#endif
}

AX_U32 COptionHelper::GetSLTFpsDiff() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("slt", "FPSDiff", 0);
    return value;
#else
    return 0;
#endif
}

AX_BOOL COptionHelper::GetInterpolationResolution(AX_U32 &nWidth, AX_U32 &nHeight) {
#ifndef _OPAL_LIB_
    string strVal = m_iniWrapper.GetStringValue("options", "InterpolationResolution", "");
    if (!strVal.empty()) {
        nWidth = 0;
        nHeight = 0;

        sscanf(&strVal[0], "%dx%d", &nWidth, &nHeight);

        if (0 < nWidth && 0 < nHeight) {
            return AX_TRUE;
        }

        return AX_FALSE;
    }

    return AX_FALSE;
#else
    nWidth = m_InterpolationResolutionWidth;
    nHeight = m_InterpolationResolutionHeight;

    return AX_TRUE;
#endif
}

AX_BOOL COptionHelper::SetInterpolationResolution(const AX_U32 &nWidth, const AX_U32 &nHeight) {
#ifndef _OPAL_LIB_
    return AX_TRUE;
#else
    m_InterpolationResolutionWidth = nWidth;
    m_InterpolationResolutionHeight = nHeight;

    return AX_TRUE;
#endif
}

AX_BOOL COptionHelper::GetSnsHnbTestMode() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("sns", "HotNoiseBalanceTestMode", 0);
    return value ? AX_TRUE : AX_FALSE;
#else
    return AX_FALSE;
#endif
}

AX_BOOL COptionHelper::GetSnsHnbPrintTemperature() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("sns", "HotNoiseBalancePrintTemperature", 0);
    return value ? AX_TRUE : AX_FALSE;
#else
    return AX_FALSE;
#endif
}

AX_BOOL COptionHelper::IsEnableWebServerStatusCheck() {
#ifndef _OPAL_LIB_
    AX_U32 value = (AX_U32)m_iniWrapper.GetIntValue("options", "WebServerStatusCheck", 0);
    return value ? AX_TRUE : AX_FALSE;
#else
    return AX_FALSE;
#endif
}

AX_U32 COptionHelper::GetWebVencRingBufSize(AX_U32 width, AX_U32 height) {
    AX_U32 nSize =0;
#ifndef _OPAL_LIB_
    static AX_F64 nRatio = m_iniWrapper.GetDoubleValue("vencRingBuffer", "defaultRatio", AX_WEB_VENC_FRM_SIZE_RATIO);
    AX_CHAR resolution[16];
    sprintf(resolution, "%dx%d", width, height);
    vector<AX_S32> vecVal;
    m_iniWrapper.GetIntValue("vencRingBuffer", (string)resolution, vecVal);
    if(vecVal.size() != 2) {
        nSize = width * height * 3 / 2 * nRatio;
    } else {
        nSize = vecVal[1];
    }
#else
    nSize = width * height * 3 / 2 * AX_WEB_VENC_FRM_SIZE_RATIO;
#endif
    return nSize;
}

AX_U32 COptionHelper::GetWebVencRingBufCount(AX_U32 width, AX_U32 height) {
    AX_U32 nCount = AX_WEB_VENC_RING_BUFF_COUNT;
#ifndef _OPAL_LIB_
    AX_CHAR resolution[16];
    sprintf(resolution, "%dx%d", width, height);
    vector<AX_S32> vecVal;
    m_iniWrapper.GetIntValue("vencRingBuffer", (string)resolution, vecVal);
    if(vecVal.size() == 2) {
        nCount =  vecVal[0];
    } else {
        nCount = (AX_U32)m_iniWrapper.GetIntValue("vencRingBuffer", "defaultCount", AX_WEB_VENC_RING_BUFF_COUNT);
    }

#endif
    return nCount;
}
