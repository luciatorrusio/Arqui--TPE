GLOBAL CreateCustomException



section .text

CreateCustomException:

    enter 0,0

    mov rax, rdi
    int 01h

    leave
    ret