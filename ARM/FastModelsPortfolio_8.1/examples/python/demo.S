        AREA    ARMex, CODE, READONLY
        ENTRY

; Simple demo image, sets r0 to 20, then subtracts 1 until it reaches 0

        MOV     r0, #20         ; set up initial values
        MOV     r1, #1
loop
        SUB     r0, r1          ; subtract r1 from r0 until r0 == 0
        CMP     r0, #0
        BNE     loop
end
        B end

        END                     ; Mark end of file
