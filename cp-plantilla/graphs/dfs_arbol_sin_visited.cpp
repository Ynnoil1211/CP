/**
 * ============================================================================
 * PLANTILLA: DFS en Árboles sin Arreglo Visited (Paso de Padre)
 * ARCHIVO:   cp-plantilla/graphs/dfs_arbol_sin_visited.cpp
 * PARADIGMA: Búsqueda en Profundidad (DFS) / Teoría de Árboles
 * COMPLEJIDAD:
 *   - Tiempo: O(N) — cada arista y nodo se visita exactamente una vez
 *   - Espacio auxiliar: O(H) call-stack donde H es la altura del árbol (O(N) peor caso)
 *     ¡Cero memoria adicional para arreglos booleanos de visited!
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. ¿POR QUÉ NO SE NECESITA UN ARREGLO `visited`?
 *    Un árbol no dirigido con N nodos tiene exactamente N - 1 aristas y CERO ciclos.
 *    La única forma en que un DFS podría volver a un nodo ya visitado es regresando
 *    inmediatamente por la arista de la cual vino (su padre directo).
 *    Pasando la firma `(int actual, int padre)` y evaluando:
 *        `if (vecino != padre) dfs(vecino, actual);`
 *    se bloquea completamente el retroceso sin gastar memoria en `visited[n]`.
 *
 * 2. OPTIMIZACIÓN DE MEMORIA Y VELOCIDAD EN CP:
 *    - En problemas con múltiples casos de prueba (T tests) o árboles con N = 5 * 10^5,
 *      crear o limpiar con `memset`/`fill` un vector `visited` introduce sobrecarga de
 *      tiempo y riesgo de TLE o Memory Limit Exceeded.
 *    - Este patrón es el estándar absoluto en problemas de Tree DP, cálculo de tamaños
 *      de subárboles (`subtree_size`), profundidad/altura y Binary Lifting para LCA.
 *
 * 3. RAÍZ CON PADRE FICTICIO:
 *    La llamada inicial se realiza con un padre que no exista en el árbol,
 *    típicamente `dfs(raiz, 0)` si los nodos son 1-indexed, o `dfs(raiz, -1)` si son 0-indexed.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

using Arbol = vector<vector<int>>;

// Estructura de métricas típicas de árbol calculadas en un único recorrido
struct MetricasArbol {
    vector<int> profundidad;
    vector<int> tamano_subarbol;
    vector<int> padre_directo;

    MetricasArbol(int n) 
        : profundidad(n + 1, 0), tamano_subarbol(n + 1, 1), padre_directo(n + 1, 0) {}
};

// DFS sin vector visited: solo valida que el vecino sea distinto del padre
void dfs_arbol(int actual, int padre, const Arbol& adj, MetricasArbol& metricas) {
    metricas.padre_directo[actual] = padre;
    metricas.tamano_subarbol[actual] = 1; // El nodo se cuenta a sí mismo

    for (int hijo : adj[actual]) {
        // La condición clave: ignorar la arista que conduce de regreso al padre
        if (hijo != padre) {
            metricas.profundidad[hijo] = metricas.profundidad[actual] + 1;
            dfs_arbol(hijo, actual, adj, metricas);
            // Acumulación bottom-up del tamaño del subárbol
            metricas.tamano_subarbol[actual] += metricas.tamano_subarbol[hijo];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: DFS en Árboles sin Arreglo Visited ===\n";

    /*
     * Árbol con 7 nodos (1-indexed):
     *         1 (raíz)
     *        / \
     *       2   3
     *      / \   \
     *     4   5   6
     *              \
     *               7
     */
    int n = 7;
    Arbol adj(n + 1);

    auto agregar_arista = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    agregar_arista(1, 2);
    agregar_arista(1, 3);
    agregar_arista(2, 4);
    agregar_arista(2, 5);
    agregar_arista(3, 6);
    agregar_arista(6, 7);

    MetricasArbol metricas(n);

    // Llamada inicial con raíz = 1 y padre ficticio = 0
    metricas.profundidad[1] = 0;
    dfs_arbol(1, 0, adj, metricas);

    cout << "Resultados por nodo:\n";
    cout << "Nodo | Padre | Profundidad | Tamaño Subárbol\n";
    cout << "-------------------------------------------\n";
    for (int i = 1; i <= n; ++i) {
        cout << "  " << i << "  |   " 
             << metricas.padre_directo[i] << "   |      " 
             << metricas.profundidad[i] << "      |       " 
             << metricas.tamano_subarbol[i] << "\n";
    }

    // Verificaciones pedagógicas
    cout << "\nVerificación clave:\n";
    cout << "- Tamaño subárbol de la raíz 1: " << metricas.tamano_subarbol[1] << " (Esperado: 7)\n";
    cout << "- Tamaño subárbol del nodo 2: " << metricas.tamano_subarbol[2] << " (Esperado: 3: {2, 4, 5})\n";
    cout << "- Tamaño subárbol del nodo 3: " << metricas.tamano_subarbol[3] << " (Esperado: 3: {3, 6, 7})\n";

    return 0;
}
