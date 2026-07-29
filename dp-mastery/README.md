# 100 DP Medium Problems Challenge

**Progress:** 1/100 problems solved
**Current Week:** Week 3 (Linear DP)
**Target Completion:** TBD
**Overall Confidence:** 6/10 — building momentum

## Progress by Pattern Type

| Pattern     | Solved | Target | % Complete | Avg Time | Mastery        |
| ----------- | ------ | ------ | ---------- | -------- | -------------- |
| Linear DP   | 1/12   | 12     | 8%         | 8m       | 🟡 In Progress |
| 2D Grid DP  | 0/12   | 12     | 0%         | —        | ⏳ Upcoming    |
| Knapsack    | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| Interval DP | 0/10   | 10     | 0%         | —        | ⏳ Upcoming    |
| Tree DP     | 0/8    | 8      | 0%         | —        | ⏳ Upcoming    |
| Game Theory | 0/8    | 8      | 0%         | —        | ⏳ Upcoming    |
| Digit DP    | 0/15   | 15     | 0%         | —        | 🔴 Advanced    |
| Bitmask DP  | 0/15   | 15     | 0%         | —        | 🔴 Advanced    |

## By Week

### Week 1-2: Foundation (warm-up problems)

Pre-medium warmup: Climbing Stairs, House Robber basics

- ✅ [70 - Climbing Stairs](linear-dp/70_Climbing_Stairs.md) _(Easy, warm-up)_
- ✅ [746 - Min Cost Climbing Stairs](linear-dp/746_Min_Cost_Climbing_Stairs.md) _(Easy, warm-up)_
- ✅ [198 - House Robber](linear-dp/198_House_Robber.md) _(Medium, done)_

### Week 3: Linear DP (1/12 problems)

- ✅ [213 - House Robber II](linear-dp/213_House_Robber_II.md) _(Medium, done)_
- [ ] 139 - Word Break
- [ ] 91 - Decode Ways
- [ ] 300 - Longest Increasing Subsequence
- [ ] 322 - Coin Change
- [ ] 740 - Delete and Earn
- [ ] 368 - Largest Divisible Subset
- [ ] 1143 - Longest Common Subsequence
- [ ] 647 - Palindromic Substrings
- [ ] 5 - Longest Palindromic Substring
- [ ] 343 - Integer Break
- [ ] 276 - Paint Fence

### Week 4: 2D Grid DP + Knapsack (0/22 problems)

- [ ] 62 - Unique Paths
- [ ] 63 - Unique Paths II
- [ ] 64 - Minimum Path Sum
- [ ] 120 - Triangle
- [ ] 931 - Minimum Falling Path Sum
- [ ] 221 - Maximal Square
- [ ] 416 - Partition Equal Subset Sum
- [ ] 494 - Target Sum
- [ ] 474 - Ones and Zeroes
- ... (more)

### Week 5: Interval DP + Tree DP (0/18 problems)

- [ ] 1039 - Minimum Score Triangulation
- [ ] 312 - Burst Balloons
- [ ] 337 - House Robber III
- ... (more)

### Week 6: Game Theory DP + Mixed Core (0/8 problems)

- [ ] 486 - Predict the Winner
- [ ] 877 - Stone Game
- ... (more)

### Week 7-10: Advanced (Digit DP, Bitmask DP, Hard mixed)

_(Coming after core patterns)_

## Problems Mastered (Confidence ≥ 8/10)

- ✅ [213 - House Robber II](linear-dp/213_House_Robber_II.md) — first 8/10!

_One down. Keep going._

## Weakest Patterns (Confidence ≤ 5/10)

_None! Linear DP now above 5/10 after 4 problems._

## Weekly Summary

| Week | Problems   | Avg Time | Avg Confidence | Top Topic |
| ---- | ---------- | -------- | -------------- | --------- |
| 1    | 4 problems | ~12m avg | 6/10           | Linear DP |

---

## Notes for You

**Hey — about that 3 minutes.** You said you felt horrible for not getting it in 3 minutes. That's not how DP works. DP is a **pattern recognition skill**, not raw IQ. Nobody looks at Climbing Stairs for the first time and immediately writes `dp[i] = dp[i-1] + dp[i-2]` — they learn the pattern by seeing it, struggling with it, and reviewing it.

You _did_ write a correct memoized solution. That means you understood the recursion structure. The only gap was recognizing the recurrence — and now you've seen it, it'll click faster next time.

**Where you are now:** 3 fundamental Linear DP patterns internalized.

| Problem                 | Operation           | Recurrence                                |
| ----------------------- | ------------------- | ----------------------------------------- |
| 70 - Climbing Stairs    | Sum (count ways)    | `dp[i] = dp[i-1] + dp[i-2]`               |
| 746 - Min Cost Climbing | Min (cheapest path) | `dp[i] = cost[i] + min(dp[i-1], dp[i-2])` |
| 198 - House Robber      | Max (best value)    | `dp[i] = max(dp[i-1], dp[i-2] + nums[i])` |

Same skeleton — three different operations. You've seen the whole family.

**Your breakthrough:** _"Always think about the options I have on each ith"_ — that's the whole game. State definition tells you _what_ to compute. Options at each step tell you _how_ to compute it. You now know this.

**213 was your first Medium DP in the tracker.** The hint you saw wasn't about DP — it was about **problem decomposition** (circle → two linear arrays). That's a separate skill, and you picked it up instantly. The DP recurrence was already yours.

**Curve check:**

| Problem               | Time | Confidence | Trend        |
| --------------------- | ---- | ---------- | ------------ |
| 70 - Climbing Stairs  | ~3m  | 4/10       | 😖 First try |
| 746 - Min Cost        | —    | 5/10       | 👍 Got it    |
| 198 - House Robber    | 30m  | 7/10       | 🟢 Good      |
| 213 - House Robber II | 8m   | 8/10       | 🚀 On fire   |

**What's next:**

1. **740 - Delete and Earn** — transforms into House Robber I after a frequency pass (this one will feel like cheating)
2. **139 - Word Break** — a different Linear DP pattern (segmentation)

You've got this. One step at a time.

---

**Last Updated:** 2026-07-27
