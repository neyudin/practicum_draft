%include "io.inc"

section .bss
    N resd 1
    array resd 10000
    SUM_L resd 1
    SUM_R resd 1
    
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_DEC 4, eax; N
    xor ebx, ebx
    xor ecx, ecx; SUM
    .L1:    GET_DEC 4, [array + 4 * ebx]
            add ecx, [array + 4 * ebx]
            inc ebx
            cmp ebx, eax
            jl .L1
    mov [SUM_R], ecx
    xor ecx, ecx
    xor esi, esi
    mov edi, [SUM_R]
    cmp edi, 0
    jge .L6
    neg edi
    .L6:    
    ;mov ecx, 1; tmp_i
    ;mov esi, ecx; i
    ;mov edx, [array]
    ;sub [SUM_R], edx
    ;add [SUM_L], edx
    ;mov edi, [SUM_R]
    ;sub edi, [SUM_L]
    ;cmp eax, 2
    ;je .END
    ;sub eax, 1
    ;cmp edi, 0
    ;jge .L5
    ;neg edi; delta
    ;.L5:    cmp edi, [SUM_R]
    ;        jl .L2
    ;        mov esi, 0
    ;        mov edi, [SUM_R]
    .L2:    mov ebx, [array + 4 * ecx]
            sub [SUM_R], ebx
            add [SUM_L], ebx
            mov ebx, [SUM_R]
            sub ebx, [SUM_L]
            cmp ebx, 0
            jge .L3
            neg ebx
            .L3:    cmp ebx, edi
                    jge .L4
                    mov esi, ecx
                    inc esi
                    mov edi, ebx
                    .L4:    inc ecx
                            cmp ecx, eax
                            jle .L2
    .END:    PRINT_DEC 4, esi
             xor eax, eax
             leave
             ret