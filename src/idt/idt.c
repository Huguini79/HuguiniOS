#include "idt.h"
#include "config.h"
#include "../kernel.h"
#include "memory/memory.h"
#include "fs/pparser.h"
#include "fs/fat/fat16.h"
#include "string/string.h"
#include "programs/calculator.h"
#include "programs/hola.h"
#include "io/io.h"

int pos;

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

char comando[100];

int num1;
int num2;

void agregar_caracter(char c) {
  comando[pos++] = c;
  comando[pos] = '\0';
}

void int21h_handler() {
    uint8_t scan_code = insb(0x60);
    (void)scan_code;
    if(scan_code == 0x1E) {
          agregar_caracter('a');
          imprimir_texto("a");
          
    } else if(scan_code == 0x30) {
      agregar_caracter('b');
      imprimir_texto("b");
    } else if(scan_code == 0x2E) {
          agregar_caracter('c');
          imprimir_texto("c");
          
    } else if(scan_code == 0x20) {
      agregar_caracter('d');
      imprimir_texto("d");
    } else if(scan_code == 0x12) {
      agregar_caracter('e');
      imprimir_texto("e");
    } else if(scan_code == 0x21) {
          agregar_caracter('f');
          imprimir_texto("f");
          
    } else if(scan_code == 0x22) {
      agregar_caracter('g');
      imprimir_texto("g");
    } else if(scan_code == 0x23) {
      agregar_caracter('h');
      imprimir_texto("h");
    } else if(scan_code == 0x17) {
          agregar_caracter('i');
          imprimir_texto("i");
          
    } else if(scan_code == 0x24) {
      agregar_caracter('j');
      imprimir_texto("j");
    } else if(scan_code == 0x25) {
      agregar_caracter('k');
      imprimir_texto("k");
    } else if(scan_code == 0x26) {
          agregar_caracter('l');
          imprimir_texto("l");
          
    } else if(scan_code == 0x32) {
      agregar_caracter('m');
      imprimir_texto("m");
    } else if(scan_code == 0x31) {
      agregar_caracter('n');
      imprimir_texto("n");
    } else if(scan_code == 0x18) {
          agregar_caracter('o');
          imprimir_texto("o");
          
    } else if(scan_code == 0x19) {
      agregar_caracter('p');
      imprimir_texto("p");
    } else if(scan_code == 0x10) {
      agregar_caracter('q');
      imprimir_texto("q");
    } else if(scan_code == 0x13) {
          agregar_caracter('r');
          imprimir_texto("r");
          
    } else if(scan_code == 0x22) {
      agregar_caracter('g');
      imprimir_texto("g");
    } else if(scan_code == 0x13) {
      agregar_caracter('r');
      imprimir_texto("r");
    } else if(scan_code == 0x1F) {
          agregar_caracter('s'); 
          imprimir_texto("s");
          
    } else if(scan_code == 0x14) {
      agregar_caracter('t');
      imprimir_texto("t");
    } else if(scan_code == 0x16) {
      agregar_caracter('u');
      imprimir_texto("u");
    } else if(scan_code == 0x2F) {
          agregar_caracter('v');
          imprimir_texto("v");
          
    } else if(scan_code == 0x11) {
      agregar_caracter('w');
      imprimir_texto("w");
    } else if(scan_code == 0x2D) {
      agregar_caracter('x');
      imprimir_texto("x");
    } else if(scan_code == 0x15) {
          agregar_caracter('y');
          imprimir_texto("y");
          
    } else if(scan_code == 0x2C) {
      agregar_caracter('z');
      imprimir_texto("z");
    } else if(scan_code == 0x39) {
      agregar_caracter(' ');
      imprimir_texto(" ");
      
    } else if(scan_code == 0x38) {
      limpiar_pantalla();
      imprimir_texto("ordenador:~/HuguiniOS$ ");
      
    } else if(scan_code == 0x02) {
      imprimir_texto("1");
    } else if(scan_code == 0x03) {
      imprimir_texto("2");
    } else if(scan_code == 0x04) {
      imprimir_texto("3");
    } else if(scan_code == 0x05) {
      imprimir_texto("4");
    } else if(scan_code == 0x06) {
      imprimir_texto("5");
    } else if(scan_code == 0x07) {
      imprimir_texto("6");
    } else if(scan_code == 0x08) {
      imprimir_texto("7");
    } else if(scan_code == 0x09) {
      imprimir_texto("8");
    } else if(scan_code == 0x0A) {
      imprimir_texto("9");
    } else if(scan_code == 0x0B) {
      imprimir_texto("0");
    }else if(scan_code == 0x02) {
      imprimir_texto("1");
    } else if(scan_code == 0x03) {
      imprimir_texto("2");
    } else if(scan_code == 0x04) {
      imprimir_texto("3");
    } else if(scan_code == 0x05) {
      imprimir_texto("4");
    } else if(scan_code == 0x06) {
      imprimir_texto("5");
    } else if(scan_code == 0x07) {
      imprimir_texto("6");
    } else if(scan_code == 0x08) {
      imprimir_texto("7");
    } else if(scan_code == 0x09) {
      imprimir_texto("8");
    } else if(scan_code == 0x0A) {
      imprimir_texto("9");
    } else if(scan_code == 0x0B) {
      imprimir_texto("0");
    }
    else if(scan_code == 0x1C) {
      if(strncmp(comando, "ver", 7) == 0) {
        imprimir_texto("\nSistema operativo HuguiniOS, desarrollado por Huguini79 Github desde cero\n\n");
        imprimir_texto("ordenador:~/HuguiniOS$ ");
        
      } else if(strncmp(comando, "clear", 7) == 0) {
        limpiar_pantalla();
        imprimir_texto("ordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "sorpresa", 7) == 0) {
        limpiar_pantalla();
        for(int i = 0; i <= 50; i++) {
          imprimir_texto("..HuguiniOS..");
        }
        imprimir_texto("\n\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "cargararchivo", 7) == 0) {
              fs_init();
          int fd = fopen("0:/hola.txt", "r");
          if(fd >= 0) {
            char buffer[200];
            fread(buffer, 1, sizeof(buffer)-1, fd);
            buffer[199] = '\0';
            imprimir_texto("\n");
            imprimir_texto(buffer);
            imprimir_texto("\n\n");
            fclose(fd);
          }
      } else if(strncmp(comando, "", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, " ", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "  ", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "   ", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "help", 7) == 0) {
      limpiar_pantalla();
          imprimir_texto("\n................................................................................\n");
          imprimir_texto("Comandos:\nver - Version del sistema operativo\nclear - Limpiar la pantalla\nsorpresa - Sorpresa\ncargararchivo - Cargar archivo hola.txt(no funciona muy bien esa funcion)\nexit - Apagar el ordenador\ncalculadora - Calculadora\nguiblanca - Muestra toda la pantalla blanca, presiona ALT para limpiar la pantalla despues de eso\nhola - un hola mundo simple\n\n................................................................................\n\n");
                    imprimir_texto("ordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "exit", 7) == 0) {
          outw(0x604, 0x2000);
      }
       else if(strncmp(comando, "calculadora", 7) == 0) {
          limpiar_pantalla();
          imprimir_texto("CALCULADORA\n\n\n\n");
          ensenar();
       } else if(strncmp(comando, "guiblanca", 7) == 0) {
          limpiar_pantalla();
          for(int i = 0; i <= 1000; i++) {
            imprimir_texto("█");
          }
       } else if(strncmp(comando, "hola", 7) == 0) {
          decir_hola();
       }
      else {
        imprimir_texto("\nComando no reconocido");
        imprimir_texto("\n\n");
        imprimir_texto("ordenador:~/HuguiniOS$ ");
      }
      comando[0] = '\0';
      pos = 0;
    } else if(scan_code == 0x0E) {
      if (pos > 0) {
        comando[--pos] = '\0';
    }
      limpiar_pantalla();
      imprimir_texto("ordenador:~/HuguiniOS$ ");
      imprimir_texto(comando);
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
