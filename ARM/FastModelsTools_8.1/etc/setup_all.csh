#!/bin/csh

# Guard the script against execution - it must be sourced!

# when sourcing: on csh $0 is not set, for tcsh it's set to /bin/tcsh
# when executing it's the name of this script

if ( $?0 ) then
    echo $0 | egrep 'setup.csh|source_me.csh|source_all.csh' > /dev/null
    if ( $status == 0 ) then
    echo ""
    echo "ERROR: the setup file must be SOURCED, NOT EXECUTED in a shell."
    echo "Try: source setup.csh"
    echo ""
    exit 1
    endif
endif

# Settings for MaxCore
setenv MAXCORE_HOME "/home/sxcheng/Workspace/kvm/ARM/FastModelsTools_8.1"
setenv ARMLMD_LICENSE_FILE "/home/sxcheng/Workspace/kvm/license.dat"
if ( ! $?MXSETUP_QUIET ) then
    echo "Setting MAXCORE_HOME to point to $MAXCORE_HOME"
    echo ""
    echo "Setting ARMLMD_LICENSE_FILE to include $ARMLMD_LICENSE_FILE"
endif

# Legacy environment settings for MaxView
setenv MAXVIEW_HOME         "$MAXCORE_HOME"

# LD_LIBRARY_PATH
if ( $?LD_LIBRARY_PATH ) then
    setenv LD_LIBRARY_PATH "${MAXCORE_HOME}/lib:${LD_LIBRARY_PATH}"
else
    setenv LD_LIBRARY_PATH "${MAXCORE_HOME}/lib"
endif

# PATH
if ( $?PATH ) then
    setenv PATH "${MAXCORE_HOME}/bin:${PATH}"
else
    setenv PATH "${MAXCORE_HOME}/bin"
endif

# TPIP package if installed
if ( -f "${MAXCORE_HOME}/OSCI/etc/setup.csh" ) then
    source "${MAXCORE_HOME}/OSCI/etc/setup.csh"
endif

# Finished
if ( ! $?MXSETUP_QUIET ) then
    echo ""
    echo "MaxCore setup completed."
endif
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

