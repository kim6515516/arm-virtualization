@echo off
rem 
rem run.bat - Run the EVS_DMA example.
rem 
rem Copyright 2012 ARM Limited.
rem All rights reserved.
rem 

.\EVS_DMA_ARM1176.exe -a DMA.Core=..\Image\dma.axf %*

:end
pause

