GLOBAL printAt

section .text:

printAt:
    enter 0,0
    
    mov rax,1       ; ID
    mov rbx,rdi     ; pos
    mov r9,rcx      ;fontColor
    mov rcx,rsi     ;  length
    mov rdx,rdx     ;  height
    ;mov r8,r8       ;fontColor
    
    int 83h

    leave
    ret

 