# RPC 2026-09 K - K-th shortest path

**Type:** Graph / Shortest Path
**Rating / Context:** Div 2D / Div 1B (UTP Open 2026)
**Tag:** iterative-dijkstra-edge-exclusion

## Key Insight

💡 Under the problem rule that the k-th path cannot share ANY edge with the preceding `k - 1` paths, iteratively run Dijkstra `K` times, disabling all edges of each found shortest path.

## Pattern Trigger

"`k`-th shortest path definition explicitly states no edge from paths `1, 2, ..., k - 1` may be reused, `K <= 10`."

## Breakthrough

Edge weights reach `10^8` and `N <= 10^4`, so path length reaches `10^12`; using `int` and `inf = 1e9` causes fatal overflow and incorrect paths; all distances must be `long long` with `INF = 1e18`.

## Code Spotlight

```cpp
for (int step = 1; step < k; ++step) {
    dijkstra(s, n);
    int cur = d;
    while (cur != s && cur != -1) {
        int p = parent_node[cur], edge_id = parent_edge_id[cur];
        disable_edge(p, cur, edge_id);
        cur = p;
    }
}
dijkstra(s, n);
```

## Example

Input: Graph with `K = 5, S = 3, D = 6`
Output: `153
3 - 5 - 6`
Why: Successive shortest paths 1 through 4 have their edges stripped, leaving path `3 - 5 - 6` as the 5th shortest path.

---

**Generated:** 2026-09-26
