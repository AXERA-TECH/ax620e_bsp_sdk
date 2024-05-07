SEC_SIGN_HEADER_SIZE := 0x400

define MB2Bytes
    $(shell printf '0x%x' "$$((`echo $(1) | sed 's/M//'` * 1024 * 1024))")
endef

define AddAddressMB
    $(shell printf "0x%X" $$(($(1) + $(2)*1048576)))
endef

define SubAddressMB
    $(shell printf "0x%X" $$(($(1) - $(2)*1048576)))
endef

define SubAddressB
    $(shell printf "0x%X" $$(($(1) - $(2))))
endef

define KM2Bytes
    $(if $(findstring K,$(1)),$(shell echo $$(($(subst K,,$(1))*1024))),$(shell echo $$(($(subst M,,$(1))*1024*1024))))
endef

define AddKM2Bytes
$(shell echo $(patsubst %,0x%x,\
	$(foreach arg,$(1),$(call KM2Bytes,$(arg))) \
	| awk '{s+=$$1} END {print s}'))
endef

define AddKM2Bytes
    sum=0; \
    for arg in $(1); do \
        sum=$$(($$sum + $$arg)); \
    done; \
    echo $$sum;
endef


# Calculates the location of each partition in the flash.
define calculate_flash_base
$(shell echo "$(1)" | sed 's/$(2)/*/' | cut -d '*' -f 1 | tr ',' '\n' | awk '\
{\
  if ($$0 ~ /[0-9]*K/) {\
    sub(/K*/, "", $$0);\
    cur = $$0 * 1024;\
    sum += cur;\
  } else if ($$0 ~ /[0-9]*M/) {\
    sub(/M*/, "", $$0);\
    cur = $$0 * 1024 * 1024;\
    sum += cur;\
  }\
}\
END {\
  printf "0x%x", sum - cur;\
}')
endef
