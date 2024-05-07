include color.mk
include config.mak
############################################################################
#	prepare param
############################################################################
COMPILE_TIME		:= $(shell date +"%Y%m%d%H%M")

# Base dir
HOME_PATH		:= $(abspath $(shell pwd)/..)
BL1_PATH		:= $(HOME_PATH)/boot/bl1
UBOOT_PATH		:= $(HOME_PATH)/boot/uboot
ATF_PATH		:= $(HOME_PATH)/boot/atf
KERNEL_PATH		:= $(HOME_PATH)/kernel/linux
SAMPLE_PATH		:= $(HOME_PATH)/msp/sample
ifeq ($(AX_BOOT_OPTIMIZATION_SUPPORT),TRUE)
RISCV_PATH		:= $(HOME_PATH)/riscv
endif

OSDRV_PATH		:= $(HOME_PATH)/kernel/osdrv
ROOTFS_PATH		:= $(HOME_PATH)/rootfs
APP_PATH		:= $(HOME_PATH)/app
BUILD_PATH		:= $(HOME_PATH)/build
TOOLS_PATH		:= $(HOME_PATH)/tools
THIRD_PARTY_PATH	:= $(HOME_PATH)/third-party
MSP_PATH                := $(HOME_PATH)/msp

PROJECT_PATH		:= $(BUILD_PATH)/projects/$(PROJECT)

ifeq ($(strip $(SUPPORT_OPTEE)),TRUE)
OPTEE_PATH		:= $(HOME_PATH)/boot/optee
SUBDIRS			:= $(OPTEE_PATH)
endif

ifeq ($(strip $(SUPPORT_ATF)),TRUE)
SUBDIRS			+= $(ATF_PATH)
endif

SUBDIRS			+= $(BL1_PATH) \
			$(UBOOT_PATH)  \
			$(ROOTFS_PATH) \
			$(KERNEL_PATH) \
			$(OSDRV_PATH)/third_drv \
			$(THIRD_PARTY_PATH) \
			$(MSP_PATH) \
			$(APP_PATH)

ifeq ($(AX_BOOT_OPTIMIZATION_SUPPORT),TRUE)
SUBDIRS			+=$(RISCV_PATH)
endif

SUBDIRS			+= $(SAMPLE_PATH)

# for axera module version
MODVER_SUBDIRS		:= $(MSP_PATH)

############################################################################
#	build
############################################################################
SUBDIRS_ALL     = $(addsuffix .all, $(SUBDIRS))
SUBDIRS_CLEAN   = $(addsuffix .clean, $(SUBDIRS))
SUBDIRS_INSTALL = $(addsuffix .install, $(SUBDIRS))
SUBDIRS_SCAN    = $(addsuffix .scan, $(filter-out $(UT_PATH),$(SUBDIRS)))
SUBDIRS_MODVER  = $(addsuffix .modversion, $(MODVER_SUBDIRS))

.PHONY: $(SUBDIRS) $(SUBDIRS_ALL) $(SUBDIRS_INSTALL) $(SUBDIRS_CLEAN) sdk $(SUBDIRS_MODVER)
.NOTPARALLEL: clean install $(SUBDIRS_MODVER)

default: $(SUBDIRS)

all: $(SUBDIRS_ALL)
	@echo -e $(GREEN)"\nBuild All Modules success!!\n"  $(DONE)

install: $(SUBDIRS_INSTALL)
	@echo -e $(CYAN)"\nInstall MSP out to rootfs!!\n"  $(DONE)

	@$(MAKE) -C $(ROOTFS_PATH) image
ifeq ($(SUPPORT_CPIO),TRUE)
	@$(MAKE) -C $(KERNEL_PATH) all install
endif
ifeq ($(AX_BOOT_OPTIMIZATION_SUPPORT),TRUE)
	@$(MAKE) -C $(RISCV_PATH) all install
endif
	@echo -e $(GREEN)"\nInstall success!!\n"  $(DONE)

clean:	$(SUBDIRS_CLEAN)
	@rm -rf $(BUILD_PATH)/out/$(PROJECT)
	@echo -e $(GREEN)"\nClean success!!\n"  $(DONE)

axp: image
	@bash axp_make.sh -p "$(PROJECT)" -v "$(SDK_VERSION)" -o "$(SUPPORT_OPTEE)" -z "$(SUPPPORT_GZIPD)" -s "$(SENSOR_TYPE)" -d "$(DETECT_TYPE)" -a "$(AX_SUPPORT_AB_PART)" -l "$(LIBC)" -f "$(FLASH_PARTITIONS)"
	@echo -e $(GREEN)"\nMake AXP success!!\n"  $(DONE)

image:
	@$(MAKE) -C $(PROJECT_PATH) image

$(SUBDIRS):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $@ ..." $(DONE)
	@$(MAKE) -C $(basename $@ )

$(SUBDIRS_ALL):
	@$(ECHO) -e $(CYAN)"Making $(notdir $@)" $(DONE)
	@$(ECHO) -e $(CYAN)"In subdir $(basename $(notdir $@) )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) all

$(SUBDIRS_INSTALL):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $(basename $(notdir $@) )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) install

$(SUBDIRS_CLEAN):
	@$(ECHO) -e $(CYAN)"In subdir $(basename $(notdir $@) )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) clean
$(SUBDIRS_MODVER):
	@$(ECHO) -e $(CYAN)"In subdir $(basename $(notdir $@) )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) modversion
