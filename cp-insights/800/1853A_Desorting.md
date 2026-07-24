# 1853A - Desorting

**Rating:** 800
**Algorithm:** Greedy / Math

## Key Insight

💡 Find the minimum adjacent difference; each operation widens one specific
gap by 2, so breaking sortedness needs (min_gap/2)+1 operations, or 0 if
already unsorted.

## Code Spotlight

```cpp
int mn = INT_MAX;
for (int i = 1; i < n; i++) {
    mn = min(mn, a[i] - a[i-1]);
}
cout << (mn < 0 ? 0 : mn / 2 + 1) << "\n";
```

## Example

Input: `[1, 3, 3, 5]` → gaps: `[2, 0, 2]`, min gap = 0
Output: `1`
Why: The zero gap means adjacent equal elements; one operation flips
the prefix/suffix and creates `[2, 3, 2, 4]` which is not sorted.

---

**Generated:** 2026-07-23
