/**
 * ============================================================================
 * PLANTILLA: Criba Lineal de Euler, SPF (Smallest Prime Factor) y Función Phi
 * ARCHIVO:   cp-plantilla/math/criba_spf.cpp
 * PARADIGMA: Number Theory / Prime Sieve / Multiplicative Functions
 * COMPLEJIDAD:
 *   - Precomputación Criba Lineal (SPF): O(MAXN) tiempo, O(MAXN) espacio
 *   - Consulta de Primalidad:            O(1) tiempo
 *   - Factorización Prima con SPF:       O(log X) tiempo por consulta
 *   - Obtención de Divisores con SPF:    O(d(X)) tiempo (d(X) = número de divisores)
 *   - Función Phi de Euler (con SPF):    O(log X) tiempo por consulta
 *   - Función Phi de Euler (aislada):    O(sqrt(N)) tiempo, O(1) espacio
 * ============================================================================
 *
 * ¿CUÁNDO SE USA?
 * 1. Factorización de múltiples números (hasta Q = 10^6 consultas con X <= 10^7):
 *    - La factorización tradicional por prueba de divisiones toma O(sqrt(X)) por número,
 *      resultando en TLE. Con SPF, cada factorización se reduce a O(log X).
 * 2. Conteo o enumeración rápida de divisores de muchos números en tiempo de ejecución.
 * 3. Problemas de coprimalidad, conteo de fracciones irreducibles o Teorema de
 *    Euler (a^phi(m) = 1 mod m para gcd(a, m) = 1) usando phi(N).
 * 4. Si N <= 10^7, se usa la criba lineal con SPF precomputada una sola vez.
 * 5. Si N es grande (N hasta 10^14) y solo se requiere phi(N) o factorizar un único
 *    número aislado, se utiliza el algoritmo O(sqrt(N)) sin memoria auxiliar.
 *
 * INVARIANTES CLAVE:
 * 1. Garantía de Linealidad O(MAXN) en Criba de Euler:
 *    - Cada número compuesto c = i * p se visita y marca EXACTAMENTE UNA VEZ por
 *      su menor factor primo (SPF).
 *    - La condición de parada `if (p > spf[i]) break;` es CRÍTICA:
 *      Dado que p recorre los primos en orden ascendente, cuando p supera a spf[i],
 *      cualquier producto posterior tendría a spf[i] como menor factor primo,
 *      no a p. Omitir el break degrada la complejidad a O(MAXN log log MAXN) o peor.
 * 2. Casos Borde en spf[]:
 *    - Los valores 0 y 1 NO son primos. Se inicializan como `spf[0] = spf[1] = 0`.
 *    - Un número x >= 2 es primo SI Y SOLO SI `spf[x] == x`.
 * 3. Identidad de Euler sin punto flotante ni desbordamiento:
 *    - phi(N) = N * producto_{p | N} (1 - 1/p).
 *    - Para evitar errores de precisión de double o float, se aplica la resta
 *      entera exacta: `result -= result / p;` para cada divisor primo único p.
 * 4. Factor Primo Residual > sqrt(N) en phi_single:
 *    - Al terminar el bucle hasta sqrt(N), si N > 1, el valor residual es
 *      garantizadamente un primo mayor a sqrt(N). Se debe aplicar `result -= result / N`.
 * ============================================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>

const int MAXN = 1000005;
int spf[MAXN];
std::vector<int> primes;

/**
 * Criba lineal de Euler para precalcular el menor factor primo (SPF) de 2..n en O(n) tiempo.
 */
void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > spf[i] || 1LL * i * p > n) break;
            spf[i * p] = p;
        }
    }
}

/**
 * Determina si x es primo en O(1) usando la tabla SPF.
 */
inline bool is_prime(int x) {
    return x >= 2 && x < MAXN && spf[x] == x;
}

/**
 * Factorización prima en O(log X) usando la tabla SPF.
 * Retorna pares {primo, exponente} ordenados de menor a mayor.
 * Ejemplo: factorize(360) = {{2, 3}, {3, 2}, {5, 1}}.
 */
std::vector<std::pair<int, int>> factorize(int x) {
    std::vector<std::pair<int, int>> factors;
    while (x > 1) {
        int p = spf[x];
        int count = 0;
        while (x % p == 0) {
            count++;
            x /= p;
        }
        factors.emplace_back(p, count);
    }
    return factors;
}

/**
 * Obtiene todos los divisores de x en O(d(x)) a partir de su factorización prima.
 */
std::vector<int> get_divisors(int x) {
    std::vector<int> divisors = {1};
    auto factors = factorize(x);
    for (const auto& entry : factors) {
        int p = entry.first;
        int exp = entry.second;
        int sz = static_cast<int>(divisors.size());
        int current_p = 1;
        for (int e = 1; e <= exp; e++) {
            current_p *= p;
            for (int i = 0; i < sz; i++) {
                divisors.push_back(divisors[i] * current_p);
            }
        }
    }
    return divisors;
}

/**
 * Calcula phi(x) (Función Totient de Euler) en O(log X) usando la tabla SPF.
 * Cuenta cuántos enteros k en [1, x] cumplen gcd(k, x) == 1.
 */
int phi_spf(int x) {
    if (x == 1) return 1;
    int result = x;
    int temp = x;
    while (temp > 1) {
        int p = spf[temp];
        result -= result / p;
        while (temp % p == 0) {
            temp /= p;
        }
    }
    return result;
}

/**
 * Función Totient de Euler para un número aislado grande (hasta 10^14).
 * O(sqrt(N)) tiempo, O(1) espacio auxiliar.
 */
long long phi_single(long long n) {
    if (n <= 1) return n == 1 ? 1 : 0;
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            result -= result / p;
            while (n % p == 0) {
                n /= p;
            }
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << "=== Demostracion: Criba Lineal SPF y Funcion Phi de Euler ===\n";

    constexpr int LIMIT = 1000000;
    sieve(LIMIT);

    // 1. Cantidad de primos y primalidad
    std::cout << "\n--- Primalidad y Criba Lineal ---\n";
    std::cout << "Total de primos <= 10^6: " << primes.size() << "\n";
    std::cout << "Es 17 primo?     " << (is_prime(17) ? "Si" : "No") << "\n";
    std::cout << "Es 100 primo?    " << (is_prime(100) ? "Si" : "No") << "\n";
    std::cout << "Es 999983 primo? " << (is_prime(999983) ? "Si" : "No") << "\n";

    // 2. Menor factor primo (SPF)
    std::cout << "\n--- Menor Factor Primo (SPF) ---\n";
    std::cout << "spf(15) = " << spf[15] << "\n";
    std::cout << "spf(35) = " << spf[35] << "\n";
    std::cout << "spf(77) = " << spf[77] << "\n";

    // 3. Factorizacion prima en O(log X)
    std::cout << "\n--- Factorizacion Prima en O(log X) ---\n";
    int num = 360;
    auto f360 = factorize(num);
    std::cout << "Factores primos de " << num << ": ";
    for (size_t i = 0; i < f360.size(); i++) {
        std::cout << f360[i].first << "^" << f360[i].second;
        if (i + 1 < f360.size()) std::cout << " * ";
    }
    std::cout << "\n";

    // 4. Divisores de un numero
    std::cout << "\n--- Divisores con SPF ---\n";
    auto divs = get_divisors(num);
    std::sort(divs.begin(), divs.end());
    std::cout << "Cantidad de divisores de " << num << ": " << divs.size() << "\n";
    std::cout << "Divisores de " << num << ": ";
    for (int d : divs) {
        std::cout << d << " ";
    }
    std::cout << "\n";

    // 5. Funcion Totient de Euler (Phi)
    std::cout << "\n--- Funcion Phi de Euler ---\n";
    std::cout << "phi(10)  = " << phi_spf(10) << " (coprimos: 1, 3, 7, 9)\n";
    std::cout << "phi(360) = " << phi_spf(360) << "\n";
    std::cout << "phi(17)  = " << phi_spf(17) << " (primo: p - 1)\n";

    // 6. Phi para numeros grandes (hasta 10^14) en O(sqrt N)
    std::cout << "\n--- Phi para Numeros Grandes O(sqrt N) ---\n";
    long long big_val = 1000000000000LL; // 10^12
    std::cout << "phi_single(10^12) = " << phi_single(big_val) << "\n";

    std::cout.flush();
    return 0;
}
