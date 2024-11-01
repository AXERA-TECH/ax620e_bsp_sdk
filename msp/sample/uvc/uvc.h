/*
 *	uvc_gadget.h  --  USB Video Class Gadget driver
 *
 *	Copyright (C) 2009-2010
 *	    Laurent Pinchart (laurent.pinchart@ideasonboard.com)
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 */

#ifndef _UVC_GADGET_H_
#define _UVC_GADGET_H_

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/usb/ch9.h>

#include <linux/usb/video.h>
#include <linux/videodev2.h>

#include <stddef.h>
#include <stdint.h>

#include "ax_isp_api.h"
#include "common_venc.h"
#include "common_cam.h"

#define UVC_EVENT_FIRST			(V4L2_EVENT_PRIVATE_START + 0)
#define UVC_EVENT_CONNECT		(V4L2_EVENT_PRIVATE_START + 0)
#define UVC_EVENT_DISCONNECT		(V4L2_EVENT_PRIVATE_START + 1)
#define UVC_EVENT_STREAMON		(V4L2_EVENT_PRIVATE_START + 2)
#define UVC_EVENT_STREAMOFF		(V4L2_EVENT_PRIVATE_START + 3)
#define UVC_EVENT_SETUP			(V4L2_EVENT_PRIVATE_START + 4)
#define UVC_EVENT_DATA			(V4L2_EVENT_PRIVATE_START + 5)
#define UVC_EVENT_LAST			(V4L2_EVENT_PRIVATE_START + 5)

struct uvc_request_data
{
	__s32 length;
	__u8 data[60];
};

struct uvc_event
{
	union {
		enum usb_device_speed speed;
		struct usb_ctrlrequest req;
		struct uvc_request_data data;
	};
};

#define UVCIOC_SEND_RESPONSE		_IOW('U', 1, struct uvc_request_data)

#define UVC_INTF_CONTROL		0
#define UVC_INTF_STREAMING		1
#define UVC_INTF_CONTROL2		2
#define UVC_INTF_STREAMING2		3
#define UVC_INTF_CONTROL3		4
#define UVC_INTF_STREAMING3		5
#define UVC_INTF_CONTROL4		6
#define UVC_INTF_STREAMING4		7

#define UVC_IMG_CACHE_COUNT     6

#define V4L2_PIX_FMT_H265     v4l2_fourcc('H', '2', '6', '5') /* H265 with start codes */

/* ------------------------------------------------------------------------
 * Structures
 */
/* IO methods supported */
enum io_method {
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
};

/* Buffer representing one video frame */
struct buffer {
    struct v4l2_buffer buf;
    void*  start;
    size_t length;
};

/* ---------------------------------------------------------------------------
 * UVC specific stuff
 */
struct uvc_frame_info {
    AX_U32 width;
    AX_U32 height;
    AX_U32 intervals[8];
    AX_U32 bitrate;  // xxx kbps
};

struct uvc_format_info {
    AX_U32 fcc;
    const struct uvc_frame_info *frames;
};

struct uvc_img_info {
    AX_U32 imgusedsize;
    AX_U8* imgdata;
    AX_S32 is_i_frame;
    AX_U64 iSerial;
    AX_U64 pts;
    AX_U64 imgphy;
};

struct uvc_img_cache {
    struct uvc_img_info imgs[UVC_IMG_CACHE_COUNT];
    AX_U32 img_max_size;
    AX_S32 has_lost;
    AX_S64 img_head;
    AX_S64 img_tail;
};

typedef struct _YUV2_CONFIG_T{
    AX_U32 u32Width;
    AX_U32 u32Height;
    AX_BOOL bExit;
}YUV2_CONFIG_T;

typedef struct _stStreamInfo{
    AX_U64 u64ResoIndex;
    AX_U64 u64FmtIndex;
    AX_U32 u32FrameRate;
}StreamInfo, *pStreamInfo;

typedef struct axMOD_INFO_S {
    AX_MOD_ID_E enModId;
    AX_S32 s32GrpId;
    AX_S32 s32ChnId;
} AX_MOD_INFO_S;

typedef struct VENC_GETSTREAM_PARA
{
    AX_S32 s32VencChn;
    AX_BOOL bThreadStart;
    AX_BOOL bChnCreated;
    AX_MOD_INFO_T ivpsMod;
    AX_MOD_INFO_T vencMod;
    AX_PAYLOAD_TYPE_E enPayloadType;
} VENC_GETSTREAM_PARA_T;

/* Represents a UVC based video output device */
typedef struct _UVC_DEVICE_T {
    /* uvc device specific */
    AX_S32 uvc_fd;
    AX_S32 dev_id;
    AX_S32 pipe;
    SAMPLE_SNS_TYPE_E sns_type;
    AX_S32 encoder_chn;
    AX_S32 is_streaming;
    AX_S32 run_standalone;
    char *uvc_devname;
    AX_U8 is_link;
    AX_U8 ivps_chn;

    pthread_t dispatch_frame_pid;
    pthread_t get_stream_pid;
    pthread_mutex_t img_mutex;
    StreamInfo stream_info;
    YUV2_CONFIG_T stYUV2Cfg;
    VENC_GETSTREAM_PARA_T venc_param;

    /* uvc control request specific */
    struct uvc_streaming_control probe;
    struct uvc_streaming_control commit;
    AX_S32 control;
    struct uvc_request_data request_error_code;
    AX_U32 brightness_val;

    /* uvc buffer specific */
    enum io_method io;
    struct buffer *mem;
    struct buffer *dummy_buf;
    AX_U32 nbufs;
    AX_U32 fcc;
    AX_U32 last_fcc;
    AX_U32 width;
    AX_U32 height;

    AX_U32 bulk;
    uint8_t color;

    /* USB speed specific */
    AX_S32 mult;
    AX_S32 burst;
    AX_S32 maxpkt;
    enum usb_device_speed speed;

    /* uvc specific flags */
    AX_S32 first_buffer_queued;
    AX_S32 uvc_shutdown_requested;

    /* uvc buffer queue and dequeue counters */
    AX_U64 qbuf_count;
    AX_U64 dqbuf_count;

    /* image cache */
    struct uvc_img_cache img_cache;

    AX_U8* imgdata;
    AX_S32 imgsize;
} UVC_DEVICE_T;

AX_S32 uvc_img_cache_init(UVC_DEVICE_T *dev, AX_U32 img_max_size);
AX_S32 uvc_img_cache_deinit(UVC_DEVICE_T *dev);
AX_S32 uvc_img_cache_clear(UVC_DEVICE_T *dev);
AX_S32 uvc_img_cache_put(UVC_DEVICE_T *dev, AX_U8 * pBuf, AX_U32 nSize, AX_U64 iSerial, AX_U64 pts, AX_BOOL bIFrame);
struct uvc_img_info * uvc_img_cache_pop(UVC_DEVICE_T *dev);

#endif /* _UVC_GADGET_H_ */

