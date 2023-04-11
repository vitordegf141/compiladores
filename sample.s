
_lit_literal_1:
	.long	1
_lit_literal_4:
	.long	1
_lit_literal_6:
	.long	1
_lit_literal_0:
	.long	2
_lit_literal_2:
	.long	2
_lit_literal_5:
	.long	1222
_lit_literal_3:
	.string	"asdasd"

.LC0:
.string	"%d"
.LC1:
.string	"%s"
_tk_vect:
	.long	2
	.long	1
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	_lit_literal_3(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_lit_literal_4(%rip), %edx
	movl	_lit_literal_5(%rip), %eax
    movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	_tk_vect(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	popq	%rbp
	ret
	popq	%rbp
	ret
	.cfi_endproc
