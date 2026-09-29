/**
 * ============================================================================
 * PLANTILLA: Exponenciación de Matrices (Matrix Exponentiation)
 * ARCHIVO:   cp-plantilla/math/matrix_exponentiation.cpp
 * PARADIGMA: Linear Algebra / Divide & Conquer / DP Acceleration
 * COMPLEJIDAD:
 *   - Multiplicación de Matrices (N x N): O(N^3) tiempo
 *   - Exponenciación a la potencia P:     O(N^3 * log P) tiempo
 *   - Espacio auxiliar:                  O(N^2)
 * ============================================================================
 *
 * ¿CUÁNDO SE USA?
 * 1. Aceleración de recurrencias lineales homogéneas donde el índice N es
 *    gigantesco (N hasta 10^18), haciendo inviable una solución de DP lineal O(N):
 *    - Sucesión de Fibonacci, Tribonacci, números de Lucas.
 *    - Transiciones de DP que solo dependen de los últimos k estados.
 * 2. Conteo de caminos de longitud exacta k en grafos dirigidos:
 *    - Si A es la matriz de adyacencia (A[u][v] = cantidad de aristas de u a v),
 *      entonces (A^k)[u][v] es el número exacto de caminos de longitud k desde u hasta v.
 * 3. Caminos de longitud mínima/máxima en grafos (álgebra min-plus o max-plus).
 *
 * INVARIANTES CLAVE:
 * 1. Elemento neutro (Matriz Identidad I):
 *    - I[i][i] = 1, e I[i][j] = 0 para todo i != j.
 *    - Para cualquier matriz cuadrada A: A * I = I * A = A, y A^0 = I.
 * 2. Orden de bucles en multiplicación (IKJ) y poda de ceros:
 *    - Recorrer i -> p -> j en lugar de i -> j -> p maximiza la localidad temporal
 *      y espacial en memoria caché (lectura secuencial de b[p][j]).
 *    - La guarda `if (a[i][p] == 0) continue;` reduce drásticamente el tiempo en
 *      matrices de adyacencia dispersas.
 * 3. Desbordamiento de 64 bits en aritmética modular:
 *    - Cuando mod > 10^9, la multiplicación a[i][p] * b[p][j] puede desbordar long long.
 *    - Se utiliza cast a __int128 para calcular el producto antes de aplicar % mod.
 * 4. Dimensión compatible:
 *    - La exponenciación binaria de matrices requiere matrices cuadradas (N x N).
 * ============================================================================
 */

#include <iostream>
#include <vector>

// Tipo de dato minimalista para matrices en CP
using Mat = std::vector<std::vector<long long>>;

/**
 * Crea una matriz identidad cuadrada de tamaño n x n.
 * I[i][j] = (i == j ? 1 : 0).
 */
Mat make_identity(int n) {
    Mat id(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        id[i][i] = 1;
    }
    return id;
}

/**
 * Multiplica dos matrices cuadradas a y b de tamaño n x n bajo módulo mod.
 * Utiliza orden de bucles IKJ y poda de ceros para óptimo rendimiento de caché.
 * Complejidad: O(N^3) operaciones.
 */
Mat mul(const Mat& a, const Mat& b, long long mod) {
    int n = static_cast<int>(a.size());
    int m = static_cast<int>(b.size());
    int k = static_cast<int>(b[0].size());
    Mat c(n, std::vector<long long>(k, 0));
    for (int i = 0; i < n; i++) {
        for (int p = 0; p < m; p++) {
            if (a[i][p] == 0) continue; // Poda de ceros
            for (int j = 0; j < k; j++) {
                c[i][j] = static_cast<long long>(
                    (c[i][j] + static_cast<__int128>(a[i][p]) * b[p][j]) % mod
                );
            }
        }
    }
    return c;
}

/**
 * Eleva una matriz cuadrada a a la potencia p bajo módulo mod usando exponenciación binaria.
 * Complejidad: O(N^3 * log p).
 */
Mat matpow(Mat a, long long p, long long mod) {
    int n = static_cast<int>(a.size());
    Mat res = make_identity(n);
    while (p > 0) {
        if (p & 1) res = mul(res, a, mod);
        a = mul(a, a, mod);
        p >>= 1;
    }
    return res;
}

/**
 * Calcula el n-ésimo término de Fibonacci en O(log n) usando exponenciación de matrices.
 * Definición estándar: F_0 = 0, F_1 = 1, F_2 = 1, F_3 = 2, ...
 */
long long fibonacci(long long n, long long mod) {
    if (n == 0) return 0;
    if (n == 1) return 1 % mod;
    Mat t = {
        {1, 1},
        {1, 0}
    };
    Mat tn = matpow(t, n, mod);
    // [F_{n+1}, F_n]^T = T^n * [F_1, F_0]^T = T^n * [1, 0]^T
    // Por lo tanto: F_n = T^n[1][0] * 1 + T^n[1][1] * 0 = T^n[1][0]
    return tn[1][0];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "=== Demostracion: Exponenciacion de Matrices ===\n";

    constexpr long long MOD = 1000000007LL; // 10^9 + 7

    // 1. Sucesion de Fibonacci en O(log N)
    std::cout << "\n--- Sucesion de Fibonacci en O(log N) ---\n";
    for (int i = 0; i <= 10; i++) {
        std::cout << "F_" << i << " = " << fibonacci(i, MOD) << "\n";
    }
    std::cout << "F_50 mod (10^9 + 7)         = " << fibonacci(50, MOD) << "\n";
    std::cout << "F_1000000000 mod (10^9 + 7) = " << fibonacci(1000000000LL, MOD) << "\n";

    // 2. Multiplicacion y potencia de matrices genericas
    std::cout << "\n--- Potencia de Matriz 2x2 ---\n";
    Mat a = {
        {1, 1},
        {1, 0}
    };
    Mat a5 = matpow(a, 5, MOD);
    std::cout << "Matriz T^5:\n";
    for (const auto& row : a5) {
        std::cout << "  ";
        for (long long val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    // 3. Conteo de caminos de longitud k en grafo dirigido
    std::cout << "\n--- Conteo de Caminos en Grafo Dirigido ---\n";
    // Grafo con 4 vertices (0, 1, 2, 3):
    // 0 -> 1, 0 -> 2, 1 -> 2, 1 -> 3, 2 -> 3, 3 -> 0
    int num_v = 4;
    Mat adj(num_v, std::vector<long long>(num_v, 0));
    adj[0][1] = 1;
    adj[0][2] = 1;
    adj[1][2] = 1;
    adj[1][3] = 1;
    adj[2][3] = 1;
    adj[3][0] = 1;

    int k = 3;
    Mat paths_k = matpow(adj, k, MOD);
    std::cout << "Numero de caminos de longitud k = " << k << " entre cada par (u -> v):\n";
    for (int u = 0; u < num_v; u++) {
        for (int v = 0; v < num_v; v++) {
            std::cout << "  De " << u << " a " << v << ": " << paths_k[u][v] << " caminos\n";
        }
    }

    std::cout.flush();
    return 0;
}
