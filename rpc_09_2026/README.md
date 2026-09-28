# RPC 09 (Septiembre 26, 2026) / UTP Open 2026 — Reporte Maestro y Editorial de Estudio

Bienvenido al repositorio de análisis técnico, notas de estudio, autopsia de código y catalogación de patrones de la **9ª Actividad de la Red de Programación Competitiva (RPC 09 - Septiembre 26, 2026)**, correspondiente al conjunto oficial del **UTP Open 2026** organizado por la Universidad Tecnológica de Pereira (Colombia).

Este paquete reúne la autopsia técnica de los problemas resueltos en vivo por el equipo, las guías pedagógicas profundas de upsolving para los problemas completados post-concurso, la deconstrucción matemática de los modelos y la catalogación de antipatrones cognitivos.

---

## 1. Cuadro de Honor y Métricas del Problemset

| ID | Problema | Autor | Estado en Concurso | Dificultad | Paradigma / Algoritmo Principal | Complejidad Temporal |
| :---: | :--- | :--- | :---: | :---: | :--- | :---: |
| **A** | [Alejandro, lee por favor](outputs/notes/A_Alejandro_Lee_Por_Favor.md) | Carlos A. Salazar Meza | **AC en Vivo** | Div 3B / Div 2A | Cifrado César Dinámico + Simulación de Cadenas | `O(len(S))` |
| **B** | [Betito el viajero](outputs/notes/B_Betito_El_Viajero.md) | Jorge H. Teran Pomier | **AC en Vivo** | Div 3A / Div 2A | Conectividad en Retícula (Flood Fill / BFS Seguro) | `O(R * C)` |
| **C** | [Company](outputs/notes/C_Company.md) | Santiago Guaneme | *Upsolved* | Div 2C / Div 1A | Tree DP Bottom-Up (`P_i < i`) + Contribución de Aristas | `O(N)` |
| **D** | [Dangerous odyssey](outputs/notes/D_Dangerous_Odyssey.md) | Roberto Solís | *Upsolved* | Div 2B / Div 2C | Multi-source BFS (8D Chebyshev + 4D Manhattan + Ruta) | `O(N * M)` |
| **E** | [Enarmonía](outputs/notes/E_Enarmonia.md) | Luis D. Carreño Pitalua | *Upsolved* | Div 2D / Div 1B | DP 4D con Memoización / Rolling Array 2D | `O(T^2 * K)` |
| **F** | [Flipando colores con la DIAN](outputs/notes/F_Flipando_Colores_Con_La_DIAN.md) | María A. Velásquez Jaimes | *Upsolved* | Div 1C / Div 2E | Lawler's Scheduling (1 &#124; tree-prec &#124; sum w_i C_i) + DSU + Heap | `O(N log N)` |
| **G** | [Guanex y el diámetro con actualizaciones](outputs/notes/G_Guanex_Y_El_Diametro_Con_Actualizaciones.md) | Santiago Guaneme | *Upsolved* | Div 1B / Div 2D | Mantenimiento Dinámico de Diámetro + Binary Lifting LCA | `O((N + Q) log V)` |
| **H** | [Humbertov y su taza de café](outputs/notes/H_Humbertov_Y_Su_Taza_De_Cafe.md) | Hugo H. Morales Peña | **AC en Vivo** | Div 3C / Div 2B | Geometría (Cono Truncado) + Búsqueda Binaria de Respuesta | `O(100)` |
| **I** | [Internal triangles](outputs/notes/I_Internal_Triangles.md) | Gabriel Gutiérrez Tamayo | **AC en Vivo** | Div 3A / Div 2A | Combinatoria `C(n, 3)` + Inverso Modular `mod 10^9 + 7` | `O(1)` |
| **J** | [Juan y sus ovejas](outputs/notes/J_Juan_Y_Sus_Ovejas.md) | Jorge H. Teran Pomier | **AC en Vivo** | Div 3A / Div 2A | Componentes Conexas con DSU (Union by Size) | `O(N + P alpha(N))` |
| **K** | [K-th shortest path](outputs/notes/K_Kth_Shortest_Path.md) | Hugo H. Morales & Gabriel Gutiérrez | **AC en Vivo** | Div 2D / Div 1B | Dijkstra Iterativo con Exclusión Acumulativa de Aristas | `O(K * (M + N log N))` |
| **L** | [Locate Tobby’s nest](outputs/notes/L_Locate_Tobbys_Nest.md) | Hugo H. Morales Peña | *Upsolved* | Div 2C | Centro de Árbol (Teorema de Jordan) + Doble BFS + Gradiente | `O(H * W)` |
| **M** | [Marble tilt maze](outputs/notes/M_Marble_Tilt_Maze.md) | Samuel L. Nacache Pérez | *Upsolved* | Div 1B / Div 2D | Espacio de Estados 4D `(r1, c1, r2, c2)` + BFS con Estabilización | `O((NM)^2 * max(N, M))` |

- **Resumen Ejecutivo:**
  - **Resueltos en Vivo en Concurso:** 6 / 13 (A, B, H, I, J, K) -> 46.2% de efectividad en vivo.
  - **Upsolved Post-Concurso:** 7 / 13 (C, D, E, F, G, L, M) -> Cobertura total del 100% (13/13 cubiertos al 100%, 0 pendientes).
  - **Pendiente de Solución en Código:** 0 / 13 (Todos resueltos).
  - **Lenguajes Empleados:** C++17 (12 soluciones), Python 3 (1 solución).

---

## 2. Catálogo de Errores y Antipatrones en Vivo

A partir de la autopsia de las soluciones desarrolladas en vivo por el equipo (Problemas A, B, H, I, J, K) y los puntos críticos detectados durante el concurso:

### 2.1. El Riesgo Latente del DFS Recursivo en Retículas Grandes (Problema B - Resuelto en Vivo)
- **Manifestación:** Implementar Flood Fill mediante recursión directa `int dfs(r, c)` en una matriz de hasta `1000 x 1000`.
- **Causa Raíz:** En grafos reticulares, caminos laberínticos o serpentinas pueden generar cadenas de recursión de longitud `10^6`. La pila del sistema (`stack memory`) suele limitarse a 2 MB u 8 MB en jueces en línea, colapsando con `SIGSEGV` (*Stack Overflow*) tras ~30,000 llamadas anidadas.
- **Lección del Concurso:** Aunque los casos de prueba oficiales de Betito no contenían espirales lineales patológicas y el DFS pasó, **en producción de CP siempre debe utilizarse BFS iterativo con `std::queue`** o DFS con pila explícita en heap para garantizar estabilidad absoluta en memoria.

### 2.2. Sombreado Accidental de Parámetros Globales (*Variable Shadowing*) (Problema H - Resuelto en Vivo)
- **Manifestación:** Declarar `double r, R, h;` en el ámbito global y luego dentro de `solve()` declarar `double l = 0, r = h;`.
- **Causa Raíz:** Usar la letra `r` como abreviación de *right* en los extremos de la búsqueda binaria, ocultando el radio de la base de la taza `r`.
- **Lección del Concurso:** Funcionó de manera fortuita porque `cin >> r` leyó el radio basal antes de declarar la variable local y la función auxiliar leyó la variable global previa. Nombrar siempre los límites de búsqueda binaria como `low` y `high` para evitar colisiones con variables de dominio físico o geométrico.

### 2.3. Desbordamiento Silencioso de 32 bits y Constante `INF` Insuficiente (Problema K - Resuelto en Vivo)
- **Manifestación:** Declarar la distancia en Dijkstra como `int` con `const int inf = 1e9`.
- **Causa Raíz:** Los pesos `P` alcanzan `10^8` y `N <= 10^4`. Un camino con decenas de aristas acumula distancias superiores a `10^{10}`, desbordando los enteros de 32 bits con signo y produciendo distancias negativas.
- **Lección del Concurso:** Siempre que la suma acumulada de aristas pueda exceder `2 * 10^9`, todos los arreglos de distancias, colas de prioridad y la constante `INF` (`1e18`) deben ser estrictamente `long long`.

### 2.4. Confusión de la Variable de Estado en Cifrados (Problema A - Resuelto en Vivo)
- **Manifestación:** Riesgo de incrementar la frecuencia sobre el carácter cifrado `E` en lugar del carácter original descifrado `L`.
- **Causa Raíz:** Incrementar el contador directamente sobre el carácter leído del stream de entrada.
- **Lección del Concurso:** El equipo mantuvo la concentración y actualizó `count[l] += 1` sobre la letra descifrada, evitando una de las trampas más penalizadas del concurso.

### 2.5. Ovejas Aisladas y Casos Borde con `P = 0` (Problema J - Resuelto en Vivo)
- **Manifestación:** Riesgo de contar únicamente las ovejas involucradas en pares `P`.
- **Causa Raíz:** Inicializar el conteo de componentes solo para nodos con grado mayor a cero.
- **Lección del Concurso:** Inicializar `total = N` y `tam[i] = 1` para todos los nodos mediante `iota`, asegurando que ovejas sin relaciones formen razas individuales de tamaño 1.

---

## 3. Síntesis Técnica y Guía Pedagógica de Upsolving (Problemas C, D, E, F, G, L, M)

### A. Grafos y Árboles
- **Linealización Bottom-Up de Árboles (Problema C):** La precondición `P_i < i` significa que el árbol ya viene en orden topológico. Un bucle descendente desde `N` hasta `1` permite resolver simultáneamente la suma de distancias de todos los pares (mediante conteo de contribución de aristas `sz[i] * (N - sz[i])`) y los diámetros de cada subárbol en tiempo lineal `O(N)` y memoria estática plana `< 20 MB` sin listas de adyacencia ni recursión.
- **Extensión Dinámica de Diámetros (Problema G):** Al agregar una hoja a un árbol, el nuevo diámetro solo puede competir contra las distancias hacia los dos extremos preexistentes `A` o `B`. Mediante Binary Lifting para consultas LCA, cada actualización se procesa online en `O(log V)`.
- **Centro de un Árbol (Problema L):** Todo árbol posee 1 o 2 centros situados en el punto medio de cualquier diámetro (Teorema de Jordan). Dos BFS sucesivos encuentran los extremos del diámetro y un retroceso guiado por gradiente de distancias localiza los centros en `O(V)` sin necesidad de vectores de padres.
- **Rutas Disjuntas Acumulativas (Problema K):** Variante constructiva de caminos k-mínimos mediante exclusión voraz acumulativa de aristas usadas en cada paso de Dijkstra.

### B. Programación Dinámica y Optimización de Memoria (Problema E)
- **DP con Cintas Circulares:** Dos punteros que avanzan de forma circular con un presupuesto estricto de alternancias `K`. La formulación Top-Down memoiza `(c1, c2, k, m)` en `O(T^2 * K)`. Para optimización extrema de memoria, colapsar `c2 = t - c1` y utilizar un *rolling array* bidimensional de 2 capas que reduce el espacio de 27 MB a tan solo 180 KB.

### C. Lawler's Scheduling & Contracción de Nodos (Problema F)
- **1 \| tree-prec \| sum w_i C_i:** Teorema de Lawler (1978). El nodo con mayor densidad `w / p` debe ejecutarse inmediatamente después de su padre. Mediante DSU y un heap con borrado perezoso, los macro-nodos se colapsan sucesivamente en `O(N log N)`.

### D. Multi-Source BFS con Métricas Heterogéneas (Problema D)
- **Combinación de Distancias:** Chebyshev (L_infinito) en 8 direcciones para peligro de sirenas/brujas acotado a `H`, y Manhattan (L_1) en 4 direcciones para alcance a refugios acotado a `D`. Un BFS final en 4 direcciones sobre agua transitable determina la ruta óptima de navegación.

### E. Geometría y Búsqueda Binaria sobre Respuesta (Problema H)
- **Frustum de Cono:** La función de volumen acumulado `V(x)` es estrictamente monótona continua. 100 iteraciones de búsqueda binaria dividen el espacio en `2^{100}`, garantizando precisión por debajo de `10^{-28}`.

### F. Combinatoria Modular para Grandes Entradas (Problema I)
- **Elección de Vértices:** `C(n, 3)` para `n <= 10^{18}`. Reducción de `n mod (10^9 + 7)` previa a la multiplicación y uso del inverso modular de 6 (`166666668`).

### G. Espacio de Estados 4D y Regla de Estabilización en Laberintos (Problema M)
- **BFS con Pasos Intermedios de Costo 1:** A diferencia de *Ricochet Robots*, el jugador no está forzado a esperar a chocar con una pared; estabilizar el tablero en cualquier celda intermedia cuesta 1 movimiento e introduce múltiples vecinos por dirección. La simulación simultánea celda a celda prioriza la canica con mayor proyección escalar sobre el vector de movimiento `(r * dr + c * dc)` (efecto convoy), resolviendo colisiones directas sin solapamiento y abortando la rama de inmediato ante agujeros `'O'` o bordes abiertos en un espacio de a lo sumo 810,000 estados visitados en `< 0.15 s`.

---

## 4. Estructura de Archivos del Paquete

```text
rpc_09_2026/
├── README.md                              # Reporte maestro, matriz completa y catálogo de antipatrones
├── inputs/
│   ├── problemset/
│   │   └── UTPOpen2026v4.pdf             # Cuadernillo oficial de problemas UTP Open 2026
│   ├── solutions/                         # Soluciones aceptadas (AC) del equipo y upsolved (A - M)
│   │   ├── A_Alejandro_Lee_Por_Favor.py
│   │   ├── B_Betito_El_Viajero.cpp
│   │   ├── C_Company.cpp
│   │   ├── D_Dangerous_Odyssey.cpp
│   │   ├── E_Enarmonia.cpp
│   │   ├── F_Flipando_Colores_Con_La_DIAN.cpp
│   │   ├── G_Guanex_Y_El_Diametro_Con_Actualizaciones.cpp
│   │   ├── H_Humbertov_Y_Su_Taza_De_Cafe.cpp
│   │   ├── I_Internal_Triangles.cpp
│   │   ├── J_Juan_Y_Sus_Ovejas.cpp
│   │   ├── K_Kth_Shortest_Path.cpp
│   │   ├── L_Locate_Tobbys_Nest.cpp
│   │   └── M_Marble_Tilt_Maze.cpp
│   └── official_solutions/                # Soluciones y editoriales de referencia
│       ├── C_Company.cpp
│       ├── D_Dangerous_Odyssey.cpp
│       ├── E_Enarmonia_BottomUp.cpp
│       ├── E_Enarmonia_TopDown.cpp
│       ├── F_Flipando_Colores.cpp
│       ├── G_Guanex_Diametro.cpp
│       └── L_Locate_Tobbys_Nest.cpp
└── outputs/
    └── notes/                             # Notas individuales y autopsias técnicas (A - M)
        ├── A_Alejandro_Lee_Por_Favor.md   # [AC en Vivo]
        ├── B_Betito_El_Viajero.md         # [AC en Vivo]
        ├── C_Company.md                   # [Upsolved]
        ├── D_Dangerous_Odyssey.md         # [Upsolved]
        ├── E_Enarmonia.md                 # [Upsolved]
        ├── F_Flipando_Colores_Con_La_DIAN.md # [Upsolved]
        ├── G_Guanex_Y_El_Diametro_Con_Actualizaciones.md # [Upsolved]
        ├── H_Humbertov_Y_Su_Taza_De_Cafe.md # [AC en Vivo]
        ├── I_Internal_Triangles.md        # [AC en Vivo]
        ├── J_Juan_Y_Sus_Ovejas.md         # [AC en Vivo]
        ├── K_Kth_Shortest_Path.md         # [AC en Vivo]
        ├── L_Locate_Tobbys_Nest.md        # [Upsolved]
        └── M_Marble_Tilt_Maze.md          # [Upsolved]
```
