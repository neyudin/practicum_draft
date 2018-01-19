%include "io.inc"

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

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    ;write your code here
    GET_UDEC 4, eax
    GET_CHAR bl
    GET_UDEC 4, ecx
    GET_CHAR bl
    GET_UDEC 4, edx
    GET_CHAR bl
    GET_UDEC 4, esi
    GET_CHAR bl
    push edx
    push esi
    push eax
    push ecx
    push ebx
    mov ebx, esp
    add ebx, 16
    push ebx
    sub ebx, 8
    push ebx
    call COMPAR
    pop ebx
    pop ebx
    PRINT_DEC 4, eax
    pop ebx
    pop ecx
    pop eax
    pop esi
    pop edx
    xor eax, eax
    leave
    ret