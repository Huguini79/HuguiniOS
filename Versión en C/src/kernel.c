#include "kernel.h"
#include "idt/idt.h"
#include "io/io.h"
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 20

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

void imprimir_texto(const char* texto, int fila) {
    terminal_row = fila;  // Establece la fila deseada
    terminal_col = 0;     // Reinicia la columna a 0

    for (const char* a = texto; *a != '\0'; a++) {
        terminal_writechar(*a, 0x0F);
    }
}

void kernel_main()
{
    terminal_initialize();
    const char mensaje[] = "BIENVENIDO A HuguiniOS";
    const char mensaje2[] = "Te estoy hablando desde C :)";
    const char mensaje3[] = "Sistema operativo hecho en Ensamblador y C por Huguini";
	const char mensaje4[] = "................";
	const char mensaje5[] = "....HuguiniOS...";
	const char mensaje6[] = "................";
	
    imprimir_texto(mensaje, 0);
    imprimir_texto(mensaje2, 2);
    imprimir_texto(mensaje3, 4);
    imprimir_texto(mensaje4, 6);
    imprimir_texto(mensaje5, 7);
    imprimir_texto(mensaje6, 8);
    
    idt_init();
    
    outb(0x60, 0xff);
        
}
