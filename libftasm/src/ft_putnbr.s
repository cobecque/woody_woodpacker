;DEFAULT REL

%define SYS_WRITE 0x2000004
%define BUFF_SIZE 11 

section .data
    negativ: db "-"

section .bss
    buff: resb BUFF_SIZE

section .text
    global _ft_putnbr
    extern _ft_bzero

_ft_putnbr:

    push rbp

    lea r9, [rel buff]

    mov r12, BUFF_SIZE

    mov r10, rdi
    mov rdi, r9
    mov rsi, BUFF_SIZE
    call _ft_bzero

    
    mov rdi, r10
    mov eax, edi
    cmp edi, 0
    jl neg
    

calc:
    mov eax, edi
    mov ecx, 10
    mov edx, 0

    idiv ecx

    mov edi, eax
    lea r9, [rel buff]

    add r9, r12
    mov byte [r9], "0"

    mov r14, rax

add:
    add byte [r9], dl
    
loop:
    mov rax, r14
    dec r12
    cmp eax, 0
    je print
    jmp calc

print:
    inc r12
   
    lea rsi, [rel buff]
    add rsi, r12

    mov rdx, BUFF_SIZE
    sub rdx, r12
    inc rdx
    mov rax, SYS_WRITE
    mov rdi, 1
    syscall
    jmp end
    
neg:
    mov r15, rdi

    lea rsi, [rel negativ]
    mov rdx, 1
    mov rdi, 1
    mov rax, SYS_WRITE
    syscall

    mov rdi, r15
    neg edi
    jmp calc

end:
    pop rbp
    ret