#include "io/io.h"
#include "idt/idt.h"
#include "../kernel.h"
#include "keyboard.h"
#include "fs/file.h"
#include "fs/fat/fat16.h"
#include "fs/pparser.h"
#include "string/string.h"
#include "programs/calculator.h"
#include "programs/guibonita.h"
#include "programs/editordetexto.h"
#include "games/menu.h"
#include "games/tickdown.h"

#include <stdbool.h>

bool app_editor_de_texto = false;

int contador = 1;

int pos;

char comando[100];

int num1;
int num2;

void iniciar_teclado() {
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
      if(tickdown_iniciado == true) {
        incrementar_numero();
      }
      agregar_caracter(' ');
      imprimir_texto(" ");
      
    } else if(scan_code == 0x1D) {
      limpiar_pantalla();
      color_terminal = 2;
      imprimir_texto("ordenador:~/HuguiniOS$ ");
    } else if(scan_code == 0x0F) {
      limpiar_pantalla();
      color_terminal = 6;
      imprimir_texto("ordenador:~/HuguiniOS$ ");
    } else if(scan_code == 0x01) {
      if(tickdown_iniciado == true) {
        menu_juegos = false;
        tickdown_iniciado = false;
        limpiar_pantalla();
        imprimir_texto("ordenador:~/HuguiniOS$ ");
      
      } else if(menu_juegos == true) {
        menu_juegos = false;
        tickdown_iniciado = false;
        limpiar_pantalla();
        imprimir_texto("ordenador:~/HuguiniOS$ ");
      
      } else {
        limpiar_pantalla();
        color_terminal = 15;
        imprimir_texto("ordenador:~/HuguiniOS$ ");
      }
    }
    else if(scan_code == 0x38) {
      app_editor_de_texto = false;
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
    } else if(scan_code == 0x36) {
      if(app_editor_de_texto == false) {
        imprimir_texto("");
      } else {
        agregar_caracter('\n');
        imprimir_texto("\n");
      }
    }
    else if(scan_code == 0x1C) {
      contador = 1;
      if(app_editor_de_texto == true) {
        agregar_caracter('\n');
        imprimir_texto("\n");
      } else if(menu_juegos == true || tickdown_iniciado == true) {
          if (strncmp(comando, "tickdown", 8) == 0) {
              iniciar_tickdown();
          } else if (strncmp(comando, "exit", 4) == 0) {
              menu_juegos = false;
              tickdown_iniciado = false;
              limpiar_pantalla();
              imprimir_texto("ordenador:~/HuguiniOS$ ");
          } else {
              imprimir_texto("\nJuego no reconocido\n");
              limpiar_pantalla();
              imprimir_texto("ordenador:~/HuguiniOS$ ");
          }
      }
      else {
        contador++;
      app_editor_de_texto = false;
      if(strncmp(comando, "ver", 7) == 0) {
        limpiar_pantalla();
        crear_ventana("VERSION SISTEMA OPERATIVO", "\n\n\n\n\n\n\n\n\n\nSistema operativo por Huguini79\nDesarrollado desde cero\nY se llama HuguiniOS\n\n\n\n\n\n\n\n\n");
        imprimir_texto("\n\n");
        
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
              int fd = fopen("0:/hola.txt", "r");
              if(fd) {
                imprimir_texto("\nEl archivo hola.txt ha sido cargado exitosamente\n\n");
                imprimir_texto("ordenador:~/HuguiniOS$ ");
              } else {
                imprimir_texto("\nNo se ha podido cargar el archivo hola.txt en la carpeta raíz\n\n");
                imprimir_texto("ordenador:~/HuguiniOS$ ");
              }
      } else if(strncmp(comando, "", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, " ", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "  ", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "   ", 7) == 0) {
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "hteclado", 7) == 0) {
          limpiar_pantalla();
          imprimir_texto("\n................................................................................\n\n");
          
          imprimir_texto("Teclas:\nCtrl - cambiar el color del texto de la pantalla a verde\nTAB - cambiar el color del texto de la pantalla a naranja\nESC - cambiar el color del texto de la pantalla al predeterminado(blanco)");
          imprimir_texto("\n\n................................................................................\n");
                              imprimir_texto("ordenador:~/HuguiniOS$ ");
      }
      else if(strncmp(comando, "help", 7) == 0) {
      limpiar_pantalla();
          imprimir_texto("\n................................................................................\n");
            imprimir_texto("Comandos:\nver - Version del sistema operativo\nclear - Limpiar la pantalla\nsorpresa - Sorpresa\ncargararchivo - Cargar archivo hola.txt(no funciona muy bien esa funcion)\nexit - Apagar el ordenador\ncalculadora - Calculadora\nguiblanca - Muestra toda la pantalla blanca, presiona ALT para limpiar la pantalla despues de eso\nhola - un hola mundo simple\nguibonita - Muestra un texto con varios colores\nhteclado - Teclas especificas para cambiar el color del texto de la pantalla\neditordetexto - Editor de texto simple sin funcion de guardar archivo\nmenujuegos - Menu de juegos!\nhuguiniosascii - Arte Ascii de HuguiniOS\n\n................................................................................\n\n");
                    imprimir_texto("ordenador:~/HuguiniOS$ ");
      } else if(strncmp(comando, "exit", 7) == 0) {
          outw(0x604, 0x2000);
      } else if(strncmp(comando, "huguiniosascii", 10) == 0) {
          limpiar_pantalla();
          imprimir_texto("\n _    _                   _       _  ____   _____");
          imprimir_texto("\n");
          imprimir_texto("| |  | |                 (_)     (_)/ __ \ / ____|");
          imprimir_texto("\n");
          imprimir_texto("| |__| |_   _  __ _ _   _ _ _ __  _| |  | | (___ ");
          imprimir_texto("\n");
          imprimir_texto("|  __  | | | |/ _` | | | | | '_ \| | |  | |\___");
          imprimir_texto("\n");
          imprimir_texto("| |  | | |_| | (_| | |_| | | | | | | |__| |____) |");
          imprimir_texto("\n");
          imprimir_texto("|_|  |_|\__,_|\__, |\__,_|_|_| |_|_|\____/|_____/");
          imprimir_texto("\n");
          imprimir_texto("__/");
          imprimir_texto("\n");
          imprimir_texto("|___/                               \n\n");
          imprimir_texto("ordenador:~/HuguiniOS$ ");
      }
      else if(strncmp(comando, "guibonita", 7) == 0) {
        iniciar_gui_bonita();
        
      } else if(strncmp(comando, "menujuegos", 7) == 0) {
        iniciar_menu();
      }
      else if(strncmp(comando, "editordetexto", 7) == 0) {
        iniciar_editor_de_texto();
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
      
    } 
    } else if(scan_code == 0x0E) {
      if (pos > 0) {
        comando[--pos] = '\0';
    }
      limpiar_pantalla();
      if(app_editor_de_texto == false) {
        for(int i = 0; i < contador; i++) { 
          imprimir_texto("\nordenador:~/HuguiniOS$ ");
        }
        imprimir_texto(comando);
      } 
      if(menu_juegos == true || tickdown_iniciado == true) {
        limpiar_pantalla();
        crear_ventana("JUEGOS", "Bienvenido al menu de los juegos, para salir, presiona ESC\nJuegos disponibles:\ntickdown - pulsa el espacio para incrementar el numero");
  imprimir_texto("\nIntroduce el nombre del juego que quieras jugar: ");
      imprimir_texto(comando);
      }
      else if(app_editor_de_texto == true) {
        imprimir_texto("EDITOR DE TEXTO\nNO SE VAN A GUARDAR EN NINGUN ARCHIVO EL CONTENIDO, PARA DAR UN SALTO DE LINEA, PRESIONA EL SHIFT DERECHO O ENTER\n\n");
        imprimir_texto(comando);
      }
      
    }
    	outb(0x20, 0x20);
}
