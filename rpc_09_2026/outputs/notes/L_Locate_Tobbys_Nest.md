# Problema L: Locate Tobby’s nest

- **Concurso:** RPC 09 (Septiembre 26, 2026) / UTP Open 2026
- **Autor:** Hugo Humberto Morales Peña (UTP Colombia)
- **Dificultad Estimada:** Media (Div 2C)
- **Estado en Concurso:** Upsolved Post-Concurso
- **Archivos de Referencia:**
  - Enunciado: [UTPOpen2026v4.pdf](../../inputs/problemset/UTPOpen2026v4.pdf)
  - Solución del Equipo: [L_Locate_Tobbys_Nest.cpp](../../inputs/solutions/L_Locate_Tobbys_Nest.cpp)
  - Solución Oficial: [L_Locate_Tobbys_Nest.cpp](../../inputs/official_solutions/L_Locate_Tobbys_Nest.cpp)

---

## 1. Lógica y Enfoque del Problema

Tobby es un perrito que vive en una casa modelada como una retícula de dimensiones `H x W`. Las celdas transitables (`'.'`) forman un **árbol libre conexo** (no hay ciclos y existe un único camino simple entre cualquier par de celdas libres).

Tobby desea construir su nido en una celda `u` que minimice la máxima distancia hacia cualquier rincón de la casa:
`min_{u in V} epsilon(u),  donde  epsilon(u) = max_{v in V} dist(u, v)`.
Esto corresponde exactamente a encontrar el **centro del árbol** (*1-center problem*).

### Teorema de Jordan (1869) sobre Centros de Árboles
1. Todo árbol tiene **exactamente 1 o 2 centros**.
2. Todos los centros pertenecen obligatoriamente al punto medio de cualquier diámetro del árbol.
3. Si el diámetro `D` es par, el centro es único y se encuentra a distancia `D / 2` de los extremos.
4. Si `D` es impar, existen dos centros adyacentes a distancias `floor(D / 2)` y `ceil(D / 2)`.
5. **Criterio de Desempate del Enunciado:** Si existen dos centros candidatos `c1` y `c2`, se escoge el de **menor columna**; en caso de empate, el de **menor fila**.

---

## 2. Algoritmo Óptimo (Doble BFS y Retroceso por Gradiente)

Para resolver el problema en `O(H * W)` de forma limpia y sin matrices de punteros a padres:
1. **Paso 1 (Primer BFS):** Desde cualquier celda libre inicial, encontrar la celda más lejana: la llamamos `A` (primer extremo de un diámetro).
2. **Paso 2 (Segundo BFS):** Enraizado en `A`, encontrar la celda más lejana a `A`: la llamamos `B`. La distancia registrada `d[B.r][B.c]` es la longitud exacta del diámetro `D`.
3. **Paso 3 (Retroceso por Gradiente):** En un árbol, todo nodo `u != A` tiene un único vecino con distancia `d[u] - 1`. Partiendo de `B`, avanzamos repetidamente al vecino de distancia decrementada hasta alcanzar las profundidades `floor(D / 2)` y `ceil(D / 2)`.
4. **Paso 4:** Si `D` es impar, desempatar según la regla estipulada e imprimir en formato 1-indexado (`Case t: fila col`).

---

## 3. Trampas Cognitivas Recurrentes

1. **El orden del criterio de desempate:**
   El enunciado estipula *"menor columna y en caso de empate menor fila"*, al revés del orden lexicográfico habitual (`fila, luego columna`). Leer descuidadamente esta regla causa `Wrong Answer` inmediato en diámetros de longitud impar.
2. **Formato de Salida:**
   Debe incluir el prefijo `"Case t: "` y las coordenadas deben ser 1-indexadas.

---

## 4. Complejidad y Código Limpio

- **Complejidad Temporal:** `O(H * W)` por caso. Para `T <= 10` y `1000 x 1000`, ejecuta en `~0.07 s` en C++ (límite: 1.0 s).
- **Complejidad Espacial:** `O(H * W)`. Una sola matriz de distancias `d[1005][1005]` consume `~4 MB`.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXN = 1005;
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

int H, W;
string grid[MAXN];
int d[MAXN][MAXN];

pair<int, int> bfs(int sr, int sc) {
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) d[i][j] = -1;
    }

    queue<pair<int, int>> q;
    q.push({sr, sc});
    d[sr][sc] = 0;
    pair<int, int> far = {sr, sc};

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (d[r][c] > d[far.first][far.second]) far = {r, c};

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && d[nr][nc] == -1) {
                d[nr][nc] = d[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return far;
}

pair<int, int> pick_best(pair<int, int> a, pair<int, int> b) {
    if (a.second != b.second) return a.second < b.second ? a : b;
    return a.first < b.first ? a : b;
}

void solve(int t) {
    cin >> H >> W;
    int sr = -1, sc = -1;
    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
        if (sr == -1) {
            for (int j = 0; j < W; ++j) {
                if (grid[i][j] == '.') { sr = i; sc = j; }
            }
        }
    }

    auto A = bfs(sr, sc);
    auto B = bfs(A.first, A.second);
    int D = d[B.first][B.second];

    pair<int, int> cur = B, c1 = {-1, -1}, c2 = {-1, -1};
    while (true) {
        if (d[cur.first][cur.second] == (D + 1) / 2) c2 = cur;
        if (d[cur.first][cur.second] == D / 2) { c1 = cur; break; }

        for (int i = 0; i < 4; ++i) {
            int nr = cur.first + dr[i], nc = cur.second + dc[i];
            if (nr >= 0 && nr < H && nc >= 0 && nc < W && d[nr][nc] == d[cur.first][cur.second] - 1) {
                cur = {nr, nc};
                break;
            }
        }
    }

    auto ans = (D % 2 == 0) ? c1 : pick_best(c1, c2);
    cout << "Case " << t << ": " << ans.first + 1 << " " << ans.second + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) solve(t);
    }
    return 0;
}
```
