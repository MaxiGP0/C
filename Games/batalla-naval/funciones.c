

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


int verificar_limites_barco(int filas, int columnas, int fila, int columna, int tamanio, char orientacion) {
    if (fila < 0 || columna < 0 || fila >= filas || columna >= columnas) {
        return 0;
    }
    if (orientacion == 'H' || orientacion == 'h') {
        if (columna + tamanio > columnas) {
            return 0;
        }
    } else if (orientacion == 'V' || orientacion == 'v') {
        if (fila + tamanio > filas) {
            return 0;
        }
    } else {
        return 0;
    }
    return 1;
}


int verificar_colision(int** mapa, int fila, int columna, int tamanio, char orientacion) {
    for (int i = 0; i < tamanio; i++) {
        int f = fila;
        int c = columna;
        if (orientacion == 'H' || orientacion == 'h') {
            c += i;
        } else {
            f += i;
        }
        if (mapa[f][c] != 0) {
            return 0;
        }
    }
    return 1;
}


int validar_colocacion_barco(int filas, int columnas, int** mapa, int fila, int columna, int tamanio, char orientacion) {
    if (!verificar_limites_barco(filas, columnas, fila, columna, tamanio, orientacion)) {
        return 0;
    }
    if (!verificar_colision(mapa, fila, columna, tamanio, orientacion)) {
        return 0;
    }
    return 1;
}


int colocar_barco(int filas, int columnas, int** mapa, int fila, int columna, int tamanio, char orientacion, int id_barco) {
    if (!validar_colocacion_barco(filas, columnas, mapa, fila, columna, tamanio, orientacion)) {
        return 0;
    }
    for (int i = 0; i < tamanio; i++) {
        int f = fila;
        int c = columna;
        if (orientacion == 'H' || orientacion == 'h') {
            c += i;
        } else {
            f += i;
        }
        mapa[f][c] = id_barco;
    }
    return 1;
}


int colocar_portaaviones(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco) {
    return colocar_barco(filas, columnas, mapa, fila, columna, TAMANIO_PORTAAVIONES, orientacion, id_barco);
}


int colocar_acorazado(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco) {
    return colocar_barco(filas, columnas, mapa, fila, columna, TAMANIO_ACORAZADO, orientacion, id_barco);
}


int colocar_crucero(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco) {
    return colocar_barco(filas, columnas, mapa, fila, columna, TAMANIO_CRUCERO, orientacion, id_barco);
}


int colocar_submarino(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco) {
    return colocar_barco(filas, columnas, mapa, fila, columna, TAMANIO_SUBMARINO, orientacion, id_barco);
}


int colocar_destructor(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco) {
    return colocar_barco(filas, columnas, mapa, fila, columna, TAMANIO_DESTRUCTOR, orientacion, id_barco);
}
