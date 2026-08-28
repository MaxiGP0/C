# Chat en Tiempo Real en C (Multiplataforma)

Sistema de chat cliente-servidor desarrollado en lenguaje C utilizando sockets TCP (`Winsock2` para Windows y `POSIX sockets` para Linux/macOS). Incluye versión por consola y versión con interfaz gráfica (GUI) usando **Raylib**.

---

## Estructura del Proyecto

* **`common.h`**: Definiciones comunes y abstracción de sockets multiplataforma.
* **`server.c`**: Servidor TCP concurrente basado en `select()` capaz de gestionar múltiples clientes simultáneamente.
* **`client.c`**: Cliente de consola con hilos para envío y recepción simultánea de mensajes.
* **`client_gui.c`**: Cliente con interfaz gráfica (Raylib) que incluye botón de conexión, desconexión y chat en tiempo real.
* **`Makefile`**: Automatización de compilación para Linux.

---

## Requisitos Previos

* **Compilador C** (ej. `gcc`, `clang` o MinGW en Windows).
* **Raylib** (opcional, solo si deseas compilar la interfaz gráfica `client_gui`).
  * En Linux: `sudo apt install libraylib-dev`

---

## Compilación y Ejecución (Linux / macOS)

1. **Compilar todos los binarios:**
   ```bash
   make
   ```

2. **Iniciar el Servidor:**
   ```bash
   ./server
   ```

3. **Ejecutar el Cliente (Consola):**
   ```bash
   ./client <IP_DEL_SERVIDOR>
   ```
   *(Si es local: `./client 127.0.0.1`)*

4. **Ejecutar el Cliente (GUI con Raylib):**
   ```bash
   ./client_gui
   ```

---

## Conexión desde Windows

1. Copia `common.h`, `client.c` (o `client_gui.c`) a tu PC con Windows.
2. Compila el cliente de consola usando MinGW:
   ```cmd
   gcc client.c -o client.exe -lws2_32
   ```
3. Ejecuta el cliente apuntando a la IP del servidor Linux:
   ```cmd
   client.exe <IP_DEL_SERVIDOR_LINUX>
   ```
