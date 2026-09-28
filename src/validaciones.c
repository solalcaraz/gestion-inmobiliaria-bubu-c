#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "validaciones.h"

int validarInt(const char num[]){
    for (int i = 0; num[i] != '\0'; i++){
        if (!isdigit(num[i])){
            return 0;
        }
    }
    return 1;
}

int validarFloat(const char flotante[]){
    int cantPuntos = 0;
    for (int i = 0; flotante[i] != '\0'; i++){
        if (flotante[i] == '.'){
            cantPuntos++;
        }
        if ((!isdigit(flotante[i]) && flotante[i] != '.') || cantPuntos > 1){
            return 0;
        }
    }
    return 1;
}

static void separarFecha(const char fecha[], int *dd, int *mm, int *yy){
    *dd = (fecha[0] - '0') * 10 + (fecha[1] - '0');
    *mm = (fecha[2] - '0') * 10 + (fecha[3] - '0');
    *yy = atoi(fecha + 4);
}

int validarFecha(const char fecha[]){
    int dd, mm, yy;
    if (!validarInt(fecha) || strlen(fecha) != 8){
        return 0;
    }
    separarFecha(fecha, &dd, &mm, &yy);
    if (yy < 1900 || yy > 9999 || mm < 1 || mm > 12 || dd < 1){
        return 0;
    }
    switch (mm){
        case 4: case 6: case 9: case 11:
            return dd <= 30;
        case 2:
            return dd <= 28 || (dd == 29 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)));
        default:
            return dd <= 31;
    }
}

int compararFecha(const char fecha[]){
    struct tm fecha_tm = {0};
    int dd, mm, yy;
    if (sscanf(fecha, "%2d%2d%4d", &dd, &mm, &yy) != 3){
        return 0;
    }
    fecha_tm.tm_mday = dd;
    fecha_tm.tm_mon = mm - 1;
    fecha_tm.tm_year = yy - 1900;
    return mktime(&fecha_tm) <= time(NULL);
}

int convertirFecha(const char fecha[]){
    int dd, mm, yy;
    separarFecha(fecha, &dd, &mm, &yy);
    return yy * 10000 + mm * 100 + dd;
}

int validarTexto(const char texto[]){
    for (int i = 0; texto[i] != '\0'; i++){
        if (!isalpha(texto[i]) && !ispunct(texto[i]) && !isspace(texto[i])){
            return 0;
        }
    }
    return 1;
}

void capitalizarPalabras(char texto[]){
    for (int i = 0; texto[i] != '\0'; i++){
        if (islower(texto[i]) && (i == 0 || !isalpha(texto[i - 1]))){
            texto[i] = toupper(texto[i]);
        }
    }
}
