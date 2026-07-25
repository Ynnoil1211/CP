# 1914D - Three Activities

**Type:** Brute Force / Exhaustive Search
**Rating:** 1200
**Tag:** top-k-candidate-reduction

## Key Insight

💡 The optimal triple must draw from the **top 3 values** of each array. Two indices from the other arrays can block at most 2 of a's positions, so at least one of a's top 3 stays available — same for b and c. Keep top 3 per array and brute force all 27 combos.

## Code Spotlight

```cpp
sort(a.rbegin(), a.rend());
sort(b.rbegin(), b.rend());
sort(c.rbegin(), c.rend());

ll ans = 0;
for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
            if (a[i].second != b[j].second
             && a[i].second != c[k].second
             && b[j].second != c[k].second)
                ans = max(ans, a[i].first + b[j].first + c[k].first);
```

## Example

Arrays:
```
a: [10, 8, 7, 1]   → top 3: indices 0(10), 1(8), 2(7)
b: [9,  2, 1, 5]   → top 3: indices 0(9), 3(5), 1(2)
c: [1,  3, 9, 2]   → top 3: indices 2(9), 1(3), 3(2)
```
27 combos checked. Best: a[0]=10, b[0]=9, c[2]=9 → sum=28. All indices distinct (0, 0, 2 — wait, 0 and 2 are distinct from each other)... Actually b[0] and a[0] share index 0 → invalid. The valid best is a[0]=10 + b[3]=5 + c[2]=9 = 24.
Why: You'd never need to look past the top 3 per array — a blocking argument guarantees it.

---

**Generated:** 2026-07-24
