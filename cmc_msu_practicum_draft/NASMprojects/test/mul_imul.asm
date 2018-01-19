%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    mov bx, -1
    mov ax, bx
    cwd
    imul bx
    PRINT_HEX 2, dx
    PRINT_HEX 2, ax
    NEWLINE
    mov ax, bx
    cwd
    mul bx
    PRINT_HEX 2, dx
    PRINT_HEX 2, ax
    xor eax, eax
    ret