#!/bin/sh
#
# run.sh - Run the EVS_DMA example.
#
# Copyright 2012 ARM Limited.
# All rights reserved.
#

./EVS_DMA_ARM1176.x -a DMA.Core=../Image/dma.axf $*
