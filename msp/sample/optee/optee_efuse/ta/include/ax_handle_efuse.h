/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#ifndef __AX_HANDLE_EFUSE_H
#define __AX_HANDLE_EFUSE_H

/*
 * Interface to the EFUSE-TA, which is used for handling
 * device root of trust function
 */
//c7cf25d5-b62a-40bc-8841-2cefabbbf5bb
#define AX_EFUSE_UUID \
		{ 0x9b1deb4d, 0x3b7d, 0x4bad, \
		{ 0x9b, 0xdd, 0x2b, 0x0d, 0x7b, 0x3d, 0xcb, 0x6d } }

#define TA_NAME		"handle_efuse.ta"


/*
 * EFUSE supported commands
 */
#define OPTEE_EFUSE_CMD_INIT		0
#define OPTEE_EFUSE_CMD_READ		1
#define OPTEE_EFUSE_CMD_WRITE		2
#define OPTEE_EFUSE_CMD_PROTECT		3
#define OPTEE_EFUSE_CMD_DEINIT		4

#endif
