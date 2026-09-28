#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000005;

struct Block {
    long long w, p;
    int id;

    // Comparador de densidad: w/p > other.w/other.p <=> w * other.p > other.w * p
    bool operator<(const Block& other) const {
        return w * other.p < other.w * p;
    }
};

int parent_dsu[MAXN];
int parent_tree[MAXN];
long long P[MAXN];
long long W[MAXN];

int find_set(int v) {
    if (v == parent_dsu[v]) return v;
    return parent_dsu[v] = find_set(parent_dsu[v]);
}

void solve() {
    int n;
    while (cin >> n) {
        long long total_cost = 0;

        // Inicializar raíz virtual 0
        P[0] = 0;
        W[0] = 0;
        parent_dsu[0] = 0;
        parent_tree[0] = 0;

        for (int i = 1; i <= n; ++i) {
            cin >> P[i];
            parent_dsu[i] = i;
            parent_tree[i] = 0; // Raíz por defecto conectada a 0
        }

        for (int i = 1; i <= n; ++i) {
            cin >> W[i];
            // Costo base propio: (0 + pi) * wi
            total_cost += P[i] * W[i];
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            // 'a' no puede cerrarse antes que 'b' => 'b' debe ejecutarse antes que 'a'
            parent_tree[a] = b;
        }

        priority_queue<Block> pq;
        for (int i = 1; i <= n; ++i) {
            pq.push({W[i], P[i], i});
        }

        while (!pq.empty()) {
            auto [w, p, u] = pq.top();
            pq.pop();

            // Lazy deletion: descartar si no es representante o sus valores cambiaron
            if (find_set(u) != u || W[u] != w || P[u] != p) {
                continue;
            }

            int par = find_set(parent_tree[u]);

            // Costo cruzado por posponer el bloque u durante la ejecución del bloque par
            total_cost += P[par] * W[u];

            // Fusión de bloques: u queda absorbido por par
            P[par] += P[u];
            W[par] += W[u];
            parent_dsu[u] = par;

            // Si el bloque padre resultante no es el nodo dummy 0, se reinserta
            if (par != 0) {
                pq.push({W[par], P[par], par});
            }
        }

        cout << total_cost << "\n";
    }
}

int main() {
    // Optimización de flujos de I/O estándar
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
