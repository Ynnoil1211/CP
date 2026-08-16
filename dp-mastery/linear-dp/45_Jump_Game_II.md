# 45 - Jump Game II

**Pattern Type:** Linear / Sequence DP (scan-all-previous variant → BFS/greedy frontier)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/jump-game-ii/
**Topics:** Greedy, BFS frontier, Minimum-jumps reachability

## Problem Statement

You are given an array `nums` where `nums[i]` is the maximum jump length from index `i`. Starting at index `0`, return the **minimum number of jumps** to reach the last index. It is guaranteed you can always reach the last index.

Constraints: `n ≤ 10^4`, `0 ≤ nums[i] ≤ 10^5`.

## State Definition

### What is dp[i]?

```
dp[i] = minimum number of jumps to reach index i from index 0
```

**Example:** If `nums = [2,3,1,1,4]`, then:
- `dp[0] = 0` (start)
- `dp[1] = 1` (jump 1 from 0)
- `dp[2] = 1` (jump 2 from 0)
- `dp[3] = 2` (0 → 1 → 3, or 0 → 2 → 3)
- `dp[4] = 2` (0 → 1 → 4)

### Why This State?

Unlike Jump Game's boolean reachability, this problem asks for a **count** — the minimum jumps. So `dp[i]` stores the best (minimum) number of jumps to stand at `i`, and you combine it with the +1 cost of one more jump from a reachable earlier index.

## Recurrence Relation

```
dp[i] = min over all j < i with nums[j] + j >= i of (dp[j] + 1)
dp[0] = 0  (base case — you start here, zero jumps)

Answer: dp[n-1]
```

### Transition Logic

**Step 1:** At index `i`, the last jump came from some earlier reachable index `j` (where `nums[j] + j >= i`).

**Step 2:** If `j` can reach `i`, then reaching `i` costs `dp[j] + 1` (the jumps to `j`, plus this one jump). Take the minimum over all valid `j`.

**Step 3:** This is a **scan-all-previous** variant — `dp[i]` must test EVERY earlier `j`, not just the last two. That's why the naive version needs a nested loop (O(n²)).

> **🔑 Key distinction — the BFS/greedy upgrade.** The minimum-jump structure is a **BFS over levels**: jump 0 reaches index 0 only; jump 1 reaches everything up to `nums[0]`; jump 2 reaches everything up to the max frontier from level-1 indices; and so on. Each "level" is one jump. So track:
> - `curr` = furthest index reachable from the current level
> - `end` = the boundary of the current level (where the next jump starts)
> - `res` = number of jumps (levels) taken
>
> When `i` hits `end`, you've exhausted the current level → take one jump (`res++`) and move the frontier to `curr`. This is BFS in disguise, O(n).

### Example Walkthrough

Input: `nums = [2,3,1,1,4]`

```
dp[0] = 0
dp[1] = 1  (j=0: nums[0]+0 = 2 >= 1 → dp[0]+1 = 1)
dp[2] = 1  (j=0: 2 >= 2 → dp[0]+1 = 1)
dp[3] = 2  (j=1: 4 >= 3 → dp[1]+1 = 2; j=2: 3 >= 3 → dp[2]+1 = 2)
dp[4] = 2  (j=1: 4 >= 4 → dp[1]+1 = 2)
```

Why `dp[4] = 2`? Because the minimum is 2 jumps: `0 → 1 → 4` (or `0 → 2 → 4`). The greedy BFS agrees: level 1 covers indices 1-2, level 2 covers 3-4.

## Implementation (C++)

```cpp
// BFS/greedy frontier — O(n) time, O(1) space
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int curr = 0, end = 0, res = 0;
        for (int i = 0; i < n - 1; i++) {
            curr = max(curr, i + nums[i]);   // extend the reachable frontier
            if (i == end) {                  // exhausted the current level
                res++;                       // take one jump
                end = curr;                  // next level's boundary
            }
        }
        return res;
    }
};
```

**Key Implementation Notes:**

- Loop runs `i < n-1` — you don't need to "jump" from the last index (you're already there).
- `curr` is the furthest index reachable from the current level; `end` is where the level ends.
- When `i == end`, you must take a jump to progress past it → `res++`, and the new level boundary is `curr`.
- The problem guarantees reachability, so no `return -1` needed.
- Edge case `n == 1`: loop doesn't run, returns `0` (already at the end).

## Complexity Analysis

- **Time:** O(n) for BFS/greedy (single pass). The naive DP is O(n²) — n states × scanning up to n previous states each.
  - Reason: greedy tracks one frontier and processes each index once.
- **Space:** O(1) for BFS/greedy. The DP version uses O(n) for the `dp` array.

## Why This Approach Works

The minimum-jump structure is exactly BFS on an implicit graph where index `j` has edges to all `j+1 .. j+nums[j]`. BFS visits nodes in order of distance (jumps), so the number of "levels" processed equals the minimum jumps. The greedy frontier (`curr`) is the furthest node reachable within the current level; when `i` reaches `end`, the level is exhausted and a new jump begins. Because every index in a level is reachable with the same jump count, tracking only the frontier (not individual nodes) is sufficient — this is the classic "BFS with two pointers" optimization.

## Common Pitfalls in This Pattern

- **Looping to `n-1` instead of `n-2`.** Jumping from the last index is meaningless; `i < n-1` avoids an extra unnecessary `res++`.
- **Forgetting the `i == end` trigger.** Without it, `res` never increments and you just track a frontier with no jump count.
- **Writing the O(n²) DP when BFS/greedy works.** The scan-all-previous DP is correct but slow; recognizing the level structure is the whole optimization.
- **Confusing this with Jump Game.** Jump Game asks *can* you reach (boolean, single frontier). Jump Game II asks *minimum jumps* (count, needs the level boundary `end` to count jumps). The frontier alone isn't enough — you need to know when a new jump starts.

### 🔴 The Greedy Trap — but in reverse (part 2)

Like Jump Game, this is a scan-all-previous DP that collapses to a greedy/BFS frontier. The trap is writing the O(n²) DP when the level structure makes O(n) possible. Ask: _"Is this boolean reachability (one frontier) or minimum jumps (frontier + level boundary)?"_ Boolean → Jump Game's single `mx`. Minimum jumps → add `end` to count levels.

## Pattern Connection

**This is a Linear DP problem because:**

1. 1D state over a linear sequence processed left to right.
2. The minimum jumps to `i` depend only on earlier indices — no 2D structure.
3. It's the **scan-all-previous** sub-variant in its naive form, but collapses to a BFS/greedy frontier.

**Within Linear DP, classify further:**

- **Scan-all-previous** (dp[i] checks ALL j < i) → the naive O(n²) version
- **BFS/greedy frontier** (two pointers: `curr` frontier + `end` level boundary) → the optimized O(n) version, valid because jumps form BFS levels

This is the second case (after Jump Game) where the scan-all-previous DP is *not* the intended solution — the level structure makes greedy correct.

**Similar problems in this pattern:**

- 55 - Jump Game (boolean reachability — single frontier, no level count)
- 1306 - Jump Game III (reachability with a different jump rule)

## Key Takeaway

_For minimum-jump reachability, think BFS levels: track a frontier `curr` and a level boundary `end`; every time `i` hits `end`, take a jump. Boolean reachability needs only the frontier; counting jumps needs the boundary too._

## 🔑 Breakthrough

The "aha" was that minimum jumps = BFS levels. Jump Game's single `mx` frontier tells you *how far* you can reach, but not *how many jumps* — you need the second pointer `end` to count when a new level (jump) begins. The `i == end` trigger is the whole trick: it's the moment you've squeezed everything out of the current jump and must take the next one.

## Your Code

```cpp
// Naive DP — O(n²), correct but slow
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n+1,INT_MAX-10000);
        dp[0] = 0;
        for(int i = 1; i<n; i++){
            for(int j = 0; j<i; j++){
                int curr = 0;
                if(nums[j]+j>=i){
                    dp[i] = min(dp[i], dp[j]+1);
                }
            }
        }
        return dp[n-1];
    }
};

// BFS/greedy frontier — O(n)
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int curr = 0, end = 0, res = 0;
        for(int i = 0; i<n-1; i++){
            curr = max(curr, i+nums[i]);
            if(i==end){
                res++;
                end=curr;
            }
        }
        return res;
    }
};
```

_This is your original work. Keep it to track how your style evolves._

## Solve Metrics

- **Solve Time:** 7 minutes
- **Attempts:** 1 (naive DP) + optimized greedy
- **Confidence:** 10/10
- **Struggles:** None reported — the Jump Game pattern transferred cleanly; the DP came out correct first try.
- **Submitted:** 2026-08-15
- **Last Reviewed:** 2026-08-15
- **Next Review:** 2026-08-18 (Day 3)

---

**Generated:** 2026-08-15
