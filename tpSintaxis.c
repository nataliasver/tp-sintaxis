#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, int *argv[]){
    FILE *farchivo;
    char buffer[200];
    char palabra[100];
    char *banderaFinArch = NULL;

    farchivo = fopen((char *)argv[1], "r");

    if(farchivo == NULL) {
        perror("Error al intentar abrir el archivo");
        return 1;
    }

    do{
          if (banderaFinArch != NULL)
            printf("%s\n", buffer);
          banderaFinArch = fgets(buffer, 200, farchivo);

    }while (banderaFinArch != NULL); //Si pongo eof no corta!

    fclose(farchivo);


    if(argc == 3){
        printf("Leo el archivo y lo guardo en %s",argv[2]);
    }
    else{
        printf("Leo el archivo e imprimo los datos en pantalla\n");
    }
    printf("LECTURA FINALIZADA - Pulse una tecla para salir del programa\n");
    getch();

    return 0;
}
