section .text
    global _ft_memalloc
    extern _ft_bzero
    extern _malloc

_ft_memalloc:
    push rdi

    mov rax, 0
    cmp rdi, 0
    jle end

    mov r15, rdi
    
    call _malloc
    cmp rax, 0
    jle end

    mov r9, rax
    mov rdi, rax
    mov rsi, r15
    call _ft_bzero
    mov rax, r9

end:
    pop rdi
    ret