// Una función por cada opción del menú principal.

#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <stdio.h>

// Crea (o vacía) el archivo de propiedades o abre el existente, según elija el usuario.
// Si no lo puede abrir, termina el programa.
FILE *crearDat(void);

void listarDat(FILE *propiedades);
void altaPropiedad(FILE *propiedades);
void buscarPropiedad(FILE *propiedades);
void modificarPropiedad(FILE *propiedades);
void bajaLogica(FILE *propiedades);

// Pasa las propiedades inactivas a "propiedades_bajas_<fecha>.xyz" y vacía sus registros.
void bajaFisica(FILE *propiedades);
void listarXyz(void);

#endif
