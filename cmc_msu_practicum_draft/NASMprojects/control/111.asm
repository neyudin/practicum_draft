%include "io.inc"

section .bss
    string resb 23
    buffer resb 256
    
section .text

CHECK:    
          push ebp
          mov ebp, esp
          push ebx
          mov ebx, [ebp + 8]
          xor eax, eax
          xor ecx, ecx
          xor edx, edx
          .L1:    mov cl, byte[ebx + eax]
                  inc byte[buffer + ecx]
                  cmp cl, '.'
                  je .L2
                  inc eax
                  jmp .L1
          .L2:    mov eax, 1
                  xor ecx, ecx
          .L3:    cmp byte[buffer + ecx], 1
                  cmova eax, edx
                  inc ecx
                  cmp ecx, 255
                  jbe .L3
          pop ebx
          leave
          ret

global CMAIN
CMAIN:
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    push ebx
    GET_STRING string, 23
    mov ebx, string
    push ebx
    call CHECK
    pop ebx
    pop ebx
    test eax, eax
    jnz .L3
    PRINT_STRING"NO"
    jmp .END
    .L3:     PRINT_STRING"YES"
    .END:    xor eax, eax
             leave
             ret