DEFAULT REL

section .text
    global _ft_memcpy

_ft_memcpy:
    push rdi
    push rsi
    push rdx

    mov rax, rdi
    mov rcx, rdx
    rep movsb

end:
    pop rdx
    pop rsi
    pop rdi
    ret