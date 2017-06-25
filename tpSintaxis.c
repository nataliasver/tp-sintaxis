#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>


#define LETRA 1
#define DIGITO 2
#define OPERADOR 3
#define PUNTUACION 4
#define ESPACIO 5
#define STRINGCHAR 6
#define CUALQUIERCOSA 7


int tipoDeCaracter(char);


int main(int argc, int *argv[]){
    FILE *farchivo;
    char buffer[200];
    char palabra[32];
    char *banderaFinArch = NULL;
    char c;
    char banderaEstado;

    int cLetras = 0;
    int cBuffer = 0;
    int lineaArchivo = 0;

    farchivo = fopen((char *)argv[1], "r");
    if(farchivo == NULL) {
        perror("Error al intentar abrir el archivo");
        return 1;
    }

    banderaFinArch = fgets(buffer, 200, farchivo);

    while(banderaFinArch != NULL){
        c = buffer[cBuffer];
        banderaEstado = tipoDeCaracter(c);

        while(c!= '\0'){
            switch(banderaEstado){
                case LETRA:
                    palabra[cLetras] = c;
                    cLetras++;
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
                    if(banderaEstado != LETRA && banderaEstado != DIGITO){
                        palabra[cLetras]= '\0';
                        printf("%s; %d; indentificador\n",palabra, lineaArchivo);
                        cLetras = 0;
                        break;
                    }
                    if(banderaEstado == DIGITO){  /*Una identificador puede contener digitos*/
                        banderaEstado = LETRA;
                    }
                    break;
                case CUALQUIERCOSA:
                    printf("Esto es otra cosa\n");
                    cBuffer++;
                    c = buffer[cBuffer];
                    banderaEstado = tipoDeCaracter(c);
                    break;

            }
        }
        banderaFinArch = fgets(buffer, 200, farchivo);
        lineaArchivo++;
    }

    fclose(farchivo);

    printf("LECTURA FINALIZADA - Pulse una tecla para salir del programa\n");
    getch();


    return 0;
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
