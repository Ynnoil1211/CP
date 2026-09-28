# RPC 2026-09 J - Juan y sus ovejas

**Type:** Graph / Connectivity Check
**Rating / Context:** Div 3A / Div 2A (UTP Open 2026)
**Tag:** dsu-component-count-and-max-size

## Key Insight

💡 Maintain total connected component count and maximum component size dynamically using Disjoint Set Union (DSU) with union by size and path compression.

## Pattern Trigger

"`N <= 10^5` entities, `P <= 2 * 10^5` pairwise relations, count number of classes and size of largest class."

## Breakthrough

Initialize `total = N` and each size `sz[i] = 1`; isolated vertices never mentioned in pairs are automatically preserved as independent classes of size 1.

## Code Spotlight

```cpp
void union_sets(int a, int b) {
    a = find_set(a); b = find_set(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        parent_node[b] = a;
        sz[a] += sz[b];
        max_component_size = max(max_component_size, sz[a]);
        total_components--;
    }
}
```

## Example

Input: `N = 9, P = 6`, pairs: `(4, 7), (5, 3), (2, 5), (6, 8), (1, 5), (4, 5)`
Output: `3 6`
Why: Component `{1, 2, 3, 4, 5, 7}` has size 6, `{6, 8}` has size 2, `{9}` has size 1. Total 3 breeds.

---

**Generated:** 2026-09-26
