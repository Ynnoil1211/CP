# Problema A: Contest Advancement

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Fácil (Div 2A / Div 3B)
- **Estado en Concurso:** Resuelto (AC en versión 3)
- **Archivos de Referencia:**
  - Soluciones de Equipo: `inputs/solutions/Contest.cpp`, `Contest (1).cpp`, `Contest (2).cpp`, `Contest (3).cpp` (AC)
  - Solución Oficial: `inputs/official_solutions/A_Contest.cpp`

---

## 1. Lógica y Enfoque del Problema

Se tienen $N$ equipos ordenados estrictamente por su desempeño (rango 1 a $N$, sin empates). Se deben seleccionar exactamente $K$ equipos para clasificar a la siguiente ronda, respetando una cuota máxima de $C$ equipos por escuela. 
La regla de desempate/relleno estipula:
1. **Pase 1:** Se recorren los equipos en orden de mérito (ranking). Un equipo clasifica si su escuela aún no ha alcanzado el límite de $C$ clasificados.
2. **Pase 2 (si no se completan $K$):** Si tras revisar todos los equipos clasifican menos de $K$, se rellena el cupo restante con los mejores equipos no clasificados de la lista general, ignorando el límite $C$, hasta completar exactamente $K$.
3. **Requisito de Salida:** Los $K$ clasificados deben imprimirse **en el orden de su ranking original**, no en el orden en que fueron seleccionados por los pases.

---

## 2. Dónde Estuvo el Error en las Versiones Previas

Analizando el historial de envíos del equipo:
- **`Contest.cpp` (v0):** 
  - *Falla:* Solo implementó el Pase 1 (`mp[s] <= c`). Si la cuota por escuela dejaba fuera a suficientes equipos y no se alcanzaban $K$, el programa terminaba sin ejecutar el Pase 2.
- **`Contest (1).cpp`:**
  - *Falla:* Añadió el Pase 2, pero imprimía en vivo durante el Pase 1 (`cout << t << endl;`). Si se requería el Pase 2, los equipos del Pase 2 se imprimían al final, alterando el orden de mérito relativo (por ejemplo, el 4to equipo general del Pase 2 salía después del 8vo equipo del Pase 1). Además, tenía un `if(cnt==b) return;` que detenía la lectura anticipadamente.
- **`Contest (2).cpp`:**
  - *Avance:* Corrigió la salida: guardó los IDs clasificados en un conjunto (`st`) y luego hizo una pasada final imprimiendo solo los elementos de `st` en orden original. Tuvo un detalle menor de control de flujo.
- **`Contest (3).cpp` (AC):**
  - *Solución:* Recolecta candidatos con cupo, rellena los restantes si faltan cupos, y finalmente imprime en el orden de ranking preservado.

---

## 3. Trampa Cognitiva Recurrente

1. **La falacia de la "impresión codiciosa en línea":**  
   Al resolver problemas de filtrado con dos fases (filtro con restricción + descarte de restricción), la mente tiende a imprimir inmediatamente conforme un elemento cumple el filtro inicial. Esto destruye el orden global cuando el criterio secundario rescata elementos que estaban arriba en la tabla de posiciones.
2. **Ignorar la cláusula de contingencia del enunciado:**  
   Asumir erróneamente que siempre habrá suficientes escuelas distintas para llenar los $K$ cupos bajo la restricción $C$.

---

## 4. Comparativa: Equipo vs Oficial

- **Equipo (`Contest (3).cpp`):**
  Usa `unordered_map<int, int>` para contar escuelas y `unordered_set<int>` para registrar a los $K$ clasificados; luego itera sobre el vector original para imprimir en orden. Complejidad: $O(N)$ tiempo, $O(N)$ memoria.
- **Oficial (`A_Contest.cpp` - Arup Guha):**
  Usa dos vectores (`res` para los aceptados en Pase 1 y `leftover` para los descartados por cupo escolar). Si `res.size() < k`, toma los primeros `k - res.size()` elementos de `leftover`. Luego, cada equipo tiene un campo `origRank` y se ordena la lista final de $K$ equipos por `origRank` usando `sort`. Ambos enfoques logran $O(N \log K)$ o $O(N)$ y son conceptualmente equivalentes.
