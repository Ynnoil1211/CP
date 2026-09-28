# RPC 2026-09 F - Flipando colores con la DIAN

**Type:** Greedy / Priority-Based
**Rating / Context:** Div 1C / Div 2E (UTP Open 2026)
**Tag:** lawlers-tree-scheduling-dsu-contraction

## Key Insight

💡 Under tree precedences, the node `u` maximizing density `w_u / p_u` among all nodes with parents must execute immediately after `par(u)`; contract them into a composite macro-node via DSU and a lazy-deletion heap.

## Pattern Trigger

"Tree precedence scheduling `1 | tree-prec | sum w_i C_i` with `N <= 10^6` tasks, duration `p_i` and penalty `w_i`."

## Breakthrough

A naive greedy choice on available roots fails when a slow root blocks an ultra-dense descendant; Lawler's theorem proves contraction must collapse the global max-density child into its current parent.

## Code Spotlight

```cpp
while (!pq.empty()) {
    auto [w, p, u] = pq.top(); pq.pop();
    if (find_set(u) != u || W[u] != w || P[u] != p) continue;
    int par = find_set(parent_tree[u]);
    total_cost += P[par] * W[u];
    P[par] += P[u]; W[par] += W[u];
    parent_dsu[u] = par;
    if (par != 0) pq.push({W[par], P[par], par});
}
```

## Example

Input: `N = 2`, `P = [10, 1]`, `W = [1, 100]`, `2` depends on `1`
Output: `Cost`
Why: Block `(1 o 2)` has combined density `(1 + 100) / (10 + 1) = 101/11`, outranking standalone tasks.

---

**Generated:** 2026-09-26
