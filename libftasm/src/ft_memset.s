DEFAULT REL

section .text
    global _ft_memset

_ft_memset:
    push rdi
    push rsi
    push rdx
    mov r9, rdi

loop_start:
    mov [rdi], rsi
    inc rdi
    dec rdx
    cmp rdx, 0
    jg loop_start
    mov rax, r9

end:
    pop rdx
    pop rsi
    pop rdi