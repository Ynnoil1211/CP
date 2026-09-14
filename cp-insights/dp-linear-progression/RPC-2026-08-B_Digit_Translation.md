# RPC 2026-08 B - Digit Translation

**Type:** DP / Linear Progression
**Rating:** 1500
**Tag:** simultaneous-min-and-count

## Key Insight

💡 Maintain 1D DP arrays for minimum transformed length and distinct string count simultaneously; when matching digit word suffixes, update min length and add/reset counts.

## Pattern Trigger

"|S| <= 10^6, replace English digit words with '0'-'9', find min length and count of distinct strings achieving that length mod 9302023." Overlapping occurrences (like `"twone"`) rule out greedy choices and force prefix DP.

## Breakthrough

Digit words have lengths 3 to 5 only (O(1) lookback); tracking both dp_len[i] and dp_cnt[i] in a single linear pass prevents exponential branching and duplicate counting across overlapping segments.

## Code Spotlight

```cpp
for (int i = 0; i < n; i++) {
    int bestL = dpL[i] + 1, bestC = dpC[i];
    for (const string& w : NUMS) {
        int m = w.size();
        if (i + 1 >= m && s.compare(i - m + 1, m, w) == 0) {
            int altL = dpL[i - m + 1] + 1, altC = dpC[i - m + 1];
            if (altL < bestL) { bestL = altL; bestC = altC; }
            else if (altL == bestL) bestC = (bestC + altC) % MOD;
        }
    }
    dpL[i + 1] = bestL; dpC[i + 1] = bestC;
}
```

## Example

Input: `"twone"`
Possibility 1: replace `"two"` -> `"2ne"` (length 3)
Possibility 2: replace `"one"` -> `"tw1"` (length 3)
Output: Length `3`, Count `2`
Why: Both substitutions yield length 3, producing 2 distinct string variations at the optimal length.

---

**Generated:** 2026-09-13