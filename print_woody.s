DEFAULT REL
%define SYS_WRITE 0x2000004

section .data
	text: db "abc"

section .text
	global _main

_main:
	lea rsi, [text]
	mov rdx, 0x1
	mov rax, 0x1
	mov rdi, 0x3
	syscall
	ret
