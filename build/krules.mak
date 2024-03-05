#  -----------------------------------------------------------------------------
#  Desc: TARGET
#  -----------------------------------------------------------------------------
MKFILE_PATH     := $(abspath $(lastword $(MAKEFILE_LIST)))
HOME_PATH       ?= $(abspath $(dir $(MKFILE_PATH))..)
SCRIPTS_PATH    := $(HOME_PATH)/kernel/linux/$(KERNEL_DIR)/scripts/axera
GENERATED_PATH  ?= $(KBUILD_DIR)/generated
KBUILD_OUTDIR   ?= $(HOME_PATH)/build/out/$(PROJECT)/objs/kernel/linux/$(KERNEL_DIR)
EXT_FLAG        ?= O=$(KBUILD_OUTDIR)  HOME_PATH=$(HOME_PATH)
AXVER_HEADER    := $(GENERATED_PATH)/ax_module_version.h

ccflags-y += -DBUILD_AXVERSION=\"$(SDK_VERSION)\"

EXTRA_CFLAGS += -Wno-error=date-time
EXTRA_CFLAGS += -D$(CHIP_NAME)

DEBUG_OUT_PATH := $(OSDRV_OUT_PATH)/debug_ko

define file_exists
	$(shell if [ -e $(1) ]; then echo 1; else echo 0; fi;)
endef

all: modules

.PHONY: modules install clean $(AXVER_HEADER)
.NOTPARALLEL: clean install

modules: $(KBUILD_MAKEFILE)
	@$(MAKE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS) KCFLAGS=$(KCFLAGS) -C $(KDIR) M=$(KBUILD_DIR) src=$(KSRC) $@ $(EXT_FLAG)

$(KBUILD_MAKEFILE): $(KBUILD_DIR)
	@$(TOUCH) $@

$(KBUILD_DIR): $(AXVER_HEADER)
	@$(MKDIR) -p $@

$(AXVER_HEADER):
ifeq ($(koversion),yes)
	@if [ $(call file_exists,$(AXVER_HEADER)) -eq 0 ]; then \
		echo "creating $@ ..."; \
		mkdir -p $(GENERATED_PATH); \
		bash $(SCRIPTS_PATH)/axera_module_version.sh $@ $(MODULE_NAME) $(SDK_VERSION); \
	else \
		echo "$@ exists!!!"; \
	fi
endif

install: modules
	@$(CP) $(KBUILD_DIR)/$(MODULE_NAME).ko $(KBUILD_DIR)/$(MODULE_NAME).debug
ifneq ($(DEBUG_OUT_PATH), $(wildcard $(DEBUG_OUT_PATH)))
	@$(MKDIR) $(DEBUG_OUT_PATH)
endif
	@$(CP) $(KBUILD_DIR)/$(MODULE_NAME).debug $(DEBUG_OUT_PATH)/$(MODULE_NAME).ko -rf
	@echo -e "\e[36;1m" "INSTALL  $(KBUILD_DIR)/$(MODULE_NAME).debug to $(DEBUG_OUT_PATH)/$(MODULE_NAME).ko" "\033[0m"
	$(CROSS)strip --strip-debug $(KBUILD_DIR)/$(MODULE_NAME).ko
ifneq ($(OSDRV_OUT_PATH)/ko, $(wildcard $(OSDRV_OUT_PATH)/ko))
	$(VERB) $(MKDIR) $(OSDRV_OUT_PATH)/ko
endif
	@$(CP) $(KBUILD_DIR)/$(MODULE_NAME).ko $(OSDRV_OUT_PATH)/ko/ -rf
ifeq ($(strip $(COMPRESS_KO)),TRUE)
	@cd $(KBUILD_DIR) && xz --lzma2=dict=2MiB -f $(MODULE_NAME).ko
	@$(CP) $(KBUILD_DIR)/$(MODULE_NAME).ko.xz $(OSDRV_OUT_PATH)/ko/ -rf
endif
	@echo -e "\e[36;1m" "INSTALL  $(KBUILD_DIR)/$(MODULE_NAME).ko to $(OSDRV_OUT_PATH)/ko" "\033[0m"

clean:
	@rm -rf $(clean-objs) *.o *~ .depend .*.cmd  *.mod.c .tmp_versions *.ko *.symvers modules.order
	@rm -rf $(OSDRV_OUT_PATH)/ko/$(MODULE_NAME).ko
	@rm -rf $(KBUILD_DIR)
ifeq ($(debug),yes)
	@rm -rf $(DEBUG_OUT_PATH)
endif