# Pattern: Digit DP

## Pattern Name: **Digit DP**

### Description

Count (or sum) numbers satisfying a property by **building them digit by digit**. The state tracks the position in the number plus flags: **`tight`** (still equal to the limit's prefix → can't exceed it), **`started`** (leading zeros are done), and problem-specific flags (last digit, digit sum, etc.).

The mental shift: a number is a digit string; you DFS over digits, and the tight flag prunes everything above the limit in one stroke.

### When to recognize it

- "count numbers between L and R such that..."
- Digit-sum / digit-property constraints
- The classic trick: answer = `f(R) − f(L−1)`

### The General Template

**State:**
```
dp[pos][tight][started][flags] = count of valid suffixes from this position
```

**Base case:**
```
pos == len: return 1 if the built number is valid (and started)
```

**Transition:**
```
for d in 0..(tight ? limit[pos] : 9):
    dp[pos][tight][...] += dp[pos+1][tight && d == limit[pos]]
                              [started || d != 0][update flags with d]
```

**Answer:** `f(R) − f(L−1)`.

**Complexity:** O(#digits × #flags × 10) — effectively O(log n × constant).

### The core intuition to keep

The **tight flag is the trick**: once you've gone below the limit at any digit, everything after is free (no upper bound). Memoize on `(pos, tight, started, flags)` and the exponential digit search collapses to a tiny table.

### 🟢 Solved Problems

None yet — advanced tier.

### ⏳ Next up

- [357 - Count Numbers with Unique Digits](https://leetcode.com/problems/count-numbers-with-unique-digits/) — the natural first digit-DP entry
