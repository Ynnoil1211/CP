# 1837A - Grasshopper on a Line

**Type:** Math / Modular Arithmetic
**Rating:** 800
**Tag:** divisibility-splitting

## Key Insight

💡 If x is not divisible by k, one jump of x works since x itself is a
valid jump distance. If x is divisible by k, two jumps always work:
jump 1 (never divisible by k when k ≥ 2) and then x−1 (≡ −1 mod k, so
also safe).

## Code Spotlight

```cpp
if (x % k != 0) {
    cout << "1\n" << x << "\n";
} else {
    cout << "2\n1 " << x - 1 << "\n";
}
```

## Example

Input: `x=10, k=2` → 10 is divisible by 2 → need 2 moves
Output: `[1, 9]` (1 + 9 = 10, neither divisible by 2)
Why: When the target is a multiple of k, split it into 1 + (target-1).
1 is always safe, and target-1 differs from a multiple of k by 1.

---

**Generated:** 2026-07-24
