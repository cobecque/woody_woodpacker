DEFAULT REL

section .text
    global _ft_isalnum
    extern _ft_isalpha
    extern _ft_isdigit

_ft_isalnum:
    push rdi
    call _ft_isalpha
    cmp rax, 1
    je alnum
    call _ft_isdigit
    cmp rax, 1
    je alnum
    mov rax, 0
    pop rdi
    ret

alnum:
    mov rax, 1
    pop rdi
    ret