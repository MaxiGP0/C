


#include <stdio.h> 
#include <stdlib.h>
#include "funciones.h" 


int main(void) {


    int** mapa = crear_mapa(10, 10);

    imprimir_mapa(10, 10, mapa);

    printf("\n");
    





    free(mapa);
    return 0;

}
