# Guía Rápida de Plantillas CP

Índice directo de operaciones y referencias a las plantillas de C++17.

---

## Estructuras de Datos

| Tipo de Operación | Documento / Archivo |
| :--- | :--- |
| Consulta de suma en rango y actualización puntual (iterativo, O(log N), intervalo semiabierto `[l, r)`) | [`data-structures/segment_tree_iterativo.cpp`](data-structures/segment_tree_iterativo.cpp) |
| Consulta de mínimo en rango (RMQ) y actualización puntual (recursivo, O(log N), divide y vencerás) | [`data-structures/segment_tree_recursivo.cpp`](data-structures/segment_tree_recursivo.cpp) |
| Suma en rango (Range Add) y consulta de suma en rango (Lazy Propagation, O(log N)) | [`data-structures/segment_tree_lazy_sum.cpp`](data-structures/segment_tree_lazy_sum.cpp) |
| Asignación en rango (Range Assignment) y consulta puntual/rango (Lazy Propagation, O(log N)) | [`data-structures/segment_tree_lazy_assignment.cpp`](data-structures/segment_tree_lazy_assignment.cpp) |

---

## Grafos

| Tipo de Operación | Documento / Archivo |
| :--- | :--- |
| Distancia más corta, niveles y reconstrucción de camino en grafo no ponderado (BFS, O(V + E)) | [`graphs/bfs_distancia.cpp`](graphs/bfs_distancia.cpp) |
| Búsqueda de camino entre dos nodos con salida temprana / early exit (DFS, O(V + E)) | [`graphs/dfs_camino_destino.cpp`](graphs/dfs_camino_destino.cpp) |
| Componentes conexas y costo mínimo / estadísticas acumuladas por componente (DFS, O(V + E)) | [`graphs/dfs_componente_min_costo.cpp`](graphs/dfs_componente_min_costo.cpp) |
| Ordenamiento topológico en DAG con 3 colores y detección de ciclos dirigidos (DFS post-orden, O(V + E)) | [`graphs/dfs_ordenamiento_rutas.cpp`](graphs/dfs_ordenamiento_rutas.cpp) |
| Recorrido en árboles y tamaño de subárbol sin arreglo `visited` (DFS pasando padre, O(N)) | [`graphs/dfs_arbol_sin_visited.cpp`](graphs/dfs_arbol_sin_visited.cpp) |

---

## Matemáticas

| Tipo de Operación | Documento / Archivo |
| :--- | :--- |
| Aritmética modular (suma, resta, multiplicación, división) | [`math/aritmetica_modular.cpp`](math/aritmetica_modular.cpp) |
| Exponenciación binaria modular en O(log B) | [`math/aritmetica_modular.cpp`](math/aritmetica_modular.cpp) |
| Inverso modular (Fermat para primo, Euclides Extendido para compuesto coprimo) | [`math/aritmetica_modular.cpp`](math/aritmetica_modular.cpp) |
| Combinatoria nCr y permutaciones nPr precalculadas en O(1) con módulo | [`math/aritmetica_modular.cpp`](math/aritmetica_modular.cpp) |
| Potencias de dos (verificar, siguiente, anterior, 2^k) en O(1) | [`math/bit_tricks_powers_of_two.cpp`](math/bit_tricks_powers_of_two.cpp) |
| Manipulación de bits (aislar/limpiar LSB, popcount, clz, ctz, floor log2) en O(1) | [`math/bit_tricks_powers_of_two.cpp`](math/bit_tricks_powers_of_two.cpp) |
| Criba lineal de Euler y Menor Factor Primo (SPF) en O(MAXN) | [`math/criba_spf.cpp`](math/criba_spf.cpp) |
| Factorización prima rápida en O(log X) y enumeración de divisores con SPF | [`math/criba_spf.cpp`](math/criba_spf.cpp) |
| Función Phi de Euler (O(log X) con SPF precalculado o O(sqrt N) aislada) | [`math/criba_spf.cpp`](math/criba_spf.cpp) |
| Teoría de juegos: Juego de Nim clásico y predicción de victoria con Nim-Sum | [`math/game_theory_nim.cpp`](math/game_theory_nim.cpp) |
| Cálculo de MEX (Minimum Excluded) en O(K) | [`math/game_theory_nim.cpp`](math/game_theory_nim.cpp) |
| Prefijo y rango XOR acumulado (1 ^ ... ^ N y L ^ ... ^ R) en O(1) | [`math/game_theory_nim.cpp`](math/game_theory_nim.cpp) |
| Multiplicación y exponenciación rápida de matrices cuadradas en O(N^3 log P) | [`math/matrix_exponentiation.cpp`](math/matrix_exponentiation.cpp) |
| Aceleración de recurrencias lineales (Fibonacci / DP) para N hasta 10^18 | [`math/matrix_exponentiation.cpp`](math/matrix_exponentiation.cpp) |
| Conteo de caminos de longitud exacta k en grafos dirigidos | [`math/matrix_exponentiation.cpp`](math/matrix_exponentiation.cpp) |

---

## Geometría

| Tipo de Operación | Documento / Archivo |
| :--- | :--- |
| Representación de puntos 2D y operaciones vectoriales enteras (suma, resta, producto punto) | [`geometry/geometria_basica.cpp`](geometry/geometria_basica.cpp) |
| Orientación de 3 puntos (giro CCW, CW, colineal) con producto cruz en O(1) | [`geometry/geometria_basica.cpp`](geometry/geometria_basica.cpp) |
| Intersección robusta de segmentos de recta (cruces propios, colineales y extremos) en O(1) | [`geometry/geometria_basica.cpp`](geometry/geometria_basica.cpp) |
| Área exacta de polígono simple con fórmula de Shoelace (`area2 = 2 * Área`) en O(N) | [`geometry/geometria_basica.cpp`](geometry/geometria_basica.cpp) |