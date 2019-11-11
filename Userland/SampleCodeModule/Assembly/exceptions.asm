GLOBAL ThrowCustomException


section .text

ThrowCustomException:

    enter 0,0

    mov rax, rdi
    int 85h

    leave
    ret