/**
 * ============================================================================
 * PLANTILLA: Aritmética Modular, Exponenciación Rápida y Combinatoria nCr
 * ARCHIVO:   cp-plantilla/math/aritmetica_modular.cpp
 * PARADIGMA: Number Theory / Modular Arithmetic / Combinatorics
 * COMPLEJIDAD:
 *   - Suma, Resta, Multiplicación: O(1) tiempo, O(1) espacio
 *   - Exponenciación Binaria:      O(log B) tiempo, O(1) espacio
 *   - Inverso (Fermat):            O(log MOD) tiempo (requiere MOD primo)
 *   - Inverso (Euclides Extendido):O(log(min(A, MOD))) tiempo (módulo general coprimo)
 *   - Precomputación Factoriales:  O(N) tiempo, O(N) espacio
 *   - Consulta nCr, nPr:           O(1) tiempo
 * ============================================================================
 *
 * ¿CUÁNDO SE USA?
 * 1. Problemas de conteo, caminos en grafos, DP combinatoria o probabilidad
 *    donde la respuesta debe imprimirse módulo 10^9 + 7 o módulo 998244353.
 * 2. Cálculo recurrente de coeficientes binomiales nCr(n, r) para consultas
 *    múltiples (hasta Q = 10^6 consultas con N <= 10^6).
 * 3. División bajo módulo: a / b (mod m) no existe en aritmética entera directa;
 *    se reemplaza por a * inv(b) (mod m), calculando el inverso modular
 *    mediante Fermat (m primo) o Euclides Extendido (m compuesto con gcd(b, m) = 1).
 * 4. Potenciación gigantesca a^B (mod m) con B hasta 10^18 en O(log B).
 *
 * INVARIANTES CLAVE:
 * 1. Manejo estricto de números negativos:
 *    - En C++, el operador % con operandos negativos produce residuos negativos.
 *    - Para garantizar resultados canónicos en el rango [0, m - 1], siempre usar:
 *      ((x % m) + m) % m.
 * 2. Desbordamiento de 64 bits en Multiplicación:
 *    - Si a, b < 10^9, (a * b) cabe en long long (64 bits, hasta ~9 * 10^18).
 *    - Si mod > 2 * 10^9, a * b puede desbordar long long; usar cast a __int128.
 * 3. Condición de existencia del Inverso Modular:
 *    - inv(a) mod m existe SI Y SOLO SI gcd(a, m) == 1 (coprimos).
 *    - Si m es primo y a % m != 0, el Teorema de Fermat garantiza inv(a) = a^(m - 2) mod m.
 *    - Si m es compuesto (ej. m = 1000, a = 7), Fermat NO aplica; se DEBE usar
 *      Euclides Extendido (extgcd).
 * 4. Precomputación lineal de inversos factoriales O(N):
 *    - Se calcula inv_fact[N] = inv_fermat(fact[N], m) con una sola exponenciación binaria.
 *    - Se llena hacia atrás en O(1) por paso: inv_fact[i] = inv_fact[i + 1] * (i + 1) mod m.
 *    - Esto es más rápido y compacto que calcular inversos individuales.
 * ============================================================================
 */

#include <iostream>
#include <vector>

constexpr long long DEFAULT_MOD = 1000000007LL; // 10^9 + 7

// Normaliza cualquier entero x al rango canónico [0, m - 1]
inline long long normalize(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// Suma modular: (a + b) mod m
inline long long add(long long a, long long b, long long m = DEFAULT_MOD) {
    long long res = (a % m + b % m) % m;
    if (res < 0) res += m;
    return res;
}

// Resta modular: (a - b) mod m
inline long long sub(long long a, long long b, long long m = DEFAULT_MOD) {
    long long res = (a % m - b % m) % m;
    if (res < 0) res += m;
    return res;
}

// Multiplicación modular segura evitando desbordamiento de 64 bits
inline long long mul(long long a, long long b, long long m = DEFAULT_MOD) {
    a = normalize(a, m);
    b = normalize(b, m);
    return static_cast<long long>(static_cast<__int128>(a) * b % m);
}

// Exponenciación Binaria Rápida: (base^exp) mod m en O(log exp)
long long binpow(long long base, long long exp, long long m = DEFAULT_MOD) {
    if (m == 1) return 0;
    base = normalize(base, m);
    long long res = 1;
    while (exp > 0) {
        if (exp & 1) res = mul(res, base, m);
        base = mul(base, base, m);
        exp >>= 1;
    }
    return res;
}

// Algoritmo de Euclides Extendido: encuentra g = gcd(a, b) y coeficientes tales que a*x + b*y = g
long long extgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}

// Inverso modular por Pequeño Teorema de Fermat: a^(m - 2) mod m (requiere m primo)
inline long long inv_fermat(long long a, long long m = DEFAULT_MOD) {
    a = normalize(a, m);
    return binpow(a, m - 2, m);
}

// Inverso modular general por Euclides Extendido (válido para m compuesto; retorna -1 si no son coprimos)
long long inv_extgcd(long long a, long long m) {
    long long x, y;
    long long g = extgcd(a, m, x, y);
    if (g != 1 && g != -1) return -1; // No existe inverso si gcd(a, m) != 1
    return normalize(x, m);
}

// ----------------------------------------------------------------------------
// Combinatoria O(N) precomputada con consultas O(1)
// ----------------------------------------------------------------------------
const int MAX_FACT = 1000005;
long long fact[MAX_FACT];
long long inv_fact[MAX_FACT];
long long inv[MAX_FACT];

// Precomputa factoriales e inversos factoriales hasta n en O(N) tiempo
void init_fact(int n, long long m = DEFAULT_MOD) {
    fact[0] = 1;
    inv_fact[0] = 1;
    inv[0] = 0;

    for (int i = 1; i <= n; i++) {
        fact[i] = mul(fact[i - 1], i, m);
    }

    inv_fact[n] = inv_fermat(fact[n], m);
    for (int i = n - 1; i >= 1; i--) {
        inv_fact[i] = mul(inv_fact[i + 1], i + 1, m);
    }

    // Inversos individuales 1..n: inv[i] = fact[i - 1] * inv_fact[i] mod m
    for (int i = 1; i <= n; i++) {
        inv[i] = mul(fact[i - 1], inv_fact[i], m);
    }
}

// Coeficiente Binomial nCr = n! / (r! * (n - r)!) mod m en O(1)
inline long long nCr(int n, int r, long long m = DEFAULT_MOD) {
    if (r < 0 || r > n || n < 0) return 0;
    long long den = mul(inv_fact[r], inv_fact[n - r], m);
    return mul(fact[n], den, m);
}

// Permutación nPr = n! / (n - r)! mod m en O(1)
inline long long nPr(int n, int r, long long m = DEFAULT_MOD) {
    if (r < 0 || r > n || n < 0) return 0;
    return mul(fact[n], inv_fact[n - r], m);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "=== Demostracion: Aritmetica Modular y Combinatoria ===\n";

    constexpr long long MOD = 1000000007LL; // 10^9 + 7

    // 1. Operaciones basicas con normalizacion automatica de negativos
    std::cout << "\n--- Operaciones Modulares Basicas ---\n";
    long long a = -3, b = 8;
    std::cout << "Normalizar -3 mod 10 = " << normalize(a, 10) << "\n";
    std::cout << "(-3 + 8) mod 10       = " << add(a, b, 10) << "\n";
    std::cout << "(-3 - 8) mod 10       = " << sub(a, b, 10) << "\n";
    std::cout << "(-3 * 8) mod 10       = " << mul(a, b, 10) << "\n";

    // 2. Exponenciacion binaria rapida
    std::cout << "\n--- Exponenciacion Rapida ---\n";
    std::cout << "2^10 mod (10^9 + 7)  = " << binpow(2, 10, MOD) << "\n";
    std::cout << "3^4 mod 100          = " << binpow(3, 4, 100) << "\n";
    std::cout << "7^(10^9 + 5) mod MOD = " << binpow(7, MOD - 2, MOD) << "\n";

    // 3. Inverso modular: Fermat vs Euclides Extendido
    std::cout << "\n--- Inverso Modular ---\n";
    long long inv_fermat_val = inv_fermat(3, MOD);
    std::cout << "Inverso de 3 mod (10^9 + 7) [Fermat]: " << inv_fermat_val << "\n";
    std::cout << "Comprobacion (3 * inv) mod MOD:       " << mul(3, inv_fermat_val, MOD) << "\n";

    // Inverso con modulo compuesto (Fermat no aplica, gcd(7, 1000) = 1)
    long long inv_comp = inv_extgcd(7, 1000);
    std::cout << "Inverso de 7 mod 1000 [Euclides Ext]: " << inv_comp << "\n";
    std::cout << "Comprobacion (7 * inv) mod 1000:      " << mul(7, inv_comp, 1000) << "\n";

    // 4. Precomputacion combinatoria nCr y nPr
    std::cout << "\n--- Combinatoria nCr y nPr ---\n";
    init_fact(1000, MOD);
    std::cout << "nCr(10, 3) mod (10^9 + 7)   = " << nCr(10, 3, MOD) << "\n";
    std::cout << "nCr(5, 2) mod (10^9 + 7)    = " << nCr(5, 2, MOD) << "\n";
    std::cout << "nPr(5, 2) mod (10^9 + 7)    = " << nPr(5, 2, MOD) << "\n";
    std::cout << "nCr(100, 50) mod (10^9 + 7) = " << nCr(100, 50, MOD) << "\n";

    std::cout.flush();
    return 0;
}
