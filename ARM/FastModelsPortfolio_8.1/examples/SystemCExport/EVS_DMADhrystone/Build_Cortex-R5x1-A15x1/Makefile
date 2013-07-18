#
# Makefile - DMADhrystone platform makefile.
#
# Copyright 2011-2012 ARM Limited.
# All rights reserved.
#

# Common rules
include ../../Common/Makefile.common

# Specify objects and target(s) to build
SRCS = $(wildcard ../Source/*.cpp) \
	   ../../EVS_DMA/Source/master.cpp \
	   ../../EVS_DMA/Source/pv_dma.cpp
TARGET = EVS_DMADhrystone_Cortex-R5x1-A15x1.x

# Determine others...
DMA_DIR = ./EVS_DMA_Cortex-R5x1
DMA_GENDIR = $(DMA_DIR)/$(CONFIG)/gen
DMA_BUILDDIR = $(DMA_DIR)/$(CONFIG)
DMA_WRAPPERLIB = scx-DMA-$(CONFIG)
DMA_EVSLIB  = DMA-$(CONFIG)
DHRY_DIR = ./EVS_Dhrystone_Cortex-A15x1
DHRY_GENDIR = $(DHRY_DIR)/$(CONFIG)/gen
DHRY_BUILDDIR = $(DHRY_DIR)/$(CONFIG)
DHRY_WRAPPERLIB = scx-Dhrystone-$(CONFIG)
DHRY_EVSLIB  = Dhrystone-$(CONFIG)

CXXFLAGS += -I$(DHRY_GENDIR) -I$(DMA_GENDIR) -I../../EVS_DMA/Source
LDFLAGS += -L$(DHRY_BUILDDIR) -L$(DMA_BUILDDIR) \
		   -l$(DHRY_WRAPPERLIB) -l$(DMA_WRAPPERLIB) -lcomponents -lpvbus \
		   $(PVLIB_HOME)/lib/Linux$(BITNESS_IN_NAME)_GCC-$(GCC_VER)/libarmctmodel.a \
		   -lscx -lfmruntime -lsystemc -l$(DHRY_EVSLIB) -l$(DMA_EVSLIB) \
		   -ldl -lrt -Wl,-rpath,'$$ORIGIN'

# Determine commands
DMA_SIMGEN_CMD = cd $(DMA_DIR) && $(MAXCORE_HOME)/bin/simgen \
				 -p ../../../EVS_DMA/Build_Cortex-R5x1/EVS_DMA_Cortex-R5x1.sgproj \
				 --num-build-cpus $(J) --configuration $(CONFIG) \
				 $(SIMGENFLAGS)
DHRY_SIMGEN_CMD = cd $(DHRY_DIR) && $(MAXCORE_HOME)/bin/simgen \
				  -p ../../../EVS_Dhrystone/Build_Cortex-A15x1/EVS_Dhrystone_Cortex-A15x1.sgproj \
				  --num-build-cpus $(J) --configuration $(CONFIG) \
				  $(SIMGENFLAGS)
CXX_CMD = $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Local rules
.SUFFIXES:

.PHONY: dbg_gcc41_32 rel_gcc41_32
.PHONY: dbg_gcc41_32 rel_gcc41_32
.PHONY: dbg_gcc41_32_clean rel_gcc41_32_clean
.PHONY: dbg_gcc41_32_clean rel_gcc41_32_clean
.PHONY: dbg_gcc41_64 rel_gcc41_64
.PHONY: dbg_gcc41_64 rel_gcc41_64
.PHONY: dbg_gcc41_64_clean rel_gcc41_64_clean
.PHONY: dbg_gcc41_64_clean rel_gcc41_64_clean

$(DMA_DIR):
	-mkdir $(DMA_DIR)

$(DHRY_DIR):
	-mkdir $(DHRY_DIR)

dbg_gcc41_32 rel_gcc41_32 dbg_gcc41_64 rel_gcc41_64 dbg_gcc44_32 rel_gcc44_32 dbg_gcc44_64 rel_gcc44_64: $(DMA_DIR) $(DHRY_DIR)
	$(DMA_SIMGEN_CMD) -b
	$(DHRY_SIMGEN_CMD) -b
	cp $(DMA_BUILDDIR)/lib$(DMA_EVSLIB).so ./
	cp $(DHRY_BUILDDIR)/lib$(DHRY_EVSLIB).so ./
	$(CXX_CMD)
	cp $(DMA_DIR)/libarmctmodel.so ./
	cp $(DMA_DIR)/libSDL-1.2.so.0.11.2 ./
	cp $(DMA_DIR)/libMAXCOREInitSimulationEngine.so.2 ./

dbg_gcc41_32_clean rel_gcc41_32_clean dbg_gcc41_64_clean rel_gcc41_64_clean dbg_gcc44_32_clean rel_gcc44_32_clean dbg_gcc44_64_clean rel_gcc44_64_clean:
	-$(DMA_SIMGEN_CMD) --clean
	-$(DHRY_SIMGEN_CMD) --clean
	-rm -f ./lib$(DMA_EVSLIB).so
	-rm -f ./lib$(DHRY_EVSLIB).so
	-rm -f $(TARGET)
	-rm -f ./libarmctmodel.so
	-rm -f ./libSDL-1.2.so.0.11.2
	-rm -f ./libMAXCOREInitSimulationEngine.so.2

