# Problema G: Guanex y el diámetro con actualizaciones

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Santiago Guaneme (IOI Colombia)
- **Dificultad Estimada:** Avanzada (Div 1B / Div 2D)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [G_Guanex_Y_El_Diametro_Con_Actualizaciones.cpp](../../inputs/solutions/G_Guanex_Y_El_Diametro_Con_Actualizaciones.cpp)
  - Solución Oficial: [G_Guanex_Diametro.cpp](../../inputs/official_solutions/G_Guanex_Diametro.cpp)

---

## 1. Lógica y Enfoque del Problema

Se inicia con un árbol de `N` vértices. Posteriormente, se reciben `Q` consultas online: cada una introduce una nueva hoja `x` conectada a un nodo existente `y`. Tras cada inserción, se debe reportar inmediatamente la longitud del nuevo diámetro del árbol.

### Propiedad Fundamental del Diámetro en Árboles

Sean `A` y `B` los dos extremos de un diámetro en un árbol `T`, con longitud `D = dist(A, B)`.

**Teorema de Extensión de Diámetro:**
Al conectar una nueva hoja `x` al árbol, el nuevo diámetro `D'` cumple:
`D' = max(D, dist(x, A), dist(x, B))`.

*Demostración:*
1. Todo camino simple en `T union {x}` que no contenga a `x` ya existía en `T`, por lo que su longitud está acotada por `D`.
2. Todo nuevo camino simple tiene obligatoriamente a la hoja `x` como uno de sus extremos.
3. En cualquier árbol, para cualquier nodo `x`, el nodo más alejado de `x` en todo el árbol siempre es **al menos uno de los extremos de cualquier diámetro** (`A` o `B`).
4. Por tanto, el camino más largo posible que involucra a `x` es `max(dist(x, A), dist(x, B))`.

Si la distancia supera a `D`, el diámetro se actualiza y el nuevo par de extremos pasa a ser `(x, A)` o `(x, B)`. Si no supera a `D`, el diámetro y los extremos `(A, B)` se conservan.

---

## 2. Binary Lifting Dinámico y LCA

Para medir distancias entre nodos en `O(log V)`:
`dist(u, v) = depth[u] + depth[v] - 2 * depth[lca(u, v)]`.

Como las actualizaciones únicamente añaden hojas a nodos existentes:
- Las profundidades y ancestros de los nodos preexistentes no cambian.
- Al agregar la hoja `x` conectada a `y`:
  - `depth[x] = depth[y] + 1`
  - `up[x][0] = y`
  - `up[x][i] = up[up[x][i - 1]][i - 1]` para `1 <= i < LOG`.
- Todo se calcula incrementalmente en `O(log V)` por inserción.

### Inicialización Inteligente con Doble BFS
1. Un primer BFS desde cualquier nodo localiza el extremo `A` del árbol inicial.
2. Un segundo BFS enraíza el árbol completo en `A`, calcula las profundidades iniciales, construye la tabla `up` y encuentra el otro extremo `B`.
3. El diámetro inicial es directamente `depth[B]`.

---

## 3. Trampas Cognitivas Recurrentes

1. **Recomputar el Diámetro Completo en Cada Consulta:**
   Intentar hacer un BFS en cada consulta tomaría `O(Q * V)`, dando TLE inmediato.
2. **Pensar que los dos extremos pueden cambiar arbitrariamente:**
   Creer que agregar una hoja puede generar un diámetro totalmente nuevo desconectado de `A` y `B`. La propiedad matemática garantiza que al menos uno de los extremos previos (`A` o `B`) sobrevive.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O((N + Q) log V)`. Con `N, Q <= 10^5` y `V < 3 * 10^5`, ejecuta en `~0.06 s` en C++ (límite: 1.0 s).
- **Complejidad Espacial:** `O(V log V)`. La matriz `up[300005][20]` ocupa `~24 MB`; memoria total `~30 MB`, muy por debajo de los 128 MB.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXV = 300005;
const int LOG = 20;

vector<int> adj[MAXV];
int depth[MAXV];
int up[MAXV][LOG];

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

inline int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int start_node = -1;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        start_node = u;
    }

    queue<int> q;
    vector<int> d(MAXV, -1);
    q.push(start_node);
    d[start_node] = 0;
    int A = start_node;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (d[u] > d[A]) A = u;
        for (int v : adj[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    vector<bool> vis(MAXV, false);
    q.push(A);
    vis[A] = true;
    depth[A] = 0;
    up[A][0] = A;
    int B = A;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 1; i < LOG; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
        if (depth[u] > depth[B]) B = u;

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                depth[v] = depth[u] + 1;
                up[v][0] = u;
                q.push(v);
            }
        }
    }

    int diam = depth[B];
    cout << diam << "\n";

    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;

        depth[x] = depth[y] + 1;
        up[x][0] = y;
        for (int i = 1; i < LOG; ++i) up[x][i] = up[up[x][i - 1]][i - 1];

        int da = dist(x, A);
        int db = dist(x, B);

        if (da > diam && da >= db) {
            diam = da;
            B = x;
        } else if (db > diam) {
            diam = db;
            A = x;
        }

        cout << diam << "\n";
    }

    return 0;
}
```
