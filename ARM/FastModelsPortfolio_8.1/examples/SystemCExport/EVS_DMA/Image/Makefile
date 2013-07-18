#
# Makefile - DMA example application makefile.
#
# Copyright 2012 ARM Limited.
# All rights reserved.
#

# This makefile is intended for use with GNU make.

RVCT_LIB = $(shell which armcc | sed -e "s/Programs/Data/" | sed -e "s;linux-pentium/armcc;lib;")
RVCT_INC = $(shell which armcc | sed -e "s/Programs/Data/" | sed -e "s;linux-pentium/armcc;include/unix;")
CC = armcc
LD = armlink
CFLAGS = -W -g -O2 -Otime -I $(RVCT_INC)
LDFLAGS = --info totals --info unused --libpath $(RVCT_LIB)
V6CFLAGS = --arm --cpu=6
V7MCFLAGS = --thumb --cpu=Cortex-M3
WFICFLAGS = --arm --cpu=7-R -D USE_WFI
V6LDFLAGS = 
V7MLDFLAGS = 
WFILDFLAGS = 

v6:
	mkdir v6

v7m:
	mkdir v7m

wfi:
	mkdir wfi

v6/%.o: %.c
	$(CC) $(CFLAGS) $(V6CFLAGS) -c -o $@ $<

v7m/%.o: %.c
	$(CC) $(CFLAGS) $(V7MCFLAGS) -c -o $@ $<

wfi/%.o: %.c
	$(CC) $(CFLAGS) $(WFICFLAGS) -c -o $@ $<

all: dma.axf dma_v7m.axf dma_wfi.axf

dma.axf: v6 v6/dma.o
	$(LD) $(LDFLAGS) $(V6LDFLAGS) -o $@ $^

dma_v7m.axf: v7m v7m/dma.o
	$(LD) $(LDFLAGS) $(V7MLDFLAGS) -o $@ $^

dma_wfi.axf: wfi wfi/dma.o
	$(LD) $(LDFLAGS) $(WFILDFLAGS) -o $@ $^

clean:
	-rm -f *.axf *.list *.map
	-rm -f v6/*.o v7m/*.o wfi/*.o

