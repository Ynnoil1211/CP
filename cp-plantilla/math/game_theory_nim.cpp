/**
 * ============================================================================
 * PLANTILLA: Teoría de Juegos Combinatorios, Nim y Operaciones XOR
 * ARCHIVO:   cp-plantilla/math/game_theory_nim.cpp
 * PARADIGMA: Game Theory / Sprague-Grundy / Bit Manipulation
 * COMPLEJIDAD:
 *   - xor_n(N):       O(1) tiempo, O(1) espacio
 *   - xor_range(L, R):O(1) tiempo, O(1) espacio
 *   - mex(V):         O(K) tiempo, O(K) espacio (donde K = V.size())
 *   - Nim Sum:        O(P) tiempo (donde P = número de pilas)
 * ============================================================================
 *
 * ¿CUÁNDO SE USA?
 * 1. Juegos combinatorios imparciales bajo convención normal (el último jugador
 *    en mover gana; quien no puede mover pierde):
 *    - Juego de Nim clásico y sus variantes (pilas de fichas con restricciones).
 * 2. Teorema de Sprague-Grundy:
 *    - Cualquier juego imparcial es equivalente a una pila de Nim con tamaño
 *      igual a su valor Grundy: G(estado) = mex({G(sucesor) | sucesor válido}).
 *    - La suma de juegos independientes equivale al XOR de sus valores Grundy:
 *      G_total = G_1 ^ G_2 ^ ... ^ G_k.
 *    - Si G_total != 0, la posición es ganadora (N-position) para el jugador actual.
 *    - Si G_total == 0, la posición es perdedora (P-position) para el jugador actual.
 * 3. Conteo y consultas de XOR en rangos continuos [L, R] en O(1) para L, R hasta 10^18.
 *
 * INVARIANTES CLAVE:
 * 1. Periodicidad de XOR de Prefijos (módulo 4):
 *    - La secuencia 1 ^ 2 ^ ... ^ n se anula en ciclos de 4 enteros:
 *      (4k) ^ (4k + 1) ^ (4k + 2) ^ (4k + 3) = 0.
 *    - Por ende, evaluar n % 4 proporciona el XOR acumulado en O(1):
 *      * n % 4 == 0 -> n
 *      * n % 4 == 1 -> 1
 *      * n % 4 == 2 -> n + 1
 *      * n % 4 == 3 -> 0
 * 2. Cota del MEX por Principio del Palomar:
 *    - Para un conjunto de K elementos, es imposible que contenga simultáneamente
 *      a los K + 1 enteros del rango [0, K].
 *    - Por lo tanto, el MEX siempre pertenece a [0, K]. Un arreglo booleano de
 *      tamaño K + 1 es suficiente para resolverlo en tiempo lineal O(K).
 * 3. Propiedad Cancelativa de XOR:
 *    - a ^ a = 0 y a ^ 0 = a.
 *    - xor_range(l, r) = xor_n(r) ^ xor_n(l - 1).
 * 4. Teorema de Bouton (Nim Clásico):
 *    - Un estado con nim-sum == 0 solo puede transicionar a estados con nim-sum != 0.
 *    - Un estado con nim-sum != 0 siempre cuenta con al menos un movimiento hacia nim-sum == 0.
 * ============================================================================
 */

#include <iostream>
#include <vector>

/**
 * Calcula 1 ^ 2 ^ 3 ^ ... ^ n en O(1) tiempo evaluando n % 4.
 * Retorna 0 si n <= 0.
 */
long long xor_n(long long n) {
    if (n < 0) return 0;
    long long rem = n % 4;
    if (rem == 0) return n;
    if (rem == 1) return 1;
    if (rem == 2) return n + 1;
    return 0; // rem == 3
}

/**
 * Calcula el XOR de todos los enteros en el intervalo cerrado [l, r] en O(1).
 * Propiedad: l ^ (l + 1) ^ ... ^ r = xor_n(r) ^ xor_n(l - 1).
 * Retorna 0 si l > r.
 */
long long xor_range(long long l, long long r) {
    if (l > r) return 0;
    return xor_n(r) ^ xor_n(l - 1);
}

/**
 * Minimum Excluded Value (MEX):
 * Retorna el menor entero no negativo (>= 0) que NO aparece en el vector v.
 * Complejidad: O(K) tiempo y O(K) espacio, donde K = v.size().
 */
int mex(const std::vector<int>& v) {
    int n = static_cast<int>(v.size());
    std::vector<bool> present(n + 1, false);
    for (int x : v) {
        if (x >= 0 && x <= n) {
            present[x] = true;
        }
    }
    for (int i = 0; i <= n; i++) {
        if (!present[i]) return i;
    }
    return n + 1;
}

/**
 * Determina si el estado de Nim con las pilas dadas es posición ganadora (N-position).
 * Retorna true si el primer jugador en mover tiene estrategia ganadora (nim-sum != 0).
 */
bool nim_is_winning(const std::vector<long long>& piles) {
    long long nim_sum = 0;
    for (long long x : piles) {
        nim_sum ^= x;
    }
    return nim_sum != 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "=== Demostracion: Teoria de Juegos (Nim) y Operaciones XOR ===\n";

    // 1. Prefijo XOR continuo 1 ^ 2 ^ ... ^ n en O(1)
    std::cout << "\n--- Prefijo XOR Continuo xor_n(n) en O(1) ---\n";
    for (int n = 1; n <= 8; n++) {
        std::cout << "xor_n(" << n << ") = " << xor_n(n) << "\n";
    }
    std::cout << "xor_n(10^12) = " << xor_n(1000000000000LL) << "\n";

    // 2. XOR en rango continuo [L, R] en O(1)
    std::cout << "\n--- XOR en Rango [L, R] en O(1) ---\n";
    std::cout << "xor_range(1, 10)  = " << xor_range(1, 10) << "\n";
    std::cout << "xor_range(5, 15)  = " << xor_range(5, 15) << "\n";
    std::cout << "xor_range(33, 77) = " << xor_range(33, 77) << "\n";

    // 3. Minimum Excluded Value (MEX)
    std::cout << "\n--- Minimum Excluded Value (MEX) ---\n";
    std::vector<int> v1 = {0, 1, 2, 4};
    std::vector<int> v2 = {1, 2, 3};
    std::vector<int> v3 = {0, 1, 2};
    std::cout << "mex({0, 1, 2, 4}) = " << mex(v1) << "\n"; // 3
    std::cout << "mex({1, 2, 3})    = " << mex(v2) << "\n"; // 0
    std::cout << "mex({0, 1, 2})    = " << mex(v3) << "\n"; // 3

    // 4. Sprague-Grundy en juego de sustraccion (retirar 1, 2 o 3 fichas)
    std::cout << "\n--- Valores Grundy en Juego de Sustraccion (1, 2 o 3 fichas) ---\n";
    std::cout << "Fichas s -> G(s):\n";
    std::vector<int> grundy = {0};
    for (int s = 1; s <= 8; s++) {
        std::vector<int> transitions;
        if (s >= 1) transitions.push_back(grundy[s - 1]);
        if (s >= 2) transitions.push_back(grundy[s - 2]);
        if (s >= 3) transitions.push_back(grundy[s - 3]);
        grundy.push_back(mex(transitions));
        std::cout << "  s = " << s << " -> G(" << s << ") = " << grundy[s]
                  << (grundy[s] != 0 ? " (Posicion ganadora)" : " (Posicion perdedora)") << "\n";
    }

    // 5. Juego de Nim clasico
    std::cout << "\n--- Juego de Nim Clasico ---\n";
    std::vector<long long> piles1 = {3, 4, 5};
    std::vector<long long> piles2 = {1, 2, 3};
    std::vector<long long> piles3 = {42, 42};

    std::cout << "Pilas {3, 4, 5}: "
              << (nim_is_winning(piles1) ? "Gana el Jugador 1" : "Gana el Jugador 2") << "\n";
    std::cout << "Pilas {1, 2, 3}: "
              << (nim_is_winning(piles2) ? "Gana el Jugador 1" : "Gana el Jugador 2") << "\n";
    std::cout << "Pilas {42, 42}:  "
              << (nim_is_winning(piles3) ? "Gana el Jugador 1" : "Gana el Jugador 2") << "\n";

    std::cout.flush();
    return 0;
}
