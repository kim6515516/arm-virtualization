#!/bin/bash
#Copyright ARM Ltd 2010

if [ -z $1 ]; then
    echo "Usage: remove_adapter.sh <location of init script>"
    echo "For example: remove_adapter.sh /etc/init.d/FMNetwork"
    exit 1
fi

$(dirname $0)/uninstall.sh $1

