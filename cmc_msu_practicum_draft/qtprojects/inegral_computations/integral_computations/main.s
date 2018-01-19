	.file	"main.c"
	.globl	EPS1_9
	.data
	.align 16
	.type	EPS1_9, @object
	.size	EPS1_9, 16
EPS1_9:
	.long	917809152
	.long	2305843009
	.long	16353
	.long	0
	.globl	EPS1_6
	.align 16
	.type	EPS1_6, @object
	.size	EPS1_6, 16
EPS1_6:
	.long	2943117312
	.long	2251799813
	.long	16363
	.long	0
	.globl	EPS2_9
	.align 16
	.type	EPS2_9, @object
	.size	EPS2_9, 16
EPS2_9:
	.long	917809152
	.long	2305843009
	.long	16353
	.long	0
	.globl	EPS2_6
	.align 16
	.type	EPS2_6, @object
	.size	EPS2_6, 16
EPS2_6:
	.long	2943117312
	.long	2251799813
	.long	16363
	.long	0
	.text
	.globl	f1
	.type	f1, @function
f1:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	call	exp
	movsd	.LC0(%rip), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	f1, .-f1
	.globl	f2
	.type	f2, @function
f2:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -8(%rbp)
	movsd	.LC1(%rip), %xmm0
	divsd	-8(%rbp), %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	f2, .-f2
	.globl	f3
	.type	f3, @function
f3:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm1
	movsd	.LC2(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	.LC3(%rip), %xmm1
	mulsd	%xmm1, %xmm0
	movsd	.LC4(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	f3, .-f3
	.globl	root_finder
	.type	root_finder, @function
root_finder:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movsd	%xmm0, -56(%rbp)
	movsd	%xmm1, -64(%rbp)
	movsd	%xmm2, -72(%rbp)
	movl	$0, %eax
	movq	%rax, -16(%rbp)
	movl	$0, %eax
	movq	%rax, -8(%rbp)
	movsd	-56(%rbp), %xmm0
	addsd	-64(%rbp), %xmm0
	movsd	.LC0(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movq	-56(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -80(%rbp)
	movq	-64(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movapd	%xmm0, %xmm3
	addsd	-80(%rbp), %xmm3
	movsd	%xmm3, -80(%rbp)
	movq	-56(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	-80(%rbp), %xmm3
	subsd	%xmm0, %xmm3
	movsd	%xmm3, -80(%rbp)
	movq	-64(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	-80(%rbp), %xmm3
	subsd	%xmm0, %xmm3
	movsd	%xmm3, -80(%rbp)
	movq	-24(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -88(%rbp)
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movsd	-96(%rbp), %xmm0
	call	*%rdx
	movsd	-88(%rbp), %xmm5
	subsd	%xmm0, %xmm5
	movsd	%xmm5, -88(%rbp)
	movq	-56(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movsd	-96(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -96(%rbp)
	movq	-64(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	call	*%rdx
	movapd	%xmm0, %xmm4
	addsd	-96(%rbp), %xmm4
	movsd	%xmm4, -96(%rbp)
	movq	-56(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	call	*%rdx
	movsd	-96(%rbp), %xmm4
	subsd	%xmm0, %xmm4
	movsd	%xmm4, -96(%rbp)
	movq	-64(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -104(%rbp)
	movsd	-104(%rbp), %xmm0
	call	*%rdx
	movsd	-96(%rbp), %xmm4
	subsd	%xmm0, %xmm4
	movapd	%xmm4, %xmm0
	movsd	.LC0(%rip), %xmm1
	divsd	%xmm1, %xmm0
	movsd	-88(%rbp), %xmm5
	subsd	%xmm0, %xmm5
	movapd	%xmm5, %xmm0
	movsd	-80(%rbp), %xmm3
	mulsd	%xmm0, %xmm3
	movapd	%xmm3, %xmm1
	movsd	-72(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm0
	xorpd	%xmm2, %xmm0
	ucomisd	%xmm1, %xmm0
	ja	.L16
	jmp	.L13
.L16:
	jmp	.L10
.L11:
	movq	-56(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -80(%rbp)
	movq	-56(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	-80(%rbp), %xmm6
	subsd	%xmm0, %xmm6
	movapd	%xmm6, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-64(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -80(%rbp)
	movq	-64(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	-80(%rbp), %xmm7
	subsd	%xmm0, %xmm7
	movapd	%xmm7, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	mulsd	-56(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	mulsd	-64(%rbp), %xmm1
	subsd	%xmm1, %xmm0
	movsd	-8(%rbp), %xmm1
	subsd	-16(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -56(%rbp)
.L10:
	movq	-24(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -80(%rbp)
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	-80(%rbp), %xmm2
	subsd	%xmm0, %xmm2
	movsd	%xmm2, -80(%rbp)
	movsd	-24(%rbp), %xmm0
	addsd	-72(%rbp), %xmm0
	movq	-40(%rbp), %rax
	call	*%rax
	movsd	%xmm0, -88(%rbp)
	movsd	-24(%rbp), %xmm0
	addsd	-72(%rbp), %xmm0
	movq	-48(%rbp), %rax
	call	*%rax
	movsd	-88(%rbp), %xmm6
	subsd	%xmm0, %xmm6
	movapd	%xmm6, %xmm0
	mulsd	-80(%rbp), %xmm0
	movsd	.LC7(%rip), %xmm1
	andpd	%xmm1, %xmm0
	ucomisd	-72(%rbp), %xmm0
	ja	.L11
	jmp	.L12
.L14:
	movq	-56(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -80(%rbp)
	movq	-56(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	-80(%rbp), %xmm7
	subsd	%xmm0, %xmm7
	movapd	%xmm7, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-64(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -80(%rbp)
	movq	-64(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	-80(%rbp), %xmm2
	subsd	%xmm0, %xmm2
	movapd	%xmm2, %xmm0
	movsd	%xmm0, -8(%rbp)
	movsd	-8(%rbp), %xmm0
	mulsd	-56(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	mulsd	-64(%rbp), %xmm1
	subsd	%xmm1, %xmm0
	movsd	-8(%rbp), %xmm1
	subsd	-16(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -64(%rbp)
.L13:
	movsd	-24(%rbp), %xmm0
	subsd	-72(%rbp), %xmm0
	movq	-40(%rbp), %rax
	call	*%rax
	movsd	%xmm0, -80(%rbp)
	movsd	-24(%rbp), %xmm0
	subsd	-72(%rbp), %xmm0
	movq	-48(%rbp), %rax
	call	*%rax
	movsd	-80(%rbp), %xmm5
	subsd	%xmm0, %xmm5
	movsd	%xmm5, -80(%rbp)
	movq	-24(%rbp), %rax
	movq	-40(%rbp), %rdx
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	call	*%rdx
	movsd	%xmm0, -88(%rbp)
	movq	-24(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rax, -96(%rbp)
	movsd	-96(%rbp), %xmm0
	call	*%rdx
	movsd	-88(%rbp), %xmm6
	subsd	%xmm0, %xmm6
	movapd	%xmm6, %xmm0
	mulsd	-80(%rbp), %xmm0
	movsd	.LC7(%rip), %xmm1
	andpd	%xmm1, %xmm0
	ucomisd	-72(%rbp), %xmm0
	ja	.L14
.L12:
	movq	-24(%rbp), %rax
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	root_finder, .-root_finder
	.globl	integral
	.type	integral, @function
integral:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$96, %rsp
	movq	%rdi, -56(%rbp)
	movsd	%xmm0, -64(%rbp)
	movsd	%xmm1, -72(%rbp)
	movsd	%xmm2, -80(%rbp)
	movsd	-80(%rbp), %xmm1
	movsd	.LC8(%rip), %xmm0
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -48(%rbp)
	movl	$0, %eax
	movq	%rax, -40(%rbp)
	movq	$8, -24(%rbp)
	jmp	.L18
.L24:
	salq	-24(%rbp)
	movsd	-72(%rbp), %xmm0
	subsd	-64(%rbp), %xmm0
	cvtsi2sdq	-24(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	movq	$0, -32(%rbp)
	movl	$0, %eax
	movq	%rax, -16(%rbp)
	jmp	.L19
.L23:
	cvtsi2sdq	-32(%rbp), %xmm0
	mulsd	-8(%rbp), %xmm0
	addsd	-64(%rbp), %xmm0
	movq	-56(%rbp), %rax
	call	*%rax
	mulsd	-8(%rbp), %xmm0
	cmpq	$0, -32(%rbp)
	je	.L20
	movq	-32(%rbp), %rax
	cmpq	-24(%rbp), %rax
	jne	.L21
.L20:
	movabsq	$4602678819172646912, %rax
	jmp	.L22
.L21:
	movabsq	$4607182418800017408, %rax
.L22:
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm3
	mulsd	%xmm3, %xmm0
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	addq	$1, -32(%rbp)
.L19:
	movq	-24(%rbp), %rax
	addq	$1, %rax
	cmpq	-32(%rbp), %rax
	jg	.L23
	movq	-48(%rbp), %rax
	movq	%rax, -40(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -48(%rbp)
.L18:
	movsd	-48(%rbp), %xmm0
	subsd	-40(%rbp), %xmm0
	movsd	.LC7(%rip), %xmm1
	andpd	%xmm1, %xmm0
	movsd	.LC4(%rip), %xmm1
	divsd	%xmm1, %xmm0
	ucomisd	-80(%rbp), %xmm0
	ja	.L24
	movq	-48(%rbp), %rax
	movq	%rax, -88(%rbp)
	movsd	-88(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	integral, .-integral
	.globl	f12
	.type	f12, @function
f12:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	call	f1
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	call	f2
	movsd	-16(%rbp), %xmm1
	subsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	f12, .-f12
	.globl	f23
	.type	f23, @function
f23:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	call	f2
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	call	f3
	movsd	-16(%rbp), %xmm1
	subsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE8:
	.size	f23, .-f23
	.globl	f13
	.type	f13, @function
f13:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	%xmm0, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	call	f1
	movsd	%xmm0, -16(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -24(%rbp)
	movsd	-24(%rbp), %xmm0
	call	f3
	movsd	-16(%rbp), %xmm1
	subsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -16(%rbp)
	movsd	-16(%rbp), %xmm0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE9:
	.size	f13, .-f13
	.section	.rodata
.LC15:
	.string	"x1 = %.9lf\n"
.LC18:
	.string	"x2 = %.9lf\n"
.LC21:
	.string	"x3 = %.9lf\n"
	.align 8
.LC22:
	.string	"square of non-linear triangle = %.9lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movabsq	$-4606056518893174784, %rax
	movq	%rax, -56(%rbp)
	movabsq	$-4646453807550688133, %rax
	movq	%rax, -48(%rbp)
	movabsq	$4517329193108106637, %rax
	movq	%rax, -40(%rbp)
	movabsq	$4517329193108106637, %rax
	movq	%rax, -32(%rbp)
	movq	-40(%rbp), %rcx
	movabsq	$-4623107147082399482, %rdx
	movabsq	$-4616820122002590269, %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f2, %esi
	movl	$f1, %edi
	call	root_finder
	movsd	%xmm0, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC15, %edi
	movl	$1, %eax
	call	printf
	movq	-40(%rbp), %rcx
	movabsq	$-4612631774349135708, %rdx
	movabsq	$-4611413550649931989, %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f3, %esi
	movl	$f2, %edi
	call	root_finder
	movsd	%xmm0, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC18, %edi
	movl	$1, %eax
	call	printf
	movq	-40(%rbp), %rcx
	movabsq	$-4607632778762754458, %rdx
	movabsq	$-4606394288865227571, %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f3, %esi
	movl	$f1, %edi
	call	root_finder
	movsd	%xmm0, -72(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC21, %edi
	movl	$1, %eax
	call	printf
	movsd	-24(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	ucomisd	-40(%rbp), %xmm0
	jae	.L33
	movsd	-24(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	movsd	-40(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	jb	.L34
	movsd	-24(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	movsd	-40(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm1
	xorpd	%xmm2, %xmm1
	ucomisd	%xmm1, %xmm0
	jb	.L34
.L33:
	movsd	-8(%rbp), %xmm0
	subsd	-24(%rbp), %xmm0
	ucomisd	-40(%rbp), %xmm0
	jae	.L37
	movsd	-8(%rbp), %xmm0
	subsd	-24(%rbp), %xmm0
	movsd	-40(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	jb	.L38
	movsd	-8(%rbp), %xmm0
	subsd	-24(%rbp), %xmm0
	movsd	-40(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm1
	xorpd	%xmm2, %xmm1
	ucomisd	%xmm1, %xmm0
	jb	.L38
.L37:
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f23, %edi
	call	integral
	movsd	%xmm0, -72(%rbp)
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, -80(%rbp)
	movsd	-80(%rbp), %xmm2
	movq	%rdx, -80(%rbp)
	movsd	-80(%rbp), %xmm1
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	movl	$f13, %edi
	call	integral
	addsd	-72(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
.L38:
	movsd	-16(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	ucomisd	-40(%rbp), %xmm0
	jae	.L41
	movsd	-16(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	movsd	-40(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	jb	.L42
	movsd	-16(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	movsd	-40(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm1
	xorpd	%xmm2, %xmm1
	ucomisd	%xmm1, %xmm0
	jb	.L42
.L41:
	movq	-32(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f13, %edi
	call	integral
	movsd	%xmm0, -72(%rbp)
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rcx, -80(%rbp)
	movsd	-80(%rbp), %xmm2
	movq	%rdx, -80(%rbp)
	movsd	-80(%rbp), %xmm1
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	movl	$f12, %edi
	call	integral
	addsd	-72(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
	jmp	.L46
.L42:
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f23, %edi
	call	integral
	movsd	%xmm0, -72(%rbp)
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rcx, -80(%rbp)
	movsd	-80(%rbp), %xmm2
	movq	%rdx, -80(%rbp)
	movsd	-80(%rbp), %xmm1
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	movl	$f12, %edi
	call	integral
	addsd	-72(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
	jmp	.L46
.L34:
	movsd	-8(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	ucomisd	-40(%rbp), %xmm0
	jae	.L47
	movsd	-8(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	movsd	-40(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	jb	.L48
	movsd	-8(%rbp), %xmm0
	subsd	-16(%rbp), %xmm0
	movsd	-40(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm1
	xorpd	%xmm2, %xmm1
	ucomisd	%xmm1, %xmm0
	jb	.L48
.L47:
	movq	-32(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f12, %edi
	call	integral
	movsd	%xmm0, -72(%rbp)
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	-16(%rbp), %rax
	movq	%rcx, -80(%rbp)
	movsd	-80(%rbp), %xmm2
	movq	%rdx, -80(%rbp)
	movsd	-80(%rbp), %xmm1
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	movl	$f13, %edi
	call	integral
	addsd	-72(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
.L48:
	movsd	-24(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	ucomisd	-40(%rbp), %xmm0
	jae	.L51
	movsd	-24(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	movsd	-40(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	jb	.L52
	movsd	-24(%rbp), %xmm0
	subsd	-8(%rbp), %xmm0
	movsd	-40(%rbp), %xmm2
	movsd	.LC6(%rip), %xmm1
	xorpd	%xmm2, %xmm1
	ucomisd	%xmm1, %xmm0
	jb	.L52
.L51:
	movq	-32(%rbp), %rcx
	movq	-24(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f13, %edi
	call	integral
	movsd	%xmm0, -72(%rbp)
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, -80(%rbp)
	movsd	-80(%rbp), %xmm2
	movq	%rdx, -80(%rbp)
	movsd	-80(%rbp), %xmm1
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	movl	$f23, %edi
	call	integral
	addsd	-72(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
	jmp	.L46
.L52:
	movq	-32(%rbp), %rcx
	movq	-8(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rcx, -72(%rbp)
	movsd	-72(%rbp), %xmm2
	movq	%rdx, -72(%rbp)
	movsd	-72(%rbp), %xmm1
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$f12, %edi
	call	integral
	movsd	%xmm0, -72(%rbp)
	movq	-32(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	-8(%rbp), %rax
	movq	%rcx, -80(%rbp)
	movsd	-80(%rbp), %xmm2
	movq	%rdx, -80(%rbp)
	movsd	-80(%rbp), %xmm1
	movq	%rax, -80(%rbp)
	movsd	-80(%rbp), %xmm0
	movl	$f23, %edi
	call	integral
	addsd	-72(%rbp), %xmm0
	movsd	%xmm0, -64(%rbp)
.L46:
	movq	-64(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC22, %edi
	movl	$1, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE10:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1073741824
	.align 8
.LC1:
	.long	0
	.long	-1074790400
	.align 8
.LC2:
	.long	0
	.long	1072693248
	.align 8
.LC3:
	.long	0
	.long	-1073741824
	.align 8
.LC4:
	.long	0
	.long	1074266112
	.align 16
.LC6:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.align 16
.LC7:
	.long	4294967295
	.long	2147483647
	.long	0
	.long	0
	.align 8
.LC8:
	.long	0
	.long	1075052544
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
