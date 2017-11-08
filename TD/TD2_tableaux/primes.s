	.file	"primes.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"Les nombres premiers compris entre 1 et %d sont :\n"
.LC1:
	.string	"%d, "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -36(%rbp)
	movq	%rsi, -48(%rbp)
	movl	$100, -20(%rbp)
	cmpl	$1, -36(%rbp)
	jle	.L2
	movq	-48(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atoi
	movl	%eax, -20(%rbp)
.L2:
	movl	-20(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -16(%rbp)
	cltq
	salq	$2, %rax
	leaq	3(%rax), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movq	$16, -56(%rbp)
	movl	$0, %edx
	divq	-56(%rbp)
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$2, (%rax)
	movq	-8(%rbp), %rax
	movl	$2, 4(%rax)
	movl	$2, -32(%rbp)
	jmp	.L3
.L4:
	movq	-8(%rbp), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	movl	$1, (%rax,%rdx,4)
	addl	$1, -32(%rbp)
.L3:
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L4
	movl	$2, -24(%rbp)
	jmp	.L5
.L10:
	movq	-8(%rbp), %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	cmpl	$1, %eax
	jne	.L6
	movq	-8(%rbp), %rax
	movl	-24(%rbp), %edx
	movslq	%edx, %rdx
	movl	$0, (%rax,%rdx,4)
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	.L7
.L9:
	movl	-28(%rbp), %eax
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-24(%rbp)
	movl	%edx, %eax
	testl	%eax, %eax
	jne	.L8
	movq	-8(%rbp), %rax
	movl	-28(%rbp), %edx
	movslq	%edx, %rdx
	movl	$2, (%rax,%rdx,4)
.L8:
	addl	$1, -28(%rbp)
.L7:
	movl	-28(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L9
.L6:
	addl	$1, -24(%rbp)
.L5:
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L10
	movl	$0, -32(%rbp)
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L11
.L13:
	movq	-8(%rbp), %rax
	movl	-32(%rbp), %edx
	movslq	%edx, %rdx
	movl	(%rax,%rdx,4), %eax
	testl	%eax, %eax
	jne	.L12
	movl	-32(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
.L12:
	addl	$1, -32(%rbp)
.L11:
	movl	-32(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L13
	movl	$10, %edi
	call	putchar
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.7.3-1ubuntu1) 4.7.3"
	.section	.note.GNU-stack,"",@progbits
