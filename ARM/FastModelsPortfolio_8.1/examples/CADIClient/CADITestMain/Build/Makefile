# CCIK example : Makefile
# Copyright (C) ARM Limited, 2010. All rights reserved.
#
# This Makefile is intended for use with GNU make

# Select build rules based on Windows or Linux
ifdef WINDIR
# Building on Windows
$(error This example is intended to be built on a Linux platform, not on Windows)
endif
ifdef windir
#  Building on Windows
$(error This example is intended to be built on a Linux platform, not on Windows)
endif

#  Building on Linux
DIST_DIR:=$(CURDIR)

ifdef COMPILER
CADILIB=$(PVLIB_HOME)/lib/$(COMPILER)/libcadiclient.a
else
ifneq ($(MAKECMDGOALS),list)
$(error COMPILER must be defined (e.g. make COMPILER=Linux_GCC-4.1))
endif
endif

ifeq ($(word 1, $(subst _, , $(COMPILER))), Linux64)
CPPFLAGS = -I $(PVLIB_HOME)/include/fmruntime -I . -Wall -W -m64
else
CPPFLAGS = -I $(PVLIB_HOME)/include/fmruntime -I . -Wall -W -m32
endif
CXXFLAGS = -Wall -g -O2

all: CADITestMain

CADITestMain: CADITestMain.cpp
	@mkdir -p $(COMPILER)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -DNDEBUG $^ $(CADILIB) -lpthread -lrt -ldl -o $(COMPILER)/$@

clean:
	rm -rf $(COMPILER)

# Use C++ linker:
CC=CXX

list:
	@echo "Linux_GCC-4.1"
	@echo "Linux64_GCC-4.1"
	@echo "Linux_GCC-4.4"
	@echo "Linux64_GCC-4.4"
