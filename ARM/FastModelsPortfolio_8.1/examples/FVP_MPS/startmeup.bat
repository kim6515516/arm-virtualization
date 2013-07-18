@echo off


echo Make sure that the release version (VC2005) of the model has been build before starting this script!
echo On the BootMonitor command line you may enter:

echo    flash
echo    list images
echo    run selftest_mpb_ESL

pause

"%MAXCORE_HOME%\bin\model_shell.exe" --model Build_Cortex-M3/Win32-Release-VC2005/cadi_system_Win32-Release-VC2005.dll --parameter "coretile.core.semihosting-cmd_line="    --parameter "coretile.fname=mps_flash.bin"     --parameter "coretile.mps_sysregs.user_switches_value=4"     --parameter "coretile.mps_sysregs.memcfg_value=0"     --parameter "mpsvisualisation.disable-visualisation=false"   --parameter "mpsvisualisation.rate_limit-enable=0"


    
