#include "kernel.h"
#include "huguinimain.h"
#include "idt/idt.h"
#include "io/io.h"
#include "config.h"
#include "gdt/gdt.h"
#include "memory/heap/kheap.h"
#include "string/string.h"
#include "disk/disk.h"
#include "string/string.h"
#include "memory/paging/paging.h"
#include "disk/streamer.h"
#include "pci/pci.h"
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define MAX_LINE_LENGTH 256

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

int color_terminal = 15;

void imprimir_texto(const char* str) {
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], color_terminal);
    }
}

void crear_boton(const char* texto) {
  imprimir_texto("╔══╗\n");
  imprimir_texto("║");
  imprimir_texto(texto);
  imprimir_texto("║");
  imprimir_texto("\n╚══╝");
}

void escribir_linea_borde(const char inicio, const char relleno, const char fin, int largo) {
    terminal_writechar(inicio, color_terminal);
    for (int i = 0; i < largo; i++) {
        terminal_writechar(relleno, color_terminal);
    }
    terminal_writechar(fin, color_terminal);
    terminal_writechar('\n', color_terminal);
}

void centrar_y_escribir(const char* texto, int ancho) {
    int len = strlen(texto);
    int padding = (ancho - len) / 2;

    terminal_writechar('║', color_terminal);
    for (int i = 0; i < padding; i++) terminal_writechar(' ', color_terminal);
    for (int i = 0; i < len; i++) terminal_writechar(texto[i], color_terminal);
    for (int i = 0; i < (ancho - len - padding); i++) terminal_writechar(' ', color_terminal);
    terminal_writechar('║', color_terminal);
    terminal_writechar('\n', color_terminal);
}

void crear_ventana(const char* titulo, const char* contenido) {
    const char* ptr = contenido;
    const char* inicio_linea = ptr;
    int max_contenido = strlen(titulo);
    char linea[MAX_LINE_LENGTH];
    int num_lineas = 0;
    const char* lineas[20];
    static char lineas_copia[20][MAX_LINE_LENGTH];

    while (*ptr) {
        if (*ptr == '\n' || *(ptr + 1) == '\0') {
            int len = ptr - inicio_linea + ((*ptr == '\n') ? 0 : 1);
            if (len > MAX_LINE_LENGTH - 1) len = MAX_LINE_LENGTH - 1;
            memcpy(lineas_copia[num_lineas], inicio_linea, len);
            lineas_copia[num_lineas][len] = '\0';
            lineas[num_lineas] = lineas_copia[num_lineas];
            if (len > max_contenido) max_contenido = len;
            num_lineas++;
            inicio_linea = ptr + 1;
        }
        ptr++;
    }

    int ancho_total = max_contenido + 17; // márgenes

    escribir_linea_borde('╔', '═', '╗', ancho_total);

    centrar_y_escribir(titulo, ancho_total);

    escribir_linea_borde('╠', '═', '╣', ancho_total);

    for (int i = 0; i < num_lineas; i++) {
        centrar_y_escribir(lineas[i], ancho_total);
    }

    escribir_linea_borde('╚', '═', '╝', ancho_total);
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

	kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT);
	
	paging_switch(paging_4gb_chunk_get_directory(kernel_chunk));
	
	enable_paging();

    enable_interrumpts();
    
    kheap_init();
    
    checkAllBuses();

    /* outb(0x60, 0xff); */
		   
    limpiar_pantalla();
    crear_ventana("           BIENVENIDO A HuguiniOS                          ", "\n\n\n\n\n\n\n\n\n\nPRESIONA ALT PARA QUITAR ESTA VENTANA\n\n\n\n\n\n\n\n\n"); 
        
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
