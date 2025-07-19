#include "../kernel.h"
#include "../huguinimain.h"
#include "graphics.h"
#include "keyboard/keyboard.h"
#include "idt/idt.h"
#include "string/string.h"

void dibujar_sprite(int x, int y, const char* texto) {
  for(int i = 0; i <= x; i++) {
    imprimir_texto(" ");
  }
  for(int ii = 0; ii <= y; ii++) {
    imprimir_texto("\n");
  }
  imprimir_texto(texto);
}
