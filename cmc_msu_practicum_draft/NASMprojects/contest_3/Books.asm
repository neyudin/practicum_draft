%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, EBX; X at the beginning
    GET_DEC 4, ECX; N buy a year
    GET_DEC 4, EAX; M lose a year
    SUB ECX, EAX; EAX is free
    GET_DEC 4, EAX; Y outlined year
    SUB EAX, 2011
    MUL ECX
    ADD EAX, EBX
    PRINT_DEC 4, EAX
    xor eax, eax
    ret