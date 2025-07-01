#include "idt.h"
#include "config.h"
#include "../kernel.h"
#include "memory/memory.h"
#include "io/io.h"

struct idt_desc idt_descriptors[HUGUINIOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

const char mensaje[] = "Tecla del teclado presionada";
const char mensaje2[] = "Error de división por cero";

void idt_zero();
void idt_set(int interrupt_no, void* address);
void int21h_handler();
void no_interrumpt_handler();

extern void idt_load(struct idtr_desc* ptr);
extern void int21h();
extern void no_interrumpt();

void int21h_handler() {
    uint8_t scan_code = insb(0x60);
    (void)scan_code;
    if(scan_code == 0x1E) {
          imprimir_texto("a");
          
    } else if(scan_code == 0x30) {
      imprimir_texto("b");
    } else if(scan_code == 0x2E) {
          imprimir_texto("c");
          
    } else if(scan_code == 0x20) {
      imprimir_texto("d");
    } else if(scan_code == 0x12) {
      imprimir_texto("e");
    } else if(scan_code == 0x21) {
          imprimir_texto("f");
          
    } else if(scan_code == 0x22) {
      imprimir_texto("g");
    } else if(scan_code == 0x23) {
      imprimir_texto("h");
    } else if(scan_code == 0x17) {
          imprimir_texto("i");
          
    } else if(scan_code == 0x24) {
      imprimir_texto("j");
    } else if(scan_code == 0x25) {
      imprimir_texto("k");
    } else if(scan_code == 0x26) {
          imprimir_texto("l");
          
    } else if(scan_code == 0x32) {
      imprimir_texto("m");
    } else if(scan_code == 0x31) {
      imprimir_texto("n");
    } else if(scan_code == 0x18) {
          imprimir_texto("o");
          
    } else if(scan_code == 0x19) {
      imprimir_texto("p");
    } else if(scan_code == 0x10) {
      imprimir_texto("q");
    } else if(scan_code == 0x13) {
          imprimir_texto("r");
          
    } else if(scan_code == 0x22) {
      imprimir_texto("g");
    } else if(scan_code == 0x13) {
      imprimir_texto("r");
    } else if(scan_code == 0x1F) {
          imprimir_texto("s");
          
    } else if(scan_code == 0x14) {
      imprimir_texto("t");
    } else if(scan_code == 0x16) {
      imprimir_texto("u");
    } else if(scan_code == 0x2F) {
          imprimir_texto("v");
          
    } else if(scan_code == 0x11) {
      imprimir_texto("w");
    } else if(scan_code == 0x2D) {
      imprimir_texto("x");
    } else if(scan_code == 0x15) {
          imprimir_texto("y");
          
    } else if(scan_code == 0x2C) {
      imprimir_texto("z");
    } else if(scan_code == 0x39) {
      imprimir_texto(" ");
      
    } else if(scan_code == 0x38) {
      limpiar_pantalla();
      imprimir_texto("ordenador:~/HuguiniOS$ ");
      
    } else if(scan_code == 0x1C) {
      imprimir_texto("\n");
      imprimir_texto("ordenador:~/HuguiniOS$ ");
    }
    	outb(0x20, 0x20);
}

void no_interrumpt_handler() {
	outb(0x20, 0x20);
}

void idt_zero() {
    imprimir_texto(mensaje2);
}

void idt_set(int interrupt_no, void* address) {
    struct idt_desc* desc = &idt_descriptors[interrupt_no];
    desc->offset_1 = (uint32_t) address & 0x0000ffff;
    desc->selector = KERNEL_CODE_SELECTOR;
    desc->zero = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2 = (uint32_t) address >> 16;
}

void idt_init() {
    memset(idt_descriptors, 0, sizeof(idt_descriptors));
	idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
	idtr_descriptor.base = (uint32_t) idt_descriptors;
	
	for(int i = 0; i < HUGUINIOS_TOTAL_INTERRUPTS; i++) {
		idt_set(i, no_interrumpt);
	}
	
	idt_set(0, idt_zero);
	
	idt_set(0x09, int21h);
	
	idt_load(&idtr_descriptor);
	
}
