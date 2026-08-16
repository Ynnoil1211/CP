# 55 - Jump Game

**Pattern Type:** Linear / Sequence DP (scan-all-previous variant → greedy)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/jump-game/
**Topics:** Greedy, Reachability DP, Running maximum

## Problem Statement

You are given an array `nums` where `nums[i]` is the maximum jump length from index `i`. Starting at index `0`, determine whether you can reach the last index.

Constraints: `n ≤ 10^4`, `0 ≤ nums[i] ≤ 10^5`.

## State Definition

### What is dp[i]?

```
dp[i] = true if index i is reachable from index 0
```

**Example:** If `nums = [2,3,1,1,4]`, then:
- `dp[0] = true` (start)
- `dp[1] = true` (jump 1 from 0)
- `dp[2] = true` (jump 2 from 0)
- `dp[3] = true` (jump 1 from 1, or 1 from 2)
- `dp[4] = true` (jump 3 from 1) → reachable

### Why This State?

Reachability is a boolean property of each index: either you can stand there or you can't. It's a 1D linear scan because you process indices left to right, and whether `i` is reachable depends only on earlier reachable indices and their jump power.

## Recurrence Relation

```
dp[i] = true  if there EXISTS some j < i with dp[j] == true and nums[j] + j >= i
dp[0] = true  (base case — you start here)

Answer: dp[n-1]
```

### Transition Logic

**Step 1:** At index `i`, you can only arrive there by jumping from some earlier reachable index `j`.

**Step 2:** Index `j` can reach `i` exactly when `nums[j] + j >= i` (its max jump covers the distance). So scan all `j < i`, and if any reachable `j` covers `i`, mark `dp[i] = true`.

**Step 3:** This is a **scan-all-previous** variant — `dp[i]` must test EVERY earlier `j`, not just the last two. That's why the naive version needs a nested loop (O(n²)).

> **🔑 Key distinction — the greedy upgrade.** Because reachability is monotone (if you can reach `i`, you can reach everything before it), you don't need the full dp array. Track a single running maximum `mx = furthest index reachable so far`. At each `i`: if `i > mx` you're stuck (return false); otherwise update `mx = max(mx, i + nums[i])`. This collapses the nested loop into one pass — the "reachable frontier" grows greedily and never needs backtracking.

### Example Walkthrough

Input: `nums = [2,3,1,1,4]`

```
dp[0] = true
dp[1] = true  (j=0: nums[0]+0 = 2 >= 1)
dp[2] = true  (j=0: 2 >= 2)
dp[3] = true  (j=1: nums[1]+1 = 4 >= 3)
dp[4] = true  (j=1: 4 >= 4)
```

Why `dp[4] = true`? Because `j=1` is reachable and `nums[1] + 1 = 4 >= 4`, so index 1 can jump straight to the last index.

## Implementation (C++)

```cpp
// Greedy — O(n) time, O(1) space
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int mx = nums[0];            // furthest index reachable so far
        for (int i = 1; i < n; i++) {
            if (i > mx) return false;   // stuck before reaching i
            mx = max(mx, i + nums[i]);  // extend the frontier
        }
        return true;  // we scanned to the end without getting stuck
    }
};
```

**Key Implementation Notes:**

- `mx` starts at `nums[0]` (you can jump up to `nums[0]` from index 0).
- The check `i > mx` happens BEFORE updating — if the current index is beyond the reachable frontier, you can never get there.
- No need to check `mx >= n-1` explicitly; if you reach the last index in the loop, you're done. `return true` after the loop means every index was reachable, including `n-1`.
- Edge case `n == 1`: loop doesn't run, returns `true` (already at the end).

## Complexity Analysis

- **Time:** O(n) for greedy (single pass). The naive DP is O(n²) — n states × scanning up to n previous states each.
  - Reason: greedy tracks one running maximum, so each index is processed once.
- **Space:** O(1) for greedy. The DP version uses O(n) for the `dp` array.

## Why This Approach Works

By induction on `i`: `mx` after processing index `i-1` is the furthest index reachable from any of `0..i-1`. If `i > mx`, then `i` is beyond every reachable index, so it (and everything after) is unreachable → return false. Otherwise `i` is reachable, and the new frontier is `max(mx, i + nums[i])`. Since reachability is monotone (reaching `i` means reaching all of `0..i`), a single frontier correctly captures the whole reachable set — no backtracking needed.

## Common Pitfalls in This Pattern

- **Forgetting the `i > mx` check before updating.** If you update `mx` first, you might extend the frontier from an index you can't actually reach.
- **Writing the O(n²) DP when the greedy works.** The scan-all-previous DP is correct but slow; recognizing the monotone frontier is the whole optimization.
- **Off-by-one on the return.** If the loop completes, every index was reachable, so return `true` — don't compare `mx >= nums[n-1]` (that's `mx >= n-1`, and it's redundant).
- **`nums[0] == 0` with `n > 1`.** You can't move at all — the greedy catches this at `i=1` (`1 > 0` → false). No special case needed.

### 🔴 The Greedy Trap — but in reverse

Most scan-all-previous problems (Word Break, LIS) REQUIRE the nested loop and punish greedy. **Jump Game is the exception:** because reachability is monotone and cumulative, a single running frontier is provably correct. The trap here is the opposite — writing the O(n²) DP when the greedy is safe. Ask: _"Is the condition cumulative (frontier grows monotonically) or does it need to try every cut independently?"_ If cumulative → greedy; if independent cuts → nested loop.

## Pattern Connection

**This is a Linear DP problem because:**

1. 1D state over a linear sequence processed left to right.
2. The reachability of `i` depends only on earlier indices — no 2D structure.
3. It's the **scan-all-previous** sub-variant in its naive form, but collapses to a running-max greedy.

**Within Linear DP, classify further:**

- **Scan-all-previous** (dp[i] checks ALL j < i) → the naive O(n²) version
- **Greedy frontier** (single running max) → the optimized O(n) version, valid because reachability is monotone

This is the rare case where the scan-all-previous DP is *not* the intended solution — the monotone frontier makes greedy correct.

**Similar problems in this pattern:**

- 45 - Jump Game II (minimum jumps — needs BFS/greedy frontier, not just boolean reachability)
- 1306 - Jump Game III (reachability with a different jump rule)

## Key Takeaway

_For reachability problems, ask if the reachable set is monotone — if reaching `i` implies reaching everything before it, track a single running frontier (greedy) instead of a full dp array._

## 🔑 Breakthrough

The "aha" was that this scan-all-previous DP is the ONE case where greedy is provably correct: reachability is cumulative, so a single `mx` frontier replaces the entire nested loop. My O(n²) dp was correct but structurally overkill — the monotone frontier is the real insight.

## Your Code

```cpp
// Naive DP — O(n²), correct but slow
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<bool> dp(n+1, false);
        dp[0] = true;
        if(nums[0]==0 && n>1) return false;
        for(int i = 1; i<n; i++){
            for(int j = 0; j<i; j++){
                if(dp[j]==true && nums[j]+j>=i){
                    dp[i]=true;
                    break;
                }
            }
        }
        return dp[n-1];
    }
};

// Optimized greedy — O(n)
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int mx = nums[0];
        for(int i = 1; i<n; i++){
            if(i>mx) return false;
            mx = max(mx, i+nums[i]);
        }
        return mx>=nums[n-1];
    }
};
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** 11m + 46s
- **Attempts:** 1 (naive DP, then optimized greedy)
- **Confidence:** N/A (not reported)
- **Struggles:** The naive DP was "really slow" — recognized the O(n²) but hadn't yet seen the monotone-frontier greedy.
- **Submitted:** 2026-08-15
- **Last Reviewed:** 2026-08-15
- **Next Review:** 2026-08-18 (Day 3)

---

**Generated:** 2026-08-15
