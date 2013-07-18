#!/bin/sh

# Call uninstaller under Linux
SAVE=`pwd`
cd /tmp
cp $SAVE/../.inst/setup.bin .
cp $SAVE/../.inst/inst_dilog .
exec /bin/sh -c "./setup.bin --uiinf ./inst_dilog ; rm -f ./setup.bin ./inst_dilog"

