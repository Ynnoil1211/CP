# Pattern: Knapsack DP

## Pattern Name: **Knapsack DP** (0/1 and Unbounded)

### Description

You have items with weight/value (or cost/benefit) and a **capacity / target**. Decide which items to take. The **0/1** version uses each item at most once; the **unbounded** version allows unlimited reuse — and that one difference changes the iteration order of your loop.

The mental shift: the state is _how much capacity you've used up_, and each item asks one question per budget: **"would taking me beat not taking me, at this capacity?"**

### When to recognize it

- "subset that sums to X", "capacity", "budget", "target sum"
- Items can or can't repeat
- "partition into two equal subsets", "fewest coins", "ways to reach a target"

### The General Template

**State:**

```
dp[cap] = best value (or # ways, or reachability) using capacity cap
        (optionally dp[i][cap] when the item index must be tracked explicitly)
```

**Base case:**

```
dp[0] = 0 (or true / 1 way)
```

**Transition:**

```
// 0/1 — iterate capacity BACKWARDS so each item is used at most once
for each item (w, v):
    for cap from target down to w:
        dp[cap] = max(dp[cap], dp[cap - w] + v)

// Unbounded — iterate capacity FORWARDS so items can be reused
for each item (w, v):
    for cap from w to target:
        dp[cap] = max(dp[cap], dp[cap - w] + v)
```

**Answer:** `dp[target]`.

**Complexity:** O(n · target) time, O(target) space.

> **🔑 Key detail:** The iteration direction IS the 0/1-vs-unbounded switch. Backwards = each item taken once. Forwards = unlimited reuse. Coin Change (unbounded, min coins) and Partition Equal Subset Sum (0/1, reachability) are the same code with the loop flipped.

### The core intuition to keep

Every capacity value is a "budget", and each item is a yes/no question per budget. Because you sweep budgets in a specific direction, the same array `dp` encodes either "this item already used" or "this item reusable" — **the loop direction is the whole trick.** A third dimension appears when items have two costs (e.g. Ones and Zeroes: `dp[zeros][ones]`).

### 🟢 Solved Problems

| ID  | Title                                           | Confidence | Core idea                                                                                    |
| --- | ----------------------------------------------- | ---------- | -------------------------------------------------------------------------------------------- |
| 322 | [Coin Change](322_Coin_Change.md) | 10/10      | Min: `dp[i] = min over coins c ≤ i of (dp[i-c] + 1)` — unbounded knapsack, -1 if unreachable |
| 377 | [Combination Sum IV](377_Combination_Sum_IV.md) | 10/10 | Count: `dp[i] = sum over nums x ≤ i of dp[i-x]` — counting variant, `dp[0] = 1` (empty way) |

> 🏆 **Family mastered after 08-04: 322 (10/10, re-solved 3:42) and 377 (10/10, re-solved 2:06).** The base-case rules are reflex-level now: counting → `dp[0] = 1` (empty way), cost → `dp[0] = 0`. Next: 518 - Coin Change II (loop-flip) or 416 (0/1, backward).

### ⏳ Next up

- [416 - Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) (0/1, reachability) → [494 - Target Sum](https://leetcode.com/problems/target-sum/) (0/1, counting) → [474 - Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/) (two capacities)
- [518 - Coin Change II](https://leetcode.com/problems/coin-change-ii/) — counting but order doesn't matter → **flip the loops** (coins outer). The one structural difference 377 taught you to look for
