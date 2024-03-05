CUR_PATH		:= $(shell pwd)
HOME_PATH		:= $(abspath $(CUR_PATH)/../../../../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

OUT_DIR			:= $(HOME_PATH)/build/out/$(PROJECT)/objs
OUT_PATH		:= $(MSP_OUT_PATH)
SRC_PATH		:= $(CUR_PATH)
BASE_PATH		:= $(HOME_PATH)/msp/component
SRC_RELATIVE_PATH	:= $(subst $(HOME_PATH)/,,$(SRC_PATH))
TARGET_OUT_PATH		:= $(OUT_DIR)/$(SRC_RELATIVE_PATH)
GENERATED_PATH       := $(TARGET_OUT_PATH)/generated

CINCLUDE    += -I$(GENERATED_PATH)
export CINCLUDE
################################################################################
# build
################################################################################

.PHONY : all clean install lib modversion
.NOTPARALLEL: clean install modversion

all: lib
	@echo -e $(GREEN)"\nBuild $@ success!!\n"  $(DONE)

clean:
	$(VERB) $(MAKE) -f Makefile.dynamic clean
	$(VERB) $(MAKE) -f Makefile.static clean
	@echo -e $(GREEN)"\nClean $@ success!!\n"  $(DONE)

install:
	@echo -e $(GREEN)"Install $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic install
	$(VERB) $(MAKE) -f Makefile.static install

lib:
	@echo -e $(GREEN)"Build dynamic $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic

	@echo -e $(GREEN)"Build static $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.static

modversion:
	@echo -e $(GREEN)"Build $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic modversion
