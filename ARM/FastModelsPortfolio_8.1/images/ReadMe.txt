Images Provided in the Fast Models Package
==========================================

The images directory contains images, provided as-is, to assist
in evaluating and using the Fast Models product. They should be used
in conjunction with the Fast Models User Guide. 

The following images are provided with the Fast Models product: 

Brot
====
Simple bare-metal mandlebrot program using the CLCD. While this
program will run on multi-core platforms, it has not been written
for such platforms and the display output may not be as expected.
This also works for Cortex-R class processors on a VE platform.

brot.axf          - brot program built for ARMv5, which will run on all 
                    ARMv5, ARMv6 and ARMv7 Cortex-R cores
Makefile          - Makefile to build brot.axf (and wfi.axf)       
brot.c            - source for brot

Brot (for VE platforms with processors with an MMU)
===================================================
Because the VE platform has a different memory map an alternate
image is required for VE based models.
Due to memory map differences, this will not work with Cortex-R
class processors. Use the brot.axf image instead.

brot_ve_A.axf     - brot program built for ARMv5, which will run on all 
                    ARMv5, ARMv6 and ARMv7 Cortex-A cores on a VE platform
Makefile_ve       - Makefile to build brot_ve_A.axf
ve.scat           - Linker scatter file used by Makefile_ve

Wfi 
===
Wait-for-interrupt example.

wfi.axf           - wfi program built for ARMv5, which will run on all 
                    ARMv5, ARMv6 and ARMv7 cores
Makefile          - Makefile to build wfi.axf (and brot.axf)       
wfi.s             - source for wfi

Phoneskin
=========
Example program to be used with the phoneskin example platform.

phoneskin.axf     - phoneskin image
phoneskin.c       - phoneskin application program

Images Provided in the Fast Models TPIP Package
===============================================

There are also some images provided in the Fast Models TPIP Package.
These are provided under their respective licenses. When the
TPIP package is installed, the following will be added to the
images directory.

Dhrystone
=========
Pre-built Dhrystone images using semi-hosting. A value must be entered
to specify the number of iterations to be run.

dhrystone.axf     - Dhrystone built for ARMv5 which will run on all 
                    ARMv5, ARMv6 and ARMv7 cores
dhrystone_v7m.axf - Dhrystone built for ARMv7m which will run on 
                    ARM Cortex-M3
source/dhrystone  - sources and makefiles to build the Dhrystone images

Linux
=====
Linux images and source code are provided in TPIP package. For more
details, please read images/LINUX_README.txt

