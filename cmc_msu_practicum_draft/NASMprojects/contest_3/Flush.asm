%include "io.inc"

section .data
    flush db "SCDH"
    value db "23456789TJQKA"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_UDEC 4, EAX
    DEC EAX
    CDQ
    MOV EBX, 13
    DIV EBX
    PRINT_CHAR [value + EDX]
    PRINT_CHAR [flush + EAX]
    xor eax, eax
    ret