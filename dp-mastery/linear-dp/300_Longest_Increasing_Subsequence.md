# 300 - Longest Increasing Subsequence

**Pattern Type:** Linear / Sequence DP (scan-all-previous variant)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/longest-increasing-subsequence/
**Topics:** LIS, Scan-all-previous DP, Patience sorting (greedy + binary search)

## Problem Statement

Given an integer array `nums`, return the length of the longest **strictly increasing** subsequence. A subsequence keeps elements in order but may skip elements (non-contiguous).

Constraints: `n ≤ 2500`, `-10^4 ≤ nums[i] ≤ 10^4`.

## State Definition

### What is dp[i]?

```
dp[i] = length of the longest increasing subsequence ENDING at index i
        (i.e. the last element of the subsequence is nums[i])
```

**Example:** If `nums = [10,9,2,5,3,7,101,18]`, then:

- `dp[0] = 1` (subsequence [10])
- `dp[1] = 1` (9 can't extend anything before it, so [9])
- `dp[2] = 1` (2 can't extend anything, so [2])
- `dp[3] = 2` (2 → 5)
- `dp[4] = 2` (2 → 3)
- `dp[5] = 3` (2 → 3 → 7, or 2 → 5 → 7)
- `dp[6] = 4` (2 → 3 → 7 → 101)
- `dp[7] = 4` (2 → 3 → 7 → 18)

Answer = `max(dp[i])` = 4.

### Why This State?

The key trick is defining `dp[i]` as the LIS **ending at** `i`, not "considering the first i elements." Why? Because to extend a subsequence with `nums[i]`, you need to know the length of the best subsequence whose last element is _smaller_ than `nums[i]` — and that's exactly "ending at some earlier `j` with `nums[j] < nums[i]`." Defining it as "ending at i" makes the extension rule local and testable.

## Recurrence Relation

```
dp[i] = 1 + max over all j < i with nums[j] < nums[i] of dp[j]
dp[i] = 1  if no such j exists (nums[i] starts a new subsequence)
dp[0] = 1  (base case)

Answer: max over all i of dp[i]
```

### Transition Logic

**Step 1:** At index `i`, the LIS ending at `i` either is just `[nums[i]]` alone (length 1), or extends some earlier subsequence.

**Step 2:** To extend, the earlier subsequence must end at some `j < i` with `nums[j] < nums[i]` (strictly increasing). Its length is `dp[j]`, so extending gives `dp[j] + 1`. Take the max over all valid `j`.

**Step 3:** This is a **scan-all-previous** variant — `dp[i]` must test EVERY earlier `j`, not just the last two. The condition `nums[j] < nums[i]` is not a fixed offset, so a nested loop is structurally required. **This is the case where greedy does NOT work** — you can't follow a single pointer, because the best subsequence to extend might end at any earlier index.

> **🔑 Key distinction — the O(n log n) greedy upgrade.** The DP is O(n²). The optimized version uses **patience sorting**: maintain `res`, where `res[k]` = the smallest possible _tail value_ of an increasing subsequence of length `k+1`. For each `nums[i]`:
>
> - If `nums[i] > res.back()`, it extends the longest subsequence → push it.
> - Else, `lower_bound` finds the first position where `nums[i]` can _replace_ a tail (keeping tails minimal), and overwrite it.
>
> `res` stays sorted, so `res.size()` = LIS length. This is NOT the same as the DP — it's a greedy that keeps the "best possible tails" so far. It works because a smaller tail is always at least as good as a larger one for future extension.

### Example Walkthrough

Input: `nums = [10,9,2,5,3,7,101,18]`

```
dp[0] = 1
dp[1] = 1  (9 < 10? no → stays 1)
dp[2] = 1  (2 < 10, 2 < 9? no → stays 1)
dp[3] = 2  (j=2: 2 < 5 → dp[2]+1 = 2)
dp[4] = 2  (j=2: 2 < 3 → dp[2]+1 = 2)
dp[5] = 3  (j=4: 3 < 7 → dp[4]+1 = 3)
dp[6] = 4  (j=5: 7 < 101 → dp[5]+1 = 4)
dp[7] = 4  (j=5: 7 < 18 → dp[5]+1 = 4)
```

Why answer = 4? Because `max(dp) = dp[6] = 4`, from the subsequence `2 → 3 → 7 → 101`.

## Implementation (C++)

```cpp
// Scan-all-previous DP — O(n²) time, O(n) space
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1);          // every index is at least length 1
        int mx = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            mx = max(mx, dp[i]);
        }
        return mx;
    }
};
```

**Key Implementation Notes:**

- Initialize `dp[i] = 1` for all — every element alone is a length-1 subsequence.
- Track `mx` as you go; the answer is `max(dp[i])`, NOT `dp[n-1]` (the LIS might not end at the last index).
- Strictly increasing means `nums[i] > nums[j]` (not `>=`).

```cpp
// Patience sorting (greedy + binary search) — O(n log n) time, O(n) space
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> res;
        res.push_back(nums[0]);
        for (int i = 1; i < n; i++) {
            if (nums[i] > res.back()) {
                res.push_back(nums[i]);          // extends the longest subsequence
            } else {
                int ind = lower_bound(res.begin(), res.end(), nums[i]) - res.begin();
                res[ind] = nums[i];              // replace a tail with a smaller one
            }
        }
        return res.size();
    }
};
```

**Key Implementation Notes:**

- `res[k]` = smallest tail value of an increasing subsequence of length `k+1`. It stays sorted.
- `lower_bound` finds the first `res[ind] >= nums[i]` and overwrites it — keeping tails minimal.
- Loop starts at `i = 1` (index 0 is already pushed). The user's version starts at `i = 0`, which re-processes index 0 redundantly but still gives the correct answer.
- `res` is NOT the actual LIS — only its length is correct. (The greedy tails don't reconstruct the subsequence.)

## Complexity Analysis

- **Time:** O(n²) for the DP (n states × scanning up to n previous states each). O(n log n) for patience sorting (n elements × O(log n) binary search each).
  - Reason: DP needs the nested loop over all `j < i`; patience sorting replaces that scan with a binary search on the sorted `res`.
- **Space:** O(n) for both (the `dp` array / the `res` array).

## Why This Approach Works

**DP (induction):** By induction on `i`, `dp[j]` correctly holds the LIS length ending at `j` for all `j < i`. Any increasing subsequence ending at `i` either is just `[nums[i]]` (length 1) or extends an increasing subsequence ending at some `j < i` with `nums[j] < nums[i]`. The best such extension is `dp[j] + 1`, maximized over valid `j`. So `dp[i]` is correct, and the answer is the max over all endpoints.

**Patience sorting (greedy):** `res` is maintained as the array of minimal tails. If `nums[i]` is larger than the largest tail, it extends the longest subsequence. Otherwise, replacing the first tail `>= nums[i]` with `nums[i]` never hurts: a smaller tail at that length is strictly better (or equal) for any future extension. Since `res` is sorted and we always replace the first `>=` element, the invariant holds, and `res.size()` is the LIS length.

## Common Pitfalls in This Pattern

- **Returning `dp[n-1]` instead of `max(dp)`.** The LIS might end before the last index. Always track the running max.
- **Using `>=` instead of `>`.** Strictly increasing means `nums[i] > nums[j]`; equal elements can't extend each other.
- **Forgetting `dp[i] = 1` initialization.** Every element alone is a length-1 subsequence; without it, the recurrence undercounts.
- **Thinking greedy works in the naive form.** Unlike Jump Game, you can't follow a single pointer — the best subsequence to extend might end at any earlier index, so the nested loop is structurally required. The O(n log n) version is a _different_ algorithm (patience sorting), not a simplification of the DP.
- **Assuming `res` reconstructs the LIS.** The patience-sorting `res` array holds minimal tails, not the actual subsequence — only its length is meaningful.

### 🔴 The Greedy Trap (the real one)

This is the canonical scan-all-previous problem where a naive greedy fails. If you try to "commit to the first match" and extend a single running subsequence, you lose the ability to backtrack and try alternative earlier endings. The nested loop over ALL `j < i` is not optimization — it's the correct DP structure. The O(n log n) patience-sorting trick is a separate, clever algorithm, not a pointer-based shortcut.

## Pattern Connection

**This is a Linear DP problem because:**

1. 1D state over a linear sequence processed left to right.
2. The LIS ending at `i` depends only on earlier indices — no 2D structure.
3. It's the **scan-all-previous** sub-variant: `dp[i]` must check ALL `j < i` with `nums[j] < nums[i]`.

**Within Linear DP, classify further:**

- **Scan-all-previous** (dp[i] checks ALL j < i) → LIS-style, requires nested loop, O(n²)
- **Patience sorting** (greedy + binary search on minimal tails) → the O(n log n) optimization

This is the textbook scan-all-previous problem — the one where the greedy trap is real and the nested loop is genuinely required.

**Similar problems in this pattern:**

- 368 - Largest Divisible Subset (same shape, different condition: `nums[j] % nums[i] == 0`)
- 55 - Jump Game (scan-all-previous DP, but collapses to greedy — the exception)
- 45 - Jump Game II (scan-all-previous DP, but collapses to BFS frontier — the exception)

## Key Takeaway

_For LIS, define `dp[i]` as the LIS ending at `i` and scan all previous `j` with `nums[j] < nums[i]`. The answer is `max(dp)`, not `dp[n-1]`. The O(n log n) version is patience sorting — a different greedy algorithm, not a DP shortcut._

## 🔑 Breakthrough

The "aha" was that LIS is the case where the nested loop is genuinely required — unlike Jump Game, you can't follow a single pointer because the best subsequence to extend might end at any earlier index. And the O(n log n) trick is a _separate_ algorithm (patience sorting on minimal tails), not a simplification I'd naturally derive from the DP. I only thought of the DP — the greedy tails idea didn't occur to me.

## Your Code

```cpp
// Scan-all-previous DP — O(n²)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1, 1);
        int mx = 1;
        for(int i = 1; i<n; i++){
            for(int j = 0; j<i; j++){
                if(nums[i]>nums[j]){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
            mx = max(mx, dp[i]);
        }
        return mx;
    }
};

// Patience sorting — O(n log n)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> res;
        res.push_back(nums[0]);
        for(int i = 0; i<n; i++){
            if(nums[i]>res.back()){
                res.push_back(nums[i]);
            } else{
                int ind = lower_bound(res.begin(), res.end(), nums[i]) - res.begin();
                res[ind] = nums[i];
            }
        }
        return res.size();
    }
};
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** 13 minutes
- **Attempts:** 1 (DP) + optimized patience sorting
- **Confidence:** 10/10
- **Struggles:** "I didn't even think about the greedy version, only DP on my head" — the O(n log n) patience-sorting idea didn't occur naturally.
- **Submitted:** 2026-08-15
- **Last Reviewed:** 2026-08-15
- **Next Review:** 2026-08-18 (Day 3)

---

**Generated:** 2026-08-15
