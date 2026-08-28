#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calc_init_state(CalculatorState *state, GtkEntry *entry) {
    state->acumulador = 0.0;
    state->operador_pendiente = '\0';
    state->iniciar_nuevo_numero = TRUE;
    state->tiene_error = FALSE;
    state->entrada_pantalla = entry;
    gtk_editable_set_text(GTK_EDITABLE(entry), "0");
}

static void actualizar_pantalla(CalculatorState *state, double valor) {
    char buf[64];
    if (valor == (long long)valor && valor > -1e12 && valor < 1e12) {
        snprintf(buf, sizeof(buf), "%lld", (long long)valor);
    } else {
        snprintf(buf, sizeof(buf), "%.8g", valor);
    }
    gtk_editable_set_text(GTK_EDITABLE(state->entrada_pantalla), buf);
}

void calc_on_number_clicked(GtkButton *button, gpointer user_data) {
    CalculatorState *state = (CalculatorState *)user_data;
    if (state->tiene_error) return;

    const char *etiqueta = gtk_button_get_label(button);
    const char *texto_actual = gtk_editable_get_text(GTK_EDITABLE(state->entrada_pantalla));

    char nuevo_texto[128];

    if (state->iniciar_nuevo_numero || strcmp(texto_actual, "0") == 0) {
        if (strcmp(etiqueta, ".") == 0) {
            snprintf(nuevo_texto, sizeof(nuevo_texto), "0.");
        } else {
            snprintf(nuevo_texto, sizeof(nuevo_texto), "%s", etiqueta);
        }
        state->iniciar_nuevo_numero = FALSE;
    } else {
        if (strcmp(etiqueta, ".") == 0 && strchr(texto_actual, '.') != NULL) {
            return;
        }
        snprintf(nuevo_texto, sizeof(nuevo_texto), "%s%s", texto_actual, etiqueta);
    }

    gtk_editable_set_text(GTK_EDITABLE(state->entrada_pantalla), nuevo_texto);
}

void calc_on_operator_clicked(GtkButton *button, gpointer user_data) {
    CalculatorState *state = (CalculatorState *)user_data;
    if (state->tiene_error) return;

    const char *etiqueta = gtk_button_get_label(button);
    char op = etiqueta[0];

    const char *texto_actual = gtk_editable_get_text(GTK_EDITABLE(state->entrada_pantalla));
    double valor_actual = g_ascii_strtod(texto_actual, NULL);

    if (state->operador_pendiente != '\0' && !state->iniciar_nuevo_numero) {
        switch (state->operador_pendiente) {
            case '+':
                state->acumulador += valor_actual;
                break;
            case '-':
                state->acumulador -= valor_actual;
                break;
            case '*':
                state->acumulador *= valor_actual;
                break;
            case '/':
                if (valor_actual == 0.0) {
                    gtk_editable_set_text(GTK_EDITABLE(state->entrada_pantalla), "Error: División por cero");
                    state->tiene_error = TRUE;
                    return;
                }
                state->acumulador /= valor_actual;
                break;
        }
    } else {
        state->acumulador = valor_actual;
    }

    state->operador_pendiente = op;
    state->iniciar_nuevo_numero = TRUE;
    actualizar_pantalla(state, state->acumulador);
}

void calc_on_equals_clicked(GtkButton *button, gpointer user_data) {
    (void)button;
    CalculatorState *state = (CalculatorState *)user_data;
    if (state->tiene_error) return;
    if (state->operador_pendiente == '\0') return;

    const char *texto_actual = gtk_editable_get_text(GTK_EDITABLE(state->entrada_pantalla));
    double valor_actual = g_ascii_strtod(texto_actual, NULL);

    switch (state->operador_pendiente) {
        case '+':
            state->acumulador += valor_actual;
            break;
        case '-':
            state->acumulador -= valor_actual;
            break;
        case '*':
            state->acumulador *= valor_actual;
            break;
        case '/':
            if (valor_actual == 0.0) {
                gtk_editable_set_text(GTK_EDITABLE(state->entrada_pantalla), "Error: División por cero");
                state->tiene_error = TRUE;
                return;
            }
            state->acumulador /= valor_actual;
            break;
    }

    actualizar_pantalla(state, state->acumulador);
    state->operador_pendiente = '\0';
    state->iniciar_nuevo_numero = TRUE;
}

void calc_on_clear_clicked(GtkButton *button, gpointer user_data) {
    (void)button;
    CalculatorState *state = (CalculatorState *)user_data;
    state->acumulador = 0.0;
    state->operador_pendiente = '\0';
    state->iniciar_nuevo_numero = TRUE;
    state->tiene_error = FALSE;
    gtk_editable_set_text(GTK_EDITABLE(state->entrada_pantalla), "0");
}
