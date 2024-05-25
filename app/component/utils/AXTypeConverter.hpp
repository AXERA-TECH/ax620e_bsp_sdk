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

#include <string.h>
#include "GlobalDef.h"
#include "BaseLinkage.h"
#include "ax_global_type.h"
#include "ax_venc_rc.h"
#include "GlobalDef.h"

class CAXTypeConverter {
public:
    /* 2M: H264 2M, H265: 1M; 4M: H264 4M, H265: 2M; 4K: H264: 8M, H265:4M */
    static AX_U32 GetVencBitrate(AX_PAYLOAD_TYPE_E enType, AX_S32 nWidth, AX_S32 nHeight, const AX_U32& nBitrate) {
        if (nBitrate <= 0) {
            if (PT_H264 == enType || PT_MJPEG == enType) {
                // 4K
                if (nWidth >= 3840) {
                    return 8192;
                }
                // 4M
                else if (nWidth >= 2560) {
                    return 4096;
                }
                // 2M
                else if (nWidth >= 1920) {
                    return 2048;
                }
                else {
                    return ALIGN_COMM_DOWN(nWidth * nHeight / 1000, 100);
                }
            } else if (PT_H265 == enType) {
                // 4K
                if (nWidth >= 3840) {
                    return 4096;
                }
                // 4M
                else if (nWidth >= 2560) {
                    return 2048;
                }
                // 2M
                else if (nWidth >= 1920) {
                    return 1024;
                }
                else {
                    return ALIGN_COMM_DOWN(nWidth * nHeight / 1000, 100);
                }
            }

            return 4096;
        }

        return nBitrate;
    }

    static AX_U32 GetVencBufSize(AX_PAYLOAD_TYPE_E enType, AX_S32 nWidth, AX_S32 nHeight) {
        // 4M
        if (nWidth >= 2560) {
            return (AX_U32)(nWidth * nHeight / 2);
        }

        return (AX_U32)(nWidth * nHeight * 3 / 4);
    }

    static AX_PAYLOAD_TYPE_E Int2EncoderType(AX_U32 nEncodeType) {
        if (0 == nEncodeType) {
            return PT_H264;
        } else if (2 == nEncodeType) {
            return PT_H265;
        } else if (1 == nEncodeType) {
            return PT_MJPEG;
        }

        return PT_H264;
    }

    static AX_U32 EncoderType2Int(AX_PAYLOAD_TYPE_E eEncodeType) {
        if (PT_H264 == eEncodeType) {
            return 0;
        } else if (PT_H265 == eEncodeType) {
            return 2;
        } else if (PT_MJPEG == eEncodeType) {
            return 1;
        }

        return 0;
    }
    static AX_VENC_RC_MODE_E Str2RcMode(std::string strRcModeName, AX_PAYLOAD_TYPE_E ePayloadType) {
        if (PT_H264 == ePayloadType) {
            if (strRcModeName == "CBR") {
                return AX_VENC_RC_MODE_H264CBR;
            } else if (strRcModeName == "VBR") {
                return AX_VENC_RC_MODE_H264VBR;
            } else if (strRcModeName == "FIXQP") {
                return AX_VENC_RC_MODE_H264FIXQP;
            } else if (strRcModeName == "AVBR") {
                return AX_VENC_RC_MODE_H264AVBR;
            } else if (strRcModeName == "CVBR") {
                return AX_VENC_RC_MODE_H264CVBR;
            }
        } else if (PT_H265 == ePayloadType) {
            if (strRcModeName == "CBR") {
                return AX_VENC_RC_MODE_H265CBR;
            } else if (strRcModeName == "VBR") {
                return AX_VENC_RC_MODE_H265VBR;
            } else if (strRcModeName == "FIXQP") {
                return AX_VENC_RC_MODE_H265FIXQP;
            } else if (strRcModeName == "AVBR") {
                return AX_VENC_RC_MODE_H265AVBR;
            } else if (strRcModeName == "CVBR") {
                return AX_VENC_RC_MODE_H265CVBR;
            }
        } else if (PT_MJPEG == ePayloadType) {
            if (strRcModeName == "CBR") {
                return AX_VENC_RC_MODE_MJPEGCBR;
            } else if (strRcModeName == "VBR") {
                return AX_VENC_RC_MODE_MJPEGVBR;
            } else if (strRcModeName == "FIXQP") {
                return AX_VENC_RC_MODE_MJPEGFIXQP;
            }
        }

        return AX_VENC_RC_MODE_H264CBR;
    }

    static AX_U32 RcMode2Int(AX_VENC_RC_MODE_E eRcMode) {
        AX_U32 nRcMode = AX_VENC_RC_MODE_BUTT;
        switch (eRcMode) {
            case AX_VENC_RC_MODE_H264CBR:
            case AX_VENC_RC_MODE_H265CBR:
            case AX_VENC_RC_MODE_MJPEGCBR:
                nRcMode = 0;
                break;
            case AX_VENC_RC_MODE_H264VBR:
            case AX_VENC_RC_MODE_H265VBR:
            case AX_VENC_RC_MODE_MJPEGVBR:
                nRcMode = 1;
                break;
            case AX_VENC_RC_MODE_H264FIXQP:
            case AX_VENC_RC_MODE_H265FIXQP:
            case AX_VENC_RC_MODE_MJPEGFIXQP:
                nRcMode = 2;
                break;
            case AX_VENC_RC_MODE_H264AVBR:
            case AX_VENC_RC_MODE_H265AVBR:
                nRcMode = 3;
                break;
            case AX_VENC_RC_MODE_H264CVBR:
            case AX_VENC_RC_MODE_H265CVBR:
                nRcMode = 4;
                break;
            default:
                break;
        }
        return nRcMode;
    }

    static AX_VENC_RC_MODE_E FormatRcMode(AX_U8 nEncoderType, AX_U8 nRcType) {
        switch (nEncoderType) {
            case 0: { /* H264 */
                switch (nRcType) {
                    case 0: { /* CBR */
                        return AX_VENC_RC_MODE_H264CBR;
                    }
                    case 1: { /* VBR */
                        return AX_VENC_RC_MODE_H264VBR;
                    }
                    case 2: { /* FIXQP */
                        return AX_VENC_RC_MODE_H264FIXQP;
                    }
                    case 3: { /* AVBR */
                        return AX_VENC_RC_MODE_H264AVBR;
                    }
                    case 4: { /* CVBR */
                        return AX_VENC_RC_MODE_H264CVBR;
                    }
                    default:
                        break;
                }
            }
            case 1: { /* MJPEG */
                switch (nRcType) {
                    case 0: { /* CBR */
                        return AX_VENC_RC_MODE_MJPEGCBR;
                    }
                    case 1: { /* VBR */
                        return AX_VENC_RC_MODE_MJPEGVBR;
                    }
                    case 2: { /* FIXQP */
                        return AX_VENC_RC_MODE_MJPEGFIXQP;
                    }
                    default:
                        break;
                }
            }
            case 2: { /* H265 */
                switch (nRcType) {
                    case 0: { /* CBR */
                        return AX_VENC_RC_MODE_H265CBR;
                    }
                    case 1: { /* VBR */
                        return AX_VENC_RC_MODE_H265VBR;
                    }
                    case 2: { /* FIXQP */
                        return AX_VENC_RC_MODE_H265FIXQP;
                    }
                    case 3: { /* AVBR */
                        return AX_VENC_RC_MODE_H265AVBR;
                    }
                    case 4: { /* CVBR */
                        return AX_VENC_RC_MODE_H265CVBR;
                    }
                    default:
                        break;
                }
            }
            default:
                break;
        }
        return AX_VENC_RC_MODE_BUTT;
    }

    static std::string ModType2String(PPL_MODULE_TYPE_E eType) {
        switch (eType) {
            case E_PPL_MOD_TYPE_VIN: {
                return "VIN";
            }
            case E_PPL_MOD_TYPE_IVPS: {
                return "IVPS";
            }
            case E_PPL_MOD_TYPE_VENC: {
                return "VENC";
            }
            case E_PPL_MOD_TYPE_SNS_MANAGER: {
                return "SNS_MGR";
            }
            case E_PPL_MOD_TYPE_DETECT: {
                return "DETECT";
            }
            case E_PPL_MOD_TYPE_COLLECT: {
                return "COLLECT";
            }
            case E_PPL_MOD_TYPE_CAPTURE: {
                return "CAPTURE";
            }
            case E_PPL_MOD_TYPE_DUMMYENC: {
                return "DUMMY_ENC";
            }
            default:
                return "Unknown";
        }
    }

    static AX_U32 AeFloat2Int(AX_F32 value, AX_U32 int_bit, AX_U32 frac_bit, AX_BOOL signed_value) {
        AX_U32 result = 0;
        if ((int_bit + frac_bit + signed_value) > 32) {
            return -1;
        }

        result = AX_ABS(value) * (AX_U64)(1 << frac_bit);

        if (signed_value) {
            if (value < 0) {
                result = -result;
            }
        }

        return result;
    }
};
