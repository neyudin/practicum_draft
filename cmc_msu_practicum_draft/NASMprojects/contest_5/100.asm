%include "io.inc"
DST:    
        push ebp
        mov ebp, esp
        push eax
        mov eax, [ebp + 8]
        push ecx
        .L1:    GET_UDEC 4, ecx
                push ecx
                call DIV3
                pop ecx
                dec eax
                cmp eax, 0
                jne .L1
                pop ecx
                pop eax
                leave
                ret
DIV3:    
         push ebp
         mov ebp, esp
         push eax
         mov eax, [ebp + 8]
         push ebx
         mov ebx, 1
         push ecx
         push edx
         xor ecx, ecx
         xor edx, edx
         .L1:    test eax, ebx
                 jz .L2
                 inc ecx
                 .L2:    shl ebx, 1
                         test eax, ebx
                         jz .L3
                         inc edx
                         .L3:    test ebx, 2147483648
                                 jnz .L4
                                 shl ebx, 1
                                 jmp .L1
                         .L4:    sub ecx, edx
                                 jge .L5
                                 neg ecx
                                 .L5:    cmp ecx, 0
                                         je .YES
                                         sub ecx, 3
                                         cmp ecx, 0
                                         jge .L5
                                         PRINT_STRING "NO"
                                         NEWLINE
                                         jmp .END
                                         .YES:    PRINT_STRING "YES"
                                                  NEWLINE
                                         .END:    pop edx
                                                  pop ecx
                                                  pop ebx
                                                  pop eax
                                                  leave
                                                  ret
section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    push ebp
    mov ebp, esp
    ;write your code here
    GET_UDEC 4, eax
    push eax
    call DST
    pop eax
    xor eax, eax
    leave
    ret