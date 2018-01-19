%include "io.inc"

section .rodata
    mask_in db "./input.txt", 0
    mask_out db "./output.txt", 0
    mask_d db "%d", 0
    mask_space db " ", 0
    mask_r db "r", 0
    mask_w db "w+", 0

section .text
CEXTERN fopen
CEXTERN malloc
CEXTERN fscanf
CEXTERN feof
CEXTERN fprintf
CEXTERN free
CEXTERN fclose

INITIALIZER_DLIST:    
                      push ebp
                      mov ebp, esp
                      sub esp, 40; 16 * k - 8
                      mov dword[ebp - 4], 12; sizeof(int) * 3
                      mov dword[esp + 4], mask_r
                      mov dword[esp], mask_in
                      call fopen
                      mov [ebp - 12], eax; FILE *
                      mov dword[ebp - 16], 0; *prev
                      .L1:    lea ecx, [ebp - 8]
                              mov [esp + 8], ecx; &N
                              mov dword[esp + 4], mask_d
                              mov ecx, [ebp - 12]
                              mov [esp], ecx
                              call fscanf
                              cmp eax, 0
                              jle .L2
                              mov ecx, [ebp - 4]
                              mov [esp], ecx
                              call malloc
                              mov ecx, [ebp - 8]
                              mov [eax], ecx; x
                              mov ecx, [ebp - 16]
                              mov [eax + 4], ecx; *prev
                              cmp ecx, 0
                              je .L3
                              mov [ecx + 8], eax; prev->next
                              .L3:    mov dword[eax + 8], 0; *next
                                      mov [ebp - 16], eax
                                      mov ecx, [ebp - 12]
                                      mov [esp], ecx
                      .L2:    call feof
                              test eax, eax
                              jz .L1
                              call fclose
                              mov eax, [ebp - 16]
                              leave
                              ret

MERGE_SORT:    
               push ebp
               mov ebp, esp
               push ebx
               push esi
               push edi
               sub esp, 44; 16 * k - 4 and use ebp - 16
               mov eax, [ebp + 8]; *DLIST
               mov ebx, [ebp + 12]; N
               mov ecx, ebx
               shr ebx, 1; ebx == N_l
               sub ecx, ebx; ecx == N_r
               mov edx, 1
               mov esi, eax
               .L1:    cmp edx, ebx
                       je .L2
                       mov esi, [esi + 8]
                       inc edx
                       jmp .L1
               .L2:    mov edi, [esi + 8]
                       mov dword[esi + 8], 0
               mov [ebp - 20], eax; *L
               mov [ebp - 16], ebx; N_l
               mov [ebp - 28], edi; *R
               mov [ebp - 24], ecx; N_r
               mov dword[ebp - 32], 0; end result
               mov dword[ebp - 36], 0; start result
               mov dword[edi + 4], 0
               mov [esp], eax
               mov [esp + 4], ebx
               cmp ebx, 1
               jle .L3
               call MERGE_SORT; sort left dlist
               mov [ebp - 20], eax
               .L3:    mov [esp], edi
                       mov ecx, [ebp - 24]
                       mov [esp + 4], ecx
               cmp ecx, 1
               jle .L4
               call MERGE_SORT; sort right dlist
               mov [ebp - 28], eax
               .L4:    mov eax, [ebp - 20]
                       mov ecx, [ebp - 24]
                       mov ebx, [eax]
                       mov ecx, [edi]
                       cmp ebx, ecx
                       jl .L5
                       mov ebx, edi
                       mov [ebp - 32], ebx
                       mov [ebp - 36], ebx
                       mov ecx, ebx
                       mov ebx, [ebx + 8]
                       mov dword[ecx + 8], 0
                       mov [ebp - 28], ebx
                       test ebx, ebx
                       jz .L6
                       mov dword[ebx + 4], 0
                       jmp .L6
                       .L5:    mov ebx, eax
                               mov [ebp - 32], ebx
                               mov [ebp - 36], ebx
                               mov ecx, ebx
                               mov ebx, [ebx + 8]
                               mov dword[ecx + 8], 0
                               mov [ebp - 20], ebx
                               test ebx, ebx
                               jz .L6
                               mov dword[ebx + 4], 0
                       .L6:    mov eax, [ebp - 20]
                               mov edi, [ebp - 28]
                               test eax, edi
                               jz .L7
                               mov ecx, [edi]
                               mov ebx, [eax]
                               cmp ebx, ecx
                               mov ebx, [ebp - 32]
                               jl .L8
                               mov [ebx + 8], edi
                               mov [edi + 4], ebx
                               mov ebx, [ebx + 8]
                               mov edi, [edi + 8]
                               mov dword[ebx + 8], 0
                               test edi, edi
                               jz .L9
                               mov dword[edi + 4], 0
                               .L9:    mov [ebp - 32], ebx
                               jmp .L6
                               .L8:    mov [ebx + 8], eax
                                       mov [eax + 4], ebx
                                       mov ebx, [ebx + 8]
                                       mov eax, [eax + 8]
                                       mov dword[ebx + 8], 0
                                       test eax, eax
                                       jz .L10
                                       mov dword[eax + 4], 0
                                       .L10:    mov [ebp - 32], ebx
                               jmp .L6
                               .L7:    mov ebx, [ebp - 32]
                                       
                                       test eax, eax
                                       jnz .L11
                                       mov [ebx + 8], edi
                                       test edi, edi
                                       jz .L12
                                       mov [edi + 4], ebx
                                       jmp .L12
                                       .L11:    mov [ebx + 8], eax
                                                mov [eax + 4], ebx 
                                       .L12:    mov eax, [ebp - 36]
                                                pop edi
                                                pop esi
                                                pop ebx
                                                leave
                                                ret

global main
main:
    push ebp
    mov ebp, esp
    and esp, -16
    sub esp, 32; 16 * k
    ;write your code here
    call INITIALIZER_DLIST
    xor ecx, ecx
    .L1:    mov edx, eax
            mov eax, [eax + 4]
            inc ecx
            test eax, eax
            jnz .L1
            mov dword[esp], mask_out
    mov [ebp - 8], edx; *DLIST
    mov [ebp - 4], ecx; N
    mov dword[esp + 4], mask_w
    call fopen
    mov [ebp - 12], eax; FILE *
    mov ecx, [ebp - 8]
    mov [esp], ecx
    mov ecx, [ebp - 4]
    mov [esp + 4], ecx
    cmp ecx, 1
    jle .L2
    call MERGE_SORT
    mov [ebp - 8], eax
    .L2:    mov ecx, [ebp - 12]
            mov [esp], ecx
            mov dword[esp + 4], mask_d
            mov ecx, [ebp - 8]
            mov eax, ecx
            mov ecx, [ecx]
            mov [esp + 8], ecx
            call fprintf
            .L3:    mov eax, [eax + 8]
                    test eax, eax
                    jz .L4
                    mov dword[esp + 4], mask_space
                    call fprintf
                    mov dword[esp + 4], mask_d
                    mov ecx, [eax]
                    mov [esp + 8], ecx
                    call fprintf
                    jmp .L3
                    .L4:    mov eax, [ebp - 12]
                            mov [esp], eax
                            call fclose
                            xor eax, eax
                            leave
                            ret
