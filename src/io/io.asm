[BITS 32]
section .asm

global insb
global insw
global outb
global outw
global outl
global inl

inl:
    push edx
    mov dx, [esp + 4]
    in eax, dx
    pop edx
    ret

insb:
    push edx
    mov dx, [esp+8]
    xor eax, eax
    in al, dx
    pop edx
    ret
    
insw:
    push edx
    mov dx, [esp+8]
    xor eax, eax
    in ax, dx
    pop edx
    ret

outb:
    push edx
    mov dx, [esp+8]
    mov al, [esp+12]
    out dx, al
    pop edx
    ret

outw:
    push edx
    mov dx, [esp+8]
    mov ax, [esp+12]
    out dx, ax
    pop edx
    ret
    
outl:
	out dx, eax
	ret
	

