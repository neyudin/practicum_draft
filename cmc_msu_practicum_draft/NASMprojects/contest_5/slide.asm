%include "io.inc"

section .bss
    old_ebp resd 1
    slide resd 1

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    add esp, 4
    mov eax, esp
    xor edx, edx
    mov ebx, 0x10
    div ebx
    sub esp, edx
    mov eax, [ebp + 4]
    mov ebx, [ebp]
    sub esp, 4
    mov [esp], ebp
    mov [esp + 4], eax
    mov ebp, esp
    mov ebx, [old_ebp]
    mov edx, [slide]
    xor eax, eax
    xor ebx, ebx
    xor edx, edx
    
    mov eax, [old_ebp]
    mov dword[ebp + 4], eax
    xor eax, eax
    pop ebp
    leave
    ret