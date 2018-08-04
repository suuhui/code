	.file	"intToHex.c"
	.text
	.globl	inttohex
	.type	inttohex, @function
inttohex:
.LFB21:
	.cfi_startproc
	movl	$0, %edx
.L5:
	movq	%rdi, %rcx
	sarq	$63, %rcx
	shrq	$60, %rcx
	leaq	(%rdi,%rcx), %rax
	andl	$15, %eax
	subq	%rcx, %rax
	movslq	%edx, %rcx
	addq	buf(%rip), %rcx
	leal	48(%rax), %esi
	leal	55(%rax), %r8d
	cmpl	$9, %eax
	movl	%esi, %eax
	cmovg	%r8d, %eax
	movb	%al, (%rcx)
	leaq	15(%rdi), %rax
	testq	%rdi, %rdi
	cmovns	%rdi, %rax
	sarq	$4, %rax
	movq	%rax, %rdi
	addl	$1, %edx
	testq	%rax, %rax
	jne	.L5
	movslq	%edx, %rdx
	movq	buf(%rip), %rax
	movb	$0, (%rax,%rdx)
	movq	buf(%rip), %rax
	ret
	.cfi_endproc
.LFE21:
	.size	inttohex, .-inttohex
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"please enter a number: "
.LC1:
	.string	"%ld"
	.text
	.globl	main
	.type	main, @function
main:
.LFB20:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	leaq	8(%rsp), %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movq	8(%rsp), %rdi
	call	inttohex
	movq	buf(%rip), %rdi
	call	puts
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE20:
	.size	main, .-main
	.comm	buf,8,8
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-11)"
	.section	.note.GNU-stack,"",@progbits
