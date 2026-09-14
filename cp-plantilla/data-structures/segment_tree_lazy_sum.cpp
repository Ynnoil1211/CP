/**
 * ============================================================================
 * PLANTILLA: Segment Tree con Lazy Propagation (Suma en Rango - Range Sum Query)
 * ARCHIVO:   cp-plantilla/data-structures/segment_tree_lazy_sum.cpp
 * PARADIGMA: Lazy Propagation / Range Addition / Range Sum
 * COMPLEJIDAD:
 *   - Construcción (build): O(N)
 *   - Actualización de rango [l, r] += val: O(log N)
 *   - Consulta de suma en rango [l, r]: O(log N)
 *   - Espacio: O(N) — tamaño 4 * N
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 *
 * 1. MULTIPLICACIÓN POR LA LONGITUD DEL SEGMENTO:
 *    Si agregamos `val` a cada elemento en el segmento `[low, high]`, la suma total
 *    del segmento se incrementa en exactamente:
 *        `val * (high - low + 1)`
 *    ¡Olvidar multiplicar por la longitud del segmento es el bug #1 en CP!
 *
 * 2. LONGITUDES DISTINTAS ENTRE HIJO IZQUIERDO Y DERECHO:
 *    Al propagar hacia abajo (`push`):
 *    - El hijo izquierdo cubre `[low, mid]`, longitud: `mid - low + 1`.
 *    - El hijo derecho cubre `[mid + 1, high]`, longitud: `high - mid`.
 *    Cuando N no es potencia de 2, los tamaños de los subárboles difieren.
 *    Almacenar el incremento aditivo pendiente en `lazy[hijo] += lazy[node]`
 *    permite acumular múltiples operaciones y diferir la multiplicación hasta
 *    que el nodo sea visitado o propagado.
 *
 * 3. ACUMULACIÓN ADITIVA (COMPOSICIÓN DE OPERADORES):
 *    A diferencia de la asignación pura (donde un valor sobrescribe al anterior),
 *    la suma de rango es acumulativa:
 *        `lazy[left] += lazy[node];`
 *        `lazy[right] += lazy[node];`
 *    Esto garantiza que múltiples actualizaciones sobre rangos coincidentes
 *    se acumulen correctamente sin perder información.
 *
 * 4. TIPO DE DATO (64-BIT / long long):
 *    La suma de rango con adiciones masivas desborda rápidamente `int` de 32 bits.
 *    Se debe usar `long long` en `tree`, `lazy` y valores de retorno.
 * ============================================================================
 */

#include <iostream>
#include <vector>

using namespace std;

struct SegmentTreeLazySum {
    int n;
    vector<long long> tree;
    vector<long long> lazy;

    SegmentTreeLazySum(int n) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

    SegmentTreeLazySum(const vector<long long>& arr) 
        : n(arr.size()), tree(4 * n, 0), lazy(4 * n, 0) {
        build(1, 0, n - 1, arr);
    }

    void build(int node, int low, int high, const vector<long long>& arr) {
        if (low == high) {
            tree[node] = arr[low];
            return;
        }
        int mid = low + (high - low) / 2;
        build(2 * node, low, mid, arr);
        build(2 * node + 1, mid + 1, high, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Aplica el incremento pendiente del nodo y lo transfiere a sus hijos
    void push(int node, int low, int high) {
        if (lazy[node] == 0) return;

        // Actualizamos la suma del nodo actual multiplicando por la longitud del segmento
        tree[node] += lazy[node] * (high - low + 1);

        // Si no es nodo hoja, delegamos la suma pendiente a los hijos
        if (low != high) {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }

        // Limpiamos el lazy del nodo actual
        lazy[node] = 0;
    }

    // Actualización de rango: suma `val` a todos los elementos en [l, r]
    void update_range(int node, int low, int high, int l, int r, long long val) {
        push(node, low, high);

        // Caso 1: Disjunto
        if (high < l || low > r) {
            return;
        }

        // Caso 2: Solapamiento total
        if (l <= low && high <= r) {
            lazy[node] += val;
            push(node, low, high);
            return;
        }

        // Caso 3: Solapamiento parcial
        int mid = low + (high - low) / 2;
        update_range(2 * node, low, mid, l, r, val);
        update_range(2 * node + 1, mid + 1, high, l, r, val);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update_range(int l, int r, long long val) {
        update_range(1, 0, n - 1, l, r, val);
    }

    // Consulta de suma en rango [l, r]
    long long query(int node, int low, int high, int l, int r) {
        push(node, low, high);

        // Caso 1: Disjunto
        if (high < l || low > r) {
            return 0;
        }

        // Caso 2: Solapamiento total
        if (l <= low && high <= r) {
            return tree[node];
        }

        // Caso 3: Solapamiento parcial
        int mid = low + (high - low) / 2;
        long long izq = query(2 * node, low, mid, l, r);
        long long der = query(2 * node + 1, mid + 1, high, l, r);
        return izq + der;
    }

    long long query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: Segment Tree Lazy Sum (Range Add & Range Sum) ===\n";
    vector<long long> datos = {1, 2, 3, 4, 5, 6, 7, 8};

    SegmentTreeLazySum st(datos);

    // Consulta inicial en [0, 7] => Suma 1..8 = 36
    cout << "Suma inicial total [0, 7]: " << st.query(0, 7) << " (Esperado: 36)\n";

    // Sumar 10 al rango [2, 5] (longitud 4)
    // Elementos originales en [2, 5]: {3, 4, 5, 6} (suma = 18)
    // Tras sumar 10: {13, 14, 15, 16} (suma = 58, incremento de 4 * 10 = 40)
    cout << "\nSumando 10 a rango [2, 5]...\n";
    st.update_range(2, 5, 10);

    cout << "Suma en rango [2, 5]: " << st.query(2, 5) << " (Esperado: 58)\n";
    cout << "Suma en rango [0, 2] ({1, 2, 13}): " << st.query(0, 2) << " (Esperado: 16)\n";
    cout << "Nueva suma total [0, 7]: " << st.query(0, 7) << " (Esperado: 76)\n";

    // Sumar 5 al rango [4, 7] (longitud 4)
    cout << "\nSumando 5 a rango [4, 7]...\n";
    st.update_range(4, 7, 5);

    // Elementos ahora:
    // 0: 1
    // 1: 2
    // 2: 13
    // 3: 14
    // 4: 15 + 5 = 20
    // 5: 16 + 5 = 21
    // 6: 7 + 5 = 12
    // 7: 8 + 5 = 13
    // Suma [3, 6] = 14 + 20 + 21 + 12 = 67
    cout << "Suma en rango [3, 6]: " << st.query(3, 6) << " (Esperado: 67)\n";

    return 0;
}
