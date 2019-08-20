DEFAULT REL

section .text
    global _ft_isprint

_ft_isprint:

    push rdi
    cmp rdi, 32
    jl not_print
    cmp rdi, 126
    jg not_print
    mov rax, 1
    pop rdi
    ret

not_print:
    mov rax, 0
    pop rdi
    ret