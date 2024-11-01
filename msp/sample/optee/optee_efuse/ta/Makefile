CUR_PATH		:= $(shell pwd)
HOME_PATH		:= $(abspath $(CUR_PATH)/../../../../..)
SRC_PATH		:= $(CUR_PATH)

include $(HOME_PATH)/build/config.mak

PRJ_OUT_HOME		:= $(HOME_PATH)/build/out/$(PROJECT)
OBJ_OUT_PATH		:= $(PRJ_OUT_HOME)/objs
OUT_PATH		    := $(MSP_OUT_PATH)
SRC_RELATIVE_PATH	:= $(subst $(HOME_PATH)/,,$(SRC_PATH))
TARGET_OUT_PATH		:= $(OBJ_OUT_PATH)/$(SRC_RELATIVE_PATH)
TA_TARGET_PATH 		?= $(MSP_OUT_PATH)/ta

CROSS_COMPILE := $(CROSS)
TA_PLATFORM			:= axera-ax650
TA_DEV_KIT_DIR		:= $(OBJ_OUT_PATH)/boot/optee/optee_os-3.21.0/export-ta_arm64
O                   := $(TARGET_OUT_PATH)

CFG_TEE_TA_LOG_LEVEL = 4
#CPPFLAGS += -DTRACE_LEVEL=$(CFG_TEE_TA_LOG_LEVEL)

#CFG_TA_OPTEE_CORE_API_COMPAT_1_1=y

# The UUID for the Trusted Application
BINARY=9b1deb4d-3b7d-4bad-9bdd-2b0d7b3dcb6d

-include $(TA_DEV_KIT_DIR)/mk/ta_dev_kit.mk

install:
	@$(MKDIR) -p $(TA_TARGET_PATH)
	@$(CP) $(TARGET_OUT_PATH)/$(BINARY).ta $(TA_TARGET_PATH)

ifeq ($(wildcard $(TA_DEV_KIT_DIR)/mk/ta_dev_kit.mk), )
clean:
	@echo 'Note: $$(TA_DEV_KIT_DIR)/mk/ta_dev_kit.mk not found, cannot clean TA'
	@echo 'Note: TA_DEV_KIT_DIR=$(TA_DEV_KIT_DIR)'
endif
