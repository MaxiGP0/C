#include <gtk/gtk.h>
#include "funciones.h"

// Función de activación de la aplicación GTK4
static void activate(GtkApplication *app, gpointer user_data) {
    (void)user_data;

    // Crear la ventana principal
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora GTK4");
    gtk_window_set_default_size(GTK_WINDOW(window), 280, 380);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    // Contenedor principal vertical
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_widget_set_margin_start(vbox, 12);
    gtk_widget_set_margin_end(vbox, 12);
    gtk_widget_set_margin_top(vbox, 12);
    gtk_widget_set_margin_bottom(vbox, 12);
    gtk_window_set_child(GTK_WINDOW(window), vbox);

    // Entrada de texto para la pantalla de la calculadora
    GtkWidget *entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
    gtk_widget_set_halign(entry, GTK_ALIGN_FILL);
    gtk_widget_set_size_request(entry, -1, 50);
    gtk_box_append(GTK_BOX(vbox), entry);

    // Inicializar el estado de la calculadora
    CalculatorState *state = g_new0(CalculatorState, 1);
    calc_init_state(state, GTK_ENTRY(entry));

    // Cuadrícula (Grid) para organizar los botones
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);
    gtk_widget_set_vexpand(grid, TRUE);
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_box_append(GTK_BOX(vbox), grid);

    // Definición de los botones de la calculadora
    struct {
        const char *label;
        int row;
        int col;
        int width;
        int height;
        int type; // 0: número, 1: operador, 2: igual, 3: limpiar
    } buttons[] = {
        {"C", 0, 0, 2, 1, 3},
        {"/", 0, 2, 1, 1, 1},
        {"*", 0, 3, 1, 1, 1},

        {"7", 1, 0, 1, 1, 0},
        {"8", 1, 1, 1, 1, 0},
        {"9", 1, 2, 1, 1, 0},
        {"-", 1, 3, 1, 1, 1},

        {"4", 2, 0, 1, 1, 0},
        {"5", 2, 1, 1, 1, 0},
        {"6", 2, 2, 1, 1, 0},
        {"+", 2, 3, 1, 1, 1},

        {"1", 3, 0, 1, 1, 0},
        {"2", 3, 1, 1, 1, 0},
        {"3", 3, 2, 1, 1, 0},
        {"=", 3, 3, 1, 2, 2},

        {"0", 4, 0, 2, 1, 0},
        {".", 4, 2, 1, 1, 0},
    };

    // Crear y conectar las señales de cada botón
    for (size_t i = 0; i < G_N_ELEMENTS(buttons); i++) {
        GtkWidget *btn = gtk_button_new_with_label(buttons[i].label);
        gtk_widget_set_hexpand(btn, TRUE);
        gtk_widget_set_vexpand(btn, TRUE);

        if (buttons[i].type == 0) {
            g_signal_connect(btn, "clicked", G_CALLBACK(calc_on_number_clicked), state);
        } else if (buttons[i].type == 1) {
            g_signal_connect(btn, "clicked", G_CALLBACK(calc_on_operator_clicked), state);
        } else if (buttons[i].type == 2) {
            g_signal_connect(btn, "clicked", G_CALLBACK(calc_on_equals_clicked), state);
        } else if (buttons[i].type == 3) {
            g_signal_connect(btn, "clicked", G_CALLBACK(calc_on_clear_clicked), state);
        }

        gtk_grid_attach(GTK_GRID(grid), btn, buttons[i].col, buttons[i].row, buttons[i].width, buttons[i].height);
    }

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.CalculadoraGTK4", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
