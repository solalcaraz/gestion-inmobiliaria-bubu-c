// fflush(stdin) no está definido por el estándar de C, pero en Windows descarta lo que quedó
// en el buffer del teclado. El programa depende de eso para que lo que sobra de un ingreso
// (por ejemplo "abc" cuando se pedía una sola letra) no se tome como respuesta a la pregunta
// siguiente. Por eso se comporta como se espera sólo en Windows.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"
#include "validaciones.h"

void leerLinea(char texto[], int tamanio){
    if (fgets(texto, tamanio, stdin) != NULL){
        texto[strcspn(texto, "\n")] = '\0';
    }
}

char elegirOpcion(const char *menu, const char *validas, const char *error){
    char opcion;
    printf("%s", menu);
    scanf(" %c", &opcion);
    fflush(stdin);
    opcion = tolower(opcion);
    while (strchr(validas, opcion) == NULL){
        printf("%s", error);
        scanf(" %c", &opcion);
        fflush(stdin);
        opcion = tolower(opcion);
    }
    return opcion;
}

// "formato" limita cuántos caracteres lee scanf para no desbordar "dato".
static void pedirValidado(const char *mensaje, const char *error, const char *formato,
                          char dato[], int (*esValido)(const char[])){
    printf("%s", mensaje);
    scanf(formato, dato);
    fflush(stdin);
    while (!esValido(dato)){
        printf("%s", error);
        scanf(formato, dato);
        fflush(stdin);
    }
}

// El ID 0 no se acepta porque es el que tienen los registros vacíos del archivo.
static int esIDValido(const char id[]){
    return validarInt(id) && atoi(id) != 0;
}

static int esFechaHastaHoy(const char fecha[]){
    return validarFecha(fecha) && compararFecha(fecha);
}

int pedirID(void){
    char id[20];
    pedirValidado("Ingrese el ID de la propiedad: ",
                  "Opci\xa2n inv\xa0lida. Por favor, ingrese un n\xa3mero entero: ",
                  " %5s", id, esIDValido);
    return atoi(id);
}

int pedirEntero(const char *mensaje, const char *error){
    char num[20];
    pedirValidado(mensaje, error, " %19s", num, validarInt);
    return atoi(num);
}

float pedirReal(const char *mensaje, const char *error){
    char num[20];
    pedirValidado(mensaje, error, " %19s", num, validarFloat);
    return atof(num);
}

void pedirFecha(const char *mensaje, char fecha[], int hastaHoy){
    pedirValidado(mensaje,
                  "Opci\xa2n inv\xa0lida. Por favor, ingrese una fecha con formato DDMMYYYY: ",
                  " %8s", fecha, hastaHoy ? esFechaHastaHoy : validarFecha);
}

void pedirTexto(const char *mensaje, const char *error, char texto[], int tamanio){
    printf("%s", mensaje);
    leerLinea(texto, tamanio);
    fflush(stdin);
    while (!validarTexto(texto)){
        printf("%s", error);
        leerLinea(texto, tamanio);
        fflush(stdin);
    }
    capitalizarPalabras(texto);
}

const char *elegirMoneda(void){
    char opcion = elegirOpcion("Moneda de la propiedad:\n[A]. ARS\n[U]. USD\n"
                               "Seleccione el tipo de moneda: ", "au",
                               "Opci\xa2n inv\xa0lida. Por favor, ingrese una opci\xa2n v\xa0lida (A/U): ");
    return opcion == 'a' ? "PESOS" : "USD";
}

const char *elegirTipoPropiedad(void){
    char opcion = elegirOpcion("Tipo de propiedad:\n[C]. Casa\n[D]. Departamento\n[P]. PH\n"
                               "Seleccione el tipo de propiedad: ", "cdp",
                               "Opci\xa2n inv\xa0lida. Por favor, ingrese una opci\xa2n v\xa0lida (C/D/P): ");
    switch (opcion){
        case 'c': return "Casa";
        case 'd': return "Depto.";
        default:  return "PH";
    }
}

const char *elegirOperacion(void){
    char opcion = elegirOpcion("Tipo de operacion:\n[V]. Venta\n[A]. Alquiler\n[T]. Alquiler Temporal\n"
                               "Seleccione el tipo de operaci\xa2n: ", "vat",
                               "Opci\xa2n inv\xa0lida. Por favor, ingrese una opci\xa2n v\xa0lida (V/A/T): ");
    switch (opcion){
        case 'v': return "Venta";
        case 'a': return "Alquiler";
        default:  return "Alquiler temporal";
    }
}
