SUBDIRS = cmm pool
SUBDIRS += rtc
SUBDIRS += ivps
SUBDIRS += ivps_venc
SUBDIRS += vin
SUBDIRS += isp_3a
SUBDIRS += vo
SUBDIRS += audio
SUBDIRS += vdec
SUBDIRS += ives
SUBDIRS += venc
SUBDIRS += skel
SUBDIRS += efuse
SUBDIRS += ivps_jenc_slice
SUBDIRS += vin_ivps_vo_venc
SUBDIRS += vin_ivps_venc_rtsp
SUBDIRS += vin_ivps_engine_venc_rtsp
SUBDIRS += vin_ivps_skel_venc_rtsp
SUBDIRS += vdec_ivps_venc
SUBDIRS += vdec_ivps_vo
SUBDIRS += npu
SUBDIRS += uvc
SUBDIRS += cipher
SUBDIRS += ive
SUBDIRS += avs
SUBDIRS += sysmap
SUBDIRS += efuse_hash
SUBDIRS += gzipd
SUBDIRS += optee
################################################################################
#	prepare param
################################################################################
LOCAL_PATH		:= $(shell pwd)
HOME_PATH		:= $(abspath $(LOCAL_PATH)/../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

PRJ_OUT_HOME		:= $(HOME_PATH)/build/out/$(PROJECT)
OBJ_OUT_PATH		:= $(PRJ_OUT_HOME)/objs

################################################################################
#	set task
################################################################################
SUBDIRS_CLEAN   = $(addsuffix .clean, $(SUBDIRS))
SUBDIRS_INSTALL = $(addsuffix .install, $(SUBDIRS))

.PHONY: $(SUBDIRS) $(SUBDIRS_INSTALL) $(SUBDIRS_CLEAN)
.NOTPARALLEL: clean install

all: $(SUBDIRS)
	@$(ECHO) -e $(GREEN)"\nBuild All sample Modules success!!\n"  $(DONE)

install: $(SUBDIRS_INSTALL)
	@$(ECHO) -e $(GREEN)"\nInstall sample success!!\n"  $(DONE)

clean:	$(SUBDIRS_CLEAN)
	@$(ECHO) -e $(GREEN)"\nClean sample success!!\n"  $(DONE)

$(SUBDIRS):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $@ ..." $(DONE)
	@$(MAKE) -C $(basename $@ )

$(SUBDIRS_INSTALL):
	@$(ECHO)
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) install

$(SUBDIRS_CLEAN):
	@$(ECHO) -e $(CYAN)"In subdir $(basename $@ )..." $(DONE)
	@$(MAKE) -C $(basename $@ ) clean
