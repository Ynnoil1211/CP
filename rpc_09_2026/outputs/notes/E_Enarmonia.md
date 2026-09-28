# Problema E: Enarmonía

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Luis Daniel Carreño Pitalua (UFPS Cúcuta, Colombia)
- **Dificultad Estimada:** Media-Alta (Div 2D / Div 1B)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [E_Enarmonia.cpp](../../inputs/solutions/E_Enarmonia.cpp)
  - Solución Oficial (Top-Down): [E_Enarmonia_TopDown.cpp](../../inputs/official_solutions/E_Enarmonia_TopDown.cpp)
  - Solución Oficial (Bottom-Up Rolling): [E_Enarmonia_BottomUp.cpp](../../inputs/official_solutions/E_Enarmonia_BottomUp.cpp)

---

## 1. Lógica y Enfoque del Problema

Se disponen de dos manuscritos circulares con secuencias de actos de longitud `N1` y `N2` respectivamente. Se debe construir una historia de exactamente `T` actos entrelazando elementos de ambos manuscritos:
- El avance en cada manuscrito es determinista y circular: tras el acto `N_i - 1`, continúa el acto `0`.
- Se inicia obligatoriamente leyendo el primer acto del Manuscrito 1.
- Se permiten a lo sumo `K` alternancias (cambios de manuscrito).
- Un *eco* ocurre cada vez que un acto elegido es idéntico al acto inmediatamente anterior.
- **Objetivo:** Maximizar el número total de ecos en la secuencia de longitud `T`.

### ¿Por qué falla un enfoque Greedy?
Elegir vorazmente el manuscrito que produce un eco inmediato puede forzar la pérdida de múltiples ecos consecutivos posteriores o agotar de manera prematura el presupuesto de cambios `K`. La decisión óptima requiere evaluar el impacto global a lo largo de los `T` pasos: se requiere **Programación Dinámica (DP)**.

---

## 2. Modelado de Programación Dinámica

### Solución Top-Down con Memoización

Definición de estado:
`solve(c1, c2, k, m)`
- `c1`: cantidad de actos leídos del manuscrito 1 (`1 <= c1 <= T`).
- `c2`: cantidad de actos leídos del manuscrito 2 (`0 <= c2 <= T`).
- `k`: alternancias consumidas hasta el momento (`0 <= k <= K`).
- `m`: manuscrito activo en el último paso (`m in {0, 1}`).
- **Retorno:** Máximo número de ecos acumulables desde este punto hasta alcanzar `c1 + c2 == T`.

Transiciones desde `(c1, c2, k, m)`:
- El último carácter registrado fue `last = (m == 0) ? A[(c1 - 1) % N1] : B[(c2 - 1) % N2]`.
- **Opción 1 (Permanecer en `m`):** No gasta alternancias (`k` no cambia). Se suma `1` si el siguiente acto de `m` es idéntico a `last`.
- **Opción 2 (Cambiar a `1 - m`):** Solo permitida si `k + 1 <= K`. Incrementa `k` en 1 y se suma `1` si el siguiente acto de `1 - m` es idéntico a `last`.

Caso base: `if (c1 + c2 == T) return 0;`.
Llamada inicial: `solve(1, 0, 0, 0)`.

---

## 3. Trampas Cognitivas Recurrentes

1. **Estado Inicial Erróneo:**
   Asumir que se puede iniciar en cualquiera de los dos manuscritos. El enunciado impone: *"La Bruja del Drama comienza su lectura en el primer acto del primer manuscrito"*.
2. **Índices Circulares del Último vs Siguiente:**
   Confundir `(c1 - 1) % N1` (último elemento emitido) con `c1 % N1` (próximo elemento a evaluar).
3. **Manejo de Memoria (Bottom-Up Rolling):**
   Si `T` y `K` fueran mayores (ej. `T, K <= 500`), la tabla 4D consumiría demasiada memoria. Como la longitud total `t = c1 + c2` avanza estrictamente de 1 en 1, `c2` queda implícito (`c2 = t - c1`) y basta una técnica de *rolling array* con 2 capas (`dp` y `next_dp`), reduciendo el consumo a solo `~180 KB`.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(T^2 * K)`. Como `T <= 150` y `K <= 150`, la cantidad de estados alcanzables es `<= 150^2 * 150 / 2 ~ 1.7 * 10^6`, ejecutando en `< 0.05 s`.
- **Complejidad Espacial:** `O(T^2 * K)` en la versión Top-Down (`~27 MB`), dentro del límite de 128 MB; o `O(T * K)` en Bottom-Up (`~0.18 MB`).

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int K, T, N1, N2;
vector<string> A, B;
int memo[152][152][152][2];

int solve_dp(int c1, int c2, int k, int m) {
    if (c1 + c2 == T) return 0;
    if (memo[c1][c2][k][m] != -1) return memo[c1][c2][k][m];

    int best = 0;
    const string& last = (m == 0) ? A[(c1 - 1) % N1] : B[(c2 - 1) % N2];

    if (m == 0) {
        // Continuar en M1
        best = max(best, (A[c1 % N1] == last) + solve_dp(c1 + 1, c2, k, 0));
        // Cambiar a M2
        if (k + 1 <= K) {
            best = max(best, (B[c2 % N2] == last) + solve_dp(c1, c2 + 1, k + 1, 1));
        }
    } else {
        // Continuar en M2
        best = max(best, (B[c2 % N2] == last) + solve_dp(c1, c2 + 1, k, 1));
        // Cambiar a M1
        if (k + 1 <= K) {
            best = max(best, (A[c1 % N1] == last) + solve_dp(c1 + 1, c2, k + 1, 0));
        }
    }

    return memo[c1][c2][k][m] = best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> K >> T) {
        cin >> N1;
        A.resize(N1);
        for (int i = 0; i < N1; ++i) cin >> A[i];

        cin >> N2;
        B.resize(N2);
        for (int i = 0; i < N2; ++i) cin >> B[i];

        if (T == 1) {
            cout << 0 << "\n";
            continue;
        }

        memset(memo, -1, sizeof(memo));
        cout << solve_dp(1, 0, 0, 0) << "\n";
    }

    return 0;
}
```
