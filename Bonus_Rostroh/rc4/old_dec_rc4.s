DEFAULT REL

section .text
	extern _rc4
	global _decode_rc4

;void		rc4(const void *key, int key_size, char *plain, int plain_len)
;void		decode_rc4(const void *key, int size_key, uint32_t *addr_tab, int *size_entry, int nb_entry)

;initalisation
_decode_rc4:
	push rdi
	push rsi
	push rdx
	push rcx
	push r8
	push r9

	xor r9, r9			;loop idx

loop:
	call _rc4
	inc r9
	cmp r9, r8
	jne inc_data
	jmp end

inc_data:
	inc rdx
	inc rcx
	jmp loop

end:
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	ret
