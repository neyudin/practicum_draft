%include "io.inc"

section .rodata
    mask_u db "%u", 0
    mask_d db "%d", 0
    mask_space db " ", 0
    mask_10 db 10, 0

section .text
CEXTERN free
CEXTERN malloc
CEXTERN scanf
CEXTERN printf
SUM:    
        push ebp
        mov ebp, esp
        push eax
        push edx
        mov eax, [ebp + 8]
        mov edx, [ebp + 12]
        add [ebp + 16], eax
        adc [ebp + 20], edx
        pop edx
        pop eax
        leave
        ret
CMPR:    
         push ebp
         mov ebp, esp
         push ecx
         push edx
         xor eax, eax
         mov ecx, [ebp + 16]
         mov edx, [ebp + 20]
         cmp [ebp + 12], edx
         jg .GREATER
         jl .LESS
         cmp [ebp + 8], ecx
         ja .GREATER
         jb .LESS
         jmp .END
         .GREATER:    inc eax
                      jmp .END
         .LESS:    dec eax
         .END:    pop edx
                  pop ecx
                  leave
                  ret
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    lea edx, [esp + 8]
    and esp, -16
    push dword[edx - 8]
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    mov dword[ebp - 16], 0; high tmp trace
    mov dword[ebp - 20], 0; low tmp trace
    mov dword[ebp - 24], 0x80000000; high trace
    mov dword[ebp - 28], 0; low trace
    mov dword[ebp - 32], 0; max trace pointer
    mov dword[ebp - 36], 0; size
    sub esp, 56; 16 * k - 8
    mov dword[esp], mask_u
    lea eax, [ebp - 4]
    mov [esp + 4], eax; &N
    xor edi, edi
    call scanf
    .L1:    lea eax, [ebp - 8]
            mov [esp + 4], eax; &Ni
            mov dword[esp], mask_u
            call scanf
            mov eax, [ebp - 8]
            shl eax, 2
            mov [esp], eax
            call malloc
            mov [ebp - 12], eax; **M_pointers
            xor ebx, ebx
            .L2:    mov esi, [ebp - 12]
                    lea esi, [esi + 4 * ebx]
                    mov esi, [esi]
                    mov eax, [ebp - 8]
                    shl eax, 2
                    mov [esp], eax
                    call malloc
                    mov ecx, [ebp - 12]
                    lea ecx, [ecx + 4 * ebx]
                    mov [ecx], eax
                    inc ebx
                    cmp ebx, [ebp - 8]
                    jl .L2
            mov [esp + 16], edi
            xor ebx, ebx
            .L3:    mov esi, [ebp - 12]
                    lea esi, [esi + 4 * ebx]
                    mov esi, [esi]; *M_pointers
                    xor edi, edi
                    .L4:    lea ecx, [esi + 4 * edi]
                            mov [esp + 4], ecx; &M_pointers[j][k]
                            mov dword[esp], mask_d
                            call scanf
                            cmp ebx, edi
                            jne .L5
                            mov ecx, [esp + 4]
                            mov ecx, [ecx]
                            mov [esp], ecx; sum 64 bit numbers
                            mov dword[esp + 4], 0
                            cmp ecx, 0
                            jg .1
                            mov dword[esp + 4], 0xffffffff
                            .1:    mov ecx, [ebp - 20]
                                   mov [esp + 8], ecx
                                   mov ecx, [ebp - 16]
                                   mov [esp + 12], ecx
                                   call SUM
                                   mov ecx, [esp + 8]
                                   mov [ebp - 20], ecx
                                   mov ecx, [esp + 12]
                                   mov [ebp - 16], ecx
                            .L5:    inc edi
                                    cmp edi, [ebp - 8]
                                    jl .L4
                    inc ebx
                    cmp ebx, [ebp - 8]
                    jl .L3
            mov edi, [esp + 16]
            mov eax, [ebp - 20]
            mov [esp], eax
            mov eax, [ebp - 16]
            mov [esp + 4], eax
            mov eax, [ebp - 28]
            mov [esp + 8], eax
            mov eax, [ebp - 24]
            mov [esp + 12], eax
            cmp edi, 0
            je .3
            call CMPR
            cmp eax, 1
            jne .L6
            .3:    mov eax, [ebp - 32]
                   mov [esp], eax
                   cmp edi, 0
                   je .5
                   call free
                   .5:    mov eax, [ebp - 12]
                          mov [ebp - 32], eax
                          mov eax, [ebp - 8]
                          mov [ebp - 36], eax
                          mov eax, [ebp - 20]
                          mov [ebp - 28], eax
                          mov eax, [ebp - 16]
                          mov [ebp - 24], eax
                          jmp .L7
            .L6:    mov eax, [ebp - 12]
                    mov [esp], eax
                    call free
            .L7:    mov dword[ebp - 20], 0
                    mov dword[ebp - 16], 0
                    inc edi
                    cmp edi, [ebp - 4]
                    jl .L1
    xor edi, edi
    .L8:    mov esi, [ebp - 32]
            lea esi, [esi + 4 * edi]
            mov esi, [esi]
            xor ebx, ebx
            .L9:    lea eax, [esi + 4 * ebx]
                    mov eax, [eax]
                    mov dword[esp], mask_d
                    mov [esp + 4], eax
                    call printf
                    mov dword[esp], mask_space
                    call printf
                    inc ebx
                    cmp ebx, [ebp - 36]
                    jl .L9
            mov dword[esp], mask_10
            call printf
            inc edi
            cmp edi, [ebp - 36]
            jl .L8
    xor eax, eax
    leave
    ret