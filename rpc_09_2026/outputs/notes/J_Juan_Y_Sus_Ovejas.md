# Problema J: Juan y sus ovejas

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Jorge Humberto Teran Pomier (UMSA Bolivia)
- **Dificultad Estimada:** Fácil (Div 3A / Div 2A)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [J_Juan_Y_Sus_Ovejas.cpp](../../inputs/solutions/J_Juan_Y_Sus_Ovejas.cpp)

---

## 1. Lógica y Enfoque del Problema

Juan posee `N` ovejas identificadas con aretes de `1` a `N`. Juan registra `P` pares de ovejas `(u, v)` indicando que pertenecen a la misma raza. Se debe determinar:
1. `R`: Cantidad total de razas diferentes (componentes conexas del grafo).
2. `C`: Cantidad de ovejas de la raza más numerosa (tamaño de la componente conexa más grande).

La entrada consta de múltiples casos de prueba finalizados por `0 0`.

### Invariantes y Estructura Disjoint Set Union (DSU)

El problema es un caso canónico de **Conjuntos Disjuntos (DSU / Union-Find)**:
- Cada oveja inicia en su propio conjunto de tamaño 1: `total_componentes = N`, `max_tam = 1`.
- Para cada par `(u, v)`:
  - Hallamos sus líderes representativos `find(u)` y `find(v)`.
  - Si pertenecen a componentes distintas, las unimos mediante *union by size* (la más pequeña cuelga de la más grande).
  - Se decrementa el total de componentes: `total_componentes -= 1`.
  - Se actualiza el tamaño máximo: `max_tam = max(max_tam, tam[lider])`.

---

## 2. Análisis Diferencial y Puntos Críticos

En la solución del equipo [J_Juan_Y_Sus_Ovejas.cpp](../../inputs/solutions/J_Juan_Y_Sus_Ovejas.cpp):
- Se indexan las ovejas de `0` a `N - 1` con `unir(a - 1, b - 1)`.
- Se reinicializan `dsu` y `tam` en cada caso usando `iota` y `assign`.
- El manejo de casos borde donde `P = 0` (ningún par) entrega correctamente `R = N` y `C = 1`.

---

## 3. Trampas Cognitivas Recurrentes

1. **Ovejas Aisladas (*Isolated Vertex Neglect*):**
   Contar únicamente las ovejas mencionadas en los pares `P`. Toda oveja no mencionada conforma una raza independiente de tamaño 1.
2. **Reutilización de Memoria entre Casos:**
   No limpiar o no redimensionar adecuadamente las estructuras DSU entre casos consecutivos en problemas multi-test con terminación `0 0`.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(N + P * alpha(N))` por caso de prueba, donde `alpha` es la función inversa de Ackermann (`<= 4`). Para `N = 10^5, P = 2 * 10^5`, procesa cada caso en `< 0.05 s`.
- **Complejidad Espacial:** `O(N)`. Vectores de `10^5` enteros ocupan `< 2 MB`, muy por debajo de los 128 MB.

```cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int total_components;
int max_component_size;
vector<int> parent_node;
vector<int> sz;

int find_set(int v) {
    if (v == parent_node[v]) return v;
    return parent_node[v] = find_set(parent_node[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        parent_node[b] = a;
        sz[a] += sz[b];
        if (sz[a] > max_component_size) {
            max_component_size = sz[a];
        }
        total_components--;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, p;
    while (cin >> n >> p && (n != 0 || p != 0)) {
        total_components = n;
        max_component_size = 1;

        parent_node.resize(n);
        iota(parent_node.begin(), parent_node.end(), 0);
        sz.assign(n, 1);

        for (int i = 0; i < p; ++i) {
            int u, v;
            cin >> u >> v;
            union_sets(u - 1, v - 1);
        }

        cout << total_components << " " << max_component_size << "\n";
    }

    return 0;
}
```
