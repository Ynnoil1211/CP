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

// Menor Ancestro Común (LCA)
int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
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

int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

int main() {
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

    // Paso 1: BFS para encontrar el extremo A del diámetro
    queue<int> q;
    vector<int> d(MAXV, -1);
    q.push(start_node);
    d[start_node] = 0;
    int A = start_node;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (d[u] > d[A]) A = u;
        for (int v : adj[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }

    // Paso 2: BFS enraizando el árbol en A.
    // Llena Binary Lifting y halla B y el diámetro inicial directamente
    vector<bool> vis(MAXV, false);
    q.push(A);
    vis[A] = true;
    depth[A] = 0;
    up[A][0] = A;
    int B = A;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 1; i < LOG; ++i) up[u][i] = up[up[u][i - 1]][i - 1];
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

    // Paso 3: Consultas online en O(log N)
    int Q;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;

        // Conectar la nueva hoja x a su padre y
        depth[x] = depth[y] + 1;
        up[x][0] = y;
        for (int i = 1; i < LOG; ++i) up[x][i] = up[up[x][i - 1]][i - 1];

        // Solo puede competir con los extremos actuales A o B
        int da = dist(x, A);
        int db = dist(x, B);

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