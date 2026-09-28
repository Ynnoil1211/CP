# RPC 2026-09 G - Guanex y el diámetro con actualizaciones

**Type:** Graph / Tree Algorithms
**Rating / Context:** Div 1B / Div 2D (UTP Open 2026)
**Tag:** dynamic-tree-diameter-binary-lifting

## Key Insight

💡 When appending a new leaf `x` to an existing tree, the new diameter can only be `max(diam, dist(x, A), dist(x, B))`, updating at most one diameter endpoint in `O(log V)` via Binary Lifting LCA.

## Pattern Trigger

"Tree starts with `N` nodes, followed by `Q <= 10^5` online leaf additions, report updated tree diameter after each insertion."

## Breakthrough

In any tree, the furthest node from any arbitrary vertex `x` is always at least one of the endpoints of any diameter; full BFS recomputations are completely avoided.

## Code Spotlight

```cpp
depth[x] = depth[y] + 1;
up[x][0] = y;
for (int i = 1; i < LOG; ++i) up[x][i] = up[up[x][i - 1]][i - 1];
int da = dist(x, A), db = dist(x, B);
if (da > diam && da >= db) { diam = da; B = x; }
else if (db > diam) { diam = db; A = x; }
cout << diam << "\n";
```

## Example

Input: Initial star/path tree with diameter ends `A, B`, add leaf `x` attached to `y`
Output: Updated diameter integer
Why: If `dist(x, A) > diam`, endpoint `B` is replaced by `x` and new diameter is `dist(x, A)`.

---

**Generated:** 2026-09-26
