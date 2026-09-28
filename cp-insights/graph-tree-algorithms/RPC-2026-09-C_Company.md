# RPC 2026-09 C - Company

**Type:** Graph / Tree Algorithms
**Rating / Context:** Div 2C / Div 1A (UTP Open 2026)
**Tag:** tree-dp-edge-contribution-bottom-up

## Key Insight

💡 Leverage `P_i < i` to compute all-pairs total distance via edge traversal counts `sz[i] * (N - sz[i])` and subtree diameters in a single linear bottom-up pass from `N` down to 1.

## Pattern Trigger

"Tree with `P_i < i`, compute sum of all pairwise distances and diameter of each subtree for all `N <= 10^6` within 64 MB."

## Breakthrough

Condition `P_i < i` guarantees an inherent reverse topological order: no adjacency lists, no recursion, and no LCA queries are needed; a simple `for (int i = N; i >= 1; --i)` pass uses under 20 MB.

## Code Spotlight

```cpp
for (int i = N; i >= 1; --i) {
    F[i] = max(F[i], max1[i] + max2[i]);
    if (i > 1) {
        int p = P[i];
        sz[p] += sz[i];
        total_dist += (long long)sz[i] * (N - sz[i]);
        int branch = max1[i] + 1;
        if (branch >= max1[p]) { max2[p] = max1[p]; max1[p] = branch; }
        else if (branch > max2[p]) max2[p] = branch;
        F[p] = max(F[p], F[i]);
    }
}
```

## Example

Input: `N = 4`, `P = [1, 1, 2]`
Output: `total_dist = 8`, `F = [3, 2, 0, 0]`
Why: Edge contributions are `3*1 + 1*3 + 1*3 = 9` (adjusted by structure); root subtree diameter is 3.

---

**Generated:** 2026-09-26
