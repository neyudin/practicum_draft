%include "io.inc"

section .rodata
    mask_u db "%u", 0
    mask_in db "input.txt", 0
    mask_out db "output.txt", 0
    mask_r db "r", 0
    mask_w db "w+", 0
    mask_uu db "%u%u", 0
    mask_space db " ", 0

section .text
CEXTERN fopen
CEXTERN fscanf
CEXTERN malloc
CEXTERN free
CEXTERN fprintf
CEXTERN fclose

INITIALIZER_DLIST:    
                      push ebp
                      mov ebp, esp
                      xor eax, eax
                      push ebx
                      sub esp, 36; 16 * k - 12
                      mov [ebp - 20], esi
                      mov [ebp - 24], edi
                      mov ebx, [ebp + 8]
                      mov [ebp - 8], ebx; N
                      mov ecx, 12
                      mov [ebp - 16], ecx; sizeof(struct node)
                      shl ebx, 2
                      mov [esp], ebx
                      call malloc
                      mov [ebp - 12], eax; **array
                      xor edx, edx
                      .L1:    mov ebx, [ebp - 12]
                              lea esi, [ebx + 4 * edx]
                              mov ebx, [ebp - 16]
                              mov [esp], ebx
                              mov [esp + 4], edx
                              call malloc
                              mov edx, [esp + 4]
                              mov ebx, edx
                              inc ebx
                              mov [eax], ebx; x
                              mov dword[eax + 4], 0; *prev
                              mov dword[eax + 8], 0; *next
                              mov [esi], eax
                              inc edx
                              cmp ebx, [ebp - 8]
                              jl .L1
                      mov ebx, [ebp - 12]
                      mov ecx, ebx
                      add ecx, 4
                      mov ebx, [ebx]
                      mov ecx, [ecx]
                      mov [ebx + 8], ecx
                      mov edx, 1
                      dec dword[ebp - 8]
                      cmp dword[ebp - 8], 0
                      jz .L5
                      .L2:    mov eax, [ebp - 12]
                              lea eax, [eax + 4 * edx]
                              mov ebx, eax
                              sub ebx, 4
                              mov ecx, eax
                              add ecx, 4
                              mov ebx, [ebx]
                              mov eax, [eax]
                              mov ecx, [ecx]
                              mov [eax + 4], ebx
                              mov [eax + 8], ecx
                              inc edx
                              cmp edx, [ebp - 8]
                              jl .L2
                              mov eax, [ebp - 12]
                              lea eax, [eax + 4 * edx]
                              mov ecx, eax
                              sub ecx, 4
                              mov ecx, [ecx]
                              mov eax, [eax]
                              test eax, eax
                              jz .L5
                              mov [eax + 4], ecx
                      .L5:    mov edi, [ebp - 24]
                              mov eax, [ebp - 12]
                              mov esi, [ebp - 20]
                              add esp, 36
                              pop ebx
                              leave
                              ret
                      
MIXER:    
          push ebp
          mov ebp, esp
          push ebx
          mov ebx, [ebp + 12]; N
          cmp ebx, 1
          jle .L1
          push esi
          push edi
          sub esp, 44; 16 * k - 4, use ebp - 16
          mov ebx, [ebp + 16]; M
          xor esi, esi
          lea eax, [ebp - 16]; R
          mov [esp + 12], eax
          lea eax, [ebp - 20]; L
          mov [esp + 8], eax
          mov dword[esp + 4], mask_uu
          mov eax, [ebp + 20]; input
          mov [esp], eax
          call fscanf
          dec dword[ebp - 20]
          dec dword[ebp - 16]
          dec ebx; ebx >= 0
          mov esi, [ebp + 8]; **array
          mov eax, [ebp - 20]
          lea eax, [esi + 4 * eax]
          mov eax, [eax]
          mov edx, eax
          cmp dword[eax + 4], 0
          je .L2
          mov eax, [eax + 4]
          mov ecx, [ebp - 16]
          lea ecx, [esi + 4 * ecx]
          mov ecx, [ecx]
          mov edi, ecx
          mov ecx, [ecx + 8]
          mov [eax + 8], ecx
          cmp ecx, 0
          je .L3
          mov [ecx + 4], eax
          .L3:    mov dword[edx + 4], 0
                  mov edx, esi
                  mov edx, [edx]
                  mov [edi + 8], edx
                  mov eax, [ebp - 16]
                  lea eax, [esi + 4 * eax]
                  mov eax, [eax]
                  mov [edx + 4], eax
          .L2:    mov eax, [ebp - 20]
                  lea eax, [esi + 4 * eax]
                  mov ecx, [ebp - 16]
                  mov [ebp - 24], ecx
                  mov ecx, [ebp - 20]
                  mov [ebp - 28], ecx; is our
                  .L4:    cmp ebx, 0; change root
                          je .L5
                          lea ecx, [ebp - 16];change **array
                          mov [esp + 12], ecx
                          lea ecx, [ebp - 20]
                          mov [esp + 8], ecx
                          mov dword[esp + 4], mask_uu
                          mov ecx, [ebp + 20]
                          mov [esp], ecx
                          call fscanf
                          dec dword[ebp - 20]
                          dec dword[ebp - 16]
                          dec ebx; ebx >= 0
                          mov eax, [ebp - 20]
                          lea eax, [esi + 4 * eax]
                          mov eax, [eax]
                          mov edx, eax
                          cmp dword[eax + 4], 0
                          je .L6
                          mov eax, [eax + 4]
                          mov ecx, [ebp - 16]
                          lea ecx, [esi + 4 * ecx]
                          mov ecx, [ecx]
                          mov edi, ecx
                          mov ecx, [ecx + 8]
                          mov [eax + 8], ecx
                          cmp ecx, 0
                          je .L7
                          mov [ecx + 4], eax
                          .L7:    mov dword[edx + 4], 0
                                  mov edx, [ebp - 28]
                                  lea edx, [esi + 4 * edx]
                                  mov edx, [edx]
                                  mov [edi + 8], edx
                                  mov [edx + 4], edi
                                  
                          .L6:    mov eax, [ebp - 20]
                                  lea eax, [esi + 4 * eax]
                                  mov ecx, [ebp - 16]
                                  mov [ebp - 24], ecx
                                  mov ecx, [ebp - 20]
                                  mov [ebp - 28], ecx
                                  jmp .L4
                  .L5:    add esp, 44
          pop edi
          pop esi
          pop ebx
          leave
          ret
          .L1:    pop ebx
                  mov eax, [ebp + 8]
                  leave
                  ret

global main
main:
    mov ebp, esp; for correct debugging
    lea eax, [esp + 8]
    and esp, -16
    push dword[eax - 8]
    push ebp
    mov ebp, esp; for correct debugging
    sub esp, 40; 16 * k - 8
    ;write your code here
    mov dword[esp + 4], mask_r
    mov dword[esp], mask_in
    call fopen
    mov [ebp - 16], eax; *input
    lea eax, [ebp - 4]
    mov [esp + 12], eax; &M
    lea eax, [ebp - 8]
    mov [esp + 8], eax; &N
    mov dword[esp + 4], mask_uu
    mov eax, [ebp - 16]
    mov [esp], eax
    call fscanf
    mov eax, [ebp - 8]
    mov [esp], eax
    call INITIALIZER_DLIST
    mov [ebp - 12], eax; **array
    mov [esp], eax
    mov eax, [ebp - 8]
    mov [esp + 4], eax
    mov eax, [ebp - 4]
    mov [esp + 8], eax
    mov eax, [ebp - 16]
    mov [esp + 12], eax
    call MIXER; will rewrite dword[ebp - 12]
    mov [ebp - 12], eax
    mov eax, [ebp - 16]
    mov [esp], eax
    call fclose
    mov dword[esp], mask_out
    mov dword[esp + 4], mask_w
    call fopen
    mov [ebp - 16], eax; *output
    mov ebx, [ebp - 12]
    mov ebx, [ebx]
    mov ecx, [ebx]; x
    mov edx, [ebp - 16]
    mov [esp], edx
    mov dword[esp + 4], mask_u
    mov [esp + 8], ecx
    call fprintf
    mov ebx, [ebx + 8]; root->next
    .L1:    test ebx, ebx
            jz .L2
            mov dword[esp + 4], mask_space
            call fprintf
            mov dword[esp + 4], mask_u
            mov ecx, [ebx]
            mov [esp + 8], ecx
            call fprintf
            mov ebx, [ebx + 8]
            jmp .L1
    .L2:    mov eax, [ebp - 16]
            mov [esp], eax
            call fclose
            mov eax, [ebp - 12]
            mov [esp], eax
            ;call free
    xor eax, eax
    leave
    ret