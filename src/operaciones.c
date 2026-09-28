#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entrada.h"
#include "operaciones.h"
#include "propiedad.h"
#include "validaciones.h"

static FILE *abrirPropiedades(const char *modo){
    FILE *propiedades = fopen(ARCHIVO_PROPIEDADES, modo);
    if (propiedades == NULL){
        printf("Error en la apertura del archivo\n");
        exit(1);
    }
    return propiedades;
}

FILE *crearDat(void){
    char opcion;
    while (1){
        printf("\xa8" "Desea crear un nuevo archivo o sobrescribirlo?(S/N): ");
        scanf("%c", &opcion);
        fflush(stdin);
        opcion = tolower(opcion);
        if (opcion == 's'){
            FILE *propiedades = abrirPropiedades("w+b");
            printf("Archivo creado o sobrescrito exitosamente.\n");
            return propiedades;
        } else if (opcion == 'n'){
            FILE *propiedades = abrirPropiedades("rb+");
            printf("Archivo abierto exitosamente.\n");
            return propiedades;
        }
        printf("Opci\xa2n inv\xa0lida.\n");
    }
}

// Criterio de cada opción del listado: a) todas, b) activas, c) un tipo, d) rango de ingreso.
static int cumpleFiltro(char opcion, const propiedad_t *prop, const char *tipo, int desde, int hasta){
    int ingreso;
    switch (opcion){
        case 'b':
            return prop->flag_activo == 1;
        case 'c':
            return strcmp(prop->tipo_propiedad, tipo) == 0;
        case 'd':
            ingreso = convertirFecha(prop->fecha_ingreso);
            return desde <= ingreso && ingreso <= hasta;
        default:
            return 1;
    }
}

void listarDat(FILE *propiedades){
    char opcion, fecha_inicio[9], fecha_fin[9];
    const char *tipo = NULL;
    int desde = 0, hasta = 0;
    propiedad_t prop;
    int total = contarRegistros(propiedades);

    printf("-----------------Listado-----------------\n");
    printf("[a]. Listar todas las propiedades.\n");
    printf("[b]. Listar solo las propiedades activas.\n");
    printf("[c]. Listar un tipo propiedad.\n");
    printf("[d]. Listar en un rango de tiempo.\n");
    scanf(" %c", &opcion);
    opcion = tolower(opcion);
    fflush(stdin);

    switch (opcion){
        case 'a':
        case 'b':
            break;
        case 'c':
            tipo = elegirTipoPropiedad();
            break;
        case 'd':
            pedirFecha("Ingrese la fecha m\xa1nima (formato: DDMMYYYY): ", fecha_inicio, 0);
            desde = convertirFecha(fecha_inicio);
            pedirFecha("Ingrese la fecha m\xa0xima (formato: DDMMYYYY): ", fecha_fin, 0);
            hasta = convertirFecha(fecha_fin);
            break;
        default:
            printf(MSG_OPCION_INVALIDA);
            return;
    }

    imprimirEncabezado();
    for (int id = 1; id <= total; id++){
        leerRegistro(propiedades, id, &prop);
        if (cumpleFiltro(opcion, &prop, tipo, desde, hasta)){
            imprimirPropiedad(&prop);
        }
    }
}

void altaPropiedad(FILE *propiedades){
    propiedad_t nuevo;
    propiedad_t dato = {0};
    int id, totalReg;

    printf("---------------Alta---------------\n");
    id = pedirID();
    do {
        totalReg = contarRegistros(propiedades);
        if (id <= totalReg){
            leerRegistro(propiedades, id, &dato);
            if (dato.id != 0){
                printf("La posici\xa2n %d ya est\xa0 ocupada.\n", id);
                id = pedirID();
            } else {
                nuevo.id = id;
            }
        } else {
            // Si el ID queda más allá del final, se completan los registros intermedios
            // con registros vacíos para que la posición en el archivo siga coincidiendo con el ID.
            fseek(propiedades, 0, SEEK_END);
            for (int i = 0; i < id - totalReg; i++){
                fwrite(&REGISTRO_VACIO, sizeof(propiedad_t), 1, propiedades);
            }
            nuevo.id = id;
        }
    } while (dato.id != 0 && id <= totalReg);

    pedirFecha("Ingrese la fecha de ingreso(formato: DDMMYYYY): ", nuevo.fecha_ingreso, 1);
    pedirTexto("Ingrese la zona de la propiedad: ",
               "Opci\xa2n inv\xa0lida. Por favor, ingrese una zona v\xa0lida: ",
               nuevo.zona, sizeof(nuevo.zona));
    pedirTexto("Ingrese la ciudad/barrio de la propiedad: ",
               "Opci\xa2n inv\xa0lida. Por favor, ingrese una ciudad/barrio v\xa0lida: ",
               nuevo.ciudad_barrio, sizeof(nuevo.ciudad_barrio));
    nuevo.dormitorios = pedirEntero("Ingrese la cantidad de dormitorios de la propiedad: ",
                                    "Opci\xa2n inv\xa0lida. Por favor, ingrese una cantidad v\xa0lida: ");
    nuevo.banos = pedirEntero("Ingrese la cantidad de ba\xa4os de la propiedad: ",
                              "Opci\xa2n inv\xa0lida. Por favor, ingrese una cantidad v\xa0lida: ");
    nuevo.superficie_total = pedirReal("Ingrese la superficie total de la propiedad: ",
                                       "Opci\xa2n inv\xa0lida. Por favor, ingrese una superficie v\xa0lida(agregando '.'): ");
    nuevo.superficie_cubierta = pedirReal("Ingrese la superficie cubierta de la propiedad: ",
                                          "Opci\xa2n inv\xa0lida. Por favor, ingrese una superficie v\xa0lida(agregando '.'): ");
    nuevo.precio = pedirReal("Ingrese el valor de la propiedad: ",
                             "Opci\xa2n inv\xa0lida. Por favor, ingrese un valor v\xa0lido(agregando '.'): ");
    strcpy(nuevo.moneda, elegirMoneda());
    strcpy(nuevo.tipo_propiedad, elegirTipoPropiedad());
    strcpy(nuevo.operacion, elegirOperacion());
    strcpy(nuevo.fecha_salida, "0");
    nuevo.flag_activo = 1;

    escribirRegistro(propiedades, id, &nuevo);
    printf("Propiedad agregada exitosamente.\n");
}

static void buscarPorID(FILE *propiedades){
    propiedad_t busqueda;
    int id = pedirID();

    if (id > contarRegistros(propiedades)){
        printf("Error, no existe el ID ingresado\n");
        return;
    }
    leerRegistro(propiedades, id, &busqueda);
    if (busqueda.id == id){
        imprimirEncabezado();
        imprimirPropiedad(&busqueda);
    } else {
        printf("Error, el registro est\xa0 vac\xa1o.\n");
    }
}

// Imprime las propiedades con esa operación (y ese tipo, si no es NULL).
// Devuelve 1 si encontró alguna.
static int imprimirCoincidencias(FILE *propiedades, const char *operacion, const char *tipo){
    propiedad_t prop;
    int encontro = 0;
    fseek(propiedades, 0, SEEK_SET);
    while (fread(&prop, sizeof(propiedad_t), 1, propiedades) == 1){
        if (strcmp(prop.operacion, operacion) == 0 &&
            (tipo == NULL || strcmp(prop.tipo_propiedad, tipo) == 0)){
            imprimirPropiedad(&prop);
            encontro = 1;
        }
    }
    return encontro;
}

static void buscarPorOperacion(FILE *propiedades){
    const char *operacion = elegirOperacion();

    printf("Filtro por Operaci\xa2n\n");
    imprimirEncabezado();
    if (!imprimirCoincidencias(propiedades, operacion, NULL)){
        printf("No se encontr\xa2 la Operaci\xa2n a buscar\n");
        return;
    }

    const char *tipo = elegirTipoPropiedad();
    printf("Filtro por Operaci\xa2n y por Propiedad\n");
    imprimirEncabezado();
    if (!imprimirCoincidencias(propiedades, operacion, tipo)){
        printf("No se hallaron resultados en b\xa3squeda por Propiedad\n");
    }
}

void buscarPropiedad(FILE *propiedades){
    fflush(stdin);
    char subopcion = elegirOpcion("---------------B\xa3squeda---------------\n"
                                  "Seleccione m\x82todo de b\xa3squeda:\n"
                                  "[a]. B\xa3squeda por ID.\n"
                                  "[b]. B\xa3squeda por Operaci\xa2n.\n", "ab",
                                  "La opci\xa2n es incorrecta, ingrese otra opci\xa2n.\n");
    if (subopcion == 'a'){
        buscarPorID(propiedades);
    } else {
        buscarPorOperacion(propiedades);
    }
}

void modificarPropiedad(FILE *propiedades){
    char opcion;
    propiedad_t prop;

    printf("------------Modificar------------\n");
    int id = pedirID();
    if (id > contarRegistros(propiedades)){
        printf("El ID no se encuentra en el archivo.\n");
        return;
    }
    leerRegistro(propiedades, id, &prop);
    if (prop.id == 0){
        printf("Este registro est\xa0 vac\xa1o.\n");
        return;
    }

    printf("Usted va a modificar la siguiente propiedad:\n");
    imprimirEncabezado();
    imprimirPropiedad(&prop);
    printf("Ingrese que modificacion desea hacer:\n[a]. Ciudad/barrio.\n[b]. Precio.\n[c]. Fecha de salida.\n");
    scanf(" %c", &opcion);
    fflush(stdin);

    switch (tolower(opcion)){
        case 'a':
            pedirTexto("Ingrese la nueva ciudad/barrio de la propiedad: ",
                       "Opci\xa2n inv\xa0lida. Por favor, ingrese una ciudad/barrio v\xa0lida: ",
                       prop.ciudad_barrio, sizeof(prop.ciudad_barrio));
            break;
        case 'b':
            prop.precio = pedirReal("Ingrese el precio de la propiedad: ",
                                    "Opci\xa2n inv\xa0lida. Por favor, ingrese un precio v\xa0lido(agregando '.'): ");
            strcpy(prop.moneda, elegirMoneda());
            break;
        case 'c':
            // Cargar la fecha de salida equivale a dar de baja la propiedad.
            pedirFecha("Ingrese la fecha de salida(formato: DDMMYYYY): ", prop.fecha_salida, 1);
            prop.flag_activo = 0;
            break;
        default:
            printf(MSG_OPCION_INVALIDA);
            return;
    }
    escribirRegistro(propiedades, id, &prop);
    printf("Modificaci\xa2n exitosa.\n");
}

void bajaLogica(FILE *propiedades){
    propiedad_t busqueda;

    printf("------------Baja l\xa2gica------------\n");
    int id = pedirID();
    if (id > contarRegistros(propiedades)){
        printf("Error, no existe el ID ingresado.\n");
        return;
    }
    leerRegistro(propiedades, id, &busqueda);
    if (strcmp(busqueda.fecha_salida, "0") != 0){
        printf("Error, el registro ya tiene una fecha de salida\n");
        return;
    }

    printf("Est\xa0 seguro que quiere dar de baja a:\n");
    imprimirEncabezado();
    imprimirPropiedad(&busqueda);
    char opcion = elegirOpcion("S/N: ", "sn", "La opci\xa2n es incorrecta, ingrese otra opci\xa2n (S/N).\n");
    if (opcion == 'n'){
        printf("La baja ha sido cancelada con \x82xito.\n");
        return;
    }

    busqueda.flag_activo = 0;
    escribirRegistro(propiedades, id, &busqueda);
    fseek(propiedades, 0, SEEK_SET);
    imprimirEncabezado();
    while (fread(&busqueda, sizeof(propiedad_t), 1, propiedades) == 1){
        if (busqueda.flag_activo == 1){
            imprimirPropiedad(&busqueda);
        }
    }
}

static void generarNombreXyz(char nombre[], int tamanio){
    time_t ahora = time(NULL);
    struct tm *hoy = localtime(&ahora);
    snprintf(nombre, tamanio, "propiedades_bajas_%2d%2d%4d.xyz",
             hoy->tm_mday, hoy->tm_mon + 1, hoy->tm_year + 1900);
}

void bajaFisica(FILE *propiedades){
    FILE *bajas;
    propiedad_t prop;
    char nombreBajas[40];

    printf("------------Baja f\xa1sica------------\n");
    generarNombreXyz(nombreBajas, sizeof(nombreBajas));
    if ((bajas = fopen(nombreBajas, "a+")) == NULL){
        printf("Error en la apertura del archivo de bajas\n");
        exit(1);
    }

    int total = contarRegistros(propiedades);
    fseek(propiedades, 0, SEEK_SET);
    for (int i = 0; i < total; i++){
        fread(&prop, sizeof(propiedad_t), 1, propiedades);
        if (prop.flag_activo == 0 && prop.id != 0){
            fprintf(bajas, "%-3d %-9s %-18s %-17s %-13d %-7d %-11.2f %-14.2f %-10.2f %-8s %-11s %-19s %-8s %-7d\n",
                    prop.id, prop.fecha_ingreso, prop.zona, prop.ciudad_barrio, prop.dormitorios, prop.banos,
                    prop.superficie_total, prop.superficie_cubierta, prop.precio, prop.moneda,
                    prop.tipo_propiedad, prop.operacion, prop.fecha_salida, prop.flag_activo);
            fseek(propiedades, -(long)sizeof(propiedad_t), SEEK_CUR);
            fwrite(&REGISTRO_VACIO, sizeof(propiedad_t), 1, propiedades);
        }
    }
    printf("Baja f\xa1sica realizada con exito.\n");
    fclose(bajas);
}

void listarXyz(void){
    char nombreBajas[40];
    int caracter;

    generarNombreXyz(nombreBajas, sizeof(nombreBajas));
    FILE *bajas = fopen(nombreBajas, "r");
    if (bajas == NULL){
        printf("Error en la apertura del archivo\n");
        exit(1);
    }
    imprimirEncabezado();
    while ((caracter = fgetc(bajas)) != EOF){
        putchar(caracter);
    }
    fclose(bajas);
}
