%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_DEC 4, esi; N
    mov eax, -2147483648
    mov ebx, eax
    mov ecx, ebx
    xor edi, edi
    
    .L5:    GET_DEC 4, edx
            cmp edx, eax
            jge .L1
            cmp edx, ebx
            jge .L2
            cmp edx, ecx
            jge .L3
            jmp .L4
    
            .L1:    mov ecx, ebx
                    mov ebx, eax
                    mov eax, edx
                    jmp .L4
    
            .L2:    mov ecx, ebx
                    mov ebx, edx
                    jmp .L4
    
            .L3:    mov ecx, edx
    
            .L4:    inc edi
                    cmp edi, esi
                    jne .L5
    
    PRINT_DEC 4, eax
    PRINT_CHAR ' '
    PRINT_DEC 4, ebx
    PRINT_CHAR ' '
    PRINT_DEC 4, ecx
    PRINT_CHAR ' '
    
    xor eax, eax
    ret