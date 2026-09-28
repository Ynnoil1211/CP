#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000005;

struct Block {
    long long w, p;
    int id;
    bool operator<(const Block& o) const {
        return w * o.p < o.w * p; // Densidad: w/p < o.w/o.p
    }
};

int parent_dsu[MAXN], parent_tree[MAXN];
long long P[MAXN], W[MAXN];

int find_set(int v) {
    return v == parent_dsu[v] ? v : parent_dsu[v] = find_set(parent_dsu[v]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        long long total_cost = 0;
        P[0] = W[0] = parent_dsu[0] = parent_tree[0] = 0;

        for (int i = 1; i <= n; ++i) {
            cin >> P[i];
            parent_dsu[i] = i;
            parent_tree[i] = 0;
        }
        for (int i = 1; i <= n; ++i) {
            cin >> W[i];
            total_cost += P[i] * W[i]; // Costo base (0 + pi) * wi
        }

        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            parent_tree[a] = b; // b debe cerrarse antes que a
        }

        priority_queue<Block> pq;
        for (int i = 1; i <= n; ++i) pq.push({W[i], P[i], i});

        while (!pq.empty()) {
            auto [w, p, u] = pq.top();
            pq.pop();

            if (find_set(u) != u || W[u] != w || P[u] != p) continue;

            int par = find_set(parent_tree[u]);

            total_cost += P[par] * W[u];
            P[par] += P[u];
            W[par] += W[u];
            parent_dsu[u] = par;

            if (par != 0) pq.push({W[par], P[par], par});
        }

        cout << total_cost << "\n";
    }
    return 0;
}