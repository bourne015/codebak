	.file	"3.c"
	.section	.rodata
.LC0:
	.string	"found: a[%d][%d]\n"
	.text
	.globl	find
	.type	find, @function
find:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, -28(%rbp)
	movl	%edx, -32(%rbp)
	movl	%ecx, -36(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L2
.L9:
	movl	-32(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	.L3
.L8:
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	movl	(%rdx,%rax,4), %eax
	cmpl	-36(%rbp), %eax
	jne	.L4
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %eax
	jmp	.L5
.L4:
	movl	-8(%rbp), %eax
	cltq
	salq	$4, %rax
	movq	%rax, %rdx
	movq	-24(%rbp), %rax
	addq	%rax, %rdx
	movl	-4(%rbp), %eax
	cltq
	movl	(%rdx,%rax,4), %eax
	cmpl	-36(%rbp), %eax
	jle	.L10
	subl	$1, -32(%rbp)
	jmp	.L7
.L10:
	nop
.L7:
	subl	$1, -4(%rbp)
.L3:
	cmpl	$0, -4(%rbp)
	jns	.L8
	addl	$1, -8(%rbp)
.L2:
	movl	-8(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L9
	movl	$0, %eax
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	find, .-find
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -80(%rbp)
	movl	$2, -76(%rbp)
	movl	$8, -72(%rbp)
	movl	$9, -68(%rbp)
	movl	$2, -64(%rbp)
	movl	$4, -60(%rbp)
	movl	$9, -56(%rbp)
	movl	$12, -52(%rbp)
	movl	$4, -48(%rbp)
	movl	$7, -44(%rbp)
	movl	$10, -40(%rbp)
	movl	$13, -36(%rbp)
	movl	$6, -32(%rbp)
	movl	$8, -28(%rbp)
	movl	$11, -24(%rbp)
	movl	$15, -20(%rbp)
	leaq	-80(%rbp), %rax
	movl	$15, %ecx
	movl	$4, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	find
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	xorq	%fs:40, %rdx
	je	.L13
	call	__stack_chk_fail
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
