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

char *tipoPalabra[] = {"palabraReservada","identificador","operador"};

int main(int argc, char *argv[]){
    FILE *farchivo;
    char buffer[500];
    char palabra[32];
    char c;
    char banderaEstado;

    char banderaPrimeraPalabra = 0;
    char banderaPalabraReservada = -1;


    int cLetras = 0;
    int cBuffer = 0;
    int lineaArchivo = 0;

    farchivo = fopen(argv[1], "r");
    if(farchivo == NULL) {
        perror("Error al intentar abrir el archivo");
        return 1;
    }

    while(fgets(buffer, 500, farchivo)!= NULL){
        palabra[0] = '\0';
        c = buffer[cBuffer];
        banderaEstado = tipoDeCaracter(c);
        while(c!= '\0'){
            switch(banderaEstado){
                case LETRA:                                                                /**Estado de palabra*/
                    if (palabra[0] == '\0'){
                        banderaPrimeraPalabra = 1;
                    }
                    palabra[cLetras] = c;
                    cLetras++;
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
                    if(banderaEstado != LETRA && banderaEstado != DIGITO){
                        palabra[cLetras]= '\0';
                        imprimirEn(argc, lineaArchivo, tipoPalabra[palabraReservada(palabra)], palabra, argv);
                        if(banderaPrimeraPalabra){
                            banderaPalabraReservada = palabraReservada(palabra);
                            banderaPrimeraPalabra = 0;
                        }
                        cLetras = 0;
                        break;
                    }
                    if(banderaEstado == DIGITO){  /*Un identificador puede contener digitos*/
                        banderaEstado = LETRA;
                    }
                    break;
                case PUNTUACION:
                    palabra[0] = c;
                    palabra[1] = '\0';
                    if(c == '(' || c == ')' || c == '[' || c == ']'){
                        if(banderaPalabraReservada == 0 ){
                            imprimirEn(argc, lineaArchivo, "caracterPuntuacion", palabra, argv);
                        }
                        else{
                            imprimirEn(argc, lineaArchivo, "operador", palabra, argv);
                        }

                    }
                    else{
                        imprimirEn(argc, lineaArchivo, "caracterPuntuacion", palabra, argv);
                    }
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
                    break;
                case STRINGCHAR:
                    palabra[cLetras] = c;
                    cLetras++;
                    cBuffer++;
                    c = buffer[cBuffer];
                    if(esStringOChar(c) == 0){                       /*Encuentro el " o un ' final, y salgo del String o Char*/
                        palabra[cLetras] = c;
                        cLetras++;
                        palabra[cLetras] = '\0';
                        imprimirEn(argc, lineaArchivo, "literalCadena", palabra, argv);
                        cBuffer++;
                        c = buffer[cBuffer];
                        banderaEstado = tipoDeCaracter(c);
                        cLetras = 0;
                    }
                    break;
                case OPERADOR:
                    palabra[0]=c;
                    cLetras++;
                    cBuffer++;
                    c = buffer[cBuffer];
                    if(esOperador(c)){
                        palabra[1]=c;
                        palabra[2]='\0';
                        cBuffer++;
                        c = buffer[cBuffer];
                    }
                    else{
                        palabra[1]='\0';
                    }
                    if(!strcmp(palabra, "=")){
                        if(banderaPalabraReservada == 0){
                            imprimirEn(argc, lineaArchivo, "caracterPuntuacion", palabra, argv);
                        }
                        else{
                            imprimirEn(argc, lineaArchivo, "operador", palabra, argv);
                        }
                    }
                    else{
                        imprimirEn(argc, lineaArchivo, "operador", palabra, argv);
                    }
                    banderaEstado = tipoDeCaracter(c);
                    cLetras = 0;
                    break;
                case DIGITO:
                    palabra[cLetras] = c;
                    cLetras++;
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
                    if(banderaEstado != DIGITO){
                        palabra[cLetras] = '\0';
                        imprimirEn(argc, lineaArchivo, "literalNumero", palabra, argv);
                        cLetras = 0;
                    }
                    break;
                case CUALQUIERCOSA:
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
                    break;

            }
        }
        lineaArchivo++;
        cBuffer = 0;
        banderaPrimeraPalabra = 0;
        banderaPalabraReservada = -1;
    }

    fclose(farchivo);
    printf("LECTURA FINALIZADA - Pulse una tecla para salir del programa\n");
    getchar();
    return 0;
}



