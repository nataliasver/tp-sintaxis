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

char *tipoPalabra[] = {"palabraReservada","identificador"};

int main(int argc, char *argv[]){
    FILE *farchivo;
    char buffer[500];
    char palabra[32];
    char c;
    char banderaEstado;

    int cLetras = 0;
    int cBuffer = 0;
    int lineaArchivo = 0;


    farchivo = fopen(argv[1], "r");
    if(farchivo == NULL) {
        perror("Error al intentar abrir el archivo");
        return 1;
    }

    while(fgets(buffer, 500, farchivo)!= NULL){
        c = buffer[cBuffer];
        banderaEstado = tipoDeCaracter(c);
        while(c!= '\0'){
            switch(banderaEstado){
                case LETRA:                                                                /**Estado de palabra*/
                    palabra[cLetras] = c;
                    cLetras++;
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
                    if(banderaEstado != LETRA && banderaEstado != DIGITO){
                        palabra[cLetras]= '\0';
                        imprimirEn(argc, lineaArchivo, tipoPalabra[palabraReservada(palabra)], palabra, argv);
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
                    imprimirEn(argc, lineaArchivo, "caracterPuntuacion", palabra, argv);
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
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
    }

    fclose(farchivo);
    printf("LECTURA FINALIZADA - Pulse una tecla para salir del programa\n");
    getchar();
    return 0;
}



