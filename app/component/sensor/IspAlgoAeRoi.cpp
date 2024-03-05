/**************************************************************************************************
 *
 * Copyright (c) 2019-2023 Axera Semiconductor (Ningbo) Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor (Ningbo) Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor (Ningbo) Co., Ltd.
 *
 **************************************************************************************************/

#include <string>
#include "IspAlgoAeRoi.h"
#include "ElapsedTimer.hpp"
#include "AppLogApi.h"
#include "AXTypeConverter.hpp"

#define AE_ROI "AE_ROI"

namespace {
#if 0
// SKEL RECT ==> FACE AE ROI normalized coordinates
static AX_ISP_AE_FACE_RECT_INPUT_PARAM_T AeRoiBoxConvert(AX_SKEL_RECT_T tRect,
                                                          AX_U32 nOriginalWidth,
                                                          AX_U32 nOriginalHeight,
                                                          AX_U32 nSensorWidth,
                                                          AX_U32 nSensorHeight,
                                                          AX_BOOL bMirror,
                                                          AX_BOOL bFlip,
                                                          AX_ROTATION_E eRotation,
                                                          AX_U32 nEZoomRatio,
                                                          AX_S16 nCenterOffsetX,
                                                          AX_S16 nCenterOffsetY) {
    if (nEZoomRatio > 0) {
        AX_U32 nStepW = nOriginalWidth / AX_EZOOM_MAX;
        AX_U32 nStepH = nOriginalHeight / AX_EZOOM_MAX;
        AX_WIN_AREA_T tCropRect;

        tCropRect.nWidth = nStepW * (AX_EZOOM_MAX - nEZoomRatio + 1);
        tCropRect.nHeight = nStepH * (AX_EZOOM_MAX - nEZoomRatio + 1);
        tCropRect.nStartX = (nOriginalWidth - tCropRect.nWidth) / 2;
        tCropRect.nStartY = (nOriginalHeight - tCropRect.nHeight) / 2;

        tRect.fX = tRect.fX * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;
        tRect.fY = tRect.fY * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;
        tRect.fW = tRect.fW * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;
        tRect.fH = tRect.fH * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;

        tRect.fX += tCropRect.nStartX;
        tRect.fY += tCropRect.nStartY;
    }

    AX_APP_ALGO_BOX_T tRectOut;

    tRectOut.fX = tRect.fX / nOriginalWidth;
    tRectOut.fY = tRect.fY / nOriginalHeight;
    tRectOut.fW = tRect.fW / nOriginalWidth;
    tRectOut.fH = tRect.fH / nOriginalHeight;
    tRectOut.nImgWidth = nSensorWidth;
    tRectOut.nImgHeight = nSensorHeight;

    AX_APP_ALGO_BOX_T tRectIn = tRectOut;

    if (bMirror || bFlip || eRotation != AX_ROTATION_0) {
      if (bMirror) {
          if (tRectOut.fX + tRectOut.fW > 1) {
              tRectOut.fX = 0;
          } else {
              tRectOut.fX = 1 - (tRectOut.fX + tRectOut.fW);
          }

          tRectIn.fX = tRectOut.fX;

          if (eRotation == AX_ROTATION_90) {
              eRotation = AX_ROTATION_270;
          } else if (eRotation == AX_ROTATION_270) {
              eRotation = AX_ROTATION_90;
          }
      }

      if (bFlip) {
          if (tRectOut.fY + tRectOut.fH > 1) {
              tRectOut.fY = 0;
          } else {
              tRectOut.fY = 1 - (tRectOut.fY + tRectOut.fH);
          }

          tRectIn.fY = tRectOut.fY;

          if (eRotation == AX_ROTATION_90) {
              eRotation = AX_ROTATION_270;
          } else if (eRotation == AX_ROTATION_270) {
              eRotation = AX_ROTATION_90;
          }
      }

      switch (eRotation) {
          case AX_ROTATION_0: {
              break;
          }
          case AX_ROTATION_90: {
              swap(tRectOut.nImgWidth, tRectOut.nImgHeight);
              tRectOut.fX = 1 - tRectIn.fY - tRectIn.fH;
              tRectOut.fY = tRectIn.fX;
              tRectOut.fW = tRectIn.fH;
              tRectOut.fH = tRectIn.fW;
              break;
          }
          case AX_ROTATION_180: {
              tRectOut.fX = 1 - tRectIn.fX - tRectIn.fW;
              tRectOut.fY = 1 - tRectIn.fY - tRectIn.fH;
              break;
          }
          case AX_ROTATION_270: {
              swap(tRectOut.nImgWidth, tRectOut.nImgHeight);
              tRectOut.fX = tRectIn.fY;
              tRectOut.fY = 1 - tRectIn.fX - tRectIn.fW;
              tRectOut.fW = tRectIn.fH;
              tRectOut.fH = tRectIn.fW;
              break;
          }
          default:
            break;
      }
    }

    AX_ISP_AE_FACE_RECT_INPUT_PARAM_T tFaceAeRoiRect;

    tFaceAeRoiRect.nFaceStartX = CAXTypeConverter::AeFloat2Int(tRectOut.fX, 1, 10, AX_FALSE);
    tFaceAeRoiRect.nFaceStartY = CAXTypeConverter::AeFloat2Int(tRectOut.fY, 1, 10, AX_FALSE);
    tFaceAeRoiRect.nFaceWidth = CAXTypeConverter::AeFloat2Int(tRectOut.fW, 1, 10, AX_FALSE);
    tFaceAeRoiRect.nFaceHeight = CAXTypeConverter::AeFloat2Int(tRectOut.fH, 1, 10, AX_FALSE);

    return tFaceAeRoiRect;
}
#endif

static AX_VOID AeRoiBoxConvert(std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem, CBaseSensor* pSensorInst) {
    if (!pSensorInst) {
        return;
    }

    AX_S32 nEZoomRatio = pSensorInst->GetSnsConfig().tEZoomAttr.nEZoomRatio;
    AX_BOOL bMirror = pSensorInst->GetSnsConfig().bMirror;
    AX_BOOL bFlip = pSensorInst->GetSnsConfig().bFlip;
    AX_ROTATION_E eRotation = pSensorInst->GetSnsConfig().eRotation;
    AX_SNS_ATTR_T tAttr = pSensorInst->GetSnsAttr();
    AX_U32 nImageWidth = tAttr.nWidth;
    AX_U32 nImageHeight = tAttr.nHeight;

    AX_F32 fCropStepW = 0;
    AX_F32 fCropStepH = 0;
    AX_F32 fCropWidth = 0;
    AX_F32 fCropHeight = 0;
    AX_F32 fCropStartX = 0;
    AX_F32 fCropStartY = 0;

    if (nEZoomRatio > 0) {
      fCropStepW = 1.0 / AX_EZOOM_MAX;
      fCropStepH = 1.0 / AX_EZOOM_MAX;

      fCropWidth = fCropStepW * (AX_EZOOM_MAX - nEZoomRatio + 1);
      fCropHeight = fCropStepH * (AX_EZOOM_MAX - nEZoomRatio + 1);
      fCropStartX = (1 - fCropWidth) / 2;
      fCropStartY = (1 - fCropHeight) / 2;
    }

    if (bMirror || bFlip || eRotation != AX_ROTATION_0 || nEZoomRatio > 0) {
        for (auto &stItem : stVecItem) {
            if (nEZoomRatio > 0) {
              stItem.tBox.fX = stItem.tBox.fX * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;
              stItem.tBox.fY = stItem.tBox.fY * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;
              stItem.tBox.fW = stItem.tBox.fW * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;
              stItem.tBox.fH = stItem.tBox.fH * (AX_EZOOM_MAX - nEZoomRatio + 1) / AX_EZOOM_MAX;

              stItem.tBox.fX += fCropStartX;
              stItem.tBox.fY += fCropStartY;
            }

            AX_APP_ALGO_BOX_T tBox = stItem.tBox;

            tBox.nImgWidth = nImageWidth;
            tBox.nImgHeight = nImageHeight;

            if (bMirror) {
                if (tBox.fX + tBox.fW > 1) {
                    tBox.fX = 0;
                } else {
                    tBox.fX = 1 - (tBox.fX + tBox.fW);
                }

                stItem.tBox.fX = tBox.fX;

                if (eRotation == AX_ROTATION_90) {
                    eRotation = AX_ROTATION_270;
                } else if (eRotation == AX_ROTATION_270) {
                    eRotation = AX_ROTATION_90;
                }
            }

            if (bFlip) {
                if (tBox.fY + tBox.fH > 1) {
                    tBox.fY = 0;
                } else {
                    tBox.fY = 1 - (tBox.fY + tBox.fH);
                }

                stItem.tBox.fY = tBox.fY;

                if (eRotation == AX_ROTATION_90) {
                    eRotation = AX_ROTATION_270;
                } else if (eRotation == AX_ROTATION_270) {
                    eRotation = AX_ROTATION_90;
                }
            }

            switch (eRotation) {
                case AX_ROTATION_0: {
                    break;
                }
                case AX_ROTATION_90: {
                    std::swap(tBox.nImgWidth, tBox.nImgHeight);
                    tBox.fX = 1 - stItem.tBox.fY - stItem.tBox.fH;
                    tBox.fY = stItem.tBox.fX;
                    tBox.fW = stItem.tBox.fW;
                    tBox.fH = stItem.tBox.fH;
                    break;
                }
                case AX_ROTATION_180: {
                    tBox.fX = 1 - stItem.tBox.fX - stItem.tBox.fW;
                    tBox.fY = 1 - stItem.tBox.fY - stItem.tBox.fH;
                    break;
                }
                case AX_ROTATION_270: {
                    std::swap(tBox.nImgWidth, tBox.nImgHeight);
                    tBox.fX = stItem.tBox.fY;
                    tBox.fY = 1 - stItem.tBox.fX - stItem.tBox.fW;
                    tBox.fW = stItem.tBox.fH;
                    tBox.fH = stItem.tBox.fW;
                    std::swap(tBox.fW, tBox.fH);
                    break;
                }
                default:
                    break;
            }

            stItem.tBox = tBox;
        }
    }
}
}

CIspAlgoAeRoi::CIspAlgoAeRoi(CBaseSensor *Sensor) : m_pSensorInst(Sensor) {
    m_nSnsId = m_pSensorInst->GetSnsConfig().nSnsID;
}

AX_BOOL CIspAlgoAeRoi::Start(const SENSOR_AE_ROI_ATTR_T& tAttr) {
    if (!m_tStatus.bMonitorStart && m_pSensorInst) {
        m_tAttr = tAttr;

        StartMonitor();
    }

    return AX_TRUE;
}

AX_BOOL CIspAlgoAeRoi::Stop() {
    LOG_MM_C(AE_ROI, "[%d] +++", m_nSnsId);

    {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_Thread.Stop();
        m_cv.notify_one();
    }

    m_Thread.Join();

    m_tStatus.bMonitorStart = AX_FALSE;
    m_tStatus.bUpdateTrigger = AX_FALSE;

    LOG_MM_C(AE_ROI, "[%d] ---", m_nSnsId);

    return AX_TRUE;
}

AX_BOOL CIspAlgoAeRoi::StartMonitor() {
    if (m_tAttr.bEnable) {
        std::string threadName = "APP_AeRoi_" + std::to_string(m_nSnsId);
        if (!m_Thread.Start([this](AX_VOID* pArg) -> AX_VOID { Monitor(pArg); }, nullptr, threadName.c_str())) {
            return AX_FALSE;
        }

        m_tStatus.bMonitorStart = AX_TRUE;
    }

    return AX_TRUE;
}

AX_BOOL CIspAlgoAeRoi::Update(const SENSOR_AE_ROI_ATTR_T& tAttr) {
    if (m_tStatus.bMonitorStart) {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_tAttr = tAttr;
        m_tStatus.bUpdateTrigger = AX_TRUE;
        m_cv.notify_one();
    } else {
        Start(tAttr);
    }

    return AX_TRUE;
}

AX_BOOL CIspAlgoAeRoi::UpdateAeRoi(const std::vector<AX_APP_ALGO_AE_ROI_ITEM_T>& stVecItem) {
    if (m_tAttr.bEnable) {
        std::unique_lock<std::mutex> lck(m_mtx);
        m_stVecItem = stVecItem;
        m_tStatus.bUpdateTrigger = AX_TRUE;
        m_cv.notify_one();
    }

    return AX_TRUE;
}

AX_S32 CIspAlgoAeRoi::Monitor(AX_VOID* pArg) {
    AX_BOOL bEnable = m_tAttr.bEnable;

    if (m_pSensorInst) {
        m_pSensorInst->SetAeRoiAttr(m_tAttr.bEnable);
    }

    while (m_Thread.IsRunning()) {
        std::vector<AX_APP_ALGO_AE_ROI_ITEM_T> stVecItem;

        {
            std::unique_lock<std::mutex> lck(m_mtx);
            m_cv.wait(lck, [this]() -> bool { return !this->m_Thread.IsRunning() || this->m_tStatus.bUpdateTrigger; });

            if (!m_Thread.IsRunning()) {
                break;
            }

            if (m_tStatus.bUpdateTrigger) {
                m_tStatus.bUpdateTrigger = AX_FALSE;

                if (bEnable != m_tAttr.bEnable) {
                    bEnable = m_tAttr.bEnable;
                    if (m_pSensorInst) {
                        m_pSensorInst->SetAeRoiAttr(bEnable);
                    }
                }

                if (!bEnable) {
                    m_Thread.Stop();
                    m_tStatus.bMonitorStart = AX_FALSE;
                    break;
                }
            }

            stVecItem = m_stVecItem;
        }

        if (m_pSensorInst) {
            AeRoiBoxConvert(stVecItem, m_pSensorInst);

            m_pSensorInst->SetAeRoi(stVecItem);
        }
    }

    return 0;
}
