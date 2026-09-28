# RPC 2026-09 I - Internal Triangles

**Type:** Math / Combinatorics
**Rating / Context:** Div 3A / Div 2A (UTP Open 2026)
**Tag:** modular-binomial-coefficient-giant-n

## Key Insight

💡 In a regular convex polygon, every subset of 3 vertices forms a non-degenerate triangle; compute `C(n, 3) = n*(n-1)*(n-2)/6 mod (10^9 + 7)` for `n <= 10^18` using `inv(6) = 166666668`.

## Pattern Trigger

"Regular convex polygon of `n` sides (`n <= 10^18`), number of triangles formed by 3 vertices modulo `10^9 + 7`."

## Breakthrough

Do not compute `n * (n - 1) * (n - 2)` directly in 64-bit integer (`n^3 <= 10^54` overflows `long long`); reduce each factor modulo `10^9 + 7` first and multiply by modular inverse `inv(6)`.

## Code Spotlight

```cpp
long long a = n % MOD, b = (n - 1) % MOD, c = (n - 2) % MOD;
long long ans = (a * b) % MOD;
ans = (ans * c) % MOD;
ans = (ans * 166666668LL) % MOD;
```

## Example

Input: `n = 5`
Output: `10`
Why: `C(5, 3) = 5 * 4 * 3 / 6 = 10` distinct triangles.

---

**Generated:** 2026-09-26
