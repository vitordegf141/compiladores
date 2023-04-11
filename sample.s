.section	.rodata
_lit_literal_18:
	.string	"\n"
	.text
_lit_literal_32:
	.string	"\n"
	.text
_lit_literal_29:
	.string	"Incrementado algumas vezes a fica "
	.text
_lit_literal_25:
	.string	"Digite mais um numero: \n"
	.text
_lit_literal_16:
	.string	"xa ="
	.text
_lit_literal_17:
	.string	" nn="
	.text
_lit_literal_37:
	.string	"OK!\n"
	.text
_lit_literal_34:
	.string	"A era=15\n"
	.text
_lit_literal_24:
	.string	"Digite um numero: \n"
	.text
_lit_literal_36:
	.string	"Nao tem como isso...\n"
	.text
.LC0:
	.string	"%d"
	.text
.LC1:
	.string	"%s"
	.data
_tmp_temp0:
	.long	0
_tmp_temp1:
	.long	0
_tmp_temp2:
	.long	0
_tmp_temp3:
	.long	0
_tmp_temp4:
	.long	0
_tmp_temp5:
	.long	0
_tmp_temp6:
	.long	0
_tmp_temp7:
	.long	0
_tmp_temp8:
	.long	0
_tmp_temp9:
	.long	0
_lit_literal_6:
	.long	0
_lit_literal_7:
	.long	0
_lit_literal_8:
	.long	0
_lit_literal_9:
	.long	0
_lit_literal_10:
	.long	0
_lit_literal_11:
	.long	0
_lit_literal_12:
	.long	0
_lit_literal_13:
	.long	0
_lit_literal_14:
	.long	0
_lit_literal_19:
	.long	0
_lit_literal_3:
	.long	1
_lit_literal_26:
	.long	1
_lit_literal_27:
	.long	1
_lit_literal_31:
	.long	1
_lit_literal_33:
	.long	1
_lit_literal_23:
	.long	2
_lit_literal_30:
	.long	2
_lit_literal_20:
	.long	5
_lit_literal_22:
	.long	5
_lit_literal_2:
	.byte	'A'
_tmp_temp10:
	.long	0
_tmp_temp11:
	.long	0
_tmp_temp12:
	.long	0
_lit_literal_4:
	.long	10
_lit_literal_5:
	.byte	'a'
_lit_literal_28:
	.long	10
_lit_literal_35:
	.long	15
_lit_literal_21:
	.long	55
_lit_literal_0:
	.byte	'x'
_lit_literal_1:
	.long	100
_lit_literal_15:
	.long	100
_lit_literal_38:
	.long	100
_tk_c:
	.byte	'x'
_tk_d:
	.byte	100
_tk_a:
	.long	'A'
_tk_i:
	.long	1
_tk_v:
	.long	'a'
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
_tk_matrix:
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
_tk_nn:
	.long	0
_tk_xa:
	.long	0
	.text
	.globl	_tk_incn
	.type	_tk_incn, @function
_tk_incn:
	.cfi_startproc
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	_lit_literal_16(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_tk_xa(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	_lit_literal_17(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_tk_nn(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	_lit_literal_18(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_tk_xa(%rip), %eax
	movl	_tk_nn(%rip), %edx
	addl	%edx, %eax
	movl	%eax, _tmp_temp0(%rip)
	movl	_tmp_temp0(%rip), %eax
	popq	%rbp
	ret
	popq	%rbp
	ret
	.cfi_endproc
	.size _tk_incn	, .-_tk_incn
	.text
	.globl	main
	.type	main, @function
main:
	.cfi_startproc
	endbr64
	pushq	%rbp
	movq	%rsp, %rbp
	movl	_lit_literal_19(%rip), %eax
	movl	%eax, _tk_a(%rip)
	movl	_tk_a(%rip), %eax
	movl	_tk_i(%rip), %edx
	subl	%edx, %eax
	movl	%eax, _tmp_temp1(%rip)
	movl	_tmp_temp1(%rip), %eax
	movl	%eax, _tk_a(%rip)
	movl	_lit_literal_20(%rip), %eax
	movl	%eax, _tk_a(%rip)
	movl	_tk_a(%rip), %edx
	movl	_lit_literal_21(%rip), %eax
	movslq	%edx, %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	_tk_v(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	_lit_literal_22(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_tk_v(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _tmp_temp2(%rip)
	movl	_tmp_temp2(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_tk_a(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_lit_literal_23(%rip), %eax
	movl	%eax, _tk_i(%rip)
	leaq	_lit_literal_24(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	_tmp_temp3(%rip), %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	_tmp_temp3(%rip), %eax
	movl	%eax, _tk_a(%rip)
	leaq	_lit_literal_25(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_tk_i(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
_label_temp0:
	movl	_tk_i(%rip), %edx
	movl	_lit_literal_28(%rip), %eax
	cmpl	%eax, %edx
	setl	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp7(%rip)
	movl	_tmp_temp7(%rip), %eax
	testl	%eax, %eax
	je	_label_temp1
	movl	_tk_i(%rip), %eax
	movl	_lit_literal_26(%rip), %edx
	addl	%edx, %eax
	movl	%eax, _tmp_temp4(%rip)
	movl	_tmp_temp4(%rip), %eax
	movl	%eax, _tk_i(%rip)
	movl	_tk_i(%rip), %eax
	movl	%eax, _tk_nn(%rip)
	movl	_lit_literal_27(%rip), %eax
	movl	%eax, _tk_xa(%rip)
	call	_tk_incn
	movl	%eax, _tmp_temp5(%rip)
	movl	_tmp_temp5(%rip), %eax
	movl	%eax, _tk_i(%rip)
	movl	_tk_a(%rip), %eax
	movl	%eax, _tk_nn(%rip)
	movl	_tk_a(%rip), %eax
	movl	%eax, _tk_xa(%rip)
	call	_tk_incn
	movl	%eax, _tmp_temp6(%rip)
	movl	_tmp_temp6(%rip), %eax
	movl	%eax, _tk_a(%rip)
	jmp _label_temp0
_label_temp1:
	leaq	_lit_literal_29(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_lit_literal_30(%rip), %eax
	movl	_tk_a(%rip), %edx
	addl	%edx, %eax
	movl	%eax, _tmp_temp8(%rip)
	movl	_tmp_temp8(%rip), %eax
	movl	_lit_literal_31(%rip), %edx
	imull	%edx, %eax
	movl	%eax, _tmp_temp9(%rip)
	movl	_tmp_temp9(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	_lit_literal_32(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_tk_a(%rip), %edx
	movl	_lit_literal_35(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp11(%rip)
	movl	_tmp_temp11(%rip), %eax
	testl	%eax, %eax
	je	_label_temp2
	movl	_tk_a(%rip), %eax
	movl	_lit_literal_33(%rip), %edx
	addl	%edx, %eax
	movl	%eax, _tmp_temp10(%rip)
	movl	_tmp_temp10(%rip), %eax
	movl	%eax, _tk_a(%rip)
	leaq	_lit_literal_34(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
_label_temp2:
	movl	_tk_i(%rip), %edx
	movl	_lit_literal_38(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp12(%rip)
	movl	_tmp_temp12(%rip), %eax
	testl	%eax, %eax
	je	_label_temp3
	leaq	_lit_literal_36(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp _label_temp4
_label_temp3:
	leaq	_lit_literal_37(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
_label_temp4:
	popq	%rbp
	ret
	.cfi_endproc
	.size main	, .-main
