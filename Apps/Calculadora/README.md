# Calculadora en C con GTK4

Una aplicación de calculadora básica desarrollada en lenguaje C utilizando el toolkit gráfico GTK4. El código fuente está modularizado siguiendo buenas prácticas de separación de responsabilidades.

## Estructura del Proyecto

- **`main.c`**: Configuración de la aplicación GTK4, creación de la ventana principal y disposición de la interfaz de usuario (cuadrícula de botones y pantalla de visualización).
- **`funciones.h`**: Archivo de cabecera con las declaraciones de la estructura de estado (`CalculatorState`) y las funciones de control y lógica.
- **`funciones.c`**: Implementación de la lógica de la calculadora (operaciones aritméticas, gestión de entrada numérica, manejo de errores como división por cero) y las funciones de retrollamada (callbacks) para los botones.
- **`Makefile`**: Automatización de la compilación utilizando `pkg-config` para enlazar con GTK4.

## Requisitos Previos

Asegúrate de tener instaladas las bibliotecas de desarrollo de GTK4 y un compilador de C (como `gcc`):

- **Ubuntu / Debian / Linux Mint:**
  ```bash
  sudo apt install build-essential libgtk-4-dev pkg-config
  ```

- **Fedora:**
  ```bash
  sudo dnf install gcc gtk4-devel pkgconf
  ```

- **Arch Linux:**
  ```bash
  sudo pacman -S base-devel gtk4
  ```

## Compilación y Ejecución

1. Compila el programa ejecutando `make`:
   ```bash
   make
   ```

2. Ejecuta la calculadora:
   ```bash
   ./calculadora
   ```

3. Para limpiar los archivos binarios generados:
   ```bash
   make clean
   ```
