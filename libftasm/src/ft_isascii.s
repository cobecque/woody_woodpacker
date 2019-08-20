DEFAULT REL

section .text
    global _ft_isascii

_ft_isascii:
    push rdi

    cmp rdi, byte 0
    jl not_ascii
    cmp rdi, byte 127
    jg not_ascii
    mov rax, 1
    pop rdi
    ret


not_ascii:
    pop rdi
    mov rax, 0
    ret