@echo off
rem 
rem run.bat - Run the EVS_DualDhrystone example.
rem 
rem Copyright 2012 ARM Limited.
rem All rights reserved.
rem 

set axf="%PVLIB_HOME%\images\dhrystone.axf"

if not exist %axf% (
    echo ERROR: %axf%: application not found
    echo Did you install the Fast Models TPIP package?
    goto end
)

echo 1000000 > run.in.tmp
echo 1000000 >> run.in.tmp
.\EVS_DualDhrystone_Cortex-A15x1-A15x1.exe -a %axf% %* < run.in.tmp
del run.in.tmp 2>nul

:end
pause

