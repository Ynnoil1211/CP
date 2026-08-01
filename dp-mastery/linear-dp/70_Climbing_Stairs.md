# 70 - Climbing Stairs

**Pattern Type:** Linear DP
**Difficulty:** Easy (warm-up for Medium)
**LeetCode Link:** https://leetcode.com/problems/climbing-stairs/
**Topics:** Fibonacci-style DP, 1D state, sequential decisions

## Problem Statement

Count the number of distinct ways to climb a staircase of `n` steps when you can take either 1 or 2 steps at a time.

**Constraints:** 1 ≤ n ≤ 45

## State Definition

### What is dp[i]?

```
dp[i] = number of distinct ways to reach step i from the bottom (step 0)
```

**Examples:**

- `dp[0] = 1` — 1 way to be at the ground (do nothing)
- `dp[1] = 1` — 1 way to reach step 1 (one 1-step)
- `dp[2] = 2` — two ways: (1+1) or (2)

### Why This State?

The problem has **optimal substructure**: the number of ways to reach step `i` depends only on the number of ways to reach the two previous steps, because you can only arrive at step `i` from step `i-1` (taking 1 step) or step `i-2` (taking 2 steps). There's no other way in — this makes a 1D state perfect.

## Recurrence Relation

```
dp[i] = dp[i-1] + dp[i-2]

Base cases:
  dp[0] = 1
  dp[1] = 1
```

### Transition Logic

**Step 1:** To reach step `i`, you must have been at step `i-1` (then take 1 step) **or** step `i-2` (then take 2 steps).

**Step 2:** Every distinct way to reach `i-1` produces a distinct way to reach `i` (by appending a 1-step). Same for `i-2` (by appending a 2-step). Since these sets don't overlap (they end with different moves), we simply add them.

**Step 3:** This is exactly the Fibonacci sequence shifted by one: `fib(2) = 1, fib(3) = 2, fib(4) = 3, ...` = `dp[0]=1, dp[1]=1, dp[2]=2, dp[3]=3, ...`.

### Example Walkthrough

Input: `n = 4`

```
dp[0] = 1   (ground)
dp[1] = 1   (1)
dp[2] = dp[1] + dp[0] = 1 + 1 = 2   (1+1, 2)
dp[3] = dp[2] + dp[1] = 2 + 1 = 3   (1+1+1, 1+2, 2+1)
dp[4] = dp[3] + dp[2] = 3 + 2 = 5   ← answer
```

## Implementation (C++)

```cpp
// Top-down memoization (your approach)
int climbStairs(int n, unordered_map<int,int>& memo) {
    if (n == 0 || n == 1) return 1;
    if (n < 0) return 0;
    if (memo.find(n) == memo.end())
        memo[n] = climbStairs(n-1, memo) + climbStairs(n-2, memo);
    return memo[n];
}
```

```cpp
// Bottom-up (space-optimized) — the cleaner DP pattern
int climbStairs(int n) {
    if (n <= 1) return 1;
    int prev2 = 1, prev1 = 1;  // dp[0], dp[1]
    for (int i = 2; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}
```

**Key Implementation Notes:**

- Top-down recursion is intuitive for the pattern, but the call stack goes O(n) deep
- Bottom-up with two variables is O(1) space — you only ever need the last two values (Fibonacci pattern)
- The answer fits in 32-bit int (n ≤ 45, fib(46) ≈ 1.8B < 2³¹)

## Complexity Analysis

- **Time:** O(n)
  - Reason: Compute dp[i] once for each i from 0 to n, each O(1) work.
- **Space:** O(1) (bottom-up) or O(n) (top-down memoization + recursion stack)
  - The recurrence only needs the last two states, so we can drop the array.

## Why This Approach Works

By induction on `i`: Suppose `dp[i-1]` correctly counts the ways to reach step `i-1`, and `dp[i-2]` for step `i-2`. Every way to reach step `i` ends with either a 1-step (coming from `i-1`) or a 2-step (coming from `i-2`). These are mutually exclusive and cover all possibilities. No move sequence is double-counted because the final move uniquely identifies which previous state it came from. Therefore `dp[i] = dp[i-1] + dp[i-2]` holds for all `i ≥ 2`.

## Common Pitfalls in This Pattern

- **Off-by-one on index**: Forgetting that dp[0] = 1 (or treating n=0 incorrectly). Decide: do you index by "steps climbed" or "current step number"? Be consistent.
- **Thinking it's combinatorial**: Trying to compute factorials or binomial coefficients instead of using DP.
- **Missing overlapping subproblems**: A naive recursive `fib(n-1) + fib(n-2)` without memoization is exponential O(2ⁿ). Always memoize or use bottom-up.

## Pattern Connection

**This is a Linear DP problem because:**

1. **1D state**: The state `dp[i]` depends only on a single integer index `i` representing progress up the stairs.
2. **Sequential decision**: At each step, you only make a local decision (1-step or 2-step), and past decisions are summarized by `dp[i-1]` and `dp[i-2]`.
3. **Fibonacci-like recurrence**: The recurrence only references the immediate previous states, no branching into unrelated subproblems.

**Similar problems in this pattern:**

- 198 - House Robber (same structure, but "take or skip" instead of "1 or 2")
- 746 - Min Cost Climbing Stairs (cost added to each step)
- 1137 - N-th Tribonacci Number (3 previous states instead of 2)

## Key Takeaway

_When you can only take 1 or 2 steps, the number of ways to reach step `i` is just `dp[i-1] + dp[i-2]` — literally the Fibonacci sequence. Spot the Fibonacci pattern immediately in any "1-step or 2-step" problem._

## Your Code

```cpp
class Solution {
public:
    int climbStairs(int n, unordered_map<int,int>& memo) {
        if(n==0 || n==1) return 1;
        if(n<0) return 0;
        if (memo.find(n)==memo.end()){
            memo[n] = (climbStairs(n-1,memo) +climbStairs(n-2,memo));
        }
        return memo[n];
    }
    int climbStairs(int n) {
        unordered_map<int,int> memo;
        return climbStairs(n, memo);
    }
};
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** ~3 minutes (attempted, struggled — got it with help/external)
- **Attempts:** 1
- **Confidence:** 8/10
- **Struggles:** Couldn't get the recurrence on your own in the first 3 minutes; DP intuition not yet automatic. That's normal — this is step 1 of the journey.
- **Submitted:** 2026-07-27
- **Last Reviewed:** 2026-08-01
- **Next Review:** Mastered — re-solved 2026-08-01 in **1.5 minutes** from scratch, no hints. No scheduled re-solve; optional Day 14 touch-up 2026-08-15.

**Re-solve Log:**

- 2026-08-01: 1.5 min, zero hints — Fibonacci is automatic now. Confidence 4 → 8/10.

---

**Generated:** 2026-07-27
