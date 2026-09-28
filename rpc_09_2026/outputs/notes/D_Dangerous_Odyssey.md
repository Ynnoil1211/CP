# Problema D: Dangerous odyssey

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Roberto Solís (UAZ México)
- **Dificultad Estimada:** Media (Div 2B / Div 2C)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [D_Dangerous_Odyssey.cpp](../../inputs/solutions/D_Dangerous_Odyssey.cpp)
  - Solución Oficial: [D_Dangerous_Odyssey.cpp](../../inputs/official_solutions/D_Dangerous_Odyssey.cpp)

---

## 1. Lógica y Enfoque del Problema

Osideo debe navegar su barco a través de un archipiélago reticular de dimensiones `N x M` desde la isla Yorta (`'Y'`) hasta la isla Acati (`'A'`), enfrentando tres restricciones espaciales simultáneas:

1. **Difusión de Peligro (Distancia de Chebyshev / L_infinito):**
   - Las sirenas (`'S'`) y brujas (`'B'`) emiten cantos y hechizos letales que se propagan en **8 direcciones** (incluyendo diagonales).
   - Cualquier celda a distancia `L_inf <= H` de una sirena o bruja es mortal.
2. **Cobertura ante Tormentas (Distancia de Manhattan / L_1):**
   - El barco no puede navegar en diagonal; en caso de tormenta, solo puede refugiarse si se encuentra a distancia `L_1 <= D` (4 direcciones ortogonales) de algún **refugio seguro**.
   - Los refugios seguros son las islas `'R'` que **no** estén dentro del alcance de peligro (`danger_dist > H`), más los puntos garantizados de partida (`'Y'`) y llegada (`'A'`).
3. **Navegabilidad Marítima:**
   - El barco únicamente puede transitar sobre casillas de agua (`'.'`) y finalizar en `'A'`.
   - Las islas refugio (`'R'`) son tierra firme; por lo tanto, el barco **no puede atravesar celdas `'R'`**.

---

## 2. Pipeline de Solución (3 Fases BFS)

El problema se resuelve de forma elegante mediante tres recorridos en anchura independientes:

```text
[Sirenas 'S' / Brujas 'B']  ---> (BFS 8D Multi-fuente hasta H) ---> Matriz danger_dist[][]
                                                                            |
                                                                            v
['Y', 'A', y 'R' seguros]    ---> (BFS 4D Multi-fuente hasta D) ---> Matriz refuge_dist[][]
                                                                            |
                                                                            v
['Y' (Inicio de Osideo)]     ---> (BFS 4D sobre '.')            ---> Distancia mínima a 'A'
```

- **Fase 1 (BFS 8D):** Encolar todas las `'S'` y `'B'` con distancia 0. Expandir en 8 direcciones hasta profundidad `H`. Posteriormente, restaurar explícitamente `danger_dist = INF` en `'Y'` y `'A'`, pues el enunciado garantiza que son inmunes.
- **Fase 2 (BFS 4D):** Encolar `'Y'`, `'A'` y toda `'R'` que tenga `danger_dist > H` con distancia 0. Expandir en 4 direcciones ortogonales hasta profundidad `D`.
- **Fase 3 (BFS 4D):** Iniciar BFS desde `'Y'`. Avanzar a una celda vecina `(nr, nc)` si y solo si:
  1. Es agua (`'.'`) o la meta (`'A'`).
  2. No ha sido visitada por Osideo (`osideo_dist == -1`).
  3. Está fuera de peligro (`danger_dist > H`).
  4. Está dentro del rango de tormenta (`refuge_dist <= D`).

Si se alcanza `'A'`, imprimir la distancia. Si la cola se vacía sin alcanzar la meta, imprimir `OSIDEO WILL DIE`.

---

## 3. Trampas Cognitivas que Causaron WA

| Trampa Detectada | Error Provocado | Corrección Aplicada |
| --- | --- | --- |
| **Múltiples casos por archivo (EOF)** | Leer un único caso con `cin >> N >> M` y salir. | Envolver la ejecución en `while (cin >> N >> M)`. |
| **Atravesar islas `'R'`** | Considerar las celdas `'R'` como navegables si eran seguras. | El barco solo se desplaza por agua `'.'` y desembarca en `'A'`. |
| **Inmunidad de `'Y'` y `'A'`** | Una sirena cercana invalidaba `'A'` o `'Y'`. | Restaurar `danger_dist = INF` en `'Y'` y `'A'`. |
| **Limpieza de matrices** | Contaminación de distancias entre casos consecutivos. | Reinicializar completamente las matrices a `INF` y `-1`. |

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(N * M)` por caso de prueba. Cada una de las 3 fases visita cada celda a lo sumo una vez. Para `1000 x 1000`, toma `< 0.15 s`.
- **Complejidad Espacial:** `O(N * M)`. Tres matrices estáticas de `1005 x 1005` enteros consumen `~15 MB`, muy por debajo de los 128 MB.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 1005;

const int dr8[] = {-1, -1, -1,  0, 0,  1, 1, 1};
const int dc8[] = {-1,  0,  1, -1, 1, -1, 0, 1};
const int dr4[] = {-1, 1,  0, 0};
const int dc4[] = { 0, 0, -1, 1};

int N, M, H, D;
string grid[MAXN];
int danger_dist[MAXN][MAXN];
int refuge_dist[MAXN][MAXN];
int osideo_dist[MAXN][MAXN];

void solve() {
    cin >> H >> D;
    for (int i = 0; i < N; ++i) cin >> grid[i];

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            danger_dist[i][j] = INF;
            refuge_dist[i][j] = INF;
            osideo_dist[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;

    // Fase 1: Peligro en 8 direcciones
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'S' || grid[i][j] == 'B') {
                danger_dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (danger_dist[r][c] == H) continue;

        for (int d = 0; d < 8; ++d) {
            int nr = r + dr8[d], nc = c + dc8[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (danger_dist[nr][nc] > danger_dist[r][c] + 1) {
                    danger_dist[nr][nc] = danger_dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    int start_r = -1, start_c = -1, target_r = -1, target_c = -1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'Y') { start_r = i; start_c = j; }
            if (grid[i][j] == 'A') { target_r = i; target_c = j; }
        }
    }

    if (start_r != -1) danger_dist[start_r][start_c] = INF;
    if (target_r != -1) danger_dist[target_r][target_c] = INF;

    // Fase 2: Cobertura de refugios en 4 direcciones
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'Y' || grid[i][j] == 'A') {
                refuge_dist[i][j] = 0;
                q.push({i, j});
            } else if (grid[i][j] == 'R' && danger_dist[i][j] > H) {
                refuge_dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (refuge_dist[r][c] == D) continue;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr4[d], nc = c + dc4[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (refuge_dist[nr][nc] > refuge_dist[r][c] + 1) {
                    refuge_dist[nr][nc] = refuge_dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    // Fase 3: Navegación de Osideo
    if (start_r == -1 || target_r == -1) {
        cout << "OSIDEO WILL DIE\n";
        return;
    }
    osideo_dist[start_r][start_c] = 0;
    q.push({start_r, start_c});
    int answer = -1;

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == target_r && c == target_c) {
            answer = osideo_dist[r][c];
            break;
        }

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr4[d], nc = c + dc4[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (grid[nr][nc] != '.' && grid[nr][nc] != 'A') continue;
                if (osideo_dist[nr][nc] == -1 && danger_dist[nr][nc] > H && refuge_dist[nr][nc] <= D) {
                    osideo_dist[nr][nc] = osideo_dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    if (answer != -1) cout << answer << "\n";
    else cout << "OSIDEO WILL DIE\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> N >> M) solve();
    return 0;
}
```
