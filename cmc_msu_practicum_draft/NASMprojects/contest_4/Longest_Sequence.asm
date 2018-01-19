%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, ecx; N
    GET_DEC 4, eax
    mov ebx, 1
    mov esi, ebx
    mov edi, ebx
    
    cmp ecx, 1
    je .EXIT
    
    .L3:    GET_DEC 4, edx
            cmp edx, eax
            jg .L1
            mov esi, 1
            jmp .L2
            
            .L1:    inc esi
                    cmp esi, edi
                    cmovg edi, esi
                    
            .L2:    inc ebx
                    mov eax, edx
                    cmp ebx, ecx
                    jl .L3
    
    .EXIT:    PRINT_DEC 4, edi
    xor eax, eax
    ret
