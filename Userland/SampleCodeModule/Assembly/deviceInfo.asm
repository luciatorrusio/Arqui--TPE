GLOBAL __READMEM__
GLOBAL __GETREGISTERS__




section .text

__READMEM__:

        enter 0,0
        
        mov rdx, rdx
        mov rcx,rsi
        mov rbx, rdi
        mov rax,0x1
        int 0x81

        leave
        ret





__GETREGISTERS__:

        enter 0,0

        mov rbx, rdi    ; Puntero a la struct
        mov rax,0x2
        int 0x81

        leave
        ret

