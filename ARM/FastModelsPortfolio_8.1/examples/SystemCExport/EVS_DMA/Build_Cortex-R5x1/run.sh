#!/bin/sh
#
# run.sh - Run the EVS_DMA example.
#
# Copyright 2012 ARM Limited.
# All rights reserved.
#

./EVS_DMA_Cortex-R5x1.x -a DMA.Core.cpu0=../Image/dma.axf $*
