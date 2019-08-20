DEFAULT REL

section .text
    global _ft_isalpha

_ft_isalpha:

    push rdi

    cmp rdi, byte 65
    jl not_alpha
    cmp rdi, byte 90
    jg lower_case
    pop rdi
    mov rax, 1
    ret

lower_case:
    cmp rdi, byte 97
    jl not_alpha
    cmp rdi, byte 122
    jg not_alpha
    mov rax, 1
    pop rdi
    ret

not_alpha:
    mov rax, 0
    pop rdi
    ret