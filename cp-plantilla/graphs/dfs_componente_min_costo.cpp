/**
 * ============================================================================
 * PLANTILLA: DFS - Componente Conexo y Estadísticas Globales (Costo Mínimo / Suma / Tamaño)
 * ARCHIVO:   cp-plantilla/graphs/dfs_componente_min_costo.cpp
 * PARADIGMA: Búsqueda en Profundidad (DFS) / Componentes Conexas
 * COMPLEJIDAD:
 *   - Tiempo: O(V + E) para recorrer todo el grafo
 *   - Espacio auxiliar: O(V) (vector visitado + stack recursivo)
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. PASO DE ACUMULADOR POR REFERENCIA:
 *    En lugar de retornar valores o usar variables globales propensas a errores,
 *    la función DFS es de tipo `void` y recibe variables acumuladoras por referencia:
 *        `void dfs(int u, ..., long long& min_costo, long long& suma_oro, int& tamano)`
 *    Cada llamada recursiva actualiza las métricas in-place:
 *        `min_costo = min(min_costo, costo[u]);`
 *        `suma_oro += oro[u];`
 *        `tamano++;`
 *
 * 2. CUÁNDO USAR (PATRÓN CLÁSICO EN CP):
 *    - Problema clásico: Codeforces "Rumor" (1020B / 893C), donde se debe elegir
 *      el elemento de costo mínimo por cada componente conexa para minimizar la suma total.
 *    - Problemas de "Bolsas de recursos": sumar todo el oro o contar el número de
 *      vértices en cada isla independiente.
 *    - Detección del número total de componentes conexas en grafos no dirigidos.
 *
 * 3. BUCLE PRINCIPAL (DRIVER LOOP):
 *    Iterar sobre todos los vértices `for (int i = 1; i <= n; ++i)` y, si no está
 *    visitado, disparar una nueva exploración para descubrir una nueva componente.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Grafo = vector<vector<int>>;

// DFS que recolecta estadísticas de la componente conexa por referencia
void dfs_componente(int u, 
                    const Grafo& adj, 
                    const vector<long long>& costos, 
                    vector<bool>& visitado, 
                    long long& min_costo, 
                    long long& suma_total, 
                    int& tamano) {
    visitado[u] = true;
    min_costo = min(min_costo, costos[u]);
    suma_total += costos[u];
    tamano++;

    for (int v : adj[u]) {
        if (!visitado[v]) {
            dfs_componente(v, adj, costos, visitado, min_costo, suma_total, tamano);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: DFS Componente Conexa y Costo Mínimo (Estilo 'Rumor') ===\n";

    // 6 vértices con costos asociados (1-indexed)
    int n = 6;
    vector<long long> costos = {0, 10, 20, 15, 5, 30, 2}; // 1..6

    Grafo adj(n + 1);

    // Componente A: {1, 2, 3} -> costos: {10, 20, 15} => Min = 10, Suma = 45, Tam = 3
    adj[1].push_back(2); adj[2].push_back(1);
    adj[2].push_back(3); adj[3].push_back(2);

    // Componente B: {4, 5} -> costos: {5, 30} => Min = 5, Suma = 35, Tam = 2
    adj[4].push_back(5); adj[5].push_back(4);

    // Componente C: {6} (aislado) -> costo: {2} => Min = 2, Suma = 2, Tam = 1

    vector<bool> visitado(n + 1, false);
    long long costo_total_minimo = 0;
    int num_componentes = 0;

    for (int i = 1; i <= n; ++i) {
        if (!visitado[i]) {
            num_componentes++;
            long long min_costo = costos[i];
            long long suma_total = 0;
            int tamano = 0;

            dfs_componente(i, adj, costos, visitado, min_costo, suma_total, tamano);

            cout << "Componente " << num_componentes << ":\n";
            cout << "  - Vértice inicial: " << i << "\n";
            cout << "  - Tamaño: " << tamano << "\n";
            cout << "  - Suma de costos: " << suma_total << "\n";
            cout << "  - Costo mínimo elegido: " << min_costo << "\n";

            costo_total_minimo += min_costo;
        }
    }

    cout << "\nNúmero total de componentes: " << num_componentes << " (Esperado: 3)\n";
    cout << "Costo total mínimo (suma de mínimos): " << costo_total_minimo << " (Esperado: 10 + 5 + 2 = 17)\n";

    return 0;
}
