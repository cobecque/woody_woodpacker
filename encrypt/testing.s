%define SYS_WRITE 0x2000004

section .data
	key: db "key"
	plain: db "testing"
	message: db "....WOODY....", 0x0a
	len equ $ - message

section .text
	extern _rc4
	global _baseDecrypt

_baseDecrypt:
	push rdi
	push rsi
	push rdx
	push rcx

	lea rdi, [plain]
	lea rsi, [key]
	mov rdx, 10
	mov rcx, 100
	call _rc4

	pop rcx
	pop rdx
	pop rsi
	pop rdi

writeWoody:
	push rsi
	push rdx
	push rax
	push rdi

	lea rsi, [message]
	mov rdx, len
	mov rax, SYS_WRITE
	mov rdi, 1
	syscall

	pop rdi
	pop rax
	pop rdx
	pop rsi
	ret
