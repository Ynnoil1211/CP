/**
 * ============================================================================
 * PLANTILLA: DFS - Construcción de Rutas y Orden Topológico (Pre-order vs Post-order)
 * ARCHIVO:   cp-plantilla/graphs/dfs_ordenamiento_rutas.cpp
 * PARADIGMA: Búsqueda en Profundidad (DFS) / Orden Topológico / Grafos Dirigidos
 * COMPLEJIDAD:
 *   - Tiempo: O(V + E)
 *   - Espacio auxiliar: O(V) (call-stack + vector ruta)
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. PRE-ORDER vs. POST-ORDER PUSH:
 *    - PRE-ORDER (Descubrimiento):
 *        `ruta.push_back(u);` se ejecuta ANTES del bucle de vecinos.
 *        Registra el orden exacto en que los nodos son descubiertos por primera vez.
 *        Ideal para: Euler Tours, recorridos jerárquicos padre-hijo, serialización de árboles.
 *    - POST-ORDER (Finalización / Retorno):
 *        `ruta.push_back(u);` se ejecuta DESPUÉS de haber explorado exhaustivamente todos
 *        los descendientes del nodo.
 *        Registra cuándo un nodo "termina su trabajo".
 *        Ideal para: Ordenamiento Topológico (invirtiendo la lista post-order),
 *        resolución de dependencias bottom-up y componentes fuertemente conexas (Kosaraju).
 *
 * 2. ORDEN TOPOLÓGICO VÍA DFS (DAG):
 *    En un Grafo Acíclico Dirigido (DAG), si una tarea `u` debe preceder a `v` (`u -> v`),
 *    la recursión finalizará primero en `v` y luego en `u`. Por lo tanto, `u` entrará
 *    a la lista post-order después de `v`.
 *    Al invertir el resultado post-order (`reverse(orden.begin(), orden.end())`),
 *    obtenemos un ordenamiento topológico válido donde `u` aparece antes que `v`.
 *
 * 3. DETECCIÓN DE CICLOS (3 COLORES):
 *    0 = no visitado (blanco), 1 = en proceso / en stack (gris), 2 = finalizado (negro).
 *    Si encontramos un vecino en estado 1 (gris), ¡el grafo contiene un ciclo dirigido
 *    y NO admite ordenamiento topológico!
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using GrafoDirigido = vector<vector<int>>;

// DFS para Orden Topológico con detección de ciclos (0: Blanco, 1: Gris, 2: Negro)
bool dfs_topologico(int u, const GrafoDirigido& adj, vector<int>& estado, vector<int>& post_order) {
    estado[u] = 1; // Nodo en proceso (en el call stack actual)

    for (int v : adj[u]) {
        if (estado[v] == 1) {
            // Se encontró una arista hacia atrás (back-edge) => Hay un ciclo
            return false;
        }
        if (estado[v] == 0) {
            if (!dfs_topologico(v, adj, estado, post_order)) {
                return false;
            }
        }
    }

    estado[u] = 2; // Nodo completamente procesado
    // POST-ORDER PUSH: se agrega al finalizar todos sus descendientes
    post_order.push_back(u);
    return true;
}

// DFS de Descubrimiento (Pre-Order)
void dfs_pre_order(int u, const GrafoDirigido& adj, vector<bool>& visitado, vector<int>& pre_order) {
    visitado[u] = true;
    // PRE-ORDER PUSH: se agrega inmediatamente al ser descubierto
    pre_order.push_back(u);

    for (int v : adj[u]) {
        if (!visitado[v]) {
            dfs_pre_order(v, adj, visitado, pre_order);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: DFS Pre-Order vs Post-Order (Topological Sort) ===\n";

    // Creamos un DAG con 6 tareas (1..6)
    // 1 -> 2, 1 -> 3
    // 2 -> 4
    // 3 -> 4, 3 -> 5
    // 4 -> 6
    // 5 -> 6
    int n = 6;
    GrafoDirigido adj(n + 1);
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(4);
    adj[3].push_back(4);
    adj[3].push_back(5);
    adj[4].push_back(6);
    adj[5].push_back(6);

    // 1. Demostración de Pre-Order desde la raíz 1
    vector<bool> visitado(n + 1, false);
    vector<int> pre_order;
    dfs_pre_order(1, adj, visitado, pre_order);

    cout << "Orden de Descubrimiento (Pre-Order desde nodo 1):\n";
    for (size_t i = 0; i < pre_order.size(); ++i) {
        cout << pre_order[i] << (i + 1 == pre_order.size() ? "" : " -> ");
    }
    cout << "\n\n";

    // 2. Demostración de Ordenamiento Topológico (Post-Order Invertido)
    vector<int> estado(n + 1, 0);
    vector<int> post_order;
    bool es_dag = true;

    for (int i = 1; i <= n; ++i) {
        if (estado[i] == 0) {
            if (!dfs_topologico(i, adj, estado, post_order)) {
                es_dag = false;
                break;
            }
        }
    }

    if (es_dag) {
        // Invertimos la lista post-order para obtener el orden topológico
        reverse(post_order.begin(), post_order.end());

        cout << "Ordenamiento Topológico Válido (Post-Order Invertido):\n";
        for (size_t i = 0; i < post_order.size(); ++i) {
            cout << post_order[i] << (i + 1 == post_order.size() ? "" : " -> ");
        }
        cout << "\n(Nótese que cada prerrequisito aparece estrictamente antes de sus tareas dependientes)\n";
    } else {
        cout << "El grafo contiene un ciclo. No existe ordenamiento topológico.\n";
    }

    return 0;
}
