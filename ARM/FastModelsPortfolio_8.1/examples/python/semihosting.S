        AREA    ARMex, CODE, READONLY
        ENTRY

; This program waits until the first byte is sent to the semihosting input,
; then sends "Hello, world!" to the semihosting output channel. It then signals
; that the application is complete using a third semihosting call.

        MOV     r0, #0x07       ; Semihosting call - READC
        MOV     r1, #0
        SVC     0x123456

        MOV     r0, #0x04       ; Semihosting call - WRITE0
        ADR     r1, hello
        SVC     0x123456
        
        MOV     r0, #0x18       ; Semihosting call - angel_SWIreason_ReportException
        ADR     r1, stop        ; ADP_Stopped_ApplicationExit
        SVC     0x123456
end
        B end

hello   DCB    "Hello, world!\n",0
stop    DCD     0x20026
        END                     ; Mark end of file
