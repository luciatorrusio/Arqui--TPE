GLOBAL read

section .text:

read:
    enter 0,0

    
    mov rax, rdi  ; FD
    mov rbx,rsi ; 
    mov rcx,rdx ; 

    int 80h

    leave
    ret

