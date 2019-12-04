DEFAULT REL

%define SIZE_TAB 256

section .bss
	S: resb SIZE_TAB

section .text
	global _rc4

;void		rc4(const void *key, int size_key, char *plain, int plain_len)
_rc4:
	push rdi
	push rsi
	push rdx
	push rcx

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
		cmp rcx, SIZE_TAB
		jne .init_tab

;fill permutation with key
	xor rcx, rcx
	xor r10, r10
	mov r11, rdx
	mov r15, SIZE_TAB
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
		cmp rcx, SIZE_TAB
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
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	ret
