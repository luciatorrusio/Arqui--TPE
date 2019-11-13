GLOBAL write

section .text:

write:
    enter 0,0
    mov rax,1
    mov rbx,rdi
    mov rcx,rsi
    int 80h

    leave
    ret


