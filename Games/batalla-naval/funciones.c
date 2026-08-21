

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"


void inicializar_en_cero(int *elemento, int i, int j, int filas, int columnas) {
    *elemento = 0;
}


void imprimir_elemento(int *elemento, int i, int j, int filas, int columnas) {
    printf("%d ", *elemento);
    
    // Salto de línea al terminar la columna
    if (j == columnas - 1) {
        printf("\n");
    }
}


void recorrer_matriz(int filas, int columnas, int** matriz,
        void (*accion)(int*, int, int, int, int)) {

    for (int i=0; i < filas; i++) {
        for (int j=0; j < columnas; j++) {
            accion(&matriz[i][j], i, j, filas, columnas);
        }
    }
}


int** crear_mapa(int filas, int columnas) {
    // Asignamos memoria para la cantidad de filas.
    int** mapa = (int**)malloc(filas * sizeof(int*));

    // Asignamos memoria para las columnas (recorriendo las filas).
    for (int i=0; i < filas; i++) {
        mapa[i] = (int*)malloc(columnas * sizeof(int));
    }

    // Iniciamos el mapa con ceros(0).
    recorrer_matriz(filas, columnas, mapa, inicializar_en_cero);

    return mapa;
}


void imprimir_mapa(int filas, int columnas, int** mapa) {
    recorrer_matriz(filas, columnas, mapa, imprimir_elemento);
}


void liberar_mapa(int filas, int** mapa) {
    for (int i = 0; i < filas; i++) {
        free(mapa[i]); // Libera cada fila
    }
    free(mapa); // Libera el arreglo de punteros principal
}
