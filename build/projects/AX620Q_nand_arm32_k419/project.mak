############################################################################################
CUR_DIR          := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
PRJECT_DIR       := $(shell dirname $(CUR_DIR))

ARCH             := arm
KERNEL_DIR       := linux-4.19.125
CHIP_TYPE        := AX620Q
LIBC             := uclibc

# The libc type can be modified by compiling parameters
ifneq ($(strip $(libc)),)
LIBC             := $(libc)
endif
ifneq ($(strip $(LIBC)),glibc)
ifneq ($(strip $(LIBC)),uclibc)
$(error "only support glibc & uclibc")
endif
endif

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
BUILD_BUSYBOX                  := FALSE
SUPPORT_UBIFS                  := TRUE
SUPPORT_CPIO                   := FALSE
SUPPPORT_GZIPD                 := TRUE
AX_BOOT_OPTIMIZATION_SUPPORT   := FALSE
FLASH_TYPE                     := nand
SUPPORT_ATF                    := FALSE
# optee=true depends on atf=true
SUPPORT_OPTEE                  := FALSE
SUPPORT_KERNEL_BOOTARGS        := TRUE
SUPPORT_DDRINIT_PART           := TRUE
ifeq ($(strip $(AX_BOOT_OPTIMIZATION_SUPPORT)),TRUE)
AX_SPL_UBOOT_KERNEL_SUPPORT    := FALSE
AX_SPL_SUPPORT_MODIFY_BOOTARGS := TRUE
else
AX_SPL_UBOOT_KERNEL_SUPPORT    := TRUE
endif
COMPRESS_KO                    := TRUE
COPY_NFS_KO                    := TRUE
ifeq ($(strip $(SUPPORT_ATF)),FALSE)
SUPPORT_OPTEE                  := FALSE
endif

# The address of the text segment in the startup phase, do not recommend modification.
IMG_HEADER_SIZE                 := (1024)
ATF_IMG_HEADER_BASE             := (0x4003FC00)
UBOOT_IMG_HEADER_BASE           := (0x5C000000)
DDRINIT_PARAM_HEADER_BASE       := (0x03200000)
AXERA_DTB_IMG_ADDR              := 0x42008000
DTB_IMG_HEADER_ADDR             := ($(AXERA_DTB_IMG_ADDR) - $(IMG_HEADER_SIZE))
AXERA_KERNEL_IMG_ADDR           := 0x40008000
KERNEL_IMG_HEADER_ADDR          := ($(AXERA_KERNEL_IMG_ADDR) - $(IMG_HEADER_SIZE))
############################################################################################
# Note: The above configuration is generally not modified.

# The sensor type can be modified by compiling parameters
SENSOR_TYPE                  := os04a10
ifneq ($(strip $(sensor)),)
SENSOR_TYPE                  := $(sensor)
endif
SENSOR_PATH                  := $(CUR_DIR)/sensors/$(SENSOR_TYPE)
ifeq ($(wildcard $(SENSOR_PATH)),)
$(error "Unsupported sensor: $(SENSOR_TYPE)")
endif



#partition size config
SPL_PARTITION_SIZE             := 1M
DDRINIT_PARTITION_SIZE         := 512K
UBOOT_PARTITION_SIZE           := 1M
ENV_PARTITION_SIZE             := 512K
PARAM_PARTITION_SIZE           := 4M
DTB_PARTITION_SIZE             := 512K
KERNEL_PARTITION_SIZE          := 4M
ROOTFS_PARTITION_SIZE          := 112M
AUTO_FIT_PARTITION             := ROOTFS

# env part size, size is equal to ENV_PARTITION_SIZE
ENV_IMG_PKG_SIZE               := 0x80000

# Dram base address and size
SYS_DRAM_BASE           := 0x40000000
SYS_DRAM_SIZE           := 256 #MB

# linux OS memory config
OS_MEM_SIZE          := 96 #MB
OS_MEM               := mem=$(strip $(OS_MEM_SIZE))M

# cmm memory config
CMM_START_ADDR       := $(call AddAddressMB, $(SYS_DRAM_BASE), $(OS_MEM_SIZE))
CMM_SIZE             := $(shell echo $$(($(SYS_DRAM_SIZE) - $(OS_MEM_SIZE))))
CMM_POOL_PARAM       := anonymous,0,$(strip $(CMM_START_ADDR)),$(CMM_SIZE)M

# uboot boot args
include $(PRJECT_DIR)/partition_tbl.mak
FLASH_PARTITIONS  := $(SPL_PART),
ifeq ($(strip $(SUPPORT_DDRINIT_PART)),TRUE)
FLASH_PARTITIONS  += $(DDRINIT_PART),
endif
FLASH_PARTITIONS  += $(UBOOT_PART),$(ENV_PART),$(PARAM_PART),
FLASH_PARTITIONS  += $(DTB_PART),$(KERNEL_PART),$(ROOTFS_PART)
FLASH_PARTITIONS  := $(shell echo '$(FLASH_PARTITIONS)' | tr -d ' ')
ROOTFS_TYPE       := ubifs
ROOTFS_POSITION   := $(shell echo "$(FLASH_PARTITIONS)" | tr ',' '\n' | grep -n 'rootfs' | cut -d ':' -f 1)
ROOTFS_DEV        := /dev/mtdblock$(strip $(ROOTFS_POSITION))
KERNEL_BOOTARGS   := "$(OS_MEM) console=ttyS0,115200n8 loglevel=8 earlycon=uart8250,mmio32,0x4880000 board_id=0,boot_reason=0x0,noinitrd \
root=$(ROOTFS_DEV) rw rootfstype=$(ROOTFS_TYPE) ubi.mtd=8,2048 root=ubi0:rootfs init=/linuxrc mtdparts=spi4.0:$(FLASH_PARTITIONS)"

# Calculates the position of each partition in flash
DDRINIT_HEADER_FLASH_BASE     := $(call calculate_flash_base,$(FLASH_PARTITIONS),ddrinit)
ATF_A_HEADER_FLASH_BASE       := $(call calculate_flash_base,$(FLASH_PARTITIONS),atf)
ATF_B_HEADER_FLASH_BASE       := $(call calculate_flash_base,$(FLASH_PARTITIONS),atf_b)
UBOOT_A_HEADER_FLASH_BASE     := $(call calculate_flash_base,$(FLASH_PARTITIONS),uboot)
UBOOT_B_HEADER_FLASH_BASE     := $(call calculate_flash_base,$(FLASH_PARTITIONS),uboot_b)
ENV_DATA_FLASH_BASE           := $(call calculate_flash_base,$(FLASH_PARTITIONS),env)
ifeq ($(strip $(SUPPORT_OPTEE)),TRUE)
OPTEE_A_HEADER_FLASH_BASE     := $(call calculate_flash_base,$(FLASH_PARTITIONS),optee)
OPTEE_B_HEADER_FLASH_BASE     := $(call calculate_flash_base,$(FLASH_PARTITIONS),optee_b)
endif
DTB_A_HEADER_FLASH_BASE       := $(call calculate_flash_base,$(FLASH_PARTITIONS),dtb)
DTB_B_HEADER_FLASH_BASE       := $(call calculate_flash_base,$(FLASH_PARTITIONS),dtb_b)
KERNEL_A_HEADER_FLASH_BASE    := $(call calculate_flash_base,$(FLASH_PARTITIONS),kernel)
KERNEL_B_HEADER_FLASH_BASE    := $(call calculate_flash_base,$(FLASH_PARTITIONS),kernel_b)
