# Pattern: Linear / Sequence DP

## Pattern Name: **Linear DP** (a.k.a. Sequence DP, Fixed-Offset DP)

### Description

This is the first DP pattern, and the one that teaches you the core move: **"what are my options at step i?"** You process a linear sequence (array, stairs, houses, fence posts) left to right, and the answer at position `i` depends on a small, **fixed number** of positions right before it — `dp[i-1]`, `dp[i-2]`, maybe `dp[i-k]`.

The mental shift: you don't need to know the whole history. The optimal value / count up to `i-1` already encodes everything about the past that matters. You just combine a *constant number* of already-computed states with one new piece of information (the current element).

### When to recognize it

Ask yourself: *"Does the decision at position i only depend on the last few positions?"* Common signals:

- "adjacent", "consecutive", "can't pick neighbors"
- A 1D array/string processed in order
- The constraint is *local* — no lookback over all earlier states

### The General Template

**State:**
```
dp[i] = the answer considering only the first i elements (steps 0..i)
```

**Base case:**
```
dp[0], dp[1] = values you can compute directly (0, 1, nums[0], ...)
```

**Transition:**
```
dp[i] = f(dp[i-1], dp[i-2], ..., nums[i])
```

Where `f` is one of:
- **Sum (count ways):** `dp[i] = dp[i-1] + dp[i-2]`
- **Min (cheapest):** `dp[i] = cost[i] + min(dp[i-1], dp[i-2])`
- **Max (best value):** `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`

**Answer:** `dp[n]` (or `dp[n-1]`, depending on indexing).

**Complexity:** O(n) time, O(1) space — you only need the last 2 (or k) values, so rolling variables replace the whole array.

> **⚠️ Sub-pattern — Scan-All-Previous Linear DP (LIS-style).** If the condition at `i` isn't a fixed offset but "any earlier `j < i` satisfying condition X" (e.g. `nums[j] < nums[i]`), you're in the *scan-all-previous* variant: `dp[i] = max over all j < i of (dp[j] + 1)` where the condition holds. This needs a **nested loop** (O(n²)) and a full dp array. It is still Linear DP because the state is 1D and the sequence is processed in order — but it is **not** Segmentation DP, because the pieces don't need to be contiguous. Examples: Longest Increasing Subsequence (300), Largest Divisible Subset (368).

### Problem Family (all share this exact skeleton)

| Problem | What `dp[i]` tracks | Transition flavor |
|---|---|---|
| **Climbing Stairs** | # ways to reach step i | Sum |
| **Min Cost Climbing Stairs** | min cost to reach step i | Min |
| **House Robber** | max loot up to house i | Max (take/skip) |
| **House Robber II** | max loot on a circular street | Max + decomposition (circle → 2 runs) |
| **Delete and Earn** | max points using values ≤ x | Max + index-by-value transform |
| **Longest Increasing Subsequence** | longest inc. subsequence ending at i | Max + scan-all-previous |
| **Largest Divisible Subset** | longest chain ending at i | Max + scan-all-previous |

### The core intuition to keep

You're walking the sequence one step at a time, and the past is *compressed*: everything before position `i-2` is already folded into `dp[i-1]` and `dp[i-2]`. You never re-scan history — that's what makes it O(n). The hard part is choosing the right `f`, and the **take-or-skip framing** (`max(dp[i-1], dp[i-2] + nums[i])`) is the single most reusable decision template in all of DP.

### 🟢 Solved Problems

| ID | Title | Confidence | Core idea |
|----|-------|------------|-----------|
| 70 | [Climbing Stairs](../linear-dp/70_Climbing_Stairs.md) | 4/10 | Count ways: `dp[i] = dp[i-1] + dp[i-2]` |
| 746 | [Min Cost Climbing Stairs](../linear-dp/746_Min_Cost_Climbing_Stairs.md) | 5/10 | Min cost: `dp[i] = cost[i] + min(dp[i-1], dp[i-2])` |
| 198 | [House Robber](../linear-dp/198_House_Robber.md) | 7/10 | Max value: `dp[i] = max(dp[i-1], dp[i-2] + nums[i])` |
| 213 | [House Robber II](../linear-dp/213_House_Robber_II.md) | 8/10 | Circle → run the recurrence twice (with / without house 0) |
| 740 | [Delete and Earn](../linear-dp/740_Delete_and_Earn.md) | 6/10 | `points[x] = x * freq[x]`, then House Robber |

**Confidence check:** The House Robber family (198/213/740) is becoming automatic. 70/746 were warm-ups — treat them as the base cases of this pattern when you review.

### ⏳ Next up

- [300 - Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/) — your first scan-all-previous variant
- [368 - Largest Divisible Subset](https://leetcode.com/problems/largest-divisible-subset/) — same shape, new condition
