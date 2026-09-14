# 1859A - United We Stand

**Type:** Greedy / Value Splitting
**Rating:** 800
**Tag:** max-value-separation

## Key Insight

💡 A number cannot divide anything strictly smaller than itself; placing all occurrences of max(a) in c and all other elements in b guarantees that no c_j divides any b_i.

## Pattern Trigger

"Partition array into two non-empty arrays b and c such that no element of c divides any element of b." Divisibility requires c_j <= b_i. Hence, setting all elements of c strictly greater than all elements of b mechanically eliminates any possible divisor relationship.

## Breakthrough

Separating strictly by max value (c = {max(a)}) makes divisibility impossible from c to b, while any all-equal array immediately yields -1 because b would be empty.

## Code Spotlight

```cpp
int mx = *max_element(a.begin(), a.end());
for (int x : a) (x == mx ? c : b).push_back(x);
if (b.empty()) cout << -1 << "\n";
else {
    cout << b.size() << " " << c.size() << "\n";
    for (int x : b) cout << x << " "; cout << "\n";
    for (int x : c) cout << x << " "; cout << "\n";
}
```

## Example

Input: `a = [2, 3, 4, 4]`
Output: `b = [2, 3]`, `c = [4, 4]`
Why: max(a) = 4. 4 > 2 and 4 > 3, so 4 cannot divide either element. The divisibility constraint only runs from c to b, not vice versa.

---

**Generated:** 2026-09-13