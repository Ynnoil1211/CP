/**
 * ============================================================================
 * PLANTILLA: Segment Tree Iterativo (0-indexed, semi-abierto [l, r))
 * ARCHIVO:   cp-plantilla/data-structures/segment_tree_iterativo.cpp
 * PARADIGMA: Estructuras de Datos / Rango
 * COMPLEJIDAD:
 *   - Construcción (build): O(N)
 *   - Actualización puntual (update): O(log N)
 *   - Consulta de rango (query): O(log N)
 *   - Espacio: O(N) — tamaño exacto 2 * N
 * ============================================================================
 *
 * 📌 DETALLES Y REGLAS CLAVE (RULES OF THUMB):
 * 
 * 1. ¿POR QUÉ EL INTERVALO ES SEMI-ABIERTO [l, r)?
 *    El algoritmo iterativo clásico utiliza la elegante condición de parada `l < r`.
 *    - Si `l` es impar (`l & 1`), `l` es el hijo derecho de su padre; por tanto, su
 *      padre incluye elementos fuera del rango a la izquierda. Tomamos `tree[l]` y
 *      avanzamos `l++` antes de subir de nivel con `l >>= 1`.
 *    - Si `r` es impar (`r & 1`), el límite superior abierto `r` está a la derecha
 *      inmediata de un hijo izquierdo (`r - 1`). Hacemos `--r` primero y tomamos
 *      `tree[r]`, luego subimos con `r >>= 1`.
 *    - Esto garantiza que nunca procesemos nodos fuera del rango y evita recursión.
 *
 * 2. CÓMO CONSULTAR UN RANGO CERRADO [left, right]:
 *    Simplemente llama a: `st.query(left, right + 1)`.
 *
 * 3. ¿CUÁNDO ES OPCIONAL build()?
 *    Si el arreglo inicial consiste únicamente de elementos neutros (ej. ceros en suma,
 *    infinito en mínimo), NO es necesario llamar a `build()`. Puedes inicializar el
 *    árbol en neutro y poblarlo directamente con llamadas a `update()`.
 *
 * 4. VENTAJA COMPETITIVA:
 *    - 2x a 4x más rápido que la versión recursiva gracias a la localidad de caché
 *      y ausencia de overhead de llamadas recursivas en el call-stack.
 *    - Memoria mínima: vector de tamaño exacto `2 * N`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct SegmentTreeIterativo {
    int n;
    T neutro;
    vector<T> tree;

    // Función de combinación asociativa (ej. suma, min, max, gcd)
    T combinar(T a, T b) const {
        return a + b; // Cambiar a min(a, b), max(a, b), etc. según el problema
    }

    SegmentTreeIterativo(int n, T neutro = 0) : n(n), neutro(neutro), tree(2 * n, neutro) {}

    SegmentTreeIterativo(const vector<T>& arr, T neutro = 0) : n(arr.size()), neutro(neutro), tree(2 * n, neutro) {
        build(arr);
    }

    // Construcción en O(N): llena las hojas [n, 2n - 1] y calcula los padres hacia atrás
    void build(const vector<T>& arr) {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = arr[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = combinar(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    // Actualización puntual: modifica la posición p (0-indexed) con val
    void update(int p, T val) {
        for (tree[p += n] = val; p > 1; p >>= 1) {
            // p ^ 1 obtiene el hermano (left/right sibling)
            tree[p >> 1] = combinar(tree[p], tree[p ^ 1]);
        }
    }

    // Consulta de rango en intervalo semi-abierto [l, r) (0-indexed)
    // Para consultar un rango cerrado [L, R], llamar: query(L, R + 1)
    T query(int l, int r) const {
        T res_izq = neutro;
        T res_der = neutro;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res_izq = combinar(res_izq, tree[l++]);
            if (r & 1) res_der = combinar(tree[--r], res_der);
        }
        return combinar(res_izq, res_der);
    }
};

int main() {
    // Optimización de I/O para Programación Competitiva
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== DEMOSTRACIÓN: Segment Tree Iterativo ===\n";
    vector<long long> datos = {1, 3, 5, 7, 9, 11};

    SegmentTreeIterativo<long long> st(datos, 0);

    // Consulta en rango [1, 4] inclusivo => índices 1 a 4: {3, 5, 7, 9} => Suma = 24
    int l = 1, r = 4;
    cout << "Suma en rango cerrado [" << l << ", " << r << "]: " 
         << st.query(l, r + 1) << " (Esperado: 24)\n";

    // Actualización puntual: cambiar posición 2 (valor 5) por 10
    cout << "Actualizando posicion 2 con valor 10...\n";
    st.update(2, 10);

    // Nueva consulta en rango [1, 4]: {3, 10, 7, 9} => Suma = 29
    cout << "Nueva suma en rango cerrado [" << l << ", " << r << "]: " 
         << st.query(l, r + 1) << " (Esperado: 29)\n";

    return 0;
}
