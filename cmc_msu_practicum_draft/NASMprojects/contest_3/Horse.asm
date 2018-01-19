%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_CHAR EAX; x1
    GET_CHAR ECX; y1 num
    GET_CHAR EBX; space
    GET_CHAR EBX; x2
    GET_CHAR EDX; y2 num
    SUB EAX, EBX; x1 -= x2
    SUB ECX, EDX; y1 -= y2
    MOV EBX, EAX
    MOV EDX, ECX
    SAR EBX, 31
    SAR EDX, 31
    XOR EAX, EBX
    XOR ECX, EDX
    SUB EAX, EBX
    SUB ECX, EDX
    ADD EAX, ECX
    PRINT_DEC 4, EAX
    xor eax, eax
    ret