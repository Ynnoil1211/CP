#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 155;

// Consumo de memoria: ~180 KB en total
short dp[MAX][MAX][2];
short next_dp[MAX][MAX][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K, T;
    while (cin >> K >> T) {
        int N1;
        cin >> N1;
        vector<string> A(N1);
        for (int i = 0; i < N1; ++i) cin >> A[i];

        int N2;
        cin >> N2;
        vector<string> B(N2);
        for (int i = 0; i < N2; ++i) cin >> B[i];

        if (T == 1) {
            cout << 0 << "\n";
            continue;
        }

        // Estado inicial para t = 1
        memset(dp, -1, sizeof(dp));
        dp[1][0][0] = 0; // Primer acto del manuscrito 1

        for (int t = 1; t < T; ++t) {
            memset(next_dp, -1, sizeof(next_dp));

            for (int c1 = 1; c1 <= t; ++c1) {
                int c2 = t - c1;
                for (int k = 0; k <= K; ++k) {
                    for (int m = 0; m < 2; ++m) {
                        short val = dp[c1][k][m];
                        if (val == -1) continue;

                        const string& last = (m == 0) ? A[(c1 - 1) % N1] : B[(c2 - 1) % N2];

                        // Rama 1: Tomar siguiente acto de M1
                        int nk1 = k + (m == 1 ? 1 : 0);
                        if (nk1 <= K) {
                            short echo = (A[c1 % N1] == last ? 1 : 0);
                            if (val + echo > next_dp[c1 + 1][nk1][0]) {
                                next_dp[c1 + 1][nk1][0] = val + echo;
                            }
                        }

                        // Rama 2: Tomar siguiente acto de M2
                        int nk2 = k + (m == 0 ? 1 : 0);
                        if (nk2 <= K) {
                            short echo = (B[c2 % N2] == last ? 1 : 0);
                            if (val + echo > next_dp[c1][nk2][1]) {
                                next_dp[c1][nk2][1] = val + echo;
                            }
                        }
                    }
                }
            }
            memcpy(dp, next_dp, sizeof(dp));
        }

        short max_ecos = 0;
        for (int c1 = 1; c1 <= T; ++c1) {
            for (int k = 0; k <= K; ++k) {
                for (int m = 0; m < 2; ++m) {
                    max_ecos = max(max_ecos, dp[c1][k][m]);
                }
            }
        }

        cout << max_ecos << "\n";
    }

    return 0;
}
