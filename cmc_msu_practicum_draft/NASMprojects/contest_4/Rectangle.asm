%include "io.inc"

section .bss
    coordinates resd 10

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    xor eax, eax
    
    .L1:    GET_DEC 4, [coordinates + 4 * eax]
            inc eax
            cmp eax, 10
            jne .L1
    
    mov eax, [coordinates + 32]; Px
    mov ebx, [coordinates + 36]; Py
    
    mov ecx, [coordinates]; x_min
    cmp ecx, [coordinates + 8]
    cmovg ecx, [coordinates + 8]
    cmp ecx, [coordinates + 16]
    cmovg ecx, [coordinates + 16]
    
    mov edx, [coordinates + 4]; y_min
    cmp edx, [coordinates + 12]
    cmovg edx, [coordinates + 12]
    cmp edx, [coordinates + 20]
    cmovg edx, [coordinates + 20]
    
    mov esi, [coordinates]; x_max
    cmp esi, [coordinates + 8]
    cmovl esi, [coordinates + 8]
    cmp esi, [coordinates + 16]
    cmovl esi, [coordinates + 16]
    
    mov edi, [coordinates + 4]; y_max
    cmp edi, [coordinates + 12]
    cmovl edi, [coordinates + 12]
    cmp edi, [coordinates + 20]
    cmovl edi, [coordinates + 20]
    
    cmp eax, ecx
    jle .1
    cmp eax, esi
    jge .1
    cmp ebx, edx
    jle .1
    cmp ebx, edi
    jge .1
    
    PRINT_STRING "YES"
    jmp .exit
    
    .1:    PRINT_STRING "NO"
    
    .exit:
    xor eax, eax
    ret