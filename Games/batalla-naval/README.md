# Batalla Naval en C

Juego clásico de **Batalla Naval** desarrollado en lenguaje C como proyecto modular. El objetivo es hundir todos los barcos del oponente adivinando sus coordenadas en un tablero estratégico de cuadrícula.

---

## 📋 Características

- **Estructura modular**: Separación clara entre cabeceras (`funciones.h`) y lógica de implementación (`funciones.c`).
- **Gestión dinámica de memoria**: Uso de matrices bidimensionales dinámicas para representar los tableros de juego.
- **Flota configurable**: Colocación interactiva de barcos (Portaaviones, Acorazado, Crucero, Submarino y Destructor) con validación de límites y colisiones.
- **Privacidad entre turnos**: Ocultación de tableros durante la colocación de barcos y en los disparos por turnos (`imprimir_mapa_oculto` y `limpiar_pantalla`).
- **Condición de victoria**: Sistema de turnos que verifica barcos vivos hasta que un jugador hunda toda la flota enemiga.

---

## 🗂️ Estructura del Proyecto

```text
batalla-naval/
│
├── funciones.h     # Declaraciones de funciones y documentación de la API del juego
├── funciones.c     # Implementación de la lógica de tableros y utilidades
├── main.c          # Punto de entrada y flujo principal del juego
└── README.md       # Documentación del proyecto
```

---

## 🚀 Compilación y Ejecución

Asegúrate de tener instalado un compilador de C (como `gcc`).

### 1. Compilar el proyecto
```bash
gcc *.c -o naval
```

### 2. Ejecutar el juego
- **En Linux / macOS:**
  ```bash
  ./naval
  ```
- **En Windows:**
  ```cmd
  naval.exe
  ```

---

## 🎮 Reglas del Juego

1. **Tablero**: Cada jugador cuenta con un tablero de $10 \times 10$ donde posiciona su flota de barcos.
2. **Colocación**: Cada jugador coloca su flota de forma secreta (usando saltos de línea para preservar privacidad).
3. **Disparos**: Por turnos, los jugadores ingresan coordenadas $(fila, columna)$ para atacar el tablero enemigo. El mapa enemigo oculta los barcos vivos y solo muestra los disparos (agua `-1` e impactos `-2`).
4. **Impactos y Agua**: 
   - Si se acierta a una posición ocupada por un barco, se registra un **impacto** (Tocado, marcado como `-2`).
   - Si no hay barcos, se registra **agua** (Fallado, marcado como `-1`).
5. **Victoria**: Gana el primer jugador en hundir todos los barcos de la flota enemiga.



