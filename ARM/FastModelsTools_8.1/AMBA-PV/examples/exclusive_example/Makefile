#
# AMBA-PV: Makefile - Exclusive example makefile.
#
# Copyright 2007-2009, 2011 ARM Limited.
# All rights reserved.
#

ifeq ($(TARGET_ARCH),)
  ifeq ($(shell uname -a | grep "\(x86_64\)\|\(ia64\)"),)
    TARGET_ARCH = Linux
  else
    TARGET_ARCH = Linux64
  endif
endif

CXX = g++
CXXVER = $(shell $(CXX) -dumpversion | \
                 sed -e "s/\([0-9]*\.[0-9]*\)\.[0-9]*/\1/")
ifeq ($(TARGET_ARCH),Linux64)
  CXXFLAGS += -m64
else
  CXXFLAGS += -m32
endif
ifeq ($(DEBUG),y)
  CXXFLAGS += -g
else
  CXXFLAGS += -DNDEBUG
endif
CXXFLAGS += -DAMBA_PV_INCLUDE_ATTRIBUTES
CXXFLAGS += -O3 -Wall -pedantic -Wno-long-long
CXXFLAGS += -I$(SYSTEMC_HOME)/include -I$(TLM_HOME)/include/tlm -I../../include
LDFLAGS += -static -L$(SYSTEMC_HOME)/lib/$(TARGET_ARCH)_GCC-$(CXXVER) \
           -lsystemc -lm

SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
TARGET = exclusive.x

.SUFFIXES:
.SUFFIXES: .cpp .o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(TARGET)

probe: CXXFLAGS += -DPROBE
probe: $(TARGET)

clean:
	-rm -f $(TARGET) *.o *.bak *~ *.*~

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)
