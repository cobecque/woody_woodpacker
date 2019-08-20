DEFAULT REL

section .text
    global _ft_toupper

_ft_toupper:
    push rdi
    cmp rdi, 97
    jl not_lower
    cmp rdi, 122
    jg not_lower
    sub rdi, byte 32
    mov rax, rdi
    pop rdi
    ret

not_lower:
    mov rax, rdi
    pop rdi
    ret