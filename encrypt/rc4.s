DEFAULT REL

%define SIZE_TAB 256

section .bss
	S: resb SIZE_TAB

section .text
	global _rc4

;char	*rc4(const char *plain, const void *key, int size_key, int text_len, uint8_t *dst)

;initialisation of variable
_rc4:
	push rdi
	push rsi
	push rdx
	push rcx
	push r8

	mov r10, rcx					;save len in r10
	mov r12, rdx					;save size in r12
	mov rcx, 0						;init idx
	lea rbx, [rel S]
	xor r15, r15
	mov r15, rdi

initialisation:
;init permutation table s[256]
; for int i < 256 i++
;	s[i] = i
	.init_tab:
	mov [rbx + rcx], rcx
	inc rcx
	cmp rcx, SIZE_TAB
	jne .init_tab

;permutation table fill with key
;r8b = j
;r12= size
	xor rcx, rcx
	xor r8, r8						;clear garbage
	mov r9, SIZE_TAB
	.fill_table:
		add r8b, [rbx + rcx]			;j + S(i)
		xor rdx, rdx					;clear garbage
		mov rax, rcx
		idiv r12						;rdx = i % size
		add r8b, [rsi + rdx]			;j += key[i % size]
		mov al, r8b
		idiv r9
		xor r8, r8
		mov r8b, dl						;j % SIZE_TAB

		;SWAP
		mov rdx, [rbx + r8]
		mov r11b, [rbx + rcx]			;save S(i) in r11
		mov [rbx + rcx], dl				;S(i) = S(j)
		mov [rbx + r8], r11b			;S(j) = r11

		inc rcx
		cmp rcx, SIZE_TAB
		jne .fill_table					;jump on fill_table

;r10 = len
;r14 = idx
		xor r8, r8
		xor r14, r14
		xor rcx, rcx				;clear garbage
		mov r9, SIZE_TAB
		.algo:
			inc rcx
			xor rdx, rdx
			mov rax, rcx
			idiv r9
			mov rcx, rdx				;(i + 1) % SIZE_TAB

			add r8b, [rbx + rcx]		;j += S(i)
			xor rdx, rdx
			mov al, r8b
			idiv r9
			mov r8b, dl					;j % SIZE_TAB

			;SWAP
			mov rdx, [rbx + r8]				;rdx = S(j)
			mov r11b, [rbx + rcx]			;save S(i) in r11
			mov [rbx + rcx], dl				;S(i) = S(j)
			mov [rbx + r8], r11b			;S(j) = r11

			mov r13, [rbx + r8]				;r13 = S(j)
			add r13, [rbx + rcx]			;S(j) + S(i)
			xor rdx, rdx
			mov al, r13b
			idiv r9							;(S(i) + S(j)) % SIZE_TAB
			xor r13, r13
			mov r13b, dl
			mov r13b, [rbx + r13]			;cyph_byte
			;jmp end

			xor r13b, [rdi]
			mov [rdi], r13b
			;jmp end

			inc rdi
			;inc r8
			mov r11b, [rdi]
			cmp r11b, 0
			;jmp end
			;inc r14
			;cmp r14, r10					;fin de condition
			jne .algo

end:
	mov rax, r15
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	ret
