# 1857A - Array Coloring

**Rating:** 800
**Category:** Math / Parity / Observation
**Solve Time:** 11 minutes
**Confidence:** 5/10

## Problem Summary

Given an array of integers, can we color each element red or blue (each color used at least once) so that the sums of the red elements and blue elements have the same parity (both even or both odd)?

## Key Insight

The parity of the total sum of the array determines everything. If the **total sum is even**, we can always split it into two groups with the same parity (both even or both odd) as long as there is at least one element to put in each group. The only impossible case is when the total sum is odd.

Wait — but the total sum being even is not sufficient by itself if there's only one element of a certain type... Let me re-examine.

Actually, the key observation is simpler: the sum of two numbers has the same parity iff both numbers have the same parity (both even or both odd). So we need `sum(red) ≡ sum(blue) (mod 2)`.

This means `sum(red) + sum(blue) ≡ 2 * sum(red) ≡ 0 (mod 2)`, so the total sum must be even.

But we also need each color to have at least one element. If the total sum is even, can we always achieve this? Let's check:

- If there's at least one even number, put it alone in one color and everything else in the other. Even + even = even sum on both sides... wait, that's not guaranteed.

Actually, let me think again. If total sum is even:
- Total = even. We need two groups with same parity.
- Case 1: If there are at least 2 odd numbers, we can put one odd in each group. The remaining elements (any mix) all have even sum, so distributing them doesn't change parity. Both groups have odd + even = odd sum. ✓
- Case 2: If there are 0 odd numbers (all even), we can put one element in one group and the rest in the other. Even + even = even. But both groups need at least one element, and with n ≥ 2 this works. ✓
- Case 3: If there is exactly 1 odd number, the total sum is odd, so impossible. ✗

So the condition is simply: **the number of odd elements must be even** (which means the total sum is even).

## Solution Approach

### Step 1: Observation

Parity of a sum depends only on the count of odd numbers:
- Even + Even = Even
- Odd + Odd = Even
- Even + Odd = Odd

So `total_sum ≡ count_odd (mod 2)`. If `count_odd` is even, total sum is even.

### Step 2: Algorithm

Count odd numbers. If the count is even → YES, otherwise → NO.

That's it. No need to check anything about even numbers, minimum sizes, etc.

### Step 3: Implementation

```cpp
int n; cin >> n;
int odd = 0;
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x & 1) odd++;
}
cout << (odd % 2 == 0 ? "YES" : "NO") << "\n";
```

### Step 4: Edge Cases

- **n = 2, both odd** → odd count = 2 (even) → YES. Put one odd in each group.
- **n = 2, one odd one even** → odd count = 1 (odd) → NO.
- **n = 2, both even** → odd count = 0 (even) → YES.
- **All odd numbers** → if count is even, YES; if odd, NO.

## Complexity Analysis

- **Time:** O(n) — single pass
- **Space:** O(1) — just two counters

## Why This Works

We need `sum(red) ≡ sum(blue) (mod 2)`. Adding them: `total_sum ≡ 2 * sum(red) ≡ 0 (mod 2)`, so total must be even. Since `total_sum ≡ odd_count (mod 2)`, this is equivalent to `odd_count % 2 == 0`.

And whenever `odd_count` is even (and `n ≥ 2`), we can always construct a valid coloring:
- If `odd_count ≥ 2`: put one odd in red, one odd in blue, everything else arbitrary (they don't change parity).
- If `odd_count == 0` (all even): put any one element alone in red, rest in blue. Both sums are even.

## Common Mistakes

- **Adding unnecessary conditions** — like checking `even == 1 && odd == 1` or `even == odd`. These are irrelevant distractions.
- **Overthinking** the "each color needs at least one element" constraint — it's automatically satisfied for `n ≥ 2` as long as `odd_count` is even.
- **Guessing conditions** instead of deriving them from parity arithmetic — leads to the wrong solution (my first attempt).

## Clean Code

```cpp
void solve() {
    int n; cin >> n;
    int odd = 0;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        odd += x & 1;
    }
    cout << (odd % 2 == 0 ? "YES\n" : "NO\n");
}
```

## Key Takeaway

**Parity problems reduce to counting odds.** Don't chase complex conditions — derive the minimal constraint from `total ≡ 0 (mod 2)` and trust the math. When your confidence is low (5/10), trace through the test cases by hand to verify the simple condition works for all of them.

## Your Code

```cpp
void solve() {
    int n; cin>>n;
    vi vt(n);
    int even = 0, odd = 0;
    for(int i = 0; i<n; i++){
        int x; cin>>x;
        if(x%2==0) even++;
        else odd++;
    }
    if(odd%2==0) cout<<"YES";
    else cout<<"NO";
    cout<<endl;
}
```

> _This is your original solution. Keep it here to track how your coding style evolves over time._

## Code Review

### What's Good

- **Correct final condition** — you landed on `odd % 2 == 0`, which is exactly right.
- **Proper I/O** — simple and direct.
- **You output newlines** — easy to miss, you didn't.

### What Went Wrong (the overcomplicated first attempt)

Your first solution had 5 branches:

```cpp
if(even==0 || odd == 0) cout<<"YES";
else if(even == 1 && odd == 1) cout<<"NO";
else if(even==odd) cout<<"YES";
else if(odd%2==0) cout<<"YES";
else cout<<"NO";
```

The chain is inconsistent and reveals confusion:

| Condition | Result | Correct? |
|---|---|---|
| `even==0` (all odd) | YES | ✅ only if `odd` is even |
| `odd==0` (all even) | YES | ✅ |
| `even==1 && odd==1` | NO | ❌ — this is just `odd=1` which is already NO, but the logic is redundant |
| `even==odd` | YES | ❌ — e.g. n=4 with [1,1,2,2] (even=2, odd=2) is YES, but what about [1,3,2,4]? Also odd=2, still YES. The condition itself isn't wrong, but the approach is fragile. |
| `odd%2==0` | YES | ✅ — this is the actual rule |
| else | NO | ✅ — catches odd count = odd |

The issue is **you had the right condition (`odd % 2 == 0`) buried at position 4**, but earlier branches could override it incorrectly. The `even==0` branch would say YES even when `odd` is odd (impossible for `n≥2` since `even==0 && n≥2` means all odd, so `odd==n≥2`, which is YES only if `n` is even... wait, no. If even==0, that means all elements are odd. If all are odd and there are an odd number of them, total is odd, so NO, not YES. But your code says YES for `even==0`. Let me check: `[1, 3, 5]` → even=0, odd=3. Your code says YES. Is that correct? Total = 9 (odd). Can we split into two groups with same parity? Total is odd, so NO. So your first condition would give a wrong answer for `[1, 3, 5]`!

Actually wait, let me check with the examples. The example doesn't include this case. Let me verify with the problem statement... The correct answer for `[1, 3, 5]` (n=3, all odd) should be NO because total sum is 9 (odd) and you can't split odd into two same-parity sums. So yes, your first branch `if(even==0 || odd == 0)` incorrectly says YES for the all-odd case.

### What the Correct Solution Teaches

The final correct solution is 3 lines of core logic. The lesson: for parity problems, **the only thing that matters is the count of odd numbers**. Even numbers are irrelevant — they contribute 0 mod 2. Forget `even` entirely.

### Why Confidence is 5/10

You understand the condition but still doubt it, probably because you arrived at it through guessing/elimination rather than derivation. To build confidence:

1. Derive from first principles: `total ≡ 0 (mod 2) → odd-count must be even`
2. Verify with hand-traced test cases for each edge case
3. The "each color non-empty" constraint is automatically satisfied when `n ≥ 2`, so don't worry about it

### Suggested Refactor

```cpp
void solve() {
    int n; cin >> n;
    int odd = 0;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        odd += x & 1;      // bitwise is faster than modulo
    }
    cout << (odd & 1 ? "NO\n" : "YES\n");
}
```

---

**Generated:** 2026-07-22
**Next Review:** 2026-07-25
