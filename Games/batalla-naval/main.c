


#include <stdio.h> 
// #include <stdlib.h>
#include "funciones.h" 



#define FILAS 10
#define COLUMNAS 10


int main(void) {


    int** Player1 = crear_mapa(FILAS, COLUMNAS);
    int** Player2 = crear_mapa(FILAS, COLUMNAS);

    imprimir_mapa(FILAS, COLUMNAS, Player1);
    printf("-------------------\n");
    imprimir_mapa(FILAS, COLUMNAS, Player2);
    





    liberar_mapa(FILAS, Player1);
    liberar_mapa(FILAS, Player2);
    return 0;

}
