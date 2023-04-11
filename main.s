	.file	"main.c"
	.text
	.globl	vect
	.data
vect:
	.long	1
	.long	2
	.size	i, 4
i:
	.long	1
	.size	haha, 4
haha:
	.long	2
	.section	.rodata
.LC0:
	.string	"asdasd"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	i(%rip), %edx
	movl	haha(%rip), %eax
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	vect(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	popq	%rbp
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main

