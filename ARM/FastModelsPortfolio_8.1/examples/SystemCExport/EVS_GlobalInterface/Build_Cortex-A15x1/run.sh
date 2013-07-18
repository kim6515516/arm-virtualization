#!/bin/sh
#
# run.sh - Run the EVS_GlobalInterface example.
#
# Copyright 2013 ARM Limited.
# All rights reserved.
#

axf=${PVLIB_HOME}/images/dhrystone.axf

if [ ! -e ${axf} ]; then
    echo "ERROR: ${axf}: application not found"
    echo "Did you install the Fast Models TPIP package?"
    exit 1
fi

./EVS_GlobalInterface_Cortex-A15x1.x -S -a ${axf} <<EOF $*
1000000
1000000
EOF

