#include "../kernel.h"
#include "menu.h"
#include "idt/idt.h"
#include "keyboard/keyboard.h"
#include "tickdown.h"
#include "string/string.h"

#include <stdbool.h>

void iniciar_menu() {
  menu_juegos = true;
  limpiar_pantalla();
  crear_ventana("JUEGOS", "Bienvenido al menu de los juegos, para salir, presiona ESC\nJuegos disponibles:\ntickdown - pulsa el espacio para incrementar el numero");
  imprimir_texto("\nIntroduce el nombre del juego que quieras jugar: ");
}
