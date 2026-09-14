# Problema B: Digit Translation

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Media (Div 2C / Div 1A)
- **Estado en Concurso:** No resuelto
- **Archivos de Referencia:**
  - Solución Oficial: `inputs/official_solutions/B_DigitTranslation.java`

---

## 1. Explicación Pedagógica del Problema

Se recibe una cadena de texto $S$ de caracteres en minúscula con longitud hasta $10^6$.
Existe un conjunto fijo de 10 palabras que representan dígitos en inglés:
$$\mathcal{D} = \{\text{"zero"}, \text{"one"}, \text{"two"}, \text{"three"}, \text{"four"}, \text{"five"}, \text{"six"}, \text{"seven"}, \text{"eight"}, \text{"nine"}\}$$

En cualquier momento, si una subcadena coincide exactamente con alguna palabra $w \in \mathcal{D}$, podemos reemplazar esa subcadena por su correspondiente dígito numérico `'0'`–`'9'`.
El problema exige dos respuestas:
1. **Longitud Mínima:** La menor longitud posible que puede tener la cadena final tras aplicar cero o más reemplazos válidos.
2. **Cantidad de Cadenas Distintas:** El número de cadenas distintas (secuencias de caracteres resultantes) que alcanzan esa longitud mínima óptima, calculado módulo $9\,302\,023$.

### Análisis de Ambigüedad y Solapamiento
Las palabras de dígitos pueden solaparse. Un ejemplo crucial es `"twone"`.
- Reemplazar `"two"` produce `"2ne"` (longitud 3).
- Reemplazar `"one"` produce `"tw1"` (longitud 3).
Ambas opciones alcanzan la longitud mínima (3), pero generan **cadenas distintas** (`"2ne"` y `"tw1"`). Por tanto, la respuesta para `"twone"` es longitud 3 y 2 cadenas distintas.

---

## 2. Patrones Evidentes y Pistas en las Restricciones

- **Longitud $|S| \le 10^6$:**  
  La cota de $10^6$ descarta cualquier búsqueda con retroceso (backtracking) exponencial o algoritmos de orden cuadrático $O(N^2)$. La solución debe ser estrictamente lineal $O(N)$ o cuasi-lineal $O(N \log N)$.
- **Tamaño de las palabras clave ($3 \le |w| \le 5$):**  
  Las palabras en $\mathcal{D}$ tienen longitudes diminutas:
  - Longitud 3: `"one"`, `"two"`, `"six"`
  - Longitud 4: `"zero"`, `"four"`, `"five"`, `"nine"`
  - Longitud 5: `"three"`, `"seven"`, `"eight"`
  Dado que la longitud máxima de una palabra de dígito es solo 5, al procesar el prefijo $S[0 \dots i-1]$, únicamente necesitamos mirar hacia atrás entre 3 y 5 caracteres.
- **Estructura de Subproblemas Superpuestos:**  
  La decisión en la posición $i$ solo depende del resultado óptimo acumulado en los prefijos $i-1$, $i-3$, $i-4$ e $i-5$. Esto grita **Programación Dinámica Lineal 1D**.

---

## 3. Técnica Algorítmica: Programación Dinámica Lineal Simultánea (Minimización + Conteo)

Definimos dos arreglos DP para cada prefijo de longitud $i \in [0, N]$:
- $\text{dp\_len}[i]$: Longitud mínima alcanzable para transformar el prefijo $S[0 \dots i-1]$.
- $\text{dp\_cnt}[i]$: Número de cadenas resultantes distintas de longitud $\text{dp\_len}[i]$, módulo $9\,302\,023$.

### Casos Base
- $\text{dp\_len}[0] = 0$ (cadena vacía tiene longitud 0).
- $\text{dp\_cnt}[0] = 1$ (solo existe la cadena vacía).

### Transiciones
Para la posición $i$ (representando el prefijo de longitud $i$, con índice $i-1$ en 0-based):

1. **Opción por defecto (no reemplazar el carácter actual $S[i-1]$):**
   - Longitud candidata: $L = \text{dp\_len}[i-1] + 1$
   - Formas candidatas: $C = \text{dp\_cnt}[i-1]$
   - Inicializamos $\text{bestLen} = L$ y $\text{bestCnt} = C$.

2. **Opciones de reemplazo (emparejar un sufijo con $w \in \mathcal{D}$):**
   Para cada palabra $w \in \mathcal{D}$ con longitud $m = |w|$ tal que $m \le i$:
   - Si el sufijo $S[i-m \dots i-1] == w$:
     El reemplazo de $w$ por un solo dígito toma 1 carácter.
     - Longitud candidata: $L_{\text{alt}} = \text{dp\_len}[i-m] + 1$.
     - Formas asociadas: $C_{\text{alt}} = \text{dp\_cnt}[i-m]$.
   - Evaluamos:
     - **Si $L_{\text{alt}} < \text{bestLen}$:** Se descubrió una longitud estrictamente más corta.
       $$\text{bestLen} = L_{\text{alt}}, \quad \text{bestCnt} = C_{\text{alt}}$$
     - **Si $L_{\text{alt}} == \text{bestLen}$:** Se llega a la misma longitud mínima por un camino estructuralmente distinto.
       $$\text{bestCnt} = (\text{bestCnt} + C_{\text{alt}}) \pmod{9\,302\,023}$$

3. **Asignación final:**
   $$\text{dp\_len}[i] = \text{bestLen}, \quad \text{dp\_cnt}[i] = \text{bestCnt}$$

---

## 4. Estrategia de Implementación y Código de Referencia

La solución oficial de Arup Guha (`inputs/official_solutions/B_DigitTranslation.java`) implementa exactamente este esquema en Java con `BufferedReader`.

```java
// Arreglos DP
int[] dplen = new int[n+1];
int[] dpcnt = new int[n+1];
dplen[0] = 0;
dpcnt[0] = 1;

for (int i = 0; i < n; i++) {
    int bestLen = dplen[i] + 1;
    int bestCnt = dpcnt[i];
    
    for (String num : NUMS) {
        int nLen = num.length();
        if (nLen > i + 1) continue;
        if (!match(num, s, i - nLen + 1)) continue;
        
        int altLen = dplen[i - nLen + 1] + 1;
        if (altLen < bestLen) {
            bestLen = altLen;
            bestCnt = dpcnt[i - nLen + 1];
        } else if (altLen == bestLen) {
            bestCnt = (bestCnt + dpcnt[i - nLen + 1]) % MOD;
        }
    }
    dplen[i+1] = bestLen;
    dpcnt[i+1] = bestCnt;
}
```

### Complejidad
- **Tiempo:** $O(N \times |\mathcal{D}| \times \max|w|) = O(10 \times 5 \times N) = O(N)$.  
  Para $N = 10^6$, toma $\approx 5 \times 10^7$ operaciones elementales, ejecutándose en menos de $0.2$ segundos en C++ o Java.
- **Espacio:** $O(N)$ para los arreglos DP, o incluso $O(1)$ optimizado mediante una ventana deslizante de tamaño 6.
