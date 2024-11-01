################################################################################
#	prepare param
################################################################################
LOCAL_PATH         := $(shell pwd)
HOME_PATH          := $(abspath $(LOCAL_PATH)/../../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

ifeq ($(strip $(SUPPORT_OPTEE)),TRUE)
SUBDIRS := optee_hello_world  optee_sec_storage optee_aes optee_acipher optee_efuse
SUBDIRS += optee_efuse_hash
endif

PRJ_OUT_HOME       := $(HOME_PATH)/build/out/$(PROJECT)
OBJ_OUT_PATH       := $(PRJ_OUT_HOME)/objs
INSTALL_DIR        := $(MSP_OUT_PATH)/bin/OPTEE
TA_TARGET_PATH     := $(MSP_OUT_PATH)/ta

################################################################################
#	set task
################################################################################
SUBDIRS_CLEAN   = $(addsuffix .clean, $(SUBDIRS))
SUBDIRS_INSTALL = $(addsuffix .install, $(SUBDIRS))

.PHONY: $(SUBDIRS) $(SUBDIRS_INSTALL) $(SUBDIRS_CLEAN)

all: $(SUBDIRS)
	@$(ECHO) -e $(GREEN)"\nBuild All sample Modules success!!\n"  $(DONE)

install: $(SUBDIRS_INSTALL)
	@$(ECHO) -e $(GREEN)"\nInstall sample success!!\n"  $(DONE)

clean:	$(SUBDIRS_CLEAN)
	@$(ECHO) -e $(GREEN)"\nClean sample success!!\n"  $(DONE)
	@$(RM) -rf $(INSTALL_DIR)
	@$(RM) -rf $(TA_TARGET_PATH)

$(SUBDIRS):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $@ ..." $(DONE)
	@$(MAKE) -C $(basename $@ )

$(SUBDIRS_INSTALL):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) install

$(SUBDIRS_CLEAN):
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) clean


# Export val
export INSTALL_DIR
export TA_TARGET_PATH
