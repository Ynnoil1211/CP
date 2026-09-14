# RPC 2026-08 E - ICPC Team Generation

**Type:** Greedy / Boundary Testing
**Rating:** 1100
**Tag:** monotonic-trio-boundary

## Key Insight

💡 Sorted ranks with monotonic preference intervals (a_i <= a_j and b_i <= b_j) guarantee that optimal teams are always consecutive trios {p, p+1, p+2} checked solely by boundaries b_p >= p+2 and a_{p+2} <= p.

## Pattern Trigger

"Form maximum 3-person teams from ranked contestants with intervals [a_r, b_r], given a_i <= a_j and b_i <= b_j for all i < j." Monotonic preference bounds eliminate general 3D-matching complexity down to adjacent subarray grouping.

## Breakthrough

The middle member p+1 is automatically compatible by monotonicity if endpoints p and p+2 accept each other; a greedy left-to-right scan forming the earliest viable trio yields the maximum possible teams.

## Code Spotlight

```cpp
int teams = 0, p = 0;
while (p + 2 < n) {
    if (b[p] >= p + 2 && a[p + 2] <= p) {
        teams++;
        p += 3;
    } else {
        p++;
    }
}
```

## Example

Input: 3 people with ranges [0, 2], [0, 2], [0, 2]
Check p=0: b[0] = 2 >= 0+2 and a[2] = 0 <= 0 -> valid trio!
Output: `1`
Why: Monotonicity guarantees that if contestant 0 accepts 2 and contestant 2 accepts 0, contestant 1 is internally consistent with both.

---

**Generated:** 2026-09-13