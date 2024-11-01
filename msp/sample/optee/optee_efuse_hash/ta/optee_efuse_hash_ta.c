/*
 * Copyright (c) 2023, Axera Limited
 * All rights reserved.
 */

#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>
#include <ax_efuse_hash.h>

/*
 * Called when the instance of the TA is created. This is the first call in
 * the TA.
 */
TEE_Result TA_CreateEntryPoint(void)
{
	DMSG("has been called");

	return TEE_SUCCESS;
}

/*
 * Called when the instance of the TA is destroyed if the TA has not
 * crashed or panicked. This is the last call in the TA.
 */
void TA_DestroyEntryPoint(void)
{
	DMSG("has been called");
}

/*
 * Called when a new session is opened to the TA. *sess_ctx can be updated
 * with a value to be able to identify this session in subsequent calls to the
 * TA. In this function you will normally do the global initialization for the
 * TA.
 */
TEE_Result TA_OpenSessionEntryPoint(uint32_t param_types,
		TEE_Param __maybe_unused params[4],
		void __maybe_unused **sess_ctx)
{
	/* nothing to do */
	(void)param_types;
	return TEE_SUCCESS;
}

/*
 * Called when a session is closed, sess_ctx hold the value that was
 * assigned by TA_OpenSessionEntryPoint().
 */
void TA_CloseSessionEntryPoint(void __maybe_unused *sess_ctx)
{
	(void)&sess_ctx; /* Unused parameter */
	IMSG("Goodbye!\n");
}

/*
 * Called when a TA is invoked. sess_ctx hold that value that was
 * assigned by TA_OpenSessionEntryPoint(). The rest of the paramters
 * comes from normal world.
 */
TEE_Result TA_InvokeCommandEntryPoint(void __maybe_unused *sess_ctx,
			uint32_t cmd_id,
			uint32_t param_types, TEE_Param params[4])
{
	(void)&sess_ctx; /* Unused parameter */
	(void)param_types;

	switch (cmd_id) {
	case OPTEE_EFUSE_CMD_READ:
			Tee_Efuse_Init();
			Tee_Efuse_Read(params[0].value.a, &(params[1].value.a));
			return Tee_Efuse_Deinit();
	case OPTEE_EFUSE_CMD_WRITE:
			Tee_Efuse_Init();
			Tee_Efuse_Write(params[0].value.a, params[2].value.a);
			return Tee_Efuse_Deinit();
	case OPTEE_EFUSE_CMD_PROTECT:
		return Tee_Efuse_Blk_Protect(params[0].value.a);
	default:
		return TEE_ERROR_BAD_PARAMETERS;
	}
}
