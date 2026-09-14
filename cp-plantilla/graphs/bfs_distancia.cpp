/**
 * ============================================================================
 * PLANTILLA: BFS - Camino Más Corto en Grafos No Ponderados
 * ARCHIVO:   cp-plantilla/graphs/bfs_distancia.cpp
 * PARADIGMA: Búsqueda en Anchura (BFS) / Expansión por Olas / Grafos No Ponderados
 * COMPLEJIDAD:
 *   - Tiempo: O(V + E) — cada nodo y arista se procesa a lo sumo una vez
 *   - Espacio auxiliar: O(V) — cola, distancias y predecesores
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. EL INVARIANTE SAGRADO DEL PUSH:
 *    ¡SIEMPRE marcar el nodo como visitado (asignar `distancia[v] = distancia[u] + 1`)
 *    EN EL MOMENTO EXACTO EN QUE SE INSERTA EN LA COLA (`push`), NUNCA AL EXTRAERLO (`pop`)!
 *    - Si marcas en el `pop`, múltiples vecinos pueden empujar el mismo nodo repetidamente
 *      antes de que sea extraído, provocando explosión exponencial de memoria y Time Limit Exceeded (TLE).
 *
 * 2. VECTOR `distancia` COMO `visited` DUAL:
 *    Inicializar `distancia` con `-1`. Un valor de `-1` indica "no visitado",
 *    eliminando la necesidad de un vector booleano `visited` redundante:
 *        `if (distancia[vecino] == -1) { distancia[vecino] = dist[u] + 1; q.push(vecino); }`
 *
 * 3. PROPIEDAD DE OPTIMALIDAD (BREADTH-FIRST):
 *    En grafos donde todas las aristas tienen costo unitario (o idéntico peso no ponderado),
 *    la primera vez que la ola de BFS toca un nodo, la distancia registrada es garantizadamente
 *    la mínima posible.
 *
 * 4. RECONSTRUCCIÓN DEL CAMINO MÁS CORTO:
 *    Mantener un vector `padre[n + 1] = -1`. Al terminar, se retrocede desde `destino`
 *    hasta `origen` siguiendo los enlaces de `padre` y se invierte el vector de ruta.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using Grafo = vector<vector<int>>;

struct ResultadoBFS {
    vector<int> distancia;
    vector<int> padre;
    int origen;

    ResultadoBFS(int n, int origen) 
        : distancia(n + 1, -1), padre(n + 1, -1), origen(origen) {}

    // Retorna el camino más corto hacia el destino (o vacío si es inalcanzable)
    vector<int> obtener_camino(int destino) const {
        if (distancia[destino] == -1) {
            return {}; // Inalcanzable
        }
        vector<int> ruta;
        for (int actual = destino; actual != -1; actual = padre[actual]) {
            ruta.push_back(actual);
        }
        reverse(ruta.begin(), ruta.end());
        return ruta;
    }
};

// BFS estándar en grafo no ponderado
ResultadoBFS bfs_distancia(int origen, int n, const Grafo& adj) {
    ResultadoBFS res(n, origen);
    queue<int> q;

    // INVARIANTE: Asignar distancia y marcar antes de encolar
    res.distancia[origen] = 0;
    q.push(origen);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            // Si no ha sido visitado aún
            if (res.distancia[v] == -1) {
                res.distancia[v] = res.distancia[u] + 1;
                res.padre[v] = u;
                q.push(v); // Inmediatamente marcado tras push
            }
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: BFS Camino Más Corto en Grafo No Ponderado ===\n";

    // Grafo con 7 nodos (1-indexed)
    // 1 conecta con 2 y 3
    // 2 conecta con 4
    // 3 conecta con 4 y 5
    // 4 conecta con 6
    // 5 conecta con 6
    // 7 desconectado
    int n = 7;
    Grafo adj(n + 1);

    auto agregar_arista = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    agregar_arista(1, 2);
    agregar_arista(1, 3);
    agregar_arista(2, 4);
    agregar_arista(3, 4);
    agregar_arista(3, 5);
    agregar_arista(4, 6);
    agregar_arista(5, 6);

    int origen = 1;
    ResultadoBFS res = bfs_distancia(origen, n, adj);

    cout << "Distancias mínimas desde el nodo " << origen << ":\n";
    for (int i = 1; i <= n; ++i) {
        cout << "Nodo " << i << ": Distancia = " << res.distancia[i] << "\n";
    }

    // Consulta de ruta más corta hacia el nodo 6
    int destino = 6;
    vector<int> camino = res.obtener_camino(destino);

    cout << "\nCamino más corto hacia el nodo " << destino << " (longitud: " << res.distancia[destino] << " aristas):\n";
    for (size_t i = 0; i < camino.size(); ++i) {
        cout << camino[i] << (i + 1 == camino.size() ? "" : " -> ");
    }
    cout << "\n(Nótese que 1 -> 3 -> 5 -> 6 y 1 -> 2 -> 4 -> 6 tienen longitud 3; BFS encuentra una ruta óptima)\n";

    // Consulta de ruta hacia nodo inalcanzable
    destino = 7;
    vector<int> camino_aislado = res.obtener_camino(destino);
    cout << "\nCamino hacia nodo " << destino << ": " 
         << (camino_aislado.empty() ? "Inalcanzable (distancia -1)" : "Alcanzado") << "\n";

    return 0;
}
