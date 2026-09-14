# Problema G: Lines Per Hour

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Muy Fácil (Div 3A / Div 2A)
- **Estado en Concurso:** Resuelto (AC en versión 2)
- **Archivos de Referencia:**
  - Soluciones de Equipo: `inputs/solutions/Lines.cpp`, `Lines (1).cpp`, `Lines (2).cpp` (AC)
  - Solución Oficial: `inputs/official_solutions/G_Lines.py`

---

## 1. Lógica y Enfoque del Problema

Un equipo de programación compite durante 5 horas. Su velocidad de codificación combinada es de P líneas de código por hora. Por lo tanto, durante todo el concurso pueden escribir a lo sumo:
Capacidad Máxima = 5 * P líneas de código

Hay N problemas disponibles, donde el problema i requiere L_i líneas de código para ser resuelto.
Para maximizar el número total de problemas resueltos, aplicamos una estrategia codiciosa (**Greedy**):
1. Ordenar el arreglo de líneas requeridas L en orden ascendente: L_1 <= L_2 <= ... <= L_N.
2. Tomar problemas en ese orden acumulando su costo mientras la suma acumulada no exceda 5 * P.
3. El número de problemas incluidos antes de exceder el límite es la respuesta óptima.

---

## 2. Dónde Estuvo el Error en las Versiones Previas

El historial de versiones revela dos errores clásicos de implementación:
1. **`Lines.cpp` (v0): Constante fija del ejemplo (Hardcoding accidental):**
   ```cpp
   // ERROR: 500 estaba cableado en el código
   if (sum > 500) {
       return i;
   }
   ```
   En el primer ejemplo de prueba, P = 100, por lo que 5 * P = 500. El programador probó con el ejemplo y dejó el literal numérico `500` quemado en vez de `5 * b`.
2. **`Lines (1).cpp`: Caso borde sin retorno (Missing return / Fall-through):**
   ```cpp
   forn(i, a) {
       sum += lines[i];
       if (sum > 5 * b) return i;
   }
   // ERROR: Si todos los problemas entran en el tiempo, 
   // el bucle termina y la función no retorna nada (Undefined Behavior).
   ```
   Si la suma de todos los problemas es menor o igual a 5 * P, el bucle terminaba sin ejecutar ningún `return`. En C++, esto produce comportamiento indefinido o imprime valores basura.
3. **`Lines (2).cpp` (AC):**
   Agregó `return a;` después del bucle, obteniendo Accepted.

---

## 3. Trampa Cognitiva Recurrente

1. **El "Síndrome del Ejemplo Quemado":**  
   Durante el fragor del concurso y la prisa por sacar problemas iniciales, calcular mentalmente el resultado del ejemplo (5 * 100 = 500) y escribir directamente el número en el código en lugar de la expresión paramétrica (5 * P).
2. **Olvidar el caso extremo de "capacidad sobrante":**  
   Pensar únicamente en la condición de corte (`sum > límite`) y no prever el escenario donde la condición de corte nunca se activa porque todos los elementos son procesables. Toda función con retorno en C++ que busca un corte debe tener un valor por defecto garantizado al final.

---

## 4. Comparativa: Equipo vs Oficial

- **Equipo (`Lines (2).cpp`):**
  Lee N, P, ordena con `sort(lines.begin(), lines.end())`, itera sumando y retorna `i` si excede 5P, o N si no excede.
- **Oficial (`G_Lines.py` - Arup Guha):**
  ```python
  n, p = map(int, input().split())
  lines = [int(input()) for _ in range(n)]
  lines.sort()
  total, res = 0, 0
  for x in lines:
      if total + x <= 5 * p:
          total += x
          res += 1
      else:
          break
  print(res)
  ```
  La versión oficial acumula con un contador explícito `res`, lo que previene por diseño el error de terminación del bucle.
- **Complejidad:** O(N log N) por el ordenamiento en ambas soluciones.