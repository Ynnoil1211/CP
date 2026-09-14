# RPC 2026-08 J - Tip of Your Tongue

**Type:** String / Pattern Build
**Rating:** 1900
**Tag:** rolling-hash-pie

## Key Insight

💡 Prefix and suffix have identical length $L$; precalculate rolling prefix, suffix, and joint hashes by length, then resolve AND, OR, XOR queries in $O(1)$ via the Principle of Inclusion-Exclusion.

## Pattern Trigger

"$N, Q \le 2 \cdot 10^5$, queries AND, OR, XOR on prefix and suffix patterns with $|p| = |s| = L$, total characters $\le 10^6$." Uniform query length allows bucketing patterns strictly by length.

## Breakthrough

By Principle of Inclusion-Exclusion:
$$\text{OR}(p, s) = |A| + |B| - |A \cap B|, \quad \text{XOR}(p, s) = |A| + |B| - 2|A \cap B|$$
Storing counts in double-hash tables indexed by length $L$ enables $O(1)$ response time per query after $O(\sum |W|)$ preprocessing.

## Code Spotlight

```cpp
int a = pre_cnt[L][hash_p];
int b = suf_cnt[L][hash_s];
int ab = joint_cnt[L][combine(hash_p, hash_s)];

if (op == "AND") cout << ab << "\n";
else if (op == "OR") cout << a + b - ab << "\n";
else if (op == "XOR") cout << a + b - 2 * ab << "\n";
```

## Example

Input: Dictionary = `["cat", "car"]`, Query = `OR ca ar` ($L=2$)
- Words with prefix "ca": `{"cat", "car"}` ($|A| = 2$)
- Words with suffix "ar": `{"car"}` ($|B| = 1$)
- Words with both: `{"car"}` ($|A \cap B| = 1$)
OR evaluation: $2 + 1 - 1 = 2$.
Output: `2`
Why: Set-theoretic identities transform combinatorial string matching into three constant-time frequency lookups.

---

**Generated:** 2026-09-13
