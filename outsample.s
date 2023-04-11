.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"%s"
	.data
_tk_verde:
	.byte	1
_tk_aaa:
	.long	1
_tk_i:
	.long	0
_tk_cachorrao:
	.long	1
_tk_outra:
	.byte	s
_tk_vect:
	.long	7
	.long	34
	.long	2
	.long	1
	.long	0
	.long	0
	.long	0
_tk_ope:
	.long	4
	.long	3
	.long	2
	.long	1
_tk_xxxx:
	.globl	_tk_caaa
	.type	_tk_caaa, @function
	_tk_caaa:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	popq	%rbp
	ret
	.cfi_endproc
_tk_tes:
_tk_vac:
	.globl	_tk_fun1c
	.type	_tk_fun1c, @function
	_tk_fun1c:
	.cfi_startproc
	pushq	%rbp
	movq	%rsp, %rbp
	leaq	_lit_literal_15(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_tk_aaa(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_lit_literal_16(%rip), %eax
	movl	_tk_i(%rip), %edx
	addl	%edx, %eax
	movl	%eax, _tmp_temp0(%rip)
	movl	_tmp_temp0(%rip), %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	_lit_literal_18(%rip), %edx
	movl	_lit_literal_19(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp1(%rip)
	movl	_lit_literal_20(%rip), %edx
	movl	_lit_literal_21(%rip), %eax
	cmpl	%eax, %edx
	setg	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp2(%rip)
	movl	_tmp_temp1(%rip), %edx
	movl	_tmp_temp2(%rip), %eax
	addl	%eax, %edx
	cmpl	$2, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp3(%rip)
	movl	_tmp_temp3(%rip), %eax
	testl%eax, %eax
	je	_label_temp0
	movl	_lit_literal_17(%rip), %eax
	movl	%eax, _lit_literal_17(%rip)
_label_temp0:
	movl	_lit_literal_24(%rip), %edx
	movl	_tk_aaa(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp4(%rip)
	movl	_tmp_temp4(%rip), %eax
	testl%eax, %eax
	je	_label_temp1
	movzbl	_lit_literal_22(%rip), %eax
	movb	%al, _lit_literal_22(%rip)
	jmp _label_temp2
_label_temp1:
	movl	_lit_literal_23(%rip), %eax
	movl	%eax, _lit_literal_23(%rip)
_label_temp2:
_label_temp3:
	movl	_lit_literal_30(%rip), %edx
	movl	_lit_literal_31(%rip), %eax
	cmpl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp9(%rip)
	movl	_tmp_temp9(%rip), %eax
	testl%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _tmp_temp10(%rip)
	movl	_tmp_temp10(%rip), %eax
	testl%eax, %eax
	je	_label_temp4
	movl	_tk_i(%rip), %eax
	movl	_lit_literal_25(%rip), %edx
	addl	%edx, %eax
	movl	%eax, _tmp_temp5(%rip)
	movl	_tmp_temp5(%rip), %eax
	movl	_lit_literal_26(%rip), %edx
	addl	%edx, %eax
	movl	%eax, _tmp_temp6(%rip)
	movl	_tmp_temp6(%rip), %eax
	movl	_lit_literal_27(%rip), %edx
	imull	%edx, %eax
	movl	%eax, _tmp_temp7(%rip)
	movl	_tmp_temp7(%rip), %eax
	movl	%eax, _tmp_temp7(%rip)
	movl	_lit_literal_28(%rip), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	_tk_vect(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, _tmp_temp8(%rip)
	movl	_tmp_temp8(%rip), %eax
	movl	%eax, _tmp_temp8(%rip)
	movq	_lit_literal_29(%rip), %rdx
	leaq	0(,%rdx,4), %rcx
	movl	_tk_cachorrao(%rip), %eax
	leaq	_tk_vect(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	jmp _label_temp3
_label_temp4:
	movq	_lit_literal_32(%rip), %rdx
	leaq	0(,%rdx,4), %rcx
	movl	_lit_literal_33(%rip), %eax
	leaq	_tk_vect(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	_tk_aaa(%rip), %eax
	movl	%eax, _tk_aaa(%rip)
	call	_tmp_temp11
	movl	_tmp_temp11(%rip), %eax
	movl	%eax, _tmp_temp11(%rip)
	popq	%rbp
	ret
	.cfi_endproc
