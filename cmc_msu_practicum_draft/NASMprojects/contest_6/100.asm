%include "io.inc"

section .text
global main
main:
    lea eax, [esp + 8]
    and esp, -16
    push dword[eax - 8]
    push ebp
    mov ebp, esp; for correct debugging
    
    ;write your code here
    xor eax, eax
    leave
    ret