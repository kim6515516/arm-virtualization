#!/bin/sh
#
# run.sh - Run the EVS_LinuxBoot example.
#
# Copyright 2012 ARM Limited.
# All rights reserved.
#

axf=${PVLIB_HOME}/images/RTSM_VE_Linux/RTSM_VE_CLI_V7_LPAE/RTSM_VE_CLI_V7_LPAE.axf
image=${PVLIB_HOME}/images/RTSM_VE_Linux/filesystems/armv5t_min_VE_V7.image

if [ ! -e ${axf} ]; then
    echo "ERROR: ${axf}: application not found"
    echo "Did you install the Fast Models TPIP package?"
    exit 1
fi

if [ ! -e ${image} ]; then
    echo "ERROR: ${image}: image not found"
    echo "Did you install the Fast Models TPIP package?"
    exit 1
fi

./EVS_LinuxBoot_Cortex-A15x1.x -a "LinuxBoot.cluster.*=${axf}" -C LinuxBoot.motherboard.mmc.p_mmc_file=${image} -C LinuxBoot.motherboard.vis.cpu_name="- LinuxBoot EVS - Cortex-A15x1" $*

