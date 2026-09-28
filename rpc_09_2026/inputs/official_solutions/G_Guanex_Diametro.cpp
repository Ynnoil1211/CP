#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAXV = 300005;
const int LOG = 20;

vector<int> adj[MAXV];
int depth[MAXV];
int up[MAXV][LOG];

// Menor Ancestro Común (LCA) en O(log V)
int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int i = LOG - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }

    if (u == v) return u;

    for (int i = LOG - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }

    return up[u][0];
}

// Distancia en árbol en O(log V)
inline int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

int main() {
    // E/S Rápida
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    int start_node = -1;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        start_node = u;
    }

    // -------------------------------------------------------------
    // PASO 1: BFS para localizar el primer extremo del diámetro (A)
    // -------------------------------------------------------------
    queue<int> q;
    vector<int> d(MAXV, -1);
    q.push(start_node);
    d[start_node] = 0;
    int A = start_node;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (d[u] > d[A]) A = u;

        for (int v : adj[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    // -------------------------------------------------------------
    // PASO 2: BFS enraizando el árbol en A
    // Construye la tabla 'up' y halla el otro extremo B
    // -------------------------------------------------------------
    vector<bool> vis(MAXV, false);
    q.push(A);
    vis[A] = true;
    depth[A] = 0;
    up[A][0] = A;
    int B = A;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int i = 1; i < LOG; ++i) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        if (depth[u] > depth[B]) B = u;

        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                depth[v] = depth[u] + 1;
                up[v][0] = u;
                q.push(v);
            }
        }
    }

    int diam = depth[B];
    cout << diam << "\n";

    // -------------------------------------------------------------
    // PASO 3: Procesamiento online de consultas
    // -------------------------------------------------------------
    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;

        // Inserción dinámica de la hoja x como hija de y
        depth[x] = depth[y] + 1;
        up[x][0] = y;
        for (int i = 1; i < LOG; ++i) {
            up[x][i] = up[up[x][i - 1]][i - 1];
        }

        // Medir distancias hacia los dos extremos actuales
        int da = dist(x, A);
        int db = dist(x, B);

        // Actualización condicional del diámetro y sus extremos
        if (da > diam && da >= db) {
            diam = da;
            B = x;
        } else if (db > diam) {
            diam = db;
            A = x;
        }

        cout << diam << "\n";
    }

    return 0;
}
