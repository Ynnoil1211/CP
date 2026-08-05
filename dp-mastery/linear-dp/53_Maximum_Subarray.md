# 53 - Maximum Subarray

**Pattern Type:** Linear DP (fixed-offset — Kadane / "extend or restart")
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/maximum-subarray/
**Topics:** "Ending at" state definition, extend-or-restart decision, running max answer

## Problem Statement

Given an integer array `nums`, find the contiguous subarray with the largest sum, and return that sum.

**Constraints:**

- `1 ≤ n ≤ 10⁵`
- `-10⁴ ≤ nums[i] ≤ 10⁴` (negatives exist!)

## State Definition

### What is dp[i]?

```
dp[i] = maximum sum of a contiguous subarray ENDING exactly at index i
        (the subarray MUST include nums[i])
```

**Examples** (nums = [-2, 1, -3, 4]):

- `dp[0] = -2` — the only subarray ending at 0 is [-2]
- `dp[1] = 1` — subarrays ending at 1: [-2,1] = -1, [1] = 1 → max is 1
- `dp[2] = -2` — [-2,1,-3] = -4, [1,-3] = -2, [-3] = -3 → max is -2
- `dp[3] = 4` — best is just [4] (restart!)

### Why This State? — 🔑 "ending at" vs "up to"

Every 1D state you've written before was **"up to i"** (House Robber: *best considering houses 0..i*), where the answer lives in the **last cell**. Kadane needs an **"ending at i"** state: the subarray *must* include `nums[i]`, so it can always extend or restart locally. The consequence: **the answer is `max` over ALL `dp[i]`, not `dp[n-1]`** — `dp[n-1]` is only "the best subarray that happens to end at the last element."

## Recurrence Relation

```
dp[i] = max( dp[i-1] + nums[i] ,   ← extend the best subarray ending at i-1
             nums[i] )             ← restart: start a new subarray at i

Base case:
  dp[0] = nums[0]

Answer:
  max over all i of dp[i]   (NOT dp[n-1]!)
```

### Transition Logic

**Step 1:** At index `i`, the best subarray ending here has exactly two possible histories: it continues the best subarray ending at `i-1` (`dp[i-1] + nums[i]`), or it starts fresh at `i` (`nums[i]`).

**Step 2:** Take the max of the two — the "extend or restart" decision.

**Step 3:** Track a running `mx = max(mx, dp[i])` because the global answer can be any `dp[i]` — the best subarray might end in the middle of the array.

> **🔑 Two 1D state flavors — know which answer you need:**
>
> - **"Up to i"** (House Robber, Climbing Stairs): dp[i] = best considering everything ≤ i → answer = **dp[n-1] / dp[n]**. The best solution may or may not include element i.
> - **"Ending at i"** (Kadane): dp[i] = best solution whose right edge is EXACTLY i → answer = **max over all dp[i]**. You need a running max.
> - **How to tell:** if the recurrence needs "must include the current element" (contiguity), you're in "ending at" territory and must track the max.

### Example Walkthrough

Input: `nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]` (expected answer 6 → [4,-1,2,1])

```
dp[0] = -2
dp[1] = max(-2+1, 1)        = 1
dp[2] = max(1-3, -3)        = -2
dp[3] = max(-2+4, 4)        = 4     ← restart
dp[4] = max(4-1, -1)        = 3
dp[5] = max(3+2, 2)         = 5
dp[6] = max(5+1, 1)         = 6     ← global max
dp[7] = max(6-5, -5)        = 1
dp[8] = max(1+4, 4)         = 5

mx = max(-2,1,-2,4,3,5,6,1,5) = 6
```

Answer: `6` — subarray [4,-1,2,1] ends at index 6, which is why `dp[6]` (not `dp[8]`) holds the answer.

## Implementation (C++)

```cpp
// Your solution — dp array version
int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n + 1, 0);
    dp[0] = nums[0];
    int mx = nums[0];
    for (int i = 1; i < n; i++) {
        dp[i] = max(dp[i - 1] + nums[i], nums[i]);
        mx = max(mx, dp[i]);
    }
    return mx;
}
```

```cpp
// O(1) space — fixed-offset means only dp[i-1] is needed
int maxSubArray(vector<int>& nums) {
    int cur = nums[0], best = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        cur = max(cur + nums[i], nums[i]);   // extend or restart
        best = max(best, cur);
    }
    return best;
}
```

**Key Implementation Notes:**

- **`dp[0] = nums[0]`, not 0** — with negatives, a 0 base would silently produce wrong answers on the first step.
- **The `mx` accumulator is NOT optional** — it's the "answer = max over all ending-at states" requirement, not a micro-optimization.
- Your `dp` array is size `n+1` but you only use `0..n-1` — harmless; the rolling version drops the array entirely (fixed-offset DP needs only the previous state).
- Handles all-negative arrays correctly: `[-2,-1]` → `dp[0] = -2`, `dp[1] = max(-3, -1) = -1` → answer `-1` (the least-bad single element).

## Complexity Analysis

- **Time:** O(n) — one pass, each element processed once.
- **Space:** O(1) with the rolling variable (O(n) if you keep the array).
  - This is a **fixed-offset** linear DP: only `dp[i-1]` is read, so the array is unnecessary — contrast with scan-all-previous problems (LIS, Word Break) where the full array is required.

## Why This Approach Works

By induction on `i`: every subarray ending at `i` either has length 1 (sum `nums[i]`) or extends a subarray ending at `i-1` (sum `dp[i-1] + nums[i]`). These two classes cover all subarrays ending at `i` with no overlap, so `dp[i] = max(nums[i], dp[i-1] + nums[i])` is exact. Every subarray of the whole array ends somewhere, so the global maximum is `max` over all `dp[i]`.

## Common Pitfalls in This Pattern

### 🔴 Returning `dp[n-1]` instead of the running max

The #1 Kadane bug, and the direct consequence of state flavor confusion. `dp[n-1]` = best subarray *ending at the last element* — the true answer can end anywhere. `nums = [1, 2, 3, -100]`: `dp[3] = -94`, but the answer is 6. If you wrote a state and then returned the last cell out of habit ("up to" habit), that's the bug.

### Other Common Mistakes

- **`dp[0] = 0`:** breaks the all-negative case (answer would be 0, but the problem expects the least-bad element, e.g. -1).
- **Forgetting the restart branch:** `dp[i] = dp[i-1] + nums[i]` alone (no `max` with `nums[i]`) turns this into "sum of everything from some fixed start" — wrong whenever a negative prefix drags you down.
- **Confusing with segmentation:** this is NOT scan-all-previous. The contiguity constraint is handled by the "ending at" state itself — one lookback, O(1) space. If you reach for a nested loop here, you've overcomplicated it.
- **`n == 1`:** `dp[0] = nums[0]` and `mx = nums[0]` handle it without special-casing — make sure your loop guards don't skip the single element.

## Pattern Connection

**This is a Linear DP problem (fixed-offset) because:**

1. **1D state**, processed left to right, one lookback (`dp[i-1]` only).
2. **"Ending at i" flavor** — the new state flavor vs your House Robber "up to i" states.
3. **New decision type: extend or restart** — vs House Robber's take/skip.

**The decision table:**

| Problem | State flavor | Decision | Answer |
| --- | --- | --- | --- |
| House Robber (198) | up to i | take / skip | `dp[n-1]` |
| Climbing Stairs (70) | up to i | 1 step / 2 steps | `dp[n]` |
| **Maximum Subarray (53)** | **ending at i** | **extend / restart** | **max over all dp[i]** |

**Similar problems in this pattern:**

- 152 - Maximum Product Subarray — same "ending at i" shape, but negatives can *flip* products, so you must track BOTH `max` and `min` — one dp value is no longer enough. That's the next lesson.
- 918 - Maximum Sum Circular Subarray — Kadane + the circle decomposition trick from 213
- 198 - House Robber — the "up to" contrast problem

## Key Takeaway

_"Kadane: dp[i] = best subarray ENDING at i, decision = extend or restart. The answer is max over ALL dp[i] — never dp[n-1] — and because it's fixed-offset, one rolling variable replaces the array."_

## 🔑 Breakthrough

_"The state flavor was the wall: every 1D state I'd written was 'best up to i' (answer = last cell). Kadane needs 'best ENDING at i' — the subarray must include nums[i] — and then the answer is the max over ALL states, tracked with a running variable. That's why returning dp[n-1] feels right but is wrong. The decision itself ('extend or restart': max(dp[i-1]+nums[i], nums[i])) was easy once the state was right — same story as 746: state first, code follows. 5/10 because the state flavor still isn't automatic; Day 3 re-solve to fix that."_

## Your Code

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1, 0);
        dp[0]=nums[0];
        int mx = nums[0];
        for(int i = 1; i<n; i++){
            dp[i] = max(dp[i-1]+nums[i], nums[i]);
            mx = max(mx, dp[i]);
        }
        return mx;
    }
};
```

_Your original work — correct as submitted, including the running max. The unsteady part was naming the state, not writing it._

## Solve Metrics

- **Solve Time:** 11 minutes
- **Attempts:** — (not reported)
- **Confidence:** 10/10 — REDO CLEARED
- **Struggles:** The state definition ("ending at i" vs the "up to i" you know) — which makes the answer selection (`max` over all `dp[i]`) non-obvious. The extend-or-restart decision itself was fine.
- **Key Lesson:** _"Ending-at states need a running max; up-to states end at the last cell. Ask which flavor you're in before writing the answer line."_
- **Submitted:** 2026-08-01
- **Last Reviewed:** 2026-08-04
- **Next Review:** **Mastered.** Re-solved 2026-08-04 in **1:27** (10/10) — rolling variables, INT_MIN init, running max. Lesson banked: **for max problems, initialize with a LOW value (INT_MIN)**.

**Re-solve Log:**
- 2026-08-04: 1:27, 10/10 — wrote the rolling-variable version (`curr`, `best`) with INT_MIN init, no dp array. Confidence 5 → 10/10.

---

**Generated:** 2026-08-01
