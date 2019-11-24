GLOBAL write
GLOBAL writeColor

section .text:

write:
    enter 0,0

    mov r15, rdx    ; guardo el valor

    mov r9, r8      ;cuarto arg
    mov rdx, rcx    ;tercer arg
    mov rcx, rdx    ;segundo arg
    mov rbx, rsi    ;primer arg
    mov rax, rdi    ; fd
    int 81h

    leave
    ret

writeColor:
    enter 0,0
    mov rax,4
    mov rbx,rdi
    int 80h

    leave
    ret

