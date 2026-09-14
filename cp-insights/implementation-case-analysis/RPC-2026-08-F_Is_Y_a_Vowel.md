# RPC 2026-08 F - Is Y a Vowel?

**Type:** Implementation / Case Analysis
**Rating:** 800
**Tag:** dual-counter-classification

## Key Insight

💡 Maintain two counters in a single linear pass: increment both for standard vowels $\{a, e, i, o, u\}$, and increment only the second when encountering $'y'$.

## Pattern Trigger

"Count vowels excluding 'y' and vowels including 'y' in a lowercase word of length $\le 50$." Simple dual-metric aggregation on short input strings.

## Breakthrough

Avoid regex overhead or multi-pass string parsing; a direct character-by-character scan cleanly branches vowel membership in $O(|S|)$ time and $O(1)$ auxiliary space.

## Code Spotlight

```cpp
int v1 = 0, v2 = 0;
for (char c : s) {
    if (string("aeiou").find(c) != string::npos) { v1++; v2++; }
    else if (c == 'y') { v2++; }
}
cout << v1 << " " << v2 << "\n";
```

## Example

Input: `"day"`
Trace:
- 'd': consonant
- 'a': standard vowel -> `v1++` (1), `v2++` (1)
- 'y': optional vowel -> `v2++` (2)
Output: `1 2`
Why: 'a' contributes to both counts; 'y' contributes only to the permissive count.

---

**Generated:** 2026-09-13
