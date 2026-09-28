/*Biblioteca personal que permite verificar los datos ingresados por usuario y operarlos,
teniendo un menor margen de error.*/


#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Recibe un string
// Chequea que contenga sólo valores numericos enteros
// Devuelve 1 en caso de ser correcto, 0 si no lo es
int validarInt(char id[]);

// Recibe un string
// Chequea que contenga sólo valores reales positivos, con separador decimal '.'
// Devuelve 1 en caso de ser correcto, 0 si no lo es
int validarFloat(char flotante[]);

// Recibe un string que contiene una fecha en formato DDMMYYYY
// chequea si esa fecha es una fecha válida, teniendo en cuenta cantidad de dias por mes y años bisiestos.
// devuelve 1 si es válida, 0 si no lo es.
int validarFecha(char fecha[]);

// Recibe un string validado previamente por validarFecha()
// devuelve una representación entera de la fecha en formato YYYYMMD
int convertirFecha(char fecha[]);


int compararFecha(char fecha[]);

// Recibe un string
// Chequea que dentro de ese string no haya ningún valor numérico.
// devuelve 1 si es válida, 0 si no lo es.
int validarTexto (char texto[]);

// Chequea que cada palabra del string "formato" empiece con mayúscula.
// Cambia la primer letra de cada palabra a mayus en caso de que no lo sea.
void validarMayus (char formato[]);



#endif