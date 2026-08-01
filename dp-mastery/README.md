# 100 DP Medium Problems Challenge

**Progress:** 5/100 problems solved
**Current Week:** Week 3 (Linear + Segmentation DP)
**Target Completion:** TBD
**Overall Confidence:** 5.0/10 (est.)

## Pattern Library

Each pattern folder starts with a `README.md` — the full pattern explanation (description, when to recognize it, general template, problem family, core intuition) followed by **your solved problems** in that family.

- **Linear / Sequence DP** → [`linear-dp/README.md`](linear-dp/README.md)
- **Segmentation DP** → [`segmentation-dp/README.md`](segmentation-dp/README.md)
- **2D Grid / Path DP** → [`2d-grid-dp/README.md`](2d-grid-dp/README.md)
- **Two-Sequence DP (LCS)** → [`lcs-dp/README.md`](lcs-dp/README.md)
- **Knapsack DP** → [`knapsack-dp/README.md`](knapsack-dp/README.md)
- **Interval DP** → [`interval-dp/README.md`](interval-dp/README.md)
- **Tree DP** → [`tree-dp/README.md`](tree-dp/README.md)
- **State Machine DP** → [`state-machine-dp/README.md`](state-machine-dp/README.md)
- **Game Theory DP** → [`game-theory-dp/README.md`](game-theory-dp/README.md)
- **Digit DP** → [`digit-dp/README.md`](digit-dp/README.md)
- **Bitmask DP** → [`bitmask-dp/README.md`](bitmask-dp/README.md)

### Quick Recognition Cheatsheet

| Keyword in problem                                | Likely pattern        |
| ------------------------------------------------- | --------------------- |
| Adjacent / consecutive / can't pick neighbors     | Linear DP             |
| Split / partition / segment into pieces           | Segmentation DP       |
| Grid / matrix / paths                             | 2D Grid DP            |
| Two strings compared / transform one into another | Two-Sequence (LCS) DP |
| Subset sums to target / capacity / budget         | Knapsack              |
| Merge / burst / remove a range                    | Interval DP           |
| Tree / binary tree / parent-child                 | Tree DP               |
| Holding / not holding / cooldown / modes          | State Machine DP      |
| Small n (≤ 20), visit all, subsets                | Bitmask DP            |
| Count numbers in range satisfying X               | Digit DP              |
| Two players, optimal play, alternate turns        | Game Theory DP        |

## Progress by Pattern Type

| Pattern                                      | Solved | Target | % Complete | Avg Time | Mastery        |
| -------------------------------------------- | ------ | ------ | ---------- | -------- | -------------- |
| [Linear DP](linear-dp/README.md)             | 3/10   | 10     | 30%        | ~20m     | 🟡 In Progress |
| [Segmentation DP](segmentation-dp/README.md) | 2/10   | 10     | 20%        | ~2h      | 🟡 In Progress |
| [2D Grid DP](2d-grid-dp/README.md)           | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| [Two-Sequence (LCS)](lcs-dp/README.md)       | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| [Knapsack](knapsack-dp/README.md)            | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| [Interval DP](interval-dp/README.md)         | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| [Tree DP](tree-dp/README.md)                 | 0/8    | 8      | 0%         | —        | ⏳ Upcoming    |
| [State Machine](state-machine-dp/README.md)  | 0/8    | 8      | 0%         | —        | ⏳ Upcoming    |
| [Game Theory](game-theory-dp/README.md)      | 0/8    | 8      | 0%         | —        | ⏳ Upcoming    |
| [Digit DP](digit-dp/README.md)               | 0/8    | 8      | 0%         | —        | 🔴 Advanced    |
| [Bitmask DP](bitmask-dp/README.md)           | 0/8    | 8      | 0%         | —        | 🔴 Advanced    |

## By Week

### Week 1-2: Foundation (warm-up problems)

Pre-medium warmup: Climbing Stairs, House Robber basics

- ✅ [70 - Climbing Stairs](linear-dp/70_Climbing_Stairs.md) _(Easy, warm-up)_
- ✅ [746 - Min Cost Climbing Stairs](linear-dp/746_Min_Cost_Climbing_Stairs.md) _(Easy, warm-up)_
- ✅ [198 - House Robber](linear-dp/198_House_Robber.md) _(Medium, done)_

### Week 3: Linear + Segmentation DP (5/20 problems)

_Linear:_ ✅ [213 - House Robber II](linear-dp/213_House_Robber_II.md), ✅ [740 - Delete and Earn](linear-dp/740_Delete_and_Earn.md) · _Segmentation:_ ✅ [139 - Word Break](segmentation-dp/139_Word_Break.md), ✅ [279 - Perfect Squares](segmentation-dp/279_Perfect_Squares.md)

- [ ] 300 - Longest Increasing Subsequence _(Linear, scan-all-previous)_
- [ ] 368 - Largest Divisible Subset _(Linear, scan-all-previous)_
- [ ] 91 - Decode Ways _(Segmentation)_
- [ ] 343 - Integer Break _(Segmentation)_

### Week 4: 2D Grid + Knapsack (0/20 problems)

- [ ] 62 - Unique Paths
- [ ] 63 - Unique Paths II
- [ ] 64 - Minimum Path Sum
- [ ] 120 - Triangle
- [ ] 931 - Minimum Falling Path Sum
- [ ] 221 - Maximal Square
- [ ] 416 - Partition Equal Subset Sum
- [ ] 494 - Target Sum
- [ ] 474 - Ones and Zeroes
- [ ] 322 - Coin Change

### Week 5: Interval + Two-Sequence/LCS (0/20 problems)

- [ ] 1039 - Minimum Score Triangulation
- [ ] 312 - Burst Balloons
- [ ] 1143 - Longest Common Subsequence
- [ ] 647 - Palindromic Substrings _(palindrome — classify on solve)_
- [ ] 5 - Longest Palindromic Substring _(palindrome — classify on solve)_
- ... (more)

### Week 6: Tree + State Machine + Game Theory (0/24 problems)

- [ ] 337 - House Robber III
- [ ] 276 - Paint Fence
- [ ] 486 - Predict the Winner
- [ ] 877 - Stone Game
- ... (more)

### Week 7-10: Advanced (Digit DP, Bitmask DP, Hard mixed)

_(Coming after core patterns)_

## Problems Mastered (Confidence ≥ 8/10)

- ✅ [213 - House Robber II](linear-dp/213_House_Robber_II.md) — first 8/10!

_One down. Keep going._

## Weakest Patterns (Confidence ≤ 5/10)

- **Segmentation DP** (2/10, avg ~2.5/10) — Word Break exposed the greedy-to-DP gap; Perfect Squares showed the gap is now the **state definition**, not the pieces. Both flagged for re-solve before Decode Ways.

## Weekly Summary

| Week | Problems   | Avg Time | Avg Confidence | Top Topic                |
| ---- | ---------- | -------- | -------------- | ------------------------ |
| 1-3  | 7 problems | ~26m avg | 5.0/10         | Linear + Segmentation DP |

---

## Notes for You

**Hey — about that 3 minutes.** You said you felt horrible for not getting it in 3 minutes. That's not how DP works. DP is a **pattern recognition skill**, not raw IQ. Nobody looks at Climbing Stairs for the first time and immediately writes `dp[i] = dp[i-1] + dp[i-2]` — they learn the pattern by seeing it, struggling with it, and reviewing it.

You _did_ write a correct memoized solution. That means you understood the recursion structure. The only gap was recognizing the recurrence — and now you've seen it, it'll click faster next time.

**Where you are now:** The Linear DP family is 3 mediums deep (House Robber trio), and you've met your first Segmentation problem (Word Break — 1/10, needs a re-solve).

| Problem                 | Operation           | Recurrence                                |
| ----------------------- | ------------------- | ----------------------------------------- |
| 70 - Climbing Stairs    | Sum (count ways)    | `dp[i] = dp[i-1] + dp[i-2]`               |
| 746 - Min Cost Climbing | Min (cheapest path) | `dp[i] = cost[i] + min(dp[i-1], dp[i-2])` |
| 198 - House Robber      | Max (best value)    | `dp[i] = max(dp[i-1], dp[i-2] + nums[i])` |

Same skeleton — three different operations. You've seen the whole family.

**Your breakthrough:** _"Always think about the options I have on each ith"_ — that's the whole game. State definition tells you _what_ to compute. Options at each step tell you _how_ to compute it. You now know this.

**213 was your first Medium DP in the tracker.** The hint you saw wasn't about DP — it was about **problem decomposition** (circle → two linear arrays). That's a separate skill, and you picked it up instantly. The DP recurrence was already yours.

**Curve check:**

| Problem               | Time | Confidence  | Trend          |
| --------------------- | ---- | ----------- | -------------- |
| 70 - Climbing Stairs  | ~3m  | 4/10        | 😖 First try   |
| 746 - Min Cost        | —    | 5/10        | 👍 Got it      |
| 198 - House Robber    | 30m  | 7/10        | 🟢 Good        |
| 213 - House Robber II | 8m   | 8/10        | 🚀 On fire     |
| 740 - Delete and Earn | 40m  | 6/10        | 🟡 Guided      |
| 139 - Word Break      | 2h   | 1/10        | 🔴 Greedy trap |
| 279 - Perfect Squares | N/A  | 4/10 (est.) | 🔴 State gap   |

**What's next:**

Word Break was the hardest one yet, and that's exactly why it's the most valuable. You hit the wall between **greedy thinking** and **DP thinking** — and that's the wall you need to break through.

**The key takeaway from this failure:** _"dp[i] = true means there EXISTS a cut point. Try ALL possible j. The nested loop is the DP, not the pointer."_

**Perfect Squares (279) — same pattern, one step closer.** You knew the ingredients this time (enumerate all squares) but couldn't write the recurrence. The missing piece was the **state**: `dp[i] = minimum squares to make exactly i`. Once the state exists, ask **"what's the last square I add?"** — every representation of i ends in some square s, and the rest is a representation of i - s. So `dp[i] = min(dp[i-s] + 1)` over all squares ≤ i. The good news: this is **Coin Change in disguise** (coins = {1, 4, 9, ...}), so 322 in Week 4 will feel familiar.

**Your homework before the next problem:** Re-solve both Word Break AND Perfect Squares from scratch with no hints — Word Break in under 10 minutes, Perfect Squares in under 15. If you can write the state + recurrence for both, the segmentation family is yours.

Then try **91 - Decode Ways** — same skeleton, counting ways instead of minimizing/existence. The full pattern writeup is in [segmentation-dp/README.md](segmentation-dp/README.md).

---

**Last Updated:** 2026-08-01
