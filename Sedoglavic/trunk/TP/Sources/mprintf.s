	.file	"mprintf.c"
	.text
	.align 2
	.type	PrintString,@function
PrintString:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	nop
.L2:
	movl	8(%ebp), %eax
	cmpb	$0, (%eax)
	jne	.L5
	jmp	.L1
.L5:
	subl	$12, %esp
	movl	8(%ebp), %eax
	movsbl	(%eax),%eax
	pushl	%eax
	call	putchar
	addl	$16, %esp
	incl	8(%ebp)
	jmp	.L2
.L1:
	leave
	ret
.Lfe1:
	.size	PrintString,.Lfe1-PrintString
	.align 2
	.type	PrintInt,@function
PrintInt:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$184, %esp
	movl	$0, -156(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -168(%ebp)
	cmpl	$0, -168(%ebp)
	jns	.L7
	negl	-168(%ebp)
.L7:
	movl	-168(%ebp), %eax
	movl	%eax, -160(%ebp)
.L8:
	movl	-156(%ebp), %eax
	movl	%eax, %ecx
	movl	-160(%ebp), %edx
	movl	%edx, %eax
	movl	$0, %edx
	divl	12(%ebp)
	movl	%edx, %eax
	movl	%eax, -164(%ebp)
	movl	%eax, -152(%ebp,%ecx,4)
	leal	-156(%ebp), %eax
	incl	(%eax)
	movl	-160(%ebp), %edx
	movl	%edx, %eax
	movl	$0, %edx
	divl	12(%ebp)
	movl	%eax, -160(%ebp)
	cmpl	$0, -160(%ebp)
	jne	.L8
	cmpl	$0, 8(%ebp)
	jns	.L12
	movl	-156(%ebp), %eax
	movl	$-3, -152(%ebp,%eax,4)
	leal	-156(%ebp), %eax
	incl	(%eax)
.L12:
	nop
.L13:
	cmpl	$0, -156(%ebp)
	jne	.L15
	jmp	.L6
.L15:
	subl	$12, %esp
	leal	-156(%ebp), %eax
	decl	(%eax)
	movl	-156(%ebp), %eax
	movl	-152(%ebp,%eax,4), %eax
	addl	$48, %eax
	pushl	%eax
	call	putchar
	addl	$16, %esp
	jmp	.L13
.L6:
	leave
	ret
.Lfe2:
	.size	PrintInt,.Lfe2-PrintInt
	.section	.rodata
.LC0:
	.string	" + "
.LC1:
	.string	" I "
	.text
	.align 2
.globl mprintf
	.type	mprintf,@function
mprintf:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$0, -4(%ebp)
	leal	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
	movl	.LC0, %eax
	movl	%eax, -16(%ebp)
	movl	.LC1, %eax
	movl	%eax, -20(%ebp)
	leal	-8(%ebp), %eax
	addl	$12, (%eax)
.L17:
	movl	8(%ebp), %eax
	cmpb	$0, (%eax)
	jne	.L20
	jmp	.L16
.L20:
	movl	8(%ebp), %eax
	cmpb	$37, (%eax)
	jne	.L21
	incl	8(%ebp)
	movl	8(%ebp), %eax
	movsbl	(%eax),%eax
	subl	$71, %eax
	movl	%eax, -24(%ebp)
	cmpl	$44, -24(%ebp)
	ja	.L30
	movl	-24(%ebp), %edx
	movl	.L31(,%edx,4), %eax
	jmp	*%eax
	.section	.rodata
	.align 4
	.align 4
.L31:
	.long	.L27
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L24
	.long	.L26
	.long	.L23
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L30
	.long	.L25
	.text
.L23:
	subl	$8, %esp
	pushl	$10
	movl	-8(%ebp), %eax
	pushl	(%eax)
	leal	-8(%ebp), %eax
	addl	$4, (%eax)
	call	PrintInt
	addl	$16, %esp
	jmp	.L19
.L24:
	subl	$8, %esp
	pushl	$2
	movl	-8(%ebp), %eax
	pushl	(%eax)
	leal	-8(%ebp), %eax
	addl	$4, (%eax)
	call	PrintInt
	addl	$16, %esp
	jmp	.L19
.L25:
	subl	$12, %esp
	movl	-8(%ebp), %eax
	pushl	(%eax)
	leal	-8(%ebp), %eax
	addl	$4, (%eax)
	call	PrintString
	addl	$16, %esp
	jmp	.L19
.L26:
	subl	$12, %esp
	movl	-8(%ebp), %eax
	pushl	(%eax)
	leal	-8(%ebp), %eax
	addl	$4, (%eax)
	call	putchar
	addl	$16, %esp
	jmp	.L19
.L27:
	incl	8(%ebp)
	movl	8(%ebp), %eax
	cmpb	$98, (%eax)
	jne	.L28
	movl	$2, -12(%ebp)
	jmp	.L29
.L28:
	movl	$10, -12(%ebp)
.L29:
	subl	$8, %esp
	pushl	-12(%ebp)
	movl	-8(%ebp), %eax
	pushl	(%eax)
	leal	-8(%ebp), %eax
	addl	$4, (%eax)
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	leal	-16(%ebp), %eax
	pushl	%eax
	call	PrintString
	addl	$16, %esp
	subl	$8, %esp
	pushl	-12(%ebp)
	movl	-8(%ebp), %eax
	pushl	(%eax)
	leal	-8(%ebp), %eax
	addl	$4, (%eax)
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	leal	-20(%ebp), %eax
	pushl	%eax
	call	PrintString
	addl	$16, %esp
	leal	-8(%ebp), %eax
	addl	$4, (%eax)
	jmp	.L19
.L30:
	subl	$12, %esp
	movl	8(%ebp), %eax
	movsbl	(%eax),%eax
	pushl	%eax
	call	putchar
	addl	$16, %esp
	jmp	.L19
.L21:
	subl	$12, %esp
	movl	8(%ebp), %eax
	movsbl	(%eax),%eax
	pushl	%eax
	call	putchar
	addl	$16, %esp
.L19:
	incl	8(%ebp)
	jmp	.L17
.L16:
	leave
	ret
.Lfe3:
	.size	mprintf,.Lfe3-mprintf
	.section	.rodata
.LC2:
	.string	"Vive PDC"
	.zero	71
.LC3:
	.string	"Hello world\n"
.LC4:
	.string	"o %c u %d e \n"
.LC5:
	.string	"o %Gb ue"
	.text
	.align 2
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	subl	$116, %esp
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	movl	.LC2, %eax
	movl	%eax, -88(%ebp)
	movl	.LC2+4, %eax
	movl	%eax, -84(%ebp)
	movb	.LC2+8, %al
	movb	%al, -80(%ebp)
	leal	-79(%ebp), %edi
	cld
	movl	$71, %ecx
	movb	$0, %al
	rep
	stosb
	movl	$10, -104(%ebp)
	movl	$22, -100(%ebp)
	leal	-88(%ebp), %eax
	movl	%eax, -96(%ebp)
	movb	$120, -105(%ebp)
	movl	$11, -112(%ebp)
	subl	$12, %esp
	pushl	$.LC3
	call	PrintString
	addl	$16, %esp
	subl	$8, %esp
	pushl	$10
	pushl	$234124
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	pushl	$10
	call	putchar
	addl	$16, %esp
	subl	$8, %esp
	pushl	$2
	pushl	$234124
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	pushl	$10
	call	putchar
	addl	$16, %esp
	subl	$8, %esp
	pushl	$10
	pushl	$0
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	pushl	$10
	call	putchar
	addl	$16, %esp
	subl	$8, %esp
	pushl	$2
	pushl	$0
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	pushl	$10
	call	putchar
	addl	$16, %esp
	subl	$8, %esp
	pushl	$10
	pushl	$-1024
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	pushl	$10
	call	putchar
	addl	$16, %esp
	subl	$8, %esp
	pushl	$2
	pushl	$-1024
	call	PrintInt
	addl	$16, %esp
	subl	$12, %esp
	pushl	$10
	call	putchar
	addl	$16, %esp
	subl	$4, %esp
	pushl	-112(%ebp)
	movsbl	-105(%ebp),%eax
	pushl	%eax
	pushl	$.LC4
	call	mprintf
	addl	$16, %esp
	pushl	-96(%ebp)
	pushl	-100(%ebp)
	pushl	-104(%ebp)
	pushl	$.LC5
	call	mprintf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %edi
	leave
	ret
.Lfe4:
	.size	main,.Lfe4-main
	.ident	"GCC: (GNU) 3.2 (Mandrake Linux 9.0 3.2-1mdk)"
