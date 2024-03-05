MKFILE_PATH     := $(abspath $(lastword $(MAKEFILE_LIST)))
HOME_PATH       ?= $(abspath $(dir $(MKFILE_PATH))..)
SCRIPTS_PATH    := $(HOME_PATH)/kernel/linux/$(KERNEL_DIR)/scripts/axera
GENERATED_PATH  ?= $(TARGET_OUT_PATH)/generated

COMPILER_HOSTNAME_STR := \"$(shell hostname)\"

CPPFLAGS	+= -DCOMPILER_HOSTNAME=$(COMPILER_HOSTNAME_STR)
CFLAGS		+= -DCOMPILER_HOSTNAME=$(COMPILER_HOSTNAME_STR)
CPPFLAGS	+= -D$(PROJECT) -D$(CHIP_NAME)
CFLAGS		+= -D$(PROJECT) -D$(CHIP_NAME)
CPPFLAGS	+= -DBUILD_AXVERSION=\"$(SDK_VERSION)\"
CFLAGS		+= -DBUILD_AXVERSION=\"$(SDK_VERSION)\"

MOD_VER_FILE    := $(GENERATED_PATH)/ax_module_version.h

ifeq ($(SUPPORT_HW_EL),TRUE)
CFLAGS		+= -DCONFIG_SUPPORT_HW_EL
endif

ifeq ($(asan),yes)
CPPFLAGS	+= -fsanitize=leak -fsanitize=address  -fno-omit-frame-pointer
CFLAGS		+= -fsanitize=leak -fsanitize=address  -fno-omit-frame-pointer
LDFLAGS     += -fsanitize=leak -fsanitize=address  -fno-omit-frame-pointer
endif

ifneq ($(SONAME),)
LDFLAGS		+= -Wl,-soname,$(SONAME)
endif

ifeq ($(LIB_DIR),)
LIB_DIR		:= lib
endif

ifneq ($(INSTALL_LIB),)
ifneq ($(wildcard $(INSTALL_LIB)),)
MV_TARGET := $(INSTALL_LIB)
endif
endif

define BUILD_STATIC_LIB
	$(if $(wildcard $@),@$(RM) $@)
	$(if $(wildcard ar.mac),@$(RM) ar.mac)
	$(if $(filter $(LIB_DIR)%.a, $@),
		@$(ECHO) CREATE $@ > ar.mac
		@$(ECHO) SAVE >> ar.mac
		@$(ECHO) END >> ar.mac
		@$(CROSS)ar -M < ar.mac)
	$(if $(filter %.o, $^),@$(CROSS)ar -q $@ $(filter %.o, $^))
	$(if $(filter %.a, $(COMBINE_LIBS)),
		@$(ECHO) OPEN $@ > ar.mac
		$(foreach LIB, $(filter %.a, $(COMBINE_LIBS)),
			@echo ADDLIB $(LIB) >> ar.mac)
		@$(ECHO) SAVE >> ar.mac
		@$(ECHO) END >> ar.mac
		@$(CROSS)ar -M < ar.mac)
	$(if $(wildcard ar.mac),@$(RM) ar.mac)
endef

define file_exists
	$(shell if [ -e $(1) ]; then echo 1; else echo 0; fi;)
endef

all: install

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
-include $(CPPDEPS)
endif

$(TARGET): $(OBJS) $(CPPOBJS)

	@$(RM) $@;
	$(VERB) $(LINK) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(CPPOBJS) $(CLIB)
ifneq ($(LINKNAME),)
	$(VERB) $(LN) $@ $(LINKNAME)
endif
ifneq ($(RENAME),)
	$(VERB) $(MV) $@ $(RENAME)
	$(VERB) $(LN) $(RENAME) $@
endif

$(STRIPPED_TARGET): $(OBJS) $(CPPOBJS)
	@$(RM) $@;
	$(VERB) $(LINK) $(CFLAGS) $(LDFLAGS) -o $(STRIPPED_TARGET) $(OBJS) $(CPPOBJS) $(CLIB)
ifeq ($(SPLIT_DEBUG_INFO),yes)
	$(OBJCPOY) --only-keep-debug $(STRIPPED_TARGET) $(DEBUG_TARGET)
	$(STRIP) -g $(STRIPPED_TARGET)
	$(OBJCPOY) --add-gnu-debuglink=$(DEBUG_TARGET) $(STRIPPED_TARGET)
else
	$(VERB) $(CP) $@ $(DEBUG_TARGET)
	$(STRIP) $@
endif
ifneq ($(LINKNAME),)
	$(VERB) $(LN) $@ $(LINKNAME)
endif
ifneq ($(RENAME),)
	$(VERB) $(MV) $@ $(RENAME)
	$(VERB) $(LN) $(RENAME) $@
endif

$(STATIC_TARGET): $(OBJS) $(CPPOBJS)
	@-$(RM) $@
ifneq ($(COMBINE_LIBS),)
	$(call BUILD_STATIC_LIB)
else
	$(VERB) $(AR) $(STATIC_TARGET) $(OBJS) $(CPPOBJS)
endif

$(STRIPPED_STATIC_TARGET): $(OBJS) $(CPPOBJS)
	@$(RM) $@;
ifneq ($(COMBINE_LIBS),)
	$(call BUILD_STATIC_LIB)
else
	$(VERB) $(AR) $(STRIPPED_STATIC_TARGET) $(OBJS) $(CPPOBJS)
endif
	$(STRIP) --strip-unneeded $(STRIPPED_STATIC_TARGET)

$(OUTPUT)/%.o %.o : %.c
	@$(MKDIR) $(dir $@)
	$(VERB) $(ECHO) "[CC]  " $<
	$(VERB) $(CC) -MMD $(CFLAGS) $(CINCLUDE) -c -o $@ $<

$(OUTPUT)/%.o %.o : %.cpp
	@$(MKDIR) $(dir $@)
	$(VERB) $(ECHO) "[CPP]  " $<
	$(VERB) $(CPP) -MMD $(CFLAGS) $(CINCLUDE) -c -o $@ $<

$(OUTPUT)/%.o %.o : %.cc
	@$(MKDIR) $(dir $@)
	$(VERB) $(ECHO) "[CPP]  " $<
	$(VERB) $(CPP) -MMD $(CFLAGS) $(CINCLUDE) -c -o $@ $<

$(OUTPUT)/%.a %.a : %.a
	@$(MKDIR) $(dir $@)
	$(VERB) $(ECHO) "[LINK STATIC]  " $<
	@-$(CP) $< $(dir $@)

$(OUTPUT)/%.o %.o : %.o
	@$(MKDIR) $(dir $@)
	$(VERB) $(ECHO) "[LINK OBJ]  " $<

clean: local_clean
	$(VERB) $(RM) $(TARGET) $(STRIPPED_TARGET) $(DEBUG_TARGET) $(STATIC_TARGET) $(STRIPPED_STATIC_TARGET) $(DEPS) $(CPPDEPS) $(LINKNAME)
	$(VERB) $(RM) $(OUTPUT) $(TARGET_OUT_PATH) -R

ifeq ($(soversion),yes)
	$(VERB) $(RM) $(MOD_VER_FILE)
endif

local_clean:
ifneq ($(LOCAL_TARGETS),)
	$(VERB) $(RM) $(LOCAL_TARGETS)
endif

#  -----------------------------------------------------------------------------
#  Desc: Install TARGET
#  -----------------------------------------------------------------------------
install: modversion $(TARGET) $(STRIPPED_TARGET) $(STATIC_TARGET) $(STRIPPED_STATIC_TARGET)
ifneq ($(INSTALL_TARGET), )
ifneq ($(INSTALL_DIR), $(dir $(INSTALL_TARGET)))

ifneq ($(INSTALL_DIR), $(wildcard $(INSTALL_DIR)))
	$(VERB) $(MKDIR) $(INSTALL_DIR)
endif
	@-$(CP) -P -p -r $(INSTALL_TARGET) $(INSTALL_DIR)
	@$(ECHO) -e "\e[36;1m" "INSTALL   $(INSTALL_TARGET) to $(INSTALL_DIR)" "\033[0m"
ifneq ($(MV_TARGET),)
ifneq ($(TARGET_OUT_PATH),)
	@$(MV)  $(MV_TARGET) $(TARGET_OUT_PATH)
endif
endif
endif
endif

ifneq ($(INSTALL_ETC), )
ifneq ($(ROOTFS_TARGET_PATH)/etc, $(dir $(INSTALL_ETC)))

ifneq ($(ROOTFS_TARGET_PATH)/etc, $(wildcard $(ROOTFS_TARGET_PATH)/etc))
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/etc
endif
	@-$(CP) -P -p $(INSTALL_ETC) $(ROOTFS_TARGET_PATH)/etc/
	@$(ECHO) -e "\e[36;1m" "INSTALL   $(INSTALL_ETC) to $(ROOTFS_TARGET_PATH)/etc" "\033[0m"
endif
endif

ifneq ($(INSTALL_AIISP_MODELS), )
ifneq ($(ROOTFS_TARGET_PATH)/etc/models/aiisp, $(dir $(INSTALL_AIISP_MODELS)))

ifneq ($(ROOTFS_TARGET_PATH)/etc/models/aiisp, $(wildcard $(ROOTFS_TARGET_PATH)/etc/models/aiisp))
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/etc/models
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/etc/models/aiisp
endif
	@-$(CP) -r -P -p $(INSTALL_AIISP_MODELS) $(ROOTFS_TARGET_PATH)/etc/models/aiisp
	@$(ECHO) -e "\e[36;1m" "INSTALL   $(INSTALL_AIISP_MODELS) to $(ROOTFS_TARGET_PATH)/etc/models/aiisp" "\033[0m"
endif
endif

ifneq ($(INSTALL_LIB), )
ifneq ($(ROOTFS_TARGET_PATH)/$(LIB_DIR), $(dir $(INSTALL_LIB)))

ifneq ($(ROOTFS_TARGET_PATH)/$(LIB_DIR), $(wildcard $(ROOTFS_TARGET_PATH)/$(LIB_DIR)))
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/$(LIB_DIR)
endif
	@-$(CP) -P -p $(INSTALL_LIB) $(ROOTFS_TARGET_PATH)/$(LIB_DIR)/
	@$(ECHO) -e "\e[36;1m" "INSTALL   $(INSTALL_LIB) to $(ROOTFS_TARGET_PATH)/$(LIB_DIR)" "\033[0m"
ifneq ($(MV_TARGET),)
ifneq ($(TARGET_OUT_PATH),)
	@$(MV)  $(MV_TARGET) $(TARGET_OUT_PATH)
endif
endif
endif
endif

ifneq ($(INSTALL_BIN), )
ifneq ($(ROOTFS_TARGET_PATH)/bin, $(dir $(INSTALL_BIN)))

ifneq ($(ROOTFS_TARGET_PATH)/bin, $(wildcard $(ROOTFS_TARGET_PATH)/bin))
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/bin
endif
	@-$(CP) -P -p -r $(INSTALL_BIN) $(ROOTFS_TARGET_PATH)/bin/
	@$(ECHO) -e "\e[36;1m" "INSTALL   $(INSTALL_BIN) to $(ROOTFS_TARGET_PATH)/bin" "\033[0m"
ifneq ($(MV_TARGET),)
ifneq ($(TARGET_OUT_PATH),)
	@$(MV)  $(MV_TARGET) $(TARGET_OUT_PATH)
endif
endif
endif
endif

ifneq ($(INSTALL_INC), )
ifneq ($(ROOTFS_TARGET_PATH)/include, $(dir $(INSTALL_INC)))

ifneq ($(ROOTFS_TARGET_PATH)/include, $(wildcard $(ROOTFS_TARGET_PATH)/include))
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/include
endif
	@-$(CP) -P -p $(INSTALL_INC) $(ROOTFS_TARGET_PATH)/include/
	@$(ECHO) -e "\e[36;1m" "INSTALL   $(INSTALL_INC) to $(ROOTFS_TARGET_PATH)/include" "\033[0m"
endif
endif

ifneq ($(INSTALL_DATA), )
ifneq ($(ROOTFS_TARGET_PATH)/data, $(dir $(INSTALL_DATA)))

ifneq ($(ROOTFS_TARGET_PATH)/data, $(wildcard $(ROOTFS_TARGET_PATH)/data))
	$(VERB) $(MKDIR) $(ROOTFS_TARGET_PATH)/data
endif
	@-$(CP) -r -P -p $(INSTALL_DATA) $(ROOTFS_TARGET_PATH)/data/
	@$(ECHO) -e "\e[36;1m" "INSTALL   $(INSTALL_DATA) to $(ROOTFS_TARGET_PATH)/data" "\033[0m"
endif
endif

modversion:
ifeq ($(soversion),yes)
ifneq ($(SONAME),)
	@if [ $(call file_exists,$(MOD_VER_FILE)) -eq 0 ]; then \
		mkdir -p $(GENERATED_PATH); \
		bash $(SCRIPTS_PATH)/axera_module_version.sh $(MOD_VER_FILE) $(SONAME) $(SDK_VERSION);\
	fi
endif
endif
