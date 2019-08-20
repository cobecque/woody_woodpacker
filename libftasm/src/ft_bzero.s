DEFAULT REL

section .text
    global _ft_bzero

_ft_bzero:
    push rsi
    push rdi

loop_start:

    cmp rsi, 0
    jle end_loop
    sub rsi, 1
    mov [rdi], byte 0
    add rdi, 1
    jmp loop_start

end_loop:

    pop rdi
    pop rsi
    ret
