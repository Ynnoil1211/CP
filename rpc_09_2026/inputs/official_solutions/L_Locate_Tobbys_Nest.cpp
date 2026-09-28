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

// BFS genérico: llena distancias desde (sr, sc) y devuelve la celda más lejana
pair<int, int> bfs(int sr, int sc) {
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            d[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;
    q.push({sr, sc});
    d[sr][sc] = 0;
    pair<int, int> far = {sr, sc};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (d[r][c] > d[far.first][far.second]) {
            far = {r, c};
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W && grid[nr][nc] == '.' && d[nr][nc] == -1) {
                d[nr][nc] = d[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return far;
}

// Criterio de desempate exigido: menor columna, luego menor fila
pair<int, int> pick_best(pair<int, int> a, pair<int, int> b) {
    if (a.second != b.second) {
        return a.second < b.second ? a : b;
    }
    return a.first < b.first ? a : b;
}

void solve(int t) {
    cin >> H >> W;
    int sr = -1, sc = -1;

    for (int i = 0; i < H; ++i) {
        cin >> grid[i];
        if (sr == -1) {
            for (int j = 0; j < W; ++j) {
                if (grid[i][j] == '.') {
                    sr = i;
                    sc = j;
                }
            }
        }
    }

    // 1. Encontrar extremo A (más lejano al inicio) y extremo B (más lejano a A)
    auto A = bfs(sr, sc);
    auto B = bfs(A.first, A.second);
    int D = d[B.first][B.second];

    // 2. Retroceso guiado por gradiente de distancia desde B hacia A
    pair<int, int> cur = B, c1 = {-1, -1}, c2 = {-1, -1};

    while (true) {
        if (d[cur.first][cur.second] == (D + 1) / 2) c2 = cur;
        if (d[cur.first][cur.second] == D / 2) {
            c1 = cur;
            break;
        }

        // Buscar el único vecino en dirección a la raíz A (con distancia d - 1)
        for (int i = 0; i < 4; ++i) {
            int nr = cur.first + dr[i];
            int nc = cur.second + dc[i];

            if (nr >= 0 && nr < H && nc >= 0 && nc < W && d[nr][nc] == d[cur.first][cur.second] - 1) {
                cur = {nr, nc};
                break;
            }
        }
    }

    // Si D es par, el centro es único (c1 == c2). Si es impar, desempatamos
    auto ans = (D % 2 == 0) ? c1 : pick_best(c1, c2);

    // Salida 1-indexada
    cout << "Case " << t << ": " << ans.first + 1 << " " << ans.second + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        for (int t = 1; t <= T; ++t) {
            solve(t);
        }
    }

    return 0;
}
