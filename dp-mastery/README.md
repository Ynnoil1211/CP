# 100 DP Medium Problems Challenge

**Progress:** 12/100 problems solved
**Current Week:** Week 4 (2D Grid + Knapsack — early start)
**Target Completion:** TBD
**Overall Confidence:** 9.1/10

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
- 🥇 **Key Tips (distilled one-liners)** → [`KEY_TIPS.md`](KEY_TIPS.md) — re-read before each session

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

| Pattern                                      | Solved | Target | % Complete | Avg Time | Mastery            |
| -------------------------------------------- | ------ | ------ | ---------- | -------- | ------------------ |
| [Linear DP](linear-dp/README.md)             | 7/10   | 10     | 70%        | ~20m     | 🟡 In Progress     |
| [Segmentation DP](segmentation-dp/README.md) | 5/10   | 10     | 50%        | ~15m     | 🟢 Family complete |
| [2D Grid DP](2d-grid-dp/README.md)           | 0/10   | 10     | 0%         | —        | ⏳ Upcoming        |
| [Two-Sequence (LCS)](lcs-dp/README.md)       | 0/10   | 10     | 0%         | —        | ⏳ Upcoming        |
| [Knapsack](knapsack-dp/README.md)            | 2/10   | 10     | 20%        | ~13m     | 🟡 In Progress     |
| [Interval DP](interval-dp/README.md)         | 1/10   | 10     | 10%        | —        | 🟢 Started         |
| [Tree DP](tree-dp/README.md)                 | 0/8    | 8      | 0%         | —        | ⏳ Upcoming        |
| [State Machine](state-machine-dp/README.md)  | 0/8    | 8      | 0%         | —        | ⏳ Upcoming        |
| [Game Theory](game-theory-dp/README.md)      | 0/8    | 8      | 0%         | —        | ⏳ Upcoming        |
| [Digit DP](digit-dp/README.md)               | 0/8    | 8      | 0%         | —        | 🔴 Advanced        |
| [Bitmask DP](bitmask-dp/README.md)           | 0/8    | 8      | 0%         | —        | 🔴 Advanced        |

## By Week

### Week 1-2: Foundation (warm-up problems)

Pre-medium warmup: Climbing Stairs, House Robber basics

- ✅ [70 - Climbing Stairs](linear-dp/70_Climbing_Stairs.md) _(Easy, warm-up)_
- ✅ [746 - Min Cost Climbing Stairs](linear-dp/746_Min_Cost_Climbing_Stairs.md) _(Easy, warm-up)_
- ✅ [198 - House Robber](linear-dp/198_House_Robber.md) _(Medium, done)_

### Week 3: Linear + Segmentation DP (5/20 problems)

_Linear:_ ✅ [213 - House Robber II](linear-dp/213_House_Robber_II.md), ✅ [740 - Delete and Earn](linear-dp/740_Delete_and_Earn.md), ✅ [53 - Maximum Subarray](linear-dp/53_Maximum_Subarray.md) _(redo list)_ · _Segmentation:_ ✅ [139 - Word Break](segmentation-dp/139_Word_Break.md), ✅ [279 - Perfect Squares](segmentation-dp/279_Perfect_Squares.md), ✅ [1043 - Partition Array for Max Sum](segmentation-dp/1043_Partition_Array_for_Maximum_Sum.md) _(redo list — Decode Ways engine)_

- [ ] 300 - Longest Increasing Subsequence _(Linear, scan-all-previous)_
- [ ] 368 - Largest Divisible Subset _(Linear, scan-all-previous)_
- ✅ 55 - Jump Game _(Linear, reachability → greedy frontier, 08-15)_
- ✅ 45 - Jump Game II _(Linear, min jumps → BFS frontier, 08-15, 10/10)_
- ✅ 300 - Longest Increasing Subsequence _(Linear, scan-all-previous → patience sorting, 08-15)_
- ✅ 91 - Decode Ways _(Segmentation — THE BOSS, cleared 08-15)_
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

### Week 5: Interval + Two-Sequence/LCS (1/20 problems)

_Interval:_ ✅ [3857 - Minimum Cost to Split into Ones](interval-dp/3857_Minimum_Cost_to_Split_into_Ones.md) _(early start — the 1D split-cost warm-up)_

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

- ✅ [213 - House Robber II](linear-dp/213_House_Robber_II.md) — first 8/10 → **9/10 (08-09, 3 min)**
- ✅ [322 - Coin Change](knapsack-dp/322_Coin_Change.md) — first 9/10 → **10/10 after 3:42 re-solve.**
- ✅ [139 - Word Break](segmentation-dp/139_Word_Break.md) — 2h → 3-minute re-solve. Biggest turnaround in the tracker. **reclaimed: 10/10 on 08-15 (2:22)**
- ✅ [70 - Climbing Stairs](linear-dp/70_Climbing_Stairs.md) — 1.5-minute re-solve. Fibonacci is automatic. **10/10 on 08-15 (1:10)**
- ✅ [746 - Min Cost Climbing Stairs](linear-dp/746_Min_Cost_Climbing_Stairs.md) — **redemption: 4/10 → 9/10** (3:13 re-solve)
- ✅ [198 - House Robber](linear-dp/198_House_Robber.md) — 7/10 → 8/10; base-case semantics now understood, not intuition
- ✅ [279 - Perfect Squares](segmentation-dp/279_Perfect_Squares.md) — 4/10 → 9/10 (3:03)
- ✅ [53 - Maximum Subarray](linear-dp/53_Maximum_Subarray.md) — 5/10 → 10/10 (1:27)
- ✅ [343 - Integer Break](segmentation-dp/343_Integer_Break.md) — 6/10 → **10/10 (2:37, zero hints — the stolen solve is owned)**
- ✅ [377 - Combination Sum IV](knapsack-dp/377_Combination_Sum_IV.md) — 7/10 → 10/10 (2:06)
- ✅ [3857 - Minimum Cost to Split into Ones](interval-dp/3857_Minimum_Cost_to_Split_into_Ones.md) — 6/10 → **10/10 (08-15 final pass, 3 min)**
- ✅ [740 - Delete and Earn](linear-dp/740_Delete_and_Earn.md) — 7/10 → **9/10 (08-09, 5 min)**

_Twelve of thirteen at ≥ 8. Only 1043 (6/10) remains — three occurrences of the same index/cap class; special protocol 08-18._

## Weakest Patterns (Confidence ≤ 5/10)

- **1043 - Partition Array for Max Sum** (6/10) — the sole weak spot, three occurrences of the same index/cap class (original: `arr[i-j]` vs `arr[i-j+1]`; 08-09: `j <` vs `j <=`; 08-15: 0/1-indexed convention flipping mid-attempt — final code was correct). Root cause: convention flipping, not the recurrence. **Special protocol 08-18:** write the j=1 check (`j=1` → window = last element, `arr[i-1]`) and the cap (`j <= min(k, i)`) BEFORE the loops, then code.

_All other problems are ≥ 8/10. This is the last boss of the redo list._

## Weekly Summary

| Week          | Problems                      | Avg Time | Avg Confidence | Top Topic                    |
| ------------- | ----------------------------- | -------- | -------------- | ---------------------------- |
| 1-3           | 12 problems                   | ~20m avg | 6.3/10         | Linear + Seg + Knapsack      |
| 4             | 1 problem                     | —        | 7/10           | Interval (early start)       |
| 08-04 session | 9 re-solves                   | ~4m avg  | 9.1/10         | 🏆 Redemption Day            |
| 08-09 session | 5 re-solves                   | ~6m avg  | 7.8/10         | Bounds & indexing day        |
| 08-15 session | 4 re-solves                   | ~2m avg  | 10/10          | 🏆 Near-clean sweep          |
| 08-15         | + 91 Decode Ways (new solve)  | —        | 7/10 (est.)    | 🏆 The boss fell             |
| 08-15         | + 55 Jump Game (new solve)    | 12m      | —              | Linear reachability → greedy |
| 08-15         | + 45 Jump Game II (new solve) | 7m       | 10/10          | Min jumps → BFS frontier     |
| 08-15         | + 300 LIS (new solve)         | 13m      | —              | Scan-all-previous → patience |

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

| Problem                | Time | Confidence  | Trend                     |
| ---------------------- | ---- | ----------- | ------------------------- |
| 70 - Climbing Stairs   | 1:10 | 10/10       | 🏆 Mastered (08-15)       |
| 746 - Min Cost         | 3:13 | 9/10        | 🚀 Redemption (was 4/10)  |
| 198 - House Robber     | 3m   | 8/10        | 🚀 Re-solved (was 7/10)   |
| 213 - House Robber II  | 8m   | 9/10        | 🚀 3m re-solve (08-09)    |
| 740 - Delete and Earn  | 5m   | 9/10        | 🚀 Re-solved (08-09)      |
| 139 - Word Break       | 2:22 | 10/10       | 🏆 Reclaimed (08-15)      |
| 279 - Perfect Squares  | 3:03 | 9/10        | 🚀 Re-solved (was 4/10)   |
| 322 - Coin Change      | 3:42 | 10/10       | 🏆 Mastered               |
| 377 - Combination IV   | 2:06 | 10/10       | 🏆 Mastered               |
| 343 - Integer Break    | 2:37 | 10/10       | 🏆 Owned the stolen solve |
| 3857 - Split into Ones | 3:00 | 10/10       | 🏆 Mastered (08-15)       |
| 53 - Maximum Subarray  | 1:27 | 10/10       | 🏆 Mastered               |
| 1043 - Partition Max   | —    | 6/10        | 🔴 Sole weak spot (x3)    |
| 91 - Decode Ways       | —    | 7/10 (est.) | 🏆 Boss cleared (08-15)   |

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

**3857 — you just opened a NEW pattern family.** The recurrence `dp[j] + dp[i−j] + j·(i−j)` (both children recurse, you pay for the split) is the **Interval DP** signature — the family of Matrix Chain Multiplication, Burst Balloons, and Triangulation (all queued in Week 5). Your instinct that "the conditions" were the hard part is exactly right: the policy (must-split vs may-stay-whole vs single-valid-piece) is what distinguishes interval from segmentation. One sentence to keep: **segmentation consumes a piece; interval splits both halves and pays for the split.**

**Still open from the ladder:** 279 re-solve (due 08-04) and **91 Decode Ways** — the last boss of the segmentation family. 3857 was a great detour into a new family, but don't let Decode Ways drift: the operator engine (OR/min/max/count) is built — only the digit gates are new.

**53 — a new state flavor, and a new kind of bug to watch for.** Kadane's `dp[i] = max(dp[i-1]+nums[i], nums[i])` uses an **"ending at i"** state (subarray MUST include nums[i]) — every 1D state before it was "up to i" (House Robber), where the answer is the last cell. The trap: returning `dp[n-1]` instead of the running max. One sentence: _"up-to states end at the last cell; ending-at states need a running max."_ You're on the redo list for 08-04. Next up after the re-solve: **152 - Maximum Product Subarray** — same shape, but negatives flip signs, so you must track BOTH max and min. That's the next lesson in this family.
That's the next lesson in this family.

**1043 — you built the Decode Ways engine (3/10, but you built it — and then you studied it deeply).** `dp[i] = max over j ≤ k of dp[i-j] + max(window)·j` is segmentation with _bounded pieces_ — exactly the scan Decode Ways needs with pieces of length 1-2. The missing move was defining the piece: _the last piece is a window ending at i_, value = max·len. Your gap pattern is now visible across problems: when pieces are _given_ (words, coins), you're fine; when you must _define_ them (squares in 279, windows here), you stall — because defining the piece IS the state. The fix is one question: **"what can the last piece be?"** — for 1043: any window of length 1..k. Deep re-study on 08-01 added the loop trick below; timed re-solve still due 08-04.

**Your new permanent tool — the loop-conditions trick (from the 1043 deep re-study):** _think in "elements I'm considering", not indices._ Three questions that resolve every off-by-one in scan-all-previous DPs: (1) how many elements have I seen? → `i+1`; (2) what's the piece-size cap? → `min(k, i+1)`; (3) which element is j steps back? → `arr[i-j+1]`. Memory aid: j=1 → `arr[i]`, j=k → `arr[i-k+1]`. This fixes the `arr[i-j]` vs `arr[i-j+1]` and `dp[i-j]` vs `dp[i-j+1]` class of bugs — and transfers directly to Decode Ways (pieces of 1-2 digits → `s[i-1]`, `s[i-2]`).

**08-04 — REDEMPTION DAY. The redo list died.**

| Problem                | Re-solve | Old → New                |
| ---------------------- | -------- | ------------------------ |
| 1043 Partition Max     | 2:02     | 3 → **10**               |
| 746 Min Cost           | 3:13     | 4 → **9**                |
| 279 Perfect Squares    | 3:03     | 4 → **9**                |
| 53 Max Subarray        | 1:27     | 5 → **10**               |
| 343 Integer Break      | 2:37     | 6 → **10** (zero hints!) |
| 377 Combination Sum IV | 2:06     | 7 → **10**               |
| 322 Coin Change        | 3:42     | 9 → **10**               |
| 198 House Robber       | 3:00     | 7 → **8**                |
| 3857 Split into Ones   | 15:45    | 7 → **6** 🔴             |

**The scoreboard: 11 of 13 problems at confidence ≥ 8.** The stolen 343 solve is now yours. 746's base-case reflex fired again — but you caught it by thinking about the state, which is the whole habit. Two lessons banked: (1) **initialization is part of the recurrence** — 0 for sums/counts, big value (sentinel) for min, INT_MIN for max, `dp[0] = 1` for counting; (2) **3857's accidental max variant passes only because the cost is invariant — an AC is not understanding.** Remaining rotation: 3857 (Day 7, 08-08) and 740's Day 7 (08-08).

**Next boss: 91 - Decode Ways.** Every engine is warm: counting (377), bounded pieces (1043), the loop trick, state-first discipline.

**08-09 — the bounds day, and the proof the method works.** You said it yourself: _"I didn't remember the solutions, but still remember the logic"_ — **that's exactly what spaced repetition is supposed to produce.** The pattern lives in long-term memory; rote details fade. And look at what actually failed: 3857 (2:10, down from 15:45 — the both-children recurrence is now cold), 740 (5 min, 9/10), 213 (3 min, 9/10). The two regressions — 139 (`dp[n-1]` vs `dp[n]`) and 1043 (`j <` vs `j <= min(k, i+1)`, which silently tries k−1 lengths) — were **bounds errors, not concept gaps**: same failure class, both fixed by one audit habit. New KEY_TIPS row added: before submitting, check (1) the loop REACHES the cap, (2) the answer reads the FULL problem (`dp[n]`, not `dp[n-1]`). The logic is yours; the bounds audit is the final polish step.

**08-15 — near-clean sweep, and 1043 gets its own protocol.** 139 (2:22), 3857 (3 min), 70 (1:10) — all 10/10, all cold. That's 12 of 13 at ≥ 8, average 9.2/10. The one remaining: **1043, third strike.** This time the diagnosis is sharper: your final code was CORRECT (1-indexed: `arr[i-j]`, `dp[i-j]`, `j <= min(k, i)`) — the failure was _flipping conventions mid-attempt_ (0-indexed `arr[i-j+1]`/`dp[i+1]` leaking into the 1-indexed skeleton). The recurrence was never the problem; the convention switch was. The 08-18 protocol: (1) pick 1-indexed `dp` and write it at the top; (2) verify `j=1` → window = `arr[i-1]` (the LAST element); (3) cap = `j <= min(k, i)` (window can't exceed the prefix). Write those three lines before the loops. If it clears, the redo list is dead and Decode Ways is the only boss left.
The logic is yours; the bounds audit is the final polish step.

**08-15 evening — 91 Decode Ways: THE BOSS FELL.** The segmentation family is complete: OR/min/max/count, unbounded and bounded pieces, all four operators banked. The first attempt had three mechanical bugs (ASCII math on chars, an `n==2` hardcode that ignored digits, and a `continue` that dropped the 1-char gate — `"27"` would've returned 0). Each mapped 1:1 to a KEY_TIPS row. The fix was the sum-of-independent-gates view: `dp[i] = (s[i-1] != '0' ? dp[i-1] : 0) + (10 <= two <= 26 ? dp[i-2] : 0)` — no special cases, gates ARE the special cases. The boss that was pending since 08-01 fell in one session. Remaining: 1043 (6/10, special protocol 08-18) and the redo list is otherwise dead. Next new content: 639 Decode Ways II, or interval classics 1039/312 (now open after 3857's mastery).

---

**Last Updated:** 2026-08-15
