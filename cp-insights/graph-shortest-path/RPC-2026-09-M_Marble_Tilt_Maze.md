# RPC 2026-09 M - Marble tilt maze

**Type:** Graph / Shortest Path
**Rating / Context:** Div 1B / Div 2D (UTP Open 2026)
**Tag:** state-space-grid-bfs

## Key Insight

💡 Unlike classic sliding puzzles, players can stabilize the board after any number of single-step advances, meaning each direction yields multiple directed neighbors of cost 1 in an unweighted 4D state space BFS.

## Pattern Trigger

"Small grid bounds (N, M <= 30), two interacting tokens, board tilts sliding marbles simultaneously until stopped or stabilized, find minimum tilts."

## Breakthrough

Advance marbles in lockstep cell-by-cell prioritizing the marble ahead along the movement vector `(r * dr + c * dc)` (convoy effect) so it vacates its square before the rear marble steps into it, aborting the branch immediately if either marble falls into a hole or off the board.

## Code Spotlight

```cpp
bool first = (a * DR[d] + b * DC[d]) >= (x * DR[d] + y * DC[d]);
while (true) {
    int s1 = first ? step(A, B, d, X, Y) : step(X, Y, d, A, B);
    if (s1 == -1) break;
    int s2 = first ? step(X, Y, d, A, B) : step(A, B, d, X, Y);
    if (s2 == -1 || (s1 == 0 && s2 == 0)) break;
    int k = id(A, B, X, Y);
    if (dist[k] == -1) { dist[k] = cur + 1; q.push({A, B, X, Y}); }
}
```

## Example

Input: `6 8` grid with walls `#`, targets `G`, marbles at `(5, 2)` and `(5, 7)`
Output: `4`
Why: Both marbles reach separate `G` targets after 4 tilts without colliding into walls or falling off bounds.

---

**Generated:** 2026-09-26
