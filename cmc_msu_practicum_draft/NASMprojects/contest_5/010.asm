%include "io.inc"
HYP:
        push ebp
        mov ebp, esp
        mov ecx, [ebp + 8]
        mov edx, [ebp + 12]
        and edx, edx
        jz .5
        .3:    push ecx
               call CONV
               pop ecx
               add ecx, eax
               dec edx
               jnz .3
               .5:    push ecx
                      call CHECK
                      pop ecx
                      leave
                      ret
CHECK:
          push ebp
          mov ebp, esp
          mov eax, [ebp + 8]
          push ebx
          mov ebx, eax
          push esi
          xor esi, esi
          push edi
          mov edi, 10
          push edx
          xor edx, edx
          .L1:    div edi
                  inc esi
                  xor edx, edx
                  cmp eax, 0
                  jnz .L1
                  mov eax, esi
                  shr esi, 1
                  jnz .L2
                  PRINT_STRING "Yes"
                  NEWLINE
                  PRINT_UDEC 4, ebx
                  jmp .END
                  .L2:    dec eax
                          mov edi, 1
                          xor edx, edx
                          .L3:    imul edi, edi, 10
                                  dec eax
                                  jnz .L3
                                  mov eax, ebx
                                  push ebx
                                  mov ebx, 10
                                  push ecx
                                  push esi
                                  .L4:    xor edx, edx
                                          div edi
                                          push eax
                                          mov eax, edx
                                          xor edx, edx
                                          div ebx
                                          push edx
                                          mov ebx, eax
                                          mov eax, edi
                                          xor edx, edx
                                          mov ecx, 100
                                          div ecx
                                          xor ecx, ecx
                                          xor edx, edx
                                          mov edi, eax
                                          mov eax, ebx
                                          mov ebx, 10
                                          dec dword[esp + 8]
                                          pop esi
                                          pop ecx
                                          cmp ecx, esi
                                          je .L5
                                          jmp .L6
                                          .L5:    mov edx, [esp]
                                                  cmp edx, 0
                                                  jnz .L4
                                                  pop esi
                                                  pop ecx
                                                  PRINT_STRING "Yes"
                                                  NEWLINE
                                                  PRINT_UDEC 4, [esp]
                                                  jmp .END
                                          .L6:    pop esi
                                                  pop ecx
                                                  PRINT_STRING "No"
          .END:
                   pop edx
                   pop edi
                   pop esi
                   pop ebx
                   leave
                   ret
CONV:
         push ebp
         mov ebp, esp
         mov eax, [ebp + 8]
         push edx
         push esi
         push edi
         mov edi, 10
         xor esi, esi
         xor edx, edx
         .L1:    div edi
                 imul esi, esi, 10
                 add esi, edx
                 xor edx, edx
                 cmp eax, 0
                 jnz .L1
                 mov eax, esi
                 pop edi
                 pop esi
                 pop edx
                 leave
                 ret
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    GET_UDEC 4, ebx
    GET_UDEC 4, esi
    push esi
    push ebx
    call HYP
    pop ebx
    pop esi
    xor eax, eax
    leave
    ret