%include "io.inc"
DIVISION:    
             push ebp
             mov ebp, esp
             mov ecx, [ebp + 8]
             dec ecx
             push ebx
             push edi
             push esi
             mov ebx, 1
             push ebx
             cmp ecx, 0
             je .SPEC
             .L1:    inc dword[esp]
                     xor edi, edi
             .L6:    xor edx, edx
                     mov eax, [esp]
                     div ebx
                     cmp edx, 0
                     jnz .L2
                     cmp ebx, [esp]
                     jge .L3
                     add edi, ebx
                     .L3:    cmp eax, [esp]
                             jge .L2
                             cmp ebx, eax
                             je .L2
                             add edi, eax
                     .L2:    inc ebx
                             mov esi, ebx
                             imul esi, ebx
                             cmp esi, [esp]
                             jg .L4
                             jmp .L6
                             .L4:    cmp edi, [esp]
                                     jge .L5
                                     dec ecx
                                     .L5:    cmp ecx, 0
                                             mov ebx, 1
                                             jg .L1
                                             jmp .END
             .SPEC:    PRINT_CHAR '1'
                       jmp .1
             .END:    PRINT_UDEC 4, [esp]
             .1:    pop ebx
                    pop esi
                    pop edi
                    pop ebx
                    leave
                    ret
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_UDEC 4, esi
    push esi
    call DIVISION
    pop esi
    xor eax, eax
    leave
    ret