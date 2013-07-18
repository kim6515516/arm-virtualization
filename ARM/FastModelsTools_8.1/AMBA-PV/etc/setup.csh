#!/bin/csh
#
# AMBA-PV: setup.csh - Setup script for AMBA-PV.
#
# Copyright 2009 ARM Limited.
# All rights reserved.
#

# Guard the script against execution - it must be sourced!
# when sourcing: on csh $0 is not set, for tcsh it's set to /bin/tcsh
# when executing it's the name of this script
if ( $?0 ) then
    echo $0 | egrep 'setup.csh|source_me.csh' > /dev/null
    if ( $status == 0 ) then
        echo ""
        echo "ERROR: the setup file must be SOURCED, NOT EXECUTED in a shell."
        echo "Try: source setup.csh"
        echo ""
        exit 1
    endif
endif

# this line is modified by the ./install.sh script which must be executed once
# before the setup scripts can be sourced
set DIR=error
if ( $DIR == "error" ) then
    echo "Please execute (not source) the file install.sh in the same directory as"
    echo "setup.csh first (this has to be done only once)"
else
    setenv AMBAPV_HOME $DIR
    if ( -e $AMBAPV_HOME/etc/license.csh ) then
        source $AMBAPV_HOME/etc/license.csh
    endif
    echo "Setting AMBAPV_HOME to $AMBAPV_HOME"
endif

