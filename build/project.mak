AX_PRJ_LIST += AX620Q_nand_arm32_k419

ifneq ($(MAKECMDGOALS),plist)
ifneq ($(MAKECMDGOALS),scan)

ifneq ($(project),)
PROJECT := $(project)
else ifneq ($(p),)
PROJECT := $(p)
else
$(error project(p) is not asigned, example: p=AX620E_haps or call "make plist" to show all projects)
endif

ifeq ($(words $(subst $(PROJECT),,$(AX_PRJ_LIST))), $(words $(AX_PRJ_LIST)))
$(error project "$(PROJECT)" does not exist!!!)
endif

CHIP_NAME := CHIP_$(shell echo  ${PROJECT} | awk -F '_' '{print $$1}' | sed 's/AX620Q/AX620E/; s/AX630C/AX620E/')
endif # ifeq ($(MAKECMDGOALS),scan)
endif # ifeq ($(MAKECMDGOALS),list)

define list_projects
	@echo -e "\e[34;1m -------project list------\033[0m"
	@for prj in $(AX_PRJ_LIST); do \
		echo -e "\e[34;1m  p=$$prj\033[0m";\
	done
endef

ifeq ($(MAKECMDGOALS),plist)
plist:
	$(call list_projects)
endif
