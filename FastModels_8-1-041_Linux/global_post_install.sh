#!/bin/sh

# In case both packages (Tools (SG, MS & MD) and ModelLib (ML)) have been
# selected during install, this script copies the 2 separate setup scripts into
# a single one during global post install (PostInstallCommand in globals
# section of package description).

# positional parameters to this script:
# pos #1:  1 if SG has been selected (else 0).
# pos #2:  1 if ML     --- " --- 
# pos #3:  path to SG (PACKAGE_DIR)
# pos #4:  path to ML (PACKAGE_DIR)

TL_PACKAGE_DIR="$3"
ML_PACKAGE_DIR="$4"

echo ""

# parameters 1 & 2 = tools + models installed
if [ $1 = "1" -a $2 = "1" ] ; then
    echo "" > $POSTINSTLOG

    echo "-----------------------------------------"
    echo "Source commands from above are for the individual packages only."
    echo "Scripts created:" >> $POSTINSTLOG

    if [ -e "$TL_PACKAGE_DIR/etc/setup.sh" -a -e "$ML_PACKAGE_DIR/etc/setup.sh" ] ; then
        cat "$TL_PACKAGE_DIR/etc/setup.sh" "$ML_PACKAGE_DIR/etc/setup.sh"  > "$TL_PACKAGE_DIR/etc/setup_all.sh"
        ln -s "$TL_PACKAGE_DIR/etc/setup_all.sh" "$TL_PACKAGE_DIR/source_all.sh"

        echo "To set up use . \"$TL_PACKAGE_DIR/source_all.sh\" for sh/ksh"
        echo "To set up use . \"$TL_PACKAGE_DIR/source_all.sh\" for sh/ksh" >> $POSTINSTLOG
    fi

    if [ -e "$TL_PACKAGE_DIR/etc/setup.csh" -a -e "$ML_PACKAGE_DIR/etc/setup.csh" ] ; then
        cat "$TL_PACKAGE_DIR/etc/setup.csh" "$ML_PACKAGE_DIR/etc/setup.csh"  > "$TL_PACKAGE_DIR/etc/setup_all.csh"
        ln -s "$TL_PACKAGE_DIR/etc/setup_all.csh" "$TL_PACKAGE_DIR/source_all.csh"

        echo "To set up use source \"$TL_PACKAGE_DIR/source_all.csh\" for csh"
        echo "To set up use source \"$TL_PACKAGE_DIR/source_all.csh\" for csh" >> $POSTINSTLOG
    fi
fi

exit 0
