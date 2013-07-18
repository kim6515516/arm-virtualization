
# Makefile to build trace plugin
# Copyright ARM Limited 2009-2011 All Rights Reserved.
#

BITS ?= 32

CPPFLAGS = -I ../../../include -I ../../../include/eslapi
CXXFLAGS = -W -Wall -Werror -m$(BITS) -O3 -DNDEBUG -fomit-frame-pointer -fPIC

ifeq ($(BITS),32)
CXXFLAGS += -march=pentiumpro -mtune=pentium4
endif

all: GenericTrace.so

GenericTrace.o: GenericTrace.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

FormattedBuffer.o: FormattedBuffer.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

PatternBuffer.o: PatternBuffer.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

GenericTrace.so: GenericTrace.o FormattedBuffer.o PatternBuffer.o
	$(CXX) -m$(BITS) -pthread -ldl -lrt -shared -o $@ GenericTrace.o FormattedBuffer.o PatternBuffer.o

clean:
	rm -f *.o
	rm -f GenericTrace.so

# Use C++ linker:
CC=CXX

# End of Makefile
