#!/bin/sh
#
# run.sh - Run the EVS_DMADhrystone example.
#
# Copyright 2012 ARM Limited.
# All rights reserved.
#

axf=${PVLIB_HOME}/images/dhrystone.axf

if [ ! -e ${axf} ]; then
    echo "ERROR: ${axf}: application not found"
    echo "Did you install the Fast Models TPIP package?"
    exit 1
fi

./EVS_DMADhrystone_Cortex-R5x1-A15x1.x -a Dhrystone.Core.cpu0=${axf} -a DMA.Core.cpu0=../../EVS_DMA/Image/dma_wfi.axf <<EOF $*
1000000
EOF
