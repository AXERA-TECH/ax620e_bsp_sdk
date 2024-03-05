################################################################################
#	prepare param
################################################################################
CUR_PATH				:= $(shell pwd)
HOME_PATH				:= $(abspath $(CUR_PATH)/../../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

PRJ_OUT_HOME			:= $(HOME_PATH)/build/out/$(PROJECT)
OBJ_OUT_PATH			:= $(PRJ_OUT_HOME)/objs
SRC_PATH				:= $(CUR_PATH)
LIB_PATH				:= $(MSP_OUT_PATH)/lib
SRC_RELATIVE_PATH		:= $(subst $(HOME_PATH)/,,$(SRC_PATH))
TARGET_OUT_PATH			:= $(OBJ_OUT_PATH)/$(SRC_RELATIVE_PATH)

################################################################################
# build
################################################################################

.PHONY : all clean install bin
.NOTPARALLEL: clean install
all: bin
	@echo -e $(GREEN)"\nBuild $@ success!!\n"  $(DONE)

clean:
	$(VERB) $(MAKE) -f Makefile.dynamic clean
	$(VERB) $(MAKE) -f Makefile.static clean
	@echo -e $(GREEN)"\nClean $@ success!!\n"  $(DONE)

install:
	@echo -e $(GREEN)"install $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic install
	$(VERB) $(MAKE) -f Makefile.static install

bin:
	@echo -e $(GREEN)"build dynamic $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic

	@echo -e $(GREEN)"build static $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.static