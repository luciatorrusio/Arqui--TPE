GLOBAL __READMEM__
GLOBAL __GETREGISTERS__
GLOBAL __GETBPP__
GLOBAL __SETBPP__
GLOBAL __GETCHARH__
GLOBAL __GETCHARW__

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

		pushState ; Es feo esto
        mov rcx,rsp

        mov rdx,0
        mov rcx,rcx
        mov rbx, rdi    ; Puntero a la struct
        mov rax,0x2
        int 0x81

        leave
        ret

__GETBPP__:

        enter 0,0

		mov rbx,rdi
        mov rax,0x3
        int 0x81

        leave
        ret

__SETBPP__:

        enter 0,0

		mov rbx,rdi
        mov rax,0x4
        int 0x81

        leave
        ret

__GETCHARH__:

        enter 0,0

		mov rbx,rdi
        mov rax,0x5
        int 0x81

        leave
        ret

__GETCHARW__:

        enter 0,0

		mov rbx,rdi
        mov rax,0x6
        int 0x81

        leave
        ret
