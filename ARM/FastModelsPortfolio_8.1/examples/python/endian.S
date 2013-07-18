        AREA    ARMex, CODE, READONLY
        ENTRY

; This image toggles the endianness of the procesor every two steps

start
        SETEND      BE
        NOP
        SETEND      LE
        B start

        END
