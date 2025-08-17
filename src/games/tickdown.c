#include "../kernel.h"
#include "../huguinimain.h"
#include "menu.h"
#include "tickdown.h"
#include "idt/idt.h"
#include "keyboard/keyboard.h"
#include "string/string.h"

#include <stdbool.h>

bool tickdown_iniciado = false;
int tickdown_contador = 0;


void incrementar_numero() {
  tickdown_contador++;
  limpiar_pantalla();
  imprimir_texto("TICKDOWN - Presina la tecla espacio para incrementar el numero y para salir presiona ESC\n\n");
  imprimir_texto("\n\n\n\n");
  char buffer2[1000000];
  itoa(tickdown_contador, buffer2);
  imprimir_texto("                                      ");
  imprimir_texto(buffer2);
}

void iniciar_tickdown() {
  tickdown_iniciado = true;
  limpiar_pantalla();
  imprimir_texto("TICKDOWN - Presina la tecla espacio para incrementar el numero y para salir presiona ESC\n\n");
  imprimir_texto("\n\n\n\n");
  char buffer[1000000];
  itoa(tickdown_contador, buffer);
  imprimir_texto("                                      ");
  imprimir_texto(buffer);
}
