# Problema C: Company

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Santiago Guaneme (IOI Colombia)
- **Dificultad Estimada:** Media (Div 2C / Div 1A)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [C_Company.cpp](../../inputs/solutions/C_Company.cpp)
  - Solución Oficial: [C_Company.cpp](../../inputs/official_solutions/C_Company.cpp)

---

## 1. Lógica y Enfoque del Problema

La jerarquía de una compañía de `N` empleados se modela como un árbol enraizado en el dueño (nodo 1). Se da el padre `P_i` para cada empleado `2 <= i <= N`, cumpliendo la propiedad estructural clave **`P_i < i`**.

Se deben responder dos preguntas:
1. **Suma total de distancias entre todos los pares:** `sum_{u < v} dist(u, v)`.
2. **Diámetro de cada subárbol:** `F[X]` para cada `1 <= X <= N`, donde `F[X]` es el camino simple más largo contenido íntegramente en el subárbol con raíz en `X`.

### Invariantes y Reducciones Algorítmicas

1. **Conteo por Aristas para la Suma de Distancias:**
   En lugar de calcular distancias par por par en `O(N^2)`, medimos la contribución de cada arista `(i, P_i)`.
   - Cortar esta arista divide al árbol en dos componentes: el subárbol de `i` (tamaño `sz[i]`) y el resto del árbol (tamaño `N - sz[i]`).
   - La cantidad de caminos simples que atraviesan dicha arista es exactamente `sz[i] * (N - sz[i])`.
   - Sumando sobre todo `2 <= i <= N`:
     `total_dist = sum_{i=2}^N sz[i] * (N - sz[i])`.
   - Como `total_dist` puede alcanzar hasta `N^3 / 6 ~ 1.67 * 10^17` para `N = 10^6`, se debe acumular estrictamente en un entero de 64 bits (`long long`).

2. **Diámetro de Subárbol `F[X]`:**
   El camino más largo en el subárbol de `X` puede:
   - Estar totalmente contenido en el subárbol de algún hijo `v`: `max_{v in hijos(X)} F[v]`.
   - Pasar a través de `X`, conectando los dos descendientes más lejanos en ramas distintas: `max1[X] + max2[X]`, donde `max1[X]` y `max2[X]` son las dos mayores distancias hacia abajo desde `X`.
   - Por tanto: `F[X] = max(max_{v in hijos(X)} F[v], max1[X] + max2[X])`.

3. **La Maravilla de `P_i < i` (Iteración Bottom-Up):**
   Como todo padre tiene índice menor que sus hijos, **un simple bucle decreciente desde `i = N` hasta `1` procesa los nodos en orden topológico inverso garantizado**.
   - No se necesitan listas de adyacencia (`vector<int> adj[]`).
   - No se requiere recursión ni DFS, eliminando el peligro de stack overflow.
   - El consumo de memoria es plano y estático (~20 MB), muy por debajo de los exigentes 64 MB del límite.

---

## 2. Análisis Diferencial y Puntos Críticos

- **64-bit Overflow:** El cálculo `sz[i] * (N - sz[i])` debe castearse explícitamente a `(long long)` antes del producto. Si se multiplica como enteros de 32 bits, desborda silenciosamente.
- **Formato de Salida:** Los valores `F[1], F[2], ..., F[N]` se imprimen separados por un espacio en una sola línea.

---

## 3. Trampas Cognitivas Recurrentes

1. **La trampa del árbol genérico (*Unnecessary LCA Syndrome*):**
   Intentar calcular diámetros con recorridos DFS o consultas de ancestro común (LCA). Con `N = 10^6` y 64 MB de memoria, crear `vector<int> adj[1000005]` consume más de 48 MB solo en cabeceras de vectores, rozando o excediendo el límite de memoria (*Memory Limit Exceeded*).
2. **Ignorar el orden topológico implícito en `P_i < i`:**
   Cuando los identificadores cumplen una relación de orden topológico estricto (`P_i < i`), el árbol ya viene linealizado. Procesar de `N` hacia 1 es la técnica óptima y más rápida posible.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(N)`. Un único pase lineal con operaciones aritméticas elementales `O(1)`. Ejecuta en `~0.12 s` para `N = 10^6`.
- **Complejidad Espacial:** `O(N)`. 5 arreglos estáticos de `10^6` enteros ocupan `5 * 4 MB = 20 MB`, cómodamente dentro de los 64 MB permitidos.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;

int P[MAXN];
int sz[MAXN];
int F[MAXN];
int max1_val[MAXN];
int max2_val[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    for (int i = 2; i <= N; ++i) {
        cin >> P[i];
    }

    for (int i = 1; i <= N; ++i) {
        sz[i] = 1;
        F[i] = 0;
        max1_val[i] = 0;
        max2_val[i] = 0;
    }

    long long total_dist = 0;

    for (int i = N; i >= 1; --i) {
        int path_through = max1_val[i] + max2_val[i];
        if (path_through > F[i]) {
            F[i] = path_through;
        }

        if (i > 1) {
            int p = P[i];
            sz[p] += sz[i];
            total_dist += (long long)sz[i] * (N - sz[i]);

            int branch = max1_val[i] + 1;
            if (branch >= max1_val[p]) {
                max2_val[p] = max1_val[p];
                max1_val[p] = branch;
            } else if (branch > max2_val[p]) {
                max2_val[p] = branch;
            }

            if (F[i] > F[p]) {
                F[p] = F[i];
            }
        }
    }

    cout << total_dist << "\n";
    for (int i = 1; i <= N; ++i) {
        cout << F[i] << (i == N ? "" : " ");
    }
    cout << "\n";

    return 0;
}
```
