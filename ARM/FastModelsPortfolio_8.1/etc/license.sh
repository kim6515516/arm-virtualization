if [ -z $ARMLMD_LICENSE_FILE ]; then
    export ARMLMD_LICENSE_FILE="/home/sxcheng/Workspace/kvm/license.dat"
else
    export ARMLMD_LICENSE_FILE="/home/sxcheng/Workspace/kvm/license.dat:$ARMLMD_LICENSE_FILE"
fi
