# 1857A - Array Coloring

**Type:** Math / Parity Check
**Rating:** 800
**Tag:** parity-counting

## Key Insight

💡 Colorings produce equal-parity sums iff the total sum is even; since even numbers do not affect sum parity, this holds iff the count of odd numbers is even.

## Pattern Trigger

When asked to partition elements into two non-empty sets with equal sum parity:
$$\text{sum}(\text{red}) \equiv \text{sum}(\text{blue}) \pmod 2 \implies \text{sum}(\text{all}) = \text{sum}(\text{red}) + \text{sum}(\text{blue}) \equiv 2 \cdot \text{sum}(\text{red}) \equiv 0 \pmod 2$$
The count of odd elements directly determines the total parity mod 2.

## Breakthrough

Parity problems reduce entirely to counting odd numbers. Even numbers contribute $0 \pmod 2$ and can be distributed arbitrarily without altering parity, completely eliminating the need for complex branch checks.

## Code Spotlight

```cpp
int odd = 0;
for (int i = 0, x; i < n; i++) {
    cin >> x;
    odd += x & 1;
}
cout << (odd % 2 == 0 ? "YES\n" : "NO\n");
```

## Example

Input: `a = [1, 2, 4, 3, 2, 3, 5, 4]` (odds: 1, 3, 3, 5 -> 4 odd elements)
Output: `YES`
Why: 4 odd numbers can be partitioned into 2 and 2 across red and blue; each side gets an even sum. If there were an odd number of odds, the total sum would be odd and impossible to split into two numbers of equal parity.

---

**Generated:** 2026-09-13
