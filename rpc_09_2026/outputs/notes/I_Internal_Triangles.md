# Problema I: Internal triangles

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Gabriel Gutiérrez Tamayo (UTP Colombia)
- **Dificultad Estimada:** Fácil (Div 3A / Div 2A)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [I_Internal_Triangles.cpp](../../inputs/solutions/I_Internal_Triangles.cpp)

---

## 1. Lógica y Enfoque del Problema

Dado un polígono regular convexo de `n` lados (`3 <= n <= 10^18`), se pide determinar cuántos triángulos distintos pueden formarse seleccionando 3 de sus vértices, imprimiendo el resultado módulo `10^9 + 7`.

### Combinatoria Inmediata

- Dado que el polígono es estrictamente convexo, ningún trío de vértices es colineal.
- Por tanto, **cualquier subconjunto de 3 vértices forma un triángulo válido y único**.
- El número total de triángulos es simplemente el coeficiente binomial:
  `C(n, 3) = n * (n - 1) * (n - 2) / 6`.

---

## 2. Aritmética Modular con Números Gigantes (`n <= 10^18`)

Como `n <= 10^18`, no podemos multiplicar `n * (n - 1) * (n - 2)` directamente antes de dividir por 6, pues `n^3` alcanzaría `10^{54}`, desbordando ampliamente los 64 bits de `long long`.

Existen dos estrategias válidas para computar `C(n, 3) mod (10^9 + 7)`:

1. **Inverso Modular de 6:**
   Dado que `MOD = 10^9 + 7` es primo y `gcd(6, MOD) = 1`, existe el inverso multiplicativo de 6:
   `6 * 166666668 = 1000000008 = 10^9 + 7 + 1 = 1 (mod 10^9 + 7)`.
   Por tanto:
   `ans = ((n % MOD) * ((n - 1) % MOD) % MOD * ((n - 2) % MOD) % MOD * 166666668) % MOD`.

2. **División Entera Previa (Propiedad de Enteros Consecutivos):**
   Entre tres enteros consecutivos `(n, n - 1, n - 2)`:
   - Al menos uno es par: se divide entre 2.
   - Exactamente uno es múltiplo de 3: se divide entre 3.
   Luego se aplican las reducciones `% MOD` a los tres factores simplificados antes de multiplicar.

---

## 3. Trampas Cognitivas Recurrentes

1. **Desbordamiento de 64 bits antes del módulo:**
   Intentar hacer `(n * (n - 1) * (n - 2) / 6) % MOD` en `long long`.
2. **Dividir después de aplicar módulo:**
   La división ordinaria no está definida en aritmética modular: `(A / 6) % MOD != (A % MOD) / 6`.
3. **I/O lenta con `q = 10^5`:**
   No incluir `ios_base::sync_with_stdio(false); cin.tie(NULL);` en un problema con `10^5` consultas.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(1)` por consulta, `O(q)` total (`~0.02 s` para `q = 10^5`).
- **Complejidad Espacial:** `O(1)` memoria auxiliar.

```cpp
#include <iostream>

using namespace std;

const long long MOD = 1000000007;
const long long INV6 = 166666668; // Inverso modular de 6 mod 10^9 + 7

void solve() {
    long long n;
    cin >> n;

    long long a = n % MOD;
    long long b = (n - 1) % MOD;
    long long c = (n - 2) % MOD;

    long long ans = (a * b) % MOD;
    ans = (ans * c) % MOD;
    ans = (ans * INV6) % MOD;

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    if (cin >> q) {
        while (q--) solve();
    }
    return 0;
}
```
