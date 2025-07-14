.section .init
.global _init
.type _init, @function
_init:
	pushl %ebp
	movl %esp, %ebp
	/* gcc will nicely put the contents of crtbegin.o's .init section here. */

.section .fini
.global _fini
.type _fini, @function
_fini:
	pushl %ebp
	movl %esp, %ebp
	/* gcc will nicely put the contents of crtbegin.o's .fini section here. */
/* x86 crtn.s */
.section .init
	/* gcc will nicely put the contents of crtend.o's .init section here. */
	popl %ebp
	ret

.section .fini
	/* gcc will nicely put the contents of crtend.o's .fini section here. */
	popl %ebp
	ret