# 3857 - Minimum Cost to Split into Ones

**Pattern Type:** Interval DP (1D split-cost variant — first problem in this family!)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/minimum-cost-to-split-into-ones/
**Topics:** Split-cost DP, both-sides recursion, min operator, first-split decomposition

## Problem Statement

Given an integer `n`, split it into `n` ones. Each operation splits an integer `x` into `a + b = x`, costing `a * b`. Return the **minimum total cost** to reach all ones.

**Constraints:**

- `2 ≤ n` (problem's exact bound not stated — DP handles any n; answer is O(n²))

## State Definition

### What is dp[i]?

```
dp[i] = minimum total cost to split the integer i into i ones
```

**Examples:**

- `dp[1] = 0` — a 1 is already a one; no split needed
- `dp[2] = 1` — 2 → 1+1 costs 1·1 = 1
- `dp[4] = 6` — 4 → 2+2 (cost 4), then each 2 → 1+1 (cost 1 + 1): total 6

### Why This State?

The problem is recursive by nature: the **first split** of `i` produces two children `j` and `i-j`, and *both children must be fully split into ones*. So the total cost is:

```
first split cost + cost to reduce the left child + cost to reduce the right child
```

That's `j·(i−j) + dp[j] + dp[i−j]` — and both `j` and `i−j` are smaller totals, already solved. The state is 1D over the total (not a 2D range) because the object being split is just a number.

## Recurrence Relation

```
dp[i] = min over every split point j in [1, i-1] of:
            dp[j] + dp[i - j] + j * (i - j)

Base cases:
  dp[0] = 0
  dp[1] = 0        (already a one — zero cost)

Answer:
  dp[n]
```

### Transition Logic

**Step 1:** Decide the **first split**: `i` → `j` and `i−j` (any j from 1 to i−1; scan-all-previous — try every split).

**Step 2:** Pay for THIS split right now: `j·(i−j)`.

**Step 3:** Both children are not done yet — each must be fully reduced: add `dp[j] + dp[i−j]`. Take the min over all splits.

> **🔑 The signature of the interval/split-cost family — BOTH sides recurse, the cost is on the SPLIT itself.** This is what separates it from segmentation (Word Break, Perfect Squares, Coin Change, 377): there, the right side was consumed as a single valid *piece* and the left was the prefix subproblem (`dp[i−x] + 1`). Here, neither side stays whole — every piece must be split all the way down, and you pay for the act of splitting, not for the pieces. That's the same shape as "merge two sub-ranges + cost of merging" — Matrix Chain Multiplication's 1D cousin.

### Example Walkthrough

Input: `n = 5`

```
dp[0] = 0, dp[1] = 0
dp[2] = min(dp[1] + dp[1] + 1·1)                       = 1
dp[3] = min(dp[1]+dp[2]+1·2, dp[2]+dp[1]+2·1)          = 3
dp[4] = min(dp[1]+dp[3]+1·3, dp[2]+dp[2]+2·2, ...)     = 6
dp[5] = min(dp[2]+dp[3]+2·3, dp[1]+dp[4]+1·4, ...)     = 10
```

Answer: `dp[5] = 10`. One optimal sequence: 5 → 2+3 (cost 6), 2 → 1+1 (1), 3 → 1+2 (2), 2 → 1+1 (1). Total 6+1+2+1 = **10**.

**Fun invariant (sanity check):** the answer is always `n·(n−1)/2` — every split separates some pairs of final ones, and each pair separates exactly once, paying 1 per pair. `dp[5] = 10 = C(5,2)` ✓. The DP computes this without knowing the formula — the formula just confirms it.

## Implementation (C++)

```cpp
// Your solution (canonical loop bounds)
int minCost(int n) {
    vector<int> dp(n + 1, 1e7);
    dp[0] = 0;
    dp[1] = 0;                          // already a one
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; j++) {   // j from 1 (j=0 is dead self-reference)
            dp[i] = min(dp[i], dp[j] + dp[i - j] + j * (i - j));
        }
    }
    return dp[n];
}
```

**Key Implementation Notes:**

- **`j = 1`, not `0`:** your `j = 0` iteration is a harmless self-reference (`dp[i] + dp[0] + 0` re-proposes the current value, never wins the min) — dead work, not a bug. Same quirk as in 343.
- **Base cases are the "already done" cases:** `dp[1] = 0` — a 1 is a final one, cost 0. `dp[0] = 0` for completeness (never actually split).
- **The sentinel `1e7`** is fine — max answer for reasonable n is `n(n−1)/2`, and `1e7` dwarfs it.
- Both `dp[j]` and `dp[i−j]` are read — the inner loop needs the full array (no rolling-variable optimization; it's scan-all-previous).

## Complexity Analysis

- **Time:** O(n²)
  - Reason: for each of n totals, we try every split j < i.
- **Space:** O(n)
  - The 1D variant is cheaper than the classic 2D interval template's O(n²) space — the "range" here is just `[0, i]`, so the second dimension collapses.

## Why This Approach Works

By induction on `i`: any valid reduction sequence of `i` begins with exactly one first split `i → j + (i−j)`, paying `j(i−j)`, followed by an arbitrary reduction of `j` and of `i−j` (valid by induction, costing at least `dp[j]` and `dp[i−j]`). So the true minimum is the min over all first splits of `j(i−j) + dp[j] + dp[i−j]`. Conversely, any choice of j with optimal child reductions is a real sequence, so the min is achievable. Every split in the whole process is counted exactly once (only the first split is charged here; children's costs account for the rest) — no double counting.

## Common Pitfalls in This Pattern

### 🔴 Confusing "must split" with "may stay whole" (the 343 confusion)

This is the same skeleton as Integer Break with two differences:

| | Integer Break (343) | Split into Ones (3857) |
| --- | --- | --- |
| Policy | a piece may **stay whole** | both pieces **must** be fully split |
| Recurrence | `max(j·(i−j), j·dp[i−j])` | `dp[j] + dp[i−j] + j·(i−j)` |
| Operator | max (product) | min (cost) |

If you drop `dp[j] + dp[i−j]` from this recurrence, you're only paying for the first split — the children's reductions vanish. If you add a "stay whole" term, you invent an illegal move (a piece > 1 can never stay). The problem statement decides the policy: *"split until all are ones"* → must-split.

### Other Common Mistakes

- **Missing one child:** `dp[i−j] + j·(i−j)` forgets the left child. BOTH sides recurse here — that's the whole difference from Coin Change-style `dp[i−x] + 1`.
- **Base cases:** `dp[1]` must be 0 (already a one). If it's left at the sentinel, every recurrence that touches `dp[1]` (i.e., every one) breaks.
- **`j` bounds:** `j < i` — a "split" into `i + 0` is not a split.
- **Scan-all-previous violation:** greedy split (e.g., always halve) happens to be fine here because the total cost is invariant — but only the full scan is provably optimal for the family. Don't build the greedy habit.

## Pattern Connection

**This is an Interval DP problem (1D variant) because:**

1. **Split-point decision:** the recurrence chooses where to split `[0, i]` into two independent sub-problems — the interval template's `dp[i][k] + dp[k][j] + cost`, collapsed to 1D since the object is a number.
2. **Both sides recurse with a split cost:** the "last/first action" framing from the template — you choose the split, pay for it, and the two halves become independent.
3. **Cost depends on the pieces' sizes** (`j·(i−j)`), like MCM's `p·q·r` merge cost — not on a per-piece validity test (that would be segmentation).

**Within the family, this is the 1D warm-up:** the classic 2D forms (1039 Minimum Score Triangulation, 312 Burst Balloons) use `dp[i][j]` over ranges with `cost(i, k, j)` — same idea, bigger state. You've now seen the split-cost shape at its simplest.

**Similar problems in this pattern:**

- 343 - Integer Break — same split skeleton, "may stay whole" + max (see [segmentation-dp/343_Integer_Break.md](../segmentation-dp/343_Integer_Break.md))
- 1130 - Minimum Cost Tree From Leaf Values — split-cost over ranges
- 1039 - Minimum Score Triangulation — the 2D upgrade (Week 5)
- 312 - Burst Balloons — the classic (Week 5)

## Key Takeaway

_"Split problems come in two flavors: segmentation (one piece stays whole / passes a test) and interval split-cost (BOTH sides recurse, you pay for the split). Ask: 'do both children need full solutions?' If yes: dp[i] = min over j of dp[j] + dp[i−j] + cost(j, i−j)."_

## 🔑 Breakthrough

_"The condition I kept groping for: EVERY piece must be split all the way down, and the cost is on the split itself. That's why the recurrence is dp[j] + dp[i−j] + j·(i−j) — both children recurse (unlike Coin Change where the remainder is consumed as dp[i−x] + 1, and unlike Integer Break where a piece may stay whole: max(j·(i−j), j·dp[i−j])). Same skeleton, three different policies. And the sanity check that made it click: every pair of final ones separates exactly once, so the answer is always n(n−1)/2 — the DP silently agrees."_

## Your Code

```cpp
class Solution {
public:
    int minCost(int n) {
        vector<int> dp(n+1,1e7);
        dp[0]=0;
        dp[1]=0;
        for(int i = 1; i<=n; i++){
            for(int j = 0; j<i; j++){
                dp[i] = min(dp[i], dp[i-j]+dp[j]+(i-j)*j);
            }
        }
        return dp[n];
    }
};
```

_Your original work — correct as submitted. The `j = 0` start is dead self-reference; `j = 1` is the intended bound._

## Solve Metrics

- **Solve Time:** — (not reported)
- **Attempts:** — (not reported)
- **Confidence:** 6/10 — STILL WEAK, stays on rotation
- **Struggles:** "Need to think more about the conditions" — pinning down that BOTH children must recurse and that the split itself is what you pay for. Re-solve 08-04: **forgot the `+dp[j]` term again** (15:45, the slowest re-solve of the session). Substituted an accidental `max` variant that passes ONLY because the total cost is invariant (always n(n−1)/2 — every pair of units separates exactly once) — it would break for any non-invariant cost. Structural lesson: both children recurse; an accidental AC is not understanding.
- **Key Lesson:** _"Both sides recurse + split cost = interval family. One side whole = segmentation family. Read the policy from the statement. And: a passing answer is not the same as the right recurrence."_
- **Submitted:** 2026-08-01
- **Last Reviewed:** 2026-08-04
- **Next Review:** 2026-08-08 (Day 7) — re-solve, target < 10 min, MUST write `min over j of dp[j] + dp[i-j] + j·(i-j)` with BOTH children. Then 2026-08-15 (Day 14).

---

**Generated:** 2026-08-01
