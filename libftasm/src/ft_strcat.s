DEFAULT REL

section .text
    global _ft_strcat
    extern _ft_strlen

_ft_strcat:
    push rsi
    push rdi
    mov rdx, rdi
    call _ft_strlen
    cmp rax, 0
    jle end
	mov rdi, rdx

loop_string:
    dec rax
    inc rdi
    cmp rax, 0
    jg loop_string

string2:
    mov r9, rdi
    mov rdi, rsi
    call _ft_strlen
    mov rdi, r9
    mov rcx, rax
    inc rcx

loop_s2:
    rep movsb

end:
    mov rax, rdx
    pop rdi
    pop rsi
    ret