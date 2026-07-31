# Pattern: Bitmask DP

## Pattern Name: **Bitmask DP** (a.k.a. DP over Subsets)

### Description

The state includes a **bitmask** encoding *which subset of elements has been used*. Transitions add one element to the set. This only works when `n` is small (**≤ 20**), because `2^n` states is the price of admission.

The mental shift: instead of tracking order or counts, **the mask IS the state** — "used these, remaining those". Bit `k` of the mask answers "have I used element k?".

### When to recognize it

- `n ≤ 20` (the hard cutoff — otherwise this pattern is impossible)
- "visit all", "subset", "assignment", "matching", "partition into groups"

### The General Template

**State:**
```
dp[mask] (or dp[mask][i]) = best value having used exactly the elements in mask (ending at i)
```

**Base case:**
```
dp[0] = neutral value (or dp[1<<start][start] = 0)
```

**Transition:**
```
for mask in 0..(1<<n):
    for each i in mask:
        for each j not in mask:
            dp[mask | (1<<j)][j] = min(dp[mask][i] + cost(i, j))
```

**Answer:** `dp[(1<<n) - 1]` (all elements used).

**Complexity:** O(2^n · n²) time, O(2^n · n) space.

### The core intuition to keep

The mask is a compressed "set". Iterate masks in increasing numeric order and every submask is already computed — that's the topological order of subset DP. **When you see `n ≤ 20` and "assign / visit all / split into groups", reach for the mask.**

### 🟢 Solved Problems

None yet — advanced tier.

### ⏳ Next up

- TBD — park this until the core patterns are done. Classic entries: TSP variant, Partition to K Equal Sum Subsets.
