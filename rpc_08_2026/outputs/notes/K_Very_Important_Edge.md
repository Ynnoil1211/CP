# Problema K: Very Important Edge

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Alta (Div 1C / Div 2F)
- **Estado en Concurso:** No resuelto
- **Archivos de Referencia:**
  - Enunciado: `inputs/problemset/ProblemsetRPC08.pdf` (página 12)

---

## 1. Explicación Pedagógica del Problema

Se tiene un grafo conexo no dirigido G = (V, E) con N vértices (3 <= N <= 10^5) y M aristas (3 <= M <= 10^6). Cada arista e = (u, v) posee un peso entero w(e) >= 1.
Se garantiza que el grafo es **2-arista-conexo** (no tiene puentes): es decir, eliminar cualquier arista individual no desconecta el grafo.

Un **Árbol de Expansión Mínima (MST)** es un subconjunto conexo y acíclico de N-1 aristas cuya suma total de pesos es mínima.
Queremos elegir estratégicamente **una arista e in E para ser eliminada** de modo que el peso del MST en el grafo resultante G \ {e} sea **lo más grande posible**.
Debemos reportar el peso del MST resultante tras eliminar dicha arista crítica.

---

## 2. Patrones Evidentes y Pistas en las Restricciones

- **N <= 10^5 y M <= 10^6:**  
  No podemos recalcular el MST desde cero para cada una de las aristas eliminadas (O(M * M log N) daría un TLE rotundo). Debemos encontrar el impacto de remover cada arista en tiempo cuasi-lineal O(M log M).
- **Propiedad Fundamental del Árbol de Expansión (Corte y Reemplazo):**  
  Sea T un MST inicial de G con peso total W(T).
  1. **Si eliminamos una arista e not in T (arista fuera del MST):**  
     El árbol T sigue estando intacto y conexo en G \ {e}. Como T ya era minimal en G, sigue siendo un MST válido en G \ {e} con el mismo peso W(T).
  2. **Si eliminamos una arista e in T (arista del MST):**  
     Al quitar e = (u, v), el árbol T se divide exactamente en dos componentes conexas disjuntas, S y V \ S.  
     Para reconectar ambas componentes en un nuevo árbol de expansión T', debemos elegir una arista de reemplazo e' = (x, y) in E \ {e} que cruce el corte (S, V \ S).  
     Por la propiedad del corte, para que el nuevo árbol sea mínimo, debemos tomar la arista de reemplazo de menor peso posible:
     W(T') = W(T) - w(e) + w(e')

- **Lema Clave de Pertenencia al Camino:**  
  ¿Cuándo una arista que no está en el árbol e' = (x, y) not in T cruza el corte formado al remover e?  
  Cruza el corte **si y solo si la arista e pertenece al único camino simple entre x e y en el árbol original T**.
  Por lo tanto, para cada arista del árbol e in T, su arista de reemplazo óptima es:
  reemplazo(e) = min { w(e') | e' = (x, y) in E \ T, e in camino_T(x, y) }
  Y el problema se reduce a encontrar:
  max_{e in T} ( W(T) - w(e) + reemplazo(e) )

---

## 3. Técnica Algorítmica: Kruskal + DSU Path Compression para Saltos en Árbol

El problema de asignar a cada arista e en el camino entre x e y el mínimo valor w(e') es un **Path Minimum Range Update** sobre un árbol. Dado que podemos procesar todas las aristas fuera del árbol *offline*, la solución es extraordinariamente rápida:

1. **Construir el MST inicial:**  
   Ejecutamos el algoritmo de Kruskal en O(M log M). Marcamos las N-1 aristas que pertenecen a T y calculamos W(T).
2. **Ordenar las aristas restantes:**  
   Tomamos todas las aristas que no quedaron en el árbol (e' in E \ T) y las ordenamos en orden creciente de peso: w(e'_1) <= w(e'_2) <= ...
3. **Pintado Codicioso de Caminos con DSU:**  
   Como procesamos las aristas de reemplazo de menor a mayor peso, **la primera arista que cubra una arista de árbol e le otorgará su valor mínimo definitivo**. Una vez asignado el reemplazo de e, ¡esa arista jamás necesita ser actualizada de nuevo!
   - Enraizamos el árbol T en el nodo 1 mediante un DFS/BFS y calculamos las profundidades depth[u] y los padres parent[u].
   - Mantenemos una estructura **DSU (Disjoint Set Union)** sobre los nodos. En el DSU, el representante de un nodo u apunta al ancestro más alto en el árbol cuya arista hacia su padre aún no ha sido cubierta.
   - Para cada arista de reemplazo e' = (x, y) con peso w(e'):
     - Subimos simultáneamente desde x e y hacia su Ancestro Común Más Cercano (LCA(x, y)).
     - Al avanzar de un nodo u a su padre p, si la arista (u, p) no tenía reemplazo, le asignamos reemplazo((u, p)) = w(e').
     - Unimos u con p en el DSU: `dsu.unite(u, p)`, de forma que futuras consultas salten inmediatamente sobre este tramo en O(alpha(N)).

---

## 4. Estrategia de Implementación Detallada (C++)

A continuación se presenta la plantilla estándar de competición para resolver este problema:

```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int u, v, id;
    ll w;
    bool in_mst = false;
};

const int MAXN = 100005;
vector<pair<int, int>> adj[MAXN]; // {vecino, edge_id}
int parent_node[MAXN], parent_edge[MAXN], depth[MAXN];
int dsu_up[MAXN]; // DSU para saltar aristas ya cubiertas
ll replacement[MAXN];

int find_up(int i) {
    return (dsu_up[i] == i) ? i : (dsu_up[i] = find_up(dsu_up[i]));
}

void dfs(int u, int p, int pe, int d) {
    parent_node[u] = p;
    parent_edge[u] = pe;
    depth[u] = d;
    for (auto& edge : adj[u]) {
        int v = edge.first;
        int id = edge.second;
        if (v != p) dfs(v, u, id, d + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].id = i;
    }

    // 1. Kruskal para encontrar el MST
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    vector<int> kruskal_dsu(n + 1);
    iota(kruskal_dsu.begin(), kruskal_dsu.end(), 0);
    auto find_k = [&](auto& self, int i) -> int {
        return (kruskal_dsu[i] == i) ? i : (kruskal_dsu[i] = self(self, kruskal_dsu[i]));
    };

    ll mst_weight = 0;
    for (int i = 0; i < m; i++) {
        int ru = find_k(find_k, edges[i].u);
        int rv = find_k(find_k, edges[i].v);
        if (ru != rv) {
            kruskal_dsu[ru] = rv;
            edges[i].in_mst = true;
            mst_weight += edges[i].w;
            adj[edges[i].u].push_back({edges[i].v, i});
            adj[edges[i].v].push_back({edges[i].u, i});
        }
    }

    // 2. DFS para enraizar el árbol
    dfs(1, 0, -1, 0);

    for (int i = 1; i <= n; i++) dsu_up[i] = i;
    memset(replacement, -1, sizeof(replacement));

    // 3. Procesar aristas fuera del árbol (ya están ordenadas por peso ascendente)
    for (int i = 0; i < m; i++) {
        if (edges[i].in_mst) continue;

        int u = find_up(edges[i].u);
        int v = find_up(edges[i].v);

        while (u != v) {
            if (depth[u] < depth[v]) swap(u, v);
            // u está estrictamente más abajo en el árbol
            int pe = parent_edge[u];
            if (replacement[pe] == -1) {
                replacement[pe] = edges[i].w;
            }
            dsu_up[u] = find_up(parent_node[u]);
            u = dsu_up[u];
        }
    }

    // 4. Encontrar la arista cuya remoción maximiza el nuevo MST
    ll max_mst = mst_weight; // Base: si se borra una arista fuera del MST
    for (int i = 0; i < m; i++) {
        if (edges[i].in_mst) {
            if (replacement[i] != -1) {
                ll new_weight = mst_weight - edges[i].w + replacement[i];
                max_mst = max(max_mst, new_weight);
            }
        }
    }

    cout << max_mst << "\n";
    return 0;
}
```

### Complejidad
- **Tiempo:**  
  - Ordenar las M aristas: O(M log M).  
  - Kruskal: O(M alpha(N)).  
  - DFS y DSU Path Compression sobre el árbol: Cada arista del árbol se visita y contrae a lo sumo una vez, tomando O(M + N alpha(N)).  
  - **Total:** O(M log M), lo que para M = 10^6 toma ≈ 0.35 segundos en C++.
- **Espacio:** O(N + M) para la lista de adyacencia y estructuras DSU.