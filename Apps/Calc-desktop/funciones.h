#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <gtk/gtk.h>

// Estructura para almacenar el estado actual de la calculadora
typedef struct {
    double acumulador;
    char operador_pendiente;
    gboolean iniciar_nuevo_numero;
    gboolean tiene_error;
    GtkEntry *entrada_pantalla;
} CalculatorState;

// Inicializa el estado de la calculadora
void calc_init_state(CalculatorState *state, GtkEntry *entry);

// Funciones de retrollamada (callbacks) para los botones
void calc_on_number_clicked(GtkButton *button, gpointer user_data);
void calc_on_operator_clicked(GtkButton *button, gpointer user_data);
void calc_on_equals_clicked(GtkButton *button, gpointer user_data);
void calc_on_clear_clicked(GtkButton *button, gpointer user_data);

#endif /* FUNCIONES_H */
