# RPC 2026-08 D - Garden of Thorns

**Type:** Math / Formula Development
**Rating:** 2100
**Tag:** linearity-of-expectation-circle-box

## Key Insight

💡 By linearity of expectation, total expected protected value is sum v_i * (Area(D(p_i, r) ∩ [0, w] * [0, h])) / (w * h); solve each plant independently via circle-rectangle clipping.

## Pattern Trigger

"N <= 10 plants with values v_i, random thorn center uniformly distributed in [0, w] * [0, h], find expected sum of protected plant values." Linearity of expectation E[sum X_i] = sum E[X_i] decouples joint probabilities completely.

## Breakthrough

The probability a plant at (x_i, y_i) is protected by a random center (X, Y) within distance r is identical to (X, Y) landing inside the disk D((x_i, y_i), r). The problem reduces purely to intersecting a circle with an axis-aligned box.

## Code Spotlight

```cpp
double expected_val = 0;
for (int i = 0; i < n; i++) {
    double area = circle_rectangle_intersection(x[i], y[i], r, w, h);
    expected_val += v[i] * (area / (w * h));
}
cout << fixed << setprecision(10) << expected_val << "\n";
```

## Example

Input: Garden 10 * 10, N=1 plant at (5, 5), v=10, r=2.
Circle is fully inside garden: Area = pi * 2^2 ≈ 12.56637.
Probability = 12.56637 / 100 ≈ 0.12566.
Expected value = 10 * 0.12566 ≈ 1.256637.
Why: Uniform continuous probability over a 2D domain equals the ratio of valid area to total domain area.

---

**Generated:** 2026-09-13