

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
void inicializar_en_cero(int *elemento, int i, int j, int filas, int columnas);





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
 * @brief Libera la memoria asignada para un mapa (matriz bidimensional dinamica).
 *
 * Esta funcion recorre cada una de las filas del mapa liberando su memoria asignada,
 * y finalmente libera el arreglo de punteros principal.
 *
 * @param filas El numero total de filas del mapa.
 * @param mapa El puntero doble a entero (int**) que representa el mapa a liberar.
 * 
*/
void liberar_mapa(int filas, int** mapa);



/**
 * @brief Constantes para los tamaños de los 5 tipos de barcos (ordenados del más grande al más chico).
 */
#define TAMANIO_PORTAAVIONES 5
#define TAMANIO_ACORAZADO 4
#define TAMANIO_CRUCERO 3
#define TAMANIO_SUBMARINO 3
#define TAMANIO_DESTRUCTOR 2

/**
 * @brief Constantes para las orientaciones de los barcos.
 */
#define ORIENTACION_HORIZONTAL 'H'
#define ORIENTACION_VERTICAL 'V'

/**
 * @brief Verifica si las coordenadas y tamaño de un barco se encuentran dentro de los límites del mapa.
 * 
 * @param filas Número total de filas del mapa.
 * @param columnas Número total de columnas del mapa.
 * @param fila Fila inicial del barco.
 * @param columna Columna inicial del barco.
 * @param tamanio Tamaño (longitud) del barco.
 * @param orientacion Orientación del barco ('H' para horizontal, 'V' para vertical).
 * @return int Retorna 1 si está dentro de los límites, 0 en caso contrario.
 */
int verificar_limites_barco(int filas, int columnas, int fila, int columna, int tamanio, char orientacion);

/**
 * @brief Verifica si hay colisión con otros barcos en las casillas donde se ubicaría el barco.
 * 
 * @param mapa Puntero doble a entero que representa el tablero.
 * @param fila Fila inicial del barco.
 * @param columna Columna inicial del barco.
 * @param tamanio Tamaño (longitud) del barco.
 * @param orientacion Orientación del barco ('H' para horizontal, 'V' para vertical).
 * @return int Retorna 1 si las casillas están libres, 0 si hay colisión.
 */
int verificar_colision(int** mapa, int fila, int columna, int tamanio, char orientacion);

/**
 * @brief Valida si un barco puede ser colocado en la posición y orientación indicadas.
 * 
 * @param filas Número total de filas del mapa.
 * @param columnas Número total de columnas del mapa.
 * @param mapa Puntero doble a entero que representa el tablero.
 * @param fila Fila inicial del barco.
 * @param columna Columna inicial del barco.
 * @param tamanio Tamaño (longitud) del barco.
 * @param orientacion Orientación del barco ('H' para horizontal, 'V' para vertical).
 * @return int Retorna 1 si la colocación es válida, 0 en caso contrario.
 */
int validar_colocacion_barco(int filas, int columnas, int** mapa, int fila, int columna, int tamanio, char orientacion);

/**
 * @brief Coloca un barco genérico en el mapa si la posición es válida.
 * 
 * @param filas Número total de filas del mapa.
 * @param columnas Número total de columnas del mapa.
 * @param mapa Puntero doble a entero que representa el tablero.
 * @param fila Fila inicial del barco.
 * @param columna Columna inicial del barco.
 * @param tamanio Tamaño (longitud) del barco.
 * @param orientacion Orientación del barco ('H' para horizontal, 'V' para vertical).
 * @param id_barco Identificador numérico del barco para marcar en la matriz.
 * @return int Retorna 1 si se colocó exitosamente, 0 en caso contrario.
 */
int colocar_barco(int filas, int columnas, int** mapa, int fila, int columna, int tamanio, char orientacion, int id_barco);

/**
 * @brief Coloca el Portaaviones (Tamaño 5 - El más grande).
 */
int colocar_portaaviones(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco);

/**
 * @brief Coloca el Acorazado (Tamaño 4).
 */
int colocar_acorazado(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco);

/**
 * @brief Coloca el Crucero (Tamaño 3).
 */
int colocar_crucero(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco);

/**
 * @brief Coloca el Submarino (Tamaño 3).
 */
int colocar_submarino(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco);

/**
 * @brief Coloca el Destructor (Tamaño 2 - El más chico).
 */
int colocar_destructor(int filas, int columnas, int** mapa, int fila, int columna, char orientacion, int id_barco);










#endif /*FUNCIONES_H*/

