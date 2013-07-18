@echo off
rem 
rem run.bat - Run the EVS_DMA example.
rem 
rem Copyright 2012 ARM Limited.
rem All rights reserved.
rem 

.\EVS_DMA_Cortex-M4.exe -a DMA.Core=..\Image\dma_v7m.axf %*

:end
pause

