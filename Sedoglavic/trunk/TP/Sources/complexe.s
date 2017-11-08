	.cstring
LC1:
	.ascii "%f\0"
LC2:
	.ascii "+%f*I \0"
LC4:
	.ascii "-%f*I \0"
	.literal4
	.align 2
LC0:
	.long	0
	.const
	.align 4
LC3:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.text
.globl _PrintComplexe
_PrintComplexe:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	call	L12
"L00000000001$pb":
L12:
	popl	%ebx
	movss	8(%ebp), %xmm0
	leal	LC0-"L00000000001$pb"(%ebx), %eax
	movss	(%eax), %xmm1
	ucomiss	%xmm1, %xmm0
	jne	L4
	jp	L4
	jmp	L2
L4:
	movss	8(%ebp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, 4(%esp)
	leal	LC1-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
L2:
	movss	12(%ebp), %xmm0
	leal	LC0-"L00000000001$pb"(%ebx), %eax
	movss	(%eax), %xmm1
	ucomiss	%xmm1, %xmm0
	ja	L7
	jmp	L5
L7:
	movss	12(%ebp), %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, 4(%esp)
	leal	LC2-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
L5:
	movss	12(%ebp), %xmm0
	leal	LC0-"L00000000001$pb"(%ebx), %eax
	movss	(%eax), %xmm1
	ucomiss	%xmm0, %xmm1
	ja	L10
	jmp	L11
L10:
	movss	12(%ebp), %xmm1
	leal	LC3-"L00000000001$pb"(%ebx), %eax
	movaps	(%eax), %xmm0
	xorps	%xmm1, %xmm0
	cvtss2sd	%xmm0, %xmm0
	movsd	%xmm0, 4(%esp)
	leal	LC4-"L00000000001$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
L11:
	addl	$20, %esp
	popl	%ebx
	leave
	ret
.globl _add
_add:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movss	12(%ebp), %xmm1
	movss	20(%ebp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -12(%ebp)
	movss	8(%ebp), %xmm1
	movss	16(%ebp), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -16(%ebp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	leave
	ret
.globl _mul
_mul:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movss	8(%ebp), %xmm1
	movss	16(%ebp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	12(%ebp), %xmm1
	movss	20(%ebp), %xmm0
	mulss	%xmm1, %xmm0
	movaps	%xmm2, %xmm1
	subss	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	movss	%xmm0, -16(%ebp)
	movss	16(%ebp), %xmm1
	movss	12(%ebp), %xmm0
	movaps	%xmm1, %xmm2
	mulss	%xmm0, %xmm2
	movss	8(%ebp), %xmm1
	movss	20(%ebp), %xmm0
	mulss	%xmm1, %xmm0
	addss	%xmm2, %xmm0
	movss	%xmm0, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	leave
	ret
	.const
	.align 4
LC5:
	.long	-2147483648
	.long	0
	.long	0
	.long	0
	.text
.globl _quo
_quo:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	call	L19
"L00000000002$pb":
L19:
	popl	%ebx
	movl	16(%ebp), %edx
	movss	20(%ebp), %xmm1
	leal	LC5-"L00000000002$pb"(%ebx), %eax
	movaps	(%eax), %xmm0
	xorps	%xmm1, %xmm0
	movl	%edx, -16(%ebp)
	movss	%xmm0, -12(%ebp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_mul
	movl	%eax, -24(%ebp)
	movl	%edx, -20(%ebp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	16(%ebp), %eax
	movl	20(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_mul
	movl	%eax, -16(%ebp)
	movl	%edx, -12(%ebp)
	movss	-24(%ebp), %xmm1
	movss	-16(%ebp), %xmm0
	movaps	%xmm1, %xmm2
	divss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, -24(%ebp)
	movss	-20(%ebp), %xmm1
	movss	-16(%ebp), %xmm0
	movaps	%xmm1, %xmm2
	divss	%xmm0, %xmm2
	movaps	%xmm2, %xmm0
	movss	%xmm0, -20(%ebp)
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	addl	$36, %esp
	popl	%ebx
	leave
	ret
	.cstring
LC8:
	.ascii "La somme de \0"
LC9:
	.ascii " et de \0"
LC10:
	.ascii " est \0"
LC11:
	.ascii "La produit de \0"
LC12:
	.ascii "La quotient de \0"
	.literal4
	.align 2
LC6:
	.long	1065353216
	.align 2
LC7:
	.long	1082130432
	.text
.globl _main
_main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$36, %esp
	call	L22
"L00000000003$pb":
L22:
	popl	%ebx
	leal	LC6-"L00000000003$pb"(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, -16(%ebp)
	leal	LC7-"L00000000003$pb"(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
	leal	LC6-"L00000000003$pb"(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, -24(%ebp)
	leal	LC7-"L00000000003$pb"(%ebx), %eax
	movl	(%eax), %eax
	movl	%eax, -20(%ebp)
	leal	LC8-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	leal	LC9-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	leal	LC10-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_add
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	movl	$10, (%esp)
	call	L_putchar$stub
	leal	LC11-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	leal	LC9-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	leal	LC10-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_mul
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	movl	$10, (%esp)
	call	L_putchar$stub
	leal	LC12-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	leal	LC9-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	leal	LC10-"L00000000003$pb"(%ebx), %eax
	movl	%eax, (%esp)
	call	L_printf$stub
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	-16(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_quo
	movl	%eax, (%esp)
	movl	%edx, 4(%esp)
	call	_PrintComplexe
	movl	$10, (%esp)
	call	L_putchar$stub
	movl	$0, %eax
	addl	$36, %esp
	popl	%ebx
	leave
	ret
	.section __IMPORT,__jump_table,symbol_stubs,self_modifying_code+pure_instructions,5
L_putchar$stub:
	.indirect_symbol _putchar
	hlt ; hlt ; hlt ; hlt ; hlt
L_printf$stub:
	.indirect_symbol _printf
	hlt ; hlt ; hlt ; hlt ; hlt
	.subsections_via_symbols
