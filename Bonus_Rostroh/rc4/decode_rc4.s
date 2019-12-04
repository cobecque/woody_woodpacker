DEFAULT REL

section .data
	message: db "....WOODY....", 0x0a
	len equ $ - message

section .text
	global _decode_rc4:function
	global SIZE_RC4:data
	global _decode_data:data
	extern _rc4

	SIZE_RC4 dd _decode_rc4 - _decode_data

_decode_rc4:

writeWoody:
	push rdi
	push rsi
	push rdx
	push rax

	lea rsi, [message]
	mov rdx, 0x0e			;size msg
	mov rax, 1				;syscall write
	mov rdi, 1
	syscall

	pop rax
	pop rdx
	pop rsi
	pop rdi

;void		decode_rc4(const void *key, int key_len)
;void		rc4(const void *key, int key_len, char *plain, int plain_len)
decode:
	push rdi
	push rsi
	push rdx
	push rcx

	lea rdx, [addr]
	lea rcx, [size]
	call _rc4

end:
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	ret

_decode_data:
	addr: dq 0
	size: dd 0
