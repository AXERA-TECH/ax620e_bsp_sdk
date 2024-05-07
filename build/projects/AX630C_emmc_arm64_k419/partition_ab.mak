# The address of the text segment in the startup phase, do not recommend modification.
IMG_HEADER_SIZE                 := 1024
DDRINIT_PARAM_HEADER_BASE       := 0x03200000
ATF_IMG_HEADER_BASE             := 0x4003FC00
ATF_IMG_ADDR                    := 0x40040000
ATF_IMG_PKG_SIZE                := 0x40000
UBOOT_IMG_HEADER_BASE           := 0x5C000000
ifeq ($(strip $(SUPPORT_OPTEE)),TRUE)
OPTEE_IMAGE_ADDR                := 0x44200000
OPTEE_RESERVED_SIZE             := 0x2000000
OPTEE_SHMEM_SIZE                := 0x200000
endif
AXERA_DTB_IMG_ADDR              := 0x40001000
DTB_IMG_HEADER_ADDR             := ($(AXERA_DTB_IMG_ADDR) - $(IMG_HEADER_SIZE))
AXERA_KERNEL_IMG_ADDR           := 0x40200000
KERNEL_IMG_HEADER_ADDR          := ($(AXERA_KERNEL_IMG_ADDR) - $(IMG_HEADER_SIZE))
#############################################################################################
# Note: The above configuration is generally not modified.

#partition size config
SPL_PARTITION_SIZE        := 768K
DDRINIT_PARTITION_SIZE    := 512K
ATF_PARTITION_SIZE        := 256K
ATF_B_PARTITION_SIZE      := 256K
UBOOT_PARTITION_SIZE      := 1536K
UBOOT_B_PARTITION_SIZE    := 1536K
ENV_PARTITION_SIZE        := 1M
ifeq ($(strip $(SUPPORT_OPTEE)),TRUE)
OPTEE_PARTITION_SIZE      := 1M
OPTEE_B_PARTITION_SIZE    := 1M
endif
LOGO_PARTITION_SIZE       := 6M
LOGO_B_PARTITION_SIZE     := 6M
DTB_PARTITION_SIZE        := 1M
DTB_B_PARTITION_SIZE      := 1M
KERNEL_PARTITION_SIZE     := 64M
KERNEL_B_PARTITION_SIZE   := 64M
ROOTFS_PARTITION_SIZE     := 2048M
PARAM_PARTITION_SIZE      := 5M
SOC_PARTITION_SIZE        := 1024M
OPT_PARTITION_SIZE        := 4096M
AUTO_FIT_PARTITION        := OPT

# env part size, size is equal to ENV_PARTITION_SIZE
ENV_IMG_PKG_SIZE          := 0x100000

# Dram base address and size
SYS_DRAM_BASE             := 0x40000000
ifneq ($(findstring yes, $(debugkconfig) $(asan)),)
SYS_DRAM_SIZE             := 2048 #MB
else
SYS_DRAM_SIZE             := 1024 #MB
endif

# linux OS memory config
ifneq ($(findstring yes, $(debugkconfig) $(asan)),)
OS_MEM_SIZE          := 1024 #MB
else
OS_MEM_SIZE          := 256 #MB
endif
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
FLASH_PARTITIONS  += $(ATF_PART),$(ATF_B_PART),$(UBOOT_PART),$(UBOOT_B_PART),
FLASH_PARTITIONS  += $(ENV_PART),$(LOGO_PART),$(LOGO_B_PART),
ifeq ($(strip $(SUPPORT_OPTEE)),TRUE)
FLASH_PARTITIONS  += $(OPTEE_PART),$(OPTEE_B_PART),
endif
FLASH_PARTITIONS  += $(DTB_PART),$(DTB_B_PART),$(KERNEL_PART),$(KERNEL_B_PART),
FLASH_PARTITIONS  += $(ROOTFS_PART),$(PARAM_PART),$(SOC_PART),$(OPT_PART)
FLASH_PARTITIONS  := $(shell echo '$(FLASH_PARTITIONS)' | tr -d ' ')
ROOTFS_TYPE       := ext4
ROOTFS_POSITION   := $(shell echo "$(FLASH_PARTITIONS)" | tr ',' '\n' | grep -n 'rootfs' | cut -d ':' -f 1)
ROOTFS_DEV        := /dev/mmcblk0p$(strip $(ROOTFS_POSITION))
KERNEL_BOOTARGS   := "$(OS_MEM) console=ttyS0,115200n8 earlycon=uart8250,mmio32,0x4880000 board_id=0,boot_reason=0x0 initcall_debug=0 loglevel=8 \
usbcore.autosuspend=-1 root=$(ROOTFS_DEV) rootfstype=$(ROOTFS_TYPE) rw rootwait blkdevparts=mmcblk0:$(FLASH_PARTITIONS)"

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
