#include <bits/stdc++.h>
using namespace std;

// Problema M: Marble tilt maze (RPC 09 / UTP Open 2026)
// Complejidad Temporal: O((N * M)^2 * max(N, M))
// Complejidad Espacial: O((N * M)^2) ~ 3.09 MB

int N, M;
vector<string> g;

// Direcciones: arriba, abajo, izquierda, derecha
const int DR[4] = {-1, 1, 0, 0};
const int DC[4] = {0, 0, -1, 1};

// Intenta mover UNA casilla la canica (r,c) en la direccion d.
// (orr, orc) = posicion actual de la otra canica.
// Devuelve: 0 = no se movio (pared u otra canica), 1 = se movio, -1 = se perdio (fuera o agujero)
int step(int &r, int &c, int d, int orr, int orc) {
    int nr = r + DR[d], nc = c + DC[d];
    if (nr < 0 || nr >= N || nc < 0 || nc >= M) return -1; // Se sale del tablero
    if (g[nr][nc] == '#') return 0;                          // Choca con pared
    if (nr == orr && nc == orc) return 0;                    // Choca con la otra canica
    r = nr; c = nc;
    if (g[r][c] == 'O') return -1;                           // Cae en un agujero
    return 1;
}

void solve() {
    g.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> g[i];
    }

    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;

    auto id = [&](int a, int b, int x, int y) {
        return ((a * M + b) * N + x) * M + y;
    };
    auto win = [&](int a, int b, int x, int y) {
        return g[a][b] == 'G' && g[x][y] == 'G';
    };

    vector<int> dist(N * M * N * M, -1);
    queue<array<int, 4>> q;

    int start_id = id(r1, c1, r2, c2);
    dist[start_id] = 0;
    q.push({r1, c1, r2, c2});

    while (!q.empty()) {
        auto [a, b, x, y] = q.front();
        q.pop();
        int cur = dist[id(a, b, x, y)];

        if (win(a, b, x, y)) {
            cout << cur << "\n";
            return;
        }

        for (int d = 0; d < 4; d++) {
            int A = a, B = b, X = x, Y = y;
            // La canica que va "adelante" en esta direccion se mueve primero,
            // asi la de atras puede ocupar la casilla que la delantera desaloja.
            bool firstIsOne = (a * DR[d] + b * DC[d]) >= (x * DR[d] + y * DC[d]);

            // Inclinamos paso a paso; tras cada paso el jugador puede estabilizar el tablero.
            while (true) {
                int s1, s2;
                if (firstIsOne) {
                    s1 = step(A, B, d, X, Y);
                    if (s1 == -1) break;
                    s2 = step(X, Y, d, A, B);
                } else {
                    s2 = step(X, Y, d, A, B);
                    if (s2 == -1) break;
                    s1 = step(A, B, d, X, Y);
                }

                if (s1 == -1 || s2 == -1) break; // Al menos una canica se perdio
                if (s1 == 0 && s2 == 0) break;   // Ambas canicas quedaron bloqueadas

                int k = id(A, B, X, Y);
                if (dist[k] == -1) {
                    dist[k] = cur + 1;
                    q.push({A, B, X, Y});
                }
            }
        }
    }

    cout << -1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> M) {
        solve();
    }
    return 0;
}
