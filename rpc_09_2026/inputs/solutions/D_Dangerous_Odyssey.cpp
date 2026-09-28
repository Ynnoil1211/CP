#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 1005;

// Desplazamientos en 8 direcciones (Chebyshev - Cantos y Hechizos)
const int dr8[] = {-1, -1, -1,  0, 0,  1, 1, 1};
const int dc8[] = {-1,  0,  1, -1, 1, -1, 0, 1};

// Desplazamientos en 4 direcciones (Manhattan - Navegación)
const int dr4[] = {-1, 1,  0, 0};
const int dc4[] = { 0, 0, -1, 1};

int N, M, H, D;
string grid[MAXN];

int danger_dist[MAXN][MAXN];
int refuge_dist[MAXN][MAXN];
int osideo_dist[MAXN][MAXN];

void solve() {
    cin >> H >> D;

    for (int i = 0; i < N; ++i) {
        cin >> grid[i];
    }

    // Inicialización de matrices para cada caso de prueba
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            danger_dist[i][j] = INF;
            refuge_dist[i][j] = INF;
            osideo_dist[i][j] = -1;
        }
    }

    queue<pair<int, int>> q;

    // -------------------------------------------------------------
    // FASE 1: Multi-source BFS (8D) para Sirenas ('S') y Brujas ('B')
    // -------------------------------------------------------------
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'S' || grid[i][j] == 'B') {
                danger_dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (danger_dist[r][c] == H) continue;

        for (int d = 0; d < 8; ++d) {
            int nr = r + dr8[d];
            int nc = c + dc8[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (danger_dist[nr][nc] > danger_dist[r][c] + 1) {
                    danger_dist[nr][nc] = danger_dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    // Localizar Yorta ('Y') y Acati ('A')
    int start_r = -1, start_c = -1;
    int target_r = -1, target_c = -1;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'Y') {
                start_r = i; start_c = j;
            } else if (grid[i][j] == 'A') {
                target_r = i; target_c = j;
            }
        }
    }

    // Por especificación: 'Y' y 'A' están garantizados libres de peligro
    if (start_r != -1) danger_dist[start_r][start_c] = INF;
    if (target_r != -1) danger_dist[target_r][target_c] = INF;

    // -------------------------------------------------------------
    // FASE 2: Multi-source BFS (4D) desde Refugios Válidos
    // -------------------------------------------------------------
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == 'Y' || grid[i][j] == 'A') {
                refuge_dist[i][j] = 0;
                q.push({i, j});
            } else if (grid[i][j] == 'R') {
                // Solo es refugio si no es alcanzado por cantos o hechizos
                if (danger_dist[i][j] > H) {
                    refuge_dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
    }

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (refuge_dist[r][c] == D) continue;

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr4[d];
            int nc = c + dc4[d];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                if (refuge_dist[nr][nc] > refuge_dist[r][c] + 1) {
                    refuge_dist[nr][nc] = refuge_dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    // -------------------------------------------------------------
    // FASE 3: BFS de camino mínimo para Osideo
    // -------------------------------------------------------------
    if (start_r == -1 || target_r == -1) {
        cout << "OSIDEO WILL DIE\n";
        return;
    }

    osideo_dist[start_r][start_c] = 0;
    q.push({start_r, start_c});

    int answer = -1;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == target_r && c == target_c) {
            answer = osideo_dist[r][c];
            break;
        }

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr4[d];
            int nc = c + dc4[d];

            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                // El barco no puede navegar a través de islas ('R', 'S', 'B')
                if (grid[nr][nc] != '.' && grid[nr][nc] != 'A') {
                    continue;
                }

                // Condiciones de supervivencia y cobertura
                if (osideo_dist[nr][nc] == -1 && 
                    danger_dist[nr][nc] > H && 
                    refuge_dist[nr][nc] <= D) {
                    
                    osideo_dist[nr][nc] = osideo_dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    // Salida
    if (answer != -1) {
        cout << answer << "\n";
    } else {
        cout << "OSIDEO WILL DIE\n";
    }
}

int main() {
    // Optimización de flujos de E/S estándar
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Lectura continua multi-caso (estándar ICPC/RPC en BOCA)
    while (cin >> N >> M) {
        solve();
    }

    return 0;
}
