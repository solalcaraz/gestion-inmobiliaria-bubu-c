#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "entrada.h"
#include "operaciones.h"

static void mostrarMenu(void){
    printf("--------Men\xa3 Inicial--------\n");
    printf("[a]. Listar propiedades.\n");
    printf("[b]. Alta de una propiedad.\n");
    printf("[c]. Buscar propiedad.\n");
    printf("[d]. Modificar propiedades.\n");
    printf("[e]. Baja logica de una propiedad.\n");
    printf("[f]. Baja fisica de propiedades inactivas.\n");
    printf("[g]. Listar baja fisica de propiedades.\n");
    printf("[h]. Salir.\n");
}

int main(void){
    printf("\xad" "Bienvenido a Inmobiliaria Bub\xa3!\n");
    FILE *propiedades = crearDat();
    fflush(stdin);
    while (1){
        mostrarMenu();
        fflush(stdin);
        switch (tolower(getchar())){
            case 'a':
                listarDat(propiedades);
                break;
            case 'b':
                altaPropiedad(propiedades);
                break;
            case 'c':
                buscarPropiedad(propiedades);
                break;
            case 'd':
                modificarPropiedad(propiedades);
                break;
            case 'e':
                bajaLogica(propiedades);
                break;
            case 'f':
                bajaFisica(propiedades);
                break;
            case 'g':
                listarXyz();
                break;
            case 'h':
                fclose(propiedades);
                printf("Gracias por confiar en Inmobiliaria Bub\xa3. Saliendo del programa...\n");
                exit(0);
            default:
                printf(MSG_OPCION_INVALIDA);
        }
    }
}
