CUR_PATH            := $(shell pwd)
HOME_PATH           := $(abspath $(CUR_PATH)/../../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

PRJ_OUT_HOME        := $(HOME_PATH)/build/out/$(PROJECT)
OBJ_OUT_PATH        := $(PRJ_OUT_HOME)/objs
LIB_PATH            := $(MSP_OUT_PATH)/lib
INC_PATH            := $(MSP_OUT_PATH)/include
SRC_RELATIVE_PATH   := $(subst $(HOME_PATH)/,,$(CUR_PATH))
TARGET_OUT_PATH     := $(OBJ_OUT_PATH)/$(SRC_RELATIVE_PATH)
BIN_PATH            := $(HOME_PATH)/app/demo/FRTDemo/bin
SRC_PATH            := $(HOME_PATH)/app/demo/FRTDemo/src
COMPONENT_PATH      := $(HOME_PATH)/app/component
COMPONENT_3RD_PATH  := $(COMPONENT_PATH)/3rd
RESOURCE_PATH       := $(HOME_PATH)/app/component/resource
3RD_PATH            := $(HOME_PATH)/third-party
SSL_PATH            := $(3RD_PATH)/openssl

FONT_USE_FREETYPE   := no
MP4ENC_SUPPORT      := yes

ifeq ($(CHIP_TYPE), AX620Q)
STRIP_APP           := yes
IPC_SUPPORT         := yes
PANO_SUPPORT        := no
TUNING_CTRL_SUPPORT := yes
else
STRIP_APP           := no
IPC_SUPPORT         := yes
PANO_SUPPORT        := yes
TUNING_CTRL_SUPPORT := yes
endif

################################################################################
# build
################################################################################

.PHONY : all clean install
all: app
	@echo -e $(GREEN)"\nBuild $@ success!!\n"  $(DONE)

clean:
	$(VERB) $(RM) $(ROOTFS_TARGET_PATH)/bin/FRTDemo -R
	$(VERB) $(MAKE) -f Makefile.dynamic clean
	$(VERB) $(MAKE) -f Makefile.static clean
	@echo -e $(GREEN)"\nClean $@ success!!\n"  $(DONE)

install:
	@echo -e $(GREEN)"Install $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic install
	$(VERB) $(MAKE) -f Makefile.static install
	$(VERB) $(CP) $(BIN_PATH)/* $(ROOTFS_TARGET_PATH)/bin/FRTDemo -R
	$(VERB) $(CP) $(RESOURCE_PATH)/lib/$(ARCH)/$(LIBC)/appweb $(ROOTFS_TARGET_PATH)/bin/FRTDemo/lib -R
	$(VERB) $(CP) $(RESOURCE_PATH)/res $(ROOTFS_TARGET_PATH)/bin/FRTDemo -R
	$(VERB) $(CP) $(RESOURCE_PATH)/web $(ROOTFS_TARGET_PATH)/bin/FRTDemo -R
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/data/avscalid
	$(VERB) $(CP) $(RESOURCE_PATH)/avs $(ROOTFS_TARGET_PATH)/data/avscalid -R
ifeq ($(CHIP_TYPE), AX620Q)
	$(VERB) $(CP) $(RESOURCE_PATH)/lite/* $(ROOTFS_TARGET_PATH)/bin/FRTDemo/config -R
endif

ifeq ($(FONT_USE_FREETYPE),yes)
	$(VERB) $(CP) $(RESOURCE_PATH)/font/GB2312.ttf $(ROOTFS_TARGET_PATH)/bin/FRTDemo/res
endif

app:
	@echo -e $(GREEN)"Build dynamic $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic

	@echo -e $(GREEN)"Build static $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.static

export FONT_USE_FREETYPE
export MP4ENC_SUPPORT
export STRIP_APP
export IPC_SUPPORT
export PANO_SUPPORT
export TUNING_CTRL_SUPPORT
