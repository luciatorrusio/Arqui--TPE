GLOBAL write
GLOBAL writeAt

section .text:

write:
    enter 0,0
    mov rax,1
    mov rbx,rdi
    mov rcx,rsi
    int 80h

    leave
    ret

writeAt:
    enter 0,0
    mov rax,2       ; ID
    mov rbx,rdi     ; FD
    mov rcx,rsi     ; char *
    mov rdx,rdx     ; pos
    int 80h

    leave
    ret
