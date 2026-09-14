# Problema E: ICPC Team Generation

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Fácil-Media (Div 2B / Div 3C)
- **Estado en Concurso:** Resuelto en primer intento (AC directo)
- **Archivos de Referencia:**
  - Solución de Equipo: `inputs/solutions/Team.cpp` (AC)
  - Solución Oficial: `inputs/official_solutions/E_Team.cpp`

---

## 1. Lógica y Enfoque del Problema

Se tienen N competidores ordenados por rango (1 a N). Cada competidor en rango r tiene un intervalo [a_r, b_r] tal que solo acepta formar equipo con competidores cuyo rango esté dentro de dicho intervalo (a_r <= r <= b_r). Cada equipo debe tener exactamente 3 integrantes.
La restricción dorada del enunciado es:
Para todo i < j => a_i <= a_j y b_i <= b_j
Esto establece una **monotonía estricta de preferencias**.

Gracias a esta monotonía:
1. Si un equipo se forma con 3 personas, la elección óptima siempre es agrupar a **3 competidores consecutivos** en el ranking: {i, i+1, i+2}. Separar competidores o tomar saltos solo estrecha las restricciones de compatibilidad.
2. Para que el trío consecutivo {i, i+1, i+2} sea mutuamente compatible, basta con que el competidor más a la izquierda acepte al de más a la derecha (b_i >= i+2) y el competidor más a la derecha acepte al de más a la izquierda (a_{i+2} <= i). Las condiciones de i+1 quedan automáticamente satisfechas por la transitividad monótona (a_{i+1} <= a_{i+2} <= i y b_{i+1} >= b_i >= i+2).
3. La estrategia óptima es puramente **codiciosa (greedy)** de izquierda a derecha: si {i, i+1, i+2} pueden formar equipo, se forma el equipo y se avanza el puntero a i+3; de lo contrario, se descarta a i y se avanza a i+1.

---

## 2. Dónde Estuvo el Error en Versiones Previas

- **El equipo obtuvo AC directo:** No hubo intentos erróneos.
- Sin embargo, un error común en este tipo de problemas radica en avanzar el índice incorrectamente: al formar un equipo de 3, el puntero debe avanzar 3 posiciones (en `Team.cpp`: `p += 2;` seguido del `p++;` al final del bucle, sumando +3). Un desliz en la aritmética de saltos provoca sobrelapamiento de equipos (usar el mismo integrante dos veces) o saltarse candidatos viables.

---

## 3. Trampa Cognitiva Recurrente

1. **Sobrecomplejidad innecesaria (buscar flujo máximo o DP cuadrática):**  
   Al ver formación de equipos con restricciones de compatibilidad y rangos, es común pensar en emparejamientos en grafos bipartitos, flujos de costo mínimo o programación dinámica O(N^2).
2. **Ignorar la propiedad de orden monótono (a_i <= a_j y b_i <= b_j):**  
   Esta pequeña frase en el enunciado transforma un problema NP-duro (partición en triángulos / 3-dimensional matching) en un barrido lineal O(N) trivial. Quien no lee la propiedad intenta comprobar emparejamientos arbitrarios no contiguos.

---

## 4. Comparativa: Equipo vs Oficial

- **Equipo (`Team.cpp`):**  
  Aprovecha elegantemente la propiedad matemática:
  ```cpp
  if (people[p].second >= p + 2 && people[p + 2].first <= p) {
      count++;
      p += 2;
  }
  p++;
  ```
  Solo evalúa los extremos p y p+2.
- **Oficial (`E_Team.cpp` - Arup Guha):**  
  Implementa una función auxiliar `canDo(idx)` que verifica explícitamente los 3 integrantes con un bucle `for (int i = idx; i < idx + 3; i++)`. Aunque hace más comprobaciones, la lógica de reemplazo e inducción greedy es exactamente idéntica.
- **Complejidad:** Ambos logran O(N) en tiempo y O(N) en espacio con N <= 50.