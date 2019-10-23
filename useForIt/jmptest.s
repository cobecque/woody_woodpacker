DEFAULT REL
%define SYS_WRITE 0x2000004

section .data
	message: db "....WOODY....", 0x0a
	len equ $ - message

section .text
	global start
	global _main

start:
	call _main
	ret

_main:
	push rdx
	lea rsi, [message]
	mov r12, rsi
	mov rdx, len
	mov rax, SYS_WRITE
	mov rdi, 1
	syscall
	pop rdx
	ret
