# Pattern: 2D Grid / Path DP

## Pattern Name: **2D Grid DP** (a.k.a. Grid Path DP)

### Description

Your state is a **cell `(i, j)` in a grid**, and you fill the table in an order that respects the direction of movement (usually top-left → bottom-right). Each cell's answer depends only on the cells you can *arrive from*.

The mental shift: instead of asking "what paths exist from start to end?" directly, you ask at every cell **"what's the best / how many ways to reach this exact cell?"** — the answer composes from the cells that can step into it.

### When to recognize it

- "grid", "matrix", "move right or down"
- Starting corner to ending corner
- Counting paths / minimum cost path / largest square

### The General Template

**State:**
```
dp[i][j] = # ways (or best score) to reach cell (i, j) from the start
```

**Base case:**
```
dp[0][0] = grid[0][0] (or 1)
First row and first column: only one way in — walk them directly
```

**Transition:**
```
dp[i][j] = combine(dp[i-1][j], dp[i][j-1]) + grid[i][j]
           (with obstacles: dp[i][j] = 0 if cell is blocked)
```

- **Counting:** `dp[i][j] = dp[i-1][j] + dp[i][j-1]`
- **Min path:** `dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])`

**Answer:** `dp[m-1][n-1]`.

**Complexity:** O(m·n) time, O(m·n) space — optimizable to O(n) by keeping only the previous row.

### The core intuition to keep

There are only **two ways into a cell** (from above, from the left) — the grid is a DAG, and you process cells in topological order. The whole pattern is: *identify the arrival edges, handle the first row/column boundary, fill row by row.* Anything fancier (obstacles, multiple players, falling paths) is still this skeleton with extra conditions.

### 🟢 Solved Problems

None yet — this is the next frontier.

### ⏳ Next up

- [62 - Unique Paths](https://leetcode.com/problems/unique-paths/) → [63 - Unique Paths II](https://leetcode.com/problems/unique-paths-ii/) (obstacles) → [64 - Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/) (min flavor)
- [120 - Triangle](https://leetcode.com/problems/triangle/), [931 - Minimum Falling Path Sum](https://leetcode.com/problems/minimum-falling-path-sum/), [221 - Maximal Square](https://leetcode.com/problems/maximal-square/)
