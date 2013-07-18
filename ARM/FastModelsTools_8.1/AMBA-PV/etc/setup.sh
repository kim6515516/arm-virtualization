#!/bin/sh
#
# AMBA-PV: setup.sh - Setup script for AMBA-PV.
#
# Copyright 2009 ARM Limited.
# All rights reserved.
#

# Guard the script against execution - it must be sourced!
echo $0 | egrep 'setup.sh|source_me.sh' > /dev/null
if [ $? -eq 0 ]; then
    echo ""
    echo "ERROR: the setup file must be SOURCED, NOT EXECUTED in a shell."
    echo "Try (for bash)  : source setup.sh"
    echo "Or (eg. for ksh): . setup.sh"
    exit 1
fi

# this line is modified by the ./install.sh script which must be executed once
# before the setup scripts can be sourced
DIR=error
if [ $DIR = "error" ]; then
    echo "Please execute (not source) the file install.sh in the same directory as"
    echo "setup.sh first (this has to be done only once)"
else
    AMBAPV_HOME=$DIR

    # Setup a license if we have one
    if [ -e $AMBAPV_HOME/etc/license.sh ]; then
        . $AMBAPV_HOME/etc/license.sh
    fi
    export AMBAPV_HOME
    echo "Setting AMBAPV_HOME to $AMBAPV_HOME"
fi

