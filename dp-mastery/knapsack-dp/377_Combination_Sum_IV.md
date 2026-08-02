# 377 - Combination Sum IV

**Pattern Type:** Knapsack DP (unbounded, counting ways — the `+` operator)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/combination-sum-iv/
**Topics:** Counting DP, last-element decomposition, base-case semantics (1 vs 0), overflow handling

## Problem Statement

Given distinct integers `nums` and a `target`, return the number of possible **sequences** (order matters!) that add up to `target`. Unlimited reuse of each number.

**Constraints:**

- `1 ≤ nums.length ≤ 200`
- `1 ≤ nums[i] ≤ 1000`
- `1 ≤ target ≤ 1000`
- The answer fits in a 32-bit integer (but **intermediate** values may not!)

## State Definition

### What is dp[i]?

```
dp[i] = number of sequences (ordered combinations) of nums that sum to exactly i
```

**Examples** (nums = [1, 2, 3]):

- `dp[0] = 1` — one way to make 0: the **empty sequence** (you're already done)
- `dp[2] = 2` — (1,1) and (2)
- `dp[4] = 7` — (1,1,1,1) (1,1,2) (1,2,1) (1,3) (2,1,1) (2,2) (3,1)

### Why This State?

Same capacity state as Coin Change — but what we store changes. Coin Change stored the _minimum number of coins_ (a cost). Here we store the _number of ways_ (a count). Same skeleton, different meaning of the cell, which changes the combine operator from `min` to `+` and the base case from `0` to `1`.

## Recurrence Relation

```
dp[i] = sum over every x in nums with x ≤ i of ( dp[i - x] )

Base case:
  dp[0] = 1        ← THE base case (one way: the empty sequence)

Answer:
  dp[target]
```

### Transition Logic

**Step 1:** Every sequence summing to `i` ends with some **last element** `x` (any num ≤ i). Remove it: the prefix is a sequence summing to `i - x`.

**Step 2:** **Counting is block addition, not +1 per path.** Each of the `dp[i - x]` existing sequences for `i - x` becomes exactly **one** new sequence for `i` when we append `x`. So we add the _whole block_ `dp[i - x]`, never `+1`.

**Step 3:** Sum over all possible last elements `x` — every sequence has exactly one last element, so nothing is double-counted and nothing is missed.

> **🔑 Counting (`+`) vs cost (`min`) — the base case tells you which you're in:**
>
> - **Counting ways:** `dp[0] = 1` — "one way to do nothing: the empty sequence." Like `0! = 1`. Think of Word Break's `dp[0] = true` — same idea, existence's version of 1.
> - **Min/max cost:** `dp[0] = 0` — "doing nothing costs zero." (Coin Change, Perfect Squares.)
> - **Your bug:** you had the intuition ("get all previous combinations") but with `dp[0] = 0` the chain could never start — `dp[3]`'s combination `(3)` alone needs `dp[3] += dp[3-3] = dp[0] = 1` to be counted. No correct formula can survive a wrong base case.

### Example Walkthrough

Input: `nums = [1, 2, 3]`, `target = 4`

```
dp[0] = 1
dp[1] = dp[0]                                       = 1   → (1)
dp[2] = dp[1] + dp[0]                               = 2   → (1,1) (2)
dp[3] = dp[2] + dp[1] + dp[0]                       = 4   → (1,1,1) (1,2) (2,1) (3)
dp[4] = dp[3] + dp[2] + dp[1]                       = 7   → (1,1,1,1) (1,1,2) (1,2,1) (1,3) (2,1,1) (2,2) (3,1)
```

Answer: `dp[4] = 7` — e.g., the block `dp[3] = 4` means "4 sequences sum to 3"; appending `1` to each gives 4 sequences summing to 4.

## Implementation (C++)

```cpp
// Your solution — unsigned to survive huge intermediate values
int combinationSum4(vector<int>& nums, int target) {
    vector<unsigned int> dp(target + 1, 0);
    sort(nums.begin(), nums.end());
    dp[0] = 1;
    for (int i = 1; i <= target; i++) {
        for (int x : nums) {
            if (x > i) break;            // sorted: everything after is also > i
            dp[i] += dp[i - x];          // block addition — NOT +1 per path
        }
    }
    return dp[target];
}
```

```cpp
// Alternative: clamp at INT_MAX instead of unsigned
int combinationSum4(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    sort(nums.begin(), nums.end());
    dp[0] = 1;
    for (int i = 1; i <= target; i++) {
        for (int x : nums) {
            if (x > i) break;
            if (dp[i] > INT_MAX - dp[i - x]) dp[i] = INT_MAX;  // clamp
            else dp[i] += dp[i - x];
        }
    }
    return dp[target];
}
```

**Key Implementation Notes:**

- **The overflow story is real.** Your adversarial test case: `dp[630] ≈ 4.6 × 10¹⁸` — astronomically above 32-bit — yet `dp[999] = 1`. The DP must compute every intermediate sum; only the _final_ answer is guaranteed to fit. Two safe fixes: `unsigned int` (wrapping mod 2³² preserves the true value, since the final answer fits in 32 bits) or clamping at `INT_MAX` (any value that big can never contribute to a 32-bit answer).
- **No `-1` sentinel needed** — unlike Coin Change, "impossible" here is naturally `0` ways. Counting problems can't have unreachable amounts; they have zero-way amounts, and `0` is already the initial value.
- `dp[0] = 1` is load-bearing: trace any single-element sequence (like `(target)` itself) — it only gets counted via `dp[target] += dp[target - x]` with `dp[0]` on the other side.
- The `break` is valid because `nums` is sorted ascending.

## Complexity Analysis

- **Time:** O(target × n) where n = |nums|
  - Reason: for each of `target` states, we scan up to n numbers.
- **Space:** O(target) for the dp array.

## Why This Approach Works

By induction on `i`: every sequence summing to `i` has a unique last element `x`, and removing it yields a unique sequence summing to `i - x`. This gives a bijection between sequences for `i` and pairs (sequence for `i - x`, element `x`). Since the sets for different `x` are disjoint (different last element), the total count is exactly the sum of `dp[i - x]`. Base case: the empty sequence is the unique sequence summing to 0.

## Common Pitfalls in This Pattern

### 🔴 The `+1` Bug (mixing cost-counting with way-counting)

Your first attempt: `dp[i] += dp[i-x]; if(i-x != 0) dp[i]++;` — that `+1` is Coin Change thinking leaking in. Coin Change counts _how many coins were used_ (`dp[i-x] + 1`). Combination Sum IV counts _how many ways exist_. A way is a whole sequence — you extend each existing way by one element, so you add the entire block `dp[i-x]`, not `+1` per path. If you catch yourself writing `+ 1` in a counting problem, you're computing the wrong quantity.

### Other Common Mistakes

- **`dp[0] = 0` (your base-case bug):** the empty sequence is one way, not zero ways. Without `dp[0] = 1`, single-element combinations are never counted and every `dp[i]` comes out short. Ask: _"what is the empty thing worth — one way, or zero cost?"_ Counting → 1, cost → 0.
- **Overflow:** plain `int` can overflow on intermediates even when the answer fits. Use `unsigned int` or clamp at `INT_MAX`. This is a real LeetCode test case, not a theoretical concern.
- **Scan-all-previous violation:** the inner loop over ALL nums is required (same as Word Break/Perfect Squares). The last element could be any num; committing to one is the greedy trap again.
- **Forgetting order matters:** this recurrence counts _sequences_. If a problem counts _sets_ (order doesn't matter), you must flip the loops (coins outer) — that's 518 Coin Change II.

## Pattern Connection

**This is a Knapsack DP problem (unbounded, counting variant) because:**

1. **Capacity state:** `dp[i]` over amount — selection of items (unlimited reuse) to reach a target.
2. **Unbounded:** reuse allowed → forward sweep, same as Coin Change.
3. **Counting objective:** the `+` operator — the third combine operator in your family.

**The operator family, now complete:**

| Problem                                   | Operator      | Base case       | Meaning of dp[i] |
| ----------------------------------------- | ------------- | --------------- | ---------------- |
| Word Break (139)                          | OR (exists)   | `dp[0] = true`  | segmentable?     |
| Perfect Squares (279) / Coin Change (322) | min (cost)    | `dp[0] = 0`     | fewest pieces    |
| Integer Break (343 ✅)                    | max (value)   | `dp[0] = 0`     | best product     |
| **Combination Sum IV (377)**              | **+ (count)** | **`dp[0] = 1`** | **# ways**       |
| Decode Ways (91, after)                   | + with gates  | `dp[0] = 1`     | # decodings      |

**The Decode Ways bridge:** Decode Ways is this exact recurrence — `dp[i] += dp[i - piece]` — except the "pieces" are 1- and 2-digit substrings that must pass validity gates, instead of nums. You just built the counting engine; Decode Ways only adds the gates.

**Similar problems in this pattern:**

- 322 - Coin Change — same skeleton, min instead of count
- 518 - Coin Change II — count but **sets** (order irrelevant) → flip the loops
- 91 - Decode Ways — count + string gates (the target)
- 494 - Target Sum — 0/1 counting

## Key Takeaway

_"Counting ways = ADD whole blocks: dp[i] += dp[i-x] (never +1 per path), with dp[0] = 1 for the empty way. Cost problems = min with dp[0] = 0. The base case tells you which operation you're in."_

## 🔑 Breakthrough

_"I had the intuition — 'get all the previous combinations' — but no correct formula, because the base case was wrong. The aha: **counting needs dp[0] = 1** (the empty sequence is one way, like 0! = 1), while min-cost problems need dp[0] = 0. Trace the single-element combination (x): it's counted via dp[x] += dp[x-x] = dp[0] — if dp[0] were 0, that combination vanishes. Also: the +1 I kept adding was Coin Change's 'count coins used' logic leaking in; ways are extended as whole blocks, not incremented per path. And intermediates can overflow int (dp[630] ≈ 4.6×10¹⁸) even when the final answer is 1 — unsigned int or clamp."_

## Your Code

```cpp
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        vector<unsigned int> dp(target + 1, 0);
        sort(nums.begin(), nums.end());
        dp[0] = 1;
        for(int i = 1; i<target+1; i++){
            for(int x : nums){
                if(x>i) break;
                dp[i]+=(dp[i-x]);

            }
        }
        return dp[target];
    }
};
```

_Your original work — correct as submitted. The unsigned trick for overflow was your own call._

## Solve Metrics

- **Solve Time:** 22 minutes
- **Attempts:** 3 (hint-guided: +1 bug → overflow bug → base case)
- **Confidence:** 7/10
- **Struggles:**
  1. Mixed "count coins used" (`+1`) with "count ways" (block addition) — Coin Change leakage
  2. Real overflow test case: intermediates like `dp[630] ≈ 4.6×10¹⁸` while `dp[999] = 1` — solved with `unsigned int`
  3. **The base case:** had the intuition, but `dp[0] = 1` (empty way) instead of `0` — without it, no formula computes correctly
- **Key Lesson:** _"Counting: dp[0] = 1, add blocks. Cost: dp[0] = 0, use min. The base case tells you the operation."_
- **Submitted:** 2026-08-01
- **Last Reviewed:** 2026-08-01
- **Next Review:** 2026-08-04 (Day 3) — re-solve, target < 12 min; then 2026-08-08 (Day 7)

---

**Generated:** 2026-08-01
