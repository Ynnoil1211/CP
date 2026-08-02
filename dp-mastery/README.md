# 100 DP Medium Problems Challenge

**Progress:** 8/100 problems solved
**Current Week:** Week 4 (2D Grid + Knapsack — early start)
**Target Completion:** TBD
**Overall Confidence:** 6.8/10

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
| [Segmentation DP](segmentation-dp/README.md) | 3/10   | 10     | 30%        | ~25m     | 🟡 In Progress |
| [2D Grid DP](2d-grid-dp/README.md)           | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| [Two-Sequence (LCS)](lcs-dp/README.md)       | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| [Knapsack](knapsack-dp/README.md)            | 2/10   | 10     | 20%        | ~13m     | 🟡 In Progress |
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
- ✅ 343 - Integer Break _(Segmentation)_

### Week 4: 2D Grid + Knapsack (2/20 problems)

_Knapsack:_ ✅ [322 - Coin Change](knapsack-dp/322_Coin_Change.md) _(early start — the 279 pattern transfer!)_, ✅ [377 - Combination Sum IV](knapsack-dp/377_Combination_Sum_IV.md) _(counting variant — the + operator, Decode Ways engine)_

- [ ] 62 - Unique Paths
- [ ] 63 - Unique Paths II
- [ ] 64 - Minimum Path Sum
- [ ] 120 - Triangle
- [ ] 931 - Minimum Falling Path Sum
- [ ] 221 - Maximal Square
- [ ] 416 - Partition Equal Subset Sum
- [ ] 494 - Target Sum
- [ ] 474 - Ones and Zeroes
- ✅ 322 - Coin Change

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
- ✅ [322 - Coin Change](knapsack-dp/322_Coin_Change.md) — first 9/10, 5 minutes. Pattern transfer from 279 paid off.
- ✅ [139 - Word Break](segmentation-dp/139_Word_Break.md) — 2h → **3-minute re-solve**. The biggest turnaround in the tracker.
- ✅ [70 - Climbing Stairs](linear-dp/70_Climbing_Stairs.md) — 1.5-minute re-solve. Fibonacci is automatic.

_Four down. The review system is working._

## Weakest Patterns (Confidence ≤ 5/10)

- **746 - Min Cost Climbing Stairs** (4/10) — re-solve exposed a **state-definition bug** (`dp[1] = min(cost[0], cost[1])` mixed two definitions; `cost[i]` OOB at `i == n`; wrong answer index). Fix: write the state as a comment first. Due 2026-08-04.
- **279 - Perfect Squares** (4/10) — can spot the pieces, can't yet derive the state cold. Due 2026-08-04.

## Weekly Summary

| Week | Problems    | Avg Time | Avg Confidence | Top Topic               |
| ---- | ----------- | -------- | -------------- | ----------------------- |
| 1-3  | 10 problems | ~21m avg | 6.8/10         | Linear + Seg + Knapsack |

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

| Problem               | Time | Confidence  | Trend                   |
| --------------------- | ---- | ----------- | ----------------------- |
| 70 - Climbing Stairs  | ~3m  | 8/10        | 🚀 1.5m re-solve        |
| 746 - Min Cost        | —    | 4/10        | 🔴 State-definition bug |
| 198 - House Robber    | 30m  | 7/10        | 🟢 Good                 |
| 213 - House Robber II | 8m   | 8/10        | 🚀 8m re-solve          |
| 740 - Delete and Earn | 40m  | 7/10        | 🟡 11m re-solve         |
| 139 - Word Break      | 2h   | 8/10        | 🚀 3m re-solve!         |
| 279 - Perfect Squares | N/A  | 4/10 (est.) | 🔴 State gap            |
| 322 - Coin Change     | 5m   | 9/10        | 🚀 Transfer!            |
| 377 - Combination IV  | 22m  | 7/10        | 🟡 Base-case gap        |
| 343 - Integer Break   | 27m  | 6/10        | 🟡 Whole-piece given    |

**What's next:**

Word Break was the hardest one yet, and that's exactly why it's the most valuable. You hit the wall between **greedy thinking** and **DP thinking** — and that's the wall you need to break through.

**The key takeaway from this failure:** _"dp[i] = true means there EXISTS a cut point. Try ALL possible j. The nested loop is the DP, not the pointer."_

**Perfect Squares (279) — same pattern, one step closer.** You knew the ingredients this time (enumerate all squares) but couldn't write the recurrence. The missing piece was the **state**: `dp[i] = minimum squares to make exactly i`. Once the state exists, ask **"what's the last square I add?"** — every representation of i ends in some square s, and the rest is a representation of i - s. So `dp[i] = min(dp[i-s] + 1)` over all squares ≤ i. The good news: this is **Coin Change in disguise** (coins = {1, 4, 9, ...}), so 322 in Week 4 will feel familiar.

**Your homework before the next problem:** Re-solve both Word Break AND Perfect Squares from scratch with no hints — Word Break in under 10 minutes, Perfect Squares in under 15. If you can write the state + recurrence for both, the segmentation family is yours.

Then try **91 - Decode Ways** — same skeleton, counting ways instead of minimizing/existence. The full pattern writeup is in [segmentation-dp/README.md](segmentation-dp/README.md).

**322 — the transfer worked, and it's a huge signal.** You solved Coin Change in **5 minutes at 9/10**, the exact problem flagged in the 279 note as "you've already written this code." That's not luck — that's the state+recurrence mental model working. Word Break took 2 hours; Perfect Squares was unsolvable alone; Coin Change was trivial. The gap between knowing a pattern's skeleton and not knowing it is the entire game.

**The one thing to remember from 322:** your bug was `if (x < amount) break` instead of `if (x > i) break` — the inner-loop guard must compare against the **current state `i`**, never the global target `amount`. A wrong guard doesn't crash; it silently degrades the DP to "only the smallest coin."

**Next:** 322 unlocked the knapsack family. 416 - Partition Equal Subset Sum is the same code with the loop flipped (0/1, backward) — a great next target. Or stay in Week 4's grid track with 62 - Unique Paths. Either way, keep the streak: two straight problems at confidence ≥ 8.

**Re-solve session (08-01) — the data speaks:**

| Problem           | First solve | Re-solve  | Δ              |
| ----------------- | ----------- | --------- | -------------- |
| 139 - Word Break  | 2h          | **3 min** | 🚀 40× faster  |
| 70 - Climbing     | ~3m         | 1.5 min   | 🚀 automatic   |
| 740 - Delete Earn | 40m         | 11 min    | 🚀 3.6× faster |
| 213 - Robber II   | 8m          | 8 min     | ➖ same, solid |
| 746 - Min Cost    | —           | STUCK     | 🔴 state bug   |

**Word Break 2h → 3 min is the proof the method works.** The greedy trap isn't just learned — it's gone. Your own diagnosis on 746 was the right debugging instinct: _"check my dp's state"_ — that's exactly what state-definition bugs look like. Base cases define the state; the recurrence must match them. Write the state as a comment first, always.

**Due 08-04:** 279 + 322 quick re-solves, 377's Day 3 review, plus 746's redemption re-solve. If 746 falls under 8 minutes with no state flubs, it's cleared.

**377 — the counting operator is now yours, and that was the last missing piece for Decode Ways.** You had the intuition (accumulate previous combinations) but the base case blocked the formula: counting needs `dp[0] = 1` (the empty way, like 0! = 1), cost problems need `dp[0] = 0`. The +1 you kept adding was Coin Change's "count coins used" logic leaking in — ways are added as whole blocks (`dp[i] += dp[i-x]`), never per-path. Also worth remembering: intermediates can overflow int even when the answer fits (dp[630] ≈ 4.6×10¹⁸) — unsigned int or clamp.

**Ladder status:** ✅ 377 (counting) → ✅ 343 (max + whole-piece) → ⏳ 279 re-solve (min, due 08-04) → **91 Decode Ways = 377 + string gates.** The operator engine is complete — OR/min/max/count are all yours in this skeleton. Only the digit gates are new.

**About 343 — don't let the stolen solve sting.** The helper handed you the `j·(i−j)` term instead of guiding you to it, and that's on the helper, not on you. But look at what you produced alone: the nested loop over cuts, `dp[i−j]·j`, the max accumulation — the segmentation skeleton, for the fifth time, without prompting. The missing term was a genuinely new concept (a piece may stay whole — no prior problem allowed it), not a gap in your skill. The 08-04 re-solve, no hints, is the real verdict. For the record: you've now solved 343 in 27 minutes; the first time you met Word Break, it took 2 hours. The trend line is the truth.

---

**Last Updated:** 2026-08-01
