	.file	"main.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%c"
	.text
	.p2align 4,,15
	.globl	build_tree
	.type	build_tree, @function
build_tree:
.LFB61:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xorl	%eax, %eax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movl	%esi, %r12d
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movl	$.LC0, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	%rsp, %rsi
	call	__isoc99_scanf
	movzbl	(%rsp), %ebx
	cmpb	$40, %bl
	je	.L32
	leal	-48(%rbx), %eax
	cmpb	$9, %al
	setbe	%r13b
	cmpb	$120, %bl
	sete	%al
	orb	%al, %r13b
	jne	.L33
.L3:
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	movzbl	(%rsp), %eax
	leal	-42(%rax), %edx
	cmpb	$1, %dl
	setbe	%cl
	cmpb	$45, %al
	sete	%dl
	orb	%dl, %cl
	movl	%ecx, %r14d
	je	.L4
	movb	%al, 0(%rbp)
.L4:
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	movzbl	(%rsp), %ebx
	cmpb	$40, %bl
	je	.L34
	leal	-48(%rbx), %eax
	cmpb	$9, %al
	setbe	%dl
	cmpb	$120, %bl
	sete	%al
	orb	%al, %dl
	movl	%edx, %r15d
	jne	.L35
.L6:
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	cmpb	$41, (%rsp)
	jne	.L10
	testl	%r12d, %r12d
	je	.L9
	testb	%r13b, %r13b
	je	.L9
	testb	%r15b, %r15b
	.p2align 4,,2
	je	.L9
	cmpq	$0, 8(%rbp)
	je	.L10
	cmpq	$0, 16(%rbp)
	je	.L10
.L11:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%rbp, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	.cfi_restore_state
	xorl	%eax, %eax
	movq	%rsp, %rsi
	movl	$.LC0, %edi
	call	__isoc99_scanf
	cmpb	$10, (%rsp)
	je	.L11
.L10:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L35:
	.cfi_restore_state
	movl	$24, %edi
	movl	%r14d, %r15d
	call	malloc
	movq	%rax, 16(%rbp)
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
	movb	%bl, (%rax)
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L33:
	movl	$24, %edi
	call	malloc
	movq	%rax, 8(%rbp)
	movq	$0, 8(%rax)
	movq	$0, 16(%rax)
	movb	%bl, (%rax)
	jmp	.L3
	.p2align 4,,10
	.p2align 3
.L34:
	movl	$24, %edi
	movl	%r14d, %r15d
	call	malloc
	movl	$1, %esi
	movq	%rax, 16(%rbp)
	movq	%rax, %rdi
	call	build_tree
	movq	%rax, 16(%rbp)
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L32:
	movl	$24, %edi
	movl	$1, %r13d
	call	malloc
	movl	$1, %esi
	movq	%rax, 8(%rbp)
	movq	%rax, %rdi
	call	build_tree
	movq	%rax, 8(%rbp)
	jmp	.L3
	.cfi_endproc
.LFE61:
	.size	build_tree, .-build_tree
	.p2align 4,,15
	.globl	computation
	.type	computation, @function
computation:
.LFB62:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %rax
	movl	%esi, %r15d
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	movq	%rdi, 40(%rsp)
	movl	$0, 64(%rsp)
	movl	$1, 52(%rsp)
.L37:
	movsbl	(%rax), %eax
	cmpb	$45, %al
	je	.L129
	cmpb	$43, %al
	je	.L130
	cmpb	$42, %al
	jne	.L41
	movq	40(%rsp), %rax
	movl	$0, 68(%rsp)
	movl	$1, 56(%rsp)
	movq	8(%rax), %rax
	movq	%rax, 32(%rsp)
.L42:
	movsbl	(%rax), %eax
	cmpb	$45, %al
	je	.L131
.L43:
	cmpb	$43, %al
	je	.L132
	cmpb	$42, %al
	jne	.L46
	movq	32(%rsp), %rax
	movl	$0, 72(%rsp)
	movl	$1, 60(%rsp)
	movq	8(%rax), %rax
	movq	%rax, 24(%rsp)
.L47:
	movsbl	(%rax), %eax
	cmpb	$45, %al
	je	.L133
.L48:
	cmpb	$43, %al
	je	.L134
	cmpb	$42, %al
	jne	.L81
	movq	24(%rsp), %rax
	movl	$0, 76(%rsp)
	movl	$1, 48(%rsp)
	movq	8(%rax), %rax
	movq	%rax, 16(%rsp)
.L82:
	movsbl	(%rax), %eax
	cmpb	$45, %al
	je	.L135
.L83:
	cmpb	$43, %al
	je	.L136
	cmpb	$42, %al
	jne	.L92
	movq	16(%rsp), %rax
	movl	$0, 8(%rsp)
	movl	$1, %r13d
	movq	8(%rax), %r12
.L93:
	movsbl	(%r12), %eax
	cmpb	$45, %al
	je	.L137
.L94:
	cmpb	$43, %al
	je	.L138
	cmpb	$42, %al
	jne	.L103
	movq	8(%r12), %rbx
	xorl	%r14d, %r14d
	movl	$1, %ebp
.L104:
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	je	.L139
.L105:
	cmpb	$43, %al
	je	.L140
	cmpb	$42, %al
	jne	.L108
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbx), %rbx
	imull	%eax, %ebp
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	jne	.L105
.L139:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%ebp, %eax
	movq	16(%rbx), %rbx
	negl	%ebp
	addl	%eax, %r14d
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L140:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%ebp, %eax
	movq	16(%rbx), %rbx
	addl	%eax, %r14d
	jmp	.L104
	.p2align 4,,10
	.p2align 3
.L108:
	cmpb	$120, %al
	je	.L122
	subl	$48, %eax
.L109:
	movq	16(%r12), %r12
	imull	%eax, %ebp
	movsbl	(%r12), %eax
	addl	%ebp, %r14d
	imull	%r14d, %r13d
	cmpb	$45, %al
	jne	.L94
.L137:
	movq	8(%r12), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%r12), %r12
	imull	%r13d, %eax
	negl	%r13d
	addl	%eax, 8(%rsp)
	jmp	.L93
	.p2align 4,,10
	.p2align 3
.L122:
	movl	%r15d, %eax
	jmp	.L109
	.p2align 4,,10
	.p2align 3
.L138:
	movq	8(%r12), %rbx
	xorl	%r14d, %r14d
	movl	$1, %ebp
.L97:
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	je	.L141
.L98:
	cmpb	$43, %al
	je	.L142
	cmpb	$42, %al
	jne	.L101
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbx), %rbx
	imull	%eax, %ebp
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	jne	.L98
.L141:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%ebp, %eax
	movq	16(%rbx), %rbx
	negl	%ebp
	addl	%eax, %r14d
	jmp	.L97
	.p2align 4,,10
	.p2align 3
.L142:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%ebp, %eax
	movq	16(%rbx), %rbx
	addl	%eax, %r14d
	jmp	.L97
	.p2align 4,,10
	.p2align 3
.L101:
	cmpb	$120, %al
	je	.L121
	subl	$48, %eax
.L102:
	imull	%ebp, %eax
	movq	16(%r12), %r12
	addl	%r14d, %eax
	imull	%r13d, %eax
	addl	%eax, 8(%rsp)
	jmp	.L93
.L103:
	cmpb	$120, %al
	je	.L123
	subl	$48, %eax
.L110:
	movq	16(%rsp), %rdx
	movl	8(%rsp), %r14d
	imull	%eax, %r13d
	movq	16(%rdx), %rcx
	addl	%r13d, %r14d
	imull	48(%rsp), %r14d
	movq	%rcx, %rax
	movq	%rcx, 16(%rsp)
	movsbl	(%rax), %eax
	cmpb	$45, %al
	movl	%r14d, 48(%rsp)
	jne	.L83
.L135:
	movq	16(%rsp), %rbx
	movl	%r15d, %esi
	movq	8(%rbx), %rdi
	call	computation
	movq	16(%rbx), %rcx
	imull	48(%rsp), %eax
	negl	48(%rsp)
	movq	%rcx, 16(%rsp)
	addl	%eax, 76(%rsp)
	movq	%rcx, %rax
	jmp	.L82
.L121:
	movl	%r15d, %eax
	jmp	.L102
.L123:
	movl	%r15d, %eax
	jmp	.L110
.L136:
	movq	16(%rsp), %rax
	xorl	%r12d, %r12d
	movl	$1, %ebp
	movq	8(%rax), %rbx
.L86:
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	je	.L143
.L87:
	cmpb	$43, %al
	je	.L144
	cmpb	$42, %al
	jne	.L90
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbx), %rbx
	imull	%eax, %ebp
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	jne	.L87
.L143:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%ebp, %eax
	movq	16(%rbx), %rbx
	negl	%ebp
	addl	%eax, %r12d
	jmp	.L86
.L144:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%ebp, %eax
	movq	16(%rbx), %rbx
	addl	%eax, %r12d
	jmp	.L86
.L90:
	cmpb	$120, %al
	je	.L120
	subl	$48, %eax
.L91:
	movq	16(%rsp), %rdx
	imull	%ebp, %eax
	movq	16(%rdx), %rcx
	addl	%r12d, %eax
	imull	48(%rsp), %eax
	movq	%rcx, 16(%rsp)
	addl	%eax, 76(%rsp)
	movq	%rcx, %rax
	jmp	.L82
.L92:
	cmpb	$120, %al
	je	.L124
	subl	$48, %eax
.L111:
	imull	48(%rsp), %eax
	movq	24(%rsp), %rdx
	addl	76(%rsp), %eax
	imull	60(%rsp), %eax
	movq	16(%rdx), %rcx
	movq	%rcx, 24(%rsp)
	movl	%eax, 60(%rsp)
	movq	%rcx, %rax
	movsbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L48
.L133:
	movq	24(%rsp), %rax
	xorl	%ebp, %ebp
	movl	$1, %r12d
	movq	8(%rax), %rbx
.L49:
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	je	.L145
.L50:
	cmpb	$43, %al
	je	.L146
	cmpb	$42, %al
	jne	.L53
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbx), %rbx
	imull	%eax, %r12d
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	jne	.L50
.L145:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%r12d, %eax
	movq	16(%rbx), %rbx
	negl	%r12d
	addl	%eax, %ebp
	jmp	.L49
.L120:
	movl	%r15d, %eax
	jmp	.L91
.L134:
	movq	24(%rsp), %rax
	movl	$0, 76(%rsp)
	movl	$1, 16(%rsp)
	movq	8(%rax), %rax
	movq	%rax, 8(%rsp)
.L57:
	movsbl	(%rax), %eax
	cmpb	$45, %al
	je	.L147
.L58:
	cmpb	$43, %al
	je	.L148
	cmpb	$42, %al
	jne	.L67
	movq	8(%rsp), %rax
	movl	$0, 48(%rsp)
	movl	$1, %r12d
	movq	8(%rax), %rbx
.L68:
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	je	.L149
.L69:
	cmpb	$43, %al
	je	.L150
	cmpb	$42, %al
	jne	.L78
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbx), %rbx
	imull	%eax, %r12d
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	jne	.L69
.L149:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbx), %rbx
	imull	%r12d, %eax
	negl	%r12d
	addl	%eax, 48(%rsp)
	jmp	.L68
.L150:
	movq	8(%rbx), %rbp
	xorl	%r14d, %r14d
	movl	$1, %r13d
.L72:
	movsbl	0(%rbp), %eax
	cmpb	$45, %al
	je	.L151
.L73:
	cmpb	$43, %al
	je	.L152
	cmpb	$42, %al
	jne	.L76
	movq	8(%rbp), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbp), %rbp
	imull	%eax, %r13d
	movsbl	0(%rbp), %eax
	cmpb	$45, %al
	jne	.L73
.L151:
	movq	8(%rbp), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%r13d, %eax
	movq	16(%rbp), %rbp
	negl	%r13d
	addl	%eax, %r14d
	jmp	.L72
.L152:
	movq	8(%rbp), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%r13d, %eax
	movq	16(%rbp), %rbp
	addl	%eax, %r14d
	jmp	.L72
.L76:
	cmpb	$120, %al
	je	.L117
	subl	$48, %eax
.L77:
	imull	%r13d, %eax
	movq	16(%rbx), %rbx
	addl	%r14d, %eax
	imull	%r12d, %eax
	addl	%eax, 48(%rsp)
	jmp	.L68
.L78:
	cmpb	$120, %al
	je	.L118
	subl	$48, %eax
.L79:
	movq	8(%rsp), %rcx
	movl	48(%rsp), %r14d
	imull	%r12d, %eax
	movq	16(%rcx), %rdx
	addl	%eax, %r14d
	imull	16(%rsp), %r14d
	movq	%rdx, %rax
	movq	%rdx, 8(%rsp)
	movsbl	(%rax), %eax
	cmpb	$45, %al
	movl	%r14d, 16(%rsp)
	jne	.L58
.L147:
	movq	8(%rsp), %rbx
	movl	%r15d, %esi
	movq	8(%rbx), %rdi
	call	computation
	movq	16(%rbx), %rdx
	imull	16(%rsp), %eax
	negl	16(%rsp)
	movq	%rdx, 8(%rsp)
	addl	%eax, 76(%rsp)
	movq	%rdx, %rax
	jmp	.L57
.L117:
	movl	%r15d, %eax
	jmp	.L77
.L118:
	movl	%r15d, %eax
	jmp	.L79
.L148:
	movq	8(%rsp), %rax
	xorl	%ebp, %ebp
	movl	$1, %r12d
	movq	8(%rax), %rbx
.L61:
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	je	.L153
.L62:
	cmpb	$43, %al
	je	.L154
	cmpb	$42, %al
	jne	.L65
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	movq	16(%rbx), %rbx
	imull	%eax, %r12d
	movsbl	(%rbx), %eax
	cmpb	$45, %al
	jne	.L62
.L153:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%r12d, %eax
	movq	16(%rbx), %rbx
	negl	%r12d
	addl	%eax, %ebp
	jmp	.L61
.L154:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%r12d, %eax
	movq	16(%rbx), %rbx
	addl	%eax, %ebp
	jmp	.L61
.L65:
	cmpb	$120, %al
	je	.L116
	subl	$48, %eax
.L66:
	movq	8(%rsp), %rcx
	imull	%r12d, %eax
	movq	16(%rcx), %rdx
	addl	%ebp, %eax
	imull	16(%rsp), %eax
	movq	%rdx, 8(%rsp)
	addl	%eax, 76(%rsp)
	movq	%rdx, %rax
	jmp	.L57
.L67:
	cmpb	$120, %al
	je	.L119
	subl	$48, %eax
.L80:
	imull	16(%rsp), %eax
	movq	24(%rsp), %rcx
	addl	76(%rsp), %eax
	movq	16(%rcx), %rdx
	imull	60(%rsp), %eax
	movq	%rdx, 24(%rsp)
	addl	%eax, 72(%rsp)
	movq	%rdx, %rax
	jmp	.L47
.L146:
	movq	8(%rbx), %rdi
	movl	%r15d, %esi
	call	computation
	imull	%r12d, %eax
	movq	16(%rbx), %rbx
	addl	%eax, %ebp
	jmp	.L49
.L53:
	cmpb	$120, %al
	je	.L115
	subl	$48, %eax
.L54:
	movq	24(%rsp), %rdx
	imull	%r12d, %eax
	movq	16(%rdx), %rcx
	addl	%ebp, %eax
	imull	60(%rsp), %eax
	movq	%rcx, 24(%rsp)
	negl	60(%rsp)
	addl	%eax, 72(%rsp)
	movq	%rcx, %rax
	jmp	.L47
.L81:
	cmpb	$120, %al
	je	.L125
	subl	$48, %eax
.L112:
	imull	60(%rsp), %eax
	movq	32(%rsp), %rdx
	addl	72(%rsp), %eax
	imull	56(%rsp), %eax
	movq	16(%rdx), %rcx
	movq	%rcx, 32(%rsp)
	movl	%eax, 56(%rsp)
	movq	%rcx, %rax
	movsbl	(%rax), %eax
	cmpb	$45, %al
	jne	.L43
.L131:
	movq	32(%rsp), %rbx
	movl	%r15d, %esi
	movq	8(%rbx), %rdi
	call	computation
	movq	16(%rbx), %rdx
	imull	56(%rsp), %eax
	negl	56(%rsp)
	movq	%rdx, 32(%rsp)
	addl	%eax, 68(%rsp)
	movq	%rdx, %rax
	jmp	.L42
	.p2align 4,,10
	.p2align 3
.L124:
	movl	%r15d, %eax
	jmp	.L111
.L116:
	movl	%r15d, %eax
	jmp	.L66
.L119:
	movl	%r15d, %eax
	.p2align 4,,2
	jmp	.L80
.L46:
	cmpb	$120, %al
	.p2align 4,,3
	je	.L126
	subl	$48, %eax
.L113:
	imull	56(%rsp), %eax
	movq	40(%rsp), %rdx
	addl	68(%rsp), %eax
	imull	52(%rsp), %eax
	movq	16(%rdx), %rcx
	movq	%rcx, 40(%rsp)
	movl	%eax, 52(%rsp)
	movq	%rcx, %rax
	jmp	.L37
.L132:
	movq	32(%rsp), %rbx
	movl	%r15d, %esi
	movq	8(%rbx), %rdi
	call	computation
	movq	16(%rbx), %rcx
	imull	56(%rsp), %eax
	movq	%rcx, 32(%rsp)
	addl	%eax, 68(%rsp)
	movq	%rcx, %rax
	jmp	.L42
.L126:
	movl	%r15d, %eax
	jmp	.L113
.L41:
	cmpb	$120, %al
	je	.L127
	subl	$48, %eax
.L114:
	imull	52(%rsp), %eax
	addl	64(%rsp), %eax
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L130:
	.cfi_restore_state
	movq	40(%rsp), %rbx
	movl	%r15d, %esi
	movq	8(%rbx), %rdi
	call	computation
	movq	16(%rbx), %rcx
	imull	52(%rsp), %eax
	movq	%rcx, 40(%rsp)
	addl	%eax, 64(%rsp)
	movq	%rcx, %rax
	jmp	.L37
.L115:
	movl	%r15d, %eax
	jmp	.L54
.L125:
	movl	%r15d, %eax
	jmp	.L112
.L129:
	movq	40(%rsp), %rbx
	movl	%r15d, %esi
	movq	8(%rbx), %rdi
	call	computation
	movq	16(%rbx), %rdx
	imull	52(%rsp), %eax
	negl	52(%rsp)
	movq	%rdx, 40(%rsp)
	addl	%eax, 64(%rsp)
	movq	%rdx, %rax
	jmp	.L37
.L127:
	movl	%r15d, %eax
	jmp	.L114
	.cfi_endproc
.LFE62:
	.size	computation, .-computation
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"please, enter expression you want to computate"
	.section	.rodata.str1.1
.LC2:
	.string	"expression is incorrect"
.LC3:
	.string	"please, enter value of x"
.LC4:
	.string	"%d"
.LC5:
	.string	"expresion equals %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB63:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$.LC1, %edi
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movl	$0, 16(%rsp)
	call	puts
	movl	$24, %edi
	call	malloc
	movq	%rsp, %rsi
	movq	%rax, %rbx
	movl	$.LC0, %edi
	xorl	%eax, %eax
	call	__isoc99_scanf
	movzbl	(%rsp), %edx
	cmpb	$40, %dl
	je	.L162
	cmpb	$120, %dl
	je	.L163
	subl	$48, %edx
	cmpb	$9, %dl
	jbe	.L164
.L160:
	movl	$.LC2, %edi
	call	puts
.L158:
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L164:
	.cfi_restore_state
	movl	$.LC3, %edi
	call	puts
	leaq	16(%rsp), %rsi
	movl	$.LC4, %edi
	xorl	%eax, %eax
	call	__isoc99_scanf
	movsbl	(%rsp), %edx
	movl	$.LC5, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	subl	$48, %edx
	call	__printf_chk
	jmp	.L158
.L162:
	movq	%rbx, %rdi
	movl	$1, %esi
	call	build_tree
	testq	%rax, %rax
	movq	%rax, %rbx
	je	.L160
	movl	$.LC3, %edi
	call	puts
	leaq	16(%rsp), %rsi
	movl	$.LC4, %edi
	xorl	%eax, %eax
	call	__isoc99_scanf
	movl	16(%rsp), %esi
	movq	%rbx, %rdi
	call	computation
	movl	$.LC5, %esi
	movl	%eax, %edx
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	jmp	.L158
.L163:
	movl	$.LC3, %edi
	call	puts
	leaq	16(%rsp), %rsi
	movl	$.LC4, %edi
	xorl	%eax, %eax
	call	__isoc99_scanf
	movl	16(%rsp), %edx
	movl	$.LC5, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	jmp	.L158
	.cfi_endproc
.LFE63:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
