# 746 - Min Cost Climbing Stairs

**Pattern Type:** Linear DP
**Difficulty:** Easy (warm-up for Medium)
**LeetCode Link:** https://leetcode.com/problems/min-cost-climbing-stairs/
**Topics:** Fibonacci-style DP, cost minimization, 1D state

## Problem Statement

Each step `i` has a cost `cost[i]`. You can start from step 0 **or** step 1. When you pay the cost at step `i`, you can climb 1 or 2 steps forward. Find the minimum cost to reach the **top** (the floor past the last element).

**Constraints:**

- `2 ≤ cost.length ≤ 1000`
- `0 ≤ cost[i] ≤ 999`

## State Definition

### What is dp[i]?

```
dp[i] = minimum total cost to reach step i (you must pay cost[i] when landing here)
```

**Examples:**

- `dp[0] = cost[0]` — only way to start at step 0 is to pay its cost
- `dp[1] = cost[1]` — only way to start at step 1 is to pay its cost
- `dp[2] = cost[2] + min(dp[1], dp[0])` — reach step 2 from step 1 (1-step) or step 0 (2-step), pay cost[2]

### Why This State?

Same structure as Climbing Stairs (dp[i] depends on dp[i-1] and dp[i-2]), but instead of **counting ways**, we're **minimizing cost**. The cost is additive — each step you land on adds its cost to the total. This is a classic "min-path-on-a-line" pattern.

## Recurrence Relation

```
dp[i] = cost[i] + min(dp[i-1], dp[i-2])

Base cases:
  dp[0] = cost[0]
  dp[1] = cost[1]

Answer:
  min(dp[n-1], dp[n-2])   — you can land on either of the last two steps, then jump past the top
```

### Transition Logic

**Step 1:** To land on step `i`, you must come from step `i-1` (1-step) or step `i-2` (2-step).

**Step 2:** You want the **cheapest** way to reach step `i`. The total cost = cost[i] (paid on arrival) + cheapest way to reach the previous step.

**Step 3:** You don't _have_ to land on the last step. If you take a 2-step from step `n-2`, you leapfrog step `n-1` entirely. So the answer is the min of the last two states.

### Example Walkthrough

Input: `cost = [10, 15, 20]`

```
dp[0] = 10                         (start at step 0)
dp[1] = 15                         (start at step 1 — cheaper!)
dp[2] = 20 + min(dp[1], dp[0])     = 20 + min(15, 10) = 20 + 10 = 30

Answer = min(dp[2], dp[1]) = min(30, 15) = 15
```

Why 15? Start at step 1 (pay 15), take a 2-step to the top (skip step 2 entirely). You never pay cost[20].

Input: `cost = [1, 100, 1, 1, 1, 100, 1, 1, 100, 1]`

```
dp[0] = 1
dp[1] = 100       (expensive start)
dp[2] = 1 + min(100, 1) = 2       (1 + 1)
dp[3] = 1 + min(2, 100) = 3       (1 + 2)
dp[4] = 1 + min(3, 2)   = 3       (1 + 2)
dp[5] = 100 + min(3, 3) = 103     (100 + 3)
dp[6] = 1 + min(103, 3) = 4       (1 + 3)
dp[7] = 1 + min(4, 103)  = 5      (1 + 4)
dp[8] = 100 + min(5, 4)  = 104    (100 + 4)
dp[9] = 1 + min(104, 5)  = 6      (1 + 5)

Answer = min(dp[9], dp[8]) = min(6, 104) = 6
```

Path: step 0 (pay 1) → step 2 (pay 1) → step 4 (pay 1) → step 6 (pay 1) → step 7 (pay 1) → step 9 (pay 1) → top. Total = 6.

## Implementation (C++)

```cpp
// Bottom-up with array
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n, 0);
    dp[0] = cost[0];
    dp[1] = cost[1];
    for (int i = 2; i < n; i++) {
        dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
    }
    return min(dp[n-1], dp[n-2]);
}
```

```cpp
// Space-optimized (O(1) memory)
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    int prev2 = cost[0];  // dp[i-2]
    int prev1 = cost[1];  // dp[i-1]
    for (int i = 2; i < n; i++) {
        int cur = cost[i] + min(prev1, prev2);
        prev2 = prev1;
        prev1 = cur;
    }
    return min(prev1, prev2);
}
```

```cpp
// Top-down memoization (your second solution)
unordered_map<int,int> memo;
int solve(vector<int>& cost, int n) {
    if (n == 1 || n == 0) return cost[n];
    if (n < 0) return 0;
    if (memo.count(n)) return memo[n];
    memo[n] = cost[n] + min(solve(cost, n-1), solve(cost, n-2));
    return memo[n];
}
int minCostClimbingStairs(vector<int>& cost) {
    return min(solve(cost, cost.size()-1), solve(cost, cost.size()-2));
}
```

**Key Implementation Notes:**

- The recurrence is identical to Climbing Stairs, but with `min()` instead of `+` and adding `cost[i]` at each step
- Start from cost[0] or cost[1] — you choose the cheaper starting point implicitly via the final `min(dp[n-1], dp[n-2])`
- Since n ≥ 2, both dp[0] and dp[1] are always valid
- The top is **past** the last index — you never pay cost[n], you just need to get there

## Complexity Analysis

- **Time:** O(n)
  - Reason: One pass through the array, each step O(1) work.
- **Space:** O(1) with space-optimized version, O(n) with array or memoization stack.

## Why This Approach Works

By induction on `i`: Suppose `dp[i-1]` and `dp[i-2]` correctly represent the minimum cost to reach steps `i-1` and `i-2`. To reach step `i`, you must come from `i-1` or `i-2`. The cheapest way to reach `i` is `cost[i]` plus the cheaper of the two predecessors. This holds because costs are non-negative and additive, and the two options cover all possible paths to `i`.

The answer `min(dp[n-1], dp[n-2])` works because once you're at `n-2`, you can take a 2-step directly to the top (landing past the array) without paying `cost[n-1]`. So the minimum cost to escape past the array is the minimum cost to reach either of the last two steps.

## Common Pitfalls in This Pattern

- **Forgetting the answer is `min(dp[n-1], dp[n-2])`**: If you return `dp[n-1]`, you force landing on the last step, which may be more expensive than skipping it.
- **Starting from dp[0] only**: The problem allows starting from step 0 OR step 1. The recurrence handles this naturally if you set both bases correctly.
- **Confusing "top" with "last step"**: The top is past the last element. You never need to land on a non-existent step n; you just need to leave from n-1 or n-2.

## Pattern Connection

**This is a Linear DP problem because:**

1. **1D state**: dp[i] depends only on i (the current step), with a single dimension.
2. **Sequential decision**: At each step, the only decision is "where did I come from?" — summarized by the minimum cost of the two previous states.
3. **Min-over-previous pattern**: Like House Robber's `max()`, this uses `min()` over the last two states — a common variant where the recurrence selects the optimal predecessor.

**Similar problems in this pattern:**

- [70 - Climbing Stairs](linear-dp/70_Climbing_Stairs.md) — same recurrence, but counting ways instead of minimizing cost
- 198 - House Robber — same sequential structure, but "take or skip" instead of "add cost"
- 120 - Triangle — minimum path sum from top to bottom (2D but similar additive cost idea)

## Key Takeaway

_"Min Cost Climbing Stairs = Climbing Stairs with cost[i] added and min() instead of +. Spot the Fibonacci skeleton, then adapt the operation."_

## Your Code

```cpp
// Solution 1: Bottom-up iterative
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n+1,0);
    dp[0] = cost[0];
    dp[1] = cost[1];
    for(int i = 2; i<n; i++){
        dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
    }
    return min(dp[n-1], dp[n-2]);
}

// Solution 2: Top-down memoization
class Solution {
public:
    unordered_map<int,int> memo;
    int solve(vector<int>& cost, int n) {
        if(n==1 || n==0) return cost[n];
        if(n<0) return 0;
        if(memo.count(n)) return memo[n];
        memo[n] = cost[n] + min(solve(cost, n-1), solve(cost, n-2));
        return memo[n];
    }
    int minCostClimbingStairs(vector<int>& cost) {
        return min(solve(cost, cost.size()-1), solve(cost, cost.size()-2));
    }
};
```

```cpp
// Re-solve attempt 2026-08-01 — BUGGY: three state bugs in one submission
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp (n+1,0);
        dp[0] = cost[0];
        dp[1] = min(cost[0],cost[1]);  // ❌ inconsistent state: dp[0] means "cost to stand on step 0",
                                       //    but dp[1] means "cheapest way to reach step 1" — two definitions at once
        for(int i = 2; i<=n; i++){
            dp[i] = cost[i]+min(dp[i-1], dp[i-2]);  // ❌ cost[n] is out of bounds when i == n
        }
        return dp[n-1];  // ❌ the top is step n (past the last stair); correct answer = min(dp[n-1], dp[n-2])
    }
};
```

_This re-solve attempt is preserved — it's the perfect example of a **state-definition bug** (see Solve Metrics). The diagnosis you made yourself was correct: when the recurrence doesn't match the base cases, check the state definition first._

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** Not specified (but understood both approaches)
- **Attempts:** N/A
- **Confidence:** 9/10 — REDEMPTION COMPLETE
- **Struggles:** Still building DP intuition — the recurrence clicked when you saw the pattern connection to Climbing Stairs
- **Submitted:** 2026-07-27
- **Last Reviewed:** 2026-08-04
- **Next Review:** **Mastered.** Re-solved 2026-08-04 in **3:13** (9/10): wrote the base case from memory, got it wrong AGAIN (dp[1] = min(cost[0], cost[1])), thought about the state, fixed it, AC. The habit is forming: base case → state check → code.

**Re-solve Log:**

- 2026-08-01: **STUCK.** Wrote `dp[1] = min(cost[0], cost[1])` (two state definitions at once), `cost[i]` at `i == n` (out of bounds), `return dp[n-1]` (wrong answer index). Your own takeaway was the right one: **"check my dp's state for debug."** With `dp[i] = min cost to reach step i, paying cost[i] when you land`: base cases are `dp[0] = cost[0]`, `dp[1] = cost[1]`, loop only `i < n`, answer `min(dp[n-1], dp[n-2])`. Confidence 5 → 4/10.
- 2026-08-04: 3:13, 9/10 — same base-case reflex error, caught it faster by thinking about the state. Confidence 4 → 9/10.

---

**Generated:** 2026-07-27
