%include "io.inc"

CEXTERN qsort

section .text

COMPAR:    
           push ebp; я запишу в стек натуральные числа по схеме 3 == 3/1
           mov ebp, esp
           push ebx
           push ecx
           push edx
           push esi
           push edi
           mov eax, [ebp + 8]; 1
           mov ebx, [ebp + 12]; 2
           mov esi, [eax]; числитель 1
           mov edi, [ebx]; числитель 2
           mov ecx, [eax - 4]; знаменатель 1
           mov ebx, [ebx - 4]; знаменатель 2
           mov eax, esi
           xor edx, edx
           div ecx
           push eax; 1 целая 
           push edx; 1 дробная - числитель
           mov eax, edi
           xor edx, edx
           div ebx
           push eax; 2 целая
           push edx; 2 дробная - числитель
           pop edi
           pop edx
           pop esi
           pop eax
           cmp eax, edx
           jb .BELOW
           je .DOUBLE
           .ABOVE:    mov eax, 1
                      jmp .END
           .BELOW:    mov eax, -1
                      jmp .END
           .DOUBLE:    xor edx, edx
                       mov eax, esi
                       mul ebx
                       push eax; low 1
                       push edx; high 1
                       xor edx, edx
                       mov eax, edi
                       mul ecx
                       push eax; low 2
                       push edx; high 2
                       pop ebx
                       pop edx
                       pop eax
                       pop ecx
                       cmp eax, ebx
                       jb .BELOW
                       je .LOW
                       jmp .ABOVE
                       .LOW:    cmp ecx, edx
                                jb .BELOW
                                ja .ABOVE
                                mov eax, [ebp + 8]
                                mov ebx, [ebp + 12]
                                mov eax, [eax]
                                mov ebx, [ebx]
                                cmp eax, ebx
                                jb .BELOW
                                ja .ABOVE
                                xor eax, eax
           .END:    pop edi
                    pop esi
                    pop edx
                    pop ecx
                    pop ebx
                    leave
                    ret

QSORT:    
          push ebp
          mov ebp, esp
          xor eax, eax
          push ebx
          push edi
          mov ebx, [ebp + 8]; *base is going down
          mov ecx, [ebp + 12]; num
          mov edx, [ebp + 16]; size equals 8 bytes
          dec ecx
          mov edi, [ebp + 20]; *compar
          push edi; *compar
          push ecx; n - 1
          push eax; 0
          push ebx; *base
          call QUICK_SORT
          pop ebx
          pop eax
          pop ecx
          pop edi
          pop edi
          pop ebx
          leave
          ret

QUICK_SORT:    
               push ebp
               mov ebp, esp
               push ebx
               push esi
               push edi
               mov ebx, [ebp + 8]; *base
               mov esi, [ebp + 12]; left
               mov edi, [ebp + 16]; right
               mov eax, edi
               add eax, esi
               shr eax, 1
               neg eax; eax
               lea eax, [ebx + 8 * eax]; 4 * eax
               PRINT_UDEC 4, [eax]
               PRINT_CHAR '/'
               PRINT_UDEC 4, [eax - 4]
               NEWLINE
               .L1:    mov ecx, esi; i
                       neg ecx
                       lea ecx, [ebx + 8 * ecx]; !
                       push eax
                       push ecx
                       call dword[ebp + 20]; compar ecx, eax
                       cmp eax, 0
                       pop ecx
                       pop eax
                       jge .BREAK_1
                       cmp esi, [ebp + 16]
                       jge .BREAK_1
                       inc esi
                       jmp .L1
               .BREAK_1:        mov edx, edi; j
                                neg edx
                                lea edx, [ebx + 8 * edx]; !
                                push edx
                                push eax
                                call dword[ebp + 20]; compar eax, edx
                                cmp eax, 0
                                pop eax
                                pop edx
                                jge .BREAK_2
                                cmp edi, [ebp + 12]
                                jle .BREAK_2
                                dec edi
                                jmp .BREAK_1
               .BREAK_2:    cmp esi, edi
                            jg .NEXT; jg
                            mov ecx, esi
                            neg ecx
                            lea ecx, [ebx + 8 * ecx]
                            mov edx, ecx
                            sub edx, 4
                            mov ecx, [ecx]
                            mov edx, [edx]
                            push ecx
                            push edx
                            mov ecx, edi
                            neg ecx
                            lea ecx, [ebx + 8 * ecx]
                            mov edx, ecx
                            sub edx, 4
                            mov ecx, [ecx]
                            mov edx, [edx]
                            push ecx
                            push edx
                            mov ecx, esi
                            neg ecx
                            lea ecx, [ebx + 8 * ecx]
                            mov edx, [esp + 4]
                            mov [ecx], edx
                            sub ecx, 4
                            mov edx, [esp]
                            mov [ecx], edx
                            mov ecx, edi
                            neg ecx
                            lea ecx, [ebx + 8 * ecx]
                            mov edx, [esp + 12]
                            mov [ecx], edx
                            sub ecx, 4
                            mov edx, [esp + 8]
                            mov [ecx], edx
                            pop edx
                            pop ecx
                            pop edx
                            pop ecx
                            inc esi
                            dec edi
               .NEXT:    cmp esi, edi
                         jle .L1; jle
                         mov eax, [ebp + 20]
                         mov ebx, [ebp + 8]
                         mov ecx, [ebp + 12]
                         mov edx, [ebp + 16]
                         cmp edi, ecx
                         jle .L3
                         push eax
                         push edi
                         push ecx
                         push ebx
                         call QUICK_SORT
                         pop ebx
                         pop ecx
                         pop edi
                         pop eax
                         .L3:     cmp edx, esi
                                  jle .END
                                  push eax
                                  push edx
                                  push esi
                                  push ebx
                                  call QUICK_SORT
                                  pop ebx
                                  pop esi
                                  pop edx
                                  pop eax
               .END:    pop edi
                        pop esi
                        pop ebx
                        leave
                        ret
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    push esi
    push edi
    push ebx
    xor ebx, ebx
    xor edi, edi
    .L1:    GET_UDEC 4, esi
            GET_CHAR bl
            push esi
            cmp edi, 0
            cmove edx, esp
            cmp bl, ','
            je .L2; next and push 1
            cmp bl, '.'
            je .L3; end and push 1
            GET_UDEC 4, esi
            push esi
            inc edi
            GET_CHAR bl
            cmp bl, ','
            je .L1
            jmp .L4; end
            .L2:    mov esi, 1
                    push esi
                    inc edi
                    jmp .L1
            .L3:    mov esi, 1
                    push esi
                    inc edi
            .L4:    mov esi, 8
                    ;lea edx, [esp + 4]
                    sub esp, 4
                    lea eax, [esp]
                    and esp, -16
                    mov [esp], eax
                    push COMPAR; *compar
                    push esi; sizeof element
                    push edi; number of elements
                    push edx; *base (pointer of the beginning of array) is going down
                    PRINT_HEX 4, esp
                    NEWLINE
                    call QSORT;we will call QSORT there
                    pop edx
                    pop edi
                    pop esi
                    pop eax
                    mov esp, [esp]
                    add esp, 4
                    inc ebx
                    mov eax, edi
            .L5:    mov ebx, [edx]
                    PRINT_UDEC 4, ebx
                    sub edx, 4
                    mov ebx, [edx]
                    cmp ebx, 1
                    je .L6
                    PRINT_CHAR '/'
                    PRINT_UDEC 4, ebx
                    .L6:    sub edx, 4
                           cmp edi, 1
                           jne .L7
                           PRINT_CHAR '.'
                           jmp .CLEAR_STACK
                           .L7:    PRINT_CHAR ','
                                   dec edi
                                   jmp .L5
           .CLEAR_STACK:    pop ecx
                            pop ecx
                            dec eax
                            cmp eax, 0
                            jne .CLEAR_STACK
    pop ebx
    pop edi
    pop esi
    xor eax, eax
    leave
    ret