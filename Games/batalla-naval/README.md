# Batalla Naval en C

Juego clásico de **Batalla Naval** desarrollado en lenguaje C como proyecto modular. El objetivo es hundir todos los barcos del oponente adivinando sus coordenadas en un tablero estratégico de cuadrícula.

---

## 📋 Características

- **Estructura modular**: Separación clara entre cabeceras (`funciones.h`) y lógica de implementación (`funciones.c`).
- **Gestión dinámica de memoria**: Uso de matrices bidimensionales dinámicas para representar los tableros de juego.


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
gcc -Wall -Wextra *.c -o naval
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

## 🎮 Reglas del Juego (Clásico)

1. **Tablero**: Cada jugador cuenta con un tablero de $N \times M$ donde posiciona su flota de barcos.
2. **Disparos**: Por turnos, los jugadores ingresan coordenadas $(fila, columna)$ para atacar el tablero enemigo.
3. **Impactos y Agua**: 
   - Si se acierta a una posición ocupada por un barco, se registra un **impacto** (Tocado).
   - Si no hay barcos, se registra **agua** (Fallado).
4. **Victoria**: Gana el primer jugador en hundir todos los barcos de la flota enemiga.

---


