# Problema C: Don't Hunger Together

- **Concurso:** RPC 08 (Septiembre 2026) / NAQ 2023-2024
- **Dificultad Estimada:** Media-Alta (Div 1B / Div 2E)
- **Estado en Concurso:** No resuelto
- **Archivos de Referencia:**
  - Enunciado: [ProblemsetRPC08.pdf](../../inputs/problemset/ProblemsetRPC08.pdf)
  - Solución Oficial: [C_Hunger.cpp](../../inputs/official_solutions/C_Hunger.cpp)

---

## 1. Explicación Pedagógica del Problema

En el juego de supervivencia *Don't Hunger Together*, K jugadores deben sobrevivir durante N turnos consecutivos. Cada turno consta de dos fases:
1. **Día i:** Se recolecta hasta una cantidad q_i de comida. Esta comida tiene una fecha de caducidad estricta: solo puede consumirse hasta la noche del turno f_i (i <= f_i <= N). Al pasar la noche f_i, cualquier porción restante se pudre.
2. **Noche i:** Cada uno de los K jugadores debe consumir exactamente una cantidad x de alimento. Si en cualquier noche algún jugador no recibe su ración completa x, todos pierden. Por lo tanto, el grupo necesita consumir en total F = K * x unidades de comida cada noche.

**Objetivo:** Encontrar el valor máximo real x > 0 de comida diaria por jugador para el cual es posible sobrevivir las N noches. Si no es posible sobrevivir para ningún x > 0, reportar `-1`. La respuesta requiere precisión de 10^-9.

---

## 2. Patrones Evidentes y Pistas en las Restricciones

- **Monotonía de la Solución (Predicado Monótono):**  
  Si el grupo puede sobrevivir consumiendo una ración x diaria por persona, trivialmente puede sobrevivir consumiendo cualquier cantidad menor x' < x (basta con desechar el excedente o comer menos).  
  Esta propiedad monótona es la señal inequívoca para **Búsqueda Binaria sobre la Respuesta (Binary Search on Answer / BSTA)** en el espacio continuo [0, total_food / K].
- **Restricción de Caducidad (Intervalos de Validez [i, f_i]):**  
  El recurso obtenido en el día i solo vive hasta la noche f_i. Esto es un problema clásico de planificación de recursos con fechas límite (*deadline scheduling*).
- **Estrategia Codiciosa (Greedy - Earliest Deadline First):**  
  Para satisfacer la cuota de la noche i, ¿qué paquete de comida disponible conviene consumir primero?  
  Siempre conviene consumir la comida cuya fecha de expiración f sea la más cercana (más urgente). La comida que vence más tarde tiene mayor flexibilidad para rescatarnos en noches futuras.
- **N <= 10^6:**  
  La verificación de factibilidad de una cuota x debe realizarse en O(N) o O(N log N) mediante una cola de prioridad (min-heap).

---

## 3. Técnica Algorítmica: BSTA + Greedy con Priority Queue (EDF)

### Función de Verificación: `canDo(F)`
Dada una demanda total requerida por noche F = K * x:
1. Mantenemos una cola de prioridad con pares (vencimiento, cantidad_disponible).
2. Para cada día i = 0, 1, ..., N-1:
   - Insertamos el alimento recolectado hoy: (f_i, q_i) si q_i > 0.
   - Necesitamos cubrir una demanda restante today = F.
   - Mientras today > 0 y la cola no esté vacía:
     - Extraemos el elemento con menor fecha de vencimiento.
     - Si ya venció (vencimiento < i), lo descartamos sin usarlo.
     - Si su cantidad <= today, lo consumimos por completo, restamos su cantidad a today y lo retiramos del heap.
     - Si su cantidad > today, consumimos la fracción today, actualizamos su cantidad remanente y lo volvemos a insertar en el heap con today = 0.
   - Si al finalizar el intento de consumo today > 10^-9, significa que no hubo comida suficiente para la noche i: retornamos `false`.
3. Si superamos las N noches sin hambruna, retornamos `true`.

---

## 4. Estrategia de Implementación y Código de Referencia

La solución oficial ([C_Hunger.cpp](../../inputs/official_solutions/C_Hunger.cpp)) implementa 150 iteraciones de bisección. Con 150 pasos, el intervalo se reduce por 2^150 ≈ 10^45, superando con holgura la precisión requerida (10^-9).

```cpp
// Búsqueda binaria sobre mid = ración por jugador
double low = 0, high = totalf / numP;
for (int iter = 0; iter < 100; iter++) { // 100 iteraciones bastan para 1e-15
    double mid = (low + high) / 2.0;
    if (canDo(food, endday, mid * numP))
        low = mid;
    else
        high = mid;
}

if (low > 1e-9)
    cout << fixed << setprecision(10) << low << endl;
else
    cout << -1 << endl;
```

### Verificación `canDo`:
```cpp
bool canDo(const vector<ll>& food, const vector<int>& endday, double F) {
    int n = food.size();
    // Min-heap ordenado por menor día de vencimiento
    priority_queue<pair<int, double>, vector<pair<int, double>>, greater<pair<int, double>>> pq;
    
    for (int i = 0; i < n; i++) {
        if (food[i] > 0) pq.push({endday[i] - 1, (double)food[i]});
        double today = F;
        
        while (!pq.empty() && today > 1e-10) {
            auto [exp, qty] = pq.top();
            pq.pop();
            if (exp < i) continue; // comida podrida
            
            if (today >= qty) {
                today -= qty;
            } else {
                pq.push({exp, qty - today});
                today = 0;
            }
        }
        if (today > 1e-9) return false;
    }
    return true;
}
```

### Complejidad
- **Tiempo:** En cada llamada a `canDo`, cada porción de comida entra y sale de la cola de prioridad a lo sumo una vez por día, resultando en O(N log N).  
  Con I ≈ 80 iteraciones de bisección: O(I * N log N). Para N = 10^6, en C++ con I/O optimizada corre holgadamente en el límite de tiempo de 3.0s.
- **Espacio:** O(N) para almacenar el arreglo de alimentos y el heap.