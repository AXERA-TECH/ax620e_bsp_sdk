VERB	= @
RM	= rm -f
MKDIR	= mkdir -p
ECHO	= echo
MV	= mv
LN	= ln -sf
CP	= cp -f
TAR	= tar
TOUCH	= touch
STATIC_FLAG := -fPIC -ffunction-sections -fdata-sections
DYNAMIC_FLAG := -shared -fPIC -Wl,--gc-sections
EXEC_FLAG := -Wl,--gc-sections

BUILD_DIR = $(shell dirname $(lastword $(MAKEFILE_LIST)))

include $(BUILD_DIR)/project.mak
include $(BUILD_DIR)/version.mak

ifneq ($(MAKECMDGOALS),plist)
ifneq ($(MAKECMDGOALS),scan)
include $(BUILD_DIR)/projects/$(PROJECT)/project.mak
endif # ifeq ($(MAKECMDGOALS),scan)
endif # ifeq ($(MAKECMDGOALS),list)

export SDK_VERSION
AXERA_SDK_RELEASE := TRUE # it must be TRUE in customer SDK
