if [ "x${MAXCORE_HOME}" = "x" ]
then
   echo "ERROR: MAXCORE_HOME is unset. Please ensure that model shell is installed and that the setup script is sourced"
   exit 1
fi


${MAXCORE_HOME}/bin/model_shell -S ./Linux-Release-GCC-3.4/cadi_system_Linux-Release-GCC-3.4.so
