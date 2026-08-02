# Breakthroughs

Every problem I solve teaches me one thing I couldn't think of.
This is where they live.

---

## 2026-07-27

- **70 - Climbing Stairs** — _dp[i] = dp[i-1] + dp[i-2]. It's just Fibonacci — the number of ways to reach step i is the sum of ways to reach the two previous steps._
- **746 - Min Cost Climbing Stairs** — _Same Fibonacci skeleton as Climbing Stairs, but add cost[i] at each step and use min() instead of +. The top is past the last index, so answer = min(dp[n-1], dp[n-2])._
- **198 - House Robber** — _At each house, two options: skip (keep dp[i-1]) or rob (dp[i-2] + nums[i]). The answer is always max of the two. State definition is everything — once dp[i] is "best up to house i," the recurrence writes itself._
- **213 - House Robber II** — _A circle just means "run the linear DP twice, excluding each endpoint once." The recurrence doesn't change — only the range does. max(rob_linear(0, n-2), rob_linear(1, n-1))._
- **740 - Delete and Earn** — _Index by value, not by uniqueness. After building points[x] = x * freq[x], the House Robber recurrence applies directly. Compressing to unique values loses gap info and invents fake adjacency conflicts._
- **139 - Word Break** — _dp[i] = true means there EXISTS some valid cut point. The nested loop over ALL possible j (from 0 to i-1) is structurally required — you must scan every previous state, not follow a single pointer. `s.substr(j, i-j)` extracts the candidate word from position j of length i-j; if it matches AND dp[j] is true, you've found a segmentation. I was stuck on a greedy approach, committing to the first match and never backtracking — but you can't use one running pointer when you need to try ALL possible cuts._

## 2026-08-01

- **279 - Perfect Squares** — _I knew the pieces (enumerate all squares) but couldn't write the formula. The missing step was the state: dp[i] = minimum squares to make exactly i. Once the state exists, the recurrence writes itself by asking "what's the last square I add?" — every representation of i ends in some square s, and the rest is a representation of i - s, so dp[i] = min(dp[i-s] + 1) over all squares. It's literally Coin Change with coins = {1, 4, 9, ...}. Ingredients without the recipe (state + last-piece question) don't make a DP._
- **322 - Coin Change** — _The 279 → 322 transfer worked: same code, coins swapped for squares, solved in 5 minutes at 9/10. Only stumble: `if (x < amount) break` instead of `if (x > i) break` — the inner-loop guard must compare against the current subproblem i, never the global target amount. A wrong guard doesn't crash; it silently degrades the DP to only the smallest coin. Word Break took 2h, Perfect Squares was unsolvable alone, Coin Change was trivial — pattern recognition is the whole game._
- **139 - Word Break (re-solve)** — _2 hours → 3 minutes. The greedy trap isn't just learned, it's gone: the nested loop and dp[0] = true base case came out automatically, no hints. Spaced repetition works — this is the proof._
- **746 - Min Cost Climbing Stairs (re-solve, stuck)** — _My own diagnosis was right: "check my dp's state." I wrote dp[1] = min(cost[0], cost[1]) which mixes two state definitions (dp[0] = "cost to stand on step", dp[1] = "cheapest way to reach"), then cost[i] at i == n (out of bounds) and return dp[n-1] (wrong index — the top is step n). All three bugs are the SAME bug: the state was never pinned down. Write the state definition as a comment BEFORE coding._
- **213 - House Robber II (re-solve)** — _Decomposition and recurrence were automatic; the only bug was forgetting the n == 1 / n == 0 guards before indexing nums[1] and nums[2]. Guard tiny inputs before touching the recurrence._
- **377 - Combination Sum IV** — _I had the intuition — "get all the previous combinations" — but no correct formula, because the base case was wrong. Counting needs dp[0] = 1 (the empty sequence is one way, like 0! = 1), while min-cost problems need dp[0] = 0. Trace (x) alone: it's counted via dp[x] += dp[x-x] = dp[0]. And the +1 I kept adding was Coin Change's "count coins used" logic leaking in — ways are extended as whole blocks, not incremented per path. Plus: intermediates can overflow int (dp[630] ≈ 4.6×10¹⁸) while the final answer is 1 — unsigned int or clamp. Counting = add blocks, dp[0] = 1; cost = min, dp[0] = 0._
- **343 - Integer Break** — _The "leave it whole" escape hatch. Every segmentation problem I'd seen forced the remainder into a full subproblem — dp[i-x] always meant "decompose further." Integer Break is the first where a piece can stay as-is, and dp[i-j] alone can't express that: without j·(i−j), dp[4] = 3 instead of 4, because 2+2 (both pieces whole) is unreachable. The helper explained it directly instead of guiding me — that stung, because the skeleton was already mine. But I now know WHY the term exists, and the no-hints Day 3 re-solve proves ownership. Ask always: may the piece stay whole?_
- **3857 - Minimum Cost to Split into Ones** — _A new pattern family: interval split-cost. The condition I kept groping for — EVERY piece must be split all the way down, and you pay for the split itself — makes it dp[j] + dp[i−j] + j·(i−j) (both children recurse), not the segmentation shapes I knew: dp[i−x] + 1 consumes a piece, and Integer Break's max(j·(i−j), j·dp[i−j]) lets a piece stay whole. Three policies, same skeleton. Sanity check that made it land: every pair of final ones separates exactly once, so the answer is always n(n−1)/2 — and the DP silently agrees._

---

**Last Updated:** 2026-08-01
