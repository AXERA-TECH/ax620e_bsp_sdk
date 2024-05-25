/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef _AX_RINGBUFFER_EX_H_
#define _AX_RINGBUFFER_EX_H_

#include <string.h>
#include <mutex>
#include "AppLogApi.h"
#include "ax_base_type.h"
#include "GlobalDef.h"

#define RING_MIN(x, y)    ((x) < (y) ? (x) : (y))
#define AXRINGEX "RINGEX"

#define RING_TAIL_SIZE  (4)
#define RING_ALIGN_TO(n, s) ((((n) + (s) - 1) / (s)) * (s))

#define RING_CHECK_PTR(p) do {\
    if (m_nRingSize > 0 && (p < m_pRingBuf || p >= (m_pRingBuf+m_nRingSize))) {\
        LOG_MM_E(AXRINGEX, "[%s] ptr(%p) is overflow [%p, %p)", m_szName, p, m_pRingBuf, m_pRingBuf + m_nRingSize);\
    }\
} while(0)

class CAXRingBufferEx;

class CAXRingElementEx {
public:
    CAXRingElementEx() {
        this->pBuf = nullptr;
        this->nSize = 0;
        this->pBuf2 = nullptr;
        this->nSize2 = 0;
        this->bIFrame = AX_FALSE;
        this->nPts = 0;
        this->nRefCount = 0;
        this->pParent = nullptr;
        this->pHeadBuf = nullptr;
        this->nHeadSize = 0;
        this->nTotalSize = 0;
    }

    CAXRingElementEx(AX_U8* pBuf, AX_U32 nSize, AX_U64 u64PTS = 0, AX_BOOL isIFrame = AX_FALSE, AX_U8* pHeadBuf = nullptr, AX_U32 nHeadSize = 0) {
        this->pBuf = pBuf;
        this->nSize = nSize;
        this->pBuf2 = nullptr;
        this->nSize2 = 0;
        this->nPts = u64PTS;
        this->bIFrame = isIFrame;
        this->nRefCount = 0;
        this->pParent = nullptr;
        this->pHeadBuf = pHeadBuf;
        this->nHeadSize = nHeadSize;
        this->nTotalSize = 0;
    }

    AX_VOID CopyFrom(CAXRingElementEx& element) {
        if (this->pBuf) {
            if (element.pHeadBuf && element.nHeadSize > 0) {
                if (this->nSize >= element.nHeadSize) {
                    memcpy(this->pBuf, element.pHeadBuf, element.nHeadSize);
                    memcpy(this->pBuf + element.nHeadSize, element.pBuf, this->nSize - element.nHeadSize);
                    if (this->nSize2 > 0) {
                        memcpy(this->pBuf2, element.pBuf + (this->nSize - element.nHeadSize), this->nSize2);
                    }
                } else {
                    memcpy(this->pBuf, element.pHeadBuf, this->nSize);
                    memcpy(this->pBuf2, element.pHeadBuf + this->nSize, element.nHeadSize - this->nSize);
                    memcpy(this->pBuf2 + (element.nHeadSize - this->nSize), element.pBuf, this->nSize2 - (element.nHeadSize - this->nSize));
                }

            } else {
                memcpy(this->pBuf, element.pBuf, this->nSize);
                if (this->nSize2 > 0) {
                    memcpy(this->pBuf2, element.pBuf + this->nSize, this->nSize2);
                }
            }
        }
        this->nHeadSize = element.nHeadSize;
        this->pHeadBuf = nullptr;
        this->nPts = element.nPts;
        this->bIFrame = element.bIFrame;
    }

    AX_S32 IncreaseRefCount() {
        return ++nRefCount;
    }

    AX_S32 DecreaseRefCount(AX_BOOL bForceClear) {
        if (bForceClear) {
            nRefCount = 0;
        } else {
            --nRefCount;
            if (nRefCount < 0) {
                nRefCount = 0;
            }
        }
        return nRefCount;
    }

    AX_S32 GetRefCount() {
        return nRefCount;
    }

    AX_VOID Clear() {
        this->nTotalSize = 0;
        this->nSize = 0;
        this->nSize2 = 0;
        this->bIFrame = AX_FALSE;
        this->nPts = 0;
        this->nRefCount = 0;
        this->nHeadSize = 0;
    }

public:
    AX_U32 nTotalSize;  //内部使用，且是sizeof(CAXRingBufferEx)对齐的。
    AX_U32 nSize;
    AX_U64 nPts;
    AX_BOOL bIFrame;
    AX_U32 nHeadSize;
    AX_S32 nRefCount;
    AX_U32 nSize2;
    AX_U8* pBuf{nullptr};
    AX_U8* pBuf2{nullptr};
    AX_U8* pHeadBuf{nullptr};
    CAXRingBufferEx* pParent{nullptr};
};


class CAXRingBufferEx {
public:
    CAXRingBufferEx(AX_U32 nElementBuffSize, AX_U32 nElementCount, const char* pszName = nullptr) {
        m_nRingSize = nElementBuffSize * nElementCount;
        m_nRingSize = RING_ALIGN_TO(m_nRingSize, sizeof(CAXRingElementEx)); // 确保CAXRingElementEx不会被分割
        m_pRingBuf = (AX_U8 *)AX_MALLOC(m_nRingSize);
        memset(m_pRingBuf, 0x0, m_nRingSize);
        m_nHeader = 0;
        m_nPopStart = 0;
        m_nTail = 0;
        m_bHasLost = AX_FALSE;
        m_szName[0] = 0;
        if (pszName && strlen(pszName)) {
            strncpy(m_szName, pszName, sizeof(m_szName) - 1);
            m_szName[sizeof(m_szName) - 1] = '\0';
        }
    }

    ~CAXRingBufferEx(AX_VOID) {
        m_mutex.lock();
        m_nHeader = 0;
        m_nTail = 0;
        m_nPopStart = 0;
        if (nullptr == m_pRingBuf) {
            return;
        }
        AX_FREE(m_pRingBuf);
        m_mutex.unlock();
    }

    AX_BOOL IsFull() {
        std::lock_guard<std::mutex> lck(m_mutex);
        return (m_nTail - m_nHeader) == m_nRingSize ? AX_TRUE : AX_FALSE;
    }

    AX_BOOL IsEmpty() {
        std::lock_guard<std::mutex> lck(m_mutex);
        return (m_nTail == m_nHeader) ? AX_TRUE : AX_FALSE;
    }

    AX_BOOL Put(CAXRingElementEx& element) {
        std::lock_guard<std::mutex> lck(m_mutex);
        //LOG_MM_C(AXRINGEX, "[%s] +++, tail=%llu, head=%llu, pop=%llu, size=%u, iFrame=%d", m_szName, m_nTail, m_nHeader, m_nPopStart, element.nSize, element.bIFrame);
        AX_U32 nSize = element.nSize + element.nHeadSize;
        AX_U32 nEleCapacity = nSize + sizeof(CAXRingElementEx) + RING_TAIL_SIZE;
        nEleCapacity = RING_ALIGN_TO(nEleCapacity, sizeof(CAXRingElementEx));

        if (!m_pRingBuf || nEleCapacity > m_nRingSize) {
            // must not go to here
            if (element.bIFrame) {
                m_bHasLost = AX_TRUE;
            }
            LOG_MM_E(AXRINGEX, "[%s] ---, drop one frame for size: %u is bigger than buffer size:%u", m_szName, nEleCapacity, m_nRingSize);
            return AX_FALSE;
        }

        AX_U64 nHead = RING_MIN(m_nPopStart, m_nHeader);
        if ((m_nTail - nHead) > m_nRingSize) {
            LOG_MM_E(AXRINGEX, "[%s] ---, tail(%llu) - head(%llu) is large than ringsize(%u)", m_szName, m_nTail, nHead, m_nRingSize);
            return AX_FALSE;
        }

        AX_U32 nLeft = m_nRingSize - (m_nTail - nHead);

        if (nLeft < nEleCapacity) {
            if (element.bIFrame) {
                // find enough space to replace the tail frame(s) with new I Frame
                do {
                    AX_U32 nPreEleSize = *(AX_U32*)(m_pRingBuf + ((m_nTail - 4) % m_nRingSize));
                    CAXRingElementEx * pEle = (CAXRingElementEx*)(m_pRingBuf + ((m_nTail - nPreEleSize) % m_nRingSize));
                    if (nPreEleSize != pEle->nTotalSize || nPreEleSize > m_nRingSize) {
                        LOG_MM_E(AXRINGEX, "[%s] element size (%u, %u) is invalid", m_szName, nPreEleSize, pEle->nTotalSize);
                        break;
                    }

                    if (pEle->GetRefCount() == 0) {
                        m_nTail -= nPreEleSize;
                        nLeft = m_nRingSize - (m_nTail - nHead);
                    } else {
                        break;
                    }
                } while (nLeft < nEleCapacity);

                if (nLeft >= nEleCapacity) {
                    m_bHasLost = AX_FALSE;
                    //LOG_MM_C(AXRINGEX, "[%s] replace last one with i frame for ring is full", m_szName);
                } else {
                    m_bHasLost = AX_TRUE;
                    //LOG_MM_C(AXRINGEX, "[%s] ---, drop one i frame for ring is full", m_szName);
                    return AX_FALSE;
                }

            } else {
                m_bHasLost = AX_TRUE;  // mark to lost all behind P Frame
                //LOG_MM_C(AXRINGEX, "[%s] ---, drop one p frame for ring is full", m_szName);
                return AX_FALSE;
            }
        }

        AX_U32 offset = m_nTail % m_nRingSize;
        AX_U32 offset2 = (m_nTail + sizeof(CAXRingElementEx)) % m_nRingSize;
        CAXRingElementEx * pEle = (CAXRingElementEx*)(m_pRingBuf + offset);
        RING_CHECK_PTR((AX_U8*)(pEle + 1) - 1);
        pEle->Clear();

        pEle->pBuf = (AX_U8*)(m_pRingBuf + offset2);
        pEle->nSize = RING_MIN(nSize, (m_nRingSize - offset2));
        pEle->pBuf2 = m_pRingBuf;
        pEle->nSize2 = nSize - pEle->nSize;

        RING_CHECK_PTR(pEle->pBuf);
        RING_CHECK_PTR(pEle->pBuf2);
        RING_CHECK_PTR(pEle->pBuf + pEle->nSize - 1);
        if (pEle->nSize2 > 0) {
            RING_CHECK_PTR(pEle->pBuf2 + pEle->nSize2 - 1);
        }

        pEle->CopyFrom(element);
        pEle->IncreaseRefCount();
        pEle->pParent = this;
        pEle->nTotalSize = nEleCapacity;
        SetElementTailSize(pEle);
        m_nTail += nEleCapacity;

        // clear next
        nLeft = m_nRingSize - (m_nTail - nHead);
        if (nLeft >= sizeof(CAXRingElementEx) && nLeft < m_nRingSize) {
            pEle = (CAXRingElementEx*)(m_pRingBuf + (m_nTail % m_nRingSize));
            pEle->Clear();
            RING_CHECK_PTR((AX_U8*)(pEle + 1) - 1);
        }

        //LOG_MM_C(AXRINGEX, "[%s] ---, tail=%llu, head=%llu, pop=%llu", m_szName, m_nTail, m_nHeader, m_nPopStart);
        return AX_TRUE;
    }

    CAXRingElementEx* Get() {
        CAXRingElementEx* element = nullptr;
        std::lock_guard<std::mutex> lck(m_mutex);
        if (m_nHeader == m_nTail) {
            return element;
        }
        //LOG_MM_C(AXRINGEX, "[%s] +++, tail=%llu, head=%llu, pop=%llu", m_szName, m_nTail, m_nHeader, m_nPopStart);
        element = (CAXRingElementEx*)(m_pRingBuf + (m_nHeader % m_nRingSize));
        if (!CheckElement(element)) {
            LOG_MM_E(AXRINGEX, "[%s] element size (%u) is invalid", m_szName, element->nTotalSize);
            return nullptr;
        }

        element->IncreaseRefCount();
        RING_CHECK_PTR((AX_U8*)(element + 1) - 1);

        //LOG_MM_C(AXRINGEX, "[%s] ---, tail=%llu, head=%llu, pop=%llu", m_szName, m_nTail, m_nHeader, m_nPopStart);
        return element;
    }

    AX_BOOL Pop(AX_BOOL bForce = AX_TRUE) {
        std::lock_guard<std::mutex> lck(m_mutex);
        if (m_nHeader == m_nTail) {
            return AX_FALSE;
        }
        //LOG_MM_C(AXRINGEX, "[%s] +++, tail=%llu, head=%llu, pop=%llu", m_szName, m_nTail, m_nHeader, m_nPopStart);
        CAXRingElementEx* element = (CAXRingElementEx*)(m_pRingBuf + (m_nHeader % m_nRingSize));
        if (!CheckElement(element)) {
            LOG_MM_E(AXRINGEX, "[%s] element size (%u) is invalid", m_szName, element->nTotalSize);
            return AX_FALSE;
        }
        AX_S32 nRefCount = element->DecreaseRefCount(bForce);
        RING_CHECK_PTR((AX_U8*)(element + 1) - 1);
        if (nRefCount == 0 && m_nPopStart == m_nHeader) {
            m_nPopStart += element->nTotalSize;
        }
        m_nHeader += element->nTotalSize;
        //LOG_MM_C(AXRINGEX, "[%s] ---, tail=%llu, head=%llu, pop=%llu", m_szName, m_nTail, m_nHeader, m_nPopStart);
        return AX_TRUE;
    }

    AX_VOID Free(CAXRingElementEx* ele, AX_BOOL bForce = AX_FALSE) {
        if (!ele) {
            return;
        }
        std::lock_guard<std::mutex> lck(m_mutex);
        if (!m_pRingBuf) {
            return;
        }

        if (!CheckElement(ele)) {
            LOG_MM_E(AXRINGEX, "[%s] element size (%u) is invalid", m_szName, ele->nTotalSize);
            return;
        }
        //LOG_MM_C(AXRINGEX, "[%s] +++, tail=%llu, head=%llu, pop=%llu, ele=%p", m_szName, m_nTail, m_nHeader, m_nPopStart, ele);
        CAXRingElementEx* elementPopStart = (CAXRingElementEx*)(m_pRingBuf + (m_nPopStart % m_nRingSize));
        AX_S32 nRefCount = ele->DecreaseRefCount(bForce);
        RING_CHECK_PTR((AX_U8*)(ele + 1) - 1);
        if (nRefCount == 0 && ele == elementPopStart) {
            m_nPopStart += ele->nTotalSize;
            while (m_nPopStart < m_nHeader) {
                elementPopStart = (CAXRingElementEx*)(m_pRingBuf + (m_nPopStart % m_nRingSize));
                if (elementPopStart->GetRefCount() == 0) {
                    m_nPopStart += elementPopStart->nTotalSize;
                } else {
                    break;
                }
            }
        }
        //LOG_MM_C(AXRINGEX, "[%s] ---, tail=%llu, head=%llu, pop=%llu", m_szName, m_nTail, m_nHeader, m_nPopStart);
    }

    AX_VOID Clear() {
        std::lock_guard<std::mutex> lck(m_mutex);
        //LOG_MM_C(AXRINGEX, "[%s] Clear ..., tail=%llu, head=%llu", m_szName, m_nTail, m_nHeader);
        if (m_pRingBuf) {
            m_nHeader = 0;
            m_nPopStart = 0;
            m_nTail = 0;
            m_bHasLost = AX_FALSE;
            CAXRingElementEx* element = (CAXRingElementEx*)(m_pRingBuf);
            element->Clear();
        }
    }

    AX_U32 Size() {
        std::lock_guard<std::mutex> lck(m_mutex);
        if (m_nTail < m_nHeader) {
            return 0;
        }
        return m_nTail - m_nHeader;
    }
private:
    AX_BOOL CheckElement(CAXRingElementEx* ele) {
        if ((AX_U8*)ele < m_pRingBuf || (AX_U8*)ele >= (m_pRingBuf + m_nRingSize)) {
            LOG_MM_E(AXRINGEX, "[%s] element ptr(%p) is invalid (ringptr=%p, size=%u)", m_szName, ele, m_pRingBuf, m_nRingSize);
            return AX_FALSE;
        }

        AX_U32 nTailSize = 0;
        if (ele->nSize2 > 0) {
            if (ele->pBuf2 < m_pRingBuf || ele->pBuf2 >= (m_pRingBuf + m_nRingSize)) {
                LOG_MM_E(AXRINGEX, "[%s] element pBuf2(%p) is invalid (ringptr=%p, size=%u)", m_szName, ele->pBuf2, m_pRingBuf, m_nRingSize);
                return AX_FALSE;
            }
            nTailSize = *(AX_U32*)(ele->pBuf2 + (ele->nTotalSize - ele->nSize - sizeof(CAXRingElementEx) - 4));
            if (nTailSize != ele->nTotalSize) {
                LOG_MM_E(AXRINGEX, "[%s] element nTailSize(%u) != nTotalSize(%u)", m_szName, nTailSize, ele->nTotalSize);
                return AX_FALSE;
            }
        } else {
            if (ele->pBuf < m_pRingBuf || ele->pBuf >= (m_pRingBuf + m_nRingSize)) {
                LOG_MM_E(AXRINGEX, "[%s] element pBuf(%p) is invalid (ringptr=%p, size=%u)", m_szName, ele->pBuf, m_pRingBuf, m_nRingSize);
                return AX_FALSE;
            }
            AX_U32 nOffset = ((AX_U32)((AX_U8*)ele - m_pRingBuf) + ele->nTotalSize - 4) % m_nRingSize;
            nTailSize = *(AX_U32*)(m_pRingBuf + nOffset);

            if (nTailSize != ele->nTotalSize) {
                LOG_MM_E(AXRINGEX, "[%s] element nTailSize(%u) != nTotalSize(%u)", m_szName, nTailSize, ele->nTotalSize);
                return AX_FALSE;
            }
        }

        return AX_TRUE;
    }

    AX_VOID SetElementTailSize(CAXRingElementEx* ele) {
        AX_U32 nTailOffset = (m_nTail + ele->nTotalSize - 4) % m_nRingSize;
        *(AX_U32*)(m_pRingBuf + nTailOffset) = ele->nTotalSize;
    }

private:
    AX_U8* m_pRingBuf;
    AX_U32 m_nRingSize;
    AX_U64 m_nHeader;
    AX_U64 m_nPopStart;
    AX_U64 m_nTail;
    AX_BOOL m_bHasLost;
    std::mutex m_mutex;
    char m_szName[64];
};
#endif  // _AX_RINGBUFFER_EX_H_