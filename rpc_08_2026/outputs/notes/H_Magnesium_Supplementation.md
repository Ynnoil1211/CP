# Problema H: Magnesium Supplementation

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Fácil-Media (Div 2B / Div 3C)
- **Estado en Concurso:** Resuelto (AC en versión 3 de C++)
- **Archivos de Referencia:**
  - Soluciones de Equipo: `inputs/solutions/Magnesium.py`, `Magnesium (1).py`, `Magnesium.cpp`, `Magnesium (1).cpp`, `Magnesium (2).cpp`, `Magnesium (3).cpp` (AC)
  - Solución Oficial: `inputs/official_solutions/H_Magnesium.py`

---

## 1. Lógica y Enfoque del Problema

Una persona debe consumir exactamente $N$ mg de magnesio en total.
Para lograrlo, debe tomar una dosis diaria constante de $D$ mg durante un número entero de días $T$. Por tanto:
$$N = D \times T \iff D \text{ es un divisor exacto de } N \quad (N \pmod D == 0)$$

Las restricciones del tratamiento imponen dos límites:
1. **Dosis máxima por pastilla ($K$):** La pastilla diaria no puede exceder $K$ mg $\implies D \le K$.
2. **Duración máxima del tratamiento ($P$):** El tratamiento no puede durar más de $P$ días $\implies T = \frac{N}{D} \le P$.

Se pide imprimir cuántos valores distintos de $D$ cumplen las condiciones y listarlos en orden estrictamente creciente.
Dado que $N \le 10^{12}$, los divisores de $N$ se encuentran en tiempo $O(\sqrt{N})$ iterando $i$ desde $1$ hasta $\lfloor\sqrt{N}\rfloor$. Para cada $i$ tal que $N \pmod i == 0$, se prueban los dos divisores conjugados $d_1 = i$ y $d_2 = \frac{N}{i}$.

---

## 2. Dónde Estuvo el Error en las Versiones Previas

El recorrido del equipo muestra tres fallos pedagógicamente valiosos:

1. **Versiones en Python (`Magnesium.py` y `(1).py`): TLE por bucle lineal:**
   ```python
   for c in range(1, limite + 1):  # limite = min(k, n)
   ```
   Con $K, N \le 10^{12}$, un bucle hasta $10^{12}$ es inviable en 1 segundo (se requieren $O(10^8)$ operaciones por segundo máximo). Provocó Time Limit Exceeded.

2. **Versiones C++ tempranas (`Magnesium.cpp` y `(1).cpp`): WA por lógica ad-hoc incompleta:**
   Intentaron iterar hacia atrás desde $\sqrt{N}$ aplicando cortes prematuros (`if (x/i > y) break;`) y parches condicionales (`if (x == z)...`), omitiendo divisores válidos.

3. **`Magnesium (2).cpp`: WA por Desbordamiento de Enteros (Integer Overflow):**
   ```cpp
   ll n, y, z; cin >> n >> y >> z;
   vi vt; // ERROR: vi = vector<int> (32 bits con signo: max 2 * 10^9)
   for (ll i = 1; i * i <= n; i++) {
       if (n % i == 0) {
           ll d2 = n / i;
           if (n / i <= z && i <= y) vt.push_back(i);
           if (d2 != i && n / d2 <= z && d2 <= y) vt.push_back(d2); // d2 hasta 10^12 desborda int!
       }
   }
   ```
   La lógica algorítmica era perfecta ($O(\sqrt{N})$), pero `vt` se declaró como `vector<int>`. Al insertar divisores mayores a $2 \times 10^9$, los números se truncaron a valores negativos o corruptos.

4. **`Magnesium (3).cpp` (AC):**
   Corrigió el contenedor a `vll vt;` (`vector<long long>`), logrando el Accepted inmediato.

---

## 3. Trampas Cognitivas Recurrentes

1. **La trampa del contenedor truncado (Alias Inconsistente):**  
   Declarar las variables de entrada como `long long` (`ll n, y, z;`), pero usar por inercia el typedef rápido `vi` (`vector<int>`) del template para almacenar las respuestas. Si las variables pueden ser $10^{12}$, sus divisores también pueden ser $10^{12}$.
2. **Confundir el tamaño de la respuesta con el tamaño del espacio de búsqueda:**  
   Al ver $K \le 10^{12}$, suponer que se puede iterar hasta $K$. La divisibilidad es una propiedad de $N$, no de $K$. El espacio de divisores de $N$ tiene a lo sumo $\approx 6\,720$ divisores para $N \le 10^{12}$, y solo requiere buscar hasta $\sqrt{N} \le 10^6$.

---

## 4. Comparativa: Equipo vs Oficial

- **Equipo (`Magnesium (3).cpp`):**
  Recorre $i$ hasta $\sqrt{N}$, agrega $i$ y $N/i$ si satisfacen las cotas de $K$ y $P$, ordena con `std::sort` e imprime.
- **Oficial (`H_Magnesium.py` - Arup Guha):**
  Aplica exactamente la misma búsqueda de factores en pares $(i, N//i)$ hasta $\sqrt{N}$ en Python:
  ```python
  i = 1
  while i * i <= n:
      if n % i == 0:
          factors.append(i)
          if i * i != n:
              factors.append(n // i)
      i += 1
  # luego filtra y ordena
  ```
- **Complejidad:** $O(\sqrt{N} + D(N) \log D(N))$ tiempo (donde $D(N) \le 6720$) y $O(D(N))$ espacio. Tiempo de ejecución $< 0.05$ s.
