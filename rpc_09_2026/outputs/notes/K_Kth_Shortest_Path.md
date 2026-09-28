# Problema K: K-th shortest path

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Hugo Humberto Morales & Gabriel Gutiérrez (UTP Colombia)
- **Dificultad Estimada:** Media-Alta (Div 2D / Div 1B)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [K_Kth_Shortest_Path.cpp](../../inputs/solutions/K_Kth_Shortest_Path.cpp)

---

## 1. Lógica y Enfoque del Problema

Se dispone de un grafo no dirigido con pesos positivos (`N <= 10^4`, `M <= 10^5`, pesos `P <= 10^8`), un vértice origen `S`, un destino `D` y un entero `K <= 10`.

### La Definición Particular del *k-ésimo* Camino
A diferencia del problema clásico de caminos k-mínimos de Yen (donde los caminos pueden compartir aristas y subrutas), el enunciado impone una regla constructiva tajante:
> *"el k-ésimo recorrido más corto no puede incluir alguna arista que pertenezca a alguno de los 1-ésimo, 2-ésimo, ..., (k - 1)-ésimo recorridos más cortos."*

Esto reduce el problema a un algoritmo iterativo de **eliminación voraz de aristas**:
1. Para cada paso `step` de `1` a `K - 1`:
   - Se ejecuta el algoritmo de Dijkstra desde `S`.
   - Se reconstruye el camino mínimo hasta `D` mediante punteros de padres `p[u]`.
   - Se **deshabilitan todas las aristas pertenecientes a este camino** (asignando su peso a infinito o marcándolas como eliminadas).
2. En el paso `K`:
   - Se ejecuta Dijkstra una última vez sobre el grafo resultante.
   - La distancia calculada y el camino reconstruido corresponden exactamente a la respuesta solicitada.
   - Se garantiza unicidad de la solución en los datos de prueba.

---

## 2. Análisis Diferencial y Puntos Críticos

En la versión del equipo [K_Kth_Shortest_Path.cpp](../../inputs/solutions/K_Kth_Shortest_Path.cpp):
- Se emplea una cola de prioridad `std::priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<...>>`.
- Para reconstruir la ruta, se retrocede desde `D` hasta `S` con `cur = p[cur]` y luego se invierte el vector.
- Formato de salida:
  - Línea 1: distancia total.
  - Línea 2: vértices separados por `" - "` (ejemplo: `3 - 5 - 6`).

---

## 3. Trampas Cognitivas y Errores Fatales Potenciales

1. **Desbordamiento de 32 bits (*Integer Overflow*):**
   Los pesos `P` alcanzan `10^8` y `N <= 10^4`. Un camino con 100 aristas puede acumular `10^{10}`, superando con creces la cota de `2 * 10^9` de un `int` con signo.
   - Si la distancia se declara como `int`, se produce desbordamiento con números negativos y ciclos erróneos.
   - Si la constante `INF` se fija en `1e9`, rutas legítimas con distancia `> 1e9` son descartadas o consideradas inalcanzables.
   - **Solución Obligatoria:** Todas las distancias y pesos acumulados deben ser `long long`, y el valor infinito debe ser `INF = 1e18`.
2. **Confundir con el Algoritmo de Yen General:**
   Modelar el problema como k-shortest paths tradicional con grafos residuales complejos o ramificaciones de prefijos. La regla del problema es estrictamente de exclusión acumulativa de aristas usadas.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(K * (M + N log N))`. Como `K <= 10`, se realizan a lo sumo 10 ejecuciones de Dijkstra. Para `N = 10^4` y `M = 10^5`, el tiempo total es `< 0.20 s` en C++ (límite: 2.0 s).
- **Complejidad Espacial:** `O(N + M)` para almacenar el grafo de adyacencia y arreglos de distancias (~10 MB, límite: 128 MB).

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
const int MAXN = 10005;

struct Edge {
    int to;
    long long weight;
    int id;
    bool disabled;
};

vector<Edge> adj[MAXN];
long long dist_node[MAXN];
int parent_node[MAXN];
int parent_edge_idx[MAXN];

void dijkstra(int s, int n) {
    for (int i = 1; i <= n; ++i) {
        dist_node[i] = INF;
        parent_node[i] = -1;
        parent_edge_idx[i] = -1;
    }

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist_node[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist_node[u]) continue;

        for (int i = 0; i < (int)adj[u].size(); ++i) {
            auto& edge = adj[u][i];
            if (edge.disabled) continue;

            int v = edge.to;
            long long w = edge.weight;

            if (dist_node[u] + w < dist_node[v]) {
                dist_node[v] = dist_node[u] + w;
                parent_node[v] = u;
                parent_edge_idx[v] = i;
                pq.push({dist_node[v], v});
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k, s, d;
    if (!(cin >> n >> m >> k >> s >> d)) return 0;

    int edge_id_counter = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w, edge_id_counter, false});
        adj[v].push_back({u, w, edge_id_counter, false});
        edge_id_counter++;
    }

    for (int step = 1; step < k; ++step) {
        dijkstra(s, n);

        int cur = d;
        while (cur != s && cur != -1) {
            int p = parent_node[cur];
            int edge_idx = parent_edge_idx[cur];
            int edge_id = adj[p][edge_idx].id;

            // Deshabilitar la arista en ambas direcciones
            adj[p][edge_idx].disabled = true;
            for (auto& back_edge : adj[cur]) {
                if (back_edge.id == edge_id) {
                    back_edge.disabled = true;
                    break;
                }
            }
            cur = p;
        }
    }

    dijkstra(s, n);

    vector<int> path;
    int cur = d;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent_node[cur];
    }
    reverse(path.begin(), path.end());

    cout << dist_node[d] << "\n";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i + 1 == path.size() ? "" : " - ");
    }
    cout << "\n";

    return 0;
}
```
