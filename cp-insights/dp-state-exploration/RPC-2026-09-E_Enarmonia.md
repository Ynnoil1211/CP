# RPC 2026-09 E - Enarmonía

**Type:** DP / State Exploration
**Rating / Context:** Div 2D / Div 1B (UTP Open 2026)
**Tag:** circular-pointer-bounded-alternation-dp

## Key Insight

💡 Model intertwined circular sequence generation as a 4-parameter DP state `(c1, c2, k, active_tape)` tracking consumed prefix lengths and alternation budget to maximize consecutive matches.

## Pattern Trigger

"Two circular tapes of sizes `N1, N2`, construct length `T` with at most `K` switches maximizing identical adjacent elements."

## Breakthrough

Greedy choice of immediate echoes burns the `K` switch budget prematurely; DP top-down memoization explores all feasible switch points in `O(T^2 * K)`.

## Code Spotlight

```cpp
int solve_dp(int c1, int c2, int k, int m) {
    if (c1 + c2 == T) return 0;
    if (memo[c1][c2][k][m] != -1) return memo[c1][c2][k][m];
    const string& last = (m == 0) ? A[(c1 - 1) % N1] : B[(c2 - 1) % N2];
    int best = (A[c1 % N1] == last) + solve_dp(c1 + 1, c2, k, 0); // stay M1
    if (k + 1 <= K) best = max(best, (B[c2 % N2] == last) + solve_dp(c1, c2 + 1, k + 1, 1));
    return memo[c1][c2][k][m] = best;
}
```

## Example

Input: `K = 1, T = 3`, `A = [x, y]`, `B = [x, z]`
Output: `Max echoes`
Why: Optimal switching point balances immediate character match against future available repetitions.

---

**Generated:** 2026-09-26
