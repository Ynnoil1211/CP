# RPC 2026-09 H - Humbertov y su taza de café

**Type:** Binary Search / Answer on Range
**Rating / Context:** Div 3C / Div 2B (UTP Open 2026)
**Tag:** geometric-frustum-volume-bsta

## Key Insight

💡 The accumulated liquid volume in a truncated cone is strictly monotonic with respect to height `x`; perform 100 iterations of Binary Search on Answer over `[0, h]` to reach `< 10^-25` precision.

## Pattern Trigger

"Truncated cone cup with bottom radius `r`, top radius `R`, height `h`. Find fill height `x` for exactly 50% volume with `10^-6` precision."

## Breakthrough

Common factor `(1/3) * pi` cancels completely; evaluate `f(x) = x * (r^2 + rx^2 + r * rx)` directly with `rx = r + (R - r) * (x / h)`.

## Code Spotlight

```cpp
double low = 0.0, high = h_total;
for (int iter = 0; iter < 100; ++iter) {
    double mid = (low + high) / 2.0;
    if (eval_volume(mid, r, R, h) >= target) high = mid;
    else low = mid;
}
cout << fixed << setprecision(9) << low << "\n";
```

## Example

Input: `r = 3.0, R = 3.0, h = 8.8` (cylinder)
Output: `4.400000000`
Why: Constant cross-section divides half volume at exactly half height `8.8 / 2 = 4.4`.

---

**Generated:** 2026-09-26
