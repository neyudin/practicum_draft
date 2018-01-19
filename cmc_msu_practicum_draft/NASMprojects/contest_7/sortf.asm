section .bss
	global compare_counter
	global swap_counter
	compare_counter resq 1
	swap_counter resq 1

section .text
global timestamp
global compare_lg
global compare_gl
global swap

timestamp:    
              rdtsc
              ret

compare_lg:    
               push ebp
               mov ebp, esp
               inc dword[compare_counter]
               adc dword[compare_counter + 4], 0
               xor eax, eax
               mov ecx, [ebp + 12]
               mov edx, [ebp + 8]
               finit
               fld qword[ecx]
               fld qword[edx]
               fucomip
               setb al
               leave
               ret

compare_gl:    
               push ebp
               mov ebp, esp
               inc dword[compare_counter]
               adc dword[compare_counter + 4], 0
               xor eax, eax
               mov ecx, [ebp + 12]
               mov edx, [ebp + 8]
               finit
               fld qword[ecx]
               fld qword[edx]
               fucomip
               seta al
               leave
               ret

            
swap:    
         push ebp
         mov ebp, esp
         inc dword[swap_counter]
         adc dword[swap_counter + 4], 0
         mov ecx, dword[ebp + 8]
         mov edx, dword[ebp + 12]
         finit
         fld qword [edx]
         fld qword [ecx]
         fstp qword[edx]
         fstp qword[ecx]
         leave
         ret