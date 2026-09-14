# 1855B - Longest Divisors Interval

**Type:** Math / Number Theory
**Rating:** 900
**Tag:** lcm-interval-bound

## Key Insight

💡 Any interval of length $k$ must contain a multiple of $k$; thus, if $k$ is the smallest integer not dividing $n$, no valid divisor interval can have length $\ge k$, making the answer simply $k - 1$.

## Pattern Trigger

"Find maximum length of interval $[l, r]$ where every integer divides $n \le 10^{18}$." Any interval of length $k$ contains a multiple of every integer $1 \dots k$, which quickly forces $\text{LCM}(1 \dots k) > 10^{18}$ (within $k \le 50$).

## Breakthrough

You never need to search arbitrary intervals $[l, r]$; the optimal interval is always the prefix $[1, k-1]$ ending right before the first non-divisor, computable in $O(\log n)$ operations.

## Code Spotlight

```cpp
ll n; cin >> n;
int i = 1;
while (n % i == 0) i++;
cout << i - 1 << "\n";
```

## Example

Input: `n = 420`
Trace:
- $420 \pmod 1 = 0, \dots, 420 \pmod 7 = 0$
- $420 \pmod 8 = 4 \ne 0 \implies k = 8$
Output: `7` (interval $[1, 7]$)
Why: Any interval of length 8 contains a multiple of 8, which would require $8 \mid 420$, a contradiction.

---

**Generated:** 2026-09-13
