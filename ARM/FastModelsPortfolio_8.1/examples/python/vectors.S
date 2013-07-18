                AREA    ARMex, CODE, READONLY
                ENTRY

; Test program to demonstrate triggering and handling exceptions

Vector_Table
                LDR pc, =Reset_Handler
                LDR pc, =Undefined_Handler
                LDR pc, =SVC_Handler
                LDR pc, =Prefetch_Handler
                LDR pc, =Abort_Handler
                NOP                    ;Reserved vector
                LDR pc, =IRQ_Handler
FIQ_Handler         ; FIQ handler starts here
Abort_Handler
                B Abort_Handler

Prefetch_Handler
        MOV     pc, lr

Reset_Handler
        MOV     r0, #0
        SVC     #0
        DCD     0xF7F0A000
done
                B       done

SVC_Handler
        ORR     r0, r0, #1
        ADR     r4, mem
        LDR     r5, [r4]
        ADD     r5, r5, #1
        STR     r5, [r4]
        MOV     pc, lr

IRQ_Handler
        ORR     r0, r0, #2
        MOV     pc, lr

Undefined_Handler
        ORR     r0, r0, #4
        MOV     pc, lr

mem     DCD     42
        END
                
                

