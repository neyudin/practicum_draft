%include "io.inc"
F:    
      push ebp
      mov ebp, esp
      mov eax, [ebp + 8]
      xor edx, edx
      push ebx
      mov ebx, 3
      div ebx
      push eax
      cmp edx, 1
      jne .L1
      inc ecx
      .L1:    cmp eax, 1
              jne .L2
              inc ecx
              .L2:    cmp eax, 3
                      jl .L3
                      call F
      .L3:    pop eax
              pop ebx
              leave
              ret
section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_UDEC 4, ebx
    xor ecx, ecx
    push ebx
    call F
    pop ebx
    PRINT_UDEC 4, ecx
    xor eax, eax
    leave
    ret