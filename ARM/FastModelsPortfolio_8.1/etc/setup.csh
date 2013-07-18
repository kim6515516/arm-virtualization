#!/bin/csh

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

# this line is modified by the ./install.sh script which must be executed once before the setup scripts can be sourced
set DIR="/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1"

if ( "$DIR" == "error" ) then

echo "please execute (not source) the file install.sh in the same directory as setup.csh first"
echo "(this has to be done only once)"

else

setenv PVLIB_HOME "$DIR"

if ( -e "$PVLIB_HOME/etc/license.csh" ) then
    source "$PVLIB_HOME/etc/license.csh"
endif

setenv PYTHONPATH "${PYTHONPATH}:${PVLIB_HOME}/lib/python2.7"

echo "setting PVLIB_HOME to $PVLIB_HOME"

endif

