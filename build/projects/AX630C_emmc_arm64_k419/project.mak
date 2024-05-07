############################################################################################
CUR_DIR          := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PRJECT_DIR       := $(shell dirname $(CUR_DIR))

ARCH             := arm64
KERNEL_DIR       := linux-4.19.125
CHIP_TYPE        := AX630C
LIBC             := glibc

BUILD_DIR        := $(shell dirname $(PRJECT_DIR))
HOME_PATH        := $(shell dirname $(BUILD_DIR))
MSP_OUT_DIR      := $(ARCH)_$(LIBC)
OSDRV_OUT_DIR    := $(ARCH)_$(LIBC)_$(KERNEL_DIR)
MSP_OUT_PATH     := $(HOME_PATH)/msp/out/$(MSP_OUT_DIR)
OSDRV_OUT_PATH   := $(HOME_PATH)/kernel/osdrv/out/$(OSDRV_OUT_DIR)
ROOTFS_TARGET_PATH := $(MSP_OUT_PATH)

include $(BUILD_DIR)/cross_$(ARCH)_$(LIBC).mak
include $(PRJECT_DIR)/common.mak

# You are not advised to modify the following options
BUILD_BUSYBOX                := FALSE
SUPPPORT_GZIPD               := TRUE
AX_BOOT_OPTIMIZATION_SUPPORT := FALSE
COMPRESS_KO                  := TRUE
FLASH_TYPE                   := emmc
SUPPORT_ATF                  := TRUE
# optee=true depends on atf=true
SUPPORT_OPTEE                := TRUE
SUPPORT_KERNEL_BOOTARGS      := TRUE
ifeq ($(strip $(AX_BOOT_OPTIMIZATION_SUPPORT)),TRUE)
AX_SPL_UBOOT_KERNEL_SUPPORT  := FALSE
AX_SPL_SUPPORT_MODIFY_BOOTARGS := TRUE
else
AX_SPL_UBOOT_KERNEL_SUPPORT  := TRUE
endif
ifeq ($(strip $(SUPPORT_ATF)),FALSE)
SUPPORT_OPTEE                := FALSE
endif

############################################################################################
# Note: The above configuration is generally not modified.

# Default use rsa2048
#SIGN_USE_RSA3072            := FALSE
# Using AB partition
AX_SUPPORT_AB_PART           := TRUE
SUPPORT_DDRINIT_PART         := TRUE
AX_SYSDUMP_EMMC              := TRUE
ifeq ($(strip $(buildin_prvdrv)),yes)
KERNEL_BUILDIN_PRVDRV := TRUE
endif
ifeq ($(strip $(AX_SUPPORT_AB_PART)),TRUE)
ENABLE_SWUPDATE := TRUE
include $(PRJECT_DIR)/AX630C_emmc_arm64_k419/partition_ab.mak
else
include $(PRJECT_DIR)/AX630C_emmc_arm64_k419/partition.mak
endif
