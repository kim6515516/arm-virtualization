#!/bin/sh
#
# AMBA-PV: install.sh - Install script for AMBA-PV.
#
# Copyright 2009, 2011 ARM Limited.
# All rights reserved.
#

THIS=$0
echo $THIS | grep '^/' > /dev/null
if [ $? -ne 0 ]; then
    THIS=`pwd`/$THIS
fi

DIR=`dirname $THIS`
HDIR=`dirname $DIR`

echo $DIR | grep 'etc/[.]$' > /dev/null
if [ $? -eq 0 ]; then
    DIR=`dirname $DIR`
    HDIR=`dirname $HDIR`
fi

sed 's!^DIR=.*$!DIR='"$HDIR"'!g' $DIR/setup.sh > $DIR/setup.sh.tmp
rm -f $DIR/setup.sh
mv $DIR/setup.sh.tmp $DIR/setup.sh

sed 's!^set DIR=.*$!set DIR='"$HDIR"'!g' $DIR/setup.csh > $DIR/setup.csh.tmp
rm -f $DIR/setup.csh
mv $DIR/setup.csh.tmp $DIR/setup.csh

# If we were given an argument then that was a license path and we need to do
# something with it
if [ "$1" != "" ]; then

    # If it was a file then copy it otherwise just output shell which will get
    # run when the setup script is run.
    if [ -f $1 ]; then
        cp $1 $DIR
    fi
    echo $1
    echo 'if ( $?LM_LICENSE_FILE ) then'                        >  $DIR/license.csh
    echo '    if ( "$LM_LICENSE_FILE" =~ ?* ) then'             >> $DIR/license.csh
    echo "        setenv LM_LICENSE_FILE $1:\$LM_LICENSE_FILE"  >> $DIR/license.csh
    echo '    else'                                             >> $DIR/license.csh
    echo "        setenv LM_LICENSE_FILE $1"                    >> $DIR/license.csh
    echo '    endif'                                            >> $DIR/license.csh
    echo 'else'                                                 >> $DIR/license.csh
    echo "    setenv LM_LICENSE_FILE $1"                        >> $DIR/license.csh
    echo 'endif'                                                >> $DIR/license.csh
    echo 'if [ -z $LM_LICENSE_FILE ]; then'                     >  $DIR/license.sh
    echo "    export LM_LICENSE_FILE=$1"                        >> $DIR/license.sh
    echo 'else'                                                 >> $DIR/license.sh
    echo "    export LM_LICENSE_FILE=$1:\$LM_LICENSE_FILE"      >> $DIR/license.sh
    echo 'fi'                                                   >> $DIR/license.sh
fi

echo ""
echo "You now have to run the following command in order to setup your"
echo "environment for AMBA-PV Extentions to OSCI TLM 2.0."
echo "For sh/ksh use     . ${DIR}/setup.sh"
echo "For csh use        source ${DIR}/setup.csh"
echo "You now have to run the following command in order to setup your"  >> $POSTINSTLOG
echo "environment for AMBA-PV Extentions to OSCI TLM 2.0."              >> $POSTINSTLOG
echo "For sh/ksh use     . ${DIR}/setup.sh"                              >> $POSTINSTLOG
echo "For csh use        source ${DIR}/setup.csh"                        >> $POSTINSTLOG
echo ""
echo "The files MUST be SOURCED, NOT EXECUTED to set up the necessary"
echo "environment."
echo ""
echo "The above line should be placed in the logins of all users who"
echo "intend to use this software.  This way they will not have to"
echo "run it every time they want to use a tool from this package."
echo ""
