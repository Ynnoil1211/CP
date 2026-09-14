# RPC 2026-08 C - Don't Hunger Together

**Type:** Binary Search / Answer on Range
**Rating:** 1800
**Tag:** bsta-earliest-deadline-first

## Key Insight

💡 Binary search the continuous daily food quota per player; for each candidate, greedily satisfy daily demand by consuming food with the earliest expiration date via a min-heap.

## Pattern Trigger

"Find maximum daily consumption $x > 0$ such that all $K$ players survive $N$ days with expiring food batches." Feasibility is monotonic (eating less is always easier than eating more), triggering Binary Search on Answer (BSTA).

## Breakthrough

Earliest Deadline First (EDF) greedy consumption is optimal: consuming food that expires earlier frees up longer-lasting food for subsequent turns. Checking feasibility in $O(N \log N)$ with 80–100 bisection iterations achieves $10^{-9}$ precision.

## Code Spotlight

```cpp
bool canDo(double F) {
    priority_queue<pair<int, double>, vector<pair<int, double>>, greater<>> pq;
    for (int i = 0; i < n; i++) {
        if (food[i] > 0) pq.push({exp[i], food[i]});
        double need = F;
        while (!pq.empty() && need > 1e-10) {
            auto [e, q] = pq.top(); pq.pop();
            if (e < i) continue;
            double take = min(need, q);
            need -= take;
            if (q > take) pq.push({e, q - take});
        }
        if (need > 1e-9) return false;
    }
    return true;
}
```

## Example

Input: 2 days, 1 player. Day 0 gets 10 food (expires day 1). Day 1 gets 0 food.
Binary search tests mid = 5.0:
- Day 0: eats 5, leaves 5 expiring day 1.
- Day 1: eats remaining 5 expiring day 1. Total consumed = 10, valid!
Output: `5.0000000000`
Why: Optimal allocation balances consumption across survival intervals without letting early batches expire unused.

---

**Generated:** 2026-09-13
