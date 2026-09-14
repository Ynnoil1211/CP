# RPC 2026-08 H - Magnesium Supplementation

**Type:** Math / Number Theory
**Rating:** 1100
**Tag:** sqrt-divisor-factorization

## Key Insight

💡 Daily dose D must divide total magnesium N such that D <= K and N / D <= P; iterate up to sqrt(N) in O(sqrt(N)) to collect paired divisors (i, N/i) using 64-bit integers.

## Pattern Trigger

"N = D * T <= 10^12, upper bounds D <= K and T <= P, list all valid doses in increasing order." Total requirement N must factor as D * T; factor search space is bounded by sqrt(N) <= 10^6.

## Breakthrough

Do not loop linearly up to K <= 10^12 (guaranteed TLE); extract symmetric divisor pairs (i, N/i) up to sqrt(N), and use `long long` (`vll`) for container storage to prevent 32-bit integer overflow when values exceed 2 * 10^9.

## Code Spotlight

```cpp
vector<ll> ans;
for (ll i = 1; i * i <= n; i++) {
    if (n % i == 0) {
        if (i <= k && n / i <= p) ans.push_back(i);
        if (i * i != n && n / i <= k && i <= p) ans.push_back(n / i);
    }
}
sort(ans.begin(), ans.end());
```

## Example

Input: N = 100, K = 25, P = 10
Divisors of 100: 1, 2, 4, 5, 10, 20, 25, 50, 100
Constraints: D <= 25 and 100/D <= 10 <=> D >= 10.
Valid doses in [10, 25]: 10, 20, 25.
Output: `3\n10\n20\n25`
Why: Searching up to sqrt(100) = 10 captures all conjugate divisor pairs without scanning up to K or N.

---

**Generated:** 2026-09-13