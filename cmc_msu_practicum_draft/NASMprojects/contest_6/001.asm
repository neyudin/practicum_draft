%include "io.inc"

section .rodata
    mask_1 db "%u", 0
    mask_2 db "0x%08X", 10, 0

section .text
CEXTERN scanf
CEXTERN printf
global main
main:
    lea edx, [esp + 8]
    and esp, -16
    push dword[edx - 8]
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    sub esp, 24
    lea edi, [ebp - 4]; &number
    .L1:    mov dword[esp], mask_1
            mov [esp + 4], edi
            call scanf
            cmp eax, 0
            jle .END
            mov dword[esp], mask_2
            mov eax, [edi]
            mov [esp + 4], eax
            call printf
            jmp .L1
    .END:                xor eax, eax
                         leave
                         ret