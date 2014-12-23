	.file	"strpbrktest.c"
	.section	.rodata
.LC0:
	.string	"Find all vowels"
.LC1:
	.string	"aeiouAEIOU"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$.LC0, 28(%esp)
	jmp	.L2
.L3:
	movl	28(%esp), %eax
	movl	%eax, (%esp)
	call	puts
	movl	28(%esp), %eax
	addl	$1, %eax
	movl	$.LC1, 4(%esp)
	movl	%eax, (%esp)
	call	strpbrk
	movl	%eax, 28(%esp)
.L2:
	cmpl	$0, 28(%esp)
	jne	.L3
	movl	$0, (%esp)
	call	exit
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
