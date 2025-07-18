#include "idt.h"
#include "config.h"
#include "../kernel.h"
#include "../huguinimain.h"
#include "memory/memory.h"
#include "string/string.h"
#include "keyboard/keyboard.h"
#include "programs/calculator.h"
#include "programs/hola.h"
#include "io/io.h"

struct idt_desc idt_descriptors[HUGUINIOS_TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

const char mensaje2[] = "Error de división por cero";

void idt_zero();
void idt_set(int interrupt_no, void* address);
void int21h_handler();
void no_interrumpt_handler();

extern void idt_load(struct idtr_desc* ptr);
extern void int21h();
extern void no_interrumpt();

int pos;

char comando[100];

int num1;
int num2;


void agregar_caracter(char c) {
  comando[pos++] = c;
  comando[pos] = '\0';
}

void int21h_handler() {
    iniciar_teclado();
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
