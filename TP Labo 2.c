// GRUPO INMOBILIARIA BUBÚ
//
// INTEGRANTES:
//      DAMIÁN PALOMBA
//      MAYLÉN MONTERDE
//      SOL ALCARAZ
//      FRANCO MEDINA



#define FILENAME "propiedades.dat"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"

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

//(PUNTO 4) Crea el archivo 'propiedades.dat'

// Crea, sobreescribe, o abre el archivo existente "propiedades.dat" segun el input del usuario.
// Si no puede abrirlo, imprime un error y termina la ejecución del programa.
FILE * crearDat(){
    FILE * propiedades;
    char opcion;
    do {
        printf ("%cDesea crear un nuevo archivo o sobrescribirlo?(S/N): ",168);
        scanf("%c", &opcion);
        fflush(stdin);
        if (tolower (opcion) == 's'){
            //Crea/sobreescribe el archivo
            propiedades = fopen ("propiedades.dat", "w+b");
            if (propiedades == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
            }
            printf ("Archivo creado o sobrescrito exitosamente.\n");
            return propiedades;
        } else if (tolower (opcion) == 'n'){
            //Abrir el archivo existente
            propiedades = fopen ("propiedades.dat", "rb+");
            if (propiedades == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
            }
            printf ("Archivo abierto exitosamente.\n");
            return propiedades;
        } else {
            printf ("Opci%cn inv%clida.\n", 162,160);
        }
    } while (tolower (opcion) != 's' || tolower (opcion) !='n');
    return NULL;
}

//(PUNTO 5) Listado del contenido del archivo

// Pide al usuario una opción entre 3 tipos de propiedad
// si es una opción válida, devuelve el caracter ingresado
// si no, pide un ingreso nuevamente.
char elegirPropiedad() {
    char opcion;
    printf("Tipo de propiedad:\n[C]. Casa\n[D]. Departamento\n[P]. PH\n");
    printf ("Seleccione el tipo de propiedad: ");
    scanf (" %c", &opcion);
    fflush(stdin);
    opcion = tolower (opcion);
    while (opcion != 'c' && opcion !='d' && opcion !='p'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (C/D/P): ", 162,160,162,160);
        scanf(" %c", &opcion);
        fflush(stdin);
        opcion = tolower (opcion);
    }
    return opcion;

}


// Imprime el encabezado correspondiente a los campos de el struct propiedad por pantalla.
void imprimirEncabezado(){
    printf("ID %c Ingreso %c         Zona       %c  Ciudad/Barrio          %c Dormitorios %c Ba%cos %c Sup.Total %c Sup.Cubierta %c  Precio       %c Moneda %c Propiedad %c     Operaci%cn     %c Salida %c Activo\n",\
            124,124,124,124,124,164,124,124,124,124,124,124,162,124,124);
}

// recibe una variable de tipo struct propiedades (propiedad_t)
// la imprime con el formato correspondiente por pantalla
void imprimirPropiedad(propiedad_t prop){
     printf("%-3d%c%-9s%c%-20s%c%-25s%c%-13d%c%-7d%c%-11.2f%c%-14.2f%c%-15.2f%c%-8s%c%-11s%c%-19s%c%-8s%c%-7d\n",
           prop.id,124, prop.fecha_ingreso,124, prop.zona,124, prop.ciudad_barrio,124, prop.dormitorios,124, prop.banos,124,
           prop.superficie_total,124, prop.superficie_cubierta,124, prop.precio,124, prop.moneda,124, prop.tipo_propiedad,124,
           prop.operacion,124, prop.fecha_salida,124, prop.flag_activo);
}

// recibe un puntero abierto al archivo binario 'propiedades'
// segun la opción elegida por el usuario, recorre el archivo en bloques de tamaño propiedad_t
// imprime por pantalla los registros que cumplan con las condiciones elegidas por el usuario.
void listarDat(FILE* propiedades){
    char opcion, op, fecha_inicio[9], fecha_fin[9];
    int aux_fecha, aux_inicio, aux_fin;
    propiedad_t prop;
    fseek(propiedades, 0, SEEK_END);
    int total = ftell(propiedades) / sizeof(propiedad_t);
    printf ("-----------------Listado-----------------\n");
    printf ("[a]. Listar todas las propiedades.\n");
    printf ("[b]. Listar solo las propiedades activas.\n");
    printf ("[c]. Listar un tipo propiedad.\n");
    printf ("[d]. Listar en un rango de tiempo.\n");
    scanf (" %c", &opcion);
    opcion = tolower(opcion);
    fflush (stdin);
    switch (opcion){
        case 'a': //todas las propiedades
            imprimirEncabezado();
            for (int i = 0; i < total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t), 1, propiedades);
                imprimirPropiedad(prop);
            }
            break;
        case 'b': //solo las activas
            imprimirEncabezado();
            for (int i = 0; i < total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t), 1, propiedades);
                if (prop.flag_activo == 1){
                    imprimirPropiedad(prop);
                }
            }
            break;
        case 'c': //un tipo de propiedad
            op = elegirPropiedad();
            imprimirEncabezado();
            for (int i = 0; i <= total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t),1, propiedades);
                if (strcmp(prop.tipo_propiedad, "Casa") == 0 && op == 'c'){
                    imprimirPropiedad(prop);
                } else if (strcmp(prop.tipo_propiedad, "PH") == 0 && op == 'p'){
                    imprimirPropiedad(prop);
                } else if (strcmp(prop.tipo_propiedad, "Depto.") == 0 && op == 'd') {
                    imprimirPropiedad(prop);
                }
            }
            break;
        case 'd': //un rango de tiempo
            printf("Ingrese la fecha m%cnima (formato: DDMMYYYY): ", 161);
            scanf("%8s", fecha_inicio);
            fflush(stdin);
            while (!validarFecha(fecha_inicio)) {
                printf("Opci%cn inv%clida. Por favor, ingrese una fecha con formato DDMMYYYY: ", 162, 160);
                scanf(" %8s", fecha_inicio);
                fflush(stdin);
            }
            aux_inicio = convertirFecha(fecha_inicio);
            printf("Ingrese la fecha m%cxima (formato: DDMMYYYY): ", 160);
            scanf("%8s", fecha_fin);
            fflush(stdin);
            while (!validarFecha(fecha_fin)) {
                printf("Opci%cn inv%clida. Por favor, ingrese una fecha con formato DDMMYYYY: ", 162, 160);
                scanf(" %8s", fecha_fin);
                fflush(stdin);
            }
            aux_fin = convertirFecha (fecha_fin);
            imprimirEncabezado();
            for (int i = 0; i < total; i++){
                fseek(propiedades, i*sizeof(propiedad_t), SEEK_SET);
                fread(&prop, sizeof(propiedad_t),1, propiedades);
                aux_fecha = convertirFecha(prop.fecha_ingreso);
                if (aux_inicio <= aux_fecha && aux_fin >= aux_fecha){
                    imprimirPropiedad(prop);
                }
            }
            break;
        default:
            printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
            break;
    }
}

//(PUNTO 1) Impresión con formato del menú principal.
void mostrarMenu(){
    printf ("--------Men%c Inicial--------\n",163);
    printf ("[a]. Listar propiedades.\n");
    printf ("[b]. Alta de una propiedad.\n");
    printf ("[c]. Buscar propiedad.\n");
    printf ("[d]. Modificar propiedades.\n");
    printf ("[e]. Baja logica de una propiedad.\n");
    printf ("[f]. Baja fisica de propiedades inactivas.\n");
    printf ("[g]. Listar baja fisica de propiedades.\n");
    printf ("[h]. Salir.\n");

}

//(PUNTO 3) Validacion de los datos ingresados
//(PUNTO 6) Alta de una propiedad
/*inserta una propiedad nueva en el archivo propiedades, en la posicion de ID correspondiente.
valida la entrada de cada campo, y pide entradas nuevas hasta que sea correcta.
llena los IDs entre el ultimo registro lleno y el nuevo con registros vacíos.*/

// recibe un string
// valida que el string contenga solamente la representación de un numero entero
// devuelve dicho número como int
int ingresoID() {
    char id[20];
    printf("Ingrese el ID de la propiedad: ");
    scanf(" %5s", id);
    fflush (stdin);
    while (!validarInt(id) || (atoi(id)==0)) {
        printf("Opci%cn inv%clida. Por favor, ingrese un n%cmero entero: ",162,160,163);
        scanf(" %5s", id);
        fflush (stdin);
    }
    return atoi(id);
}

// Pide al usuario una opción entre tipos de moneda
// si es una opción válida, devuelve el caracter ingresado
// si no, pide un ingreso nuevamente.
char elegirMoneda(){
    char opcion;
    printf("Moneda de la propiedad:\n[A]. ARS\n[U]. USD\n");
    printf ("Seleccione el tipo de moneda: ");
    scanf (" %c", &opcion);
    fflush(stdin);
    opcion = tolower (opcion);
    while (opcion != 'a' && opcion !='u'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (A/U): ", 162,160,162,160);
        scanf(" %c", &opcion);
        fflush(stdin);
        opcion = tolower (opcion);
    }
    return opcion;
}

// Pide al usuario una opción entre 3 tipos de operación inmobiliaria
// si es una opción válida, devuelve el caracter ingresado
// si no, pide un ingreso nuevamente.
char elegirOperacion() {
    char opcion;
    printf("Tipo de operacion:\n[V]. Venta\n[A]. Alquiler\n[T]. Alquiler Temporal\n");
    printf ("Seleccione el tipo de operaci%cn: ", 162);
    scanf (" %c", &opcion);
    opcion = tolower (opcion);
    while (opcion != 'a' && opcion !='v' && opcion !='t'){
        printf("Opci%cn inv%clida. Por favor, ingrese una opci%cn v%clida (V/A/T): ", 162,160,162,160);
        scanf(" %c", &opcion);
        opcion = tolower (opcion);
    }
    return opcion;
}

// Recibe un puntero abierto a un archivo binario 'propiedades'
// Pide un ID al usuario. De ser un ID valido chequea si la posición ID * sizeof(struct propiedad) está ocupada.
// Si el ID supera el la cantidad maxima de struct propiedad existentes en el archivo,
// genera y escribe 'struct propiedad' vacíos hasta alcanzar la ubicación correspondiente al ID pedido.
// Si el ID está disponible, le pide al usuario los datos necesarios para llenar un struct propiedad y los valida.
// Guarda dicho struct en la posición correspondiente con su campo 'activo' en 1.
void altaPropiedad(FILE* propiedades){
    char num[20], fecha[9], letra[30];
    propiedad_t nuevo;
    propiedad_t dato;
    propiedad_t vacio = {0,"0","0","0",0,0,0,0,0,"0","0","0","0",0};
    int id = 0, totalReg = 0;
    printf ("---------------Alta---------------\n");
    id = ingresoID();
    do {
        fseek(propiedades, 0, SEEK_END);
        totalReg = ftell(propiedades) / sizeof(propiedad_t);
        if (id <= totalReg){
            fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
            fread (&dato, sizeof(propiedad_t), 1, propiedades);
            if (dato.id != 0){
                printf("La posici%cn %d ya est%c ocupada.\n", 162, id, 160);
                id = ingresoID();
            } else {
                nuevo.id = id;
            }
        } else {
            int filasInt = id - totalReg;
            fseek(propiedades, 0, SEEK_END);
            for (int i = 0; i < filasInt ; i++){
                fwrite(&vacio, sizeof(propiedad_t),1,propiedades);
                fseek(propiedades, 0, SEEK_END);
            }
            nuevo.id = id;
        }
    } while (dato.id !=0 && id <= totalReg);

    printf("Ingrese la fecha de ingreso(formato: DDMMYYYY): ");
    scanf("%8s", fecha);
    fflush(stdin);
    while (!validarFecha(fecha) || !compararFecha(fecha)) {
        printf("Opci%cn inv%clida. Por favor, ingrese una fecha con formato DDMMYYYY: ", 162,160);
        scanf(" %8s", fecha);
        fflush(stdin);
    }
    strcpy(nuevo.fecha_ingreso, fecha);

    printf ("Ingrese la zona de la propiedad: ");
    gets(letra);
    fflush(stdin);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una zona v%clida: ", 162,160, 160);
        gets(letra);
        fflush(stdin);
    }
    validarMayus(letra);
    strcpy(nuevo.zona, letra);

    printf ("Ingrese la ciudad/barrio de la propiedad: ");
    gets(letra);
    fflush(stdin);
    while (!validarTexto(letra)){
        printf("Opci%cn inv%clida. Por favor, ingrese una ciudad/barrio v%clida: ", 162,160, 160);
        gets(letra);
        fflush(stdin);
    }
    validarMayus(letra);
    strcpy(nuevo.ciudad_barrio, letra);

    printf ("Ingrese la cantidad de dormitorios de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarInt (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una cantidad v%clida: ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    int dormi = atoi(num);
    nuevo.dormitorios = dormi;

    printf ("Ingrese la cantidad de ba%cos de la propiedad: ",164);
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarInt (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una cantidad v%clida: ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    int bano = atoi(num);
    nuevo.banos = bano;

    printf ("Ingrese la superficie total de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una superficie v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    float s_total = atof(num);
    nuevo.superficie_total = s_total;

    printf ("Ingrese la superficie cubierta de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese una superficie v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    float s_cub = atof(num);
    nuevo.superficie_cubierta = s_cub;

    printf ("Ingrese el valor de la propiedad: ");
    scanf (" %19s", num);
    fflush(stdin);
    while (!validarFloat (num)){
        printf("Opci%cn inv%clida. Por favor, ingrese un valor v%clida(agregando '.'): ", 162,160, 160);
        scanf(" %19s", num);
        fflush(stdin);
    }
    float precio = atof(num);
    nuevo.precio = precio;
    char opcionMoneda = elegirMoneda();
    if (opcionMoneda == 'a') {
    strcpy(nuevo.moneda, "PESOS");
    } else {
    strcpy(nuevo.moneda, "USD");
    }
    char opcionPropiedad = elegirPropiedad();
    if (opcionPropiedad == 'c'){
        strcpy (nuevo.tipo_propiedad, "Casa");
    } else if (opcionPropiedad == 'd') {
        strcpy (nuevo.tipo_propiedad, "Depto.");
    } else {
        strcpy (nuevo.tipo_propiedad, "PH");
    }
    char opcionOperacion = elegirOperacion();
    if (opcionOperacion == 'v'){
        strcpy (nuevo.operacion, "Venta");
    } else if (opcionOperacion == 'a') {
        strcpy (nuevo.operacion, "Alquiler");
    } else {
        strcpy (nuevo.operacion, "Alquiler temporal");
    }
    fflush(stdin);

    //Guardo el nuevo struct en el lugar que corresponda
    /*si todo esta ok, la propiedad queda activa*/

    strcpy(nuevo.fecha_salida,"0");
    nuevo.flag_activo = 1;

    fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
    fwrite(&nuevo, sizeof(propiedad_t), 1, propiedades);
    printf("Propiedad agregada exitosamente.\n");
}

//(PUNTO 7) Busqueda de datos
// Recibe un puntero abierto a un archivo 'propiedades'
// Busca propiedades por ID (acceso directo)
// Emite los datos encontrados, o un mensaje en caso de no encontrar nada
void buscarPorID(FILE * propiedades){
    int nReg = 0, aux_id = 0;
    propiedad_t busqueda;

    aux_id = ingresoID();

    fseek(propiedades, 0, SEEK_END);
    nReg = ftell(propiedades)/sizeof(propiedad_t);

    if (aux_id <= nReg){
        fseek(propiedades,(aux_id-1)*sizeof(propiedad_t),SEEK_SET);
        fread(&busqueda,sizeof(propiedad_t),1,propiedades);
        if (busqueda.id == aux_id){
            imprimirEncabezado();
            imprimirPropiedad(busqueda);
        } else {
            printf ("Error, el registro est%c vac%co.\n",131,161);}
    } else {
        printf ("Error, no existe el ID ingresado\n");
        }
}

void buscarPorOp(FILE * propiedades){

    int flag1 = 0, flag2 = 0;
    char operacion, propiedad;
    propiedad_t regBuscar,regArchivo;
    operacion = elegirOperacion();
    if (operacion == 'v'){
        strcpy (regArchivo.operacion, "Venta");
    } else if (operacion == 'a') {
        strcpy (regArchivo.operacion, "Alquiler");
    } else {
        strcpy (regArchivo.operacion, "Alquiler temporal");
    }
    fseek(propiedades,0,SEEK_SET);
    fflush(stdin);
    printf ("Filtro por Operaci%cn\n",162);
    imprimirEncabezado();
    while (fread(&regBuscar, sizeof(propiedad_t), 1, propiedades) == 1) {
        if (strcmp(regBuscar.operacion, regArchivo.operacion) == 0) {
            imprimirPropiedad(regBuscar);
            flag1 = 1;
        }
    }
    if (flag1 == 1){
        propiedad = elegirPropiedad();
        if (propiedad == 'c'){
            strcpy (regArchivo.tipo_propiedad, "Casa");
        } else if (propiedad == 'd') {
            strcpy (regArchivo.tipo_propiedad, "Depto.");
        } else {
            strcpy (regArchivo.tipo_propiedad, "PH");
        }
        fseek(propiedades,0,SEEK_SET);
        fflush(stdin);
        printf ("Filtro por Operaci%cn y por Propiedad\n",162);
        imprimirEncabezado();
        while (fread(&regBuscar, sizeof(propiedad_t), 1, propiedades) == 1) {
            if (strcmp(regBuscar.operacion, regArchivo.operacion) == 0 && strcmp(regBuscar.tipo_propiedad, regArchivo.tipo_propiedad) == 0) {
                imprimirPropiedad(regBuscar);
                flag2 = 1;
            }
        }
        if (flag2 == 0){
            printf ("No se hallaron resultados en b%csqueda por Propiedad\n",163);
        }
    } else{
        printf ("No se encontr%c la Operaci%cn a buscar\n",162,162);
    }
}

// Recibe un puntero abierto a un archivo 'propiedades'
// Muestra un submenu de opciones.
// Busca propiedades por ID (acceso directo)
// o por operación y luego por tipo de propiedad (secuencialmente).
// emite los datos encontrados, o un mensaje de no encontrar nada..
void buscarPropiedad(FILE* propiedades){
    char subopcion;
    printf ("---------------B%csqueda---------------\n", 163);
    printf ("Seleccione m%ctodo de b%csqueda:\n",130,163);
    printf ("[a]. B%csqueda por ID.\n",163);
    printf ("[b]. B%csqueda por Operaci%cn.\n",163,162);
    do{
        fflush(stdin);
        scanf (" %c",&subopcion);
        subopcion = tolower(subopcion);
        if (subopcion != 'a' && subopcion != 'b')
            printf("La opci%cn es incorrecta, ingrese otra opci%cn.\n",162,162);
    } while (subopcion != 'a' && subopcion != 'b');

    switch (subopcion){
        case 'a':
            buscarPorID(propiedades);
            break;
        case 'b':
            buscarPorOp(propiedades);
            break;
    }
}

//(PUNTO 8) Modificar datos

// Recibe un puntero abierto a un archivo binario.
// Permite modificar ciudad/barrio, precio o fecha de salida de un registro.
// Con la modificacion de la fecha de salida se modifica la baja logica
// Se validan las entradas del usuario y se pide una confirmación antes de modificar el registro.

void modificarPropiedad(FILE* propiedades){
    char num[20], letra[30], opcion, fecha[9];
    propiedad_t prop;
    printf ("------------Modificar------------\n");
    int id = ingresoID();
    fseek(propiedades, 0, SEEK_END);
    int totalReg = ftell(propiedades)/sizeof(propiedad_t);
    if (id <= totalReg){
        fseek (propiedades, (id-1)*sizeof (propiedad_t), SEEK_SET);
        fread (&prop, sizeof(propiedad_t), 1, propiedades);
        if (prop.id != 0){
            printf ("Usted va a modificar la siguiente propiedad:\n");
            imprimirEncabezado();
            imprimirPropiedad(prop);
            printf("Ingrese que modificacion desea hacer:\n[a]. Ciudad/barrio.\n[b]. Precio.\n[c]. Fecha de salida.\n");
            scanf(" %c", &opcion);
            fflush(stdin);
            opcion = tolower (opcion);
            switch (opcion){
            case 'a':
                printf ("Ingrese la nueva ciudad/barrio de la propiedad: ");
                gets(letra);
                while (!validarTexto(letra)){
                    printf("Opci%cn inv%clida. Por favor, ingrese una ciudad/barrio v%clida: ", 162,160, 160);
                    gets(letra);
                }
                validarMayus(letra);
                strcpy(prop.ciudad_barrio, letra);
                fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
                fwrite(&prop, sizeof(propiedad_t), 1, propiedades);
                printf("Modificaci%cn exitosa.\n",162);
                break;
            case 'b':
                printf ("Ingrese el precio de la propiedad: ");
                scanf (" %19s", num);
                fflush(stdin);
                while (!validarFloat(num)){
                    printf("Opci%cn inv%clida. Por favor, ingrese un precio v%clido(agregando '.'): ", 162,160, 160);
                    scanf(" %19s", num);
                    fflush(stdin);
                }
                float precio_nuevo = atof(num);
                prop.precio = precio_nuevo;
                char opcionMoneda = elegirMoneda();
                if (opcionMoneda == 'a') {
                strcpy(prop.moneda, "PESOS");
                } else {
                strcpy(prop.moneda, "USD");
                }
                fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
                fwrite(&prop, sizeof(propiedad_t), 1, propiedades);
                printf("Modificaci%cn exitosa.\n",162);
                break;
            case 'c':
                printf("Ingrese la fecha de salida(formato: DDMMYYYY): ");
                scanf(" %8s", fecha);
                fflush(stdin);
                while (!validarFecha(fecha) || !compararFecha(fecha)) {
                    printf("Opci%cn inv%clida. Por favor, ingrese una fecha con formato DDMMYYYY: ", 162,160);
                    scanf(" %8s", fecha);
                    fflush(stdin);
                }
                strcpy(prop.fecha_salida, fecha);
                prop.flag_activo = 0;
                fseek (propiedades, (id-1)*sizeof(propiedad_t), SEEK_SET);
                fwrite(&prop, sizeof(propiedad_t), 1, propiedades);
                printf("Modificaci%cn exitosa.\n",162);
                break;
            default:
                printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
                break;
            }
        } else {
            printf("Este registro est%c vac%co.\n", 160,161);
        }
    } else {
        printf("El ID no se encuentra en el archivo.\n");
    }
}

//(PUNTO 9) Baja logica.

//busca una propiedad en el archivo segun ID.
//cambia el campo "fecha de salida" por la fecha actual.
//cambia el campo "activo" a cero.
void bajaLogica(FILE* propiedades){
    int nReg,aux_id;
    char opcion, cadAux[6] = "0";
    propiedad_t busqueda;
    printf ("------------Baja l%cgica------------\n", 162);
    aux_id = ingresoID();
    fseek(propiedades, 0, SEEK_END);
    nReg = ftell(propiedades)/sizeof(propiedad_t);
    if (aux_id <= nReg){
        fseek(propiedades,(aux_id-1)*sizeof(propiedad_t),SEEK_SET);
        fread(&busqueda,sizeof(propiedad_t),1,propiedades);

        if (strcmp(busqueda.fecha_salida, cadAux) == 0){
            printf ("Est%c seguro que quiere dar de baja a:\n",160);
            imprimirEncabezado();
            imprimirPropiedad(busqueda);
            printf ("S/N: ");
            do{
                scanf (" %c",&opcion);
                fflush(stdin);
                opcion = tolower(opcion);
                if (opcion != 's' && opcion != 'n'){
                    printf("La opci%cn es incorrecta, ingrese otra opci%cn (S/N).\n",162,162);
                }
            } while (opcion != 's' && opcion != 'n');
            switch (opcion){
                case 's':
                    busqueda.flag_activo = 0;
                    fseek(propiedades,-sizeof(propiedad_t),SEEK_CUR);
                    fwrite(&busqueda, sizeof(propiedad_t),1,propiedades);
                    fseek(propiedades,0,SEEK_SET);
                    imprimirEncabezado();
                    while (fread(&busqueda, sizeof(propiedad_t), 1, propiedades) == 1) {
                        if (busqueda.flag_activo == 1) {
                            imprimirPropiedad(busqueda);
                        }
                    }
                    break;
                case 'n':
                    printf ("La baja ha sido cancelada con %cxito.\n",130);
                    break;
            }
        } else {
            printf ("Error, el registro ya tiene una fecha de salida\n");
        }
    } else {
        printf ("Error, no existe el ID ingresado.\n");
    }
}

//(PUNTO 11) Listado de propiedades con baja fisica.
//imprime los registros de bajasXyz con el formato correspondiente.
void generarNombreXyz(char nombre[]){
    time_t fechaActual;
    struct tm *fechaConvert;
    time(&fechaActual);
    fechaConvert = localtime(&fechaActual);
    sprintf(nombre,"propiedades_bajas_%2d%2d%4d.xyz",fechaConvert->tm_mday,fechaConvert->tm_mon+1,fechaConvert->tm_year+1900);
}
void listarXyz(){
    char filename[40];
    generarNombreXyz(filename);
    FILE* bajasXyz = fopen(filename,"r");
    if (bajasXyz == NULL){
                printf ("Error en la apertura del archivo\n");
                exit (1);
    }
    imprimirEncabezado();
    char caracter;
    while((caracter=fgetc(bajasXyz))!=EOF){
        printf("%c",caracter);
    }
    fclose(bajasXyz);
}

//(PUNTO 10) Baja fisica.
//crea un archivo "propiedades_bajas_<fecha>.xyz" con la fecha actual.
//en este graba todas las propiedades inactivas de "propiedades"
//simultaneamente elimina esos registros de "propiedades"
void bajaFisica(FILE* propiedades) {
    FILE* pArchivoBajas;
    int nReg;
    propiedad_t busqueda;
    propiedad_t vacio = {0, "0", "0", "0", 0, 0, 0, 0, 0, "0", "0", "0", "0", 0};
    char bajasNombre[40];
    printf ("------------Baja f%csica------------\n", 161);
    generarNombreXyz(bajasNombre);
    if ((pArchivoBajas = fopen(bajasNombre, "a+"))==NULL) {
        printf("Error en la apertura del archivo pArchivoBajas");
        exit(1);
    }

    fseek(propiedades, 0, SEEK_END);
    nReg = ftell(propiedades) / sizeof(propiedad_t);
    fseek(propiedades, 0, SEEK_SET);
    for (int i = 0; i < nReg; i++){
        fread(&busqueda, sizeof(propiedad_t), 1, propiedades);
        if (busqueda.flag_activo == 0 && busqueda.id != 0){
            fprintf(pArchivoBajas, "%-3d %-9s %-18s %-17s %-13d %-7d %-11.2f %-14.2f %-10.2f %-8s %-11s %-19s %-8s %-7d\n",
                    busqueda.id, busqueda.fecha_ingreso, busqueda.zona, busqueda.ciudad_barrio, busqueda.dormitorios,busqueda.banos,
                    busqueda.superficie_total, busqueda.superficie_cubierta, busqueda.precio,busqueda.moneda, busqueda.tipo_propiedad,
                    busqueda.operacion, busqueda.fecha_salida, busqueda.flag_activo);
            fseek(propiedades, -sizeof(propiedad_t), SEEK_CUR);
            fwrite(&vacio, sizeof(propiedad_t), 1, propiedades);
        }
    }
    printf ("Baja f%csica realizada con exito.\n",161,130);
    fclose(pArchivoBajas);
}

int main(){
    printf("%cBienvenido a Inmobiliaria Bub%c!\n", 173, 163);
    FILE* propiedades = crearDat();
    fflush(stdin);
    while(1){
        mostrarMenu();
        fflush(stdin);
        char input = getchar();
        input = tolower(input);
        switch (input) {
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
                fclose (propiedades);
                printf("Gracias por confiar en Inmobiliaria Bub%c. Saliendo del programa...\n",163);
                exit(0);
            default:
                printf("Opci%cn inv%clida. Int%cntelo de nuevo.\n", 162, 160, 130);
        }
    }
    return 0;
}
