

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


void imprimir_juego(int filas, int columnas, int** jugador1, int** jugador2){
    imprimir_mapa(filas, columnas, jugador1);
    printf("-------------------\n");
    imprimir_mapa(filas, columnas, jugador2);
}


int colocar_todos_los_barcos(int filas, int columnas, int** mapa) {
    int tamanios[] = {TAMANIO_PORTAAVIONES, TAMANIO_ACORAZADO, TAMANIO_CRUCERO, TAMANIO_SUBMARINO, TAMANIO_DESTRUCTOR};
    int ids[] = {1, 2, 3, 4, 5};
    int n_barcos = 5;

    for (int i = 0; i < n_barcos; i++) {
        int colocado = 0;
        while (!colocado) {
            int fila, columna;
            char orientacion;
            printf("Colocando barco %d (tamanio %d):\n", ids[i], tamanios[i]);
            printf("Ingrese fila, columna y orientacion (H/V): ");
            if (scanf("%d %d %c", &fila, &columna, &orientacion) != 3) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                continue;
            }
            if (colocar_barco(filas, columnas, mapa, fila, columna, tamanios[i], orientacion, ids[i])) {
                colocado = 1;
                printf("Barco colocado exitosamente.\n");
            } else {
                printf("Posicion invalida o colision. Intente nuevamente.\n");
            }
        }
    }
    return 1;
}
