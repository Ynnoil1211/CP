# 213 - House Robber II

**Pattern Type:** Linear DP (with circular decomposition)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/house-robber-ii/
**Topics:** Circular array → linear transformation, include/skip decision, 1D state

## Problem Statement

Same as House Robber, but houses are arranged in a **circle** — the first and last houses are adjacent. You still cannot rob two adjacent houses.

**Constraints:**

- `1 ≤ nums.length ≤ 100`
- `0 ≤ nums[i] ≤ 1000`

## State Definition

### What is dp[i]? (same as House Robber I)

```
dp[i] = maximum amount that can be robbed considering houses 0..i (inclusive) in a linear arrangement
```

Same state as HR I. The only new constraint is that house `0` and house `n-1` cannot both be robbed because they're now adjacent (circle).

### The Problem Decomposition

A circle means you can't rob both ends. So you break it into **two linear problems**:

| Scenario            | Range            | Excludes    | Why                              |
| ------------------- | ---------------- | ----------- | -------------------------------- |
| Exclude last house  | `nums[0 .. n-2]` | house `n-1` | First house can be robbed freely |
| Exclude first house | `nums[1 .. n-1]` | house `0`   | Last house can be robbed freely  |

The answer = `max(rob_linear(0, n-2), rob_linear(1, n-1))`

This covers all possibilities: either house 0 is not robbed (second scenario) or it is robbed (first scenario). If house 0 is robbed, house n-1 can't be — so we exclude it from the range.

### Why This State?

The circle adds exactly **one** additional constraint vs. HR I: house 0 and house n-1 conflict. By running HR I on two overlapping linear subarrays, we evaluate both possibilities and take the max. The DP recurrence per subarray is identical to HR I.

## Recurrence Relation

```
rob_linear(l, r):  // standard House Robber I on nums[l..r]
    if (l == r) return nums[l];
    dp[l] = nums[l];
    dp[l+1] = max(nums[l], nums[l+1]);
    for (int i = l+2; i <= r; i++)
        dp[i] = max(dp[i-1], dp[i-2] + nums[i]);
    return dp[r];

answer = max(rob_linear(0, n-2), rob_linear(1, n-1))
```

### Transition Logic

**Step 1:** Understand that in a circle, at most one of the first/last houses can be robbed.

**Step 2:** Create two linear subarrays by removing either the first or last element.

**Step 3:** Run the standard House Robber I DP on each. Take the max.

### Example Walkthrough

Input: `nums = [2, 3, 2]`

```
Scenario 1: exclude last → [2, 3]
  dp[0] = 2
  dp[1] = max(2, 3) = 3
  result = 3

Scenario 2: exclude first → [3, 2]
  dp[1] = 3
  dp[2] = max(3, 2) = 3
  result = 3

Answer = max(3, 3) = 3
```

Input: `nums = [1, 2, 3, 1]`

```
Scenario 1: exclude last → [1, 2, 3]
  dp[0] = 1
  dp[1] = max(1, 2) = 2
  dp[2] = max(dp[1]=2, dp[0]+3=1+3=4) = 4
  result = 4

Scenario 2: exclude first → [2, 3, 1]
  dp[1] = 2
  dp[2] = max(2, 3) = 3
  dp[3] = max(dp[2]=3, dp[1]+1=2+1=3) = 3
  result = 3

Answer = max(4, 3) = 4
```

Path: rob house 0 (1) + house 2 (3) = 4.

## Implementation (C++)

```cpp
// Clean version with helper function
int rob_linear(vector<int>& nums, int l, int r) {
    if (l == r) return nums[l];
    int prev2 = nums[l];
    int prev1 = max(nums[l], nums[l+1]);
    for (int i = l+2; i <= r; i++) {
        int cur = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}

int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);
    return max(rob_linear(nums, 0, n-2), rob_linear(nums, 1, n-1));
}
```

```cpp
// Your approach (two separate dp arrays)
int rob(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp1(n+1,0), dp2(n+1,0);
    if(n==1) return nums[0];
    if(n==2) return max(nums[0],nums[1]);
    dp1[0]=nums[0];
    dp1[1]=max(nums[0],nums[1]);
    dp2[1]=nums[1];
    dp2[2]=max(nums[1],nums[2]);
    for(int i = 2;i<n-1;i++){
        dp1[i]=max(nums[i]+dp1[i-2], dp1[i-1]);
    }
    for(int i = 3;i<n;i++){
        dp2[i]=max(nums[i]+dp2[i-2], dp2[i-1]);
    }
    return max(dp1[n-2],dp2[n-1]);
}
```

**Key Implementation Notes:**

- The helper function avoids duplicating code and makes the logic self-documenting
- When `n == 2`, both scenarios give the same result (`max(nums[0], nums[1])`) — handle early
- dp1 covers range [0, n-2], dp2 covers range [1, n-1]
- Your dp2 starts at index 1 with `dp2[1] = nums[1]` — the loop runs `i = 3` to `n-1` because indices are shifted by 1 vs dp1

## Complexity Analysis

- **Time:** O(n)
  - Reason: Two linear passes of HR I, each O(n). Total O(2n) = O(n).
- **Space:** O(1) with the helper function approach (two variables per pass).
  - Your array version uses O(n) for two dp arrays.

## Why This Approach Works

**Key insight:** In a circle, the constraint is that houses `0` and `n-1` cannot both be robbed. Any valid solution **either** excludes house `n-1` (solving on `[0, n-2]`) **or** excludes house `0` (solving on `[1, n-1]`). These two cases cover all possibilities because:

- If a solution doesn't rob house 0, it's covered by scenario 2
- If a solution robs house 0, it can't rob house n-1, so it's covered by scenario 1

Therefore, taking the max of the two linear solutions yields the optimal circular solution.

## Common Pitfalls in This Pattern

- **Running HR I on the full array**: The whole point of the circle is that end-to-start adjacency matters. You must split.
- **Using `rob_linear(0, n-1)`**: This assumes end-to-start adjacency doesn't exist — wrong for a circle.
- **Forgetting n=1 and n=2 edge cases**: With 1 or 2 houses, there's no circular conflict because you can't have both first and last be distinct and adjacent.
- **Off-by-one on the ranges**: `[0, n-2]` leaves out index n-1; `[1, n-1]` leaves out index 0. Double-check your loop bounds.

## Pattern Connection

**This is a Linear DP problem (with circular decomposition) because:**

1. **Core recurrence is HR I**: Inside each subarray, the `max(skip, take)` pattern is identical to HR I.
2. **Circle → linear trick**: The circular constraint is handled by decomposing into two linear subproblems. This is a general technique for circular arrays — not a different DP pattern.
3. **Still 1D state**: Each subproblem uses a 1D state.

**Similar problems in this pattern:**

- [198 - House Robber I](linear-dp/198_House_Robber.md) — the foundation for this problem
- 918 - Maximum Sum Circular Subarray — same circular decomposition trick
- 740 - Delete and Earn — transforms into HR I after frequency mapping

## Key Takeaway

_"A circular constraint just means 'run the linear DP twice, excluding each endpoint once.' The recurrence stays the same — only the range changes."_

## Your Code

```cpp
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp1(n+1,0), dp2(n+1,0);
        if(n==1) return nums[0];
        if(n==2) return max(nums[0],nums[1]);
        dp1[0]=nums[0];
        dp1[1]=max(nums[0],nums[1]);
        dp2[1]=nums[1];
        dp2[2]=max(nums[1],nums[2]);
        for(int i = 2;i<n-1;i++){
            dp1[i]=max(nums[i]+dp1[i-2], dp1[i-1]);
        }
        for(int i = 3;i<n;i++){
            dp2[i]=max(nums[i]+dp2[i-2], dp2[i-1]);
        }
        return max(dp1[n-2],dp2[n-1]);
    }
};
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** 8 minutes
- **Attempts:** 1 (with a hint on the circular decomposition)
- **Confidence:** 9/10
- **Struggles:** Needed a hint to realize the "two subarrays" trick for the circle. Once you saw that, the DP was straightforward.
- **What you proved:** You've fully internalized House Robber I's recurrence. The hint was about _problem decomposition_, not DP — and that's a separate skill. You'll recognize the circle trick next time.
- **Submitted:** 2026-07-27
- **Last Reviewed:** 2026-08-09
- **Next Review:** **Mastered.** Re-solved 2026-08-09 in ~3 min (9/10) — logic automatic.

**Re-solve Log:**

- 2026-08-01: ~8 min, no hints. One bug: forgot the `n == 1` / `n == 0` base cases before indexing `nums[1]` / `nums[2]` in the two subarray runs — the classic "guard tiny inputs before touching the recurrence" mistake. Decomposition and recurrence were automatic. Confidence stays 8/10.
- 2026-08-09: ~3 min, 9/10 — clean. Confidence 8 → 9/10.

---

**Generated:** 2026-07-27
