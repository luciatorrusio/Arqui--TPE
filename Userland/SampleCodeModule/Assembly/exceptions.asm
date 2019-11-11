GLOBAL CreateCustomException



section .text

CreateCustomException:

    enter 0,0

    mov rax, rdi
    int 85h

    leave
    ret