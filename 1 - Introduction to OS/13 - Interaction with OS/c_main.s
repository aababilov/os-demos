	.file	"c_main.c"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movabsq	$8583909746840200520, %rax
	movl	$1, %edi
	movq	%rsp, %rsi
	movl	$14, %edx
	movq	%rax, (%rsp)
	movl	$1684828783, 8(%rsp)
	movw	$2593, 12(%rsp)
	movb	$0, 14(%rsp)
	call	write
	xorl	%edi, %edi
	call	_exit
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (Gentoo 4.5.4 p1.0, pie-0.4.7) 4.5.4"
	.section	.note.GNU-stack,"",@progbits
