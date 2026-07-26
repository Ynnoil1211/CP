# RPC 2026-07 H - You You See What?

**Type:** String / Stack Processing
**Rating:** —
**Tag:** bang-path-elimination

## Key Insight

💡 Two patterns to eliminate: consecutive duplicates (X!X → X) and
three-step loops (X!Y!X → X). A stack processes left to right:
if curr matches top → skip; if curr matches below-top → pop top + skip curr.

## Code Spotlight

```cpp
if (!st.empty() && sameIgnoreCase(curr, st.top())) {
    // Rule 1: consecutive duplicate — skip curr
} else if (st.size() >= 2) {
    string top = st.top(); st.pop();
    if (sameIgnoreCase(curr, st.top())) {
        // Rule 2: loop — skip top AND curr
    } else {
        st.push(top); st.push(curr);
    }
}
```

## Example

Input: `texasam!rice!baylor!csdept!baylor!rice!dev!bresearch!bpoucher`
Output: `texasam!rice!dev!bresearch!bpoucher`
Why: Inner loop `baylor!csdept!baylor` collapses, then outer loop
`rice!...!rice` collapses too, leaving the minimal path.

---

**Generated:** 2026-07-25
