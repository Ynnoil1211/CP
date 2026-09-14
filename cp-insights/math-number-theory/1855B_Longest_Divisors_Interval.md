# 1855B - Longest Divisors Interval

**Type:** Math / Number Theory
**Rating:** 900
**Tag:** lcm-interval-bound

## Key Insight

💡 Any interval of length k must contain a multiple of k; thus, if k is the smallest integer not dividing n, no valid divisor interval can have length >= k, making the answer simply k - 1.

## Pattern Trigger

"Find maximum length of interval [l, r] where every integer divides n <= 10^18." Any interval of length k contains a multiple of every integer 1 ... k, which quickly forces LCM(1 ... k) > 10^18 (within k <= 50).

## Breakthrough

You never need to search arbitrary intervals [l, r]; the optimal interval is always the prefix [1, k-1] ending right before the first non-divisor, computable in O(log n) operations.

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
- 420 (mod 1) = 0, ..., 420 (mod 7) = 0
- 420 (mod 8) = 4 != 0 => k = 8
Output: `7` (interval [1, 7])
Why: Any interval of length 8 contains a multiple of 8, which would require 8 | 420, a contradiction.

---

**Generated:** 2026-09-13