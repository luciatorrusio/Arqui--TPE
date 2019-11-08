GLOBAL printAt

section .text:

printAt:
    enter 0,0
    mov rax,1       ; ID
    mov rbx,rdi     ; x
    mov r9,rcx     ;height
    mov rcx,rsi     ; y
    mov rdx,rdx     ; lenght
    mov r8,r8       ;fontColor
   
    int 83h

    leave
    ret