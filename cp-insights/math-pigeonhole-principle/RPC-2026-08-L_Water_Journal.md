# RPC 2026-08 L - Water Journal

**Type:** Math / Pigeonhole Principle
**Rating:** 800
**Tag:** pigeonhole-extreme-coverage

## Key Insight

💡 One missing day cannot simultaneously cover two missing extremes ($a \ne b$ with neither recorded); if both appear, any value in $[a, b]$ is valid, otherwise the missing extreme is uniquely forced.

## Pattern Trigger

"$n-1$ entries recorded, overall min was $a$ and max was $b$, output all possible values for the single missing day or -1 if impossible." Boundary tracking with 1 missing degree of freedom.

## Breakthrough

Evaluate the four-state boolean matrix $(\text{has\_a}, \text{has\_b})$; with only 1 missing slot, needing both distinct extremes is an immediate contradiction by the pigeonhole principle ($k > 1$ requirements, 1 slot).

## Code Spotlight

```cpp
bool has_a = count(v.begin(), v.end(), a);
bool has_b = count(v.begin(), v.end(), b);

if (!has_a && !has_b) cout << -1 << "\n";
else if (has_a && has_b) for (int x = a; x <= b; x++) cout << x << "\n";
else if (!has_a) cout << a << "\n";
else cout << b << "\n";
```

## Example

Input: $a = 3, b = 7$, logs = `[4, 5, 6]` (neither 3 nor 7 observed)
Output: `-1`
Why: Exactly one log entry is missing, but both minimum 3 and maximum 7 are required; one integer cannot simultaneously equal both 3 and 7.

---

**Generated:** 2026-09-13
