; Copyright (c) ARM Ltd 2013 All Rights Reserved.
;
; File: init_v8.s - Extra initialisation to disable VFP traps for ARMv8

        REQUIRE8
        PRESERVE8

        AREA ||.text||, CODE, READONLY, ALIGN=2

        IMPORT __main [CODE]

__init_v8
        MSR   CPTR_EL3,xzr  ;  CPTR_EL3.TFP=0 - Disable traps for VFP instructions
        B     __main        ;  Branch to normal entry point

        EXPORT __init_v8 [CODE]

        END
