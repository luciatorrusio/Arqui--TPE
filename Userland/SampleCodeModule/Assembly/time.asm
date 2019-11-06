GLOBAL __time__


section .text

__time__:
        enter 0,0
        mov rbx,rsi ; puntero a int para devolver
        mov rax,rdi ; id de time
        int 82h
        
        leave
        ret