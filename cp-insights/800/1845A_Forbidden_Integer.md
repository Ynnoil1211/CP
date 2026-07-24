# 1845A - Forbidden Integer

**Rating:** 800
**Algorithm:** Constructive / Greedy / Math

## Key Insight

💡 If 1 is available (x≠1), use n copies of 1. If 1 is forbidden (x=1),
build n with 2s and at most one 3 — impossible only when k=1 (nothing
available) or k=2 with odd n (can't sum to odd with only 2s).

## Code Spotlight

```cpp
if (x != 1) {
    cout << "YES\n" << n << "\n";
    for (int i = 0; i < n; i++) cout << "1 ";
    cout << "\n";
} else {
    if (k == 1 || (k == 2 && n % 2 == 1)) { cout << "NO\n"; return; }
    cout << "YES\n";
    if (n % 2 == 0) { /* n/2 copies of 2 */ }
    else            { /* (n/2-1) copies of 2 + one 3 */ }
}
```

## Example

Input: `n=5, k=2, x=1` → can only use 2, can't sum 5 (odd) → **NO**
Input: `n=7, k=3, x=1` → use 2+2+3 = 7 → **YES: [2, 2, 3]**
Why: Available set {2, 3}. Even n uses all 2s, odd n replaces one 2 with a 3.

---

**Generated:** 2026-07-24
