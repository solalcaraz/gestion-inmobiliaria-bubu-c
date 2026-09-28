// Lectura de datos por teclado: cada función vuelve a preguntar hasta recibir un valor válido.

#ifndef ENTRADA_H
#define ENTRADA_H

// Los acentos de todos los mensajes van como escapes (\xa2 = ó, \xa0 = á, ...) porque la consola
// de Windows en español usa la página de códigos 850, no UTF-8.
#define MSG_OPCION_INVALIDA "Opci\xa2n inv\xa0lida. Int\x82ntelo de nuevo.\n"

// Reemplazo seguro de gets(): no se pasa del tamaño del buffer y quita el '\n' final.
void leerLinea(char texto[], int tamanio);

// Muestra "menu" y lee un caracter hasta que sea una de las letras de "validas"
// (en minúscula); si no lo es, muestra "error". Devuelve la opción en minúscula.
char elegirOpcion(const char *menu, const char *validas, const char *error);

int pedirID(void);
int pedirEntero(const char *mensaje, const char *error);
float pedirReal(const char *mensaje, const char *error);
void pedirTexto(const char *mensaje, const char *error, char texto[], int tamanio);

// Guarda en "fecha" (9 caracteres) una fecha DDMMYYYY válida.
// Con hastaHoy distinto de 0 tampoco acepta fechas futuras.
void pedirFecha(const char *mensaje, char fecha[], int hastaHoy);

// Devuelven el texto que se guarda en el registro para la opción elegida.
const char *elegirMoneda(void);
const char *elegirTipoPropiedad(void);
const char *elegirOperacion(void);

#endif
