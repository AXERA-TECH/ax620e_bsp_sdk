/**************************************************************************************************
 *
 * Copyright (c) 2019-2024 Axera Semiconductor Co., Ltd. All Rights Reserved.
 *
 * This source file is the property of Axera Semiconductor Co., Ltd. and
 * may not be copied or distributed in any isomorphic form without the prior
 * written consent of Axera Semiconductor Co., Ltd.
 *
 **************************************************************************************************/

#include <err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

/* For the UUID (found in the TA's h-file(s)) */
#include <ax_handle_efuse.h>

int main(int argc, char *argv[])
{
	TEEC_Result res;
	TEEC_Context ctx;
	TEEC_Session sess;
	TEEC_Operation op;
	TEEC_UUID uuid = AX_EFUSE_UUID;
	uint32_t err_origin;
	unsigned int write_val;
	char *hex;
	int read_or_write = atoi(argv[1]);
	unsigned int blk = atoi(argv[2]);

	/* Initialize a context connecting us to the TEE */
	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);

	res = TEEC_OpenSession(&ctx, &sess, &uuid,
			       TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS)
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x",
			res, err_origin);


	/* Clear the TEEC_Operation struct */
	memset(&op, 0, sizeof(op));

	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */
	op.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_VALUE_OUTPUT,TEEC_VALUE_INPUT, TEEC_NONE);

	op.params[0].value.a = blk;  // read/write blk

	if (argc > 4)
	{
		printf("efuse failed\n");
		TEEC_CloseSession(&sess);
		TEEC_FinalizeContext(&ctx);
		return -1;
	}
	if (read_or_write == 0) {
		if (argc != 3)
		{
			printf("efuse read failed\n");
			TEEC_CloseSession(&sess);
			TEEC_FinalizeContext(&ctx);
			return -1;
		}
		/*
		 * OPTEE_EFUSE_CMD_READ is the actual function in the TA to be
		 * called.
		 */
		res = TEEC_InvokeCommand(&sess, OPTEE_EFUSE_CMD_READ, &op, &err_origin);
		if (res != TEEC_SUCCESS)
			errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
				res, err_origin);
		printf("TA efuse read value to 0x%08x\n", op.params[1].value.a);
	}
	if (read_or_write == 1) {
		if (argc != 4)
		{
			printf("efuse write failed\n");
			TEEC_CloseSession(&sess);
			TEEC_FinalizeContext(&ctx);
			return -1;
		}
		hex = argv[3];
		write_val = strtol(hex, NULL, 16);
		printf("write_val:0x%08x\n", write_val);

		op.params[2].value.a = write_val; // write  value
		/*
		 * OPTEE_EFUSE_CMD_WRITE is the actual function in the TA to be
		 * called.
		 */
		res = TEEC_InvokeCommand(&sess, OPTEE_EFUSE_CMD_WRITE, &op, &err_origin);
		if (res != TEEC_SUCCESS)
			errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x",
				res, err_origin);
	}
	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);


	return 0;
}
