GLOBAL printAt

section .text:

printAt:
    enter 0,0
    
    ; mov rax,1       ; ID
    ; mov rbx,rdi     ; pos
    ; mov r9,rcx      ;fontColor
    ; mov rcx,rsi     ;  length
    ; mov rdx,rdx     ;  height
    ; ;mov r8,r8       ;fontColor

    mov r15, rdx

    mov r9,  r8    ; heght 
    mov rdx, rcx    ; lenght 
    mov rcx, r15    ; pos 
    mov rbx, rsi   ; FD
    mov rax,rdi       ; FD
    
    int 81h

    leave
    ret

 