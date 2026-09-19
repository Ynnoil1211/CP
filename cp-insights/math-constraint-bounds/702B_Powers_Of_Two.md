# Codeforces 702B - Powers of Two

**Type:** Math / Constraint Bounds
**Rating / Context:** 1500 / Educational Codeforces Round 15
**Tag:** powers-of-two-complement-frequency

## Key Insight

💡 Since `a_i <= 10^9`, any pair sum `a_i + a_j <= 2 * 10^9 < 2^31`. There are only 31 possible power-of-two targets (`2^0` through `2^30`). Instead of testing all pairs in `O(N^2)`, iterate over the 31 candidate powers and query the frequency of complement `(1LL << k) - a[i]` in `O(31 * N)`.

## Pattern Trigger

Pairs satisfying a target sum condition `a_i + a_j = TARGET` where each `a_i <= 10^9` and the set of valid targets is heavily bounded (`TARGET in {2^0, 2^1, ..., 2^30}`, only 31 values), while `N <= 10^5` rules out exhaustive `O(N^2)` pair evaluation.

## Breakthrough

Avoid computing target sets in `std::set<long long>` or binary searching sum arrays; compute powers on the fly in `O(1)` with bit shifts. Beware of 32-bit signed integer overflow with `1 << 31` (which invokes undefined behavior in C++ and wraps to negative); always cast to 64-bit with `1LL << k`. Accumulating frequency counts in a hash map during a single pass automatically prevents self-pairing, avoids double-counting, and achieves `O(31 * N)` time.

## Code Spotlight

```cpp
map<int, int> freq;
long long ans = 0;
for (int i = 0; i < n; i++) {
    for (int k = 0; k <= 30; k++) {
        long long complement = (1LL << k) - a[i];
        if (freq.count(complement)) {
            ans += freq[complement];
        }
    }
    freq[a[i]]++;
}
```

## Example

Input: `a = [7, 3, 2, 1]`  
- At `i = 0` (`7`): `freq = {7: 1}`, `ans = 0`  
- At `i = 1` (`3`): no complement exists in `freq`, `freq = {7: 1, 3: 1}`, `ans = 0`  
- At `i = 2` (`2`): no complement exists in `freq`, `freq = {7: 1, 3: 1, 2: 1}`, `ans = 0`  
- At `i = 3` (`1`): for `k = 2` (`4`), `4 - 1 = 3` (`freq[3] = 1`); for `k = 3` (`8`), `8 - 1 = 7` (`freq[7] = 1`) -> `ans = 2`  
Output: `2` (valid pairs are `(7, 1)` and `(3, 1)`)  
Why: Bounding sum targets to the 31 powers of two transforms an intractable `O(N^2)` pair search into 31 constant-factor frequency lookups per element.

---

**Generated:** 2026-09-19
