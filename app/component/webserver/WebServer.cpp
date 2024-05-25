/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include "WebServer.h"
#include <sys/prctl.h>
#include <map>
#include "AudioOptionHelper.h"
#include "AudioWrapper.hpp"
#include "CommonUtils.hpp"
#include "ElapsedTimer.hpp"
#include "IModule.h"
#include "IPPLBuilder.h"
#include "OptionHelper.h"
#include "SensorOptionHelper.h"
#include "WebOptionHelper.h"
#include "appweb.h"
#include "arraysize.h"
#include "http.h"
#define WEB "WEB SERVER"
#define JSON2INT(val) picojson::value(double(val))
#define JSON2BOOL(val) picojson::value(bool(val))
#define JSON2STRING(val) picojson::value(std::string(val))

#define RESPONSE_STATUS_OK "200"
#define RESPONSE_STATUS_AUTH_FAIL "401"
#define RESPONSE_STATUS_INVALID_REQ "400"
#define RESPONSE_STATUS_OK_CODE 200
#define RESPONSE_STATUS_FAILURE_CODE 406
#define PARAM_KEY_PREVIEW_SNS_SRC "src_id"
#define PARAM_KEY_PREVIEW_CHANNEL "stream"
#define PARAM_KEY_APP_NAME "appName"
#define PARAM_KEY_APP_VERSION "appVersion"
#define PARAM_KEY_SDK_VERSION "sdkVersion"
#define PARAM_KEY_SETTING_CAPABILITY "capInfo"
#define PARAM_KEY_SNS_MODE "snsMode"
using namespace std;

extern string g_SDKVersion;

static AX_BOOL g_web_mem_limit_notified = AX_FALSE;
static MprList* g_pClients = nullptr;
std::mutex g_mtxWSData;
std::mutex g_mtxWebOprProcess;
static std::map<AX_U8, std::map<AX_U8, std::pair<AX_U8, AX_U8>>> m_sMapPrevChn2UniChn; /* {SnsID: {PrevID: (UniChn, CodecType)}} */
static std::map<AX_U8, AX_U8> g_mapSns2CurrPrevChn;
static std::map<string, string> g_mapUserInfo;
static std::map<string, string> g_mapUser2Token;
static std::map<string, AX_U16> g_mapToken2Data;
static CWebServer* s_pWebInstance = CWebServer::GetInstance();

typedef struct {
    HttpConn* conn{nullptr};
    AX_VOID* packet{nullptr};
} WSMsg_T;
static std::map<void*, std::unique_ptr<WSMsg_T>> g_mapWSMsg;

typedef struct {
    AX_U32 nMagic{0x54495841};  // "AXIT" by default
    AX_U32 nDatalen{0};
    AX_U64 nPts{0};
} PTS_HEADER_T;

// strong
extern "C" void *MprVmalloc(size_t size, int mode) {
    void    *ptr;

#if 1
    if ((ptr = AX_MALLOC(size)) != 0) {
        memset(ptr, 0, size);
    }
#else
    if ((ptr = mmap(0, size, mode, MAP_PRIVATE | MAP_ANON, -1, 0)) == (void*) -1) {
        return 0;
    }
#endif

    return ptr;
}

extern "C" void MprVmfree(void *ptr, size_t size) {
#if 1
    AX_FREE(ptr);
#else
    munmap(ptr, size);
#endif
}

static AX_VOID WebMprYield() {
#if 0
    if (mprNeedYield()) {
        mprYield(MPR_YIELD_DEFAULT);
    }
#endif
}

static AX_S32 YieldProcessWebOpr(HttpConn* conn, WEB_REQUEST_TYPE_E requestType, AX_VOID** pResult = nullptr, AX_BOOL bNeedYield = AX_TRUE) {
    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;
    // if (bNeedYield) {
    //     mprYield(MPR_YIELD_STICKY);
    // }

    MprJson* jsonParam = httpGetParams(conn);
    if (!s_pWebInstance->GetPPLInstance()->ProcessWebOprs(requestType, jsonParam, pResult)){
        nHttpStatusCode = RESPONSE_STATUS_FAILURE_CODE;
    }

    // if (bNeedYield) {
    //     mprResetYield();
    // }

    return nHttpStatusCode;
}

static AX_VOID* MprListGetNextItem(MprList* lp, AX_S32* next) {
    AX_VOID* item = nullptr;
    int index = 0;

    if (lp == 0 || lp->length == 0) {
        return nullptr;
    }
    index = *next;
    if (index < lp->length) {
        item = lp->items[index];
        *next = ++index;
        return item;
    }
    return nullptr;
}

static AX_VOID WebServerMemNotifier(int cause, int policy, size_t size, size_t total) {
    switch (cause) {
    case MPR_MEM_LIMIT:
        {
            HttpConn* client = nullptr;
            MprTicks now = mprGetTicks();
            MprTicks requestTimeout = 0;
            constexpr MprTicks minRequestTimeout = 300000; // 5mins

            mprLock(g_pClients->mutex);
            // modify RequestTimeout
            for (AX_S32 next = 0; (client = (HttpConn*)MprListGetNextItem(g_pClients, &next)) != 0;) {
                if (WS_STATE_OPEN != httpGetWebSocketState(client)) {
                    continue;
                }

                if (client->limits->requestTimeout > minRequestTimeout) {
                    if (now > client->started) {
                        requestTimeout = now - client->started;
                    }

                    if (requestTimeout < minRequestTimeout) {
                        requestTimeout = minRequestTimeout;
                    }

                    httpSetTimeout(client, requestTimeout, -1);

                    g_web_mem_limit_notified = AX_TRUE;
                }
            }
            mprUnlock(g_pClients->mutex);
        }
        break;

    default:
        break;
    }
}

/* http event callback */
static AX_VOID SendHttpData(WSMsg_T* msg) {
    HttpConn* stream = msg->conn;
    CAXRingElementEx* pData = static_cast<CAXRingElementEx*>(msg->packet);
    {
        std::lock_guard<std::mutex> guard(g_mtxWSData);
        g_mapWSMsg.erase(msg);
    }

    if ((mprLookupItem(g_pClients, stream) < 0) || (pData == nullptr)) {
        if (pData && pData->pParent) {
            pData->pParent->Free(pData);
        }
        return;
    }

    if (!s_pWebInstance->IsRunning()) {
        return;
    }

    /* pData->pBuf and pData->nSize is not stable, so save them to local varible */
    AX_U8* pBuf = pData->pBuf;
    AX_S32 nSize = (AX_S32)(pData->nSize);
    AX_U8* pBuf2 = pData->pBuf2;
    AX_S32 nSize2 = (AX_S32)(pData->nSize2);

    do {
        if (stream == nullptr || stream->connError || stream->timeout != 0 || !pBuf || nSize == 0) {
            break;
        }

        ssize nRet = 0;
        if (nSize2 > 0) {
            nRet = httpSendBlock(stream, WS_MSG_BINARY, (cchar*)pBuf, nSize, HTTP_BLOCK | HTTP_MORE);
        } else {
            nRet = httpSendBlock(stream, WS_MSG_BINARY, (cchar*)pBuf, nSize, HTTP_BLOCK);
        }
        if (nRet == nSize) {
            if (nSize2 > 0 && pBuf2) {
                nRet = httpSendBlock(stream, WS_MSG_BINARY, (cchar*)pBuf2, nSize2, HTTP_BLOCK);
                if (nRet == nSize2) {
                    break;
                }
            } else {
                break;
            }
        }
        switch (nRet) {
            case MPR_ERR_TIMEOUT:
                LOG_MM_E(WEB, "httpSendBlock() return ERR_TIMEOUT.");
                break;
            case MPR_ERR_MEMORY:
                LOG_MM_E(WEB, "httpSendBlock() return ERR_MEMORY.");
                break;
            case MPR_ERR_BAD_STATE:
                LOG_MM_E(WEB, "httpSendBlock() return MPR_ERR_BAD_STATE.");
                break;
            case MPR_ERR_BAD_ARGS:
                LOG_MM_E(WEB, "httpSendBlock() return MPR_ERR_BAD_ARGS.");
                break;
            case MPR_ERR_WONT_FIT:
                LOG_MM_E(WEB, "httpSendBlock() return MPR_ERR_WONT_FIT.");
                break;
            default:
                LOG_MM_E(WEB, "httpSendBlock failed.");
                break;
        }
    } while (false);

    if (pData && pData->pParent) {
        pData->pParent->Free(pData);
    }
}

static size_t GenKeyData(AX_U8 nSnsID, AX_U8 nChnID) {
    return (size_t)(nSnsID | (size_t)nChnID << 8);
}

static AX_S32 GetSnsIDFromWS(HttpConn* conn) {
    if (!conn) {
        return -1;
    }
    AX_U32 nWSData = (size_t)conn->staticData;
    return (AX_S32)(nWSData & 0xFF);
}

static AX_S32 GetChnFromWS(HttpConn* conn) {
    if (!conn) {
        return -1;
    }
    AX_U32 nWSData = (size_t)conn->staticData;
    return (AX_S32)(nWSData >> 8);
}

static AX_U8 GetUniChnFromToken(cchar* token, AX_U8 nSnsID) {
    AX_U16 nData = g_mapToken2Data[(string)token];
    return (AX_U8)((0 == nSnsID) ? nData & 0x00FF : nData >> 8);
}

static AX_VOID SaveTokenData(cchar* token, AX_U8 nSnsID, AX_U8 nUniChn) {
    AX_U16 nData = 0;
    std::map<string, AX_U16>::iterator itFind = g_mapToken2Data.find(token);
    if (itFind != g_mapToken2Data.end()) {
        nData = g_mapToken2Data[(string)token];
    }

    AX_U8 nSns0Chn = nData & 0x00FF;
    AX_U8 nSns1Chn = nData >> 8;

    if (0 == nSnsID) {
        nSns0Chn = nUniChn;
    } else {
        nSns1Chn = nUniChn;
    }

    g_mapToken2Data[(string)token] = (AX_U16)(nSns0Chn | (AX_U16)nSns1Chn << 8);
}

static AX_S32 GetUniChn(AX_U8 nSnsID, AX_U8 nPrevIndex) {
    if (m_sMapPrevChn2UniChn.find(nSnsID) == m_sMapPrevChn2UniChn.end()) {
        return -1;
    }

    return std::get<0>(m_sMapPrevChn2UniChn[nSnsID][nPrevIndex]);
}

static bool CheckUser(HttpConn* conn, cchar* user, cchar* pwd) {
    std::map<string, string>::iterator itFind = g_mapUserInfo.find(user);
    if (itFind != g_mapUserInfo.end()) {
        return strcmp(itFind->second.c_str(), pwd) == 0;
    }

    return false;
}

static cchar* GenToken(string user, string pwd) {
    uint64 nTickcount = mprGetHiResTicks();
    string strTokenKey = sfmt("%s_%lld", user.c_str(), nTickcount);
    g_mapUser2Token[strTokenKey] = mprGetSHABase64(sfmt("token:%s-%s-%lld", user.c_str(), pwd.c_str(), nTickcount));

    return g_mapUser2Token[strTokenKey].c_str();
}

static MprJson* ConstructBaseResponse(cchar* pszStatus, cchar* pszToken) {
    MprJson* pResponseBody = mprCreateJson(MPR_JSON_OBJ);
    mprWriteJson(pResponseBody, "data", "", MPR_JSON_OBJ);
    if (pszToken) {
        mprWriteJson(mprReadJsonObj(pResponseBody, "data"), "token", pszToken, MPR_JSON_STRING);
    }
    mprWriteJson(pResponseBody, "meta", "", MPR_JSON_OBJ);
    mprWriteJson(mprReadJsonObj(pResponseBody, "meta"), "status", pszStatus, MPR_JSON_NUMBER);

    return pResponseBody;
}

inline picojson::object ConstructJsonResponse(AX_S32 nHttpStatusCode, cchar* pszToken) {
    picojson::object root;
    root["data"] = picojson::value(picojson::object());
    if (pszToken) {
        picojson::object token;
        token["token"] = picojson::value(pszToken);
        root["data"] = picojson::value(token);
    }
    picojson::object statusObj;
    statusObj["status"] = picojson::value(double(nHttpStatusCode));
    root["meta"] = picojson::value(statusObj);

    return root;
}

inline picojson::value ParseJsonString(const std::string& str) {
    picojson::value value;
    picojson::parse(value, str);
    return value;
}

inline std::string WriteJsonString(picojson::object& value) {
    std::string strJson = picojson::value(value).serialize().data();
    return strJson;
}

static cchar* GetTokenFromConn(HttpConn* conn, AX_BOOL bFromHeader) {
    if (!conn) {
        return nullptr;
    }

    cchar* szToken = nullptr;
    if (bFromHeader) {
        szToken = (httpGetHeader(conn, "authorization"));
    } else {
        szToken = (httpGetParam(conn, "token", nullptr));
    }

    char* p = nullptr;
    while ((p = schr(szToken, ' ')) != 0) {
        *p = '+';
    }

    return szToken;
}

static AX_BOOL IsAuthorized(HttpConn* conn, AX_BOOL bGetTokenFromHeader) {
    cchar* szToken = GetTokenFromConn(conn, bGetTokenFromHeader);
    if (0 == szToken || strlen(szToken) == 0) {
        return AX_FALSE;
    }

    for (const auto& kv : g_mapUser2Token) {
        if (strcmp(kv.second.c_str(), szToken) == 0) {
            return AX_TRUE;
        }
    }
    return AX_FALSE;
}

static AX_VOID ResponseUnauthorized(HttpConn* conn) {
    LOG_MM_I(WEB, "Unauthorized, try to login again.");
    HttpQueue* q = conn->writeq;
    MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_AUTH_FAIL, 0);

    httpSetContentType(conn, "application/json");
    httpWrite(q, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

    httpSetStatus(conn, RESPONSE_STATUS_OK_CODE);
    httpFinalize(conn);
    WebMprYield();
}

static AX_VOID ResponseError(HttpConn* conn, const AX_CHAR* szErrorCode) {
    HttpQueue* q = conn->writeq;
    MprJson* pResponseBody = ConstructBaseResponse(szErrorCode, 0);

    httpSetContentType(conn, "application/json");
    httpWrite(q, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

    httpSetStatus(conn, RESPONSE_STATUS_OK_CODE);
    httpFinalize(conn);
    WebMprYield();
}

static AX_VOID ResponseStatusCode(HttpConn* conn, AX_S32 nHttpStatusCode) {
    MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
    httpSetContentType(conn, "application/json");
    httpWrite(conn->writeq, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));
    httpSetStatus(conn, nHttpStatusCode);
    httpFinalize(conn);
    WebMprYield();
}

AX_VOID ReadAndPlayAudioData(HttpConn* conn) {
    static AX_U32 nTalkChannel = s_pWebInstance->GetTalkChannel();
    AX_U32 nChannel = GetChnFromWS(conn);
    if (nChannel != nTalkChannel) {
        return;
    }

    HttpPacket *packet = httpGetPacket(conn->readq);
    if ((packet != nullptr) &&
        (packet->type == WS_MSG_BINARY)) {
        // FIXME: webapp only support PCM
        ssize nSize = httpGetPacketLength(packet);
        AX_APP_Audio_Play(APP_AUDIO_WEB_TALK_CHANNEL(), PT_LPCM, (AX_U8*)httpGetPacketStart(packet), nSize);
    }
}

static AX_VOID WebNotifier(HttpConn* conn, AX_S32 event, AX_S32 arg) {
    if ((event == HTTP_EVENT_APP_CLOSE) || (event == HTTP_EVENT_ERROR) || (event == HTTP_EVENT_DESTROY)) {
        AX_S32 nIndex = mprRemoveItem(g_pClients, conn);
        if (nIndex >= 0) {
            LOG_MM_D(WEB, "remove connection %p, index=%d", conn, nIndex);
            CWebServer::GetInstance()->UpdateConnStatus();
        }
    } else if (event == HTTP_EVENT_READABLE) {
        ReadAndPlayAudioData(conn);
    }
}

static AX_VOID LoginAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    cchar* strUser = httpGetParam(conn, "username", "unspecified");
    cchar* strPwd = httpGetParam(conn, "password", "unspecified");

    cchar* szToken = nullptr;
    string strStatus;
    bool bAuthRet = CheckUser(conn, strUser, strPwd);
    if (!bAuthRet) {
        strStatus = RESPONSE_STATUS_AUTH_FAIL;
    } else {
        strStatus = RESPONSE_STATUS_OK;
        szToken = GenToken(strUser, strPwd);
    }

    MprJson* pResponseBody = ConstructBaseResponse(strStatus.c_str(), szToken);

    AX_U8 nSnsMode = (CCommonUtils::GetPPLSpecification() == "PANO") ? 0 : APP_SENSOR_COUNT();
    string strSnsMode = to_string(nSnsMode);
    LOG_MM_I(WEB, "strSnsMode: %s", strSnsMode.c_str());
    mprWriteJson(mprReadJsonObj(pResponseBody, "data"), PARAM_KEY_SNS_MODE, strSnsMode.c_str(), MPR_JSON_STRING);

    httpSetContentType(conn, "application/json");
    httpWrite(conn->writeq, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

    httpSetStatus(conn, RESPONSE_STATUS_OK_CODE);
    httpFinalize(conn);
    WebMprYield();
}

static AX_VOID CapabilityAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);

    if (strcmp(conn->rx->method, "GET") == 0) {
        AX_CHAR szStr[1024] = {0};
        if (CWebOptionHelper::GetInstance()->GetCapSettingStr(szStr, 1024)) {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), PARAM_KEY_SETTING_CAPABILITY, mprParseJson(szStr));
        }

        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

        httpSetStatus(conn, RESPONSE_STATUS_OK_CODE);
        httpFinalize(conn);
    }

    WebMprYield();
}

static AX_VOID PreviewInfoAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    WEB_CAMERA_ATTR_T tCamAttr = CWebOptionHelper::GetInstance()->GetCamera(0);
    AX_BOOL bTrigger = tCamAttr.bTriggerEnable;
    AX_BOOL bCapture = tCamAttr.bCaptureEnable;
    AX_BOOL bFlash = tCamAttr.bFlashEnable;
    AX_BOOL bEZoomEnable = tCamAttr.bEZoomEnable;
    string szTrigger = (bTrigger ? "true" : "false");
    string szCapture = (bCapture ? "true" : "false");
    string szFlash = (bFlash ? "true" : "false");
    string szEZoomEnable = (bEZoomEnable ? "true" : "false");

    MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
    if (strcmp(conn->rx->method, "GET") == 0) {
        AX_U8 nSnsCnt = (CCommonUtils::GetPPLSpecification() == "PANO") ? 1 : APP_SENSOR_COUNT();
        AX_CHAR arrStreamStr[2][16] = {0};
        for (AX_U8 i = 0; i < 2; i++) {
            if (i < nSnsCnt) {
                AX_U8 nPrevChnCount = m_sMapPrevChn2UniChn[i].size();
                if (1 == nPrevChnCount) {
                    sprintf(arrStreamStr[i], "[%d]", 0);
                } else if (2 == nPrevChnCount) {
                    sprintf(arrStreamStr[i], "[%d, %d]", 0, 1);
                } else if (3 == nPrevChnCount) {
                    sprintf(arrStreamStr[i], "[%d, %d, %d]", 0, 1, 2);
                } else if (4 == nPrevChnCount) {
                    sprintf(arrStreamStr[i], "[%d, %d, %d, %d]", 0, 1, 2, 3);
                }
            } else {
                sprintf(arrStreamStr[i], "[0, 1, 2, 3]");
            }
        }

        AX_CHAR arrCodecType[2][16] = {0};
        for (AX_U8 i = 0; i < 2; i++) {
            if (i < nSnsCnt) {
                AX_U8 nPrevChnCount = m_sMapPrevChn2UniChn[i].size();
                if (1 == nPrevChnCount) {
                    sprintf(arrCodecType[i], "[%d]", std::get<1>(m_sMapPrevChn2UniChn[i][0]));
                } else if (2 == nPrevChnCount) {
                    sprintf(arrCodecType[i], "[%d, %d]", std::get<1>(m_sMapPrevChn2UniChn[i][0]), std::get<1>(m_sMapPrevChn2UniChn[i][1]));
                } else if (3 == nPrevChnCount) {
                    sprintf(arrCodecType[i], "[%d, %d, %d]", std::get<1>(m_sMapPrevChn2UniChn[i][0]),
                            std::get<1>(m_sMapPrevChn2UniChn[i][1]), std::get<1>(m_sMapPrevChn2UniChn[i][2]));
                } else if (4 == nPrevChnCount) {
                    sprintf(arrCodecType[i], "[%d, %d, %d, %d]", std::get<1>(m_sMapPrevChn2UniChn[i][0]),
                            std::get<1>(m_sMapPrevChn2UniChn[i][1]), std::get<1>(m_sMapPrevChn2UniChn[i][2]),
                            std::get<1>(m_sMapPrevChn2UniChn[i][3]));
                }
            } else {
                sprintf(arrCodecType[i], "[0, 1, 0, 0]");
            }
        }

        static constexpr AX_U8 nFramerateStringBUfferSize = 32;
        AX_CHAR arrVideoFPS[2][nFramerateStringBUfferSize] = {"[0, 0, 0, 0]", "[0, 0, 0, 0]"};

        AX_APP_AUDIO_ATTR_T stAttr;
        AX_APP_Audio_GetAttr(&stAttr);
        const AX_CHAR* szAudioCapture = (stAttr.stCapAttr.bEnable) ? "true" : "false";
        // TODO: aenc channel index
        AX_CHAR szData[512] = {0};
        string aencType = "aac";
        AX_APP_AUDIO_ENCODER_ATTR_T stEncodeAttr;
        memset(&stEncodeAttr, 0, sizeof(AX_APP_AUDIO_ENCODER_ATTR_T));
        if (stAttr.stCapAttr.bEnable) {
            AX_APP_AUDIO_CHAN_E eChannel = APP_AUDIO_WEB_STREAM_CHANNEL();
            AX_APP_Audio_GetEncoderAttr(eChannel, &stEncodeAttr);
            switch (stEncodeAttr.eType) {
                case PT_G711A:
                    aencType = "g711a";
                    break;
                case PT_G711U:
                    aencType = "g711u";
                    break;
                case PT_LPCM:
                    aencType = "lpcm";
                    break;
                default:
                    aencType = "aac";
                    break;
            }
        }

        // ezomm
        string szEZoom = "[";
        for (AX_U8 i = 0; i < 2; i++) {
            if (i < nSnsCnt) {
                WEB_CAMERA_ATTR_T tCamAttrItem = CWebOptionHelper::GetInstance()->GetCamera(i);
                AX_CHAR szEZoomItem[128] = {0};
                sprintf(szEZoomItem, "{ezoom_ratio:%d,center_offset_x:%d,center_offset_y:%d}",
                        tCamAttrItem.tEZoomAttr.nEZoomRatio, tCamAttrItem.tEZoomAttr.nCenterOffsetX, tCamAttrItem.tEZoomAttr.nCenterOffsetY);
                szEZoom += szEZoomItem;
                if (i < 2) {
                    szEZoom += ",";
                }

            } else {
                szEZoom += "{ezoom_ratio:0,center_offset_x:0,center_offset_y:0}";
                if (i < 2) {
                    szEZoom += ",";
                }
            }
        }
        szEZoom += "]";

        sprintf(szData,
                "{%s:%d,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%s,%s:%d,"
                "%s:%d,%s:%s,%s:%s,%s:%s,%s:%s}",
                "sns_num", nSnsCnt,
                "sns0_codec", arrCodecType[0], /* 0: VENC; 1: MJPEG */
                "sns1_codec", arrCodecType[1], /* 0: VENC; 1: MJPEG */
                "sns0_video_fps", arrVideoFPS[0],
                "sns1_video_fps", arrVideoFPS[1],
                "stream0_list", arrStreamStr[0],
                "stream1_list", arrStreamStr[1],
                "ai_enable", "false",
                "searchimg", "false",
                "detect_mode", "hvcfp",
                "osd_enable", "true",
                "capture_enable", szCapture.c_str(),
                "aenc_enable", szAudioCapture,
                "aenc_type", &aencType[0],
                "aenc_sample_rate", stEncodeAttr.eSampleRate,
                "aenc_bit_width", stEncodeAttr.eBitWidth,
                "trigger_enable", szTrigger.c_str(),
                "flash_enable", szFlash.c_str(),
                "ezoom_enable", szEZoomEnable.c_str(),
                "ezoom", szEZoom.c_str());

        LOG_MM_I(WEB, "szData:%s", szData);

        mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "info", mprParseJson(szData));

        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

        httpSetStatus(conn, RESPONSE_STATUS_OK_CODE);
        httpFinalize(conn);
    }

    WebMprYield();
}

static AX_VOID SwitchChnAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));
    AX_U8 nPrevIndex = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_CHANNEL, "0"));

    LOG_MM_I(WEB, "Sensor %d switching to channel %d.", nSnsID, nPrevIndex);

    g_mapSns2CurrPrevChn[nSnsID] = nPrevIndex;
    AX_U8 nUniChn = GetUniChn(nSnsID, nPrevIndex);
    if (-1 == nUniChn) {
        LOG_MM_W(WEB, "Can not find channel id for this request(Switch Channel <sns:%d, chn:%d>)", nSnsID, nPrevIndex);
        ResponseError(conn, RESPONSE_STATUS_INVALID_REQ);
        return;
    }

    cchar* szToken = GetTokenFromConn(conn, AX_TRUE);
    if (0 != szToken && strlen(szToken) > 0) {
        LOG_MM_I(WEB, "Sensor %d save unique chn %d to token %p", nSnsID, nUniChn, szToken);
        SaveTokenData(szToken, nSnsID, nUniChn);
    }

    ResponseStatusCode(conn, RESPONSE_STATUS_OK_CODE);
}

static AX_VOID SaveWSConnection(HttpConn* conn, AX_U8 nSnsID, AX_U8 nUniChnID) {
    conn->staticData = (void*)GenKeyData(nSnsID, nUniChnID);
    AX_S32 nIndex = mprAddItem(g_pClients, conn);
    LOG_MM_D(WEB, "connected %p, index=%d", conn, nIndex);
    httpSetConnNotifier(conn, WebNotifier);
    WebMprYield();
}

static AX_VOID WSPreviewAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    LOG_MM_D(WEB, "WSPreview setup conn=%p.", conn);

    if (!IsAuthorized(conn, AX_FALSE)) {
        LOG_MM_E(WEB, "Unauthorized, try to login again.");
        ResponseUnauthorized(conn);
        return;
    }

    AX_U8 nSrcID = 0;
    if (strstr(conn->rx->uri, "/preview_1") != nullptr) {
        nSrcID = 1;
    }

    LOG_MM(WEB, "Websocket preview request src id: %d", nSrcID);

    cchar* szToken = GetTokenFromConn(conn, AX_FALSE);
    if (nullptr != szToken && strlen(szToken) > 0) {
        AX_U8 nSnsID = nSrcID;
        AX_U8 nUniChnID = GetUniChnFromToken(szToken, nSnsID);
        SaveWSConnection(conn, nSnsID, nUniChnID);
        LOG_MM(WEB, "[Sns:%d][UniChn:%d] preview connected: %p", nSnsID, nUniChnID, conn);
    }
}

static AX_VOID WSCaptureAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_FALSE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_U8 nSrcID = 0; /* Dual sensor's capture shares one connection */
    LOG_MM_I(WEB, "[%d] Capture stream %d setup conn=%p.", nSrcID, s_pWebInstance->GetCaptureChannel(), conn);
    SaveWSConnection(conn, nSrcID, s_pWebInstance->GetCaptureChannel());
}

static AX_VOID WSSnapshotAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_FALSE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_U8 nSrcID = 0; /* Dual sensor's capture shares one connection */
    AX_U8 nChnnelID = s_pWebInstance->GetSnapshotChannel();

    LOG_MM_I(WEB, "[%d] Snapshot picture %d setup.", nSrcID, nChnnelID);
    SaveWSConnection(conn, nSrcID, nChnnelID);
}

static AX_VOID TriggerAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    static AX_BOOL bActionProcessing = AX_FALSE; /* Avoiding multiple web operations */

    if (strcmp(conn->rx->method, "GET") == 0) {
    } else if (!bActionProcessing) {
        bActionProcessing = AX_TRUE;
        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_TRIGGER);
        bActionProcessing = AX_FALSE;
    } else if (bActionProcessing) {
        // Response status: Not Acceptable
        nHttpStatusCode = RESPONSE_STATUS_FAILURE_CODE;
    }

    ResponseStatusCode(conn, nHttpStatusCode);
}

static AX_VOID SnapshotAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    using AXSnapshotDataCallback = std::function<AX_VOID(AX_VOID* data, AX_U32 size, AX_VOID* conn)>;
    static AX_BOOL bActionProcessing = AX_FALSE;
    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;
    if (!bActionProcessing) {
        bActionProcessing = AX_TRUE;
        std::pair<AX_VOID*, AXSnapshotDataCallback> tSnapshotData = std::make_pair(
            conn, std::bind(&CWebServer::SendSnapshotData, s_pWebInstance, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_CAPTURE, (AX_VOID**)&tSnapshotData);

        bActionProcessing = AX_FALSE;
    } else {
        // Response status: Not Acceptable
        nHttpStatusCode = RESPONSE_STATUS_FAILURE_CODE;
        LOG_MM_W(WEB, "Snapshot already in process, please wait.");
    }

    ResponseStatusCode(conn, nHttpStatusCode);
}

static AX_VOID EZoomAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));
    AX_U8 nPrevIndex = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_CHANNEL, "0"));
    LOG_MM_I(WEB, "Request zoom, sns:%d, chn:%d", nSnsID, nPrevIndex);

    static AX_BOOL bActionProcessing = AX_FALSE;
    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;
    if (!bActionProcessing) {
        bActionProcessing = AX_TRUE;
        YieldProcessWebOpr(conn, E_REQ_TYPE_EZOOM, nullptr, AX_FALSE);
        bActionProcessing = AX_FALSE;
    }
    ResponseStatusCode(conn, nHttpStatusCode);
}

static AX_VOID WSAudioAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_FALSE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_U8 nSnsID = 0;
    AX_U8 nUniChnID = s_pWebInstance->GetAencChannel();
    SaveWSConnection(conn, nSnsID, nUniChnID);
}

static AX_VOID WSTalkAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_FALSE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_U8 nUniChnID = s_pWebInstance->GetTalkChannel();
    LOG_M_I(WEB, "Websocket talk channel id: %d", nUniChnID);
    SaveWSConnection(conn, 0, nUniChnID);
}

static AX_VOID WSEventsAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_FALSE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_U16 nChnID = (0x0 /*sensor id*/ | ((WS_EVENTS_CHANNEL & 0x00FF) << 8));
    LOG_MM_D(WEB, "nChnID:%d", nChnID);
    SaveWSConnection(conn, 0, WS_EVENTS_CHANNEL);
}

static AX_VOID AssistInfoAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    if (strcmp(conn->rx->method, "GET") == 0) {
        std::lock_guard<std::mutex> guard(g_mtxWebOprProcess);

        AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));
        AX_U8 nPrevIndex = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_CHANNEL, "0"));

        AX_CHAR szResolution[16] = {0};

        AX_S32 nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_GET_ASSIST_INFO, (AX_VOID**)&szResolution[0], AX_FALSE);

        MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
        if (nHttpStatusCode == RESPONSE_STATUS_OK_CODE) {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "assist_res", mprParseJson(szResolution));
        } else {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "assist_res", mprParseJson("--"));
        }

        AX_CHAR szBitrate[16] = {0};
        if (CWebOptionHelper::GetInstance()->GetAssistBitrateStr(nSnsID, GetUniChn(nSnsID, nPrevIndex), szBitrate, 16)) {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "assist_bitrate", mprParseJson(szBitrate));
        } else {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "assist_bitrate", mprParseJson("--"));
            // LOG_MM_E(WEB, "[%d][%d] Get assist bitrate info failed.", nSnsID, nPrevIndex);
        }
        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

        httpSetStatus(conn, RESPONSE_STATUS_OK_CODE);
        httpFinalize(conn);
    }

    WebMprYield();
}

static AX_VOID SystemAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    LOG_MM_D(WEB, "Request system info.");

    if (strcmp(conn->rx->method, "GET") == 0) {
        AX_CHAR szTitle[64] = {0};
        AX_CHAR szOutTitle[64] = {0};

        AX_S32 nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_GET_SYSTEM_INFO, (AX_VOID**)&szOutTitle[0], AX_FALSE);

        if (nHttpStatusCode == RESPONSE_STATUS_OK_CODE) {
            sprintf(szTitle, "%s", szOutTitle);
        } else {
            LOG_MM_W(WEB, "Failed to retrieve web title specification.");
            sprintf(szTitle, "%s", "FRTDemo");
        }

        MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
        string strDispVer(APP_BUILD_VERSION);
        mprWriteJson(mprReadJsonObj(pResponseBody, "data"), PARAM_KEY_APP_NAME, szTitle, MPR_JSON_STRING);
        mprWriteJson(mprReadJsonObj(pResponseBody, "data"), PARAM_KEY_APP_VERSION, strDispVer.c_str(), MPR_JSON_STRING);
        mprWriteJson(mprReadJsonObj(pResponseBody, "data"), PARAM_KEY_SDK_VERSION, g_SDKVersion.c_str(), MPR_JSON_STRING);

        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

        httpSetStatus(conn, RESPONSE_STATUS_OK_CODE);
        httpFinalize(conn);
    }

    WebMprYield();
}

static AX_VOID CameraAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;
    static AX_BOOL bActionProcessing = AX_FALSE; /* Avoiding multiple web operations */

    if (strcmp(conn->rx->method, "GET") == 0) {
        MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
        AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));

        auto jsonCameraAttr = CWebOptionHelper::GetInstance()->GetCameraJson(nSnsID);
        if (jsonCameraAttr) {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "camera_attr", jsonCameraAttr);
        }

        mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "framerate_opts",
                        mprParseJson(CWebOptionHelper::GetInstance()->GetFramerateOptStr(nSnsID).c_str()));

        char *pStr = mprJsonToString(pResponseBody, MPR_JSON_QUOTES);
        LOG_MM_I(WEB, "resp:%s", pStr);
        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, pStr);

        httpSetStatus(conn, nHttpStatusCode);
        httpFinalize(conn);
        WebMprYield();
    } else {
        LOG_MM_C(WEB, "...");
        if (!bActionProcessing) {
            bActionProcessing = AX_TRUE;

            nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_CAMERA);
            ResponseStatusCode(conn, nHttpStatusCode);

            bActionProcessing = AX_FALSE;
        } else if (bActionProcessing) {
            // Response status: Not Acceptable
            nHttpStatusCode = RESPONSE_STATUS_FAILURE_CODE;
            ResponseStatusCode(conn, nHttpStatusCode);
        }
    }

}

static AX_VOID ImageAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    static AX_BOOL bActionProcessing = AX_FALSE; /* Avoiding multiple web operations */

    if (strcmp(conn->rx->method, "GET") == 0) {
        MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
        AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));

        AX_CHAR szStr[1024] = {0};
        if (CWebOptionHelper::GetInstance()->GetImageStr(nSnsID, szStr, 1024)) {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "image_attr", mprParseJson(szStr));
        }
        if (CWebOptionHelper::GetInstance()->GetLdcStr(nSnsID, szStr, 1024)) {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "ldc_attr", mprParseJson(szStr));
        }
        if (CWebOptionHelper::GetInstance()->GetDisStr(nSnsID, szStr, 1024)) {
            mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "dis_attr", mprParseJson(szStr));
        }

        char *pStr = mprJsonToString(pResponseBody, MPR_JSON_QUOTES);
        LOG_MM_I(WEB, "resp:%s", pStr);
        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, pStr);

        httpSetStatus(conn, nHttpStatusCode);
        httpFinalize(conn);
        WebMprYield();
    } else {
        LOG_MM_C(WEB, "...");
        if (!bActionProcessing) {
            bActionProcessing = AX_TRUE;
            nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_IMAGE);
            ResponseStatusCode(conn, nHttpStatusCode);
            bActionProcessing = AX_FALSE;
        } else {
            // Response status: Not Acceptable
            nHttpStatusCode = RESPONSE_STATUS_FAILURE_CODE;
            ResponseStatusCode(conn, nHttpStatusCode);
        }
    }
}

static AX_VOID AudioAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    if (strcmp(conn->rx->method, "GET") == 0) {
        MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);

        const AX_U32 MAX_CHAR = 512;
        AX_CHAR szAudio[MAX_CHAR] = {0};
        WEB_AUDIO_ATTR_T tAudioAttr = CWebOptionHelper::GetInstance()->GetAudio();
        sprintf(szAudio, "{capture_attr:{volume_val: %.2f}, \
                            play_attr:{volume_val: %.2f}, \
                            aed_attr:{enable: %s, threshold: %d, interval: %d}}",
                            tAudioAttr.fCapture_volume,
                            tAudioAttr.fPlay_volume,
                            ADAPTER_INT2BOOLSTR(tAudioAttr.bAedEnable),
                            (AX_S32)tAudioAttr.fAedThreshold,
                            tAudioAttr.nAedInterval / 1000);
        mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "info", mprParseJson(szAudio));

        char *pStr = mprJsonToString(pResponseBody, MPR_JSON_QUOTES);
        LOG_MM_I(WEB, "resp:%s", pStr);
        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, pStr);
        httpSetStatus(conn, nHttpStatusCode);
        httpFinalize(conn);
        WebMprYield();
    } else {
        LOG_MM_C(WEB, "...");
        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_AUDIO);
        ResponseStatusCode(conn, nHttpStatusCode);
    }

}

static AX_VOID VideoAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    if (strcmp(conn->rx->method, "GET") == 0) {
        auto root = ConstructJsonResponse(RESPONSE_STATUS_OK_CODE, 0);
        AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));

        AX_CHAR szCapList[16] = {0};
        AX_U8 nSize = CWebOptionHelper::GetInstance()->GetVideoCount(nSnsID);

        if (1 == nSize) {
            sprintf(szCapList, "[1,0,0,0]");
        } else if (2 == nSize) {
            sprintf(szCapList, "[1,1,0,0]");
        } else if (3 == nSize) {
            sprintf(szCapList, "[1,1,1,0]");
        } else if (4 == nSize) {
            sprintf(szCapList, "[1,1,1,1]");
        }

        auto& data = root["data"].get<picojson::object>();
        data["cap_list"] = ParseJsonString(szCapList);
        for (AX_U8 i = 0; i < nSize; i++) {
            string strKey = "video" + to_string(i);
            data[strKey] = picojson::value(CWebOptionHelper::GetInstance()->GetVideoJsonObj(nSnsID, i));

            string strAttrKey = "attrVideo" + to_string(i);
            data[strAttrKey] = picojson::value(CWebOptionHelper::GetInstance()->GetVideoAttrJsonObj(nSnsID, i));
        }

        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, WriteJsonString(root).c_str());

        httpSetStatus(conn, nHttpStatusCode);
        httpFinalize(conn);
        WebMprYield();
    } else {
        LOG_MM_C(WEB, "...");
        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_VIDEO);
        ResponseStatusCode(conn, nHttpStatusCode);
    }
}

static AX_VOID AiAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));
    if (strcmp(conn->rx->method, "GET") == 0) {
        MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
        AX_CHAR szAiAttr[2048] = {0};
        if (!CWebOptionHelper::GetInstance()->GetAiInfoStr(nSnsID, szAiAttr, 2048)) {
            LOG_MM_E(WEB, "Get AI info failed.");
            return;
        }
        mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "ai_attr", mprParseJson(szAiAttr));
        char *pStr = mprJsonToString(pResponseBody, MPR_JSON_QUOTES);
        LOG_MM_I(WEB, "resp:%s", pStr);
        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, pStr);

        httpSetStatus(conn, nHttpStatusCode);
        httpFinalize(conn);
        WebMprYield();
    } else {
        LOG_MM_C(WEB, "...");
        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_AI);
        ResponseStatusCode(conn, nHttpStatusCode);
    }
}

static AX_VOID OverlayAction(HttpConn* conn) {
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    if (strcmp(conn->rx->method, "GET") == 0) {
        MprJson* pResponseBody = ConstructBaseResponse(RESPONSE_STATUS_OK, 0);
        AX_U8 nSnsID = atoi(httpGetParam(conn, PARAM_KEY_PREVIEW_SNS_SRC, "0"));

        auto jsonOSD = CWebOptionHelper::GetInstance()->GetOsdJson(nSnsID);
        mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "overlay_attr", jsonOSD);

        auto jsonPrivacy = CWebOptionHelper::GetInstance()->GetPrivacyJson(nSnsID);
        mprWriteJsonObj(mprReadJsonObj(pResponseBody, "data"), "privacy_attr", jsonPrivacy);

        httpSetContentType(conn, "application/json");
        httpWrite(conn->writeq, mprJsonToString(pResponseBody, MPR_JSON_QUOTES));

        httpSetStatus(conn, nHttpStatusCode);
        httpFinalize(conn);
        WebMprYield();
    } else {
        LOG_MM_C(WEB, "...");
        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_OSD);
        ResponseStatusCode(conn, nHttpStatusCode);
    }

}

static AX_VOID Switch3ASyncAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    static AX_BOOL bActionProcessing = AX_FALSE;
    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    if (!bActionProcessing) {
        bActionProcessing = AX_TRUE;

        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_SWITCH_3A_SYNC);

        bActionProcessing = AX_FALSE;
    } else if (bActionProcessing) {
        // Response status: Not Acceptable
        nHttpStatusCode = RESPONSE_STATUS_FAILURE_CODE;
    }

    ResponseStatusCode(conn, nHttpStatusCode);
}

static AX_VOID SwitchScreenAction(HttpConn* conn) {
    LOG_MM_C(WEB, "...");
    if (!IsAuthorized(conn, AX_TRUE)) {
        ResponseUnauthorized(conn);
        return;
    }

    static AX_BOOL bActionProcessing = AX_FALSE;
    AX_S32 nHttpStatusCode = RESPONSE_STATUS_OK_CODE;

    if (!bActionProcessing) {
        bActionProcessing = AX_TRUE;

        nHttpStatusCode = YieldProcessWebOpr(conn, E_REQ_TYPE_SWITCH_SCREEN);

        bActionProcessing = AX_FALSE;
    } else if (bActionProcessing) {
        // Response status: Not Acceptable
        nHttpStatusCode = RESPONSE_STATUS_FAILURE_CODE;
    }

    ResponseStatusCode(conn, nHttpStatusCode);
}

static AX_VOID ReportHttpStatus(AX_VOID) {
    printf("%s", httpStatsReport(HTTP_STATS_ALL));
}


/////////////////////////////////////////////////////////////////////////////////////////
typedef struct _HTTP_ACTION_INFO {
    cchar* name;
    HttpAction action;
} HTTP_ACTION_INFO;

const HTTP_ACTION_INFO g_httpActionInfo[] = {{"/action/login", LoginAction},
                                             {"/action/setting/capability", CapabilityAction},
                                             {"/action/preview/assist", AssistInfoAction},
                                             {"/action/setting/system", SystemAction},
                                             {"/action/setting/camera", CameraAction},
                                             {"/action/setting/image", ImageAction},
                                             {"/action/setting/audio", AudioAction},
                                             {"/action/setting/video", VideoAction},
                                             {"/action/setting/ai", AiAction},
                                             {"/action/setting/overlay", OverlayAction},
                                             {"/action/preview/info", PreviewInfoAction},
                                             {"/action/preview/stream", SwitchChnAction},
                                             {"/action/preview/snapshot", SnapshotAction},
                                             {"/action/preview/trigger", TriggerAction},
                                             {"/action/preview/ezoom", EZoomAction},
                                             {"/action/preview/3a_sync", Switch3ASyncAction},
                                             {"/action/preview/screen", SwitchScreenAction},
                                             {"/audio_0", WSAudioAction},
                                             {"/talk", WSTalkAction},
                                             {"/preview_0", WSPreviewAction},
                                             {"/preview_1", WSPreviewAction},
                                             {"/capture_0", WSCaptureAction},
                                             {"/capture_1", WSSnapshotAction},
                                             {"/events", WSEventsAction}};

CWebServer::CWebServer() : m_bServerStarted(AX_FALSE), m_pAppwebThread(nullptr) {
    for (AX_U32 i = 0; i < MAX_WS_CONN_NUM; i++) {
        m_arrConnStatus[i] = AX_FALSE;
    }
}

CWebServer::~CWebServer(AX_VOID) {
    for (AX_U32 i = 0; i < MAX_WS_CONN_NUM; i++) {
        if (m_arrChannelData[i].pRingBuffer) {
            delete m_arrChannelData[i].pRingBuffer;
            m_arrChannelData[i].pRingBuffer = nullptr;
        }
    }
}

AX_BOOL CWebServer::Init() {
    g_mapUserInfo["admin"] = "admin";
    char szName[64] = {0};
    sprintf(szName, "EVENTS_CH%d", WS_EVENTS_CHANNEL);
    RequestRingbuf(WS_EVENTS_CHANNEL, MAX_EVENTS_CHN_SIZE, COptionHelper::GetInstance()->GetWebEventsRingBufCount(), szName);
    return AX_TRUE;
}

AX_BOOL CWebServer::DeInit() {
    return AX_TRUE;
}

AX_BOOL CWebServer::Start() {
    LOG_MM_I(WEB, "+++");

    m_pAppwebThread = new thread(WebServerThreadFunc, this);

    LOG_MM_I(WEB, "---");

    return (m_pAppwebThread) ? AX_TRUE : AX_FALSE;
}

AX_BOOL CWebServer::Stop() {
    LOG_MM_C(WEB, "+++");

    // Make sure logout first
    LogOut();

    m_bServerStarted = AX_FALSE;

    {
        std::unique_lock<std::mutex> lck(m_mtxStatusCheck);
        m_bStatusCheckStarted = AX_FALSE;
        m_cvStatusCheck.notify_one();
    }

    if (m_pSendDataThread) {
        if (m_pSendDataThread->joinable()) {
            m_pSendDataThread->join();
        }
        delete m_pSendDataThread;
        m_pSendDataThread = nullptr;
    }
    if (m_pStatucCheckThread) {
        if (m_pStatucCheckThread->joinable()) {
            m_pStatucCheckThread->join();
        }
        delete m_pStatucCheckThread;
        m_pStatucCheckThread = nullptr;
    }
    if (m_pAppwebThread) {
        mprShutdown(MPR_EXIT_NORMAL, -1, MPR_EXIT_TIMEOUT);
        if (m_pAppwebThread->joinable()) {
            m_pAppwebThread->join();
        }
        delete m_pAppwebThread;
        m_pAppwebThread = nullptr;
    }

    LOG_MM_C(WEB, "---");
    return AX_TRUE;
}

AX_VOID CWebServer::RestartPreview() {
    // WEB_EVENTS_DATA_T tEvent;
    // tEvent.eType = E_WEB_EVENTS_TYPE_ReStartPreview;
    // g_webserver.SendEventsData(&tEvent);
}

AX_BOOL CWebServer::RequestRingbuf(AX_U32 nUniChn, AX_U32 nElementBuffSize, AX_U32 nBuffCount, string strName) {
    if (nUniChn >= MAX_WS_CONN_NUM) {
        return AX_FALSE;
    }

    WS_CHANNEL_DATA_T& tChnData = m_arrChannelData[nUniChn];
    tChnData.nChannel = nUniChn;
    if (tChnData.pRingBuffer != nullptr) {
        delete tChnData.pRingBuffer;
        tChnData.pRingBuffer = nullptr;
    }
    tChnData.pRingBuffer = new CAXRingBufferEx(nElementBuffSize, nBuffCount, strName.c_str());

    return tChnData.pRingBuffer == nullptr ? AX_FALSE : AX_TRUE;
}

AX_VOID* CWebServer::WebServerThreadFunc(AX_VOID* pThis) {
    LOG_MM_I(WEB, "+++");

    prctl(PR_SET_NAME, "APP_WEB_Server");

    CWebServer* pWebServer = (CWebServer*)pThis;
    Mpr* pMpr = nullptr;

    do {
        if ((pMpr = mprCreate(0, NULL, MPR_USER_EVENTS_THREAD)) == 0) {
            LOG_MM_E(WEB, "Cannot create runtime.");
            break;
        }

        if (httpCreate(HTTP_CLIENT_SIDE | HTTP_SERVER_SIDE) == 0) {
            LOG_MM_E(WEB, "Cannot create the HTTP services.");
            break;
        }

        if (maLoadModules() < 0) {
            LOG_MM_E(WEB, "Cannot load modules.");
            break;
        }

        // open appweb log
        // mprStartLogging("stderr:5", MPR_LOG_ANEW | MPR_LOG_DETAILED | MPR_LOG_CONFIG | MPR_LOG_CMDLINE);
        // httpStartTracing("stderr:3");
        g_pClients = mprCreateList(0, 0);
        mprAddRoot(g_pClients);
        mprStart();

        // web config must read from app default path.
        string strConfigDir = CCommonUtils::GetPPLConfigDir(AX_TRUE);
        if (strConfigDir.empty()) {
            LOG_MM_E(WEB, "Get configuration directory failed.");
            break;
        }
        strConfigDir += "/appweb.conf";

        if (maParseConfig(strConfigDir.c_str()) < 0) {
            LOG_MM_E(WEB, "Cannot parse the config file %s.", strConfigDir.c_str());
            break;
        }

        for (AX_U32 i = 0; i < sizeof(g_httpActionInfo) / sizeof(HTTP_ACTION_INFO); i++) {
            httpDefineAction(g_httpActionInfo[i].name, g_httpActionInfo[i].action);
        }

        if (httpStartEndpoints() < 0) {
            LOG_MM_E(WEB, "Cannot start the web server.");
            break;
        }

        LOG_M(WEB, "Appweb started.");

        pWebServer->m_bServerStarted = AX_TRUE;
        pWebServer->m_pSendDataThread = new thread(SendDataThreadFunc, pWebServer);

        pWebServer->m_bStatusCheckStarted = AX_TRUE;
        pWebServer->m_pStatucCheckThread = new thread(StatusCheckThreadFunc, pWebServer);

        mprSetMemNotifier(WebServerMemNotifier);

        if (COptionHelper::GetInstance()->IsEnableWebServerStatusCheck()) {
            mprCreateTimerEvent(NULL, "HttpStatusReport", 1000 * 60, (AX_VOID*)ReportHttpStatus, NULL, MPR_EVENT_CONTINUOUS | MPR_EVENT_QUICK);
        }

        mprServiceEvents(-1, 0);
    } while (false);

    LOG_MM_I(WEB, "---");

    return nullptr;
}

AX_VOID* CWebServer::SendDataThreadFunc(AX_VOID* pThis) {
    LOG_MM_I(WEB, "+++");
    prctl(PR_SET_NAME, "APP_WEB_Send");

    CWebServer* pWebServer = (CWebServer*)pThis;
    while (pWebServer->m_bServerStarted) {
        pWebServer->SendWSData();
        CElapsedTimer::mSleep(10);
    }

    LOG_MM_I(WEB, "---");
    return nullptr;
}

AX_VOID* CWebServer::StatusCheckThreadFunc(AX_VOID* pThis) {
    LOG_MM_I(WEB, "+++");
    prctl(PR_SET_NAME, "APP_WEB_Mem");

    CWebServer* pWebServer = (CWebServer*)pThis;
    while (pWebServer->m_bServerStarted && pWebServer->m_bStatusCheckStarted) {
        {
            std::unique_lock<std::mutex> lck(pWebServer->m_mtxStatusCheck);
            pWebServer->m_cvStatusCheck.wait_for(lck, std::chrono::milliseconds(60000), [pWebServer]() -> bool { return !pWebServer->m_bServerStarted || !pWebServer->m_bStatusCheckStarted;});
        }

        if (!pWebServer->m_bServerStarted || !pWebServer->m_bStatusCheckStarted) {
            break;
        }

        mprLock(g_pClients->mutex);
        // recovery RequestTimeout
        if (g_web_mem_limit_notified) {
            MprMemStats *ap = mprGetMemStats();
            HttpConn* client = nullptr;
            constexpr MprTicks RequestTimeout = 432000000; // 5days

            if (ap && ap->bytesAllocated > ap->bytesFree) {
                uint64 heapUsed = ap->bytesAllocated - ap->bytesFree;

                if (heapUsed < ap->warnHeap) {
                    for (AX_S32 next = 0; (client = (HttpConn*)MprListGetNextItem(g_pClients, &next)) != 0;) {
                        if (WS_STATE_OPEN != httpGetWebSocketState(client)) {
                            continue;
                        }

                        httpSetTimeout(client, RequestTimeout, -1);
                    }

                    g_web_mem_limit_notified = AX_FALSE;
                }
            }
        }
        mprUnlock(g_pClients->mutex);
    }

    LOG_MM_I(WEB, "---");
    return nullptr;
}

AX_VOID CWebServer::SendWSData(AX_VOID) {
    CWebServer* pWebServer = this;
    AX_S32 nSnsID = 0;
    AX_S32 nUniChannel = 0;
    AX_BOOL arrDataStatus[MAX_WS_CONN_NUM] = {AX_FALSE};
    HttpConn* client = nullptr;

    // gPrintHelper.Remove(E_PH_MOD_WEB_CONN, 0);
    mprLock(g_pClients->mutex);
    for (AX_S32 next = 0; (client = (HttpConn*)MprListGetNextItem(g_pClients, &next)) != 0;) {
        LOG_MM_D(WEB, "connect %p send data +++", client);

        if (WS_STATE_OPEN != httpGetWebSocketState(client)) {
            LOG_MM_D(WEB, "connect %p is closed", client);
            continue;
        }

        nSnsID = GetSnsIDFromWS(client);
        if (nSnsID == -1 || nSnsID >= 2) {
            LOG_MM_D(WEB, "connect %p nSnsID = %d is invalid", client, nSnsID);
            continue;
        }

        nUniChannel = GetChnFromWS(client);
        if (nUniChannel == -1 || nUniChannel >= MAX_WS_CONN_NUM) {
            if (nUniChannel != m_nSnapshotChannel) {
                LOG_MM_D(WEB, "connect %p nUniChannel = %d is invalid", client, nUniChannel);
            }
            continue;
        }
        // gPrintHelper.Add(E_PH_MOD_WEB_CONN, 0, 0);
        {
            std::lock_guard<std::mutex> guard(pWebServer->m_mtxConnStatus);
            if (!pWebServer->m_arrConnStatus[nUniChannel]) {
                pWebServer->m_arrConnStatus[nUniChannel] = AX_TRUE;
            }
        }

        if (!pWebServer->m_arrChannelData[nUniChannel].pRingBuffer) {
            /* Ringbuff is null */
            if (nUniChannel == 0) {
                LOG_MM_D(WEB, "connect %p nUniChannel = %d, pRingBuffer is empty", client, nUniChannel);
            }
            continue;
        }

        CAXRingElementEx* pData = pWebServer->m_arrChannelData[nUniChannel].pRingBuffer->Get();
        if (!pData) {
            /* Ringbuff is empty */
            if (nUniChannel == 0) {
                LOG_MM_D(WEB, "connect %p nUniChannel = %d pdata is empty", client, nUniChannel);
            }
            continue;
        }

        arrDataStatus[nUniChannel] = AX_TRUE;  // got data
        AX_U32 limit = client->rx->route->limits->webSocketsFrameSize;
        if (pData->nSize >= (AX_U32)limit) {
            LOG_MM_E(WEB, "Websocket data size(%u) exceeding max frame size(%u).", pData->nSize, limit);
        }

        if (nUniChannel == 0) {
            LOG_MM_D(WEB, "connect %p send data ---", client);
        }

        {
            auto msg = std::make_unique<WSMsg_T>();
            msg->conn = client;
            msg->packet = pData;
            auto pEvent =
                mprCreateEvent(client->dispatcher, "ws", 0, (AX_VOID*)SendHttpData, (AX_VOID*)msg.get(), MPR_EVENT_STATIC_DATA | MPR_EVENT_ALWAYS);
            if (!pEvent) {
                pData->pParent->Free(pData);
                msg.reset();
            } else {
                std::lock_guard<std::mutex> guard(g_mtxWSData);
                g_mapWSMsg.emplace(msg.get(), std::move(msg));
            }
        }
    }
    mprUnlock(g_pClients->mutex);

    pWebServer->UpdateConnStatus();
    for (AX_U32 i = 0; i < MAX_WS_CONN_NUM; i++) {
        if (arrDataStatus[i] && pWebServer->m_arrChannelData[i].pRingBuffer) {
            pWebServer->m_arrChannelData[i].pRingBuffer->Pop(AX_FALSE);
        }
    }
}

AX_VOID CWebServer::SendPreviewData(AX_U8 nUniChn, AX_VENC_PACK_T* pVencPack) {
    if (!m_bServerStarted) {
        return;
    }

    {
        /* Waiting for reading thread to refresh the websock conn status */
        std::lock_guard<std::mutex> guard(m_mtxConnStatus);
        AX_BOOL bConnect = m_arrConnStatus[nUniChn];
        if (!bConnect) {
            if (nUniChn == 0) {
                LOG_MM_D(WEB, "[%d] is not connected", nUniChn);
            }
            return;
        }
    }

    AX_BOOL bSuc = AX_FALSE;
    AX_VOID* data = pVencPack->pu8Addr;
    AX_U32 size = pVencPack->u32Len;
    AX_U64 nPts = pVencPack->u64PTS;
    AX_BOOL bIFrame = (AX_VENC_INTRA_FRAME == pVencPack->enCodingType || PT_MJPEG == pVencPack->enType) ? AX_TRUE : AX_FALSE;

    PTS_HEADER_T tHeader;
    tHeader.nDatalen = size;
    tHeader.nPts = nPts;
    CAXRingElementEx ele((AX_U8*)data, size, nPts, bIFrame, (AX_U8*)&tHeader, (AX_U32)(sizeof(tHeader)));
    bSuc = m_arrChannelData[nUniChn].pRingBuffer->Put(ele);
    if (nUniChn == 0 && !bSuc) {
        LOG_MM_W(WEB, "[%d] put data failed", nUniChn);
    }
}

AX_VOID CWebServer::SendPushImgData(AX_U8 nSnsID, AX_U8 nUniChn, AX_VOID* data, AX_U32 size, AX_U64 nPts /*= 0*/,
                                    AX_BOOL bIFrame /*= AX_TRUE*/, JPEG_DATA_INFO_T* pJpegInfo /*= nullptr*/) {
    if (!m_bServerStarted) {
        return;
    }

    if (0 == nSnsID && !m_arrCaptureEnable[nSnsID]) {
        return;
    }

    if (1 == nSnsID && !m_arrCaptureEnable[nSnsID]) {
        return;
    }

    {
        /* Waiting for reading thread to refresh the websock conn status */
        std::lock_guard<std::mutex> guard(m_mtxConnStatus);
        AX_BOOL bConnect = m_arrConnStatus[m_nCaptureChannel];
        if (!bConnect) {
            return;
        }
    }

    LOG_MM_D(WEB, "[%d] Send capture data, size=%d", m_nCaptureChannel, size);

    if (nullptr != pJpegInfo) {
        AX_CHAR szJsonData[256] = {0};
        /* construct json data info */
        if (pJpegInfo->eType == JPEG_TYPE_PLATE) {
            sprintf(szJsonData, "{\"snsId\": %d, \"type\": %d, \"attribute\": {\"plate\": {\"number\": \"%s\", \"color\": \"%s\"} }}",
                    nSnsID, pJpegInfo->eType, pJpegInfo->tPlateInfo.szNum, pJpegInfo->tPlateInfo.szColor);
        } else if (pJpegInfo->eType == JPEG_TYPE_FACE) {
            sprintf(szJsonData,
                    "{\"snsId\": %d, \"type\": %d, \"attribute\": {\"face\": {\"gender\": %d, \"age\": %d, \"mask\": \"%s\", \"info\": "
                    "\"%s\"}}}",
                    nSnsID, pJpegInfo->eType, pJpegInfo->tFaceInfo.nGender, pJpegInfo->tFaceInfo.nAge, pJpegInfo->tFaceInfo.szMask,
                    pJpegInfo->tFaceInfo.szInfo);
        } else {
            sprintf(szJsonData, "{\"snsId\": %d, \"type\": %d, \"attribute\": {\"src\": %d, \"width\": %d, \"height\": %d}}", nSnsID,
                    pJpegInfo->eType, pJpegInfo->tCaptureInfo.tHeaderInfo.nSnsSrc, pJpegInfo->tCaptureInfo.tHeaderInfo.nWidth,
                    pJpegInfo->tCaptureInfo.tHeaderInfo.nHeight);
        }

        AX_U32 nJsnLen = strlen(szJsonData);

        /* construct jpeg head */
        JpegHead tJpegHead;
        tJpegHead.nJsonLen = nJsnLen > 0 ? nJsnLen + 1 : 0;
        tJpegHead.nTotalLen = 4 /*magic*/ + 4 /*total len*/ + 4 /*tag*/ + 4 /*json len*/ + tJpegHead.nJsonLen;

        strcpy(tJpegHead.szJsonData, szJsonData);

        CAXRingElementEx _ele((AX_U8*)data, size, nPts, bIFrame, (AX_U8*)&tJpegHead, tJpegHead.nTotalLen);
        m_arrChannelData[m_nCaptureChannel].pRingBuffer->Put(_ele);
    } else {
        CAXRingElementEx ele((AX_U8*)data, size, nPts, bIFrame);
        m_arrChannelData[m_nCaptureChannel].pRingBuffer->Put(ele);
    }
}

AX_VOID CWebServer::SendCaptureData(AX_U8 nSnsID, AX_U8 nUniChn, AX_VOID* data, AX_U32 size, AX_U64 nPts /*= 0*/,
                                    AX_BOOL bIFrame /*= AX_TRUE*/, JPEG_DATA_INFO_T* pJpegInfo /*= nullptr*/) {
    if (!m_bServerStarted) {
        return;
    }

    if (0 == nSnsID && !m_arrCaptureEnable[nSnsID]) {
        return;
    }

    if (1 == nSnsID && !m_arrCaptureEnable[nSnsID]) {
        return;
    }

    {
        /* Waiting for reading thread to refresh the websock conn status */
        std::lock_guard<std::mutex> guard(m_mtxConnStatus);
        AX_BOOL bConnect = m_arrConnStatus[m_nCaptureChannel];
        if (!bConnect) {
            return;
        }
    }

    LOG_MM_D(WEB, "[%d] Send capture data, size=%d", m_nCaptureChannel, size);
    JPEG_TYPE_E eType = m_mapJencChnType[nUniChn];
    if (nullptr != pJpegInfo) {
        AX_CHAR szJsonData[256] = {0};
        /* construct json data info */
        sprintf(szJsonData, "{\"snsId\": %d, \"type\": %d, \"attribute\": {\"src\": %d, \"width\": %d, \"height\": %d}}", nSnsID, eType,
                pJpegInfo->tCaptureInfo.tHeaderInfo.nSnsSrc, pJpegInfo->tCaptureInfo.tHeaderInfo.nWidth,
                pJpegInfo->tCaptureInfo.tHeaderInfo.nHeight);

        AX_U32 nJsnLen = strlen(szJsonData);

        /* construct jpeg head */
        JpegHead tJpegHead;
        tJpegHead.nJsonLen = nJsnLen > 0 ? nJsnLen + 1 : 0;
        tJpegHead.nTotalLen = 4 /*magic*/ + 4 /*total len*/ + 4 /*tag*/ + 4 /*json len*/ + tJpegHead.nJsonLen;

        strcpy(tJpegHead.szJsonData, szJsonData);

        CAXRingElementEx _ele((AX_U8*)data, size, nPts, bIFrame, (AX_U8*)&tJpegHead, tJpegHead.nTotalLen);
        m_arrChannelData[m_nCaptureChannel].pRingBuffer->Put(_ele);
    } else {
        CAXRingElementEx ele((AX_U8*)data, size, nPts, bIFrame);
        m_arrChannelData[m_nCaptureChannel].pRingBuffer->Put(ele);
    }
}

AX_VOID CWebServer::SendSnapshotData(AX_VOID* data, AX_U32 size, AX_VOID* conn) {
    /* mprResetYield is needed when this function works as callback of SnapshotAction */
    // mprResetYield();

    if (!m_bServerStarted) {
        return;
    }

    AX_U8 nSnapshotChannelID = GetSnapshotChannel();
    HttpConn* client = nullptr;
    cchar* szHttpToken = GetTokenFromConn((HttpConn*)conn, AX_TRUE);
    // no mprLock(g_pClients->mutex) because sync call by web server snapshot command.
    for (AX_S32 next = 0; (client = (HttpConn*)MprListGetNextItem(g_pClients, &next)) != 0;) {
        if (WS_STATE_OPEN != httpGetWebSocketState(client)) {
            continue;
        }

        AX_U8 nUniChannel = GetChnFromWS(client);
        if (nUniChannel != nSnapshotChannelID) {
            continue;
        }

        cchar* szWSToken = GetTokenFromConn(client, AX_FALSE);
        if ((szWSToken == nullptr) ||
            (strcmp(szWSToken, szHttpToken) != 0)) {
            continue;
        }

        LOG_MM_I(WEB, "[%d] Send snapshot data, size=%d", nSnapshotChannelID, size);
        ssize nRet = httpSendBlock(client, WS_MSG_BINARY, (cchar*)data, size, HTTP_BLOCK);
        if (nRet >= 0) {
            break;
        }
    }
}

AX_VOID CWebServer::SendAudioData(AX_U8 nUniChn, AX_VOID* data, AX_U32 size, AX_U64 nPts /*= 0*/) {
    // AAC/PCM711A
    if (!m_bServerStarted) {
        return;
    }

    AX_U8 nAencChannel = GetAencChannel();
    {
        /* Waiting for reading thread to refresh the websock conn status */
        std::lock_guard<std::mutex> guard(m_mtxConnStatus);
        AX_BOOL bConnect = m_arrConnStatus[nAencChannel];
        if (!bConnect) {
            return;
        }
    }
    PTS_HEADER_T tHeader;
    tHeader.nDatalen = size;
    tHeader.nPts = nPts;

    CAXRingElementEx ele((AX_U8*)data, size, nPts, AX_TRUE, (AX_U8*)&tHeader, (AX_U32)(sizeof(tHeader)));
    m_arrChannelData[nAencChannel].pRingBuffer->Put(ele);
}

AX_BOOL CWebServer::SendEventsData(WEB_EVENTS_DATA_T* data) {
    if (!m_bServerStarted) {
        return AX_FALSE;
    }
    {
        /* Waiting for reading thread to refresh the websock conn status */
        std::lock_guard<std::mutex> guard(m_mtxConnStatus);
        AX_BOOL bConnect = m_arrConnStatus[WS_EVENTS_CHANNEL];
        if (!bConnect) {
            return AX_FALSE;
        }
    }

    AX_U8 nChnnelID = m_arrChannelData[WS_EVENTS_CHANNEL].nInnerIndex;
    string strEventsJson;
    if (E_WEB_EVENTS_TYPE_ReStartPreview == data->eType || E_WEB_EVENTS_TYPE_LogOut == data->eType) {
        strEventsJson = FormatPreviewEventsJson(data);
    } else if (E_WEB_EVENTS_TYPE_AED == data->eType) {
        strEventsJson = FormatAedEventsJson(data);
    } else {
        strEventsJson = FormatIVESEventsJson(data);
    }
    CAXRingElementEx ele((AX_U8*)strEventsJson.c_str(), strEventsJson.length(), nChnnelID);
    m_arrChannelData[WS_EVENTS_CHANNEL].pRingBuffer->Put(ele);

    return AX_TRUE;
}

std::string CWebServer::FormatPreviewEventsJson(WEB_EVENTS_DATA_T* pEvent) {
    AX_CHAR szEventJson[MAX_EVENTS_CHN_SIZE] = {0};
    AX_CHAR szDate[64] = {0};
    CElapsedTimer::GetInstance()->GetLocalTime(szDate, 16);
    snprintf(szEventJson, MAX_EVENTS_CHN_SIZE, "{\"events\": [{\"type\": %d, \"sensor\":%d, \"date\": \"%s\"}]}", pEvent->eType,
             pEvent->nReserved, szDate);

    std::string strEvent;
    strEvent = szEventJson;

    return strEvent;
}

std::string CWebServer::FormatIVESEventsJson(WEB_EVENTS_DATA_T* pEvent) {
    AX_CHAR szEventJson[MAX_EVENTS_CHN_SIZE] = {0};
    AX_CHAR szDate[64] = {0};
    CElapsedTimer::GetInstance()->GetLocalTime(szDate, 16);

    if (E_WEB_EVENTS_TYPE_MD == pEvent->eType) {
        snprintf(szEventJson, MAX_EVENTS_CHN_SIZE, "{\"events\": [{\"type\": %d, \"sensor\":%d, \"date\": \"%s\"}]}", pEvent->eType,
                 pEvent->nReserved, szDate);
    } else if (E_WEB_EVENTS_TYPE_OD == pEvent->eType) {
        snprintf(szEventJson, MAX_EVENTS_CHN_SIZE, "{\"events\": [{\"type\": %d, \"sensor\":%d,\"date\": \"%s\"}]}", pEvent->eType,
                 pEvent->nReserved, szDate);
    } else if (E_WEB_EVENTS_TYPE_SCD == pEvent->eType) {
        snprintf(szEventJson, MAX_EVENTS_CHN_SIZE, "{\"events\": [{\"type\": %d, \"sensor\":%d, \"date\": \"%s\"}]}", pEvent->eType,
                 pEvent->nReserved, szDate);
    } else if (E_WEB_EVENTS_TYPE_ReStartPreview == pEvent->eType) {
        snprintf(szEventJson, MAX_EVENTS_CHN_SIZE, "{\"events\": [{\"type\": %d, \"sensor\":%d, \"date\": \"%s\"}]}", pEvent->eType,
                 pEvent->nReserved, szDate);
    }
    std::string strEvent;
    strEvent = szEventJson;

    return strEvent;
}

std::string CWebServer::FormatAedEventsJson(WEB_EVENTS_DATA_T* pEvent) {
    AX_CHAR szEventJson[MAX_EVENTS_CHN_SIZE] = {0};
    AX_CHAR szDate[64] = {0};
    CElapsedTimer::GetInstance()->GetLocalTime(szDate, 16);

    snprintf(szEventJson, MAX_EVENTS_CHN_SIZE, "{\"events\": [{\"type\": %d, \"db\":%d, \"date\": \"%s\"}]}", pEvent->eType,
             pEvent->tAED.nDb, szDate);

    std::string strEvent;
    strEvent = szEventJson;

    return strEvent;
}

/* TODO: PrevChn -> UniChn mapping must be registered in order by modules */
static AX_U8 s_arrSnsPrevInnerIndex[2] = {0, 0};
AX_U8 CWebServer::RegistPreviewChnMappingInOrder(AX_U8 nSnsID, AX_U8 nUniChn, AX_U8 nType) {
    m_sMapPrevChn2UniChn[nSnsID][s_arrSnsPrevInnerIndex[nSnsID]] = std::make_pair(nUniChn, nType);
    return s_arrSnsPrevInnerIndex[nSnsID]++;
}

AX_VOID CWebServer::UpdateMediaTypeInPreviewChnMap(AX_U8 nSnsID, AX_U8 nUniChn, AX_U8 nType) {
    /* {SnsID: {PrevID: (UniChn, CodecType)}} */
    auto& snsIDMap = m_sMapPrevChn2UniChn[nSnsID];
    for (auto& item : snsIDMap) {
        // {PrevID: {UniChn, CodecType}}
        if (item.second.first == nUniChn) item.second.second = nType;
    }
}

AX_VOID CWebServer::RegistUniCaptureChn(AX_S8 nCaptureChn, JPEG_TYPE_E eType) {
    if (WS_CAPTURE_CHANNEL == m_nCaptureChannel) {
        /* Applies the first setting value */
        m_nCaptureChannel = nCaptureChn;
    }
    m_mapJencChnType[nCaptureChn] = eType;
}

AX_VOID CWebServer::UpdateConnStatus(AX_VOID) {
    AX_S32 nUniChannel = -1;
    AX_BOOL arrConnStatus[MAX_WS_CONN_NUM] = {AX_FALSE};
    HttpConn* client = nullptr;

    mprLock(g_pClients->mutex);
    for (AX_S32 next = 0; (client = (HttpConn*)MprListGetNextItem(g_pClients, &next)) != 0;) {
        if (WS_STATE_OPEN != httpGetWebSocketState(client)) {
            continue;
        }

        nUniChannel = GetChnFromWS(client);
        if (nUniChannel == -1 || nUniChannel >= MAX_WS_CONN_NUM) {
            continue;
        }

        arrConnStatus[nUniChannel] = AX_TRUE;
    }
    mprUnlock(g_pClients->mutex);

    std::lock_guard<std::mutex> guard(m_mtxConnStatus);
    for (AX_U32 i = 0; i < MAX_WS_CONN_NUM; ++i) {
        if (!arrConnStatus[i]) {
            m_arrConnStatus[i] = AX_FALSE;
        } else {
            m_arrConnStatus[i] = AX_TRUE;
        }
    }
}

AX_VOID CWebServer::LogOut() {
    WEB_EVENTS_DATA_T tEvent;
    tEvent.eType = E_WEB_EVENTS_TYPE_LogOut;
    if (SendEventsData(&tEvent)) {
        CElapsedTimer::mSleep(1500);  // Wait for Logout done
    }
}
