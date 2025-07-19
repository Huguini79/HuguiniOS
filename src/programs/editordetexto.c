#include "editordetexto.h"
#include "../kernel.h"
#include "../huguinimain.h"
#include "idt/idt.h"
#include "keyboard/keyboard.h"

void iniciar_editor_de_texto() {
  app_editor_de_texto = true;
  limpiar_pantalla();
  imprimir_texto("EDITOR DE TEXTO\nNO SE VAN A GUARDAR EN NINGUN ARCHIVO EL CONTENIDO, PARA DAR UN SALTO DE LINEA, PRESIONA EL SHIFT DERECHO O ENTER\n\n");
}
