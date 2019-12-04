DEFAULT REL

section .text
	global _decode_rc4:function
	global SIZE_RC4:data
	global _decode_data:data

	SIZE_RC4 dd _decode_data - _decode_rc4

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
	push r9
	push r10
	push r11
	push r12
	push r13
	push r15

	lea rdi, [key]
	lea rsi, [key_size]
	lea rdx, [cyph_addr]
	lea rcx, [cyph_size]

;void		rc4(const void *key, int size_key, char *plain, int plain_len)
startRc4:
	S: resb 256			;tab

	mov r9, rcx			;save len in r9
	lea rbx, [REL S]

initalisation:
;init permutation table s[256]
; for int i < 256 i++
;	s[i] = i
	xor rcx, rcx		;clear garbage
	.init_tab:
		mov [rbx + rcx], rcx
		inc rcx
		cmp rcx, 256
		jne .init_tab

;fill permutation with key
	xor rcx, rcx
	xor r10, r10
	mov r11, rdx
	mov r15, 256
	.fill_table:
		add r10b, [rbx + rcx]			;j + S(i)
		xor rdx, rdx
		mov rax, rcx
		idiv rsi						;rdx = i % size
		add r10b, [rdi + rdx]			;j += key[i % size]
		mov al, r10b
		idiv r15
		xor r10, r10
		mov r10b, dl					;j % SIZE_TAB

		;SWAP
		mov rdx, [rbx + r10]			;save S(j) in rdx
		mov r12b, [rbx + rcx]			;save S(i) in r12
		mov [rbx + rcx], dl				;S(i) = S(j)
		mov [rbx + r10], r12b			;S(i) = S(j)

		inc rcx
		cmp rcx, 256
		jne .fill_table

algo:
	mov rax, r11
	xor rcx, rcx
	xor r10, r10
	xor r12, r12
	xor r13, r13
	.loop:
		;r10 = i
		;i = (i + 1) % SIZE_TAB
		inc r10
		xor rdx, rdx
		mov rax, r10
		idiv r15
		mov r10, rdx

		;r12 = j
		;j = j + s(i) % SIZE_TAB
		add r12b, [rbx + r10]
		xor rdx, rdx
		mov al, r12b
		idiv r15
		mov r12b, dl

		;SWAP
		mov rdx, [rbx + r12]
		mov r13b, [rbx + r10]
		mov [rbx + r10], dl
		mov [rbx + r12], r13b

		;CYPHER BYTE
		xor r13, r13
		mov r13, [rbx + r12]
		add r13, [rbx + r10]
		xor rdx, rdx
		mov al, r13b
		idiv r15
		xor r13, r13
		mov r13b, dl
		mov r13b, [rbx + r13]

		;ENCODE
		xor [r11], r13b
		inc r11

		inc rcx
		cmp rcx, r9
		jne .loop

end:
	pop r15
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	ret
	mov rdx, 1

_decode_data:
	key: resb 16
	key_size: dd 0
	message: resb 14
	cyph_addr: dq 0
	cyph_size: dd 0
