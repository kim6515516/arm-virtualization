#!/bin/sh 
BASEDIR="$1"
LICENSE="$2"

echo ""
echo "########################################################"
echo "# Fast Models MaxCore"
echo "# - Installer -"
echo "########################################################"
echo ""


#
# guard against all but Installer usage
#
if [ "$DATA_ENV" != "4093567" ]; then
    echo "Please use 'setup' to start the installation"  
    exit 1
fi


#
# check for sed
#
_SED=""
set sed; tool=$1
case "$SED" in
    /*)
    _SED="$SED" # Let the user override the test with a path.
    ;;
    *)
    IFS=":"
    for dir in $PATH; do
        if test -f $dir/$tool; then
            _SED="$dir/$tool"
            break
        fi
    done
    ;;
esac
SED="$_SED"
if test -z "$SED"; then
    echo "" 
    echo "**ERROR**"
    echo "Installer was unable to find the utility \`sed\`."
    echo "If this tool is installed, you can tell the Installer"
    echo "where it is by setting the environment variable SED to point"
    echo "to the executable (i.e. export SED=/usr/local/bin/sed)."
    echo "Otherwise please install this tool and try again."
    echo ""
    exit 1
fi


#
# configure setup scripts
#
MAXCORE_BASE=$BASEDIR


echo "Configuring Setup Scripts"
if sed "s*@MAXCOREINSTALLDIR@*${MAXCORE_BASE}*" "$BASEDIR/etc/setup.csh.template" | sed "s*@MAXCORELICENSEFILE@*${LICENSE}*" > "$BASEDIR/etc/setup.csh" 2>/dev/null; then
    REMOVE_SETUP_CSH="yes"
else
    REMOVE_SETUP_CSH="no"
    echo ""
    echo "**WARNING**"
    echo "Installer is unable to configure the C-Shell setup script:"
    echo "    ${MAXCORE_BASE}/etc/setup.csh.template"
    echo "Please search and replace all instances of @MAXCOREINSTALLDIR@ with ${MAXCORE_BASE}"
    echo "Also replace all instances of @MAXCORELICENSEFILE@ with ${LICENSE}"
    echo "And rename the file to setup.csh"
    echo ""
fi

if sed "s*@MAXCOREINSTALLDIR@*${MAXCORE_BASE}*" "$BASEDIR/etc/setup.sh.template" | sed "s*@MAXCORELICENSEFILE@*${LICENSE}*" > "$BASEDIR/etc/setup.sh" 2>/dev/null; then
    REMOVE_SETUP_SH="yes"
else
    REMOVE_SETUP_SH="no"
    echo ""
    echo "**WARNING**"
    echo "Installer is unable to configure the Bourne setup script:"
    echo "  ${MAXCORE_BASE}/etc/setup.sh.template"
    echo "Please search and replace all instances of @MAXCOREINSTALLDIR@ with ${MAXCORE_BASE}"
    echo "Also replace all instances of @MAXCORELICENSEFILE@ with ${LICENSE}"
    echo "And rename the file to setup.sh"
    echo ""
fi


#
# create source_me links in $BASEDIR
#
if ! cd "$BASEDIR"; then
    echo ""
    echo "**ERROR**"
    echo "Installer is unable to change to the install directory ($BASEDIR)"
    echo "Please make sure the above directory is both readable and writable."
    echo ""
    exit 1
fi
rm -f source_me.csh
ln -s etc/setup.csh source_me.csh
rm -f source_me.sh
ln -s etc/setup.sh source_me.sh
chmod -R a+rX .


#
# remove setup script templates
#
if [ "$REMOVE_SETUP_CSH" = "yes" ]; then
    if ! rm -f etc/setup.csh.template 2>/dev/null; then
        echo ""
        echo "**WARNING**"
        echo "Installer is unable to remove ${MAXCORE_BASE}/etc/setup.csh.template"
        echo "Please remove this file."
        echo ""
    fi
fi

if [ "$REMOVE_SETUP_SH" = "yes" ]; then
    if ! rm -f etc/setup.sh.template 2>/dev/null; then
        echo ""
        echo "**WARNING**"
        echo "Installer is unable to remove ${MAXCORE_BASE}/etc/setup.sh.template"
        echo "Please remove this file."
        echo ""
    fi
fi


#
#  report info for user
#
echo ""
echo "You now have to run the following command in order to setup your"
echo "environment to correctly."
echo "For sh/ksh use     . \"${MAXCORE_BASE}/etc/setup.sh\""
echo "For csh use        source \"${MAXCORE_BASE}/etc/setup.csh\""

echo "You now have to run the following command in order to setup your"  >> $POSTINSTLOG
echo "environment to correctly."                                         >> $POSTINSTLOG
echo "For sh/ksh use     . \"${MAXCORE_BASE}/etc/setup.sh\""             >> $POSTINSTLOG
echo "For csh use        source \"${MAXCORE_BASE}/etc/setup.csh\""       >> $POSTINSTLOG

echo ""
echo "The files MUST be SOURCED, NOT EXECUTED to set up the necessary environment."
echo ""
echo "The above line should be placed in the logins of all users who"
echo "intend to use this software.  This way they will not have to"
echo "run it every time they want to use a tool from this package."
echo ""

if [ x"$LICENSE" != x ] ; then
    TEST_ATSIGN=`echo "$LICENSE" | sed 's/@//'`

    if [ "$TEST_ATSIGN" = "$LICENSE" ]; then
        if [ ! -r "${LICENSE}" ]; then
            echo "NOTE: The license file ${LICENSE} does not exist. "
            echo "If you already have a valid license file, copy it to the above directory. "
            echo "Otherwise please contact ARM to request an evaluation license"
            echo "by sending an email to:"
            echo ""
            echo "support-esl@arm.com"
            echo ""
            echo "Once you receive the license file, you will need to copy it to"
            echo "'${LICENSE}'"
        fi
    fi
else
    echo "No license file was specified."
    echo ""
    echo "Please modify etc/setup.csh and etc/setup.sh by setting the"
    echo "ARMLMD_LICENSE_FILE variable to the location where the license file is."
fi
