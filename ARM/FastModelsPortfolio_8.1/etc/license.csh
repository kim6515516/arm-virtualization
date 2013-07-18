if ( $?ARMLMD_LICENSE_FILE ) then
    if ( "$ARMLMD_LICENSE_FILE" =~ ?* ) then
        setenv ARMLMD_LICENSE_FILE "/home/sxcheng/Workspace/kvm/license.dat:$ARMLMD_LICENSE_FILE"
    else
        setenv ARMLMD_LICENSE_FILE "/home/sxcheng/Workspace/kvm/license.dat"
    endif
else
    setenv ARMLMD_LICENSE_FILE "/home/sxcheng/Workspace/kvm/license.dat"
endif
