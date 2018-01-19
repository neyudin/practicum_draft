	.file	"main.c"
	.intel_syntax noprefix
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%d\t"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	ebx
	and	esp, -16
	sub	esp, 64
	.cfi_offset 3, -12
	mov	DWORD PTR [esp+32], 0
	mov	DWORD PTR [esp+48], 0
	mov	DWORD PTR [esp+52], 0
	mov	DWORD PTR [esp+56], 0
	mov	DWORD PTR [esp+60], -2147483648
	lea	eax, [esp+16]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:.LC0
	call	__isoc99_scanf
	mov	DWORD PTR [esp+44], 0
	mov	DWORD PTR [esp+36], 0
	mov	DWORD PTR [esp+24], 0
	jmp	.L2
.L13:
	lea	eax, [esp+20]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:.LC0
	call	__isoc99_scanf
	mov	eax, DWORD PTR [esp+20]
	sal	eax, 2
	mov	DWORD PTR [esp], eax
	call	malloc
	mov	DWORD PTR [esp+44], eax
	mov	DWORD PTR [esp+40], 0
	jmp	.L3
.L4:
	mov	eax, DWORD PTR [esp+40]
	lea	edx, [0+eax*4]
	mov	eax, DWORD PTR [esp+44]
	lea	ebx, [edx+eax]
	mov	eax, DWORD PTR [esp+20]
	sal	eax, 2
	mov	DWORD PTR [esp], eax
	call	malloc
	mov	DWORD PTR [ebx], eax
	add	DWORD PTR [esp+40], 1
.L3:
	mov	eax, DWORD PTR [esp+20]
	cmp	DWORD PTR [esp+40], eax
	jl	.L4
	mov	DWORD PTR [esp+28], 0
	jmp	.L5
.L9:
	mov	DWORD PTR [esp+40], 0
	jmp	.L6
.L8:
	mov	eax, DWORD PTR [esp+28]
	lea	edx, [0+eax*4]
	mov	eax, DWORD PTR [esp+44]
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	mov	edx, DWORD PTR [esp+40]
	sal	edx, 2
	add	eax, edx
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:.LC0
	call	__isoc99_scanf
	mov	eax, DWORD PTR [esp+28]
	cmp	eax, DWORD PTR [esp+40]
	jne	.L7
	mov	eax, DWORD PTR [esp+28]
	lea	edx, [0+eax*4]
	mov	eax, DWORD PTR [esp+44]
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	mov	edx, DWORD PTR [esp+40]
	sal	edx, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	cdq
	add	DWORD PTR [esp+48], eax
	adc	DWORD PTR [esp+52], edx
.L7:
	add	DWORD PTR [esp+40], 1
.L6:
	mov	eax, DWORD PTR [esp+20]
	cmp	DWORD PTR [esp+40], eax
	jl	.L8
	add	DWORD PTR [esp+28], 1
.L5:
	mov	eax, DWORD PTR [esp+20]
	cmp	DWORD PTR [esp+28], eax
	jl	.L9
	mov	eax, DWORD PTR [esp+48]
	mov	edx, DWORD PTR [esp+52]
	cmp	edx, DWORD PTR [esp+60]
	jl	.L10
	cmp	edx, DWORD PTR [esp+60]
	jg	.L19
	cmp	eax, DWORD PTR [esp+56]
	jbe	.L10
.L19:
	mov	eax, DWORD PTR [esp+48]
	mov	edx, DWORD PTR [esp+52]
	mov	DWORD PTR [esp+56], eax
	mov	DWORD PTR [esp+60], edx
	mov	eax, DWORD PTR [esp+36]
	mov	DWORD PTR [esp], eax
	call	free
	mov	eax, DWORD PTR [esp+44]
	mov	DWORD PTR [esp+36], eax
	mov	eax, DWORD PTR [esp+20]
	mov	DWORD PTR [esp+32], eax
	jmp	.L12
.L10:
	mov	eax, DWORD PTR [esp+44]
	mov	DWORD PTR [esp], eax
	call	free
.L12:
	mov	DWORD PTR [esp+48], 0
	mov	DWORD PTR [esp+52], 0
	add	DWORD PTR [esp+24], 1
.L2:
	mov	eax, DWORD PTR [esp+16]
	cmp	DWORD PTR [esp+24], eax
	jl	.L13
	mov	DWORD PTR [esp+24], 0
	jmp	.L14
.L17:
	mov	DWORD PTR [esp+28], 0
	jmp	.L15
.L16:
	mov	eax, DWORD PTR [esp+24]
	lea	edx, [0+eax*4]
	mov	eax, DWORD PTR [esp+36]
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	mov	edx, DWORD PTR [esp+28]
	sal	edx, 2
	add	eax, edx
	mov	eax, DWORD PTR [eax]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:.LC1
	call	printf
	add	DWORD PTR [esp+28], 1
.L15:
	mov	eax, DWORD PTR [esp+28]
	cmp	eax, DWORD PTR [esp+32]
	jl	.L16
	mov	DWORD PTR [esp], 10
	call	putchar
	add	DWORD PTR [esp+24], 1
.L14:
	mov	eax, DWORD PTR [esp+24]
	cmp	eax, DWORD PTR [esp+32]
	jl	.L17
	mov	eax, 0
	mov	ebx, DWORD PTR [ebp-4]
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
