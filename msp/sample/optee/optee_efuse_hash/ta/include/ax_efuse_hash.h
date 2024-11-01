#ifndef __AX_EFUSE_HASH_H
#define __AX_EFUSE_HASH_H

/*
 * Interface to the EFUSE_HASH-TA, which is used for handling
 * device root of trust function
 */
//6127a75d-0aed-4b35-bd8b-82e68d3b766c
#define AX_EFUSE_HASH_UUID \
		{ 0x6127a75d, 0x0aed, 0x4b35, \
		{ 0xbd, 0x8b, 0x82, 0xe6, 0x8d, 0x3b, 0x76, 0x6c } }

/*
 * EFUSE supported commands
 */
#define OPTEE_EFUSE_CMD_INIT		0
#define OPTEE_EFUSE_CMD_READ		1
#define OPTEE_EFUSE_CMD_WRITE		2
#define OPTEE_EFUSE_CMD_PROTECT		3
#define OPTEE_EFUSE_CMD_DEINIT		4

#endif
