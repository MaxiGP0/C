


#include <stdio.h> 
// #include <stdlib.h>
#include "funciones.h"


#define ID_PORTAAVIONES 1 // tamano 5
#define ID_ACORAZADO 2 // tamano 4
#define ID_CRUCERO 3 // tamano 3
#define ID_SUBMARINO 4 // tamano 3
#define ID_DESTRUCTOR 5 // tamano 2


#define FILAS 10
#define COLUMNAS 10


int main(void) {


    int** Player1 = crear_mapa(FILAS, COLUMNAS);
    int** Player2 = crear_mapa(FILAS, COLUMNAS);

    imprimir_juego(FILAS, COLUMNAS, Player1, Player2);

    printf("Colocacion de barcos para Jugador 1:\n");
    colocar_todos_los_barcos(FILAS, COLUMNAS, Player1);

    imprimir_juego(FILAS, COLUMNAS, Player1, Player2);

    printf("Colocacion de barcos para Jugador 2:\n");
    colocar_todos_los_barcos(FILAS, COLUMNAS, Player2);

    liberar_mapa(FILAS, Player1);
    liberar_mapa(FILAS, Player2);
    return 0;

}
