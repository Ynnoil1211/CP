#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int K, T, N1, N2;
vector<string> A, B;
int memo[152][152][152][2];

int solve_dp(int c1, int c2, int k, int m) {
    // Caso base: completamos la lectura de T actos
    if (c1 + c2 == T) return 0;
    
    if (memo[c1][c2][k][m] != -1) {
        return memo[c1][c2][k][m];
    }

    int best = 0;
    string last = (m == 0) ? A[(c1 - 1) % N1] : B[(c2 - 1) % N2];

    if (m == 0) {
        // Opción A: Seguir en el Manuscrito 1 (no gasta cambios)
        best = max(best, (A[c1 % N1] == last) + solve_dp(c1 + 1, c2, k, 0));
        
        // Opción B: Cambiar al Manuscrito 2 (gasta 1 cambio)
        if (k + 1 <= K) {
            best = max(best, (B[c2 % N2] == last) + solve_dp(c1, c2 + 1, k + 1, 1));
        }
    } else {
        // Opción A: Seguir en el Manuscrito 2 (no gasta cambios)
        best = max(best, (B[c2 % N2] == last) + solve_dp(c1, c2 + 1, k, 1));
        
        // Opción B: Cambiar al Manuscrito 1 (gasta 1 cambio)
        if (k + 1 <= K) {
            best = max(best, (A[c1 % N1] == last) + solve_dp(c1 + 1, c2, k + 1, 0));
        }
    }

    return memo[c1][c2][k][m] = best;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> K >> T) {
        cin >> N1;
        A.resize(N1);
        for (int i = 0; i < N1; ++i) cin >> A[i];

        cin >> N2;
        B.resize(N2);
        for (int i = 0; i < N2; ++i) cin >> B[i];

        if (T == 1) {
            cout << 0 << "\n";
            continue;
        }

        // Limpiar la tabla de memoización para el caso actual
        memset(memo, -1, sizeof(memo));

        // Siempre se empieza leyendo el primer acto de A (c1 = 1, c2 = 0, k = 0, m = 0)
        cout << solve_dp(1, 0, 0, 0) << "\n";
    }

    return 0;
}