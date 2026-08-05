# 1043 - Partition Array for Maximum Sum

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
for (int i = 0; i < n; i++) {                    // i = current position (0 to n-1)
    for (int j = 1; j <= min(k, i + 1); j++) {   // j = how many elements back?
```

**Ask yourself:**

1. **How many elements have I seen so far?** → `i+1` (indices 0 through i)
2. **Can I partition i+1 elements?** → yes, but max `k` at a time → `min(k, i+1)`
3. **Which element is at position j steps back?** → `arr[i-j+1]`

**Memory aid:**

| j     | Window start            | Meaning         |
| ----- | ----------------------- | --------------- |
| j = 1 | `arr[i-1+1] = arr[i]`   | current element |
| j = 2 | `arr[i-2+1] = arr[i-1]` | one back        |
| j = k | `arr[i-k+1]`            | k elements back |

**Why it kills the off-by-ones:** every wrong index in this problem is the same mistake — thinking in positions instead of counts. `arr[i-j+1]` is "the element that starts a j-element window ending at i"; `dp[i-j+1]` is "the best for everything before that window." The question _"how many elements does this piece cover?"_ resolves both. Same question applies to Decode Ways (`j ∈ {1,2}`), Word Break (piece = `s[i-j..i-1]` of length j), and every scan-all-previous recurrence.

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
// Your solution — with the loop trick annotated
int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n + 1, 0);          // dp[i+1] corresponds to arr[0..i]
    for (int i = 0; i < n; i++) {      // i = current position
        int mx = 0;                    // max of the window — RESET per i
        for (int j = 1; j <= min(k, i + 1); j++) {   // j = piece size (1..k, capped)
            mx = max(mx, arr[i - j + 1]);            // window start = j elements back
            dp[i + 1] = max(dp[i + 1], dp[i - j + 1] + mx * j);  // try this piece
        }
    }
    return dp[n];
}
```

**Key Implementation Notes:**

- **The running `mx` trick:** as `j` grows, the window extends _leftward_ one element at a time, so `mx = max(mx, arr[i-j+1])` maintains the window max in O(1) per candidate.
- **`mx` must be reset inside the outer loop** (per `i`), not outside.
- **Use `max(dp[i+1], ...)`, never assignment** — each state accumulates the best over all `j`.
- **The bound `min(k, i+1)` is load-bearing** — without it, negative indices when the window would run past the array start.
- `dp[0] = 0` bootstraps: a piece covering the whole prefix uses `dp[0] + max·i`.

## Complexity Analysis

- **Time:** O(n·k) — for each of n prefixes, at most k window lengths.
- **Space:** O(n) — dp[i] reads dp[i-j] for j up to k, so you need the array (or a k-window ring).

## Why This Approach Works

By induction on `i`: any valid partition of the first `i` elements has a last piece of length `j ≤ k` covering `i-j+1..i`, contributing `max·j`; the prefix before it is validly partitioned, costing at least `dp[i-j]`. Scanning every `j` covers every partition exactly once (unique last piece), so the max is exact. Base `dp[0] = 0` bootstraps.

## Common Mistakes to Avoid (your checklist)

- ❌ Using `arr[i-j]` instead of `arr[i-j+1]` — the window start is **j elements back**, i.e. index `i-j+1` when the window ends at `i`
- ❌ Using `dp[i-j]` when you mean `dp[i-j+1]` — with the `dp[i+1] = arr[0..i]` convention, "before the window" is `dp[i-j+1]`
- ❌ Forgetting `min(k, i+1)` — crashes with negative indices on small prefixes
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

_"Segmentation with bounded pieces: dp[i] = max over last-piece length j ≤ k of dp[i-j] + value(window)·j. And the loop trick: think in ELEMENTS, not indices — i = current position, j = how many back, window start = arr[i-j+1]."_

## 🔑 Breakthrough

_"Two things clicked. (1) The missing move: define the LAST piece as a window of length j ≤ k ending at i, value max·len — I kept thinking forward ('which element anchors a group?') instead of backward ('what's the last piece?'). (2) The loop trick that kills my off-by-ones: think in 'elements I'm considering' — i = current position, j = how many elements back, so the window start is arr[i-j+1] and the cap is min(k, i+1). Every wrong index I wrote was a position-vs-count confusion; the question 'how many elements does this piece cover?' fixes all of them. And bounded pieces → only k candidates — the same scan Decode Ways needs. The trace confusion also resolved: 54 = [1,15,7]+[9] (45+9), not [1,15]+[7,9] (48)."_

## Your Code

```cpp
class Solution {
public:
    int maxSumAfterPartitioning(vector<int>& arr, int k) {
        int n = arr.size();
        vector<int> dp(n+1, 0);  // dp[i+1] corresponds to arr[0...i]

        for(int i = 0; i < n; i++){
            int mx = 0;
            // j = partition size (1 to k, but can't exceed i+1 elements)
            for(int j = 1; j <= min(k, i+1); j++){
                // Find max in the partition [i-j+1 ... i]
                mx = max(mx, arr[i-j+1]);
                // Try this partition: previous best + (max * size)
                dp[i+1] = max(dp[i+1], dp[i-j+1] + mx*j);
            }
        }
        return dp[n];
    }
};
```

_Your original work — correct as submitted, and now fully understood._

## Solve Metrics

- **Solve Time:** — (not reported — solution seen)
- **Attempts:** 1 (solution seen)
- **Confidence:** 10/10 — re-solved 08-04 in **2:02** (from 3/10). The loop trick now fully internalized: outer i = position, go back min(k, i+1), index via dp[i-j+1]. User still wants a lock-in re-solve on 08-08 ("might forget it") — scheduled.
- **Struggles:** Original: couldn't define the piece (a window of length ≤ k with value max·len). Re-solve: zero struggle; the only lingering question was why outer loop starts at i=0 (answer: 1-indexed dp makes bounds trivial).
- **Key Lesson:** _"Defining the piece IS the state. And when indexing a window: count elements, don't name positions."_
- **Submitted:** 2026-08-01
- **Last Reviewed:** 2026-08-04
- **Next Review:** 2026-08-08 (Day 7, user-requested lock-in re-solve), then 2026-08-15 (Day 14, optional).

---

**Generated:** 2026-08-01
