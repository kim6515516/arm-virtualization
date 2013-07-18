@echo off
rem 
rem run.bat - Run the EVS_DMA example.
rem 
rem Copyright 2012 ARM Limited.
rem All rights reserved.
rem 

.\EVS_DMA_Cortex-R5x1.exe -a DMA.Core.cpu0=..\Image\dma.axf %*

:end
pause

