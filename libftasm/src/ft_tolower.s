DEFAULT REL

section .text
    global _ft_tolower

_ft_tolower:
    push rdi
    cmp rdi, byte 65
    jl not_upper
    cmp rdi, byte 90
    jg not_upper
    add rdi, byte 32
    mov rax, rdi
    pop rdi
    ret

not_upper:
    pop rdi
    mov rax, rdi
    ret