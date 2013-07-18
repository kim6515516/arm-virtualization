                AREA    ARMex, CODE, READONLY
                ENTRY

; calculates fibonacci numbers

        ADR     sp, stack
        MOV     r0, #5
        BL      Fib
        MOV     r0, r0
done
                B       done

Fib
        STMIA   sp!, {r1-r2, lr}
        CMP     r0, #1
        BLS     base_case
        MOV     r1, r0
        SUB     r0, r1, #1
        BL      Fib
        MOV     r2, r0
        SUB     r0, r1, #2
        BL      Fib
        ADD     r0, r2, r0
        LDMDB   sp!, {r1-r2, pc}
base_case
        MOV     r0, #1
        LDMDB   sp!, {r1-r2, pc}

stack   SPACE   4096
        END
                
                

