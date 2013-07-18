@echo off
rem 
rem run.bat - Run the EVS_bigLITTLE example.
rem 
rem Copyright 2012 ARM Limited.
rem All rights reserved.
rem 

set axf="%PVLIB_HOME%\images\RTSM_VE_Linux\RTSM_VE_CLI_V7_LPAE\RTSM_VE_CLI_V7_LPAE.axf"
set image="%PVLIB_HOME%\images\RTSM_VE_Linux\filesystems\armv5t_min_VE_V7.image"

if not exist %axf% (
    echo ERROR: %axf%: application not found
    echo Did you install the Fast Models TPIP package?
    goto end
)

if not exist %image% (
    echo ERROR: %image%: image not found
    echo Did you install the Fast Models TPIP package?
    goto end
)

.\EVS_bigLITTLE_Cortex-A15x1-A7x1_MMU400_DMA330.exe -a %axf% -C bigLITTLE.motherboard.mmc.p_mmc_file=%image% -C bigLITTLE.motherboard.vis.cpu_name="- bigLITTLE EVS - Cortex-A15x1-A7x1_MMU400_DMA330" %*

:end
pause

