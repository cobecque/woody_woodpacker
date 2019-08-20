DEFAULT REL

section .text
    global _ft_strdup
    extern _ft_strlen
    extern _malloc

_ft_strdup:
    push rdi

    mov r12, rdi
    call _ft_strlen
    cmp rax, 0
    je end

    inc rax
    mov r15, rax
    mov rdi, rax
    call _malloc
    cmp rax, 0
    je end

    mov rcx, r15
    mov rdi, rax
    mov rsi, r12
    mov r9, rdi
    rep movsb
    mov rax, r9

end:
    
    pop rdi
    ret
