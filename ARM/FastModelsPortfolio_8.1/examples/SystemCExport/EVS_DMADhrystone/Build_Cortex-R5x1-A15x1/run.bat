@echo off
rem 
rem run.bat - Run the EVS_DMADhrystone example.
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

echo 1000000 | .\EVS_DMADhrystone_Cortex-R5x1-A15x1.exe -a Dhrystone.Core.cpu0=%axf% -a DMA.Core.cpu0=..\..\EVS_DMA\Image\dma_wfi.axf %*

:end
pause

