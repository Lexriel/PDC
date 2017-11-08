	.file	"sizeof.c"
.globl ch
	.section	.rodata
.LC0:
	.string	"Hello world"
	.data
	.align 4
	.type	ch, @object
	.size	ch, 4
ch:
	.long	.LC0
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	subl	%eax, %esp
	movl	$.LC0, -4(%ebp)
	movl	$4, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.0.0 20050519 (Red Hat 4.0.0-8)"
	.section	.note.GNU-stack,"",@progbits
