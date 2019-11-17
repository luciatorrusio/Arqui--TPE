GLOBAL delete


section .text:

delete:
        enter 0,0

        mov rbx,rdi
        mov rax,2
        int 80h

        leave
        ret