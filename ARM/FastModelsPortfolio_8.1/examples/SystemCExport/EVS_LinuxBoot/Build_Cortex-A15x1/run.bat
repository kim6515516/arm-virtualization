@echo off
rem 
rem run.bat - Run the EVS_LinuxBoot example.
rem 
rem Copyright 2012 ARM Limited.
rem All rights reserved.
rem 

set axf="%PVLIB_HOME%\images\RTSM_VE_Linux\RTSM_VE_CLI_V7_LPAE\RTSM_VE_CLI_V7_LPAE.axf"
set image="%PVLIB_HOME%\images\RTSM_VE_Linux\filesystems\armv5t_min_VE_V7.image"

if not exist %axf% (
    echo ERROR: %axf%: application not found
    echo "Did you install the Fast Models TPIP package?"
    goto end
)

if not exist %image% (
    echo ERROR: %image%: image not found
    echo "Did you install the Fast Models TPIP package?"
    goto end
)

.\EVS_LinuxBoot_Cortex-A15x1.exe -a LinuxBoot.cluster.*=%axf% -C LinuxBoot.motherboard.mmc.p_mmc_file=%image% -C LinuxBoot.motherboard.vis.cpu_name="- LinuxBoot EVS - Cortex-A15x1" %*

:end
pause

