section .text
    global _ft_strndup
    extern _ft_strlen
    extern _malloc

_ft_strndup:
    push rdi

    mov r12, rdi
    mov r14, rsi
    call _ft_strlen
    cmp rax, 0
    je end

    inc rax
    mov r15, r14
    sub r14, rax

    mov rdi, r15
    call _malloc
    cmp rax, 0
    je end

continue:
    mov rcx, r15
    mov rdi, rax
    mov rsi, r12
    mov r9, rdi
    rep movsb
    lea rax, [rel r9]
    jmp end

end:
    pop rdi
    ret