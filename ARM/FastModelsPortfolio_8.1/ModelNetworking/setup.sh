#!/bin/bash
#Copyright ARM Ltd 2010

# errors handling function
error()
{
    echo -e "$1"
    exit 1
}

print()
{
    echo -e "$1"
}

print_no_newline()
{
    echo -en "$1"
}

yes_no()
{
  print "$1(Yes or No)"
  while true
  do
    read agree
    case "$agree" in
      [yY]|[Yy][Ee][Ss])
        return 0
        break
        ;;
      [nN]|[nN][oO])
        print "Quit the script"
        return 1
        break
        ;;
      *)
        print "Sorry, answer is unrecognized. Please answer yes or no"
        ;;
    esac
  done
}

print_confirmation()
{
  print ""
  print "About to proceed to create TAP devices and MAC bridge. Please check the 
following information is correct:"
  print "Create private tap device for:"
  print "Username\t\tAdapter"

  prefix=$2
  for user in $1
  do
      print "$user\t\t$prefix$user"
  done

  print
  print "This script will also copy the utilities 'brctl' and 'tapctrl' to the"
  print "/usr/sbin directory if not already present, and create an init script at"
  print "'$script.'"

  yes_no "Accept the configuration? "
  conti=$?
  if [ $conti == 1 ]
    then
      exit 0
  fi
}

write_file()
{
  case "$2" in
    "append")
       echo "$3">>"$1"
       ;;
     "new")
       echo "$3">"$1"
       ;;
     *)
       print "write_file: Wrong command"
       ;;
  esac
}

# Deterine where we are running.
dir=`dirname $0`

print "ARM FastModels configuration script.\n"

# check if the script is running as root
if [ $(whoami) != "root" ]
then
    error "ERROR: Please run this script as root."
fi

#check bitness setting
if [ -z $1 ]
then
    error "ERROR: Must give a parameter of either '32' or '64', depending on whether 
target kernel is 32 or 64 bit."
elif [ "$1" == "32" ]
then
    brctl_bin=brctl_32
elif [ "$1" == "64" ]
then
    brctl_bin=brctl_64
else
    error "ERROR: First parameter must be '32' or '64', depending on whether target 
kernel is 32 or 64 bit"
fi

# check presence of TPIP package utilities / distro util.
if [[ ! -x "$dir/tapctrl" ]]; then
    error "ERROR: TAP networking support requires the 'FastModel ThirdParty IP' package
to configure networking. Please install this package and re-run this script. 
Exiting."
fi

# setup path
PATH=.:/sbin:/usr/sbin:/bin:/usr/bin

if [ ! -e /usr/sbin/brctl ]
then
    cp -f "$dir/$brctl_bin" /usr/sbin/brctl
fi

# set default tap device name prefix and
# ask root to specify the tap device name prefix
# otherwise use the default one
print "Please specify the TAP device prefix:(ARM)"
read tapPrefix
if [ -z $tapPrefix ]
then
    tapPrefix=ARM
fi

# Please specify the users who are able to 
# use TAP devices. Each user will be assign
# a private TAP device. usernames are seperated
# by blank space
print "To allow access to the network, each permitted user will have a private
TAP device assigned to them. Please specify a list of users to create
TAP devices for; seperating usernames with a space:"

while true
do
  read users
  if [ -z "$users" ]
  then
      print "Please enter at least one user."
  else
      break
  fi
done


# Ask root to specify the network adapter which connect to network
print "\nThe TAP devices need to be bridged to a network adapter to allow access to
the network. Please enter the adapter to bridge (eth0):"
read nic
if [ -z $nic ]
then
    nic=eth0
fi

# Ask root to specify a name for the network bridge
print "Please enter a name for the network bridge that will be created (armbr0):"
read bridge
if [ -z $bridge ]
then
    bridge=armbr0
fi

# Ask root to specify where they want the init script written
print "Please enter the location where the init script should be written
(/etc/init.d/FMNetwork):"
read script
if [ -z $script ]
then
    script=/etc/init.d/FMNetwork
fi

# Give warning about building bridge 
# Ask for the confirmation
print "WARNING: The script will create a bridge which includes the specified local
network adapter and TAP devices. You may suffer temporary network loss while
the bridge is created. Do you want to proceed? (Yes or No)"

while true
do
  read agree
  case "$agree" in
    [yY]|[Yy][Ee][Ss])
      print_confirmation "$users" $tapPrefix 
      break
      ;;
    [nN]|[nN][oO])
      print "Quit the script"
      exit 0
      ;;
    *)
      print "Sorry, answer is unrecognized. Please answer 'yes' or 'no'"
    ;;
  esac
done

# Nothing is done to the system before this point; apart from installing
# the brctl utility if not present.

# Give permission to normal users
print "Installing"
print_no_newline "- Changing '/dev/net/tun' permissions... "
chmod 666 /dev/net/tun
file=`grep \"tun\" /etc/udev/rules.d/* -l`
count=`grep "\"tun\"" $file | grep 666 -c`
if [ $count == 0  ]
then
    sed '/KERNEL=*\"tun\"/ s/$/\, MODE=\"0666\"/' -i $file
fi
print "done."

# take down ethx
print_no_newline "- Creating bridge '$bridge'... "
ip addr flush "$nic" >/dev/null 2>&1

ifconfig "$nic" 0.0.0.0 promisc >/dev/null 2>&1

# create bridge
brctl addbr $bridge >/dev/null 2>&1

brctl addif $bridge "$nic" >/dev/null 2>&1
print "done."

print_no_newline "- Installing tapctrl to /usr/sbin/... "
cp "$dir/tapctrl" /usr/sbin/
print "done."

# create tap devices and add them into the bridge
for user in $users
do
    print_no_newline "- Creating TAP device for '$user'... "
    tapctrl -n $tapPrefix$user -a create -o $user -t tap >/dev/null 2>&1
    ifconfig $tapPrefix$user 0.0.0.0 promisc >/dev/null 2>&1
    brctl addif $bridge $tapPrefix$user >/dev/null 2>&1
    print "done."
done

ifconfig $bridge 0.0.0.0 promisc

ip link set $bridge up
# renew the DHCP address
killall -e dhclient >/dev/null 2>&1
# wait process to finish
sleep 1s
dhclient $bridge >/dev/null 2>&1
ip addr flush $nic

print_no_newline "- Generating init script... "

if [ -e "$script" ]
  then
    write_file "$script" "new" "#! /bin/sh"
else
    touch "$script"
    write_file "$script" "append" "#! /bin/sh"
fi

lsb_header="$dir/lsb.header"
cat "$lsb_header" >>$script

write_file "$script" "append" "# source function library"
write_file "$script" "append" "if [ -e /etc/rc.d/init.d/functions ];then"
write_file "$script" "append" "    source /etc/rc.d/init.d/functions"
write_file "$script" "append" "elif [ -e /lib/lsb/init-functions ];then"
write_file "$script" "append" "    source /lib/lsb/init-functions"
write_file "$script" "append" "else"
write_file "$script" "append" "    echo 'Unable to find lsb functions'"
write_file "$script" "append" "fi"

write_file "$script" "append" "PATH=.:/sbin:/usr/sbin:/bin:/usr/bin"
write_file "$script" "append" "USERS=\"$users\""
write_file "$script" "append" "NIC=$nic"
write_file "$script" "append" "PREFIX=$tapPrefix"
write_file "$script" "append" "BRIDGE=$bridge"


write_file "$script" "append" "start()"
write_file "$script" "append" "{"
write_file "$script" "append" "    # take down ethx"
write_file "$script" "append" "    ip addr flush \$NIC"
write_file "$script" "append" "    ifconfig \$NIC 0.0.0.0 promisc"
write_file "$script" "append" "    ifdown \$NIC"
write_file "$script" "append" "    # create bridge"
write_file "$script" "append" "    brctl addbr \$BRIDGE"
write_file "$script" "append" "    brctl addif \$BRIDGE \$NIC"
write_file "$script" "append" "    # create tap devices and add them into the bridge"
write_file "$script" "append" "    for user in \$USERS"
write_file "$script" "append" "    do"
write_file "$script" "append" "       tapctrl -n \$PREFIX\$user -a create -o \$user -t tap"
write_file "$script" "append" "       ifconfig \$PREFIX\$user 0.0.0.0 promisc"
write_file "$script" "append" "       brctl addif \$BRIDGE \$PREFIX\$user"
write_file "$script" "append" "    done"
write_file "$script" "append" "    ifconfig \$NIC up"
write_file "$script" "append" "    ifconfig \$BRIDGE 0.0.0.0 promisc"
write_file "$script" "append" "    ip link set \$BRIDGE up"
write_file "$script" "append" "    killall -e dhclient"
write_file "$script" "append" "    # wait process to finish"
write_file "$script" "append" "    sleep 1s"
write_file "$script" "append" "    dhclient \$BRIDGE"
write_file "$script" "append" "    ip addr flush \$NIC"
write_file "$script" "append" "    ip addr show"
write_file "$script" "append" "}"

write_file "$script" "append" "stop()"
write_file "$script" "append" "{"
write_file "$script" "append" "   # take down the bridge"
write_file "$script" "append" "   ip addr flush \$BRIDGE"
write_file "$script" "append" ""
write_file "$script" "append" "   # remove the interfaces from the bridge"
write_file "$script" "append" "   brctl delif \$BRIDGE \$NIC"
write_file "$script" "append" ""
write_file "$script" "append" "   # unset promiscous mode"
write_file "$script" "append" "   ifconfig \$NIC 0.0.0.0 promisc"
write_file "$script" "append" ""
write_file "$script" "append" "   for user in \$USERS"
write_file "$script" "append" "   do"
write_file "$script" "append" "      brctl delif \$BRIDGE \$PREFIX\$user"
write_file "$script" "append" "      tapctrl -n \$PREFIX\$user -a delete -o \$user -t tap"
write_file "$script" "append" "   done"
write_file "$script" "append" "   ip link set \$BRIDGE down"
write_file "$script" "append" "   # delete the bridge"
write_file "$script" "append" "   brctl delbr \$BRIDGE"
write_file "$script" "append" ""
write_file "$script" "append" "   # bring up the network"
write_file "$script" "append" "   ip link set \$NIC up"
write_file "$script" "append" "   if [ -e /etc/init.d/network ]; then"
write_file "$script" "append" "       /etc/init.d/network restart"
write_file "$script" "append" "   elif [ -e /etc/init.d/network-manager ]; then"
write_file "$script" "append" "       /etc/init.d/network-manager restart"
write_file "$script" "append" "   else"
write_file "$script" "append" "       echo 'Unable to restart network, please do so manually'"
write_file "$script" "append" "   fi"
write_file "$script" "append" "   ip addr show"
write_file "$script" "append" "}"
write_file "$script" "append" "RETVAL=0"
write_file "$script" "append" "case \"\$1\" in"
write_file "$script" "append" "    start)"
write_file "$script" "append" "           start"
write_file "$script" "append" "           ;;"
write_file "$script" "append" "    stop)"
write_file "$script" "append" "           stop"
write_file "$script" "append" "           ;;"
write_file "$script" "append" "    restart)"
write_file "$script" "append" "           stop"
write_file "$script" "append" "           start"
write_file "$script" "append" "           ;;"
write_file "$script" "append" "    *)"
write_file "$script" "append" "           echo -e \"Usage: \$0 {start|stop|restart}\""
write_file "$script" "append" "           RETVAL=1"
write_file "$script" "append" "esac"
write_file "$script" "append" ""
write_file "$script" "append" "exit \$RETVAL"

write_file "$script" "append" "# Script End"
chmod 744 "$script"

print "done."

scriptname=`basename $script`
print "Info: init script created at '$script'.
You can create symlinks to this script in appropriate locations for your
system's runlevels. For example, on Red Hat Enterprise Linux 5 you might
create links of the form:"
echo "ln -s $script /etc/rc.d/rc3.d/S99$scriptname"
echo "ln -s $script /etc/rc.d/rc4.d/S99$scriptname"
echo "ln -s $script /etc/rc.d/rc5.d/S99$scriptname"
echo ""


print "Script finished. Thanks for using Fast Models. " 

# End of the script
