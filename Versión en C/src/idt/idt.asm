section .asm

extern int21h_handler
extern no_interrumpt_handler

global int21h
global idt_load
global no_interrumpt

idt_load:
	push ebp
	mov ebp, esp
	
	mov ebx, [ebp + 8]
	lidt [ebx]
	pop ebp
	ret

int21h:
	cli
	pushad
	call int21h_handler
	popad
	sti
	iret
	
no_interrumpt:
	cli
	pushad
	call no_interrumpt_handler
	popad
	sti
	iret
