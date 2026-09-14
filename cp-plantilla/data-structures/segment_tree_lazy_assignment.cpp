/**
 * ============================================================================
 * PLANTILLA: Segment Tree con Lazy Propagation (Asignación de Rango - Point Query)
 * ARCHIVO:   cp-plantilla/data-structures/segment_tree_lazy_assignment.cpp
 * PARADIGMA: Lazy Propagation / Range Assignment / Point Query
 * COMPLEJIDAD:
 *   - Construcción: O(N)
 *   - Actualización de rango [l, r] = val: O(log N)
 *   - Consulta puntual en posición p: O(log N)
 *   - Espacio: O(N) — tamaño 4 * N
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. EL CONCEPTO DE PROPAGACIÓN PEREZOSA (LAZY PROPAGATION):
 *    Cuando actualizamos un rango masivo [l, r] con un nuevo valor constante `val`,
 *    descender hasta cada una de las hojas tomaría O(N). En su lugar, si un nodo
 *    está completamente dentro de [l, r], guardamos el valor pendiente en `lazy[node]`,
 *    marcamos `has_lazy[node] = true` y nos detenemos inmediatamente en O(1).
 *
 * 2. FUNCIÓN `push(node)` (Propagación hacia abajo):
 *    Antes de que cualquier consulta o actualización descienda a los hijos de `node`,
 *    se debe transferir la asignación pendiente a sus dos hijos directos.
 *    - Los hijos heredan `lazy[hijo] = lazy[node]` y `has_lazy[hijo] = true`.
 *    - El nodo actual limpia su bandera: `has_lazy[node] = false`.
 *    - Sobrescribe cualquier asignación antigua que tuvieran los hijos, respetando
 *      el orden cronológico.
 *
 * 3. ¿POR QUÉ USAR `has_lazy` BOOLEANO EN VEZ DE VALORES CENTINELA (-1, 0)?
 *    En problemas de CP, los valores asignados pueden ser legítimamente 0 o negativos.
 *    Un arreglo auxiliar `vector<bool> has_lazy` garantiza inmunidad total a errores
 *    por colisión con centinelas.
 *
 * 4. CONSULTA PUNTUAL (POINT QUERY):
 *    Para consultar el valor de una posición específica `idx`, descendemos por el árbol.
 *    En cada paso llamamos a `push()`, lo que asegura que cuando llegamos a la hoja,
 *    ésta ha recibido la asignación más reciente que la cubría.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct SegmentTreeLazyAssignment {
    int n;
    vector<T> tree;
    vector<T> lazy;
    vector<bool> has_lazy;

    SegmentTreeLazyAssignment(int n) 
        : n(n), tree(4 * n, 0), lazy(4 * n, 0), has_lazy(4 * n, false) {}

    SegmentTreeLazyAssignment(const vector<T>& arr) 
        : n(arr.size()), tree(4 * n, 0), lazy(4 * n, 0), has_lazy(4 * n, false) {
        build(1, 0, n - 1, arr);
    }

    void build(int node, int low, int high, const vector<T>& arr) {
        if (low == high) {
            tree[node] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * node, low, mid, arr);
        build(2 * node + 1, mid + 1, high, arr);
        // En point query el valor de nodos internos no es crítico, pero mantenemos consistencia
        tree[node] = tree[2 * node];
    }

    // Propaga la asignación pendiente hacia los hijos inmediatos
    void push(int node) {
        if (!has_lazy[node]) return;

        int left = 2 * node;
        int right = 2 * node + 1;

        // Propagar al hijo izquierdo
        lazy[left] = lazy[node];
        tree[left] = lazy[node];
        has_lazy[left] = true;

        // Propagar al hijo derecho
        lazy[right] = lazy[node];
        tree[right] = lazy[node];
        has_lazy[right] = true;

        // Limpiar la bandera del nodo actual
        has_lazy[node] = false;
    }

    // Actualización de rango: arr[i] = val para todo i en [l, r]
    void update_range(int node, int low, int high, int l, int r, T val) {
        // Fuera de rango
        if (high < l || low > r) {
            return;
        }
        // Solapamiento total: aplicamos lazy y salimos
        if (l <= low && high <= r) {
            tree[node] = val;
            lazy[node] = val;
            has_lazy[node] = true;
            return;
        }
        // Solapamiento parcial: propagamos hacia abajo antes de descender
        push(node);
        int mid = low + (high - low) / 2;
        update_range(2 * node, low, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, high, l, r, val);
        tree[node] = tree[2 * node]; // o cualquier métrica representativa
    }

    void update_range(int l, int r, T val) {
        update_range(1, 0, n - 1, l, r, val);
    }

    // Consulta puntual: obtiene el valor exacto en el índice idx
    T point_query(int node, int low, int high, int idx) {
        if (low == high) {
            return tree[node];
        }
        // Propagar para garantizar que los hijos tengan la información más reciente
        push(node);
        int mid = low + (high - low) / 2;
        if (idx <= mid) {
            return point_query(2 * node, low, mid, idx);
        } else {
            return point_query(2 * node + 1, mid + 1, high, idx);
        }
    }

    T point_query(int idx) {
        return point_query(1, 0, n - 1, idx);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: Segment Tree Lazy Assignment (Point Query) ===\n";
    vector<long long> datos = {5, 5, 5, 5, 5, 5, 5, 5};

    SegmentTreeLazyAssignment<long long> st(datos);

    cout << "Arreglo inicial: todos en 5.\n";
    cout << "Valor en posicion 3: " << st.point_query(3) << " (Esperado: 5)\n";

    // Asignación en rango [2, 5] = 99
    cout << "\nAsignando 99 en rango [2, 5]...\n";
    st.update_range(2, 5, 99);

    cout << "Valor en posicion 1: " << st.point_query(1) << " (Esperado: 5)\n";
    cout << "Valor en posicion 2: " << st.point_query(2) << " (Esperado: 99)\n";
    cout << "Valor en posicion 5: " << st.point_query(5) << " (Esperado: 99)\n";
    cout << "Valor en posicion 6: " << st.point_query(6) << " (Esperado: 5)\n";

    // Asignación solapada: rango [4, 7] = -42 (prueba de números negativos)
    cout << "\nAsignando -42 en rango [4, 7]...\n";
    st.update_range(4, 7, -42);

    cout << "Valor en posicion 3: " << st.point_query(3) << " (Esperado: 99 - asignacion anterior conservada)\n";
    cout << "Valor en posicion 4: " << st.point_query(4) << " (Esperado: -42 - sobrescrito exitosamente)\n";
    cout << "Valor en posicion 7: " << st.point_query(7) << " (Esperado: -42)\n";

    return 0;
}
