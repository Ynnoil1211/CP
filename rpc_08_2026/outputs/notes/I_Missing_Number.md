# Problema I: Missing Number

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Media (Div 2C / Div 3D)
- **Estado en Concurso:** No resuelto
- **Archivos de Referencia:**
  - Solución Oficial: `inputs/official_solutions/I_Missing.cpp`

---

## 1. Explicación Pedagógica del Problema

Kirby escribió todos los enteros consecutivos desde un valor inicial a hasta un valor final b (1 <= a < b <= 99999), concatenados uno tras otro en una única cadena de dígitos continua (sin espacios ni ceros a la izquierda):
"a(a+1)(a+2)... b"
Luego, Kirby se comió exactamente **uno** de los números escritos.
Se nos entrega la cadena resultante. Nuestro objetivo es reconstruir qué número o números pudo haberse comido Kirby.
Debemos reportar la cantidad de números posibles y listarlos en orden ascendente.

### Ejemplo
Si la entrada es `"891112"`:
- Si comenzó en 8: la secuencia esperada sería 8, 9, 10, 11, 12. Vemos '8', '9', falta el '10', y luego continúan '11', '12'. Kirby se comió el **10**.
- Es la única interpretación válida, por lo que la respuesta es `1` posibilidad: `10`.

---

## 2. Patrones Evidentes y Pistas en las Restricciones

- **Cota del número inicial (1 <= a < b <= 99999):**  
  ¡Esta es la clave fundamental del problema! Cualquier número en el rango tiene a lo sumo 5 dígitos (1 <= dígitos(a) <= 5).  
  Por ende, el primer número de la secuencia a está formado obligatoriamente por los primeros L caracteres de la cadena, donde L in {1, 2, 3, 4, 5}.
- **Determinismo Absoluto tras Fijar a:**  
  Una vez fijada la longitud L del primer número, el valor inicial a queda determinado unívocamente. A partir de ahí, **no hay bifurcaciones**:
  - El siguiente número *debe* ser a+1 (o a+2 si Kirby se comió a+1).
  - La cantidad de dígitos del siguiente número esperado es puramente aritmética (`floor(log10(x)) + 1`).
- **Suma de longitudes sum |S| <= 10^6:**  
  Probar las 5 posibles longitudes iniciales para la cadena toma 5 * O(|S|) = O(|S|) operaciones. Esto garantiza una ejecución casi instantánea.

---

## 3. Técnica Algorítmica: Búsqueda Exhaustiva sobre Prefijo (L in [1, 5]) + Simulación Determinista

Para cada posible longitud inicial L in {1, 2, 3, 4, 5} tal que L <= |S|:
1. Extraer a = stoi(S[0 ... L-1]). Si a >= 100000, descartar.
2. Mantener:
   - cur = a (último número procesado).
   - skip = -1 (número comido detectado).
   - idx = L (puntero actual en la cadena S).
3. Mientras idx < |S|:
   - Sea next = cur + 1 y d = longitud_dígitos(next).
   - **Caso 1 (Coincidencia consecutiva):** Si los siguientes d dígitos en S son iguales a next:
     Avanzar idx += d, actualizar cur = next.
   - **Caso 2 (Kirby comió next):** Si no coincide con next, pero los siguientes dígitos coinciden con next + 1:
     - Si ya habíamos saltado un número antes (skip != -1), esta hipótesis es inválida (Kirby solo come un número). Abortar.
     - Registrar skip = next, avanzar idx += longitud(next+1), actualizar cur = next + 1.
   - **Caso 3 (Transición de cambio de número de dígitos al saltar):**  
     Si next tiene d dígitos pero next+1 tiene d+1 dígitos (ej. next=9 -> next+1=10), verificar si en S aparecen los d+1 dígitos de next+1.
   - **Cualquier otro caso:** La hipótesis L es inválida. Abortar.
4. Si la cadena se consumió perfectamente (idx == |S|):
   - **Si hubo un salto (skip != -1):** El único número comido fue skip.
   - **Si no hubo ningún salto en el interior (skip == -1):** Kirby pudo haberse comido el número justo antes de empezar (a - 1, válido si a > 1) o el número inmediatamente posterior al final (cur + 1, válido si cur + 1 <= 99999).
5. Unir los resultados de todas las longitudes válidas L in [1, 5], eliminar duplicados y ordenar.

---

## 4. Estrategia de Implementación y Código de Referencia

La solución oficial (`inputs/official_solutions/I_Missing.cpp`) estructura el proceso mediante una función `solve(s, len)`:

```cpp
for (int len = 1; len <= 5; len++) {
    vector<int> tmp = solve(s, len);
    for (int x : tmp) res.push_back(x);
}
sort(res.begin(), res.end());
res.erase(unique(res.begin(), res.end()), res.end());
```

Dentro de `solve(string s, int len)`:
- Valida si `idx + nextlen <= s.size()`.
- Compara `newn == next` o `newn == next + 1`.
- Al finalizar sin saltos, maneja los extremos con precisión:
  ```cpp
  if (skip != -1) {
      res.push_back(skip);
  } else {
      if (cur + 1 < 100000) res.push_back(cur + 1);
      if (start > 1) res.push_back(start - 1);
  }
  ```

### Complejidad
- **Tiempo:** sum_{T} 5 * |S| = O(sum |S|) <= 10^6 operaciones. Tiempo de ejecución < 0.08 s en C++.
- **Espacio:** O(|S|) para almacenar la cadena de entrada.