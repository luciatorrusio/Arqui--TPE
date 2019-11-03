GLOBAL write
GLOBAL writeAt

section .text:

write:
    enter 0,0
    mov rax,rdi
    mov rbx,rsi
    int 80h

    leave
    ret

writeAt:
    enter 0,0
    mov rax,rdi
    mov rbx,rsi
    mov rcx,rdx
    int 81h

    leave
    ret
