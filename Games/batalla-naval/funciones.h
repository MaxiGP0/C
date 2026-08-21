

#ifndef FUNCIONES_H
#define FUNCIONES_H


/**
 * @brief Inicializa en cero un puntero a entero.
 *
 * Esta funcion toma un puntero a entero, y lo inicializa en cero.
 *
 * @param elemento El puntero el cual sera iniciado en cero.
 *
*/
void inicializar_en_cero(int *elemento, int i, int j, int filas, int columnas)





/**
 *  @brief Imprime un puntero a entero.
 *
 *  Esta funcion toma un puntero a entero, y lo imprime en pantalla.
 *
 *  @param elemento El puntero el cual sera impreso.
 *
*/
void imprimir_elemento(int *elemento, int i, int j, int filas, int columnas);





/**
 * @brief Recorre una matriz bidimensional dinamica y aplica una funcion a cada elemento.
 *
 * Esta funcion itera a traves de cada fila y columna de un arreglo dinamico (int**)
 * y aplica la funcion pasada por parametro a cada elemento.
 *
 * @param filas El numero total de filas.
 * @param columnas El numero total de columnas.
 * @param matriz Puntero doble (int**) a la matriz dinamica en memoria. 
 * @param accion Puntero a la funcion que se ejecutara sobre cada elemento.
 *               Debe aceptar un puntero (int*) y cuatro enteros(fila y columna actual,
 *               y su cantidad de filas y columnas) parametros.
 *
*/
void recorrer_matriz(int filas, int columnas, int** matriz,
        void (*accion)(int*, int, int, int, int));





/**
 *  @brief Crea un mapa (matriz bidimensional dinamica).
 *
 *  Esta funcion toma dos numero enteros que representan las filas y columnas, 
 *  y reserva la memoria necesaria para retornar un puntero doble a entero.
 *
 *  Nota: Es responsabilidad del usuario liberar la memoria de la matriz retornada
 *  utilizando free() despues de su uso.
 *
 *  @param filas El numero de filas del mapa.
 *  @param columnas El numero de columnas del mapa.
 *
 *  @return Retorna un puntero doble a entero que representa el mapa.
 *
 */
int** crear_mapa(int filas, int columnas);




/**
 * @brief Toma una matriz bidimensional dinamica e imprime sus elementos.
 *
 * Esta funcion toma puntero doble a entero (int**), itera sobre cada fila y columna
 * imprimiendo en pantalla sus elementos.
 *
 * @param filas El numero total de filas.
 * @param columnas El numero total de columnas.
 * @param mapa El puntero doble a entero (int**) que representa un mapa.
 * 
*/
void imprimir_mapa(int filas, int columnas, int** mapa);




/**
 *
*/
void liberar_mapa(int filas, int** mapa);










#endif /*FUNCIONES_H*/

