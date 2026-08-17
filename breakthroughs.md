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

- **1043 - Partition Array for Maximum Sum** — _The missing move: define the LAST piece as a window of length j ≤ k ending at i, value max·len. I kept thinking forward ("which element anchors a group?") instead of backward ("what's the last piece?"). Once the piece is the window, dp[i] = max over j ≤ k of dp[i-j] + mx·j — and bounded pieces mean only k candidates, the same scan Decode Ways needs with pieces of 1-2 digits. My gap pattern: when pieces are given I'm fine; when I must define them (squares in 279, windows here) I stall — because defining the piece IS the state._
- **1043 - Partition Array for Maximum Sum (deep re-study)** — _The loop trick that fixes my whole off-by-one class: think in "elements I'm considering", not indices. i = current position, j = how many elements back → window start = arr[i-j+1], piece-size cap = min(k, i+1), dp[i+1] holds the best for arr[0..i]. j=1 touches arr[i]; j=k touches arr[i-k+1]. Same question serves Decode Ways (pieces of length 1-2). Trace confusion resolved: arr=[1,15,7,9], k=3 → 54 comes from [1,15,7]+[9] (45+9), not [1,15]+[7,9] (48)._

## 2026-08-04

**Redemption Day — the full re-solve session. Average confidence 6.4 — 8.7/10; 11 of 13 problems now ≥ 8.**

- **343 - Integer Break (re-solve)** — _2:37, 10/10, ZERO hints: max({dp[i], dp[i-j]\*j, (i-j)\*j}) written alone. The stolen solve is officially repaid — the Day 3 verdict came back: it's mine. The whole-piece term appeared by itself._
- **3857 - Split into Ones (re-solve)** — _15:45 and I forgot +dp[j] again — both children must recurse, that's the interval signature. I "solved" it with a max-variant that only passes because the total cost is invariant: every pair of final units separates exactly once, so ANY consistent recurrence lands on n(n−1)/2. An accidental AC is not understanding — Day 7 re-solve with both children._
- **198 - House Robber (re-solve)** — _dp[1] = max(nums[0], nums[1]) is not intuition — it's the base case. Under "best considering houses 0..i", at i=1 you face two adjacent houses: the take/skip decision at the boundary where dp[i-2] doesn't exist yet. Base cases are the recurrence applied at the start of the array._
- **746 - Min Cost (re-solve)** — _The base-case reflex error fired AGAIN (dp[1] = min(cost[0], cost[1]) from memory), but I caught it by thinking about the state, not by luck — 3:13, 9/10. The state-first habit is forming._
- **The init lesson (from 279, 53, 377)** — _Initialization is part of the recurrence: 0 for sums/counts, big sentinel for min, INT_MIN for max, dp[0] = 1 for counting (i-x = 0 must be reachable)._

## 2026-08-09

**The bounds day — and the proof the method works.**

- **3857 - Split into Ones (re-solve)** — _15:45 → 2:10. The both-children recurrence came out COLD; only base case + dp-init values were buggy. 8/10, one final confirmation pass on 08-12 — but the interval signature is now mine._
- **1043 - Partition Max (re-solve)** — _16 min, had to see the solution: `j < min(k, i+1)` runs only k−1 lengths — the cap must be `<=`. The state and loop trick were RIGHT; the bounds audit was skipped. Same class as 139._
- **139 - Word Break (re-solve)** — _Looped to n−1, but the answer reads dp[n]. The nested loop and dp[0]=true were automatic — the boundary was off by one. Same failure class as 1043: bounds audit._
- **740 (5 min, 9/10) and 213 (3 min, 9/10)** — _Clean re-solves, logic remembered without the solutions._
- **The meta-proof** — _"I didn't remember the solutions but remembered the logic" — that's EXACTLY what spaced repetition produces: the pattern in long-term memory, rote details faded. Two of today's stalls were bounds/indexing, not concepts — a habit to build, not a hole in understanding._

## 2026-08-15

**Near-clean sweep: 139 (2:22, 10/10), 3857 (3 min, 10/10 — final pass), 70 (1:10, 10/10). 12 of 13 at ≥ 8.**

- **139 - Word Break (re-solve)** — _2:22, 10/10 — including the dp[n] answer line that slipped on 08-09. The regression is closed; the bounds audit worked when it mattered._
- **3857 - Split into Ones (final pass)** — _3 min, 10/10, clean. From 15:45 and a forgotten +dp[j] to 3 minutes in 11 days. The interval signature is reflex._
- **1043 - Partition Max (re-solve, still stuck)** — _Third occurrence of the same class, but the diagnosis finally sharpened: my final code was CORRECT (1-indexed arr[i-j], dp[i-j], j <= min(k, i)) — I was flipping between 0-indexed and 1-indexed conventions mid-attempt. The recurrence was never the problem; the convention switch was. Protocol for 08-18: write the convention, the j=1 check (window = arr[i-1]), and the cap BEFORE the loops._
- **The convention lesson** — _When indexing a window: choose the convention once, then verify j=1 touches the LAST element. Every 1043 failure is the same root: mixing two conventions in one attempt._
- **91 - Decode Ways (NEW SOLVE — THE BOSS FELL)** — _Three mechanical bugs, each mapping to a KEY_TIPS row: ASCII char math (s[i-2]*10 = 49*10, not 1\*10), an n==2 hardcode ("10" is 1 way, not 2), and a continue that dropped the 1-char gate ("27" → 0 instead of 1). The insight that fixed it: the two gates are INDEPENDENT TERMS OF A SUM, not branches of an if-else. dp[i] = (s[i-1]!='0' ? dp[i-1] : 0) + (10<=two<=26 ? dp[i-2] : 0). Zero traps fall out of the gates by themselves — "06" → 0, "10" → 1, "210" → 1 — no special-casing. The segmentation family is COMPLETE._
- **55 - Jump Game (NEW SOLVE)** — _The scan-all-previous DP (dp[i] = any reachable j with nums[j]+j >= i) is correct but O(n²) and "really slow." The insight: reachability is MONOTONE — reaching i means reaching everything before it — so a single running frontier mx = max(mx, i+nums[i]) replaces the whole nested loop. It's the ONE case where greedy is provably correct, the reverse of the Word Break trap._
- **45 - Jump Game II (NEW SOLVE, 7 min, 10/10)** — _The min-jump sequel: the DP (dp[i] = min over reachable j of dp[j]+1) transferred cleanly, but the O(n) trick needs a SECOND pointer. Jump Game's single mx frontier tells you how far you can reach, not how many jumps — you need `end` (the current level's boundary) and the `i == end` trigger to count when a new jump begins. Minimum jumps = BFS levels: frontier + level boundary._
- **300 - Longest Increasing Subsequence (NEW SOLVE, 13 min)** — _The REAL scan-all-previous problem, the reverse of Jump Game: here greedy does NOT work, the nested loop is genuinely required. I only thought of the DP — the O(n log n) patience-sorting trick (res[k] = minimal tail of a length-k+1 subsequence, lower_bound to replace) is a SEPARATE algorithm I wouldn't derive from the DP. Also: answer is max(dp), not dp[n-1], because the LIS might not end at the last index._

---

**Last Updated:** 2026-08-15
