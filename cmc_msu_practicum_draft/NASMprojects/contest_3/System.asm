%include "io.inc"

section .bss
    a11 resd 1
    a12 resd 1
    a21 resd 1
    a22 resd 1
    b1 resd 1
    b2 resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    GET_UDEC 4, a11
    GET_UDEC 4, a12
    GET_UDEC 4, a21
    GET_UDEC 4, a22
    GET_UDEC 4, b1
    GET_UDEC 4, b2
    
        MOV EAX, [a11]
        AND EAX, [a12]
        OR EAX, [a22]
        
        MOV ECX, [b1]
        AND ECX, [a22]
        MOV EDX, [b2]
        AND EDX, [a12]
        XOR ECX, EDX
        AND ECX, [a11]
        
        XOR EAX, ECX
        AND EAX, [a21]
        XOR EAX, [a22]
        
        MOV EBX, [b1]
        AND EBX, [a11]
        OR EBX, [b2]
        
        AND EBX, [a21]
        XOR EBX, [b2]
        
        AND EBX, EAX
        
        MOV ECX, [b1]
        AND ECX, [a22]
        MOV EDX, [b2]
        AND EDX, [a12]
        XOR EDX, ECX
        AND EDX, [a21]
        
        MOV ECX, [a22]
        AND ECX, [a21]
        OR ECX, [a12]
        
        XOR EDX, ECX
        AND EDX, [a11]
        XOR EDX, [a12]
        
        MOV EAX, [b2]
        AND EAX, [a21]
        OR EAX, [b1]
        AND EAX, [a11]
        XOR EAX, [b1]
        
        AND EAX, EDX
        
        OR EBX, EAX
        
        MOV EAX, [a12]
        AND EAX, EBX
        XOR EAX, [b1]
        AND EAX, [a11]
        
        MOV ECX, [a22]
        AND ECX, EBX
        XOR ECX, [b2]
        AND ECX, [a21]
        
        OR EAX, ECX
        
    PRINT_UDEC 4, EAX
    PRINT_CHAR ' '
    PRINT_UDEC 4, EBX
    xor eax, eax
    ret