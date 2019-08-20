%define SYS_WRITE 0x2000004
%define SYS_READ 0x2000003

%define BUFF_SIZE 4096

section .bss
    buff: resb BUFF_SIZE

section .text
    global _ft_cat

_ft_cat:
    push rdi
    mov r14, rdi

loop_start:
    mov rdi, r14
    lea rsi, [rel buff]
    mov r13, rsi
    mov rdx, BUFF_SIZE
    mov rax, SYS_READ
    syscall

    mov r15, rax
    mov rdx, rax
    mov rax, SYS_WRITE
    mov rdi, 1
    mov rsi, r13
    syscall

    cmp rax, byte -1
    je end

    cmp r15, byte 0
    jg loop_start

end:
    pop rdi
    ret