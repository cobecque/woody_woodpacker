DEFAULT REL

section .text
    global _ft_isdigit

_ft_isdigit:
    push rdi

    cmp rdi, byte 48
    jl not_digit
    cmp rdi, byte 57
    jg not_digit
    mov rax, 1
    pop rdi
    ret

not_digit:
    mov rax, 0
    pop rdi
    ret