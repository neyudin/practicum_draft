%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_UDEC 4, EAX; N
    GET_UDEC 1, CL; K
    MOV EBX, 1
    SHL EBX, CL        
    DEC EBX
    AND EAX, EBX
    PRINT_UDEC 4, EAX
    xor eax, eax
    ret