DEFAULT REL
%define SYS_WRITE 0x2000004

section .text
	global _ft_strlen

_ft_strlen:

    mov rax, 0
    cmp rdi, byte 0
    je ret_error   
    sub rcx, rcx
    sub al, al
    not rcx
    repne scasb
    not rcx
    dec rcx
    mov rax, rcx
    ret

ret_error:
    mov rax, -1
    ret
