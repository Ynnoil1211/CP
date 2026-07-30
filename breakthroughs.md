# Breakthroughs

Every problem I solve teaches me one thing I couldn't think of.
This is where they live.

---

## 2026-07-27

- **70 - Climbing Stairs** — *dp[i] = dp[i-1] + dp[i-2]. It's just Fibonacci — the number of ways to reach step i is the sum of ways to reach the two previous steps.*
- **746 - Min Cost Climbing Stairs** — *Same Fibonacci skeleton as Climbing Stairs, but add cost[i] at each step and use min() instead of +. The top is past the last index, so answer = min(dp[n-1], dp[n-2]).*
- **198 - House Robber** — *At each house, two options: skip (keep dp[i-1]) or rob (dp[i-2] + nums[i]). The answer is always max of the two. State definition is everything — once dp[i] is "best up to house i," the recurrence writes itself.*
- **213 - House Robber II** — *A circle just means "run the linear DP twice, excluding each endpoint once." The recurrence doesn't change — only the range does. max(rob_linear(0, n-2), rob_linear(1, n-1)).*
- **740 - Delete and Earn** — *Index by value, not by uniqueness. After building points[x] = x * freq[x], the House Robber recurrence applies directly. Compressing to unique values loses gap info and invents fake adjacency conflicts.*

---

**Last Updated:** 2026-07-27
