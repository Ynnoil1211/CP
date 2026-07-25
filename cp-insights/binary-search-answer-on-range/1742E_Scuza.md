# 1742E - Scuza

**Type:** Binary Search / Answer on Range
**Rating:** 1200
**Tag:** prefix-max-binary-search

## Key Insight

💡 The limiting factor is the **maximum step height seen so far** (prefix
max), not the current step. Build prefix max array, binary search on it
for each query to find how many steps are passable.

## Code Spotlight

```cpp
pref[i] = pref[i - 1] + a;
mx[i] = max(mx[i - 1], a);
// ...
int last = upper_bound(mx.begin() + 1, mx.end(), k) - mx.begin() - 1;
cout << pref[last] << " ";
```

## Example

Steps: `[1, 2, 1, 5]`, prefix max: `[1, 2, 2, 5]`
Query k=4 → upper_bound finds first >4 at index 4 (value 5)
→ last index = 3 → pref[3] = 1+2+1 = 4
Why: k=4 clears the max prefix height up to step 3 (max=2 ≤ 4),
but fails at step 4 (height 5 > 4).

---

**Generated:** 2026-07-24
