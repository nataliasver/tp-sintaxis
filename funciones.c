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
#define ESPACIO 5
#define STRINGCHAR 6
#define CUALQUIERCOSA 7


char *pReservadas[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while"};



int palabraReservada(char* palabra){
    int i = 0;
    while(i<= 31 ){
        if(!strcmp(pReservadas[i],palabra)){
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
        printf("%s; %d; %s\n",palabra, linea,tipo);

}

void imprimirEnArchivo(char *rutaArchivo, int linea, char*tipo, char*palabra){
    FILE *farchivo;
    farchivo = fopen(rutaArchivo, "a");
    if(farchivo == NULL) {
        perror("Error al intentar abrir el archivo");
        return;
    }
    fprintf(farchivo, "%s;%d;%s\n",palabra,linea,tipo);
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
    else{
        banderaEstado = CUALQUIERCOSA;
    }
    return banderaEstado;
}



