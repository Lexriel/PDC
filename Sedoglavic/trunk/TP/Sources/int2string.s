	.file	"int2string.c"
	.text
.globl int2string
	.type	int2string,@function
int2string:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$1, -4(%ebp)
	movl	$1, -8(%ebp)
.L2:
	movl	8(%ebp), %edx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	-4(%ebp)
	cmpl	8(%ebp), %edx
	jne	.L4
	jmp	.L3
.L4:
	leal	-8(%ebp), %eax
	incl	(%eax)
	movl	-4(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -4(%ebp)
	jmp	.L2
.L3:
	subl	$12, %esp
	pushl	-8(%ebp)
	call	malloc
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	movl	$0, -16(%ebp)
.L5:
	cmpl	$0, 8(%ebp)
	jne	.L7
	jmp	.L6
.L7:
	movl	-4(%ebp), %ecx
	movl	$1717986919, %eax
	imull	%ecx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	movl	%eax, -4(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, %ecx
	addl	-12(%ebp), %ecx
	movl	8(%ebp), %edx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	-4(%ebp)
	movl	%eax, -20(%ebp)
	movb	-20(%ebp), %al
	addl	$48, %eax
	movb	%al, (%ecx)
	leal	-16(%ebp), %eax
	incl	(%eax)
	movl	8(%ebp), %edx
	movl	%edx, %eax
	sarl	$31, %edx
	idivl	-4(%ebp)
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	imull	-4(%ebp), %eax
	subl	%eax, 8(%ebp)
	jmp	.L5
.L6:
	movl	-16(%ebp), %eax
	addl	-12(%ebp), %eax
	movb	$0, (%eax)
	movl	-12(%ebp), %eax
	leave
	ret
.Lfe1:
	.size	int2string,.Lfe1-int2string
	.section	.rodata
.LC0:
	.string	"Entrez un entier "
.LC1:
	.string	"%d"
.LC2:
	.string	"Le r\\'esultat est %s\n"
	.text
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	subl	$12, %esp
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC1
	call	scanf
	addl	$16, %esp
	subl	$8, %esp
	subl	$4, %esp
	pushl	-4(%ebp)
	call	int2string
	addl	$8, %esp
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe2:
	.size	main,.Lfe2-main
	.ident	"GCC: (GNU) 3.2.2 (Mandrake Linux 9.1 3.2.2-3mdk)"
