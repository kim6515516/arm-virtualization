#!/bin/sh

# Guard the script against execution - it must be sourced!
echo $0 | egrep 'setup.sh|source_me.sh' > /dev/null
if [ $? -eq 0 ]; then
echo ""
echo "ERROR: the setup file must be SOURCED, NOT EXECUTED in a shell."
echo "Try (for bash)  : source setup.sh"
echo "Or (eg. for ksh): . setup.sh"
exit 1
fi

# this line is modified by the ./install.sh script which must be executed once before the setup scripts can be sourced
DIR="/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1"

if [ "$DIR" = "error" ]; then

echo "please execute (not source) the file install.sh in the same directory as setup.sh first"
echo "(this has to be done only once)"

else

PVLIB_HOME="$DIR"

# Setup a license if we have one
if [ -e "$PVLIB_HOME/etc/license.sh" ]; then
    . "$PVLIB_HOME/etc/license.sh"
fi

export PVLIB_HOME

export PYTHONPATH=$PYTHONPATH:$PVLIB_HOME/lib/python2.7

echo "setting PVLIB_HOME to $PVLIB_HOME"

fi

