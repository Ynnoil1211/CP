# 1157E - Minimum Array

**Type:** Greedy / Priority-Based
**Rating:** 1700
**Tag:** multiset-greedy-matching

## Key Insight

💡 Greedily pick the complement $n - a_i$ using `b.lower_bound(n - a_i)` to minimize $(a_i + b_j) \pmod n$; if none is found, wrap around to `b.begin()`.

## Breakthrough

`std::lower_bound(b.begin(), b.end(), x)` on a `multiset` is an $O(n)$ linear scan because set iterators are bidirectional; always use the member method `b.lower_bound(x)` for $O(\log n)$ tree traversal.

## Code Spotlight

```cpp
auto low = b.lower_bound(n - a[i]);
if (low == b.end()) low = b.begin();
cout << (*low + a[i]) % n << " ";
b.erase(low);
```

## Example

Input:
`n = 4`
`a = [0, 1, 2, 1]`
`b = [3, 2, 1, 0]`

Step-by-step:
1. $a_0 = 0 \implies \text{target } 4 - 0 = 4$. `b.lower_bound(4)` is `end()`, wrap to `begin()` $\implies b_j = 0$, result $(0 + 0) \% 4 = 0$. Remaining $b = \{1, 2, 3\}$.
2. $a_1 = 1 \implies \text{target } 4 - 1 = 3$. `b.lower_bound(3)` finds $3$, result $(1 + 3) \% 4 = 0$. Remaining $b = \{1, 2\}$.
3. $a_2 = 2 \implies \text{target } 4 - 2 = 2$. `b.lower_bound(2)` finds $2$, result $(2 + 2) \% 4 = 0$. Remaining $b = \{1\}$.
4. $a_3 = 1 \implies$ only $1$ left, result $(1 + 1) \% 4 = 2$.
Output: `0 0 0 2`
Why: Each step greedily achieves the best possible remainder $0$ whenever a complement $\ge n - a_i$ exists.

---

**Generated:** 2026-09-13
