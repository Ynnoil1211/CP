# Codeforces 1520D - Same Differences

**Type:** Math / Formula Development
**Rating / Context:** 1200 / Codeforces Round 719 (Div. 3)
**Tag:** index-decoupling-frequency

## Key Insight

💡 Rewriting relational constraint `a_j - a_i = j - i` into invariant single-index keys `a_j - j = a_i - i` decouples indices and reduces pair-counting from `O(N^2)` to `O(N)`.

## Pattern Trigger

Equations or relations relating two positions `(i, j)` where algebraic rearrangement isolates all `j`-terms on one side and `i`-terms on the other under large `N` (`sum of N <= 2 * 10^5`).

## Breakthrough

Whenever an equation links `(i, j)`, rewriting it into `f(j) == f(i)` shifts the problem from finding pairs to counting equal keys in a hash map or frequency array in `O(N)`. Here, `a_j - j = a_i - i` defines the invariant key `b_k = a_k - k`. Accumulating frequency counts requires 64-bit integers (`long long`) to prevent overflow from up to `N * (N - 1) / 2 ~ 2 * 10^10` pairs.

## Code Spotlight

```cpp
map<int, int> freq;
long long ans = 0;
for (int i = 0; i < n; i++) {
    int diff = a[i] - i;
    ans += freq[diff];
    freq[diff]++;
}
```

## Example

Input: `a = [3, 5, 1, 4, 6, 6]` (0-indexed: `i = 0, 1, 2, 3, 4, 5`)  
Transformed keys `a[i] - i`: `[3, 4, -1, 1, 2, 1]`  
Output: `1` (pair `(3, 5)` where `diff = 1`)  
Why: Positions with identical `a[i] - i` values change at the exact same rate as their indices, satisfying `a_j - a_i = j - i`.

---

**Generated:** 2026-09-19
