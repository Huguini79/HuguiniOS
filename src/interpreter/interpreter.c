#include "kernel.h"
#include "huguinimain.h"
#include "idt/idt.h"
#include "keyboard/keyboard.h"
#include "string/string.h"

void interpretar_comando(const char* comando) {
      int i = 0;
      while (comando[i] != '\0') {
        if(comando[i] == 'i' && 
        comando[i+1] == 'm' && 
        comando[i+2] == 'p' && 
        comando[i+3] == 'r' && 
        comando[i+4] == 'i' &&
        comando[i+5] == 'm' &&
        comando[i+6] == 'i' &&
        comando[i+7] == 'r') {
          i += 8;
          
          while(comando[i] == ' ') i++;
          
          imprimir_texto("\n");
          
          while(comando[i] != '\0') {
              char letra[2];
              letra[0] = comando[i];
              letra[1] = '\0';
              imprimir_texto(letra);

              i++;
          }
          
          imprimir_texto("\n\n");
          imprimir_texto("huguinilanguage> ");
          return;

          
        }
        i++;
      }
      imprimir_texto("Comando no reconocido");
}  
