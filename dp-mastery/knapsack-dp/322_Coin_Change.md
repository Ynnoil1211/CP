# 322 - Coin Change

**Pattern Type:** Knapsack DP (unbounded, min coins)
**Difficulty:** Medium
**LeetCode Link:** https://leetcode.com/problems/coin-change/
**Topics:** Unbounded knapsack, min-count recurrence, last-coin decomposition, unreachable detection

## Problem Statement

Given an array of coin denominations (unlimited supply of each) and an `amount`, return the **fewest number of coins** needed to make up that amount. If it's impossible, return `-1`.

**Constraints:**

- `1 ≤ coins.length ≤ 12`
- `1 ≤ coins[i] ≤ 2³¹ - 1`
- `0 ≤ amount ≤ 10⁴`

## State Definition

### What is dp[i]?

```
dp[i] = minimum number of coins needed to make exactly amount i
```

**Examples:**

- `dp[0] = 0` — amount 0 needs 0 coins (base case)
- `dp[5] = 1` for coins [1, 2, 5] — one 5-coin
- `dp[11] = 3` for coins [1, 2, 5] — 5 + 5 + 1

### Why This State?

Exactly the Perfect Squares state, with squares swapped for coins: any way of making amount `i` ends with some **last coin** `c`, and everything before it is a way of making `i - c`. So the subproblem is a smaller amount. "Minimum pieces to build a total" is a capacity-style problem → knapsack family.

The one **new** thing vs 279: unreachable amounts exist. `dp[i]` can stay at the sentinel value, and the answer is `-1` if `dp[amount]` never became finite.

## Recurrence Relation

```
dp[i] = min over every coin c ≤ i of ( dp[i - c] + 1 )

Base case:
  dp[0] = 0

Answer:
  dp[amount], or -1 if dp[amount] is still the INF sentinel
```

### Transition Logic

**Step 1:** To make amount `i`, pick the **last coin added** — any denomination `c ≤ i`.

**Step 2:** The rest is a minimal coin combination for `i - c`, which is exactly `dp[i - c]`. Adding coin `c` costs +1.

**Step 3:** Try **every** coin ≤ `i` and take the minimum — the last coin could be any denomination, so scanning all of them is structurally required (same scan-all-previous principle as Word Break / Perfect Squares).

> **🔑 Unbounded vs 0/1 — the loop direction is the whole trick:**
>
> - **Unbounded (this problem):** coins may repeat → you may re-enter `dp[i-c]` that itself used the same coin. That's correct and desired here.
> - **0/1 knapsack (Partition Equal Subset Sum):** each item once → you must iterate capacity **backwards** (`for cap = target down to w`) so an item can't be used twice.
> - **How to tell:** "unlimited supply / unlimited times" → forward, unbounded. "Each item at most once" → backward, 0/1. Same skeleton, one flipped loop.

### Example Walkthrough

Input: `coins = [1, 2, 5]`, `amount = 11`

```
dp[0]  = 0
dp[1]  = dp[0]+1                          = 1
dp[2]  = min(dp[1]+1, dp[0]+1)            = 1
dp[3]  = min(dp[2]+1, dp[1]+1)            = 2
dp[4]  = min(dp[3]+1, dp[2]+1)            = 2
dp[5]  = min(dp[4]+1, dp[3]+1, dp[0]+1)   = 1
dp[6]  = min(dp[5]+1, dp[4]+1, dp[1]+1)   = 2
dp[7]  = min(dp[6]+1, dp[5]+1, dp[2]+1)   = 2
dp[8]  = min(dp[7]+1, dp[6]+1, dp[3]+1)   = 3
dp[9]  = min(dp[8]+1, dp[7]+1, dp[4]+1)   = 3
dp[10] = min(dp[9]+1, dp[8]+1, dp[5]+1)   = 2
dp[11] = min(dp[10]+1, dp[9]+1, dp[6]+1)  = 3
```

Answer: `dp[11] = 3` — choosing last coin `5` leaves `11 - 5 = 6`, and `dp[6] = 2` (5+1), so `2 + 1 = 3`.

Unreachable case: `coins = [2]`, `amount = 3` → `dp[1]` and `dp[3]` never get updated (no coin ≤ 1), so `dp[3]` stays `INF` → return `-1`.

## Implementation (C++)

```cpp
// Your solution — sorted coins + early break
int coinChange(vector<int>& coins, int amount) {
    sort(coins.begin(), coins.end());
    vector<int> dp(amount + 1, INT_MAX - 10000);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        for (int c : coins) {
            if (c > i) break;          // coins sorted: everything after is also > i
            dp[i] = min(dp[i], dp[i - c] + 1);
        }
    }
    return dp[amount] == INT_MAX - 10000 ? -1 : dp[amount];
}
```

**Key Implementation Notes:**

- **The `break` must compare against `i` (the current subproblem), not `amount`.** A coin bigger than the subproblem `i` can't be used (would index `dp[i - c] < 0`). Your bug was `if (x < amount) break` — wrong variable AND wrong direction. Since `x < amount` is almost always true, the loop broke after the FIRST coin, silently using only the smallest denomination.
- **Sorting + break is optional** — you could skip the sort and write `if (c > i) continue;`. The break is just the sorted shortcut.
- **Sentinel `INT_MAX - 10000`** avoids overflow when adding 1 (amount ≤ 10⁴, so this is safe). Check the sentinel with `==`, not `>=` — amounts can't legitimately reach it.
- `dp[0] = 0` bootstraps every exact-denomination amount: `dp[5] = dp[0] + 1`.

## Complexity Analysis

- **Time:** O(amount × n) where n = number of coin types
  - Reason: for each of `amount` states, we try all n coins (the sorted break only skips the oversize tail).
- **Space:** O(amount) for the dp array.
  - No constant-space version — dp[i] depends on many different `dp[i - c]`.

## Why This Approach Works

By induction on `i`: assume `dp[k]` is the true minimum coin count for all `k < i`. Any combination making `i` has a last coin `c`, and removing it leaves a combination of `i - c` with `dp[i - c]` coins — so nothing beats `min over c of (dp[i - c] + 1)`. Conversely, the best combination for `i - c` plus coin `c` is a valid combination for `i`. If no coin ≤ `i` exists, every representation is impossible and `dp[i]` correctly stays infinite. Base case `dp[0] = 0` bootstraps.

## Common Pitfalls in This Pattern

### 🔴 The Greedy Trap

Greedy "always take the largest coin" fails. Example: `coins = [1, 3, 4]`, `amount = 6` → greedy takes 4, then 1, then 1 = **3 coins**, but the optimum is 3 + 3 = **2 coins**. You must scan every coin as the last one — the nested loop is the DP, not a single pointer.

### Other Common Mistakes

- **The `x < amount` vs `x > i` bug (your bug):** the break guard must use the *current subproblem* `i`. Comparing against the total `amount` (or flipping the direction) silently breaks the DP — it still compiles and returns *an* answer, just a wrong one.
- **Forgetting unreachable amounts:** without the sentinel check, you'd return `INF` (or garbage) instead of `-1`. LeetCode requires exactly `-1`.
- **Overflow:** `dp[i - c] + 1` on plain `INT_MAX` overflows. Use `INT_MAX - n` or `INT_MAX / 2` as the sentinel.
- **Missing `dp[0] = 0`:** no amount exactly equal to a coin could ever bootstrap.

## Pattern Connection

**This is a Knapsack DP problem because:**

1. **Capacity/target framing**: make *exactly* amount `i` — the state is capacity used.
2. **Selection with reuse**: unlimited coins → **unbounded** knapsack → forward iteration is fine (your nested loop over coins inside the amount loop IS the forward sweep).
3. **Min-count objective**: `min` combine operator over all item choices.

**The family bridge — this is Perfect Squares with coins in place of squares:**

| Problem            | "Items"          | Reuse? | Objective      | Unreachable? |
| ------------------ | ---------------- | ------ | -------------- | ------------ |
| Perfect Squares    | squares ≤ n      | yes    | min pieces     | no (1 exists) |
| **Coin Change**    | coin denominations | yes  | min coins      | **yes → -1**  |

Same state `dp[i]`, same recurrence `dp[i] = min(dp[i - item] + 1)`, same nested loop. That's why this took you 5 minutes — you'd already written this code as 279.

**Similar problems in this pattern:**

- 279 - Perfect Squares — identical code, squares instead of coins (see [segmentation-dp/279_Perfect_Squares.md](../segmentation-dp/279_Perfect_Squares.md))
- 416 - Partition Equal Subset Sum — 0/1 knapsack, reachability, *backward* loop
- 494 - Target Sum — 0/1 knapsack, counting ways
- 474 - Ones and Zeroes — knapsack with TWO capacities

## Key Takeaway

_"Minimum coins to make an amount: dp[i] = min over every coin c ≤ i of (dp[i-c] + 1). Unlimited coins = unbounded knapsack = forward sweep. And the inner-loop break compares against i (the subproblem), never the total amount."_

## 🔑 Breakthrough

_"The 279 → 322 transfer worked exactly as predicted — I wrote the Perfect Squares code again with coins swapped in, in 5 minutes. The only stumble was a bug I couldn't see: I wrote `if(x < amount) break` instead of `if(x > i) break` — comparing to the total amount instead of the current subproblem i. Since the break fired after the first coin, my DP silently used only the smallest coin. The guard must always be against the state you're computing, not the global target."_

## Your Code

```cpp
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        sort(coins.begin(), coins.end());
        vector<int> dp(amount + 1, INT_MAX-10000);
        dp[0] = 0;
        for(int i = 1; i<=amount; i++){
            for(int x : coins){
                if (x>i) break;
                dp[i] = min(dp[i], dp[i-x]+1);
            }
        }
        if(dp[amount] == INT_MAX-10000) return -1;
        else return dp[amount];
    }
};
```

_Your original work — correct as submitted. The buggy version (`x < amount`) is preserved in your memory; it's the classic wrong-guard mistake._

## Solve Metrics

- **Solve Time:** 5 minutes
- **Attempts:** 1 (one AI-assisted debug of the `x < amount` guard)
- **Confidence:** 9/10
- **Struggles:** Only the break guard — `if (x < amount)` instead of `if (x > i)`. Couldn't see it yourself, but understood instantly once pointed out.
- **Key Lesson:** _"Inner-loop guards compare against the current state (i), never the global target (amount)."_
- **Submitted:** 2026-08-01
- **Last Reviewed:** 2026-08-01
- **Next Review:** Day 3 (2026-08-04) quick re-solve to lock in — then **mastered**. Per schedule, 8-10 confidence: no Day 7 review needed.

---

**Generated:** 2026-08-01
