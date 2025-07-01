#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include "config.h"
#include "gdt/gdt.h"
#include "fs/file.h"
#include "memory/heap/kheap.h"
#include "string/string.h"
#include "disk/disk.h"
#include "string/string.h"
#include "memory/paging/paging.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

uint16_t* video_mem;
uint16_t terminal_row;
uint16_t terminal_col;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }
    
    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void limpiar_pantalla() {
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            terminal_putchar(x, y, ' ', 0);
        }
    }
    terminal_row = 0;
    terminal_col = 0;
}

void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;

    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }   
}

void imprimir_texto(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

static struct paging_4gb_chunk* kernel_chunk = 0;

struct gdt gdt_real[HUGUINIOS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[HUGUINIOS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},                // NULL Segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a},           // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92},            // Kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8},              // User code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2},             // User data segment
};

void kernel_main() {
    terminal_initialize();

    idt_init();
    
    outb(0x21, 0xFD);  // Habilita solo IRQ1 (teclado)
outb(0xA1, 0xFF);  // Deshabilita todas las interrupciones del segundo PIC

	kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT);
	
	paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));
	
	enable_paging();

    enable_interrumpts();
    
    fs_init();
    
    kheap_init();

    outb(0x60, 0xff); 
		  
    imprimir_texto("BIENVENIDO A HuguiniOS\n\n");
    imprimir_texto("Introduce un comando, presiona ALT para limpiar la pantalla\n\n");
    imprimir_texto("ordenador:~/HuguiniOS$ ");
        
    char buf[512];
    disk_read_sector(0, 1, buf);
    
    struct disk_stream* stream = diskstreamer_new(0);
    diskstreamer_seek(stream, 0x201);
    unsigned char c = 0;
    
    diskstreamer_read(stream, &c, 1);
    
    memset(gdt_real, 0x00, sizeof(gdt_real));

    gdt_structured_to_gdt(gdt_real, gdt_structured, HUGUINIOS_TOTAL_GDT_SEGMENTS);


    while(1) {
        __asm__("hlt");
        
    }

       
}
