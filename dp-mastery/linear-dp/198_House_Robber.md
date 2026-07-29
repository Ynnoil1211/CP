# 198 - House Robber

**Pattern Type:** Linear DP
**Difficulty:** Medium (warm-up classification: Easy)
**LeetCode Link:** https://leetcode.com/problems/house-robber/
**Topics:** Include/skip decision, 1D state, max-over-previous

## Problem Statement

Given an array `nums` where `nums[i]` is the money at house `i`, rob the maximum amount without robbing **adjacent** houses.

**Constraints:**
- `1 ≤ nums.length ≤ 100`
- `0 ≤ nums[i] ≤ 400`

## State Definition

### What is dp[i]?

```
dp[i] = maximum amount that can be robbed considering houses 0..i (inclusive)
```

**Examples:**
- `dp[0] = nums[0]` — only one house, must rob it
- `dp[1] = max(nums[0], nums[1])` — two houses, can only rob one of them (adjacent)
- `dp[2] = max(dp[1], nums[0] + nums[2])` — either skip house 2 (dp[1]) or rob it + dp[0]

### Why This State?

At each house `i`, you have exactly **two options**:
1. **Skip** house `i` → the max is `dp[i-1]` (same as what you had up to the previous house)
2. **Rob** house `i` → you get `nums[i]` + the max up to house `i-2` (because `i-1` is adjacent and can't be robbed)

This is the classic **include/skip** pattern — the fundamental structure that separates House Robber from the Fibonacci-style problems.

## Recurrence Relation

```
dp[i] = max(dp[i-1], dp[i-2] + nums[i])

Base cases:
  dp[0] = nums[0]
  dp[1] = max(nums[0], nums[1])

Answer:
  dp[n-1]   (or equivalently max(dp[n-1], dp[n-2]) which is the same)
```

### Transition Logic

**Step 1:** At house `i`, look at the two options:

| Option | Expression | Why |
|--------|-----------|-----|
| Skip house i | `dp[i-1]` | Best value up to i-1, no change |
| Rob house i | `dp[i-2] + nums[i]` | Must skip i-1, add current house's value |

**Step 2:** Choose the maximum of the two. This is a local decision with global optimality — the "optimal substructure" of DP.

**Step 3:** The recurrence avoids double-counting because the two options are mutually exclusive and cover all possibilities. Either you include house `i` (and exclude `i-1`) or you don't.

### Example Walkthrough

Input: `nums = [2, 7, 9, 3, 1]`

```
dp[0] = 2                                    (rob house 0)
dp[1] = max(2, 7) = 7                        (rob house 1 instead)
dp[2] = max(dp[1]=7, dp[0]+9=2+9=11) = 11   (rob houses 0 and 2: 2+9=11)
dp[3] = max(dp[2]=11, dp[1]+3=7+3=10) = 11  (skip house 3 — robbing it gives less)
dp[4] = max(dp[3]=11, dp[2]+1=11+1=12) = 12  (rob houses 0, 2, 4: 2+9+1=12)

Answer: dp[4] = 12
```

Path: house 0 (2) → skip 1 → house 2 (9) → skip 3 → house 4 (1) = 12.

Why not house 1 (7)? Because 7 + 1 = 8 < 12. Better to take 2 + 9 + 1.

## Implementation (C++)

```cpp
// Bottom-up with array
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    
    vector<int> dp(n, 0);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
    }
    return dp[n-1];
}
```

```cpp
// Space-optimized (O(1) memory)
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    
    int prev2 = nums[0];          // dp[i-2]
    int prev1 = max(nums[0], nums[1]);  // dp[i-1]
    
    for (int i = 2; i < n; i++) {
        int cur = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}
```

**Key Implementation Notes:**
- The recurrence only needs the last **two** dp values — `O(1)` space is always possible
- Handle `n == 1` early to avoid out-of-bounds on `nums[1]`
- Your `return max(dp[n-1], dp[n-2])` is correct but redundant — `dp` is non-decreasing so `dp[n-1] ≥ dp[n-2]` always holds
- The `dp(n+1, 0)` allocation is slightly wasteful (one unused slot at index n) but harmless

## Complexity Analysis

- **Time:** O(n)
  - Reason: One pass, O(1) work per house.
- **Space:** O(1) with optimized version, O(n) with full array.

## Why This Approach Works

**Induction argument:** For house `i`, assume `dp[i-1]` correctly represents the optimal solution for houses `0..i-1` and `dp[i-2]` for houses `0..i-2`.

Any optimal solution for houses `0..i` either:
- **Doesn't include house i** → it's also optimal for houses `0..i-1`, so value = `dp[i-1]`
- **Includes house i** → it must exclude house `i-1`, so it's `nums[i]` + optimal for houses `0..i-2` = `dp[i-2] + nums[i]`

Taking the max of these two gives the optimal for houses `0..i`. By induction, the recurrence holds for all `i`.

## Common Pitfalls in This Pattern

- **Starting with dp[0] = nums[0], dp[1] = nums[1]** (both robbed) — Wrong! dp[1] must be `max(nums[0], nums[1])` because you can't rob both.
- **Forgetting the skip option**: Some beginners only consider `dp[i-2] + nums[i]` and forget `dp[i-1]`, which means they miss the case where skipping the current house is better.
- **Not handling n=1 edge case**: If `nums` has only 1 element, accessing `nums[1]` is out of bounds.

## Pattern Connection

**This is a Linear DP problem because:**

1. **1D state**: dp[i] depends only on a single index i.
2. **Include/skip decision**: The hallmark of this variant — at each position, you choose between taking the current element (and skipping the previous) or passing on it.
3. **Two previous states needed**: dp[i-1] (skip) vs dp[i-2] + value (include). Same spatial structure as Climbing Stairs, different operation.

**Similar problems in this pattern:**
- [70 - Climbing Stairs](linear-dp/70_Climbing_Stairs.md) — same `dp[i-1] + dp[i-2]` skeleton but counting ways
- [746 - Min Cost Climbing Stairs](linear-dp/746_Min_Cost_Climbing_Stairs.md) — same skeleton with cost minimization
- 213 - House Robber II — same logic but houses are in a circle
- 740 - Delete and Earn — transformed into House Robber after frequency mapping

### The Three Fundamental Linear DP Operations

| Problem | Operation | Recurrence |
|---------|-----------|------------|
| Climbing Stairs | Sum (count ways) | `dp[i] = dp[i-1] + dp[i-2]` |
| Min Cost Climbing | Min (cheapest path) | `dp[i] = cost[i] + min(dp[i-1], dp[i-2])` |
| House Robber | Max (best value) | `dp[i] = max(dp[i-1], dp[i-2] + nums[i])` |

Same skeleton, three different operations. **This is the core of Linear DP.**

## Key Takeaway

*"For any sequential include/skip problem, define dp[i] as 'best value considering items 0..i', then at each step decide: skip (keep dp[i-1]) or take (dp[i-2] + value[i]). Always think: what are the options at index i?"*

## Your Code

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1,0);
        if(n==1) return nums[0];
        if(n==2) return max(nums[0], nums[1]);
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        for(int i = 2; i<n; i++){
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
        }
        return max(dp[n-1],dp[n-2]);
    }
};
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** ~30 minutes
- **Attempts:** 1 (with hint on dp[i] meaning)
- **Confidence:** 7/10
- **Struggles:** Needed a hint to define `dp[i]` — once the state meaning clicked, the recurrence followed naturally
- **Breakthrough Realization:** *"Always think about the options I have on each ith"* — this is the core of DP. At every i, ask: what choices do I have? That gives you the recurrence.
- **Submitted:** 2026-07-27
- **Last Reviewed:** 2026-07-27
- **Next Review:** 2026-07-30 (Day 3) — re-solve from scratch, timing yourself

---

**Generated:** 2026-07-27
