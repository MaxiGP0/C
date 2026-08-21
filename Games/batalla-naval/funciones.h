

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
void inicializar_en_cero(int *elemento);





/**
 *  @brief Imprime un puntero a entero.
 *
 *  Esta funcion toma un puntero a entero, y lo imprime en pantalla.
 *
 *  @param elemento El puntero el cual sera impreso.
 *
*/
void imprimir_elemento(int *elemento);





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
 *               Debe aceptar un puntero (int*) como unico parametro.
 *
*/
void recorrer_matriz(int filas, int columnas, int** matriz, void (*accion)(int*));





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













#endif /*FUNCIONES_H*/

