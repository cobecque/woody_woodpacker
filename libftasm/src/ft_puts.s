DEFAULT REL
%define SYS_WRITE 0x2000004

section .data
	nl: db 0x0A

section .text
	global _ft_puts
	extern _ft_strlen

_ft_puts:

	push rdi
	
	mov rsi, rdi
	call _ft_strlen
	mov rdx, rax
	mov rax, SYS_WRITE
	mov rdi, 1
	syscall

	lea rsi, [nl]
	mov rdx, 1
	mov rax, SYS_WRITE
	mov rdi, 1
	syscall

	pop rdi
	ret
