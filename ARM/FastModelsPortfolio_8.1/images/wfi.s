; Copyright (c) ARM Ltd 2005, All Rights Reserved.
; File: wfi.s - Wait For Interrupts
;
; Cause a core to spin, executing WFI (Wait For Interrupt) instructions.
; In a dual core model, this stops one core from taking lots of simulation
; time when it has nothing to run.

        CODE32

        AREA ||.text||, CODE, READONLY

main PROC
    ENTRY
        MCR p15, 0, r0, c7, c0, 4   ; WFI
        B main
        ENDP


        END
