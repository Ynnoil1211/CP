# Problema L: Water Journal

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Muy Fácil (Div 3A / Div 2A)
- **Estado en Concurso:** Resuelto (AC en versión 2)
- **Archivos de Referencia:**
  - Soluciones de Equipo: `inputs/solutions/Water.cpp`, `Water (1).cpp`, `Water (2).cpp` (AC)
  - Solución Oficial: `inputs/official_solutions/L_Water.py`

---

## 1. Lógica y Enfoque del Problema

Eugene registró durante n días su consumo de agua, pero olvidó anotar exactamente **un día** (tenemos n-1 registros). Recuerda con certeza que el mínimo de todo el periodo fue a y el máximo fue b, y que hubo al menos un día con consumo a y al menos un día con consumo b.
Se solicita imprimir todos los posibles valores que pudo haber bebido el día faltante (en orden creciente), o imprimir `-1` si los recuerdos de Eugene son contradictorios/imposibles.

### Análisis por Principio del Palomar
Revisamos los n-1 registros disponibles y verificamos dos banderas booleanas:
- tiene_min: ¿aparece al menos una vez el valor a?
- tiene_max: ¿aparece al menos una vez el valor b?

Se presentan cuatro casos mutuamente excluyentes:
1. **Ambos están presentes (tiene_min AND tiene_max):**  
   Como el mínimo y el máximo ya fueron alcanzados en otros días, el día faltante puede tomar **cualquier valor entero en el intervalo cerrado [a, b]**. Se imprimen todos los enteros desde a hasta b.
2. **Falta solo el máximo (tiene_min AND NOT tiene_max):**  
   El único día faltante está obligado a ser el máximo. La única respuesta es b.
3. **Falta solo el mínimo (NOT tiene_min AND tiene_max):**  
   El día faltante está obligado a ser el mínimo. La única respuesta es a.
4. **Faltan ambos (NOT tiene_min AND NOT tiene_max):**  
   - Si a == b, un solo número cubre ambos roles (imprimir a).
   - Si a != b, harían falta al menos **dos días distintos** para cubrir a y b. Como solo se olvidó **un día**, es matemáticamente imposible. Se imprime `-1`.

---

## 2. Dónde Estuvo el Error en las Versiones Previas

1. **`Water.cpp` (v0): Omisión del caso donde faltan ambos extremos (WA):**
   ```cpp
   if (nums.contains(a)) {
       if (nums.contains(b)) { ... }
       else cout << b;
   }
   else cout << a; // ERROR CRÍTICO
   ```
   Si el conjunto no contenía a, el código asumía ciegamente que contenía b, imprimiendo a. En un caso de prueba donde ni a ni b aparecían en el registro (con a != b), el programa debió responder `-1`, pero imprimió a.

2. **`Water (1).cpp`: Detección de `-1` añadida, pero formato con espacio final:**
   Corrigió la ramificación añadiendo `else if (nums.contains(b)) cout << a; else cout << -1;`.

3. **`Water (2).cpp` (AC):**
   Ajustó el formateo de la lista de enteros para evitar espacios finales redundantes (`fore(i, a, b-1) cout << i << " "; cout << b;`), logrando Accepted.

---

## 3. Trampa Cognitiva Recurrente

1. **La falacia del "complemento binario" en condicionales:**  
   Pensar que si la condición A no se cumple (NOT tiene_min), automáticamente la condición B sí se cumple (tiene_max). Cuando hay dos variables booleanas independientes, existen 4 estados (2 * 2), no 2.
2. **Olvidar el Principio del Palomar con recursos únicos:**  
   Si hay k restricciones no satisfechas y solo 1 grado de libertad (1 valor faltante), es imposible satisfacer k > 1 restricciones disjuntas simultáneamente.

---

## 4. Comparativa: Equipo vs Oficial

- **Equipo (`Water (2).cpp`):**  
  Almacena los números leídos en un `std::set` y evalúa `nums.contains(a)` y `nums.contains(b)`.
- **Oficial (`L_Water.py` - Arup Guha):**  
  ```python
  haveMin = (low in vals)
  haveMax = (high in vals)

  if not haveMin and not haveMax:
      print(-1)
  elif haveMin and haveMax:
      print(*(range(low, high + 1)))
  elif not haveMin:
      print(low)
  else:
      print(high)
  ```
  La solución oficial maneja la comprobación de `-1` en primer lugar, protegiendo el flujo contra inconsistencias de forma muy limpia.
- **Complejidad:** O(N) tiempo y O(N) espacio en ambas soluciones (con N <= 50).