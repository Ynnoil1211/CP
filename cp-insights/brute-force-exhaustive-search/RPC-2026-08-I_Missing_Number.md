# RPC 2026-08 I - Missing Number

**Type:** Brute Force / Exhaustive Search
**Rating:** 1400
**Tag:** prefix-length-bounded-simulation

## Key Insight

💡 The starting number a < 10^5 has length L in [1, 5]; try all 5 initial prefix lengths, deterministically verifying consecutive number parsing with at most one missing number.

## Pattern Trigger

"Concatenation of consecutive integers a ... b with b < 10^5 has one eaten number; find all candidate missing numbers." Upper bound b < 100000 restricts the starting number to at most 5 digits.

## Breakthrough

Fixing the first number's length (1 <= L <= 5) completely removes all branching ambiguity; from a, each subsequent segment must deterministically match cur+1 or jump to cur+2 (eaten number), running linearly in O(|S|) time.

## Code Spotlight

```cpp
for (int len = 1; len <= 5 && len <= s.size(); len++) {
    int cur = stoi(s.substr(0, len)), idx = len, skip = -1;
    bool ok = true;
    while (idx < s.size()) {
        string n1 = to_string(cur + 1), n2 = to_string(cur + 2);
        if (s.compare(idx, n1.size(), n1) == 0) { idx += n1.size(); cur++; }
        else if (skip == -1 && s.compare(idx, n2.size(), n2) == 0) {
            skip = cur + 1; idx += n2.size(); cur += 2;
        } else { ok = false; break; }
    }
    if (ok) record_candidates(skip, cur, start);
}
```

## Example

Input: `"891112"`
Try L=1: starts at 8.
- Matches '9' -> cur = 9
- Fails on '10', but matches '11' -> skip = 10, cur = 11
- Matches '12' -> cur = 12
String consumed completely with exactly one skipped number: 10.
Output: `1\n10`
Why: Testing all 5 possible prefix lengths reveals every valid decomposition.

---

**Generated:** 2026-09-13