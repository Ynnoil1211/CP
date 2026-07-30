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

---

**Last Updated:** 2026-07-27
