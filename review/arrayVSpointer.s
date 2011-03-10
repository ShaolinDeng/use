	.file	"arrayVSpointer.c"
	.section	.rodata
.LC0:
	.string	"1234"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$875770417, -13(%ebp)
	movb	$0, -9(%ebp)
	movl	$.LC0, -8(%ebp)
	movzbl	-12(%ebp), %eax
	movb	%al, -1(%ebp)
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movzbl	(%eax), %eax
	movb	%al, -1(%ebp)
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
