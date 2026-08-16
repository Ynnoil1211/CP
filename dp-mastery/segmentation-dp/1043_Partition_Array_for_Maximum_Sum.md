a# 1043 - Partition Array for Maximum Sum

**Pattern Type:** Segmentation DP (bounded piece length variant — the Decode Ways engine)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/partition-array-for-maximum-sum/
**Topics:** Last-piece decomposition, bounded window scan, piece value = max·len, running max, loop-condition hygiene

## Problem Statement

Partition `arr` into contiguous subarrays of length **at most `k`**. Each subarray's values are replaced by the subarray's maximum. Return the largest possible sum after partitioning.

**Constraints:**

- `1 ≤ n ≤ 500`
- `1 ≤ k ≤ n`
- `0 ≤ arr[i] ≤ 10⁹`

## State Definition

### What is dp[i]?

```
dp[i] = maximum sum achievable for the FIRST i elements of arr (pieces ≤ k)
```

**Convention used in the code (1-indexed prefix):** `dp[i+1]` corresponds to `arr[0..i]` — "the best sum for the i+1 elements I've seen so far."

**Examples** (arr = [1, 15, 7, 9], k = 3):

- `dp[0] = 0` — empty prefix, nothing partitioned
- `dp[2] = 30` — [1,15] as one piece → both become 15 → 15·2
- `dp[4] = 54` — [1,15,7] + [9] → 15·3 + 9·1

### Why This State?

The segmentation skeleton on a prefix: every partition of the first `i` elements has a **last piece** — a window of length `j ≤ k` — and everything before it is an optimal partition of `i - j` elements, already in `dp[i-j]`. The piece's contribution is `max(window) · j` because all `j` values become the window max.

## Recurrence Relation

```
dp[i] = max over every last-piece length j in [1, min(k, i)] of:
            dp[i - j] + max(arr[i-j .. i-1]) * j

Base case:
  dp[0] = 0        (NOT arr[0] — dp[0] is the empty prefix)

Answer:
  dp[n]
```

### Transition Logic

**Step 1:** Decide the **last piece**: a window of length `j` ending at the current position (1 ≤ j ≤ k).

**Step 2:** The window's value is `max(window) · j` — every element inside becomes the max.

**Step 3:** Add the best partition of everything before the window (`dp[i-j]`), try ALL lengths `j`, take the max.

> **🔑 Bounded pieces = bounded scan.** The piece length is capped at `k`, so only `k` candidates per state — O(n·k), not O(n²). **This is exactly the scan Decode Ways needs with pieces of length 1-2.** Swap "piece value = max·len" for "piece value = digit-validity gates" and you have 91.

## 🔧 The Loop-Conditions Trick (your own — keep it forever)

**Golden Rule:** think in **"elements I'm considering"**, not indices.

```cpp
for (int i = 1; i <= n; i++) {                    // i = how many elements covered (1 to n)
    for (int j = 1; j <= min(k, i); j++) {        // j = how many elements back?
```

**Ask yourself:**

1. **How many elements have I covered?** → `i` (the first i elements)
2. **Can I make a piece of j elements?** → yes, max `k` at a time, and never more than the prefix → `min(k, i)`
3. **Which element is at position j steps back?** → `arr[i-j]`

**Memory aid:**

| j     | Window start | Meaning         |
| ----- | ------------ | --------------- |
| j = 1 | `arr[i-1]`   | last element    |
| j = 2 | `arr[i-2]`   | one back        |
| j = k | `arr[i-k]`   | k elements back |

**Why it kills the off-by-ones:** every wrong index in this problem is the same mistake — thinking in positions instead of counts, or mixing conventions mid-attempt. `arr[i-j]` is "the element that starts a j-element window ending at the last element"; `dp[i-j]` is "the best for everything before that window." The question _"how many elements does this piece cover?"_ resolves both — and the j=1 check (`arr[i-1]` = the LAST element) verifies the convention before coding. Same question applies to Decode Ways (`j ∈ {1,2}` → `s[i-1]`, `s[i-2]`), Word Break (piece = `s[i-j..i-1]` of length j), and every scan-all-previous recurrence.

### Example Walkthrough (hand-trace — the real teacher)

Input: `arr = [1, 15, 7, 9]`, `k = 3`

```
i=0 (arr[0]=1):
  j=1: mx=1,  dp[1] = max(0, dp[0]+1·1)  = 1
i=1 (arr[1]=15):
  j=1: mx=15, dp[2] = max(0, dp[1]+15·1) = 16
  j=2: mx=15, dp[2] = max(16, dp[0]+15·2) = 30 ✓
i=2 (arr[2]=7):
  j=1: mx=7,  dp[3] = max(0, dp[2]+7·1)  = 37
  j=2: mx=15, dp[3] = max(37, dp[1]+15·2) = 37
  j=3: mx=15, dp[3] = max(37, dp[0]+15·3) = 45 ✓
i=3 (arr[3]=9):
  j=1: mx=9,  dp[4] = max(0, dp[3]+9·1)  = 54
  j=2: mx=9,  dp[4] = max(54, dp[2]+9·2) = 54
  j=3: mx=15, dp[4] = max(54, dp[1]+15·3) = 54

Return dp[4] = 54
```

**Why 54?** The winning partition is **[1,15,7] + [9]**: the window [1,15,7] → all become 15 → 45, plus [9] → 9. Total **54**. (Not [1,15] + [7,9] = 30 + 18 = 48 — that's a valid partition, just not optimal. The dp trace's last row keeps 54 via `j=1`, i.e. the _final_ piece [9] alone.)

## Implementation (C++)

```cpp
// 1-indexed convention — matches the walkthrough above
int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n + 1, 0);          // dp[i] = best for the FIRST i elements (arr[0..i-1])
    for (int i = 1; i <= n; i++) {     // i = how many elements we've covered
        int mx = 0;                    // max of the window — RESET per i
        for (int j = 1; j <= min(k, i); j++) {   // j = piece size (1..k, capped by prefix)
            mx = max(mx, arr[i - j]);            // window start = j elements back from the end
            dp[i] = max(dp[i], dp[i - j] + mx * j);  // try this last piece
        }
    }
    return dp[n];
}
```

**Key Implementation Notes:**

- **The running `mx` trick:** as `j` grows, the window extends _leftward_ one element at a time, so `mx = max(mx, arr[i-j])` maintains the window max in O(1) per candidate.
- **Convention check (1-indexed):** at `j=1` the window must be exactly the LAST element → `arr[i-1]` ✓ (`arr[i-j]` with j=1). At `j=k` → `arr[i-k]`. If your formula gives anything else at j=1, it's wrong.
- **The cap `min(k, i)` is load-bearing** — the window can't exceed the prefix (i elements seen); without it, negative indices on small prefixes.
- **`mx` must be reset inside the outer loop** (per `i`), not outside.
- **Use `max(dp[i], ...)`, never assignment** — each state accumulates the best over all `j`.
- `dp[0] = 0` bootstraps: a piece covering the whole prefix uses `dp[0] + max·i`.

## Complexity Analysis

- **Time:** O(n·k) — for each of n prefixes, at most k window lengths.
- **Space:** O(n) — dp[i] reads dp[i-j] for j up to k, so you need the array (or a k-window ring).

## Why This Approach Works

By induction on `i`: any valid partition of the first `i` elements has a last piece of length `j ≤ k` covering `i-j+1..i`, contributing `max·j`; the prefix before it is validly partitioned, costing at least `dp[i-j]`. Scanning every `j` covers every partition exactly once (unique last piece), so the max is exact. Base `dp[0] = 0` bootstraps.

## Common Mistakes to Avoid (your checklist)

- ❌ Mixing conventions: `arr[i-j+1]` or `dp[i-j+1]` in the 1-indexed version — here the window start is `arr[i-j]` (j elements back) and the prefix is `dp[i-j]`. Pick 1-indexed, verify j=1 → `arr[i-1]`, and stay consistent
- ❌ Using `arr[i-j]` with the OLD 0-indexed `dp[i+1]` convention — the two conventions differ by exactly one; never combine them
- ❌ Forgetting `min(k, i)` — crashes with negative indices on small prefixes
- ❌ Not resetting `mx = 0` inside the outer loop — the window max leaks across positions
- ❌ Using `dp[i] = ...` (assignment) instead of `dp[i] = max(dp[i], ...)` — you'd only keep the last j tried
- ❌ Piece value = sum instead of `max · j` — every element in the window becomes the max, that's the whole problem

### 🔴 The bounded greedy trap

"Always take the k-length window containing the biggest element" fails — sometimes a smaller window wins (the trace above: at i=3, j=1 beats j=2 and j=3). All lengths must be tried; the nested loop is the DP, not a pointer.

## Pattern Connection

**This is a Segmentation DP problem because:**

1. **1D prefix state**, split into contiguous pieces, each piece must satisfy a condition (length ≤ k).
2. **Scan over piece candidates** — bounded to ≤ k lengths, making it O(n·k).
3. **Max operator** — third segmentation operator you've used (OR in 139, min in 279, max here).

**The Decode Ways bridge — the engine is built:**

|                                  | Piece length         | Piece value           | Recurrence                           |
| -------------------------------- | -------------------- | --------------------- | ------------------------------------ |
| Word Break (139)                 | unbounded            | is a word?            | OR over j                            |
| Perfect Squares (279)            | unbounded            | is a square?          | min(dp[i-s]+1)                       |
| Integer Break (343)              | unbounded            | may stay whole        | max(j·(i−j), j·dp[i−j])              |
| **Partition for Max Sum (1043)** | **≤ k (bounded)**    | **max·len**           | **max over j ≤ k of dp[i-j] + mx·j** |
| **Decode Ways (91, next)**       | **1 or 2 (bounded)** | **valid digit code?** | **gates(dp[i-1]) + gates(dp[i-2])**  |

1043's bounded-window scan is _exactly_ what Decode Ways does with pieces of length 1-2 — and the loop trick above answers Decode Ways' indexing questions too ("how many digits does this piece cover?" → 1 or 2 → `s[i-1]`, `s[i-2]`).

**Similar problems in this pattern:**

- 91 - Decode Ways — bounded pieces (1-2), counting + gates — THE next problem
- 139 - Word Break — unbounded pieces, existence
- 279 - Perfect Squares — unbounded pieces, min

## Key Takeaway

_"Segmentation with bounded pieces: dp[i] = max over last-piece length j ≤ k of dp[i-j] + value(window)·j. And the loop trick: think in ELEMENTS, not indices — i = elements covered, j = how many back, window start = arr[i-j] (1-indexed dp), verified by the j=1 check (arr[i-1] = last element)."_

## 🔑 Breakthrough

_"Two things clicked. (1) The missing move: define the LAST piece as a window of length j ≤ k ending at i, value max·len — I kept thinking forward ('which element anchors a group?') instead of backward ('what's the last piece?'). (2) The loop trick that kills my off-by-ones: think in 'elements I'm considering' — i = elements covered, j = how many back, window start = arr[i-j] (1-indexed), cap = min(k, i). Every wrong index I wrote was a position-vs-count confusion — or worse, mixing the 0-indexed and 1-indexed conventions mid-attempt, which is what happened on 08-15. The question 'how many elements does this piece cover?' fixes all of them, and the j=1 check (arr[i-1] = last element) verifies the convention before coding. And bounded pieces → only k candidates — the same scan Decode Ways needs. The trace confusion also resolved: 54 = [1,15,7]+[9] (45+9), not [1,15]+[7,9] (48)."_

## Your Code

```cpp
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n+1,0);
        for(int i = 1; i<=n; i++){
            int mx = 0;
            for(int j = 1; j<=min(k,i); j++){
                mx = max(mx, arr[i-j]);
                dp[i] = max(dp[i], dp[i-j] + mx*j);
            }
        }
        return dp[n];
    }
};
```

_Your original work — the 1-indexed version (from the 08-15 attempt, which supersedes the earlier 0-indexed submission). This is the convention the whole note now uses._

_Your original work — correct as submitted, and now fully understood._

## Solve Metrics

- **Solve Time:** — (not reported — solution seen)
- **Attempts:** 1 (solution seen)
- **Confidence:** 6/10 — the sole weak spot, third occurrence of the same class
- **Struggles:** Original: couldn't define the piece (a window of length ≤ k with value max·len). Re-solve 08-04: zero struggle (2:02). **Re-solve 08-09: `j < min(k, i+1)` vs `j <=` — runs k−1 lengths.** **Re-solve 08-15: again blocked on the cap/index during the attempt — the final code was correct (1-indexed: `arr[i-j]`, `dp[i-j]`, `j <= min(k, i)`), but mid-attempt the 0-indexed and 1-indexed conventions were getting mixed.** Root cause: convention flipping, not the recurrence. Fix: pick the convention FIRST, then verify with the j=1 check.
- **Key Lesson:** _"Define the piece, pick the convention, then verify: at j=1 the window must be exactly the LAST element (1-indexed: `arr[i-1]`). Then the cap: `j <= min(k, i)`."_
- **Submitted:** 2026-08-01
- **Last Reviewed:** 2026-08-15
- **Next Review:** 2026-08-18 (Day 3) — special protocol: write the j=1 check and the cap BEFORE the loops, then code.

---

**Generated:** 2026-08-01
