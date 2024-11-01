CUR_PATH		:= $(shell pwd)
HOME_PATH		:= $(abspath $(CUR_PATH)/../../..)

include $(HOME_PATH)/build/color.mk
include $(HOME_PATH)/build/config.mak

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
	@echo -e $(GREEN)"Install $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic install
	$(VERB) $(MAKE) -f Makefile.static install

bin:
	@echo -e $(GREEN)"Build dynamic $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.dynamic

	@echo -e $(GREEN)"Build static $@ ..."  $(DONE)
	$(VERB) $(MAKE) -f Makefile.static

