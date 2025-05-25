ORG 0x7c00
BITS 16

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

_start:
    jmp short start
    nop

start:
    jmp 0:step2

set_palette_color:
    push ax
    push dx
    push bx
    mov dx, 0x3C8     ; Puerto de índice de color
    out dx, al        ; Seleccionar el color a cambiar
    inc dx            ; 0x3C9 es el puerto de datos RGB
    mov al, dh        ; Rojo
    out dx, al
    mov al, dl        ; Verde
    out dx, al
    mov al, bl        ; Azul
    out dx, al
    pop bx
    pop dx
    pop ax
    ret

draw_rect:
    push ax
    push bx
    push cx
    push dx
    push si
    push di
    push bp

    mov bp, di        ; alto
    mov bx, dx        ; y inicial
    mov dx, cx        ; x inicial
    mov cl, al        ; color

draw_rect_y:
    push cx
    push dx

    mov cx, si        ; ancho
    mov ax, bx        ; y
    mov di, 320
    mul di            ; y * 320
    add ax, dx        ; + x
    mov di, ax

draw_rect_x:
    mov [es:di], cl
    inc di
    loop draw_rect_x

    pop dx
    pop cx
    inc bx
    dec bp
    jnz draw_rect_y

    pop bp
    pop di
    pop si
    pop dx
    pop cx
    pop bx
    pop ax
    ret

step2:
    cli
    mov ax, 0xA000
    mov es, ax
    mov ax, 0x0000
    mov ds, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    ; Establecer modo gráfico 320x200x256 colores
    mov ax, 0x0013
    int 0x10

    ; Configurar color amarillo (índice 40)
    mov al, 40        ; Índice de color personalizado
    mov dh, 63        ; Rojo máximo
    mov dl, 40        ; Verde reducido (para evitar dominancia)
    mov bl, 0         ; Azul cero
    call set_palette_color

    ; Dibujar botón amarillo con tamaño adecuado
    mov cx, 100       ; Coordenada X (centrado horizontalmente: (320-120)/2)
    mov dx, 170        ; Coordenada Y (centrado verticalmente: (200-30)/2)
    mov si, 120       ; Ancho del botón
    mov di, 30        ; Alto del botón
    mov al, 40        ; Índice de color amarillo
    call draw_rect

    ; Mostrar mensaje con int 10h
    mov si, imprimir
        
.print_char:
    lodsb
    cmp al, 0
    je .done_print
    mov ah, 0x0E
    int 0x10
    jmp .print_char
.done_print:

.load_protected:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:load32
    
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0
    db 0
    db 0x9a
    db 11001111b
    db 0

gdt_data:
    dw 0xffff
    dw 0
    db 0
    db 0x92
    db 11001111b
    db 0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

%include "./src/boot/data.asm"

[BITS 32]
load32:
    in al, 0x92
    or al, 2
    out 0x92, al

    ; CARGAR EL KERNEL
    mov eax, 1
    mov ecx, 100
    mov edi, 0x0100000
    call ata_lba_read
    jmp CODE_SEG:0x0100000

ata_lba_read:
    mov ebx, eax
    shr eax, 24
    or eax, 0xE0
    mov dx, 0x1F6
    out dx, al
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al
    mov eax, ebx
    mov dx, 0x1F3
    out dx, al

    mov dx, 0x1F4
    mov eax, ebx
    shr eax, 8
    out dx, al
    mov dx, 0x1F5
    mov eax, ebx
    shr eax, 16
    out dx, al
    mov dx, 0x1F7
    mov al, 0x20
    out dx, al

.next_sector:
    push ecx

.try_again:
    mov dx, 0x1F7
    in al, dx
    test al, 8
    jz .try_again

    mov ecx, 256
    mov dx, 0x1F0
    rep insw
    pop ecx
    loop .next_sector
    ret

times 510-($-$$) db 0
dw 0xAA55
