GLOBAL printAt

section .text:

printAt:
    enter 0,0
    
    mov rax,1       ; ID
    mov rbx,rdi     ; x
    mov rcx,rsi     ; y
    mov rdx,rdx     ; lenght
    mov r9,rcx      ;height
    mov r8,r8;0xFFFFFFFF       ;fontColor
    int 83h

    leave
    ret

;irqHandlerMaster
;    mov r10,r8 ;sexto Param	
;	mov r9, r9 ; Quinto Param
;	mov r8, rdx ; Cuarto Param
;	mov rcx,rcx ; Tercer Param
;	mov rdx,rbx ; Segundo Param
;	mov rsi,rax ; Primer Param
;	mov rdi, %1 ; Tipo de Interrupcion
	

    
