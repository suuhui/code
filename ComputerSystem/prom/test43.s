	.file	"test43.c"
	.text
	.globl	getLine
	.type	getLine, @function
getLine:
.LFB32:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	movq	%rsp, %rdi
	call	gets
	movq	%rsp, %rdi
	movl	$0, %eax
	movq	$-1, %rcx
	repnz scasb
	notq	%rcx
	leaq	-1(%rcx), %rdi
	call	malloc
	movq	%rax, %rbx
	movq	%rsp, %rsi
	movq	%rax, %rdi
	call	strcpy
	movq	%rbx, %rax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE32:
	.size	getLine, .-getLine
	.globl	main
	.type	main, @function
main:
.LFB33:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$0, %eax
	call	getLine
	movq	%rax, %rdi
	call	puts
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE33:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-11)"
	.section	.note.GNU-stack,"",@progbits
