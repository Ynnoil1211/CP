# Problema H: Humbertov y su taza de café

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Hugo Humberto Morales Peña (UTP Colombia)
- **Dificultad Estimada:** Fácil-Media (Div 3C / Div 2B)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [H_Humbertov_Y_Su_Taza_De_Cafe.cpp](../../inputs/solutions/H_Humbertov_Y_Su_Taza_De_Cafe.cpp)

---

## 1. Lógica y Enfoque del Problema

La taza de café del profesor Humbertov Moralov es un cono truncado con:
- Radio del fondo (base inferior): `r`.
- Radio de la boca (base superior): `R` (con `r <= R`).
- Altura total: `h`.

El profesor exige que el café ocupe exactamente el 50% del volumen total de la taza, llenándose desde el fondo hasta una altura `x`. Se debe determinar dicha altura `x` con un error absoluto o relativo menor a `10^-6`.

### Modelado Matemático y Búsqueda Binaria

1. **Fórmula del Cono Truncado:**
   Para un cono truncado de altura `H_c`, radio inferior `r_1` y radio superior `r_2`, el volumen es:
   `V = (1/3) * pi * H_c * (r_1^2 + r_2^2 + r_1 * r_2)`.

2. **Volumen a Altura `x`:**
   Al llenar la taza hasta altura `x` (`0 <= x <= h`), el radio superior alcanzado por el líquido es una interpolación lineal:
   `r_x = r + (R - r) * (x / h)`.
   El volumen acumulado de líquido a altura `x` es:
   `V(x) = (1/3) * pi * x * (r^2 + r_x^2 + r * r_x)`.

3. **Cancelación de Constantes y Monotonía:**
   Queremos resolver `V(x) = 0.5 * V(h)`.
   Como el factor `(1/3) * pi` aparece en ambos lados, se simplifica:
   `f(x) = x * (r^2 + r_x^2 + r * r_x)`.
   Buscamos `x` tal que `f(x) = 0.5 * f(h)`.
   Como `f(x)` es estrictamente creciente y continua en `[0, h]`, el problema se resuelve con **Búsqueda Binaria sobre Respuesta (BSTA)** en el intervalo `[0, h]`.

---

## 2. Análisis Diferencial y Puntos Críticos

En la solución del equipo [H_Humbertov_Y_Su_Taza_De_Cafe.cpp](../../inputs/solutions/H_Humbertov_Y_Su_Taza_De_Cafe.cpp):
- Se ejecutan exactamente 100 iteraciones de búsqueda binaria:
  Tras 100 iteraciones, el rango de incertidumbre se reduce en un factor de `2^{100} ~ 1.26 * 10^{30}`. Dado que `h <= 10.0`, el error absoluto final es inferior a `10^{-28}`, pulverizando el requerimiento de `10^-6`.
- Se imprime con `fixed` y `setprecision(9)`.

---

## 3. Trampa Cognitiva: *Variable Shadowing*

- **El peligro del sombreado de variables:**
  En la implementación del equipo:
  ```cpp
  double r, R, h; // Variables globales
  void solve() {
      cin >> r >> R >> h;
      double l = 0, r = h; // ¡Alerta! 'r' local sombrea al radio 'r' global
  ```
  La variable local `r` usada como cota superior de la búsqueda binaria ocultó el radio global `r`. Aunque funcionó fortuitamente porque `cin >> r` se ejecutó antes y la función `bs(mid)` leía el `r` global que ya tenía el valor correcto, este antipatrón es fuente frecuente de bugs indetectables durante las competencias. Es una buena práctica nombrar las cotas como `low` y `high`.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(100)` por caso de prueba. Para `t = 5 * 10^4`, son `~5 * 10^6` operaciones, ejecutando en `< 0.08 s` en C++ (límite: 1.0 s).
- **Complejidad Espacial:** `O(1)` de memoria auxiliar.

```cpp
#include <iostream>
#include <iomanip>

using namespace std;

double eval_volume(double x, double r_base, double R_top, double h_total) {
    double rx = r_base + (R_top - r_base) * (x / h_total);
    return x * (r_base * r_base + rx * rx + r_base * rx);
}

void solve() {
    double r_base, R_top, h_total;
    cin >> r_base >> R_top >> h_total;

    double target = eval_volume(h_total, r_base, R_top, h_total) / 2.0;

    double low = 0.0, high = h_total;
    for (int iter = 0; iter < 100; ++iter) {
        double mid = (low + high) / 2.0;
        if (eval_volume(mid, r_base, R_top, h_total) >= target) {
            high = mid;
        } else {
            low = mid;
        }
    }

    cout << fixed << setprecision(9) << low << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}
```
