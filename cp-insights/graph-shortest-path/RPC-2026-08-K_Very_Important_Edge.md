# RPC 2026-08 K - Very Important Edge

**Type:** Graph / Shortest Path
**Rating:** 2000
**Tag:** mst-replacement-dsu-jump

## Key Insight

💡 Removing a non-tree edge leaves the MST unchanged; removing a tree edge $e \in T$ requires replacing it with the minimum non-tree edge $e'$ crossing the cut, found by DSU path compression along $T$.

## Pattern Trigger

"Find maximum MST weight after deleting any single edge in a 2-edge-connected graph ($N \le 10^5, M \le 10^6$)." Deleting an edge $e$ in an MST splits the tree into two connected components requiring a minimal replacement cross-edge.

## Breakthrough

Sort non-tree edges by weight; the first non-tree edge $(u, v)$ covering a tree edge provides its optimal replacement. DSU compresses covered tree paths so each tree edge is updated at most once, achieving $O(M \log M)$ overall.

## Code Spotlight

```cpp
for (const auto& e : non_tree_edges) {
    int u = find_up(e.u), v = find_up(e.v);
    while (u != v) {
        if (depth[u] < depth[v]) swap(u, v);
        replacement[parent_edge[u]] = e.w;
        dsu_up[u] = find_up(parent_node[u]);
        u = dsu_up[u];
    }
}
// Best answer: max_{e in MST} (mst_weight - e.w + replacement[e])
```

## Example

Input: Triangle graph with edges $(1-2, w=1)$, $(2-3, w=2)$, $(1-3, w=5)$.
- MST has edges $(1-2)$ and $(2-3)$, weight = 3.
- Remove $(1-2)$: replacement is $(1-3, w=5) \implies 3 - 1 + 5 = 7$.
- Remove $(2-3)$: replacement is $(1-3, w=5) \implies 3 - 2 + 5 = 6$.
Max new MST weight = 7.
Output: `7`
Why: Cutting an MST edge creates a 2-component cut; the cheapest non-tree edge spanning the cut restores connectivity.

---

**Generated:** 2026-09-13
