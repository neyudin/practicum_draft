%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_CHAR BL
    GET_DEC 1, AL
    SUB BL, 'H'
    SUB AL, 8
    IMUL BL
    SHR AL, 1
    PRINT_DEC 1, AL
    xor eax, eax
    ret