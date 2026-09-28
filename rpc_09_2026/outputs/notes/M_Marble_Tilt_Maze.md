# Problema M: Marble tilt maze

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Samuel Leonardo Nacache Pérez (UCV Venezuela)
- **Dificultad Estimada:** Media-Alta (Div 1B / Div 2D)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [M_Marble_Tilt_Maze.cpp](../../inputs/solutions/M_Marble_Tilt_Maze.cpp)

---

## 1. Deconstrucción del Enunciado y Dinámica de Juego

El problema presenta un tablero de madera de dimensiones `N x M` (`2 <= N, M <= 30`) con los siguientes elementos:
- Celdas vacías (`'.'`).
- Paredes inamovibles (`'#'`).
- Agujeros mortales (`'O'`).
- Regiones ganadoras (`'G'`).

En el tablero se colocan **exactamente dos canicas** en las posiciones iniciales `(r1, c1)` y `(r2, c2)`.
- El tablero puede inclinarse en 4 direcciones ortogonales: arriba, abajo, izquierda o derecha.
- Al inclinar el tablero, **ambas canicas se deslizan simultáneamente** a razón de 1 casilla por unidad de tiempo en la dirección escogida.
- Dos canicas **no pueden ocupar la misma posición** en ningún momento.
- Si una o ambas canicas se salen de los límites del tablero o caen en un agujero `'O'`, se pierden irremediablemente.
- **Condición de Victoria:** Ambas canicas deben quedar situadas sobre casillas ganadoras (`'G'`) al estabilizarse el tablero.
- **Objetivo:** Encontrar la **mínima cantidad de inclinaciones** necesarias para ganar el juego, o imprimir `-1` si es imposible.

---

## 2. Observaciones Clave y Regla de Estabilización (La Trampa del Problema)

### A. Estabilización Voluntaria vs. Rebote Obligatorio
En problemas clásicos de laberintos de hielo o deslizamiento (*Ricochet Robots*, *Tilt Mazes* tradicionales), las piezas viajan obligatoriamente hasta topar contra un obstáculo o pared.

En este problema, el enunciado especifica explícitamente:
> *"Antes de cambiar de dirección, el jugador debe estabilizar el tablero (es decir, sin inclinación alguna, perfectamente plano)."*

Esto implica que **no es obligatorio esperar a que las canicas choquen contra una pared o se detengan**. El jugador puede inclinar el tablero en una dirección, dejar que las canicas rueden `k` casillas (`k >= 1`), detener el movimiento estabilizando el tablero en ese instante, y desde esa nueva configuración elegir una nueva inclinación.

En términos de teoría de grafos:
- Desde un estado actual `u`, inclinar hacia una dirección `d` no produce un único vecino terminal, sino **múltiples vecinos dirigidos**, uno por cada paso intermedio válido alcanzado antes de que el movimiento se bloquee o alguna canica se pierda.
- Todas estas transiciones intermedias tienen **costo uniforme 1** (una inclinación del tablero).

---

## 3. Física del Movimiento Simultáneo e Invariante de Colisión (Efecto Convoy)

Cuando dos canicas se mueven en la misma dirección `d = (dr, dc)`, existe el riesgo de colisión entre ellas si están alineadas en la misma fila o columna.

Para modelar correctamente el avance simultáneo celda a celda sin que se atraviesen ni se bloqueen falsamente:
1. **Prioridad por Proyección Escalar:**
   Se calcula la proyección de la posición de cada canica sobre el vector de movimiento:
   `prioridad(r, c) = r * dr + c * dc`
   - La canica con **mayor proyección** se encuentra "delante" en la dirección del movimiento y debe procesarse primero.
   - De esta forma, si la canica delantera avanza una casilla, desaloja inmediatamente su posición previa.
   - La canica trasera, al ser evaluada a continuación, encuentra dicha casilla libre y puede ingresar a ella en ese mismo ciclo de tiempo.
2. **Bloqueo Mutuo:**
   Si la canica delantera choca contra una pared `'#'` o contra el borde y no se mueve, permanece en su casilla. Cuando la canica trasera intenta avanzar hacia dicha celda, detecta la colisión (`nr == orr && nc == orc`) y se detiene también.
3. **Muerte de Rama:**
   Si cualquiera de las dos canicas cae en un agujero `'O'` o rebasa los límites del tablero, **toda la secuencia de deslizamiento en esa dirección queda abortada inmediatamente**, ya que ambas canicas deben permanecer en juego para ganar.

---

## 4. Modelado del Grafo 4D y Búsqueda BFS

- **Vértices (Estados):** La configuración completa del sistema se define mediante la 4-tupla de coordenadas de ambas canicas:
  `S = (r1, c1, r2, c2)`
  `Total de estados = (N * M)^2 <= (30 * 30)^2 = 810,000`

- **Linealización del Espacio de Estados:**
  Para máxima eficiencia y localidad de caché, el estado se mapea a un índice lineal:
  `id(a, b, x, y) = ((a * M + b) * N + x) * M + y`

- **Aristas (Transiciones):**
  Desde el estado `(a, b, x, y)`, para cada una de las 4 direcciones cardinales se itera paso a paso (`while (true)`). Tras cada paso exitoso en el que al menos una canica se mueva y ninguna muera, el estado intermedio resultante `(A, B, X, Y)` es un vecino alcanzable con distancia `dist[actual] + 1`.

- **Algoritmo:** **Breadth-First Search (BFS)** con cola `std::queue<array<int, 4>>` y arreglo de distancias `vector<int> dist(N * M * N * M, -1)`.
  Al ser aristas de peso uniforme 1, la primera vez que se extrae un estado donde `g[a][b] == 'G' && g[x][y] == 'G'`, la distancia es óptima mínima.

---

## 5. Trampas Cognitivas y Puntos de Falla Críticos

| Trampa Detectada | Manifestación / Error | Corrección Rigurosa |
| :--- | :--- | :--- |
| **Múltiples casos por archivo (EOF)** | Leer un único caso con `cin >> N >> M` y terminar. Si el juez concatena casos, produce WA en los restantes. | Envolver la ejecución en `while (cin >> N >> M) solve();` reinicializando matrices y colas. |
| **Suposición Ricochet Robots** | Forzar a que las canicas solo frenen al chocar contra paredes. | Permitir estabilización en cualquier paso `k >= 1`, agregando cada paso intermedio a la cola BFS. |
| **Colisión Frontal Falsa en Convoy** | Procesar la canica trasera primero, bloqueándola contra la delantera aunque esta fuera a avanzar en ese mismo turno. | Evaluar primero la canica con mayor proyección escalar `r * dr + c * dc`. |
| **Caída Asimétrica en Agujero / Borde** | Dejar que una canica continúe moviéndose después de que su compañera cayó al vacío o a un agujero `'O'`. | Abortar la rama de deslizamiento de inmediato (`break`) si cualquiera de las dos canicas retorna `-1`. |
| **Distancia Cero Inicial** | Procesar la cola sin verificar si el estado inicial ya cumple `win(r1, c1, r2, c2)`. | Evaluar la condición de victoria inmediatamente al extraer de la cola (retornando `0` en el estado inicial). |
| **Tableros Abiertos sin Paredes Perimetrales** | Asumir que la retícula siempre tiene un borde de `'#'`. | Validar explícitamente límites de cuadrícula (`nr < 0 \|\| nr >= N \|\| nc < 0 \|\| nc >= M`). |

---

## 6. Código de Referencia Completo (C++17)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Problema M: Marble tilt maze (RPC 09 / UTP Open 2026)
// Complejidad Temporal: O((N * M)^2 * max(N, M))
// Complejidad Espacial: O((N * M)^2) ~ 3.09 MB

int N, M;
vector<string> g;

// Direcciones: arriba, abajo, izquierda, derecha
const int DR[4] = {-1, 1, 0, 0};
const int DC[4] = {0, 0, -1, 1};

// Intenta mover UNA casilla la canica (r,c) en la direccion d.
// (orr, orc) = posicion actual de la otra canica.
// Devuelve: 0 = no se movio (pared u otra canica), 1 = se movio, -1 = se perdio (fuera o agujero)
int step(int &r, int &c, int d, int orr, int orc) {
    int nr = r + DR[d], nc = c + DC[d];
    if (nr < 0 || nr >= N || nc < 0 || nc >= M) return -1; // Se sale del tablero
    if (g[nr][nc] == '#') return 0;                          // Choca con pared
    if (nr == orr && nc == orc) return 0;                    // Choca con la otra canica
    r = nr; c = nc;
    if (g[r][c] == 'O') return -1;                           // Cae en un agujero
    return 1;
}

void solve() {
    g.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> g[i];
    }

    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;

    auto id = [&](int a, int b, int x, int y) {
        return ((a * M + b) * N + x) * M + y;
    };
    auto win = [&](int a, int b, int x, int y) {
        return g[a][b] == 'G' && g[x][y] == 'G';
    };

    vector<int> dist(N * M * N * M, -1);
    queue<array<int, 4>> q;

    int start_id = id(r1, c1, r2, c2);
    dist[start_id] = 0;
    q.push({r1, c1, r2, c2});

    while (!q.empty()) {
        auto [a, b, x, y] = q.front();
        q.pop();
        int cur = dist[id(a, b, x, y)];

        if (win(a, b, x, y)) {
            cout << cur << "\n";
            return;
        }

        for (int d = 0; d < 4; d++) {
            int A = a, B = b, X = x, Y = y;
            // La canica que va "adelante" en esta direccion se mueve primero,
            // asi la de atras puede ocupar la casilla que la delantera desaloja.
            bool firstIsOne = (a * DR[d] + b * DC[d]) >= (x * DR[d] + y * DC[d]);

            // Inclinamos paso a paso; tras cada paso el jugador puede estabilizar el tablero.
            while (true) {
                int s1, s2;
                if (firstIsOne) {
                    s1 = step(A, B, d, X, Y);
                    if (s1 == -1) break;
                    s2 = step(X, Y, d, A, B);
                } else {
                    s2 = step(X, Y, d, A, B);
                    if (s2 == -1) break;
                    s1 = step(A, B, d, X, Y);
                }

                if (s1 == -1 || s2 == -1) break; // Al menos una canica se perdio
                if (s1 == 0 && s2 == 0) break;   // Ambas canicas quedaron bloqueadas

                int k = id(A, B, X, Y);
                if (dist[k] == -1) {
                    dist[k] = cur + 1;
                    q.push({A, B, X, Y});
                }
            }
        }
    }

    cout << -1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> M) {
        solve();
    }
    return 0;
}
```

---

## 7. Análisis de Complejidad

- **Complejidad Temporal:** `O((N * M)^2 * max(N, M))`.
  En el peor caso teórico existen `(30 * 30)^2 = 810,000` estados. Para cada estado se exploran 4 direcciones con a lo sumo `max(N, M) <= 30` micro-pasos de deslizamiento. El número máximo de operaciones está acotado por `~2.4 * 10^7`, lo cual se ejecuta en `< 0.15 segundos` en C++, muy holgado respecto al límite de `1.0 s`.
- **Complejidad Espacial:** `O((N * M)^2)`.
  El arreglo `dist` linealizado de `810,000` enteros de 32 bits ocupa aproximadamente `810,000 * 4 bytes = 3.09 MB`. La cola BFS en el momento de mayor ancho contiene a lo sumo varias decenas de miles de estados (`~1 MB`), cumpliendo con holgura absoluta el límite estricto de `128 MB`.
