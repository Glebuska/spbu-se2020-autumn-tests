	.file	"sort.c"
	.text
	.p2align 4
	.globl	sort
	.type	sort, @function
sort:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movslq	%esi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$416, %rsp
	.cfi_def_cfa_offset 448
	movq	%fs:40, %rax
	movq	%rax, 408(%rsp)
	xorl	%eax, %eax
	testl	%r12d, %r12d
	jle	.L14
	movq	%rsp, %r10
	leal	-1(%r12), %eax
	movq	%rdi, %rbp
	movq	%rdi, %rsi
	leaq	4(,%rax,4), %rdx
	movq	%r10, %rdi
	movq	%rax, %rbx
	call	memcpy@PLT
	movl	%ebx, %edx
	xorl	%r9d, %r9d
	leaq	4(%rbp), %r11
	movq	%rax, %r10
	leaq	-4(,%r12,4), %r8
	.p2align 4,,10
	.p2align 3
.L3:
	testl	%edx, %edx
	je	.L25
.L8:
	subl	$1, %edx
	movq	%rbp, %rax
	movq	%rdx, %rdi
	leaq	(%r11,%rdx,4), %rsi
	.p2align 4,,10
	.p2align 3
.L5:
	movl	(%rax), %edx
	movl	4(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L4
	movl	%ecx, (%rax)
	movl	%edx, 4(%rax)
.L4:
	addq	$4, %rax
	cmpq	%rax, %rsi
	jne	.L5
	movl	(%r10,%r8), %eax
	cmpl	%eax, 0(%rbp,%r8)
	je	.L26
.L11:
	addl	$1, %r9d
.L7:
	movl	%edi, %edx
	subq	$4, %r8
	cmpl	$-1, %edi
	jne	.L3
.L1:
	movq	408(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L27
	addq	$416, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	movl	%r9d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L26:
	.cfi_restore_state
	movl	%edi, %edx
	subq	$4, %r8
	testl	%edx, %edx
	jne	.L8
.L25:
	movl	(%r10,%r8), %eax
	movl	$-1, %edi
	cmpl	%eax, 0(%rbp,%r8)
	jne	.L11
	jmp	.L7
.L14:
	xorl	%r9d, %r9d
	jmp	.L1
.L27:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE0:
	.size	sort, .-sort
	.ident	"GCC: (Ubuntu 9.3.0-10ubuntu2) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
