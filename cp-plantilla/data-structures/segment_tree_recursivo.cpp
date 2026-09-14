/**
 * ============================================================================
 * PLANTILLA: Segment Tree Recursivo (0-indexed, rango cerrado [l, r])
 * ARCHIVO:   cp-plantilla/data-structures/segment_tree_recursivo.cpp
 * PARADIGMA: Divide and Conquer / Estructuras de Datos
 * COMPLEJIDAD:
 *   - Construcción (build): O(N)
 *   - Actualización puntual (update): O(log N)
 *   - Consulta de rango (query): O(log N)
 *   - Espacio: O(N) — tamaño 4 * N
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. SIGNIFICADO DE `low` Y `high`:
 *    Representan los límites exactos del segmento que el nodo actual `node` está
 *    administrando. En la raíz, `node = 1` cubre `[0, n - 1]`.
 *
 * 2. CONDICIONES FUNDAMENTALES DE LA RECURSIÓN:
 *    a) Solapamiento Total (Completely Overlap):
 *       `if (l <= low && high <= r)`
 *       El segmento del nodo está completamente contenido dentro del rango buscado.
 *       Se retorna el valor almacenado en `tree[node]` directamente en O(1).
 *    b) Disjuntos (No Overlap):
 *       `if (high < l || low > r)`
 *       El segmento no comparte ningún elemento con el rango pedido. Se retorna
 *       el elemento neutro (0 para suma, INF para min, etc.).
 *    c) Solapamiento Parcial (Partial Overlap):
 *       Se divide el segmento en el punto medio `mid = low + (high - low) / 2`,
 *       se consultan ambos hijos recursivamente y se combinan los resultados.
 *
 * 3. REGLA DEL TAMAÑO 4 * N:
 *    El árbol es conceptualmente un árbol binario casi completo. Si N no es potencia
 *    de 2, la siguiente potencia de 2 puede ser hasta ~2N, y un árbol binario completo
 *    con 2N hojas tiene 2 * (2N) - 1 ≈ 4N nodos. Asignar `vector<T>(4 * n)` evita
 *    cualquier desbordamiento de memoria por indexación 1-based (`2 * node` y `2 * node + 1`).
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct SegmentTreeRecursivo {
    int n;
    T neutro;
    vector<T> tree;

    // Función de combinación asociativa (ej. suma, min, max, gcd)
    T combinar(T a, T b) const {
        return a + b; // Ajustar según la operación requerida
    }

    SegmentTreeRecursivo(int n, T neutro = 0) : n(n), neutro(neutro), tree(4 * n, neutro) {}

    SegmentTreeRecursivo(const vector<T>& arr, T neutro = 0) : n(arr.size()), neutro(neutro), tree(4 * n, neutro) {
        build(1, 0, n - 1, arr);
    }

    // Construcción recursiva: divide el arreglo hasta hojas unitarias y combina hacia arriba
    void build(int node, int low, int high, const vector<T>& arr) {
        if (low == high) {
            tree[node] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * node, low, mid, arr);
        build(2 * node + 1, mid + 1, high, arr);
        tree[node] = combinar(tree[2 * node], tree[2 * node + 1]);
    }

    // Actualización puntual: modifica la posición idx con val
    void update(int node, int low, int high, int idx, T val) {
        if (low == high) {
            tree[node] = val;
            return;
        }
        int mid = low + (high - low) / 2;
        if (idx <= mid) {
            update(2 * node, low, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, high, idx, val);
        }
        tree[node] = combinar(tree[2 * node], tree[2 * node + 1]);
    }

    // Sobrecarga amigable para actualizar desde el exterior (0-indexed)
    void update(int idx, T val) {
        update(1, 0, n - 1, idx, val);
    }

    // Consulta de rango en intervalo cerrado [l, r]
    T query(int node, int low, int high, int l, int r) const {
        // Caso 1: Rango disjunto (completamente fuera)
        if (high < l || low > r) {
            return neutro;
        }
        // Caso 2: Solapamiento total (completamente contenido)
        if (l <= low && high <= r) {
            return tree[node];
        }
        // Caso 3: Solapamiento parcial (recorrer ambos hijos)
        int mid = low + (high - low) / 2;
        T izq = query(2 * node, low, mid, l, r);
        T der = query(2 * node + 1, mid + 1, high, l, r);
        return combinar(izq, der);
    }

    // Sobrecarga amigable para consultar desde el exterior (0-indexed)
    T query(int l, int r) const {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: Segment Tree Recursivo ===\n";
    vector<long long> datos = {2, 4, 6, 8, 10, 12};

    SegmentTreeRecursivo<long long> st(datos, 0);

    // Consulta en rango [1, 3] inclusivo => {4, 6, 8} => Suma = 18
    int l = 1, r = 3;
    cout << "Suma en rango [" << l << ", " << r << "]: " 
         << st.query(l, r) << " (Esperado: 18)\n";

    // Actualización puntual: en índice 2 cambiar 6 por 20
    cout << "Actualizando posicion 2 con valor 20...\n";
    st.update(2, 20);

    // Consulta en rango [1, 3] tras actualización => {4, 20, 8} => Suma = 32
    cout << "Nueva suma en rango [" << l << ", " << r << "]: " 
         << st.query(l, r) << " (Esperado: 32)\n";

    return 0;
}
