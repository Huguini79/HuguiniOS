#include "calculator.h"
#include "idt/idt.h"
#include "../kernel.h"
#include "../huguinimain.h"

void ensenar() {
  crear_ventana("                   CALCULADORA                              ", "");
  for(int i = 1; i <= 5; i++) {
    int suma = i + i;
    int resta = i - i;
    int multi = i * i;
    int divi;
    if (i != 0) {
        divi = i / i;
    } else {
        divi = 0;
    }

    char buffer1[100];
    char buffer2[100];
    char buffer3[100];
    char buffer4[100];
    itoa(suma, buffer1);
    itoa(resta, buffer2);
    itoa(multi, buffer3);
    itoa(divi, buffer4);
    imprimir_texto("Suma de los numeros del 1 al 5 por si mismos:\n");
    imprimir_texto(buffer1);
    imprimir_texto("\n");
     imprimir_texto("Resta de los numeros del 1 al 5 por si mismos:\n");
    imprimir_texto(buffer2);
        imprimir_texto("\n");
     imprimir_texto("Multiplicacion de los numeros del 1 al 5 por si mismos:\n");
    imprimir_texto(buffer3);
        imprimir_texto("\n");
     imprimir_texto("Division de los numeros del 1 al 5 por si mismos:\n");
    imprimir_texto(buffer4);
        imprimir_texto("\n");
  }
}
