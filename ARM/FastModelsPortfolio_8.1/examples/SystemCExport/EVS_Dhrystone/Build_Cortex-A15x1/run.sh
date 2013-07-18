#!/bin/sh
#
# run.sh - Run the EVS_Dhrystone example.
#
# Copyright 2012-2013 ARM Limited.
# All rights reserved.
#

axf=${PVLIB_HOME}/images/dhrystone.axf

if [ ! -e ${axf} ]; then
    echo "ERROR: ${axf}: application not found"
    echo "Did you install the Fast Models TPIP package?"
    exit 1
fi

./EVS_Dhrystone_Cortex-A15x1.x -a ${axf} <<EOF $*
1500000
EOF

