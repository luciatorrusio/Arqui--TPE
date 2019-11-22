GLOBAL cpuVendor

GLOBAL raxRegister
GLOBAL rbxRegister
GLOBAL rcxRegister
GLOBAL rdxRegister
GLOBAL rdiRegister
GLOBAL rsiRegister
GLOBAL r8Register
GLOBAL r9Register
GLOBAL r10Register
GLOBAL r11Register
GLOBAL r12Register
GLOBAL r13Register
GLOBAL r14Register
GLOBAL r15Register
GLOBAL ipRegister

GLOBAL WritePITConfiguration
GLOBAL WritePIT2Data
GLOBAL ReadSpeakerData
GLOBAL WriteSpeakerData

section .text

WritePITConfiguration:
	enter 0,0

	mov rax,rdi

	out 43h,al

	leave
	ret

WritePIT2Data:
	enter 0,0

	mov rax,rdi

	out 42h,al

	leave
	ret

ReadSpeakerData:
	enter 0,0

	mov rax,0

	in al,61h


	leave
	ret

WriteSpeakerData:
	enter 0,0

	mov rax,rdi

	out 61h,al

	leave
	ret


	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx


	mov rsp, rbp
	pop rbp
	ret




raxRegister: 
	enter 0,0

	mov rax, rax ; pasaje de parametro
	leave
	ret

rbxRegister: 
	enter 0,0

	mov rax, rbx ; pasaje de parametro
	leave
	ret

rcxRegister: 
	enter 0,0

	mov rax, rcx ; pasaje de parametro
	leave
	ret

rdxRegister: 
	enter 0,0

	mov rax, rdx ; pasaje de parametro
	leave
	ret

rdiRegister: 
	enter 0,0

	mov rax, rdi ; pasaje de parametro
	leave
	ret

rsiRegister: 
	enter 0,0

	mov rax, rsi ; pasaje de parametro
	leave
	ret

r8Register: 
	enter 0,0

	mov rax, r8 ; pasaje de parametro
	leave
	ret

r9Register: 
	enter 0,0

	mov rax, r9 ; pasaje de parametro
	leave
	ret

r10Register: 
	enter 0,0

	mov rax, r10 ; pasaje de parametro
	leave
	ret

r11Register: 
	enter 0,0

	mov rax, r11 ; pasaje de parametro
	leave
	ret

r12Register: 
	enter 0,0

	mov rax, r12 ; pasaje de parametro
	leave
	ret

r13Register: 
	enter 0,0

	mov rax, r13 ; pasaje de parametro
	leave
	ret

r14Register: 
	enter 0,0

	mov rax, r14 ; pasaje de parametro
	leave
	ret

r15Register: 
	enter 0,0

	mov rax, r15 ; pasaje de parametro
	leave
	ret

ipRegister: 
	enter 0,0
	call address
address:
	pop rax
	leave
	ret