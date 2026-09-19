/**
 * ============================================================================
 * PLANTILLA: Trucos de Bits y Operaciones O(1) con Potencias de Dos
 * ARCHIVO:   cp-plantilla/math/bit_tricks_powers_of_two.cpp
 * PARADIGMA: Bit Manipulation / Bitwise Tricks / Math
 * COMPLEJIDAD:
 *   - Todas las operaciones: O(1) tiempo
 *   - Espacio auxiliar:      O(1)
 * ============================================================================
 *
 * ¿CUÁNDO SE USA?
 * 1. Problemas de conteo o búsqueda de complementos donde la meta es una potencia
 *    de dos (ej. a_i + a_j = 2^k), limitando el espacio de búsqueda a 64 objetivos.
 * 2. Redondeo de tamaños de arreglos o árboles binarios (Segment Tree, Fenwick) a
 *    la potencia de dos superior más cercana en O(1).
 * 3. Consultas en estructuras tipo Sparse Table / RMQ donde se necesita calcular
 *    el piso logarítmico floor(log2(len)) = 63 - __builtin_clzll(len) en O(1).
 * 4. Aislamiento y manipulación rápida de bits encendidos (LSB) en Fenwick Trees
 *    y máscaras de bits (Bitmasks / SOS DP).
 *
 * INVARIANTES CLAVE:
 * 1. Desbordamiento de 32 bits con signo (Undefined Behavior):
 *    - La expresión `1 << 31` en C++ opera sobre `int` de 32 bits con signo,
 *      provocando desbordamiento (UB) y generando valores negativos.
 *    - REGLA DE ORO: Utilizar siempre literales no signados de 64 bits: `1ULL << k`.
 * 2. Comportamiento en cero (x == 0):
 *    - `x & (x - 1)` evalúa a `0` cuando `x == 0`, pero `0` NO es potencia de dos.
 *      Por lo tanto, `is_power_of_two` DEBE exigir `x > 0`.
 *    - Las funciones intrínsecas `__builtin_clzll(0)` y `__builtin_ctzll(0)` son
 *      Comportamiento Indefinido (UB) en GCC/Clang si el argumento es 0. Se debe
 *      incorporar siempre una guarda explícita `if (x == 0)`.
 * 3. Límite superior en `next_power_of_two`:
 *    - Para `x > 2^63` (`x > (1ULL << 63)`), la siguiente potencia de dos no cabe
 *      en un entero de 64 bits (`uint64_t`), retornando 0 como centinela de overflow.
 * ============================================================================
 */

#include <iostream>
#include <cstdint>
#include <cassert>

namespace BitTricks {

/**
 * Calcula 2^k en O(1).
 * Requiere: 0 <= k <= 63.
 */
inline constexpr uint64_t power_of_two(int k) {
    assert(k >= 0 && k <= 63);
    return 1ULL << k;
}

/**
 * Determina si x es una potencia de dos (2^k con k >= 0) en O(1).
 * Retorna false para x == 0.
 */
inline constexpr bool is_power_of_two(uint64_t x) {
    return x > 0 && (x & (x - 1ULL)) == 0;
}

/**
 * Aísla el bit menos significativo encendido (LSB - Least Significant Bit) en O(1).
 * Ejemplo: lsb(12) = lsb(1100_2) = 4 (0100_2).
 * Si x == 0, retorna 0.
 */
inline constexpr uint64_t lsb(uint64_t x) {
    return x & (~x + 1ULL); // Equivalente a x & (-x) en aritmética complementaria a 2
}

/**
 * Apaga el bit menos significativo encendido (LSB) en O(1).
 * Base de la técnica de Brian Kernighan para iterar sobre bits encendidos.
 */
inline constexpr uint64_t clear_lsb(uint64_t x) {
    return x & (x - 1ULL);
}

/**
 * Cuenta la cantidad de ceros a la derecha (Trailing Zeros) en O(1).
 * Para x > 0 representa el índice del bit encendido más bajo (0-indexado).
 * Si x == 0, retorna 64 (evita Undefined Behavior en __builtin_ctzll).
 */
inline int count_trailing_zeros(uint64_t x) {
    if (x == 0) return 64;
    return __builtin_ctzll(x);
}

/**
 * Retorna la mayor potencia de dos menor o igual a x en O(1).
 * Si x == 0, retorna 0 (no existe potencia de 2 <= 0).
 * Para x >= 1, calcula 2^(63 - __builtin_clzll(x)).
 */
inline uint64_t prev_power_of_two(uint64_t x) {
    if (x == 0) return 0;
    return 1ULL << (63 - __builtin_clzll(x));
}

/**
 * Retorna la menor potencia de dos mayor o igual a x en O(1).
 * Para x <= 1, retorna 1.
 * Si x > 2^63, la respuesta excede la capacidad de uint64_t y retorna 0 (overflow).
 */
inline uint64_t next_power_of_two(uint64_t x) {
    if (x <= 1) return 1;
    if (x > (1ULL << 63)) return 0; // Overflow sentinel
    return 1ULL << (64 - __builtin_clzll(x - 1ULL));
}

} // namespace BitTricks

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "=== DEMOSTRACIÓN: Bit Tricks & Powers of Two ===\n";

    // 1. Verificación de potencias de 2 (power_of_two e is_power_of_two)
    assert(!BitTricks::is_power_of_two(0));
    assert(BitTricks::is_power_of_two(1));  // 2^0
    assert(BitTricks::is_power_of_two(2));  // 2^1
    assert(BitTricks::is_power_of_two(4));  // 2^2
    assert(BitTricks::is_power_of_two(1ULL << 30));
    assert(BitTricks::is_power_of_two(1ULL << 62));
    assert(BitTricks::is_power_of_two(1ULL << 63));

    assert(!BitTricks::is_power_of_two(3));
    assert(!BitTricks::is_power_of_two(5));
    assert(!BitTricks::is_power_of_two(6));
    assert(!BitTricks::is_power_of_two(7));
    assert(!BitTricks::is_power_of_two(1000));
    assert(!BitTricks::is_power_of_two((1ULL << 30) + 1));
    assert(!BitTricks::is_power_of_two(~0ULL)); // Todos los bits en 1

    for (int k = 0; k < 64; ++k) {
        uint64_t p = BitTricks::power_of_two(k);
        assert(BitTricks::is_power_of_two(p));
        assert(BitTricks::count_trailing_zeros(p) == k);
    }
    std::cout << "[OK] is_power_of_two y power_of_two verificados en todos los rangos.\n";

    // 2. Verificación de prev_power_of_two
    assert(BitTricks::prev_power_of_two(0) == 0);
    assert(BitTricks::prev_power_of_two(1) == 1);
    assert(BitTricks::prev_power_of_two(2) == 2);
    assert(BitTricks::prev_power_of_two(3) == 2);
    assert(BitTricks::prev_power_of_two(4) == 4);
    assert(BitTricks::prev_power_of_two(5) == 4);
    assert(BitTricks::prev_power_of_two(6) == 4);
    assert(BitTricks::prev_power_of_two(7) == 4);
    assert(BitTricks::prev_power_of_two(8) == 8);
    assert(BitTricks::prev_power_of_two(15) == 8);
    assert(BitTricks::prev_power_of_two(16) == 16);
    assert(BitTricks::prev_power_of_two(1000) == 512);
    assert(BitTricks::prev_power_of_two((1ULL << 62) + 500) == (1ULL << 62));
    assert(BitTricks::prev_power_of_two(1ULL << 63) == (1ULL << 63));
    assert(BitTricks::prev_power_of_two(~0ULL) == (1ULL << 63));
    std::cout << "[OK] prev_power_of_two verificado correctamente.\n";

    // 3. Verificación de next_power_of_two
    assert(BitTricks::next_power_of_two(0) == 1);
    assert(BitTricks::next_power_of_two(1) == 1);
    assert(BitTricks::next_power_of_two(2) == 2);
    assert(BitTricks::next_power_of_two(3) == 4);
    assert(BitTricks::next_power_of_two(4) == 4);
    assert(BitTricks::next_power_of_two(5) == 8);
    assert(BitTricks::next_power_of_two(7) == 8);
    assert(BitTricks::next_power_of_two(8) == 8);
    assert(BitTricks::next_power_of_two(9) == 16);
    assert(BitTricks::next_power_of_two(1000) == 1024);
    assert(BitTricks::next_power_of_two((1ULL << 62) - 1) == (1ULL << 62));
    assert(BitTricks::next_power_of_two(1ULL << 62) == (1ULL << 62));
    assert(BitTricks::next_power_of_two((1ULL << 62) + 1) == (1ULL << 63));
    assert(BitTricks::next_power_of_two(1ULL << 63) == (1ULL << 63));
    assert(BitTricks::next_power_of_two((1ULL << 63) + 1) == 0); // Overflow sentinel
    std::cout << "[OK] next_power_of_two verificado correctamente.\n";

    // 4. Verificación de LSB y count_trailing_zeros
    assert(BitTricks::lsb(0) == 0);
    assert(BitTricks::lsb(1) == 1);
    assert(BitTricks::lsb(12) == 4); // 1100_2 -> 0100_2
    assert(BitTricks::lsb(40) == 8); // 101000_2 -> 001000_2
    assert(BitTricks::lsb(1ULL << 63) == (1ULL << 63));

    assert(BitTricks::clear_lsb(12) == 8);
    assert(BitTricks::clear_lsb(8) == 0);
    assert(BitTricks::clear_lsb(7) == 6);

    assert(BitTricks::count_trailing_zeros(0) == 64);
    assert(BitTricks::count_trailing_zeros(1) == 0);
    assert(BitTricks::count_trailing_zeros(12) == 2);
    assert(BitTricks::count_trailing_zeros(40) == 3);
    assert(BitTricks::count_trailing_zeros(1ULL << 63) == 63);
    std::cout << "[OK] lsb, clear_lsb y count_trailing_zeros verificados correctamente.\n";

    std::cout << "\nTodas las aserciones pasaron exitosamente sin errores.\n";
    return 0;
}
