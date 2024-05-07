HOME_PATH    := $(abspath $(shell pwd)/../../../)
BUILD_PATH   := $(HOME_PATH)/build
BUSYBOX_PATH := $(shell pwd)/busybox

include $(BUILD_PATH)/color.mk
include $(BUILD_PATH)/config.mak

OUT_DIR           := $(BUILD_PATH)/out/$(PROJECT)/objs
IMAGE_OUTDIR      := $(BUILD_PATH)/out/$(PROJECT)/images
TOOLS_PATH        := $(HOME_PATH)/tools
MAKE_EXT4FS       := $(TOOLS_PATH)/mkext4fs/make_ext4fs
MKFS_JFFS2        := $(TOOLS_PATH)/mkjffs2fs/mkfs.jffs2
MKFS_UBIFS        := $(TOOLS_PATH)/mkubifs/mkfs.ubifs
MK_UBINIZE        := $(TOOLS_PATH)/mkubifs/ubinize
COPY_FILE         := $(BUILD_PATH)/tools/copy_files.py
MAKE_SQUASHFS     := $(TOOLS_PATH)/mksquashfs/mksquashfs
PROJECT_MAK       := $(BUILD_PATH)/projects/$(PROJECT)/project.mak

#rootfs
SRC_ROOTFS_DIR    := $(HOME_PATH)
DST_ROOTFS_DIR    := $(OUT_DIR)/rootfs
ROOTFS_IMG        := $(IMAGE_OUTDIR)/rootfs_soc_opt.ubi
ROOTFS_UBI_IMG    := rootfs.ubifs
SOC_UBI_IMG       := soc.ubifs
OPT_UBI_IMG       := opt.ubifs
rootfs_img_size   := $(call KM2Bytes,$(ROOTFS_PARTITION_SIZE))
MODIFY_FSTAB_FILE := $(BUILD_PATH)/tools/modify_fstab.sh
OUT_FSTAB_FILE    := $(DST_ROOTFS_DIR)/etc/fstab

#soc
SRC_SOC_DIR       := $(HOME_PATH)
SCRIPTS_DIR       := $(SRC_ROOTFS_DIR)/rootfs/opt/scripts
DST_SOC_DIR       := $(DST_ROOTFS_DIR)/soc

#opt
SRC_OPT_DIR       := $(HOME_PATH)
DST_OPT_DIR       := $(OUT_DIR)/opt

#param
DST_PARAM_DIR     := $(OUT_DIR)/param
PARAM_IMG         := $(IMAGE_OUTDIR)/param.ubi
PARAM_UBI_IMG     := param.ubifs
param_img_size    := $(call KM2Bytes,$(PARAM_PARTITION_SIZE))

#optee
LIB_OPTEE_PATH    := $(DST_ROOTFS_DIR)/lib/optee_armtz

ifeq ($(debug), yes)
COPY_DEBUG        := $(BUILD_PATH)/tools/copy_debug.py
DEBUG_SO_PATH     := $(MSP_OUT_PATH)/lib
DEBUG_SO_TYPE     := .debug
DST_SO_PATH       := $(MSP_OUT_PATH)/lib
DST_SO_TYPE       := .so
DEBUG_KO_PATH     := $(OSDRV_OUT_PATH)/debug_ko
DEBUG_KO_TYPE     := .ko
DST_KO_PATH       := $(OSDRV_OUT_PATH)/ko
DST_KO_TYPE       := .ko
endif

FSTAB_FILE        := rootfs/etc/fstab

.PHONY: prepare all install rootfs image rootfs_image check

default: all
all: prepare rootfs
	@$(ECHO) -e $(GREEN)"\nBuild Rootfs success!!\n" $(DONE)

prepare:
	@$(ECHO) -e $(GREEN) "Making $@..." $(DONE)
	@$(MKDIR) -p $(OUT_DIR)

rootfs:
	@$(ECHO) -e $(GREEN) "Making $@..." $(DONE)
	@$(MKDIR) -p $(DST_ROOTFS_DIR)
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/proc
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/sys
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/mnt/tfcard
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/tmp
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/run
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/root
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/media
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/param
	@$(MKDIR) -p $(DST_ROOTFS_DIR)/opt
	@$(MKDIR) $(DST_ROOTFS_DIR)/var/www
	@$(MKDIR) $(IMAGE_OUTDIR)
	@python3 $(COPY_FILE) $(PROJECT) $(PROJECT_MAK) $(SRC_ROOTFS_DIR) rootfs.filelist $(DST_ROOTFS_DIR)
	@cp -rf $(FSTAB_FILE) $(DST_ROOTFS_DIR)/etc/fstab
	@cp -rf rootfs/etc/fw_env.config $(DST_ROOTFS_DIR)/etc/
	@cp -rf rootfs/etc/init.d/rcS $(DST_ROOTFS_DIR)/etc/init.d/
	@sed -i '/\/proc\/sys\/kernel\/core_pattern/d' $(DST_ROOTFS_DIR)/etc/profile
ifneq ($(findstring yes, $(debugkconfig) $(debug)),)
	echo "/soc/scripts/kmemleak_scan.sh &" >> $(DST_ROOTFS_DIR)/etc/init.d/rcS
endif
	@chmod 755 $(MODIFY_FSTAB_FILE)
	@bash $(MODIFY_FSTAB_FILE) $(OUT_FSTAB_FILE) "$(FLASH_PARTITIONS)"

install:
	@$(ECHO) -e $(GREEN) "rootfs $@..." $(DONE)
#optee
ifeq ($(strip $(SUPPORT_OPTEE)),TRUE)
	@$(MKDIR) -p $(LIB_OPTEE_PATH)
	@cp -rf $(MSP_OUT_PATH)/ta/* $(LIB_OPTEE_PATH)
endif

image: rootfs_image param_image
	@$(ECHO) -e $(GREEN) "make $@..." $(DONE)

rootfs_image:
	@$(ECHO) -e $(GREEN) "making $@ ..." $(DONE)
#soc
	@python3 $(COPY_FILE) $(PROJECT) $(PROJECT_MAK) $(SRC_SOC_DIR) soc.filelist $(DST_SOC_DIR)
	@chmod 755 $(DST_SOC_DIR)/scripts/*.sh
ifneq ($(strip $(CMM_POOL_PARAM)),)
	@sed -i "s/cmmpool*=.*/cmmpool=$(CMM_POOL_PARAM)/g" $(DST_SOC_DIR)/scripts/auto_load_all_drv.sh
endif
ifeq ($(debug), yes)
	@python3 $(COPY_DEBUG) $(DEBUG_SO_PATH) $(DEBUG_SO_TYPE) $(DST_SO_PATH) $(DST_SO_TYPE)
	@python3 $(COPY_DEBUG) $(DEBUG_KO_PATH) $(DEBUG_KO_TYPE) $(DST_KO_PATH) $(DST_KO_TYPE)
endif
ifeq ($(SUPPORT_CPIO),TRUE)
	@cd $(DST_ROOTFS_DIR) && find . | cpio -o -H newc > $(IMAGE_OUTDIR)/rootfs.cpio
endif
#opt
	@$(ECHO) -e $(GREEN) "making $@ ..." $(DONE)
ifeq ($(asan), yes)
	@mkdir -p $(DST_OPT_DIR)/lib
	@cp -rf $(CROSS_LIB_PATH)/libasan*.so* $(DST_OPT_DIR)/lib
endif
	@mkdir -p $(DST_OPT_DIR)/etc/models/aiisp
	@python3 $(COPY_FILE) $(PROJECT) $(PROJECT_MAK) $(SRC_OPT_DIR) opt.filelist $(DST_OPT_DIR)
	@for element in $(SENSOR_TYPE); do \
		if [ ! -d $(CUR_DIR)/sensors/$$element ]; then \
			echo "Error: Unsupported sensor: $$element"; \
			exit 1; \
		fi; \
		python3 $(COPY_FILE) $(PROJECT) $(PROJECT_MAK) $(SRC_OPT_DIR) $(CUR_DIR)/sensors/$$element/so.filelist $(DST_OPT_DIR); \
		python3 $(COPY_FILE) $(PROJECT) $(PROJECT_MAK) $(SRC_OPT_DIR) $(CUR_DIR)/sensors/$$element/model.filelist $(DST_OPT_DIR); \
	done
	@mkdir -p $(DST_OPT_DIR)/data
	@mkdir -p $(DST_OPT_DIR)/usr/bin
ifeq ($(SUPPORT_VALGRIND), yes)
	@cp -rf $(VALGRIND_PATH)/bin/* $(DST_OPT_DIR)/bin
	@cp -rf $(VALGRIND_PATH)/libexec $(DST_OPT_DIR)/
endif
#image
	@$(MKFS_UBIFS) -F -q -r $(DST_ROOTFS_DIR) -m 2048 -e 126976 -c 2047 -o $(ROOTFS_UBI_IMG)
	@$(MKFS_UBIFS) -F -q -r $(DST_SOC_DIR) -m 2048 -e 126976 -c 2047 -o $(SOC_UBI_IMG)
	@$(MKFS_UBIFS) -F -q -r $(DST_OPT_DIR) -m 2048 -e 126976 -c 2047 -o $(OPT_UBI_IMG)
	@$(MK_UBINIZE) -o $(ROOTFS_IMG) -m 2048 -p 128KiB ubi/ubinize_1Gb.cfg
	@imgsize=$$(stat -c %s $(ROOTFS_IMG));\
	if [ $$imgsize -gt $(rootfs_img_size) ]; then \
		echo "Error: $(ROOTFS_IMG) file size($$imgsize bytes) exceeds $(strip $(rootfs_img_size)) bytes"; \
		exit 1; \
	fi
	@cp -rf $(ROOTFS_UBI_IMG) $(IMAGE_OUTDIR)
	@cp -rf $(SOC_UBI_IMG) $(IMAGE_OUTDIR)
	@cp -rf $(OPT_UBI_IMG) $(IMAGE_OUTDIR)

param_image:
	@$(ECHO) -e $(GREEN) "making $@ ..." $(DONE)
	@$(MKDIR) -p $(DST_PARAM_DIR)
# copy avs cali data
	@$(MKDIR) $(DST_PARAM_DIR)/avs

	@$(MKFS_UBIFS) -F -q -r $(DST_PARAM_DIR) -m 2048 -e 126976 -c 2047 -j 1048576 -o $(PARAM_UBI_IMG)
	@rm -rf $(DST_PARAM_DIR)
	@$(MK_UBINIZE) -o $(PARAM_IMG) -m 2048 -p 128KiB ubi/ubinize_param.cfg
	@imgsize=$$(stat -c %s $(PARAM_IMG));\
	if [ $$imgsize -gt $(param_img_size) ]; then \
		echo "Error: $(PARAM_IMG) file size($$imgsize bytes) exceeds $(strip $(param_img_size)) bytes"; \
		exit 1; \
	fi
	@cp -rf $(PARAM_UBI_IMG) $(IMAGE_OUTDIR)

clean:
	@$(ECHO) -e $(GREEN) "rootfs $@..." $(DONE)
	@rm -rf $(DST_SOC_DIR)
	@rm -rf $(DST_OPT_DIR)
	@rm -rf $(DST_PARAM_DIR)
	@rm -rf $(DST_ROOTFS_DIR)
	@rm -rf $(ROOTFS_UBI_IMG) $(SOC_UBI_IMG) $(OPT_UBI_IMG) $(PARAM_UBI_IMG)
