%include 'io.inc'

                    %define BUF_SIZE 4096

                    section .text

                    f:; 3 arguments
                            push    ebp
                            xor     eax, eax
                            mov     ebp, esp
                            push    esi
                            mov     ecx, dword [ebp+12]; 4624 -> 1 string
                            push    ebx
                            mov     edx, dword [ebp+16]; 4368 -> 2 string
                            mov     ebx, dword [ebp+8]; 4112 delta is 256: what will be written here? answer: this is buffer sample for substitution
                    .L2:
                            mov     byte [ebx+eax], al
                            inc     eax
                            cmp     eax, 255
                            jne     .L2
                            jmp     .L9
                    .L6:
                            mov     al, byte [edx]
                            test    al, al
                            jne     .L4
                            xor     eax, eax
                            jmp     .L5
                    .L4:
                            movzx   esi, byte [ecx]
                            inc     edx
                            inc     ecx
                            mov     byte [ebx+esi], al
                    .L9:
                            cmp     byte [ecx], 0
                            jne     .L6
                            xor     eax, eax
                            cmp     byte [edx], 0
                            sete    al; al = ZF
                    .L5:
                            pop     ebx
                            pop     esi
                            pop     ebp
                            ret

                    p:; 2 arguments
                            push    ebp
                            mov     ebp, esp
                            mov     edx, dword [ebp+8]
                            mov     eax, dword [ebp+12]
                            jmp     .L12
                    .L13:
                            movzx   ecx, byte [eax]
                            mov     cl, byte [edx+ecx]
                            mov     byte [eax], cl
                            inc     eax
                    .L12:
                            cmp     byte [eax], 0
                            jne     .L13
                            pop     ebp
                            ret

                    s:; 2 arguments
                            push    ebp
                            mov     ebp, esp
                            mov     edx, dword [ebp+8]
                            mov     ecx, dword [ebp+12]
                            sub     ecx, 1
                            GET_STRING [edx], ecx
                            mov     byte [edx+ecx], 0; +255 = 256 bytes for string with 0-terminator
                            mov     al, 1
                            pop     ebp
                            ret


                    global CMAIN
                    CMAIN:
                            push    ebp
                            mov     ebp, esp
                            sub     esp, 4880
                            lea     eax, [esp+4624]
                            mov     dword [esp], eax
                            mov     dword [esp+4], 256
                            call    s;scanf('%s", src) what change
                            lea     eax, [esp+4368]
                            mov     [esp], eax
                            mov     dword [esp+4], 256
                            call    s;scanf('%s", dst) what substitute
                            lea     eax, [esp+4112]
                            mov     dword [esp], eax
                            lea     eax, [esp+4624]
                            mov     dword [esp+4], eax
                            lea     eax, [esp+4368]
                            mov     dword [esp+8], eax
                            call    f; buffer with src and dst and check their length for equlity
                            test    eax, eax
                            je      .L1
                            mov     dword [esp+4108], ebx
                            GET_DEC 4, ebx; N
                            GET_STRING [esp+12], BUF_SIZE  ; пропускаем перевод строки после введенного числа
                    .L8:
                            test    ebx, ebx
                            je      .L7
                            lea     edx, [esp+12]
                            mov     dword [esp], edx
                            mov     dword [esp+4], BUF_SIZE
                            call    s; scanf('%s", string)
                            lea     edx, [esp+4112]
                            mov     dword [esp], edx
                            lea     edx, [esp+12]
                            mov     dword [esp+4], edx
                            call    p; substitute
                            PRINT_STRING [esp+12]
                            dec     ebx
                            jmp     .L8
                    .L7:
                            mov     ebx, dword [esp+4108]
                    .L1:
                            xor     eax, eax
                            mov     esp, ebp
                            pop     ebp
                            ret