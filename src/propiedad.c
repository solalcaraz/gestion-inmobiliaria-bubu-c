#include <stdio.h>
#include "propiedad.h"

const propiedad_t REGISTRO_VACIO = {0, "0", "0", "0", 0, 0, 0, 0, 0, "0", "0", "0", "0", 0};

int contarRegistros(FILE *propiedades){
    fseek(propiedades, 0, SEEK_END);
    return ftell(propiedades) / sizeof(propiedad_t);
}

void leerRegistro(FILE *propiedades, int id, propiedad_t *prop){
    fseek(propiedades, (id - 1) * sizeof(propiedad_t), SEEK_SET);
    fread(prop, sizeof(propiedad_t), 1, propiedades);
}

void escribirRegistro(FILE *propiedades, int id, const propiedad_t *prop){
    fseek(propiedades, (id - 1) * sizeof(propiedad_t), SEEK_SET);
    fwrite(prop, sizeof(propiedad_t), 1, propiedades);
}

void imprimirEncabezado(void){
    printf("ID | Ingreso |         Zona       |  Ciudad/Barrio          | Dormitorios | Ba\xa4os | Sup.Total "
           "| Sup.Cubierta |  Precio       | Moneda | Propiedad |     Operaci\xa2n     | Salida | Activo\n");
}

void imprimirPropiedad(const propiedad_t *prop){
    printf("%-3d|%-9s|%-20s|%-25s|%-13d|%-7d|%-11.2f|%-14.2f|%-15.2f|%-8s|%-11s|%-19s|%-8s|%-7d\n",
           prop->id, prop->fecha_ingreso, prop->zona, prop->ciudad_barrio, prop->dormitorios, prop->banos,
           prop->superficie_total, prop->superficie_cubierta, prop->precio, prop->moneda,
           prop->tipo_propiedad, prop->operacion, prop->fecha_salida, prop->flag_activo);
}
