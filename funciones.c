#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "funciones.h"

#define LETRA 1
#define DIGITO 2
#define OPERADOR 3
#define PUNTUACION 4
#define STRINGCHAR 5
#define CUALQUIERCOSA 6

#define DDS 7           /*Dentro de String*/
#define FCCS 8          /*Fin Case Caracter y String */
#define CEDDS 9        /*Caracter Especial dentro de String*/
#define CECH 10         /*Caracter Especial dentro de Char*/
#define DDCH 11         /*Dentro de Char*/

char *pReservadas[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};
char operadores[]= {'!','~','^','*','/','%','&','>','<','|','?',':','=',','};

int estadoString = FCCS;

int esOperador(char c){
    int i = 0;
    while(i<= 13 ){
        if(c == operadores[i]){
            return 1;
        }
        i++;
    }
    return 0;

}

int palabraReservada(char* palabra){
    int i = 0;
    while(i<= 31 ){
        if(!strcmp(pReservadas[i],palabra)){
            if(!strcmp("sizeof",palabra))
                return 3;
            return 0;
        }
        i++;
    }
    return 1;
}

void imprimirEn(int cArgv, int linea, char* tipo, char* palabra, char*argv[]){
    if(cArgv == 3)
        imprimirEnArchivo((char*)argv[2], linea, tipo, palabra);
    else
        printf(" %d; %s; %s\n", linea,palabra,tipo);

}

void imprimirEnArchivo(char *rutaArchivo, int linea, char*tipo, char*palabra){
    FILE *farchivo;
    farchivo = fopen(rutaArchivo, "a");
    if(farchivo == NULL) {
        perror("Error al intentar abrir el archivo");
        return;
    }
    fprintf(farchivo, " %d; %s; %s\n",linea,palabra,tipo);
    fclose(farchivo);
}


int tipoDeCaracter(char c){
    char banderaEstado;
    if(isupper(c) || islower(c) || c == '_'){
        banderaEstado = LETRA;
    }
    else if(isdigit(c)){
        banderaEstado = DIGITO;
    }
    else if(c == '{' || c == '}' || c == ';'|| c == ',' || c == '[' || c == ']' || c == '(' || c == ')'){
        banderaEstado = PUNTUACION;
    }
    else if(c == '\"'){
        banderaEstado = STRINGCHAR;
        estadoString = DDS;
    }
    else if(c == '\''){
        banderaEstado = STRINGCHAR;
        estadoString = DDCH;
    }
    else if(esOperador(c)){
        banderaEstado = OPERADOR;
    }
    else{
        banderaEstado = CUALQUIERCOSA;
    }
    return banderaEstado;
}


int esStringOChar(char unChar){
    switch(estadoString){
        case DDS:                           /*Dentro de string*/
            switch (unChar){
                case '"':
                    estadoString = FCCS;
                    return 0;
                    break;
                case '\\':
                    estadoString = CEDDS;
                    break;
            }
            break;
        case CEDDS:                         /*Caracter especial dentro de String*/
            estadoString = DDS;
            break;
        case CECH:                          /*Catacter especial dentro de Char*/
            estadoString = DDCH;
            break;
        case DDCH:                          /*Dentro de char*/
            switch (unChar){
                case '\\':
                    estadoString = CECH;
                    break;
                case '\'':
                    estadoString = FCCS;
                    return 0;
                    break;
                default:
                    break;
            }
            break;

    }
    return 1;

}






