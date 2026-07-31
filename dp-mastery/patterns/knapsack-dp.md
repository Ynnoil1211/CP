# Pattern: Knapsack DP

## Pattern Name: **Knapsack DP** (0/1 and Unbounded)

### Description

You have items with weight/value (or cost/benefit) and a **capacity / target**. Decide which items to take. The **0/1** version uses each item at most once; the **unbounded** version allows unlimited reuse — and that one difference changes the iteration order of your loop.

The mental shift: the state is *how much capacity you've used up*, and each item asks one question per budget: **"would taking me beat not taking me, at this capacity?"**

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

None yet.

### ⏳ Next up

- [416 - Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/) (0/1, reachability) → [494 - Target Sum](https://leetcode.com/problems/target-sum/) (0/1, counting) → [474 - Ones and Zeroes](https://leetcode.com/problems/ones-and-zeroes/) (two capacities)
- [322 - Coin Change](https://leetcode.com/problems/coin-change/) (unbounded, min coins)
