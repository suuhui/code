	.file	"fact_while.c"
	.text
	.globl	fact_while
	.type	fact_while, @function
fact_while:
.LFB11:
	.cfi_startproc
	cmpl	$1, %edi
	jle	.L4
	movl	$1, %eax
.L3:
	imull	%edi, %eax
	subl	$1, %edi
	cmpl	$1, %edi
	jne	.L3
	rep ret
.L4:
	movl	$1, %eax
	ret
	.cfi_endproc
.LFE11:
	.size	fact_while, .-fact_while
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-11)"
	.section	.note.GNU-stack,"",@progbits
