#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <stdio.h>

#define ARCHIVO_PROPIEDADES "propiedades.dat"

// Las fechas se guardan como texto DDMMYYYY y la de salida vale "0" mientras la propiedad
// sigue activa. Los registros vacíos (huecos entre IDs) tienen id 0.
typedef struct Propiedad {
    int id;
    char fecha_ingreso[9];
    char zona[30];
    char ciudad_barrio[30];
    int dormitorios;
    int banos;
    float superficie_total;
    float superficie_cubierta;
    float precio;
    char moneda[6];
    char tipo_propiedad[20];
    char operacion[20];
    char fecha_salida[9];
    int flag_activo;
} propiedad_t;

extern const propiedad_t REGISTRO_VACIO;

// El archivo es de acceso directo: la propiedad con ID n ocupa el registro n (contando desde 1),
// así se lee o escribe cualquier propiedad con un fseek, sin recorrer el archivo.
int contarRegistros(FILE *propiedades);
void leerRegistro(FILE *propiedades, int id, propiedad_t *prop);
void escribirRegistro(FILE *propiedades, int id, const propiedad_t *prop);

void imprimirEncabezado(void);
void imprimirPropiedad(const propiedad_t *prop);

#endif
