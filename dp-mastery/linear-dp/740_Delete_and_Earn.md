# 740 - Delete and Earn

**Pattern Type:** Linear DP (transformed from frequency map)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/delete-and-earn/
**Topics:** Frequency preprocessing, House Robber reduction, value-indexed DP

## Problem Statement

Given an array `nums`, you can pick any `nums[i]` and earn its value, but you must delete **all** occurrences of `nums[i] - 1` and `nums[i] + 1`. Maximize the total earned.

**Constraints:**

- `1 ≤ nums.length ≤ 2 * 10^4`
- `1 ≤ nums[i] ≤ 10^4`

## State Definition

### What is dp[i]?

```
dp[i] = maximum points earnable considering values from 0 up to i (inclusive)
points[i] = i * freq[i]   (total points you get if you take ALL copies of value i)
```

**Examples:**

- `dp[0] = 0` — value 0 doesn't exist; earn nothing
- `dp[1] = points[1]` — either take value 1 or don't; only one option since there's no conflict with 0
- `dp[2] = max(points[2] + dp[0], dp[1])` — take 2 (add points[2], skip 1) or skip 2

### Why This State?

The twist: the constraint "taking value `i` forbids `i-1` and `i+1`" is **structurally identical** to House Robber's "can't rob adjacent houses" when the array is indexed by **value**.

The key transformation:

1. Build `freq[x]` = count of value `x` in `nums`
2. Build `points[x] = x * freq[x]`
3. Index by value `0 .. maxVal` (fill gaps with 0 points)
4. Apply House Robber I recurrence

Once you index by value, adjacency in the array = adjacency in the number line. So the House Robber recurrence applies directly.

## Recurrence Relation

```
points[i] = i * freq[i]

dp[i] = max(points[i] + dp[i-2], dp[i-1])

Base cases:
  dp[0] = points[0] = 0
  dp[1] = points[1] = 1 * freq[1]

Answer:
  dp[maxVal]
```

### Transition Logic

**Step 1:** Take value `i` → you earn `points[i]` but must skip `i-1` (so add `dp[i-2]`).

**Step 2:** Skip value `i` → you keep the best up to `i-1` (so take `dp[i-1]`).

**Step 3:** Pick whichever is larger. Same include/skip decision as House Robber.

### Example Walkthrough

Input: `nums = [2, 2, 3, 3, 3, 4]`

```
freq:      [0, 0, 2, 3, 1]    (indices 0..4)
points:    [0, 0, 4, 9, 4]    (value × freq)

dp[0] = 0
dp[1] = max(0 + dp[-1]?, 0)  hmm, dp[1] = points[1] = 0 (since freq[1] = 0)
```

Wait, let me be more careful.

```
freq:  0→0, 1→0, 2→2, 3→3, 4→1
points: 0→0, 1→0, 2→4, 3→9, 4→4

dp[0] = 0
dp[1] = max(points[1] + dp[-1], dp[0]) = max(0, 0) = 0
       But simpler: just set dp[1] = max(points[1], dp[0]) = 0
dp[2] = max(points[2] + dp[0], dp[1]) = max(4 + 0, 0) = 4
dp[3] = max(points[3] + dp[1], dp[2]) = max(9 + 0, 4) = 9
dp[4] = max(points[4] + dp[2], dp[3]) = max(4 + 4, 9) = 9

Answer: dp[4] = 9
```

Indeed, taking all 3's (3×3=9) is better than taking 2's (2×2=4) + 4 (1×4=4) = 8.

## Implementation (C++)

```cpp
// Your solution (value-indexed dp array)
int deleteAndEarn(vector<int>& nums) {
    vector<int> freq(10001, 0);
    for (int x : nums) freq[x]++;

    vector<int> dp(10001, 0);
    dp[0] = 0;
    dp[1] = freq[1] * 1;  // points[1]

    for (int i = 2; i <= 10000; i++) {
        int points = freq[i] * i;
        dp[i] = max(points + dp[i-2], dp[i-1]);
    }
    return dp[10000];
}
```

```cpp
// Cleaner version (find maxVal dynamically)
int deleteAndEarn(vector<int>& nums) {
    int maxVal = *max_element(nums.begin(), nums.end());
    vector<int> freq(maxVal + 1, 0);
    for (int x : nums) freq[x]++;

    int prev2 = 0;           // dp[i-2]
    int prev1 = freq[1];     // dp[i-1] = points[1] (may be 0)
    for (int i = 2; i <= maxVal; i++) {
        int cur = max(freq[i] * i + prev2, prev1);
        prev2 = prev1;
        prev1 = cur;
    }
    return prev1;
}
```

**Key Implementation Notes:**

- **Index by value, not by unique values.** This is the critical insight. If you compress to unique values (e.g., `[2,3,5]`), indices `i` and `i-1` in your array don't correspond to values `i` and `i-1` — they might be 2 apart (3 and 5), which wrongly forbids taking both 3 and 5 when they're actually safe together.
- Your fixed array of size 10001 works, but `maxVal = *max_element(...)` is cleaner and avoids iterating to 10000 unnecessarily.
- Points for each value = `value × freq[value]`. You take ALL copies at once.
- The `dp[nums[0]]` assignment in your code is harmless but unnecessary — the loop overwrites it.

## Complexity Analysis

- **Time:** O(n + maxVal)
  - Reason: O(n) to build frequency map, O(maxVal) for DP pass. Since maxVal ≤ 10⁴, it's essentially O(n).
- **Space:** O(maxVal) for the frequency/DP arrays. Can be O(1) with the two-variable optimization.

## Why This Approach Works

**Transformation proof:** The operation "take value x, delete all x-1 and x+1" has the same constraint structure as House Robber's "can't rob adjacent houses." By indexing an array by value, the adjacency constraint becomes index adjacency. Values with 0 frequency contribute 0 points and act as "empty houses" that don't affect the recurrence.

**Correctness:** Once transformed into `points[i] = i × freq[i]`, the recurrence is House Robber's — and we've already proven that works by induction on `i`.

## Common Pitfalls in This Pattern

- **Compressing to unique values**: If you build an array of only values that exist (e.g., `[2,3,5]`), you lose the gap between 3 and 5. The recurrence would incorrectly forbid taking both 3 and 5, when in reality they're not adjacent in the number line.
- **Forgetting to multiply by frequency**: Each copy of value `x` earns `x` points. If value 2 appears 3 times, taking value 2 earns `2 × 3 = 6`.
- **Looping from 0 instead of 1 or 2**: `dp[0]` should be 0 (value 0 doesn't exist). `dp[1]` needs correct initialization.

## Pattern Connection

**This is a Linear DP problem because:**

1. **Reduces to House Robber I**: After frequency preprocessing, the recurrence is identical. This is the most important connection — learn to spot problems that _transform into_ a known DP.
2. **1D state**: dp[i] depends only on value index i.
3. **Include/skip decision**: Same `max(take + dp[i-2], dp[i-1])` pattern.

**Similar problems in this pattern:**

- [198 - House Robber I](linear-dp/198_House_Robber.md) — the foundation this transforms into
- [213 - House Robber II](linear-dp/213_House_Robber_II.md) — circular variant
- 2266 — Count Number of Texts (different but also uses frequency precomputation)

## Key Takeaway

_"Delete and Earn = House Robber on a frequency-indexed array. If a problem says 'taking X removes X-1 and X+1', map it to a value-indexed array and apply the include/skip recurrence."_

## Your Code

```cpp
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int n = nums.size();
        vector<int> uniq(1e4+2, 0);
        for(int x : nums){
            uniq[x]++;
        }
        vector<int> dp(1e4+2,0);
        dp[nums[0]] = uniq[nums[0]];
        dp[1] = uniq[1];
        for(int i = 2; i<1e4+1; i++){
            dp[i] = max(uniq[i]*i + dp[i-2], dp[i-1]);
        }
        return dp[1e4];
    }
};
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** ~40 minutes
- **Attempts:** 1 (with hints guiding the transformation)
- **Confidence:** 7/10
- **Struggles:**
  1. Didn't initially see how to map to House Robber — needed the hint to compute `points[x] = x * freq[x]`
  2. Tried compressing to unique values first (which loses the gap information) — that was the trap
  3. Needed the nudge to _index by value_ so adjacency in the array = adjacency in the number line
- **Key insight you landed on:** _"Index by value, not by uniqueness."_ Once that clicked, the House Robber recurrence was immediate.
- **Submitted:** 2026-07-27
- **Last Reviewed:** 2026-08-01
- **Next Review:** 2026-08-08 (Day 7) — re-solve, target < 8 minutes

**Re-solve Log:**

- 2026-08-01: 11 min, no hints. Struggled briefly with the `1e4` array bound (nums values ≤ 10⁴, so `freq` needs size `10001`, and `dp` must cover the top value) and then the base case — fixed by using `dp[1] = freq[1]` instead of the fragile `dp[nums[0]]`. The index-by-value transform itself is now yours. Confidence 6 → 7/10.

---

**Generated:** 2026-07-27
