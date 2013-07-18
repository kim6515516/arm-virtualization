#
# AMBA-PV: Makefile - Examples Makefile.
#
# Copyright 2009 ARM Limited.
# All rights reserved.
#

# To avoid trouble on systems where the SHELL variable might be inherited from
# the environment.
SHELL := /bin/sh

# Check OS being built on
ifneq ($(shell uname),Linux)
    $(error $(shell uname): Unknown or unsupported platform)
endif

# Location of SystemC and TLM
ifeq ($(SYSTEMC_HOME),)
    $(error SYSTEMC_HOME: Undefined variable)
endif
ifeq ($(TLM_HOME),)
    $(error TLM_HOME: Undefined variable)
endif

# Rules
.PHONY: all

all: all-subdirs

.PHONY: clean

clean: clean-subdirs

.PHONY: dbg rel

dbg:
	@$(MAKE) DEBUG=y all

rel:
	@$(MAKE) DEBUG=n all

.PHONY: all-subdirs clean-subdirs

all-subdirs clean-subdirs:
	@dirs='$(shell ls -d ./*/)' ; \
		for dir in $$dirs ; do $(MAKE) -C $$dir $(patsubst %-subdirs,%,$@) || exit 1 ; done
