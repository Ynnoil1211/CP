# RPC 2026-08 G - Lines Per Hour

**Type:** Greedy / Sorting-Based
**Rating:** 800
**Tag:** fractional-knapsack-ordering

## Key Insight

💡 Sort problems ascending by line count and greedily take the smallest until cumulative lines exceed total coding capacity 5 * P.

## Pattern Trigger

"Maximize count of completed tasks with individual line requirements under a fixed total time limit (5 hours at rate P)." Equal unit reward (+1 per problem) with varying costs.

## Breakthrough

Uniform reward per task implies taking elements with minimal cost maximizes total count; avoid hardcoding sample constants (e.g. 500) and ensure proper return if all tasks fit without exceeding capacity.

## Code Spotlight

```cpp
sort(lines.begin(), lines.end());
int budget = 5 * p, solved = 0;
for (int x : lines) {
    if (budget >= x) {
        budget -= x;
        solved++;
    } else break;
}
cout << solved << "\n";
```

## Example

Input: P = 20 (capacity = 5 * 20 = 100), lines = `[40, 20, 50, 10, 30]`
Sorted: `[10, 20, 30, 40, 50]`
- Take 10 (rem 90) -> count 1
- Take 20 (rem 70) -> count 2
- Take 30 (rem 40) -> count 3
- Take 40 (rem 0) -> count 4
- 50 exceeds remaining 0 -> stop
Output: `4`
Why: Ascending greedy choice minimizes capacity spent per problem solved.

---

**Generated:** 2026-09-13