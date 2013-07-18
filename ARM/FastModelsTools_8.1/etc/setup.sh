#!/bin/sh

# Guard the script against execution - it must be sourced!
echo $0 | egrep 'setup.sh|source_me.sh|source_all.sh' > /dev/null
if [ $? -eq 0 ]; then
    echo ""
    echo "ERROR: the setup file must be SOURCED, NOT EXECUTED in a shell."
    echo "Try (for bash)  : source setup.sh"
    echo "Or (eg. for ksh): . setup.sh"
    exit 1
fi

# Settings for MaxCore
MAXCORE_HOME="/home/sxcheng/Workspace/kvm/ARM/FastModelsTools_8.1"
export MAXCORE_HOME
ARMLMD_LICENSE_FILE="/home/sxcheng/Workspace/kvm/license.dat"
export ARMLMD_LICENSE_FILE
if [ -z "${MXSETUP_QUIET}" ]; then
    echo "Setting MAXCORE_HOME to point to $MAXCORE_HOME"
    echo ""
    echo "Setting ARMLMD_LICENSE_FILE to include $ARMLMD_LICENSE_FILE"
fi


# Legacy environment settings for MaxView
MAXVIEW_HOME="$MAXCORE_HOME"
export MAXVIEW_HOME


# LD_LIBRARY_PATH
if test -z "${LD_LIBRARY_PATH}"; then
    LD_LIBRARY_PATH="${MAXCORE_HOME}/lib"
else
    LD_LIBRARY_PATH="${MAXCORE_HOME}/lib:${LD_LIBRARY_PATH}"
fi
export LD_LIBRARY_PATH

# PATH
if test -z "${PATH}"; then
    PATH="${MAXCORE_HOME}/bin"
else
    PATH="${MAXCORE_HOME}/bin:${PATH}"
fi
export PATH

# TPIP package if installed
if test -f "${MAXCORE_HOME}/OSCI/etc/setup.sh"; then
    source "${MAXCORE_HOME}/OSCI/etc/setup.sh"
fi

# Finished
if [ -z "${MXSETUP_QUIET}" ]; then
    echo ""
    echo "MaxCore setup completed."
fi
