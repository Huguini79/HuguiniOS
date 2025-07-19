#include "../kernel.h"
#include "../huguinimain.h"
#include "guibonita.h"

void iniciar_gui_bonita() {
  for(int ii = 0; ii <= 1500; ii++) {
    for(int i = 0; i <= 15; i++) {
      limpiar_pantalla();
      color_terminal = i;
      imprimir_texto("GUI BONITA");
    }
  }
      imprimir_texto("\n\nPRESIONA ENTER PARA TERMINAR...\n");
}
