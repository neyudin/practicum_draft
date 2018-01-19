%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, EAX; N M K D X Y
    GET_DEC 4, EBX
    GET_DEC 4, ECX
    GET_DEC 4, EDX
    GET_DEC 4, ESI
    GET_DEC 4, EDI
    MOV EDI, EDX
    MUL EBX
    MUL ECX
    CDQ
    DIV EDI
    NEG EDX
    SHR EDX, 31
    ADD EAX, EDX
    MOV EBX, EAX
    DEC EAX
    CDQ
    MOV EDI, 3
    DIV EDI
    MOV ECX, EDX
    MOV EDI, 2
    MUL EDI
    ADD ECX, EAX
    SUB ESI, 6
    SHR ESI, 31
    MOV EAX, EBX
    MUL ESI
    MOV EBX, EAX
    MOV EAX, ECX
    DEC ESI
    NEG ESI
    MUL ESI
    ADD EAX, EBX
    PRINT_DEC 4, EAX
    xor eax, eax
    ret