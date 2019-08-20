%define SYS_WRITE 0x2000004

section .text
    global _ft_strncmp

_ft_strncmp:
    
    push rcx
    
    xor rcx, rcx
    mov rax, 0

loop:

    cmp rdx, 0
    je end

    mov r9, rdi
    mov al, [rel rdi + rcx]
    sub al, [rel rsi + rcx]
   
    mov rdi, r9
    cmp byte [rel rdi + rcx], 0
    je end    

    cmp al, 0
    jl sub

continue:

    cmp al, 0
    jne end

    inc rcx
    dec rdx

    jmp loop

sub:
    sub rax, 256

end:
    pop rcx
    ret