GLOBAL __GETREGISTERS__
GLOBAL __executeCodeFromAddress__

section .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15

%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro




__executeCodeFromAddress__:

		enter 0,0

		jmp rdi

		leave
		ret



__GETREGISTERS__:

        enter 0,0
		pushState ; Es feo esto
        mov rcx,rsp

        mov rdx,0
        mov rcx,rcx
        mov rbx, rdi    ; Puntero a la struct
        mov rax,0x07
        int 0x80

        leave
        ret

