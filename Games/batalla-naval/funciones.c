

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"


void inicializar_en_cero(int *elemento) {
    *elemento=0;
}


void imprimir_elemento(int *elemento) {
    printf("%d ", *elemento);
}


void recorrer_matriz(int filas, int columnas, int** matriz, void (*accion)(int*)) {

    for (int i=0; i < filas; i++) {
        for (int j=0; j < columnas; j++) {
            accion(&matriz[i][j]);
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
