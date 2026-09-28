# Problema B: Betito el viajero

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Jorge Humberto Teran Pomier (UMSA Bolivia)
- **Dificultad Estimada:** Fácil (Div 3A / Div 2A)
- **Estado en Concurso:** Resuelto en Vivo (AC)
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [B_Betito_El_Viajero.cpp](../../inputs/solutions/B_Betito_El_Viajero.cpp)

---

## 1. Lógica y Enfoque del Problema

Se proporciona un mapa bidimensional de `R` filas y `C` columnas representando el país *Matrizlandia*:
- Celdas transitables marcadas con punto `'.'`.
- Obstáculos/paredes marcadas con numeral `'#'`.
- Punto de inicio de Betito marcado con un asterisco `'*'`.
- Movimientos permitidos: 4 direcciones ortogonales (arriba, abajo, izquierda, derecha).

Se solicita calcular el total de celdas accesibles por Betito partiendo desde `'*'` (incluyendo la casilla inicial). La entrada consta de múltiples casos de prueba finalizados por `0 0`.

Se trata de un problema estándar de conectividad en grafos reticulares (**Flood Fill / Componente Conexa**).

---

## 2. Análisis Diferencial y Puntos Críticos

En la solución del equipo [B_Betito_El_Viajero.cpp](../../inputs/solutions/B_Betito_El_Viajero.cpp):
- Se localiza la posición inicial `(bx, by)` durante la lectura de la matriz.
- Se ejecuta un recorrido en profundidad (DFS) recursivo mutando las celdas visitadas a `'#'` para evitar repeticiones:
  `vt[bx][by] = '#';`
- La recursión retorna `1 + suma_de_vecinos`.
- El bucle principal lee casos hasta encontrar `fi == 0 && cl == 0`.

---

## 3. Trampa Cognitiva Crítica: Riesgo de Desbordamiento de Pila (*Stack Overflow*)

1. **La trampa del DFS recursivo en matrices de 1000 x 1000:**
   Aunque el código del equipo fue aceptado gracias a que los casos de prueba oficiales no contenían laberintos lineales patológicos (como serpientes o espirales de longitud `10^6`), **usar DFS recursivo en retículas de 1000 x 1000 es un riesgo mortal**.
   - En una retícula con `R, C <= 1000`, la profundidad máxima de recursión puede alcanzar `10^6` marcos de pila.
   - En sistemas con límite de pila estándar (por ejemplo, 8 MB o 2 MB en Windows), cada llamada a función consume entre 32 y 64 bytes, provocando `Runtime Error (SIGSEGV)` tras ~30,000 llamadas.
2. **Recomendación de Producción / CP:**
   Para problemas de Flood Fill en retículas grandes, siempre se debe preferir **BFS iterativo con cola (`std::queue`)** o un DFS manual con vector de pila. El BFS garantiza uso exclusivo de memoria heap, es inmune a desbordamientos de pila y opera en tiempo estrictamente lineal `O(R * C)`.

---

## 4. Complejidad y Código Limpio (BFS Recomendado)

- **Complejidad Temporal:** `O(R * C)` por caso de prueba. Cada celda transitable se visita exactamente una vez. Con `R, C <= 1000`, toma menos de `0.04 s` en C++.
- **Complejidad Espacial:** `O(R * C)` para almacenar la matriz y la cola del BFS (~2 MB, muy por debajo de los 128 MB permitidos).

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

void solve() {
    int R, C;
    while (cin >> R >> C && (R != 0 || C != 0)) {
        vector<string> grid(R);
        int start_r = -1, start_c = -1;
        for (int i = 0; i < R; ++i) {
            cin >> grid[i];
            for (int j = 0; j < C; ++j) {
                if (grid[i][j] == '*') {
                    start_r = i;
                    start_c = j;
                }
            }
        }

        // BFS seguro en heap para prevenir Stack Overflow
        queue<pair<int, int>> q;
        q.push({start_r, start_c});
        grid[start_r][start_c] = '#';
        int visited_count = 0;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            visited_count++;

            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
                    grid[nr][nc] = '#';
                    q.push({nr, nc});
                }
            }
        }

        cout << visited_count << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
```
