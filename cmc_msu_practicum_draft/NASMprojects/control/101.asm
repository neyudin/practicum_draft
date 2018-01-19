%include "io.inc"

section .text
global CMAIN
CMAIN:
    ;write your code here
    GET_UDEC 4, eax
    xor edi, edi
    mov ecx, 4
    mov esi, eax
    .L1:    mov eax, esi
            xor edx, edx
            div ecx
            cmp edx, 1
            jne .L2
            mov esi, eax
            inc edi
            jmp .L1
    .L2:    PRINT_UDEC 4, esi
            PRINT_CHAR ' '
            PRINT_UDEC 4, edi
    xor eax, eax
    ret