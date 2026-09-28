# RPC 2026-09 L - Locate Tobby’s nest

**Type:** Graph / Tree Algorithms
**Rating / Context:** Div 2C (UTP Open 2026)
**Tag:** tree-center-jordan-theorem-gradient-backtrack

## Key Insight

💡 Every tree has 1 or 2 centers located at the exact midpoint of any diameter (Jordan's Theorem, 1869); find diameter via two BFS runs and backtrack from `B` towards `A` using distance gradient.

## Pattern Trigger

"Grid maze where open cells `.` form a free connected tree (no cycles), find cell minimizing maximum distance to any cell."

## Breakthrough

Backtrack from `B` to `A` without storing parent pointers by simply stepping to any orthogonal neighbor with distance `d[u] - 1`, and strictly enforce the author's tie-break rule: smaller column first, then smaller row.

## Code Spotlight

```cpp
pair<int, int> cur = B, c1, c2;
while (true) {
    if (d[cur.r][cur.c] == (D + 1) / 2) c2 = cur;
    if (d[cur.r][cur.c] == D / 2) { c1 = cur; break; }
    for (int i = 0; i < 4; ++i) {
        int nr = cur.r + dr[i], nc = cur.c + dc[i];
        if (valid(nr, nc) && d[nr][nc] == d[cur.r][cur.c] - 1) {
            cur = {nr, nc}; break;
        }
    }
}
auto ans = (D % 2 == 0) ? c1 : tie_break(c1, c2);
```

## Example

Input: Maze grid with odd diameter `D`
Output: `Case 1: r c`
Why: Center candidate with smaller column index is selected to break the tie.

---

**Generated:** 2026-09-26
