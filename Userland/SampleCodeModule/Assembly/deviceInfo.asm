GLOBAL getRegisters
GLOBAL __UD2__


EXTERN recoverRegisters

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




__UD2__:

		enter 0,0

		ud2

		leave
		ret



getRegisters:

        enter 0,0

		; mov rax, 10
		; mov rbx, 11
		; mov rcx, 12
		; mov rdx, 13
		; mov r15, 21
		; mov r14, 20
		; mov r13, 19
		; mov r12,18
		; mov r11,17
		; mov r10,16
		; mov r8,8
		; mov r9, 9
		; mov rdi, 255
		; mov rsi, 238

		pushState 
        mov rdi,rsp

		call recoverRegisters
        
        leave
        ret

