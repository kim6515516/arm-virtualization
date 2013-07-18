#!/bin/bash
#Copyright ARM Ltd 2010

print()
{
    echo -e "$1"
}

if [ -z $1 ]; then
    print "Usage: $0 <location of init script>"
    exit 1
fi
script=$1

# check if the script is running as root
if [ $(whoami) != "root" ]
then
    print "Please run this script as root"
    exit 1
fi

print "Start uninstallation process..."
print "Stop the FM network..."
$script stop
if [ $? -ne 0 ]; then
    print "Error stopping network, abandoning uninstallation."
    print "No changes have been made to the system."
    exit 1
fi
print "FM network stopped"

print "Remove installed files"
rm -f /usr/sbin/tapctrl
rm -f $script
print "Uninstallation succeeded"
print "You should now remove any links that you created to $script"
print "If it was installed by this product and is not being used"
print "for any other purpose, you may wish to remove /usr/sbin/brctl"
