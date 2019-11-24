GLOBAL delete


section .text:

delete:
        enter 0,0

        mov rax,rdi
        int 82h

        leave
        ret