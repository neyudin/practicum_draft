%include "io.inc"

section .rodata
    mask_f db "data.in", 0
    mask_r db "r", 0
    mask_u db "%u", 0

section .text
CEXTERN fopen
CEXTERN feof
CEXTERN fscanf
CEXTERN printf
CEXTERN fclose
global CMAIN
CMAIN:
    lea edx, [esp + 8]
    and esp, -16
    push dword[edx - 8]
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    xor edi, edi
    sub esp, 24; 16 * k - 8
    lea esi, [ebp - 4]; &number
    mov dword[esp], mask_f
    mov dword[esp + 4], mask_r
    call fopen
    mov [esp], eax; FILE *eax
    mov dword[esp + 4], mask_u
    mov [esp + 8], esi
    .L1:    call fscanf
            cmp eax, 0
            jle .L2
            inc edi
            .L2:    call feof
                    test eax, eax
                    jnz .END
                    jmp .L1
    .END:    call fclose
             mov dword[esp], mask_u
             mov [esp + 4], edi
             call printf
    xor eax, eax
    leave
    ret