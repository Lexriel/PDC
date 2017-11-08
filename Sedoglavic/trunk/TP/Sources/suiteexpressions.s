	.file	"suiteexpressions.c"
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
	movl	$2, -4(%ebp)
	movl	$0, -8(%ebp)
	movl	-8(%ebp), %edx
	leal	-4(%ebp), %eax
	addl	%edx, (%eax)
	leal	-8(%ebp), %eax
	addl	$2, (%eax)
	movl	-8(%ebp), %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 (Mandrake Linux 9.1 3.2.2-3mdk)"
