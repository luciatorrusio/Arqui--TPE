GLOBAL write
GLOBAL writeColor

section .text:

write:
    enter 0,0
    mov rax,1
    mov rbx,rdi
    mov rcx,rsi
    int 80h

    leave
    ret

writeColor:
    enter 0,0
    mov rax,4
    mov rbx,rdi
    int 80h

    leave
    ret

