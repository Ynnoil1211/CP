/**
 * ============================================================================
 * PLANTILLA: DFS - Existencia de Camino a Destino (Early Exit)
 * ARCHIVO:   cp-plantilla/graphs/dfs_camino_destino.cpp
 * PARADIGMA: Búsqueda en Profundidad (DFS) / Grafos
 * COMPLEJIDAD:
 *   - Peor caso (sin camino): O(V + E)
 *   - Mejor caso (camino cercano): O(longitud del camino)
 *   - Espacio auxiliar (call-stack + visited): O(V)
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. RETORNO BOOLEANO Y "PASS THE BALL BACKWARDS":
 *    En lugar de recorrer todo el grafo o esperar a que la recursión termine
 *    exhaustivamente, la función retorna `bool`. Tan pronto como un hijo reporta
 *    `true`, la condición `if (dfs(vecino, destino)) return true;` pasa la señal
 *    inmediatamente hacia atrás en la pila de llamadas ("early exit").
 *
 * 2. CUÁNDO USAR:
 *    - Búsqueda de existencia de un camino directo entre dos nodos específicos.
 *    - Salida de laberintos o juegos con estado terminal único.
 *    - Validación de alcanzabilidad donde NO se requiere la ruta más corta (para
 *      camino más corto en grafos no ponderados, usar siempre BFS).
 *
 * 3. RECONSTRUCCIÓN OPCIONAL DEL CAMINO:
 *    Si además de saber si existe camino queremos reconstruirlo, se puede llenar
 *    un vector `camino.push_back(u)` al recibir el `true`, produciendo la ruta en
 *    orden inverso o directo.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

// Grafo representado como lista de adyacencia
using Grafo = vector<vector<int>>;

// DFS con retorno booleano y salida temprana (early exit)
bool dfs_existe_camino(int actual, int destino, const Grafo& adj, vector<bool>& visitado, vector<int>& camino) {
    // Caso base: se alcanzó el nodo objetivo
    if (actual == destino) {
        camino.push_back(actual);
        return true;
    }

    visitado[actual] = true;

    for (int vecino : adj[actual]) {
        if (!visitado[vecino]) {
            // "Pass the ball backwards": si el vecino encuentra el destino, propagamos true inmediatamente
            if (dfs_existe_camino(vecino, destino, adj, visitado, camino)) {
                camino.push_back(actual);
                return true;
            }
        }
    }

    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: DFS Existencia de Camino (Early Exit) ===\n";

    int n = 6; // Nodos del 1 al 6
    Grafo adj(n + 1);

    // Conexiones: 1 -> 2 -> 3 -> 5, 2 -> 4, 6 aislado
    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[2].push_back(3);
    adj[3].push_back(2);

    adj[2].push_back(4);
    adj[4].push_back(2);

    adj[3].push_back(5);
    adj[5].push_back(3);

    // Consulta 1: Camino de 1 a 5
    int origen = 1, destino = 5;
    vector<bool> visitado(n + 1, false);
    vector<int> camino;

    if (dfs_existe_camino(origen, destino, adj, visitado, camino)) {
        cout << "Camino encontrado entre " << origen << " y " << destino << ": ";
        // El camino se llena en reversa durante el desapilado; invertimos para mostrarlo
        for (int i = (int)camino.size() - 1; i >= 0; --i) {
            cout << camino[i] << (i == 0 ? "" : " -> ");
        }
        cout << "\n";
    } else {
        cout << "No existe camino entre " << origen << " y " << destino << "\n";
    }

    // Consulta 2: Camino de 1 a 6 (nodo desconectado)
    destino = 6;
    fill(visitado.begin(), visitado.end(), false);
    camino.clear();

    if (dfs_existe_camino(origen, destino, adj, visitado, camino)) {
        cout << "Camino encontrado entre " << origen << " y " << destino << "\n";
    } else {
        cout << "Resultado para " << origen << " a " << destino << ": No alcanzable (Esperado: No alcanzable)\n";
    }

    return 0;
}
