# 279 - Perfect Squares

**Pattern Type:** Segmentation DP
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/perfect-squares/
**Topics:** Segmentation, min-cost recurrence, last-piece decomposition, Coin Change connection

## Problem Statement

Given an integer `n`, return the **least number of perfect square numbers** (1, 4, 9, 16, ...) that sum to `n`.

**Constraints:**

- `1 ≤ n ≤ 10⁴`

## State Definition

### What is dp[i]?

```
dp[i] = minimum number of perfect squares needed to sum to exactly i
```

**Examples:**

- `dp[0] = 0` — 0 needs 0 squares (base case)
- `dp[4] = 1` — 4 is itself a perfect square
- `dp[12] = 3` — 12 = 4 + 4 + 4

### Why This State?

Same reason as Word Break: the problem is about **splitting a total into pieces**, where each piece must pass a test (here: _be a perfect square_). The natural subproblem is a smaller total `i`, because any valid representation of `i` ends with some last square `s`, and everything before it is a valid representation of `i - s`.

The one difference from Word Break: instead of _existence_ (`dp[i]` = can we?), we track the _minimum count_ (`dp[i]` = fewest pieces). Same skeleton, different combine operator: `min` instead of `OR`.

## Recurrence Relation

```
dp[i] = min over every square s ≤ i of ( dp[i - s] + 1 )

Base case:
  dp[0] = 0

Answer:
  dp[n]
```

### Transition Logic

**Step 1:** To build total `i`, pick the **last square you add** — call it `s` (any perfect square with `s ≤ i`).

**Step 2:** Everything before that last square must itself be a minimal representation of `i - s`, which is exactly `dp[i - s]`. Adding the square `s` costs 1 more piece.

**Step 3:** Try **every** square `s ≤ i` and take the minimum. The nested loop over all squares is structurally required — the last piece could be any square, and committing to one guess loses the answer (exactly the Word Break greedy trap).

> **🔑 This is a scan-all-previous problem — but the "previous states" are indexed by the piece value:**
>
> - **Fixed-offset Linear DP** (House Robber): dp[i] looks back at dp[i-1], dp[i-2] only.
> - **Scan-all-previous** (Word Break, Perfect Squares): dp[i] must check ALL possible last pieces. In Word Break you scan cut points `j`; here you scan square values `s`. Both are nested loops. `dp[i - s]` with `s` = perfect square ⟺ `dp[j]` where `i - j` is a perfect square — same thing, two notations.
> - **How to tell:** if the last piece can be _any_ element of a set (dictionary word / square / coin), you must scan all of them.

### Example Walkthrough

Input: `n = 12`, squares = [1, 4, 9]

```
dp[0]  = 0
dp[1]  = dp[0]+1                          = 1
dp[2]  = dp[1]+1                          = 2
dp[3]  = dp[2]+1                          = 3
dp[4]  = min(dp[3]+1, dp[0]+1)            = 1   (4 itself)
dp[5]  = min(dp[4]+1, dp[1]+1)            = 2
dp[6]  = min(dp[5]+1, dp[2]+1)            = 3
dp[7]  = min(dp[6]+1, dp[3]+1)            = 4
dp[8]  = min(dp[7]+1, dp[4]+1)            = 2   (4+4)
dp[9]  = min(dp[8]+1, dp[5]+1, dp[0]+1)   = 1   (9 itself)
dp[10] = min(dp[9]+1, dp[6]+1, dp[1]+1)   = 2   (9+1)
dp[11] = min(dp[10]+1, dp[7]+1, dp[2]+1)  = 3   (9+1+1)
dp[12] = min(dp[11]+1, dp[8]+1, dp[3]+1)  = 3   (4+4+4)
```

Answer: `dp[12] = 3` — because choosing the last square `4` leaves `i - s = 8`, and `dp[8] = 2` (4+4), so `2 + 1 = 3`.

## Implementation (C++)

```cpp
// Precompute squares, then min-cost DP (the Coin Change shape)
int numSquares(int n) {
    vector<int> sqr;
    for (int s = 1; s * s <= n; s++)
        sqr.push_back(s * s);

    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int s : sqr) {
            if (s > i) break;              // squares are sorted ascending
            dp[i] = min(dp[i], dp[i - s] + 1);
        }
    }
    return dp[n];
}
```

```cpp
// The exact Word Break skeleton — scan all cut points j, test the piece
int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            int r = sqrt(i - j);
            if (r * r == i - j)            // piece (j, i] is a perfect square
                dp[i] = min(dp[i], dp[j] + 1);
        }
    }
    return dp[n];
}
```

**Key Implementation Notes:**

- **Your code already has the right shape.** The `break` inside the inner loop is valid because `sqr` is built ascending — once `num > i`, every later square is also `> i`.
- **`INT_MAX - 1000` (or `INT_MAX / 2`) instead of `INT_MAX`**: `dp[i - s] + 1` would overflow on `INT_MAX`. Any large sentinel below `INT_MAX - n` works.
- **Building squares directly** (`s * s <= n`) is cleaner than sqrt-checking every `i` from 1 to n — same result, no float math.
- Loop bounds: `dp[n]` must be computed, so the outer loop goes to `i <= n`, inner squares only while `s <= i`.

## Complexity Analysis

- **Time:** O(n√n)
  - Reason: ~√n squares, and for each of the n totals we try every square `s ≤ i`. (#states n) × (work per state √n).
- **Space:** O(n) for the dp array (+ O(√n) for the squares list).
  - No constant-space optimization here — unlike fixed-offset DP, `dp[i]` depends on `dp[i - s]` for many different `s`, so you need the full array.

## Why This Approach Works

By induction on `i`: assume `dp[k]` is the true minimum square count for every `k < i`. Any representation of `i` has a last square `s`, and removing it leaves a representation of `i - s` using `dp[i - s]` squares, so no representation beats `min over s of (dp[i - s] + 1)`. Conversely, taking the best `i - s` and appending `s` is a valid representation of `i`. So the recurrence is both an upper and lower bound — it's exact. Base case `dp[0] = 0` bootstraps the chain.

## Common Pitfalls in This Pattern

### 🔴 The Greedy Trap (Scan-All-Previous problems)

Same trap as Word Break: grabbing the **largest** square ≤ remaining (greedy) fails. Example: `n = 12` → greedy takes 9, leaving 3 → 3+1+1+1 = 4 pieces, but the optimum is 4+4+4 = 3 pieces. You **must try every square** as the last piece, not commit to the biggest one.

### Other Common Mistakes

- **Forgetting `dp[0] = 0`**: without it, no square can ever bootstrap (`dp[s]` would need `dp[0]`).
- **Overflow**: initializing with `INT_MAX` and adding 1 overflows. Use `INT_MAX - 1000` or `INT_MAX / 2` as the sentinel.
- **Inner loop bound**: `if (num > i) break;` is required — `dp[i - num]` would be negative-indexed garbage otherwise.
- **Confusing the two notations**: `dp[j] + 1` where `(i - j)` is a square (Word Break style) and `dp[i - s] + 1` where `s` is a square (your style) are the **same** recurrence — don't think they're different algorithms.

## Pattern Connection

**This is a Segmentation DP problem because:**

1. **1D state** over a total/prefix, split into contiguous pieces (here: additive pieces of a sum).
2. **Every piece must pass a test** — Word Break: piece is a dictionary word; here: piece is a perfect square.
3. **Scan-all-previous recurrence** — try every possible last piece, take the best.

**The family table (min-cost variant):**

| Problem                   | What the piece must be    | dp[i] tracks        | Combine |
| ------------------------- | ------------------------- | ------------------- | ------- |
| Word Break                | A dictionary word         | Reachable?          | OR      |
| **Perfect Squares**       | A perfect square          | Min pieces to sum i | min     |
| Coin Change (322)         | A coin denomination       | Min coins for i     | min     |
| Decode Ways (91, next up) | A valid 1 or 2-digit code | # ways to decode    | +       |

**Big connection — Perfect Squares is literally Coin Change with `coins = {1, 4, 9, 16, ...}`.** Same state, same recurrence, same code skeleton. If you solve one, you've solved the other (322 - Coin Change is queued in Week 4 — you'll see this code again).

**Similar problems in this pattern:**

- 322 - Coin Change — identical recurrence, arbitrary coin set
- 91 - Decode Ways — same skeleton, counting ways instead of minimizing
- 139 - Word Break — same skeleton, existence instead of minimizing

## Key Takeaway

_"To minimize the number of pieces summing to n, ask 'what's the LAST piece?' — dp[i] = min over every valid piece p ≤ i of (dp[i - p] + 1). Enumerate all pieces, don't greedily commit to one."_

## 🔑 Breakthrough

_"I knew the pieces — enumerate all the squares — but couldn't write the DP formula. The missing step was the **state**: dp[i] = minimum squares to make exactly i. Once the state exists, the recurrence writes itself by asking **'what's the last square I add?'**: every representation of i ends in some square s, and the rest is just a representation of i - s. So dp[i] = min(dp[i-s] + 1) over all squares. I was holding the ingredients (squares) without the recipe (state + last-piece question). It's the exact Coin Change code with coins = squares."_

## Your Code

```cpp
class Solution {
public:
    int numSquares(int n) {
        vector<int> sqr;
        for(int i = 1; i<=n; i++){
            int x = sqrt(i);
            if(x*x == i) sqr.push_back(i);
        }
        vector<int> dp(n+1, INT_MAX-1000);
        dp[0] = 0;
        for(int i = 1; i<n+1; i++){
            for(int num : sqr){
                if(num>i) break;
                int left=i-num;
                dp[i]=min(dp[i], dp[left]+1);
            }
        }
        return dp[n];
    }

};
```

_Your original work — the recurrence and the `break` on sorted squares are correct. The only growth area: deriving the state definition from scratch next time._

## Solve Metrics

- **Solve Time:** N/A — couldn't solve independently (completed with reference)
- **Attempts:** N/A
- **Confidence:** 9/10
- **Struggles:**
  1. Knew the ingredients (use all squares) but couldn't define the state
  2. Didn't see the **last-piece decomposition** — "every representation ends in one square, the rest is a smaller subproblem"
  3. Hadn't yet connected this to Coin Change / segmentation family
- **Key Lesson:** _"State first, recurrence second. dp[i] = min squares to make i; then the last square question writes the formula."_
- **Submitted:** 2026-08-01
- **Last Reviewed:** 2026-08-04
- **Next Review:** **Mastered.** Re-solved 2026-08-04 in **3:03** (9/10) — wrote `dp[i] = min(dp[i-s]+1)` cold. Lesson banked: dp init — **0 for sums/counts, a BIG value for min problems**.

**Re-solve Log:**

- 2026-08-04: 3:03, 9/10 — state and recurrence came out without hesitation; the one thing to always check is dp initialization (sentinel for min). Confidence 4 → 9/10.

---

**Generated:** 2026-08-01
