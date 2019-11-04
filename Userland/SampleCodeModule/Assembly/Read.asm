GLOBAL read1

section .text:

read1:
    enter 0,0

    
    mov rax, 3  ; ID Read
    mov rbx,rdi ; file descriptor
    mov rcx,rsi ; puntero Buffer
    mov rdx,rdx ; Tama;o buffer
    int 80h

    leave
    ret

