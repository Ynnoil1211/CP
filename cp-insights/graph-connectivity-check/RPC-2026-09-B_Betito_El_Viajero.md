# RPC 2026-09 B - Betito el viajero

**Type:** Graph / Connectivity Check
**Rating / Context:** Div 3A / Div 2A (UTP Open 2026)
**Tag:** grid-flood-fill-bfs-safety

## Key Insight

💡 Compute the reachable connected component size from `*` over open cells `.` using iterative BFS to strictly prevent call stack overflow on `1000 x 1000` grids.

## Pattern Trigger

"Grid of dimensions `R, C <= 1000`, 4-directional movement, count total visitable cells from initial point `*`."

## Breakthrough

Recursive DFS on a `1000 x 1000` grid risks `10^6` stack frames and instant SIGSEGV; an iterative `queue<pair<int,int>>` BFS consumes heap memory safely without recursion limits.

## Code Spotlight

```cpp
queue<pair<int, int>> q;
q.push({start_r, start_c});
grid[start_r][start_c] = '#';
while (!q.empty()) {
    auto [r, c] = q.front(); q.pop();
    ans++;
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr >= 0 && nr < R && nc >= 0 && nc < C && grid[nr][nc] != '#') {
            grid[nr][nc] = '#';
            q.push({nr, nc});
        }
    }
}
```

## Example

Input: `7 7` grid with walls and obstacles starting at `*`
Output: `22`
Why: 22 transitively adjacent `.` cells form the single connected component containing the start point.

---

**Generated:** 2026-09-26
