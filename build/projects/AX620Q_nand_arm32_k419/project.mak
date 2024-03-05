CUR_DIR          := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PRJECT_DIR       := $(shell dirname $(CUR_DIR))

ARCH             := arm
KERNEL_DIR       := linux-4.19.125
CHIP_TYPE        := AX620Q
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

BUILD_BUSYBOX    := FALSE
SUPPORT_UBIFS    := TRUE
SUPPORT_CPIO     := FALSE
SUPPPORT_GZIPD   := TRUE
SUPPORT_OPTEE    := FALSE
AX_BOOT_OPTIMIZATION_SUPPORT := FALSE
COMPRESS_KO      := TRUE
SENSOR_TYPE      := os04a10
FLASH_TYPE       := nand
SUPPORT_ATF      := FALSE
SUPPORT_KERNEL_BOOTARGS  := TRUE
COPY_NFS_KO      := TRUE

ifneq ($(strip $(sensor)),)
SENSOR_TYPE      := $(sensor)
endif
SENSOR_PATH      := $(CUR_DIR)/sensors/$(SENSOR_TYPE)
ifeq ($(wildcard $(SENSOR_PATH)),)
$(error "Unsupported sensor: $(SENSOR_TYPE)")
endif

ifeq ($(strip $(AX_BOOT_OPTIMIZATION_SUPPORT)),TRUE)
AX_SPL_UBOOT_KERNEL_SUPPORT  := FALSE
AX_SPL_SUPPORT_MODIFY_BOOTARGS := TRUE
else
AX_SPL_UBOOT_KERNEL_SUPPORT  := TRUE
endif

#partition size config
SPL_PARTITION_SIZE    := 1M
DDRINIT_PARTITION_SIZE := 512K
UBOOT_PARTITION_SIZE  := 1280K
ENV_PARTITION_SIZE    := 512K
PARAM_PARTITION_SIZE  := 4M
DTB_PARTITION_SIZE    := 512K
KERNEL_PARTITION_SIZE := 8M
ROOTFS_PARTITION_SIZE := 112M
AUTO_FIT_PARTITION    := ROOTFS

SYS_DRAM_BASE                   := 0x40000000
SYS_DRAM_SIZE                   := 256 #MB

UBOOT_IMG_HEADER_BASE           := (0x5C000000)
IMG_HEADER_SIZE                 := (1024)
UBOOT_IMG_PKG_SIZE              := (0x180000) #1.5M

UBOOT_HEADER_FLASH_EXP          := $(call KM2Bytes,$(SPL_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(DDRINIT_PARTITION_SIZE))
UBOOT_HEADER_FLASH_BASE         := $(shell printf "0x%X" $$(($(UBOOT_HEADER_FLASH_EXP))))
UBOOT_DATA_FLASH_BASE           := (UBOOT_HEADER_FLASH_BASE + IMG_HEADER_SIZE)
UBOOT_HEADER_BAK_FLASH_BASE     := (UBOOT_HEADER_FLASH_BASE + UBOOT_IMG_PKG_SIZE)
UBOOT_DATA_BAK_FLASH_BASE       := (UBOOT_HEADER_BAK_FLASH_BASE + IMG_HEADER_SIZE)

ENV_IMG_PKG_SIZE                := 0x80000
ENV_DATA_FLASH_BASE_EXP         := $(call KM2Bytes,$(SPL_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(DDRINIT_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(UBOOT_PARTITION_SIZE))
ENV_DATA_FLASH_BASE             := $(shell printf "0x%X" $$(($(ENV_DATA_FLASH_BASE_EXP))))

DDRINIT_PARAM_HEADER_BASE       := 0x03200000
DDRINIT_HEADER_FLASH_EXP        := $(call KM2Bytes,$(SPL_PARTITION_SIZE))
DDRINIT_HEADER_FLASH_BASE       := $(shell printf "0x%X" $$(($(DDRINIT_HEADER_FLASH_EXP))))
DDRINIT_DATA_FLASH_BASE         := (DDRINIT_HEADER_FLASH_BASE + IMG_HEADER_SIZE)

AXERA_DTB_IMG_ADDR              := 0x42008000
DTB_IMG_HEADER_ADDR             := ($(AXERA_DTB_IMG_ADDR) - 0x400)
DTB_HEADER_FLASH_EXP            := $(call KM2Bytes,$(SPL_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(DDRINIT_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(UBOOT_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(ENV_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(PARAM_PARTITION_SIZE))
DTB_HEADER_FLASH_BASE           := $(shell printf "0x%X" $$(($(DTB_HEADER_FLASH_EXP))))
DTB_DATA_FLASH_BASE             := (DTB_HEADER_FLASH_BASE + IMG_HEADER_SIZE)

AXERA_KERNEL_IMG_ADDR           := 0x40008000
KERNEL_IMG_HEADER_ADDR          := ($(AXERA_KERNEL_IMG_ADDR) - 0x400)
KERNEL_HEADER_FLASH_EXP         := $(call KM2Bytes,$(SPL_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(DDRINIT_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(UBOOT_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(ENV_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(PARAM_PARTITION_SIZE))\
                                   +$(call KM2Bytes,$(DTB_PARTITION_SIZE))
KERNEL_HEADER_FLASH_BASE        := $(shell printf "0x%X" $$(($(KERNEL_HEADER_FLASH_EXP))))
KERNEL_DATA_FLASH_BASE          := (KERNEL_HEADER_FLASH_BASE + IMG_HEADER_SIZE)

# linux OS memory config
OS_MEM_SIZE          := 96 #MB
OS_MEM               := mem=$(strip $(OS_MEM_SIZE))M

# cmm memory config
CMM_START_ADDR       := $(call AddAddressMB, $(SYS_DRAM_BASE), $(OS_MEM_SIZE))
CMM_SIZE             := $(shell echo $$(($(SYS_DRAM_SIZE) - $(OS_MEM_SIZE))))
CMM_POOL_PARAM       := anonymous,0,$(strip $(CMM_START_ADDR)),$(CMM_SIZE)M

# uboot boot args
include $(PRJECT_DIR)/partition_tbl.mak
FLASH_PARTITIONS  := $(SPL_PART),$(DDRINIT_PART),
FLASH_PARTITIONS  += $(UBOOT_PART),$(ENV_PART),$(PARAM_PART),
FLASH_PARTITIONS  += $(DTB_PART),$(KERNEL_PART),$(ROOTFS_PART)
FLASH_PARTITIONS  := $(shell echo '$(FLASH_PARTITIONS)' | tr -d ' ')
ROOTFS_TYPE       := ubifs
ROOTFS_DEV        := /dev/mtdblock8
KERNEL_BOOTARGS   := "$(OS_MEM) console=ttyS0,115200n8 loglevel=8 earlycon=uart8250,mmio32,0x4880000 board_id=0,boot_reason=0x0,noinitrd \
root=$(ROOTFS_DEV) rw rootfstype=$(ROOTFS_TYPE) ubi.mtd=8,2048 root=ubi0:rootfs init=/linuxrc mtdparts=spi4.0:$(FLASH_PARTITIONS)"
