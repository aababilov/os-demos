	.file	"write_rev.c"
	.section	.rodata
.LC0:
	.string	"write"
	.text
.globl write
	.type	write, @function
write:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movq	%rdx, -72(%rbp)
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	movq	$-1, %rdi
	.cfi_offset 3, -24
	call	dlsym@PLT
	movq	%rax, -32(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	malloc@PLT
	movq	%rax, -40(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L2
.L3:
	movl	-20(%rbp), %eax
	cltq
	movq	-72(%rbp), %rdx
	movq	%rdx, %rcx
	subq	%rax, %rcx
	movq	%rcx, %rax
	subq	$1, %rax
	addq	-40(%rbp), %rax
	movq	-64(%rbp), %rcx
	movl	-20(%rbp), %edx
	movslq	%edx, %rdx
	leaq	(%rcx,%rdx), %rdx
	movzbl	(%rdx), %edx
	movb	%dl, (%rax)
	addl	$1, -20(%rbp)
.L2:
	movl	-20(%rbp), %eax
	cltq
	cmpq	-72(%rbp), %rax
	jb	.L3
	movq	-72(%rbp), %rdx
	movq	-40(%rbp), %rcx
	movl	-52(%rbp), %eax
	movq	-32(%rbp), %rbx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	*%rbx
	movl	%eax, -20(%rbp)
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	free@PLT
	movl	-20(%rbp), %eax
	cltq
	addq	$72, %rsp
	popq	%rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	write, .-write
	.ident	"GCC: (Gentoo 4.5.4 p1.0, pie-0.4.7) 4.5.4"
	.section	.note.GNU-stack,"",@progbits
