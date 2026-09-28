//Desarollo de las funciones propias para la libreria 'validaciones.h'

#include <time.h>
#include <string.h>
#include <ctype.h>

int validarInt (char num[]){
    for(int i=0; i<strlen(num); i++){
        if(!isdigit(num[i])){
            return 0;
        }
    }
    return 1;
}
int validarFloat(char flotante[]){
    int cantPuntos = 0;
    for(int i=0; i<strlen(flotante); i++){
        if(flotante[i] == '.'){
                cantPuntos++;
            }
        if((!isdigit(flotante[i]) && flotante[i] != '.') || cantPuntos>1){
            return 0;
        }
    }
    return 1;
}

int validarFecha(char fecha[]){
    if(validarInt(fecha) && strlen(fecha)==8){
        int dd,mm,yy;
        dd = (fecha[0]-48)*10 + (fecha[1]-48);
        mm = (fecha[2]-48)*10 + (fecha[3]-48);
        yy = atoi(fecha+4);
        //chequea el año
        if(yy>=1900 && yy<=9999){
            //chequea meses
            if(mm>=1 && mm<=12){
                //chequea dias
                if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                    return 1;
                else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                    return 1;
                else if((dd>=1 && dd<=28) && (mm==2))
                    return 1;
                else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))  //chequea bisiestos
                    return 1;
            }

        }
    }
    return 0;
}
int compararFecha(char fecha[]) {
    struct tm fecha_tm;
    int dd, mm, yy;
    if (sscanf(fecha, "%2d%2d%4d", &dd, &mm, &yy) != 3) {
        return 0; // Formato incorrecto
    }

    // Configurar la estructura tm con la fecha ingresada
    fecha_tm.tm_mday = dd;
    fecha_tm.tm_mon = mm - 1; // Restar 1 porque en struct tm, enero es 0
    fecha_tm.tm_year = yy - 1900; // Restar 1900 porque struct tm cuenta los años desde 1900
    fecha_tm.tm_hour = 0;
    fecha_tm.tm_min = 0;
    fecha_tm.tm_sec = 0;

    time_t fecha_actual;

    // Obtener la fecha actual
    time(&fecha_actual);

    // Comparar las fechas
    if (mktime(&fecha_tm) > fecha_actual) {
        return 0; // La fecha ingresada es mayor que la fecha actual
    } else {
        return 1; // La fecha ingresada es menor o igual que la fecha actual
    }
}
int convertirFecha(char fecha[]){
    int dd,mm,yy;
        dd = (fecha[0]-48)*10 + (fecha[1]-48);
        mm = (fecha[2]-48)*10 + (fecha[3]-48);
        yy = atoi(fecha+4);
    return (yy * 10000 + mm * 100 + dd);
}


int validarTexto (char texto[]){
    for(int j = 0; j < strlen(texto); j++){
        if(!isalpha(texto[j]) && !ispunct(texto[j]) && !isspace(texto[j])){
            return 0;
        }
    }
    return 1;
}

void validarMayus (char formato[]){

    if(islower(formato[0])){
        formato[0] = toupper(formato[0]);
    }

    for(int i = 1; i < strlen(formato); i++){
        if(islower(formato[i]) && !isalpha(formato[i-1])){
            formato[i] = toupper(formato[i]);
        }
    }
}
