%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, esi
    mov edi, 1
    mov ebx, edi
    .L1:    mov eax, esi
            cdq
            idiv ebx
            cmp eax, esi
            je .L2
            cmp edx, 0
            cmove edi, eax
            je .L3
            .L2:inc ebx
                mov eax, ebx
                imul eax, eax
                cmp eax, esi
                jle .L1
    .L3:
    PRINT_DEC 4, edi
    xor eax, eax
    ret