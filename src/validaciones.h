// Validaciones sobre el texto que ingresa el usuario. Todas devuelven 1 si es válido y 0 si no.

#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Sólo dígitos (no acepta signo, así que los negativos quedan afuera).
int validarInt(const char num[]);

// Real positivo con '.' como separador decimal.
int validarFloat(const char flotante[]);

// Fecha DDMMYYYY existente (días por mes y bisiestos) con año entre 1900 y 9999.
int validarFecha(const char fecha[]);

// Fecha DDMMYYYY que no sea posterior a hoy.
int compararFecha(const char fecha[]);

// Sin dígitos: sólo letras, signos de puntuación y espacios.
int validarTexto(const char texto[]);

// Convierte una fecha DDMMYYYY ya validada en el entero YYYYMMDD,
// que se puede comparar con < y > para ordenar fechas.
int convertirFecha(const char fecha[]);

// Pasa a mayúscula la primera letra de cada palabra.
void capitalizarPalabras(char texto[]);

#endif
