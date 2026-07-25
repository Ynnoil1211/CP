# 1527B1 - Palindrome Game (easy version)

**Type:** Game Theory / Parity Turn
**Rating:** 1200
**Tag:** zero-count-parity

## Key Insight

💡 Zero-count parity decides who exploits the free reverse. Even c → Bob
reverses to make Alice pay for the last zero. Odd c ≥ 3 → Alice flips
the center first (keeping it palindrome), then uses reverse against Bob.
c = 1 → Alice forced to flip the only zero, Bob wins for free.

## Code Spotlight

```cpp
int zeros = count(s.begin(), s.end(), '0');
if (zeros == 1 || zeros % 2 == 0) cout << "BOB\n";
else cout << "ALICE\n";
```

## Example

Input: `s = "1001"` (n=4, palindrome, zeros=2)
Output: `BOB`
Why: Alice flips a zero → $1. Bob reverses (free). Alice flips the
remaining zero → $1 more. Alice $2, Bob $0 → Bob wins.

---

**Generated:** 2026-07-25
