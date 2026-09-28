#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;

// Arreglos globales estáticos para no fragmentar memoria (consumo total ~20 MB)
int P[MAXN];
int sz[MAXN];
int F[MAXN];
int max1_val[MAXN];
int max2_val[MAXN];

int main() {
    // Optimización de I/O indispensable para N = 10^6
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    for (int i = 2; i <= N; ++i) {
        cin >> P[i];
    }

    for (int i = 1; i <= N; ++i) {
        sz[i] = 1;
        F[i] = 0;
        max1_val[i] = 0;
        max2_val[i] = 0;
    }

    long long total_dist = 0;

    // Procesamiento bottom-up garantizado por Pi < i
    for (int i = N; i >= 1; --i) {
        // Mejor camino con LCA en el nodo i
        int path_through = max1_val[i] + max2_val[i];
        if (path_through > F[i]) {
            F[i] = path_through;
        }

        if (i > 1) {
            int p = P[i];
            sz[p] += sz[i];
            total_dist += (long long)sz[i] * (N - sz[i]);

            // Rama que desciende desde p a través de i
            int branch = max1_val[i] + 1;
            if (branch >= max1_val[p]) {
                max2_val[p] = max1_val[p];
                max1_val[p] = branch;
            } else if (branch > max2_val[p]) {
                max2_val[p] = branch;
            }

            // El diámetro del subárbol de p puede ser heredado del subárbol de i
            if (F[i] > F[p]) {
                F[p] = F[i];
            }
        }
    }

    // Salida
    cout << total_dist << "\n";
    for (int i = 1; i <= N; ++i) {
        cout << F[i] << (i == N ? "" : " ");
    }
    cout << "\n";

    return 0;
}
