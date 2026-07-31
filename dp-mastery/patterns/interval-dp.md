# Pattern: Interval DP

## Pattern Name: **Interval DP**

### Description

Your state is a **range `[i, j]`** of the array. You solve small ranges first, then combine them into larger ranges by trying every **split point `k`** inside the range.

The mental shift: instead of processing left to right, you think "the answer for this range = best way to combine the answers of two sub-ranges". This is the DP of *order-of-operations* problems — you choose where the **last operation** happens, and everything before it becomes two independent sub-problems.

### When to recognize it

- "burst", "merge", "remove a range", "triangulate"
- The order of operations on a range matters
- Cost depends on endpoints (e.g. balloons adjacent to the burst position)

### The General Template

**State:**
```
dp[i][j] = best result for the range [i, j]
```

**Base case:**
```
dp[i][i] = single-element cost (often 0)
```

**Transition:**
```
dp[i][j] = best over k in (i, j) of: dp[i][k] + dp[k][j] + cost(i, k, j)
```

**Answer:** `dp[0][n-1]`.

**Complexity:** O(n³) time (range × split point), O(n²) space.

### The core intuition to keep

Pick the **"last action"** (the last balloon burst, the last merge, the last cut) — it splits the range into two independent halves. The split point `k` is the decision, which is what makes this different from Linear DP, where the decision is per-element. If a problem gives you a range and asks "what's the best order of operations?", reach for the split.

### 🟢 Solved Problems

None yet.

### ⏳ Next up

- [1039 - Minimum Score Triangulation](https://leetcode.com/problems/minimum-score-triangulation/) → [312 - Burst Balloons](https://leetcode.com/problems/burst-balloons/) (the classic)
- [647 - Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) / [5 - Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/) — 2D substring checks; classify as interval vs. 2D when you solve them
