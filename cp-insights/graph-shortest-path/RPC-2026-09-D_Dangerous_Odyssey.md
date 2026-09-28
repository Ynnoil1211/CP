# RPC 2026-09 D - Dangerous Odyssey

**Type:** Graph / Shortest Path
**Rating / Context:** Div 2B / Div 2C (UTP Open 2026)
**Tag:** multi-metric-grid-bfs

## Key Insight

💡 Decouple multi-hazard grid constraints into 3 separate BFS passes: 8D Chebyshev BFS for hazard spread, 4D Manhattan BFS for storm shelters, and 4D pathfinding on navigable water.

## Pattern Trigger

"Hazards propagate diagonally (Chebyshev `L_inf <= H`), ship moves ortogonally and must stay within `L_1 <= D` of a safe island shelter."

## Breakthrough

Islands (`R`) are landmasses that provide shelter radius but cannot be sailed through; ship navigation must be strictly restricted to `.` and arrival at `A`.

## Code Spotlight

```cpp
// Phase 1: 8D BFS for hazards <= H
// Phase 2: 4D BFS from 'Y', 'A', and safe 'R' (danger > H) <= D
// Phase 3: 4D BFS from 'Y' to 'A' traversing only '.' with danger > H and refuge <= D
if (grid[nr][nc] == '.' || grid[nr][nc] == 'A') {
    if (osideo_dist[nr][nc] == -1 && danger_dist[nr][nc] > H && refuge_dist[nr][nc] <= D) {
        osideo_dist[nr][nc] = osideo_dist[r][c] + 1;
        q.push({nr, nc});
    }
}
```

## Example

Input: `grid` with hazards `S`, islands `R`, start `Y`, target `A`
Output: `Dist` or `OSIDEO WILL DIE`
Why: Any path stepping within `H` Chebyshev distance of `S` or exceeding `D` Manhattan distance to safe `R` is pruned.

---

**Generated:** 2026-09-26
